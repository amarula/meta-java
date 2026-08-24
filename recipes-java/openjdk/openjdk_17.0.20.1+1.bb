require openjdk-common.inc

SRC_URI:append = "\
    file://0001-awt-fix-HEADLESS-compilation-without-X11.patch \
"
SRCREV = "c35a8d5a87559ad2734f1023bb321176c13c7ba0"
