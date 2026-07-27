#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

/* 플랫폼별 헤더 및 매크로 정의 */
#ifdef _WIN32
    #include <windows.h>
    #include <direct.h>
    #define PATH_MAX_LEN MAX_PATH
    #define GET_CWD _getcwd
    #define STR_CASE_CMP _stricmp
    #define ABS_PATH(path, resolved) _fullpath(resolved, path, PATH_MAX_LEN)
    #define STAT_STRUCT struct _stat
    #define STAT_FUNC _stat
#else
    #include <unistd.h>
    #include <limits.h>
    #include <sys/stat.h>
    #define PATH_MAX_LEN PATH_MAX
    #define GET_CWD getcwd
    #define STR_CASE_CMP strcasecmp
    #define ABS_PATH(path, resolved) realpath(path, resolved)
    #define STAT_STRUCT struct stat
    #define STAT_FUNC stat
#endif

/* 유틸리티: 문자열의 앞뒤 공백 및 줄바꿈 제거 */
void trim(char *str) {
    char *end;
    // 앞쪽 공백 제거
    while (isspace((unsigned char)*str)) str++;
    if (*str == 0) return;
    // 뒤쪽 공백 제거
    end = str + strlen(str) - 1;
    while (end > str && isspace((unsigned char)*end)) end--;
    end[1] = '\0';
}

/* 유틸리티: 문자열을 대문자로 변환 */
void to_upper(char *str) {
    for (; *str; ++str) *str = toupper((unsigned char)*str);
}

/* 파일 존재 여부 확인 함수 */
bool file_exists(const char *path) {
    STAT_STRUCT buffer;
    return (STAT_FUNC(path, &buffer) == 0);
}

/* 파일 확장자 확인 함수 */
bool ends_with(const char *str, const char *suffix) {
    if (!str || !suffix) return false;
    size_t len_str = strlen(str);
    size_t len_suffix = strlen(suffix);
    if (len_suffix > len_str) return false;
    return STR_CASE_CMP(str + len_str - len_suffix, suffix) == 0;
}

