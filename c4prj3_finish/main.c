#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <ctype.h>
#include "cards.h"
#include "deck.h"
#include "eval.h"
#include "future.h"
#include "input.h"
int main(int argc, char ** argv) {
  if(argc<2)
    {
      perror("you do not have enough argument\n");
      exit(EXIT_FAILURE);
    }
  unsigned int  num_trials = 10000;
  if(argc >= 3)
    {
      num_trials = atoi(argv[2]);
    }
  FILE *f = fopen(argv[1], "r");
  if(f==NULL)
    {
      perror("the file couldn't open\n");
      exit(EXIT_FAILURE);
    }
  future_cards_t *fc = malloc(sizeof(*fc));
  fc->n_decks = 0;
  fc->decks = NULL;
  size_t *n_hands = malloc(sizeof(*n_hands));
  *n_hands = 0;
  deck_t** deckt = read_input(f, n_hands, fc);
  deck_t *remainingDeck = build_remaining_deck(deckt, *n_hands);
  unsigned int *winCountArray = malloc((*n_hands+1)*sizeof(*winCountArray));
  for(int i=0; i <= *n_hands; i++)
    {
      winCountArray[i]=0;
    }
  
  for(int i=0; i<num_trials; i++)
    {
      shuffle(remainingDeck);
      future_cards_from_deck(remainingDeck, fc);
      int winner = 0, winnerTie=0;
      for(size_t j=1; j < *n_hands; j++)
	{
	  if(compare_hands(deckt[winner], deckt[j])== -1)
	    {
	      winner = j;
	      winnerTie = 0;
	    }
	  else if(compare_hands(deckt[winner], deckt[j])==0)
	    {
	      winnerTie +=1;
	    }
	}
      if(winnerTie !=0)
	{
	  winCountArray[*n_hands]+=1;
	}
      else
	{
	  winCountArray[winner]+=1;
	}
    }
  for(size_t j=0; j < *n_hands; j++)
    {
      double percent = winCountArray[j];
      fprintf(stdout, "Hand %zu won %u / %u times (%.2f%%)\n", j, winCountArray[j], num_trials, 100* percent/num_trials);
    }
  fprintf(stdout, "And there were %u ties\n", winCountArray[*n_hands]);
  free(winCountArray);
  free_deck(remainingDeck);
  for(size_t i=0; i<*n_hands; i++)
    {
      free_deck(deckt[i]);
    }
  free(deckt);
  for(size_t i=0; i<fc->n_decks; i++)
    {
      free(fc->decks[i].cards);
    }
  free(fc->decks);
  free(fc);
  free(n_hands);
  if(fclose(f)!=0)
    {
      perror("the file f couldn't close\n");
      exit(EXIT_FAILURE);
    }
  return EXIT_SUCCESS;
}
