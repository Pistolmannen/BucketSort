#include <iostream>
#include <vector>
#include <queue>

using namespace std;

class Tree {                                
public:
    // Creates a leaf with a character
    Tree(int w, char c){                    
        weight = w;
        character = c;
    };

    // Creates a tree with two branches
    Tree(int w, Tree* t1, Tree* t2){        
        weight = w;
        right = t1;
        left = t2;
    };

    // Deletes the root node of the tree
    ~Tree(){                                
        if (left != NULL){
            free(left);
        }
        if (right != NULL){
            free(right);
        }
    };

    // Retreives the weight of the tree
    int getWeight() {          
        return(weight);                     // Returns the weight of the tree
    };

    // Print the components of the tree
    string printTree(vector<char>& bitString) { 
        if ((int)character > 96){               // If the current function-iteration finds a character/leaf in the tree
            
            for (char bit : bitString) {        // Adds the whole branch-path (the path down the tree to the character/leaf) to the bit path
                numberBit.push_back(bit);
                encodedBitString.push_back(bit); // Adds the character bit path to the bit string for that character
                numberBit.append(" ");
            }

            cout << numberBit << ": " << character << endl; // Prints out the branch-path to the character/leaf

            for (int i = 0; i < weight; i++){ // Adds the correct bit(s) per character into the output string
                fullBit.append(encodedBitString); // Checks how many time the found character appears in the input
            }
            return(fullBit);                // Returns the answer bit string for the character
        }
        else{                               // Continues down the brances
            if(right->getWeight() >= left->getWeight()){ // Takes the right branch if it has a higher or equal weight to the left branch
                bitString.push_back('0');               // Adds a 0 to the branch-path down the tree
                fullBit.append(right->printTree(bitString));  // Calls a new function-iteration to continue down the right branch 

                bitString.pop_back();                   // When the right branch is checked the current function-iteration forgets about the right branch

                bitString.push_back('1');               // Adds a 1 to the branch-path down the tree
                fullBit.append(left->printTree(bitString));  // Calls a new function-iteration to continue down the left branch 
                
                bitString.pop_back();                   // When the left branch is checked the current function-iteration forgets about the left branch
            }                                            
            else{                                   // Takes the left side otherwise
                bitString.push_back('1');           // Adds a 1 to the branch-path down the tree
                fullBit.append(left->printTree(bitString));  // Calls a new function-iteration to continue down the left branch 
                
                bitString.pop_back();               // When the left branch is checked the current function-iteration forgets about the left branch

                bitString.push_back('0');           // Adds a 0 to the branch-path down the tree
                fullBit.append(right->printTree(bitString));   // Calls a new function-iteration to continue down the right branch 
                
                bitString.pop_back();               // When the right branch is checked the current function-iteration forgets about the right branch
            }
            return(fullBit);                 // The current function-iteration has no branch left to check so it returns the output string and automatically get's removed
        }
    }; 

private:
    Tree* left;
    Tree* right;
    int weight; // The weight is the amount of time a character appears in the input
    char character;
    string numberBit; // Branch-path to the character
    string encodedBitString; // The actual bit string of a character
    string fullBit; // Answer bit string
};

#ifndef NULL
#define NULL 0
#endif

// Tree-helper
struct TreeWrapper {                           
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
    
    queue.push(TreeWrapper(new Tree(4, 'a')));
    queue.push(TreeWrapper(new Tree(3, 'b')));
    queue.push(TreeWrapper(new Tree(1, 'c')));

    while (queue.size() > 1)                    // Puts the entire tree together
    {
        TreeWrapper tree1 = queue.top();
        queue.pop();
        TreeWrapper tree2 = queue.top();
        queue.pop();
        int treeWeight = (tree1.tree->getWeight() + tree2.tree->getWeight());

        queue.push(TreeWrapper(new Tree(treeWeight, tree1.tree, tree2.tree))); // Puts the combined tree back into the priority queue 
    }

    // Retreives the fully built tree
    TreeWrapper fullTreeWrapper = queue.top();      
    queue.pop();

    vector<char> bitString;
    string answer = (fullTreeWrapper.tree->printTree(bitString));          // Prints out the bith path to all the characters in the final tree
    cout << "Answer is: " << answer << endl;                               // Prints out the final answer bit string

    return 0;
}