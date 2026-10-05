#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <ctime>

using namespace std;

//this is what we use to describe our task
struct Task {
    string description;
    int priority;
    string dateAdded;
};

//functions we will be using during our program
string getCurrentDateTime();
void printMenu();
void displayTasks(const vector<Task>& taskList);
void addTask(vector<Task>& taskList);
void removeTask(vector<Task>& taskList);
void customSortAlphabetical(vector<Task>& taskList, bool reverse);
void customSortByPriority(vector<Task>& taskList);
void resetTaskList(vector<Task>& taskList);
void saveToFile(const vector<Task>& taskList, const string& fileName);
void loadFromFile(vector<Task>& taskList, const string& fileName);
bool isPriorityTaken(const vector<Task>& taskList, int priority);

int main() {
    vector<Task> taskList;
    string fileName = "todo_list.txt";

    cout << "_________________________________________________" << endl;
    cout << "Welcome user, this is the to do list program" << endl;
    cout << "__________________________________________________" << endl;

    //attempt to auto-load existing list on startup
    loadFromFile(taskList, fileName);

    //setup if there is no existing file loaded tasks
    if (taskList.empty()) {
        int initialCount = 0;
        cout << "How many entries would you like to start with? ";
        cin >> initialCount;
        cin.ignore(10000, '\n');

        for (int i = 0; i < initialCount; ++i) {
            cout << "Adding initial task #" << (i + 1) << ":" << endl;
            addTask(taskList);
        }
    }

    int choice = 0;
    while (choice != 8) {
        printMenu();
        cout << "Enter your choice (1-8): ";
        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Invalid input. Please enter a number." << endl;
            continue;
        }
        cin.ignore(10000, '\n');

        if (choice == 1) {
            addTask(taskList);
        } else if (choice == 2) {
            displayTasks(taskList);
        } else if (choice == 3) {
            removeTask(taskList);
        } else if (choice == 4) {
            int sortDir = 1;
            cout << "1. Sort A to Z" << endl;
            cout << "2. Sort Z to A" << endl;
            cout << "Select direction: ";
            cin >> sortDir;
            cin.ignore(10000, '\n');
            customSortAlphabetical(taskList, (sortDir == 2));
            cout << "Tasks sorted alphabetically!" << endl;
        } else if (choice == 5) {
            customSortByPriority(taskList);
            cout << "Tasks sorted by priority!" << endl;
        } else if (choice == 6) {
            resetTaskList(taskList);
        } else if (choice == 7) {
            saveToFile(taskList, fileName);
        } else if (choice == 8) {
            cout << "Saving tasks before exiting..." << endl;
            saveToFile(taskList, fileName);
            cout << "Goodbye!" << endl;
        } else {
            cout << "Invalid option. Please choose between 1 and 8." << endl;
        }
    }

}

// gets the current date and time
string getCurrentDateTime() {
    time_t now = time(nullptr);
    char buf[80];
    strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M", localtime(&now));
    return string(buf);
}

void printMenu() {
    cout << "________________ MENU _______________" << endl;
    cout << "1. Add Task" << endl;
    cout << "2. Read / View Tasks" << endl;
    cout << "3. Remove Task" << endl;
    cout << "4. Sort Alphabetically (A-Z / Z-A)" << endl;
    cout << "5. Sort by Priority" << endl;
    cout << "6. Completely Reset List" << endl;
    cout << "7. Save to File" << endl;
    cout << "8. Exit Program" << endl;
    cout << "________________________________________" << endl;;
}

bool isPriorityTaken(const vector<Task>& taskList, int priority) {
    for (const auto& task : taskList) {
        if (task.priority == priority) {
            return true;
        }
    }
    return false;
}

void addTask(vector<Task>& taskList) {
    Task newTask;
    cout << "Enter task description: ";
    getline(cin, newTask.description);

    int prio = 0;
    while (true) {
        cout << "Enter priority (unique positive integer, #1 is highest): ";
        if (cin >> prio && prio > 0) {
            if (isPriorityTaken(taskList, prio)) {
                cout << "Priority #" << prio << " is already assigned. Pick a different number." << endl;
            } else {
                newTask.priority = prio;
                break;
            }
        } else {
            cout << "Invalid priority. Enter a positive integer." << endl;
            cin.clear();
            cin.ignore(10000, '\n');
        }
    }
    cin.ignore(10000, '\n');

    newTask.dateAdded = getCurrentDateTime();
    taskList.push_back(newTask);
    cout << "Task successfully added!" << endl;
}

