#include "stdafx.h"
#include "iostream"
#include "CastException.h"
#include "ErrorSymbol.h"
#include "Overflow.h"
bool boolFromString(const char* data)
{
	if (strcmp(data, "false") == 0 || strcmp(data, "0") == 0)
	{
		return false;
	}
	else if (strcmp(data, "true") == 0 || strcmp(data, "1") == 0)
	{
		return true;
	}
	else
	{
		throw ErrorSymbol();
	}
}
int intFromString(const char* data)
{
	int start = 0;
	int len = 0;
	int result = 0;
	int x = 0;
	bool minus = false;
	if (data[0] == '-')
	{
		minus = true;
		start++;
	}
	while (data[len + start] != '\0')
	{
		if (len == 0 && data[len + start] == '0')
		{
			start++;
		}
		else
		{
			len++;
		}
	}
	for (int i = 0; i < len; i++) 
	{
		if (data[i + start] >= 48 && data[i + start] <= 57) 
		{
			x = (data[i + start] - 48) * (pow(10, (len - i - 1)));
			result += x;
		}
		else
		{
			throw ErrorSymbol();
		}
	}	
	if (minus == true)
	{
		result *= -1;
	}
	if ((minus == true && result >= 0)||(minus == false && result < 0))
	{
		throw Overflow();
	}
	return result;
}
float floatFromString(const char* data)
{
	int start = 0;
	int len = 0;
	float result = 0;
	int step = 0;
	int x = 0;
	bool minus = false;
	while (data[len+start])
	{
		if (len == 0 && data[len + start] == '0')
		{
			start++;
		}
		else if (len == 0 && data[len + start] == '-')
		{
			minus = true;
			start++;
		}
		else if (data[len + start] == ',' || data[len + start] == '.')
		{
			break;
		}
		else 
		{
			len++;
		}
	}
	for (int i = start; i < len + start; i++)
	{
			if (data[i] >= 48 && data[i] <= 57)	
			{
				x = data[i] - 48;
				result += (pow(10, (len - step - 1))*x);
				step++;
			}
			else
			{
				throw ErrorSymbol();
			}
	}
	for (int i = 1; data[len + start + i]; i++)
	{
		if (data[len + start + i] >= 48 && data[len + start + i] <= 57)
		{
			x = data[len + start + i] - 48;
			result += (1 / pow(10, i))*x;
		}
		else
		{
			throw ErrorSymbol();
		}
	}
	if (result >= 2147483648)
	{
		throw Overflow();
	}
	if (minus == true)
	{
		return -result;
	}
	return result;
}
int _tmain(int argc, _TCHAR* argv[])
{
	boolFromString("true");
	boolFromString("false");
	boolFromString("1");
	try
	{
		boolFromString("truuu");
	}
	catch (ErrorSymbol & exc)
	{
		std::cout << "Uncorrect input (bool)!" << std::endl;
	}	
	std::cout << intFromString("-214748364") << std::endl;
	std::cout << intFromString("020214846") << std::endl;
	try
	{
		std::cout << intFromString("00415623534432");
	}
	catch (Overflow & exc)
	{
		std::cout <<"Overflow (int)!" << std::endl;
	}
	try
	{
		intFromString("034.5");
	}
	catch (ErrorSymbol & exc)
	{
		std::cout << "Uncorrect input (int)!" << std::endl;
	}
	std::cout << floatFromString("-11245.6623") << std::endl;
	try
	{
		floatFromString("-0214748345648");
	}
	catch (Overflow &exc)
	{
		std::cout << "Overflow(float)!" << std::endl;
	}
	try
	{
		floatFromString("10.324x5");
	}
	catch (ErrorSymbol & exc)
	{
		std::cout << "Uncorrect input (float)!";
	}
	system("pause");
	return 0;
}
