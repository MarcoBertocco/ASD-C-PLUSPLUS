#include "visitTree.hpp"
#include <iostream>
/*
    g++ -o main main.cpp visitTree.cpp visitTree_BFS.cpp visitTree_DFS.cpp
    ./main
*/
int main()
{
    /*Tree root = new Node("A");
    root->left = new Node("L");
    root->right = new Node("B");
    root->left->left = new Node("E");
    root->left->right = new Node("R");
    root->right->left = new Node("O");
    root->right->right = new Node("!");*/

    Node* root = new Node("20");
    root->left = new Node("18");
    root->right = new Node("30");

    root->left->right = new Node("13");
    root->left->right->left = new Node("14");

    root->right->left = new Node("5");
    root->right->right = new Node("9");
    root->right->left->right = new Node("7");


    std::cout << "GENERIC: ";
    generic_visit(root);
    std::cout << std::endl;

    std::cout << "BFS: ";
    breadth_first_search(root);
    std::cout << std::endl;

    std::cout << "DFS Normal: ";
    depth_first_search(root);
    std::cout << std::endl;

    std::cout << "DFS Recursive: ";
    depth_first_search_rec(root);
    std::cout << std::endl;

    std::cout << "DFS Rec Pre Order: ";
    depth_first_search_rec_preorder(root);
    std::cout << std::endl;

    std::cout << "DFS Rec Simmetric: ";
    depth_first_search_rec_simmetric(root);
    std::cout << std::endl;

    std::cout << "DFS Rec Post Order: ";
    depth_first_search_rec_postorder(root);
    std::cout << std::endl;
    return 0;
}
