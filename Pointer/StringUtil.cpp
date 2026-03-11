#include "StringUtil.h"

int IndexOf(char* String, int Size, char FindCharacter)
{
	for (int i = 0; i < Size; ++i)
	{
		if (String[i] == FindCharacter)
		{
			return i;
		}
	}

	return -1;
}

void Replace(char* String, int Size, char FindCharacter, char ReplaceCharacter)
{
	for (int i = 0; i < Size; ++i)
	{
		if (String[i] == FindCharacter)
		{
			String[i] = ReplaceCharacter;
		}
	}
}
int Length(char* String, int Size)
{
	for (int i = 0; i < Size; ++i)
	{
		if (String[i] == 0)
		{
			return i;
		}
	}

	return Size;
}