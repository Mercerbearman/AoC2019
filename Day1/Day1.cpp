#include <iostream>

int CalcFuelForModule(int mass) {

	int retval(0);
	retval = static_cast<int> (mass / 3) - 2;

	if (retval < 0)
		retval = 0;
	return retval;
}


int main(int argc, char* argv[]) {

	int totalWeight(0);
	int modWeight(0);

	while (std::cin >> modWeight) {
		int fuel(modWeight);
		modWeight = 0;
		while (fuel > 0) {
			fuel = CalcFuelForModule(fuel);
			modWeight += fuel;
		}

		totalWeight += modWeight;
		
	}

	std::cout << "totalWeight is: " << totalWeight << std::endl;

}
