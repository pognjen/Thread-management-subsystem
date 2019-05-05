#include <ivtable.h>
#include <kernel.h>
#include <thread.h>

IVTable::IVTable()
{
lock();

for (int i=0;i<N;i++) arr[i]=0;

unlock();
}


void IVTable::put(IVTEntry *ivt,unsigned numOfEntry)
{
	arr[numOfEntry]=ivt;
}

IVTEntry *IVTable::get(unsigned numOfEntry)
{
	return arr[numOfEntry];
}
