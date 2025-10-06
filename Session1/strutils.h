#ifndef STRUTILS_H
#define STRUTILS_H

//Reverses a string in-place.
void str_reverse(char *str);

//Reverses a string in-place.
void str_trim(char *str);

//Safely converts a string to an integer.
int str_to_int(const char *str, int *out_value);

#endif // STRUTILS_H