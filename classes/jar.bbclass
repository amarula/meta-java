inherit openjdk
# Defines the commonly used target directories and provides a convenience
# function to install jar files.
#
# All the default directory locations herein resemble locations chosen in
# the Debian distribution.

datadir_java ?= "${datadir}/java"

oe_jarinstall() {
  # Purpose: Install a jar file and create all the given symlinks to it.
  # Example:
  # oe_jarinstall foo-1.3.jar foo.jar
  # Installs foo-1.3.jar and creates symlink foo.jar.
  #
  # oe_jarinstall -r foo-1.3.jar foo_1_3.jar foo.jar
  # Installs foo_1_3.jar as foo-1.3.jar and creates a symlink to this.
  #
  dir=${D}${datadir_java}
  destname=""
  while [ "$#" -gt 0 ]; do
    case "$1" in
    -r)
      shift
      destname=$1
      ;;
    -*)
      bbfatal "oe_jarinstall: unknown option: $1"
      ;;
    *)
      break;
      ;;
    esac
    shift
  done

  jarname="${1}"
  destname=${destname:-$(basename $jarname)}
  shift

  install -d $dir
  install -m 0644 $jarname $dir/$destname

  # Creates symlinks out of the remaining arguments.
  while [ "$#" -gt 0 ]; do
    if [ -e $dir/$1 -o -h $dir/$1 ]; then
      bbnote "file was in the way. removing:" $dir/$1
      rm $dir/$1
    fi
    ln -s $destname $dir/$1
    shift
  done
}
oe_jarinstall[doc] = "Install a jar file and create all the given symlinks to it."
