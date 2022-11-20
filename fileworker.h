#ifndef FILEWORKER_H
#define FILEWORKER_H
#include <stdio.h>
#include "mainwindow.h"
struct Record {
    char func[50];
    char date[20];
};
// получение размера файла
int GetFileSizeInBytes(FILE *pfile);

// получение количества записей в файле
int GetRecordsCountInFile(FILE *pfile);

// чтение из файла по индексу
Record ReadRecordFromFile(FILE *pfile, int index);

// запись в файл
void WriteFile(FILE *pfile, char *func);

// файл пустой или нет?
bool FileEmpty(FILE* f_param);

#endif // FILEWORKER_H
