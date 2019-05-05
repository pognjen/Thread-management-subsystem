#include <semaphor.h>
#include <kernel.h>
#include <kersem.h>
#include <thread.h>

 Semaphore::Semaphore(int init)
{
lock();
	myImpl=new KernelSem(init);
unlock();
}
Semaphore::~Semaphore()
{

}
int Semaphore::wait(int toBlock)
{
lock();
	int retVal=myImpl->wait(1);
unlock();

return retVal;
}
void Semaphore::signal()
{
lock();
	myImpl->signal();
unlock();
}
int Semaphore::val()const
{
	return myImpl->val();
}
