#include <queue.h>
#include <pcb.h>
#include <kernel.h>
Queue::Queue()
{
lock();
	head=0;
	tail=0;
	size=0;
unlock();
}
Queue::~Queue()
{
lock();
	Node *curr=head;
	while (head)
	{
		curr=head;
		head=head->next;
		delete curr;
	}
unlock();
}
void Queue::put(PCB *p)
{

	Node *newNode=new Node();
	newNode->next=0;
	newNode->pcb=p;
	if (size==0)
	{
		head=newNode;
		tail=newNode;
	}
	else
	{
		tail->next=newNode;
		tail=newNode;
	}
	size++;

}

PCB* Queue::get()
{
	Node *curr;
	PCB *temp;
	if (size==0) return 0;
	if (size==1)
	{
		curr=head;
		temp=head->pcb;
		head=0;
		tail=0;
		size=0;
		delete curr;
		return temp;
	}
	curr=head;
	temp=head->pcb;
	head=head->next;
	size--;
	delete curr;
	return temp;

}


int Queue::getSize()const
{
	return size;
}
