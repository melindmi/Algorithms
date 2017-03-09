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

int getMedianOfThreePos(vector<int>& a, int l, int r)
{
	int pos=l, middle;
	
	if((r-l)%2 == 0)
	{
		middle = (r+l)/2 - 1; // l + ((r-l)/2 - 1 )
	}
	else
	{
		middle = (r+l)/2;  // l + (r-l)/2
	}
	if(((a[l] <= a[middle]) && (a[middle] <= a[r-1])) || ((a[r-1] <= a[middle]) && (a[middle] <= a[l])))
	{
		pos = middle;	
	}
	else if(((a[middle] <= a[l]) &&(a[l] <= a[r-1])) || ((a[r-1] <= a[l]) && (a[l] <= a[middle])))
	{
		pos = l;
	}
	else if(((a[middle] <= a[r-1]) &&(a[r-1] <= a[l])) || ((a[l] <= a[r-1]) && (a[r-1] <= a[middle])))
	{
		pos = r-1;
	}
	
	return pos;
}

int getPivot(vector<int>& a, int l, int r, string iPivotPos)
{
	if((iPivotPos != "first") && (iPivotPos != "last") && (iPivotPos != "median"))
	{
		cerr << "Unknown pivot position!" <<endl;
		throw;
	}
	
	//if (iPivotPos == "first") do nothing, return l;
	
	if(iPivotPos == "last")
	{	
		swap(a[l], a[r-1]);
	}
	else if (iPivotPos == "median")
	{
		swap(a[l], a[getMedianOfThreePos(a, l, r)]);	
	}

	return l;
}

//the pivot is the first element
int quick_sort(vector<int>& a, int l, int r, string iPivotPos)
{
	int total_comparisons=0;
	if((r-l) < 2)
	{
		return total_comparisons;
	}
	else
	{
		int pivot = getPivot(a, l, r, iPivotPos);
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
		total_comparisons += quick_sort(a, l, i-1, iPivotPos);
		total_comparisons += quick_sort(a, i, r, iPivotPos);
	}
	
	return total_comparisons;
}

int testFromVector1(string iPivotPos)
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

		ret = quick_sort(vect, 0, vect.size(), iPivotPos);
		cout << "Total comparisons for pivot on position "<< iPivotPos << " : " << ret << endl; 
		
		return ret;
}

int testFromFile(string iName, string iPivotPos)
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

	ret = quick_sort(vect, 0, vect.size(), iPivotPos);
	cout << "Total comparisons for pivot on position " << iPivotPos <<" : "<< ret << endl; 
	
	return ret;
}



int main(int argc, char** argv)
{
	cout << ((15 == testFromVector1("first")) ? "OK" : "FAILED") << endl;
	cout << ((25 == testFromFile("10.txt", "first")) ? "OK" : "FAILED") << endl;
	cout << ((615 == testFromFile("100.txt", "first")) ? "OK" : "FAILED") << endl;
	cout << ((10297 == testFromFile("1000.txt", "first")) ? "OK" : "FAILED") << endl;
	
	cout << ((15 == testFromVector1("last")) ? "OK" : "FAILED") << endl;
	cout << ((29 == testFromFile("10.txt", "last")) ? "OK" : "FAILED") << endl;
	cout << ((587 == testFromFile("100.txt", "last")) ? "OK" : "FAILED") << endl;
	cout << ((10184 == testFromFile("1000.txt", "last")) ? "OK" : "FAILED") << endl;
  
	cout << ((13 == testFromVector1("median")) ? "OK" : "FAILED") << endl;
	cout << ((21 == testFromFile("10.txt", "median")) ? "OK" : "FAILED") << endl;
	cout << ((518 == testFromFile("100.txt", "median")) ? "OK" : "FAILED") << endl;
	cout << ((8921 == testFromFile("1000.txt", "median")) ? "OK" : "FAILED") << endl;
	
	testFromFile("10000.txt", "first");
	testFromFile("10000.txt", "last");
	testFromFile("10000.txt", "median");
	
	return 0;
}
