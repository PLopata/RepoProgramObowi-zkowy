#include <stdio.h>

#define NULL 0
#define MAX_TOKEN_NR 3
#define MAX_KEYWORD_NR 3
#define MAX_KEYWORD_STRING_LTH 10

enum Result {ERROR, OK};

enum CompResult {DIFFERENT, EQUAL};

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

/*-----------------------------------------------------------------*/

typedef enum KeywordCode {LD, ST, RST} KeyCode;

typedef enum TokenType {KEYWORD, NUMBER, STRING} TokenType;

typedef union TokenValue
{
	enum KeywordCode     eKeyword;
	unsigned int         uiNumber;
	char *               pcString;
}TokenValue;

typedef struct Token
{
	enum TokenType       eType;
	union TokenValue     uValue;
}Token;

struct Token asToken[MAX_TOKEN_NR];

typedef struct Keyword
{
	enum KeywordCode     eCode;
	char                 cString[MAX_KEYWORD_STRING_LTH + 1];
}Keyword;

struct Keyword asKeywordList[MAX_KEYWORD_NR] = 
{ 
	{RST, "reset"}, 
	{LD, "load"}, 
	{ST, "store"} 
};

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

void TestOf_ucFindTokensInString()
{
	char acSource1Token[]="Token1";
	char acSource3Tokens[]="Token1 token2 token3";
	char acSource4Tokens[]="Token1 token2 token3 token4";
	char acSourceEmptyString[]="   ";
	char acFirstDelimiter[]="  Token1 token2";
	char ac3DelimitersBetweenTokens[]="Token1   Token2";
	unsigned char ucNumberOfTokens;
	enum CompResult eCompResult;
	printf("ucFindTokensInString\n\n");
	
	printf("Test 1-\n");
	//test 1 sprawdza czy poprawnie znajduje token
	ucNumberOfTokens = ucFindTokensInString( acSource1Token );
	eCompResult = eCompareString( acSource1Token, asToken[0].uValue.pcString );
	if ( eCompResult == EQUAL && ucNumberOfTokens == 1 )
	{
		printf("Ok\n");
	}
	else 
	{
		printf("Error\n");
	}
	
	printf("Test 2-\n");
	//test 2 sprawdza czy poprawnie znajduje kilka tokenow
	ucNumberOfTokens = ucFindTokensInString( acSource3Tokens );
	eCompResult = eCompareString( acSource3Tokens, asToken[0].uValue.pcString );
	if ( eCompResult == EQUAL && ucNumberOfTokens == 3 )
	{
		printf("Ok\n");
	}
	else 
	{
		printf("Error\n");
	}
	
	printf("Test 3-\n");
	//test 3 sprawdza czy nie wpisuje wiecej niz 3 tokenow
	ucNumberOfTokens = ucFindTokensInString( acSource4Tokens );
	eCompResult = eCompareString( acSource4Tokens, asToken[0].uValue.pcString );
	if ( eCompResult == EQUAL && ucNumberOfTokens == 3 )
	{
		printf("Ok\n");
	}
	else 
	{
		printf("Error\n");
	}
	
	printf("Test 4-\n");
	//test 4 sprawdza czy nie wpisuje pustego stringa jako token
	ucNumberOfTokens = ucFindTokensInString( acSourceEmptyString );
	if ( ucNumberOfTokens == 0 )
	{
		printf("Ok\n");
	}
	else 
	{
		printf("Error\n");
	}
	
	printf("Test 5-\n");
	//test 5 sprawdza czy dziala jak pierwszymi znakami sa delimitery
	ucNumberOfTokens = ucFindTokensInString( acFirstDelimiter );
	eCompResult = eCompareString( acFirstDelimiter+2, asToken[0].uValue.pcString );
	if ( eCompResult == EQUAL && ucNumberOfTokens == 2 )
	{
		printf("Ok\n");
	}
	else 
	{
		printf("Error\n");
	}
	
	printf("Test 6-\n");
	//test 6 sprawdza czy dziala jak miedzy tokenami jest wiecej niz jeden delimiter
	ucNumberOfTokens = ucFindTokensInString( ac3DelimitersBetweenTokens );
	eCompResult = eCompareString( ac3DelimitersBetweenTokens, asToken[0].uValue.pcString );
	if ( eCompResult == EQUAL && ucNumberOfTokens == 2 )
	{
		printf("Ok\n");
	}
	else 
	{
		printf("Error\n");
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

void TestOf_eStringToKeyword()
{
	char acCorrectReset[]="reset";
	char acCorrectLoad[]="load";
	char acCorrectStore[]="store";
	char acIncorrectKeyword[]="lOad";
	char acKeywordWithDelimiter[]=" reset ";
	enum Result eResult;
	enum KeywordCode eKeyCode;
	printf("eStringToKeyword\n\n");
	
	printf("Test 1-\n");
	//test 1 sprawdza czy dobrze wpisuje keyword reset
	eResult = eStringToKeyword(acCorrectReset, &eKeyCode );
	if ( eResult == OK && eKeyCode == RST )
	{
		printf("Ok\n");
	}
	else
	{
		printf("Error\n");
	}
	
	printf("Test 2-\n");
	//test 2 sprawdza czy dobrze wpisuje keyword load
	eResult = eStringToKeyword(acCorrectLoad, &eKeyCode );
	if ( eResult == OK && eKeyCode == LD )
	{
		printf("Ok\n");
	}
	else
	{
		printf("Error\n");
	}
	
	printf("Test 3-\n");
	//test 3 sprawdza czy dobrze wpisuje keyword store
	eResult = eStringToKeyword(acCorrectStore, &eKeyCode );
	if ( eResult == OK && eKeyCode == ST )
	{
		printf("Ok\n");
	}
	else
	{
		printf("Error\n");
	}
	
	printf("Test 4-\n");
	//test 4 sprawdza czy dobrze odnajduje keyword
	eResult = eStringToKeyword(acIncorrectKeyword, &eKeyCode );
	if ( eResult == ERROR )
	{
		printf("Ok\n");
	}
	else
	{
		printf("Error\n");
	}
	
	printf("Test 5-\n");
	//test 5 sprawdza czy dziala z delimiterami
	eResult = eStringToKeyword(acKeywordWithDelimiter, &eKeyCode );
	if ( eResult == ERROR )
	{
		printf("Ok\n");
	}
	else
	{
		printf("Error\n");
	}
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

void TestOf_DecodeTokens()
{
	char acCorrectKeywordNumberString[]="reset 0x12AC  string";
	char acIncorrectNumbers[]="1x12AC 0b12AC 0x";
	
	printf("DecodeTokens\n\n");
	
	printf("Test 1-\n");
	//test 1 sprawdza czy poprawnie dekoduje keyword number i string
	ucFindTokensInString( acCorrectKeywordNumberString );
	ReplaceCharactersInString(acCorrectKeywordNumberString, ' ', NULL);
	DecodeTokens();
	if ( asToken[0].uValue.eKeyword == RST && asToken[0].eType == KEYWORD && asToken[1].uValue.uiNumber == 0x12AC && asToken[1].eType == NUMBER  && asToken[2].eType == STRING )
	{
		printf("Ok\n");
	}
	else
	{
		printf("Error\n");
	}
	
	printf("Test 2-\n");
	//test 2 sprawdza czy liczby w zlym formacie traktuje jako string
	ucFindTokensInString( acIncorrectNumbers );
	ReplaceCharactersInString(acIncorrectNumbers, ' ', NULL);
	DecodeTokens();
	if ( asToken[0].eType == STRING && asToken[1].eType == STRING  && asToken[2].eType == STRING )
	{
		printf("Ok\n");
	}
	else
	{
		printf("Error\n");
	}
}

void DecodeMsg( char *pcString )
{
	ucFindTokensInString( pcString );
	ReplaceCharactersInString( pcString, ' ', NULL);
	DecodeTokens();
}

void TestOf_DecodeMsg()
{
	char acTestMessage[]="store 0x12AC quickly";
	
	printf("DecodeMsg\n\n");
	
	printf("Test 1-\n");
	//test 1 sprawdza czy poprawnie dekoduje caly komunikat
	DecodeMsg(acTestMessage);
	if ( asToken[0].eType == KEYWORD && asToken[0].uValue.eKeyword==ST && asToken[1].eType == NUMBER && asToken[1].uValue.uiNumber == 0x12AC && asToken[2].eType == STRING )
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
	TestOf_DecodeMsg();
}
