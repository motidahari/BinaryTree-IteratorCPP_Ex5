/**
  * BinaryTree Tests
  * Create a BinaryTree
  * CPP course, Ariel University
  * Created by: Moti Dahari
  * https://github.com/motidahari
  */
  
#pragma once
#include <iostream>
#include <list>
#include <map>
#include <stack>
#include <vector>
#include <unordered_set>
namespace ariel {

    enum iterator_type { postOrder, inOrder, preOrder };   

    template<typename T> class BinaryTree {
        struct Node {
            T val;
            Node *right, *left;
            Node(T val): val(val), right(nullptr), left(nullptr){}
        };
        
        private:
            Node* _root; 
        public:
            /**
             * BinaryTree - A constructor that initializes the main vertex to the value nullptr
            */
            BinaryTree() {
                _root = nullptr;
            }
            /**
             * ~BinaryTree - Erasing the memory of the tree
            */
            ~BinaryTree(){
                delTree();
            }
            /**
             * BinaryTree - Erasing the memory of the old tree and building the new tree Deep copy
             * @param: const BinaryTree& someTree - The new tree
            */
            BinaryTree(const BinaryTree& someTree){   
                delTree();
                getCopyOfTree(someTree);
            }
            /**
             * BinaryTree - Erasing the memory of the old tree and building the new tree shallow copy
             * @param: BinaryTree& someTree - The new tree
            */
            BinaryTree(BinaryTree&& someTree) noexcept {
                _root = someTree._root;
                someTree._root = nullptr;
            }
            /**
             * operator= - Erasing the memory of the old tree and building the new tree Deep copy
             * @param: const BinaryTree& someTree - The new tree
             * @return: Returns refernce of BinaryTree
            */
            BinaryTree& operator=(const BinaryTree& someTree){
                if(this != &someTree){
                    delTree();
                    getCopyOfTree(someTree);
                }
                return *this;
            }
            /**
             * operator= - Erasing the memory of the old tree and building the new tree shallow copy
             * @param: BinaryTree&& someTree - 
             * @return: Returns refernce of Node
            */
            BinaryTree &operator=(BinaryTree&& someTree) noexcept{
                _root = someTree._root;
                someTree._root = nullptr;
                return *this;
            }

            /**
             * delTree - Function for erasing all the wood present from memory
            */
            void delTree(){
                if(_root){return;}
                for (auto it = begin(); it != end();++it){
                    Node *temp = it.getCurr();
                    delete temp;
                }
            }
            /**
             * copyTree - Deep copy for the tree
             * @param: Node* node - In the first run it is the value of the old tree from which we want to copy the organs
             * @param: Node* someNode - The organs in the old tree
            */
            void copyTree(Node* node, Node* someNode){
                if(someNode->left){
                    node->left = new Node(someNode->left->val);
                    copyTree(node->left, someNode->left);
                }
                if(someNode->right){
                    node->right = new Node(someNode->right->val);
                    copyTree(node->right, someNode->right);
                }
            }
            /**
             * getCopyOfTree - Check if the main vertex is not null and create the tree duplication
             * @param: const BinaryTree& tree - The tree we want to copy
            */
            void getCopyOfTree(const BinaryTree& tree){
                if(!tree._root){return;}
                _root = new Node(tree._root->val);
                copyTree(_root, tree._root);
            }
            
            /**
             * add_root - add the head of the tree
             * @param: root - The head of the tree
             * @return: Returns refernce of BinaryTree
            */
            BinaryTree<T>& add_root(const T root) {
                if(_root == nullptr){
                    _root = new Node(root);  
                }else{
                    _root->val = root;
                }
                // std::cout << "new root = " << _root->val << " is son of (null)"<< std::endl;
                return *this; 
            }

            /**
             * add_right - add the right child to some node in the tree
             * @param: node - A Vertex that should be in the graph (the father)
             * @param: rChild - A Vertex we want to connect from right side
             * @return: Returns refernce of BinaryTree
            */
            BinaryTree& add_right(const T node, const T rChild){
                Node* temp = getNode(node);
                if(temp == nullptr){
                    // std::string msg = "the vertex is not exist";
                    delTree();
                    printError("the vertex is not exist");
                }
                if(temp->right == nullptr){
                    // std::cout << "the right child it was null"<< std::endl;
                    temp->right = new Node(rChild);
                }else{
                    // std::cout << "the right child it was"<<temp->right->val << std::endl;
                    temp->right->val = rChild;
                }
                // std::cout << "new vertex = (" << temp->right->val << ") is right son of (" << temp->val << ")"<<std::endl;
                return *this;
            }

            /**
             * add_right - add the left child to some node in the tree
             * @param: node - A Vertex that should be in the graph (the father)
             * @param: rChild - A Vertex we want to connect from left side
             * @return: Returns refernce of BinaryTree
            */
            BinaryTree& add_left(const T node, const T lChild){
                Node* temp = getNode(node);
                if(temp == nullptr){
                    delTree();
                    printError("the vertex is not exist");
                }
                if(temp->left == nullptr){
                    // std::cout << "the right child it was null "<< std::endl;
                    // std::cout << "the value of temp is: "<< temp->val << std::endl;
                    temp->left = new Node(lChild);
                }else{
                    // std::cout << "the right child it was "<<temp->left->val << std::endl;
                    temp->left->val = lChild;
                }
                // std::cout << "new vertex = (" << temp->left->val << ") is left son of (" << temp->val << ")"<< std::endl;
                return *this;
            }

            
            /**
             * getNode - A function that searches for a vertex by its value, runs on the tree and searches for the vertex
             * @param: T value - The value of the vertex we want to search for
             * @return: Returns refernce of Node if it is found, otherwise nullptr returns
            */
            Node* getNode(T value){
                if(_root){
                    for (auto it = begin_inorder(); it != end_inorder(); ++it){
                        if (*it == value){
                            return it.getCurr();
                        }
                    }
                }
                return nullptr;
            }


            /**
             * hasLeft - Check if there is a left child
             * @param: Node *node - A vertex we would like to test on
             * @return: True if there is, otherwise False
            */
            bool hasLeft(Node* node){
                return node->left != nullptr;
            }

            /**
             * hasRight - Check if there is a right child
             * @param: Node *node - A vertex we would like to test on
             * @return: True if there is, otherwise False 
            */
            bool hasRight(Node* node){
                return node->right != nullptr;
            }

             /**
             * printError - Error throwing function
             * @param: const std::string& msg - Error message
            */
            void printError(const std::string& msg){
                // std::cout << msg << std::endl;
               throw std::invalid_argument(msg);
            }
            
            
             /**
             * printTree - Function for printing the tree
             * @return: std::string - A string that represents all the vertices in the graph and their children
            */
            std::string printTree(){
                printBinaryTreeVisualy(this->_root);
                print(this->_root);
                return "";
            }

             /**
             * print - A recursive function that prints each vertex and its two children
             * @param: Node* node - Starts at the parent vertex of the tree and changes as it runs
             */
            void print(Node* node) {
                if(node == nullptr) {
                    return;
                }
                std::cout << "(" << node->val << ") -> ";
                if(node->left == nullptr){
                    std::cout << "(L-null,";
                }else{
                    std::cout << "("<< node->right->val << ", ";
                }
                if(node->right == nullptr){
                    std::cout << "R-null)" << std::endl;
                }else{
                    std::cout << node->left->val << ")" << std::endl;

                }
                print(node->right);
                print(node->left);
            }

            /**
             * printBinaryTreeVisualy - A recursive function that graphically prints the tree
             * @param: Node* _root - Begins at the parent vertex of the tree
             */
            void printBinaryTreeVisualy(Node* _root){
                std::cout << "================================" << std::endl;
                printVisualyTree(_root, 0);
                std::cout << "================================" << std::endl;
            }

             /**
             * printVisualyTree - A recursive function that prints the tree graphically
             * @param: Node* root - Starts at the parent vertex of the tree and changes as it runs
             * @param: int level - The level of the tree where we are
             */
            void printVisualyTree(Node* root, int level){
                if(root == nullptr){return;}
                printVisualyTree(root->right, level+1);
                if(level != 0){
                    for(int i=0;i<level-1;i++){
                        std::cout << "|\t";
                    }
                    std::cout << "|-------" << root->val << std::endl;
                }else{
                    std::cout << root->val << std::endl;
                }
                printVisualyTree(root->left, level+1);
            }


            /**
             * operator<< - print the tree
             * @return: out - ostream
            */
            friend std::ostream& operator<<(std::ostream& out, BinaryTree<T> &binaryTree) {
                return out << binaryTree.printTree() << std::endl;
            }

        class iterator {
            public:
                Node* curr;
		        /**
                 * operator* - A function that returns the refernce of the value 
                 * @return: T& - reference to a value within the vertex
                */
               T& operator*() const {
		        	return curr->val;
		        }

		        /**
                 * operator-> - The function return a pointer of the value within the vertex
                 * @return: T* - Pointer of the value
                */
               T* operator->() const {
		        	return &(curr->val);
		        }

		        /**
                 * operator== - Equality test between two organs
                 * @param: const iterator& otherList - Value for equality testing
                 * @return: Returns true if equal, otherwise false
                */
               bool operator==(const iterator& otherList) const {
		        	return (curr == otherList.curr);
		        }

		        /**
                 * operator!= - An inequality test between two organs
                 * @param: const iterator& otherList - Value for equality testing
                 * @return: Returns false if equal, otherwise true 
                */
               bool operator!=(const iterator& otherList) const {
		        	return !(curr == otherList.curr);
		        }
                /**
                 * getCurr - A function that returns the current vertex
                 * @return: curr - Current vertex
                */
               Node* getCurr(){
                    return curr;
                }
        };



        class preorder_iterator : public iterator{
            private:
                std::stack<Node*> list;

            public:
                /**
                 * getCurr - A function that returns the current vertex
                 * @return: curr - Current vertex
                */
                preorder_iterator(Node* _root = nullptr){
                    if(_root == nullptr){
                        iterator::curr = nullptr;
                        return;
                    }
                    list.push(_root);
                    iterator::curr = list.top();
                }

		        /**
                 * operator++ -Function for advancing to the next limb in the list 
                 * (the function is with the plus before the limb, i.e. we will return the limb after the promotion)
                 * @return: The next organ on the list
                */
               preorder_iterator& operator++() {
                    if(list.empty()){
                        iterator::curr = nullptr;
                    }else{
                        Node* node = iterator::curr;
                        list.pop();
                        if(node->right != nullptr){
                            list.push(node->right);
                        }
                        if(node->left != nullptr){
                            list.push(node->left);
                        }
                        if(!(list.empty())){
                           iterator::curr = list.top(); 
                        }else{
                            iterator::curr = nullptr;
                        }
                    }
		        	return *this;
		        }

		        /**
                 * operator++ -Function for advancing to the next limb in the list 
                 * (the function is with the plus after the limb, i.e. we will return the limb before the promotion)
                 * @param: int - This is the plus after the limb
                 * @return: The next organ on the list
                */
               preorder_iterator operator++(int){
                    preorder_iterator it = *this;
                    if(list.empty()){
                        iterator::curr = nullptr;
                    }else{
                        Node* node = iterator::curr;
                        list.pop();
                        if(node->right != nullptr){
                            list.push(node->right);
                        }
                        if(node->left != nullptr){
                            list.push(node->left);
                        }
                        if(!(list.empty())){
                           iterator::curr = list.top(); 
                        }else{
                            iterator::curr = nullptr;
                        }
                    }
		        	return it;
		        }

        };
        class inorder_iterator : public iterator{
             private:
                std::stack<Node*> list;
            public:
                /**
                 * inorder_iterator - A constructor that initializes the initial organ in the list
                */
               inorder_iterator(Node* _root = nullptr){
                    while(_root != nullptr){
                        list.push(_root);
                        _root = _root->left;
                    }
                    if(list.empty()){
                        iterator::curr = nullptr;
                    }else{
                        iterator::curr = list.top();
                        list.pop();
                    }
                }

                /**
                 * operator++ -Function for advancing to the next limb in the list 
                 * (the function is with the plus before the limb, i.e. we will return the limb after the promotion)
                 * @return: The next organ on the list
                */
               inorder_iterator& operator++() {
                    if(list.empty() && iterator::curr == nullptr){
                        iterator::curr = nullptr;
                    }else{
                        if(iterator::curr->right == nullptr){
                            if(!list.empty()){
                                iterator::curr = list.top();
                                list.pop();
                            }else{
                                iterator::curr = nullptr;
                            }
                        }else{
                            iterator::curr = iterator::curr->right;
                            while(iterator::curr != nullptr){
                                list.push(iterator::curr);
                                iterator::curr = iterator::curr->left;
                            }
                            iterator::curr = list.top();
                            list.pop();
                        }
                    }
		        	return *this;
		        }

		        /**
                 * operator++ -Function for advancing to the next limb in the list 
                 * (the function is with the plus after the limb, i.e. we will return the limb before the promotion)
                 * @param: int - This is the plus after the limb
                 * @return: The next organ on the list
                */
               inorder_iterator operator++(int){
                    inorder_iterator it= *this;
                    if(list.empty() && iterator::curr == nullptr){
                        iterator::curr = nullptr;
                    }else{
                        if(iterator::curr->right == nullptr){
                            if(!list.empty()){
                                iterator::curr = list.top();
                                list.pop();    
                            }else{
                                iterator::curr = nullptr;
                            }
                        }else{
                            iterator::curr = iterator::curr->right;
                            while(iterator::curr != nullptr){
                                list.push(iterator::curr);
                                iterator::curr = iterator::curr->left;
                            }
                            iterator::curr = list.top();
                            list.pop();
                        }
                    }
		        	return it;
		        }
        };


        class postorder_iterator : public iterator{
             private:
                Node* temp;
                std::unordered_set<Node*> list;
            public:
                /**
                 * postorder_iterator - A constructor that initializes the initial organ in the list
                */
                postorder_iterator(Node* _root = nullptr){
                    if(_root == nullptr){
                        iterator::curr = nullptr;
                    }else{
                        temp = _root;
                        buildList(_root);
                    }
                }

		        /**
                 * operator++ -Function for advancing to the next limb in the list 
                 * (the function is with the plus before the limb, i.e. we will return the limb after the promotion)
                 * @return: The next organ on the list
                */
                postorder_iterator& operator++() {
                    Node* node = temp;
                    if(temp && list.find(temp) == list.end()){
                        buildList(node);
                    }else{
                        iterator::curr = nullptr;
                    }
		        	return *this;
		        }

		        /**
                 * operator++ -Function for advancing to the next limb in the list 
                 * (the function is with the plus after the limb, i.e. we will return the limb before the promotion)
                 * @param: int - This is the plus after the limb
                 * @return: The next organ on the list
                */
               postorder_iterator operator++(int) {
		        	postorder_iterator it = *this;
                    Node* node = temp;
                    if(temp && list.find(temp) == list.end()){
                        buildList(node);
                    }else{
                        iterator::curr = nullptr;
                    }
		        	return it;
		        }
                
                /**
                 * buildList -Running on the tree and building our list
                 * @param: Node* node - In the first run it is our main vertex
                */ 
               void buildList(Node* node) {
                    while (temp != nullptr && list.find(temp) == list.end()) {
                        if (temp->left != nullptr && list.find(temp->left) == list.end()){
                            temp = temp->left;
                        }else if (temp->right && list.find(temp->right) == list.end()){
                            temp = temp->right;
                        }else {
                            iterator::curr = temp;
                            list.insert(temp);
                            temp = node;
                            break;   
                        }
                    }
                }
        };


             /**
             * begin - get iterator as normal run like inOrder
             * @return: iterator - list of the vertex in the graph
            */
            inorder_iterator begin() const{
                return inorder_iterator{_root};
            }

            /**
             * begin_inorder - get iterator as inOrder
             * @return: iterator - list of the vertex in the graph
            */
            inorder_iterator begin_inorder() const{
                return inorder_iterator{_root};
            }
            
            /**
             * begin_postorder - get iterator as postorder
             * @return: iterator - list of the vertex in the graph
            */
            postorder_iterator begin_postorder() const{
                return postorder_iterator{_root};
            }

            /**
             * begin_preorder - get iterator as preorder
             * @return: iterator - list of the vertex in the graph
            */
            preorder_iterator begin_preorder() const{
                return preorder_iterator{_root};
            }

            /**
             * end - get iterator as normal run like inOrder
             * @return: iterator - list of the vertex in the graph
            */
            inorder_iterator end() const{
                return inorder_iterator{nullptr};
            }
            /**
             * end_inorder - get iterator as inOrder
             * @return: iterator - list of the vertex in the graph
            */
            inorder_iterator end_inorder() const{
                return inorder_iterator{nullptr};
            }

            /**
             * end_preorder - get iterator as preorder
             * @return: iterator - list of the vertex in the graph
            */
            preorder_iterator end_preorder() const{
                return preorder_iterator{nullptr};
            }

            /**
             * end_postorder - get iterator as postorder
             * @return: iterator - list of the vertex in the graph
            */
            postorder_iterator end_postorder() const{
                return postorder_iterator{nullptr};
            } 
    };
};