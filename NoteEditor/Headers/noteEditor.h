#ifndef NOTEEDIT_H_
#define NOTEEDIT_H_
#include <termios.h>
#include <sys/ioctl.h>
#include <signal.h>
#include <stdlib.h>
#include <curses.h>
#include <locale.h>
#include <string.h>
#include <malloc.h>

enum mode {check_args, open, cmd, save, input, close};

enum mode cmdKeyReader(enum mode *curmode); //считывание кнопки переключения режима
int       stringCounter(FILE* textFile, char* filename); //подсчёт строк в файле
char**    outputOpenedFile(int strCount, char** textBuffer, size_t strSize, WINDOW* wnd, FILE* textFile); //вывод открытого файла
void      optionbar(WINDOW* optionWnd, int y, int x, char* message, int strCount, enum mode curmode); //рисование верхнего бара состояний
void      drawWnd(WINDOW* wnd, int strCount, char** textBuffer); //рисование главного окна и буфера
char**    inputKeyTreat(int* y, int* x, char** textBuffer, int* strCount, size_t strSize, WINDOW* wnd, int inputChar); //обработчик клавиш ввода
char**    enterTreat(int* y, int* x, char** textBuffer, int* strCount, size_t strSize, WINDOW* wnd); //обработка клавиши enter
char**    deleteTreat(int* y, int* x, char** textBuffer, int* strCount, size_t strSize, WINDOW* wnd); //обработка клавиши delete
char**    backspaceTreat(int* y, int* x, char** textBuffer, int* strCount, size_t strSize, WINDOW* wnd); //обработка клавиши backspace
void      keyDownTreat(int* y, int* x, int strCount); //обработка стрелки вниз
void      keyUpTreat(int* y, int* x, int strCount); //обработка стрелки вверх
void      keyLeftTreat(int* x, int strCount); //обработка стрелки влево
void      keyRightTreat(int* x, int* y, int strCount, char** textBuffer); //обработка стрелки вправо
void      keyHomeTreat(int* x, int* y,char** textBuffer); //обработка клавиши home
void      keyEndTreat(int* x, int* y,char** textBuffer); //обработка клавиши end
char**    inputKeyReader(int* y, int* x, char** textBuffer, int* strCount, int strSize, int inputChar, WINDOW* wnd, enum mode* curmode); //обработчик input

#endif
