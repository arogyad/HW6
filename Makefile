all:
	g++ -g -Wall --std=c++14 RedBlackTree.cpp SpeedTest.cpp -o rbt-tests

try:
	./rbt-tests

run: all try
