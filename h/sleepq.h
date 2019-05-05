#ifndef _sleepq_h
#define _sleepq_h
#define N 100
class PCB;

class SleepQueue{
public:
	SleepQueue();
	~SleepQueue();
	void put(PCB *p,unsigned time);
	void updateSleepingTime();
	int getSize()const;
private:
	struct Node{
		PCB *pcb;
		Node *next;
		unsigned time;
	};
	Node  *head,*tail;
	unsigned size;
};


#endif
