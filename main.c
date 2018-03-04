#include <locale.h>
#include <curses.h>
#include "poker.h"

/* Cursor positions */
#define CURS_POS_1 15
#define CURS_POS_2 26
#define CURS_POS_3 37
#define CURS_POS_4 48
#define CURS_POS_5 59
#define CURS_ROW 22
#define CURS_NEXT 11
#define START_OF_LINE 1

/* Marker to swap cards */
#define MARK_CARD "x"

/* Starting bankroll */
#define START_BANK 1000

/* Flag for Deal or Draw round */
#define DRAW 0;
#define DEAL 1;

void moveCursRight(int*);

void moveCursLeft(int*);

void dealRound(CARD *, CARD *, int *, int *, int *);

void drawRound(CARD *, int *, int *);

void resetUI(WINDOW *, WINDOW *, WINDOW *, WINDOW *,
             WINDOW *, WINDOW *, WINDOW *, CARD *, int, int);

void replaceCards(CARD *, CARD*, int *, int);

int main(int argc, char *argv[]){

    // Need this for unicode. Not sure why
    setlocale(LC_ALL, "");
    // initialize the screen with curses
    initscr();
    // enable color
    start_color();
    raw();
    noecho();

    // Create color schemes    
    init_pair(1, COLOR_BLACK, COLOR_WHITE);
    init_pair(2, COLOR_RED, COLOR_WHITE);
    init_pair(3, COLOR_WHITE, COLOR_BLUE);
    init_pair(4, COLOR_WHITE, COLOR_RED);
    // refreshes the main window.       
    refresh();    

    // Create pointers for each window.
    WINDOW *card1;
    WINDOW *card2;
    WINDOW *card3;
    WINDOW *card4;
    WINDOW *card5;
    WINDOW *scoreTable;
    WINDOW *bankRollWindow;
    WINDOW *instructions;
    
    // create an array for 52 CARDs.
    CARD deck[52];
    // create an array for 5 CARDs.
    CARD hand[5];
    // counter to keep track of how many cards have been dealt.
    
    int cardsDealt;
    // Counter to keep track winnings.
    int bankRoll;
    // value for what the user chooses to do
    int choice;
    // column number that the cursor is in
    int cursPos;
    // Counter to determine if its time to deal or draw.
    int dealOrDraw = DRAW;
    // Start the play our with 1000 points
    bankRoll =  START_BANK;
    cardsDealt = 0;
    
    // Fill the deck with CARDs
    createDeck(deck);
    
    // Randomize the deck
    shuffleDeck(deck);
    
    // Draw the windows
    drawBankRoll(bankRollWindow, bankRoll);  
    drawScoreTable(scoreTable);
    drawInstructions(instructions, dealOrDraw);
    
    // Deal the initial hand.
    dealHand(deck, hand, &cardsDealt);
    // Draw the hand on the screen.
    drawCards(card1, card2, card3, card4, card5, hand);
    // Start the cursor under the first card.
    move(CURS_ROW, CURS_POS_1);
    // Set the cursor position. (For swapping cards)
    cursPos = CURS_POS_1;
  
    refresh();
    
    // Let the user interact until q is entered
    do {
        // Get the user's keystroke
        choice = getch();
        
        switch(choice) {
            /* Move the cursor under the cards */
            case 's':
                moveCursRight(&cursPos);
                break;
            case 'a':
                moveCursLeft(&cursPos);
                break;
            /* Deals a hand, or draws the cards to replace
             * and score the hand */
            case 'd':
                if((dealOrDraw)){
                    dealRound(deck, hand, &cardsDealt, &dealOrDraw,
                              & cursPos);
                    refresh();                     
                }
                else {
                    drawRound(hand, &dealOrDraw, &bankRoll);
                }
                resetUI(card1, card2, card3, card4, card5, instructions, 
                        bankRollWindow, hand, bankRoll, dealOrDraw);
                break;

            case 'x':
                // Not a deal round so cards can be swapped
                if(!dealOrDraw){
                    replaceCards(deck, hand, &cardsDealt, cursPos);
                }                                
        }
        
    } while(choice != 'q');
    endwin();
}

