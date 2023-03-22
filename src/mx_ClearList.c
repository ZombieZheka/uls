#include "uls.h"

void mx_ClearList(t_list **fileList, t_cmd *cmd) {
    t_list *newfileList = *fileList;
    t_list *tmp = NULL;

    if (!(*fileList) || !fileList)
        return;
    while (newfileList) {
        t_file *file = newfileList->data;
        if (!file)
            return;
        mx_strdel(&file->path);
        mx_strdel(&file->filename);
        if (cmd->format_g)
            mx_strdel(&file->perm);
        else if (cmd->print_func == longFormat) {
            mx_strdel(&file->perm);
            mx_strdel(&file->owner);
            mx_strdel(&file->group);
        }
        free(file);
        file = NULL;

        tmp = newfileList->next;
        free(newfileList);
        newfileList = tmp;
    }
    *fileList = NULL;
}
