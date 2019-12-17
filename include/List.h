#pragma once
#ifndef _LIST_H_
#define _LIST_H_

#include <iostream>

using std::size_t;

template <typename ValType>
class List
{
private:
	struct Node
	{
		ValType data;
		Node *next;
	};

	Node *top;
	size_t size;
	Node* Prev(Node*);
	Node* Find(size_t);

public:
	class Iterator
	{
	private:
		Node* cur_node;

	public:
		Iterator(Node* nd) : cur_node(nd) {}
		Iterator(const Iterator& it) : cur_node(it.cur_node) {}
		Iterator& operator= (const Iterator&);
		bool operator==(const Iterator& it) const { return (cur_node == it.cur_node); }
		bool operator!=(const Iterator& it) const { return (cur_node != it.cur_node); }
		ValType operator*() const;
		Node* operator->() const { return cur_node; }
		Iterator operator++();
		Iterator operator++(int);
	};

	Iterator begin() const;
	Iterator end() const;

	List() : top(NULL), size(0) {}
	List(size_t);
	List(const List&);
	List(size_t, size_t);
	~List();

	void Push_top(ValType);
	void Push_bot(ValType);
	ValType Pop_top();
	ValType Pop_bot();
	void Insert(size_t, ValType);
	void Delete(size_t);
	void Set(size_t, ValType);
	ValType Get(size_t);
	ValType& operator[](size_t);
	ValType Top() const;
	bool Empty() const { return (size == 0); }
	size_t GetSize() const { return size; }
	void Print() const;

	bool IsLooped();
	bool Reverse();
};

template <typename ValType>
typename List<ValType>::Iterator& List<ValType>::Iterator::operator=(const Iterator& it)
{
	if (this == &it)
		return *this;
	cur_node = it.cur_node;
	return *this;
}

template <typename ValType>
typename ValType List<ValType>::Iterator::operator*() const
{
	if (cur_node)
		return cur_node->data;
	else
		throw "Error: out of range";
}

template <typename ValType>
typename List<ValType>::Iterator List<ValType>::Iterator::operator++()
{
	if (cur_node)
	{
		cur_node = cur_node->next;

		return *this;
	}
	else
		throw "Error: out of range";
}

template <typename ValType>
typename List<ValType>::Iterator List<ValType>::Iterator::operator++(int)
{
	if (cur_node)
	{
		List<ValType>::Iterator out(*this);
		cur_node = cur_node->next;

		return out;
	}
	else
		throw "Error: out of range";
}

template <typename ValType>
typename List<ValType>::Iterator List<ValType>::begin() const
{
	return Iterator(top);
}

template <typename ValType>
typename List<ValType>::Iterator List<ValType>::end() const
{
	return Iterator(NULL);
}


template <typename ValType>
typename List<ValType>::Node* List<ValType>::Prev(List<ValType>::Node* node)
{
	if (Empty() || (node == top))
		return NULL;
	Node* tmp = head;
	while (tmp->next != node)
		tmp = tmp->next;
	return tmp;
}

template <typename ValType>
typename List<ValType>::Node* List<ValType>::Find(size_t index)
{
	Node* tmp = top;
	for (size_t i = 0; i < index; i++)
		tmp = tmp->next;
	
	return tmp;
}


template <typename ValType>
List<ValType>::List(size_t sz)
{
	size = sz;
	top = NULL;
	for (int i = 0; i < size; i++)
	{
		if (Node* tmp = new Node)
		{
			tmp->next = top;
			top = tmp;
		}
		else
			throw "Error: failed to allocate memory";
	}
}

template <typename ValType>
List<ValType>::List(const List<ValType>& ls)
{
	size = ls.size;
	top = NULL;
	Node* input_node = ls.top;
	Node* cur_node, * prev_node = NULL;
	while (input_node != NULL)
	{
		cur_node = new Node;
		cur_node->data = input_node->data;
		cur_node->next = NULL;

		if (top == NULL)
		{
			top = cur_node;
			prev_node = cur_node;
		}
		else
		{
			prev_node->next = cur_node;
			prev_node = prev_node->next;
		}

		input_node = input_node->next;
	}
}

template <typename ValType>
List<ValType>::List(size_t sz, size_t loop_index)
{
	if (sz < 2 || loop_index > sz - 2)
		throw "Error: failed to create a looped list";

	size = sz;
	if (Node* loop = new Node)
	{
		top = loop;
		for (int i = 1; i < size; i++)
		{
			if (Node* tmp = new Node)
			{
				if (i == size - loop_index - 1)
					loop->next = tmp;
				tmp->next = top;
				top = tmp;
			}
			else
				throw "Error: failed to allocate memory";
		}
	}
	else
		throw "Error: failed to allocate memory";
}

