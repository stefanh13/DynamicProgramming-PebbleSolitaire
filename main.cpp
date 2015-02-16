//
//  main.cpp
//  PebbleSolitarie
//
//  Created by Stefán Hafsteinsson on 08/12/14.
//  Copyright (c) 2014 Stefán Hafsteinsson. All rights reserved.
//

#include <algorithm>
#include <bitset>
#include <cassert>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <list>
#include <map>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <utility>
#include <vector>
using namespace std;
bool arr[23];
int mem[0x7FFFFF];

bool canMoveLeft(int i, int mask)
{
    if(i < 2)
    {
        return false;
    }
    
    if(((mask >> (22 - i + 1)) & 1) && !((mask >> (22 - i + 2)) & 1))
    {
        return true;
    }
    
    return false;
    
}

bool canMoveRight(int i, int mask)
{
    if(i > 20)
    {
        return false;
    }
    
    if(((mask >> (22 - i - 1)) & 1) && !((mask >> (22 - i - 2)) & 1))
    {
        return true;
    }
    
    return false;
}

int moveRight(int i, int mask)
{
    mask = mask ^ (1 << (22 - i));
    mask = mask ^ (1 << (22 - i - 1));
    mask = mask | (1 << (22 - i - 2));
    
    return mask;
    
}

int moveLeft(int i, int mask)
{
    mask = mask ^ (1 << (22 - i));
    mask = mask ^ (1 << (22 - i + 1));
    mask = mask | (1 << (22 - i + 2));
    
    return mask;
}

int maximum(int a, int b, int c)
{
    int max = a;
    
    if(b > max)
    {
        max = b;
    }
    if(c > max)
    {
        max = c;
    }
    
    return max;
}
/*
 * A function that returns maximum moves for this board.
 */
int playGame(int mask)
{
    //If board is empty or full.
    if(mask == 0 || mask == 0x7FFFFF)
    {
        return 0;
    }
    
    //Check if we have seen this board before.
    if(mem[mask] != -1)
    {
        return mem[mask];
    }
    
    int a = 0, b = 0;
    
    //Iteratie through every piece of the board.
    for(int i = 0; i < 23; i++)
    {
        //If piece is 'o'.
        if((mask >> (22 - i)) & 1)
        {
            if(canMoveRight(i, mask))
            {
                //Get the board after the right move.
                int temp = moveRight(i, mask);
                a = max(a, 1 + playGame(temp));
            }
            
            if(canMoveLeft(i, mask))
            {
                //Get the board for the right move.
                int temp = moveLeft(i, mask);
                b = max(b, 1 + playGame(temp));
            }
            
            
        }
    }
    
    if(a > b)
    {
        mem[mask] = a;
    }
    else
    {
        mem[mask] = b;
    }

    
    
    return max(a, b);
}



int main(int argc, const char * argv[]) {
    
    int ts, mask;
    string input;
    
    
    scanf("%d", &ts);

    for(int t = 0; t < ts; t++)
    {
        cin >> input;
        
        int countPebbles = 0;
        mask = 0;
        for(int i = 0; i < 23; i++)
        {
            if(input[i] == 'o')
            {
                mask = mask | 1 << (22 - i);
                countPebbles++;
            }
            
            
        }
        
    
        memset(mem, -1, sizeof(mem));
        
        int moves = playGame(mask);
        
        cout << countPebbles - moves<< endl;
    }
    
    return 0;
}
