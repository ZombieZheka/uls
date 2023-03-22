#include "uls.h"

void mx_flags(char flag, t_cmd *cmd) {
    if(flag == 'l')
        cmd->print_func = longFormat;
    else if(flag == 'C') {
        if (cmd->print_func != mFormat)
            cmd->print_func = stdFormat;
    }
    else if(flag == '1')
        cmd->print_func = colFormat;
    else if(flag == 'm')
        cmd->print_func = mFormat;
    else if(flag == 'R')
        cmd->print_recursion = true;
    else if(flag == 'r')
        cmd->print_reverse = true;
    else if(flag == 't') {
        if (cmd->sort_type != sizeType)
            cmd->sort_type = timeType;
    }
    else if(flag == 'a')
        cmd->print_hidden = true;
    else if(flag == 'A')
        cmd->print_dots_folder = true;
    else if(flag == 'f')
        cmd->print_f = true;
    else if(flag == 'h')
        cmd->format_h = true;
    else if(flag == 'T')
        cmd->format_t = true;
    else if(flag == 'g')
        cmd->print_owner = false;
    else if(flag == 'o')
        cmd->print_group = false;
    else if(flag == 'n')
        cmd->print_owner_group_num = true;
    else if(flag == 'G')
        cmd->format_g = true;

    else if(flag == 'S')
        cmd->sort_type = sizeType;
    else if(flag == 'c')
        cmd->time_type = cTime;
    else if(flag == 'u')
        cmd->time_type = aTime;



}
