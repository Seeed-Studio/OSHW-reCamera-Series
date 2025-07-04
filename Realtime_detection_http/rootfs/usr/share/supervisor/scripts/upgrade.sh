#!/bin/sh

RECAMERA_URL=https://files.seeedstudio.com/reCamera
LATEST_URL=https://files.seeedstudio.com/reCamera/latest
LATEST_VERSION_FILE=/tmp/latest

MD5_FILE=sg2002_recamera_emmc_md5sum.txt
URL_FILE=url.txt
ZIP_FILE=zip.txt

RECV_PARTITION=/dev/mmcblk0p5
ROOTFS=/dev/mmcblk0p3
ROOTFS_B=/dev/mmcblk0p4
ROOTFS_FILE=rootfs_ext4.emmc
LATEST_PATH=/tmp/latest.upgrade
DOWNLOAD_PATH=/tmp/download.upgrade

ACTION=$1
PERCENTAGE=0
PERCENTAGE_FILE=/tmp/upgrade.percentage
CTRL_FILE=/tmp/upgrade.ctrl
LATEST_FILE=/tmp/upgrade.latest
RESULT_LATEST_FILE=/tmp/upgrade_result.latest
RESULT_MD5_FILE=/tmp/upgrade_md5.latest
START_FILE=/tmp/upgrade.start
VERSION_FILE=/tmp/upgrade.version

function clean_up() {
    # if [ ! -z $MOUNTPATH ]; then
    #     umount $MOUNTPATH
    #     rm -rf $MOUNTPATH
    # fi
    rm -rf $CTRL_FILE

    if [ "$ACTION" = "start" ]; then
        rm -rf $START_FILE
    else
        rm -rf $LATEST_FILE
    fi
}

function write_percent() {
    echo $PERCENTAGE > $PERCENTAGE_FILE

    if [ -f $CTRL_FILE ]; then
        stop_it=$(cat $CTRL_FILE)
        if [ "$stop_it" = "stop" ]; then
            echo "Stop upgrade."
            clean_up
            exit 2
        fi
    fi
}

function exit_upgrade() {
    write_percent
    clean_up
    exit $1
}

function exit_latest() {
    clean_up
    exit 1
}

function write_upgrade_flag() {
    fw_setenv use_part_b $1
    fw_setenv boot_cnt 0
    fw_setenv boot_failed_limits 5
    fw_setenv boot_rollback
}

function get_mirror_url() {
    channel=$(cat /etc/upgrade | awk -F',' '{print $1}')
    if [ "$channel" != "0" ]; then
        echo ""
        return
    fi

    result=$(wget_file $LATEST_URL $LATEST_VERSION_FILE)
    if [ $result != "OK" ]; then
        echo ""
        return
    fi

    version=$(cat $LATEST_VERSION_FILE)
    rm -rf $LATEST_VERSION_FILE
    if [ -z $version ]; then
        echo ""
        return
    fi

    echo "$RECAMERA_URL/$version/$MD5_FILE"
}

function get_upgrade_url() {
    local url=$1
    local full_url=$url

    if [[ $url =~ .*\.txt$ ]]; then
        full_url=$url
    else
        url=$(curl -skLi $url --connect-timeout 2 | grep -i '^location:.*tag.*' | awk '{print $2}' | sed 's/^"//;s/"$//')
        if [ -z "$url" ]; then
            echo "$(get_mirror_url)"
            return 1
        fi

        url=$(echo "$url" | sed 's/tag/download/g')
        full_url=$url/$MD5_FILE
    fi

    echo $full_url
    return 0
}

function check_version() {
    issue=""
    if [ -f "/etc/issue" ]; then
        issue=$(cat /etc/issue)
    fi
    if [ -z "$issue" ]; then
        echo "Failed,No issue file."
        return
    fi

    os_name=$(echo $issue | awk '{print $1}')
    os_version=$(echo $issue | awk '{print $2}')

    if [ $os_name != $1 ]; then
        echo "YES,OS name is not match(current:$os_name != $1)."
        return
    else
        if [ $os_version != $2 ]; then
            echo "YES,OS version is not match(current:$os_version != $2). "
            return
        else
            echo "NO,OS version is match."
        fi
    fi
}

