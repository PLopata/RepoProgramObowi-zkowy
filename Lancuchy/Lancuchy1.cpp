#include<iostream>
using namespace std;

#define StringLength 253
 
void CopyString(char pcSource[], char pcDestination[])
{
	for (unsigned char ucCharacterCounter=0; pcSource[ucCharacterCounter]!='\0'; ucCharacterCounter++)	
	{
		pcDestination[ucCharacterCounter] = pcSource[ucCharacterCounter];
	}		
}
 
int main()
{
	char pcSource[StringLength], pcDestination[StringLength];
	cout<<"wprowadz string:\n";
	cin>>pcSource;
	cout<<"\nCopying commences:\n";
	//faktyczne kopiowanie
	
	CopyString(pcSource, pcDestination);
	
	cout<<"\n\nCorrectness test:\nStrings:\n"
		<<pcSource<<"\n"<<pcDestination;
}
