#include "uls.h"

static t_list *ListUls(t_list *list, t_cmd *cmd, bool (*cmp)(void *first, void *second, t_cmd *cmd));
static void PrintFormat(t_list *fileList, t_cmd *cmd);
static bool aTimeFunc(void *firstDirectory, void *secondDirectory, t_cmd *cmd);
static bool cTimeFunc(void *firstDirectory, void *secondDirectory, t_cmd *cmd);
static bool mTimeFunc(void *firstDirectory, void *secondDirectory, t_cmd *cmd);
static bool Size(void *firstDirectory, void *secondDirectory, t_cmd *cmd);
static bool Name(void *firstDirectory, void *secondDirectory, t_cmd *cmd);

void mx_PrintListFor(t_list *fileList, t_cmd *cmd) {
    if (cmd->sort_type == noneType)
        return;
    ListUls(fileList, cmd, Name);

    if (cmd->sort_type == timeType) {
        if (cmd->time_type == cTime)
            ListUls(fileList, cmd, cTimeFunc);
        else if (cmd->time_type == mTime)
            ListUls(fileList, cmd, mTimeFunc);
        else if (cmd->time_type == aTime)
            ListUls(fileList, cmd, aTimeFunc);
    }
    else if (cmd->sort_type == sizeType)
        ListUls(fileList, cmd, Size);
    if (cmd->print_func == longFormat)
        mx_PrintLong(fileList, cmd);
    else if (cmd->print_func == stdFormat)
        mx_PSF(fileList, cmd);
    else if (cmd->print_func == colFormat)
        PrintFormat(fileList, cmd);
    else if (cmd->print_func == mFormat)
        mx_FormatForPrint(fileList, cmd);
}
t_list *ListUls(t_list *list, t_cmd *cmd, bool (*cmp)(void *first, void *second, t_cmd *cmd)) {
    t_list *tmp = NULL;
    t_list *newList = list;
    void *dataForTransf;

    while (list) {
        tmp = newList;
        while (tmp) {
            if (tmp->next && cmp(tmp->data, tmp->next->data, cmd)) {
                dataForTransf = tmp->data;
                tmp->data = tmp->next->data;
                tmp->next->data = dataForTransf;
            }
            tmp = tmp->next;
        }
        list = list->next;
    }
    return tmp;
}
void PrintFormat(t_list *fileList, t_cmd *cmd) {
    t_file *cur;

    for (t_list *i = fileList; i; i = i->next) {
        cur = i->data;
        if (i->next == NULL) {
            mx_printstr(cur->filename);
            break;
        }
        if (!cmd->format_g)
            mx_printstr(cur->filename);
        else
            mx_ColorPrint(cur);
        mx_printchar('\n');
    }
    mx_printchar('\n');
}
bool aTimeFunc(void *firstDirectory, void *secondDirectory, t_cmd *cmd) {

    if (((t_file *)firstDirectory)->newStructFile.st_atime
            > ((t_file *)secondDirectory)->newStructFile.st_atime
            && cmd->print_reverse)
        return true;
    else if (((t_file *)firstDirectory)->newStructFile.st_atime
            < ((t_file *)secondDirectory)->newStructFile.st_atime
            && !(cmd->print_reverse))
        return true;
    else
        return false;
}
bool cTimeFunc(void *firstDirectory, void *secondDirectory, t_cmd *cmd) {
    if (((t_file *)firstDirectory)->newStructFile.st_ctime
            < ((t_file *)secondDirectory)->newStructFile.st_ctime
            && !(cmd->print_reverse))
        return true;
    else if (((t_file *)firstDirectory)->newStructFile.st_ctime
            > ((t_file *)secondDirectory)->newStructFile.st_ctime
            && cmd->print_reverse)
        return true;
    else
        return false;
}
bool mTimeFunc(void *firstDirectory, void *secondDirectory, t_cmd *cmd) {
    if (((t_file *)firstDirectory)->newStructFile.st_mtime
                < ((t_file *)secondDirectory)->newStructFile.st_mtime
                && !(cmd->print_reverse))
        return true;
    else if (((t_file *)firstDirectory)->newStructFile.st_mtime
            > ((t_file *)secondDirectory)->newStructFile.st_mtime
            && cmd->print_reverse)
        return true;
    else
        return false;
}
bool Name(void *firstDirectory, void *secondDirectory, t_cmd *cmd) {

    char *file1 = ((t_file *)firstDirectory)->filename;
    char *file2 = ((t_file *)secondDirectory)->filename;

    while (*file1 == *file2 && *file1 != '\0' && *file2 != '\0') {
        file1++;
        file2++;
    }
    if ((*file1 - *file2) > 0
            && !(cmd->print_reverse))
        return true;
    else if ((*file1 - *file2) < 0
            && cmd->print_reverse)
        return true;
    else
        return false;
}
bool Size(void *firstDirectory, void *secondDirectory, t_cmd *cmd) {
    if (((t_file *)firstDirectory)->newStructFile.st_size
                < ((t_file *)secondDirectory)->newStructFile.st_size
                && !(cmd->print_reverse))
        return true;
    else if (((t_file *)firstDirectory)->newStructFile.st_size
            > ((t_file *)secondDirectory)->newStructFile.st_size
            && cmd->print_reverse)
        return true;
    else
        return false;
}
