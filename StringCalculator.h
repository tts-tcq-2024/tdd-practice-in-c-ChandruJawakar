#include <stdio.h>
#include <string.h>
#include <ctype.h>

// Function: add_arr
// Adds up integers in the array 'arr' with 'cnt' elements, ignoring values >= 1000.
// Returns the sum of valid integers.
int add_arr(int *arr, int cnt) {
    int i = 0;
    int total = 0;
    while (i < cnt) {
        if (arr[i] < 1000) {
            total += arr[i];  // Add the number to total if it's less than 1000
        }
        i++;
    }
    return total;
}

// Function: check_num
// Checks if a character 'ch' is a digit ('0'-'9').
// Returns 1 if 'ch' is a digit, otherwise returns 0.
int check_num(const char ch) {
    if (ch >= '0' && ch <= '9') {
        return 1;
    }
    return 0;
}

// Function: strtonum
// Converts a substring in 'ch' starting at 'cnt' into an integer and stores it in 'num_arr'.
// Updates 'cnt' to point to the next non-digit character.
void strtonum(const char* ch, int *num_arr, int *cnt) {
    static int num = 0;

    if (check_num(ch[*cnt])) {
        num = num * 10 + ch[*cnt] - '0';  // Convert character to integer
        if (check_num(ch[(*cnt) + 1])) {
            (*cnt)++;  // Move to the next character if it's also a digit
        } else {
            num_arr[*cnt] = num;  // Store the complete number in num_arr
            num = 0;  // Reset num for the next number
            (*cnt)++;  // Move to the next position in the array
        }
    } else {
        (*cnt)++;  // Move to the next character if current one is not a digit
        num = 0;  // Reset num
    }
}

// Function: sum
// Sums up all integers embedded in the string 'ch'.
// Returns the total sum of valid integers.
int sum(const char *ch) {
    int cnt = 0;
    int total = 0;
    int num_arr[100] = {0};

    while (ch[cnt] != '\0') {
        strtonum(ch, num_arr, &cnt);  // Convert string to numbers
    }

    total = add_arr(num_arr, cnt);  // Calculate total sum of numbers

    return total;
}

// Function: neg_loop
// Checks if '-' followed by a digit in 'ch' at position 'i'.
// Returns 0 if a negative number is found, otherwise returns 1.
int neg_loop(const char *ch, int i) {
    if (ch[i] == '-') {
        if (check_num(ch[i + 1])) {
            return 0;  // Negative number found
        }
    }
    return 1;  // Not a negative number
}

// Function: check_neg
// Checks if 'ch' contains any negative numbers.
// Returns 0 if a negative number is found, otherwise returns 1.
int check_neg(const char *ch) {
    int i = 0;
    while (ch[i] != '\0') {
        if (!neg_loop(ch, i)) {
            return 0;  // Negative number found
        }
        i++;
    }
    return 1;  // No negative numbers found
}

// Function: check_empty
// Checks if 'ch' is an empty string.
// Returns 1 if 'ch' is empty, otherwise returns 0.
int check_empty(const char* ch) {
    int strlength = strlen(ch);

    if (strlength == 0) {
        return 1;  // Empty string
    }
    return 0;  // Not empty
}

// Function: check_neg_empty
// Checks if 'ch' contains negative numbers or is empty.
// Returns 1 if 'ch' contains negative numbers or is empty, otherwise returns 0.
int check_neg_empty(const char *ch) {
    if (!check_neg(ch) || check_empty(ch)) {
        return 1;  // Negative number found or empty string
    }
    return 0;  // No negative numbers and not empty
}

// Function: check_string
// Checks if 'ch' is a valid string containing only non-negative integers.
// Returns 1 if 'ch' is valid, otherwise returns 0.
int check_string(const char *ch) {
    if (ch != NULL) {
        return check_neg_empty(ch);  // Check for negative numbers or empty string
    }

    return 0;  // NULL pointer
}

// Function: add
// Parses 'ch' to sum up all non-negative integers and returns the total sum.
// Returns the sum if successful and positive, 0 if the sum is 0, and -1 for invalid input.
int add(const char *ch) {
    if (check_string(ch)) {  // Check if 'ch' contains only non-negative integers
        int total = sum(ch);  // Calculate sum of integers
        if (total > 0) {
            return total;  // Return positive sum
        }
        return 0;  // Return 0 if sum is 0
    }

    return -1;  // Return -1 for invalid input
}
