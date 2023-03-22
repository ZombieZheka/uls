#include "uls.h"
#define MAX 15778400
#define TIMESIZE 20
#define CURMORE 4
#define RESALTSIZE 12

static void printTimeWithoutSeond(time_t ourTime);
static void printTimeWithSecond(time_t ourTime);

void mx_printT(t_file *file, t_cmd *cmd) {
    if (cmd->time_type == aTime) {
        if (cmd->format_t)
            printTimeWithSecond(file->newStructFile.st_atime);
        else
            printTimeWithoutSeond(file->newStructFile.st_atime);
    }
    else if (cmd->time_type == mTime) {
        if (cmd->format_t)
            printTimeWithSecond(file->newStructFile.st_mtime);
        else
            printTimeWithoutSeond(file->newStructFile.st_mtime);
    }
    else {
        if (cmd->format_t)
            printTimeWithSecond(file->newStructFile.st_ctime);
        else
            printTimeWithoutSeond(file->newStructFile.st_ctime);
    }
}

static void printTimeWithoutSeond(time_t ourTime) {
    char *cur = ctime(&ourTime);
    char *result = mx_strnew(RESALTSIZE);
    time_t timeNow = time(NULL);

    if (timeNow < ourTime || (timeNow - MAX) > ourTime) {
        result = mx_strncpy(result, cur + CURMORE, RESALTSIZE/2);
        mx_strcpy(result + RESALTSIZE/2, "  ");
        mx_strncpy(result + CURMORE * 2, cur + TIMESIZE, CURMORE);
        mx_printstr(result);
        free(result);
    }
    else {
        result = mx_strncpy(result, cur + CURMORE, CURMORE*3);
        mx_printstr(result);
        free(result);
    }
}

static void printTimeWithSecond(time_t ourTime) {
    char *cur = ctime(&ourTime);
    char *result = mx_strnew(TIMESIZE);

    result = mx_strncpy(result, cur + CURMORE, TIMESIZE);
    mx_printstr(result);
    free(result);
}
