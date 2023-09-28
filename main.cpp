#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <limits>
using namespace std;

enum Priority { HIGH, MEDIUM, LOW };

struct Task {
    string description;
    bool completed;
    Priority priority;
    string dueDate;
    
};

vector<Task> tasks;

int getIndexFromUser() {
    int index;
    cin >> index;
    if (cin.fail() || index <= 0 || index > tasks.size()) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return -1;
    }
    return index;
}

string getDueDateFromUser() {
    string date;
    cout << "Enter due date (YYYY-MM-DD): ";
    cin >> date;
    return date;
}

void loadTasks() {
    ifstream inputFile("tasks.txt");
    if (inputFile.is_open()) {
        Task task;
        int priorityInt;
        while (getline(inputFile, task.description)) {
            inputFile >> task.completed >> priorityInt >> task.dueDate;
            task.priority = static_cast<Priority>(priorityInt);
            tasks.push_back(task);
            inputFile.ignore();
        }
        inputFile.close();
    }
}

void saveTasks() {

    ofstream outputFile("tasks.txt");

    for (const Task& task : tasks) {
        outputFile << task.description << '\n'
            << task.completed << ' '
            << static_cast<int>(task.priority) << ' '
            << task.dueDate << '\n';
    }
    outputFile.close();
} 



//Menu Functions

void addTask() { 

    Task newTask;
    cout << "Enter task description: ";
    cin.ignore(); // discard newline character
    getline(cin, newTask.description);
    newTask.completed = false;

    cout << "Select task priority:\n";
    cout << "0. High\n";
    cout << "1. Medium\n";
    cout << "2. Low\n";

    int priorityChoice; cin >> priorityChoice;

    switch (priorityChoice) {
    case 0:
        newTask.priority = HIGH;
        break;
    case 1:
        newTask.priority = MEDIUM;
        break;
    case 2:
        newTask.priority = LOW;
        break;
    default:
        cout << "Invalid choice. Setting priority to MEDIUM.\n";
        newTask.priority = MEDIUM;
        break;
    }

    newTask.dueDate = getDueDateFromUser();
    tasks.push_back(newTask);
    saveTasks();
}

void viewTasks() {
    if (tasks.empty()) {
        cout << "No tasks to display.\n";
    }
    else {
        for (size_t i = 0; i < tasks.size(); ++i) {
            cout << i + 1 << ". " << (tasks[i].completed ? "[Completed] " : "[Not Completed] ")
                << tasks[i].description << " (Due: " << tasks[i].dueDate
                << ", Priority: " << tasks[i].priority << ")\n";
        }
    }
}

void markTaskCompleted() {
    viewTasks();
    int index;
    cout << "Enter the number of the task to mark as completed: ";
    index = getIndexFromUser();
    if (index != -1) {
        tasks[index - 1].completed = true;
        saveTasks();
    }
    else {
        cout << "Invalid task number.\n";
    }
}

void removeTask() {
    viewTasks();
    int index;
    cout << "Enter the number of the task to remove: ";
    index = getIndexFromUser();
    if (index != -1) {
        tasks.erase(tasks.begin() + index - 1);
        saveTasks();
    }
    else {
        cout << "Invalid task number.\n";
    }
}

void searchTasks() {
    string keyword;
    cout << "Enter keyword to search: ";
    cin.ignore();
    getline(cin, keyword);
    cout << "Matching tasks:\n";
    for (const Task& task : tasks) {
        if (task.description.find(keyword) != string::npos) {
            cout << task.description << '\n';
        }
    }
}

int main() {
    loadTasks();
    int choice;
    do {
        cout << "\nMenu:\n";
        cout << "1. Add Task\n";
        cout << "2. View Tasks\n";
        cout << "3. Mark Task as Completed\n";
        cout << "4. Remove Task\n";
        cout << "5. Search Tasks\n";
        cout << "0. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        switch (choice) {
        case 1:
            addTask();
            break;
        case 2:
            viewTasks();
            break;
        case 3:
            markTaskCompleted();
            break;
        case 4:
            removeTask();
            break;
        case 5:
            searchTasks();
            break;
        case 0:
            saveTasks();
            break;
        default:
            cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 0);

    return 0;
}