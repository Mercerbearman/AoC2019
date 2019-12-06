#include <iostream>
#include <vector>
std::vector<unsigned int> passwords;

bool TwoAdjacentDigitsMatch(unsigned int val1, unsigned int val2) {

	if (val1 == val2) {
		return true;
	}

	return false;
}

bool CheckForLargetGroups(unsigned int digits[6], unsigned int val) {

	unsigned int firstDigit(digits[0]);
	unsigned int secondDigit(digits[1]);
	unsigned int numInGroup(0);

	if (TwoAdjacentDigitsMatch(firstDigit, secondDigit)) numInGroup = 2;

	for (int ix = 2; ix < 6; ++ix) {

		firstDigit = secondDigit;
		secondDigit = digits[ix];

		if (TwoAdjacentDigitsMatch(firstDigit, secondDigit)) {
			if (numInGroup == 0) { 
				numInGroup = 2; 
			}
			else {
				numInGroup++;
			}
			
		}
		else {
			if (numInGroup == 2) {
				return true; //Always wins if only 2 in a row.
			}
			else {
				numInGroup = 0;
			}
		}
	}

	if (numInGroup == 2) {
		return true;
	}

	return false;


}

bool DigitsNeverDecrease(unsigned int val) {

	unsigned int valToCheck(0);
	unsigned int nextVal(0);
	unsigned int decreasingVal(val);
	bool adjacentDigits(false);
	unsigned int digits[6];

	valToCheck = static_cast<unsigned int> (val / 100000);
	nextVal = static_cast<unsigned int> ((decreasingVal - (valToCheck * 100000)) / 10000);

	digits[0] = valToCheck;
	digits[1] = nextVal;

	if (nextVal < valToCheck) {
		return false;
	}

	adjacentDigits = TwoAdjacentDigitsMatch(valToCheck, nextVal);

	decreasingVal -= (valToCheck * 100000);

	valToCheck = nextVal;
	nextVal = static_cast<unsigned int> ((decreasingVal - (valToCheck * 10000)) / 1000);

	digits[2] = nextVal;

	if (nextVal < valToCheck) {
		return false;
	}	

	adjacentDigits |= TwoAdjacentDigitsMatch(valToCheck, nextVal);

	decreasingVal -= (valToCheck * 10000);

	valToCheck = nextVal;
	nextVal = static_cast<unsigned int> ((decreasingVal - (valToCheck * 1000)) / 100);

	digits[3] = nextVal;

	if (nextVal < valToCheck) {
		return false;
	}

	adjacentDigits |= TwoAdjacentDigitsMatch(valToCheck, nextVal);

	decreasingVal -= (valToCheck * 1000);

	valToCheck = nextVal;
	nextVal = static_cast<unsigned int> ((decreasingVal - (valToCheck * 100)) / 10);

	digits[4] = nextVal;

	if (nextVal < valToCheck) {
		return false;
	}

	adjacentDigits |= TwoAdjacentDigitsMatch(valToCheck, nextVal);

	decreasingVal -= (valToCheck * 100);

	valToCheck = nextVal;
	nextVal = static_cast<unsigned int> (decreasingVal - (valToCheck * 10));

	digits[5] = nextVal;

	if (nextVal < valToCheck) {
		return false;
	}

	adjacentDigits |= TwoAdjacentDigitsMatch(valToCheck, nextVal);

	if (adjacentDigits) {
		adjacentDigits = CheckForLargetGroups(digits, val);
	}

	return adjacentDigits;


}

bool PassAllChecks(unsigned int val) {

	if (DigitsNeverDecrease(val)) {
		passwords.push_back(val);
		return true;
	}

	return false;

}

int main()
{
	unsigned int inputMin(273025);
	unsigned int inputMax(767253);

	for (int ix = inputMin; ix <= inputMax; ++ix) {
		PassAllChecks(ix);
	}

	std::cout << "# Passwords: " << passwords.size();

}
