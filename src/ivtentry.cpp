#include <ivtentry.h>
#include <thread.h>
#include <dos.h>
#include <kernelev.h>
#include <kernel.h>
IVTEntry::IVTEntry(unsigned numEntry,pInterrupt newRout)
{
lock();
	this->numEntry=numEntry;
#ifndef BCC_BLOCK_IGNORE
	oldRout=getvect(numEntry);
	setvect(numEntry,newRout);
#endif
	Kernel::ivtable.put(this,numEntry);
unlock();
}
IVTEntry::~IVTEntry()
{
lock();
#ifndef BCC_BLOCK_IGNORE
	setvect(numEntry,oldRout);
#endif
unlock();
}

void IVTEntry::callOldRoutine()
{
	*oldRout;
}

void IVTEntry::signal()
{
lock();
	myEvent->signal();
unlock();
}

void IVTEntry::linkEvent(KernelEv *myEv)
{

	myEvent=myEv;

}
