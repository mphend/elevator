/* main.cpp : elevator simulator

   Mike Henderson
   June 2026
*/

#include <iostream>

#include "exception.h"
#include "elevator.h"

void
Usage()
{
    printf("Usage: elevator [--human <'u' or 'd'>] <initialFloor> <space separated floor list>\n");
    printf("    --human : visit floors with typical people-elevator policy,\n");
    printf("              visiting all floors in one direction before any in the other.\n");
    printf("              'u' or 'd' indicates initial direction of up or down\n");
    printf("              The default behavior visits the floors in the strict order given\n");
}

int main(int argc, char** argv)
{
    try
    {
        const double floorTravelTimeSeconds = 10;

        if (argc < 3)
        {
            Usage();
            return 1;
        }

        // XXX no input validation is performed below
        bool human = false;
        Direction direction;
        if (std::string(argv[1]) == "--human")
        {
            human = true;
            if (std::string(argv[2]) == "u")
                direction = eUp;
            else if (std::string(argv[2]) == "d")
                direction = eDown;
            else
            {
                Usage();
                return 1;
            }
        }

        FloorSet floorSet;
        FloorList floorList;
        int initialFloor = 1;
        if (human)
        {
            if (argc < 5)
            {

                Usage();
                return 1;
            }

            initialFloor = atoi(argv[3]);
            for (size_t i = 4; i < argc; i++)
                floorSet.insert(atoi(argv[i]));
        }
        else
        {
            initialFloor = atoi(argv[1]);
            for (size_t i = 2; i < argc; i++)
               floorList.push_back(atoi(argv[i]));
        }

        Elevator elevator(floorTravelTimeSeconds, initialFloor);
        if (human)
            elevator.Visit(floorSet, direction);
        else
            elevator.Visit(floorList);

        elevator.PrintHistory(std::cout);

        if (false)
        {
            printf(("Regression testing\n----------------------\n"));
            Elevator elevator2(floorTravelTimeSeconds, 12);

            elevator2.Visit({2, 3, 4, 14, 15}, eUp);
            elevator2.Visit({1, 2, 3, 4, 14, 15}, eDown);
            elevator2.PrintFullHistory(std::cout);
        }

        return 0; // success
    }
    catch (const Exception& e)
    {
        std::cout << "Error: " << e.what() << std::endl;
    }
    catch (...)
    {
        std::cout << "Unknown exception" << std::endl;
    }
    return 1; // error
}