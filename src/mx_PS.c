#include "uls.h"
#define MAXCHAR 256
#define SIZEFILE 10
#define SPACECOUNT 3
#define MAX 24


void mx_PS(t_file *file, t_lenthMax *lenMax, t_cmd *cmd) {
    char *cur;

    if (S_ISBLK(file->newStructFile.st_mode) || S_ISCHR(file->newStructFile.st_mode)) {
        int newCur;
        char *max;
        char *min;
        char *curent = NULL;

        max = mx_itoa((file->newStructFile.st_rdev >> MAX) & 0xffffff);
        newCur = (file->newStructFile.st_rdev & 0xffffff);

        if (newCur > MAXCHAR) {
            min = mx_strnew(SIZEFILE);
            mx_strcpy(min, "0x00000000");
            curent = mx_nbr_to_hex(newCur);
            mx_strcpy(min + (SIZEFILE - mx_strlen(curent)), curent);
            free(curent);
        }
        else
            min = mx_itoa(newCur);

        mx_printspaces(SPACECOUNT - mx_strlen(max));
        mx_printstr(max);
        mx_printstr(", ");
        mx_printspaces(SPACECOUNT - mx_strlen(min));
        mx_printstr(min);
        free(max);
        free(min);
        cmd->format_h = false;
    }
    else {
        if (cmd->format_h) {
            mx_printspaces(1);
            cur = mx_Size(file->newStructFile.st_size);
            mx_printstr(cur);
            free(cur);
        }
        else {
            cur = mx_itoa(file->newStructFile.st_size);
            mx_printspaces(lenMax->SizeStruct - mx_strlen(cur));
            mx_printstr(cur);
            free(cur);
        }
    }
}



