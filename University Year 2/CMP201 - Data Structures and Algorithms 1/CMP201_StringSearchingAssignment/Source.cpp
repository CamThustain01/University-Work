#include <iostream>
#include <fstream>
#include "algorithms.h"
#include "utils.h"
#include <chrono>


using std::fstream; //allows access to fstream

using std::chrono::duration_cast;
using std::chrono::milliseconds; //sets up time value

typedef std::chrono::steady_clock bmClock; //creates our clocks 
typedef std::chrono::steady_clock rkClock;




int main()
{

	string text; //string for english script
	string text2; //string for japanese (translated) script 
	
	//loads in our text files
	load_file("inputs/ff7engscript.txt", text);//loads in both scripts and assigns it a string
	load_file("inputs/ff7jpscript.txt", text2);

	string pat = " are ";
	algorithms alg; //creates an instances of algorithm class


	//start clock for timing boyer moore
	bmClock::time_point start = bmClock::now();

	//Boyer Moore Algorithm
	alg.boyerMoore(pat, text);
	//Call function which displays values within the boyer moore swt
	alg.resultsBM();
	//stop clock for boyer moore
	bmClock::time_point end = bmClock::now();

	//work out difference between the two times.
	auto time_taken = duration_cast<milliseconds>(end - start).count();
	//display time it took to find the string using Boyer Moore 
	cout << "It took: " << time_taken << "ms. \n";
	cout << endl;
	cout << endl;



	//start clock for timing rabin karp
	rkClock::time_point start2 = rkClock::now();

	//Rabin Karp Algorithm
	alg.rabinKarp(pat, text2, pat.size()); //hashes value by size of pattern

	//displays set holding rabin karp results
	alg.resultsRK();
	//stop clock for rabin karp 
	rkClock::time_point end2 = rkClock::now();

	auto time_taken2 = duration_cast<milliseconds>(end2 - start2).count();

	//display time it took to find string using Rabin Karp
	cout << "It took: " << time_taken2 << "ms. \n";
	cout << endl;
	cout << endl;




	string filename("results.txt"); //creates a text file called results 
	fstream file; //creates an object of fstream



	file.open(filename, std::ios_base::app | std::ios_base::in); //opens our file
	if (file.is_open()) //if the file is open do the following
	{
		file << "Results" << endl; //add this text and results to our text file 
		file << "Pattern Found - " << pat << endl;
		file << "Boyer-Moore Count:" << endl;
		file << alg.getBMcount()<<",  "<< time_taken <<"ms."<< endl;
		cout<<endl;
		file << "Rabin Karp Count:" << endl;
		file << alg.getRKcount() <<",  "<< time_taken2<<"ms."<< endl;
		cout << endl;
		cout << endl;
	}

	file.close(); //close files afterwards

	system("Pause");

	return EXIT_SUCCESS;

	


	

	
	 

	
	
	

}