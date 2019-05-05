#include <kernelev.h>
#include <pcb.h>
#include <kernel.h>
#include <ivtentry.h>
#include <schedule.h>

KernelEv::KernelEv(IVTNo ivtNo)
{
	Kernel::ivtable.get(ivtNo)->linkEvent(this);
	blocked=0;
	owner=(PCB *)Kernel::running;
	value=1;
}

void KernelEv::wait()
{
	if (owner==Kernel::running)
	{
		if (value==0)
		{
			blocked=(PCB *)Kernel::running;
			blocked->state=PCB::BLOCKED;
			unlock();
			dispatch();
		}
		else
			if (value==1) value=0;
	}


}
void KernelEv::signal()
{
	if (blocked==0) value=1;
	else
	if (blocked!=0)
	{
	blocked->state=PCB::READY;
	Scheduler::put(blocked);
	blocked=0;
	}
}
