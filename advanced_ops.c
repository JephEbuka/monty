#include "monty.h"

/**
 * op_pchar - print the character represented by the top stack value
 * @stack: pointer to the stack
 * @line_number: current line number
 */
void op_pchar(stack_t **stack, unsigned int line_number)
{
	if (*stack == NULL)
	{
		fprintf(stderr, "L%u: can't pchar, stack empty\n", line_number);
		monty_fail(*stack);
	}

	if ((*stack)->n < 0 || (*stack)->n > 127)
	{
		fprintf(stderr, "L%u: can't pchar, value out of range\n",
			line_number);
		monty_fail(*stack);
	}

	printf("%c\n", (*stack)->n);
}

/**
 * op_pstr - print a string beginning at the top of the stack
 * @stack: pointer to the stack
 * @line_number: current line number
 */
void op_pstr(stack_t **stack, unsigned int line_number)
{
	stack_t *current = *stack;

	(void)line_number;

	while (current != NULL && current->n > 0 && current->n <= 127)
	{
		putchar(current->n);
		current = current->next;
	}

	putchar('\n');
}

/**
 * op_rotl - rotate the first stack element to the bottom
 * @stack: pointer to the stack
 * @line_number: current line number
 */
void op_rotl(stack_t **stack, unsigned int line_number)
{
	stack_t *first;
	stack_t *tail;

	(void)line_number;

	if (*stack == NULL || (*stack)->next == NULL)
		return;

	first = *stack;
	*stack = first->next;
	(*stack)->prev = NULL;

	tail = *stack;
	while (tail->next != NULL)
		tail = tail->next;

	tail->next = first;
	first->prev = tail;
	first->next = NULL;
}

/**
 * op_rotr - rotate the last stack element to the top
 * @stack: pointer to the stack
 * @line_number: current line number
 */
void op_rotr(stack_t **stack, unsigned int line_number)
{
	stack_t *tail;

	(void)line_number;

	if (*stack == NULL || (*stack)->next == NULL)
		return;

	tail = *stack;
	while (tail->next != NULL)
		tail = tail->next;

	tail->prev->next = NULL;
	tail->prev = NULL;
	tail->next = *stack;
	(*stack)->prev = tail;
	*stack = tail;
}

/**
 * op_stack - switch the interpreter to stack mode
 * @stack: pointer to the stack
 * @line_number: current line number
 */
void op_stack(stack_t **stack, unsigned int line_number)
{
	(void)stack;
	(void)line_number;
	monty.mode = 0;
}

/**
 * op_queue - switch the interpreter to queue mode
 * @stack: pointer to the stack
 * @line_number: current line number
 */
void op_queue(stack_t **stack, unsigned int line_number)
{
	(void)stack;
	(void)line_number;
	monty.mode = 1;
}
