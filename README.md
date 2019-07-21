How to build and run:
1. Compile the code with g++ (or any other c++ compiler).
2. Run the output file.
3. Input the name of DIMACS file from which input is to be taken.
4. You will get the output.

Heuristics used:
Unit propagation:
 Find all the unit clauses.
 If a set of clauses contain a unit clause, then this set is deleted.
 If a set of clauses contain the negation of a unit clause, then this element is deleted.

