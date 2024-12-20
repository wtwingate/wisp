#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "mpc.h"

int main(int argc, char *argv[])
{
    // create parsers
    mpc_parser_t* Number     = mpc_new("number");
    mpc_parser_t* Operator   = mpc_new("operator");
    mpc_parser_t* Expression = mpc_new("expression");
    mpc_parser_t* Wisp       = mpc_new("wisp");

    // define parsers
    mpca_lang(MPCA_LANG_DEFAULT,
	      " number     : /-?[0-9]+/;                                  "
	      " operator   : '+' | '-' | '*' | '/';                       "
	      " expression : <number> | '(' <operator> <expression>+ ')'; "
	      " wisp       : /^/ <operator> <expression>+ /$/;            ",
	      Number, Operator, Expression, Wisp);

    // welcome message
    printf("Wisp Version 0.0.1\n");
    printf("Press Ctrl+d to Exit\n\n");

    // read-eval-print loop
    while(1) {
	char *line = readline("wisp> ");
	if (!line) break;

        mpc_result_t res;
	if (mpc_parse("<stdin>", line, Wisp, &res)) {
	    // on success print AST
	    mpc_ast_print(res.output);
	    mpc_ast_delete(res.output);
	} else {
	    // on failure print error
	    mpc_err_print(res.error);
	    mpc_err_delete(res.error);
	}

	add_history(line);
	free(line);
    }

    // undefine and delete parsers
    mpc_cleanup(4, Number, Operator, Expression, Wisp);

    return 0;
}
