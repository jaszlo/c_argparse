#ifndef HELPERS_H
#define HELPERS_H

#include <stdio.h>


/**
 * @brief Check if a given string leads to a valid file or directory.
 * 
 * @param path String to check
 * @return true If the path exists
 * @return false If the path does not exist
 */
unsigned int path_exists(const char *path); 


/**
 * @brief Checks if two strings are equal. Used to not require string.h
 * 
 * @param s1 String to check
 * @param s2 String to check
 * @return true If the strings are equal
 * @return false If the strings are not equal
 */
unsigned int _streq(char *s1, char *s2);


/**
 * @brief Checks if a string is a number.
 * A number is a string that can be parsed as one of the following:
 * - integer/float base 10
 * - integer base 16
 * - integer base 2
 * 
 * @param s String to check
 * @return true If the string is a number
 * @return false If the string is not a number
 */
unsigned int is_number(char *s);

unsigned int is_hexadecimal(char *s);

unsigned int is_binary(char *s);

#endif // HELPERS_H