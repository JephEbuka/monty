#include "monty.h"

monty_state_t monty = {NULL, NULL, NULL, 0};

/**
 * main - run the Monty bytecode interpreter
 * @argc: number of command-line arguments
 * @argv: command-line arguments
 *
 * Return: EXIT_SUCCESS on success, EXIT_FAILURE on failure
 */
int main(int argc, char **argv)
{
	stack_t *stack = NULL;
	size_t length = 0;
	ssize_t read;
	unsigned int line_number = 0;
	char *opcode;

	if (argc != 2)
	{
		fprintf(stderr, "USAGE: monty file\n");
		return (EXIT_FAILURE);
	}

	monty.file = fopen(argv[1], "r");
	if (monty.file == NULL)
	{
		fprintf(stderr, "Error: Can't open file %s\n", argv[1]);
		return (EXIT_FAILURE);
	}

	while ((read = getline(&monty.line, &length, monty.file)) != -1)
	{
		(void)read;
		line_number++;
		opcode = strtok(monty.line, " \t\r\n");

		if (opcode == NULL || opcode[0] == '#')
			continue;

		monty.arg = strtok(NULL, " \t\r\n");

		if (execute_opcode(opcode, &stack, line_number) == EXIT_FAILURE)
		{
			fprintf(stderr, "L%u: unknown instruction %s\n",
				line_number, opcode);
			monty_fail(stack);
		}
	}

	free_stack(stack);
	free(monty.line);
	fclose(monty.file);

	return (EXIT_SUCCESS);
}
