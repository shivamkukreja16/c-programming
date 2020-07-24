#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "deck.h"

//void print_hand(deck_t * hand) {
//  card_t ** ptr = hand->cards;
//  for (int i=0; i<(hand->n_cards); i++) {
//    print_card(**ptr);
//    printf("%s"," ");
//    ptr++;
//  }
//}

void print_hand(deck_t * hand) {
  for (int i=0; i<(hand->n_cards); i++) {
    print_card(*(hand->cards[i]));
    printf(" ");
  }
}

int deck_contains(deck_t * d, card_t c) {
  card_t ** ptr = d->cards;
  for (int i=0; i<(d->n_cards); i++) {
    if(suit_letter(**ptr) == suit_letter(c) && value_letter(**ptr) == value_letter(c)) {
      return 1;
    }
    ptr++;
  }
  return 0;
}

void shuffle(deck_t * d) {
  card_t ** card = d->cards ;
  card_t * temp;
  size_t n =d->n_cards;
  int rand;
  for (int i=0; i<(n/2); i++) {
    rand = random()%n;
    temp = card[i];
    card[i] = card[rand];
    card[rand] = temp;
  }
}

void assert_full_deck(deck_t * d) {
  for (int i=0; i<d->n_cards; i++)
    assert(deck_contains(d, card_from_num(i)));
}

void add_card_to(deck_t * deck, card_t c) {
  deck->n_cards++;
  deck->cards = realloc(deck->cards, deck->n_cards * sizeof(*deck->cards));
  deck->cards[deck->n_cards-1] = NULL;
  deck->cards[deck->n_cards-1] = realloc(deck->cards[deck->n_cards-1], sizeof(*deck->cards[deck->n_cards-1]));
  deck->cards[deck->n_cards-1]->value = c.value;
  deck->cards[deck->n_cards-1]->suit = c.suit;
}

card_t * add_empty_card(deck_t * deck) {
  card_t c;
  c.value = 0;
  c.suit = 0;
  add_card_to(deck, c);
  return deck->cards[deck->n_cards-1];
}

deck_t * make_deck_exclude(deck_t * excluded_cards) {
  deck_t * result = malloc(sizeof(*result));
  result->cards = NULL;
  result->n_cards = 0;
  int a;
  card_t c;
  for(int i=0; i<52; i++) {
    c = card_from_num(i);
    a = deck_contains(excluded_cards, c);
    if(a==0) {
      add_card_to(result, c);
    }
  }
  return result;
}

deck_t * build_remaining_deck(deck_t ** hands, size_t n_hands) {
  deck_t * excluded_cards = malloc(sizeof(*excluded_cards));
  excluded_cards->cards = malloc(sizeof(*excluded_cards->cards));
  excluded_cards->n_cards = 0;
  for (int i=0; i<n_hands; i++) {
    for (int j=0; j<hands[i]->n_cards; j++) {
      add_card_to(excluded_cards, *hands[i]->cards[j]);
    }
  }
  excluded_cards = make_deck_exclude(excluded_cards);
  return excluded_cards;
}

void free_deck(deck_t * deck) {
  for (int i=0; i<deck->n_cards; i++) {
    free(deck->cards[i]);
  }
  free(deck->cards);
  free(deck);
}
