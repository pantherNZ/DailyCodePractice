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
#include <deque>
#include <memory>
#include <sstream>
#include <random>
#include <set>
#include <typeindex>
#include <array>

#include "test.h"
#include "HandleClass.h"

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

	std::cout << "\nHighest Frequency Number = " << iHighestFreq << "\n";
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
			std::cout << "Pair found: " << vecArray[ i ] << " + " << iMax - vecArray[ i ] << "\n";
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

		std::cout << "Fib " << i << " = " << iTotal << "\n";
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
		std::cout << "Fib " << i << " = " << pArray[i] << "\n";
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
			std::cout << "\nFirst unique integer = " << i << "\n";
			return;
		}
	}

	std::cout << "\nNo unique integers\n";
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

	std::cout << "\n";
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

	std::cout << "\n";
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

	std::cout << "\n";
}

bool ParseInt(std::string _str, int& _riVal)
{
	if (_str.length() == 0)
	{
		std::cout << "\nPaseInt: String failed to convert\n";
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
			std::cout << "\nPaseInt: String failed to convert\n";
			return(false);
		}
	}

	_riVal = (bNegative ? -_riVal : _riVal);

	std::cout << "\nPaseInt: \"" << _str.c_str() << "\"converted to: " << _riVal << "\n";

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
	std::cout << "\nSquareRoot: Sqrt(" << _dX << ") = " << dResult << "\n";

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
	std::cout << "\nMultiply: " << _dX << "*" << _dY << " = " << dTotal << "\n";

	return(dResult);
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

		std::cout << "\n";
	}

	std::cout << "\nCount = " << iIslands << "\n";

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
			std::cout << "\nFirst unique char = " << c << "\n";
			_rc = c;
			return(true);
		}
	}

	std::cout << "\nNo unique chars\n";

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

	std::cout << " = " << _str.c_str() << "\n";

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
	std::cout << " = " << _strOrig.c_str() << "\n";
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
				std::cout << "\n" << _str2.c_str() << " is not an anagram of " << _str1.c_str() << "\n";
				return(false);
			}
		}
		else
		{
			std::cout << "\n" << _str2.c_str() << " is not an anagram of " << _str1.c_str() << "\n";
			return(false);
		}
	}

	std::cout << "\n" << _str2.c_str() << " is an anagram of " << _str1.c_str() << "\n";
	return(true);
}

bool IsPalindrome(std::string _str, bool _bShowOutput)
{
	for (int i = 0; i < int(_str.length() / 2); ++i)
	{
		if (_str[i] != _str[_str.length() - 1 - i])
		{
			if(_bShowOutput) std::cout << "\n" << _str.c_str() << " is not a palindrome\n";
			return(false);
		}
	}

	if(_bShowOutput) std::cout << "\n" << _str.c_str() << " is a palindrome\n";
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
			std::cout << "\n" << _str.c_str() << " does not contain unique characters\n";
			return(false);
		}
		else
		{
			mapTable[c] = 0;
		}
	}

	std::cout << "\n" << _str.c_str() << " contains unique characters\n";
	return(true);
}

bool IsStringInt(std::string _str, bool& _rbIsDouble)
{
	if (_str.length() == 0)
	{
		std::cout << "\nIsStringInt: String is empty\n";
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
				std::cout << "\nIsStringInt: String is not a valid number\n";
				return(false);
			}
		}
		else if(!(_str[uiCounter] >= '0' && _str[uiCounter] <= '9'))
		{
			std::cout << "\nIsStringInt: String is not a valid number\n";
			return(false);
		}
	}

	std::cout << "\nIsStringInt: \"" << _str.c_str() << (_rbIsDouble ? "\" is a double\n" : "\" is an int\n");

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
		std::cout << _rstrPalindrome.c_str() << "\n";
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

	std::cout << "\n";
}


struct Tag
{
	std::string name;
	std::string value;

	Tag( std::string _name, std::string _value ) : name( _name ), value( _value ) { }
};

// String for the text, vector containing index's of the tags required into the tags_map array.
typedef std::pair< std::string, std::deque< unsigned > > output_string;

