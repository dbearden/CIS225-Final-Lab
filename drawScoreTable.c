
#include "poker.h"


void drawScoreTable(WINDOW *scoreTable){
   
    scoreTable = newwin(10, 30, 1, 34);
    wbkgd(scoreTable, COLOR_PAIR(3));
    mvwprintw(scoreTable, 0, 1, "Winning Hands");
    mvwprintw(scoreTable, 9, 1, "Jacks or Better:  50");
    mvwprintw(scoreTable, 8, 1, "Two Pair:        100");
    mvwprintw(scoreTable, 7, 1, "Three of a Kind: 150");
    mvwprintw(scoreTable, 6, 1, "Straight:        200");
    mvwprintw(scoreTable, 5, 1, "Flush:           250");
    mvwprintw(scoreTable, 4, 1, "Full House:      400");
    mvwprintw(scoreTable, 3, 1, "Four of a Kind:  500");
    mvwprintw(scoreTable, 2, 1, "Straight Flush: 1000");
    mvwprintw(scoreTable, 1, 1, "Royal Flush:    2000");
    wrefresh(scoreTable);

}
