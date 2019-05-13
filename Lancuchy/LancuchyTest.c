#define StrLength 254

void CopyString(char pcSource[], char pcDestination[])
{
	unsigned char ucCharacterCounter;
	for(ucCharacterCounter=0; pcSource[ucCharacterCounter]!='\0'; ucCharacterCounter++)	
	{
		pcDestination[ucCharacterCounter] = pcSource[ucCharacterCounter];
	}		
}

enum CompResult
{
	DIFFERENT=0,
	EQUAL
};

enum CompResult eCompareString(char pcStr1[], char pcStr2[])
{
		unsigned char ucCharacterCounter;
		for(ucCharacterCounter=0; pcStr1[ucCharacterCounter]!='\0'; ucCharacterCounter++)
	{
		if(pcStr1[ucCharacterCounter]!=pcStr2[ucCharacterCounter])
		{
			return DIFFERENT;
		}
	}
	return EQUAL;
}

void AppendString(char pcSourceStr[],char pcDestinationStr[])
{
	unsigned char ucEndPointer;
	
	for(ucEndPointer=0; pcDestinationStr[ucEndPointer]!='\0' ;ucEndPointer++) {}
	CopyString(pcSourceStr, pcDestinationStr+ucEndPointer);
}


void ReplaceCharactersInString(char pcSource[], char cOldChar, char cNewChar)
{
	unsigned char ucCharacterCounter;
	for(ucCharacterCounter=0; pcSource[ucCharacterCounter]!=0; ucCharacterCounter++)
	{
		if(pcSource[ucCharacterCounter]==cOldChar)	
		pcSource[ucCharacterCounter]=cNewChar;
	}
}

int main()
{
	//test CopyString
	char string1[StrLength]="test";
	char string2[StrLength]="test";
	
}

