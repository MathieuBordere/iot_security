#include <stdio.h>

#define SZ 16

void overflow()
{
	char small_stack_buffer[SZ];
	fgets(small_stack_buffer, SZ*2, stdin);
}

int main(int argc, char *argv[])
{
	(void) argc;
	(void) argv;
	overflow();
	return 0;
}
