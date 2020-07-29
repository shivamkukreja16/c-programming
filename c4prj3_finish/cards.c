#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include "cards.h"


void assert_card_valid(card_t c) {
  assert(2 <= c.value && c.value <= VALUE_ACE);
  assert(SPADES <= c.suit && c.suit <= CLUBS); // or (SPADES <= c.suit && c.suit < NUM_SUITS)
}

const char * ranking_to_string(hand_ranking_t r) {
  switch (r) {
  case STRAIGHT_FLUSH: return "STRAIGHT_FLUSH";
  case FOUR_OF_A_KIND: return "FOUR_OF_A_KIND";
  case FULL_HOUSE: return "FULL_HOUSE";
  case FLUSH: return "FLUSH";
  case STRAIGHT: return "STRAIGHT";
  case THREE_OF_A_KIND: return "THREE_OF_A_KIND";
  case TWO_PAIR: return "TWO_PAIR";
  case PAIR: return "PAIR";
  case NOTHING: return "NOTHING";
  }

  return "";
}

char value_letter(card_t c) {
  if (c.value == 10) {
    return '0';
  }
  else if (2 <= c.value && c.value <= 9) {
    return '0' + c.value;
  }
  else {
    switch(c.value){
    case VALUE_ACE : return 'A';
    case VALUE_KING: return 'K';
    case VALUE_QUEEN: return 'Q';
    case VALUE_JACK: return 'J';
    }
  }
  
  return 'x';
}


char suit_letter(card_t c) {

  switch (c.suit) {
  case SPADES: return 's';
  case HEARTS: return 'h';
  case DIAMONDS: return 'd';
  case CLUBS: return 'c';
  case NUM_SUITS: return '?';
  }
  
  return 'x';  
}

void print_card(card_t c) {
  char cvalue = value_letter(c);
  char csuit = suit_letter(c);
  printf("%c%c", cvalue, csuit);
}

card_t card_from_letters(char value_let, char suit_let) {

  card_t temp;

  switch(value_let) {
  case '2':
    temp.value = 2; break;
  case '3':
    temp.value = 3; break;
  case '4':
    temp.value = 4; break;
  case '5':
    temp.value = 5; break;
  case '6':
    temp.value = 6; break;
  case '7':
    temp.value = 7; break;
  case '8':
    temp.value = 8; break;
  case '9':
    temp.value = 9; break;
  case '0':
    temp.value = 10; break;
  case 'J':
    temp.value = 11; break;
  case 'Q':
    temp.value = 12; break;
  case 'K':
    temp.value = 13; break;
  case 'A':
    temp.value = 14; break;
  }

  switch(suit_let) {
  case 's':
    temp.suit = SPADES; break;
  case 'h':
    temp.suit = HEARTS; break;
  case 'd':
    temp.suit = DIAMONDS; break;
  case 'c':
    temp.suit = CLUBS; break;
  }

  assert_card_valid(temp);
  return temp;
}

card_t card_from_num(unsigned c) {
  card_t temp;
  temp.value = (c % 13) + 2;
  temp.suit = c/13;
  return temp;
}
