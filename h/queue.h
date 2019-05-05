#ifndef _queue_h
#define _queue_h
#define N 100
class PCB;
class Queue{
public:
	Queue();
	~Queue();
	void put(PCB *p);
	PCB *get();
	int getSize()const;
private:
	struct Node{
		PCB *pcb;
		Node *next;
	};
	Node *head,*tail;
	int size;
};

#endif
