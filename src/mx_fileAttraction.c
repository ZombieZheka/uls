#include "uls.h"

static void Path(t_file *file, char *directory);
static void getGroupCreator(t_file *file, struct stat newStruct, t_cmd *cmd);
void mx_getOutPrint(t_file *file);

t_file *mx_fileAttraction(char *filename, char *directory, t_cmd *cmd) {
    t_file *file = NULL;
    struct stat newStruct;

    if (!filename || !directory || !cmd)
        return file;
    file = malloc(sizeof(t_file));
    file->filename = mx_strdup(filename);
    Path(file, directory);
    lstat(file->path, &newStruct);
    file->newStructFile = newStruct;
    if (cmd->print_func == longFormat) {
        mx_getOutPrint(file);
        getGroupCreator(file, newStruct, cmd);
    }
    else if (cmd->format_g)
        mx_getOutPrint(file);
    return file;
}

static void Path(t_file *file, char *directory) {
    char *tmp = NULL;

    if (!file || !directory)
        return;
    if (file->filename[0] == '/' || directory[0] == 0)
        file->path = mx_strdup(file->filename);
    else {
        tmp = mx_strjoin(directory, "/");
        file->path = mx_strjoin(tmp, file->filename);
        free(tmp);
    }
}

static void getGroupCreator(t_file *file, struct stat newStruct, t_cmd *cmd) {
    struct passwd *pw;
    struct group *grp;

    pw = getpwuid(newStruct.st_uid);
    if (pw->pw_name != NULL && !(cmd->print_owner_group_num))
        file->owner = mx_strdup(pw->pw_name);
    else
        file->owner = mx_itoa(newStruct.st_uid);
    grp = getgrgid(newStruct.st_gid);
    if (grp != NULL && !(cmd->print_owner_group_num))
        file->group = mx_strdup(grp->gr_name);
    else
        file->group = mx_itoa(newStruct.st_gid);
}
void mx_getOutPrint(t_file *file) {
    char *resalt = mx_strnew(10);

    resalt[0] = S_ISBLK(file->newStructFile.st_mode) ? 'b' :
             S_ISCHR(file->newStructFile.st_mode) ? 'c' :
             S_ISDIR(file->newStructFile.st_mode) ? 'd' :
             S_ISSOCK(file->newStructFile.st_mode) ? 's' :
             S_ISFIFO(file->newStructFile.st_mode) ? 'p' :
             S_ISLNK(file->newStructFile.st_mode) ? 'l' : '-';

    resalt[1] = (S_IRUSR & file->newStructFile.st_mode) ? 'r' : '-';
    resalt[2] = (S_IWUSR & file->newStructFile.st_mode) ? 'w' : '-';
    resalt[3] = (file->newStructFile.st_mode & S_IXUSR) ?
             ((file->newStructFile.st_mode & S_ISUID) ? 's' : 'x') :
             ((file->newStructFile.st_mode & S_ISUID) ? 'S' : '-');
    resalt[4] = (S_IRGRP & file->newStructFile.st_mode) ? 'r' : '-';
    resalt[5] = (S_IWGRP & file->newStructFile.st_mode) ? 'w' : '-';
    resalt[6] = (file->newStructFile.st_mode & S_IXGRP) ?
             ((file->newStructFile.st_mode & S_ISGID) ? 's' : 'x') :
             ((file->newStructFile.st_mode & S_ISGID) ? 'S' : '-');
    resalt[7] = (S_IROTH & file->newStructFile.st_mode) ? 'r' : '-';
    resalt[8] = (S_IWOTH & file->newStructFile.st_mode) ? 'w' : '-';
    resalt[9] = (file->newStructFile.st_mode & S_IXOTH) ?
             ((file->newStructFile.st_mode & S_ISTXT) ? 't' : 'x') :
             ((file->newStructFile.st_mode & S_ISTXT) ? 'T' : '-');
    file->perm = mx_strdup(resalt);
    free(resalt);
}
