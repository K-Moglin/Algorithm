#pragma once
#include <iostream>
#include <algorithm>

template <typename T>
class AVL {
private:
	struct Node {
		T val;
		int height;
		Node* left;
		Node* right;

		Node(const T& x) : val(x), height(1), left(nullptr), right(nullptr) {}
	};

	Node* root;

	int getHeight(Node* node) const{
		if (node == nullptr) {
			return 0;
		}
		return node->height;
	}

	void updateHeight(Node* node) {
		if (node == nullptr) {
			return;
		}
		node->height = std::max(getHeight(node->left), getHeight(node->right)) + 1;
	}

	int getBalance(Node* node) const{
		if (node == nullptr) {
			return 0;
		}
		return getHeight(node->left) - getHeight(node->right);
	}

	Node* rightRotate(Node* y) {
		Node* x = y->left;
		Node* T2 = x->right;

		x->right = y;
		y->left = T2;

		updateHeight(y);
		updateHeight(x);

		return x;
	}

	Node* leftRotate(Node* x) {
		Node* y = x->right;
		Node* T2 = y->left;

		y->left = x;
		x->right = T2;

		updateHeight(x);
		updateHeight(y);

		return y;
	}

	Node* insert(Node* node, const T& x) {
		if (node == nullptr) {
			return new Node(x);
		}

		if (x < node->val) {
			node->left = insert(node->left, x);
		}
		else if (x > node->val) {
			node->right = insert(node->right, x);
		}
		else {
			return node;
		}

		updateHeight(node);
		int balance = getBalance(node);

		// LL
		if (balance > 1 && x < node->left->val) {
			return rightRotate(node);
		}

		// RR
		if (balance < -1 && x > node->right->val) {
			return leftRotate(node);
		}

		// LR
		if (balance > 1 && x > node->left->val) {
			node->left = leftRotate(node->left);
			return rightRotate(node);
		}

		// RL
		if (balance < -1 && x < node->right->val) {
			node->right = rightRotate(node->right);
			return leftRotate(node);
		}

		return node;
	}

	void inorder(Node* node) const{
		if (node == nullptr) {
			return;
		}
		inorder(node->left);
		std::cout << node->val << " ";
		inorder(node->right);
	}

	void destroy(Node* node) {
		if (node == nullptr) {
			return;
		}
		destroy(node->left);
		destroy(node->right);
		delete node;
	}

	bool search(Node* node, const T& x) const {
		if (node == nullptr) {
			return false;
		}

		if (node->val == x) {
			return true;
		}
		else if (node->val > x) {
			return search(node->left, x);
		}
		else {
			return search(node->right, x);
		}
	}

	Node* findMin(Node* node) const {
		while (node != nullptr && node->left != nullptr) {
			node = node->left;
		}
		return node;
	}

	Node* erase(Node* node, const T& x) {
		if (node == nullptr) {
			return nullptr;
		}

		if (x < node->val) {
			node->left = erase(node->left, x);
		}
		else if (x > node->val) {
			node->right = erase(node->right, x);
		}
		else {
			// no chirld or 1 chirld
			if (node->left == nullptr || node->right == nullptr) {
				Node* temp = (node->left != nullptr) ? node->left : node->right;

				if (temp == nullptr) {
					delete node;
					return nullptr;
				}
				else {
					delete node;
					return temp;
				}
			}
			// 2 chilrd
			Node* temp = findMin(node->right);
			node->val = temp->val;
			node->right = erase(node->right, temp->val);
		}

		updateHeight(node);
		int balance = getBalance(node);
		// LL
		if (balance > 1 && getBalance(node->left) >= 0) {
			return rightRotate(node);
		}
		// LR
		if (balance > 1 && getBalance(node->left) < 0) {
			node->left = leftRotate(node);
		}
		// RR
		if (balance < -1 && getBalance(node->right) <= 0) {
			return leftRotate(node);
		}
		// RL
		if (balance < -1 && getBalance(node->right) > 0) {
			node->right = rightRotate(node->right);
			return leftRotate(node);
		}

		return node;
	}

public:
	AVL() : root(nullptr) {}

	~AVL() {
		destroy(root);
	}

	void insert(const T& x) {
		root = insert(root, x);
	}

	void inorder() const{
		inorder(root);
		std::cout << '\n';
	}

	bool search(const T& x) const {
		return search(root, x);
	}

	void erase(const T& x) {
		root = erase(root, x);
	}
};