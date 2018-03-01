/* dealHand.c
 *
 * Authors: Justin Crawford, Daniel Bearden
 *
 * Date : 2/28/2018
 *
 */

#include "poker.h"

#define NEEDS_SHUFFLE 43
#define HAND_SIZE 5

/* dealHand adds the first five CARDS from current position
 * of deck, indicated by the value of cardsDealt, to another 
 * CARD array. dealHand makes a call to shuffleDeck if there
 * are less than ten indexes left in deck.
 * param deck - An array of 52 CARDS
 * param hand - An array of 5 CARDS
 * param cardsDealt - The number of cards dealt since last shuffle
 * return void
 */
void dealHand(CARD *deck, CARD *hand, int *cardsDealt){
    
    if((*cardsDealt < NEEDS_SHUFFLE)){
        for(int i = 0; i < HAND_SIZE; i++){
             hand[i] = deck[*cardsDealt];
             *cardsDealt = (*cardsDealt) + 1;
        } 
    } else {
        shuffleDeck(deck);
        *cardsDealt = 0;
        dealHand(deck, hand, cardsDealt);
    }    
}

