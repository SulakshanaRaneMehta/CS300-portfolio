CS 300 Project One (Continuation)
Sulakshana Mehta
June 13, 2025

This document contains two main parts: PSEUDOCODE and EVALUATION. It covers three milestones from previous assignments: Milestone One (Vector), Milestone Two (Hash Table), and Milestone Three (Binary Search Tree).

PSEUDOCODE

1. Vector-Based Pseudocode
The vector-based approach involves reading course data into a dynamically resizable array (vector). This structure allows sequential access and sorting, making it suitable for small datasets where order matters but fast retrieval is not critical.

a. Open File, read, parse, and check formatting errors
Function LoadCoursesFromFile(filename)
    Open file with name 'filename'
    While not end of file
        Read line from file
        Split line by ',' into tokens
        If number of tokens < 2
            Print "Formatting error in line: " + line
            Continue
        EndIf
        Call CreateCourse(tokens)
    EndWhile
    Close file
EndFunction

b. Create course object from a line
This function parses each line, creates a course object, and appends it to a vector.
Function CreateCourse(tokens)
    courseNumber = tokens[0]
    courseTitle = tokens[1]
    prerequisites = Empty list
    For i from 2 to length(tokens) - 1
        Append tokens[i] to prerequisites
    EndFor
    Create Course object with courseNumber, courseTitle, prerequisites
    Append Course object to VectorCourses
EndFunction

c. Print course information and prerequisites
This function performs a linear search on the vector to find and display a specific course.
Function PrintCourseInfo(courseNumber)
    For each course in VectorCourses
        If course.courseNumber == courseNumber
            Print "Course Number: " + course.courseNumber
            Print "Title: " + course.courseTitle
            If course.prerequisites is empty
                Print "Prerequisites: None"
            Else
                Print "Prerequisites: " + join(course.prerequisites, ", ")
            EndIf
            Return
        EndIf
    EndFor
    Print "Course not found."
EndFunction
2. Hash Table-Based Pseudocode
Using a hash table provides constant-time retrieval, which is ideal for fast lookups. However, additional steps are required for sorted output since hash tables are unordered.

a. Open file, read, parse, and check formatting errors
Same as vector version, but CreateCourse inserts into HashTableCourses instead.

b. Create course object from a line
This function inserts the parsed course into a hash table with the course number as the key.
Function CreateCourse(tokens)
    courseNumber = tokens[0]
    courseTitle = tokens[1]
    prerequisites = Empty list
    For i from 2 to length(tokens) - 1
        Append tokens[i] to prerequisites
    EndFor
    Create Course object with courseNumber, courseTitle, prerequisites
    Insert into HashTableCourses using courseNumber as key
EndFunction

c. Print course information and prerequisites
Hash table allows fast direct access by course number.
Function PrintCourseInfo(courseNumber)
    If courseNumber in HashTableCourses
        course = HashTableCourses[courseNumber]
        Print "Course Number: " + course.courseNumber
        Print "Title: " + course.courseTitle
        If course.prerequisites is empty
            Print "Prerequisites: None"
        Else
            Print "Prerequisites: " + join(course.prerequisites, ", ")
        EndIf
    Else
        Print "Course not found."
    EndIf
EndFunction

3. Binary Search Tree-Based Pseudocode
A binary search tree (BST) maintains data in sorted order, allowing efficient in-order traversal. This structure is especially effective when both lookup and ordered listing are required.

a. Open file, read, parse, and check formatting errors
Same logic as above, but uses TreeInsert in CreateCourse.

b. Create course object from a line
Parsed course objects are inserted into the BST based on course number.
Function CreateCourse(tokens)
    courseNumber = tokens[0]
    courseTitle = tokens[1]
    prerequisites = Empty list
    For i from 2 to length(tokens) - 1
        Append tokens[i] to prerequisites
    EndFor
    Create Course object with courseNumber, courseTitle, prerequisites
    Insert into BinarySearchTree by courseNumber
EndFunction

c. Print course information and prerequisites
Efficient retrieval using BST search.
Function PrintCourseInfo(courseNumber)
    node = BSTSearch(courseNumber)
    If node != null
        course = node.course
        Print "Course Number: " + course.courseNumber
        Print "Title: " + course.courseTitle
        If course.prerequisites is empty
            Print "Prerequisites: None"
        Else
            Print "Prerequisites: " + join(course.prerequisites, ", ")
        EndIf
    Else
        Print "Course not found."
    EndIf
