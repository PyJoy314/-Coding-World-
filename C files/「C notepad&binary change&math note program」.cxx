#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char* custom_strdup(const char* s) {
    size_t len = strlen(s) + 1;
    char* d = malloc(len);
    if (d == NULL) return NULL;
    memcpy(d, s, len);
    return d;
}

char* get_joined_binary_string(const char* input_message) {
    size_t len = strlen(input_message);
    if (len == 0) {
        char* empty = malloc(1);
        empty[0] = '\0';
        return empty;
    }
    size_t binary_len = len * 8 + (len - 1);
    char* result = malloc(binary_len + 1);
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

int is_exit_command(const char* str) {
    if (strlen(str) != 4) return 0;
    char lower[5];
    for (int i = 0; i < 4; i++) {
        lower[i] = (char)tolower((unsigned char)str[i]);
    }
    lower[4] = '\0';
    return strcmp(lower, "exit") == 0;
}

int Chat() {
    int CM = 0;
    long long M = 0;
    char** C = NULL;
    char Nick[256];

    double A, B, C_val;
    int Z;
    int N;

    printf("input the Nickname: ");
    if (fgets(Nick, sizeof(Nick), stdin)) {
        Nick[strcspn(Nick, "\n")] = 0;
    }
    printf("%s user welcome to my Python one line notepad&2binary string change\n", Nick);
    printf("\n");

    while (1) {
        char input_message[1024];
        printf("input the txt when want to exit input the exit: ");
        if (!fgets(input_message, sizeof(input_message), stdin)) {
            break;
        }
        input_message[strcspn(input_message, "\n")] = 0;

        C = realloc(C, (CM + 1) * sizeof(char*));
        C[CM] = custom_strdup(input_message);

        char* joined_binary_string = get_joined_binary_string(input_message);
        M += (long long)strlen(input_message) + (long long)strlen(joined_binary_string);

        if (is_exit_command(input_message)) {
            free(joined_binary_string);
            break;
        }

        printf("%s %lld %s\n", Nick, M, C[CM]);
        printf("change to binary string: %s\n", joined_binary_string);

        free(joined_binary_string);
        CM++;
    }

    for (int i = 0; i < CM; i++) {
        free(C[i]);
    }
    free(C);

    printf("\nInput 3 numbers: ");
    scanf("%lf %lf %lf", &A, &B, &C_val);
    while (getchar() != '\n');

    printf("\nEngineering Calculator\n");
    printf("A + B + C = %.2lf\n", A + B + C_val);
    printf("A - B - C = %.2lf\n", A - B - C_val);
    printf("A * B * C = %.2lf\n", A * B * C_val);
    if (B != 0 && C_val != 0) {
        printf("A / B / C = %.6lf\n", A / B / C_val);
    } else {
        printf("A / B / C = Cannot divide by zero\n");
    }

    printf("\nComparison\n");
    Z = (A > B);
    printf("A > B = %d\n", Z);
    Z = (A < B);
    printf("A < B = %d\n", Z);
    Z = (A >= B);
    printf("A >= B = %d\n", Z);
    Z = (A <= B);
    printf("A <= B = %d\n", Z);
    Z = (A == B);
    printf("A == B = %d\n", Z);
    Z = (A != B);
    printf("A != B = %d\n", Z);

    printf("\nSquare\n");
    printf("A ^ 2 = %.2lf\n", A * A);
    printf("B ^ 2 = %.2lf\n", B * B);
    printf("C ^ 2 = %.2lf\n", C_val * C_val);

    printf("\nCube\n");
    printf("A ^ 3 = %.2lf\n", A * A * A);
    printf("B ^ 3 = %.2lf\n", B * B * B);
    printf("C ^ 3 = %.2lf\n", C_val * C_val * C_val);

    printf("\nIncrement\n");
    N = 10;
    printf("N = %d\n", N);
    N++;
    printf("N++ = %d\n", N);
    N++;
    printf("N++ = %d\n", N);
    printf("N = %d\n", N);

    return 0;
}

int main() {
    Chat();
    return 0;
}
