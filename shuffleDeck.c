/* shuffleDeck.c
 *
 * Authors: Justin Crawford, Daniel Bearden
 *
 * Date: 2/27/2016
 *
 */

#include <time.h>

#include "poker.h"

/* shuffleDeck loops through an array of 52 cards, swapping
 * the index equal to the current iteration to the index of
 * a random number. Based on psueudo code from 
 * https://en.wikipedia.org/wiki/Fisher%E2%80%93Yates_shuffle 
 * param deck - An array of CARD structs.
 * return void
 */
void shuffleDeck (CARD *deck){
    // seeds rand() function with the current time.
    srand(time(NULL));
        for(int i = 51; i >= 1; i--){
            // set range for random number generated
            int random = rand() % (i + 1);
            // swap the cards
            CARD temp = deck[i];
            deck[i] = deck[random];
            deck[random] = temp;
    }
}
