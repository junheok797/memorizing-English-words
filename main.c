#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct Word
{
    char* english;
    char* korean;
} Word;

Word* getWord(const char* filename, int* size)
{
    // 파일 열기
    FILE* file = fopen(filename, "r");
    if (file == NULL)
        printf("파일 열기 실패: %s\n", filename);

    // 단어 개수 세기
    *size = 0;
    char line[50];
    while (fgets(line, sizeof(line), file))
        (*size)++;
    rewind(file);

    // 동적 할당
    Word* words = malloc(sizeof(Word) * (*size));
    if (words == NULL)
    {
        printf("메모리 할당 실패\n");
        fclose(file);
        exit(1);
    }

    // 파일 내용 읽어서 배열에 저장
    int i = 0;
    while (fgets(line, sizeof(line), file))
    {
        char* english = strtok(line, " ");
        char* korean = strtok(NULL, "\n");

        words[i].english = malloc(strlen(english) + 1);
        words[i].korean = malloc(strlen(korean) + 1);

        strcpy(words[i].english, english);
        strcpy(words[i].korean, korean);

        i++;
    }

    fclose(file);
    return words;
}

void printWords(Word* words, int size)
{
    for (int i = 0; i < size; i++)
        printf("%s: %s\n", words[i].english, words[i].korean);
}

void freeWords(Word* words, int size)
{
    for (int i = 0; i < size; i++)
    {
        free(words[i].english);
        free(words[i].korean);
    }
    free(words);
}

void check(char* word, int* correct, int length, int stage)
{
    char* answer = malloc(length);

    if (stage == 1) {
        printf("Enter a letter: ");
        scanf("%s", answer);
        printf("\n");

        for (int i = 0; i < length; i++) {
            if (word[i] == answer[0]) {
                correct[i] = 1;
            }
        }
    }
    else {

    }
}

void printWord(char* word, int* correct, int length)
{
    for (int i = 0; i < length; i++)
    {
        if (correct[i] == 1)
            printf("%c ", word[i]);
        else
            printf("_ ");
    }
    printf("\n\n");
}

void stage2(char* word, int* length, int* life)
{

}

void stage1(char* word, int* correct, int length, int* life)
{
    int stage = 1;
    int repetition = 1;

    while (repetition <= 3) {
        printWord(word, correct, length);
        check(word, correct, length, stage);
        repetition++;
    }

    free(correct);
}

void game(Word* words, int size, int* life)
{
    srand(time(NULL));
    int i = rand() % size;

    int length = strlen(words[i].english);
    char* word = malloc(length + 1);
    strcpy(word, words[i].english);

    int* correct = (int*)malloc(sizeof(int) * length);
    memset(correct, 0, sizeof(int) * length);

    printf("Welcom to Hangman!\n\n");

    stage1(word, correct, length, &life);
    //stage2(word, &length, &life);

    free(word);
}

int main()
{
    int life;
    int size;
    const char* filename = "words.txt";

    Word* words = getWord(filename, &size);
    if (words == NULL) {
        return 1;
    }

    game(words, size, &life);

    //printWords(words, size);

    freeWords(words, size);
}