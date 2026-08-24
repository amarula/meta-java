DEPENDS += "maven-bin-native"

MAVEN = "\
    JAVA_HOME="${STAGING_DIR_NATIVE}/${libdir}/jvm"\
    M2_HOME="${STAGING_DIR_NATIVE}/${libdir}/maven" \
    MAVEN_HOME="${STAGING_DIR_NATIVE}/${libdir}/maven" \
    MAVEN_REPO_DIR="${DL_DIR}/maven-repo" \
    ${STAGING_DIR_NATIVE}/${libdir}/maven/bin/mvn \
"

MAVEN_BUILD_FLAGS ?= "clean package -DskipTests"

do_compile() {
    cd ${S}
    ${MAVEN} \
        --offline \
        -Dmaven.repo.local="${DL_DIR}/maven-repo" \
        ${MAVEN_BUILD_FLAGS}
}
