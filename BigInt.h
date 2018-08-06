#pragma once
#include <string>
#include <vector>
#include <iostream>

class BigInt
{
public:
	BigInt();
	BigInt(int); 
	const BigInt & operator += (const BigInt &);
	const BigInt & operator -= (const BigInt &);
	const BigInt & operator *= (const BigInt &);
	const BigInt & operator *= (int num);
	int ToInt();
	double ToDouble();
	std::string ToString();
	bool Equal(BigInt & toCheck);
	bool LessThan(BigInt & rhs);
	void Print();
	void generate(); //generate a random big number
	void generatePrime(); //generate a random big prime
private:
	bool IsNegative();
	int NumDigits() { return numDigits; };
	int GetDigit(int i) const;
	void AddSigDigit(int value); //expand the number
	enum Sign{positive, negative};
	Sign sign; //is number positive or negative
	std::vector<char> Digits; //holds the number
	int numDigits; //# of digits in a number
};