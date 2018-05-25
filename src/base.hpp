#ifndef BASE_H
#define BASE_H

template<typename T>
class BST {
public:
	BST() {};
	virtual ~BST() {};
	virtual bool insertNode(const T &key) = 0;
	virtual bool searchNode(const T &key) = 0;
	virtual bool deleteNode(const T &key) = 0;

	// self defined
	virtual void inOrder() = 0;
	virtual void preOrder() = 0;
	virtual void postOrder() = 0;
	virtual int getSize() = 0;
	virtual void printTree() = 0;

};


#endif