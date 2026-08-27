SUMMARY = "SQLite JDBC Driver"
DESCRIPTION = "\
    SQLite JDBC is a library for accessing and creating SQLite database \
    files in Java."
HOMEPAGE = "https://github.com/xerial/sqlite-jdbc"
BUGTRACKER = "https://github.com/xerial/sqlite-jdbc/issues"
CVE_PRODUCT = "sqlite-jdbc"

SECTION = "support"

LICENSE = "Apache-2.0 & BSD-2-Clause"
LIC_FILES_CHKSUM = "\
    file://LICENSE;md5=d273d63619c9aeaf15cdaf76422c4f87 \
    file://LICENSE.zentus;md5=d393760bd738a58c439f0a8eb5305d1b \
"

S = "${WORKDIR}/git"

inherit jar maven maven_update_deps

SRC_URI = "git://github.com/xerial/sqlite-jdbc;protocol=https;branch=master"
SRCREV = "cab7981c19ce04d691f0675f0b2586afc2bbf803"
require ${BPN}-deps.inc

do_install() {
    oe_jarinstall ${S}/target/${BPN}-${PV}.jar ${BPN}.jar
}

FILES:${PN} += "${datadir}/java/${BPN}*.jar"

RDEPENDS:${PN} = "openjdk sqlite3"

BBCLASSEXTEND = "native nativesdk"
