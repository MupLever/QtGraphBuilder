#include "fileworker.h"

void WriteFile(FILE *pfile, char *func) {
    Record record;
    if (!(pfile = fopen("./cache", "rb+")) || FileEmpty(pfile)) {
        pfile = fopen("./cache", "wb");
        rewind(pfile);
    } else {
        pfile = fopen("./cache", "a+b");
        fseek(pfile, 0, SEEK_END);
    }
    time_t now = time(0);
    tm *ltm = localtime(&now);
    char buffer[20];
    strftime(buffer, 20, "%d.%m.%y %H:%M:%S", ltm);
    strcpy(record.func, func);
    strcpy(record.date, buffer);
    fwrite(&record, sizeof(Record), 1, pfile);
    fclose(pfile);
}

Record ReadRecordFromFile(FILE *pfile, int index) {
    int offset = index * sizeof(Record);
    fseek(pfile, offset, SEEK_SET);
    Record l_record;
    fread(&l_record, sizeof(Record), 1, pfile);
    rewind(pfile);
    return l_record;
}

int GetFileSizeInBytes(FILE *pfile) {
    int size = 0;
    fseek(pfile, 0, SEEK_END);
    size = ftell(pfile);
    rewind(pfile);
    return size;
}

int GetRecordsCountInFile(FILE *pfile) {
    return GetFileSizeInBytes(pfile) / sizeof(Record);
}

bool FileEmpty(FILE* pfile) {
    bool flag = true;
    fseek(pfile, 0, SEEK_END);
    long pos = ftell(pfile);
    if (pos > 0 ) {
        rewind(pfile);
        flag = false;
    }
    return flag;
}
