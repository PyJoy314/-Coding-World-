#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/**
 * Custom implementation of strdup since it's not part of the C standard library (ISO C),
 * though it is part of POSIX.
 */
char* custom_strdup(const char* s) {
    size_t len = strlen(s) + 1;
    char* d = malloc(len);
    if (d == NULL) return NULL;
    memcpy(d, s, len);
    return d;
}

/**
 * Helper function to convert a string into a space-separated string of 8-bit binary representations.
 * Mimics: joined_binary_string = ' '.join([format(ord(char), '08b') for char in input_message])
 */
char* get_joined_binary_string(const char* input_message) {
    size_t len = strlen(input_message);
    if (len == 0) {
        char* empty = (char*)malloc(1);
        empty[0] = '\0';
        return empty;
    }

    // Each character is 8 bits plus a space (except the last character).
    // Length: (len * 8) + (len - 1) + 1 for null terminator.
    size_t binary_len = (len * 8) + (len - 1);
    char* result = (char*)malloc(binary_len + 1);
    if (!result) return NULL;
    result[0] = '\0';

    for (size_t i = 0; i < len; i++) {
        unsigned char c = (unsigned char)input_message[i];
        char bits[9];
        for (int j = 7; j >= 0; j--) {
            bits[7 - j] = (c & (1 << j)) ? '1' : '0';
        }
        bits[8] = '\0';
        strcat(result, bits);
        if (i < len - 1) {
            strcat(result, " ");
        }
    }
    return result;
}

/**
 * Helper function to check if a string is "exit" (case-insensitive).
 * Mimics: input_message.lower() == 'exit'
 */
int is_exit_command(const char* str) {
    if (strlen(str) != 4) return 0;
    char lower[5];
    for (int i = 0; i < 4; i++) {
        lower[i] = (char)tolower((unsigned char)str[i]);
    }
    lower[4] = '\0';
    return strcmp(lower, "exit") == 0;
}

// #import sys
// #sys.stdin("input.txt", "r",encoding="UTF-8")
// #sys.outdin("output.txt", "w",encoding="UTF-8")

void Chat() {
    // C = {}
    // CM = 0
    // M = 0
    char** C = NULL; // Dictionary C implemented as a dynamic array of strings
    int CM = 0;
    long long M = 0; // Using long long to accommodate potentially large sums of lengths
    
    char Nick[256];
    printf("input the Nickname : ");
    if (fgets(Nick, sizeof(Nick), stdin)) {
        Nick[strcspn(Nick, "\n")] = 0; // Remove trailing newline
    }

    printf("%s user, welcome to my Python one line notepad&2binary string change~!\n", Nick);
    printf("\n");

    while (1) {    
        char input_message[1024];
        printf("input the txt(when want to exit, input the 'exit') :"); // Use a clearer variable name instead of 'MCAT'.
        if (!fgets(input_message, sizeof(input_message), stdin)) break;
        input_message[strcspn(input_message, "\n")] = 0; // Remove trailing newline
        
        // C[CM] = input_message
        C = (char**)realloc(C, (CM + 1) * sizeof(char*));
        C[CM] = custom_strdup(input_message);

        // Generates a real binary string list instead of a generator object.
        // Link the generated binary string list to a blank space.
        char* joined_binary_string = get_joined_binary_string(input_message);

        // M += (len(input_message)+len(joined_binary_string))
        M += (long long)(strlen(input_message) + strlen(joined_binary_string));

        // if input_message.lower() == 'exit':
        if (is_exit_command(input_message)) {
            free(joined_binary_string);
            break;
        }

//        sys.outdin(write(f"{Nick} {M}₩/$ : {C[CM]}\n"))
//        sys.outdin(write(f"-> 2진수 = {joined_binary_string}\n"))
        
        printf("%s %lld₩/$ : %s\n", Nick, M, C[CM]);
        printf("-> change to binary string = %s\n", joined_binary_string); // Prints a properly connected binary string.
        
        free(joined_binary_string);
        CM += 1;
    }

    // Cleanup allocated memory for C
    for (int i = 0; i <= CM; i++) {
        free(C[i]);
    }
    free(C);
}

int main() {
    Chat();
    return 0;
}
