#include <iostream>
#include <vector>
#include <queue>

using namespace std;

class Tree {    // Tree class
public:
    Tree(int w, char c){    // Creates a tree with a character
        weight = w;
        character = c;
    };

    Tree(int w, Tree* t1, Tree* t2){  // Creates a tree with two branches
        weight = w;
        right = t1;
        left = t2;
    };

    ~Tree(){                    // Deletes the root node of the tree
        if (left != NULL){
            free(left);
        }
        if (right != NULL){
            free(right);
        }
    };

    int getWeight() {         // Returns the weight of the tree 
        return(weight);
    };

    string printTree(vector<char>& bitString) {   // Print the components of the tree 
        if ((int)character > 96){
            
            for (char bit : bitString) {        // Adds the bit path so it can be printed out
                numberBit.push_back(bit);
                testBit.push_back(bit);
                numberBit.append(" ");
            }

            cout << numberBit << " : " << character << endl;

            for (int i = 0; i < weight; i++){
                fullBit.append(testBit);
            }
            return(fullBit);

        }
        else{                               // Continues down the tree

            if(right->getWeight() >= left->getWeight()){
                bitString.push_back('0');
                fullBit = (right->printTree(bitString));

                bitString.pop_back();

                bitString.push_back('1');
                fullBit.append(left->printTree(bitString));
            }
            else{
                bitString.push_back('1');
                fullBit = (left->printTree(bitString));
                
                bitString.pop_back();

                bitString.push_back('0');
                fullBit.append(right->printTree(bitString));
            }
            

            return(fullBit);
        }
    }; 

private:
    Tree* left;
    Tree* right;
    int weight;
    int rightWeight;
    int leftWeight;
    char character;
    string numberBit;
    string testBit;
    string fullBit;
};

#ifndef NULL
#define NULL 0
#endif
struct TreeWrapper {        // Tree-helper
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
    priority_queue<TreeWrapper> queue;          // Creates the bottoms of the tree
    queue.push(TreeWrapper(new Tree(4, 'a')));
    queue.push(TreeWrapper(new Tree(3, 'b')));
    queue.push(TreeWrapper(new Tree(1, 'c')));

    while (queue.size() > 1)            // Puts the entire tree together
    {
        TreeWrapper tree1 = queue.top();
        queue.pop();
        TreeWrapper tree2 = queue.top();
        queue.pop();
        int treeWeight = tree1.tree->getWeight() + tree2.tree->getWeight();

        queue.push(TreeWrapper(new Tree(treeWeight, tree1.tree, tree2.tree)));
    }

    TreeWrapper fullTreeWrapper = queue.top();      // Retreives the fully built tree
    queue.pop();

    vector<char> bitString;
    string answer = (fullTreeWrapper.tree->printTree(bitString));          // Prints out the tree
    cout << "Answer is: " << answer << endl;

    return 0;
}