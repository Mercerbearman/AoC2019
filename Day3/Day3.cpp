#include <string>
#include <iostream>
#include <map>
#include <set>

enum Dir {
    UpDown,
    LeftRight
};

struct Point {
    int X;
    int Y;

    Point() : X(0), Y(0) {}

	friend bool operator<(const Point& l, const Point& r) {
		return std::tie(l.X, l.Y)
			< std::tie(r.X, r.Y);
	}
};

enum Wires {
    One,
    Two,
    Both
};

struct PointData{
	Wires wire;
	unsigned int steps[2];

	PointData() : wire(One) {
		steps[0] = 1000000000;
		steps[1] = 1000000000;
	}
};

std::map<Point, unsigned int> crossings;

void AddPointToMap(std::map<Point, PointData> &map, const Wires &curWire, const Point &curPoint, unsigned int &steps) {
    //See if the point already has a wire associated with it.

	unsigned int idx(0);
	unsigned int otherIdx(0);
	if (curWire == One) {
		idx = 0;
		otherIdx = 1;
	}
	else if (curWire == Two) {
		idx = 1;
		otherIdx = 0;
	}

	auto search = map.find(curPoint);

	++steps;

	//If we found our point... do some stuff.
	if (search != map.end()) {

		//If we are crossing our own wire, who cares.
		if (search->second.wire == curWire) {
			return;
		}
		//If we have already been to this intersection... skip
		else if (search->second.wire == Both) {
			//Already been here.  Return;
			return;
		}
		else {
			search->second.wire = Both;
			//steps--;
			auto x = search->second.steps[idx];

			if (x == 0) {
				search->second.steps[idx] = steps;
				crossings[search->first] = steps + map[curPoint].steps[otherIdx];
			}
			else if (steps <= x) {
				search->second.steps[idx] = steps;
				crossings[search->first] = steps + map[curPoint].steps[otherIdx];
			}
			
		}
	}
	//Enter a new point into our map.
	else {
		PointData data;
		data.wire = curWire;
		data.steps[idx] = steps;
		map[curPoint] = data;
	}
}

Point AddSegmentToMap(std::map<Point, PointData> &map, Dir direction, int mag, Point startingPoint, Wires curWire, unsigned int &steps) {

    int segStart(0);
    int segEnd(0);
	Point temp, endingPoint;
    if (direction == UpDown) {
        if (mag < 0) {
            segStart = startingPoint.Y + mag;
			segEnd = startingPoint.Y;
			endingPoint.Y = segStart;
        }
        else {
            segStart = startingPoint.Y;
            segEnd = startingPoint.Y + mag;
			endingPoint.Y = segEnd;
        }

		endingPoint.X = startingPoint.X;
        temp.X = startingPoint.X;
        for (int ix = segStart; ix < segEnd; ++ix) {
            temp.Y = ix;
            AddPointToMap(map, curWire, temp, steps);
        }
    }
    else {
        if (mag < 0) {
            segStart = startingPoint.X + mag;
            segEnd = startingPoint.X;
			endingPoint.X = segStart;
        }
        else {
            segStart = startingPoint.X;
            segEnd = startingPoint.X + mag;
			endingPoint.X = segEnd;
        }

		endingPoint.Y = startingPoint.Y;
		temp.Y = startingPoint.Y;
		for (int ix = segStart; ix < segEnd; ++ix) {
			temp.X = ix;
			AddPointToMap(map, curWire, temp, steps);
		}
    }
    
	//Location of last point in line.
	return endingPoint;
}

int main(int argc, char* argv[]) {
    char dir, _;
    int mag(0);
    Dir direction = UpDown;
    Point startingPoint;
    Wires wire = One;
	unsigned int stepsForWire(0);

    std::map<Point, PointData> myMap;

    std::cin >> std::noskipws;

    while (std::cin >> dir >> mag >> _) {

        switch (dir) {
            case 'U':
            direction = UpDown;
            break;
            case 'D':
            direction = UpDown;
            mag *= -1;
            break;
            case 'L':
            direction = LeftRight;
            mag *= -1;
            break;
            case 'R':
            direction = LeftRight;
            break;
        }

        startingPoint = AddSegmentToMap(myMap, direction, mag, startingPoint, wire, stepsForWire);

        // Reset, search for wire 2.
        if (_ == '\n' && wire == One) {
            std::cout << "new line detected with " << "Mag: " << mag << std::endl;
            wire = Two;
            startingPoint.X = 0;
            startingPoint.Y = 0;
			stepsForWire = 0;
        }
		else if (_ == '\n' && wire == Two) {
			break; //We done.
		}

    }

	//Remove the origin
	startingPoint = Point();
	crossings.erase(startingPoint);

	unsigned int manDist(1000000000000);
	Point tempDist;
	unsigned int minSteps(0);
	auto itr = crossings.begin();
	minSteps = itr->second;
	//Get the manhattan distance.
	while (crossings.end() != itr) {
		tempDist.X = itr->first.X;
		tempDist.Y = itr->first.Y;

		if (tempDist.X < 0) tempDist.X *= -1;
		if (tempDist.Y < 0) tempDist.Y *= -1;

		if (manDist > (tempDist.X + tempDist.Y)) {
			manDist = tempDist.X + tempDist.Y;
			startingPoint = tempDist;
		}

		//Now get the smallest steps.
		if (minSteps > itr->second) {
			minSteps = itr->second;
		}

		itr++;
	}

	std::cout << "Min Manhat Dist: " << manDist << "at Point: (" << startingPoint.X << ", " << startingPoint.Y << ")" << std::endl;

	std::cout << "Min Steps: " << minSteps << "With " << crossings.size() << " crossings." << std::endl;
}