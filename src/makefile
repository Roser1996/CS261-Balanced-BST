# test: test.o bst.o AVLbst.o
# 	g++ test.o bst.o AVLbst.o -o test

# test.o: test.cpp bst.h AVLbst.h
# 	g++ -c test.cpp

# bst.o: bst.cpp bst.h
# 	g++ -c bst.cpp

# AVLbst.o: AVLbst.cpp AVLbst.h 
# 	g++ -c AVLbst.cpp

test: test.o
	g++ test.o -o test

test.o: test.cpp base.hpp bst.hpp AVLbst.hpp treap.hpp splay.hpp
	g++ -c test.cpp

clean:
	rm *.o