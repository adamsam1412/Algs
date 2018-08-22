#include <iostream>

using std::cout;
using std::cin;
using std::endl;

struct node
{
    int value;
    node* next;
};

struct queue
{
    node* stack1;
    node* stack2;
};

void push(node *& head, int value)
{
    node* newNode = new node;
    newNode->value = value;
    newNode->next = head;
    head = newNode;
}

int pop(node *& head)
{
    node* temp = head;
    int x = temp->value;
    head = head->next;
    temp->next = nullptr;
    delete temp;
    return x;
}

void enqueue(queue* Q, int value)
{
    push(Q->stack1, value);
}

int dequeue(queue* Q)
{
    if(Q->stack2)
        return pop(Q->stack2);
    
    while(Q->stack1)
    {
        push(Q->stack2, pop(Q->stack1));
    }    
    return pop(Q->stack2);    
}

int main ()
{

    node* test = nullptr;

    push(test, 1);
    push(test, 2);
    push(test, 3);
    push(test, 6);

    cout << test->value << endl;
    cout << test->next->value << endl;
    cout << test->next->next->value << endl;
    cout << test->next->next->next->value << endl;
    //cout << test->next->next->next->next->value << endl;

    cout << pop(test) << endl;
    cout << test->value << endl;

    cout << "QUEUE" << endl;

    queue* q = new queue;
    q->stack1 = nullptr;
    q->stack2 = nullptr;

    enqueue(q, 1);
    enqueue(q, 2);
    enqueue(q, 3);
    enqueue(q, 1);
    enqueue(q, 6);
    enqueue(q, 7);


    cout << dequeue(q) << endl;
    cout << dequeue(q) << endl;
    cout << dequeue(q) << endl;
    cout << dequeue(q) << endl;
    cout << dequeue(q) << endl;
    cout << dequeue(q) << endl;

    return 0;
}

