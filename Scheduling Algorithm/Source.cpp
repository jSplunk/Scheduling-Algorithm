#include <iostream>
#include <chrono>

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
		while (front != nullptr) delete NodeDequeue(); // Clearing our allocated memory for the Queue nodes
	}
	void Enqueue(int i, int priority = 0) // Enqueue function for enqueuing items in our Queue, which takes two integer parameters, one for the value of the Node, and one for the priority of the Node
	{
		Node* tmp = new Node(i, back, nullptr, priority); // Creating a new Node pointer, with 4 different parameters
		try // A trya dn catch block to see if the following code throws any exceptions
		{
			if (!(priority > 10 || priority < 1)) // Checking if our priority integer is out of bounds, in our case if the value exceeds 10 and if it is lower than 0, if it is we throw an exception
			{
				back = tmp; // Make sure the back will always be the the new entry in the queue

				if (front == nullptr) front = back; // If there is no front node pointer in the Queue, then the front node is equal to the back node
				else
				{
					tmp = back->getNext(); //Seting a temporary Node to the new front element in the Queue 
					tmp->setPrev(back); //Set the temporary front Node's pointer to the back of the Queue
					front = tmp; //Set the front Node to equal the temporary front Node
				}
			}
			else
			{
				throw priority; // If the priority is outside of the bounds
			}
		}
		catch (int e) // Catches the exception that was thrown when priority is out of bounds
		{
			std::cout << e << " Not a valid priority, only between 1-10" << std::endl; // Printing a message out to the screen, informing about an unvalid priority that the user entered
			exit(-1);
		}
	}
	int Dequeue(void) // Dequeuing function with 0 arguments that returns the value of the deleted node
	{
		Node* tmp = NodeDequeue(); // Sets a temporary Node to be the Node we delete from the Queue
		int ret = 0; //Initianlizing a variable to store the priority value of the Node we are deleting
		try //A try and catch block which tries to delete the pointer which has been choosen, and return the value
		{
			if (tmp != nullptr) // As long as the Node we are deleting isn't a null pointer
			{
				ret = tmp->getPriority(); // Store the priority in our previously made variable
				delete tmp; // Delete the Node we are deleting
				return ret; // Return the value of the priority we stored
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
	int val;
	Node* NodeDequeue(void)
	{
		Node *tmp = front;
		val = 0;
		if (front != nullptr)
		{
			front = nodeToDelete(front, val);

			if (front != nullptr)
			{
				if (front->getPrev() != nullptr && front->getNext() != nullptr)
				{
					tmp = front;
					front->getPrev()->setNext(front->getNext());
					front->getNext()->setPrev(front->getPrev());
				}
				if (front->getPrev() == nullptr)
				{
					tmp = front;
					back = front->getNext();
					if (back != nullptr) back->setPrev(nullptr);
				}
				else if (front->getNext() == nullptr)
				{
					tmp = front;
					front = front->getPrev();
					if (front != nullptr) front->setNext(nullptr);
				}
				front = back;
			}
		}
		else
		{
			tmp = back;
			back = front;
		}
		return tmp;

	}

	Node* nodeToDelete(Node* front, int val)
	{
		while (front != nullptr)
		{
			if (counter < 2)
			{
				if (front->getPriority() > val)
				{
					val = front->getPriority();
				}
			}
			else
			{
				val = front->getPriority();
			}
			if (front->getNext() == nullptr) break;
			front = front->getNext();

		}


		while (front != nullptr)
		{

			if (counter < 2 && front->getPriority() == val)
			{
				counter++;
				return front;
			}
			if (counter >= 2 && front->getPriority() == val)
			{
				counter = 0;
				return front;
			}
			/*else if (counter >= 2 && front->getPriority() != val)
			{
				counter = 0;
				return front;
			}*/
			front = front->getPrev();
		}


		/*front = back;
		while (front != nullptr)
		{
			if (front->getPriority() == val && counter < 2)
			{
				counter++;
				return front;
			}
			if (counter >= 2 && front->getPriority() == val)
			{
				return front;
			}
			else if (counter >= 2 && front->getPriority() != val)
			{
				counter = 0;
				return front;
			}

			front = front->getNext();
		}*/

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
	s.Enqueue(20, 2);
	s.Enqueue(20, 7);
	s.Enqueue(20, 5);
	s.Enqueue(11, 1);
	s.Enqueue(11, 2);
	s.Enqueue(11, 6);
	s.Enqueue(15, 9);
	s.Enqueue(15, 8);
	s.Enqueue(15, 7);
	s.Enqueue(78, 10);
	s.Enqueue(66, 10);
	s.Enqueue(55, 10);
	s.Enqueue(44, 10);
	s.Enqueue(33, 10);
	s.Enqueue(22, 10);
	s.Enqueue(89, 10);
	s.Enqueue(16, 3);
	s.Enqueue(17, 8);
	s.Enqueue(36, 9);


	std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
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
	std::cout << s.Dequeue() << std::endl;
	std::cout << s.Dequeue() << std::endl;
	std::cout << s.Dequeue() << std::endl;
	std::cout << s.Dequeue() << std::endl;
	std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();

	std::cout << "Time difference in ms = " << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() << std::endl;


	getchar();
	return 0;
}