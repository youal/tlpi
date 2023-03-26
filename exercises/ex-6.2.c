/* Write a program to see what happens if we try to longjmp() into a function
that has already returned.

Jumping to a function that has returned is an error since the stack frame ins
not avaiable anymore. Doing so show unexpected beehaviours.
On my machine, the message "longjmp 1" shows as if the function has been
executed as expected, but the variable "i" being not in the stack anymore in
printed with the value "0" instead of "9".
*/

#include <stdio.h>
#include <setjmp.h>


static jmp_buf env;

void f0(void);
void f1(void);


void f0(void)
{
	int i = 9;
	switch (setjmp(env)) {
		case 0:
			puts("initial setjmp");
			break;
		case 1:
			puts("longjmp 1");
			printf("%d\n", i);
			break;
		default:
			puts("default");
			break;
	}
}


void
f1(void) { longjmp(env, 1); }


int
main(int argc, char *argv[])
{
	f0();
	f1();


	return 0;
}
