#include<iostream>

using namespace std;

enum Example;
{
	a=0,
	b,
	c
}

int main()
{
	Example test=a;
	if(test == a)
	{
		cout<<"Success!";
	}
	
}


