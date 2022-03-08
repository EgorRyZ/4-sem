#include <fstream>
#include <iostream>
#include <stdio.h>
#include <cstdlib>
#include <cstring>
#define MAXWORD 100

using namespace std;

struct Node
{
    char *word;
    struct Node *next;
};

class List
{
public:
    List();
    ~List();
    void add_to_list(char *w);
	struct Node *find_in_list(char *w);
    void remove_from_list(char *w);
    bool list_is_empty();
    void print_list();
	int count;
private:
    Node *head;
	Node *top;
};

struct Node *create_node(char *w);

void delete_node(struct Node **p);


int main()
{
	ifstream txt_input;
    txt_input.open("test1.txt");
    char *w = new char[MAXWORD];
    List _list = List();
	
	cout << "LIST IS EMPTY " << _list.list_is_empty() << endl;
	
    while(txt_input.getline(w, MAXWORD, '\n'))
        _list.add_to_list(w);
        
    txt_input.close();
	delete[] w;
	
    _list.print_list();
    
	cout << "WORDS : " << _list.count << endl;
	cout << "LIST IS EMPTY " << _list.list_is_empty() << endl;
	
	_list.~List();
	//struct Node *nd = new Node();
	
	
    return 0;
}

List::List()
{
	head = nullptr;
	top = nullptr;
	count = 0;
}

bool List::list_is_empty()
{
    return (head == nullptr) ? true : false;
}

void List::add_to_list(char *w)
{
    if(list_is_empty())
        head = top = create_node(w);
	else
		top = (top->next = create_node(w));
    count++;
}

struct Node *List::find_in_list(char *w)
{
	struct Node *ptr = head;
	while(ptr != nullptr)
	{
		if(strcmp(ptr->word, w))
			return ptr;
		ptr = ptr->next;
	}
	return nullptr;
}

void List::remove_from_list(char *w)
{
	struct Node **ptr = &head;
	
	if(strcmp((*ptr)->word, w))
	{
		head = (*ptr)->next;
		delete_node(ptr);
	}
	
	while((*ptr)->next != nullptr)
	{
		if(strcmp(((*ptr)->next)->word, w))
			(*ptr)->next = ((*ptr)->next)->next;
		ptr = &((*ptr)->next);
	}
}
   
void List::print_list()
{
	struct Node *ptr = head;
	
	while(ptr != nullptr)
	{
		printf("%s\n", ptr->word);
		ptr = ptr->next;
	}
}

List::~List()
{
	struct Node **ptr = &head;
	struct Node *p;
	
	while(*ptr != nullptr)
	{
		p = (*ptr)->next;
		delete_node(ptr);
		*ptr = p;
	}
}

struct Node *create_node(char *w)
{
    struct Node *node = new Node;
    node->word = new char[MAXWORD];
    strcpy(node->word, w);
    node->next = nullptr;
    return node;
}

void delete_node(struct Node **ptr)
{
	delete[] (*ptr)->word;
	delete *ptr;
	*ptr = nullptr;
}

