#include "eval.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

int card_ptr_comp(const void * vp1, const void * vp2) {
  const card_t * const * cp1 = vp1;
  const card_t * const * cp2 = vp2;
  if ((*cp2)->value < (*cp1)->value ) {
    return -1;
  }
  if ((*cp2)->value > (*cp1)->value ) {
    return 1;
  }
  // if ((*cp2)->value == (*cp1)->value ) {
  else if ((*cp2)->suit < (*cp1)->suit) {
      return -1;
    }
  else if ((*cp2)->suit > (*cp1)->suit) {
      return 1;
    }
  //  else if ((*cp2)->suit == (*cp1)->suit) {
  else {
    return 0;
    }
}

suit_t flush_suit(deck_t * hand) {
  card_t ** cards = hand->cards;
  size_t n = hand->n_cards;
  int s,h,d,c;
  s=0;
  h=0;
  d=0;
  c=0;
  card_t card;
    //printf("testing the loop to check for flush\n");
    for (int i=0; i<n; i++) {
      card.value = cards[i]->value;
      card.suit = cards[i]->suit;
      //print_card(card);
      //printf(" ");
      switch (card.suit) {
      case 0: {s++; break;}
      case 1: {h++; break;}
      case 2: {d++; break;}
      case 3: {c++; break;}
      case 4: break;
      }
    }
    //printf("\n");
    if(s>=5) return SPADES;
    if(h>=5) return HEARTS;
    if(d>=5) return DIAMONDS;
    if(c>=5) return CLUBS;
    return NUM_SUITS;
  }


unsigned get_largest_element(unsigned * arr, size_t n) {
  int largest = 0;
  for (size_t i = 0; i < n; i++) {
    if (*(arr + i) > largest) {
      largest = arr[i];
    }
  }
  //printf("here is largest %d \n", largest);
  return largest;
}

size_t get_match_index(unsigned * match_counts, size_t n,unsigned n_of_akind) {
  for (int i = 0; i < n; i++) {
    if ( match_counts[i] == n_of_akind) {
      return i;
    }
  }
  printf("n_of_akind not found in match_counts");
  abort();
}

ssize_t find_secondary_pair(deck_t * hand,
			     unsigned * match_counts,
			     size_t match_idx) {
  ssize_t index = -1;
  for(index=0;index<hand->n_cards;index++){
    if(match_counts[index] > 1 && hand->cards[index]->value != hand->cards[match_idx]->value){
      return index;
      //break;
    }
  }
  //printf("no second pair\n");
  return -1;
}

//two helper functions:
/*
int is_n_length_straight_at(deck_t * hand, size_t index, suit_t fs, int n) {
  int count = 1;
  card_t ** cardsInHand = hand->cards;
  if (fs == NUM_SUITS) {
    for (size_t i = index; i < hand->n_cards-1; i++) {
      if (cardsInHand[i]->value == cardsInHand[i+1]->value) continue;
      if (cardsInHand[i]->value-1 == cardsInHand[i+1]->value) {
	count++;
	if (count == n) return 1;
      } else return 0;
    }
  } else {
    if (cardsInHand[index]->suit != fs) return 0;
    else {
      card_t * tmpCard = cardsInHand[index];
      for (size_t i = index+1; i < hand->n_cards; i++) {
	if (cardsInHand[i]->suit != fs) continue;
	if (tmpCard->value-1 == cardsInHand[i]->value) {
	  count++;
	  if (count == n) return 1;
	  tmpCard = cardsInHand[i];
	} else return 0;
      }
    }
  }
  return 0;
}
*/


int is_n_length_straight_at(deck_t * hand, size_t index, suit_t fs, int n) {
  int count = 1;
  //int index = 0;  

  for (int i=index; i<(i + n - 1) && i<(hand->n_cards-1); i++) {
    if ( (fs != NUM_SUITS) && (hand->cards[i]->suit != fs) ) {
    break;
    }
   
    if ( ( hand->cards[i+1]->value ) == hand->cards[i]->value - 1 ) {
      //    printf("true\n");
     if ( ( fs == NUM_SUITS ) || ( hand->cards[i]->suit == fs ) )
     count++;
     //if ( hand->cards[i+1]->suit == fs ) { printf("if c>5 this is a straight flush\n"); }
    // index = i;
     } else {
       break;
     }
  } 
  //printf("count of cards in a row = %d\n", count);
  if (count >= n) {
  return 1;
  } else {
  //printf("there is no straight at index position %zu\n", index);
  return 0;
  }
}