template <typename ValType>
List<ValType>::~List()
{
	while (top)
		Pop_top();
}

template <typename ValType>
void List<ValType>::Push_top(ValType elem)
{
	if (Node* tmp = new Node)
	{
		tmp->data = elem;
		tmp->next = top;
		top = tmp;
		size++;
	}
	else
		throw "Error: failed to allocate memory";
}

template <typename ValType>
void List<ValType>::Push_bot(ValType elem)
{
	Node* tmp = top;
	while (tmp->next != NULL)
		tmp = tmp->next;
	if (Node* last = new Node)
	{
		last->data = elem;
		last->next = NULL;
		tmp->next = last;
		size++;
	}
	else
		throw "Error: failed to allocate memory";
}


template <typename ValType>
ValType List<ValType>::Pop_top()
{
	if (size == 0)
		throw "Error: list is empty";

	Node* tmp = top;
	ValType top_data = top->data;

	top = top->next;
	delete tmp;
	size--;

	return top_data;
}


template <typename ValType>
ValType List<ValType>::Pop_bot()
{
	if (size == 0)
		throw "Error: list is empty";

	Node* tmp = top;
	//for (size_t i = 1; i < size - 1; i++)
		//tmp = tmp->next;

	while (tmp->next->next != NULL)
		tmp = tmp->next;

	Node* bot = tmp->next;
	tmp->next = bot->next;
	ValType bot_data = bot->data;
	delete bot;
	size--;

	return bot_data;
}

template <typename ValType>
void List<ValType>::Insert(size_t index, ValType data)
{
	if (index >= size)
		throw "Error: incorrect index";

	Node* tmp = top;
	for (size_t i = 1; i <= index - 1; i++)
		tmp = tmp->next;

	Node* following = tmp->next;
	if (Node* new_elem = new Node)
	{
		new_elem->data = data;
		new_elem->next = following;
		tmp->next = new_elem;
		size++;
	}
	else
		throw "Error: failed to allocate memory";
}

template <typename ValType>
void List<ValType>::Delete(size_t index)
{
	if (index >= size)
		throw "Error: incorrect index";

	Node* tmp = top;
	for (size_t i = 1; i <= index - 1; i++)
		tmp = tmp->next;

	Node* following = tmp->next;
	tmp->next = following->next;
	delete following;
	size--;
}

template <typename ValType>
void List<ValType>::Set(size_t index, ValType data)
{
	if (index >= size)
		throw "Error: incorrect index";

	Node* tmp = Find(index);
	tmp->data = data;
}


template <typename ValType>
ValType List<ValType>::Get(size_t index)
{
	if (index >= size)
		throw "Error: incorrect index";

	Node* tmp = Find(index);
	return tmp->data;
}

template <typename ValType>
ValType& List<ValType>::operator[](size_t index)
{
	if (index >= size)
		throw "Error: incorrect index";

	Node* tmp = Find(index);
	return tmp->data;
}

template <typename ValType>
ValType List<ValType>::Top() const
{
	if (size == 0)
		throw "Error: list is empty";
	return top->data;
}

template <typename ValType>
void List<ValType>::Print() const
{
	for (Iterator it = begin(); it != end(); it++)
		cout << *it << ' ';
	cout << endl;
}

template <typename ValType>
bool List<ValType>::IsLooped()
{
	if (size < 2)
		return false;

	Node* ptr1 = top->next, * ptr2 = top;
	while (ptr1 != NULL && ptr1 != ptr2)
	{
		ptr1 = ptr1->next;
		if (ptr1 != NULL)
			ptr1 = ptr1->next;
		ptr2 = ptr2->next;
	}

	return ptr1;
}


template <typename ValType>
bool List<ValType>::Reverse()
{
	if (size < 2)
		return true;

	Node* ptr1 = NULL, * ptr2 = top, * ptr3 = top->next;
	while (ptr3 != NULL && ptr3 != top)
	{
		ptr2->next = ptr1;
		ptr1 = ptr2;
		ptr2 = ptr3;
		ptr3 = ptr3->next;
	}

	ptr2->next = ptr1;
	if (ptr3 == NULL)
		top = ptr2;
	else
	{
		ptr3->next = ptr2;
		top = ptr3;
	}

	return (!ptr3);
}

#endif // !_LIST_H_
