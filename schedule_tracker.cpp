#include <iostream>
#include <string>
#include <list>
#include <ctime>
#include <vector>
#include <algorithm>
#include <limits> // for numeric_limits
using namespace std;

// task node structure with priority and recurrence
struct Task {
    string taskDescription;
    string priority;      // task priority (high, medium, low)
    string recurrence;    // recurrence type (none, daily, weekly, monthly)
    Task* next;

    // constructor to initialize task
    Task(string description, string prio, string recur) : taskDescription(description), priority(prio), recurrence(recur), next(nullptr) {}
};

// date node structure
struct DateNode {
    int day, month, year;        // date
    Task* tasks;                 // list of tasks for that date
    DateNode* next;              // pointer to next date node

    // constructor to initialize date node
    DateNode(int d, int m, int y) : day(d), month(m), year(y), tasks(nullptr), next(nullptr) {}
};

// function to print a date in dd/mm/yyyy format
void printDate(int day, int month, int year) {
    cout << (day < 10 ? "0" : "") << day << "/"
         << (month < 10 ? "0" : "") << month << "/"
         << year << endl;
}

// function to check if the entered date is valid
bool isValidDate(int day, int month, int year) {
    if (year < 2023 || month < 1 || month > 12 || day < 1 || day > 31) {
        return false;
    }

    // handle months with 30 days
    if ((month == 4 || month == 6 || month == 9 || month == 11) && day > 30) return false;
    
    // handle February with leap year check
    if (month == 2 && (day > 29 || (day > 28 && (year % 4 != 0 || (year % 100 == 0 && year % 400 != 0))))) return false;
    
    return true;
}

// function to compare two dates to see if the first is before the second
bool isBefore(int d1, int m1, int y1, int d2, int m2, int y2) {
    if (y1 < y2 || (y1 == y2 && m1 < m2) || (y1 == y2 && m1 == m2 && d1 < d2)) {
        return true;
    }
    return false;
}

// schedule tracker class using linked list
class ScheduleTracker {
private:
    DateNode* head;

public:
    // constructor to initialize head of the list
    ScheduleTracker() : head(nullptr) {}

    // function to add a task to a specific date
    void addTask(int day, int month, int year, const string& taskDescription, const string& priority, const string& recurrence) {
        // check if the date is valid
        if (!isValidDate(day, month, year)) {
            cout << "invalid date!" << endl;
            return;
        }

        DateNode* temp = head;

        // find the node for the specific date or create a new one if not found
        while (temp) {
            if (temp->day == day && temp->month == month && temp->year == year) {
                break;
            }
            temp = temp->next;
        }

        if (!temp) {  // create a new node if date doesn't exist
            DateNode* newNode = new DateNode(day, month, year);
            newNode->next = head;
            head = newNode;
            temp = head;
        }

        // check if there are any tasks already for this date
        Task* taskTemp = temp->tasks;
        while (taskTemp) {
            if (taskTemp->taskDescription == taskDescription) {
                cout << "warning: this task is already scheduled for this date!" << endl;
                return;
            }
            taskTemp = taskTemp->next;
        }

        // add the new task to the date node
        Task* newTask = new Task(taskDescription, priority, recurrence);
        newTask->next = temp->tasks;
        temp->tasks = newTask;
        cout << "task added to " << day << "/" << month << "/" << year << endl;
    }

    // function to display all tasks sorted by priority
    void displayAllTasks() {
        vector<Task*> allTasks;
        DateNode* temp = head;

        // collect all tasks from the linked list
        while (temp) {
            Task* taskTemp = temp->tasks;
            while (taskTemp) {
                allTasks.push_back(taskTemp);
                taskTemp = taskTemp->next;
            }
            temp = temp->next;
        }

        // sort tasks by priority (high > medium > low)
        sort(allTasks.begin(), allTasks.end(), [](Task* a, Task* b) {
            if (a->priority == "high" && b->priority != "high") return true;
            if (a->priority == "medium" && b->priority == "low") return true;
            return false;
        });

        // display sorted tasks
        for (auto& task : allTasks) {
            cout << "task: " << task->taskDescription << " | priority: " << task->priority
                 << " | recurrence: " << task->recurrence << endl;
        }
    }

    // function to display future tasks
    void displayFutureTasks(int currentDay, int currentMonth, int currentYear) {
        DateNode* temp = head;
        bool foundFutureTask = false;

        while (temp) {
            if (isBefore(currentDay, currentMonth, currentYear, temp->day, temp->month, temp->year)) {
                foundFutureTask = true;
                cout << "upcoming tasks for ";
                printDate(temp->day, temp->month, temp->year);
                Task* taskTemp = temp->tasks;
                while (taskTemp) {
                    cout << "  - " << taskTemp->taskDescription << " | priority: " << taskTemp->priority
                         << " | recurrence: " << taskTemp->recurrence << endl;
                    taskTemp = taskTemp->next;
                }
            }
            temp = temp->next;
        }

        if (!foundFutureTask) {
            cout << "no future tasks found." << endl;
        }
    }

    // destructor to free memory
    ~ScheduleTracker() {
        while (head) {
            DateNode* temp = head;
            head = head->next;

            // free tasks
            Task* taskTemp = temp->tasks;
            while (taskTemp) {
                Task* toDelete = taskTemp;
                taskTemp = taskTemp->next;
                delete toDelete;
            }

            delete temp;
        }
    }
};

int main() {
    ScheduleTracker tracker;

    // current date (for demonstration, use actual current date if necessary)
    int currentDay = 23, currentMonth = 11, currentYear = 2024;

    while (true) {
        cout << "\nSchedule Tracker Menu:\n";
        cout << "1. Add Task\n";
        cout << "2. Display All Tasks\n";
        cout << "3. Display Future Tasks\n";
        cout << "4. Exit\n";
        cout << "Choose an option: ";
        int choice;
        cin >> choice;

        if (cin.fail()) { 
            cin.clear(); 
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
            cout << "invalid input. please enter a number." << endl;
            continue;
        }

        if (choice == 1) {
            int day, month, year;
            string taskDescription, priority, recurrence;

            cout << "Enter date (day month year): ";
            cin >> day >> month >> year;

            if (cin.fail()) { 
                cin.clear(); 
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
                cout << "invalid date input." << endl;
                continue;
            }

            cin.ignore();  // to ignore the newline character left by cin
            cout << "Enter task description: ";
            getline(cin, taskDescription);
            cout << "Enter priority (high, medium, low): ";
            getline(cin, priority);
            cout << "Enter recurrence (none, daily, weekly, monthly): ";
            getline(cin, recurrence);

            tracker.addTask(day, month, year, taskDescription, priority, recurrence);
        } else if (choice == 2) {
            tracker.displayAllTasks();
        } else if (choice == 3) {
            tracker.displayFutureTasks(currentDay, currentMonth, currentYear);
        } else if (choice == 4) {
            break;
        } else {
            cout << "invalid option. please try again." << endl;
        }
    }

    return 0;
}

