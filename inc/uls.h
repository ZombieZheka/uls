#ifndef ULS_H
#define ULS_H

#include "libmx/inc/libmx.h"

#include <string.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>
#include <dirent.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/ioctl.h>
#include <sys/xattr.h>
#include <sys/acl.h>

#define FLAGS "ACGRSTacfghlmnortu1"

typedef struct s_uls {
	void *data;
    int len;
	struct s_uls *next;
} t_uls;

typedef struct s_lenthMax {
    int lnkStruct;
    int OwnStruct;
    int GrpStruct;
    int SizeStruct;
} t_lenthMax;

typedef struct s_file {
	char *path;
	char *filename;
	struct stat newStructFile;
	char *owner;
	char *group;
	char *perm;
} t_file;

enum typeTime{
    mTime,
    cTime,
    aTime
};

enum typePrint{
    longFormat,
    stdFormat,
    colFormat,
    mFormat
};

enum typeForSort{
    noneType,
    nameType,
    sizeType,
    timeType,
};

typedef struct s_cmd {
	int print_func;
	int sort_type;
	int time_type;
	bool error_null_args;
	bool print_recursion;
	bool print_reverse;
	bool print_dots_folder;
	bool print_hidden;
	bool print_f;
	bool print_owner;
	bool print_group;
	bool print_owner_group_num;
	bool format_h;
	bool format_t;
	bool format_g;
} t_cmd;



int mx_check(int argc, char **argv);

t_lenthMax *mx_LenForPrint(t_list *fileList);
void mx_PrintListFor(t_list *fileList, t_cmd *cmd);
void mx_PrintLong(t_list *fileList, t_cmd *cmd);
void mx_PSF(t_list *fileList, t_cmd *cmd);
void mx_FormatForPrint(t_list *fileList, t_cmd *cmd);

t_cmd *mx_CreateCmd(int argc, char **argv);
void mx_PS(t_file *file, t_lenthMax *ml, t_cmd *cmd);
char *mx_Size(off_t num);
void mx_printT(t_file *file, t_cmd *cmd);
void mx_ColorPrint(t_file *file);
void mx_flags(char flag, t_cmd *cmd);

int mx_islink(char *filename, t_list *input);
void mx_ClearList(t_list **fileList, t_cmd *cmd);
t_list *mx_getListOfDirectories(char *directoryOut, t_cmd *cmd);
t_file *mx_fileAttraction(char *filename, char *directory, t_cmd *cmd);

#endif
