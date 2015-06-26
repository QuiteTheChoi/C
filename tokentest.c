#include <stdio.h>
#include <string.h>
int main(int argc, char *argv[])
{
    char buffer[1024];
    int rv = sprintf(buffer, "a string\ttoke                nize.");
    char *token = strtok(buffer, " \t");
    int i = 0;
    printf("cnt  token\n");
    printf("==========\n");
    while (token) {
        printf("%2d %s\n", i++, token);
        token = strtok(NULL, " \t");
    }
    return 0;
}
