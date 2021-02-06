/*
** RPI Game Architecture Engine
**
** Portions adapted from:
** Viper Engine - Copyright (C) 2016 Velan Studios - All Rights Reserved
**
** This file is distributed under the MIT License. See LICENSE.txt.
*/

#include "ga_queue.h"
#include <mutex>          // std::mutex
#include <iostream>

struct node {
	void* value;
	node* next;
};

node* head;
node* tail;
std::mutex head_lock;
std::mutex tail_lock;
int node_num = 0;

ga_queue::ga_queue(int node_count)
{
	// TODO:
	// Initialize the queue.
	// For extra credit, preallocate 'node_count' elements (instead of
	// allocating on push).
	// See https://www.research.ibm.com/people/m/michael/podc-1996.pdf
	node* n = new node;
	n->next = nullptr;
	head = n;
	tail = n;
	//head_lock.unlock();
	//tail_lock.unlock();
	node_num = 0;
}

ga_queue::~ga_queue()
{
	node_num = 0;
	while (head->next != nullptr) {
		node* next = head->next;
		free(head);
		head = next;
	}
	// TODO:
	// Free any resources held by the queue.
	// See https://www.research.ibm.com/people/m/michael/podc-1996.pdf	
}

void ga_queue::push(void* data)
{
	// TODO:
	// Push 'data' onto the queue in a thread-safe manner.
	// If you preallocated 'node_count' elements, and if the queue is full when
	// this function is called, you must block until another thread pops an
	// element off the queue.
	// See https://www.research.ibm.com/people/m/michael/podc-1996.pdf
	node* n = new node;
	n->value = data;
	n->next = nullptr;
	tail_lock.lock();
		tail->next = n;
		tail = n;
	tail_lock.unlock();
	node_num++;
}

bool ga_queue::pop(void** data)
{
	// TODO:
	// Pop one element off the queue in a thread-safe manner and place it in
	// the memory pointed to by 'data'.
	// If the queue is empty when this function is called, return false.
	// Otherwise return true.
	// See https://www.research.ibm.com/people/m/michael/podc-1996.pdf
	head_lock.lock();
		node* n = head;
		node* new_head = n->next;
		if (new_head == nullptr)
		{
			head_lock.unlock();
			return false;
		}
		*data = new_head->value;
		head = new_head;
	head_lock.unlock();
	free(n);
	node_num--;
	return true;
}

int ga_queue::get_count() const
{
	// TODO:
	// Get the number of elements currently in the queue.
	return node_num;
}
