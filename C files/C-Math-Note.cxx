#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void engineering_calculator();

int gcd(int a, int b)
{
    while (b != 0)
    {
        int r = a % b;
        a = b;
        b = r;
    }
    return a;
}

int main()
{
    int choice;

    while (1)
    {
        printf("\n=================================\n");
        printf("   Multiverse Math Notebook\n");
        printf("=================================\n");
        printf("1. GCD & LCM\n");
        printf("2. Prime Factorization\n");
        printf("3. Linear Equation\n");
        printf("4. Geometry Area\n");
        printf("5. Engineering Calculator\n");
        printf("0. Exit\n");
        printf("=================================\n");

        printf("Select : ");
        scanf("%d", &choice);

        if (choice == 0)
        {
            printf("Program End\n");
            break;
        }

        switch(choice)
        {
            case 1:
            {
                int a, b;

                printf("Input 2 integers : ");
                scanf("%d %d", &a, &b);

                int g = gcd(a, b);
                int l = (a * b) / g;

                printf("GCD = %d\n", g);
                printf("LCM = %d\n", l);
                break;
            }

            case 2:
            {
                int n;

                printf("Input number : ");
                scanf("%d", &n);

                printf("%d = ", n);

                int first = 1;

                for (int i = 2; i <= n; i++)
                {
                    int count = 0;

                    while (n % i == 0)
                    {
                        count++;
                        n /= i;
                    }

                    if (count > 0)
                    {
                        if (!first)
                            printf(" x ");

                        if (count > 1)
                            printf("%d^%d", i, count);
                        else
                            printf("%d", i);

                        first = 0;
                    }
                }

                printf("\n");
                break;
            }

            case 3:
            {
                double a, b, c;

                printf("Input a b c : ");
                scanf("%lf %lf %lf", &a, &b, &c);

                if (a == 0)
                {
                    printf("No unique solution\n");
                }
                else
                {
                    double x = (c - b) / a;
                    printf("x = %.4lf\n", x);
                }

                break;
            }

            case 4:
            {
                int type;

                printf("1 Triangle\n");
                printf("2 Rectangle\n");
                printf("3 Circle\n");
                printf("Select : ");

                scanf("%d", &type);

                if (type == 1)
                {
                    double base, height;

                    scanf("%lf %lf", &base, &height);

                    printf("Area = %.2lf\n",
                           (base * height) / 2.0);
                }
                else if (type == 2)
                {
                    double width, length;

                    scanf("%lf %lf",
                           &width,
                           &length);

                    printf("Area = %.2lf\n",
                           width * length);
                }
                else if (type == 3)
                {
                    double r;

                    scanf("%lf", &r);

                    printf("Area = %.4lf\n",
                           r * r * M_PI);
                }

                break;
            }

            case 5:
            {
                engineering_calculator();
                break;
            }

            default:
            {
                printf("Invalid Menu\n");
            }
        }
    }

    return 0;
}

void engineering_calculator()
{
    double A, B, C;
    int Z;

    printf("\nInput 3 numbers : ");
    scanf("%lf %lf %lf",
          &A,
          &B,
          &C);

    printf("\n===== Engineering Calculator =====\n");

    printf("A + B + C = %.2lf\n",
           A + B + C);

    printf("A - B - C = %.2lf\n",
           A - B - C);

    printf("A * B * C = %.2lf\n",
           A * B * C);

    if (B != 0 && C != 0)
    {
        printf("A / B / C = %.6lf\n",
               A / B / C);
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

    printf("A^2 = %.2lf\n", A*A);
    printf("B^2 = %.2lf\n", B*B);
    printf("C^2 = %.2lf\n", C*C);

    printf("\n===== Cube =====\n");

    printf("A^3 = %.2lf\n", A*A*A);
    printf("B^3 = %.2lf\n", B*B*B);
    printf("C^3 = %.2lf\n", C*C*C);

    printf("\n===== Increment =====\n");

    int N = 10;

    printf("N = %d\n", N);

    N++;
    printf("N++ = %d\n", N);

    N++;
    printf("N++ = %d\n", N);

    N--;
    printf("N-- = %d\n", N);
}