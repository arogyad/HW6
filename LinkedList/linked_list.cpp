
#include "linked_list.h"
#include <stdexcept>
//#include <iostream>

template <typename T> 
LinkedList<T>::~LinkedList() {
	Node<T>* curr = this->head;

	while(curr != nullptr) {
		Node<T>* next = curr->next;
		delete curr;
		curr = next;
	}
}

/**
 * Inserts an item @param item at position @param pos in the list
 */
template <typename T>
void LinkedList<T>::insert(size_t pos, T item) {
	// If the insertion is at head
	if(pos == 0) {
		this->push_front(item);
		return;
	}

	// if the insertion is at tail
	if(pos == this->numItems) {
		this->push_back(item);
		return;
	}

	// before the first or after the last gives error
	if(pos < 0 || pos > this->numItems) {
		throw std::invalid_argument("Cannot insert in this position.");
	}

	size_t idx = 0;
	Node<T>* curr = this->head;

	while(idx != pos) {
		curr = curr->next;
		idx++;
	}

	Node<T>* insert_node = new Node<T>;
	insert_node->data = item;

	/**
	 * Given: 1 <-> 2 <-> 3 <-> 4
	 * insert(2, 0)
	 * prev = 2
	 * curr = 3
	 * inserted_node = 0
	 */
	Node<T>* prev = curr->prev;
	// 2 -> 0
	prev->next = insert_node;
	// 0 <- 3
	curr->prev = insert_node;
	// 2 <- 0
	insert_node->prev = prev;
	// 0 -> 3
	insert_node->next = curr;
	
	// Final: 1 <-> 2 <-> 0 <-> 3 <-> 4
	this->numItems++;
}

template <typename T> 
void LinkedList<T>::push_back(T item){
	Node<T> *n = new Node<T>;
	n->data = item;
	numItems++;
	
	if(head == nullptr){
		head = n;
		tail = n;
		return;
	}

	tail->next = n;
	n->prev = tail;
	tail = n;	
}


template <typename T>
void LinkedList<T>::push_front(T item){
	Node<T> *n = new Node<T>;
	n->data = item;
	numItems++;

	if(head == nullptr){
		head = n;
		tail = n;
		return;
	}

	head->prev = n;
	n->next = head;
	head = n;
}


template <typename T>
T LinkedList<T>::at(size_t idx){
	if(idx >= numItems){
		throw std::invalid_argument("List index out of range: " + std::to_string(idx));
	}

	Node<T> *n = get_node(idx);
	return n->data;
}


template <typename T>
Node<T> *LinkedList<T>::get_node(size_t idx){

	size_t i = 0;
	Node<T> *cur = head;
	while(i < idx){
		cur = cur->next;
		i++;
	}

	return cur;
}



