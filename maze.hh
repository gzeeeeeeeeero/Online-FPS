#pragma once

#include <vector>
#include <stack>
#include <random>

#include "core.hh"
#include "config.hh"

using std::stack;
using std::vector;
using std::pair;
using std::random_device;
using std::mt19937;
using std::uniform_int_distribution;

constexpr auto row = mw;
constexpr auto col = mh;

constexpr uint16_t empty    = 0;
constexpr uint16_t boundary = 1;
constexpr uint16_t shut     = 2;
constexpr uint16_t esc      = 3;

void    genMaze       (vector<vector<int>>&);
void    printM        (vector<vector<int>>&);
void    initMez       (vector<vector<int>>&);

void initMez(vector<vector<int>>& maze){
    for(auto i = 0; i < row; i++)
        for(auto ii = 0; ii < col; ii++)
            maze[i].push_back(!i ||i ==row-1?1
                             :!ii||ii==col-1?1
                             :shut);

    maze[1][1]         = empty;
    maze[row-2][col-2] = esc;
}
void printM (vector<vector<int>>& maze){
    for(auto &i : maze){
            for(auto ii : i)
                cout << ii << " ";
            cout << "\n";
    }
}

#define     X        active.first
#define     Y        active.second
#define  left(step)  maze[X][Y-step]
#define right(step)  maze[X][Y+step]
#define    up(step)  maze[X-step][Y]
#define  down(step)  maze[X+step][Y]
#define     current  maze[X][Y]

void genMaze  (vector<vector<int>>& maze)
{
    using coord = pair<int, int>;  random_device rd;
          coord   active(1, 1);    mt19937 gen(rd());
    stack<coord>  moves;           uniform_int_distribution<> r(1, 4);

    auto nahDeadEnd = [&]{
        moves.pop();
        active = (coord (moves.top().first, moves.top().second));
    };

    int  total   = row*col;
    int  visit   = 0;
    bool resFlag = false;
    
    #define nahDeadEnd  nahDeadEnd();
    #define action(where, expression) \
                   if(where(1) == empty || where(1) == shut){ \
                       if(where(2) == shut){\
                           where(1) = empty;\
                           where(2)  = empty;\
                           expression;\
                           visit++;\
                           moves.push(active);\
                           continue; \
                       }\
                       else if(where(2) == esc){ \
                           where(1) = empty; \
                           visit++; \
                           nahDeadEnd \
                           continue; \
                       } \
                   } \
                   if(!resFlag){ \
                       resFlag = true; \
                       goto start; \
                   }

    while(visit != total){
        auto dir = r(gen);
        resFlag  = false;
        switch(dir){
          start:  
            case 1:
                action(left, Y-=2);
            case 2:
                action(right,Y+=2);
            case 3:
                action(up,   X-=2);
            case 4:
                action(down, X+=2);
            default:
                resFlag = false;
                nahDeadEnd;
        }
    }   
}
#undef X
#undef Y