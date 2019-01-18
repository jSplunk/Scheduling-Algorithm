#include <iostream>
//#include <chrono>

class Node // Node class serving as Nodes for our Stack, Queue and Scheduler
{
public:
	Node(int val, Node* nextptr, Node* prevptr = nullptr, int currentpriority = 0) : // Node constuctor that takes four parameters, a value, a previous Node pointer, a Next Node pointer and a priority
		priority(currentpriority), next(nextptr), prev(prevptr), value(val)
	{}

	// Getters and setters for all the attributes, value, Next pointer, Previous pointer and priority
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
	//Private attributes of the Node class
	Node* next;
	Node* prev;
	int priority;
	int value;
};
class Stack // Stack class
{
public:
	Stack(void) : // Initializer list for our stack constructor
		top(0)
	{}
	~Stack(void)
	{
		delete top; // Decontructor, that will delete the top pointer when the stack object gets destroyed
	}
	void Push(int value) // Push function, meant for pushing Nodes on top of the stack
	{
		Node* tmp = new Node(value, top); // Creating a temporary Node to store the next Node in the stack
		top = tmp; // Assigning that new node to the top Node pointer
		delete tmp; // Deleting the temporary Node
	}
	Node* NodePop(void) // NodePop function, it returns the first Node item in the stack
	{
		Node* tmp = top; // Assigns a temporary Node pointer to the current top Node Pointer
		if (top != nullptr) // As long as the top pointer isn't a null pointer
		{
			top = top->getNext(); // Shift the top pointer to the next one in the stack, since we are deleting the temporary Node we assigned before
		}
		return tmp; // Returns the temporary Node we want to delete from the stack
	}
	int Pop(void) // Pop function, which returns the value of the returned Node from the NodePop function
	{
		Node* tmp = NodePop(); // Assigning a temporary Node to serve as the Node we are deleting 
		int ret = 0; // Integer that will hold the value of the Node we are deleting
		try // Try and catch block where we are checking if the queue is empty or not
		{
			if (tmp != nullptr) // As long as the temporary Node isn't a null pointer
			{
				ret = tmp->getVal(); // Assign the value to the integer we are returning
				delete tmp; // Deleting the temporary Node
				return ret; // Returning the value of the Node we deleted
			}
			else
			{
				delete tmp; // Deleting the temporary Node
				throw "Empty Stack"; // Throwing a string to the catch block, that will tell the user that the stack is empty
			}
		}
		catch (const char* m) // Catching the thrown exception that happened if the stack is empty
		{
			std::cout << m << std::endl; // Displays the string to the user
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
		try // A try and catch block to see if the following code throws any exceptions
		{
			if (!(priority > 10 || priority < 1)) // Checking if our priority integer is out of bounds, in our case if the value exceeds 10 and if it is lower than 0, if it is we throw an exception
			{
				back = tmp; // Make sure the back will always be the the new entry in the queue

				if (front == nullptr) front = back; // If there is no front node pointer in the Queue, then the front node is equal to the back node
				else
				{
					tmp = back->getNext(); //Seting a temporary Node to the new front element in the Queue 
					tmp->setPrev(back); //Set the temporary front Node's pointer to the back of the Queue
					//front = tmp; //Set the front Node to equal the temporary front Node
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
		catch (const char* m) // Catches the Queue Empty exception if the try block throws it
		{
			std::cout << m << std::endl; // Displaying that the Queue is empty to the user
		}
	}
protected:
	Node* back; 
	Node* front;
private:
	virtual Node* NodeDequeue(void) // A abstract function for the Queue to be used when Scheduler is inheriting from Queue, it returns the node which is ready for deletion
	{
		Node* tmp = front; // Making a temporary front Node pointer

		if (front != nullptr) // As long as the front Node pointer is not a null pointer
		{
			front = front->getPrev(); // The front Node gets set to the second to first item in the Queue
			if (front != nullptr) front->setNext(nullptr); // if the front Node  isn't a null pointer, the next pointer of the front Node is a null pointer
		}
		else // Make sure the front Node and the back Node are the same, when the front pointer is a null pointer 
		{
			tmp = back; 
			back = front;
		}
		return tmp; // Return the Node we are deleting
	}
};
class Scheduler : public Queue // Scheduler class inherited from the Queue class
{
private:
	int counter = 0; // Integer counter used to count when the same priority of Nodes get deleted in a row
	int val; // Integer used to store the highest priority value when looping through the Queue
	Node* NodeDequeue(void) // A implementation of the abstract function defined in the Queue class, that returns the Node we are deleting
	{
		Node *tmp = back; // Assigning the back Node to a temporary variable
		val = 0; // Assigning the integer that is used to store the highest priority to 0
		if (tmp != nullptr) // If the temporary Node pointer isn't a null pointer
		{
			tmp = nodeToDelete(tmp, val); // Setting the temporary Node pointer to the Node we are deleting

			if (tmp != nullptr) // If the temporary Node pointer isn't a null pointer
			{
				// Checking all the possible positions the Node can have, and then making sure that the pointers are right when the Node gets deleted
				if (tmp->getPrev() != nullptr && tmp->getNext() != nullptr)
				{
					tmp->getPrev()->setNext(tmp->getNext());
					tmp->getNext()->setPrev(tmp->getPrev());
				}
				if (tmp->getPrev() == nullptr)
				{
					back = back->getNext();
					if (back != nullptr) back->setPrev(nullptr);
				}
				if (tmp->getNext() == nullptr)
				{
					front = front->getPrev();
					if (front != nullptr) front->setNext(nullptr);
				}
			}
		}
		else
		{
			back = front; // The back pointer will be equal to the front pointer, if the back pointer is a null pointer
		}
		return tmp; 

	}

	Node* nodeToDelete(Node* tmp, int val) // A fucntion which loops through the Queue with a pointer and returns the Node that needs to be deleted
	{
		while (tmp != nullptr) 
		{
			if (counter < 2) // If the counter used to determine if there has been to many items in a row of the same item is less than 2
			{
				if (tmp->getPriority() > val) // If the priority value of the current Node pointer is bigger than the highest stored value
				{
					val = tmp->getPriority(); // The highest stored value gets updated to that new priority value
				}
			}
			else // If the counter is above 2
			{
				val = tmp->getPriority(); // The value gets assigned to the first Node's priority in the Queue
			}
			if (tmp->getNext() == nullptr) break; // We break the loop when the next item is a null pointer so we can continue to loop through the Queue object
			tmp = tmp->getNext(); // Setting the temporary Node pointer to the next one in the Queue

		}


		while (tmp != nullptr) // As long as the temporary pointer isn't a null pointer
		{
			// checking if the counter is above or lower than 2, and from there we either reset the counter or add one to it. And we are also checking if the priority is equal to the value set by the previous loop
			if (counter < 2 && tmp->getPriority() == val)
			{
				counter++;
				return tmp;
			}
			if (counter >= 2 && tmp->getPriority() == val)
			{
				counter = 0;
				return tmp;
			}
			tmp = tmp->getPrev(); // Setting the temporary Node pointer to the previous Node in the Queue
		}
	}
};

//int main()
//{
//	Queue s;
//	s.Enqueue(20, 1);
//	s.Enqueue(10, 8);
//	s.Enqueue(19, 5);
//	s.Enqueue(9, 3);
//	s.Enqueue(9, 4);
//	std::cout << s.Dequeue() << std::endl;
//	std::cout << s.Dequeue() << std::endl;
//	std::cout << s.Dequeue() << std::endl;
//	std::cout << s.Dequeue() << std::endl;
//	std::cout << s.Dequeue() << std::endl;
//
//	Scheduler s;
//	int m = (rand() % 10) + 1;
//	int r = (rand() % 500) + 1;
//	for (int i = 0; i < 500; i++)
//	{
//		s.Enqueue(r, m);
//		r = (rand() % 500) + 1;
//		m = (rand() % 10) + 1;
//	}
//
//	std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
//	for (int i = 0; i < 500; i++)
//	{
//		std::cout << s.Dequeue() << std::endl;
//	}
//	std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
//
//	std::cout << "Time difference in ms = " << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() << std::endl;
//
//
//	getchar();
//	return 0;
//}