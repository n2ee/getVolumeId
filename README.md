A shell script and a C tool to extract the Volume Serial Number of a FAT
volume on macos - in particular, it involves jumping through several hoops
to work with the security constrictions that come with the more recent
versions of macos.

The shell script getVolumeId does the preliminary work of discovering if the
specified volume is a USB disk formatted FAT32, and the actual underlying
device node for the volume. It then unmounts the volume so the get_vsn
tool can then peek at the device and pluck out the 4-byte id in the FAT32 at
offset 67. Finally, it re-mounts the volume, and prints out the VSN as an
8 character value in the form "XXXX-YYYY".

See https://www.digital-detective.net/documents/Volume%20Serial%20Numbers.pdf
for an explanation of how to find the VSN and why the value 67 is magic.

The install target of the Makfile details the permissions and location of where
get_vsn must be installed and codesigned such that macos will run it without
requiring the user to have sudo privileges. In addition to those steps, the
user must grant "Full Disk Access" to the terminal app of choice in order for
the os to allow get_vsn to peek at the raw USB disk.


