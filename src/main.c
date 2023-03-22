#include "uls.h"

static void printFiles(t_list *fileName, t_list *dataNames, t_cmd *cmd);
static void printDir(t_list *dataNames, t_cmd *cmd);
static void printDirOwn(char *directory, t_cmd *cmd);
static t_list *ArgF(int argc, char **argv, int data, t_cmd *cmd);
static t_list *ArgD(int argc, char **argv, int data, t_cmd *cmd);
static bool isDirectory(char *filename, t_list *intput);
static bool BoolF(void *firstDirectory, void *secondDirectory);

int main(int argc, char **argv) {
    int position = mx_check(argc, argv);
    t_cmd *cmd = mx_CreateCmd(argc, argv);
    t_list *fileName = ArgF(argc, argv, position, cmd);
    t_list *dataNames = ArgD(argc, argv, position, cmd);

    printFiles(fileName, dataNames, cmd);
    if (!fileName && !dataNames && !cmd->error_null_args)
        mx_push_back(&dataNames, ".");
    printDir(dataNames, cmd);
    return 0;
}

static void printFiles(t_list *fileNames, t_list *dataNames, t_cmd *cmd) {
    t_list *fileList = NULL;
    if (fileNames) {
        for (t_list *i = fileNames; i; i = i->next)
            mx_push_back(&fileList, mx_fileAttraction(i->data, ".", cmd));
        mx_PrintListFor(fileList, cmd);
        mx_ClearList(&fileList, cmd);
        if (dataNames) {
            mx_printstr("\n");
            if (mx_list_size(dataNames) == 1 && !cmd->error_null_args) {
                mx_printstr(dataNames->data);
                mx_printstr(":\n");
            }
        }
    }
}

static void printDir(t_list *dataNames, t_cmd *cmd) {
    if (dataNames) {
        if (mx_list_size(dataNames) == 1 && cmd->error_null_args) {
            mx_printstr(dataNames->data);
            mx_printstr(":\n");
        }
        for (t_list *i = dataNames; i; i = i->next) {
            if (mx_list_size(dataNames) != 1) {
                mx_printstr(i->data);
                mx_printstr(":\n");
            }
            printDirOwn(i->data, cmd);
            if (i->next != NULL)
                mx_printstr("\n");
        }
    }
}

static void printDirOwn(char *directory, t_cmd *cmd) {
    t_list *fileList = mx_getListOfDirectories(directory, cmd);
    t_file *tmp;

    if (fileList == NULL)
        return;
    if (cmd->print_func == longFormat){
        blkcnt_t res = 0;
        t_file *cur;

        for (t_list *i = fileList; i != NULL; i = i->next) {
            cur = i->data;
            res += cur->newStructFile.st_blocks;
        }
        mx_printstr("total ");
        mx_printint((int)res);
        mx_printstr("\n");
    }
    mx_PrintListFor(fileList, cmd);
    if (cmd->print_recursion)
        for (t_list *i = fileList; i; i = i->next) {
            tmp = i->data;
            if (isDirectory(NULL, i) && mx_strcmp(tmp->filename, ".")
                && mx_strcmp(tmp->filename, "..")) {
                mx_printstr("\n");
                mx_printstr(tmp->path);
                mx_printstr(":\n");
                printDirOwn(tmp->path, cmd);
            }
        }
    mx_ClearList(&fileList, cmd);
}
t_list *ArgF(int argc, char **argv, int data, t_cmd *cmd) {
    t_list *fileArg = NULL;

    for (;data < argc; data++)
        if (argv[data] && !isDirectory(argv[data], NULL)
            && mx_islink(argv[data], NULL) != 5)
            mx_push_back(&fileArg, argv[data]);
        else if (argv[data]
                 && (mx_islink(argv[data], NULL) == 5)
                 && cmd->print_func == longFormat)
            mx_push_back(&fileArg, argv[data]);
    if (!cmd->print_f)
        mx_sort_list(fileArg, BoolF);
    return fileArg;
}
t_list *ArgD(int argc, char **argv, int data, t_cmd *cmd) {
    t_list *DataArg = NULL;

    for (; data < argc; data++)
        if (argv[data] && isDirectory(argv[data], NULL))
            mx_push_back(&DataArg, argv[data]);
        else if (argv[data] && (mx_islink(argv[data], NULL) == 5)
                 && cmd->print_func != longFormat)
            mx_push_back(&DataArg, argv[data]);
    if(!cmd->print_f)
        mx_sort_list(DataArg, BoolF);
    return DataArg;
}
bool isDirectory(char *filename, t_list *input) {
    struct stat fileStruct;

    if (!filename && input){
        lstat(((t_file *)input->data)->path, &fileStruct);
        if(S_ISDIR(fileStruct.st_mode))
            return true;
        else
            return false;
    }
    else if (filename && !input) {
        lstat(filename, &fileStruct);
        if(S_ISDIR(fileStruct.st_mode))
            return true;
        else
            return false;
    }
    else
        return false;
}
bool BoolF(void *firstDirectory, void *secondDirectory) {
    char *newFirstDir = firstDirectory;
    char *newSecondDir = secondDirectory;

    while (*newFirstDir == *newSecondDir
            && *newFirstDir != '\0'
            && *newSecondDir != '\0') {
        newFirstDir++;
        newSecondDir++;
    }
    if ((*newFirstDir - *newSecondDir) > 0)
        return true;
    else
        return false;
}
