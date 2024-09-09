//
// Created by Morra on 07.09.2024.
//
#include "dev_opt.h"
#include "gam_opt.h"
#include "user_interfaces.h"
#include <iostream>

using namespace std;

template <typename T>
void print (const T& word) {
    cout << word << endl;
}

void main_menu(){
    int choice;
    do {
        cout << endl;
        print("    MorrS");
        print("Select User: ");
        print("1. Developer");
        print("2. Gamer");
        print("0. Exit");
        cout << "You're Choice: ";
        cin >> choice;
        switch (choice) {
            case 1:
                print("Selected User: Developer");
                developer_menu();
                break;
            case 2:
                print("Selected User: Gamer");
                gamer_menu();
                break;
            case 0:
                print("Exiting...");
                break;
            default:
                print("wtf lol");
                break;
        }
    }while (choice != 0);
}

void developer_menu(){
    print ("Select Option: ");
    print ("1. Add game");
    print ("2. List games");
    print ("3. Select game");
    print ("0. Exit to main menu");
    cout << "You're Choice: ";
    int choice;
    cin >> choice;
    switch (choice) {
        case 1:
            print ("");
            createGame();
            break;
        case 2:
            print ("Games:");
            readGames();
            break;
        case 3:
            findGameDev();
            break;
        case 0:
            print ("Exiting...");
            break;
        default:
            print("wtf lol");
            break;
    }
}

void gamer_menu(){
    print ("Select Option: ");
    print ("1. Add game to library");
    print ("2. Games in library");
    print ("3. Select game");
    print ("0. Exit to main menu");
    cout << "You're Choice: ";
    int choice;
    cin >> choice;
    switch (choice) {
        case 1:
            print ("Buy game:");
            buy_game();
            break;
        case 2:
            read_library();
            break;
        case 3:
            findGameGam();
            break;
        case 0:
            print ("Exiting...");
            break;
        default:
            print("wtf lol");
            break;
    }
}