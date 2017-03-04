#include <iostream>
#include <fstream>
#include <vector>
#include <stdlib.h>  //for atoi

using namespace std;

//print a vector of integers
void print(vector<int> a)
{
	int n = a.size();
	for(int i=0; i < n; ++i)
	{
		cout << a[i] << " ";
	}
	cout <<endl;
}

//merge 2 sorted vectors and count the number of inversions
vector<int> merge_and_count(vector<int> a, vector<int>b, long long int& count_inv)
{
	int i=0, j=0, n=a.size(), m=b.size();
	vector<int> c;
	while((i<n)&&(j<m))
	{
		if(a[i] > b[j])
		{
			c.push_back(b[j]);
			++j;
			//inversion = if a value from the first sorted vector is bigger than a value from the second sorted vector
			//the number of inversions to be considered from this point is equal to the number 
			//of the remining values in the first sorted vector
			count_inv += n-i;
		}
		else if(a[i] < b[j])
		{
			c.push_back(a[i]);  
			++i;
		}
		else 
		{
			c.push_back(a[i]);
			c.push_back(b[j]);
			++i;
			++j;
		}
	}
	while (i < n)
	{
		c.push_back(a[i]);
		++i;
	}
	while(j < m)
	{
		c.push_back(b[j]);
		++j;
	}

	return c;
}

//sort a vector and count the number of inversions
vector<int> sort_and_count(vector<int> a, long long int& count_inv)
{
	int n = a.size();
	if (n == 1)
	{
		return a;
	}
	else
	{
		n = n/2;
		vector<int> aa(a.begin(), a.begin()+n);
		vector<int> ab(a.begin()+n, a.end());
		aa = sort_and_count(aa, count_inv);  
		ab = sort_and_count(ab, count_inv);  
		return merge_and_count(aa, ab, count_inv);
	}
}

void test(vector<int> a)
{
	long long int count_inv=0;
	int n = a.size();
	vector<int> sorted_vect = sort_and_count(a, count_inv);
	//if the vector of int is not to big
	if(n < 21)
	{
		print(a);
		cout << "Sorted: "; 
		print(sorted_vect);
	}
	else //print just the size of the vector
	{	
		cout<<"Vector size: " << n << endl;	
	}
	cout << "Nb Of inversions: " << count_inv << endl;
	cout << endl;
}

vector<int> readFromFile(string name)
{
	vector<int> nbrs;
	string line;
	ifstream file(name.c_str());

	if(file.is_open())
	{
		while(getline(file, line))
		{
			nbrs.push_back(atoi(line.c_str()));
		}

		file.close();
	}

	return nbrs;	
}

int main()
{ 
	int n;
	///////////////
	int arr1[] = {4, 3, 6, 2};
	n=4;
	vector<int> a1(arr1, arr1+n);
	test(a1);
	//////////////////////////////////////////////
	int arr2[] = {2, 4, 7, 1, 3, 9, 23, 12, 45};
	n=9;
	vector<int> a2(arr2, arr2+n);
	test(a2);
	//////////////////////////////////////////////
	int arr3[] = {2, 2, 7, 1, 3, 9, 2, 12, 45};
	n=9;
	vector<int> a3(arr3, arr3+n);
	test(a3);
	//////////////////////////////////////////////
	int arr4[] = {6, 3, 5, 2, 4, 1};
	n=6;
	vector<int> a4(arr4, arr4+n);
	test(a4);
	//////////////////////////////////////////////
	int arr5[] = {20,19,18,17,16,15,14,13,12,11,10,9,8,7,6, 5, 4, 3, 2, 1};
	n=20;
	vector<int> a5(arr5, arr5+n);
	test(a5);

	//////////////////////////////////////////////
	vector<int> rf = readFromFile("input.txt");
	test(rf);
}
