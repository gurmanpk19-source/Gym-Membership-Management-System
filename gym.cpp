#include <iostream>
#include <vector>
#include <memory>
#include <string>
#include <limits>
#include <iomanip>

using namespace std;

// Base Class
class GymMember {
protected:
    int id;
    string name;
    int age;

public:
    // Constructor
    GymMember(int i, string n, int a)
        : id(i), name(n), age(a) {}

    int getId() const {
        return id;
    }

    virtual double calculateFee() const = 0;
    virtual string getPlan() const = 0;
    virtual int getDuration() const = 0;

    virtual void display() const {
        cout << "\nMember ID: " << id;
        cout << "\nName: " << name;
        cout << "\nAge: " << age;
        cout << "\nMembership Plan: " << getPlan();
        cout << "\nDuration: " << getDuration() << " month(s)";
        cout << "\nMembership Fee: Rs. "
             << fixed << setprecision(2) << calculateFee();
        cout << "\n-----------------------------\n";
    }

    virtual ~GymMember() = default;
};

// Monthly Membership
class MonthlyMember : public GymMember {
public:
    MonthlyMember(int i, string n, int a)
        : GymMember(i, n, a) {}

    double calculateFee() const override {
        return 1000;
    }

    string getPlan() const override {
        return "Monthly";
    }

    int getDuration() const override {
        return 1;
    }
};

// Quarterly Membership
class QuarterlyMember : public GymMember {
public:
    QuarterlyMember(int i, string n, int a)
        : GymMember(i, n, a) {}

    double calculateFee() const override {
        return 2700;
    }

    string getPlan() const override {
        return "Quarterly";
    }

    int getDuration() const override {
        return 3;
    }
};

// Yearly Membership
class YearlyMember : public GymMember {
public:
    YearlyMember(int i, string n, int a)
        : GymMember(i, n, a) {}

    double calculateFee() const override {
        return 9000;
    }

    string getPlan() const override {
        return "Yearly";
    }

    int getDuration() const override {
        return 12;
    }
};

// Gym Management System
class GymManagementSystem {
private:
    vector<unique_ptr<GymMember>> members;

public:
    void registerMember() {
        int id, age, choice;
        string name;

        cout << "\nEnter Member ID: ";

        if (!(cin >> id) || id <= 0) {
            cout << "Invalid Member ID.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return;
        }

        // Check for duplicate member ID
        for (const auto& member : members) {
            if (member->getId() == id) {
                cout << "Member ID already exists.\n";
                return;
            }
        }

        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        cout << "Enter Member Name: ";
        getline(cin, name);

        if (name.empty()) {
            cout << "Name cannot be empty.\n";
            return;
        }

        cout << "Enter Age: ";

        if (!(cin >> age) || age <= 0 || age > 120) {
            cout << "Invalid age.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return;
        }

        cout << "\nSelect Membership Plan:\n";
        cout << "1. Monthly - Rs. 1000\n";
        cout << "2. Quarterly - Rs. 2700\n";
        cout << "3. Yearly - Rs. 9000\n";
        cout << "Enter Choice: ";

        if (!(cin >> choice)) {
            cout << "Invalid choice.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return;
        }

        switch (choice) {
            case 1:
                members.push_back(
                    make_unique<MonthlyMember>(id, name, age));
                break;

            case 2:
                members.push_back(
                    make_unique<QuarterlyMember>(id, name, age));
                break;

            case 3:
                members.push_back(
                    make_unique<YearlyMember>(id, name, age));
                break;

            default:
                cout << "Invalid membership plan.\n";
                return;
        }

        cout << "\nMember Registered Successfully!\n";
        cout << "Membership Fee: Rs. "
             << fixed << setprecision(2)
             << members.back()->calculateFee() << "\n";
    }

    void displayMembers() const {
        if (members.empty()) {
            cout << "\nNo members registered yet.\n";
            return;
        }

        cout << "\n===== REGISTERED GYM MEMBERS =====\n";

        for (const auto& member : members) {
            member->display();
        }
    }

    void run() {
        int choice;

        do {
            cout << "\n===== GYM MEMBERSHIP SYSTEM =====\n";
            cout << "1. Register Member\n";
            cout << "2. Display All Members\n";
            cout << "3. Exit\n";
            cout << "Enter Your Choice: ";

            if (!(cin >> choice)) {
                cout << "Please enter a valid number.\n";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                continue;
            }

            switch (choice) {
                case 1:
                    registerMember();
                    break;

                case 2:
                    displayMembers();
                    break;

                case 3:
                    cout << "\nThank you for using Gym Membership System!\n";
                    break;

                default:
                    cout << "Invalid choice. Please try again.\n";
            }

        } while (choice != 3);
    }
};

// Main Function
int main() {
    GymManagementSystem gym;
    gym.run();

    return 0;
}