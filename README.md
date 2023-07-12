# LEDA-practice
This project was created as part of "Algorithm implementation technologies" subject in Computer Engineering &amp; Informatics Department (CEID) of University of Patras. It involves the creation of a bipartite graph detection as well as a validator code using the LEDA library

The goal of this project was to create an algorithm to find a bipartite graph and an algorithm to check if what we created works correctly. The logic of the checking algorithm, therefore, is to guarantee that what we have created is functional. Also, we were also asked to experiment with the function that the LEDA library provides for finding bipartite graphs and to compare the two algorithms mainly in terms of execution time.

The purpose was to experiment and gain experience with the LEDA library, as well as to study more practically how to run experiments on algorithms we create, Finally, with the help of this exercise, it became more understandable how we can prove that the structure we created is functional (correctness check).
Within this repository, there are 5 code files, which are listed below.

1. `squares.cpp` -- This code contains as test data the family of nested squares.
2. `circles.cpp` -- This code contains as test data the family of odd-length circles.
3. `l4_graph.cpp` -- This code contains as test data the family of 4-level graphs.
4. `bonus.cpp` -- This code contains as test data the n-level graph family.
5. `queue.h` -- Header file necessary to execute the above code files.
6. `Makefile` -- Running the "make" command creates executables for all four code files (assuming that LEDA is correctly installed in your system).
