#include "BigInt.h"

//default constructor: set to 0
BigInt::BigInt()
{
	sign = positive;
	Digits.push_back('0');
	numDigits = 1;
}

//constructor: intilize with int
BigInt::BigInt(int n)
{

}

//convert stored number to a string for display
std::string BigInt::ToString() 
{
	std::string s = "";
	if (IsNegative())
		s += "-";
	for (int i = 0; i < NumDigits(); i++)
		s += char(GetDigit(i));
	return s;
}

//display number as a string
void BigInt::Print() 
{
	std::cout << ToString() << std::endl;
}

bool BigInt::IsNegative()
{
	if (sign == positive)
		return false;
	else
		return true;
}

bool BigInt::Equal(BigInt & rhs)
{
	//check for negatives and size first
	if (NumDigits() != rhs.NumDigits() ||
		IsNegative() != rhs.IsNegative())
		return false;
	//now loop through our two numbers and check every digit
	for (int i = 0; i < NumDigits() - 1; i++)
		if (GetDigit(i) != rhs.GetDigit(i))
			return false;
	//if we get here they are the same
	return true;
}

bool  BigInt::LessThan(BigInt & rhs)
{
	//if the number is negative it is automatically less than
	if (IsNegative() != rhs.IsNegative())
		return IsNegative();
	//now look at number size
	if (NumDigits() != rhs.NumDigits())
		return (NumDigits() < rhs.NumDigits() && !IsNegative() ||
			NumDigits() > rhs.NumDigits() && IsNegative());
	//if we get here we need to loop through the two numbers
	for (int i = 0; i < NumDigits(); i++)
	{
		if (GetDigit(i) < rhs.GetDigit(i) && !IsNegative())
			return true;
		else if (GetDigit(i) > rhs.GetDigit(i) && IsNegative())
			return true;
	}
	return false; // if we get here then it is not less than
}

//not finished
const BigInt & BigInt::operator+= (const BigInt & rhs)
{
	int carry = 0;
	int len = NumDigits();
	if (len < rhs.NumDigits())
		len = rhs.NumDigits();
	for (int i = len - 1; i >= 0; i--)
	{
		int sum = GetDigit(i) + rhs.GetDigit(i);
		Digits[i] = char(sum % 10);
		carry = sum / 10;
		if (carry != 0) 
		{
			if (i == 0)
				Digits.insert(Digits.begin(), char(carry)); 
			else
				Digits.insert(Digits.end() - (i - 1), char(carry)); //insert the carry in the next slot to be added the next round 
		}
	}
}

