#include <kernel.h>
#include <dos.h>
#include <pcb.h>
#include <schedule.h>
#include <starting.h>
#include <idle.h>
#include <iostream.h>
volatile unsigned Kernel::currentlyActive=0;
unsigned volatile Kernel::lockFlag=1;
volatile unsigned Kernel::explicitContextSwitch=0;
volatile unsigned Kernel::isDispatched=0;
unsigned volatile tbp,tss,tsp;

volatile PCB *Kernel::running;
volatile unsigned Kernel::counter=2;
volatile PCB *Kernel::start;
volatile PCB *Kernel::idle;

volatile StartingThread *Kernel::str;
volatile IdleThread *Kernel::idl;
volatile pInterrupt Kernel::oldISR;

SleepQueue Kernel::sleepList;
IVTable Kernel::ivtable;

extern void tick();
void interrupt Kernel::timer(...)
{
	if (Kernel::counter==0 && Kernel::isDispatched==0 ) {
			Kernel::sleepList.updateSleepingTime();
			tick();
			asm int 60h;
			}
		else {


		if (Kernel::isDispatched==0) Kernel::counter--;
			if (Kernel::counter == 0 || Kernel::explicitContextSwitch==1 || Kernel::isDispatched==1) {
				if (Kernel::lockFlag==1){
					Kernel::explicitContextSwitch=0;
				asm {
					mov tsp, sp
					mov tss, ss
					mov tbp, bp
				}

				running->sp = tsp;
				running->ss = tss;
				running->bp = tbp;


				if (running->state==PCB::READY && running!=Kernel::start && running!=Kernel::idle)Scheduler::put((PCB *)running);

				running=Scheduler::get();

				if (running==0){
					if (Kernel::currentlyActive==0) running=Kernel::start;
					else
					running=Kernel::idle;
				}


				Kernel::counter=running->myTimeSlice;

				tbp = running->bp;
				tsp = running->sp;
				tss = running->ss;



				asm {
					mov sp, tsp
					mov ss, tss
					mov bp, tbp
					}
				}
				else
					Kernel::explicitContextSwitch=1;
			}
		if(Kernel::isDispatched==0) {
			Kernel::sleepList.updateSleepingTime();
			tick();
			asm int 60h;
		}
		
	}
		Kernel::isDispatched=0;
}
void Kernel::LoadSystem()
{
lock();
#ifndef BCC_BLOCK_IGNORE
	str=new StartingThread();
	idl=new IdleThread();
	Kernel::running=Kernel::start;

	Kernel::oldISR=getvect(0x8);
	setvect(0x8,Kernel::timer);
	setvect(0x60,Kernel::oldISR);
#endif
unlock();
}

void Kernel::deallocate()
{
	delete Kernel::str;
	delete Kernel::idl;
}
void Kernel::RestoreSystem()
{
	lock();
#ifndef BCC_BLOCK_IGNORE
	setvect(0x8,Kernel::oldISR);
#endif
	Kernel::deallocate();
	unlock();

}


