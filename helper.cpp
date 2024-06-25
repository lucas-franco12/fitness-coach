#include <iostream>
#include <fstream>
#include <string>
#include <sstream>


using namespace std;

void printMenu(){
    cout<<"Type a, b, c, d to do the following or type q to quit the program:"<<endl;
    cout<<"a. See your top 5 recommended exercises"<<endl;
    cout<<"b. Add a exercise to your plan"<<endl;
    cout<<"c. See your current plan"<<endl;
    cout<<"d. Remove an exercise from your plan"<<endl;
    cout<<"e. Change preferences"<<endl;
    cout<<"q. Quit"<<endl;
}

void getLocation(string& location){
    string selection;
    cout<<"Where do you want to do the exercise?"<<endl;
    cout<<"a: At Home\nb: At the Gym\nSelection: ";
    cin>>selection;
    while(selection != "a" && selection != "b"){
        cout<<"Invalid selection. Please type \"a\" (for at home workouts) or \"b\" (for gym workouts): ";
        cin>>selection;
    }
    if (selection == "a"){
        location = "At Home";
    } else if (selection == "b"){
        location = "Gym";
    }
}

void getMuscles(std::vector<std::string>& muscles_arr){
    std::string muscles;
    // char muscle;
    
    cout<<"What muscles are you looking to work out?"<<endl;
    cout<<"a: Arms\nb: Back\nc: Chest\nl: Legs\ns: Shoulders\nf: Full Body\nType each separated by a space: "<<endl;
    cin.ignore (std::numeric_limits<std::streamsize>::max(), '\n'); 
    std::getline(std::cin, muscles);
    for (char muscle : muscles){
        while(muscle != 'a' && muscle != 'b' && muscle != 'c' && muscle != 'l' && muscle != 's' && muscle != 'f' && muscle != ' '){
            cout<<"\""<<muscle<<"\" is an invalid character. Please enter a valid option to take its place: ";
            cin>>muscle;
        }
        if (muscle == 'a'){
            muscles_arr.push_back("Arms");
        } else if (muscle == 'b'){
            muscles_arr.push_back("Back");
        } else if (muscle == 'c'){
            muscles_arr.push_back("Chest");
        } else if (muscle == 'l'){
            muscles_arr.push_back("Legs");
        } else if (muscle == 's'){
            muscles_arr.push_back("Shoulders");
        } else if (muscle == 'f'){
            muscles_arr.push_back("Full Body");
        }
    }
}

void getDifficulty(string& difficulty){
    string selection;
    cout<<"What difficulty level are you looking for?"<<endl;
    cout<<"a: Beginner\nb: Intermediate\nc: Advanced\nSelection: ";
    cin>>selection;
    while(selection != "a" && selection != "b" && selection != "c"){
        cout<<"Invalid selection. Please type \"a\" (for beginner), \"b\" (for intermediate), or \"c\" (for advanced): ";
        cin>>selection;
    }
    if (selection == "a"){
        difficulty = "Beginner";
    } else if (selection == "b"){
        difficulty = "Intermediate";
    } else if (selection == "c"){
        difficulty = "Advanced";
    }
}

void clearMuscles(std::vector<std::string>& muscles_arr){
    muscles_arr.clear();
}

void clearDifficulty(string& difficulty){
    difficulty = "";
}

void clearLocation(string& location){
    location = "";
}