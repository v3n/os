#ifndef osQueue_h
#define osQueue_h

//Empty queue
template<typename Item_Type>
queue<Item_Type>::queue() : frontOfQueue(NULL), backOfQueue(NULL), numItems() {}

//Pushes item onto back of queue
template<typename Item_Type> 
	void queue<Item_Type>::push(const Item_Type& item) 
	{
		if (frontOfQueue == NULL)
		{
			backOfQueue = new Node(item, NULL);
			frontOfQueue = backOfQueue;
		}
		else
		{
			backOfQueue->next = new Node(item, NULL);
			backOfQueue = backOfQueue->next;
		}
		numItems++;
	}

//Returns reference to the item at the front of the queue
template<typename Item_Type>
	Item_Type& queue<Item_Type>::front()
	{
		return frontOfQueue->data;
	}

//Removes front item from queue
template<typename Item_Type>
	void queue<Item_Type>::pop()
	{
		Node* oldFront = frontOfQueue;
		frontOfQueue = frontOfQueue -> next;
		if (frontOfQueue == NULL)
		{
			backOfQueue == NULL;
		}
		delete oldFront;
		numItems--;
	}

//Checks if queue is empty
template<typename Item_Type>
	bool queue<Item_Type>::empty() const
	{
		return frontOfQueue == NULL;
	}

//Finds size of queue
template<typename Item_Type>
	size_t queue<Item_Type>::size() const
	{
		return numItems;
	}



#endif