#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <ctype.h>

int main() {
    DIR *dir = opendir("/proc");
    struct dirent *entry;
    char path[300], buf[1024], line[256];
    FILE *fp;
    int top_pid = -1, ppid = -1;

    while ((entry = readdir(dir))) {
        if (!isdigit((unsigned char)entry->d_name[0])) continue;

        snprintf(path, sizeof(path), "/proc/%s/cmdline", entry->d_name);
        fp = fopen(path, "rb");
        if (!fp) continue;

        size_t len = fread(buf, 1, sizeof(buf) - 1, fp);
        fclose(fp);
        buf[len] = '\0';

        printf("PID %s CMDLINE: [%s]\n", entry->d_name, buf);

        if (strstr(buf, "top") != NULL) {
            printf("Matched: %s\n", entry->d_name);
            top_pid = atoi(entry->d_name);
            break;
        }
    }

    closedir(dir);

    if (top_pid == -1) {
        printf("No /usr/bin/top found\n");
        return 0;
    }

    snprintf(path, sizeof(path), "/proc/%d/status", top_pid);
    fp = fopen(path, "r");
    if (!fp) {
        printf("Failed to open status for PID %d\n", top_pid);
        return 0;
    }

    while (fgets(line, sizeof(line), fp)) {
        if (strncmp(line, "PPid:", 5) == 0) {
            sscanf(line + 5, "%d", &ppid);
            break;
        }
    }

    fclose(fp);

    printf("\nTop program name : top\n");
    printf("Top program PID  : %d\n", top_pid);
    printf("Parent PID       : %d\n", ppid);

    return 0;
}
