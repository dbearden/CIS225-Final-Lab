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
            switch(deck[card].value){
                case 1:
                    deck[card].face = 65;
                    break;
                case 2:
                    deck[card].face = 50;
                    break;
                case 3:
                    deck[card].face = 51;
                    break;
                case 4:
                    deck[card].face = 52;
                    break;
                case 5:
                    deck[card].face = 53;
                    break;                   
                case 6:
                    deck[card].face = 54;
                    break;
                case 7:
                    deck[card].face = 55;
                    break;
                case 8:
                    deck[card].face = 56;
                    break;
                case 9:
                    deck[card].face = 57;
                    break;
                case 10:
                    deck[card].face = 84;
                    break;
                case 11:
                    deck[card].face = 74;
                    break;
                case 12:
                    deck[card].face = 81;
                    break;
                case 13:
                    deck[card].face = 75;
                    break;
            }
            card ++;
        }
    }
}

