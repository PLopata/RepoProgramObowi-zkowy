#include <LPC21xx.H>

#define MAX_TOKEN_NR 3

typedef union TokenValue
{
	enum KeywordCode     eKeyword;
	unsigned int         uiNumber;
	char *               pcString;
};


typedef enum TokenType {KEYWORD, NUMBER, STRING};

typedef struct Token
{
	enum TokenType     eType;
	union TokenValue   uValue;
};

struct Token asToken[MAX_TOKEN_NR];
