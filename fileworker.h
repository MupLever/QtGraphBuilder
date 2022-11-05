#ifndef FILEWORKER_H
#define FILEWORKER_H
#include <stdio.h>
#include "mainwindow.h"
struct Record {
    char func[50];
    char date[20];
};
int GetFileSizeInBytes(FILE *pfile);

int GetRecordsCountInFile(FILE *pfile);

Record ReadRecordFromFile(FILE *pfile, int index);

void WriteFile(FILE *pfile, char *func);

bool FileEmpty(FILE* f_param);

#endif // FILEWORKER_H
