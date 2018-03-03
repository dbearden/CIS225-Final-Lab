/* swapCards.c
 *
 * Authors: Daniel Bearden
 *
 * Created: 3/1/2018
 */

#include "poker.h"

/* Takes a mask indicating which cards in the hand should be swapped,
 * the array which represents the hand,
 * the array which represents the deck,
 * the address of how many cards have been dealt.
 */
void swapCards(CARDS_TO_SWAP handMask,
               CARD *hand,
               CARD *deck,
               int *cardsDealtPtr){
    int maskCheck = 0x10;
    int i;
    for(i = 0; i < 5; i++){
        if(handMask.mask & maskCheck){
            hand[i] = deck[*cardsDealtPtr];
            (*cardsDealtPtr)++;
        }
        handMask.mask <<= 1;
    }
}
