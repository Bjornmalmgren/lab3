#include <iostream>
#include <vector> 
using namespace std;
class BST {
    
public:
    int height;
    int data;
    
    BST* left, * right,*parent;


    // Default constructor.
    BST();

    // Parameterized constructor.
    BST(int);
    int getHeight(BST*);

    // Insert function.
    BST* Insert(BST*, int);

    // Inorder traversal.
    void InOrderWalk(BST*);

    int isBalanced(BST* root);

    void UpdatingHeight(BST* root);
    BST* Balancetree(int start, int end, vector<int>& inOrderValues);
    void InOrder(BST* root, vector<int>& result);
};

// Default Constructor definition.
BST::BST()
    : data(0)
    , height(1)
    , parent(NULL)
    , left(NULL)
    , right(NULL)
{
}

// Parameterized Constructor definition.
BST::BST(int value)
{
    data = value;
    height = 1;
    left = right = parent= NULL;

}
int BST::getHeight(BST* root)
{
    if (!root)
    {
        return 0;
    }
    else
    {
        return root->height;
    }
}
// Insert function definition.
BST* BST::Insert(BST* root, int value)
{
    if (!root) {

        // Insert the first node, if root is NULL.
        return new BST(value);
    }

    // Insert data.
    if (value > root->data) {
        // Insert right node data, if the 'value'
        // to be inserted is greater than 'root' node data.

        // Process right nodes.
        
        root->right = Insert(root->right, value);
        if (root->right->parent != root)
        root->right->parent = root;
    }
    else if (value < root->data) {
        // Insert left node data, if the 'value'
        // to be inserted is smaller than 'root' node data.

        // Process left nodes.
            
        root->left = Insert(root->left, value);
        if(root->left->parent != root)
        root->left->parent = root;
    }

    // Return 'root' node, after insertion.
    return root;
}

// Inorder traversal function.
// This gives data in sorted order.
void BST::InOrderWalk(BST* root)
{
    if (!root) {
        return;
    }
    InOrderWalk(root->left);
    cout << root->data << " "<<root->height<<endl;
    InOrderWalk(root->right);
}

// Function to check if tree is height balanced (works recursively) checks from leaf up to main root
int BST::isBalanced(BST* root)
{
    //if list is empty
    if (root == NULL)
        return 0;
    int lh = isBalanced(root->left); // recursive checks if left "root" of left branch is balanced
    if (lh == -1) // returns -1 if unbalanced
        return -1;
    int rh = isBalanced(root->right); // recursive checks if left "root" of right branch is balanced
    if (rh == -1)
        return -1; // returns -1 if unbalanced

    if (abs(lh - rh) > 1) // adds the node value of left node and right node and gives abs value (+), if greater than 1 then tree is not balanced
        return -1; // returns -1 if unbalanced
    else
        return max(lh, rh) + 1; // returns the height of the tree
}

void BST::UpdatingHeight(BST* root) {
    if (!root) { return; }
    UpdatingHeight(root->left);
    UpdatingHeight(root->right);
    if (root->left == NULL && root->right == NULL) {
        root->height = 1;
        return;
    }
    else if (root->left != NULL && root->right != NULL)
    {
        root->height = abs(root->left->height -root->right->height);
        if (root->height == 0) {
            root->height = root->left->height + 1;
        }
    }
    else if(root->left != NULL)
    {
        root->height = root->left->height+1;
    }
    else if (root->right != NULL)
    {
        root->height = root->right->height + 1;
    }

}


//walks through the BST in order and puts all values in a vector to use for balancing
void BST::InOrder(BST* root, vector<int>& result) {
    if (root == NULL) {
        return;
    }

    InOrder(root->left, result);
    result.push_back(root->data);
    InOrder(root->right, result);
}

//balances
BST* BST::Balancetree(int start, int end, vector<int>& inOrderValues) {
    if (start > end) {
        return NULL;
    }
    //we find the middle value
    int middle = (start + end) / 2;
    //make the middle value the new root
    BST* newRoot = new BST(inOrderValues[middle]);
    //balances both right and left
    newRoot->left = Balancetree(start, middle - 1, inOrderValues);
    newRoot->right = Balancetree(middle+1, end, inOrderValues);

    return newRoot;
}


int main(void)
{
    BST b, * root = NULL;
    vector<int> inOrderInt;
    root = b.Insert(root, 20);
    b.Insert(root, 50);
    b.Insert(root, 10);
    b.Insert(root, 70);
    b.Insert(root, 80);
    b.Insert(root, 30);
    b.Insert(root, 160);

    b.InOrder(root, inOrderInt);

    root = b.Balancetree(0, inOrderInt.size() - 1, inOrderInt);

    //updating height is need to make sure that we can se that the result is correct
    b.UpdatingHeight(root);
    b.InOrderWalk(root);

    if (b.isBalanced(root) == -1)
    {
        cout << "not balanced in height";

    }
    else
        cout << "is balanced height";

    return 0;
}