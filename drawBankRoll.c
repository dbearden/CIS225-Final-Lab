/* drawBankRoll.c
 *
 * Authors: Justin Crawford, Daniel Bearden
 *
 * Date: 3/3/2018
 *
 *
 */

#include "poker.h"

void drawBankRoll(WINDOW *bankWindow, int bankroll){
    bankWindow = newwin(3,15, 8, 15);
    wbkgd(bankWindow, COLOR_PAIR(3));
    mvwprintw(bankWindow, 0, 1, "%s", "Your Bankroll");
    mvwprintw(bankWindow, 2, 1, "%d", bankroll);
    wrefresh(bankWindow);
}
