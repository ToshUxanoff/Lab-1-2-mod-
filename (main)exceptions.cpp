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
	int step = 0;
	int x = 0;
	while (data[len + start])
	{
		 if ((data[len+start] == '-' || data[len+start] == '0') && len == 0)
		{
			start++;
		}
		else
		{
			len++;
		}
		
	}
		for (int i = start; i < len+start; i++)
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
	
	if (result >= 2147483648)
	{
		throw Overflow();
	}
	return result;
}
float floatFromString(const char* data)
{
	int start = 0;
	int len = 0;
	int result = 0;
	int step = 0;
	int x = 0;

	while (data[len+start])
	{
		if (len == 0 && (data[len + start] == '0'|| data[len+start] == '-'))
		{
			start++;
		}
		else if (data[len + start] == '.' || data[len + start] == ',')
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
	if (result >= 2147483648)
	{
		throw Overflow();
	}
	return 0;
}
int _tmain(int argc, _TCHAR* argv[])
{
	boolFromString("true");
	try
	{
		boolFromString("truuu");
	}
	catch (ErrorSymbol & exc)
	{
		std::cout << "Uncorrect input (bool)!" << std::endl;
	}	
	intFromString("-214748364");
	intFromString("2147483646");
	try
	{
		intFromString("00435324832235");
	}
	catch (Overflow & exc)
	{
		std::cout <<"Overflow (int)!" << std::endl;
	}
	try
	{
		intFromString("0xcdd");
	}
	catch (ErrorSymbol & exc)
	{
		std::cout << "Uncorrect input (int)!" << std::endl;
	}
	floatFromString("-00,214748345649");
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
		floatFromString("0x.32rewg");
	}
	catch (ErrorSymbol & exc)
	{
		std::cout << "Uncorrect input (float)!";
	}
	system("pause");
	return 0;
}
