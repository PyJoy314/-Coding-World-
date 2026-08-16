/******************************************************************************

Welcome to GDB Online.
GDB online is an online compiler and debugger tool for C, C++, Python, Java, PHP, Ruby, Perl,
C#, OCaml, VB, Swift, Pascal, Fortran, Haskell, Objective-C, Assembly, HTML, CSS, JS, SQLite, Prolog.
Code, Compile, Run and Debug online from anywhere in world.

*******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/* =========================================================
   문자열 복사
   ========================================================= */
char* custom_strdup(const char* s)
{
    size_t len = strlen(s) + 1;

    char* d = malloc(len);

    if (d == NULL)
        return NULL;

    memcpy(d, s, len);

    return d;
}


/* =========================================================
   문자열 -> 8비트 Binary 문자열
   예:
   ABC
   ->
   01000001 01000010 01000011
   ========================================================= */
char* get_joined_binary_string(const char* input_message)
{
    size_t len = strlen(input_message);

    if (len == 0)
    {
        char* empty = malloc(1);

        if (empty == NULL)
            return NULL;

        empty[0] = '\0';

        return empty;
    }

    size_t binary_len = len * 8 + (len - 1);

    char* result = malloc(binary_len + 1);

    if (result == NULL)
        return NULL;

    result[0] = '\0';

    for (size_t i = 0; i < len; i++)
    {
        unsigned char c = (unsigned char)input_message[i];

        char bits[9];

        for (int j = 7; j >= 0; j--)
        {
            bits[7 - j] =
                (c & (1 << j)) ? '1' : '0';
        }

        bits[8] = '\0';

        strcat(result, bits);

        if (i < len - 1)
        {
            strcat(result, " ");
        }
    }

    return result;
}


/* =========================================================
   EXIT 명령 확인
   EXIT / exit / ExIt 등 모두 가능
   ========================================================= */
int is_exit_command(const char* str)
{
    if (strlen(str) != 4)
        return 0;

    char lower[5];

    for (int i = 0; i < 4; i++)
    {
        lower[i] =
            (char)tolower((unsigned char)str[i]);
    }

    lower[4] = '\0';

    return strcmp(lower, "exit") == 0;
}


/* =========================================================
   Lewin Diaz KBO 통계
   ========================================================= */
void show_lewin_diaz_stats(void)
{
    const char* stats[] =
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

        "Walks / HBP\t43\t1\t2\t2\t0\t0\t0",

        "Strikeouts\t56\t0\t0\t0\t1\t1\t2",

        "On-base Percentage\t0.372\t0.200\t0.800\t0.750\t0.500\t0.000\t0.250",

        "Slugging Percentage\t0.487\t0.000\t1.000\t1.000\t0.500\t0.000\t0.250",

        "OPS\t0.859\t0.200\t1.800\t1.750\t1.000\t0.000\t0.500"
    };


    printf("\n");
    printf("=========================================\n");
    printf("      Lewin Diaz Statistics (KBO)\n");
    printf("=========================================\n");

    for (int i = 0; i < 15; i++)
    {
        printf("%s\n", stats[i]);
    }

    printf("=========================================\n");
}


/* =========================================================
   Chat
   ========================================================= */
