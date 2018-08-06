#include <iostream>
#include <cmath>
#include <random>
#include <string>
#include <algorithm>
#include <ctime>
#include <Windows.h>
#include <vector>
#include "InfInt.h"

std::string dictionary = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz1234567890\'\"!@#$%^&*()-+<>?:;/ ";

struct KeyHolder
{
	InfInt publicKey[2];
	InfInt privateKey[2];
};

InfInt customPow(InfInt base, InfInt Power)
{
	InfInt result = base;
	for (InfInt i = 0; i < Power - 1; i++)
		result *= base;
	//std::cout << "result in customPow: " << result << std::endl;
	return result;
}

InfInt gcd(InfInt n1, InfInt n2) //euclids algorithim
{
	if (n2 != 0)
		return gcd(n2, n1 % n2);
	else
		return n1;
}

void extendedGcd(InfInt n1, InfInt n2, InfInt values[])
{
	InfInt x = 0; InfInt v = 0; InfInt q = 0; InfInt r = 0; InfInt m = 0; InfInt n = 0;
	InfInt y = 1; InfInt u = 1;
	while (n1 != 0)
	{
		q = n2 / n1;
		r = n2 % n1;
		m = x - u * q;
		n = y - v * q;
		n2 = n1; n1 = r; x = u; y = v; u = m; v = n;
	}
	values[0] = n2;
	values[1] = x;
	values[2] = y;
	return;
}

bool isPrime(InfInt n)
{
	bool prime = true;
	for (InfInt i = 2; i <= n / 2; i++)
	{
		if (n % i == 0)
		{
			prime = false;
			break;
		}
	}
	return prime;
}

InfInt getRandomPrime() //TODO: fix this function
{
	bool found = false;
	InfInt prime = 0;
	//std::srand(std::time(0));
	while (!found)
	{
		prime = std::rand() % 100;
		if (isPrime(prime))
			found = true;
	}
	std::cout << "random number found: " << prime << std::endl;
	return prime;
}

KeyHolder generateKeys()
{
	KeyHolder keys;

	//to get started we need to find a modulus both keys will use
	InfInt p = 31;
	InfInt q = 53;
	InfInt n = p * q; //this is our modulus that both keys will use
	InfInt totient = (p - 1) * (q - 1); 
	keys.publicKey[1] = n; //set the modulus for both keys
	keys.privateKey[1] = n;

	//calculate public key
	InfInt e = 0;
	std::srand(std::time(0));
	for (InfInt i = 1; i < totient; i++)
	{
		if (gcd(i, totient) == 1)
		{
			e = i; 
			int pick = std::rand() % 3; //1/3 chance of picking the current value
			//std::cout << pick << std::endl;
			if (e != 1 && pick == 2)
				break;
		}
	}
	keys.publicKey[0] = e;

	//calculate private key
	InfInt values[3];
	extendedGcd(e, totient, values);

	if (values[1] < 0)
		keys.privateKey[0] = totient + values[1];
	else
		keys.privateKey[0] = values[1];

	return keys;
}

std::vector<InfInt> encrypt(std::string message, InfInt n, InfInt e)
{
	std::vector<InfInt> encodedText;
	for (int i = 0; i < message.length(); i++) //C = M^e(mod N)
	{
		int encoded = dictionary.find(message[i]);
		std::cout << "encoded value: " << encoded << std::endl;
		InfInt num = customPow(encoded, e); 
		num = num % n;
		encodedText.push_back(num);
	}
	return encodedText;
}

std::string decrypt(std::vector<InfInt> encoding, InfInt n, InfInt d)
{
	std::cout << "------------------------inside decrypt-------------------------\n";
	std::string message = "";
	for (int i = 0; i < encoding.size(); i++) //M = C^d(mod N)
	{
		InfInt big = customPow(encoding[i], d);
		big = big % n;
		std::cout << "decrypted value: " << big << std::endl;
		char c = dictionary[big.toInt()];
		message += c; 
	}
	return message;
}

int main()
{
	//before we ask for message we need to generate keys
	KeyHolder keys = generateKeys();
	std::cout << "Keys generated.\n";
	std::cout << "Public: " << keys.publicKey[0] << std::endl;
	std::cout << "Private: " << keys.privateKey[0] << std::endl;
	std::cout << "Modulus: " << keys.publicKey[1] << std::endl;

	std::string message;
	std::cout << "Enter a message to encrypt: \n";
	std::getline(std::cin, message);

	std::vector<InfInt> encodedCipher = encrypt(message, keys.publicKey[1], keys.publicKey[0]);
	for (int i = 0; i < encodedCipher.size(); i++)
		std::cout << "encrypted value: " << encodedCipher[i] << std::endl;

	message = decrypt(encodedCipher, keys.privateKey[1], keys.privateKey[0]);
	std::cout << "decoded message: " << message << std::endl;

	return 0;
}