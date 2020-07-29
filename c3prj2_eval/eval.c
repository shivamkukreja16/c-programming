#include "eval.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>


int card_ptr_comp(const void * vp1, const void * vp2) {
  const card_t * const * cp1 = vp1;
  const card_t * const * cp2 = vp2;
  if( (**cp1).value > (**cp2).value){ return -1;}
  else if( (**cp1).value == (**cp2).value){
    if((**cp1).suit >= (**cp2).suit){ return -1;}
    else { return 1;}
  }
  else if( (**cp1).value < (**cp2).value){ return 1;}
  return 0;
}

suit_t flush_suit(deck_t * hand) {
  if((*hand).n_cards >= 5){
    int i=0;
    int s_count=0, h_count=0, c_count=0, d_count=0;
    for(i=0; i<(*hand).n_cards; i++){
      if((*(*hand).cards[i]).suit == SPADES ){
	s_count++;}
      if((*(*hand).cards[i]).suit == HEARTS){
	h_count++;}
      if((*(*hand).cards[i]).suit == CLUBS ){
	c_count++;}
      if((*(*hand).cards[i]).suit == DIAMONDS ){
	d_count++;}
    }
    if(s_count >= 5){ return SPADES;}
    else if( h_count >=5 ){ return HEARTS;}
    else if( d_count >=5){ return DIAMONDS;}
    else if( c_count >=5){ return CLUBS;}
  }
  return NUM_SUITS;
}

unsigned get_largest_element(unsigned * arr, size_t n) {
  if((arr!=0) && (n!=0)){
    unsigned max = arr[0];
    size_t i;
    for(i=0; i<n; i++){
      if(max<=arr[i]){
	max = arr[i];
      }
    }
    return max;
  }
  return 0;
}

size_t get_match_index(unsigned * match_counts, size_t n,unsigned n_of_akind){
  unsigned i;
  for(i=0; i< n; i++){
    if(match_counts[i]==n_of_akind){ return i;}
  }
  // printf(" ERROR there is no n_of_kind in match_count\n");

  return 0;
}
ssize_t  find_secondary_pair(deck_t * hand,
			     unsigned * match_counts,
			     size_t match_idx) {
  size_t i, k=0;
  size_t j=match_idx;
  while(((j + 1) < (hand->n_cards))&&(hand->cards[j]->value == hand->cards[j+1]->value)){
    j++;
  };
  for(i=0; i<(hand->n_cards); i++){
    if( (match_idx <= i)&&( i<= j)){
      k++;
      continue;
    }
    if( match_counts[i] > 1){
      return i;
    }
  }

  return -1;
}

int  straight_starting_at( deck_t *hand, size_t index){
  int k = index;
  int count=1;
  if(index >= hand->n_cards - 4){ return 0;}
  while((((*(*hand).cards[k+1]).value) == (((*(*hand).cards[k]).value) - 1))||(((*(*hand).cards[k+1]).value) == ((*(*hand).cards[k]).value))){
    if((*(*hand).cards[k+1]).value == (*(*hand).cards[k]).value - 1){
      count++;
    }
    k++;
    if( k+1 >=  hand->n_cards){ break;}
  }
  if(count >= 5){ return 1;}
  return 0;
}

int is_there_ACE_low( deck_t *hand, size_t index){
  if(index >= hand->n_cards - 3){ return 0;}
  if( (hand->cards[index]->value) == 14){
    size_t k=index;
    for(int v=0; v<hand->n_cards; v++){
      if(hand->cards[v]->value == 5){
	k = v;
	break;
      }
    }
    if( k+1 >= hand->n_cards){ return 0;}
    if( k == index ){ return 0;}
    int count = 1;
    while(((hand->cards[k+1]->value) == ((hand->cards[k]->value) - 1))||(hand->cards[k]->value == hand->cards[k+1]->value)){
      if((hand->cards[k+1]->value) == (hand->cards[k]->value - 1)){
	count++;
      }
      k++;
      if( k+1 >= hand->n_cards){ break ;}
    }
    if(count >= 4){
      /*int count3=0;
	for(int v=0; v<4; v++){
	  if((hand->cards[v]->value) == 14){
	        count3++;
		        }
			}
			if(count3 >0){*/
      return -1;
    }
  }
  return 0;
}

