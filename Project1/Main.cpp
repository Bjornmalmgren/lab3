#include <iostream>

using namespace std;
class BST {
public:
    int data;
    int height;
    BST* left, * right,*parent;


    // Default constructor.
    BST();

    // Parameterized constructor.
    BST(int);

    // Insert function.
    BST* Insert(BST*, int);

    // Inorder traversal.
    void InOrderWalk(BST*);

    void ISBalanced(BST);

    BST* ParentSearch(BST*, int value);
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
    cout << root->data << " ";
    InOrderWalk(root->right);
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
    else if (value < root->data) {
       
        root->left = ParentSearch(root->left, value);
        
    }

   
}



//this is left to implement...
void BST::ISBalanced(BST root) {
    BST tootTemp = root;



}

int main(void)
{
    BST b, * root = NULL;
    root = b.Insert(root, 50);
    b.Insert(root, 30);
    b.Insert(root, 20);
    b.Insert(root, 40);
    b.Insert(root, 70);
    b.Insert(root, 80);
    b.Insert(root, 60);
    b.Insert(root, -60);
    b.Insert(root, 120);



    b.InOrderWalk(root);
   

    return 0;
}