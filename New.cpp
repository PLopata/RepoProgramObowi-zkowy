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

void AppendString(char pcSource[],char pcDestination[])
{
	unsigned char ucCharacterCounter;
	for(ucCharacterCounter=0; pcDestination[ucCharacterCounter]!='\0' ;ucCharacterCounter++) {}
	CopyString(pcSource, pcDestination+ucCharacterCounter);
}


void ReplaceCharactersInString(char pcSource[], char cOldChar, char cNewChar)
{
	for(unsigned char ucCharacterCounter=0; pcSource[ucCharacterCounter]!=0; ucCharacterCounter++)
	{
		if(pcSource[ucCharacterCounter]==cOldChar)	
		pcSource[ucCharacterCounter]=cNewChar;
	}
}

int main()
{
	char pcSource[StringLength], cOldChar, cNewChar;
	cout<<"wprowadz string1\n";
	cin>>pcSource;
	cout<<"\nPodaj jaki znak chcesz zmienic\n";
	cin>>cOldChar;
	cout<<"\nPodaj na jaki znak chcesz zamienic\n";
	cin>>cNewChar;

	ReplaceCharactersInString(pcSource, cOldChar, cNewChar)	;

	cout<<"\n\n"<<pcSource;
}
