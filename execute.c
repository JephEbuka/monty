#include "monty.h"

/**
 * execute_opcode - execute an opcode
 * @opcode: opcode string
 * @stack: pointer to the stack
 * @line_number: current bytecode line number
 *
 * Return: EXIT_SUCCESS if opcode exists, otherwise EXIT_FAILURE
 */
int execute_opcode(char *opcode, stack_t **stack, unsigned int line_number)
{
	instruction_t instructions[] = {
		{"push", op_push},
		{"pall", op_pall},
		{"pint", op_pint},
		{"pop", op_pop},
		{"swap", op_swap},
		{"add", op_add},
		{"nop", op_nop},
		{"sub", op_sub},
		{"div", op_div},
		{"mul", op_mul},
		{"mod", op_mod},
		{"pchar", op_pchar},
		{"pstr", op_pstr},
		{"rotl", op_rotl},
		{"rotr", op_rotr},
		{"stack", op_stack},
		{"queue", op_queue},
		{NULL, NULL}
	};
	int index = 0;

	while (instructions[index].opcode != NULL)
	{
		if (strcmp(opcode, instructions[index].opcode) == 0)
		{
			instructions[index].f(stack, line_number);
			return (EXIT_SUCCESS);
		}
		index++;
	}

	return (EXIT_FAILURE);
}
