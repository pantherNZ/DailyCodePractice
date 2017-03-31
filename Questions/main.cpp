#include <iostream>
#include <cstdlib>
#include <time.h>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <functional>
#include <string.h>
#include <math.h>
#include <unordered_set>

struct IndexFrequency
{
	int iValue;
	int iFrequency;
};

std::vector<int> CreateRandomVector(unsigned int _uiCount, unsigned int _uiMax)
{
	std::vector<int> vecNumbers;

	std::cout << "\nRandom Vector: ";

	for (unsigned int i = 0; i < _uiCount; ++i)
	{
		vecNumbers.push_back(rand() % _uiMax);
		std::cout << vecNumbers.back() << " ";
	}

	return(vecNumbers);
}

void FrequentInt()
{
	// Setup
	std::vector<int> vecArray = CreateRandomVector(30, 15);

	// Algorithm
	std::unordered_map<int, int> mapFrequencies;
	int iHighestFreq = 0;

	for (unsigned int i : vecArray)
	{
		int iValue = 1;
		const auto found = mapFrequencies.find( vecArray[ i ] );

		if( found != mapFrequencies.end() )
			iValue = found->second + 1;
		
		mapFrequencies[ vecArray[ i ] ] = iValue;

		if( iValue > iHighestFreq )
			iHighestFreq = iValue;
	}

	std::cout << "\nHighest Frequency Number = " << iHighestFreq << std::endl;
}

void IntegerPairs()
{
	// Setup
	int iMax = 10;
	std::vector<int> vecArray = CreateRandomVector(10, 15);
	std::cout << "\n";

	// Algorithm
	std::unordered_map<int, int> set;

	for( int i = 0; i < vecArray.size(); ++i )
	{	
		set[ vecArray[ i ] ] = i;
		const auto found = set.find( iMax - vecArray[i] );
		if( found != set.end() && found->second != i )
		{
			std::cout << "Pair found: " << vecArray[ i ] << " + " << iMax - vecArray[ i ] << std::endl;
		}
	}
}

void RotatedArray()
{
	int iArray[7] = { 1,2,3,5,6,7,8 };
	int iArray2[7] = { 5,6,7,8,1,2,3 };

	int iPtr = 0;

	for (int i = 0; i < 7; ++i)
	{
		if (iArray[0] == iArray2[i])
		{
			iPtr = i;
			break;
		}
	}

	bool bRotated = true;

	for(int i : iArray)
	{
		if (i != iArray2[iPtr])
		{
			bRotated = false;
			break;
		}

		iPtr = (iPtr < 6 ? iPtr + 1 : 0);
	}

	std::cout << (bRotated ? "\nRotated Array\n" : "\nNot Rotated\n");
}

void Fibbonaci(int _iNumbers)
{
	int iPrevious = 0;
	int iTotal = 1;

	std::cout << "\nFib 0 = 0\n";
	std::cout << "Fib 1 = 1\n";

	for (int i = 2; i < _iNumbers; ++i)
	{
		int iTemp = iTotal;
		iTotal += iPrevious;
		iPrevious = iTemp;

		std::cout << "Fib " << i << " = " << iTotal << std::endl;
	}
}

int Fibbonaci_Recursive(int _iNumber)
{
	if (_iNumber <= 1)
	{
		return(_iNumber);
	}
		
	return(Fibbonaci_Recursive(_iNumber - 1) + Fibbonaci_Recursive(_iNumber - 2));
}

void Fibbonaci_Dynamic(int _iNumber)
{
	int* pArray = new int[_iNumber];

	pArray[0] = 0;
	pArray[1] = 1;

	std::cout << "\nFib 0 = 0\n";
	std::cout << "Fib 1 = 1\n";

	for (int i = 2; i <= _iNumber; ++i)
	{
		pArray[i] = pArray[i - 1] + pArray[i - 2];
		std::cout << "Fib " << i << " = " << pArray[i] << std::endl;
	}
}

