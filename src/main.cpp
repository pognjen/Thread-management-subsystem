
#include <kernel.h>

extern int userMain(int argc,char *argv[]);

int main(int argc,char *argv[])
{
//-----------------------------------//
	Kernel::LoadSystem();
//-----------------------------------//
	int retVal=userMain(argc,argv);
//-----------------------------------//
	Kernel::RestoreSystem();
//-----------------------------------//
	return retVal;
//-----------------------------------//
}
