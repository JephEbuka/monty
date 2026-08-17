#include "monty.h"

/**
 * free_stack - free every node in a stack
 * @stack: head of the stack
 */
void free_stack(stack_t *stack)
{
	stack_t *next;

	while (stack != NULL)
	{
		next = stack->next;
		free(stack);
		stack = next;
	}
}

/**
 * monty_fail - free resources and exit with failure
 * @stack: current stack
 */
void monty_fail(stack_t *stack)
{
	free_stack(stack);
	free(monty.line);

	if (monty.file != NULL)
		fclose(monty.file);

	exit(EXIT_FAILURE);
}