void ParseTextTags( std::string _str )
{
	// Stack containing the current tags
	std::deque< unsigned > tags;
	// All unique tags are saved here to save memory
	std::vector< std::unique_ptr< Tag > > tag_map;	
	// Final output is a vector of strings that have a list of tag index's attached
	std::vector< output_string > output;

	// Data
	std::string current;
	std::string value;
	bool reading_tag = false;
	bool end_tag = false;
	bool value_tag = false;

	// Loop through string
	for( auto c : _str )
	{
		// Start of a tag
		if( c == '<' )
		{
			// Only add text from before this tag if it is > 0 in size & isn't just a space
			// This will save the text in these tags + the stack of tag index's right now
			if( current.size() > 0 && current[ 0 ] != ' ' )
				output.push_back( std::make_pair( current, tags ) );

			current = "";
			value = "";
			reading_tag = true;
			end_tag = false;
			value_tag = false;
		}
		// Tag read in
		else if( reading_tag )
		{
			// Ending tag (later used to check for a matching start tag)
			if( c == '/' )
				end_tag = true;
			// End of a tag
			else if( c == '>' )
			{
				// If we are an ending tag, find the matching start tag (and remove it)
				if( end_tag )
				{
					if( tag_map.size() > tags.back() && current == tag_map[ tags.back() ]->name )
						tags.pop_back();
					else
						std::cout << "\nParseTextTags: *Warning* - Ending tag without a matching start tag: \"" << current.c_str() << "\"";
				}
				else
				{
					// Otherwise let's check if this is a unique tag or not
					unsigned index = 0;
					const auto found = std::find_if( tag_map.begin(), tag_map.end(), [&current, &value, &index]( const std::unique_ptr< Tag >& t )
					{
						++index;
						return t->name == current && t->value == value;
					} );

					// Create a new tag in the map if it is unique
					if( found == tag_map.end() )
					{
						tag_map.push_back( std::make_unique< Tag >( current, value ) );
						index = ( unsigned )tag_map.size();
					}

					// Add the index of the tag to the tags stack
					tags.push_back( index - 1 );
				}

				current = "";
			}
			else if( c == '=' )
			{
				// End tags can't have a value
				if( end_tag )
					std::cout << "\nParseTextTags: *Warning* - Ending tag with a value: \"" << current.c_str() << "\"";
				else
					value_tag = true;
			}
			// Read into the value part of the tag
			else if( value_tag )
				value += c;
			// Otherwise just regular read in
			else
				current += c;
		}	
		else
			current += c;
	}

	// If at the end we aren't an ending tag, we will want to make sure we add the remaining text
	if( _str.back() != '>' )
		output.push_back( std::make_pair( current, tags ) );
}

std::string ToOrdinalForm( const long long _input )
{
	std::stringstream ss;
	ss << _input;
	
	const auto mod = ( _input % 100 ) / 10 == 1 ? 0 : _input % 10;

	switch( mod )
	{
	case 1: ss << "st"; break;
	case 2: ss << "nd"; break;
	case 3: ss << "rd"; break;
	default: ss << "th"; break;
	}

	return ss.str( );
}

