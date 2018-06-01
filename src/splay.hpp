#ifndef SPLAY_H
#define SPLAY_H

#include <queue>
#include <iostream>
#include <algorithm>
#include "base.hpp"


template<typename T>
class Splay : public BST<T> {
private:
	treeNode<T>* root;
	int size;

	int height(treeNode<T>* node);
	treeNode<T>* maxNode(treeNode<T>* node);
	treeNode<T>* minNode(treeNode<T>* node);
	treeNode<T>* leftRotate(treeNode<T>* node);
	treeNode<T>* rightRotate(treeNode<T>* node);
	treeNode<T>* leftLeftRotate(treeNode<T>* node);
	treeNode<T>* leftRightRotate(treeNode<T>* node);
	treeNode<T>* rightRightRotate(treeNode<T>* node);
	treeNode<T>* rightLeftRotate(treeNode<T>* node);

	treeNode<T>* splayTree(treeNode<T>* &node, const T &key);
	treeNode<T>* searchNodePr(treeNode<T>* &node, const T &key);
	treeNode<T>* insertNodePr(treeNode<T>* &node, const T &key);
	treeNode<T>* deleteNodePr(treeNode<T>* &node, T &key);
	void inOrderTra(treeNode<T>* node);
	void preOrderTra(treeNode<T>* node);
	void postOrderTra(treeNode<T>* node);
	
public:
	Splay();
	~Splay();
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
Splay<T>::Splay() {
	root = nullptr;
	size = 0;
	return;
}

template<typename T>
Splay<T>::~Splay() {
	if(root == nullptr)
		return;

	std::queue< treeNode<T>* > store;
	store.push(root);
	while(store.size()) {
		treeNode<T>* delNode = store.front();
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
int Splay<T>::height(treeNode<T>* node) {
	if(node == nullptr)
		return 0;
	return std::max(height(node->left), height(node->right)) + 1;
}

template<typename T>
treeNode<T>* Splay<T>::maxNode(treeNode<T>* node) {
	while(node->right != nullptr)
		node = node->right;
	return node;
}

template<typename T>
treeNode<T>* Splay<T>::minNode(treeNode<T>* node) {
	while(node->left != nullptr) 
		node = node->left;
	return node;
}

template<typename T>
treeNode<T>* Splay<T>::leftRotate(treeNode<T>* node) {
	treeNode<T>* tempNode = node->right;
	node->right = tempNode->left;
	tempNode->left = node;
	return tempNode;
}

template<typename T>
treeNode<T>* Splay<T>::rightRotate(treeNode<T>* node) {
	treeNode<T>* tempNode = node->left;
	node->left = tempNode->right;
	tempNode->right = node;
	return tempNode;
}

template<typename T>
treeNode<T>* Splay<T>::leftLeftRotate(treeNode<T>* node) {
	node->right = leftRotate(node->right);
	return leftRotate(node);
}

template<typename T>
treeNode<T>* Splay<T>::leftRightRotate(treeNode<T>* node) {
	node->left = leftRotate(node->left);
	return rightRotate(node);
}

template<typename T>
treeNode<T>* Splay<T>::rightRightRotate(treeNode<T>* node) {
	node->left = rightRotate(node->left);
	return rightRotate(node);
}

template<typename T>
treeNode<T>* Splay<T>::rightLeftRotate(treeNode<T>* node) {
	node->right = rightRotate(node->right);
	return leftRotate(node);
}

template<typename T>
treeNode<T>* Splay<T>::splayTree(treeNode<T>* &node, const T &key) {
	if(node != nullptr) {
		if(key == node->key) {
			return node;
		}
		else if(key > node->key) {
			if(node->right != nullptr) {
				if(key == node->right->key) {
					node = leftRotate(node);
					return splayTree(node, key);
				}
				else if(key > node->right->key) {
					if(node->right->right != nullptr) {
						node = leftLeftRotate(node);
						return splayTree(node, key);
					}
				}
				// key < node->right->key
				else {
					if(node->right->left != nullptr) {
						node = rightLeftRotate(node);
						return splayTree(node, key);
					}
				}
			}
			return node;
		}
		else {
			if(node->left != nullptr) {
				if(key == node->left->key) {
					node = rightRotate(node);
					return splayTree(node, key);
				}
				else if(key > node->left->key) {
					node = leftRightRotate(node);
					return splayTree(node, key);
				}
				// key < node->left->key
				else {
					node = rightRightRotate(node);
					return splayTree(node, key);
				}
			}
			return node;
		}
	}
	return nullptr;
}

template<typename T>
treeNode<T>* Splay<T>::searchNodePr(treeNode<T>* &node, const T &key) {
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
bool Splay<T>::searchNode(const T &key) {
	treeNode<T>* tempNode = searchNodePr(root, key);
	if(tempNode == nullptr)
		return false;
	splayTree(root, key);
	return true;
}

template<typename T>
treeNode<T>* Splay<T>::insertNodePr(treeNode<T>* &node, const T &key) {
	if(node == nullptr) {
		node = new treeNode<T>(key);
	}
	else if(key > node->key) {
		node->right = insertNodePr(node->right, key);
	}
	else if(key < node->key) {
		node->left = insertNodePr(node->left, key);
	}
	return node;
}

template<typename T>
bool Splay<T>::insertNode(const T &key) {
	if(searchNode(key))
		return false;
	insertNodePr(root, key);
	splayTree(root, key);
	size++;
	return true;
}

template<typename T>
treeNode<T>* Splay<T>::deleteNodePr(treeNode<T>* &node, T &key) {
	if(node == nullptr)
		return nullptr;
	treeNode<T> *res;
	if(node->left != nullptr) {
		treeNode<T>* tempNode = maxNode(node->left);
		res = splayTree(node->left, tempNode->key);
		res->right = node->right;
	}
	else 
		res = node->right;

	delete node;
	node = nullptr;

	return res;
}

template<typename T>
bool Splay<T>::deleteNode(const T &key) {
	if(!searchNode(key))
		return false;
	T delKey = key;
	root = deleteNodePr(root, delKey);
	size--;
	return true;
}

template<typename T>
int Splay<T>::getSize() {
	return size;
}

template<typename T>
void Splay<T>::inOrder() {
	return inOrderTra(root);
}

template<typename T>
void Splay<T>::preOrder() {
	return preOrderTra(root);
}

template<typename T>
void Splay<T>::postOrder() {
	return postOrderTra(root);
}

template<typename T>
void Splay<T>::inOrderTra(treeNode<T>* node) {
	if(node == nullptr)
		return;
	inOrderTra(node->left);
	std::cout << node->key << std::endl;
	inOrderTra(node->right);
}

template<typename T>
void Splay<T>::preOrderTra(treeNode<T>* node) {
	if(node == nullptr) 
		return;
	std::cout << node->key << std::endl;
	preOrderTra(node->left);
	preOrderTra(node->right);
}

template<typename T>
void Splay<T>::postOrderTra(treeNode<T>* node) {
	if(node == nullptr)
		return;
	postOrderTra(node->left);
	postOrderTra(node->right);
	std::cout << node->key << std::endl;
}

template<typename T>
void Splay<T>::printTree() {
	if(root == nullptr)
		return;

	std::queue< std::pair<treeNode<T>*, int> > tra;
	tra.push(std::make_pair(root, 0));
	int lastHeight = 0;
	while(tra.size()) {
		std::pair<treeNode<T>*, int> temp = tra.front();
		tra.pop();
		treeNode<T>* tempNode = temp.first;
		int height = temp.second;

		if(height > lastHeight) {
			std::cout << std::endl;
			lastHeight = height;
		}

		std::cout << "Key: " << temp.first->key << " ";

		if(temp.first->left)
			tra.push(std::make_pair(temp.first->left, height + 1));
		if(temp.first->right)
			tra.push(std::make_pair(temp.first->right, height + 1));
	}
	std::cout << std::endl;
	return;
}

#endif












