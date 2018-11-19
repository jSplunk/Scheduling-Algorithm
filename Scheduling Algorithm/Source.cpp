#include <iostream>

class Node
{
public:
	Node(int value, Node* nextptr, Node* prevptr = NULL, int currentpriority = 0)
	{
		this->value = value;
		next = nextptr;
		prev = prevptr;
		priority = currentpriority;
	}
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
		prev = prevptr;
	}
	void setNext(Node* nextptr)
	{
		next = nextptr;
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
class Stack //Works!
{
public:
	Stack(void)
	{
		top = 0;
	}
	~Stack(void)
	{

	}
	void Push(int value)
	{
		Node* tmp = new Node(value, top);
		top = tmp;
	}
	Node* NodePop(void)
	{
		Node* tmp = top;
		if (top != nullptr)
		{
			top = top->getNext();
		}
		return tmp;
	}
	int Pop(void)
	{
		
		Node* tmp = NodePop();
		int ret = 0;
		try
		{
			if (tmp != nullptr)
			{
				ret = tmp->getVal();
				delete tmp;
				return ret;
			}
			else
			{
				throw "Empty Stack";
			}
		}
		catch (const char* m)
		{
			std::cout << m << std::endl;
		}
	}
private:
	Node* top;
};
class Queue
{
public:
	Queue(void)  // Constuctor of our Queue class, which takes in two integer parameters, a value of the process and a priority of the process
	{
		front = back = NULL; // Enqueuing the first process as the value of i, and the priority of priority
	}
	~Queue(void)
	{
		while(front != NULL) delete NodeDequeue(); // Clearing our allocated memory for the Queue back and front pointers
	}
	void Enqueue(int i, int priority = 0)
	{
		Node* tmp = new Node(i, back, nullptr, priority);
		back = tmp;

		if (front == nullptr) front = back;
		else
		{
			tmp = back->getNext();
			tmp->setPrev(back);
			front = tmp;
		}
	}
	int Dequeue(void)
	{
		Node* tmp = NodeDequeue();
		int ret = 0;
		try 
		{
			if (tmp != nullptr)
			{
				ret = tmp->getVal();
				delete tmp;
				return ret;
			}
			else
			{
				throw "Queue Empty";
			}
		}
		catch (const char* m)
		{
			std::cout << m << std::endl;
		}
	}
protected:
	Node* back;
	Node* front;
private:
	virtual Node* NodeDequeue(void)
	{
		Node* tmp = front;

		if (front != nullptr)
		{
			front = front->getNext();
			if (front != nullptr) front->setNext(nullptr);
		}
		else
		{
			tmp = back;
			back = front;
		}
		return tmp;
	}
};
class Scheduler : public Queue
{
private:
	Node* NodeDequeue(void)
	{
		Node* tmp = front;
		if (checkPriority(front->getPriority()))
		{
			if (front != nullptr)
			{
				front = front->getNext();
				if (front != nullptr) front->setNext(nullptr);
			}
			else
			{
				tmp = back;
				back = front;
			}
		}
		return tmp;
	}
	bool checkPriority(int priority) // A boolean fuctions which returns true if no exceptions were thrown
	{
		try
		{
			//i; // Checking if i is an integer, and if it is not, then we throw an exception for our catch block
			if (priority > 10 || priority < 1) // Checking if our priority integer is out of bounds, in our case if the value exceeds 10 and if it is lower than 0, if it is we throw an exception
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
			std::cout << "Out of bounds priority: " << e << std::endl; // Displaying that we catched a bad integer value to the user, and displaying that value
			return false; // Returning false since we got an exception for our integer value
		}
	}
};

int main()
{
	Queue q;
	q.Enqueue(20);
	q.Enqueue(10);
	std::cout << q.Dequeue() << std::endl;
	std::cout << q.Dequeue() << std::endl;
	std::cout << q.Dequeue() << std::endl;

	getchar();
	return 0;
}
