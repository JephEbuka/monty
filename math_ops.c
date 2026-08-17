#include "monty.h"

/**
 * require_two - ensure at least two stack elements exist
 * @stack: pointer to the stack
 * @line_number: current line number
 * @opcode: opcode used in the error message
 */
static void require_two(stack_t **stack, unsigned int line_number,
			const char *opcode)
{
	if (*stack == NULL || (*stack)->next == NULL)
	{
		fprintf(stderr, "L%u: can't %s, stack too short\n",
			line_number, opcode);
		monty_fail(*stack);
	}
}

/**
 * remove_top - remove the top node from a stack
 * @stack: pointer to the stack
 */
static void remove_top(stack_t **stack)
{
	stack_t *top = *stack;

	*stack = top->next;
	(*stack)->prev = NULL;
	free(top);
}

/**
 * op_add - add the top two stack values
 * @stack: pointer to the stack
 * @line_number: current line number
 */
void op_add(stack_t **stack, unsigned int line_number)
{
	require_two(stack, line_number, "add");
	(*stack)->next->n += (*stack)->n;
	remove_top(stack);
}

/**
 * op_sub - subtract top from second top stack value
 * @stack: pointer to the stack
 * @line_number: current line number
 */
void op_sub(stack_t **stack, unsigned int line_number)
{
	require_two(stack, line_number, "sub");
	(*stack)->next->n -= (*stack)->n;
	remove_top(stack);
}

/**
 * op_div - divide second top by top stack value
 * @stack: pointer to the stack
 * @line_number: current line number
 */
void op_div(stack_t **stack, unsigned int line_number)
{
	require_two(stack, line_number, "div");

	if ((*stack)->n == 0)
	{
		fprintf(stderr, "L%u: division by zero\n", line_number);
		monty_fail(*stack);
	}

	(*stack)->next->n /= (*stack)->n;
	remove_top(stack);
}

/**
 * op_mul - multiply the top two stack values
 * @stack: pointer to the stack
 * @line_number: current line number
 */
void op_mul(stack_t **stack, unsigned int line_number)
{
	require_two(stack, line_number, "mul");
	(*stack)->next->n *= (*stack)->n;
	remove_top(stack);
}

/**
 * op_mod - calculate second top modulo top stack value
 * @stack: pointer to the stack
 * @line_number: current line number
 */
void op_mod(stack_t **stack, unsigned int line_number)
{
	require_two(stack, line_number, "mod");

	if ((*stack)->n == 0)
	{
		fprintf(stderr, "L%u: division by zero\n", line_number);
		monty_fail(*stack);
	}

	(*stack)->next->n %= (*stack)->n;
	remove_top(stack);
}
