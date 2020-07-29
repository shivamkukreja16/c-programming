#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <ctype.h>
#include <string.h>
#include "cards.h"
#include "deck.h"
#include "eval.h"
#include "future.h"
#include "input.h"

long int check_value(const char * string) {
  char * endptr = NULL;
  long int ans = strtol(string,&endptr,10);
  if (endptr == string) { return -1; }
  if (*endptr != '\0') { return -1; }
  return ans;
}

long int * run_a_simulation(const char * fileName, long int nTrials, size_t * size) {
  FILE * f = fopen(fileName,"r");
  if (f == NULL) {
    perror("Could not open the input file!");
    exit(EXIT_FAILURE);
  }
  size_t nHands;
  future_cards_t * fc = malloc(sizeof(*fc));
  fc->decks = NULL;
  fc->n_decks = 0;
  deck_t ** inputHands = read_input(f,&nHands,fc);
  *size = nHands;
  deck_t * remainingDeck = build_remaining_deck(inputHands,nHands);
  long int * wins = malloc((nHands+1)*sizeof(*wins));
  for (size_t i = 0; i < nHands+1; i++) {
    wins[i] = 0;
  }
  for (long int trial = 0; trial < nTrials; trial++) {
    shuffle(remainingDeck);
    future_cards_from_deck(remainingDeck,fc);
    size_t bestHand = 0;
    int tie = 0;
    int currentResult;
    for (size_t j = 1; j < nHands; j++) {
      currentResult = compare_hands(inputHands[j],inputHands[bestHand]);
      if (currentResult > 0) {
	bestHand = j;
	tie = 0;
      }
      else if (currentResult == 0) {
	tie = 1;
      }
    }
    if (tie) { (wins[nHands])++; }
    else { (wins[bestHand])++; }
  }
  for (size_t count1 = 0; count1 < fc->n_decks; count1++) {
    free(fc->decks[count1].cards);
  }
  free(fc->decks);
  free(fc);
  for (size_t count2 = 0; count2 < nHands; count2++) {
    free_deck(inputHands[count2]);
  }
  free(inputHands);
  free_deck(remainingDeck);
  if (fclose(f) != 0) {
    perror("Could not close the input file!");
    exit(EXIT_FAILURE);
  }
  return wins;
}

int main(int argc, char ** argv) {
  if ((argc<2)||(argc>3)) {
    fprintf(stderr,"Usage: poker inputFileName (numberOfTrials)\n");
    return EXIT_FAILURE;
  }
  long int nTrials;
  if (argc == 3) {
    nTrials = check_value(argv[2]);
    if (nTrials <= 0) {
      fprintf(stderr,"numberOfTrials must be a positive integer!\n");
      return EXIT_FAILURE;
    }
  }
  else {
    nTrials = 10000;
  }
  int debug = 0;
  if (!strcmp(argv[1],"-debug")) { debug = 1; }
  if (!debug) {
    size_t size;
    long int * wins = run_a_simulation(argv[1],nTrials,&size);
    for (size_t k = 0; k < size; k++) {
      printf("Hand %zu won %u / %u times (%.2f%%)\n",
	     k,(unsigned int)wins[k],(unsigned int)nTrials,100*(wins[k]/(float)nTrials));
    }
    printf("And there were %u ties\n",(unsigned int)wins[size]);
    free(wins);
  }
  else {
    const char * dirPath = "./provided-tests/";
    const char * prefix = "test";
    const char * suffix = ".txt";
    char number[] = "00";
    char * fileName = malloc((strlen(dirPath)+strlen(prefix)+2+strlen(suffix)+1)*sizeof(*fileName));
    FILE * outFile = fopen("./provided-tests/my_answers.txt","w");
    if (outFile == NULL) {
      perror("Could not open the output file!");
      exit(EXIT_FAILURE);
    }
    for (char n = 1; n <= 16; n++) {
      char n1 = n/10 + '0';
      char n2 = n - (n/10)*10 + '0';
      number[0] = n1;
      number[1] = n2;
      strcat(strcat(strcat(strcpy(fileName,dirPath),prefix),number),suffix);
      size_t size;
      long int * wins = run_a_simulation(fileName,nTrials,&size);
      fprintf(outFile,"%s%s%s: ",prefix,number,suffix);
      for (size_t k = 0; k < size-1; k++) {
	fprintf(outFile,"Hand %zu = %0.f%%,",k,100*(wins[k]/(float)nTrials));
	if (100*(wins[k]/(float)nTrials)<99.5) { fprintf(outFile," "); }
	if (100*(wins[k]/(float)nTrials)<9.5) { fprintf(outFile," "); }
	if ((k % 3) == 0) { fprintf(outFile," "); }
	if ((k % 3) == 2) { fprintf(outFile,"\n            "); }
      }
      fprintf(outFile,"Hand %zu = %0.f%%\t",size-1,100*(wins[size-1]/(float)nTrials));
      fprintf(outFile,"\n");
      free(wins);
    }
    free(fileName);
    if (fclose(outFile) != 0) {
      perror("Could not close the output file!");
      exit(EXIT_FAILURE);
    }
  }
  return EXIT_SUCCESS;
}
