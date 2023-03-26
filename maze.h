#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <queue>
#include <stdexcept>
#include <stdlib.h>

using namespace std;

//constants for maze format

const char m_wall = '1'; //a wall ... duh
const char m_corr = '0'; //explored not part of path
const char m_path = '4'; //explored on path
const char m_start = '2'; //starting point
const char m_end = '3'; //ending point
const char m_reserved = '5'; //is a reserved symbol, it will be used as an unexplored id

/**
*Class for solving mazes
*/
class maze
{
protected:
	/**
	*map used for solving
	*/
	char* map = nullptr; 

	/**
	*map for output
	*/
	char* map_out = nullptr;

	/**
	*xs -> x size; ys -> y size
	*/
	int xs = 0, ys = 0;

	/**
	*stream for reading input file
	*/
	ifstream in_stream;

	/** 
	*stores wether the maze is in debug mode
	*/
	bool debug = false;

public:
	/**
	*constructor for maze
	*@param input_path -> Location of file for input
	*\param output_path -> Location of file for output
	*/
	maze(string input_path, bool debug = false); //constructor

	/**
	*destructor for maze
	*/
	virtual ~maze(); //destructor

	//---------------------------------------------------------------------------
	//utility methods for printing of maze
	/**
	*print the entire maze 
	*\param exp -> 0 prints map ; 1 prints map_out)
	*/
	void print(bool exp);

	/**
	*prints a character that is at specified position in map 
	*/
	char print_one(int x, int y); 

	/**
	*print contents of map_out to output file
	*/
	void print_to_file(string path = "");
};

/*
*Virtualy inheriting interface for maze solvers.
*Has to inherit virtualy so that i don't have to define passing constructors (they would just call the same constructor in maze)
*/
class maze_solver : public virtual maze{
public:
	//---------------------------------------------------------------------------
	//these methods are for working with the maze
	/**
	*called automatically in constructor for loading from file, works only if class was created from file
	*filling map for search algorithm
	*/
	virtual bool maze_fill() = 0;

	/**
	*solves the maze by using an algorithm
	*/
	virtual int solve() = 0;

};