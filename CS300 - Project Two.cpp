// CS 300 - Project Two
// Sulakshana Mehta
// June 20, 2025

#include <algorithm>
#include <cctype>
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

// Structure to hold course information
struct Course {
  string courseId;
  string title;
  vector<string> prerequisites;
};

// Converts string to uppercase for consistent lookups
string toUpper(string input) {
  for (char &c : input) {
    c = toupper(c);
  }
  return input;
}

// Function to split a CSV line into tokens
vector<string> splitLine(const string &line, char delimiter = ',') {
  vector<string> tokens;
  stringstream ss(line);
  string token;
  while (getline(ss, token, delimiter)) {
    tokens.push_back(token);
  }
  return tokens;
}

// Function to load course data from a file into a vector
void loadCourses(string fileName, vector<Course> &courses) {
  ifstream file(fileName);
  if (!file.is_open()) {
    cerr << "Error: Could not open file " << fileName << endl;
    return;
  }

  string line;
  while (getline(file, line)) {
    vector<string> tokens = splitLine(line);
    if (tokens.size() < 2)
      continue; // Ensure the line has at least ID and title

    Course course;
    course.courseId = tokens[0];
    course.title = tokens[1];

    for (size_t i = 2; i < tokens.size(); ++i) {
      if (!tokens[i].empty()) {
        course.prerequisites.push_back(tokens[i]);
      }
    }

    courses.push_back(course); // Add course to the list
  }
  file.close();
  cout << "Courses loaded successfully.\n";
}

// Function to print course list in alphanumeric order
void printCourseList(const vector<Course> &courses) {
  // Create a temporary vector to sort by courseId
  vector<Course> sortedCourses = courses;
  sort(sortedCourses.begin(), sortedCourses.end(),
       [](const Course &a, const Course &b) {
         return toUpper(a.courseId) < toUpper(b.courseId);
       });

  cout << "\nHere is a sample schedule:\n";
  for (const Course &c : sortedCourses) {
    cout << c.courseId << ", " << c.title << endl;
  }
}

// Function to print specific course information by searching the vector
void printCourseInfo(const vector<Course> &courses, const string &courseId) {
  string upperId = toUpper(courseId);
  bool found = false;

  for (const Course &c : courses) {
    if (toUpper(c.courseId) == upperId) {
      cout << c.courseId << ", " << c.title << endl;
      cout << "Prerequisites: ";
      if (c.prerequisites.empty()) {
        cout << "None";
      } else {
        for (size_t i = 0; i < c.prerequisites.size(); ++i) {
          cout << c.prerequisites[i];
          if (i < c.prerequisites.size() - 1)
            cout << ", ";
        }
      }
      cout << endl;
      found = true;
      break;
    }
  }
  if (!found) {
    cout << "Course not found: " << courseId << endl;
  }
}

// Main program loop
int main() {
  vector<Course> courses; // Stores all courses as a list
  int choice;
  string fileName;

  cout << "Welcome to the course planner.\n";

  do {
    // Display the main menu
    cout << "\n1. Load Data Structure.\n";
    cout << "2. Print Course List.\n";
    cout << "3. Print Course.\n";
    cout << "9. Exit\n";
    cout << "What would you like to do? ";
    cin >> choice;

    switch (choice) {
    case 1:
      cout << "Enter file name: ";
      cin >> fileName;
      loadCourses(fileName, courses); // Load course data into vector
      break;
    case 2:
      if (courses.empty()) {
        cout << "Please load course data first using option 1.\n";
      } else {
        printCourseList(courses); // Print sorted list of courses
      }
      break;
    case 3: {
      if (courses.empty()) {
        cout << "Please load course data first using option 1.\n";
        break;
      }
      string courseId;
      cout << "What course do you want to know about? ";
      cin >> courseId;
      printCourseInfo(courses, courseId); // Print specific course info
      break;
    }
    case 9:
      cout << "Thank you for using the course planner!\n";
      break;
    default:
      // Handle invalid input
      cout << choice << " is not a valid option.\n";
    }

  } while (choice != 9);

  return 0;
}
