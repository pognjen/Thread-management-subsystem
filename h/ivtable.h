#ifndef _ivtable_h
#define _ivtable_h
#define N 256

class IVTEntry;

class IVTable{
public:

IVTable();

void put(IVTEntry *ivt,unsigned numOfEntry);

IVTEntry *get(unsigned numOfEntry);

private:
	IVTEntry *arr[N];
};

#endif
