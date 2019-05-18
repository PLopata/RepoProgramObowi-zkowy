#define StringLength 253

void CopyString(char pcSource[], char pcDestination[])
{
	unsigned char ucCharacterCounter;
	for (ucCharacterCounter=0; pcSource[ucCharacterCounter]!='\0'; ucCharacterCounter++)	
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
	char string1[StringLength]="test";
	char string2[StringLength];
	
	CopyString(string1, string2);
	printf(string1);
	
	
	
	
	
	
	
	
	
	
	
//	char string1[StringLength], string2[StringLength], string3[StringLength], char1, char2; 
//	cout<<"type string\n";
//	cin>>string1;
//	cout<<"\n\ntype string2\n\n";
//	cin>>string2;
//	cout<<"\n\nnow type character you want to replace\n\n";
//	cin>>char1;
//	cout<<"\n\nnow char2\n\n";
//	cin>>char2;
//	
//	cout<<"\n\ncopystring test\n";
//	CopyString(string1, string3);
//	cout<<string1<<"\n and string3\n"<<string3;	
//	cout<<"\n\nResult of comparing\n"<<eCompareString(string1, string2);
//	cout<<"\nAppendString test\n";
//	AppendString(string1, string2);
//	cout<<"\nString1\n"<<string1<<"\n\nand string2\n"<<string2;
//	cout<<"\n\nReplacing test\nBefore:\n"<<string1;
//	ReplaceCharactersInString(string1, char1, char2);
//	cout<<"\n\nAnd after\n\n"<<string1;
	
}
