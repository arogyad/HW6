
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

template <typename T>
void LinkedList<T>::insert(size_t pos, T item) {
	if(pos < 0 || pos > this->numItems) {
		throw invalid_argument("Cannot insert in position");
	}

	if(pos == 0) {
		this->push_front(item);
		return;
	}

	if(pos == this->numItems) {
		this->push_back(item);
		return;
	}

	size_t idx = 0;
	Node<T>* curr = this->head;

	while(idx != pos) {
		curr = curr->next;
		idx++;
	}

	Node<T>* insert_node = new Node<T>;
	insert_node->data = item;

	Node<T>* prev = curr->prev;
	prev->next = insert_node;
	curr->prev = insert_node;
	insert_node->prev = prev;
	insert_node->next = curr;
	
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



