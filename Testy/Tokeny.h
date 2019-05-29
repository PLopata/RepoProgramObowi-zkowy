typedef enum KeywordCode {LD, ST, RST} KeyCode;

unsigned char ucFindTokensInString(char *pcString);
enum Result eStringToKeyword (char pcStr[], enum KeywordCode *peKeywordCode);
void DecodeTokens (void);
void DecodeMsg( char *pcString );
