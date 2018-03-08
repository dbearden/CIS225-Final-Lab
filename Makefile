clean :
	rm -f poker $(MAIN)

Poker: poker.c poker.h 
	gcc -std=c99 -o poker poker.c

INC = poker.h
MAIN = poker
SRC = createDeck.c dealHand.c drawBankRoll.c drawCards.c drawInstructions.c drawScoreTable.c scoreHand.c shuffleDeck.c

$(MAIN) : $(INC) $(MAIN).c $(SRC)
	gcc -std=c99 -lncursesw -g -o $(MAIN) $(MAIN).c $(SRC)

