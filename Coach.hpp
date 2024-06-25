#include <vector>
#include <string>
#include <sstream>
#include <fstream>
#include "PlanLinkedList.hpp"
#include "HeapQueue.hpp"
#include "json.hpp"




class Coach {
public:

    Coach(const std::string& d, const std::vector<std::string>& m, const std::string& l) {
        user_profile.difficulty = d;
        user_profile.muscles = m;
        user_profile.location = l;
        buildExerciseMap();
        buildPlan();

    };

    
    void printTopExercises();
    void addExerciseToPlan();
    void clearAll(const std::string& d, const std::vector<std::string>& m, const std::string& l);
    void printPlan();
    void removeExerciseFromPlan();
private:
    UserProfile user_profile;
    PlanLL* plan = new PlanLL();
    std::unordered_map<std::string, Exercise*> exercises_map;
    HeapQueue<Exercise*, Exercise::Compare> exercise_queue;
    std::vector<Exercise*> top_exercises;

    bool buildExerciseMap();
    void buildPlan();

};

bool Coach::buildExerciseMap() {
    std::string filename = "exercises.json"; 

    // Open the JSON file for reading
    std::ifstream file_stream(filename);

    if (!file_stream.is_open()) {
        std::cerr << "Error: Could not open file '" << filename << "'" << std::endl;
        return false; // Exit with an error code
    }

    // Read the entire file content into a string
    std::string json_data;
    std::string line;
    while (std::getline(file_stream, line)) {
        json_data += line;
    }

    file_stream.close(); // Close the file stream


    // Parse the JSON string using nlohmann/json
    nlohmann::json json_array;
    try {
        json_array = nlohmann::json::parse(json_data);
    } catch (const nlohmann::json::parse_error& e) {
        std::cerr << "Error parsing JSON: " << e.what() << std::endl;
        return false; // Exit with an error code
    }

    // Iterate through each exercise object in the JSON array
    for (const auto& exercise_json : json_array) {
        std::string id = exercise_json["ID"];
        std::string name = exercise_json["Name of exercise"];
        std::vector<std::string> muscles;

        // Extract target muscles (assuming it's an array)
        for (const auto& muscle_json : exercise_json["Target muscles"]) {
            muscles.push_back(muscle_json);
        }

        std::string difficulty = exercise_json["Difficulty"];
        std::string location = exercise_json["Location"];

        Exercise* exercise = new Exercise(id, name, muscles, difficulty, location);
        exercise->calculate_priority(user_profile); 
        exercises_map[id] = exercise;
    }
    return true; // Success
}

void Coach::buildPlan() {
    cout<<"We are getting your best fit exercises!"<<endl;
    for (auto& exercise : exercises_map) {
        if (exercise.second->location == user_profile.location) {
            exercise_queue.insert(exercise.second);
        }
    }

    for (int i = 0; i < 5; i++) {
        top_exercises.push_back(exercise_queue.min());
        exercise_queue.removeMin();
    }
    cout<<"Matching done! Choose \"a\" from the menu below to see your personalized exercises."<<endl;
}

void Coach::printTopExercises() {
    for (auto& exercise : top_exercises) {
        exercise->printInfo();
    }
}

void Coach::addExerciseToPlan() {
    std::string id;
    std::cout << "Enter the ID of the exercise you want to add: ";
    std::cin >> id;

    if (exercises_map.find(id) != exercises_map.end()) {
        if (plan->isInList(id)) {
            std::cout << "Exercise already in plan." << std::endl;
            return;
        }
        plan->insert(exercises_map[id]);
        std::cout << "Exercise "<<id<<" added to plan" << std::endl;
    } else {
        std::cout << "Exercise not found" << std::endl;
    }
}

void Coach::printPlan() {
    plan->printPlan();
}

void Coach::removeExerciseFromPlan() {
    std::string id;
    std::cout << "Enter the ID of the exercise you want to remove: ";
    std::cin >> id;

    if (exercises_map.find(id) != exercises_map.end()) {
        std::string deleted_id = plan->deleteNode(id);
        if (deleted_id == "-1") {
            std::cout << "Exercise not found in plan." << std::endl;
            return;
        }
        std::cout << "Exercise "<<deleted_id<<" removed from plan" << std::endl;
    } else {
        std::cout << "Exercise not found" << std::endl;
    }
}


void Coach::clearAll(const std::string& d, const std::vector<std::string>& m, const std::string& l) {
    while(!exercise_queue.empty()){
        exercise_queue.removeMin();
    }
    top_exercises.clear();

    user_profile.difficulty = d;
    user_profile.muscles = m;
    user_profile.location = l;
    for (const auto& pair : exercises_map){
        pair.second->calculate_priority(user_profile);
    }
    buildPlan();
}