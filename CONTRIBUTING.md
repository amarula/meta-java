meta-openjdk contribution guidelines
=================================

Contributing via github.com
---------------------------

To contribute to this layer you may fork the repository and create a merge
request at https://github.com/amarula/meta-openjdk.

Contributing via E-Mail
-----------------------

To contribute to this layer you may submit the patches for review to the
mailing list (openembedded-devel@lists.openembedded.org).

Please refer to:
https://wiki.yoctoproject.org/wiki/Contribution_Guidelines#General_Information

for some useful guidelines to be followed when submitting patches.

Mailing list:

    http://lists.yoctoproject.org/mailman/listinfo/yocto-patches

Source code:

    git://github.com:amarula/meta-openjdk.git
    https://github.com/amarula/meta-openjdk

When creating single patches, please use something like:

    git format-patch -M -s --subject-prefix='meta-openjdk][PATCH' -1

When creating a patch series, please add a cover letter describing it shortly.
Therefore use something like:

    git format-patch -M -s --cover-letter --subject-prefix='meta-openjdk][PATCH' origin

When sending patches, please use something like:

    git send-email --to yocto-patches@lists.yoctoproject.org <generated patch(es)>

Please add the main layer maintainer to CC:

  Adam Duskett <adam.duskett@amarulasolutions.com>
