#include <stdio.h>
#include <stdlib.h>


static const char end_of_text = 0;
int initialized_data = 42;
static char uninitialized_data[1];

int main() {
    char *str = (char *)malloc(1024);
    if (!str) return 1;

    printf("Simulated end of text segment         : %p\n", (void *)&end_of_text);
    printf("Simulated end of initialized data     : %p\n", (void *)&initialized_data);
    printf("Simulated end of uninitialized data   : %p\n", (void *)uninitialized_data);

    free(str);
    return 0;
}
