/* poker. h
 * 
 * Authors: Daniel Bearden, Justin Crawford
 *
 * Date : 2/26/2018
 *
 */

#include <stdio.h>
#include <stdlib.h>

typedef enum suits{ SPADE, CLUB, HEART, DIAMOND } SUITS;

typedef enum values{ ACE=1, TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT,
             NINE, TEN, JACK, QUEEN, KING } VALUES;

typedef struct card{ 
    unsigned int suit:2; 
    unsigned int value:4;
} CARD;


void createDeck(CARD *);

void shuffleDeck(CARD *);
