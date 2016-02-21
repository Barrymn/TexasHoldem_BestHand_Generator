//
//  cards.cpp
//  cards
//
//  Created by Ning Ma on 2/13/2014.
//  Copyright (c) 2014 Ning Ma. All rights reserved.
//

#include <iostream>
#include <vector>
#include <time.h>
using namespace std;

typedef pair<int,string>* card;

class Generator {
private:
  vector<card> *v;
public:
  Generator() {
    srand(time(NULL));
    v = new vector<card>;
  }
  
  ~Generator() {
    for (vector<card>::iterator it = this->v->begin(); it != this->v->end(); it++) {
      delete *it;
    }
    delete v;
  }
  
  card transform(int i) {
    card p = new pair<int,string>;
    p->first = i % 13 + 1;
    int color = i % 4;
    if (color == 0) {
      p->second = "spade";
    } else if (color == 1) {
      p->second = "club";
    } else if (color == 2) {
      p->second = "heart";
    } else {
      p->second = "diamond";
    }
    return p;
  }
  
  vector<card>* debug() {
    v->push_back(new pair<int,string>(1,"spade"));
    v->push_back(new pair<int,string>(7,"heart"));
    v->push_back(new pair<int,string>(3,"diamond"));
    v->push_back(new pair<int,string>(4,"spade"));
    v->push_back(new pair<int,string>(5,"heart"));
    v->push_back(new pair<int,string>(12,"spade"));
    v->push_back(new pair<int,string>(13,"diamond"));
    v->push_back(new pair<int,string>(8,"heart"));
    v->push_back(new pair<int,string>(8,"club"));
    
    // output
    cout << "9 random cards generated:" << endl;
    for (vector<card>::iterator it = this->v->begin(); it != this->v->end(); it++) {
      cout << (*it)->first << " " << (*it)->second << endl;
    }
    
    return v;
  }
  
  vector<card>* getCards() {
    int a[9];
    int size_a = 0;
    bool found = false;
    
    while(this->v->size() < 9) {
      int i = rand() % 52;
      // check if i is already generated
      for (int j = 0; j < size_a; j++) {
        if (a[j] == i) {
          found = true;
          break;
        }
      }
      
      if (found == false) {
        // not generated
        a[size_a] = i;
        size_a++;
        v->push_back(this->transform(i));
      } else {
        // if already generated,  reset it
        found = false;
      }
    }
    
    // output
    cout << "9 random cards generated:" << endl;
    for (vector<card>::iterator it = this->v->begin(); it != this->v->end(); it++) {
      cout << (*it)->first << " " << (*it)->second << endl;
    }
    return v;
  }
};



vector<card>* findStraight(vector<card>* vop){
  vector<card>* output = new vector<card>;
  int n[14];
  // initialize
  for(int i=0; i<14; i++) {
    n[i] = 0;
  }
  for(int i=0; i<vop->size(); i++){
    n[vop->at(i)->first]++;
  }//counting sort algorithm
  
  int counter = 0; // count straight
  int minInStraight = 0;
  for(int i=13; i>0; i--){
    if(n[i] > 0){
      counter++;
      if(counter >= 5){
        if(minInStraight < i){
          minInStraight = i;
        }
      }
      if(counter == 4 && i == 10 && n[1] > 0){
        minInStraight = 10;
        break;
      }
    }
    else{
      counter = 0;
    }
  }
  
  if(counter >= 5){
    for(int i = minInStraight; i<=minInStraight+5; i++){
      for(int j = 0; j<9; j++){
        if(vop->at(j)->first == i){
          output->push_back(vop->at(j));
          break;
        }
      }
    }
    return output;
  }
  else if(counter == 4 && minInStraight == 10){
    for(int i = minInStraight; i<=minInStraight+4; i++){
      for(int j = 0; j<9; j++){
        if(vop->at(j)->first == i){
          output->push_back(vop->at(j));
          break;
        }
      }
    }
    for(int i = 0; i<9; i++){
      if(vop->at(i)->first == 1){
        output->push_back(vop->at(i));
        break;
      }
    }
    return output;
  }
  else{
    delete output;
    return NULL;
  }
}// return the largest straight if we have



vector<card>* findFullHouse(vector<card>* vop){
  vector<card>* output = new vector<card>;
  int n[14];
  // initialize
  for(int i=0; i<14; i++) {
    n[i] = 0;
  }
  for(int i=0; i<9; i++){
    n[vop->at(i)->first]++;
  }//counting sort algorithm
  
  int maxThree = 0;
  int maxPair = 0;
  for(int i=0; i<14; i++){
    if(n[i] == 3){
      if(maxThree < i){
        maxThree = i;
      }
    }
  }
  for(int i=13; i>0; i--){
    if(n[i] >= 2 && i != maxThree){
      if(maxPair < i){
        maxPair = i;
        break;
      }
    }
  }
  
  if(maxThree == 0 || maxPair == 0){
    return NULL;
  }
  for(int j = 0; j<9; j++){
    if(vop->at(j)->first == maxThree){
      output->push_back(vop->at(j));
    }
  }
  
  for(int j = 0; j<9 && output->size()<=5; j++){
    if(vop->at(j)->first == maxPair){
      output->push_back(vop->at(j));
    }
  }
  
  
  if(output->size() > 1){
    return output;
  }
  else{
    delete output;
    return NULL;
  }
}//find all threes if we have



