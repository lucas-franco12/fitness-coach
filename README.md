Instructions:
1. Put all the files into a folder in the student cluster.
2. Open the folder using the following command:
cd [folder name]
3. Type the following commands:
g++ driver.cpp -std=c++11 -Wall
./a.out
4. Follow the instructions within the program to use it.


Project Structures:
Exercise.hpp: Defines the class of Exercise
PlanLinkedList: - PlanNode (a node in LinkedList that includes Exercise info)
                - PlanLL (A doubly-linkedlist with basic operations)
Coach: A class to manage user operations (buildPlan, add, remove exercise from plan)
helper.cpp: a file includes helper functions for driver.cpp
driver.cpp: a file includes main function served as a menu and control the main loop

References:
json.hpp: https://github.com/nlohmann/json
HeapQueue.hpp: Class files/project 3

