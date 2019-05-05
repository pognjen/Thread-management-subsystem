#ifndef _start_h_
#define _start_h_

#include <thread.h>
class StartingThread:public Thread{
public:
	StartingThread():Thread(1024,2){}
};

#endif
