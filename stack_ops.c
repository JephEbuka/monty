#include "monty.h"

/**
 * is_integer - check whether a string is a valid integer
 * @value: string to check
 *
 * Return: 1 if valid, otherwise 0
 */
static int is_integer(char *value)
{
	int index = 0;

	if (value == NULL || value[0] == '\0')
		return (0);

	if (value[index] == '-' || value[index] == '+')
		index++;

	if (value[index] == '\0')
		return (0);

	while (value[index] != '\0')
	{
		if (value[index] < '0' || value[index] > '9')
			return (0);
		index++;
	}

	return (1);
}

/**
 * op_push - push an integer onto the stack
 * @stack: pointer to the stack
 * @line_number: current line number
 */
void op_push(stack_t **stack, unsigned int line_number)
{
	stack_t *node;

	if (!is_integer(monty.arg))
	{
		fprintf(stderr, "L%u: usage: push integer\n", line_number);
		monty_fail(*stack);
	}

	node = malloc(sizeof(stack_t));
	if (node == NULL)
	{
		fprintf(stderr, "Error: malloc failed\n");
		monty_fail(*stack);
	}

	node->n = atoi(monty.arg);
	node->prev = NULL;
	node->next = *stack;

	if (*stack != NULL)
		(*stack)->prev = node;

	*stack = node;
}

/**
 * op_pall - print every value in the stack
 * @stack: pointer to the stack
 * @line_number: current line number
 */
void op_pall(stack_t **stack, unsigned int line_number)
{
	stack_t *current = *stack;

	(void)line_number;

	while (current != NULL)
	{
		printf("%d\n", current->n);
		current = current->next;
	}
}

/**
 * op_pint - print the value at the top of the stack
 * @stack: pointer to the stack
 * @line_number: current line number
 */
void op_pint(stack_t **stack, unsigned int line_number)
{
	if (*stack == NULL)
	{
		fprintf(stderr, "L%u: can't pint, stack empty\n", line_number);
		monty_fail(*stack);
	}

	printf("%d\n", (*stack)->n);
}

/**
 * op_pop - remove the top element of the stack
 * @stack: pointer to the stack
 * @line_number: current line number
 */
void op_pop(stack_t **stack, unsigned int line_number)
{
	stack_t *top;

	if (*stack == NULL)
	{
		fprintf(stderr, "L%u: can't pop an empty stack\n", line_number);
		monty_fail(*stack);
	}

	top = *stack;
	*stack = top->next;

	if (*stack != NULL)
		(*stack)->prev = NULL;

	free(top);
}

/**
 * op_swap - swap the top two stack values
 * @stack: pointer to the stack
 * @line_number: current line number
 */
void op_swap(stack_t **stack, unsigned int line_number)
{
	int temporary;

	if (*stack == NULL || (*stack)->next == NULL)
	{
		fprintf(stderr, "L%u: can't swap, stack too short\n", line_number);
		monty_fail(*stack);
	}

	temporary = (*stack)->n;
	(*stack)->n = (*stack)->next->n;
	(*stack)->next->n = temporary;
}

/**
 * op_nop - do nothing
 * @stack: pointer to the stack
 * @line_number: current line number
 */
void op_nop(stack_t **stack, unsigned int line_number)
{
	(void)stack;
	(void)line_number;
}
