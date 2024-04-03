#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// ?ñâÎß®Í≤å?ûÑ Íµ¨ÌòÑ
// ?ïúÍ∏? Íπ®Ïßê

typedef struct Word {
    char* english;
    char* korean;
} Word;

Word* getWord(const char* filename, int* size){
    // ?åå?ùº ?ó¥Í∏?
    FILE *in = fopen("word.txt", "r");
    if (in == NULL) {
        printf("?åå?ùº ?ó¥Í∏? ?ã§?å®: %s\n", filename);
    }

    // ?ã®?ñ¥ Í∞úÏàò ?Ñ∏Í∏?
    *size = 0;
    char line[50];
    while (fgets(line, sizeof(line), in)) {
        (*size)++;
    }
    rewind(in);

    // ?èô?†Å ?ï†?ãπ
    Word* words = malloc(sizeof(Word) * (*size));
    if (words == NULL) {
        printf("?èô?†Å Î©îÎ™®Î¶? ?ï†?ãπ ?ò§Î•?\n");
        fclose(in);
        exit(1);
    }

    // ?åå?ùº ?Ç¥?ö© ?ùΩ?ñ¥?Ñú Î∞∞Ïó¥?óê ????û•
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

void check(char* word, int* correct, int length, int stage) {
    char* answer = malloc(length);
    if (stage == 1) {
        printf("ø¯«œ¥¬ æÀ∆ƒ∫™¿ª ¿‘∑¬«œººø‰>> ");
        scanf("%s", &answer);

        for (int i = 0; i < length; i++) {
            if (word[i] == answer[0]) {
                correct[i] = 1;
            }
        }
    }
    else {

    }
}

void stage2(char* word, int* length) {
    char* answer = malloc(length + 1);

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < length; j++) {
            printf("_");
        }
        scanf("%c", &answer);
        //check(word, answer, length, stage);
    }


}

void stage1(char* word, int length, int* life) {
    int* correct = (int*)malloc(sizeof(int) * length);
    int stage = 1;

    memset(correct, 0, sizeof(int) * length);
    for (int i = 0; i < length; i++) {
        printf("_ ");
    }
    printf("\n");
    
    check(word, &correct, length, stage);

    for (int i = 0; i < length; i++) {
        if (correct[i] == 1) {
            printf("%c ", word[i]);
        }
        else {
            printf("_ ");
        }
    }

    free(correct);
}

void game(Word* words, int size, int* life) {
    srand(time(NULL));
    int i = rand() % size;

    int length = strlen(words[i].english);
    char* word = malloc(length + 1);
    strcpy(word, words[i].english);

    stage1(word, length, &life);
    //stage2(word, length);

    free(word);
}

int main() {
    int life;
    int size;
    const char* filename = "word.txt";

    Word* words = getWord(filename, &size);
    if (words == NULL) {
        return 1;
    }

    game(words, size, &life);

    //printWords(words, size);

    freeWords(words, size);
}