void UniqueInteger()
{
	// Setup
	std::vector<int> vecArray = CreateRandomVector(10, 20);

	// Algorithm
	std::unordered_map<int, bool> map;

	for (int i : vecArray)
	{
		if( map.find( i ) != map.end() )
			map[ i ] = true;
		else
			map[ i ] = false;
	}

	for (int i : vecArray)
	{
		if (!map[i])
		{
			std::cout << "\nFirst unique integer = " << i << std::endl;
			return;
		}
	}

	std::cout << "\nNo unique integers" << std::endl;
}

void CommonElements()
{
	// Setup
	std::vector<int> vecArray = CreateRandomVector(10, 20);
	std::vector<int> vecArray2 = CreateRandomVector(10, 20);

	std::unordered_map<int, int> mapTable;

	for (int i : vecArray)
	{
		mapTable[i] = 1;
	}

	std::cout << "\nCommon Elements: ";

	for (int i : vecArray2)
	{
		if (mapTable.find(i) != mapTable.end())
		{
			std::cout << i << " ";
		}
	}

	std::cout << std::endl;
}

bool BinarySearch_Recur(std::vector<int> _vector, const int _kiGoal, int& _riIndexResult)
{
	if (_vector.size() == 0) return(false);
	int iMidIndex = int(_vector.size() / 2);

	if (_kiGoal == _vector[iMidIndex])
	{
		_riIndexResult += iMidIndex;
		return(true);
	}
	else if (_vector.size() == 1)
	{
		return(false);
	}

	if (_kiGoal > _vector[iMidIndex])
	{
		std::vector<int> newVec(_vector.begin() + iMidIndex, _vector.end());
		_riIndexResult += iMidIndex;

		return(BinarySearch_Recur(newVec, _kiGoal, _riIndexResult));
	}

	if (_kiGoal < _vector[iMidIndex])
	{
		std::vector<int> newVec(_vector.begin(), _vector.end() - iMidIndex);

		return(BinarySearch_Recur(newVec, _kiGoal, _riIndexResult));
	}

	return(false);
}

bool BinarySearch(std::vector<int> _vector, const int _kiGoal, int& _riIndexResult)
{
	std::sort(_vector.begin(), _vector.end());

	return(BinarySearch_Recur(_vector, _kiGoal, _riIndexResult));
}

void Primes(unsigned int _uiPrimes)
{
	std::vector<unsigned long long> vecPrimes;
	vecPrimes.push_back(2);
	std::cout << "\nPrimes: 2 ";

	int iCounter = 3;

	while(vecPrimes.size() < _uiPrimes)
	{
		bool bPrime = true;
		double dMax = std::sqrt(iCounter);

		for (unsigned long long i : vecPrimes)
		{
			if (iCounter % i == 0)
			{
				bPrime = false;
				break;
			}

			if (i > dMax)
			{
				break;
			}
		}

		if (bPrime)
		{
			vecPrimes.push_back(iCounter);
			std::cout << iCounter << " ";
		}

		++iCounter;
	}

	std::cout << std::endl;
}

void BinaryForm(int _iValue)
{
	size_t uiBytes = sizeof(_iValue);
	char* pRaw = ((char*)(&_iValue));

	std::cout << "\nBinaryForm: ";

	for (size_t byte = 0; byte < uiBytes; byte++)
	{
		for (size_t bit = 0; bit < CHAR_BIT; bit++) 
		{
			std::cout << (((pRaw[byte]) >> bit) & 1);
		}
	}

	std::cout << std::endl;
}

bool ParseInt(std::string _str, int& _riVal)
{
	if (_str.length() == 0)
	{
		std::cout << "\nPaseInt: String failed to convert" << std::endl;
		return(false);
	}

	bool bNegative = _str[0] == '-';
	unsigned int uiCounter = 0;
	_riVal = 0;

	if (_str[0] == '-' || _str[0] == '+')
	{
		uiCounter++;
	}

	for (; uiCounter < _str.length(); uiCounter++)
	{
		if (_str[uiCounter] >= '0' && _str[uiCounter] <= '9')
		{
			_riVal += (_str[uiCounter] - '0') * int(std::pow(10, _str.length() - uiCounter - 1));
		}
		else
		{
			std::cout << "\nPaseInt: String failed to convert" << std::endl;
			return(false);
		}
	}

	_riVal = (bNegative ? -_riVal : _riVal);

	std::cout << "\nPaseInt: \"" << _str.c_str() << "\"converted to: " << _riVal << std::endl;

	return(true);
}

