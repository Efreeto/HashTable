
#include <unordered_map>
#include <iostream>
#include <vector>
using namespace std;

int main()
{	
	// Initialize input (Input must be an array of integers with each number occuring an even number of times except for one number that occurs an odd number of times.)
	int input_raw_[] = { 1,1,14,5,5,14,73,5,73,1,1 };	// initialize input_raw_ : CHANGE ITS CONTENTS TO RUN OTHER TESTS
	vector<int> input;
	for (int i=0; i<sizeof(input_raw_)/sizeof(int); i++)
		input.push_back(input_raw_[i]);					// initialize input : will be used by the codes below instead of input_raw_

	//////////////////////////////////////////
	//	The first method using hash table	//
	//////////////////////////////////////////

	// Create a hash table with integer key and bool value
    unordered_map<int,bool> table;

	for (int i=0; i<input.size(); i++)
	{
		table[input[i]] = !table[input[i]];
		// All in one function that performs:
		// 1. inserts input[i] (key) to table
		// 2. if there is an entry, loads the value (bool) with the entry (key) (table is already initialized to have 0 values)
		// 3. toggles true/false of the value
	}
	
	// Output that occurs an odd number of times in the input array
	int output;
	int output_count = 0;

	// Check for every entry with the value true
	for (unordered_map<int,bool>::iterator it=table.begin(); it!=table.end(); it++)
	{		
		// Print out the table and the output
		cout << it->first << ": " << it->second << endl;
	
		if (it->second)
		{
			output = it->first;
			output_count++;
		}
	}
	
	// Check for incorrect input array and print out the output
	if (output_count!=1)
	{
		cout << "Incorrect input array format:\n";
		cout << "One number must occur an odd number of times in the array.\n";
		exit(1);
	}	
	cout << endl << "Output: " << output << endl;

	//////////////////////////////////
	//	The second method using XOR	//
	//////////////////////////////////

	int output2 = 0;
	for (int i=0; i<input.size(); i++)
	{
		output2 ^= input[i];
	}
	cout << endl << "Output2: " << output2 << endl;
}