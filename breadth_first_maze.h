#pragma once
#include "maze.h"

using namespace std;

class breadth_first_maze : public maze_solver{
private:
    /**
	*stores wether a solution to the maze has been found
	*/
	bool found_path = false;

	/**
	*internal class defining a joint
	*/
	class joint
	{
	private:
		/**
		*pointer to the joint, from which you can get to this one (if nullptr => starting joint)
		*/
		joint* origin = nullptr;

		/**
		*position in map
		*/
		int positon; 

	public:
		joint(joint* orig, int pos) {
			this->origin = orig;
			this->positon = pos;
		}
		int getpos() {
			return this->positon;
		}
		joint* getorig() {
			return this->origin;
		}

	};

	vector<joint*> joints; //storage for explored points (joints)
	queue<joint*> joint_buffer; //buffer for processing joints


	int internal_stamp(joint* joint); //recursive internal method for stamping
	void clear_queue(queue<joint*>& q); //internal method for clearing joint_buffer

public:
	/**
	*constructor for reading from file 
	*@param input_path -> Location of file for input
	*/
    breadth_first_maze(string input_path, bool debug = false);

	/**
	* constructor for generating a maze
	*@param x_size -> x size of maze
	*@param y_size -> y size of maze
	*@param start_x -> x position of starting point
	*@param start_y -> y position of starting point
	*@param end_x -> x position of ending point
	*@param end_y -> y position of ending point
	*/
	breadth_first_maze(int x_size, int y_size, int start_x, int start_y, int end_x, int end_y, bool debug = false);

    ~breadth_first_maze();

	/**
	*filling map for use of Breadth-first search algorithm
	*/
	bool maze_fill() override;

	/**
	*solves the maze by using a Breadth-first search algorithm
	*should only be called after maze_fill was called
	*/
	int solve() override;

	/**
	*stamps the solution to map_out (if there is any)
	*should only be called after solve was found (will not do anything if no solution to stamp)
	*/
	int stamp();
};