vector<card>* findFour(vector<card>* vop){
  vector<card>* output = new vector<card>;
  int n[14];
  // initialize
  for(int i=0; i<14; i++) {
    n[i] = 0;
  }
  for(int i=0; i<9; i++){
    n[vop->at(i)->first]++;
  }//counting sort algorithm
  
  int maxFour = 0;
  
  for(int i=0; i<14; i++){
    if(n[i] == 4){
      if(maxFour < i){
        maxFour = i;
      }
    }
  }
  
  if(maxFour == 0){
    return NULL;
  }
  
  for(int j = 0; j<9; j++){
    if(vop->at(j)->first == maxFour){
      output->push_back(vop->at(j));
    }
  }
  
  int k = 0;
  for(int i=13; i>0; i--){
    if(n[i] > 0 && i != maxFour){
      for(int j=0; j<9; j++){
        if(vop->at(j)->first == i){
          output->push_back(vop->at(j));
          break;
        }
      }
      break;
    }
  }
  
  if(output->size() > 1){
    return output;
  }
  else{
    delete output;
    return NULL;
  }
}//find all Fours and one if we have

vector<card>* findThree(vector<card>* vop){
  vector<card>* output = new vector<card>;
  int n[14];
  // initialize
  for(int i=0; i<14; i++) {
    n[i] = 0;
  }
  for(int i=0; i<9; i++){
    n[vop->at(i)->first]++;
  }//counting sort algorithm
  
  int maxThree = 0;
  
  for(int i=0; i<14; i++){
    if(n[i] == 3){
      if(maxThree < i){
        maxThree = i;
      }
    }
  }
  
  if(maxThree == 0){
    return NULL;
  }
  
  for(int j = 0; j<9; j++){
    if(vop->at(j)->first == maxThree){
      output->push_back(vop->at(j));
    }
  }
  
  int k = 0;
  for(int i=13; i>0&&k<2; i--){
    if(n[i] > 0 && i != maxThree){
      k++;
      for(int j=0; j<9; j++){
        if(vop->at(j)->first == i){
          output->push_back(vop->at(j));
          break;
        }
      }
    }
  }
  
  if(output->size() > 1){
    return output;
  }
  else{
    delete output;
    return NULL;
  }
}// Find three of a kind



vector<card>* findTwoPair(vector<card>* vop){
  vector<card>* output = new vector<card>;
  int n[14];
  // initialize
  for(int i=0; i<14; i++) {
    n[i] = 0;
  }
  for(int i=0; i<9; i++){
    n[vop->at(i)->first]++;
  }//counting sort algorithm
  
  int maxPair1 = 0;
  int maxPair2 = 0;
  for(int i=0; i<14; i++){
    if(n[i] == 2){
      if(maxPair1 < i){
        maxPair1 = i;
      }
    }
  }
  n[maxPair1] = 0;
  for(int i=0; i<14; i++){
    if(n[i] == 2){
      if(maxPair2 < i){
        maxPair2 = i;
      }
    }
  }
  if(maxPair1 == 0 || maxPair2 == 0){
    return NULL;
  }
  
  for(int j = 0; j<9; j++){
    if(vop->at(j)->first == maxPair1){
      output->push_back(vop->at(j));
    }
  }
  for(int j = 0; j<9; j++){
    if(vop->at(j)->first == maxPair2){
      output->push_back(vop->at(j));
    }
  }
  
  for(int i=13; i>0; i--){
    if(n[i] > 0 && i != maxPair1 && i != maxPair2){
      for(int j=0; j<9; j++){
        if(vop->at(j)->first == i){
          output->push_back(vop->at(j));
          break;
        }
      }
      break;
    }
  }
  
  if(output->size() > 1){
    return output;
  }
  else{
    delete output;
    return NULL;
  }
}



vector<card>* findPair(vector<card>* vop){
  vector<card>* output = new vector<card>;
  int n[14];
  // initialize
  for(int i=0; i<14; i++) {
    n[i] = 0;
  }
  for(int i=0; i<9; i++){
    n[vop->at(i)->first]++;
  }//counting sort algorithm
  
  int maxPair = 0;
  
  for(int i=0; i<14; i++){
    if(n[i] == 2){
      if(maxPair < i){
        maxPair = i;
      }
    }
  }
  
  if(maxPair == 0){
    return NULL;
  }
  
  for(int j = 0; j<9; j++){
    if(vop->at(j)->first == maxPair){
      output->push_back(vop->at(j));
    }
  }
  
  int k = 0;
  for(int i=13; i>0 && k<3; i--){
    if(n[i] > 0 && i != maxPair){
      k++;
      for(int j=0; j<9; j++){
        if(vop->at(j)->first == i){
          output->push_back(vop->at(j));
          break;
        }
      }
    }
  }
  
  if(output->size() > 1){
    return output;
  }
  else{
    delete output;
    return NULL;
  }
}



