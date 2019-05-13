#include <LPC21xx.H>

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

enum Result {ERROR, OK} eResult;

enum Result eHexStringToUInt(char pcStr[], unsigned int *puiValue)
{
	unsigned char ucCharCounter;
	unsigned char ucCurrentCharacter;
	
	if ( (pcStr[0] != '0') || (pcStr[1] != 'x') || (pcStr[2] == NULL) || (pcStr[6] != NULL) )
	{
		return ERROR;
	}
	
	for ( ucCharCounter = 2; ucCharCounter <= 6 ; ucCharCounter++ )
	{
		ucCurrentCharacter = pcStr[ucCharCounter];
		
		if ( ucCurrentCharacter == NULL ) 
		{
			return OK;
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
}


void AppendUIntToString (unsigned int uiValue, char pcDestinationStr[])
{
	unsigned char ucEndPointer;
	
	for ( ucEndPointer=0; pcDestinationStr[ucEndPointer] != NULL; ucEndPointer++ ) {}
	UIntToHexStr(uiValue, pcDestinationStr+ucEndPointer);
}

char pcStr[] = "0x12AC";
unsigned int uiValue;

int main()
{
	eResult = eHexStringToUInt( pcStr, &uiValue );
}