std::string ToEnglishForm( const long long _input )
{
	std::string ones[] = { "one", "two", "three", "four", "five", "six", "seven", "eight", "nine" };
	std::string teens[] = { "ten", "eleven", "twelve", "thirteen", "fourteen", "fifteen", "sixteen", "seventeen", "eighteen", "nineteen" };
	std::string tens[] = { "twenty", "thirty", "forty", "fifty", "sixty", "seventy", "eighty", "ninety" };
	std::string illions[] = { "million", "billion", "trillion", "quadrillion", "quintillion", "sextillion", "septillion", "octillion", "nonillion", "decillion" };
	std::string decillions[] = { "undecillion", "duodecillion", "tredecillion", "quattuordecillion", "quindecillion", "sexdecillion", "septendecillion", "octodecillion", "novemdecillion", "vigintillion" };

	if( _input == 0 )
		return "zero";

	// # of digits
	std::stringstream ss;
	ss << _input;
	std::string strInput( ss.str( ) );

	std::string output;

	const auto and_string = [&]( ) -> std::string
	{
		return output.size( ) > 0 ? " and " : "";
	};

	const auto space_string = [&]( ) -> std::string
	{
		return output.size( ) > 0 ? " " : "";
	};

	const bool negative = strInput[0] == '-';

	if( negative )
		strInput[0] = '0';

	auto digits = strInput.length( );

	while( strInput.size( ) % 3 != 0 )
		strInput = "0" + strInput;

	for( unsigned i = 0; i < strInput.length( ); i += 3, digits -= 3 )
	{
		// Hundreds
		if( strInput[i] != '0' )
			output += space_string( ) + ones[char( strInput[i] - '0' - 1 )] + " hundred";

		// Tens
		if( strInput[i + 1] != '0' )
		{
			// Teens
			if( strInput[i + 1] == '1' )
				output += and_string( ) + teens[char( strInput[i + 2] - '0' )];
			else
				output += and_string( ) + tens[char( strInput[i + 1] - '0' - 2 )];
		}

		// Ones
		if( strInput[i + 2] != '0' && strInput[i + 1] != '1' )
			output += ( strInput[i + 1] == '0' && strInput[i] != '0' ? and_string( ) : space_string( ) ) + ones[char( strInput[i + 2] - '0' - 1 )];

		// Thousands
		if( digits >= 4 && digits < 7 )
		{
			output += " thousand";
		}
		// Illions
		else if( digits >= 7 && digits < 35 )
		{
			output += space_string( ) + illions[( digits - 7 ) / 3];
		}
		// Decillions
		else if( digits >= 35 && digits < 65 )
		{
			output += space_string( ) + decillions[( digits - 7 ) / 3];
		}
		else if( digits >= 65 )
		{
			std::cout << "\nNumber is too large to convert!\n";
			return "";
		}
	}

	if( negative )
		output = "negative " + output;

	return output;
}

std::string ZigZag( std::string s, int numRows )
{
	std::string output;
	int length = ( int )s.length();
	 
	if( numRows >= length || numRows == 1 )
		return s;
		
	for ( int i = 0; i < numRows; ++i )
	{
		for ( int j = i; j < length; j += ( numRows - 1 ) * 2 )
		{
			output += s[j];

			if ( i > 0 && i < numRows - 1 && j + ( numRows - 1 - i ) * 2 < length )
				output += s[j + ( numRows - 1 - i ) * 2];
		}
	}

	return output;
}

bool IsValidSudoku( std::vector< std::vector< char > >& board )
{
	for( int i = 0; i < 9; ++i )
	{
		std::unordered_set< char > hash_map_a, hash_map_b, hash_map_c;

		for( int j = 0; j < 9; ++j )
		{
			// Horizontal
			if( board[i][j] != '.' && hash_map_a.find( board[i][j] ) != hash_map_a.end() )
				return false;
			hash_map_a.insert( board[i][j] );

			// Vertical
			if( board[j][i] != '.' && hash_map_b.find( board[j][i] ) != hash_map_b.end() )
				return false;
			hash_map_b.insert( board[j][i] );

			// Square
			const int x = 3 * ( i % 3 ) + j % 3;
			const int y = 3 * ( i / 3 ) + j / 3;
			if( board[y][x] != '.' && hash_map_c.find( board[y][x] ) != hash_map_c.end() )
				return false;
			hash_map_c.insert( board[y][x] );
		}
	}

	return true;
}

bool TrySudokuPosition( std::vector< std::vector< char > >& board, int current_index_x, int current_index_y )
{
	// Find next valid position
	while( board[current_index_y][current_index_x] != '.' )
	{
		current_index_x++;
		if( current_index_x >= 9 )
		{
			current_index_x = 0;
			current_index_y++;

			if( current_index_y >= 9 )
				return true;
		}
	}

	// Place number
	char number_to_try = '0';

	while( number_to_try < '9' )
	{
		bool valid = true;
		number_to_try++;
		board[current_index_y][current_index_x] = number_to_try;

		// Check board is valid from this change
		for( int i = 0; i < 9; ++i )
		{
			// Horizontal
			if( i != current_index_x && board[current_index_y][i] == number_to_try )
			{
				valid = false;
				break;
			}

			// Vertical
			if( i != current_index_y && board[i][current_index_x] == number_to_try )
			{
				valid = false;
				break;
			}

			// Square
			const int x = ( current_index_x - current_index_x % 3 ) + i % 3;
			const int y = ( current_index_y - current_index_y % 3 ) + i / 3;

			if( x != current_index_x && y != current_index_y && board[y][x] == number_to_try )
			{
				valid = false;
				break;
			}
		}

		if( !valid )
			board[current_index_y][current_index_x] = '.';
		else if( !TrySudokuPosition( board, current_index_x, current_index_y ) )
			board[current_index_y][current_index_x] = '.';
		else
			return true;
	}

	return false;
}