double SquareRoot(double _dX) 
{
	if (_dX <= 0)
	{
		return(0);
	}

	int iExp = 0;

	_dX = frexp(_dX, &iExp);

	if (iExp & 1)
	{      
		iExp--;
		_dX *= 2;
	}

	double dY = (_dX + 1) / 2;
	double dZ = 0;

	while (dY != dZ)
	{
		dZ = dY;
		dY = (dY + _dX / dY) / 2;
	}

	double dResult = ldexp(dY, iExp / 2);
	std::cout << "\nSquareRoot: Sqrt(" << _dX << ") = " << dResult << std::endl;

	return(dResult);
}

double Exponent(double _dValue, int _iPow)
{
	double dResult = 1.0;

	for (int i = 0; i < _iPow; ++i)
	{
		dResult *= _dValue;
	}

	std::cout << "\nExponent: " << _dValue << "^" << _iPow << " = " << dResult;

	return(dResult);
}

double Multiply_Recur(double _dX, double _dY, double _dTotal)
{
	if (_dY == 1)
	{
		return(_dTotal + _dX);
	}

	return(Multiply_Recur(_dX, _dY - 1, _dTotal + _dX));
}

double Multiply(double _dX, double _dY)
{
	double dTotal = 0.0;

	double dResult = Multiply_Recur(_dX, _dY, dTotal);
	std::cout << "\nMultiply: " << _dX << "*" << _dY << " = " << dTotal << std::endl;

	return(dResult);
}

int Rand5()
{
	return(rand() % 6);
}

int Rand7()
{
	int iRandom = 0;

	// 8 * 5 = 40 total / 5 per = 1/8 chance (including 0)
	for (int i = 1; i <= 8; ++i)
	{
		iRandom += Rand5();
	}

	return(int(floor(iRandom / 5)));
}

int Islands()
{
	// Setup
	int iWidth = 10;
	int iHeight = 10;

	int iArray[10][10] = 
	{
		{ 1,1,0,0,1,0,0,0,0,0 },
		{ 1,1,0,0,0,0,0,1,1,0 },
		{ 0,0,1,1,0,0,0,0,0,0 },
		{ 1,0,0,1,1,1,1,0,0,0 },
		{ 0,0,0,0,0,1,1,0,0,0 },
		{ 1,0,0,0,0,0,0,0,1,0 },
		{ 1,1,0,0,1,1,1,1,1,1 },
		{ 1,0,0,0,1,1,1,1,1,1 },
		{ 1,1,0,0,1,1,1,1,1,1 },
		{ 1,0,0,0,0,1,1,1,0,0 }
	};

	// Algorithm
	int iIslands = 1;

	for (int y = 0; y < iHeight; ++y)
	{
		for (int x = 0; x < iWidth; ++x)
		{	
			if (iArray[y][x] == 1)
			{
				iIslands++;
				std::vector<int> vecIslandIndices;
				vecIslandIndices.push_back(x * iWidth + y);
				iArray[y][x] = iIslands;

				while (vecIslandIndices.size() > 0)
				{
					int iCurrentX = vecIslandIndices.back() / iWidth;
					int iCurrentY = vecIslandIndices.back() % iWidth;

					vecIslandIndices.pop_back();

					for (int i = -1; i <= 1; ++i)
					{
						for (int j = 0; j <= 1; ++j)
						{
							if (!(j == 1 && abs(i) == 1) &&
								iCurrentX + i >= 0 && iCurrentX + i < iWidth &&
								iCurrentY + j >= 0 && iCurrentY + j < iHeight)
							{
								if (iArray[iCurrentY + j][iCurrentX + i] == 1)
								{
									iArray[iCurrentY + j][iCurrentX + i] = iIslands;
									vecIslandIndices.push_back((iCurrentX + i) * iWidth + (iCurrentY + j));
								}
							}
						}
					}
				}
			}
		}
	}

	iIslands--;
	std::cout << "\nIslands:\n";

	for (int y = 0; y < iHeight; ++y)
	{
		for (int x = 0; x < iWidth; ++x)
		{
			std::cout << iArray[y][x];
		}

		std::cout << std::endl;
	}

	std::cout << "\nCount = " << iIslands << std::endl;

	return(iIslands);
}

