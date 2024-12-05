#include <iostream>
#include <vector>
#include <queue>

using namespace std;

class Tree {                                // Tree class
public:
    Tree(int w, char c){                    // Creates a tree with a character
        weight = w;
        character = c;
    };

    Tree(int w, Tree* t1, Tree* t2){        // Creates a tree with two branches
        weight = w;
        right = t1;
        left = t2;
    };

    ~Tree(){                                // Deletes the root node of the tree
        if (left != NULL){
            free(left);
        }
        if (right != NULL){
            free(right);
        }
    };

    int getWeight() {          
        return(weight);                     // Returns the weight of the tree
    };

    string printTree(vector<char>& bitString) {   // Print the components of the tree 
        if ((int)character > 96){
            
            for (char bit : bitString) {        // Adds the bit path so it can be printed out
                numberBit.push_back(bit);
                encodedBitString.push_back(bit);
                numberBit.append(" ");
            }

            cout << numberBit << ": " << character << endl;

            for (int i = 0; i < weight; i++){ // Adds the correct bit(s) per character into the output string
                fullBit.append(encodedBitString);
            }
            return(fullBit);                // Returns the output string
        }
        else{                               // Continues down the tree
            if(right->getWeight() >= left->getWeight()){ // Takes the right side if it has a higher or equal weight to the left side
                bitString.push_back('0');
                fullBit.append(right->printTree(bitString));

                bitString.pop_back();

                bitString.push_back('1');
                fullBit.append(left->printTree(bitString));
                
                bitString.pop_back();
            }
            else{                           // Takes the left side otherwise
                bitString.push_back('1');
                fullBit.append(left->printTree(bitString));
                
                bitString.pop_back();

                bitString.push_back('0');
                fullBit.append(right->printTree(bitString));
                
                bitString.pop_back();
            }
            return(fullBit);                 // Returns the output string
        }
    }; 

private:
    Tree* left;
    Tree* right;
    int weight;
    char character;
    string numberBit;
    string encodedBitString;
    string fullBit;
};

#ifndef NULL
#define NULL 0
#endif
struct TreeWrapper {                           // Tree-helper
    TreeWrapper() {
        tree = NULL;
    }
    TreeWrapper(Tree* t) {
        tree = t;
    }
    bool operator<(const TreeWrapper &tw) const {
        return tree->getWeight() > tw.tree->getWeight();
    }
    Tree* tree;
};

int main(int argc, char const *argv[])
{
    priority_queue<TreeWrapper> queue;          // Creates the bottom of the tree
    
    queue.push(TreeWrapper(new Tree(3, 'b')));
    queue.push(TreeWrapper(new Tree(1, 'c')));
    queue.push(TreeWrapper(new Tree(2, 'j')));
    queue.push(TreeWrapper(new Tree(7, 'l')));
    queue.push(TreeWrapper(new Tree(12, 'a')));

    while (queue.size() > 1)                    // Puts the entire tree together
    {
        TreeWrapper tree1 = queue.top();
        queue.pop();
        TreeWrapper tree2 = queue.top();
        queue.pop();
        int treeWeight = (tree1.tree->getWeight() + tree2.tree->getWeight());

        queue.push(TreeWrapper(new Tree(treeWeight, tree1.tree, tree2.tree))); 
    }

    TreeWrapper fullTreeWrapper = queue.top();      // Retreives the fully built tree
    queue.pop();

    vector<char> bitString;
    string answer = (fullTreeWrapper.tree->printTree(bitString));          // Prints out the tree
    cout << "Answer is: " << answer << endl;

    return 0;
}