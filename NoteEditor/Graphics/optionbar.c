#include "../Headers/noteEditor.h"

void optionbar(WINDOW* optionWnd, int y, int x, char* message, int strCount, enum mode curmode)
{
  werase(optionWnd);
  switch (curmode)
  {
    case check_args:{mvwprintw(optionWnd, 1, 1, message, strCount, "Проверка аргументов"); break;}
    case save:{mvwprintw(optionWnd, 1, 1, message, strCount,  "Сохранение файла"); break;}
    case open:{mvwprintw(optionWnd, 1, 1, message, strCount,  "Открытие файла"); break;}
    case input:{mvwprintw(optionWnd, 1, 1, message, strCount,  "Редактирование текста"); break;}
    case close:{mvwprintw(optionWnd, 1, 1, message, strCount,  "Закрытие программы"); break;}
    case cmd:{mvwprintw(optionWnd, 1, 1, message, strCount,  "Командный режим"); break;}
    default: break;
  }
  box(optionWnd,0,0);
  wrefresh(optionWnd);
}
