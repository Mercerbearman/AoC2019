#include <string>
#include <iostream>
#include <map>

enum Dir {
    UpDown,
    LeftRight
};

struct Point {
    int X;
    int Y;

    Point() : X(0), Y(0) {}
};

enum Wires {
    One,
    Two,
    Both
};

void AddPointToMap(std::map<Point, Wires> &map, Wires curWire, Point curPoint) {

    Wires temp;
    //See if the point already has a wire associated with it.
    try {
        temp = map.at(curPoint);

        //Wires are the same, do nothing.
        if (temp == curWire) {
            return;
        }
        else {
            temp = Both;
        }

    }
    //Insertion failed, we didn't have the point.  So create one with our current wire.
    catch (std::exception e) {
        map[curPoint] = curWire;
    }

}

Point AddSegmentToMap(std::map<Point, Wires> &map, Dir direction, int mag, Point startingPoint, Wires curWire) {

    int segStart(0);
    int segEnd(0);
    if (direction == UpDown) {
        if (mag < 0) {
            segStart = startingPoint.Y + mag;
            segEnd = startingPoint.Y;
        }
        else {
            segStart = startingPoint.Y;
            segEnd = startingPoint.Y + mag;
        }

        Point temp;
        temp.X = startingPoint.X;
        for (int ix = segStart; ix < segEnd; ++ix) {
            temp.Y = ix;
            AddPointToMap(map, curWire, temp);
        }
    }
    else {
        if (mag < 0) {
            segStart = startingPoint.X + mag;
            segEnd = startingPoint.X;
        }
        else {
            segStart = startingPoint.X;
            segEnd = startingPoint.X + mag;
        }
    }
    

}

int main(int argc, char* argv[]) {
    char dir, _;
    int mag(0);
    Dir direction;
    Point startingPoint;
    Wires wire = One;

    std::map<Point, Wires> myMap;

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

        startingPoint = AddSegmentToMap(myMap, direction, mag, startingPoint, wire);

        // Reset, search for wire 2.
        if (_ == '\n' && wire == One) {
            std::cout << "new line detected with " << "Mag: " << mag << std::endl;
            wire = Two;
            startingPoint.X = 0;
            startingPoint.Y = 0;
        }

    }
}