#include "dominion.h"
#include <stdio.h>
#include <stdlib.h>

int failed = 0;

void myassert(int b, char *msg)
{
	if (b == 0) {
		printf("FAILED ASSERTION: %s\n", msg);
		failed = 1;
	}
}

void checkasserts()
{
	if (!failed) {
		printf("TEST SUCCESSFULLY COMPLETED.\n");
	}
}

// Card Testing: village
int main()
{
	printf("Testing card: village\n");
	int final_numhand, init_numhand, init_numact, final_numact;

	//Setup a game.
	struct gameState *g = calloc(1, sizeof(struct gameState));
	int k[10] =
	    { smithy, adventurer, gardens, embargo, cutpurse, mine, ambassador,
		outpost, baron, tribute
	};

	initializeGame(2, k, 5, g);

	//Make the card we are testing the first in the users hand, and make sure
	//we play the first user.
	g->hand[0][0] = village;
	g->whoseTurn = 0;

	//Get current number of cards in hand and number of actions for comparison.
	init_numhand = numHandCards(g);
	init_numact = g->numActions;

	playCard(0, 0, 0, 0, g);

	//playCard with village should add one card to the hand, but discard one
	//(village), so the final should be the same as initial. And number of
	//actions should increased by two, but subtract one for playing the card.
	final_numhand = numHandCards(g);
	final_numact = g->numActions;
	myassert(final_numhand == init_numhand,
		 "Village should add one card to hand.");

	myassert(final_numact == init_numact + 1,
		 "Village should add two actions");

	checkasserts();
	free(g);
	return 0;
}
