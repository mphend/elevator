/* elevator.h
 *
 * Mike Henderson
 * June 2026
 */

#include <iosfwd>
#include <list>
#include <map>
#include <set>

typedef std::set<unsigned int> FloorSet;
typedef std::list<unsigned int> FloorList;
typedef std::map<double, unsigned int> FloorHistory;

enum Direction {eUp, eDown };

// class Elevator : tracks state and history of an elevator car
class Elevator
{
public:
    Elevator(double floorTravelTimeSeconds, unsigned int initialFloor);

    // visit a set of floors
    // This will obey normal elevator convention, that the car has a current
    // direction (up, or down), and will visit the floors in that direction
    // first before reversing and going to others that require movement in
    // the opposite direction.
    void Visit(const FloorSet& newFloors, Direction initialDirection);

    // visit the floors strictly in the order given, such as a delivery
    // system with a schedule would use.
    void Visit(const FloorList& newFloors);

    // output the travel history; floors visited and final time
    void PrintHistory(std::ostream& os) const;

    // output the full travel history; floors visited and time of each floor
    void PrintFullHistory(std::ostream& os) const;

private:
    const double mFloorTravelTimeSeconds; // time to move between adjacent floors, in seconds
    unsigned int mFloor; // current floor

    // floors visited keyed on travel time
    FloorHistory mTravelHistory;

    void TravelUp(FloorSet::const_iterator& i, const FloorSet& newFloors);
    void TravelDown(FloorSet::const_iterator& i, const FloorSet& newFloors);
};
