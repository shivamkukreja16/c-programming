#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "deck.h"
void print_hand(deck_t * hand){

void print_hand(deck_t * hand)
{
  for (int i = 0; i < hand->n_cards; i++)
  {
    print_card(* hand->cards[i]);
    printf(" ");
  }
}

int deck_contains(deck_t * d, card_t c) {
int deck_contains(deck_t * d, card_t c) 
{
  for (int i = 0; i < d->n_cards; i++)
  {
    if (d->cards[i]->value == c.value && d->cards[i]->suit == c.suit)
      return 1;
  }
  return 0;
}

void shuffle(deck_t * d){
void shuffle(deck_t * d)
{
  int rd = 0;
  card_t *temp;  

  for (int i = 0; i < d->n_cards; i++)
  {
    rd = random() % (d->n_cards);
    temp = d->cards[i];
    d->cards[i] = d->cards[rd];
    d->cards[rd] = temp;
  }
}

void assert_full_deck(deck_t * d) {

void assert_full_deck(deck_t * d) 
{
  assert(d->n_cards == 52 && "Invalid number of cards");

  for (int i = 0; i < d->n_cards; i++)
  {
    assert(deck_contains(d, card_from_num(i)) && "Deck is invalid");
  }
}
  