// this function check if there is a straight starting at the position index and return 1 if there is and 0 if not.
int is_straight_at(deck_t * hand, size_t index, suit_t fs) {

  if(fs == NUM_SUITS){   // when fs is NUM_suits, we check for any straight
    if(straight_starting_at(hand,index)== 1){ return 1;}
    else{
      return is_there_ACE_low(hand,index);
    }
    return 0;
  }
  else{ // when fs is not NUM_SUITS, we check for a straight flush with fs
    if(hand->cards[index]->suit == fs){
      int count=1;
      int k=index;
      while(((hand->cards[k+1]->value) == ((hand->cards[k]->value) - 1))||((hand->cards[k+1]->value) == (hand->cards[k]->value))){
	card_t n_card = (*(*hand).cards[k+1]);
	card_t c_card = (*(*hand).cards[k]);
	if(n_card.suit==fs){
	  count++;
	}
	else if((n_card.value == c_card.value - 1)&&(!(n_card.suit == fs))){
	  if(k+2< hand->n_cards)
	    {
	      if((*(*hand).cards[k+2]).value != (*(*hand).cards[k+1]).value){
		break;
	      }
	    }
	}
	if(n_card.value == c_card.value){
	  card_t check_c;
	  check_c.value = n_card.value;
	  check_c.suit = fs;
	  if(deck_contains(hand, check_c)==0){
	    break;
	  }
	}
	k++;
	if( k+1 >=  hand->n_cards){ break;}
      }
      if(count >= 5){ return 1;}
      int count3=1000;
      for(int v=0; v<4; v++){
	if(((hand->cards[v]->value) == 14)&&(hand->cards[v]->suit == fs)){
	  count3=v;
	}
      }
      if(count3!= 1000){
	count3 = 1000;
	for(int v=0; v<hand->n_cards - 3;v++){
	  if((hand->cards[v]->value==5)&&(hand->cards[v]->suit==fs)){
	    count3 = v;
	  }
	}
	if(count3!=1000){
	  k = count3;
	  count =0;
	  while((((*(*hand).cards[k+1]).value) == (((*(*hand).cards[k]).value) - 1))||(((*(*hand).cards[k+1]).value) == ((*(*hand).cards[k]).value))){
	    card_t n_card = (*(*hand).cards[k+1]);
	    card_t c_card = (*(*hand).cards[k]);
	    if((n_card.value == c_card.value - 1)&&(n_card.suit==fs)){
	      count++;
	    }
	    k++;
	    if( k+1 >=  hand->n_cards){ break;}
	  }
	  if(count>=3){ return -1;}
	}
      }
    }
  }
  return 0;
}

hand_eval_t build_hand_from_match(deck_t * hand,
				  unsigned n,
				  hand_ranking_t what,
				  size_t idx) {

  hand_eval_t ans;
  size_t  i=0;
  for(i=0; i<5; i++){
    ans.cards[i] = hand->cards[i];
  }
  size_t p = n;
  ans.ranking = what;
  for(i=0; i<p; i++){
    size_t k = i + idx;
    ans.cards[i]= hand->cards[k];
  }
  if(n==4){
    if(idx != 0){
      ans.cards[4] = hand->cards[0];
    }
    else{
      ans.cards[4] = hand->cards[4];
    }
  }
  if(n==3){
    if(idx > 1){
      ans.cards[3] = hand->cards[0];
      ans.cards[4] = hand->cards[1];
    }
    else if(idx == 1){
      ans.cards[3] = hand->cards[0];
      ans.cards[4] = hand->cards[4];
    }
    else{
      ans.cards[3] = hand->cards[3];
      ans.cards[4] = hand->cards[4];
    }
  }
  if(n==2){
    if(idx > 2){
      ans.cards[2] = hand->cards[0];
      ans.cards[3] = hand->cards[1];
      ans.cards[4] = hand->cards[2];
    }
    else if(idx == 2){
      ans.cards[2] = hand->cards[0];
      ans.cards[3] = hand->cards[1];
      ans.cards[4] = hand->cards[4];
    }
    else if(idx == 1){
      ans.cards[2] = hand->cards[0];
      ans.cards[3] = hand->cards[3];
      ans.cards[4] = hand->cards[4];
    }
    else{
      ans.cards[2] = hand->cards[2];
      ans.cards[3] = hand->cards[3];
      ans.cards[4] = hand->cards[4];
    }
  }
  return ans;
}


int compare_hands(deck_t * hand1, deck_t * hand2) {
  qsort( hand1->cards, (*hand1).n_cards, sizeof(hand1->cards[0]), card_ptr_comp);
  qsort( hand2->cards, (*hand2).n_cards, sizeof(hand2->cards[0]), card_ptr_comp);
  hand_eval_t h1= evaluate_hand( hand1);
  hand_eval_t h2= evaluate_hand( hand2);
  if( h1.ranking <  h2.ranking ){ return 1;}
  else if( h1.ranking >  h2.ranking ){ return -1;}
  else {
    int i;
    for(i=0; i<5; i++){
      if((h1.cards[i]->value) > (h2.cards[i]->value)){ return 1;}
      if((h1.cards[i]->value)< (h2.cards[i]->value)){ return -1;}
    }
  }
  return 0;
}



//this function
//   allocates an array of unsigned ints with as
//      many elements as there are cards in the hand.
//      It then fills in this array with
//      the "match counts" of the corresponding cards.
//For example,
//   given
//        Ks Kh Qs Qh 0s 9d 9c 9h
//      This function would return
//        2  2  2  2  1  3  3  3
//   because there are 2 kings, 2 queens,
//  1 ten, and 3 nines.
unsigned * _get_match_counts(deck_t * hand){
  unsigned *match = malloc((hand->n_cards)*sizeof(*match));
  for(int p=0; p<hand->n_cards; p++){
    match[p]=1;
  }
  int count=1;
  size_t index=0;
  while(index<hand->n_cards - 1){
    int i=index;
    while(hand->cards[i]->value == hand->cards[i+1]->value){
      count++;
      i++;
      if(i + 1>=hand->n_cards){
	break;
      }
    }
    for(int k=index; k<(index + count); k++){
      match[k] = count;
    }
    index +=count;
    count = 1;
  }
  return match;
}


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
  unsigned * match_counts = _get_match_counts(hand);
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
