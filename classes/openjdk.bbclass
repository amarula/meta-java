def get_openjdk_build_version(d):
    pv = bb.parse.vars_from_file(d.getVar('FILE', False),d)[1]
    return pv.split("+")[1]

def get_openjdk_version(d):
    supported_versions = ["26", "25", "21", "17"]
    preferred_version = d.getVar("PREFERRED_VERSION_openjdk")

    if preferred_version is None:
        return supported_versions[0]

    if "%" in preferred_version:
        preferred_version = preferred_version.split("%")[0]

    preferred_version = preferred_version.split(".")[0]
    if preferred_version not in supported_versions:
        bb.fatal(f"Unsupported PREFERRED_VERSION_openjdk: {preferred_version}")

    return preferred_version
