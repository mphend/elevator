/* elevator.cpp
 *
 * Mike Henderson
 * June 2026
 */

#include <iostream>
#include <cmath>

#include "elevator.h"
#include "exception.h"



Elevator::Elevator(double floorTravelTime, unsigned int initialFloor) :
    mFloorTravelTimeSeconds(floorTravelTime),
    mFloor(initialFloor)
{
    mTravelHistory[0] = mFloor;
}


void
Elevator::Visit(const FloorSet& newFloorsIn, Direction initialDirection)
{
    FloorSet newFloors = newFloorsIn;

    // remove the current floor from the set, if present
    newFloors.erase(mFloor);

    if (newFloors.empty())
        return;

    // Visit all floors in one direction ('up' or 'down') before visiting any
    // floors in the other. This obeys elevator convention.
    FloorSet::iterator upIt = newFloors.lower_bound(mFloor);   // >=
    FloorSet::iterator downIt = upIt;
    //if (downIt != newFloors.begin())
    //    --downIt;

    // up travel
    if (initialDirection == eUp)
    {
        TravelUp(upIt, newFloors);
        TravelDown(downIt, newFloors);
    }
    else
    {
        TravelDown(downIt, newFloors);
        TravelUp(upIt, newFloors);
    }
}

void
Elevator::Visit(const FloorList& newFloors)
{
    FloorList::const_iterator i = newFloors.begin();
    for ( ; i != newFloors.end(); ++i)
    {
        double travelTime = abs(*i - mFloor) * mFloorTravelTimeSeconds;
        mFloor = *i;
        mTravelHistory[travelTime + mTravelHistory.rbegin()->first] = mFloor;
    }
}

void
Elevator::TravelUp(FloorSet::const_iterator& i, const FloorSet& newFloors)
{
    while (i != newFloors.end())
    {
        double travelTime = (*i - mFloor) * mFloorTravelTimeSeconds;
        mFloor = *i;
        mTravelHistory[travelTime + mTravelHistory.rbegin()->first] = mFloor;
        i++;
    }
}

void
Elevator::TravelDown(FloorSet::const_iterator& i, const FloorSet& newFloors)
{
    while (i != newFloors.begin())
    {
        i--;
        double travelTime = (mFloor - *i) * mFloorTravelTimeSeconds;
        mFloor = *i;
        mTravelHistory[travelTime + mTravelHistory.rbegin()->first] = *i;
    }
}

void
Elevator::PrintHistory(std::ostream& os) const
{
    os << mTravelHistory.rbegin()->first << " ";

    for (FloorHistory::const_iterator i = mTravelHistory.begin(); i != mTravelHistory.end();)
    {
        os << i->second;
        i++;
        if (i != mTravelHistory.end())
            os << ",";
    }
    os << std::endl;
}

void
Elevator::PrintFullHistory(std::ostream& os) const
{
    for (FloorHistory::const_iterator i = mTravelHistory.begin(); i != mTravelHistory.end(); ++i)
        os << "floor " << i->second << ": " << i->first << std::endl;
}