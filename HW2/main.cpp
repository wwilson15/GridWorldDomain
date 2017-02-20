//
//  main.cpp
//  HW2
//
//  Created by Wade Wilson on 2/16/17.
//  Copyright © 2017 Wade Wilson. All rights reserved.
//

#include <iostream>
#include <vector>
#include <assert.h>
#include <stdio.h>
#include <fstream>

using namespace::std;

class square{
public:
    int x;
    int y;
    int goalx;
    int goaly;
};

class agent{
public:
    int xpos = 0;
    int ypos = 0;
    double areward;
    int input;
    bool win = false;
    
    void move(vector<square>* pboard);
    void eval(vector<square>* pboard);
};

void agent::move(vector<square>* pboard){ // will accept movement commands, cannot deal with edges yet.
    if( input == 0 && ypos != pboard->back().y){
        ypos ++;
    }
    else if(input == 0 && ypos == pboard->back().y){
         cout << "Cannot move up, at the top of the board" << endl;
    }
    if(input ==1 && ypos != pboard->front().y){
        ypos --;
    }
    else if(input == 1 && ypos == pboard->front().y){
        cout << "Cannot move down, at the bottom of the board" << endl;
    }
    if(input == 2 && ypos != pboard->front().x){
        xpos -- ;
    }
    else if(input == 2 && xpos == pboard->front().x){
        cout << "Cannot move left, at the left of the board" << endl;
    }
    if(input == 3 && ypos != pboard->back().x){
        xpos ++;
    }
    else if(input == 3 && xpos == pboard->back().x){
        cout << "Cannot move right, at the right of the board" << endl;
    }
    /*else{
        cout << "Incorrect input specified" << endl;
    }*/
}

void agent::eval(vector<square>* pboard){
    bool xwin =false;
    bool ywin = false;
    if(xpos == pboard->at(0).goalx){
        xwin = true;
    }
    if (ypos == pboard->at(0).goaly){
        ywin = true;
    }
    if(xwin && ywin){
        win = true;
    }
}

void createboard(vector<square>* pboard, int x, int y){
    square tsq;
    tsq.goalx=3;//rand()%x;
    tsq.goaly=4;//rand()%y;
    for(int i=0; i<x; i++){
        for( int j=0; j<y; j++){
            tsq.x=i;
            tsq.y=j;
            pboard->push_back(tsq);
        }
    }
}

int inputchoice(){ //user input choice
    int input;
    cout << "Up(0), down(1), left(2) or right(3)?\n>";
    cin >> input;
    return input;
}

int main(){
    cout << "main start" << endl;
    srand(time(NULL));
    int x=10;
    int y=10;
    vector<square> board;
    vector<square>* pboard = &board;
    agent robot;
    //agent *probot = &robot;  // need a pointer to the robot?
    createboard(pboard, x, y);
    bool notwinner = true;
    cout << "before while loop" << endl;
    while(notwinner != robot.win){
        robot.eval(pboard);
        int choice = inputchoice();
        robot.input=choice;
        robot.move(pboard);
        robot.eval(pboard);
        cout << " Goal coords are  " << pboard->at(0).goalx << ", " << pboard->at(0).goaly << endl;
        cout << "Agent is at  " << robot.xpos << ", " << robot.ypos << endl;
    }
    cout << "Winner" << endl;
}