int Chat()
{
    int CM = 0;

    long long M = 0;

    /*
       C는 저장된 문자열 배열
       계산용 C는 C_val이라는 이름을 사용해서
       변수 이름 충돌을 방지한다.
    */
    char** C = NULL;

    char Nick[256];


    /* =====================================================
       닉네임 입력
       ===================================================== */
    printf("input the Nickname: ");

    if (fgets(Nick, sizeof(Nick), stdin))
    {
        Nick[strcspn(Nick, "\n")] = 0;
    }


    printf(
        "%s user welcome to my C one line notepad&2binary string change\n",
        Nick
    );

    printf("\n");


    /* =====================================================
       메인 반복
       ===================================================== */
    while (1)
    {
        char input_message[1024];


        /* =================================================
           텍스트 입력
           ================================================= */
        printf(
            "input the txt when want to exit input the exit: "
        );


        if (!fgets(
                input_message,
                sizeof(input_message),
                stdin))
        {
            break;
        }


        input_message[
            strcspn(input_message, "\n")
        ] = 0;


        /* =================================================
           EXIT
           ================================================= */
        if (is_exit_command(input_message))
        {
            printf("Program exit.\n");
            break;
        }


        /* =================================================
           텍스트 저장
           ================================================= */
        char** temp =
            realloc(
                C,
                (CM + 1) * sizeof(char*)
            );


        if (temp == NULL)
        {
            printf("Memory allocation error.\n");
            break;
        }


        C = temp;


        C[CM] =
            custom_strdup(input_message);


        if (C[CM] == NULL)
        {
            printf("Memory allocation error.\n");
            break;
        }


        /* =================================================
           Binary 변환
           ================================================= */
        char* joined_binary_string =
            get_joined_binary_string(input_message);


        if (joined_binary_string == NULL)
        {
            printf("Memory allocation error.\n");
            break;
        }


        /* =================================================
           $ 정보 계산
           ================================================= */
        M +=
            (long long)strlen(input_message)
            +
            (long long)strlen(joined_binary_string);


        /* =================================================
           Lewin Diaz 특별 기능
           ================================================= */
        if (strcmp(input_message, "Lewin Diaz") == 0)
        {
            show_lewin_diaz_stats();
        }


        /* =================================================
           계산용 변수
           ================================================= */
        double A;
        double B;
        double C_val;

        int Z;

        int N;


        /* =================================================
           숫자 입력
           ================================================= */
        printf(
            "\nInput 3 numbers "
            "(for circle calculation, use A as radius) : "
        );


        if (scanf(
                "%lf %lf %lf",
                &A,
                &B,
                &C_val) != 3)
        {
            printf("Invalid number input.\n");


            /* 입력 버퍼 비우기 */
            int ch;

            while ((ch = getchar()) != '\n' &&
                   ch != EOF)
            {
                /* clear buffer */
            }


            free(joined_binary_string);

            break;
        }


        /* 숫자 입력 뒤 남은 '\n' 제거 */
        while (getchar() != '\n')
        {
            /* clear buffer */
        }


        /* =================================================
           Engineering Calculator
           ================================================= */
        printf("\n===== Engineering Calculator =====\n");


        printf(
            "A + B + C = %.2lf\n",
            A + B + C_val
        );


        printf(
            "A - B - C = %.2lf\n",
            A - B - C_val
        );


        printf(
            "A * B * C = %.2lf\n",
            A * B * C_val
        );


        /* =================================================
           나눗셈
           ================================================= */
        if (B != 0 && C_val != 0)
        {
            printf(
                "A / B / C = %.6lf\n",
                A / B / C_val
            );
        }
        else
        {
            printf(
                "A / B / C = Cannot divide by zero\n"
            );
        }


        /* =================================================
           Circle Calculation
           ================================================= */
        printf(
            "\n===== Circle Calculation (Radius: A) =====\n"
        );


        printf(
            "Radius : %.2lf\n",
            A
        );


        printf(
            "Diameter : %.2lf\n",
            A * 2
        );


        printf(
            "Circumference : %.2lf\n",
            A * 2 * 3.14
        );


        printf(
            "Area : %.2lf\n",
            A * A * 3.14
        );


        /* =================================================
           Comparison
           ================================================= */
        printf("\n===== Comparison =====\n");


        Z = (A > B);

        printf(
            "A > B = %d\n",
            Z
        );


        Z = (A < B);

        printf(
            "A < B = %d\n",
            Z
        );


        Z = (A >= B);

        printf(
            "A >= B = %d\n",
            Z
        );


        Z = (A <= B);

        printf(
            "A <= B = %d\n",
            Z
        );


        Z = (A == B);

        printf(
            "A == B = %d\n",
            Z
        );


        Z = (A != B);

        printf(
            "A != B = %d\n",
            Z
        );


        /* =================================================
           Square
           ================================================= */
        printf("\n===== Square =====\n");


        printf(
            "A^2 = %.2lf\n",
            A * A
        );


        printf(
            "B^2 = %.2lf\n",
            B * B
        );


        printf(
            "C^2 = %.2lf\n",
            C_val * C_val
        );


        /* =================================================
           Cube
           ================================================= */
        printf("\n===== Cube =====\n");


        printf(
            "A^3 = %.2lf\n",
            A * A * A
        );


        printf(
            "B^3 = %.2lf\n",
            B * B * B
        );


        printf(
            "C^3 = %.2lf\n",
            C_val * C_val * C_val
        );


        /* =================================================
           Increment
           ================================================= */
        printf("\n===== Increment =====\n");


        N = 10;


        printf(
            "N = %d\n",
            N
        );


        N++;

        printf(
            "N++ = %d\n",
            N
        );


        N++;

        printf(
            "N++ = %d\n",
            N
        );


        /* =================================================
           Decrement
           ================================================= */
        printf("\n===== Decrement =====\n");


        N--;

        printf(
            "N-- = %d\n",
            N
        );


        /* =================================================
           텍스트 정보 출력
           ================================================= */
        printf("\n");


        printf(
            "%s %lld$ : %s\n",
            Nick,
            M,
            C[CM]
        );


        /* =================================================
           Binary 출력
           ================================================= */
        printf(
            "change to binary string: %s\n",
            joined_binary_string
        );


        printf("\n");


        /* =================================================
           메모리 정리
           ================================================= */
        free(joined_binary_string);


        CM++;
    }


    /* =====================================================
       전체 문자열 메모리 정리
       ===================================================== */
    for (int i = 0; i < CM; i++)
    {
        free(C[i]);
    }


    free(C);


    return 0;
}


/* =========================================================
   main
   ========================================================= */
int main()
{
    Chat();

    return 0;
}