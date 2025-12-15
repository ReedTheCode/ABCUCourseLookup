#include <iostream>
#include <algorithm>
#include <cctype>
#include <sstream>
#include <string>
#include <vector>
#include <unordered_map>
#include <fstream>

using namespace std;

struct Course
{
    string id;
    string title;
    vector<string> prereqIds;
};

// -------------------Helper functions-------------------
static inline string trim(const string& s)
{
    size_t start = 0;
    while (start < s.size() && isspace(static_cast<unsigned char>(s[start]))) start++;

    size_t end = s.size();
    while (end > start && isspace(static_cast<unsigned char>(s[end - 1]))) end--;

    return s.substr(start, end - start);
}

static inline string toUpper(string s)
{
    transform(s.begin(), s.end(), s.begin(), [](unsigned char c) {return static_cast<char>(toupper(c)); });

    return s;
}

static vector<string> splitCSVLine(const string& line)
{
    vector<string> tokens;
    string token;
    stringstream ss(line);

    while (getline(ss, token, ','))
    {
        tokens.push_back(trim(token));
    }

    return tokens;
}

// -------------------Core functions-------------------

bool loadCoursesFromFile(const string& filename, unordered_map<string, Course>& coursesById)
{
    ifstream file(filename);
    if (!file.is_open())
    {
        cout << "Error: Could not open file." << endl;
        return false;
    }

    coursesById.clear();

    string line;
    int lineNum = 0;

    while (getline(file, line))
    {
        lineNum++;
        line = trim(line);
        if (line.empty()) continue;

        vector<string> parts = splitCSVLine(line);

        // Must have at least courseId and title
        if (parts.size() < 2 || trim(parts[0]).empty() || trim(parts[1]).empty())
        {
            cout << "Format error on line " << lineNum << ": line must contain courseID and Title." << endl;
            continue;
        }

        Course c;
        c.id = toUpper(parts[0]);
        c.title = parts[1];

        // Remaining tokens are prerequisites. Ignore the empties
        for (size_t i = 2; i < parts.size(); i++)
        {
            if (!parts[i].empty())
            {
                c.prereqIds.push_back(toUpper(parts[i]));
            }
        }

        coursesById[c.id] = c;
    }

    return true;
}

void printCourseList(const unordered_map<string, Course>& coursesById)
{
    vector<string> keys;
    keys.reserve(coursesById.size());
    for (const auto& kv : coursesById)
    {
        keys.push_back(kv.first);
    }

    sort(keys.begin(), keys.end()); // Alphanumeric sort by course ID

    cout << "Here is a sample schedule:" << endl;
    for (const string& id : keys)
    {
        const Course& c = coursesById.at(id);
        cout << c.id << ", " << c.title << endl;
    }
}

void printSingleCourse(const unordered_map<string, Course>& coursesById)
{
    cout << "What course do you want to know about? ";
    string input;
    cin >> input;
    input = toUpper(trim(input));

    auto it = coursesById.find(input);
    if (it == coursesById.end())
    {
        cout << "Course not found." << endl;
        return;
    }

    const Course& c = it->second;
    cout << c.id << ", " << c.title << endl;

    if (c.prereqIds.empty())
    {
        cout << "Prerequisites: None" << endl;
        return;
    }

    // Match sample output formatting: IDs only on one line
    cout << "Prerequisites: ";
    for (size_t i = 0; i < c.prereqIds.size(); i++)
    {
        cout << c.prereqIds[i];
        if (i + 1 < c.prereqIds.size()) cout << ", ";
    }
    cout << endl;

    for (const string& pid : c.prereqIds)
    {
        auto pit = coursesById.find(pid);
        if (pit != coursesById.end())
        {
            cout << "  " << pit->second.id << ", " << pit->second.title << endl;
        } else
        {
            cout << "  " << pid << " (title not found)" << endl;
        }
    }
}

// -------------------MENU-------------------
void printMenu()
{
    cout << "1. Load Data Structure." << endl;
    cout << "2. Print Course List." << endl;
    cout << "3. Print Course." << endl;
    cout << "9. Exit" << endl;
}

int main()
{
    unordered_map<string, Course> coursesById;
    bool loaded = false;

    cout << "Welcome to the course planner!" << endl;

    while (true)
    {
        printMenu();
        cout << "What would you like to do? ";

        string choiceStr;
        cin >> choiceStr;

        // Handle non-numeric input robustly
        bool allDigits = !choiceStr.empty() && all_of(choiceStr.begin(), choiceStr.end(), [](unsigned char ch) {return isdigit(ch); });

        if (!allDigits)
        {
            cout << choiceStr << " is not a valid option." << endl;
            continue;
        }

        int choice = stoi(choiceStr);

        switch (choice)
        {
            case 1:
                {
                    cout << "Enter file name: ";
                    string filename;
                    cin >> filename;

                    loaded = loadCoursesFromFile(filename, coursesById);
                    if (loaded) cout << "Data loaded successfully!" << endl;
                    break;
                }
            case 2:
                if (!loaded)
                {
                    cout << "Please load data first." << endl;
                    break;
                }
                printCourseList(coursesById);
                break;

        case 3:
            if (!loaded)
            {
                cout << "Please load data first." << endl;
                break;
            }
            printSingleCourse(coursesById);
            break;

        case 9:
            cout << "Thank you for using the course planner!" << endl;
            return 0;

        default:
            cout << choice << " is not a valid option." << endl;
            break;
        }
    }
}