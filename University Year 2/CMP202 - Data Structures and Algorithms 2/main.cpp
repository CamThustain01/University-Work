#include "mandelbrot_farm.h"
#include "task_sub.h"
#include "task.h"

// Task-based parallelism example
// Adam Sampson <a.sampson@abertay.ac.uk>

#include <iostream>
#include <string>
#include <array>
#include <thread>
#include<chrono>
#include<condition_variable>
#include<mutex>


using namespace std;

// Import things we need from the standard library
using std::cout;
using std::to_string;
using std::cin;
using std::thread;
using std::this_thread::sleep_for;
using std::chrono::microseconds;
using std::mutex;
using std::condition_variable;


// The image data.
// Each pixel is represented as 0xRRGGBB.
Array2D image;

//variables
float total_ = 15;
float sum_;
float count_;

std::mutex mtx_;
std::condition_variable cv_;

bool result_calculated = false;

//thread functions
void CalculatePercentage()//calculate percentage
{
	sleep_for(microseconds(5));
	unique_lock<mutex> lock(mtx_);

	//sum = count_ (starts at 0 but in for loops will go up until 15) divided by total_ (15) 
	sum_ = count_ / total_;
	//sum needs to be multiplied by 100 to be in percentage format
	sum_ = sum_ * 100;

	result_calculated = true;

	cv_.notify_one();
	

}
void ShowPercentage()//displays percentage
{
	unique_lock<mutex>lock(mtx_);

	while (!result_calculated)
	{
		cv_.wait(lock);
	}


	//display sum to window
	cout << "Mandelbrot is: " << sum_ << "% complete.\n";

}

//thread for showing completion 
//std::thread completion_worker(ShowCompletion);

void write_tga(const char* filename)
{
	ofstream outfile(filename, ofstream::binary);

	uint8_t header[18] = {
		0, // no image ID
		0, // no colour map
		2, // uncompressed 24-bit image
		0, 0, 0, 0, 0, // empty colour map specification
		0, 0, // X origin
		0, 0, // Y origin
		WIDTH & 0xFF, (WIDTH >> 8) & 0xFF, // width
		HEIGHT & 0xFF, (HEIGHT >> 8) & 0xFF, // height
		24, // bits per pixel
		0, // image descriptor
	};
	outfile.write((const char*)header, 18);

	for (int y = 0; y < HEIGHT; ++y)
	{
		for (int x = 0; x < WIDTH; ++x)
		{
			uint8_t pixel[3] = {
				image[y][x] & 0xFF, // blue channel
				image[y][x] >> 8 & 0xFF, // green channel
				image[y][x] >> 16 & 0xFF, // red channel
			};
			outfile.write((const char*)pixel, 3);
		}
	}

	outfile.close();
	if (!outfile)
	{
		// An error has occurred at some point since we opened the file.
		cout << "Error writing to " << filename << endl;
		exit(1);
	}
}




int main(int argc, char* argv[])
{
	//threads
	mandelbrot_farm farm_;


	int choice_;
	int colour_;

	int slice = 75;


	cout << "MANDELBROT FARM" << endl;
	cout << "Please Pick A Colour:" << endl;
	cout << endl;
	cout << "RED - Press 1" << endl;
	cout << "GREEN - Press 2"<<endl;
	cout << "BLUE - Press 3" << endl;
	cin >> choice_;


	if (choice_ == 1)
	{
		//pass the colour variable into farm thread function
		colour_ = 0xff0000;//red
	}
	else if (choice_ == 2)
	{
		//pass the colour variable into farm thread function
		colour_ = 0x00ff00;//green
	}
	else if (choice_ == 3)
	{
		//pass the colour variable into farm thread function
		colour_ = 0x0000ff;//blue
	}
	else//if user doesnt pick appropriate input they are asked again....
	{
		cout << "Not Appropriate Input" << endl;
		cout << "Please Pick One Of These Colours" << endl;
		cout << "RED Press 1" << endl;
		cout << "GREEN Press 2" << endl;
		cout << "BLUE Press 3" << endl;
		cin >> choice_; //user input goes into choice_ variable
	}

	cout << "Please wait..." << endl;
	cout << endl;

	// Start timing
	the_clock::time_point start = the_clock::now();

	for (count_; count_ <= total_; count_++)
	{

		// This shows the whole set.
		farm_.add_task(new task_sub(-2.0, 1.0, 1.125, -1.125, slice, colour_));//add task to farm

		slice = slice + 75; //adds 75 to slice each iteration 


		// This zooms in on an interesting bit of detail.
		//for (int i = 0; i <= 15; i++)
		//{
		//	farm_.add_task(new task_sub(-0.751085, -0.734975, 0.118378, 0.134488, slice, 0xff0000))
		//	slice = slice + 75;
		//}


		std::thread calcThread(CalculatePercentage); //makes threads for calculating and showing percentage
		std::thread showThread(ShowPercentage);

		calcThread.join();//calculate perentage
		showThread.join();//show percentage

		

	}

	cout<< "Mandelbrot is : " << sum_ << " % complete.\n";//displays final percentage

	farm_.run();//run farm 

	// Stop timing
	the_clock::time_point end = the_clock::now(); //ends clock

	// Compute the difference between the two times in milliseconds
	auto time_taken = duration_cast<milliseconds>(end - start).count();
	cout << "Computing the Mandelbrot set took " << time_taken << " ms." << endl;


	write_tga("output.tga");//writes file

	return 0;



}