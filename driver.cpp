#include <iostream>
#include <fstream>
#include "json.hpp"
#include <string>
#include <sstream>
#include "helper.cpp"
#include "Coach.hpp"

using namespace std;

int main() {
    string location;
    string difficulty;
    vector<string> muscles;

    getLocation(location);
    getDifficulty(difficulty);
    getMuscles(muscles);
    // cout<<"Your target muscles are: "<<endl;
    // for (string muscle : muscles){
    //     cout<<muscle<<endl;
    // }
    
    Coach coach(difficulty, muscles, location);
    while (true){
        cout<<"------------------------------------------------"<<endl;
        printMenu();
        string choice;
        cin>>choice;
        if(choice == "a"){
            coach.printTopExercises();
        } else if(choice == "b"){
            coach.addExerciseToPlan();
        } else if(choice == "c"){
            coach.printPlan();
        } else if(choice == "d"){
            coach.removeExerciseFromPlan();
        } else if(choice == "e"){
            clearLocation(location);
            clearDifficulty(difficulty);
            clearMuscles(muscles);
            getLocation(location);
            getDifficulty(difficulty);
            getMuscles(muscles);
            coach.clearAll(difficulty, muscles, location);
        } else if(choice == "q"){
            break;
        } else {
            cout<<"Invalid choice"<<endl;
        }
       
    }
    

}
