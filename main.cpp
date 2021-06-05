/**
  * BinaryTree - main
  * Create a BinaryTree
  * CPP course, Ariel University
  * Created by: Moti Dahari
  * https://github.com/motidahari
  */

#include "sources/BinaryTree.hpp"
#include <fstream>
#include <sstream>
#include <iostream>
#include <stdexcept>
#include <vector>
#include <stack>
#include <queue>


using namespace std;
using namespace ariel;


const int max_rand = 1000;
const int div_factor = 100;

double NextDouble() {
    return (double)((unsigned int)rand() % max_rand) / div_factor;
}

int NextInt() {
    return (rand() % max_rand);
}

bool RandomBool() {
    return rand() % 2 == 0;
}
BinaryTree<int> randTree(int size) {
  BinaryTree<int> tree_of_ints;
  std::stack<int> list;
  int parent = NextInt();
  queue<int> q;
  q.push(parent);

  tree_of_ints.add_root(parent);
  for (size_t i = 0; i < size; i++){
    parent = q.front();
    q.pop();
    int left = NextInt();
    int right = NextInt();
    q.push(left);
    q.push(right);

    tree_of_ints.add_left(parent,left);
    tree_of_ints.add_right(parent,right);
  }
  return tree_of_ints;
}



/* 
              50
           /     \
          30      70
         /  \    /  \
        20   40  60   80
*/
int main(){



  BinaryTree<int> randTreeOfInt = randTree(100);
  cout << randTreeOfInt;

  BinaryTree<int> tree_of_ints;
  tree_of_ints.add_root(50)
  .add_left(50, 30).add_right(50, 70)
  .add_left(30, 20).add_right(30, 40)
  .add_left(70, 60).add_right(70, 80);

  cout << tree_of_ints;
  cout << "postorder =  \n" ;
  for (auto it=tree_of_ints.begin_postorder(); it!=tree_of_ints.end_postorder(); ++it) {
    cout << (*it) << " " ;
  }  // prints: 20 40 30 60 80 70 50
  cout << " \n" ;
  
  cout << "inorder =  \n" ;
  for (auto it=tree_of_ints.begin_inorder(); it!=tree_of_ints.end_inorder(); ++it) {
    cout << (*it) << " " ;
  }  // prints: 20 30 40 50 60 70 80 
  cout << " \n" ;

  cout << "preorder =  \n" ;
  for (auto it=tree_of_ints.begin_preorder(); it!=tree_of_ints.end_preorder(); ++it) {
    cout << (*it) << " " ;
  }  // prints: 50 30 20 40 70 60 80
  cout << " \n" ;
  


  BinaryTree<int> tree_of_ints2;
  tree_of_ints2.add_root(1)
  .add_left(1, 9)      // Now 9 is the left child of 1
  .add_left(9, 4)      // Now 4 is the left child of 9
  .add_right(9, 5)     // Now 5 is the right child of 9
  .add_right(1, 3)     // Now 3 is the right child of 1
  .add_left(1, 2);     // Now 2 is the left child of 1, instead of 9 (the children of 9 remain in place)

  cout << tree_of_ints2 << endl;  /* Prints the tree in a reasonable format. For example:
        1
        |--------|
        2        3
        |---|
        4   5
  */
   cout << "\npreorder =  \n" ;

  for (auto it=tree_of_ints2.begin_preorder(); it!=tree_of_ints2.end_preorder(); ++it) {
    cout << (*it) << " " ;
  }  // prints: 1 2 4 5 3
    cout << "\ninorder =  \n" ;

  for (auto it=tree_of_ints2.begin_inorder(); it!=tree_of_ints2.end_inorder(); ++it) {
    cout << (*it) << " " ;
  }  // prints: 4 2 5 1 3 
    cout << "\npostorder = \n" ;

  for (auto it=tree_of_ints2.begin_postorder(); it!=tree_of_ints2.end_postorder(); ++it) {
    cout << (*it) << " " ;
  }  // prints: 4 5 2 3 1
  cout << std::endl;
    return 0;
  }
    



/*

clear && clang++-9 -std=c++2a -o main main.cpp && ./main
clear && clang++-9 -std=c++2a -o main main.cpp && ./main > output.txt

*/