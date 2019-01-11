# Poker Hand Group Lab

# Program Specification:

Develop a terminal-graphics program using the Linux curses library to display and score poker hands from a shuffled deck.

Develop your code on cis2 (a Linux box). Compile your code with "gcc -g -o poker poker.c -Wall -std=c99 -lcurses" to make an executable named "poker". If you have additional source files, they would be listed after poker.c. Run your program by typing "./poker" at the prompt.

The program needs to provide the following functionality:

* Display the user's accumulated score and then give the user the option to shuffle the deck, display a hand, or exit the program. Perform the chosen option.

* When the user requests that you display the hand display 5 cards graphically, and instructions to the user.

  * Users are given a way to replace any/all of the 5 cards with new cards from the deck.

  * Once users have replaced the requested cards (or specified in some manner that they did not want to), the hand is scored.

  * The hand's score and its feature (Royal Flush, for example) is displayed to the user.

* You will draw from the same shuffled deck (not redrawing any cards already dealt) until the user requests a re-shuffle or there are less than 10 cards left un-dealt. 

* If there are less than 10 cards remaining once the score is displayed, only the exit and shuffle options should be provided.

* If the user requests a shuffle, all cards are returned to the deck.

* Find a way to be creative in the display, using color, card shapes, layout, and so-forth. Note that the Hedgehog example had that creativity, though it did not fully implement this specification.

* Upon exit, the terminal should operate normally (reset or stty sane should not be required) -- this requires a clean use of curses with appropriate endwin() calls.

* Once a hand is scored, the original options are displayed again. Let the user then either quit, shuffle the deck, or get a new hand. If there are less than 10 cards left, only quit or shuffle are valid options (they must not be allowed to deal).

For scoring, use these values:

* Lose: -50
* Pair of Jacks or Better: 50
* Two Pairs: 100
* Three of a Kind: 150
* Straight: 200
* Flush: 250
* Full House: 400
* Four of a Kind: 500
* Straight Flush: 1000
* Royal Flush: 2000


## Specific Requirements

* have a compact representation of the deck of cards

* use bitfields in a struct for a small representation of each card

* use enum in an appropriate manner (vs. constants)

* do not directly invoke malloc (curses uses malloc, that is the only permitted use of it)

* implement an efficient shuffle, and document your source. You *cannot* copy shuffle code from some other place -- you must cite a source, and it can at most have pseudocode in it. The Wikipedia pages are good for the Fischer-Yates shuffle. Any efficient shuffle is permitted.

* implement efficient scoring of the hand.

* The Unicode characters for card suits can be used; curses provides color manipulation

* Note that putty and curses often interact poorly -- if any particular settings for putty are needed, document them in the header comment in your poker.c

* If you have multiple files, create a Makefile for compilation.

* modularize - if similar actions are needed for several operations, their common portions should be turned into functions and re-used by the operations. Typically no function should be more than 30 lines in length (including main).

* your program must compile in gcc on cis2

* your program must run with a clean valgrind result and cleanup of the windows to return the terminal to proper operating condition

* put your code in a file named poker.c; if you choose to use multiple files, main() should be in poker.c 

* your program has to follow class style, including proper indentation (use whitespaces, not tabs), whitespaces, braces, meaningful function and variable names, etc.

* Your program should include the following comments:

  * each file should have a header comment contain the author(s) - note if pair programming is used, as git records who made the actual changes to a file, noting any known issues with the functions in that file, and any putty settings required by the particular use of curses

  * A comment on each function explaining its parameters, any output it produces, and any values it returns.

  * Comments explaining your logic, inline within functions, as appropriate

  * There should be a poker.h with any structs, enums, and functions called from other files defined in it.

* Do not include any executables in your codeline files (use a .gitignore to avoid adding them).

* The program can assume a standard terminal-size window (it does not need to be responsive to resizing).

* The program can use curses box()/border() capability (which requires putty settings to change) or Unicode line drawing, but should not mix the two (be consistent).
