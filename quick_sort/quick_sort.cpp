#include <iostream>
#include <vector>
#include <stdlib.h>
#include <fstream>

using namespace std;

void print(vector<int> a)
{
	int n = a.size();

	for(int i=0; i<n; ++i)
	{
			cout << a[i] << " "; 	
	}
	cout << endl;
}

void swap(int &a, int &b)
{
	int temp;
	temp = a;
	a = b;
  b = temp;
}

int quick_sort(vector<int> a, int l, int r)
{
	int pivot = l, total_comparisons=0;
	if((r-l) < 2)
	{
		//print(a);
		return total_comparisons;
	}
	else
	{
		int i = l+1; //the position of the first element grater then the pivot
		// j = the position of the last element that has been processed until now
		for(int j=i; j<r; ++j)
		{
			//if(a[j] > pivot) do nothing
			if(a[j] < a[pivot])
			{	
				swap(a[j], a[i]);
				++i;
			}			
		}
		swap(a[pivot], a[i-1]);
		
		total_comparisons += (r-l-1);
		total_comparisons += quick_sort(a, l, i-1);
		total_comparisons += quick_sort(a, i, r);
	}
	
	return total_comparisons;
}

int testFromVector1()
{
		int ret;
		vector<int> vect;
		vect.push_back(3);
		vect.push_back(8);
		vect.push_back(1);
		vect.push_back(5);
		vect.push_back(2);
		vect.push_back(6);
		vect.push_back(4);
		vect.push_back(7);

		//print(vect);
		ret = quick_sort(vect, 0, vect.size());
		cout << "Total comparisons: " << ret << endl; 
		return ret;
}

int testFromFile(string iName)
{
	int ret;
	string line;
	vector<int> vect;
	ifstream file(iName.c_str());
	if(file.is_open())
	{
		while(getline(file, line))
		{
			vect.push_back(atoi(line.c_str()));
		}
		file.close();
	}

	//print(vect);
	ret = quick_sort(vect, 0, vect.size());
	cout << "Total comparisons: " << ret << endl; 
	return ret;
}



int main(int argc, char** argv)
{
	cout << ((15 == testFromVector1()) ? "OK" : "FAILED") << endl;
	cout << ((25 == testFromFile("10.txt")) ? "OK" : "FAILED") << endl;
	cout << ((615 == testFromFile("100.txt")) ? "OK" : "FAILED") << endl;
	cout << ((10297 == testFromFile("1000.txt")) ? "OK" : "FAILED") << endl;

	return 0;
}
