#!/bin/bash

IPK_PATH=$(dirname $1)
OUTPUT_PATH=$IPK_PATH/output
PACKAGE_NAME=$2
PACKAGE_VERSION=$3

function generateBinary() {
    cd $IPK_PATH

    echo "2.0" > linux-binary
}

function generateControl() {
    mkdir -p $IPK_PATH/control
    cd $IPK_PATH/control

    touch control postinst postrm prerm
    chmod 755 ./postinst ./postrm ./prerm

    cat << EOF >> ./control
Package: $PACKAGE_NAME
Version: $PACKAGE_VERSION
Depends:
Section: app
Maintainer: Seeed <seeedstudio.cn>
Architecture: riscv64
Installed-Size: 200000000
Description: $PACKAGE_NAME is a app of reCamera.
EOF

    cat << EOF >> ./postinst
#!/bin/sh
echo "App install completed" && exit 0
EOF

    cat << EOF >> ./prerm
#!/bin/sh
echo "Start uninstalling the app" && exit 0
EOF

    cat << EOF >> ./postrm
#!/bin/sh
echo "App uninstall completed" && exit 0
EOF

    tar zcf $IPK_PATH/control.tar.gz ./*
}

function generateData() {
    cd $IPK_PATH
    cp app.zip data.tar.gz
}

function generateIpkContent() {
    generateBinary
    generateControl
    generateData
}

function generateIpk() {
    [ ! -d $OUTPUT_PATH ] && mkdir -p $OUTPUT_PATH

    cd $IPK_PATH && tar zc ./data.tar.gz ./control.tar.gz ./linux-binary > $OUTPUT_PATH/app.ipk
}

function cleanFile() {
    rm -rf $IPK_PATH/control*
    rm -rf $IPK_PATH/linux-binary
    rm -rf $IPK_PATH/data.tar.gz
}

generateIpkContent
generateIpk && cleanFile && echo "Finished" && exit 0
echo "ERROR"
