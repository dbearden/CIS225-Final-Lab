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

/* Menu options */
#define MOVE_RIGHT 's'
#define MOVE_LEFT 'a'
#define SWAP_CARD 'f'
#define DEAL_HAND 'd'
#define QUIT 'q'
#define SHUFFLE_DECK 'g'

/* Hand Results */
#define ROYAL_FLUSH 2000
#define STRAIGHT_FLUSH 1000
#define FOUR_KIND 500
#define FULL_HOUSE 400
#define FLUSH 250
#define STRAIGHT 200
#define THREE_KIND 150
#define TWO_PAIR 100
#define PAIR 50
#define LOSE -50

/* Bit values for swapping cards at a given position */
#define HAND_BIT_1 0x10
#define HAND_BIT_2 0x08
#define HAND_BIT_3 0x04
#define HAND_BIT_4 0x02
#define HAND_BIT_5 0x01

/* Mask for selecting which cards should be swapped */
typedef struct cardsToSwap{
    unsigned int mask:5;
}CARDS_TO_SWAP;

/* Moves the cursor to the next card */
void moveCursRight(int*);

/* Moves the cursor to the previous card */
void moveCursLeft(int*);

/* Deals a new hand */
void dealRound( CARD *, CARD *, int *, int *, int *);

/* Draw round actions */ 
void drawRound(WINDOW *, CARD *, int *, int *);

/* Resets the UI for the next hand */
void resetUI(WINDOW *, WINDOW *, WINDOW *, WINDOW *,
             WINDOW *, WINDOW *, WINDOW *, CARD *, int, int);

/* Replaces selected cards with next card in the deck */
void replaceCards(CARD *, CARD*, int, CARDS_TO_SWAP *);

/* Reminds the user to deal a new hand or swap out cards */
void drawPlayGuide(WINDOW *, int);

/* Draws hand result */
void drawResult(WINDOW *, int);
/* sorts the hand for scoring */
void sortHand(CARD *, CARD *);

/* swaps selected cards in the hand */
void swapCards(CARD *, CARD *, int *, CARDS_TO_SWAP);

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
    WINDOW *playGuide;    
    WINDOW *resultWindow;    
    // create an array for 52 CARDs.
    CARD deck[52];
    // create an array for 5 CARDs.
    CARD hand[HAND_SIZE];
    CARD tempHand[HAND_SIZE];   
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
    
    // Initialize the swap mask to 0
    CARDS_TO_SWAP swapMask;
    swapMask.mask = 0;

    // Fill the deck with CARDs
    createDeck(deck);
    
    // Randomize the deck
    shuffleDeck(deck);
    
    // Draw the windows
    drawBankRoll(bankRollWindow, bankRoll);  
    drawScoreTable(scoreTable);
    drawInstructions(instructions, dealOrDraw);
    drawPlayGuide(playGuide, dealOrDraw);
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
            case MOVE_RIGHT:
                moveCursRight(&cursPos);
                break;
            case MOVE_LEFT:
                moveCursLeft(&cursPos);
                break;
            /* Deals a hand, or draws the cards to replace
             * and score the hand */
            case DEAL_HAND:
                if((dealOrDraw)){
                    dealRound( deck, hand, &cardsDealt, &dealOrDraw,
                              & cursPos);
                    refresh();                     
                }
                else {
                    swapCards(deck, hand, &cardsDealt, swapMask);
                    drawRound(resultWindow, hand, &dealOrDraw, &bankRoll);
                }
                drawPlayGuide(playGuide, dealOrDraw);
                resetUI(card1, card2, card3, card4, card5, instructions, 
                        bankRollWindow, hand, bankRoll, dealOrDraw);

                // Reset swapMask after each dealing or replacement
                swapMask.mask = 0;
                break;

            case SWAP_CARD:
                // Not a deal round so cards can be swapped
                if(!dealOrDraw){
                    replaceCards(deck, hand, cursPos, &swapMask);
                }
            case SHUFFLE_DECK:
                shuffleDeck(deck);                               
        }
        
    } while(choice != QUIT);
    delwin(scoreTable);
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

