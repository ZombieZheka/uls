#include "uls.h"
#define stand 8

void arrayPrint(int name, int lenth);
void mx_PSF(t_list *fileList, t_cmd *cmd) {
    int max = 0;
    int cur = 0;
    struct winsize win;
    t_file **result = NULL;

    for (t_list *i = fileList; i != NULL; i = i->next) {
        cur = mx_strlen(((t_file *)i->data)->filename);
        if (cur > max)
            max = cur;
    }

    int numberOfNames = mx_list_size(fileList);
    int i = 0;
    result = (t_file **)malloc((numberOfNames + 1) * sizeof(t_file *));
    for (t_list *j = fileList; j != NULL; j = j->next, i++)
        result[i] = j->data;
    result[numberOfNames] = NULL;

    ioctl(STDOUT_FILENO, TIOCGWINSZ, &win);
    if (cmd->format_g) {
        int rows;
        int size;
        int cols = win.ws_col / (max + 1);

        for (size = 0; result[size]; size++)
            if (!result || !cols || !max)
                exit(0);
        rows = size / cols;
        if (size % cols)
            rows += 1;
        for (int i = 0; i < rows; i++) {
            for (int j = 0; i + j < size; j += rows) {
                mx_ColorPrint(result[i + j]);
                if (result[i + j + 1] && (i + j + rows < size))
                    mx_printspaces(max + 1
                                   - mx_strlen(result[i + j]->filename));
            }
            mx_printchar('\n');
        }
    }
    else{

        int rows;
        int size;
        int cols = (win.ws_col / ((stand - (max % stand)) + max));

        for (size = 0; result[size]; size++)
            if (!result || !cols || !max)
                exit(0);
        rows = size / cols;
        if (size % cols)
            rows += 1;
        for (int i = 0; i < rows; i++) {
            for (int j = 0; i + j < size; j += rows) {
                mx_printstr(result[i + j]->filename);
                if (result[i + j + 1] && (i + j + rows < size))
                    arrayPrint(mx_strlen(result[i + j]->filename), max);
            }
            mx_printchar('\n');
        }
    }
    free(result);
}
void arrayPrint(int name, int lenth) {
    int count;
    int p;
    for (p = 1; ; p++) {
        if (lenth < (p * stand - 1))
            break;
    }
    count = p * stand - name;
    for (int i = 0; i < count; i += stand)
        mx_printchar('\t');
}
