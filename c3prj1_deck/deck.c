#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "deck.h"

void print_card(card_t c);

void print_hand(deck_t * hand){
  for(int i=0;i<hand->n_cards;i++){
    print_card((*(*hand).cards[i]));
    printf(" ");
  }
}

int deck_contains(deck_t * d, card_t c) {
  for (int i=0;i<d->n_cards;i++){
    if ((*(*d).cards[i]).value==c.value&&(*(*d).cards[i]).suit==c.suit){
      return 1;
    }
  }
  return 0;
}

void shuffle(deck_t * d){
  for (int i=0;i<2*(d->n_cards);i++){
    int n=random()%(d->n_cards);
    card_t temp=**(*d).cards;
    **(*d).cards=*((*d).cards[n]);
    *((*d).cards[n])=temp;
  }
}

void assert_full_deck(deck_t * d) {
  for (int i=0;i<d->n_cards;i++){
    for (int j=i+1;j<d->n_cards;j++){
      if ((*(*d).cards[i]).value==(*(*d).cards[j]).value&&(*(*d).cards[i]).suit==(*(*d).cards[j]).suit){
  	printf("invalid deck");
  	return;
      }
    }
  }
}

void add_card_to(deck_t*deck,card_t c){
  (*deck).cards=realloc((*deck).cards,(deck->n_cards+1)*sizeof(*(*deck).cards));
  card_t * c1=malloc(sizeof(*c1));
  c1->value=c.value;
  c1->suit=c.suit;
  (*deck).cards[deck->n_cards]=c1;
  deck->n_cards++;
}

card_t * add_empty_card(deck_t * deck){
  card_t* empty_card=malloc(sizeof(*empty_card));
  empty_card->value=0;
  empty_card->suit=0;
  (*deck).cards=realloc((*deck).cards,(deck->n_cards+1)*sizeof(*(*deck).cards));
  (*deck).cards[deck->n_cards]=empty_card;
  deck->n_cards++;
  return empty_card;
}

deck_t * make_deck_exclude(deck_t * excluded_cards){
  deck_t* spdeck=malloc(sizeof(*spdeck));
  spdeck->cards=NULL;
  spdeck->n_cards=0;
  for (int i=0;i<52;i++){
    card_t c=card_from_num(i);
    if(deck_contains(excluded_cards,c)==0){
      (*spdeck).cards=realloc((*spdeck).cards,(spdeck->n_cards+1)*sizeof(*(*spdeck).cards));
      card_t *card=malloc(sizeof(*card));
      card->value=c.value;
      card->suit=c.suit;
      (*spdeck).cards[spdeck->n_cards]=card;
      spdeck->n_cards++;
    }
  }
  return spdeck;
}

deck_t *build_remaining_deck(deck_t **hands,size_t n_hands){
  deck_t *exclude=malloc(sizeof(*exclude));
  exclude->cards=NULL;
  exclude->n_cards=0;
  for(int i=0;i<n_hands;i++){
    for(int j=0;j<(hands[i])->n_cards;j++){
      add_card_to(exclude,*(*hands[i]).cards[j]);
    }
  }
  deck_t * remaining=make_deck_exclude(exclude);
  free(exclude->cards);
  free(exclude);
  return remaining;
}

void free_deck(deck_t * deck){
  for(int i=0;i<deck->n_cards;i++){
    free((*deck).cards[i]);
  }
  free(deck->cards);
  free(deck);
}