int is_ace_low_straight_at(deck_t * hand, size_t index, suit_t fs) {
  if ((hand->cards[index])->value == VALUE_ACE) {
    card_t ** cardsInHands = hand->cards;
    for (size_t i = index+1; i < hand->n_cards-3; i++) {
      if (cardsInHands[i]->value == 5 && is_n_length_straight_at(hand, i, fs, 4) == 1) {
	if (fs == NUM_SUITS) return 1;
	else if (cardsInHands[index]->suit == fs) return 1;
	else return 0;
      }
    }
  }
  return 0;
}

/*int is_ace_low_straight_at(deck_t * hand, size_t index, suit_t fs) {
  if(hand->cards[index]->value != VALUE_ACE) {
    //   printf("there is no ace low straight at index %zu\n", index);
    return 0;
    //printf("i a here now !!! ");
  }
  int index_of_Five = -1;
  for (int i = 0; i < hand->n_cards; i ++) {
    if(hand->cards[i]->value == 5) {
    index_of_Five = i;
    }
  }
  if (index_of_Five == -1) {
  //  printf("no 5 in this hand\n");
    return 0;
  } else {
    // return the 5, 4, 3, 2 combo we will need to complete the straight
    return is_n_length_straight_at(hand, index_of_Five, fs, 4);
  }
}
*/

int is_straight_at(deck_t * hand, size_t index, suit_t fs) {
  if(is_ace_low_straight_at(hand, index, fs) == 1) {
    return -1;
  }
  if(is_n_length_straight_at(hand, index, fs, 5) == 1) {
    return 1;
  }
  return 0;
}

hand_eval_t build_hand_from_match(deck_t * hand,
				  unsigned n,
				  hand_ranking_t what,
				  size_t idx) {

  hand_eval_t ans;
  ans.ranking = what;
  int n_of_a_kind_value = hand->cards[idx]->value;

  for(int i=0;i<n;i++){
    ans.cards[i] = (hand->cards[idx+i]);
  }

  int index = 0; 
  for(int i=0;i<(hand->n_cards);i++){
     if (n > 0) {
       if (hand->cards[i]->value != n_of_a_kind_value) {
       ans.cards[index + n] = hand->cards[i];
       index ++;
       } 
    }
    else {
      ans.cards[index + n] = hand->cards[i]; 
      index++;
    }    
     if ((index + n) == 5) {
      break;
    }  
   }
  
  return ans;
}


/*hand_eval_t build_hand_from_match(deck_t * hand,
				  unsigned n,
				  hand_ranking_t what,
				  size_t idx) {
  hand_eval_t ans;
  ans.ranking = what;
  int index = 0;
  int more_cards = 5 - n;
  int n_of_a_kind = hand->cards[idx]->value;
  for (int i = idx; i < idx + n; i++, index++)
    ans.cards[index] = hand->cards[i];
  for (int i = 0; i < hand->n_cards; i++) {
    if (hand->cards[i]->value != n_of_a_kind) {
      ans.cards[index] = hand->cards[i];
      more_cards--;
      index++;
    }
    if (more_cards == 0)
      break;
  }
  return ans;
}
*/

int compare_hands(deck_t * hand1, deck_t * hand2) {
  qsort(hand1->cards, hand1->n_cards, sizeof(hand1->cards[0]), card_ptr_comp);
  qsort(hand2->cards, hand2->n_cards, sizeof(hand2->cards[0]), card_ptr_comp);

  hand_eval_t hand_1 = evaluate_hand(hand1);
  hand_eval_t hand_2 = evaluate_hand(hand2);

  if (hand_1.ranking < hand_2.ranking)
    return 1;
  else if (hand_2.ranking < hand_1.ranking)
    return -1;

  for (int i = 0; i < 5; i++) {
    if (hand_1.cards[i]->value > hand_2.cards[i]->value)
      return 1;
    else if (hand_1.cards[i]->value < hand_2.cards[i]->value)
      return -1;
  }
  return 0;
}

//You will write this function in Course 4.
//For now, we leave a prototype (and provide our
//implementation in eval-c4.o) so that the
//other functions we have provided can make
//use of get_match_counts.
unsigned * get_match_counts(deck_t * hand) ;

// We provide the below functions.  You do NOT need to modify them
// In fact, you should not modify them!


//This function copies a straight starting at index "ind" from deck "from".
//This copies "count" cards (typically 5).
//into the card array "to"
//if "fs" is NUM_SUITS, then suits are ignored.
//if "fs" is any other value, a straight flush (of that suit) is copied.
void copy_straight(card_t ** to, deck_t *from, size_t ind, suit_t fs, size_t count) {
  assert(fs == NUM_SUITS || from->cards[ind]->suit == fs);
  unsigned nextv = from->cards[ind]->value;
  size_t to_ind = 0;
  while (count > 0) {
    assert(ind < from->n_cards);
    assert(nextv >= 2);
    assert(to_ind <5);
    if (from->cards[ind]->value == nextv &&
	(fs == NUM_SUITS || from->cards[ind]->suit == fs)){
      to[to_ind] = from->cards[ind];
      to_ind++;
      count--;
      nextv--;
    }
    ind++;
  }
}