void SolveSudoku( std::vector< std::vector< char > >& board )
{
	/* Brute force
	- Attempt to place a number in next available position
	- Check if this is valid firstly in the current square, then the vertical row, then the horizontal
	- If it is valid, continue to next available position
	- Otherwise, increment the number and try again
	*/
	const bool result = TrySudokuPosition( board, 0, 0 );
	std::cout << ( result ? "\n\nSoduku successfully solved!\n" : "\n\nNo solution found for Soduku!\n" );
}

double FindMedianArray( std::vector< int >& nums )
{
	const auto size = nums.size();
	if( size == 1 )
		return nums[0];
	else
		return ( size & 1 ? nums[size / 2] : ( nums[size / 2 - 1] + nums[size / 2] ) / 2.0 );
}

const int GetRomanValue( const char c )
{
	switch( c )
	{
	case 'I':   return 1;
	case 'V':   return 5;
	case 'X':   return 10;
	case 'L':   return 50;
	case 'C':   return 100;
	case 'D':   return 500;
	case 'M':   return 1000;
	default:	return 0;
	}
}

int RomanToInt( std::string s )
{
	if( s.empty() )
		return 0;

	if( s.size() == 1 )
		return GetRomanValue( s.front() );

	int iResult = 0;
	int iPrevious = 0;

	for( unsigned i = 0; i < s.size(); ++i )
	{
		const auto iNew = GetRomanValue( s[i] );

		if( i > 0 )
		{
			if( iPrevious < iNew )
				iResult -= iPrevious;
			else
				iResult += iPrevious;
		}

		iPrevious = iNew;
	}

	iResult += iPrevious;

	return iResult;
}

// https://www.reddit.com/r/dailyprogrammer/comments/7vx85p/20180207_challenge_350_intermediate_balancing_my/
void FindEquailibriaPoints( std::vector< int >& nums )
{
	std::cout << "FindEquailibriaPoints( ";

	size_t count = nums.size();
	std::vector< int > reverse_totals( count );
	int forward_total = 0;
	reverse_totals[count - 1] = 0;

	for( size_t i = count - 1; i > 0; --i )
	{
		reverse_totals[i - 1] = nums[i] + ( i < count - 1 ? reverse_totals[i] : 0 );
		std::cout << i << ", ";
	}

	std::cout << ");\n";

	for( size_t i = 0; i < count; ++i )
	{
		if( forward_total == reverse_totals[i] )
			std::cout << i << " ";
		forward_total += nums[i];
	}

	std::cout << "\n\n";
}

void CricketSolver( const std::string& input )
{
	constexpr unsigned batsmanCount = 11U;
	std::array< unsigned, batsmanCount > batsman = { 0 };
	unsigned extraRuns = 0U;
	unsigned striker = 0U;
	unsigned batsman2 = 1U;
	unsigned ballCount = 0U;

	for( auto& c : input )
	{
		bool exit_loop = false;

		switch( c )
		{
		case '.':
			break;
		case 'b':
		{
			extraRuns++;
			std::swap( striker, batsman2 );
			break;
		}
		case 'w':
		{
			extraRuns++;
			break;
		}
		case 'W':
		{
			// Swap strikers to next available one
			unsigned next_batter = std::max( striker, batsman2 );
			exit_loop = striker >= batsmanCount;
			striker = std::min( batsmanCount, next_batter + 1U );
			break;
		}
		default:
		{
			// Add runs
			if( c >= '0' && c <= '9' )
			{
				int runs = ( c - '0' );
				batsman[striker] += runs;

				if( ( runs & 1 ) == 1 )
					std::swap( striker, batsman2 );
			}
			break;
		}
		}

		if( exit_loop )
			break;

		if( c != 'w' )
		{
			ballCount++;

			if( ballCount >= 6 )
			{
				ballCount = 0;
				std::swap( striker, batsman2 );
			}
		}
	}

	for( unsigned i = 0; i <= std::max( striker, batsman2 ); ++i )
		std::cout << "P" << i << ": " << batsman[i] << " ";
	std::cout << "Extras: " << extraRuns;
}

