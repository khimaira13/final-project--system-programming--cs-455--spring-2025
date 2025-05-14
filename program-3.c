#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>

int main() {
    int fd = open("README.md", O_RDWR);
    if (fd < 0) {
        perror("open");
        return 1;
    }

    char buffer[256];
    off_t offset = 0;
    ssize_t bytes;

    while ((bytes = read(fd, buffer, sizeof(buffer))) > 0) {
        for (int i = 0; i <= bytes - 13; i++) {
            if (strncmp(&buffer[i], "### Program 3", 13) == 0) {
                off_t match_pos = offset + i;
                lseek(fd, match_pos, SEEK_SET);
                write(fd, "### PROGRAM 3", 13);
                close(fd);
                printf("Replaced at offset %ld\n", match_pos);
                return 0;
            }
        }
        offset += bytes;
    }

    close(fd);
    printf("Pattern '### Program 3' not found.\n");
    return 1;
}
