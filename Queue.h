#pragma once
#include <iostream>
using namespace std;
template <class T>
class QNode
{
public:
	T data;
	QNode<T>* next = nullptr;

	QNode() : data(0)
	{}

	QNode(T d) : data(d)
	{}
};

template <class T>
class Queue
{
public:
	QNode<T>* front = nullptr;
	QNode<T>* rear = nullptr;
	int num_items;
	Queue()
	{
		front = rear = nullptr;
		num_items = 0;
	}


	void Concatenate(Queue q)
	{
		if (front == nullptr && rear == nullptr)
		{
			front = q.front;
			rear = q.rear;
		}
		else
		{
			rear->next = q.front;
			rear = q.rear;

		}
	}

	void enqueue(T data);
	T dequeue();
	void print();
	T Front()
	{
		return front->data;
	}
	bool isEmpty()
	{
		if (front == nullptr && rear == nullptr)
			return true;
		else return false;
	}

};

template <class T>
void Queue<T>::enqueue(T data)
{
	QNode<T>* newNode = new QNode<T>(data);
	if (isEmpty())
	{
		front = rear = newNode;
		num_items++;
	}
	else
	{
		rear->next = newNode;
		rear = newNode;
		num_items++;

	}

}

template <class T>
T Queue<T>::dequeue()
{
		T tempData = front->data;
		QNode<T>* temp = front;
		front = front->next;
		if (front == nullptr) rear = nullptr;
		delete temp;
		num_items--;
		return tempData;
}

template <class T>
void  Queue<T>::print()
{
	if (isEmpty()) return;
	else
	{
		QNode<T>* temp = front;
		while (temp != rear->next)
		{
			cout << temp->data << " ";
			temp = temp->next;
		}
	}
}