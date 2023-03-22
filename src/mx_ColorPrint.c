#include "uls.h"

static void printDirectory(t_file *file);
static void printFile(t_file *file);

void mx_ColorPrint(t_file *file) {
    if (S_ISDIR(file->newStructFile.st_mode))
        printDirectory(file);
    else if (S_ISLNK(file->newStructFile.st_mode))
        mx_printstr("\x1B[35m");
    else if (S_ISBLK(file->newStructFile.st_mode))
        mx_printstr("\x1B[37m");
    else if (S_ISCHR(file->newStructFile.st_mode))
        mx_printstr("\x1B[0;34;43m");
    else if (S_ISFIFO(file->newStructFile.st_mode))
        mx_printstr("\x1B[37m");
    else if (S_ISSOCK(file->newStructFile.st_mode))
        mx_printstr("\x1B[32m");
    else if (S_ISREG(file->newStructFile.st_mode)) {
        printFile(file);
    }
    mx_printstr(file->filename);
    mx_printstr("\x1B[0m");
}

static void printFile(t_file *file) {
    if ((file->perm[3] == 's') || (file->perm[3] == 'S'))
        mx_printstr("\x1B[37m");
    else if ((file->perm[6] == 's') || (file->perm[6] == 'S'))
        mx_printstr("\x1B[37m");
    else if (file->perm[3] == 'x')
        mx_printstr("\x1B[31m");
    else
        mx_printstr("\x1B[0m");
}
static void printDirectory(t_file *file) {
    if (((file->perm[9] == 't') || (file->perm[9] == 'T')) && file->perm[8] == 'w')
        mx_printstr("\x1B[37m");
    else if ((file->perm[9] == 'x') && file->perm[8] == 'w')
        mx_printstr("\x1B[37m");
    else
        mx_printstr("\x1B[34m");
}

