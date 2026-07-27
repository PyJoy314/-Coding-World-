#include <stdio.h>

int main() {
    int B;
    char ID[10];

    printf("input the Samsung baseball number : ");
    scanf("%d", &B);
    printf("No.%d \n", B);

    printf("input the Samsung baseball name : ");
    scanf("%9s", ID);
    printf("Samsung Team of %s\n\n", ID); // 가독성을 위해 줄바꿈 추가

    // 배열 정리: 가독성을 위해 데이터를 정렬하여 선언
    char *stats[] = {
        "경기일\t시즌종합\t06.12\t06.11\t06.10\t06.09\t06.07\t06.06",
        "타율\t0.285\t0.333\t0.400\t0.000\t0.000\t0.250\t0.000",
        "타수\t246\t3\t5\t3\t4\t4\t5",
        "안타\t70\t1\t2\t0\t0\t1\t0",
        "2타\t10\t0\t0\t0\t0\t0\t0",
        "3타\t0\t0\t0\t0\t0\t0\t0",
        "홈런\t11\t0\t0\t0\t0\t0\t0",
        "타점\t48\t0\t2\t0\t0\t0\t0",
        "득점\t36\t1\t2\t0\t0\t0\t0",
        "도루\t1\t0\t0\t0\t0\t1\t0",
        "사사구\t31\t1\t0\t1\t0\t1\t0",
        "삼진\t45\t0\t1\t0\t1\t1\t1",
        "출루율\t0.361\t0.500\t0.400\t0.250\t0.000\t0.400\t0.000",
        "장타율\t0.459\t0.333\t0.400\t0.000\t0.000\t0.250\t0.000",
        "OPS\t0.820\t0.833\t0.800\t0.250\t0.000\t0.650\t0.000"
    };

    // 요청하신 대로 마지막 출력 방식은 그대로 유지
    printf("%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n", 
           stats[0], stats[1], stats[2], stats[3], stats[4], 
           stats[5], stats[6], stats[7], stats[8], stats[9], 
           stats[10], stats[11], stats[12], stats[13], stats[14]);

    return 0;
}
