/*
	Location.cpp
		code by Jack Magnusson 4/29/18
		Final Assignment csci-e53
*/

#include "Location.h"

using namespace std;

std::string loc2String(Location loc)
{
	static const char * LOCATIONNAMES[] =
	{ "New York", "Boston", "Los Angeles", "San Francisco" };
	return LOCATIONNAMES[loc];
}

/*
// not working due to int conversion!
std::ostream & operator<<(std::ostream & out, Location & loc)
{
	const char * LOCATIONNAMES[] = { "New York", "Boston", "Los Angeles", "San Francisco" };
	out << LOCATIONNAMES[loc];
	return out;
}
*/