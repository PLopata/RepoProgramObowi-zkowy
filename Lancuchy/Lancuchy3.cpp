#include<iostream>
using namespace std;

#define StringLength 253

void CopyString(char pcSource[], char pcDestination[])
{
	for (unsigned char ucCharacterCounter=0; pcSource[ucCharacterCounter]!='\0'; ucCharacterCounter++)	
	{
		pcDestination[ucCharacterCounter] = pcSource[ucCharacterCounter]; pcSource++;
	}		
} 

void AppendString(char pcSource[],char pcDestination[])
{
	unsigned char ucCharacterCounter;
	for(ucCharacterCounter=0; pcDestination[ucCharacterCounter]!='\0' ;ucCharacterCounter++) {}
	CopyString(pcSource, pcDestination+ucCharacterCounter);
}

int main()
{
	char pcSource[StringLength], pcDestination[StringLength];
	cout<<"wprowadz string1\n";
	cin>>pcSource;
	cout<<"\nwprowadz string2\n";
	cin>>pcDestination;
	cout<<"\n\ntesting commences\n\n";
	
	AppendString(pcSource, pcDestination);
	
	cout<<pcDestination;
}
