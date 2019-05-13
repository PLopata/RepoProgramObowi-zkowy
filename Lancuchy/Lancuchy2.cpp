#include<iostream>
using namespace std;

#define StringLength 253
 
enum CompResult
{
	DIFFERENT=0,
	EQUAL
};

enum CompResult eCompareString(char pcSource[], char pcDestination[])
{
		for(unsigned char ucCharacterCounter=0; pcSource[ucCharacterCounter]!='\0'; ucCharacterCounter++)
	{
		if(pcSource[ucCharacterCounter]!=pcDestination[ucCharacterCounter])
		{
			return DIFFERENT;
		}
	}
	return EQUAL;
}
 
int main()
{
	char pcSource[StringLength], pcDestination[StringLength];
	cout<<"wprowadz string1\n";
	cin>>pcSource;
	cout<<"\nwprowadz string2\n";
	cin>>pcDestination;
	cout<<"\n\ntesting commences\n\n";
	
	cout<<eCompareString(pcSource, pcDestination);
	
}
