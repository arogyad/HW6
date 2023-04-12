all:
	g++ -g -Wall --std=c++14 RedBlackTree.cpp RedBlackTreeTests.cpp -o rdt-tests

try:
	./rdt-tests

run: all try
