#include <iostream>

class Node
{
public:
	Node(int value, Node* nextptr = nullptr, Node* prevptr = nullptr, int currentpriority = 0);
	int getVal(void)
	{
		return value;
	}
	Node* getNext(void)
	{
		return next;
	}
	Node* getPrev(void)
	{
		return prev;
	}
	void setVal(int value)
	{
		this->value = value;
	}
	void setPrev(Node* prevptr)
	{
		this->prev = prevptr;
	}
	void setNext(Node* nextptr)
	{
		this->next = next;
	}
	int getPriority(void)
	{
		return priority;
	}
	void setPriority(int priority)
	{
		this->priority = priority;
	}
private:
	Node* next;
	Node* prev;
	int priority;
	int value;
};
class Stack
{
public:
	Stack(void);
	~Stack(void);
	void Push(int value);
	Node* NodePop(void);
	int Pop(void);
private:
	Node* top;
};
class Queue
{
public:
	Queue(void);
	~Queue(void);
	void Enqueue(int i, int priority = 0);
	int Dequeue(void);
protected:
	Node* back;
	Node* front;
private:
	virtual Node* NodeDequeue(void);
};
class Scheduler : public Queue
{
public:
	Scheduler(int i, int priority = 0) // Constuctor of our Scheduler class, which takes in two integer parameters, a value of the process and a priority of the process
	{
		if (checkPriorityAndVal(i, priority)) // Checking if i and priority are bad values for the purpose of our implementation
			Enqueue(i, priority); // Enqueuing the first process as the value of i, and the priority of priority
	}
	~Scheduler() 
	{
		delete back, front; // Clearing our allocated memory for the Queue back and front pointers
	}
	void enqueue(int i, int priority = 0)
	{
		if (checkPriorityAndVal(i, priority)) // Checking if i and priority are bad values for the purpose of our implementation
			Enqueue(i, priority); // Enqueuing a process as the value of i, and the priority of priority
	}
	bool checkPriorityAndVal(int i, int priority = 0) // A boolean fuctions which returns true if no exceptions were thrown
	{
		try
		{
			i; // Checking if i is an integer, and if it is not, then we throw an exception for our catch block
			if (priority > 10 && priority < 0) // Checking if our priority integer is out of bounds, in our case if the value exceeds 10 and if it is lower than 0, if it is we throw an exception
			{
				throw priority; // Throws priority as the exception for our catch block
			}
			else
			{
				return true; // Returning that everything went well and no exceptions were thrown
			}
		}
		catch (int e) // Catching an integer exception of either the value of the process or the value of the priority and displaying the value
		{
			std::cout << "Bad integer value " << e << std::endl; // Displaying that we catched a bad integer value to the user, and displaying that value
			return false; // Returning false since we got an exception for our integer value
		}
	}
private:
	Node* NodeDequeue(void)
	{
		Dequeue();
	}
};