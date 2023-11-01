Predictive / Non-recursive LL(1) Parser

Work in progress.


1. Write grammar specifications in grammar.txt. The format is:
    ``<non-terminal>:<non-terminal><terminal>|``   // <- indicates epsilon
2. Both non-terminal and terminal should be single characters. 
3. The grammar should be LL(1) and not left recursive.
4. Run ```make build ``` to compile
5. Enter a string through stdin and press enter.


Data Structures:

1.  sym: Each Symbol in the grammar productions is represented using Sym. It has attributes type (to represent Terminal or Non-Terminal) and Data to represent the symbol

2.  Node: Each Node represents a single production in the Grammar. It has an array of Symbols, n is used to denote its size. Next pointer points to the next production of parent non-terminal.

3. gramm: Dummy struct created to be able to return the Grammar G and number of non-terminal n, in one go from input function. (Is there a better way?)

4. Grammar G: is represented as an array of linked lists. The array has size n for number of non-terminals and each cell i has a linked list, which is the productions of G[i].

5. char_set: Struct which simply contains an array of characters called items. Default size is 128.

6. FIRST(X), FOLLOW(X): Use the ff struct (defined in first_follow.h) to store the first and follow of each terminal/non-terminal. FIRST and FOLLOW sets are defined as char_sets.
(In a possible refactoring, we can get rid of char_set and declare FIRST and FOLLOW as an array of Sym of size 128). 

In main.c we manually add FIRST[X] = {X} for all terminals X. This is necessary as when parse table tries to find FIRST[Y_1...Y_k], the output would become incorrect if any of the Y_i's were terminals.

7. Parse Table is represented as a 2D array of char pointers. Assignment is done as M[N][T] = prod where N, T are characters and prod is a char pointer.

8. Stack : Simple stack data structure with helper functions, which uses table doubling.