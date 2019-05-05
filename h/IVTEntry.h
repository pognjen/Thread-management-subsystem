#ifndef _ivt_h
#define _ivt_h

typedef void interrupt (*pInterrupt)(...);

#define PREPAREENTRY(numEntry,callOld)\
	void interrupt inter##numEntry(...);\
	IVTEntry newEntry##numEntry(numEntry,inter##numEntry);\
	void interrupt inter##numEntry(...){\
	newEntry##numEntry.signal();\
	if (callOld==1) newEntry##numEntry.callOldRoutine();\
}
class KernelEv;

class IVTEntry{
public:
	IVTEntry(unsigned numEntry,pInterrupt newRout);
	~IVTEntry();
	void callOldRoutine();
	void signal();
	void linkEvent(KernelEv *myEv);
private:
pInterrupt oldRout;
KernelEv *myEvent;
unsigned numEntry;
};

#endif
