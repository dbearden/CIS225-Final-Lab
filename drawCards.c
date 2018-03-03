/* drawCards.c
 *
 * Authors: Justin Crawford, Daniel Bearden
 *
 * Date: 3/3/2018
 *
 * Requires compile with "lncursesw -g"
 *
 */


#include <locale.h>
#include <curses.h>
#include "poker.h"

/* Unicode values for card suit characters */
#define SPADE_CHAR "\xE2\x99\xA0"
#define CLUB_CHAR "\xE2\x99\xA3"
#define HEART_CHAR "\xE2\x99\xA5"
#define DIAMOND_CHAR "\xE2\x99\xA6"

/* card window size */
#define CARD_HEIGHT 10
#define CARD_WIDTH 10

/* Card screen locations */
#define CARD_ROW 10
#define CARD1_COL 10
#define CARD2_COL 21
#define CARD3_COL 32
#define CARD4_COL 43
#define CARD5_COL 54

/* Draws individual card */
void _drawCard(WINDOW *, CARD );


/* Creates the windows for the cards and draws with
 * a call to _drawCard 
 * param card1 - Card Window
 * param card2 - Card Window
 * param card3 - Card Window
 * param card4 - Card Window
 * param card5 - Card Window
 * param hand - Array of CARDs
 * return void
 */
void drawCards(WINDOW *card1, WINDOW *card2, WINDOW *card3, WINDOW *card4,
               WINDOW *card5, CARD *hand){
    // Create the windows for the cards
    card1 = newwin(CARD_HEIGHT, CARD_WIDTH, CARD_ROW, CARD1_COL);
    card2 = newwin(CARD_HEIGHT, CARD_WIDTH, CARD_ROW, CARD2_COL);
    card3 = newwin(CARD_HEIGHT, CARD_WIDTH, CARD_ROW, CARD3_COL);
    card4 = newwin(CARD_HEIGHT, CARD_WIDTH, CARD_ROW, CARD4_COL);
    card5 = newwin(CARD_HEIGHT, CARD_WIDTH, CARD_ROW, CARD5_COL);
    // Draw the cards in the windows
    _drawCard(card1, hand[0]);  
    _drawCard(card2, hand[1]);
    _drawCard(card3, hand[2]);
    _drawCard(card4, hand[3]);
    _drawCard(card5, hand[4]);
   
}

/* Draws the card details in the card window
 * param cardWindow - The window to be drawn on
 * param card - the CARD that will be drawn
 * return void
 */
void _drawCard(WINDOW *cardWindow, CARD card ){
    if(card.suit > 2){
    wbkgd(cardWindow, COLOR_PAIR(2));
    }
    else {
        wbkgd(cardWindow, COLOR_PAIR(1));  
    }
    // Character array to store unicode string for card suits
    char *suit;

    // Draw the upper left corner of the card.
    mvwprintw(cardWindow, 0, 0, UP_LEFT_CORNER);

    // Draw the left edge of the card.
    for(int i = 1; i <= 9; i++){
        mvwprintw(cardWindow, i, 0, LINE);
    }

    // Draw the lower left corner of the card.
    mvwprintw(cardWindow, 9, 0, LOWER_LEFT_CORNER);

    // Draw the bottom edge of the card.
    for(int i = 1; i <= 8; i++){
     mvwprintw(cardWindow, 9, i, HORIZONTAL_LINE);
    }
    // Draw the lower right corner of the card.
    mvwprintw(cardWindow, 9, 9, LOWER_RIGHT_CORNER);

    // Draw the right edge of the card.
    for(int i = 8; i >= 1; i--){
    mvwprintw(cardWindow, i, 9, LINE);
    }

    // Draw the upper right corner of the card.
    mvwprintw(cardWindow, 0, 9, UP_RIGHT_CORNER);
    
    // Draw the top edge of the card.
    for(int i = 8; i >= 1; i--){
        mvwprintw(cardWindow, 0, i, HORIZONTAL_LINE);
    }
    
    // Set suit to value of card.suit
    if(card.suit == SPADE){
        suit = SPADE_CHAR;
    }
    else if(card.suit == CLUB){
        suit = CLUB_CHAR;
    } 
    else if(card.suit == HEART){
        suit = HEART_CHAR;
    } 
    else {
        suit = DIAMOND_CHAR;
    }
        
    attron(COLOR_PAIR(2));   
    // Draw the suit in the upper left corner of the card.
    mvwprintw(cardWindow, 1, 1, suit);
   
    // Draw the card face in the middle of the card
    mvwprintw(cardWindow, 5, 4, "%c", card.face);
   
    // Draw the suit in bottom right corner of the card
    mvwprintw(cardWindow, 8, 8, suit);
    
    wrefresh(cardWindow);
}
