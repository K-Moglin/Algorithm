#include "avl.h"
#include <iostream>


int main() {
	AVL<int> tree;

	tree.insert(5);
	tree.insert(3);
	tree.insert(7);
	tree.insert(2);
	tree.insert(4);
	tree.insert(6);
	tree.insert(8);

	tree.inorder();

	tree.erase(2);
	std::cout << "delete 2 : ";
	tree.inorder();

	tree.erase(7);
	std::cout << "delete 7 : ";
	tree.inorder();

	tree.erase(5);
	std::cout << "delete 5 : ";
	tree.inorder();

	std::cout << "search 4: " << (tree.search(4) ? "YES" : "NO") << '\n';
	std::cout << "search 5: " << (tree.search(5) ? "YES" : "NO") << '\n';


	return 0;
}