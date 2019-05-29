#include <stdio.h>
#define NULL 0

enum Result {ERROR, OK} eResult;

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

/*------------------------------------------------------------------*/

void UIntToHexStr (unsigned int uiValue, char pcStr[])
{
	unsigned char ucNibbleCounter;
	unsigned char ucCurrentNibble;
	
	pcStr[0] = '0';
	pcStr[1] = 'x';
	for( ucNibbleCounter=0; ucNibbleCounter<4; ucNibbleCounter++ )
	{
		ucCurrentNibble = (uiValue >> (4*ucNibbleCounter)) & 0x000F;
		if ( ucCurrentNibble >= 10 )
		{
			pcStr[5 - ucNibbleCounter] = ucCurrentNibble + 'A' - 10;
		}
		else 
		{
			pcStr[5 - ucNibbleCounter] = ucCurrentNibble + '0';
		}
	}
	pcStr[6] = NULL;
}

void TestOf_UIntToHexStr()
{
	char acTestDestinationIdeal[6];
	char acTestDestinationTooShort[2];
	char acTestDestinationTooLong[8];
	char acTestDestinationNotEmpty[]="abcdef";
	char acTestDestinationNotEmptyTooLong[8]="abcdefgh";
	unsigned int uiTestSource = 0x12AC;
	char acTestCorrecResult[]="0x12AC";
	enum CompResult eCompResult;
	
	printf("UIntToHexStr\n\n");
	printf("Test 1-\n\n");
	//test 1 sprawdza poprawna konwersje na stringa w idealnych warunkach
	UIntToHexStr(uiTestSource, acTestDestinationIdeal);
	eCompResult = eCompareString(acTestDestinationIdeal, acTestCorrecResult );
	if ( eCompResult == EQUAL ) 
	{
		printf("Ok\n");
	}
	else
	{
		printf("Error\n");
	}
	
	printf("Test 2-\n\n");
	//test 2 sprawdza poprawna konwersje na stringa dla za krotkiej tablicy
	UIntToHexStr(uiTestSource, acTestDestinationTooShort);
	eCompResult = eCompareString(acTestDestinationTooShort, acTestCorrecResult );
	if ( eCompResult == EQUAL ) 
	{
		printf("Ok\n");
	}
	else
	{
		printf("Error\n");
	}
	
	printf("Test 3-\n\n");
	//test 3 sprawdza poprawna konwersje na stringa dla za dlugiej tablicy
	UIntToHexStr(uiTestSource, acTestDestinationTooLong);
	eCompResult = eCompareString(acTestDestinationTooLong, acTestCorrecResult );
	if ( eCompResult == EQUAL ) 
	{
		printf("Ok\n");
	}
	else
	{
		printf("Error\n");
	}
	
	printf("Test 4-\n\n");
	//test 4 sprawdza poprawna konwersje na stringa dla niepustej tablicy
	UIntToHexStr(uiTestSource, acTestDestinationNotEmpty);
	eCompResult = eCompareString(acTestDestinationNotEmpty, acTestCorrecResult );
	if ( eCompResult == EQUAL ) 
	{
		printf("Ok\n");
	}
	else
	{
		printf("Error\n");
	}
	
	printf("Test 5-\n\n");
	//test 5 sprawdza poprawna konwersje na stringa dla niepustej i za dlugiej tablicy
	UIntToHexStr(uiTestSource, acTestDestinationNotEmptyTooLong);
	eCompResult = eCompareString(acTestDestinationNotEmptyTooLong, acTestCorrecResult );
	if ( eCompResult == EQUAL ) 
	{
		printf("Ok\n");
	}
	else
	{
		printf("Error\n");
	}
}

enum Result eHexStringToUInt(char pcStr[], unsigned int *puiValue)
{
	unsigned char ucCharCounter;
	unsigned char ucCurrentCharacter;
	
	if ( (pcStr[0] != '0') || (pcStr[1] != 'x') || (pcStr[2] == NULL) )
	{
		return ERROR;
	}
	
