#include "PrintMessage.h"

int main (void)
{
	printMessage();
	return 0;
}


/*
! gcc unused.c
 |
\ /
! gcc -Wunused unused.c
 < the COMPILER=GCC does not complain
 |
\ /
unused.c: In function 'main':
unused.c:3: warning: unused variable 'i'
*/