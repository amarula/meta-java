SUMMARY = "OpenJDK"
DESCRIPTION = "OpenJDK is a free and open-source implementation of the Java Platform."
HOMEPAGE = "https://openjdk.org"
BUGTRACKER = "https://github.com/adoptium/adoptium-support/issues"
CVE_PRODUCT = "eclise:temurin"
SECTION = "base"

LICENSE = "GPL-2.0-or-later"
LIC_FILES_CHKSUM = "file://LICENSE;md5=3e0b59f8fac05c3c03d4a26bbda13f8f"

inherit ccache openjdk pkgconfig

OPENJDK_CONF_ENV = "\
    CC="${TARGET_PREFIX}gcc" \
    CXX="${TARGET_PREFIX}g++" \
    CPP="${TARGET_PREFIX}gcc -E" \
    LD="${TARGET_PREFIX}gcc" \
    BUILD_SYSROOT_CFLAGS="${BUILD_CFLAGS}" \
    BUILD_SYSROOT_LDFLAGS="${BUILD_LDFLAGS}" \
"

# This must be passed to configure.
OPENJDK_JOBS := "${@oe.utils.parallel_make(d) or 1}"
PARALLEL_MAKE = ""

OPENJDK_INSTALL_BASE = "${libdir}/jvm"

# JDK vs JRE image choice
BUILD_FULL_JDK ?= "false"
JVM_VARIANT ?= "client"

OPENJDK_MAKE_TARGET = "${@'jdk-image' if d.getVar('BUILD_FULL_JDK') == 'true' else 'legacy-jre-image'}"
OPENJDK_VARIANT = "${@'jdk' if d.getVar('BUILD_FULL_JDK') == 'true' else 'jre'}"

python do_check_openjdk_jvm_variant() {
    valid_variants = ["client", "server", "zero"]
    variant = d.getVar('JVM_VARIANT')

    if variant not in valid_variants:
        bb.fatal(f"Invalid JVM_VARIANT '{variant}'. Supported options are: {', '.join(valid_variants)}")
}
addtask do_check_openjdk_jvm_variant before configure
do_check_openjdk_jvm_variant[doc] = "Ensure a supported JVM variant is set"

DEPENDS:append = " \
    alsa-lib \
    autoconf-native \
    cups \
    fontconfig \
    gawk-native \
    giflib \
    jpeg \
    lcms \
    libpng \
    libpng-native \
    libusb \
    openjdk-bin-native \
    pkgconfig-native \
    rsync-native \
    unzip-native \
    zip-native \
    zlib \
    zlib-native \
"

DEPENDS:append = " ${@bb.utils.contains('JVM_VARIANT', 'zero', 'libffi', '', d)}"

PV_MAJOR = "${@d.getVar('PV').split('.')[0]}"
SRC_URI = "git://github.com/openjdk/jdk${PV_MAJOR}u;protocol=https;branch=master"

S = "${WORKDIR}/git"

PACKAGECONFIG[x11] = "--disable-headless-only, --enable-headless-only, libxrandr libxrender libxt libxtst"

CONFIGUREOPTS ?= "\
    --disable-full-docs \
    --disable-javac-server \
    --disable-warnings-as-errors \
    --enable-ccache \
    --enable-headless-only \
    --enable-openjdk-only \
    --enable-unlimited-crypto \
    --openjdk-target=${TARGET_SYS} \
    --with-boot-jdk=${STAGING_DIR_NATIVE}/${libdir}/jvm \
    --with-build-user="bitbake" \
    --with-ccache-dir=${CCACHE_DIR} \
    --with-debug-level=release \
    --with-devkit=${STAGING_DIR_NATIVE} \
    --with-extra-cflags="${TARGET_CC_ARCH} ${BUILD_CFLAGS} ${TARGET_CFLAGS}" \
    --with-extra-cxxflags="${TARGET_CC_ARCH} ${BUILD_CXXFLAGS} ${TARGET_CXXFLAGS} -fpermissive" \
    --with-extra-ldflags="${LDFLAGS} -Wl,-rpath,${OPENJDK_INSTALL_BASE}/lib,-rpath,${OPENJDK_INSTALL_BASE}/lib/${JVM_VARIANT}" \
    --with-giflib=system \
    --with-jobs=${OPENJDK_JOBS} \
    --with-jvm-variants=${JVM_VARIANT} \
    --with-lcms=system \
    --with-libjpeg=system \
    --with-libpng=system \
    --with-native-debug-symbols=none \
    --without-version-pre \
    --with-stdc++lib=dynamic \
    --with-sysroot=${STAGING_DIR_HOST} \
    --with-version-build="${@get_openjdk_build_version(d)}" \
    --with-version-string="${@d.getVar('PV').split('+')[0]}" \
    --with-zlib=system \
    ${PACKAGECONFIG_CONFARGS} \
"

CONFIGUREOPTS:append:aarch64 = " --with-abi-profile=aarch64"

do_configure() {
    rm -rf "${S}"/build
    chmod +x "${S}"/configure
    cd ${S}; ${OPENJDK_CONF_ENV} ./configure autogen ${CONFIGUREOPTS}
}

do_compile() {
    oe_runmake -C ${S} ${OPENJDK_MAKE_TARGET}
}

do_install() {
    install -d ${D}${OPENJDK_INSTALL_BASE}
    install -d ${D}${bindir}

    rsync -acIr --no-perms --no-owner --no-group \
        ${S}/build/linux-*-release/images/${OPENJDK_VARIANT}/ \
        ${D}${OPENJDK_INSTALL_BASE}/

    cd ${D}${bindir}/
    ln -snf ../../${OPENJDK_INSTALL_BASE}/bin/* .
    rm -rf ${D}${OPENJDK_INSTALL_BASE}/{demo,jmods,include}
}

sysroot_stage_all:append() {
    install -d ${STAGING_DIR_HOST}/${includedir}/jvm

    rsync -acIr --no-perms --no-owner --no-group \
        ${S}/build/linux-*-release/jdk/include/ \
        ${STAGING_DIR_HOST}/${includedir}/jvm/
}

# Packaging setup
FILES:${PN} += "\
    ${libdir}/jvm \
    ${bindir}/* \
"

BBCLASSEXTEND = "native nativesdk"
