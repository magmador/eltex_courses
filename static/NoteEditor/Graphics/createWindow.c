#include "../Headers/noteEditor.h"

WINDOW *create_window(int y, int x, int width, int height, int color_id)
{
    WINDOW* win;
    int i;
    win = newwin(height, width, y, x);
    wbkgd(win, A_NORMAL | COLOR_PAIR(color_id) | ' ');
    /* start of shadow */
    attron(COLOR_PAIR(3));
    for(i = (x + 2); i < (x + width + 1); i++){
     move((y + height), i);
     addch(' ');
    }
    for(i = (y + 1); i < (y + height + 1); i++){
     move(i, (x + width));
     addch(' ');
     move(i, (x + width + 1));
     addch(' ');
    }
    attroff(COLOR_PAIR(3));
    /* end of shadow */
    refresh();
    return win;
}