EndFunction

4. Menu Pseudocode
This function provides an interactive menu that allows users to perform common operations: load data, list courses, or get course details.
Function MainMenu()
    Repeat
        Print "1. Load Data"
        Print "2. Print Course List"
        Print "3. Print Course Details"
        Print "9. Exit"
        Read userChoice

        If userChoice == 1
            Call LoadCoursesFromFile("courses.txt")
        Else If userChoice == 2
            Call PrintAllCourses()
        Else If userChoice == 3
            Read courseNumber
            Call PrintCourseInfo(courseNumber)
        Else If userChoice == 9
            Print "Goodbye!"
        Else
            Print "Invalid option."
        EndIf
    Until userChoice == 9
EndFunction

5. Print Sorted List (Vector, Hash Table, Tree)
Each implementation uses its own mechanism to provide a sorted list of courses.

Vector:
Function PrintAllCourses()
    Sort VectorCourses by courseNumber (ascending)
    For each course in VectorCourses
        Print course.courseNumber + ": " + course.courseTitle
    EndFor
EndFunction

Hash Table:
Function PrintAllCourses()
    Extract all values from HashTableCourses to a list
    Sort list by courseNumber
    For each course in list
        Print course.courseNumber + ": " + course.courseTitle
    EndFor
EndFunction

Binary Search Tree:
Function PrintAllCourses()
    InOrderTraversal(root)

Function InOrderTraversal(node)
    If node is not null
        InOrderTraversal(node.left)
        Print node.course.courseNumber + ": " + node.course.courseTitle
        InOrderTraversal(node.right)
    EndIf
EndFunction

EVALUATION

6. Runtime and Memory Analysis Chart
This section compares the time complexity and memory use of each data structure for the loading process.
Operation	Vector	Hash Table	Binary Search Tree (Balanced)
Load Time	O(n)	O(n)	O(n log n)
Search Time	O(n)	O(1)	O(log n)
Sort Time	O(n log n)	O(n log n)*	O(n)**
Memory Use	Moderate	Higher (buckets)	Moderate
Sorted Output	Manual sorting	Manual sorting	Built-in (via traversal)

* Hash table sorting requires extracting values and sorting externally.
** BST traversal produces sorted output directly, no extra sorting step needed.
7. Runtime Evaluation
Vector
•	Load Time: O(n) – All elements are appended in order.
•	Search: O(n) – Linear search required.
•	Sort: O(n log n) – Additional sort operation required.
Hash Table
•	Load Time: O(n) – Constant time insertions.
•	Search: O(1) – Constant-time retrieval by key.
•	Sort: O(n log n) – Requires extraction and sorting.
Binary Search Tree
•	Load Time: O(n log n) – Each insertion takes O(log n).
•	Search: O(log n) – Efficient lookup.
•	Sort: O(n) – In-order traversal outputs sorted list without extra operations.
Evaluation Summary:
•	For raw speed in retrieval, the hash table is optimal.
•	For maintaining order without needing to sort, the BST excels.
•	The vector is simple and sufficient only when working with small, infrequent datasets.
8. Advantages and Disadvantages
Vector
•	Advantages: Simple, lightweight, and easy to implement. Familiar to most programmers.
•	Disadvantages: Inefficient search; sorting must be done manually each time.
Hash Table
•	Advantages: Near-instantaneous access by key, very efficient.
•	Disadvantages: Unordered structure requires additional logic to sort courses.
Binary Search Tree
•	Advantages: Automatically keeps data in sorted order. Efficient for search and list.
•	Disadvantages: More complex to implement. Performance depends on tree balance.

9. Recommendation
Given the academic advising scenario, which involves frequent sorted course listings and direct course lookups, the Binary Search Tree is recommended for implementation. It supports:
•	O(log n) search time
•	Sorted output by design
•	Scalable and organized data structure
If ease of implementation is prioritized over runtime optimization, the Hash Table offers an excellent compromise for lookup operations, although it lacks a natural mechanism for maintaining sorted data.
