/* elevator.cpp
 *
 * Mike Henderson
 * June 2026
 */

#include <iostream>
#include <cmath>

#include "elevator.h"
#include "exception.h"



Elevator::Elevator(double floorTravelTimeSeconds, unsigned int initialFloor) :
    mFloorTravelTimeSeconds(floorTravelTimeSeconds),
    mFloor(initialFloor)
{
    mTravelHistory[0] = mFloor;
}


void Elevator::Visit(const FloorSet& newFloorsIn, Direction initialDirection)
{
    FloorSet newFloors = newFloorsIn;

    // remove the current floor from the set, if present
    newFloors.erase(mFloor);

    if (newFloors.empty())
    {
        return;
    }

    // Visit all floors in one direction ('up' or 'down') before visiting any
    // floors in the other. This obeys elevator convention.
    FloorSet::iterator upIt = newFloors.lower_bound(mFloor);   // >=
    FloorSet::iterator downIt = upIt;

    switch (initialDirection)
    {
        case eUp:
            TravelUp(upIt, newFloors);
            TravelDown(downIt, newFloors);
            break;

        case eDown:
            TravelDown(downIt, newFloors);
            TravelUp(upIt, newFloors);
            break;
    }
}

void Elevator::Visit(const FloorList& newFloors)
{
    for (FloorList::const_iterator it = newFloors.begin(); it != newFloors.end(); ++it)
    {
        double travelTime = abs(*it - mFloor) * mFloorTravelTimeSeconds;
        mFloor = *it;
        mTravelHistory[travelTime + mTravelHistory.rbegin()->first] = mFloor;
    }
}

void Elevator::TravelUp(FloorSet::const_iterator& it, const FloorSet& newFloors)
{
    while (it != newFloors.end())
    {
        double travelTime = (*it - mFloor) * mFloorTravelTimeSeconds;
        mFloor = *it;
        mTravelHistory[travelTime + mTravelHistory.rbegin()->first] = mFloor;
        ++it;
    }
}

void Elevator::TravelDown(FloorSet::const_iterator& it, const FloorSet& newFloors)
{
    while (it != newFloors.begin())
    {
        --it;
        double travelTime = (mFloor - *it) * mFloorTravelTimeSeconds;
        mFloor = *it;
        mTravelHistory[travelTime + mTravelHistory.rbegin()->first] = *it;
    }
}

void Elevator::PrintHistory(std::ostream& os) const
{
    os << mTravelHistory.rbegin()->first << " ";

    for (FloorHistory::const_iterator it = mTravelHistory.begin(); it != mTravelHistory.end();)
    {
        os << it->second;
        ++it;
        if (it != mTravelHistory.end())
            os << ",";
    }
    os << std::endl;
}

void Elevator::PrintFullHistory(std::ostream& os) const
{
    for (FloorHistory::const_iterator it = mTravelHistory.begin(); it != mTravelHistory.end(); ++it)
    {
        os << "floor " << it->second << ": " << it->first << std::endl;
    }
}