void moveCursRight(int *cursPos){

    /* Move to the right unless the cursor
     * is under the last card */
     if(*cursPos < CURS_POS_5){
         move(CURS_ROW, (*cursPos += CURS_NEXT));
     }
    /* The cursor is under the last card.
     * Set the cursor pos to be under the first
     * card and move there */
     else {
         *cursPos = CURS_POS_1;
         move(CURS_ROW, *cursPos);
     }
}

void moveCursLeft(int *cursPos){
    /* Move to the left unless the cursor
     * is under the first card */
     if(*cursPos > CURS_POS_1){
         move(CURS_ROW, (*cursPos -= CURS_NEXT));
     }
     /* The cursor is under the first card,
      * set the cursor position to the last card
      * and move there. */
     else {
         *cursPos = CURS_POS_5;
         move(CURS_ROW, *cursPos);
     }
}

void dealRound(CARD *deck, CARD *hand, int *cardsDealt,
               int *dealOrDraw, int *cursPos){

    // fill hand with the next 5 cards       
    dealHand(deck, hand, cardsDealt);
    // set dealOrDraw to draw round
    *dealOrDraw = DRAW;
    // move the cursor back to the first card        
    *cursPos = CURS_POS_1;
    move(CURS_ROW , *cursPos);
    // refresh the changes
    refresh();                    
}

void drawRound(CARD *hand, int *dealOrDraw, int *bankRoll){
    // Draw round, start cursor at card 1
    // Card replacements take place in other
    // functions.           
    move(CURS_ROW, CURS_POS_1);
    // Score the hand and update score
    *bankRoll += scoreHand(hand);
    // Set to deal round
    *dealOrDraw = DEAL;
    refresh();
}

void resetUI(WINDOW *card1, WINDOW *card2, WINDOW *card3, 
             WINDOW *card4, WINDOW *card5, WINDOW *instructions,
             WINDOW *bankRollWindow, CARD *hand, int bankRoll, 
             int dealOrDraw){
   // Move the cursor to the first column
   move(CURS_ROW, START_OF_LINE);
   // Erase any card selection indicators
   clrtoeol();
   // move the cursor back to the first card
   move(CURS_ROW, CURS_POS_1);
   /* Draw the hand including the new cards that 
   * were replaced in the swap */
   drawCards(card1, card2, card3, card4, card5, hand);
   // update the score
   drawBankRoll(bankRollWindow, bankRoll);
   /* Update instructions. Instructions change
   * based on dealOrDraw value */
   drawInstructions(instructions, dealOrDraw);
   refresh();
}

// assumes the user will only select a card once.
// needs work.
void replaceCards(CARD *deck, CARD *hand, int *cardsDealt,
               int cursPos){
    // swap cards in hand based on cursor position
    switch(cursPos){
        case CURS_POS_1:
            // replace the first card
            hand[0] = deck[*cardsDealt];
            (*cardsDealt) ++;
            // Mark that the card was selected for swap
            mvprintw( CURS_ROW, (CURS_POS_1 - 1), MARK_CARD);
            refresh();
            break;
                       
        case CURS_POS_2:
            // Replace the second card.
            hand[1] = deck[*cardsDealt];
            (*cardsDealt) ++;
            mvprintw(CURS_ROW, (CURS_POS_2 -1), MARK_CARD);
            refresh();
            break;
 
        case CURS_POS_3:
            // Replace the third card.
            hand[2] = deck[*cardsDealt];
            (*cardsDealt) ++;
            mvprintw(CURS_ROW,(CURS_POS_3 -1), MARK_CARD);
            refresh();
            break;

        case CURS_POS_4:
            // Replace the fourth Card;
            hand[3] = deck[*cardsDealt];
            (*cardsDealt) ++;
            mvprintw(CURS_ROW,(CURS_POS_4 -1), MARK_CARD);
            refresh();
            break;

            case CURS_POS_5:
            // Replace the 5th Card
            hand[4] = deck[*cardsDealt];
            (*cardsDealt) ++;
            mvprintw(CURS_ROW, (CURS_POS_5 - 1), MARK_CARD);
            refresh();
            break;    
    }
                   
}
