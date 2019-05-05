#include <kersem.h>
#include <pcb.h>
#include <kernel.h>
#include <schedule.h>
#include <iostream.h>
KernelSem::KernelSem(int init)
{
	value=init;
}
int KernelSem::wait(int toBlock)
{
	if(toBlock!=0) return standardWait();
	else
		return nonstandardWait();
}
int KernelSem::standardWait()
{
	value--;
	if (value<0)
	{
		Kernel::running->state=PCB::BLOCKED;
		queue.put((PCB *)Kernel::running);
		unlock();
		dispatch();
		return 1;
	}
	return 0;
}
int KernelSem::nonstandardWait()
{
 if (value<=0) return -1;
 else
 {
	 value--;
	 return 0;
 }
}
void KernelSem::signal()
{
	value++;
	PCB *temp;
	if (value<=0)
	{
			temp=queue.get();
			temp->state=PCB::READY;
			Scheduler::put(temp);

	}


}

int KernelSem::val()const
{
	return value;
}
