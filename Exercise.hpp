#include <vector>
#include <string>
#include <sstream>
#include <iostream> // for printing

struct UserProfile {
    std::string difficulty;
    std::string location;
    std::vector<std::string> muscles;
};

class Exercise {
private:
    std::string name;         // Exercise name
    std::vector<std::string> muscles; // Target muscles
    std::string difficulty;   // Exercise difficulty (e.g., easy, medium, hard)
    int priority = 0;
    std::unordered_map<std::string, int> difficulty_map = {{"Beginner", 1}, {"Intermediate", 2}, {"Advanced", 3}};
public:
    std::string ID;  
    std::string location;     // Exercise location (e.g., at home, gym)

    // Constructor
    // Exercise(const std::string& id, const std::string& n, const std::vector<std::string>& m, const std::string& d, const std::string& l)
    //     : ID(id), name(n), muscles(m), difficulty(d), location(l) {};

    Exercise(const std::string& id, const std::string& n, const std::vector<std::string>& m, const std::string& d, const std::string& l)
    : name(n), muscles(m), difficulty(d), priority(0), difficulty_map({{"Beginner", 1}, {"Intermediate", 2}, {"Advanced", 3}}), ID(id), location(l) {};


    // Function to print exercise information in a user-friendly format
    void calculate_priority (const UserProfile& profile) {
        priority = 0;
        int difficulty_exercise = difficulty_map[difficulty];
        int difficulty_user = difficulty_map[profile.difficulty];
        int difference = abs(difficulty_exercise - difficulty_user);
        if (difference == 0) {
            priority += 2;
        } else if (difference == 1) {
            priority += 1;
        } else {
            priority += 0;
        }
        // cout<<"User Profile Muscles: "<<endl;
        // for (const std::string& muscle : profile.muscles) {
        //     cout<<muscle<<endl;
        // }

        for (const std::string& muscle : muscles) {
            if (std::find(profile.muscles.begin(), profile.muscles.end(), muscle) != profile.muscles.end()) {
                priority += 2;
            }
            else if (std::find(profile.muscles.begin(), profile.muscles.end(), "Full Body") != profile.muscles.end()) {
                priority += 1;
            }
        }
        priority *= -1;
    }
    void printInfo() const {
        std::cout << "ID: " << ID << std::endl;
        std::cout << "Name: " << name << std::endl;
        std::cout << "Target Muscles: ";
        if (muscles.empty()) {
            std::cout << "None" << std::endl; // Handle case with no muscles listed
        } else {
            for (const std::string& muscle : muscles) {
                if (&muscle == &muscles.back()) {
                    std::cout << muscle << std::endl; // Print without comma and space for the last muscle
                } else {
                    std::cout << muscle << ", ";
                }
            }
        }
        std::cout << "Difficulty: " << difficulty << std::endl;
        std::cout << "Location: " << location << std::endl;
        //std::cout << "Priority: " << priority << std::endl;
        std::cout << std::endl; 
    }
    class Compare {
        public:
            Compare(bool lessThan = true) : lessThan(lessThan) {};
            bool operator()(const Exercise &n1, const Exercise &n2) const;
            bool operator()(const Exercise *n1, const Exercise *n2) const;
        private:
            bool lessThan;
    };


};

bool Exercise::Compare::operator()(const Exercise &n1, const Exercise &n2) const {
    if (lessThan) {
        return n1.priority < n2.priority;
    } else {
        return n1.priority > n2.priority;
    }
}

bool Exercise::Compare::operator()(const Exercise *n1, const Exercise *n2) const {
    if (lessThan) {
        return n1->priority < n2->priority;
    } else {
        return n1->priority > n2->priority;
    }
}