void displayTasks(const vector<Task>& taskList) {
    if (taskList.empty()) {
        cout << "Your TODO list is currently empty." << endl;
        return;
    }

    cout << "________________ CURRENT TODO LIST ________________" << endl;
    for (size_t i = 0; i < taskList.size(); ++i) {
        cout << (i + 1) << ". [Priority #" << taskList[i].priority << "] "
             << taskList[i].description
             << " (Added: " << taskList[i].dateAdded << ")" << endl;
    }
    cout << "===================================================" << endl;
}

//removes the task apon request
void removeTask(vector<Task>& taskList) {
    if (taskList.empty()) {
        cout << "List is empty. Nothing to remove." << endl;
        return;
    }

    displayTasks(taskList);
    int index = 0;
    cout << "Enter the number of the task to remove: ";
    if (cin >> index && index >= 1 && static_cast<size_t>(index) <= taskList.size()) {
        taskList.erase(taskList.begin() + (index - 1));
        cout << "Task removed successfully." << endl;
    } else {
        cout << "Invalid index entered." << endl;
        cin.clear();
    }
    cin.ignore(10000, '\n');
}

//sort for alphebetical order
void customSortAlphabetical(vector<Task>& taskList, bool reverse) {
    size_t n = taskList.size();
    for (size_t i = 0; i < n; ++i) {
        for (size_t j = 0; j + 1 < n - i; ++j) {
            bool condition = reverse ? (taskList[j].description < taskList[j + 1].description)
                                     : (taskList[j].description > taskList[j + 1].description);
            if (condition) {
                Task temp = taskList[j];
                taskList[j] = taskList[j + 1];
                taskList[j + 1] = temp;
            }
        }
    }
}

//bubble sort for prioraty list(niche)
void customSortByPriority(vector<Task>& taskList) {
    size_t n = taskList.size();
    for (size_t i = 0; i < n; ++i) {
        for (size_t j = 0; j + 1 < n - i; ++j) {
            if (taskList[j].priority > taskList[j + 1].priority) {
                Task temp = taskList[j];
                taskList[j] = taskList[j + 1];
                taskList[j + 1] = temp;
            }
        }
    }
}

//clear the task list if new todo list is asked for
void resetTaskList(vector<Task>& taskList) {
    taskList.clear();
    cout << "List cleared!" << endl;

    int initialCount = 0;
    cout << "How many entries would you like to start your new list with? " << endl;
    cin >> initialCount;
    cin.ignore(10000, '\n');

    for (int i = 0; i < initialCount; ++i) {
        cout << "Adding new task #" << (i + 1) << ":" << endl;
        addTask(taskList);
    }
}

//save to txt file
void saveToFile(const vector<Task>& taskList, const string& fileName) {
    ofstream outFile(fileName);
    if (!outFile) {
        cerr << "Error opening file for writing." << endl;
        return;
    }

    for (const auto& task : taskList) {
        outFile << task.priority << "|" << task.dateAdded << "|" << task.description << endl;
    }

    outFile.close();
    cout << "Successfully saved tasks to " << fileName << endl;
}

//Load list from a txt file
void loadFromFile(vector<Task>& taskList, const string& fileName) {
    ifstream inFile(fileName);
    if (!inFile) {
        return;
    }

    taskList.clear();
    string line;
    while (getline(inFile, line)) {
        if (line.empty()) continue;

        size_t pos1 = line.find('|');
        size_t pos2 = line.find('|', pos1 + 1);

        if (pos1 != string::npos && pos2 != string::npos) {
            Task task;
            task.priority = stoi(line.substr(0, pos1));
            task.dateAdded = line.substr(pos1 + 1, pos2 - pos1 - 1);
            task.description = line.substr(pos2 + 1);
            taskList.push_back(task);
        }
    }


    inFile.close();
    if (!taskList.empty()) {
        cout << "Loaded " << taskList.size() << " task(s) from " << fileName << endl;
    }
}
