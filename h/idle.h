#ifndef _idle_h
#define _idle_h
#include <thread.h>

class IdleThread:public Thread{
public:
	IdleThread():Thread(1024,1){}
	void run();
};
#endif
