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

    printf("input the Nickname: ");
    if (fgets(Nick, sizeof(Nick), stdin)) {
        Nick[strcspn(Nick, "\n")] = 0;
    }

    printf("%s user welcome to my C one line notepad&2binary string change\n", Nick);
    printf("\n");

    while (1) {
        char input_message[1024];

        // ===== 텍스트 입력 =====
        printf("input the txt when want to exit input the exit: ");

        if (!fgets(input_message, sizeof(input_message), stdin)) {
            break;
        }

        input_message[strcspn(input_message, "\n")] = 0;

        // exit 입력 시 종료
        if (is_exit_command(input_message)) {
            printf("Program exit.\n");
            break;
        }

        // ===== 텍스트 저장 =====
        C = realloc(C, (CM + 1) * sizeof(char*));
        if (C == NULL) {
            printf("Memory allocation error.\n");
            break;
        }

        C[CM] = custom_strdup(input_message);

        // ===== Binary 변환 =====
        char* joined_binary_string =
            get_joined_binary_string(input_message);

        if (joined_binary_string == NULL) {
            printf("Memory allocation error.\n");
            break;
        }

        // $ 정보 계산
        M += (long long)strlen(input_message)
           + (long long)strlen(joined_binary_string);


        // ==================================================
        // ===== 계산 부분 =====
        // ==================================================

        double A, B, C_val;
        int Z;
        int N;

        printf("\nInput 3 numbers: ");

        if (scanf("%lf %lf %lf", &A, &B, &C_val) != 3) {
            printf("Invalid number input.\n");

            // 입력 버퍼 비우기
            int ch;
            while ((ch = getchar()) != '\n' && ch != EOF);

            free(joined_binary_string);
            break;
        }

        // 숫자 입력 뒤 남은 '\n' 제거
        while (getchar() != '\n');

        printf("\nEngineering Calculator\n");

        printf("A + B + C = %.2lf\n",
               A + B + C_val);

        printf("A - B - C = %.2lf\n",
               A - B - C_val);

        printf("A * B * C = %.2lf\n",
               A * B * C_val);

        if (B != 0 && C_val != 0) {
            printf("A / B / C = %.6lf\n",
                   A / B / C_val);
        } else {
            printf("A / B / C = Cannot divide by zero\n");
        }


        // ===== Comparison =====
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


        // ===== Square =====
        printf("\nSquare\n");

        printf("A ^ 2 = %.2lf\n", A * A);
        printf("B ^ 2 = %.2lf\n", B * B);
        printf("C ^ 2 = %.2lf\n", C_val * C_val);


        // ===== Cube =====
        printf("\nCube\n");

        printf("A ^ 3 = %.2lf\n", A * A * A);
        printf("B ^ 3 = %.2lf\n", B * B * B);
        printf("C ^ 3 = %.2lf\n",
               C_val * C_val * C_val);


        // ===== Increment =====
        printf("\nIncrement\n");

        N = 10;

        printf("N = %d\n", N);

        N++;
        printf("N++ = %d\n", N);

        N++;
        printf("N++ = %d\n", N);

        printf("N = %d\n", N);


        // ==================================================
        // ===== 계산이 끝난 다음 텍스트 정보 출력 =====
        // ==================================================

        printf("\n");

        printf("%s %lld$ %s\n",
               Nick,
               M,
               C[CM]);

        printf("change to binary string: %s\n",
               joined_binary_string);

        printf("\n");


        // 다음 입력을 위해 정리
        free(joined_binary_string);

        CM++;
    }


    // ===== 메모리 정리 =====
    for (int i = 0; i < CM; i++) {
        free(C[i]);
    }

    free(C);

    return 0;
}

int main() {
    Chat();
    return 0;
}
