#ifndef _pcb_h_
#define _pcb_h_
#define MAXSSIZE 65535
#include <thread.h>
#include <queue.h>


class PCB{
public:
	enum State{CREATED,READY,BLOCKED,FINISHED};
	PCB(StackSize stackSize, Time time, Thread *thread);
	~PCB();
	void start();
	void waitToComplete();
	static void Wrapper(Thread *myThread);
	unsigned sp;
	unsigned ss;
	unsigned bp;
	unsigned *stack;
	volatile State state;
	Time myTimeSlice;
	static ID Id;
	ID id;
	Queue waitQueue;
};
#endif
