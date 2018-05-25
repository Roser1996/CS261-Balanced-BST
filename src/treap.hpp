#ifndef TREAP_H
#define TREAP_H

#include <iostream>
#include <queue>
#include <cstdlib>
#include <ctime>
#include "base.hpp"

#define NUMBERSIZE 100000

template<typename T>
struct heapTreeNode {
	T key;
	int weight;
	heapTreeNode<T>* left;
	heapTreeNode<T>* right;

	heapTreeNode(void) : left(nullptr), right(nullptr) {}
	heapTreeNode(T item) : key(item), left(nullptr), right(nullptr) { weight = std::rand() % NUMBERSIZE; }
};

template<typename T>
class Treap : public BST<T> {
private:
	int size;
	heapTreeNode<T>* root;

	heapTreeNode<T>* leftRotate(heapTreeNode<T>* node);
	heapTreeNode<T>* rightRotate(heapTreeNode<T>* node);
	heapTreeNode<T>* insertNodePr(heapTreeNode<T>* &node, const T &key);
	heapTreeNode<T>* searchNodePr(heapTreeNode<T>* &node, const T &key);
	heapTreeNode<T>* deleteNodePr(heapTreeNode<T>* &node, const T &key);
	void inOrderTra(heapTreeNode<T>* node);
	void preOrderTra(heapTreeNode<T>* node);
	void postOrderTra(heapTreeNode<T>* node);
public:
	Treap();
	~Treap();
	bool insertNode(const T &key);
	bool searchNode(const T &key);
	bool deleteNode(const T &key);

	// self defined
	void inOrder();
	void preOrder();
	void postOrder();
	int getSize();
	void printTree();
};


// implementation
template<typename T>
Treap<T>::Treap() {
	size = 0;
	root = nullptr;
	return;
}

template<typename T>
Treap<T>::~Treap() {
	if(root == nullptr)
		return;
	std::queue< heapTreeNode<T>* > store;
	store.push(root);
	while(store.size()) {
		heapTreeNode<T> *delNode = store.front();
		store.pop();

		if(delNode->left)
			store.push(delNode->left);
		if(delNode->right)
			store.push(delNode->right);

		delete delNode;
		delNode = nullptr;
	}
	return;
}

template<typename T>
heapTreeNode<T>* Treap<T>::leftRotate(heapTreeNode<T>* node) {
	heapTreeNode<T>* tempNode = node->right;
	node->right = tempNode->left;
	tempNode->left = node;

	return tempNode;
}

template<typename T>
heapTreeNode<T>* Treap<T>::rightRotate(heapTreeNode<T>* node) {
	heapTreeNode<T>* tempNode = node->left;
	node->left = tempNode->right;
	tempNode->right = node;

	return tempNode;
}

template<typename T>
heapTreeNode<T>* Treap<T>::insertNodePr(heapTreeNode<T>* &node, const T &key) {
	if(node == nullptr) {
		node = new heapTreeNode<T>(key);
	}
	else if(key < node->key) {
		node->left = insertNodePr(node->left, key);
		if(node->weight > node->left->weight) {
			node = rightRotate(node);
		}
	}
	else if(key > node->key) {
		node->right = insertNodePr(node->right, key);
		if(node->weight > node->right->weight) {
			node = leftRotate(node);
		}
	}
	return node;
}

template<typename T>
bool Treap<T>::insertNode(const T &key) {
	if(searchNode(key)) 
		return false;
	insertNodePr(root, key);
	size++;
	return true;
}

template<typename T> 
heapTreeNode<T>* Treap<T>::searchNodePr(heapTreeNode<T>* &node, const T &key) {
	if(node != nullptr) {
		if(node->key == key)
			return node;
		else if(key > node->key)
			return searchNodePr(node->right, key);
		else
			return searchNodePr(node->left, key);
	}
	return nullptr;
}

template<typename T>
bool Treap<T>::searchNode(const T &key) {
	heapTreeNode<T>* tempNode = searchNodePr(root, key);
	if(tempNode)
		return true;
	return false;
}

template<typename T>
heapTreeNode<T>* Treap<T>::deleteNodePr(heapTreeNode<T>* &node, const T &key) {
	if(node != nullptr) {
		if(key > node->key) {
			node->right = deleteNodePr(node->right, key);
		}
		else if(key < node->key) {
			node->left = deleteNodePr(node->left, key);
		}
		else {
			if(node->left != nullptr && node->right != nullptr) {
				if(node->left->weight < node->right->weight) {
					node = rightRotate(node);
					node->right = deleteNodePr(node->right, key);
				}
				else {
					node = leftRotate(node);
					node->left = deleteNodePr(node->left, key);
				}
			}
			else {
				if(node->left == nullptr && node->right == nullptr) {
					delete node;
					node = nullptr;
					return nullptr;
				}
				else if(node->left != nullptr && node->right == nullptr) {
					heapTreeNode<T>* resNode = node->left;
					delete node;
					node = nullptr;
					return resNode;
				}
				else {
					heapTreeNode<T>* resNode = node->right;
					delete node;
					node = nullptr;
					return resNode;
				}
			}
		}
		return node;
	}
	return nullptr;
}

template<typename T>
bool Treap<T>::deleteNode(const T &key) {
	if(!searchNode(key))
		return false;
	deleteNodePr(root, key);
	size--;
	return true;
}

template<typename T>
void Treap<T>::inOrderTra(heapTreeNode<T>* node) {
	if(node == nullptr)
		return;
	inOrderTra(node->left);
	std::cout << node->key << " " << node->weight << std::endl;
	inOrderTra(node->right);
}

template<typename T>
void Treap<T>::preOrderTra(heapTreeNode<T>* node) {
	if(node == nullptr)
		return;
	std::cout << node->key << std::endl;
	preOrderTra(node->left);
	preOrderTra(node->right);
}

template<typename T>
void Treap<T>::postOrderTra(heapTreeNode<T>* node) {
	if(node == nullptr)
		return;
	postOrderTra(node->left);
	postOrderTra(node->right);
	std::cout << node->key << std::endl;
}

template<typename T>
int Treap<T>::getSize() {
	return size;
}

template<typename T>
void Treap<T>::inOrder() {
	return inOrderTra(root);
}

template<typename T>
void Treap<T>::preOrder() {
	return preOrderTra(root);
}

template<typename T>
void Treap<T>::postOrder() {
	return postOrderTra(root);
}

template<typename T>
void Treap<T>::printTree() {
	if(root == nullptr)
		return;

	std::queue< std::pair<heapTreeNode<T>*, int> > tra;
	tra.push(std::make_pair(root, 0));
	int lastHeight = 0;
	while(tra.size()) {
		std::pair<heapTreeNode<T>*, int> temp = tra.front();
		tra.pop();
		heapTreeNode<T>* tempNode = temp.first;
		int height = temp.second;

		if(height > lastHeight) {
			std::cout << std::endl;
			lastHeight = height;
		}

		std::cout << " (" << temp.first->key << "," << temp.first->weight << ")";

		if(temp.first->left)
			tra.push(std::make_pair(temp.first->left, height + 1));
		if(temp.first->right)
			tra.push(std::make_pair(temp.first->right, height + 1));
	}
	std::cout << std::endl;
	return;
}



#endif














