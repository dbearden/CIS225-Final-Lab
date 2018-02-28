/* createDeck.c
 *
 * Authors: Justin Crawford, Daniel Bearden
 *
 * Date: 2/26/2018
 *
 */

#include "poker.h"

void createDeck(CARD *deck){
    int card; 
    card = 0;
    for(int i = SPADE; i <= DIAMOND; i++){
        for(int j = ACE; j <= KING; j++){
            deck[card].suit = i;
            deck[card].value = j;
            card ++;
        }
    }
}

