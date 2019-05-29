#include <stdio.h>
#define NULL 0

enum Result {ERROR, OK} eResult;

void CopyString(char pcSource[], char pcDestination[])
{
	unsigned char ucCharacterCounter;
	
	for (ucCharacterCounter=0; pcSource[ucCharacterCounter] != NULL; ucCharacterCounter++)	
	{
		pcDestination[ucCharacterCounter] = pcSource[ucCharacterCounter];
	}		
}

void TestOf_CopyString(void)
{
	char acTestSource[] = "Test of copy";
	char acTestDestination[13];
	unsigned char ucCharCounter;
	enum Result eResult;
	CopyString(acTestSource, acTestDestination );
	
	printf("CopyString\n\n");
	printf("Test 1- \n");
	//Test 1 sprawdza, czy funkcja dobrze kopiuje stringi
	for ( ucCharCounter = 0; ucCharCounter < 13; ucCharCounter++ )
	{
		if ( acTestSource[ucCharCounter] == acTestDestination[ucCharCounter]  )
		{
			eResult=OK;
		}
		else
		{
			eResult=ERROR;
			break;
		}
	}
	if ( eResult == ERROR )
	{
		printf("ERROR\n");
	}
	else
	{
		printf("OK\n");
	}
}

enum CompResult { DIFFERENT, EQUAL } eCompareResult;

enum CompResult eCompareString(char pcStr1[], char pcStr2[])
{
	unsigned char ucCharacterCounter;
	
	for(ucCharacterCounter=0; ( pcStr1[ucCharacterCounter] != NULL ) || ( pcStr2[ucCharacterCounter] != NULL ); ucCharacterCounter++)
	{
		if(pcStr1[ucCharacterCounter] != pcStr2[ucCharacterCounter])
		{
			return DIFFERENT;
		}
	}
	return EQUAL;
}

void TestOf_eCompareString(void)
{
	char acTestString[]="Test 1";
	char acTestStringCorrect[]="Test 1";
	char acTestStringIncorrect[]="Test 2";
	enum CompResult eCompResult;
	
	printf("eCompareString\n\n");
	printf("\nTest 1- \n");
	//test 1 sprawdza czy funkcja poprawnie porownuje takie same stringi
	eCompResult = eCompareString(acTestString, acTestStringCorrect);
	if ( eCompResult == EQUAL )
	{
		printf("Ok\n");
	}
	else 
	{
		printf("Error\n");
	}
	
	printf("\nTest 2- \n");
	//test 2 sprawdza czy funkcja poprawnie porownuje rozne stringi
	eCompResult = eCompareString(acTestString, acTestStringIncorrect);
	if ( eCompResult == DIFFERENT )
	{
		printf("Ok\n");
	}
	else 
	{
		printf("Error\n");
	}
}

void AppendString(char pcSourceStr[],char pcDestinationStr[])
{
	unsigned char ucEndPointer;
	
	for(ucEndPointer=0; pcDestinationStr[ucEndPointer]!='\0' ;ucEndPointer++) {}
	CopyString(pcSourceStr, pcDestinationStr+ucEndPointer);
}

void TestOf_AppendString(void)
{
	enum CompResult eCompResult;
	char acTestResultDidntAppend[]="Test";
	char acTestResultCorrect[]="Test 1";
	char acTestSource[]=" 1";
	char acTestDestination[]="Test";
	AppendString(acTestSource, acTestDestination);
	
	printf("AppendString\n\n");
	printf("\nTest 1- \n");
	//test 1 sprawdza czy funkja w ogole przedluza stringa
	eCompResult=eCompareString(acTestDestination,acTestResultDidntAppend);
	if ( eCompResult == EQUAL )
	{
		printf("Error\n");
	}
	else
	{
		printf("Ok\n");
	}
	
	printf("\nTest 2- \n");
	//test 2 sprawdza czy funkcja poprawnie przedluza stringa
	eCompResult=eCompareString(acTestDestination,acTestResultCorrect);
	if ( eCompResult == DIFFERENT )
	{
		printf("Error\n");
	}
	else
	{
		printf("Ok\n");
	}
}

void ReplaceCharactersInString(char pcSource[], char cOldChar, char cNewChar)
{
	unsigned char ucCharacterCounter;
	
	for(ucCharacterCounter=0; pcSource[ucCharacterCounter]!=0; ucCharacterCounter++)
	{
		if(pcSource[ucCharacterCounter]==cOldChar)	
		{
			pcSource[ucCharacterCounter]=cNewChar;
		}
	}
}

void TestOf_ReplaceCharactersInString(void)
{
	char acTestSource[]="test 1";
	char acTestOldChar='t';
	char acTestNewChar='a';
	char acTestResult[]="aesa 1";
	enum CompResult eCompResult;
	ReplaceCharactersInString(acTestSource, acTestOldChar, acTestNewChar);
	
	printf("ReplaceCharactersInString\n\n");
	printf("Test 1- \n");
	//test 1 sprawdza poprawne zmienianie znakow
	eCompResult = eCompareString(acTestSource, acTestResult);
	if ( eCompResult == DIFFERENT )
	{
		printf("Error\n");
	}
	else
	{
		printf("Ok\n");
	}
}

int main()
{
	TestOf_ReplaceCharactersInString();
}
