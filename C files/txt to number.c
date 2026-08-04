#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>

int main() {
    const char *str = "https://www.desmos.com/calculator/3rsafxdhxs | https://alanbecker.wiki/wiki/Yellow  | StickFigureYellow.exe | https://open.spotify.com/playlist/4YlmnRFnayIkVYyYUW7Duv?si=b3d81ad820524dde";

    char *endptr;
    errno = 0; // 에러 플래그 초기화

    long num = strtol(str, &endptr, 10); // 10진수 변환

    // 변환 실패 또는 범위 초과 체크
    if (errno == ERANGE || num > INT_MAX || num < INT_MIN) {
        printf("숫자 범위를 초과했습니다.\n");
        return 1;
    }
    if (endptr == str || *endptr != '\0') {
        printf("유효하지 않은 숫자 형식입니다.\n");
        return 1;
    }

    printf("변환된 숫자: %ld\n", num);
    return 0;
}
