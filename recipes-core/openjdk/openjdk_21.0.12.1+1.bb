require openjdk-common.inc

SRC_URI:append = " \
    file://0001-awt-fix-HEADLESS-compilation-without-X11.patch \
    file://0002-autoconf-libraries-drop-the-need-for-X11-in-headless.patch \
"
SRCREV = "eac07229cf6cacc8a22eb79f4929e7fed61338b7"
