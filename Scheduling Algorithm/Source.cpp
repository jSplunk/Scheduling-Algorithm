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
	Queue(void)  // Constuctor of our Queue class
	{
		front = back = nullptr; // Default values of front and back pointers are set to null
	}
	~Queue(void) // Deconstructor of our Queue class
	{
		while(front != nullptr) delete NodeDequeue(); // Clearing our allocated memory for the Queue nodes
	}
	void Enqueue(int i, int priority = 0) // Enqueue function for enqueuing items in our Queue, which takes two integer parameters, one for the value of the Node, and one for the priority of the Node
	{
		Node* tmp = new Node(i, back, nullptr, priority); // Creating a new Node pointer, with 4 different parameters
		try 
		{
			if (!(priority > 10 || priority < 1)) // Checking if our priority integer is out of bounds, in our case if the value exceeds 10 and if it is lower than 0, if it is we throw an exception
			{
				back = tmp; // Make sure the back will always be the the new entry in the queue

				if (front == nullptr) front = back; // If there is no front node pointer in the Queue, then the front node is equal to the back node
				else
				{
					tmp = back->getNext(); // Make the the temporary Node equal the next Node in the line, which then sets the front Node as that temporary node, which makes it represent the node infront of the current node
					tmp->setPrev(back);
					front = tmp;
				}
			}
			else
			{
				throw priority; // If the priority is outside of the bounds
			}
		}
		catch (int e)
		{
			std::cout << e << " Not a valid priority, only between 1-10" << std::endl;
			exit(-1);
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
				ret = tmp->getPriority();
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
		Node* tmp = back;
		int val = 0;
		if (back != nullptr) val = back->getPriority();
		if (tmp != nullptr)
		{
			tmp = nodeToDelete(tmp, val);

			if (tmp != nullptr)
			{
				tmp = updateScheduler(tmp);
			}
		}
		return tmp;
		
	}
	Node* updateScheduler(Node* tmp) // A boolean fuctions which returns true if no exceptions were thrown
	{
		if (tmp->getPrev() != nullptr && tmp->getNext() != nullptr) {
			tmp->getPrev()->setNext(tmp->getNext());
			tmp->getNext()->setPrev(tmp->getPrev());
		}
		if (tmp->getPrev() == nullptr)
		{
			back = tmp->getNext();
			if (back != nullptr) {
				back->setPrev(nullptr);
				if (back->getNext() != nullptr) back->getNext()->setPrev(back);
				front = back->getNext();
			}

		}
		if (tmp->getNext() == nullptr)
		{
			front = tmp->getPrev();
			if (front != nullptr)
			{
				front->setNext(nullptr);
				if (front->getPrev() != nullptr) front->getPrev()->setNext(front);
			}
		}
		return tmp;
	}

	Node* nodeToDelete(Node* tmp, int val)
	{
		while (tmp != nullptr)
		{
			if (tmp->getPriority() > val)
				val = tmp->getPriority();
			tmp = tmp->getNext();
		}

		tmp = back;
		while (tmp != nullptr)
		{
			if (tmp->getPriority() == val && counter < 2)
			{
				counter++;
				return tmp;
			}
			if (counter >= 2 && tmp->getPriority() != val)
			{
				counter = 0;
				return tmp;
			}
			tmp = tmp->getNext();
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
	s.Enqueue(11, 2);
	s.Enqueue(15, 7);
	s.Enqueue(13, 9);
	s.Enqueue(16, 3);
	s.Enqueue(17, 8);
	s.Enqueue(36, 10);
	s.Enqueue(45, 6);
	s.Enqueue(67, 10);
	s.Enqueue(67, 10);
	s.Enqueue(67, 10);
	s.Enqueue(67, 10);
	s.Enqueue(67, 10);
	s.Enqueue(67, 10);
	std::cout << s.Dequeue() << std::endl;
	std::cout << s.Dequeue() << std::endl;
	std::cout << s.Dequeue() << std::endl;
	std::cout << s.Dequeue() << std::endl;
	std::cout << s.Dequeue() << std::endl;
	std::cout << s.Dequeue() << std::endl;
	std::cout << s.Dequeue() << std::endl;
	std::cout << s.Dequeue() << std::endl;
	std::cout << s.Dequeue() << std::endl;
	std::cout << s.Dequeue() << std::endl;
	std::cout << s.Dequeue() << std::endl;
	std::cout << s.Dequeue() << std::endl;
	std::cout << s.Dequeue() << std::endl;
	std::cout << s.Dequeue() << std::endl;
	std::cout << s.Dequeue() << std::endl;

	getchar();
	return 0;
}
