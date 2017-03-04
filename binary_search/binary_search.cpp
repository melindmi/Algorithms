#include <iostream>
#include <vector>
#include <stdlib.h> //for atoi
#include <fstream>

using namespace std;

bool binary_search_rec(vector<int> input, int key)
{
	int n=input.size(), pos=n/2;
	vector<int> newInput;
	
	if(n == 0)
	{
		return false;	
	}
	if((n == 1) && (input[pos] != key))
	{
		return false;
	}	
	
	if(input[pos] == key)
	{
			return true;
	}
	else if(input[pos] > key)
	{
		newInput.assign(input.begin(), input.begin()+pos);
	}
	else if(input[pos] < key)
	{
		newInput.assign(input.begin()+pos, input.end());	
	}
		
	return binary_search_rec(newInput, key);		
}

bool test1()
{
	int key = 8;
	vector<int> inputValues;
	int a[] = {6, 8, 9};
	inputValues.assign(a, a+3);
	
	return (true == binary_search_rec(inputValues, key));
}

bool test2()
{
	int key = 21;
	vector<int> inputValues;
	int a[] = {1, 2, 3, 5, 6, 8, 9, 10, 12, 14, 16, 21};
	inputValues.assign(a, a+12);
	
	return (true == binary_search_rec(inputValues, key));
}

bool test3()
{
	int key = 8;
	vector<int> inputValues;
	int a[] = {6, 9};
	inputValues.assign(a, a+2);
	
	return (false == binary_search_rec(inputValues, key));
}

bool test4()
{
	int key = 10001;
	vector<int> inputValues;
	ifstream file("input.txt");
	string line;
	if(file.is_open())
	{
			while(getline(file, line))
			{
				inputValues.push_back(atoi(line.c_str()));
			}	
			file.close();	
	}
	
	return (true == binary_search_rec(inputValues, key));
}

int main(int argc, char** argv)
{
	cout << "test1 " << (test1() ? "OK" : "FAILED") << endl; 	
	cout << "test2 " << (test2() ? "OK" : "FAILED") << endl; 	
	cout << "test3 " << (test3() ? "OK" : "FAILED") << endl; 	
	cout << "test4 " << (test4() ? "OK" : "FAILED") << endl; 	
		
	return 0;
}