void drawRound(WINDOW *resultWindow, CARD *hand, int *dealOrDraw, int *bankRoll){
    CARD tempHand[HAND_SIZE];
    int score;
    // Draw round, start cursor at card 1
    // Card replacements take place in other
    // functions.           
    move(CURS_ROW, CURS_POS_1);
    sortHand(hand, tempHand);
    score = scoreHand(tempHand);
    // Score the hand and update score
    *bankRoll += score;
    drawResult(resultWindow, score);
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

//TODO: toggle MARK_CARD
//somethinge like(?):
//mvprintw(CURS_ROW, 
//         (CURS_POS_X - 1), 
//         (swapMask->mask & HAND_BIT_X) ? MARK_CARD : UNMARK_CARD);
void replaceCards(CARD *deck, CARD *hand, int cursPos, CARDS_TO_SWAP *swapMask){
    // swap cards in hand based on cursor position
    switch(cursPos){
        case CURS_POS_1:
            // Toggle the first card selection
            swapMask->mask ^= HAND_BIT_1;
            // Mark that the card was selected for swap in display
            mvprintw( CURS_ROW, (CURS_POS_1 - 1), MARK_CARD);
            refresh();
            break;
                       
        case CURS_POS_2:
            // Toggle the second card.
            swapMask->mask ^= HAND_BIT_2;
            mvprintw(CURS_ROW, (CURS_POS_2 -1), MARK_CARD);
            refresh();
            break;
 
        case CURS_POS_3:
            // Toggle the third card.
            swapMask->mask ^= HAND_BIT_3;
            mvprintw(CURS_ROW,(CURS_POS_3 -1), MARK_CARD);
            refresh();
            break;

        case CURS_POS_4:
            // Toggle the fourth Card;
            swapMask->mask ^= HAND_BIT_4;
            mvprintw(CURS_ROW,(CURS_POS_4 - 1), MARK_CARD);
            refresh();
            break;

            case CURS_POS_5:
            // Toggle the 5th Card
            swapMask->mask ^= HAND_BIT_5;
            mvprintw(CURS_ROW, (CURS_POS_5 - 1), MARK_CARD);
            refresh();
            break;    
    }
                   
}

void drawPlayGuide(WINDOW *playGuide, int dealOrDraw){
    playGuide = newwin(2, 30, 1, 1);
    wbkgd(playGuide, COLOR_PAIR(3));
    if(dealOrDraw){
        mvwprintw(playGuide, 1, 1, "Press 'd' to deal");
    }
    else{
        mvwprintw(playGuide, 1, 1, "Select cards to swap");
    }
    refresh();
    wrefresh(playGuide); 
    delwin(playGuide);   
}

void drawResult(WINDOW *resultWindow, int result){
    resultWindow = newwin(2, 20, 5, 10);
    wbkgd(resultWindow, COLOR_PAIR(3));
    switch(result){
        case ROYAL_FLUSH:
            mvwprintw(resultWindow, 1, 1, "Royal Flush");
            break;
        case STRAIGHT_FLUSH:
            mvwprintw(resultWindow, 1, 1, "Straight Flush");
            break;
        case FOUR_KIND:
            mvwprintw(resultWindow, 1, 1, "4 of a Kind");
            break;
        case FULL_HOUSE:
            mvwprintw(resultWindow, 1, 1, "Full House");
            break;
        case FLUSH:
            mvwprintw(resultWindow, 1, 1, "Flush");
            break;
        case STRAIGHT:
            mvwprintw(resultWindow, 1, 1, "Straight");
            break;
        case THREE_KIND:
            mvwprintw(resultWindow, 1, 1, "Three of a kind");
            break;
        case TWO_PAIR:
            mvwprintw(resultWindow, 1, 1, "Two Pair");
            break;
        case PAIR: 
            mvwprintw(resultWindow, 1, 1, "Jacks or better");
            break;
        case LOSE:
            mvwprintw(resultWindow, 1, 1, "You lose");
            break;
    }
    refresh();
    wrefresh(resultWindow);
    delwin(resultWindow);
}

void sortHand(CARD *hand, CARD *sortedHand){
    CARD temp;
    for(int i = 0; i < HAND_SIZE; i++){
        sortedHand[i] = hand[i];
    }
    for(int i = 0; i < HAND_SIZE - 1; i++){
        for(int j = 0; j < HAND_SIZE - 1; j ++){
            if(sortedHand[j].value > sortedHand[j+1].value){
                temp = sortedHand[j];
                sortedHand[j] = sortedHand[j+1];
                sortedHand[j+1] = temp;
            }
        }
    }
}

void swapCards(CARD *deck, CARD *hand, int *cardsDealt, CARDS_TO_SWAP swapMask){
    unsigned int checkMask = 0x10;
    
    int i;
    for(i = 0; i < HAND_SIZE; i++){
        if(swapMask.mask & checkMask){
            hand[i] = deck[*cardsDealt];
            (*cardsDealt)++;
        }
        swapMask.mask <<= 1;
    }
}
