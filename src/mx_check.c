#include "uls.h"

static int checkFlags(int argc, char **argv);
static void printError(char c, char ex);
static void checkArg(int argc, char **argv, int argument);
static void printErrorArg(char *error);

int mx_check(int argc, char **argv) {
    int position = checkFlags(argc, argv);

    if (argv[position] && mx_strcmp(argv[position], "--") == 0)
        position++;

    for (int j = position; j < argc; j++)
        if (argv[j][0] == '-')
            checkArg(1, &argv[j], 0);

    checkArg(argc, argv, position);
    return position;
}

static int checkFlags(int argc, char **argv) {
    char *ex = FLAGS;
    int len_ex = mx_strlen(ex);
    int i = 1;

    for (; i < argc; i++)
        if (argv[1][0] == '-' && argv[i][0] == '-') {
            if (mx_strcmp(argv[i], "--") == 0)
                break;
            for (int j = 1; j < mx_strlen(argv[i]); j++)
                for (int k = 0; k < len_ex && argv[i][j] != ex[k]; k++)
                    if (k == len_ex - 1) {
                        printError(argv[i][j], argv[i][j]);
                        exit(1);
                    }
        }
        else
            break;
    return i;
}

static void printError(char c, char ex) {
    mx_printerr("uls: illegal option -- ");
    write(2, &c, 1);
    mx_printerr("\nusage: uls [-");
    mx_printchar(ex);
    mx_printerr("] [file ...]\n");
}

static void checkArg(int argc, char **argv, int argument) {
    struct stat buff;

    for (int i = argument; i < argc; i++) {
        if (argv[i] && (lstat(argv[i], &buff) != 0)) {
            printErrorArg(argv[i]);
            argv[i] = NULL;
        }
    }
}

static void printErrorArg(char *error) {
    mx_printerr("uls: ");
    mx_printerr(error);
    mx_printerr(": ");
    mx_printerr(strerror(errno));
    mx_printerr("\n");
}
