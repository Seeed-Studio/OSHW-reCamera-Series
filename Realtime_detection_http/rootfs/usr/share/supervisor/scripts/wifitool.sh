#!/bin/sh

ifname=wlan0
hostapdFile=/etc/hostapd_2g4.conf
IFS=""
CTRL_FILE=/tmp/upgrade.ctrl
LATEST_FILE=/tmp/upgrade.latest
START_FILE=/tmp/upgrade.start

clean_upgrade_file() {
    pid="`pidof upgrade.sh`"

    if [ -z "$pid" ]; then
        if [ -f "$CTRL_FILE" ]; then
            rm -rf $CTRL_FILE
        fi
        if [ -f "$START_FILE" ]; then
            rm -rf $START_FILE
        fi
        if [ -f "$LATEST_FILE" ]; then
            rm -rf $LATEST_FILE
        fi
    fi
}

get_wifi_scan_results() {
    wpa_cli -i wlan0 scan_results | tail -n +2 | while read -r line
    do
        printf "%b\n" $line | awk -F'\t' '$5 != "" {print $5 "\t" $3 "\t" $4 "\t" $1}'
    done
}

list_wifi() {
    # wpa_cli -i wlan0 list_networks | tail -n +2 | awk '{print $1, $2, $4}'
    wpa_cli -i wlan0 list_networks | tail -n +3 | while read -r line
    do
        printf "%b\n" $line | awk -F'\t' '{print $1 "\t" $2 "\t" $4}'
    done
}

connect_wifi() {
    ssid="'"'"'$1'"'"'"
    passwd="'"'"'$2'"'"'"

    id=`wpa_cli -i wlan0 add_network`
    echo $id

    ret=`echo $ssid | xargs wpa_cli -i wlan0 set_network $id ssid`
    if [ $ret == "OK" ]; then
        ret=`echo $passwd | xargs wpa_cli -i wlan0 set_network $id psk`
        if [ $ret == "OK" ]; then
            wpa_cli -i wlan0 enable_network $id
            wpa_cli -i wlan0 select_network $id
        else
            echo "Invalid password"
            wpa_cli -i wlan0 remove_network $id 1> /dev/null
        fi
    fi
}

wifi_status() {
    ret=$(wpa_cli -i wlan0 status)
    printf "%b" "$ret" | awk -F= '/ssid/ {ssid=$2} /key_mgmt/ {key_mgmt=$2} /ip_address/ {ip_address=$2} /address/ {address=$2} END {printf "%s\n%s\n%s\n%s\n", ssid, key_mgmt, ip_address, address}'
}

case $1 in
wifi_valid)
    if [ -z "$(ifconfig wlan0 2>/dev/null)" ]; then
        echo "0"
    else
        echo "1"
    fi
    ;;

start)
    if [ -z "$(ifconfig wlan1 2> /dev/null)" ]; then
        iw dev wlan0 interface add wlan1 type __ap;
    fi

    if [ "$2" ]; then
        sed -i "s/ssid=.*$/ssid=$2/g" $hostapdFile
        sync
    fi

    ifconfig wlan1 up
    wpa_supplicant -B -i wlan0 -c /etc/wpa_supplicant.conf
    hostapd -B $hostapdFile

    export PS1='[\u@\h]\w\$ '
    ttyd -p $3 -u $4 login > /dev/null 2>&1 &

    if [ -c /dev/null ]; then
        chmod 666 /dev/null
    fi

    clean_upgrade_file
    ;;

stop)
    kill -9 `pidof wpa_supplicant`
    kill -9 `pidof hostapd`
    kill -9 `pidof ttyd`
    ifconfig wlan1 down

    clean_upgrade_file
    ;;

start_ap)
    if [ ! "`pidof hostapd`" ]; then
        ifconfig wlan1 up
        hostapd -B $hostapdFile
    fi
    ;;

stop_ap)
    kill -9 `pidof hostapd`
    ifconfig wlan1 down
    ;;

state)
    wpa_cli -i wlan0 status | grep "^wpa_state" | awk -F= '{print $2}'
    ;;

get_gateway)
    iproute | grep default | grep "$2" | awk '{print $3}'
    ;;

scan)
    wpa_cli -i wlan0 scan
    ;;

scan_results)
    get_wifi_scan_results
    ;;

list)
    list_wifi
    ;;

connect)
    connect_wifi $2 $3
    wpa_cli -i wlan0 save_config
    ;;

connect_status)
    wpa_cli -i wlan0 status | grep "^wpa_state" | awk -F= '{print $2}'
    ;;

auto_connect)
    if [ "$3" == "1" ]; then
        wpa_cli -i wlan0 enable_network $2
    else
        wpa_cli -i wlan0 disable_network $2
    fi
    wpa_cli -i wlan0 save_config
    ;;

get_wifi_id)
    id="`wpa_cli -i wlan0 status | grep "^id" | awk -F= '{print $2}'`"
    if [ ! "$id" ]; then
        id="-1"
    fi
    echo $id
    ;;

get_wifi_ip)
    wpa_cli -i wlan0 status | grep "^ip_address" | awk -F= '{print $2}'
    ;;

select)
    echo $2
    wpa_cli -i wlan0 select_network $2
    ;;

disconnect)
    wpa_cli -i wlan0 disconnect
    ;;

status)
    wifi_status
    ;;

remove)
    wpa_cli -i wlan0 disable_network $2
    wpa_cli -i wlan0 remove_network $2
    wpa_cli -i wlan0 save_config
    ;;

passwd)
    if [ "$2" ]; then
        sed -i "s/wpa_passphrase=.*$/wpa_passphrase=$2/g" $hostapdFile
        sync
    else
        echo ""
    fi
    ;;

esac