void Test( Handle< int > test )
{
	std::cout << "nblafgh";
}

class BaseClass
{
public:
	BaseClass( int t ) : i( t ) {}
	virtual void DoStuff() { std::cout << "\nBase class: " << i; }
	int i = 0;
};

class DerivedClass : public BaseClass
{
public:
	DerivedClass( int t ) : BaseClass( t ) {}
	void DoStuff() final { std::cout << "\nDerived class: " << i; }
};

void PassWeakPtrAround( const std::weak_ptr< DerivedClass >& test )
{
	if( auto ptr = test.lock() )
		ptr->DoStuff();
}

void WeakPtrTest()
{
	std::vector< std::shared_ptr< BaseClass > > storage;
	storage.push_back( std::make_shared< DerivedClass >( 5 ) );
	storage.front()->DoStuff();

	auto passed_around = std::weak_ptr< DerivedClass >( std::static_pointer_cast< DerivedClass>( storage.front() ) );

	const auto test = [&]() -> const std::weak_ptr< DerivedClass >& { return passed_around; };
	const auto another = std::weak_ptr< DerivedClass >( passed_around );
	
	if( auto ptr = another.lock() )
	{
		ptr->i = 10;
		ptr->DoStuff();
	}

	if( auto ptr = test().lock() )
		ptr->DoStuff();


	std::cout << ( passed_around.expired() ? "\nExpired" : "\nValid" );

	const auto handle = Reflex::Core::Handle< DerivedClass >( storage.front() );
	storage.clear();
}

