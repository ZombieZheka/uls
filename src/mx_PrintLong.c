#include "uls.h"
#define a 2
#define MAXCHAR 255

static void printOutLine(t_file *file, t_lenthMax *printFile, t_cmd *cmd);
static void printLink(t_file *file, t_lenthMax *maxLenth);

void mx_PrintLong(t_list *fileList, t_cmd *cmd) {
    t_lenthMax *printFile;

    printFile = mx_LenForPrint(fileList);
    for (t_list *i = fileList; i; i = i->next)
        printOutLine(i->data, printFile, cmd);
    free(printFile);
    printFile = NULL;
}

static void printOutLine(t_file *file, t_lenthMax *printFile, t_cmd *cmd) {
    char newChar;
    acl_t newFile;
    ssize_t prefiks;

    prefiks = listxattr(file->path, NULL, 0, XATTR_NOFOLLOW);
    mx_printstr(file->perm);
    newFile = acl_get_file(file->path, ACL_TYPE_EXTENDED);
    if (prefiks > 0)
        newChar = '@';
    else if (newFile == NULL)
        newChar = ' ';
    else
        newChar = '+';
    acl_free(newFile);
    mx_printchar(newChar);

    printLink(file, printFile);
    mx_printspaces(1);
    if (cmd->print_owner) {
        mx_printstr(file->owner);
        mx_printspaces(printFile->OwnStruct - mx_strlen(file->owner) + a);
    }
    if (cmd->print_group) {
        mx_printstr(file->group);
        mx_printspaces(printFile->GrpStruct - mx_strlen(file->group));
    }
    mx_printspaces(a);
    mx_PS(file, printFile, cmd);
    mx_printspaces(1);
    mx_printT(file, cmd);
    mx_printspaces(1);
    if (cmd->format_g)
        mx_ColorPrint(file);
    else
        mx_printstr(file->filename);
    if (S_ISLNK(file->newStructFile.st_mode)) {
        char link[MAXCHAR];
        int size = 0;

        if (!file)
            return;
        size = readlink(file->path, link, sizeof(link) - 1);
        link[size] = '\0';
        mx_printstr(" -> ");
        mx_printstr(link);
    }
    mx_printstr("\n");
}

void printLink(t_file *file, t_lenthMax *maxLenth){
    char *tmp;

    tmp = mx_itoa(file->newStructFile.st_nlink);
    mx_printspaces(1 + maxLenth->lnkStruct - mx_strlen(tmp));
    free(tmp);
    mx_printint(file->newStructFile.st_nlink);
}
