#include "uls.h"


void mx_FormatForPrint(t_list *fileList, t_cmd *cmd) {
    struct winsize win;
    t_file *tmp;
    int len = 0;
    int i = 0;

    if (!fileList)
        return;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &win);
    for (t_list *j = fileList; j; j = j->next, i++) {
        tmp = j->data;
        if (i != 0) {
            mx_printchar(',');

            char separator;

            if (len + 2 + mx_strlen(tmp->filename) < win.ws_col - 1) {
                (len) += 2;
                separator = ' ';
            }
            else {
                (len) = 0;
                separator = '\n';
            }

            mx_printchar(separator);
        }

        if (cmd->format_g)
            mx_ColorPrint(tmp);
        else
            mx_printstr(tmp->filename);

        len += mx_strlen(tmp->filename);
    }
    mx_printstr("\n");
}

