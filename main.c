#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct Word {
    char* english;
    char* korean;
} Word;

Word* getWord(const char* filename, int* size){
    // 파일 열기
    FILE *in = fopen("word.txt", "r");
    if (in == NULL) {
        printf("파일 열기 실패: %s\n", filename);
    }

    // 단어 개수 세기
    *size = 0;
    char line[50];
    while (fgets(line, sizeof(line), in)) {
        (*size)++;
    }
    rewind(in);

    // 동적 할당
    Word* words = malloc(sizeof(Word) * (*size));
    if (words == NULL) {
        printf("동적 메모리 할당 오류\n");
        fclose(in);
        exit(1);
    }

    // 파일 내용 읽어서 배열에 저장
    int i = 0;
    while (fgets(line, sizeof(line), in)) {
        char* english = strtok(line, " ");
        char* korean = strtok(NULL, "\n");

        words[i].english = malloc(strlen(english) + 1);
        words[i].korean = malloc(strlen(korean) + 1);

        strcpy(words[i].english, english);
        strcpy(words[i].korean, korean);

        i++;
    }

    fclose(in);
    return words;
}

void printWords(Word* words, int size) {
    for (int i = 0; i < size; i++) {
        printf("%s: %s\n", words[i].english, words[i].korean);
    }
}

void freeWords(Word* words, int size) {
    for (int i = 0; i < size; i++) {
        free(words[i].english);
        free(words[i].korean);
    }
    free(words);
}

int main(){
    const char* filename = "word.txt";
    
    int size;

    Word* words = getWord(filename, &size);
    if (words == NULL) {
        return 1;
    }

    printWords(words, size);

    freeWords(words, size);
}