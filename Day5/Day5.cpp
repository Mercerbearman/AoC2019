#include <iostream>
#include <vector>
#include <string>
#include <sstream>

int part1(std::vector<int> inputs) {
	int opCode(0);
	int firstParam(0);
	int secParam(0);
	int thirdParam(0);
	bool firstParamImmediateMode(false);
	bool secondParamImmediateMode(false);
	bool thirdParamImmediateMode(false);
	int temp(0);

	int commandWord(0);

	int result(0);

	int val1Loc(0);
	int val2Loc(0);
	int val3Loc(0);
	int numParams(0);

	for (unsigned int idx = 0; idx < inputs.size() - 1;) {

		val1Loc = 0;
		val2Loc = 0;
		val3Loc = 0;
		//numParams = 0;

		commandWord = inputs[idx];
		
		opCode = commandWord % 100;

		if (opCode == 99) {
			numParams = 1;
			break;
		}

		temp = (commandWord / 10000);
		thirdParamImmediateMode = temp == 1;

		temp = (commandWord % 10000) / 1000;
		secondParamImmediateMode = temp == 1;

		temp = (commandWord % 1000) / 100;
		firstParamImmediateMode = temp == 1;

		firstParam = inputs[idx + 1];

		if (firstParamImmediateMode) {
			val1Loc = inputs[idx + 1];
		}
		else {
			val1Loc = firstParam;
		}

		//Add
		if (opCode == 1) {

			secParam = inputs[idx + 2];
			thirdParam = inputs[idx + 3];

			if (secondParamImmediateMode) {
				val2Loc = inputs[idx + 2];
			}
			else {
				val2Loc = secParam;
			}

			if (thirdParamImmediateMode) {
				val3Loc = inputs[idx + 3];
			}
			else {
				val3Loc = thirdParam;
			}

			int value1(firstParam);
			int value2(secParam);

			if (!firstParamImmediateMode) {
				value1 = inputs[val1Loc];
			}
			if (!secondParamImmediateMode) {
				value2 = inputs[val2Loc];
			}

			result = value1 + value2;
			inputs[val3Loc] = result;
			numParams = 4;
		}
		//Multiple
		else if (opCode == 2) {

			secParam = inputs[idx + 2];
			thirdParam = inputs[idx + 3];

			if (secondParamImmediateMode) {
				val2Loc = inputs[idx + 2];
			}
			else {
				val2Loc = secParam;
			}

			if (thirdParamImmediateMode) {
				val3Loc = inputs[idx + 3];
			}
			else {
				val3Loc = thirdParam;
			}

			int value1(firstParam);
			int value2(secParam);

			if (!firstParamImmediateMode) {
				value1 = inputs[val1Loc];
			}
			if (!secondParamImmediateMode) {
				value2 = inputs[val2Loc];
			}

			result = value1 * value2;
			inputs[val3Loc] = result;

			numParams = 4;
		}
		//Read in
		else if (opCode == 3) {
			int input(0);
			std::cout << "Please provide an input: ";
			std::cin >> input;
			inputs[val1Loc] = input;

			numParams = 2;
		}

		//Print out
		else if (opCode == 4) {
			if (val1Loc > inputs.size()) {
				std::cout << "Value(BB): " << val1Loc;
			}
			else {
				std::cout << "Value: " << inputs[val1Loc];
			}
			//std::cout << "Value: " << inputs[val1Loc];

			numParams = 2;
		}

		//jump if true
		else if (opCode == 5) {
			secParam = inputs[idx + 2];

			if (secondParamImmediateMode) {
				val2Loc = inputs[idx + 2];
			}
			else {
				val2Loc = secParam;
			}

			int value1(firstParam);
			int value2(secParam);

			if (!firstParamImmediateMode) {
				value1 = inputs[val1Loc];
			}
			if (!secondParamImmediateMode) {
				value2 = inputs[val2Loc];
			}

			if (value1 != 0) {
				idx = value2;
				numParams = 0;
			}
			else {
				numParams = 3;
			}
		}

		//jump if false
		else if (opCode == 6) {
			secParam = inputs[idx + 2];

			if (secondParamImmediateMode) {
				val2Loc = inputs[idx + 2];
			}
			else {
				val2Loc = secParam;
			}

			int value1(firstParam);
			int value2(secParam);

			if (!firstParamImmediateMode) {
				value1 = inputs[val1Loc];
			}
			if (!secondParamImmediateMode) {
				value2 = inputs[val2Loc];
			}

			if (value1 == 0) {
				idx = value2;
				numParams = 0;
			}
			else {
				numParams = 3;
			}
		}

		//Less than
		else if (opCode == 7) {

			secParam = inputs[idx + 2];
			thirdParam = inputs[idx + 3];

			if (secondParamImmediateMode) {
				val2Loc = inputs[idx + 2];
			}
			else {
				val2Loc = secParam;
			}

			if (thirdParamImmediateMode) {
				val3Loc = inputs[idx + 3];
			}
			else {
				val3Loc = thirdParam;
			}

			int value1(firstParam);
			int value2(secParam);

			if (!firstParamImmediateMode) {
				value1 = inputs[val1Loc];
			}
			if (!secondParamImmediateMode) {
				value2 = inputs[val2Loc];
			}

			if (value1 < value2) {
				inputs[val3Loc] = 1;
			}
			else {
				inputs[val3Loc] = 0;
			}

			numParams = 4;
		}

		//Equals
		else if (opCode == 8) {
			secParam = inputs[idx + 2];
			thirdParam = inputs[idx + 3];

			if (secondParamImmediateMode) {
				val2Loc = inputs[idx + 2];
			}
			else {
				val2Loc = secParam;
			}

			if (thirdParamImmediateMode) {
				val3Loc = inputs[idx + 3];
			}
			else {
				val3Loc = thirdParam;
			}

			int value1(firstParam);
			int value2(secParam);

			if (!firstParamImmediateMode) {
				value1 = inputs[val1Loc];
			}
			if (!secondParamImmediateMode) {
				value2 = inputs[val2Loc];
			}

			if (value1 == value2) {
				inputs[val3Loc] = 1;
			}
			else {
				inputs[val3Loc] = 0;
			}

			numParams = 4;
		}

		//Cease
		else if (opCode == 99) {
			numParams = 1;
			break;
		}

		else {
			std::cout << "Bad juju... how did I get an unknown opCode?" << std::endl;
		}

		idx += numParams;
	}

	return inputs[0];
}

int main(int argc, char* argv[]) {

	int ret(0);
	int temp(0);

	std::vector<int> inputs;
	std::string line;

	std::getline(std::cin, line);

	std::stringstream ss(line);

	for (int i; ss >> i;) {
		inputs.push_back(i);
		if (ss.peek() == ',')
			ss.ignore();
	}


	part1(inputs);
}