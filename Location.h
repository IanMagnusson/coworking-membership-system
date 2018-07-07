/*
	Location.h
		code by Jack Magnusson 4/29/18
		Final Assignment csci-e53
*/

#pragma once

#include <string>
#include <stdexcept>

enum Location 
{
	NYC,
	BOS,
	LA,
	SF
};

std::string  loc2String(Location loc);

// std::ostream & operator<< (std::ostream &out, Location &loc); // not working due to int conversion!