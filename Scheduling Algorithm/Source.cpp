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
	int counter = 0;
	Node* NodeDequeue(void)
	{
		Node* tmp = checkPriority(front, front->getPriority());
		
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
	Node* checkPriority(Node* a, int priority) // A boolean fuctions which returns true if no exceptions were thrown
	{
		try
		{
			if (priority > 10 || priority < 1) // Checking if our priority integer is out of bounds, in our case if the value exceeds 10 and if it is lower than 0, if it is we throw an exception
			{
				throw a->getPriority(); // Throws priority as the exception for our catch block
			}
			else
			{
				Node* tmp = a;
				int val = priority;
				if (counter == 3)
				{
					counter = 0;
					return tmp;
				}
				while (tmp->getPrev() != nullptr)
				{
					if (tmp->getPrev()->getPriority() < 10 || tmp->getPrev()->getPriority() > 1)
					{
						if (tmp->getPrev()->getPriority() > val)
							val = tmp->getPrev()->getPriority();
						tmp = tmp->getPrev();
					}
					else { throw tmp->getPriority(); }
				}
				tmp = a;
				while (tmp->getPrev() != nullptr)
				{
					if (tmp->getPrev()->getPriority() == val)
						counter++;
						return tmp; // Returning that everything went well and no exceptions were thrown
					tmp = tmp->getPrev();
				}
				
				
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
	/*Queue s;
	s.Enqueue(20, 1);
	s.Enqueue(10, 2);
	std::cout << s.Dequeue() << std::endl;
	std::cout << s.Dequeue() << std::endl;
	std::cout << s.Dequeue() << std::endl;*/

	Scheduler s;
	s.Enqueue(20, 1);
	s.Enqueue(10, 2);
	std::cout << s.Dequeue() << std::endl;
	std::cout << s.Dequeue() << std::endl;
	std::cout << s.Dequeue() << std::endl;

	getchar();
	return 0;
}
