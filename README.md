# SNHU CS 300 - Data Structures and Algorithms
This repository contains selected work from CS 300: Data Structures and Algorithms. The projects demonstrate my understanding of data structures, algorithm efficiency, and the use of C++ to solve programming problems.

## What was the problem you were solving in the projects for this course?
The projects in this course focused on developing an advising assistance program that could store, organize, search, and display course information for academic advisors. Project One required me to evaluate different data structures and compare their run-time and memory characteristics to determine which structure would be most appropriate for the program. In Project Two, I implemented the program in C++ using a binary search tree to load course data, display the courses in alphanumeric order, and allow a user to search for an individual course and its prerequisites.

## How did you approach the problem? Consider why data structures are important to understand.
I approached the problem by first considering how the program needed to use the data rather than simply choosing a data structure and writing code around it. The program needed to load course information, search for individual courses, and produce an ordered list of courses. Understanding the advantages and disadvantages of different data structures helped me determine which structure best supported those requirements. A binary search tree provided an effective way to organize the course numbers while also allowing an in-order traversal to produce the required alphanumeric course list.

## How did you overcome any roadblocks you encountered while going through the activities or project?
One of the biggest lessons from the course was the importance of testing individual parts of a program instead of waiting until everything was finished. When I encountered problems, I worked through them incrementally by building and testing after changes and checking the program with different types of input. For Project Two, this included testing valid and invalid menu selections, courses with and without prerequisites, invalid file names, and course data containing prerequisites that did not exist. This approach made it easier to identify where a problem originated and correct it without introducing additional problems elsewhere in the program.

## How has your work on this project expanded your approach to designing software and developing programs?
This course reinforced the importance of considering program design before beginning implementation. The same problem can be solved with several different data structures or algorithms, but those choices affect efficiency, complexity, and how easily the program can satisfy its requirements. I now give more consideration to how data will be stored, searched, sorted, and modified before deciding how to implement a solution.

## How has your work on this project evolved the way you write programs that are maintainable, readable, and adaptable?
My work in this course has made me more deliberate about organizing code into functions with specific responsibilities and using descriptive names and comments where they improve readability. Project Two separated tasks such as loading data, inserting and searching for courses, traversing the binary search tree, and displaying information instead of placing everything inside the main function. I also added input validation and error handling so the program could respond appropriately to unexpected input. These practices make the code easier to understand, test, maintain, and modify later.

## Build and Run

Project Two is a C++ console application developed in Microsoft Visual Studio. It uses a binary search tree to organize course information and display courses in alphanumeric order.

### Instructions

1. Open `CS300_ProjectTwo_Portfolio/ProjectTwo.slnx` in Visual Studio.
2. Build and run the project.
3. Select **1. Load Data Structure** from the menu.
4. When prompted for a filename, enter:

   `CS 300 ABCU_Advising_Program_Input.csv`

5. Select **2. Print Course List** to display all courses in alphanumeric order.
6. Select **3. Print Course** to search for a specific course and display its prerequisites.
7. Select **9. Exit** to close the application.

The sample CSV file is included with the Visual Studio project. The application also validates course records, detects duplicate course numbers, verifies prerequisites, and handles invalid input.
