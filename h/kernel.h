#ifndef _kernel_h_
#define _kernel_h_
#include <sleepq.h>
#include <ivtable.h>
#include <queue.h>


#define lock() Kernel::lockFlag=0;


#define unlock() {				  \
Kernel::lockFlag=1;				  \
if (Kernel::explicitContextSwitch)\
	dispatch();					  \
}


class PCB;
class StartingThread;
class IdleThread;

typedef void interrupt (*pInterrupt)(...);
class Kernel{
public:
	static volatile unsigned lockFlag;
	static volatile unsigned explicitContextSwitch;
	static volatile unsigned currentlyActive;
	static volatile unsigned counter;
	static volatile unsigned isDispatched;
	static SleepQueue sleepList;
	static IVTable ivtable;
	static volatile PCB *running;
	static volatile PCB *start;
	static volatile StartingThread *str;
	static volatile IdleThread *idl;
	static volatile PCB *idle;
	static volatile pInterrupt oldISR;
	static void interrupt timer(...);
	static void LoadSystem();
	static void RestoreSystem();
	static void deallocate();
};

#endif
