#include "main.h"

/**
 * _sigint - Handle the crtl + c call in prompt
 * @signal: Signal handler
 */
void get_sigint(int signal)
{
	(void)signal;
	write(STDOUT_FILENO, "\n^-^ ", 5);
}

