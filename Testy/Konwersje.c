#include "Konwersje.h"

#define NULL 0

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

void AppendUIntToString (unsigned int uiValue, char pcDestinationStr[])
{
	unsigned char ucEndPointer;
	
	for ( ucEndPointer=0; pcDestinationStr[ucEndPointer] != NULL; ucEndPointer++ ) {}
	UIntToHexStr(uiValue, pcDestinationStr+ucEndPointer);
}
