#pragma once
#ifndef TASK_SUB_H
#define TASK_SUB_H

#include "task.h"
#include <string>
#include <array>
#include <chrono>
#include <cstdint>
#include <cstdlib>
#include <complex>
#include <fstream>
#include <iostream>


// Import things we need from the standard library
using std::chrono::duration_cast;
using std::chrono::milliseconds;
using std::complex;
using std::cout;
using std::endl;
using std::ofstream;

// Define the alias "the_clock" for the clock type we're going to use.
typedef std::chrono::steady_clock the_clock;


// The size of the image to generate.
const int WIDTH = 1920;
const int HEIGHT = 1200;

typedef std::array < std::array < uint32_t, WIDTH>, HEIGHT> Array2D; //reates an array

extern Array2D image; //creates public array called image


// The number of times to iterate before we assume that a point isn't in the
// Mandelbrot set.
// (You may need to turn this up if you zoom further into the set.)
const int MAX_ITERATIONS = 500;

class task_sub : public task //inherits from task
{
public:

	//functions
	task_sub(double left, double right, double top, double bottom, int slice, int colour);
	void run();
	
	void compute_mandelbrot(double left, double right, double top, double bottom, int slice,int colour);

		


private:

	//variables for computing the mandelbrot
	int slice_;
	int left_; 
	int right_;
	int top_;
	int bottom_;
	int colour_;

};

#endif
