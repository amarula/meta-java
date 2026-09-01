SUMMARY = "A pure Java implementation of SSH2"
DESCRIPTION = "\
    JSch is a pure Java implementation of SSH2. Sch allows you to connect \
    to an sshd server and use port forwarding, X11 forwarding, file transfer, \
    etc. and you can integrate its functionality into your own Java programs."
HOMEPAGE = "https://github.com/mwiede/jsch"
BUGTRACKER = "https://github.com/mwiede/jsch/issues"
CVE_PRODUCT = "jsch"

SECTION = "support"

LICENSE = "MIT AND BSD-2-Clause"
LIC_FILES_CHKSUM = "\
    file://LICENSE.txt;md5=1574d148eee71dc1c78bb3ce6826b309 \
    file://LICENSE.jBCrypt.txt;md5=8ac9e65ef0e09deedd05f8e131b5b2e5 \
    file://LICENSE.JZlib.txt;md5=5726f2e9799112bcdb199b9c7233b454 \
"

inherit jar maven maven_update_deps

SRC_URI = "git://github.com/mwiede/jsch;protocol=https;branch=master;tag=${BPN}-${PV};"
SRCREV = "27e9dfea5a50a0c4f810a2e7c83e32a1906c4e9a"
require ${BPN}-deps.inc

do_install() {
     oe_jarinstall ${S}/target/${BPN}-${PV}.jar ${BPN}.jar
}

FILES:${PN} += "${datadir}/java/${BPN}*.jar"

RDEPENDS:${PN} = "openjdk sqlite3"

BBCLASSEXTEND = "native nativesdk"
