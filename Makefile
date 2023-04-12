all:
	g++ -g -Wall --std=c++14 RedBlackTree.cpp RedBlackTreeTestsFirstStep.cpp -o rdt-tests-1
	g++ -g -Wall --std=c++14 RedBlackTree.cpp RedBlackTreeTests.cpp -o rdt-tests-2

try:
	./rdt-tests-2

run: all try
