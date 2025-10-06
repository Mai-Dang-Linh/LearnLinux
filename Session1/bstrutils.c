#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include "strutils.h"
#include <limits.h>

//Reverses a string in-place
void str_reverse(char *str) {
    if (!str) return;
    int left = 0;
    int right = strlen(str) - 1;
    while (left < right) {
        char tmp = str[left];
        str[left] = str[right];
        str[right] = tmp;
        left++;
        right--;
    }
}

// Removes leading and trailing whitespace from a string
void str_trim(char *str) {
    if (!str) return;

    int start = 0;
    int end = strlen(str) - 1;

    while (isspace((unsigned char)str[start])) {
        start++;
    }

    while (end >= start && isspace((unsigned char)str[end])) {
        end--;
    }

    int len = end - start + 1;
    if (len > 0) {
        memmove(str, str + start, len);
    }
    str[len] = '\0';
}

//Safely converts a string to an integer
int str_to_int(const char *str, int *out_value) {
    if (!str || !out_value) return 0;

    char *endptr;
    long val = strtol(str, &endptr, 10);

    if (*endptr != '\0') return 0;

    if (val < INT_MIN || val > INT_MAX) return 0;

    *out_value = (int)val;
    return 1;
}