bool FirstUniqueChar(std::string _str, char& _rc)
{
	// Algorithm
	std::unordered_map<char, char> mapTable;

	for (char c : _str)
	{
		if (mapTable.find(c) != mapTable.end())
		{
			mapTable[c] = 1;
		}
		else
		{
			mapTable[c] = 0;
		}
	}

	for (char c : _str)
	{
		if (mapTable[c] == 0)
		{
			std::cout << "\nFirst unique char = " << c << std::endl;
			_rc = c;
			return(true);
		}
	}

	std::cout << "\nNo unique chars" << std::endl;

	return(false);
}

std::string ReverseString(std::string _str)
{
	std::cout << "\nReverseString: " << _str.c_str();

	for (int i = 0; i < int(_str.length() / 2); ++i)
	{
		auto iIndex = _str.length() - 1 - i;
		char cTemp = _str[i];
		_str[i] = _str[iIndex];
		_str[iIndex] = cTemp;
	} 

	std::cout << " = " << _str.c_str() << std::endl;

	return(_str);
}

std::string ReverseString_Recur(std::string _strOrig, std::string _strNew, int _iIndex)
{
	if (_iIndex == 0)
	{
		return(_strNew + _strOrig[_iIndex]);
	}

	return(ReverseString_Recur(_strOrig, _strNew + _strOrig[_iIndex], _iIndex - 1));
}

std::string ReverseStringRecursive(std::string _strOrig)
{
	std::cout << "\nReverseString: " << _strOrig.c_str();
	_strOrig = ReverseString_Recur(_strOrig, "", ( int )( _strOrig.length() - 1 ) );
	std::cout << " = " << _strOrig.c_str() << std::endl;
	return(_strOrig);
}

bool IsAnagram(std::string _str1, std::string _str2)
{
	// Algorithm
	std::unordered_map<char, int> mapTable;

	for (char c : _str1)
	{
		if (mapTable.find(c) != mapTable.end())
		{
			mapTable[c] = mapTable[c] + 1;
		}
		else
		{
			mapTable[c] = 1;
		}
	}

	for (char c : _str2)
	{
		if (mapTable.find(c) != mapTable.end())
		{
			mapTable[c] = mapTable[c] - 1;

			if (mapTable[c] < 0)
			{
				std::cout << std::endl << _str2.c_str() << " is not an anagram of " << _str1.c_str() << std::endl;
				return(false);
			}
		}
		else
		{
			std::cout << std::endl << _str2.c_str() << " is not an anagram of " << _str1.c_str() << std::endl;
			return(false);
		}
	}

	std::cout << std::endl << _str2.c_str() << " is an anagram of " << _str1.c_str() << std::endl;
	return(true);
}

bool IsPalindrome(std::string _str, bool _bShowOutput)
{
	for (int i = 0; i < int(_str.length() / 2); ++i)
	{
		if (_str[i] != _str[_str.length() - 1 - i])
		{
			if(_bShowOutput) std::cout << std::endl << _str.c_str() << " is not a palindrome\n";
			return(false);
		}
	}

	if(_bShowOutput) std::cout << std::endl << _str.c_str() << " is a palindrome\n";
	return(true);
}

bool IsStringUnique(std::string _str)
{
	// Algorithm
	std::unordered_map<char, int> mapTable;

	for (char c : _str)
	{
		if (mapTable.find(c) != mapTable.end())
		{
			std::cout << std::endl << _str.c_str() << " does not contain unique characters\n";
			return(false);
		}
		else
		{
			mapTable[c] = 0;
		}
	}

	std::cout << std::endl << _str.c_str() << " contains unique characters\n";
	return(true);
}