	*puiValue = 0;
	for ( ucCharCounter = 2; pcStr[ucCharCounter] != NULL ; ucCharCounter++ )
	{
		ucCurrentCharacter = pcStr[ucCharCounter];
		
		if ( ucCharCounter == 6 ) 
		{
			return ERROR;
		}
		
		*puiValue = (*puiValue << 4);
		if ( ucCurrentCharacter >= 'A' )
		{
			*puiValue = *puiValue + (ucCurrentCharacter - 'A' + 10);
		}
		else
		{
			*puiValue = *puiValue + (ucCurrentCharacter - '0');
		}
	}
	return OK;
}

void TestOf_eHexStringToUInt()
{
	char acTestCorrect[]="0x12AC";
	char acTestShortCorrect[]="0x1";
	char acTestStartsWith1[]="1x12AC";
	char acTestSecondIsB[]="0b12AC";
	char acTestTooShort[]="0x";
	char actestTooLong[]="0x121AC";
	unsigned int uiTestResult;
	enum Result eResult;
	printf("eHexStringToUInt\n\n");
	
	printf("Test 1-\n");
	//test 1 sprawdza eHexStringToUInt dla idealnego stringa
	eResult = eHexStringToUInt( acTestCorrect, &uiTestResult );
	if ( eResult == OK && uiTestResult == 0x12AC )
	{
		printf("Ok\n");
	}
	else
	{
		printf("Error\n");
	}
	
	printf("Test 2-\n");
	//test 2 sprawdza eHexStringToUInt dla najkrotszego poprawnego stringa
	eResult = eHexStringToUInt( acTestShortCorrect, &uiTestResult );
	if ( eResult == OK && uiTestResult == 0x1 )
	{
		printf("Ok\n");
	}
	else
	{
		printf("Error\n");
	}
	
	printf("Test 3-\n");
	//test 3 sprawdza eHexStringToUInt dla stringa nie zaczynajacego sie od 0
	eResult = eHexStringToUInt( acTestStartsWith1, &uiTestResult );
	if ( eResult == ERROR )
	{
		printf("Ok\n");
	}
	else
	{
		printf("Error\n");
	}
	
	printf("Test 4-\n");
	//test 4 sprawdza eHexStringToUInt dla stringa nie majacego x jako drugi znak
	eResult = eHexStringToUInt( acTestSecondIsB, &uiTestResult );
	if ( eResult == ERROR )
	{
		printf("Ok\n");
	}
	else
	{
		printf("Error\n");
	}
	
	printf("Test 5-\n");
	//test 5 sprawdza eHexStringToUInt dla za krotkiego stringa
	eResult = eHexStringToUInt( acTestTooShort, &uiTestResult );
	if ( eResult == ERROR )
	{
		printf("Ok\n");
	}
	else
	{
		printf("Error\n");
	}
	
	printf("Test 6-\n");
	//test 6 sprawdza eHexStringToUInt dla za dlogiego stringa
	eResult = eHexStringToUInt( actestTooLong, &uiTestResult );
	if ( eResult == ERROR )
	{
		printf("Ok\n");
	}
	else
	{
		printf("Error\n");
	}
	
}

void AppendUIntToString (unsigned int uiValue, char pcDestinationStr[])
{
	unsigned char ucEndPointer;
	
	for ( ucEndPointer=0; pcDestinationStr[ucEndPointer] != NULL; ucEndPointer++ ) {}
	UIntToHexStr(uiValue, pcDestinationStr+ucEndPointer);
}

void TestOf_AppendUIntToString()
{
	char acTestDestination[]="abcd";
	unsigned int uiTestSource = 0x12AC;
	char acTestResult[]="abcd0x12AC";
	enum CompResult eCompResult;
	AppendUIntToString( uiTestSource, acTestDestination );
	printf("AppendUIntToString\n\n");
	
	printf("Test 1-\n");
	//Test 1 sprawdza czy poprawnie wydluzono stringa
	eCompResult = eCompareString(acTestDestination, acTestResult );
	if ( eCompResult == EQUAL )
	{
		printf("Ok\n");
	}
	else
	{
		printf("Error\n");
	}
	
}

int main()
{
	TestOf_AppendUIntToString();
}
