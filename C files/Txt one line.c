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