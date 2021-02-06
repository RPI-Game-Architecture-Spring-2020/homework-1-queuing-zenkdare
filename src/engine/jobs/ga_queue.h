#pragma once

/*
** RPI Game Architecture Engine
**
** Portions adapted from:
** Viper Engine - Copyright (C) 2016 Velan Studios - All Rights Reserved
**
** This file is distributed under the MIT License. See LICENSE.txt.
*/

/*
** Thread-safe queue.
** https://www.research.ibm.com/people/m/michael/podc-1996.pdf
*/

#include <mutex>          // std::mutex
class ga_queue
{
public:
	struct node {
		void* value;
		node* next;
	};
	ga_queue(int node_count);
	~ga_queue();

	void push(void* data);
	bool pop(void** data);

	int get_count() const;
private:
	node* head;
	node* tail;
	std::mutex head_lock;
	std::mutex tail_lock;
	int node_num = 0;
};