int main()
{
	std::random_device rd;
	std::mt19937 rng( rd( ) );
	const auto max_long_long = std::numeric_limits< long long >::max( );
	std::uniform_int_distribution<long long> distribution( -max_long_long, max_long_long );

	const auto Rand = [&]( long long _min, long long _max = 0 ) -> long long
	{
		const auto max = _max == 0 ? _min : _max;
		const auto min = _max == 0 ? 0 : _min;
		return min + ( distribution( rng ) % ( long long )( max - min + 1 ) );
	};

	FrequentInt();
	IntegerPairs();
	RotatedArray();
	Fibbonaci_Dynamic(25);
	UniqueInteger();
	CommonElements();

	std::vector<int> vecBSA = { 5,3,7,8,9,1,5,7,9,4,263,5,1,6 };
	int iResult;
	std::cout << (BinarySearch(vecBSA, 5, iResult) ? "\nBSA: Result found\n" : "\nBSA: Result not found\n");

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

	ParseTextTags( "Lorem ipsum <size=10>dolor sit amet,<size=5> <bold>consectetur</bold> <colour=red>adipiscing</colour> elit.</size>\
		Donec eu arcu eget enim hendrerit</size> finibus eu vel<italic>dolor. In ultrices lorem odio, in condimentum massa luctus</italic>\
		vel. Curabitur<size=15> id nibh mi. Proin orci erat,<size=12> porta in sem sit amet, condimentum aliquet ligula. Curabitur leo lacus,\
		</size> aliquam <colour=green>auctor ullamcorper vitae, pulvinar eget lectus. Praesent <bold>felis risus, euismod at enim</bold> \
		quis, consequat hendrerit magna.</colour> Class aptent <italic><bold> <colour=purple>taciti</colour></bold></italic> sociosqu ad \
		litora torquent per conubia nostra, per inceptos himenaeos. Donec varius sem sapien. Nam vitae scelerisque est, eget feugiat tortor. \
		Class aptent taciti sociosqu ad litora torquent per conubia nostra, per inceptos himenaeos.</size>" );

	//for( int i = 0; i < 10; ++i )
	{
		const auto rand = Rand( 100000 );
		std::cout << "\nToOrdinalForm( " << rand << " ) = " << ToOrdinalForm( rand );
	}

	std::cout << "\n";
	//std::cout << "\nToEnglishForm( 1 ) = " << ToEnglishForm( 1 );
	//std::cout << "\nToEnglishForm( 10 ) = " << ToEnglishForm( 10 );
	//std::cout << "\nToEnglishForm( 20 ) = " << ToEnglishForm( 20 );
	//std::cout << "\nToEnglishForm( 16 ) = " << ToEnglishForm( 16 );
	//std::cout << "\nToEnglishForm( 100 ) = " << ToEnglishForm( 100 );
	//std::cout << "\nToEnglishForm( 65 ) = " << ToEnglishForm( 65 );
	//std::cout << "\nToEnglishForm( 999 ) = " << ToEnglishForm( 999 );
	//std::cout << "\nToEnglishForm( 1000 ) = " << ToEnglishForm( 1000 );
	//std::cout << "\nToEnglishForm( 1005 ) = " << ToEnglishForm( 1005 );
	//std::cout << "\nToEnglishForm( 1615 ) = " << ToEnglishForm( 1615 );
	//std::cout << "\nToEnglishForm( -1,353,574,123,666 ) = " << ToEnglishForm( -1353574123666 );

	//for( int i = 0; i < 10; ++i )
	{
		const auto rand = Rand( 105605650000 );
		std::cout << "\nToEnglishForm( " << rand << ") = " << ToEnglishForm( rand );
	}


	std::cout << "\n\nZigZag( \"PAYPALISHIRING\", 3 ) = " << ZigZag( "PAYPALISHIRING", 3 );
	std::cout << "\nZigZag( \"PAYPALISHIRING\", 4 ) = " << ZigZag( "PAYPALISHIRING", 4 );

	std::vector< std::vector< char > > board =
	{
		{ '.', '.', '.', '.', '.', '.', '.', '.', '.' },
		{ '.', '.', '.', '.', '.', '.', '3', '.', '.' },
		{ '.', '.', '.', '1', '8', '.', '.', '.', '.' },
		{ '.', '.', '.', '7', '.', '.', '.', '.', '.' },
		{ '.', '.', '.', '.', '1', '.', '9', '7', '.' },
		{ '.', '.', '.', '.', '.', '.', '.', '.', '.' },
		{ '.', '.', '.', '3', '6', '.', '1', '.', '.' },
		{ '.', '.', '.', '.', '.', '.', '.', '.', '.' },
		{ '.', '.', '.', '.', '.', '.', '.', '2', '.' }
	};

	IsValidSudoku( board );

	std::vector< std::vector< char > > board2 =
	{
		{ '5', '3', '.', '.', '7', '.', '.', '.', '.' },
		{ '6', '.', '.', '1', '9', '5', '.', '.', '.' },
		{ '.', '9', '8', '.', '.', '.', '.', '6', '.' },
		{ '8', '.', '.', '.', '6', '.', '.', '.', '3' },
		{ '4', '.', '.', '8', '.', '3', '.', '.', '1' },
		{ '7', '.', '.', '.', '2', '.', '.', '.', '6' },
		{ '.', '6', '.', '.', '.', '.', '2', '8', '.' },
		{ '.', '.', '.', '4', '1', '9', '.', '.', '5' },
		{ '.', '.', '.', '.', '8', '.', '.', '7', '9' }
	};
	
	SolveSudoku( board2 );

	RomanToInt( "III" );
	RomanToInt( "IV" );
	RomanToInt( "VI" );
	RomanToInt( "VII" );
	RomanToInt( "VIII" );
	RomanToInt( "IX" );

	FindEquailibriaPoints( std::vector<int>{ 0, -3, 5, -4, -2, 3, 1, 0 } );
	FindEquailibriaPoints( std::vector<int>{ 3, -2, 2, 0, 3, 4, -6, 3, 5, -4, 8 } );
	FindEquailibriaPoints( std::vector<int>{ 9, 0, -5, -4, 1, 4, -4, -9, 0, -7, -1 } );
	FindEquailibriaPoints( std::vector<int>{ 9, -7, 6, -8, 3, -9, -5, 3, -6, -8, 5 } );

	CricketSolver( "1.2wW6.2b34" );

	auto obj = Object();
	Entity* b = &obj;
	b->~Entity();

	const auto test = Handle< int >();
	//const auto base = BaseHandle();
	auto test2 = Handle< char >();

	const auto testfunc = []( Handle< int > input )
	{
		std::cout << "test wahtever";
	};

	Test( test2 );

	WeakPtrTest();

	int iTemp;
	std::cin >> iTemp;

	return(0);
}