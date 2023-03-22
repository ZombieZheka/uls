#include "uls.h"

t_list *mx_getListOfDirectories(char *directoryOut, t_cmd *cmd) {
    t_list *fileList = NULL;
    DIR *directory = opendir(directoryOut);
    struct dirent *entry;

    if (!directoryOut)
        return NULL;
    if (!(directory)) {
        int i = mx_strlen(directoryOut) - 1;

        if (directoryOut[i] == '/')
            perror("uls: ");
        else {
            while (directoryOut[i] != '/')
                i--;
            mx_printerr("uls: ");
            perror(&directoryOut[i + 1]);
        }
        return NULL;
    }

    while ((entry = readdir(directory))) {
        if(cmd->print_hidden == true || cmd->print_f == true)
            mx_push_back(&fileList, mx_fileAttraction(entry->d_name, directoryOut, cmd));
        else if (cmd->print_dots_folder == true){
            if (mx_strcmp(entry->d_name, ".")
                && mx_strcmp(entry->d_name, "..") != 0)
                mx_push_back(&fileList, mx_fileAttraction(entry->d_name, directoryOut, cmd));
        }
        else if (entry->d_name[0] != '.')
            mx_push_back(&fileList, mx_fileAttraction(entry->d_name, directoryOut, cmd));
    }
    closedir(directory);
    return fileList;
}