void handle_file() {
    /* 파일 경로를 입력받아 실행하거나 내용을 출력/수정하는 함수 */
    printf("--- 파일 관리 프로그램 시작 ---\n");

    char file_path[PATH_MAX_LEN];
    char action_input[10];
    char resolved_path[PATH_MAX_LEN];

    while (true) {
        // 파일 경로 입력 루틴 (오류 처리 포함)
        printf("\n[1] 파일 경로를 입력하세요 (예: C:/my_file.py 또는 ./my_script.py): ");
        if (fgets(file_path, PATH_MAX_LEN, stdin) == NULL) break;
        
        trim(file_path);

        // 'exit' 입력 시 프로그램 종료
        char temp_path[PATH_MAX_LEN];
        strcpy(temp_path, file_path);
        for(int i = 0; temp_path[i]; i++) temp_path[i] = tolower(temp_path[i]);
        
        if (strcmp(temp_path, "exit") == 0) {
            printf("프로그램을 종료합니다.\n");
            break;
        }

        // 1. 파일 경로 유효성 및 존재 여부 확인
        if (strlen(file_path) == 0) {
            printf("❌ 오류: 파일 경로를 입력하지 않았습니다. 다시 입력해주세요.\n");
            continue;
        }

        if (!file_exists(file_path)) {
            printf("❌ 오류: '%s' 경로에 파일이 존재하지 않습니다. 경로/파일명이 정확한지 확인해 주세요.\n", file_path);
            // 팁 제공: Pydroid3 사용자에게 유용한 팁
            if (strstr(file_path, "storage/emulated") != NULL) {
                printf("💡 팁: Android(Pydroid3 등)에서는 경로가 정확해도 권한 문제로 접근이 안될 수 있습니다. 파일을 작업 폴더로 복사해 보세요.\n");
            }
            continue;
        }

        // 2. 파일 처리 옵션 선택
        if (ABS_PATH(file_path, resolved_path) != NULL) {
            printf("\n✅ 파일 확인됨: %s\n", resolved_path);
        } else {
            printf("\n✅ 파일 확인됨: %s\n", file_path);
        }

        while (true) {
            printf("[2] 원하는 작업을 선택하세요 (S: 실행, R: 읽기/출력, E: 수정, C: 경로 재입력): ");
            if (fgets(action_input, sizeof(action_input), stdin) == NULL) break;
            
            trim(action_input);
            to_upper(action_input);
            char action = action_input[0];

            if (action == 'C') {
                break; // 상위 while 루프로 돌아가 경로를 재입력
            } else if (action == 'S') {
                // 3. 파일 실행 (파이썬 파일에 주로 사용)
                printf("\n🚀 파일 실행 시작: %s\n", file_path);
                
                char command[PATH_MAX_LEN + 50];
                int result_code = -1;

                // 파이썬 파일 여부 확인
                if (ends_with(file_path, ".py") || ends_with(file_path, ".pyw")) {
                    // C에서는 sys.executable에 직접 대응하는 값이 없으므로 시스템의 python/python3 명령어를 사용함
                    #ifdef _WIN32
                        snprintf(command, sizeof(command), "python \"%s\"", file_path);
                    #else
                        snprintf(command, sizeof(command), "python3 \"%s\"", file_path);
                    #endif
                    result_code = system(command);
                } else {
                    // 파이썬 파일이 아니면 기본 시스템 프로그램으로 열기 시도
                    #ifdef _WIN32
                        snprintf(command, sizeof(command), "start \"\" \"%s\"", file_path);
                    #elif __APPLE__
                        snprintf(command, sizeof(command), "open \"%s\"", file_path);
                    #else
                        snprintf(command, sizeof(command), "xdg-open \"%s\"", file_path);
                    #endif
                    result_code = system(command);
                }

                if (result_code == -1) {
                    printf("\n❌ 실행 오류: 파일 실행기를 찾을 수 없거나 실행에 실패했습니다.\n");
                } else {
                    printf("\n✅ 파일 실행 완료 (종료 코드: %d)\n", result_code);
                }
                break;
            } else if (action == 'R') {
                // 4. 파일 내용 읽기 및 출력
                FILE *f = fopen(file_path, "r");
                if (f == NULL) {
                    printf("❌ 읽기 오류 발생: 파일을 열 수 없습니다.\n");
                } else {
                    printf("\n================== 파일 내용 시작 ==================\n");
                    char buffer[1024];
                    // C의 기본 파일 읽기는 인코딩 검사를 자동으로 수행하지 않으나, 
                    // 로직상 내용을 그대로 출력함
                    while (fgets(buffer, sizeof(buffer), f) != NULL) {
                        printf("%s", buffer);
                    }
                    if (ferror(f)) {
                        printf("\n❌ 읽기 오류 발생: 파일 읽기 중 오류가 발생했습니다.\n");
                    }
                    printf("\n================== 파일 내용 끝 ==================\n");
                    fclose(f);
                }
                break;
            } else if (action == 'E') {
                // 5. 파일 수정 (텍스트 에디터 실행)
                char *editor = getenv("EDITOR");
                char command[PATH_MAX_LEN + 100];

                if (editor == NULL) {
                    #ifdef _WIN32
                        editor = "notepad";
                    #else
                        // code(VS Code) 존재 여부 확인 시뮬레이션
                        if (access("/usr/bin/code", F_OK) == 0) {
                            editor = "code";
                        } else {
                            editor = "nano";
                        }
                    #endif
                }

                printf("\n🛠️ %s를 사용하여 파일 수정 시작: %s\n", editor, file_path);
                snprintf(command, sizeof(command), "%s \"%s\"", editor, file_path);
                
                int edit_res = system(command);
                if (edit_res == -1) {
                    printf("\n❌ 오류: 텍스트 에디터 '%s'를 찾을 수 없습니다. 수동으로 파일을 여세요.\n", editor);
                } else {
                    printf("\n✅ 파일 수정 완료 (에디터 종료됨)\n");
                }
                break;
            } else {
                printf("❌ 오류: 올바른 작업을 선택하세요 (S, R, E, C).\n");
            }
        }
    }
}

int main() {
    handle_file();
    return 0;
}
