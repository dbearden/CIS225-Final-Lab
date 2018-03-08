/* drawInstructions.c
 *
 * Authors: Justin Crawford, Daniel Bearden
 *
 * Date: 3/4/2018
 *
 */

#include "poker.h"

void drawInstructions(WINDOW *instructions, int drawOrDeal){
    instructions = newwin(8,15, 13, 66);
    wbkgd(instructions, COLOR_PAIR(3));
    mvwprintw(instructions, 1, 1, "Instructions");
    mvwprintw(instructions, 2, 1, "move:     a,d");
    mvwprintw(instructions, 3, 1, "select: SPACE");
    if(drawOrDeal){
    mvwprintw(instructions, 4, 1, "deal:   ENTER");
    
    }
    else {
        mvwprintw(instructions, 4, 1, "draw:   ENTER");
    }
    mvwprintw(instructions, 5,1, "Shuffle:    s");
    mvwprintw(instructions, 6, 1, "quit:       q");
    wrefresh(instructions); 


}


