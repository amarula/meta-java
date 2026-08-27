SUMMARY = "A tool that for building and managing Java-based projects"
DESCRIPTION = "\
    Maven provides a standard way to build the projects, a clear definition \
    of what the project consisted of, an easy way to publish project \
    information, and a way to share JARs across several projects."

HOMEPAGE = "https://maven.apache.org"
BUGTRACKER = "https://github.com/apache/maven/issues"
CVE_PRODUCT = "maven"

SECTION = "devtools"

LICENSE = "Apache-2.0"
LIC_FILES_CHKSUM = "file://LICENSE;md5=fb162148a125602a93c6e342da3cf5b0"

DEPENDS += "\
    openjdk-bin-native \
    rsync-native \
"
SRC_URI = "https://dlcdn.apache.org/maven/maven-3/${PV}/binaries/apache-maven-${PV}-bin.tar.gz"
SRC_URI[sha256sum] = "80ffca22aed9e8b9713a232f3394fd81d7f20322df75efdb2b047dbd3e3a23bb"

S = "${WORKDIR}/apache-maven-${PV}"

do_install() {
    install -d ${D}${libdir}/maven
    rsync -acIr --no-perms --no-owner --no-group ${S}/ ${D}${libdir}/maven/
}

FILES:${PN} += "${libdir}/maven"

BBCLASSEXTEND = "native nativesdk"
