#include <iostream>

using namespace std;

struct Node
{
    int data;
    struct Node *next;
};

class Queue
{
public:
    Queue();
    ~Queue();
	
    void push(int dat);
    int pop();
    bool queue_is_empty();
    void print_queue();
	
	int count;
	
    Node *front;
	Node *back;
};

struct Node *create_node(int dat);

void delete_node(struct Node **p);


int main()
{
	
	Queue _queue = Queue();
	
	cout << "QUEUE IS EMPTY :" << ((_queue.queue_is_empty()) ? " TRUE" : " FALSE") << endl;
	
	for (int i = 1; i <= 5; i++) 
	{
		_queue.push(i);
		_queue.print_queue();
	}
	
	cout << "QUEUE IS EMPTY :" << ((_queue.queue_is_empty()) ? " TRUE" : " FALSE") << endl;
	
	for (int i = 1; i <= 10; i++) 
	{
		cout << _queue.pop() << endl;
	}
	
	for (int i = 1; i <= 5; i++) 
	{
		_queue.push(i);
		_queue.print_queue();
	}
	
	for (int i = 30; i <= 35; i++) 
	{
		_queue.push(i);
		_queue.print_queue();
	}
	
	cout << "QUEUE IS EMPTY :" << ((_queue.queue_is_empty()) ? " TRUE" : " FALSE") << endl;
	
	for (int i = 0; i <= 10; i++) 
	{
		cout << _queue.pop() << endl;
	}
	
	cout << "QUEUE IS EMPTY :" << ((_queue.queue_is_empty()) ? " TRUE" : " FALSE") << endl;
	_queue.~Queue();
	
	
    return 0;
}

Queue::Queue()
{
	front = nullptr;
	back = nullptr;
	count = 0;
}

bool Queue::queue_is_empty()
{
    return (front == nullptr) ? true : false;
}

void Queue::push(int dat)
{
    if(queue_is_empty())
        front = back = create_node(dat);
	else
		back = (back->next = create_node(dat));
    count++;
}

int Queue::pop()
{
	if(queue_is_empty())
	{
		cout << "QUEUE IS EMPTY" << endl;
		return 0;
	}
	int dat = front->data;
	struct Node *ptr = front->next;
	delete_node(&front);
	front = ptr;
    count--;
	return dat;
	
}
   
void Queue::print_queue()
{
	struct Node *ptr = front;
	
	while(ptr != nullptr)
	{
		cout << ptr->data << ' ';
		ptr = ptr->next;
	}
	cout << '\n';
}

Queue::~Queue()
{
	struct Node **ptr = &front;
	struct Node *p;
	
	while(*ptr != nullptr)
	{
		p = (*ptr)->next;
		delete_node(ptr);
		*ptr = p;
	}
}

struct Node *create_node(int dat)
{
    struct Node *node = new Node;
	node->data = dat;
    node->next = nullptr;
    return node;
}

void delete_node(struct Node **ptr)
{
	delete *ptr;
	*ptr = nullptr;
}

