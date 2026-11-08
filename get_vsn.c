#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

/*
  This tool needs the following steps to make it operate on macos -
 
  Terminal app needs to get granted "Full Disk Access" in
  System Settings -> Privacy & Security -> Full Disk Access
 
  The executable needs to be placed in a system-trusted path:
  sudo cp get_vsn /usr/local/bin
 
  The owner/group need to be set, and the setuid bit set:
  sudo chown root:wheel /usr/local/bin/get_vsn
  sudo chmod 4755 /usr/local/bin/get_vsn
 
  Finally, we need an ad-hoc signature on the executable:
  sudo codesign --force --sign - /usr/local/bin/get_vsn
*/

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s /dev/diskXsY\n", argv[0]);
        return 1;
    }

    // Securely elevate privileges to the owner of the binary (root)
    if (setuid(0) != 0) {
        perror("Setuid failed");
        return 1;
    }

    // Open the disk strictly in Read-Only mode
    int fd = open(argv[1], O_RDONLY);
    if (fd < 0) {
        perror("Error opening disk device");
        return 1;
    }

    unsigned char buffer[4];
    // Seek exactly to the FAT32 Volume ID offset (67)
    if (lseek(fd, 67, SEEK_SET) < 0) {
        perror("Error seeking offset");
        close(fd);
        return 1;
    }

    // Read exactly 4 bytes
    if (read(fd, buffer, 4) != 4) {
        perror("Error reading bytes");
        close(fd);
        return 1;
    }

    close(fd);

    // Print the Volume Serial Number in Windows-style HEX
    printf("%02X%02X%02X%02X\n", buffer[3], buffer[2], buffer[1], buffer[0]);
    return 0;
}
