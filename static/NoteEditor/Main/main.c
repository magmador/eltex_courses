#include "../Headers/noteEditor.h"

int main(int argc, char ** argv)
{
    setlocale(LC_ALL, "");
    WINDOW * wnd;
    WINDOW * optionWnd;
    char* optionbarMessage = " F1 - сохранить файл | F2 - режим ввода | F3 - выйти из программы | количество строк в файле: %d | режим работы: %s"; //сделано ввиде переменной, чтобы иметь возможно задать другое сообщение в опциональном баре
    int key,y=3,x=5;
    enum mode curmode;
    char** textBuffer = (char**)malloc(1*sizeof(char*)); //буфер пока в одну строку
    size_t strSize = 300;
    char *filename = (char*)malloc(strSize*sizeof(char));
    int strCount = 0;
    FILE *textFile;

    initscr();
    cbreak();
    curs_set(FALSE);
    keypad(stdscr, TRUE);
    noecho();
    start_color();
    refresh();

    curmode = check_args;
    wnd = newwin(LINES, COLS, 0,0);
    init_pair(1, COLOR_BLACK, COLOR_WHITE);
    keypad(wnd,TRUE);
    optionWnd = derwin(wnd,3, COLS,0, 0);
    keypad(optionWnd, TRUE);
    wbkgd(optionWnd, COLOR_PAIR(1));
    wbkgd(wnd, COLOR_PAIR(1));
    wattron(optionWnd, A_BOLD);
    box(optionWnd,0,0);
    optionbar(optionWnd, 1, 1, optionbarMessage, strCount, curmode);
    wrefresh(wnd);
    do
    {
      switch (curmode) {
        case check_args:
        {
            if(argc>1)
            {
              filename = argv[1];
              curmode = open;
              break;
            }
            else
            {
              curmode=open;
              break;
            }
        }
        case open:
        {
          if((textFile=fopen(filename, "r"))==NULL)
          {
            //окно с сообщением о том, что файл не смог открыться. пока не работает
            curmode=check_args;
            break;
          }
          else
          {
            strCount = stringCounter(textFile, filename);
            optionbar(optionWnd, 1, 1, optionbarMessage, strCount, curmode);
            if(strCount>0)
            {
              textBuffer = outputOpenedFile(strCount, textBuffer, strSize, wnd, textFile); //сейчас количество индексов textBuffer == strCount
            }
            curmode=cmd;
            optionbar(optionWnd, 1, 1, optionbarMessage, strCount, curmode);
            break;
          }
        }
        case cmd:
        {
          y=3, x=5;
          curmode = cmdKeyReader(&curmode);
          break;
        }
        //textBuffer=enterTreat(&y, &x, textBuffer, &strCount, strSize,wnd);
        case input:
        {
          if(y==3 && x==5)
          {
            optionbar(optionWnd, 1, 1, optionbarMessage, strCount, curmode);
            curs_set(TRUE);
          }
          wmove(wnd,y,x);
          int inputChar = wgetch(wnd); //switch надо засунуть в функцию
          textBuffer = inputKeyReader(&y, &x, textBuffer, &strCount, strSize, inputChar, wnd, &curmode);
          optionbar(optionWnd, 1, 1, optionbarMessage, strCount, curmode);
          wrefresh(optionWnd);
          break;
        }
        case save:
        {
          optionbar(optionWnd, 1, 1, optionbarMessage, strCount, curmode);
          //здесь должен быть запрос на сохранение
          FILE* testfile = NULL;
          if((testfile=fopen(argv[2], "w"))==NULL)
          {
            mvwprintw(wnd, 1, 1, "Ошибка при записи в файл!\n");
            exit(1);
          }
          for(int i = 0; i<strCount; i++)
          {
            fprintf(testfile, "%s", textBuffer[i]);
          }
          curmode=cmd;
          optionbar(optionWnd, 1, 1, optionbarMessage, strCount, curmode);
          fclose(testfile);
          break;
        }
      }
    }while(curmode!=close);
    textBuffer=NULL;
    free(textBuffer);
    fclose(textFile);
    delwin(optionWnd);
    delwin(wnd);
    endwin();
    exit(EXIT_SUCCESS);
  }
