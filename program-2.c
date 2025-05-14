#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[], char *envp[]) {
    for (int i = 0; envp[i] != NULL; i++) {
        if (strncmp(envp[i], "SHELL=", 6) == 0 ||
            strncmp(envp[i], "PATH=", 5) == 0 ||
            strncmp(envp[i], "USERNAME=", 9) == 0) {
            printf("%s\n", envp[i]);
        }
    }

    printf("\nOther variables that can be viewed through main's third argument:\n");
    for (int i = 0; envp[i] != NULL; i++) {
        if (!(strncmp(envp[i], "SHELL=", 6) == 0 ||
              strncmp(envp[i], "PATH=", 5) == 0 ||
              strncmp(envp[i], "USERNAME=", 9) == 0)) {
            char *equal = strchr(envp[i], '=');
            if (equal) {
                *equal = '\0'; 
                printf("%s\n", envp[i]);
                *equal = '=';  
            }
        }
      }
    return 0;
}
