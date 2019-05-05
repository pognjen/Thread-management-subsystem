#ifndef _kersem_h
#define _kersem_h
#include <queue.h>
class KernelSem{
public:
	KernelSem (int init=1);
	int wait (int toBlock);
	int standardWait();
	int nonstandardWait();
	void signal();
	int val () const;
private:
Queue queue;
int value;
};
#endif
