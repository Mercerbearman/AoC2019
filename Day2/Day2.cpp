#include <iostream>
#include <vector>

int part1(int noun, int verb, std::vector<int> inputs) {
	int opCode(0);
	int oper1Loc(0);
	int oper2Loc(0);
	int resultLoc(0);

	//Seed the program with 1202.
	inputs[1] = noun;
	inputs[2] = verb;

	int result(0);
	//skip by 4.
	for (unsigned int idx = 0; idx < (inputs.size() - 4); idx += 4) {

		if (inputs.size() < idx + 4) {
			break;
		}
		opCode = inputs[idx];
		oper1Loc = inputs[idx + 1];
		oper2Loc = inputs[idx + 2];
		resultLoc = inputs[idx + 3];

		if (opCode == 1) {
			result = inputs[oper1Loc] + inputs[oper2Loc];
			inputs[resultLoc] = result;
		}
		else if (opCode == 2) {
			result = inputs[oper1Loc] * inputs[oper2Loc];
			inputs[resultLoc] = result;
		}
		else if (opCode == 99) {
			break;
		}
	}

	return inputs[0];
}

int main(int argc, char* argv[]) {

	int ret(0);
	int noun(0);
	int verb(0);
	int temp(0);
	const int answer(19690720);

	std::vector<int> inputs;
	char _; // This will handle the ',' crap.

	while (std::cin >> temp >> _) {
		inputs.push_back(temp);
	}

	for (int noun = 0; noun < 100; ++noun) {
		for (int verb = 0; verb < 100; ++verb) {
			ret = part1(noun, verb, inputs);
			if (ret == answer) {
				std::cout << "Answer found: " << 100 * noun + verb << std::endl;
			}
		}
	}
}