// ProjectTwo.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

// Stores course information, including the course number, title, and prerequisites.
struct Course {
    string courseNumber;
    string courseTitle;
    vector<string> prerequisites;
};

// Represents a node in the binary search tree.
struct Node {
    Course course;
    Node* left;
    Node* right;

    Node(Course newCourse) {
        course = newCourse;
        left = nullptr;
        right = nullptr;
    }
};

// Manages course storage, searching, insertion, traversal, and memory cleanup.
class BinarySearchTree {

private:
    Node* root;

    void InsertNode(Node* node, Course course);
    void InOrder(Node* node);
    void DeleteTree(Node* node);

public:
    BinarySearchTree();
    ~BinarySearchTree();
    void Clear();
    void Insert(Course course);
    Course Search(string courseNumber);
    void PrintCourseList();
};

// Initializes an empty binary search tree.
BinarySearchTree::BinarySearchTree() {
    root = nullptr;
}

// Releases all dynamically allocated nodes when the tree is destroyed.
BinarySearchTree::~BinarySearchTree() {

    // Removes all nodes from the tree and resets the root.
    Clear();
}

// Recursively deletes nodes using post-order traversal.
void BinarySearchTree::DeleteTree(Node* node) {
    if (node != nullptr) {
        DeleteTree(node->left);
        DeleteTree(node->right);
        delete node;
    }
}

void BinarySearchTree::Clear() {
    DeleteTree(root);
    root = nullptr;
}
 
// Inserts a course into the binary search tree.
void BinarySearchTree::Insert(Course course) {
    if (root == nullptr) {
        root = new Node(course);
    }
    else {
        InsertNode(root, course);
    }
}

// Recursively places a course according to its course number.
void BinarySearchTree::InsertNode(Node* node, Course course) {
    if (course.courseNumber < node->course.courseNumber) {
        if (node->left == nullptr) {
            node->left = new Node(course);
        }
        else {
            InsertNode(node->left, course);
        }
    }

    else {
        if (node->right == nullptr) {
            node->right = new Node(course);
        }
        else {
            InsertNode(node->right, course);
        }
    }
}

// Searches the binary search tree for a specified course number.
Course BinarySearchTree::Search(string courseNumber) {
    Node* current = root;

    while (current != nullptr) {
        if (current->course.courseNumber == courseNumber) {
            return current->course;
        }

        if (courseNumber < current->course.courseNumber) {
            current = current->left;
        }
        else {
            current = current->right;
        }
    }

    Course emptyCourse;
    return emptyCourse;
}

// Traverses the binary search tree in order to print courses alphanumerically.
void BinarySearchTree::InOrder(Node* node) {

    if (node != nullptr) {
        InOrder(node->left);

        cout << node->course.courseNumber << ", "
            << node->course.courseTitle << endl;

        InOrder(node->right);
    }
}

// Prints all courses in alphanumeric order using in-order traversal
void BinarySearchTree::PrintCourseList() {
    InOrder(root);
}

// Loads and validates course data from the input file.
bool LoadCourses(string fileName, BinarySearchTree& courses) {
    ifstream file(fileName);

    if (!file.is_open()) {
        cout << "Error: Could not open file." << endl;
        return false;
    }

    string line;

    vector<Course> loadedCourses;

    while (getline(file, line)) {
        stringstream ss(line);
        string token;
        vector<string> tokens;

        while (getline(ss, token, ',')) {
            tokens.push_back(token);
        }

        if (tokens.size() < 2) {
            cout << "Error: Invalid course record." << endl;
            file.close();
            return false;
        }

        Course course;
        course.courseNumber = tokens[0];
        course.courseTitle = tokens[1];

        for (size_t i = 2; i < tokens.size(); ++i) {
            if (!tokens[i].empty()) {
                course.prerequisites.push_back(tokens[i]);
            }            
        }

        courses.Insert(course);
        loadedCourses.push_back(course);
    }

    // Verifies that every listed prerequisite exists in the loaded course data.
    for (const Course& course : loadedCourses) {
        for (const string& prerequisiteNumber : course.prerequisites) {
            Course prerequisiteCourse = courses.Search(prerequisiteNumber);

            if (prerequisiteCourse.courseNumber.empty()) {
                cout << "Error: Prerequisite " << prerequisiteNumber
                    << " for " << course.courseNumber
                    << " does not exist in the course data." << endl;
                courses.Clear();
                file.close();
                return false;
            }
        }
    }
    file.close();
    return true;
}

// Runs the course planner menu and processes user selections.
int main() {
    BinarySearchTree courses;

    string fileName;
    int choice = 0;
    bool dataLoaded = false;

    cout << "Welcome to the course planner. " << endl;

    // Displays the menu repeatedly until the user chooses to exit.
    while (choice != 9) {
        cout << endl;
        cout << "1. Load Data Structure." << endl;
        cout << "2. Print Course List." << endl;
        cout << "3. Print Course." << endl;
        cout << "9. Exit" << endl;
        cout << endl;
        cout << "What would you like to do? ";

        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Invalid input. Please enter a menu number." << endl;
            continue;
        }

        // Loads and validates course data from the selected input file.
        if (choice == 1) {
            cout << "Enter course data file name: ";
            getline(cin >> ws, fileName);
            courses.Clear();

            if (LoadCourses(fileName, courses)) {
                cout << "Course data loaded successfully." << endl;
                dataLoaded = true;
            }

            else {
                dataLoaded = false;
            }
        }

        else if (choice == 2) {
            if (!dataLoaded) {
                cout << "Please load the course data first." << endl;
            }

            else {
                cout << endl << "Here is a sample schedule: " << endl << endl;
                courses.PrintCourseList();
            }
        }

        // Searches for and displays an individual course and its prerequisites.
        else if (choice == 3) {
            if (!dataLoaded) {
                cout << "Please load the course data first." << endl;
            }

            else {
                string requestedCourseNumber;

                cout << "What course do you want to know about? ";
                cin >> requestedCourseNumber;
                transform(requestedCourseNumber.begin(), requestedCourseNumber.end(), requestedCourseNumber.begin(), ::toupper);

                Course foundCourse = courses.Search(requestedCourseNumber);

                if (!foundCourse.courseNumber.empty()) {
                    cout << foundCourse.courseNumber << ", "
                        << foundCourse.courseTitle << endl;

                    if (foundCourse.prerequisites.empty()) {
                        cout << "Prerequisites: None" << endl;
                    }

                    else {
                        cout << "Prerequisites:" << endl;

                        for (const string& prerequisiteNumber : foundCourse.prerequisites) {
                            Course prerequisiteCourse = courses.Search(prerequisiteNumber);

                            if (!prerequisiteCourse.courseNumber.empty()) {
                                cout << prerequisiteCourse.courseNumber << ", "
                                    << prerequisiteCourse.courseTitle << endl;
                            }
                        }
                    }
                }

                else {
                    cout << "Course not found." << endl;
                }
            }
        }

        else if (choice == 9) {
            cout << "Thank you for using the course planner!" << endl;
        }

        else {
            cout << choice << " is not a valid option." << endl;
        }
    }

    return 0;
}
   


