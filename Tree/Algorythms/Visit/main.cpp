#include "visitTree.hpp"
#include <iostream>
/*
    g++ -o main main.cpp visitTree.cpp visitTree_BFS.cpp visitTree_DFS.cpp
    ./main
*/
int main()
{
    Tree root = new Node("A");
    root->left = new Node("L");
    root->right = new Node("B");
    root->left->left = new Node("E");
    root->left->right = new Node("R");
    root->right->left = new Node("O");
    root->right->right = new Node("!");

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
