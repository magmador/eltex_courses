#include "../Headers/noteEditor.h"

enum mode cmdKeyReader(enum mode *curmode)
{
  switch (getch()) {
    case KEY_F(1):
    {
      *curmode = save;
      break;
    }
    case KEY_F(2):
    {
      *curmode = input;
      break;
    }
    case KEY_F(3):
    {
      *curmode = close;
      break;
    }
    default: break;
  }
  return *curmode;
}
