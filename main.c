#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>

int main(int argc, char *argv[])
{
    // welcome message
    printf("Wisp Version 0.0.1\n");
    printf("Press Ctrl+d to Exit\n\n");

    // read-eval-print loop
    while(1) {
	char *line = readline("wisp> ");
	if (!line) break;

	printf("Quoth the Raven, \"%s\"\n", line);

	add_history(line);
	free(line);
    }

    return 0;
}
