#include <iostream>
#include <random>

using namespace std;

struct Node
{
    int data;
	int priority;
    struct Node *next;
    struct Node *prev;
};

class Priority_queue
{
public:
    Priority_queue();
    ~Priority_queue();
	
    void push(int dat, int pr);
    int pop();
	int peek();
    bool queue_is_empty();
    void print_queue();
	
	int count;
	
    struct Node *front;
	struct Node *back;
};

struct Node *create_node(int dat, int pr);

void delete_node(struct Node **p);


int main()
{
	
	Priority_queue _queue = Priority_queue();
	
	cout << "QUEUE IS EMPTY :" << ((_queue.queue_is_empty()) ? " TRUE" : " FALSE") << endl;
	
	for(int i = 0; i < 20; i++)
	{
		_queue.push(i, rand() % 9 + 1);
		_queue.print_queue();
	}
	
	cout << "TOP : " << _queue.peek() << endl;
	
	/*
	while(!_queue.queue_is_empty())
	{
		cout << _queue.pop() << ' ';
	}
	
	*/
	
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
	
	
	
	/*
	int dat, prior;
	
	while(1)
	{
		cin >> dat >> prior;
		_queue.push(dat, prior);
		_queue.print_queue();
	}
	*/
	
	
	
	/*
	_queue.push(1, 3);
	_queue.print_queue();
	_queue.push(1, 1);
	_queue.print_queue();
	_queue.push(1, 2);
	_queue.print_queue();
	_queue.push(1, 3);
	_queue.print_queue();
	_queue.push(1, 1);
	_queue.print_queue();
	_queue.push(1, 2);
	_queue.print_queue();
	*/
	
	/*
	cout <<  _queue.front->data << endl;
	cout <<  _queue.pop() << endl;
	cout <<  _queue.pop() << endl;*/
	
	cout << "QUEUE IS EMPTY :" << ((_queue.queue_is_empty()) ? " TRUE" : " FALSE") << endl;
	
	_queue.~Priority_queue();
	
	
    return 0;
}

Priority_queue::Priority_queue()
{
	front = nullptr;
	back = nullptr;
	count = 0;
}

bool Priority_queue::queue_is_empty()
{
    return (front == nullptr) ? true : false;
}

void Priority_queue::push(int dat, int pr)
{
    if(queue_is_empty())
        front = (back = create_node(dat, pr));
	else
	{
		struct Node *ptr = back;
		
		struct Node *new_node = create_node(dat, pr);
		
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
			struct Node *t = ptr->next;
			
		    new_node->prev = ptr;
		    new_node->next = ptr->next;
		    
		    ptr->next = new_node;
		    t->prev = new_node;
		}
	}
    count++;
}

int Priority_queue::pop()
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

int Priority_queue::peek()
{
	if(queue_is_empty())
	{
		cout << "QUEUE IS EMPTY" << endl;
		return 0;
	}
	return front->data;
}

void Priority_queue::print_queue()
{
	struct Node *ptr = front;
	
    cout << "front ";
	while(ptr != nullptr)
	{
		cout << '<' << ptr->data << ',' << ptr->priority << '>' << ' ';
		ptr = ptr->next;
	}
	cout << " back " << '\n';
}

Priority_queue::~Priority_queue()
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

struct Node *create_node(int dat, int pr)
{
    struct Node *node = new Node;
	node->data = dat;
	node->priority = pr;
    node->next = nullptr;
    node->prev = nullptr;
    return node;
}

void delete_node(struct Node **ptr)
{
	delete *ptr;
	*ptr = nullptr;
}

