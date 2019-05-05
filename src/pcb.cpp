#include <pcb.h>
#include <dos.h>
#include <schedule.h>
#include <kernel.h>
#include <iostream.h>

ID PCB::Id=0;

PCB::PCB(StackSize stackSize,Time time,Thread *thr)
{
	myTimeSlice=time;
	stack=0;
	stackSize/=sizeof(unsigned);
	if (stackSize>MAXSSIZE) stackSize=MAXSSIZE;

	state=CREATED;
	id=++Id;

	if (id==1)
	{
		Kernel::start=this;
		return;
	}
	if (id==2)
	{
		Kernel::idle=this;
	}
	stack=new unsigned[stackSize];

#ifndef BCC_BLOCK_IGNORE
	stack[stackSize-1]=FP_SEG(thr);
	stack[stackSize-2]=FP_OFF(thr);

	stack[stackSize-5]=0x200;
	stack[stackSize-6]=FP_SEG(PCB::Wrapper);
	stack[stackSize-7]=FP_OFF(PCB::Wrapper);

	ss=FP_SEG(stack+stackSize-16);
	sp=FP_OFF(stack+stackSize-16);

#endif
	bp=sp;
}

PCB::~PCB()
{
	if (stack!=0)
	{
	delete[] stack;
	stack=0;
	}
}
void PCB::start()
{
	if (state==PCB::CREATED)
	{
	state=PCB::READY;
	Kernel::currentlyActive++;
	if (this!=Kernel::start)Scheduler::put(this);
	}
}

void PCB::Wrapper(Thread *myThread)
{
	myThread->run();
lock();
	myThread->myPCB->state=FINISHED;
	Kernel::currentlyActive--;

	while (myThread->myPCB->waitQueue.getSize()>0)
	{
		PCB *temp=myThread->myPCB->waitQueue.get();
		temp->state=PCB::READY;
		if (temp!=Kernel::start)Scheduler::put(temp);

	}
unlock();
	dispatch();
}

void PCB::waitToComplete()
{
	if (this==Kernel::start) return;
	if (this==Kernel::idle) return;
	if (this==Kernel::running) return;
	if (this->state==FINISHED) return;

	Kernel::running->state=BLOCKED;
	waitQueue.put((PCB *)Kernel::running);
	unlock();
	dispatch();
}
