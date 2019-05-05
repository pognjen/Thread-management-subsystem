#include <sleepq.h>
#include <kernel.h>
#include <pcb.h>
#include <schedule.h>
#include <iostream.h>

SleepQueue::SleepQueue()
{
lock();
	head=0;
	tail=0;
	size=0;
unlock();
}
SleepQueue::~SleepQueue()
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
int SleepQueue::getSize()const
{
	return size;
}

void SleepQueue::put(PCB *p,unsigned time)
{
lock();
	Node *newNode=new Node();
	newNode->pcb=p;
	newNode->next=0;
	newNode->time=time;
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

unlock();
}

void SleepQueue::updateSleepingTime()
{
lock();
Node  *curr;
	if (size==0) {unlock(); return; }
	if (size==1)
	{
		head->time--;
		if (head->time==0)
		{
			curr=head;
			head->pcb->state=PCB::READY;
			Scheduler::put(head->pcb);
			head=tail=0;
			size--;
			unlock();
			delete curr;
			return;
		}
		unlock();
		return;
	}
	Node *temp=head;

	Node *prev=0;
	while (temp)
	{
		curr=temp;
		temp->time--;

		if (temp->time==0)
		{
			temp->pcb->state=PCB::READY;
			Scheduler::put(temp->pcb);
			size--;
			if (prev==0)
			{
				head=head->next;
			}
			else
			{
				prev->next=temp->next;
				if (!(prev->next)) tail=prev;
			}
			temp=temp->next;
			delete curr;
		}
		else
		{
			prev=temp;
			temp=temp->next;
		}

	}
	unlock();
}





