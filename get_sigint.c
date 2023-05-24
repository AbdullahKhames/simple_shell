#include "main.h"

/**
 * get_sigint - deal crtl + c call in prompt
 * @signal: Signal handler
 */
void get_sigint(int signal)
{
	(void)signal;
	write(STDOUT_FILENO, "\nshelly$ ", 9);
}

