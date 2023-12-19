#include "helpers.h"


/// Paths
#define true 1
#define false 0

unsigned int path_exists(const char *path) {
    FILE *fp = fopen(path, "r");
    unsigned int is_exist = false;
    if (fp != NULL) {
        is_exist = true;
        fclose(fp); // close the file
    }
    return is_exist;
}



/// Strings


unsigned int _streq(char *s1, char *s2) {
    char c1 = *(s1++);
    char c2 = *(s2++);
    while (c1 != '\0' && c2 != '\0') {
        if (c1 != c2) {
            return 0;
        }
        c1 = *(s1++);
        c2 = *(s2++);
    }
    return c1 == c2;
}



/// Numbers


unsigned int is_digit(char c) {
    return (c >= '0' && c <= '9');
}

unsigned int is_hex_digit(char c) {
    return ((c >= '0' && c <= '9') || (c >= 'a' && c <= 'f') || (c >= 'A' && c <= 'F'));
}

unsigned int is_binary_digit(char c) {
    return (c == '0' || c == '1');
}

unsigned int is_integer(char *s) {
    int i = 0;
    if (s[i] == '-' || s[i] == '+') {
        i++;
    }

    while (s[i] != '\0') {
        if (!is_digit(s[i])) {
            return false;
        }
        i++;
    }
    return true;
}

unsigned int is_float(char *s) {
    int i = 0;
    if (s[i] == '-' || s[i] == '+') {
        i++;
    }

    unsigned int dotEncountered = false;

    while (s[i] != '\0') {
        if (s[i] == '.') {
            if (dotEncountered) {
                return false;  // More than one dot in the string
            }
            dotEncountered = true;
        } else if (!is_digit(s[i])) {
            return false;  // Non-digit character in the float
        }
        i++;
    }
    return dotEncountered;  // At least one digit and one dot
}

unsigned int is_hexadecimal(char *s) {
    int i = 0;

    if (s[i] == '-' || s[i] == '+') {
        i++;
    }

    if (s[i] == '0' && (s[i + 1] == 'x' || s[i + 1] == 'X')) {
        i += 2;
    } else {
        return false;
    }

    while (s[i] != '\0') {
        if (!is_hex_digit(s[i])) {
            return false;
        }
        i++;
    }
    return true;
}

unsigned int is_binary(char *s) {
    int i = 0;
    if (s[i] == '-' || s[i] == '+') {
        i++;
    }

    if (s[i] == '0' && (s[i + 1] == 'b' || s[i + 1] == 'B')) {
        i += 2;
    } else {
        return false;
    }

    while (s[i] != '\0') {
        if (!is_binary_digit(s[i])) {
            return false;
        }
        i++;
    }
    return true;
}

unsigned int is_number(char *s) {
    return is_integer(s) || is_float(s) || is_hexadecimal(s) || is_binary(s);
}