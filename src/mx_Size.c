#include "uls.h"

static void sizeLessThouthend(off_t st_size, char *size);
static void sizeMoreThouthend(off_t num, double g, int pow, char *size);
static int rnd(double inputNumber);
static void addPrefForOutput(char *size, int add);
void writeNumber(char *size, off_t st_size);
int powOwn(off_t st_size);
#define MAXSIZE 1000
#define mn 10
#define alhab 48
#define min 9.95

char *mx_Size(off_t num) {
    char *size = mx_strnew(4);
    double newNum;
    int pow = 0;

    if (num < MAXSIZE)
        sizeLessThouthend(num, size);
    else if (num >= MAXSIZE)
    {
        pow = powOwn(num);
        newNum = num / mx_pow(2, pow);
        sizeMoreThouthend(num, newNum, pow, size);
    }
    return size;
}

static void sizeMoreThouthend(off_t num, double number, int pow, char *size) {
    if (number >= min) {
        num = rnd(number);
        if (num < MAXSIZE - 1)
            writeNumber(size, num);
        else {
            num = rnd(number * mn);
            pow += mn;
            size[0] = num / mn + alhab;
            size[1] = '.';
            size[2] = num % mn + alhab;
        }
    }
    else {
        num = rnd(number * mn);
        size[0] = num / mn + alhab;
        size[1] = '.';
        size[2] = num % mn + alhab;
    }
    addPrefForOutput(size, pow);
}

static void sizeLessThouthend(off_t st_size, char *size){
    off_t num = st_size;
    if (num == 0)
      size = mx_strcpy(size, "  0B");
    else if (st_size < MAXSIZE) {
        writeNumber(size, num);
        size[3] = 'B';
    }
}

static int rnd(double inputNumber) {
    off_t res;

    if (((off_t)(inputNumber * mn) % mn) >= 5)
        res = (off_t)(inputNumber * mn) /mn + 1;
    else
        res = (off_t)(inputNumber * mn) /mn;
    return res;
}

static void addPrefForOutput(char *size, int add) {
    if(add == 10)
        size[3] = 'K';
    else if(add == 30)
        size[3] = 'G';
    else if(add == 20)
        size[3] = 'M';
    else if(add == 50)
        size[3] = 'P';
    else if(add == 40)
        size[3] = 'T';
}
void writeNumber(char *size, off_t st_size) {
    off_t num = st_size;

    for (int i = 3; i > 0; i--) {
        if (num > 0) {
            size [i - 1] = num % mn + alhab;
            num /= mn;
        }
        else
            size[i - 1] = ' ';
    }
}
int powOwn(off_t size) {
    off_t num = size;
    int pow = 0;
    while (num >= MAXSIZE) {
        num /= (MAXSIZE + 24);
        pow += mn;
    }
    return pow;
}
