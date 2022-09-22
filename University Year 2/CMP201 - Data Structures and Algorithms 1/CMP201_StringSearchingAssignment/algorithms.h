#pragma once
#include "utils.h"
#include <iostream>
#include <string>
#include <cassert>
#include <list>
#include <vector>
#include <set>
#include <iterator>


using std::cout;
using std::endl;
using std::string;

class algorithms
{
public:

	std::set<int> BMset; //two sets that we insert counts into
	std::set<int> RKset;
	typedef std::set<int>::iterator it; //allows us to create our two iterators

	it iterator; //iterators for sets 
	it iterator2;

	Position boyerMoore(const string& pat, const string& text);
	Position rabinKarp(const string& pat, const string& text, int q);
	int resultsRK();//function to display rk resultss
	int resultsBM(); //function for displaying bm results
	int getBMcount() { return BMcount; }; //getters for count variables so we can use this in our file append in source...
	int getRKcount() { return RKcount; };

	

	int BMcount = 0; //count variable for times pattern is found
	int RKcount = 0;

};

