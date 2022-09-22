#include "task_sub.h"
#include<iostream>

task_sub::task_sub(double left, double right, double top, double bottom, int slice, int colour)
{
	left_ = left;
	right_ = right;
	top_ = top;
	bottom_ = bottom;
	slice_ = slice;
	colour_ = colour;
}



void task_sub::run()
{
	//computes mandelbrot
	compute_mandelbrot(left_, right_, top_, bottom_, slice_, colour_); //run computes the mandelbrot
}

void task_sub::compute_mandelbrot(double left, double right, double top, double bottom, int slice, int colour)
{


	for (int y = slice - 75; y < slice; ++y)
	{
		for (int x = 0; x < WIDTH; ++x)
		{
			// Work out the point in the complex plane that
			// corresponds to this pixel in the output image.
			complex<double> c(left + (x * (right - left) / WIDTH),
				top + (y * (bottom - top) / HEIGHT));

			// Start off z at (0, 0).
			complex<double> z(0.0, 0.0);

			// Iterate z = z^2 + c until z moves more than 2 units
			// away from (0, 0), or we've iterated too many times.
			int iterations = 0;
			while (abs(z) < 2.0 && iterations < MAX_ITERATIONS)
			{
				z = (z * z) + c;

				++iterations;
			}

			if (iterations == MAX_ITERATIONS)
			{
				// z didn't escape from the circle.
				// This point is in the Mandelbrot set.
				image[y][x] = 0x00000; // black
			}
			else
			{
				// z escaped within less than MAX_ITERATIONS
				// iterations. This point isn't in the set.
				image[y][x] = colour << iterations;
			}
		}
	}

}


