#include <pcb.h>
#include <kernel.h>


Thread::Thread(StackSize stackSize, Time timeSlice)
{

lock();
	myPCB=new PCB(stackSize,timeSlice,this);
unlock();
}

int Thread::getId()
{
	return myPCB->id;
}

void Thread::start()
{
lock();
	myPCB->start();
unlock();
}

Thread::~Thread()
{
	waitToComplete();
lock();
	delete myPCB;
	myPCB=0;
unlock();
}

void dispatch()
{
	asm pushf;
	asm cli;

	Kernel::explicitContextSwitch=1;
	Kernel::isDispatched=1;
	asm int 8h;

	asm popf;
}

void Thread::waitToComplete()
{
lock();
	myPCB->waitToComplete();
unlock();


}

void Thread::sleep(Time timeToSleep)
{
lock();
if (timeToSleep!=0)
{
	Kernel::running->state=PCB::BLOCKED;
	Kernel::sleepList.put((PCB *)Kernel::running,timeToSleep);
}
unlock();
if (timeToSleep!=0)dispatch();

}

int Thread::getRunningId()
{
	return Kernel::running->id;
}
