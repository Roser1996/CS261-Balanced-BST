#ifndef AVLBST_H
#define AVLBST_H

#include <queue>
#include <iostream>
#include <algorithm>
#include "base.hpp"

template<typename T>
struct avTreeNode {
	T key;
	int height;
	avTreeNode *left;
	avTreeNode *right;

	avTreeNode(void) : height(0), left(nullptr), right(nullptr) {}
	avTreeNode(T item) : key(item), height(1), left(nullptr), right(nullptr) {}
};

template<typename T>
class avlBST : public BST<T> {
private:
	avTreeNode<T> *root;
	int size;

	int height(const avTreeNode<T>* node);
	avTreeNode<T>* leftRotate(avTreeNode<T>* node);
	avTreeNode<T>* rightRotate(avTreeNode<T>* node);
	avTreeNode<T>* rightLeftRotate(avTreeNode<T>* node);
	avTreeNode<T>* leftRightRotate(avTreeNode<T>* node);
	avTreeNode<T>* insertNodePr(avTreeNode<T>* &node, const T &key);
	avTreeNode<T>* searchNodePr(avTreeNode<T>* &node, const T &key);
	avTreeNode<T>* deleteNodePr(avTreeNode<T>* &node, T &key);
	void inOrderTra(avTreeNode<T>* node);
	void preOrderTra(avTreeNode<T>* node);
	void postOrderTra(avTreeNode<T>* node);
public:
	avlBST();
	~avlBST();
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

template<typename T>
avlBST<T>::avlBST() {
	root = nullptr;
	size = 0;
	return;
}

template<typename T>
avlBST<T>::~avlBST() {
	if(root == nullptr)
		return;

	std::queue< avTreeNode<T>* > store;
	store.push(root);
	while(store.size()) {
		avTreeNode<T>* delNode = store.front();
		store.pop();

		if(delNode->left != nullptr)
			store.push(delNode->left);
		if(delNode->right != nullptr)
			store.push(delNode->right);

		delete delNode;
		delNode = nullptr;
	}
	return;
}

template<typename T>
int avlBST<T>::height(const avTreeNode<T>* node) {
	if(node != nullptr) {
		return node->height;
	}

	return 0;
}

template<typename T> 
avTreeNode<T>* avlBST<T>::leftRotate(avTreeNode<T>* node) {
	avTreeNode<T>* tempNode = node->right;
	node->right = tempNode->left;
	tempNode->left = node;

	node->height = std::max(height(node->left), height(node->right)) + 1;
	tempNode->height = std::max(height(tempNode->left), height(tempNode->right)) + 1;
	return tempNode;
}

template<typename T>
avTreeNode<T>* avlBST<T>::rightRotate(avTreeNode<T>* node) {
	avTreeNode<T>* tempNode = node->left;
	node->left = tempNode->right;
	tempNode->right = node;

	node->height = std::max(height(node->left), height(node->right)) + 1;
	tempNode->height = std::max(height(tempNode->left), height(tempNode->right)) + 1;
	return tempNode;
}

template<typename T>
avTreeNode<T>* avlBST<T>::rightLeftRotate(avTreeNode<T>* node) {
	node->right = rightRotate(node->right);
	return leftRotate(node);
}

template<typename T>
avTreeNode<T>* avlBST<T>::leftRightRotate(avTreeNode<T>* node) {
	node->left = leftRotate(node->left);
	return rightRotate(node);
}

template<typename T> 
avTreeNode<T>* avlBST<T>::insertNodePr(avTreeNode<T>* &node, const T &key) {
	if(node == nullptr) {
		node = new avTreeNode<T>(key);
	}
	else if(key > node->key) {
		node->right = insertNodePr(node->right, key);
		if(height(node->right) - height(node->left) == 2) {
			if(key > node->right->key) {
				node = leftRotate(node);
			}
			else if(key < node->right->key) {
				node = rightLeftRotate(node);
			}
		}
	}
	else if(key < node->key) {
		node->left = insertNodePr(node->left, key);
		if(height(node->left) - height(node->right) == 2) {
			if(key < node->left->key) {
				node = rightRotate(node);
			}
			else if(key > node->left->key) {
				node = leftRightRotate(node);
			}
		}
	}
	// key == node->key
	else {
		return node;
	}
	node->height = std::max(height(node->left), height(node->right)) + 1;
	return node;

} 

template<typename T>
bool avlBST<T>::insertNode(const T &key) {
	if(searchNode(key))
		return false;
	insertNodePr(this->root, key);
	size++;
	return true;
}

template<typename T>
avTreeNode<T>* avlBST<T>::searchNodePr(avTreeNode<T>* &node, const T &key) {
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
bool avlBST<T>::searchNode(const T &key) {
	avTreeNode<T>* tempNode = searchNodePr(root, key);
	if(tempNode == nullptr)
		return false;

	return true;
}

template<typename T>
avTreeNode<T>* avlBST<T>::deleteNodePr(avTreeNode<T>* &node, T &key) {
	if(node != nullptr) {
		if(key > node->key) {
			node->right = deleteNodePr(node->right, key);
			if(height(node->left) - height(node->right) == 2) {
				if(height(node->left->left) > height(node->left->right)) {
					node = rightRotate(node);
				}
				else {
					node = leftRightRotate(node);
				}
			}
		}
		else if(key < node->key) {
			node->left = deleteNodePr(node->left, key);
			if(height(node->right) - height(node->left) == 2) {
				if(height(node->right->right) > height(node->right->left)) {
					node = leftRotate(node);
				}
				else {
					node = rightLeftRotate(node);
				}
			}
		}
		// key == node->key
		else if(key == node->key) {
			if(node->left != nullptr && node->right != nullptr) {
				if(height(node->left) > height(node->right)) {
					avTreeNode<T>* maxNode = node->left;
					while(maxNode->right != nullptr)
						maxNode = maxNode->right;
					node->key = maxNode->key;
					node->left = deleteNodePr(node->left, maxNode->key);
				}
				else {
					avTreeNode<T>* minNode = node->right;
					while(minNode->left != nullptr)
						minNode = minNode->left;
					node->key = minNode->key;
					node->right = deleteNodePr(node->right, minNode->key);
				}
			}
			else {
				if(node->left == nullptr && node->right == nullptr) {
					delete node;
					node = nullptr;
					return nullptr;
				}
				else if(node->left != nullptr && node->right == nullptr) {
					avTreeNode<T>* resNode = node->left;
					delete node;
					node = nullptr;
					return resNode;
				}
				else {
					avTreeNode<T>* resNode = node->right;
					delete node;
					node = nullptr;
					return resNode;
				}
			}
		}
		node->height = std::max(height(node->left), height(node->right)) + 1;
		return node;
	}
	return nullptr;
}

template<typename T>
bool avlBST<T>::deleteNode(const T &key) {
	if(!searchNode(key))
		return false;
	T tempKey = key;
	deleteNodePr(root, tempKey);
	size--;
	return true;
}

template<typename T>
void avlBST<T>::inOrderTra(avTreeNode<T>* node) {
	if(node == nullptr)
		return;
	inOrderTra(node->left);
	std::cout << node->key << std::endl;
	inOrderTra(node->right);
}

template<typename T>
void avlBST<T>::preOrderTra(avTreeNode<T>* node) {
	if(node == nullptr)
		return;
	std::cout << node->key << std::endl;
	preOrderTra(node->left);
	preOrderTra(node->right);
}

template<typename T>
void avlBST<T>::postOrderTra(avTreeNode<T>* node) {
	if(node == nullptr)
		return;
	postOrderTra(node->left);
	postOrderTra(node->right);
	std::cout << node->key << std::endl;
}

template<typename T>
int avlBST<T>::getSize() {
	return size;
}

template<typename T>
void avlBST<T>::inOrder() {
	return inOrderTra(root);
}

template<typename T>
void avlBST<T>::preOrder() {
	return preOrderTra(root);
}

template<typename T>
void avlBST<T>::postOrder() {
	return postOrderTra(root);
}

template<typename T>
void avlBST<T>::printTree() {
	if(root == nullptr)
		return;

	std::queue< std::pair<avTreeNode<T>*, int> > tra;
	tra.push(std::make_pair(root, 0));
	int lastHeight = 0;
	while(tra.size()) {
		std::pair<avTreeNode<T>*, int> temp = tra.front();
		tra.pop();
		avTreeNode<T>* tempNode = temp.first;
		int height = temp.second;

		if(height > lastHeight) {
			std::cout << std::endl;
			lastHeight = height;
		}

		std::cout << " (" << temp.first->key << "," << temp.first->height << ")";

		if(temp.first->left)
			tra.push(std::make_pair(temp.first->left, height + 1));
		if(temp.first->right)
			tra.push(std::make_pair(temp.first->right, height + 1));
	}
	std::cout << std::endl;
	return;
}



#endif