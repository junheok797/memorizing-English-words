#ifndef WORD_H
#define WORD_H

typedef struct Word
{
    char* english;
    char* korean;

} Word;

Word* getWord(const char* filename, int* size);

#endif