#include <stdio.h>
#include <string.h>
#include <ctype.h>

// Function: add_arr
// Adds up integers in the array 'arr' with 'cnt' elements, ignoring values >= 1000.
// Returns the sum of valid integers.
int add_arr(int *arr, int cnt) {
    int total = 0;
    for (int i = 0; i < cnt; i++) {
        if (arr[i] < 1000) {
            total += arr[i];
        }
    }
    return total;
}

// Function: check_num
// Checks if a character 'ch' is a digit ('0'-'9').
// Returns 1 if 'ch' is a digit, otherwise returns 0.
int check_num(const char ch) {
    return (ch >= '0' && ch <= '9');
}

// Function: strtonum
// Converts a substring in 'ch' starting at 'cnt' into an integer and stores it in 'num_arr'.
// Updates 'cnt' to point to the next non-digit character.
void strtonum(const char* ch, int *num_arr, int *cnt) {
    static int num = 0;

    while (check_num(ch[*cnt])) {
        num = num * 10 + ch[*cnt] - '0';
        (*cnt)++;
    }
    num_arr[*cnt] = num;
    num = 0;
    (*cnt)++;
}

// Function: sum
// Sums up all integers embedded in the string 'ch'.
// Returns the total sum of valid integers.
int sum(const char *ch) {
    int cnt = 0;
    int num_arr[100] = {0};

    while (ch[cnt] != '\0') {
        strtonum(ch, num_arr, &cnt);
    }

    return add_arr(num_arr, cnt);
}

// Function: neg_loop
// Checks if '-' followed by a digit in 'ch' at position 'i'.
// Returns 0 if a negative number is found, otherwise returns 1.
int neg_loop(const char *ch, int i) {
    if (ch[i] == '-') {
        if (check_num(ch[i+1])) {
            return 0;
        }
    }
    return 1;
}

// Function: check_neg
// Checks if 'ch' contains any negative numbers.
// Returns 0 if a negative number is found, otherwise returns 1.
int check_neg(const char *ch) {
    int i = 0;
    while (ch[i] != '\0') {
        if (!neg_loop(ch, i)) {
            return 0;
        }
        i++;
    }
    return 1;
}

// Function: check_empty
// Checks if 'ch' is an empty string.
// Returns 1 if 'ch' is empty, otherwise returns 0.
int check_empty(const char* ch) {
    return (strlen(ch) == 0);
}

// Function: check_neg_empty
// Checks if 'ch' contains negative numbers or is empty.
// Returns 1 if 'ch' contains negative numbers or is empty, otherwise returns 0.
int check_neg_empty(const char *ch) {
    if (!check_neg(ch) || check_empty(ch)) {
        return 1;
    }
    return 0;
}

// Function: check_string
// Checks if 'ch' is a valid string containing only non-negative integers.
// Returns 1 if 'ch' is valid, otherwise returns 0.
int check_string(const char *ch) {
    if (ch != NULL) {
        return check_neg_empty(ch);
    }
    return 0;
}

// Function: add
// Parses 'ch' to sum up all non-negative integers and returns the total sum.
// Returns the sum if successful and positive, 0 if the sum is 0, and -1 for invalid input.
int add(const char *ch) {
    if (check_string(ch)) {
        int total = sum(ch);
        if (total > 0) {
            return total;
        }
        return 0;
    }
    return -1;
}

