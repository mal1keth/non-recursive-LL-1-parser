
build: main.c helpers.c input_grammar.c first_follow.c parse_table.c parser.c _stack.c grammar.txt
	gcc main.c helpers.c input_grammar.c first_follow.c parse_table.c parser.c _stack.c -o parser