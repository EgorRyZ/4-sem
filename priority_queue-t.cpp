#include <iostream>
#include <random>
#include <string>

using namespace std;

template <typename Type> struct Node
{
    Type data;
	int priority;
    struct Node<Type> *next;
    struct Node<Type> *prev;
};

template <typename Type> class Priority_queue
{
public:
    Priority_queue();
    ~Priority_queue();
	
    void push(Type dat, int pr);
    Type pop();
	Type peek();
    bool queue_is_empty();
    void print_queue();
	
	int count;
	
    struct Node<Type> *front;
	struct Node<Type> *back;
};

template <typename Type> struct Node<Type> *create_node(Type dat, int pr);

template <typename Type> void delete_node(struct Node<Type> **p);


int main()
{
	
	Priority_queue<char> _queue = Priority_queue<char>();
	
	cout << "QUEUE IS EMPTY :" << ((_queue.queue_is_empty()) ? " TRUE" : " FALSE") << endl;
	
	for(int i = 0; i < 20; i++)
	{
		_queue.push(i + 70, rand() % 9 + 1);
		_queue.print_queue();
	}
	
	cout << "TOP : " << _queue.peek() << endl;
	
	cout << '\n';
	
	
	for(int i = 0; i < 4; i++)
	{
		cout <<  _queue.pop() << endl;
		cout << '\n';
	}
	
	
	
	_queue.print_queue();
	
	while(!_queue.queue_is_empty())
	{
		cout << _queue.pop() << ' ';
	}
	
	_queue.print_queue();
	
	
	cout << "QUEUE IS EMPTY :" << ((_queue.queue_is_empty()) ? " TRUE" : " FALSE") << endl;
	
	_queue.~Priority_queue();
	
	
    return 0;
}

template <typename Type> Priority_queue<Type>::Priority_queue()
{
	front = nullptr;
	back = nullptr;
	count = 0;
}

template <typename Type> bool Priority_queue<Type>::queue_is_empty()
{
    return (front == nullptr) ? true : false;
}

template <typename Type> void Priority_queue<Type>::push(Type dat, int pr)
{
    if(queue_is_empty())
        front = (back = create_node(dat, pr));
	else
	{
		struct Node<Type> *ptr = back;
		
		struct Node<Type> *new_node = create_node(dat, pr);
		
		//cout << "*ptr: "<< '<' << (*ptr)->data << ',' << (*ptr)->priority << '>' << ',' << (*ptr) << ',' << (*ptr)->prev << ',' << (*ptr)->next << '\n';
		
		while(ptr->priority > pr && ptr->prev != nullptr)
			ptr = ptr->prev;
		//cout << '<' << (*ptr)->data << ',' << (*ptr)->priority << '>' << "<--"<< '\n';
		
		//cout << "*ptr: "<< '<' << (*ptr)->data << ',' << (*ptr)->priority << '>' << ',' << (*ptr) << ',' << (*ptr)->prev << ',' << (*ptr)->next << '\n';
		
		
		
		if(ptr == back && back->priority <= pr)
		{
			back->next = new_node;
			new_node->prev = back;
			back = new_node;
		}
		else if(ptr == front && front->priority > pr)
		{
			front->prev = new_node;
			new_node->next = front;
			front = new_node;
		}
		else
		{
			struct Node<Type> *t = ptr->next;
			
		    new_node->prev = ptr;
		    new_node->next = ptr->next;
		    
		    ptr->next = new_node;
		    t->prev = new_node;
		}
	}
    count++;
}

template <typename Type> Type Priority_queue<Type>::pop()
{
	if(queue_is_empty())
	{
		cout << "QUEUE IS EMPTY" << endl;
		return 0;
	}
	Type dat = front->data;
	struct Node<Type> *ptr = front->next;
	delete_node(&front);
	front = ptr;
    count--;
	return dat;
}

template <typename Type> Type Priority_queue<Type>::peek()
{
	if(queue_is_empty())
	{
		cout << "QUEUE IS EMPTY" << endl;
		return 0;
	}
	return front->data;
}

template <typename Type> void Priority_queue<Type>::print_queue()
{
	struct Node<Type> *ptr = front;
	
    cout << "front ";
	while(ptr != nullptr)
	{
		cout << '<' << ptr->data << ',' << ptr->priority << '>' << ' ';
		ptr = ptr->next;
	}
	cout << " back " << '\n';
}

template <typename Type> Priority_queue<Type>::~Priority_queue()
{
	struct Node<Type> **ptr = &front;
	struct Node<Type> *p;
	
	while(*ptr != nullptr)
	{
		p = (*ptr)->next;
		delete_node(ptr);
		*ptr = p;
	}
}

template <typename Type> struct Node<Type> *create_node(Type dat, int pr)
{
    struct Node<Type> *node = new Node<Type>;
	node->data = dat;
	node->priority = pr;
    node->next = nullptr;
    node->prev = nullptr;
    return node;
}

template <typename Type> void delete_node(struct Node<Type> **ptr)
{
	delete *ptr;
	*ptr = nullptr;
}

