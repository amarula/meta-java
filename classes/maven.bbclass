DEPENDS += "maven-bin-native"

MAVEN = "\
    JAVA_HOME="${STAGING_DIR_NATIVE}/${libdir}/jvm" \
    M2_HOME="${STAGING_DIR_NATIVE}/${libdir}/maven" \
    MAVEN_HOME="${STAGING_DIR_NATIVE}/${libdir}/maven" \
    ${STAGING_DIR_NATIVE}/${libdir}/maven/bin/mvn \
    --batch-mode \
    --strict-checksums \
    -T ${@oe.utils.parallel_make(d) or 1} \
"

MAVEN_BUILD_FLAGS ?= "clean package -DskipTests"

def get_maven_debug_args(d):
    import bb.msg
    level = bb.msg.loggerDefaultLogLevel
    if level <= 9: # >= -DD
        return "-e -X"
    elif level <= 10: # -D
        return "-e"
    return ""

MAVEN_DEBUG_ARGS := "${@get_maven_debug_args(d)}"

do_compile() {
    cd ${S}
    ${MAVEN} \
        --offline \
        -Dmaven.repo.local="${DL_DIR}/maven-repo/${BP}" \
        ${MAVEN_DEBUG_ARGS} \
        ${MAVEN_BUILD_FLAGS}
}

python do_cleanall:append() {
    import shutil
    mvn_repo_dir = f"{d.getVar('DL_DIR')}/maven-repo/{d.getVar('BP')}"
    if os.path.isdir(mvn_repo_dir):
        bb.debug(1, f"removing {mvn_repo_dir}")
        shutil.rmtree(mvn_repo_dir)
}
