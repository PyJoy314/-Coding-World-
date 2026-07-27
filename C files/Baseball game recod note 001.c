#include <stdio.h>
#include <string.h>

int main() {
    int B;
    char ID[30];

    printf("Input the Samsung baseball number : ");
    scanf("%d", &B);
    printf("No.%d \n", B);

    printf("Input the Samsung baseball name : ");

    getchar(); // 엔터 제거
    fgets(ID, sizeof(ID), stdin);

    // 줄바꿈 제거
    ID[strcspn(ID, "\n")] = 0;

    printf("Samsung Team of %s\n\n", ID);

    if (strcmp(ID, "Lewin Diaz") == 0) {
        // 문자열 배열
        char *stats[] = {

        "Match day\tSeason Summary\t06.13\t06.12\t06.11\t06.10\t06.09\t06.07",

        "batting average\t0.285\t0.333\t0.333\t0.400\t0.000\t0.000\t0.250",

        "hitter\t249\t3\t3\t5\t3\t4\t4",

        "safety\t71\t1\t1\t2\t0\t0\t1",

        "2 hits\t10\t0\t0\t0\t0\t0\t0",

        "3 hits\t0\t0\t0\t0\t0\t0\t0",

        "homer\t11\t0\t0\t0\t0\t0\t0",

        "RBIs\t48\t0\t0\t2\t0\t0\t0",

        "score\t37\t1\t1\t2\t0\t0\t0",

        "theft\t1\t0\t0\t0\t0\t0\t1",

        "Sasago\t32\t1\t1\t0\t1\t0\t1",

        "fan\t45\t0\t0\t1\t0\t1\t1",

        "On-base percentage\t0.363\t0.500\t0.500\t0.400\t0.250\t0.000\t0.400",

        "Slugging percentage\t0.458\t0.333\t0.333\t0.400\t0.000\t0.000\t0.250",

        "OPS\t0.821\t0.833\t0.833\t0.800\t0.250\t0.000\t0.650"
        };
        
        // printf 하나만 사용
        printf(
        "%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n",

        stats[0], stats[1], stats[2], stats[3], stats[4],
        stats[5], stats[6], stats[7], stats[8], stats[9],
        stats[10], stats[11], stats[12], stats[13], stats[14]
        );
    }

    return 0;
}