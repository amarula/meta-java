OpenEmbedded/Yocto Project layer for Java support
=================================================

This layer provides support for OpenJDK 17, 21, 25, and 26 for use with the OpenEmbedded build systems.

Dependencies
============

This layer depends on:

  URI: git://git.openembedded.org/openembedded-core
  branch: master
  revision: HEAD

  URI: git://git.openembedded.org/meta-openembedded
  sub-layer: meta-oe
  branch: master
  revision: HEAD

For use with a specific Yocto Project release please refer to the corresponding
git branches.

Patches
=======

Please submit any patches to the meta-openjdk layer at https://github.com/amarula/meta-openjdk/pulls

Guides on how to contribute to meta-openjdk are described in CONTRIBUTING.md.

Usage instructions
=======

You should define at least the following variables in a distro include file or local.conf

For conf/bblayers.conf you have to add

BBLAYERS ?= " \
   ...
  path_to_source/meta-openembedded/meta-oe \
  path_to_source/sources/meta-openjdk \
  "

Configuration instructions
=======
meta-openjdk supports OpenJDK 17, 21, 25, and 26. By default, the highest version of OpenJDK is built.
To build a different version, add `PREFERRED_VERSION_openjdk = "$PV%" where "$PV" is a supported
version found in recipes-java/openjdk.

PREFERRED_VERSION_openjdk-bin-native is automatically set by the java_version_sanity_check
method in classes/sanity_meta_openjdk.bbclass file.

Maintainers
=======
Adam Duskett <adam.duskett@amarulasolutions.com>
