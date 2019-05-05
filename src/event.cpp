#include <kernel.h>
#include <thread.h>
#include <kernelev.h>

Event::Event(IVTNo ivtNo)
{
lock();
	myImpl=new KernelEv(ivtNo);
unlock();
}
Event::~Event()
{

}
void Event::wait()
{
lock();
	myImpl->wait();
unlock();
}

void Event::signal()
{
lock();
	myImpl->signal();
unlock();
}
