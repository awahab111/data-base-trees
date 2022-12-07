template <class T>
class SNode
{
public:
	T data;
	SNode* next;

	SNode()
	{
		next = NULL;
	}

	SNode(T d, SNode* n) : data(0), next(n)
	{}

	SNode(T d) : data(d), next(nullptr)
	{}

	void setData(T d)
	{}

	void setNext(SNode* n)
	{}

	T getData()
	{}

	SNode* getNext()
	{}

};



template <class T>
class SLinkedList {

public:

	SNode<T>* head;


	SLinkedList()
	{
		head = NULL;
	}

	void insert(T num);
	void insertAtHead(T num);
	void InsertAtIndex(int i, int j);
	int search(T value);
	void update(T original, T replace);
	void remove(T value);
	void print();
	void mergeLists(SLinkedList newList);
	bool isEmpty()
	{
		if (head == nullptr) return true;
		else return false;
	}


};


//-------------------------------- Implementation

template <class T>
void SLinkedList<T>::insert(T num)
{
	SNode<T>* newNode = new SNode<T>(num);
	if (head == nullptr)
	{
		head = newNode;
		newNode = nullptr;
	}
	else
	{
		SNode<T>* temp = head;
		while (temp->next)
		{
			temp = temp->next;
		}
		temp->next = newNode;
		temp = nullptr;
	}
}

template <class T>
void SLinkedList<T>::insertAtHead(T num)
{
	SNode<T>* newNode = new SNode<T>(num);
	if (head == nullptr)
	{
		head = newNode;
		newNode = nullptr;
	}
	else
	{
		newNode->next = head;
		head = newNode;
	}
}

template <class T>
void SLinkedList<T>::InsertAtIndex(int value, int index)
{
	SNode<T>* newNode = new SNode<T>(value);
	SNode<T>* temp = head;
	while (index>0)
	{
		if(temp->next != nullptr)
		temp = temp->next;
		index--;
	}
	newNode->next = temp->next;
	temp->next = newNode;
}

template <class T>
int SLinkedList<T>::search(T value)
{
	SNode<T>* temp = head;
	int index = 0;
	while (temp && temp->data != value)
	{
		temp = temp->next;
		index++;
	}
	return index;
}

template <class T>
void SLinkedList<T>::update(T original, T replace)
{
	SNode<T>* temp = head;
	while (temp->data != original)
	{
		temp = temp->next;
	}
	temp->data = replace;
}

template <class T>
void SLinkedList<T>::remove(T value)
{
	SNode<T>* traverse = head;
	while (traverse->next->data != value)
	{
		traverse = traverse->next;
	}
	SNode<T>* temp = traverse->next;
	traverse->next = temp->next;
	delete temp;
	temp = nullptr;

}

template <class T>
void SLinkedList<T>::print()
{
	SNode<T>* temp = head;
	while (temp)
	{
		cout << temp->data << " ";
		temp = temp->next;
	}
}