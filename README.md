Everybody can do anything with code, Conway's life of game, txt, ect of in code diractory folder. 
Also learning to codeing too
You can make code, explore, and make website like that.
You can do relly anything with code
enjoy the codeing~

My websits
https://ide.mblock.cc/#/?cloudProjectId=8199042
https://www.youtube.com/@Joyce-i2c
https://www.desmos.com/calculator/3rsafxdhxs?lang=ko
https://open.spotify.com/track/4PtJNlcpEGyNAkYy44m5fI?si=8ed1e323681041ec
___________________________________________________________________________________________________________________________________________________________________________________________________________________
My code&img
img
<img width="1919" height="1079" alt="image" src="https://github.com/user-attachments/assets/0a4f53bb-a22e-4007-86af-334e37cb0bcd" />
code 1
[「C notepad&binary change&math note program」.c](https://github.com/user-attachments/files/30490115/C.notepad.binary.change.math.note.program.c)
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

        printf("%s %lld %s\n", Nick, M,"$", C[CM]);
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
___________________________________________________________________________________________________________________________________________________________________________________________________________________
code 2
[Txt one line.c](https://github.com/user-attachments/files/30490120/Txt.one.line.c)
#include <stdio.h>
#include <string.h>

int main()
{
    char Nick[10];
    char txt[1024];
    double A, B, C;
    int Z;
    int N;

    printf("input the Nickname : ");
    fgets(Nick, sizeof(Nick), stdin);
    Nick[strcspn(Nick, "\n")] = '\0';

    while (1)
    {
        printf("input the txt (if want to exit, then input 'exit') : ");

        fgets(txt, sizeof(txt), stdin);
        txt[strcspn(txt, "\n")] = '\0';

        if (strcmp(txt, "exit") == 0)
        {
            printf("Exit the program.\n");
            break;
        }

        if (strcmp(txt, "Lewin Diaz") == 0)
        {
            char *stats[] =
            {
                "Game\tSeason\t07.03\t07.02\t07.01\t06.30\t06.28\t06.27",
                "Batting Average\t0.290\t0.000\t0.667\t0.500\t0.250\t0.000\t0.250",
                "At Bats\t314\t4\t3\t2\t4\t4\t4",
                "Hits\t91\t0\t2\t1\t1\t0\t1",
                "Doubles\t17\t0\t1\t1\t1\t0\t0",
                "Triples\t0\t0\t0\t0\t0\t0\t0",
                "Home Runs\t15\t0\t0\t0\t0\t0\t0",
                "RBIs\t68\t0\t0\t0\t0\t0\t0",
                "Runs\t47\t0\t1\t2\t2\t0\t0",
                "Stolen Bases\t2\t0\t1\t0\t0\t0\t0",
                "Walks / HBP\t43\t1\t2\t2\t2\t0\t0",
                "Strikeouts\t56\t0\t0\t0\t1\t1\t2",
                "On-base Percentage\t0.372\t0.200\t0.800\t0.750\t0.500\t0.000\t0.250",
                "Slugging Percentage\t0.487\t0.000\t1.000\t1.000\t0.500\t0.000\t0.250",
                "OPS\t0.859\t0.200\t1.800\t1.750\t1.000\t0.000\t0.500"
            };

            printf("\n=========================================\n");
            printf("      Lewin Diaz Statistics (KBO)\n");
            printf("=========================================\n");

            for (int i = 0; i < 15; i++)
            {
                printf("%s\n", stats[i]);
            }

            printf("=========================================\n");
        }
        else
        {
            printf("%s : %s\n", Nick, txt);
        }

        printf("\nInput 3 numbers : ");
        scanf("%lf %lf %lf", &A, &B, &C);

        while (getchar() != '\n');

        printf("\n===== Engineering Calculator =====\n");

        printf("A + B + C = %.2lf\n", A + B + C);
        printf("A - B - C = %.2lf\n", A - B - C);
        printf("A * B * C = %.2lf\n", A * B * C);

        if (B != 0 && C != 0)
        {
            printf("A / B / C = %.6lf\n", A / B / C);
        }
        else
        {
            printf("A / B / C = Cannot divide by zero\n");
        }

        printf("\n===== Comparison =====\n");

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

        printf("\n===== Square =====\n");

        printf("A^2 = %.2lf\n", A * A);
        printf("B^2 = %.2lf\n", B * B);
        printf("C^2 = %.2lf\n", C * C);

        printf("\n===== Cube =====\n");

        printf("A^3 = %.2lf\n", A * A * A);
        printf("B^3 = %.2lf\n", B * B * B);
        printf("C^3 = %.2lf\n", C * C * C);

        printf("\n===== Increment =====\n");

        N = 10;

        printf("N = %d\n", N);

        N++;
        printf("N++ = %d\n", N);

        N++;
        printf("N++ = %d\n", N);

        N--;
        printf("N-- = %d\n", N);
    }

    return 0;
}
