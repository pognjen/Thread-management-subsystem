#ifndef _kernel_ev_h
#define _kernel_ev_h
#include <queue.h>
#include <event.h>

class PCB;

class KernelEv{
public:
	KernelEv(IVTNo ivtNo);
	void wait ();
	void signal();
private:
	PCB *blocked;
	PCB *owner;
	int value;
};
#endif
