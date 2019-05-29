#include <LPC21xx.H>

#define NULL 0
#define MAX_TOKEN_NR 3
#define MAX_KEYWORD_NR 3
#define MAX_KEYWORD_STRING_LTH 10

/*------------------------------------------------------------*/

typedef enum KeywordCode {LD, ST, RST};

enum Result {ERROR, OK} eResult;

typedef enum TokenType {KEYWORD, NUMBER, STRING};

typedef union TokenValue
{
	enum KeywordCode     eKeyword;
	unsigned int         uiNumber;
	char *               pcString;
};

typedef struct Token
{
	enum TokenType       eType;
	union TokenValue     uValue;
};

struct Token asToken[MAX_TOKEN_NR];

typedef struct Keyword
{
	enum KeywordCode     eCode;
	char                 cString[MAX_KEYWORD_STRING_LTH + 1];
};

struct Keyword asKeywordList[MAX_KEYWORD_NR] = 
{ 
	{RST, "reset"}, 
	{LD, "load"}, 
	{ST, "store"} 
};

/*------------------------------------------------------------*/

enum CompResult { DIFFERENT, EQUAL };

enum CompResult eCompareString(char pcStr1[], char pcStr2[])
{
	unsigned char ucCharacterCounter;
	
	for(ucCharacterCounter=0; ( pcStr1[ucCharacterCounter]!=NULL ) || ( pcStr2[ucCharacterCounter]!=NULL ); ucCharacterCounter++)
	{
		if(pcStr1[ucCharacterCounter] != pcStr2[ucCharacterCounter])
		{
			return DIFFERENT;
		}
	}
	return EQUAL;
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

/*------------------------------------------------------------*/

unsigned char ucFindTokensInString(char *pcString)
{
	unsigned char ucCharCounter;
	unsigned char ucCurrentCharacter;
	unsigned char ucNumberOfTokens ;
	enum State { DELIMITER, TOKEN } eState;
	
	eState = DELIMITER;
	ucNumberOfTokens = 0;
	for ( ucCharCounter = 0; ; ucCharCounter++ )
	{
		ucCurrentCharacter = pcString[ucCharCounter];
		switch ( eState )
		{
			case DELIMITER:
			{
				if ( ucCurrentCharacter == NULL ) 
				{
					return ucNumberOfTokens;
				}
				else if ( ucNumberOfTokens == MAX_TOKEN_NR )
				{
					return ucNumberOfTokens;
				}
				else if ( ucCurrentCharacter != ' ' )
				{
					eState = TOKEN;
					asToken[ucNumberOfTokens].uValue.pcString = &pcString[ucCharCounter];
					ucNumberOfTokens++;
				}
				else 
				{
					eState = DELIMITER;
				}
				break;
			}
			
			case TOKEN:
			{
				if ( ucCurrentCharacter == NULL ) 
				{	
					return ucNumberOfTokens;
				}
				else if ( ucCurrentCharacter == ' ' )
				{
					eState = DELIMITER;
				}
				else 
				{
					eState = TOKEN;
				}
				break;
			}
		}
	}
}

enum Result eStringToKeyword (char pcStr[], enum KeywordCode *peKeywordCode)
{
	unsigned char ucKeywordCounter;
	
	for ( ucKeywordCounter=0; ucKeywordCounter < MAX_KEYWORD_NR; ucKeywordCounter++ )
	{
		if ( eCompareString( pcStr, asKeywordList[ucKeywordCounter].cString ) == EQUAL )
		{
			*peKeywordCode = asKeywordList[ucKeywordCounter].eCode;
			return OK;
		}
	}
	return ERROR;
}

void DecodeTokens (void)
{
	unsigned char ucTokenNr;
	struct Token *TokenValue;
	
	for ( ucTokenNr=0; ucTokenNr < MAX_TOKEN_NR; ucTokenNr++ )
	{
		TokenValue = &asToken[ucTokenNr];
		
		if ( eStringToKeyword( TokenValue->uValue.pcString, &TokenValue->uValue.eKeyword ) == OK  )
		{
			TokenValue->eType = KEYWORD;
		}
		else if ( eHexStringToUInt ( TokenValue->uValue.pcString, &TokenValue->uValue.uiNumber ) == OK )
		{
			TokenValue->eType = NUMBER;
		}
		else 
		{	
			TokenValue->eType = STRING;
		}
	}
}

void DecodeMsg( char *pcString )
{
	ucFindTokensInString( pcString );
	ReplaceCharactersInString( pcString, ' ', NULL);
	DecodeTokens();
}

char aucInput[] = "  reset 0xA2C2 quickly  ";
unsigned char ucNumberOfTokens;

int main()
{
	DecodeMsg( aucInput );
}
