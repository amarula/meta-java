SUMMARY = "Prebuilt OpenJDK to bootstrap cross-compiling openjdk"
DESCRIPTION = "\
    OpenJDK requires OpenJDK to compile. \
    This package provides prebuilt OpenJDK binaries suitable for \
    the job. \
"
HOMEPAGE = "https://www.adoptium.net"
BUGTRACKER = "https://github.com/adoptium/adoptium-support/issues"
CVE_PRODUCT = "eclise:temurin"
SECTION = "base"

inherit openjdk
inherit_defer native

LICENSE = "GPL-2.0-or-later"
LIC_FILES_CHKSUM = "\
    file://jdk-${PV}/legal/java.prefs/LICENSE;md5=3e0b59f8fac05c3c03d4a26bbda13f8f \
"

DEPENDS:append = " rsync-native"

PV_MAJOR = "${@d.getVar('PV').split('.')[0]}"
PV_TAG = "${@d.getVar('PV').replace('+', '%2B')}"
OPENJDK_BIN_NAME = "OpenJDK${PV_MAJOR}U-jdk_x64_linux_hotspot_${@d.getVar('PV').replace('+', '_')}.tar.gz"
SRC_URI = "https://github.com/adoptium/temurin${PV_MAJOR}-binaries/releases/download/jdk-${PV_TAG}/${OPENJDK_BIN_NAME}"

S = "${UNPACKDIR}"

# unpack200 has an invalid RPATH and relies on libzlib.
# Because unpack200 is a deprecated tool, removing it
# to fix this issue is safe.
do_install() {
    install -d ${D}${libdir}/jvm
    rsync -acIr --no-perms --no-owner --no-group \
        ${S}/jdk-${PV}/ ${D}${libdir}/jvm/
}

FILES:${PN} += "${libdir}/jvm"

BBCLASSEXTEND = "native nativesdk"