//This looks for a straight (or straight flush if "fs" is not NUM_SUITS)
// in "hand".  It calls the student's is_straight_at for each possible
// index to do the work of detecting the straight.
// If one is found, copy_straight is used to copy the cards into
// "ans".
int find_straight(deck_t * hand, suit_t fs, hand_eval_t * ans) {
  if (hand->n_cards < 5){
    return 0;
  }
  for(size_t i = 0; i <= hand->n_cards -5; i++) {
    int x = is_straight_at(hand, i, fs);
    if (x != 0){
      if (x < 0) { //ace low straight
	assert(hand->cards[i]->value == VALUE_ACE &&
	       (fs == NUM_SUITS || hand->cards[i]->suit == fs));
	ans->cards[4] = hand->cards[i];
	size_t cpind = i+1;
	while(hand->cards[cpind]->value != 5 ||
	      !(fs==NUM_SUITS || hand->cards[cpind]->suit ==fs)){
	  cpind++;
	  assert(cpind < hand->n_cards);
	}
	copy_straight(ans->cards, hand, cpind, fs,4) ;
      }
      else {
	copy_straight(ans->cards, hand, i, fs,5);
      }
      return 1;
    }
  }
  return 0;
}


//This function puts all the hand evaluation logic together.
//This function is longer than we generally like to make functions,
//and is thus not so great for readability :(
hand_eval_t evaluate_hand(deck_t * hand) {
  suit_t fs = flush_suit(hand);
  hand_eval_t ans;
  if (fs != NUM_SUITS) {
    if(find_straight(hand, fs, &ans)) {
      ans.ranking = STRAIGHT_FLUSH;
      return ans;
    }
  }
  unsigned * match_counts = get_match_counts(hand);
  unsigned n_of_a_kind = get_largest_element(match_counts, hand->n_cards);
  assert(n_of_a_kind <= 4);
  size_t match_idx = get_match_index(match_counts, hand->n_cards, n_of_a_kind);
  ssize_t other_pair_idx = find_secondary_pair(hand, match_counts, match_idx);
  free(match_counts);
  if (n_of_a_kind == 4) { //4 of a kind
    return build_hand_from_match(hand, 4, FOUR_OF_A_KIND, match_idx);
  }
  else if (n_of_a_kind == 3 && other_pair_idx >= 0) {     //full house
    ans = build_hand_from_match(hand, 3, FULL_HOUSE, match_idx);
    ans.cards[3] = hand->cards[other_pair_idx];
    ans.cards[4] = hand->cards[other_pair_idx+1];
    return ans;
  }
  else if(fs != NUM_SUITS) { //flush
    ans.ranking = FLUSH;
    size_t copy_idx = 0;
    for(size_t i = 0; i < hand->n_cards;i++) {
      if (hand->cards[i]->suit == fs){
	ans.cards[copy_idx] = hand->cards[i];
	copy_idx++;
	if (copy_idx >=5){
	  break;
	}
      }
    }
    return ans;
  }
  else if(find_straight(hand,NUM_SUITS, &ans)) {     //straight
    ans.ranking = STRAIGHT;
    return ans;
  }
  else if (n_of_a_kind == 3) { //3 of a kind
    return build_hand_from_match(hand, 3, THREE_OF_A_KIND, match_idx);
  }
  else if (other_pair_idx >=0) {     //two pair
    assert(n_of_a_kind ==2);
    ans = build_hand_from_match(hand, 2, TWO_PAIR, match_idx);
    ans.cards[2] = hand->cards[other_pair_idx];
    ans.cards[3] = hand->cards[other_pair_idx + 1];
    if (match_idx > 0) {
      ans.cards[4] = hand->cards[0];
    }
    else if (other_pair_idx > 2) {  //if match_idx is 0, first pair is in 01
      //if other_pair_idx > 2, then, e.g. A A K Q Q
      ans.cards[4] = hand->cards[2];
    }
    else {       //e.g., A A K K Q
      ans.cards[4] = hand->cards[4];
    }
    return ans;
  }
  else if (n_of_a_kind == 2) {
    return build_hand_from_match(hand, 2, PAIR, match_idx);
  }
  return build_hand_from_match(hand, 0, NOTHING, 0);
}
