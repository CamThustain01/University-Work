#include "algorithms.h"
#include "utils.h"

Position algorithms::boyerMoore(const string& pat, const string& text)
{
	Position pattern_len = pat.size(); //creates instance of Position called pattern_len which is equal to the size of our pattern
	Position text_len = text.size();  //creates instances of Position called text_len which is equal to the size of our text
	int skip[256]; //array called skip holding 256 (characters)
	


	for (int i = 0; i < 256; i++)
	{
		skip[i] = pattern_len; //not in the pattern
	}
	for (int i = 0; i < pattern_len; i++)
	{
		skip[int(pat[i])] = (pattern_len - 1) - i;

	}
	
	std::vector<int> result;

	for (int i = 0; i < text_len - pattern_len-1; ++i)//get rid of -1 if it causes issues later
	{
		int s = skip[int(text[i + pattern_len - 1])]; 

		if (s != 0)
		{
			i += s - 1;//skips forward
			continue;
		}
		int j;
		for (j = 0; j < pattern_len; j++)
		{
			if (text[i + j] != pat[j])
			{
				break; //doesnt match
			}
		}
		if (j == pattern_len) //pattern found
		{
			
			BMcount++; //adds to bm count variable
		
		}
		BMset.insert(BMcount); //inserts value of variable into the set
	}
	return -1;
}

Position algorithms::rabinKarp(const string& pat, const string& text, int q)
{
	Position pattern_len = pat.size(); //create two instances of position pattern_len and text_len 
	Position text_len = text.size();
	
	auto d = text.length();  //auto d which is equal to text length
	int i, j; 

	int values[3] = { 0,0,1 }; //values for working out hashing

	
	
		for (i = 0; i < pattern_len - 1; i++)
			values[2] = ( values[2] * d) % q;

	
		for (i = 0; i < pattern_len; i++) {
			values[0] = (d * values[0] + pat[i]) % q; //works out the has value for the text and the pattern
			values[1] = (d * values[1] + text[i]) % q;
		}

		
		for (i = 0; i <= text_len - pattern_len; i++) {
			if (values[0] == values[1]) { //this looks through the text for a match
				for (j = 0; j < pattern_len; j++) {
					if (text[i + j] != pat[j])
						break;
				}

				if (j == pattern_len) //if j equals the pattern there is a match
				{
					RKcount++; //adds one to count
				}
				RKset.insert(RKcount); //insets count into the set
			}

			if (i < text_len - pattern_len) { //if pattern isnt found
				values[1] = (d * (values[1] - text[i] * values[2]) + text[i + pattern_len]) % q;

				if (values[1] < 0)
					values[1] = (values[1] + q);
			}
		}

		return -1;
	}

int algorithms::resultsRK()
{
	for (iterator2 = RKset.begin(); iterator2 != RKset.end(); iterator2++) //begins going through set until theres no more values
	{
		cout <<  *iterator2<<endl; //displays iterator (count values)

	}

	return 0;

	cout << endl;

	cout << endl;
}




int algorithms::resultsBM()
{
	for (iterator = BMset.begin(); iterator != BMset.end(); iterator++) //begins going through each value until theres no more
	{
		cout << *iterator<<endl; //display the values
		
	} 
	
	return 0;

	cout << endl;
	
	cout << endl;
}





