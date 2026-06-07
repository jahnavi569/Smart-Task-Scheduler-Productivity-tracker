/*
========================================
SMART TASK SCHEDULER & PRODUCTIVITY TRACKER
========================================

Project Overview:
A Smart Task Scheduler and Productivity Tracker developed using C++,Object-Oriented Programming (OOP), Linked Lists, and Binary Search Trees. The application helps users manage tasks efficiently through priority-based
scheduling, productivity analytics, deadline tracking, and task categorization.

Key Features:
- Add and manage tasks
- Smart Priority Recommendation
- Priority-based task sorting using BST
- Task completion tracking
- Undo last completed task
- Productivity Dashboard
- Search tasks by tag
- Deadline alerts
- Pending and completed task management

Data Structures Used:
1 Linked List (STL List)
   - Stores active and completed tasks.
2 Binary Search Tree (BST)
   - Organizes tasks according to priority.

Technologies:
- C++
- Object-Oriented Programming
- STL (list, algorithms)
- Binary Search Trees 
*/

#include <iostream>
#include <list>
#include <string>
#include <algorithm>
using namespace std;

class Task {
public:
    int taskID;
    string taskName;
    int priority;
    string deadline;
    string tag;
    string notes;
    bool isCompleted;

    Task(int id, string name, int prio, string dl, string tg)
        : taskID(id), taskName(name), priority(prio),
          deadline(dl), tag(tg), isCompleted(false) {}

    void addNotes(const string& note) { notes = note; }
    void completeTask() { isCompleted = true; }

    void display() const {
        cout << "\nTask ID: " << taskID
             << "\nName: " << taskName
             << "\nPriority: " << priority
             << "\nDeadline: " << deadline
             << "\nCompleted: " << (isCompleted ? "Yes" : "No") << endl;

        if (!tag.empty()) cout << "Tag: " << tag << endl;
        if (!notes.empty()) cout << "Notes: " << notes << endl;
        cout << "-----------------------------\n";
    }
};

class TreeNode {
public:
    Task task;
    TreeNode* left;
    TreeNode* right;

    TreeNode(const Task& t) : task(t), left(nullptr), right(nullptr) {}
};

class TaskPriorityTree {
public:
    TreeNode* root;
    TaskPriorityTree() : root(nullptr) {}

    TreeNode* insert(TreeNode* node, const Task& t) {
        if (node == nullptr)
            return new TreeNode(t);

        if (t.priority < node->task.priority)
            node->left = insert(node->left, t);
        else
            node->right = insert(node->right, t);

        return node;
    }

    void insertTask(const Task& t) {
        root = insert(root, t);
    }

    void inorder(TreeNode* node) {
        if (!node) return;

        inorder(node->left);
        node->task.display();
        inorder(node->right);
    }

    void displayInPriorityOrder() {
        inorder(root);
    }
};

class TaskScheduler {
private:
    list<Task> tasks;
    list<Task> completedTasks;
    TaskPriorityTree priorityTree;
    int streak = 0;

public:

    void addTask(int id) {
        string name, deadline, tag, note;
        int priority;
        int daysRemaining;

        cin.ignore();

        cout << "Enter Task Name: ";
        getline(cin, name);

        cout << "Enter Deadline (YYYY-MM-DD): ";
        cin >> deadline;

        cout << "Days remaining until deadline: ";
        cin >> daysRemaining;

        if(daysRemaining <= 2)
            priority = 1;
        else if(daysRemaining <= 7)
            priority = 2;
        else if(daysRemaining <= 15)
            priority = 3;
        else if(daysRemaining <= 30)
            priority = 4;
        else
            priority = 5;

        cout << "Suggested Priority: " << priority << endl;

        cout << "Enter Tag: ";
        cin >> tag;

        cin.ignore();

        cout << "Enter Notes: ";
        getline(cin, note);

        Task newTask(id, name, priority, deadline, tag);
        newTask.addNotes(note);

        tasks.push_back(newTask);
        priorityTree.insertTask(newTask);

        cout << "\nTask Added Successfully!\n";
    }

