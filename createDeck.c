/* createDeck.c
 *
 * Authors: Justin Crawford, Daniel Bearden
 *
 * Date: 2/26/2018
 *
 */

#define ASCII_TWO 50
#define ASCII_THREE 51
#define ASCII_FOUR 52
#define ASCII_FIVE 53
#define ASCII_SIX 54
#define ASCII_SEVEN 55
#define ASCII_EIGHT 56
#define ASCII_NINE 57
#define ASCII_T 84
#define ASCII_J 74
#define ASCII_K 75
#define ASCII_Q 81
#define ASCII_A 65

#include "poker.h"

void createDeck(CARD *deck){
    int card; 
    card = 0;
    // loop through each of the suits
    for(int i = SPADE; i <= DIAMOND; i++){
        // Add the values of each card
        for(int j = ACE; j <= KING; j++){
            deck[card].suit = i;
            deck[card].value = j;
            // Add the card faces with ASCII values
            switch(deck[card].value){
                case 1:
                    deck[card].face = ASCII_A;
                    break;
                case 2:
                    deck[card].face = ASCII_TWO;
                    break;
                case 3:
                    deck[card].face = ASCII_THREE;
                    break;
                case 4:
                    deck[card].face = ASCII_FOUR;
                    break;
                case 5:
                    deck[card].face = ASCII_FIVE;
                    break;                   
                case 6:
                    deck[card].face = ASCII_SIX;
                    break;
                case 7:
                    deck[card].face = ASCII_SEVEN;
                    break;
                case 8:
                    deck[card].face = ASCII_EIGHT;
                    break;
                case 9:
                    deck[card].face = ASCII_NINE;
                    break;
                case 10:
                    deck[card].face = ASCII_T;
                    break;
                case 11:
                    deck[card].face = ASCII_J;
                    break;
                case 12:
                    deck[card].face = ASCII_Q;
                    break;
                case 13:
                    deck[card].face = ASCII_K;
                    break;
            }
            card ++;
        }
    }
}

