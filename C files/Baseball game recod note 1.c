#include <stdio.h>

int main() {
    int B;
    char ID[10];

    printf("Input the Samsung baseball number : ");
    scanf("%d", &B);
    printf("No.%d \n", B);

    printf("Input the Samsung baseball name : ");
    scanf("%9s", ID);
    printf("Samsung Team of %s\n\n", ID);

    // Array update: All Korean labels converted to professional baseball English stats
    char *stats[] = {
        "DATE\tTOTAL\t06.12\t06.11\t06.10\t06.09\t06.07\t06.06",
        "AVG\t0.285\t0.333\t0.400\t0.000\t0.000\t0.250\t0.000",
        "AB\t246\t3\t5\t3\t4\t4\t5",
        "H\t70\t1\t2\t0\t0\t1\t0",
        "2B\t10\t0\t0\t0\t0\t0\t0",
        "3B\t0\t0\t0\t0\t0\t0\t0",
        "HR\t11\t0\t0\t0\t0\t0\t0",
        "RBI\t48\t0\t2\t0\t0\t0\t0",
        "R\t36\t1\t2\t0\t0\t0\t0",
        "SB\t1\t0\t0\t0\t0\t1\t0",
        "BB/HBP\t31\t1\t0\t1\t0\t1\t0",
        "SO\t45\t0\t1\t0\t1\t1\t1",
        "OBP\t0.361\t0.500\t0.400\t0.250\t0.000\t0.400\t0.000",
        "SLG\t0.459\t0.333\t0.400\t0.000\t0.000\t0.250\t0.000",
        "OPS\t0.820\t0.833\t0.800\t0.250\t0.000\t0.650\t0.000"
    };

    // The output structure remains completely identical to your original code
    printf("%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n", 
           stats[0], stats[1], stats[2], stats[3], stats[4], 
           stats[5], stats[6], stats[7], stats[8], stats[9], 
           stats[10], stats[11], stats[12], stats[13], stats[14]);

    return 0;
}