    void completeTask(int taskID) {

        auto it = find_if(tasks.begin(), tasks.end(),
            [taskID](const Task& task) {
                return task.taskID == taskID;
            });

        if(it != tasks.end()) {

            Task task = *it;
            task.completeTask();
            completedTasks.push_back(task);
            streak++;
            tasks.erase(it);
            cout << "Task Completed Successfully!\n";
        }
        else {
            cout << "Task ID Not Found!\n";
        }
    }

    void undoLastTask() {

        if(completedTasks.empty()) {
            cout << "No Completed Tasks To Undo!\n";
            return;
        }

        Task task = completedTasks.back();
        completedTasks.pop_back();
        task.isCompleted = false;

        if(streak > 0)
            streak--;
        tasks.push_back(task);

        cout << "Undo Successful: " << task.taskName << endl;
    }

    void displayTasks() {

        if(tasks.empty()) {
            cout << "No Tasks Available!\n";
            return;
        }
        for(const auto& task : tasks)
            task.display();
    }

    void displayCompletedTasks() {

        if(completedTasks.empty()) {
            cout << "No Completed Tasks!\n";
            return;
        }
        for(const auto& task : completedTasks)
            task.display();
    }

    void displayPendingTasks() {
        bool found = false;

        for(const auto& task : tasks) {

            if(!task.isCompleted) {
                task.display();
                found = true;
            }
        }

        if(!found)
            cout << "No Pending Tasks!\n";
    }

    void displayTasksByPriority() {

        cout << "\n===== TASKS BY PRIORITY =====\n";
        priorityTree.displayInPriorityOrder();
    }

    void searchByTag(string searchTag) {
        bool found = false;

        for(const auto& task : tasks) {

            if(task.tag == searchTag) {
                task.display();
                found = true;
            }
        }
        if(!found)
            cout << "No Tasks Found With Tag: " << searchTag << endl;
    }
    void showDashboard() {

        int completed = completedTasks.size();
        int pending = tasks.size();
        int total = completed + pending;
        double productivity = 0;

        if(total > 0)
            productivity = ((double)completed / total) * 100;

        cout << "\n===== PRODUCTIVITY DASHBOARD =====\n";
        cout << "Completed Tasks : " << completed << endl;
        cout << "Pending Tasks   : " << pending << endl;
        cout << "Productivity %  : " << productivity << endl;
        cout << "Task Streak     : " << streak << endl;
    }

    void showDeadlineAlerts() {

        cout << "\n===== DEADLINE ALERTS =====\n";
        if(tasks.empty()) {
            cout << "No Active Tasks.\n";
            return;
        }

        for(const auto& task : tasks) {
            cout << task.taskName
                 << " --> "
                 << task.deadline
                 << endl;
        }
    }
};

int main() {

    TaskScheduler scheduler;
    int choice;
    int taskCount = 1;

    while(true) {

        cout << "\n===== SMART TASK SCHEDULER =====\n";
        cout << "1. Add Task\n";
        cout << "2. Complete Task\n";
        cout << "3. Undo Last Task\n";
        cout << "4. Display All Tasks\n";
        cout << "5. Display Tasks By Priority\n";
        cout << "6. Display Completed Tasks\n";
        cout << "7. Display Pending Tasks\n";
        cout << "8. Productivity Dashboard\n";
        cout << "9. Search Tasks By Tag\n";
        cout << "10. Deadline Alerts\n";
        cout << "11. Exit\n";

        cout << "Enter Choice: ";
        cin >> choice;

        switch(choice) {
            case 1:
                scheduler.addTask(taskCount++);
                break;
            case 2: {
                int id;
                cout << "Enter Task ID: ";
                cin >> id;
                scheduler.completeTask(id);
                break;
            }
            case 3:
                scheduler.undoLastTask();
                break;
            case 4:
                scheduler.displayTasks();
                break;

            case 5:
                scheduler.displayTasksByPriority();
                break;
            case 6:
                scheduler.displayCompletedTasks();
                break;
            case 7:
                scheduler.displayPendingTasks();
                break;
            case 8:
                scheduler.showDashboard();
                break;
            case 9: {
                string tag;
                cout << "Enter Tag: ";
                cin >> tag;
                scheduler.searchByTag(tag);
                break;
            }
            case 10:
                scheduler.showDeadlineAlerts();
                break;
            case 11:
                cout << "Exiting Program...\n";
                return 0;
            default:
                cout << "Invalid Choice!\n";
        }
    }
    return 0;
}
