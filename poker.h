/* poker. h
 * 
 * Authors: Daniel Bearden, Justin Crawford
 *
 * Date : 2/26/2018
 *
 */

#include <stdlib.h>
#include <time.h>

enum SUITS{ SPADE, CLUB, HEART, DIAMOND }

enum VALUES{ ACE=1, TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT,
             NINE, TEN, JACK, QUEEN, KING }

typedef struct card{ 
    enum SUITS suit:2; 
    enum VALUES value:4;
} CARD;

