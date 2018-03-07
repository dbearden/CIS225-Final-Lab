/* scoreHand.c
 *
 * Authors: Daniel Bearden
 *
 * Created: 3/1/2018
 */

#include "poker.h"
#define HAND_SIZE 5


/*
 * Takes a 5-card hand as a sorted array
 * and returns the relevant point value 
 * for the hand.
 */
int scoreHand(CARD *hand){
    short royalFlush=0;
    short straightFlush=0;
    short fourOfAKind=0;
    short fullHouse=0;
    short flush=0;
    short straight=0;
    short threeOfAKind=0;
    short twoPair=0;
    short facePair=0;

    // Used to differentiate four of a kind from full house
    // and two pair from three of a kind.
    // Without a scaling factor like this, the above pairs
    // would not score properly.
    short continuedMatching = 1;

    int i;

    CARD currentCard;
    CARD previousCard;


    // Differentiates royal flush and straight flush.
    // Also corrects for 10-Ace straight not counting
    // on the first loop
    if(hand[0].value == ACE &&
        hand[1].value == TEN){
        if(hand[0].suit == hand[1].suit){
            royalFlush+=2;
        }
        straight++;
    }

    currentCard = hand[0];
    for(i = 1; i < HAND_SIZE; i++){
        previousCard = currentCard;
        currentCard = hand[i];
        //Straights
        if(currentCard.value - previousCard.value == 1){
            continuedMatching = 1;
            //Straight Flushes (and flush)
            if(currentCard.suit == previousCard.suit){
                royalFlush++;
                straightFlush++;
                flush++;
            }
            straight++;
        //Flush
        } else if(currentCard.suit == previousCard.suit){
            continuedMatching = 1;
            flush++;
        //Kinds
        } else if(currentCard.value == previousCard.value){
            if(currentCard.value == JACK ||
               currentCard.value == QUEEN||
               currentCard.value == KING ||
               currentCard.value == ACE){
                facePair += continuedMatching;
            }
            twoPair += continuedMatching;
            threeOfAKind += continuedMatching;
            fullHouse += continuedMatching;
            fourOfAKind += continuedMatching;

            //Scales with consecutive matches,
            //ergo, four of a kind matches
            //higher than full house matches
            //higher than three of a kind matches
            //higher than two pair
            continuedMatching++;
        } else {
            continuedMatching = 1;
        }
    }

    if(royalFlush == 5){
        return 2000;
    } else if(straightFlush == 4){
        return 1000;
    } else if(fourOfAKind == 6){
        return 500;
    } else if(fullHouse == 4){
        return 400;
    } else if(flush == 4){
        return 250;
    } else if(straight == 4){
        return 200;
    } else if(threeOfAKind == 3){
        return 150;
    } else if(twoPair == 2){
        return 100;
    } else if(facePair == 1){
        return 50;
    } else {
        return -50;
    }
}



