#include "../Headers/noteEditor.h"

char** inputKeyReader(int* y, int* x, char** textBuffer, int* strCount, int strSize, int inputChar, WINDOW* wnd, enum mode* curmode)
{
  switch (inputChar)
  {
    case KEY_DOWN:
    {
      keyDownTreat(y, x, *strCount);
      break;
    }
    case KEY_UP:
    {
      keyUpTreat(y, x, *strCount);
      break;
    }
    case KEY_RIGHT:
    {
      keyRightTreat(x, y, *strCount, textBuffer);
      break;
    }
    case KEY_LEFT:
    {
      keyLeftTreat(x, *strCount);
      break;
    }
    case KEY_HOME:
    {
      keyHomeTreat(x, y,textBuffer);
      break;
    }
    case KEY_END:
    {
      keyEndTreat(x, y,textBuffer);
      break;
    }
    case KEY_F(2):
    {
      *curmode=cmd;
      curs_set(FALSE);
      break;
    }
    case 10: //не знаю почему, но KEY_ENTER не работает, даже с кейпадом
    {
        textBuffer=enterTreat(y, x, textBuffer, strCount, strSize, wnd);
        break;
    }
    case KEY_DC:
    {
      textBuffer=deleteTreat(y, x, textBuffer, strCount, strSize, wnd);
      break;
    }
    case KEY_BACKSPACE: //KEY_BACKSPACE (8) не работает, но работает на ноутбуке
    {
      textBuffer=backspaceTreat(y, x, textBuffer, strCount, strSize, wnd);
      break;
    }
    default:
    {
      textBuffer=inputKeyTreat(y, x, textBuffer, strCount, strSize, wnd, inputChar);
      break;
    }
  }
  return textBuffer;
}
