#include <iostream>

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
    BST* Insert(BST*, int,float);

    // Inorder traversal.
    void InOrderWalk(BST*);

    BST* rr_rotat(BST* parent);

    BST* ll_rotat(BST* parent);

    BST* lr_rotat(BST* parent);

    BST* rl_rotat(BST* parent);

    BST* ParentSearch(BST*, int value);

    int isBalanced(BST* root);

    void UpdatingHeight(BST* root);
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
BST* BST::Insert(BST* root, int value,float constant)
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

    root->height = 1 + max(getHeight(root->right), getHeight(root->left));

    int  heightDifference = getHeight(root->left) - getHeight(root->right);

    if (getHeight(root->right) > constant * heightDifference || getHeight(root->left) > constant * heightDifference)
    {
        //rebalance
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
    static int height = 1;
    UpdatingHeight(root->left);
    if (root->left == NULL && root->right == NULL) {
        root->height = 1;
    }
    else
    {
        root->height = height;
    }
    UpdatingHeight(root->right);
    height++;
}

//search the node of the parent from the value of the child
BST* BST::ParentSearch(BST *root, int value)
{
    
    if (root->data == value)
    {
        if (!root->parent)
        {
            return root;
        }
        return root->parent;
    }
    
    if (value > root->data) {
        // Insert right node data, if the 'value'
        // to be inserted is greater than 'root' node data.

        // Process right nodes.
        root->right = ParentSearch(root->right, value);
       
    }
    else if (value < root->data) 
    {
        root->left = ParentSearch(root->left, value);   
    }  
}



BST* BST::ll_rotat(BST* parent) 
{
    BST* t;
    t = parent->right;
    parent->right = nullptr;
    t->left = parent;
    parent->parent = t;
    t->parent = NULL;
    cout << "Left-Left Rotation";
    cout << endl;
    return t;
}


BST* BST::rr_rotat(BST* parent) 
{
    BST* t;
    t = parent->right;
    parent->right = parent->left;
    parent->left = parent;
    cout << "Right-Right Rotation";
    cout << endl;
    return t;
}

BST* BST::lr_rotat(BST* parent) 
{
    BST* t;
    t = parent->left;
    parent->left = rr_rotat(t);
    cout << "Left-Right Rotation";
    cout << endl;
    return ll_rotat(parent);
}

BST* BST::rl_rotat(BST* parent) 
{
    BST* t;
    t = parent->right;
    parent->right = ll_rotat(t);
    cout << "Right-Left Rotation";
    cout << endl;
    return rr_rotat(parent);
}

int main(void)
{
    BST b, * root = NULL;
    root = b.Insert(root, 10);
    b.Insert(root, 50);
    //b.Insert(root, 20);
    b.Insert(root, 70);
    //b.Insert(root, 80);
    //b.Insert(root, 30);
    //b.Insert(root, 60);
    //b.Insert(root, 160);
    //b.Insert(root, 170);
    root = b.ll_rotat(root);
    //b.rr_rotat(root);
    cout << root->left->data << " " << root->right->data << endl;
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