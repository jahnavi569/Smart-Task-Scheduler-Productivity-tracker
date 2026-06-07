
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