vector<card>* findHighCard(vector<card>* vop){
  vector<card>* output = new vector<card>;
  int n[14];
  // initialize
  for(int i=0; i<14; i++) {
    n[i] = 0;
  }
  for(int i=0; i<9; i++){
    n[vop->at(i)->first]++;
  }//counting sort algorithm
  
  int k=0;
  for(int i=13; i>0&&k<5; i--){
    if(n[i] > 0){
      k++;
      for(int j=0; j<9; j++){
        if(vop->at(j)->first == i){
          output->push_back(vop->at(j));
          break;
        }
      }
    }
  }
  
  if(output->size() > 1){
    return output;
  }
  else{
    delete output;
    return NULL;
  }
}

vector<card>* findFiveFlush(vector<card>* vop){
  vector<card>* output = new vector<card>;
  int n[14];
  // initialize
  for(int i=0; i<14; i++) {
    n[i] = 0;
  }
  for(int i=0; i<vop->size(); i++){
    n[vop->at(i)->first]++;
  }//counting sort algorithm
  
  int k=0;
  for(int i=13; i>0&&k<5; i--){
    if(n[i] > 0){
      k++;
      for(int j=0; j<9; j++){
        if(vop->at(j)->first == i){
          output->push_back(vop->at(j));
          break;
        }
      }
    }
  }
  
  if(output->size() > 1){
    return output;
  }
  else{
    delete output;
    return NULL;
  }
}



vector<card>* findFlush(vector<card>* cards) {
  
  vector<card>* retval = new vector<card>;
  // make a shallow copy
  for (vector<card>::iterator it = cards->begin(); it != cards->end(); it++) {
    retval->push_back(*it);
  }
  
  // use Moore's algorithm to find the majority element
  string major = retval->at(0)->second;
  int count = 1;
  
  for (vector<card>::iterator it = ++retval->begin(); it != retval->end(); it++) {
    if (major.compare((*it)->second) == 0) {
      count++;
    }
    else {
      count--;
    }
    if (count == 0) {
      major = (*it)->second;
      count=1;
    }
  }
  
  for (vector<card>::iterator it = retval->begin(); it != retval->end(); it++) {
    if (major.compare((*it)->second) != 0) {
      retval->erase(it);
      it--;
    }
  }
  // check if major is majority element
  if (retval->size() >= 5) {
    return retval;
  } else {
    delete retval;
    return NULL;
  }
}

void output(vector<card>* v, string type){
  cout << endl;
  cout << type << ":" << endl;
  for (vector<card>::iterator it = v->begin(); it != v->end(); it++) {
    cout << (*it)->first << " " << (*it)->second << endl;
  }
}

int main()
{
  
  Generator* g = new Generator();
  vector<card> *v = g->getCards();
  vector<card>* flush = findFlush(v);
  if(flush != NULL){
    vector<card>* straightFlush = findStraight(flush);
    if(straightFlush != NULL){
      if (straightFlush->at(4)->first == 1) {
        output(straightFlush, "Royal Flush");
      } else {
        output(straightFlush, "Straight Flush");
      }
      delete straightFlush;
      return 0;
    }
  }
  vector<card>* Four = findFour(v);
  if(Four != NULL){
    output(Four, "Four of a Kind");
    delete Four;
    return 0;
  }
  vector<card>* FullHouse = findFullHouse(v);
  if(FullHouse != NULL){
    output(FullHouse, "Full House");
    delete FullHouse;
    return 0;
  }
  if (flush != NULL) {
    vector<card>* FiveFlush = findFiveFlush(flush);
    output(FiveFlush, "Flush");
    delete FiveFlush;
    delete flush;
    return 0;
  }
  vector<card>* straight = findStraight(v);
  if(straight != NULL){
    output(straight, "Straight");
    delete straight;
    return 0;
  }
  vector<card>* ThreeOfKind = findThree(v);
  if(ThreeOfKind != NULL){
    output(ThreeOfKind, "Three of a Kind");
    delete ThreeOfKind;
    return 0;
  }
  vector<card>* TwoPair = findTwoPair(v);
  if(TwoPair != NULL){
    output(TwoPair, "Two Pairs");
    delete TwoPair;
    return 0;
  }
  vector<card>* pair = findPair(v);
  if(pair != NULL){
    output(pair, "One Pair");
    delete pair;
    return 0;
  }
  vector<card>* highCard = findHighCard(v);
  if(highCard != NULL){
    output(highCard, "High Card");
    delete highCard;
    return 0;
  }
  delete g;
}
