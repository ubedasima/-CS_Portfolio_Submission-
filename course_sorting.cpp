#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <unordered_map>
#include <algorithm>

using namespace std;

// Course structure
struct Course {
    string courseNumber;
    string courseTitle;
    vector<string> prerequisites;
};

// Function to split a string into tokens based on a delimiter
vector<string> split(const string& str, char delimiter) {
    vector<string> tokens;
    stringstream ss(str);
    string token;

    while (getline(ss, token, delimiter)) {
        tokens.push_back(token);
    }
    return tokens;
}

// Function to read courses from the input file
bool readCourses(const string& filePath, unordered_map<string, Course>& courseMap) {
    ifstream file(filePath);
    if (!file.is_open()) {
        cout << "Error: File cannot be opened." << endl;
        return false;
    }

    string line;
    int lineNumber = 0;

    while (getline(file, line)) {
        lineNumber++;
        vector<string> tokens = split(line, ',');

        // Check for at least two tokens (courseNumber and courseTitle)
        if (tokens.size() < 2) {
            cout << "Error: File format invalid on line " << lineNumber << endl;
            return false;
        }

        // Create a new Course object
        Course course;
        course.courseNumber = tokens[0];
        course.courseTitle = tokens[1];

        // Add prerequisites if present
        for (size_t i = 2; i < tokens.size(); ++i) {
            course.prerequisites.push_back(tokens[i]);
        }

        // Insert the course into the hash table
        courseMap[course.courseNumber] = course;
    }

    file.close();
    return true;
}

// Function to print the sorted list of courses
void printSortedCourses(const vector<Course>& courses) {
    cout << "\nSorted Course List:\n";
    for (const Course& course : courses) {
        cout << course.courseNumber << " - " << course.courseTitle << endl;
    }
}

int main() {
    unordered_map<string, Course> courseMap; // Hash table to store courses
    vector<Course> courseList;

    string filePath;

    // Prompt user to enter the file path
    cout << "Enter the file path: ";
    cin >> filePath;

    // Step 1: Read courses from the file
    if (!readCourses(filePath, courseMap)) {
        return 1; // Exit on error
    }

    // Step 2: Transfer courses from hash table to a vector for sorting
    for (const auto& pair : courseMap) {
        courseList.push_back(pair.second);
    }

    // Step 3: Sort the courses alphanumerically by course number
    sort(courseList.begin(), courseList.end(), [](const Course& a, const Course& b) {
        return a.courseNumber < b.courseNumber;
        });

    // Step 4: Print the sorted list of courses
    printSortedCourses(courseList);

    return 0;
}
