#include "Node.h"
#include "BinaryTreeTraversal.h"

using namespace alg4::binaryTree;

int main()
{
    Node* root = init_tree();

    Base_traversal* traversal = new Recursive_traversal(root);

    cout << "Pre-order traversal: ";
    traversal->pre_order();
    cout << endl;

    cout << "In-order traversal: ";
    traversal->in_order();
    cout << endl;

    cout << "After-order traversal: ";
    traversal->aft_order();
    cout << endl;

    delete_tree(root);
    return 0;
}