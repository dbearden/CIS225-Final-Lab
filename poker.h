/* poker. h
 * 
 * Authors: Daniel Bearden, Justin Crawford
 *
 * Date : 2/26/2018
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <curses.h>

/* Unicode values for box drawing */
#define UP_LEFT_CORNER "\xE2\x94\x8C"
#define LINE "\xE2\x94\x82"
#define LOWER_LEFT_CORNER "\xE2\x94\x94"
#define LOWER_RIGHT_CORNER "\xE2\x94\x98"
#define UP_RIGHT_CORNER "\xE2\x94\x90"
#define HORIZONTAL_LINE "\xE2\x94\x80"

typedef enum suits{ SPADE, CLUB, HEART, DIAMOND } SUITS;

typedef enum values{ ACE=1, TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT,
             NINE, TEN, JACK, QUEEN, KING } VALUES;

typedef struct card{ 
    unsigned int suit:2; 
    unsigned int value:4;
    /* Stores the ascii value card faces */
    unsigned int face:8;
} CARD;

typedef struct cardsToSwap{
    unsigned int mask:5;
} CARDS_TO_SWAP;

void createDeck(CARD *);

void shuffleDeck(CARD *);

void dealHand( CARD *, CARD *, int *);

int scoreHand(CARD *);

void swapCards(CARDS_TO_SWAP, CARD *, CARD *, int *);

void drawCards(WINDOW *, WINDOW *, WINDOW *, WINDOW *, WINDOW *, CARD *hand);

void drawScoreTable(WINDOW *);

void drawBankRoll(WINDOW *, int);

void drawInstructions(WINDOW *, int);
