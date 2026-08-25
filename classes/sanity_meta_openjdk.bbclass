inherit openjdk

python java_version_sanity_check() {
    # Because openjdk-bin-native needs to always match openjdk, force-set
    # the PREFERRED_VERSION to match openjdk.
    d.setVar("PREFERRED_VERSION_openjdk-bin-native", f"{get_openjdk_version(d)}%")
}
addhandler java_version_sanity_check
java_version_sanity_check[eventmask] = "bb.event.SanityCheck"
java_version_sanity_check[doc] = "\
    - Check to ensure a valid preferred OpenJDK version is set. \
    - Set the openjdk-bin-native preferred version to match the OpenJDK version. \
"

python java_toolchain_sanity_check() {
    toolchain=d.getVar("PREFERRED_TOOLCHAIN_TARGET")
    if toolchain != "gcc":
        bb.fatal(f"Compiling OpenJDK requires a GCC toolchain")
}
addhandler java_toolchain_sanity_check
java_toolchain_sanity_check[eventmask] = "bb.event.SanityCheck"
java_toolchain_sanity_check[doc] = "Check to ensure the user is compiling with GCC"
