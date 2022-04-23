#include "frontier_queue.hpp"
#include <iostream>

// TODO implement the member functions here

template <typename T>
State<T> frontier_queue<T>::pop() {
  //Put first element last and return it
  swap(0, queue.size()-1);
  State<T> buffer = queue.back();
  queue.pop_back();

  //Traverse list from root to different nodes and swap wrong values to put everythin in place
  std::size_t i=1;
  while( (i*2)-1 < queue.size() ){
    if(queue[(i*2)-1].getFCost() < queue[i-1].getFCost()){
      swap((i*2)-1, i-1);
    }
    else if((i*2)<queue.size() && (queue[(i*2)].getFCost() < queue[i-1].getFCost())){
      swap((i*2), i-1);
    }
    else{return buffer;}
  }
  return buffer;

}

template <typename T>
void frontier_queue<T>::push(const T &p, std::size_t cost, std::size_t heur) {
  //Add to back of list
  queue.push_back(State<T>(p, cost, heur));

  //Traverse list, going to each parent to compare if better fscore. If so, swap
  std::size_t i=queue.size();
  while(i/2>=1){
    if( queue[(i/2)-1].getFCost() > queue[i-1].getFCost()){
      swap( (i/2)-1 , i-1 );
      i = i/2;
    }
    else{return;}
  }

}

template <typename T>
bool frontier_queue<T>::empty() {

  return queue.size()==0;
}

template <typename T> 
bool frontier_queue<T>::contains(const T &p) {

  //Go through list and determine if item in traversing between nodes
  for(std::size_t i=0;i<queue.size();i++){
    if(queue[i].getValue()==p){
      return true;
    }
  }
  return false;

}

template <typename T>
void frontier_queue<T>::replaceif(const T &p, std::size_t cost) {

  //Look for value, and if it finds, update value, then push pull
  for(std::size_t i=0;i<queue.size();i++){
    if(queue[i].getValue()==p){
      if(queue[i].getPathCost()>cost){
        queue[i].updatePathCost(cost);
        //Go through and sort it like a psedo sorted list
        for(std::size_t j=i-1;j>=0;j--){
          //Check for integer overflow
          if(i==0){return;}
          if(queue[j].getFCost()>queue[i].getFCost()){
            swap(i,j);
          }
        }
        return;
      }
    }
  }
  return;

}

template <typename T>
void frontier_queue<T>::swap(std::size_t index1, std::size_t index2){
  //Buffer swap
  State<T> buffer = queue[index1];
  queue[index1] = queue[index2];
  queue[index2] = buffer;

}

