#include <iostream>

#include <string>
#include <iomanip>
#include <vector>
#include <map>

using namespace std;

// ANSI color codes
const string RESET = "\033[0m";
const string RED = "\033[31m";
const string GREEN = "\033[32m";
const string YELLOW = "\033[33m";
const string BLUE = "\033[34m";
const string MAGENTA = "\033[35m";
const string CYAN = "\033[36m";


struct Workout {
    string name;
    string date; 
    int duration; 
    bool completed; 
    string category; 
};

// Class to manage workouts
class WorkoutTracker {
private:
    vector<Workout> workouts; // Store workouts in a vector
    map<string, int> workoutStats; // Store statistics

public:
    // Add workout to the tracker
    void addWorkout(const Workout& workout) {
        workouts.push_back(workout);
        workoutStats["total"]++;
        workoutStats["duration"] += workout.duration;
        if (workout.completed) {
            workoutStats["completed"]++;
        }
    }

    // Update statistics when a workout is completed
    void updateStats(const Workout& workout) {
        if (workout.completed) {
            workoutStats["completed"]++;
        }
    }

    // Display today's workouts by date
    void displayWorkoutsByDate(const string& date) {
        cout << "\n*Today's Workout:*\n";
        cout << "| Workout Name | Duration (mins) | Status | Category |\n";
        cout << "|---|---|---|---|\n";

        bool found = false;
        for (const auto& workout : workouts) {
            string color;
            if (workout.category == "Cardio") color = GREEN;
            else if (workout.category == "Strength") color = BLUE;
            else if (workout.category == "Flexibility") color = YELLOW;
            else if (workout.category == "HIIT") color = RED;
            else color = RESET; // Default color

            if (workout.date == date) {
                cout << "| " << setw(12) << workout.name
                     << " | " << setw(15) << workout.duration
                     << " | " << (workout.completed ? "Completed ✅" : "Paused ⏸️")
                     << " | " << color << workout.category << RESET << " |\n";
                found = true;
            }
        }
        if (!found) {
            cout << "No workouts found on this date.\n";
        }
    }

    // Start workout routine
    void startWorkoutRoutine(const string& date) {
        bool found = false;

        for (auto& workout : workouts) {
            if (workout.date == date && !workout.completed) {
                found = true;
                char option;
                cout << "Starting workout: " << workout.name << " (" << workout.duration << " mins)" << endl;
                cout << "Press 'y' to mark this workout as completed, or 'n' to pause the workout." << endl;

                while (true) {
                    cin >> option;
                    if (option == 'y') {
                        workout.completed = true; // Mark as completed
                        cout << "🎉 Great job! You've completed: " << workout.name << " 🎉" << endl;
                        updateStats(workout); // Update stats
                        break; // Move to the next workout
                    } else if (option == 'n') {
                        cout << "Workout paused." << endl;
                        return; // Exit to main menu
                    } else {
                        cout << "Invalid option. Press 'y' to complete or 'n' to pause." << endl;
                    }
                }
            }
        }
        if (!found) {
            cout << "No workouts to start on this date." << endl;
        }
    }

    // Display all workouts
    void displayAllWorkouts() {
        cout << "\n*All Workouts:*\n";
        cout << "| Date | Workout Name | Duration (mins) | Completed | Category |\n";
        cout << "|---|---|---|---|---|\n";

        for (const auto& workout : workouts) {
            string color;
            if (workout.category == "Cardio") color = GREEN;
            else if (workout.category == "Strength") color = BLUE ;
            else if (workout.category == "Flexibility") color = YELLOW;
            else if (workout.category == "HIIT") color = RED;
            else color = RESET; // Default color

            cout << "| " << setw(10) << workout.date
                 << " | " << setw(12) << workout.name
                 << " | " << setw(15) << workout.duration
                 << " | " << (workout.completed ? "Yes ✅" : "No ❌")
                 << " | " << color << workout.category << RESET << " |\n";
        }
    }

    // Display workout statistics
    void displayStatistics() {
        cout << "\n*Workout Statistics:*\n";
        cout << "Total Workouts: " << workoutStats["total"] << endl;
        cout << "Total Duration: " << workoutStats["duration"] << " mins" << endl;
        cout << "Completed Workouts: " << workoutStats["completed"] << endl;
        if (workoutStats["completed"] > 0) {
            cout << "Average Duration: " << static_cast<double>(workoutStats["duration"]) / workoutStats["completed"] << " mins" << endl;
        } else {
            cout << "Average Duration: N/A (No workouts completed)" << endl;
        }
    }

    // Function to input new workouts
    void inputNewWorkout() {
        Workout newWorkout;
        cout << "Enter workout name: ";
        cin.ignore(); // Clear the input buffer
        getline(cin, newWorkout.name);
        cout << "Enter workout date (MM-DD): ";
        cin >> newWorkout.date;
        cout << "Enter workout duration (in minutes): ";
        cin >> newWorkout.duration;
        newWorkout.completed = false; // Default to not completed

        // Category selection menu
        cout << "Select workout category:\n";
        cout << "1. Cardio\n";
        cout << "2. Strength\n";
        cout << "3. Flexibility\n";
        cout << "4. HIIT\n";
        cout << "Enter your choice (1-4): ";
        int choice;
        cin >> choice;

        switch (choice) {
            case 1: newWorkout.category = "Cardio"; break;
            case 2: newWorkout.category = "Strength"; break;
            case 3: newWorkout.category = "Flexibility"; break;
            case 4: newWorkout.category = "HIIT"; break;
            default: newWorkout.category = "Other"; break; // Default category
        }

        addWorkout(newWorkout);
        cout << "Workout added successfully!\n";
    }
};

// Main function
int main() {
    WorkoutTracker tracker;
    string date;
    char addMore;

    // Input new workouts
    do {
        tracker.inputNewWorkout();
        cout << "Do you want to add another workout? (y/n): ";
        cin >> addMore;
    } while (addMore == 'y');

    cout << "Enter today's date (MM-DD): ";
    cin >> date;

    tracker.displayWorkoutsByDate(date);
    tracker.startWorkoutRoutine(date);
    tracker.displayAllWorkouts();
    tracker.displayStatistics();

    return 0;
}
