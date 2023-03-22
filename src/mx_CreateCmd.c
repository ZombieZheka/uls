#include "uls.h"


t_cmd *mx_CreateCmd(int argc, char **argv) {
    t_cmd *cmd = (t_cmd *)malloc(sizeof(t_cmd));
    int i = 1;

    if (isatty(STDOUT_FILENO))
        cmd->print_func = stdFormat;
    else
        cmd->print_func = colFormat;
    cmd->sort_type = nameType;
    cmd->time_type = mTime;
    cmd->error_null_args = false;
    cmd->print_recursion = false;
    cmd->print_reverse = false;
    cmd->print_dots_folder = false;
    cmd->print_hidden = false;
    cmd->print_f = false;
    cmd->print_owner = true;
    cmd->print_group = true;
    cmd->print_owner_group_num = false;

    cmd->format_h = false;
    cmd->format_t = false;
    cmd->format_g = false;

    for (; i < argc; i++)
        if (argv[i] && argv[i][0] == '-') {
            if (mx_strcmp(argv[i], "--") == 0)
                break;
            for (int j = 1; j < mx_strlen(argv[i]); j++)
                mx_flags(argv[i][j], cmd);
        }
        else
            break;
    for (; i < argc; i++)
        if (!argv[i]) {
            cmd->error_null_args = true;
            break;
        }
    if (!isatty(STDOUT_FILENO))
        cmd->format_g = false;
    if (cmd->print_f == true) {
        cmd->print_dots_folder = true;
        cmd->print_hidden = true;
        cmd->sort_type = noneType;
    }
    return cmd;
}

