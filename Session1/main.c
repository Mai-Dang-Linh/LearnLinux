#include <stdio.h>
#include "strutils.h"

void str_reverse(char *str);
void str_trim(char *str);
int str_to_int(const char *str, int *out_value);

int main() {
    char s1[] = "  Hello World!  ";
    char s2[] = "12345";
    int num;

    // Test trim
    str_trim(s1);
    printf("Trimmed: '%s'\n", s1);

    // Test reverse
    str_reverse(s1);
    printf("Reversed: '%s'\n", s1);

    // Test to int
    if (str_to_int(s2, &num)) {
        printf("Converted: %d\n", num);
    } else {
        printf("Conversion failed\n");
    }

    return 0;
}
