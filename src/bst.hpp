#ifndef BST_H
#define BST_H

#include <iostream>
#include <stack>
#include <queue>
#include "base.hpp"

template<typename T>
struct treeNode {
	T key;
	treeNode<T> *left;
	treeNode<T> *right;

	treeNode() {left = nullptr; right = nullptr;}
	treeNode(T item) {key = item; left = nullptr; right = nullptr;}
};

template<typename T>
class standBST : public BST<T> {
private:
	int size;
	treeNode<T> *head;

	// private method
	void inOrderTra(const treeNode<T>* node);
	void preOrderTra(const treeNode<T>* node);
	void postOrderTra(const treeNode<T>* node);
	treeNode<T>* getHead();
public:
	standBST();
	~standBST();
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


// Implementation of standard BST
template<typename T>
standBST<T>::standBST() {
	size = 0;
	head = nullptr;
	return;
}

template<typename T>
standBST<T>::~standBST() {
	if(head == nullptr)
		return;
	std::queue< treeNode<T>* > delNode;
	delNode.push(head);
	while(delNode.size() != 0) {
		treeNode<T> *del = delNode.front();
		delNode.pop();

		if(del->left != nullptr)
			delNode.push(del->left);
		if(del->right != nullptr)
			delNode.push(del->right);

		delete del;
		del = nullptr;
	}

	return;
}

template<typename T>
bool standBST<T>::insertNode(const T &key) {
	if(head == nullptr) {
		head = new treeNode<T>(key);
		size++;
		return true;
	}

	// head is not null pointer
	std::stack< treeNode<T>* > store;
	store.push(head);
	while(store.size() != 0) {
		treeNode<T> *temp = store.top();
		store.pop();

		// No insertion
		if(key == temp->key)
			return true;
		else if(key < temp->key) {
			if(temp->left == nullptr) {
				temp->left = new treeNode<T>(key);
				size++;
				return true;
			}
			store.push(temp->left);
		}
		// key > temp->key
		else {
			if(temp->right == nullptr) {
				temp->right = new treeNode<T>(key);
				size++;
				return true;
			}
			store.push(temp->right);
		}
	}

	std::cerr << "Insertion failed" << std::endl;
	return false;
}

template<typename T>
bool standBST<T>::searchNode(const T &key) {

	// The tree is empty
	if(head == nullptr) {
		std::cerr << "search failed" << std::endl;
		return false;
	}

	//search the node
	std::stack< treeNode<T>* > store;
	store.push(head);
	while(store.size() != 0) {
		treeNode<T> *temp = store.top();
		store.pop();

		if(key == temp->key) 
			return true;
		else if(key < temp->key) {
			if(temp->left == nullptr) 
				return false;
			store.push(temp->left);
		}
		else {
			if(temp->right == nullptr)
				return false;
			store.push(temp->right);
		}
	}

	return false;
}

template<typename T> 
bool standBST<T>::deleteNode(const T &key) {

	// The tree is empty
	if(head == nullptr) {
		std::cerr << "deletion failed" << std::endl;
		return false;
	}

	treeNode<T> *cur = head;
	treeNode<T> *parent = nullptr;
	while(cur != nullptr) {
		if(cur->key < key) {
			parent = cur;
			cur = cur->right;
		}
		else if(cur->key > key) {
			parent = cur;
			cur = cur->left;
		}
		// cur->key == key
		else {
			treeNode<T> *del = nullptr;
			if(cur->left == nullptr) {
				if(parent == nullptr) {
					del = cur;
					head = cur->right;
					delete del;
					del = nullptr;
					size--;
					return true;
				}
				else if(parent->left == cur) {
					del = cur;
					parent->left = cur->right;
					delete del;
					del = nullptr;
					size--;
					return true;
				}
				else {
					del = cur;
					parent->right = cur->right;
					delete del;
					del = nullptr;
					size--;
					return true;
				}
			}
			else if(cur->right == nullptr) {
				if(parent == nullptr) {
					del = cur;
					head = cur->left;
					delete del;
					del = nullptr;
					size--;
					return true;
				}
				else if(parent->left == cur) {
					del = cur;
					parent->left = cur->left;
					delete cur;
					del = nullptr;
					size--;
					return true;
				}
				else {
					del = cur;
					parent->right = cur->left;
					delete del;
					del = nullptr;
					size--;
					return true;
				}
			}
			else {
				del = cur;
				parent = nullptr;
				treeNode<T> *rightFirst = cur->right;
				if(rightFirst->left == nullptr) {
					cur->key = rightFirst->key;
					del = rightFirst;
					cur->right = rightFirst->right;
					delete del;
					del = nullptr;
					size--;
					return true;
				}

				while(rightFirst->left != nullptr) {
					parent = rightFirst;
					rightFirst = rightFirst->left;
				}
				cur->key = rightFirst->key;
				del = rightFirst;
				parent->left = rightFirst->right;
				delete del;
				del = nullptr;
				size--;
				return true;
			}
		}
	}

	return false;
}

template<typename T>
int standBST<T>::getSize() {
	return size;
}

template<typename T>
treeNode<T>* standBST<T>::getHead() {
	return head;
}

template<typename T>
void standBST<T>::inOrder() {
	return inOrderTra(this->getHead());
}

template<typename T>
void standBST<T>::preOrder() {
	return preOrderTra(this->getHead());
}

template<typename T>
void standBST<T>::postOrder() {
	return postOrderTra(this->getHead());
}

template<typename T>
void standBST<T>::inOrderTra(const treeNode<T>* node) {
	if(node == nullptr)
		return;

	inOrderTra(node->left);
	std::cout << node->key << std::endl;
	inOrderTra(node->right);
}

template<typename T>
void standBST<T>::preOrderTra(const treeNode<T>* node) {
	if(node == nullptr)
		return;

	std::cout << node->key << std::endl;
	preOrderTra(node->left);
	preOrderTra(node->right);
}

template<typename T>
void standBST<T>::postOrderTra(const treeNode<T>* node) {
	if(node == nullptr)
		return;

	postOrderTra(node->left);
	postOrderTra(node->right);
	std::cout << node->key << std::endl;
}

template<typename T>
void standBST<T>::printTree() {
	if(head == nullptr)
		return;

	std::queue< std::pair<treeNode<T>*, int> > tra;
	tra.push(std::make_pair(head, 0));
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