bool IsStringInt(std::string _str, bool& _rbIsDouble)
{
	if (_str.length() == 0)
	{
		std::cout << "\nIsStringInt: String is empty" << std::endl;
		return(false);
	}

	unsigned int uiCounter = 0;
	int iDecimalCount = 0;
	_rbIsDouble = false;

	if (_str[0] == '-' || _str[0] == '+' || _str[0] == '.')
	{
		uiCounter++;
	}

	for (; uiCounter < _str.length(); uiCounter++)
	{
		if (_str[uiCounter] == '.')
		{
			iDecimalCount++;

			if (iDecimalCount == 1)
			{
				_rbIsDouble = true;
			}
			else
			{
				std::cout << "\nIsStringInt: String is not a valid number" << std::endl;
				return(false);
			}
		}
		else if(!(_str[uiCounter] >= '0' && _str[uiCounter] <= '9'))
		{
			std::cout << "\nIsStringInt: String is not a valid number" << std::endl;
			return(false);
		}
	}

	std::cout << "\nIsStringInt: \"" << _str.c_str() << (_rbIsDouble ? "\" is a double" : "\" is an int") << std::endl;

	return(true);
}

bool ShortestPalindrome(std::string _str, std::string& _rstrPalindrome)
{
	auto uiLength = ( int )_str.length();
	_rstrPalindrome = "";
	auto iShortest = INT_MAX;

	std::cout << "\nShortestPalindrome: \"" << _str.c_str() << "\" = ";

	while (uiLength >= 3)
	{
		bool bRemoved = false;

		if (_str.length() >= uiLength)
		{
			for (unsigned int i = 0; i <= (_str.length() - uiLength); i++)
			{
				std::string strSub = _str.substr(i, uiLength);

				if (IsPalindrome(strSub, false))
				{
					iShortest = uiLength;
					_rstrPalindrome = strSub;
					_str.erase(i, uiLength);
					bRemoved = true;
					break;
				}
			}
		}

		if (!bRemoved)
		{
			uiLength--;
		}
	}

	if (iShortest < INT_MAX)
	{
		std::cout << _rstrPalindrome.c_str() << std::endl;
		return(true);
	}

	std::cout << "no palindromes found\n";
	return(false);
}

int Factorial(int _i)
{
	int iTotal = 1;

	for (int i = 2; i <= _i; ++i)
	{
		iTotal *= i;
	}

	return(iTotal);
}

void StringPermutations(std::string _str)
{
	int iCombinations = Factorial( ( int )_str.length() );
	std::cout << "\nStringPermutations: \"" << _str.c_str() << "\" \n";

	for (int i = 0; i < iCombinations; ++i)
	{
		int iVal = i;
		std::string strPerm = _str;

		for (unsigned int j = 1; j < _str.size(); ++j)
		{
			std::swap(strPerm[iVal % (j + 1)], strPerm[j]);
			iVal /= (j + 1);
		}

		std::cout << strPerm.c_str() << " ";
	}

	std::cout << std::endl;
}

int main()
{
	srand((unsigned int)(time(0)));

	FrequentInt();
	IntegerPairs();
	RotatedArray();
	Fibbonaci_Dynamic(25);
	UniqueInteger();
	CommonElements();

	std::vector<int> vecBSA = { 5,3,7,8,9,1,5,7,9,4,263,5,1,6 };
	int iResult;
	std::cout << (BinarySearch(vecBSA, 5, iResult) ? "\nBSA: Result found" : "\nBSA: Result not found") << std::endl;

	Primes(100);
	BinaryForm(345345);

	int iVal;
	ParseInt("2015", iVal);

	SquareRoot(3.1415926);
	Exponent(2.0f, 8);
	Multiply(5.0f, 20.0f);
	Islands();

	char c;
	FirstUniqueChar("UunniquuqeTiestt", c);

	ReverseString("Hello my name is Alex");
	ReverseStringRecursive("This string will be reversed using recursion");
	IsAnagram("good morning", "donorm going");
	IsPalindrome("wasiteliotstoiletisaw", true);
	IsStringUnique("tes word");

	bool bDouble;
	IsStringInt("5", bDouble);

	std::string str;
	ShortestPalindrome("wasaw systematic wasiteliotstoiletisaw", str);

	StringPermutations("ABC");

	int iTemp;
	std::cin >> iTemp;

	return(0);
}