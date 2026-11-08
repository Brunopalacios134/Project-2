Smart Campus Navigation and Facility Analytics System
Project 2 - Milestone 1
Team: Bruno Palacios Busnelli, Donovan Ellis, Kristian Muteba
------------------------------------------------------------
1. PURPOSE
------------------------------------------------------------
This program manages campus information by loading data from four text files: 
buildings, connections, facilities, and departments. 

Users can explore campus buildings through a graph with Breadth-First Search (BFS) and 
manage the department hierarchy using a general tree. Facilities can be searched by 
ID using a custom hash table.

------------------------------------------------------------
2. BUILD
------------------------------------------------------------
From the project root:

    g++ -std=c++17 -Wall -Iinclude src/*.cpp -o campus

The program was compiled and tested on the UNT CSE CELL environment.
------------------------------------------------------------
3. RUN
------------------------------------------------------------
Default :

    ./campus

With a custom data directory:

    ./campus testdata/collision
------------------------------------------------------------
4. DIRECTORY LAYOUT
------------------------------------------------------------
include/              Header files (.h)
src/                  Source files (.cpp), including main.cpp
data/                 The four provided input files
testdata/collision/   Our test data that produces a hash collision
                      and a duplicate facility ID
tests/                Standalone unit test programs
README.txt            This file
CONTRIBUTIONS.txt     Team member contributions
design_document.txt   Design decisions
test_results.txt      Recorded test cases and results
