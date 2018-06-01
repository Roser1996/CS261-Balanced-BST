#include <iostream>
#include <fstream>
#include <vector>
#include <ctime>

#include "base.hpp"
#include "bst.hpp"
#include "AVLbst.hpp"
#include "treap.hpp"
#include "splay.hpp"

#define TESTSIZE 10000
#define NUMBERSIZE 10000000

using namespace std;

void testFunction(BST<int>* &b, vector<int> &array, vector<int> &testArray, ofstream &file) {
	clock_t begin, end;
	begin = clock();
	for(int i = 0; i < array.size(); i++) 
		b->insertNode(array[i]);
	end = clock();
	double insert_time = 1000 * (end - begin) / CLOCKS_PER_SEC;

	begin = clock();
	for(int i = 0; i < testArray.size(); i++)
		b->searchNode(testArray[i]);
	end = clock();
	double search_time = 1000 * (end - begin) / CLOCKS_PER_SEC;

	begin = clock();
	for(int i = 0; i < testArray.size(); i++)
		b->deleteNode(testArray[i]);
	end = clock();
	double delete_time = 1000 * (end - begin) / CLOCKS_PER_SEC;

	file.precision(8);
	file << "Insert Time: " << fixed << insert_time << "\n";
	file << "Search Time: " << fixed << search_time << "\n";
	file << "Delete Time: " << fixed << delete_time << "\n";

	return;
}

int main() {

	srand(time(nullptr));


	vector<int> array(TESTSIZE, 0);
	vector<int> testArray(TESTSIZE, 0);
	for(int i = 0; i < array.size(); i++) {
		// random case
		// array[i] = rand() % NUMBERSIZE + 1;
		// testArray[i] = rand() % NUMBERSIZE + 1;

		// worst case
		array[i] = i;
		testArray[i] = rand() % TESTSIZE + 1;
	}


	
	ofstream file;
	file.open("../results/test_results_worst_1.txt", ios::out);
	file << "Current test size: " << TESTSIZE << "\n";
	file << "Current key number size: " << NUMBERSIZE << "\n";

	// Standard BST
	BST<int>* b1 = new standBST<int>();
	file << "\n" << "Standard Binary Search Tree" << "\n";
	testFunction(b1, array, testArray, file);
	file << "\n";
	delete b1;
	b1 = nullptr;

	// AVL tree
	BST<int>* b2 = new avlBST<int>();
	file << "\n" << "AVL Tree" << "\n";
	testFunction(b2, array, testArray, file);
	file << "\n";
	delete b2;
	b2 = nullptr;

	// Treap
	BST<int>* b3 = new Treap<int>();
	file << "\n" << "Treap" << "\n";
	testFunction(b3, array, testArray, file);
	file << "\n";
	delete b3;
	b3 = nullptr;

	// Splay tree
	BST<int>* b4 = new Splay<int>();
	file << "\n" << "Splay Tree" << "\n";
	testFunction(b4, array, testArray, file);
	file << "\n";
	delete b4;
	b4 = nullptr;

	file << flush;
	file.close();

	return 0;
}