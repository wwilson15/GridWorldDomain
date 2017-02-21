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
    
    int choice(vector<square>* pboard);
    void move(vector<square>* pboard);
    void eval(vector<square>* pboard);
};

void agent::move(vector<square>* pboard){ // will accept movement commands, cannot deal with edges yet.
    if(input == 0){
        if(ypos == pboard->back().y){
            cout << "Cannot move up, at the top of the board" << endl;
            ypos = pboard->back().y;
        }
        else{
            ypos++;
        }
    }
    if( input == 1){
        if(ypos == pboard->front().y){
            cout << "Cannot move down, at the bottom of the board" << endl;
            ypos = pboard->front().y;
        }
        else{
            ypos -- ;
        }
    }
    if( input == 2){
        if(xpos == pboard->front().x){
            cout << "Cannot move left, at the left of the board" << endl;
            xpos = pboard->front().x;
        }
        else{
            xpos -- ;
        }
    }
    if( input == 3){
        if(xpos == pboard->back().x){
            cout << "Cannot move right, at the right of the board" << endl;
            xpos = pboard->back().x;
        }
        else{
            xpos ++ ;
        }
    }
}

int agent::choice(vector<square>* pboard){
    int input=0;
    if(pboard->at(0).goalx > xpos){ // robot is left of goal
        input = 3;
    }
    if(pboard->at(0).goalx < xpos){ // robot is right of goal
        input = 2;
    }
    if(pboard->at(0).goaly > ypos){ // robot is below goal
        input = 0;
    }
    if(pboard->at(0).goaly < ypos){ // robot is above goal
        input = 1;
    }
    return input;
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
        tsq.x=i;
        pboard->push_back(tsq);
    }
    for( int j=0; j<y; j++){
        tsq.y=j;
        pboard->push_back(tsq);
        
    }
    cout << pboard->front().x << "\t" << pboard->back().x << endl;
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
        //int choice = inputchoice();
        robot.input=robot.choice(pboard);
        robot.move(pboard);
        robot.eval(pboard);
        cout << " Goal coords are  " << pboard->at(0).goalx << ", " << pboard->at(0).goaly << endl;
        cout << "Agent is at  " << robot.xpos << ", " << robot.ypos << endl;
    }
    cout << "Winner" << endl;
}
