# SAT Solver

## Author : Harsh Agarwal

How to build and run:
1. Compile the code with g++ (or any other c++ compiler)
``` 
g++ SAT_Solver.cpp 
```
2. Run the output file.

```
./a.out
```
3. Input the name of DIMACS file from which input is to be taken.
4. You will get the output.

Implemented DPLL algorithm which on top of backtracking uses:

Unit propagation:
If a clause is a unit clause, i.e. it contains only a single unassigned literal, this clause can only be satisfied by assigning the necessary value to make this literal true. Thus, no choice is necessary. In practice, this often leads to deterministic cascades of units, thus avoiding a large part of the naive search space.

Pure Literal Elimination:
If a propositional variable occurs with only one polarity in the formula, it is called pure. Pure literals can always be assigned in a way that makes all clauses containing them true. Thus, these clauses do not constrain the search anymore and can be deleted.