function mount_recovery() {
    fs_type=$(blkid -o value -s TYPE $RECV_PARTITION)
    if [ "$fs_type" != "ext4" ]; then
        mkfs.ext4 $RECV_PARTITION

        # check again
        fs_type=$(blkid -o value -s TYPE $RECV_PARTITION)
        if [ "$fs_type" != "ext4" ]; then
            echo "Recovery partition is not ext4!"
            return 1
        fi
    fi

    if [ -d "$MOUNTPATH" ]; then
        mount_result=$(mount | grep "$MOUNTPATH")
        if [ "$mount_result" ]; then
            echo "Already mount $RECV_PARTITION on $MOUNTPATH."
            return 0
        else
            rm -rf $MOUNTPATH/*
        fi
    else
        mkdir -p $MOUNTPATH
    fi

    mount $RECV_PARTITION $MOUNTPATH
    if mount | grep -q "$RECV_PARTITION on $MOUNTPATH type"; then
        echo "Mount $RECV_PARTITION on $MOUNTPATH ok."
        return 0
    else
        echo "Mount $RECV_PARTITION on $MOUNTPATH failed."
        return 2
    fi
}

function wget_file() {
    wget -T 10 -t 3 -c -q --no-check-certificate $1 -O $2

    if [ "$?" = "0" ]; then
        echo "OK"
    else
        echo "Failed"
    fi
}

function is_use_partition_b() {
    root_dev=$(mountpoint -n /)
    root_dev=${root_dev%% *}

    if [ "$root_dev" = "$(realpath $ROOTFS_B)" ]; then
        return 1
    else
        return 0
    fi
}

function download_file() {
    MOUNTPATH=$DOWNLOAD_PATH
    result=$(mount_recovery)

    if [ $? -ne 0 ]; then
        echo "mount directory failed"
        return 1
    fi

    zip_txt="$MOUNTPATH/$ZIP_FILE"
    url_txt="$MOUNTPATH/$URL_FILE"

    if [[ ! -f $zip_txt || ! -f $url_txt ]]; then
        echo "Failed"
        return 1
    fi

    zip=$(cat $zip_txt | awk '{print $2}')
    md5=$(cat $zip_txt | awk '{print $1}')
    full_url=$(cat $url_txt)
    full_path=$MOUNTPATH/$zip

    find "$MOUNTPATH" -name "*.zip" | grep -v $zip | xargs rm -rf

    if [ -f "$full_path" ]; then
        if [ "$1" = "start" ]; then
            while true
            do
                pid=$(ps | grep wget | grep ota.zip)
                if [ -z "$pid" ]; then
                    break
                fi

                sleep 1
            done
        else
            if [ "`ps | grep wget | grep ota.zip`" ]; then
                echo "Failed, Firmware is downloading"
                return 0
            fi
        fi

        if [ ! -f "$RESULT_MD5_FILE" ]; then
            md5sum $full_path > $RESULT_MD5_FILE
        fi
        current_md5="`cat $RESULT_MD5_FILE | awk '{print $1}'`"
        if [ "$current_md5" == "$md5" ]; then
            echo "OK"
            return 0
        else
            rm -rf $RESULT_MD5_FILE
        fi
    fi

    channel=$(cat /etc/upgrade | awk -F',' '{print $1}')
    if [ "$channel" = "0" ]; then
        version=$(cat $VERSION_FILE | awk -F' ' '{print $2}')
        mirror_url="https://files.seeedstudio.com/reCamera/$version/$zip"

        result=$(wget_file $mirror_url $full_path)
        if [ "$result" == "OK" ]; then
            current_md5="`md5sum $full_path | awk '{print $1}'`"
            if [ "$current_md5" != "$md5" ]; then
                echo "Failed, Firmware download error"
                rm -rf $full_path
                return 1
            fi

            echo $result
            echo "$current_md5" > $RESULT_MD5_FILE
            return 0
        else
            echo "" > $RESULT_MD5_FILE
        fi
    fi

    result=$(wget_file $full_url $full_path)
    if [ "$result" == "OK" ]; then
        current_md5="`md5sum $full_path | awk '{print $1}'`"
        if [ "$current_md5" != "$md5" ]; then
            echo "Failed, Firmware download error"
            rm -rf $full_path
            return 1
        fi

        echo $result
        echo "$current_md5" > $RESULT_MD5_FILE
    else
        echo $result
        echo "" > $RESULT_MD5_FILE
    fi
}

# trap `rm -rf $CTRL_FILE` SIGINT

case $1 in
latest)
    if [ -z "$2" ]; then echo "Usage: $0 latest <url>"; exit 1; fi
    if [ -f $LATEST_FILE ]; then echo "Failed,latest is running."; exit 1; fi
    echo "" > $LATEST_FILE

    MOUNTPATH=$LATEST_PATH
    result=$(mount_recovery)
    if [ $? -ne 0 ]; then
        echo "Failed, mount recovery"
        exit_latest
    fi

    if [ -f "$RESULT_LATEST_FILE" ]; then
        base_url=$(echo $2 | sed 's/\/latest$//')
        last_url="`cat $MOUNTPATH/$URL_FILE | cut -c 1-${#base_url}`"

        if [ "$last_url" = "$base_url" ]; then
            result="`cat $RESULT_LATEST_FILE`"
            if [[ "$result" == "NO*" ]]; then
                rm -rf $RESULT_LATEST_FILE
            else
                echo "$result"
                exit_latest
            fi
        else
            rm -rf $RESULT_LATEST_FILE
        fi
    fi

    url_md5=$(get_upgrade_url $2)
    if [ -z $url_md5 ]; then
        echo "Failed, get upgrade url"
        exit_latest
    fi

    md5_txt=$MOUNTPATH/$MD5_FILE
    wget_file $url_md5 $md5_txt >/dev/null 2>&1

    zip_txt=$MOUNTPATH/$ZIP_FILE
    echo $(cat $md5_txt | grep ".*ota.*\.zip") > $zip_txt
    rm -rf $md5_txt

    zip=$(cat $zip_txt | awk '{print $2}')
    if [ -z "$zip" ]; then
        echo "Failed, get zip txt"
        rm -rfv $zip_txt
        exit_latest
    fi

    os_name=$(echo "$zip" | awk -F'_' '{print $2}')
    os_version=$(echo "$zip" | awk -F'_' '{print $3}')
    if [ -z "$os_name" ] || [ -z "$os_version" ]; then
        echo "Failed, get os name and version"
        rm -rfv $zip_txt
        exit_latest
    fi

    result=$(check_version $os_name $os_version)
    echo "$result"

    echo "$result" > $RESULT_LATEST_FILE
    echo "$os_name $os_version" > $VERSION_FILE
    echo "${url_md5%/*}/$zip" > $MOUNTPATH/$URL_FILE
    exit_latest
    ;;

start)
    if [ -f $CTRL_FILE ]; then echo "Upgrade is running."; exit 1; fi
    echo "" > $CTRL_FILE
    echo "" > $START_FILE

    step=0
    PERCENTAGE=0
    write_percent

    let step+=1
    echo "Step$step: Mount recovery partition"
    MOUNTPATH=$(mktemp -d)
    result=$(mount_recovery)
    if [ $? -eq 0 ]; then
        PERCENTAGE=20
    else
        echo "Step$step: failed."
        PERCENTAGE=20,"$result"
        exit_upgrade 1
    fi
    write_percent

    if [ -z $2 ]; then
        let step+=1
        echo "Step$step: download firmware"
        result=$(download_file start)
        if [ "$result" = "OK" ]; then
            PERCENTAGE=40
        else
            PERCENTAGE=40,"download firmware failed"
            exit_upgrade 1
        fi
        write_percent
    else
        if [ $2 = "." ]; then
            full_path=$(ls -t $MOUNTPATH | grep -E '.*\.zip' | head -n 1)
            full_path=$MOUNTPATH/$full_path
        else
            full_path=$2
        fi
        full_path=$(realpath $full_path)

        let step+=1
        echo "Step$step: Use local: $full_path"
    fi

    zip=$(cat $MOUNTPATH/$ZIP_FILE | awk '{print $2}')
    full_path=$MOUNTPATH/$zip

    read_md5=$(unzip -p $full_path md5sum.txt | grep "$ROOTFS_FILE" | awk '{print $1}')
    let step+=1
    echo "Step$step: Read $ROOTFS_FILE md5: $read_md5"
    PERCENTAGE=50
    write_percent

    is_use_partition_b
    if [ $? -eq 1 ]; then
        target=$ROOTFS
    else
        target=$ROOTFS_B
    fi
    let step+=1
    file_size=$(unzip -l "$full_path" | grep "$ROOTFS_FILE" | awk '{print $1}')
    let file_size/=1024*1024
    echo "Step$step: Writing rootfs $target size=${file_size}MB"
    if [ $file_size -eq 0 ]; then
        echo "Step$step: failed."
        PERCENTAGE=70,"Read file size is 0."
        exit_upgrade 1
    fi
    unzip -p $full_path $ROOTFS_FILE | dd of=$target bs=1M
    PERCENTAGE=70
    write_percent

    let step+=1
    echo "Step$step: Calc $target md5"
    partition_md5=$(dd if=$target bs=1M count=$file_size 2>/dev/null | md5sum | awk '{print $1}')
    echo "$target md5: $partition_md5"
    PERCENTAGE=80
    write_percent

    let step+=1
    echo "Step$step: Check $target md5"
    if [ "$partition_md5" = "$read_md5" ]; then
        PERCENTAGE=90
        if [ "$target" = "$ROOTFS" ]; then
            write_upgrade_flag 0
            echo "Step$step: change to rootfs A"
        elif [ "$target" = "$ROOTFS_B" ]; then
            write_upgrade_flag 1
            echo "Step$step: change to rootfs B"
        fi
    else
        echo "Step$step: failed: md5 not match."
        PERCENTAGE=90,"Partition md5 check failed."
        exit_upgrade 1
    fi
    sync
    sleep 1

    PERCENTAGE=100
    echo "Finished!"
    exit_upgrade 0
    ;;

rollback)
    is_use_partition_b
    if [ $? -eq 1 ]; then
        write_upgrade_flag 0
        echo "Finished: rollback to rootfs A."
    else
        write_upgrade_flag 1
        echo "Finished: rollback to rootfs B."
    fi
    echo "Restart to valid."
    ;;

download)
    download_file
    ;;

stop)
    echo "stop" > $CTRL_FILE
    pid="`pidof unzip`"
    if [ "$pid" ]; then
        kill $pid
    fi
    pid="`pidof dd`"
    if [ "$pid" ]; then
        kill $pid
    fi
    ;;

query)
    if [ -f $PERCENTAGE_FILE ]; then
        cat $PERCENTAGE_FILE
    else
        echo "0"
    fi
    ;;

recovery)
    echo "Start recovery"
    /mnt/system/upgrade.sh start .
    ;;

*)
    echo "Usage: $0 {latest|start|rollback|stop|query|recovery}"
    exit 1
    ;;

esac
