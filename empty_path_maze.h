#pragma once
#include "maze.h"

using namespace std;

class empty_path_maze : public maze_solver{
private:
    /**
    *checks proximity and if the specified point is a blind end, recursively goes to next intersection
    *should be private
    */
    int proximity(int x, int y);
public:
	/**
	*constructor for reading from file 
    *@param input_path -> Location of file for input
	*/
    empty_path_maze(string input_path, bool debug = false);

    /**
    *constructor for generating a maze
    *@param x_size -> x size of maze
	*@param y_size -> y size of maze
	*@param start_x -> x position of starting point
	*@param start_y -> y position of starting point
	*@param end_x -> x position of ending point
	*@param end_y -> y position of ending point
    */
    empty_path_maze(int x_size, int y_size, int start_x, int start_y, int end_x, int end_y, bool debug = false);
    /**
    *filling map for use of empty path algorithm
    *should only be called if maze was read from file
    */
    bool maze_fill() override;

    /**
    *solves the maze by empty path algorithm
    *should only be called after maze_fill_ep() has been called
    */
    int solve() override;


};