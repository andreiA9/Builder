#include <stdio.h>

int main (void)
{
  printf ("Hello, world!\n");
  return 0;
}



/* CREATE OBJECT FILE
! gcc -Wall -o hello.o  hello.c
The option -Wall turns on all the most commonly-used compiler warnings---it
 is recommended that you always use this option! There are many other
 warning options which will be discussed in later chapters, but -Wall is
 the most important. GCC will not produce any warnings unless they are
 enabled.
*/