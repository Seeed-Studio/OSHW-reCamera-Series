#!/bin/sh

change_name() {
    TEMP_FILE=$(mktemp)
    chmod 660 $TEMP_FILE
    sed "s/$1:x/$2:x/g" /etc/passwd > "$TEMP_FILE" && cp "$TEMP_FILE" /etc/passwd
    sed "s/$1:/$2:/g" /etc/shadow > "$TEMP_FILE" && cp "$TEMP_FILE" /etc/shadow
    rm $TEMP_FILE
}

verify_passwd() {
    old_passwd="`cat /etc/secret`"
    input_passwd="`echo $1 | sha256sum`"

    if [ "$old_passwd" == "$input_passwd" ]; then
        echo "OK"
    else
        echo "ERROR"
    fi
}

change_passwd() {
    TEMP_FILE=$(mktemp)
    TEMP_ERR_FILE=$(mktemp)
    passwd $1 > $TEMP_FILE 2> $TEMP_ERR_FILE << EOF
$3
$3
EOF

    res=`cat $TEMP_ERR_FILE | grep "unchanged"`

    if [ -z "$res" ]; then
        echo "OK"
    else
        echo "ERROR"
        cat $TEMP_FILE | tail -1
    fi

    rm $TEMP_FILE
    rm $TEMP_ERR_FILE
}

cal_key() {
    TEMP_FILE=$(mktemp)
    echo "$1" > $TEMP_FILE
    ssh-keygen -lf $TEMP_FILE 2>/dev/null | awk '{printf $2 " "}'
    echo -n "$2"
    cat $TEMP_FILE | awk -F# '{print $2 " " }'
    rm $TEMP_FILE
}

query_key() {
    filename="/home/recamera/.ssh/authorized_keys"
    if [ ! -f "$filename" ]; then
        mkdir -p /home/recamera/.ssh
        touch $filename
    fi

    num=1
    while IFS= read -r line; do
        cal_key "$line" $num
        num=$((num + 1))
    done < "$filename"
}

case $1 in
id)
    cat /etc/passwd | grep -e "/home.*/bin/.*sh" | awk -F':' '{ print $3 }'
    ;;

name)
    change_name $2 $3
    ;;

verify)
    verify_passwd $2
    ;;

passwd)
    change_passwd $2 $3 $4
    ;;

save)
    echo $2 | sha256sum > /etc/secret
    ;;

query_key)
    query_key
    ;;

verify_key)
    ssh-keygen -lf $2 >/dev/null 2>&1
    if [ 0 -eq $? ]; then
        echo "OK"
    else
        echo "Failed"
    fi
    ;;
esac
