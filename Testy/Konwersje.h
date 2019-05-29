enum Result {ERROR, OK};

void UIntToHexStr (unsigned int uiValue, char pcStr[]);
enum Result eHexStringToUInt(char pcStr[], unsigned int *puiValue);
void AppendUIntToString (unsigned int uiValue, char pcDestinationStr[]);
