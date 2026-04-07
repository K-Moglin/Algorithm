#pragma once
#include <iostream>

template <typename T>
class BST {
private:
	struct Node {
		T val;
		Node* left;
		Node* right;

		Node(const T& x) : val(x), left(nullptr), right(nullptr) {}
	};

	Node* root;

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

		return node;
	}

	bool search(Node* node, const T& x) const {
		if (node == nullptr) {
			return false;
		}

		if (x == node->val) {
			return true;
		}
		else if (x < node->val) {
			return search(node->left, x);
		}
		else {
			return search(node->right, x);
		}
	}

	void inorder(Node* node) const {
		if (node == nullptr) {
			return;
		}

		inorder(node->left);
		std::cout << node->val << " ";
		inorder(node->right);
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
			if (node->left == nullptr) {
				Node* temp = node->right;
				delete node;
				return temp;
			}
			if (node->right == nullptr) {
				Node* temp = node->left;
				delete node;
				return temp;
			}

			Node* temp = findMin(node->right);
			node->val = temp->val;
			node->right = erase(node->right, temp->val);
		}

		return node;
	}

	Node* findMin(Node* node) const {
		while (node != nullptr && node->left != nullptr) {
			node = node->left;
		}
		return node;
	}

	void destroy(Node* node) {
		if (node == nullptr) {
			return;
		}

		destroy(node->left);
		destroy(node->right);
		delete node;
	}

public:
	BST() : root(nullptr) {}
	~BST() {
		destroy(root);
	}

	void insert(const T& x) {
		root = insert(root, x);
	}

	bool search(const T& x) const {
		return search(root, x);
	}

	void erase(const T& x) {
		root = erase(root, x);
	}

	void inorder() const {
		inorder(root);
		std::cout << '\n';
	}
};