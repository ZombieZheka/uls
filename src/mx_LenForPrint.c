#include "uls.h"

static void cmpMaxNumber(int *number, int numb);
static void cmpMaxChr(int *number, char *str);

#define LINESIZE 8

t_lenthMax *mx_LenForPrint(t_list *fileList) {
    t_lenthMax *lenth;

    lenth = malloc(sizeof(t_lenthMax));

    lenth->lnkStruct = 0;
    lenth->OwnStruct = 0;
    lenth->GrpStruct = 0;
    lenth->SizeStruct = 0;

    t_file *current;
    bool isPrint = false;

    if (!fileList)
        return NULL;

    for (t_list *i = fileList; i != NULL; i = i->next) {
        current = i->data;
        cmpMaxNumber(&lenth->lnkStruct, current->newStructFile.st_nlink);
        cmpMaxChr(&lenth->OwnStruct, current->owner);
        cmpMaxChr(&lenth->GrpStruct, current->group);
        cmpMaxNumber(&lenth->SizeStruct, current->newStructFile.st_size);
        if (S_ISBLK(current->newStructFile.st_mode) || S_ISCHR(current->newStructFile.st_mode))
            isPrint = true;
    }
    if (isPrint) {
        if (lenth->SizeStruct < LINESIZE)
            lenth->SizeStruct = LINESIZE;
        else
            lenth->SizeStruct = lenth->SizeStruct;
    }
    return lenth;
}

static void cmpMaxChr(int *number, char *str) {
    int newSize = mx_strlen(str);
    if (*number < newSize)
        *number = newSize;
}

static void cmpMaxNumber(int *number, int numb) {
    char *cur = mx_itoa(numb);
    int newSize = mx_strlen(cur);
    if (*number < newSize)
        *number = newSize;
    free(cur);
}

