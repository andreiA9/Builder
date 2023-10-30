#include <stdio.h>

int
main (void)
{
  printf ("Two plus two is %f\n", 4);
  return 0;
}



/*
$ gcc -Wall bad.c -o bad
bad.c: In function `main':
bad.c:6: warning: double format, different type arg (arg 2)

!!!!
IMPORTANT
The messages produced by GCC always have the form
 file:line-number:message
In this case, the correct format specifier should be '%d'
 for an integer argument.

Without the warning option -Wall the program appears to
 compile cleanly, but produces incorrect results:
 |
\ /
$ gcc bad.c -o bad
$ ./bad
Two plus two is 2.585495    (incorrect output)
1The incorrect format specifier causes the output to be
 corrupted, because the function printf is passed an integer
 instead of a floating-point number. Integers and
 floating-point numbers are stored in different formats in
 memory, and generally occupy different numbers of bytes,
 leading to a spurious result.
*/