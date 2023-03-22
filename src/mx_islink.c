#include "uls.h"

static bool isDirectory(char *filename, t_list *input);
#define MAXCHAR 255

int mx_islink(char *filename, t_list *input) {
    struct stat fileStruct;
    int size = 0;
    char link[MAXCHAR];

    if (filename && !input)
        lstat(filename, &fileStruct);
    else if (!filename && input)
        lstat(((t_file *)input->data)->path, &fileStruct);

    if (S_ISLNK(fileStruct.st_mode)) {
        size = readlink(filename, link, sizeof(link) - 1);
        link[size] = '\0';
        if (isDirectory(link, NULL))
            return 5;
        else
            return 1;
    }
    else
        return 0;
}
bool isDirectory(char *filename, t_list *input) {
    struct stat fs;

    if (filename && !input) {
        lstat(filename, &fs);
        return (S_ISDIR(fs.st_mode) ? true : false);
    }
    else if (!filename && input){
        lstat(((t_file *)input->data)->path, &fs);
        return (S_ISDIR(fs.st_mode) ? true : false);
    }
    else
        return false;
}
