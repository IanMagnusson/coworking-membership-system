/*
	ActivityEvent.h
		code by Jack Magnusson 5/4/18
		Final Assignment csci-e53
*/

#pragma once

#include <iostream>
#include <ctime>
#include "Location.h"

struct ActivityEvent
{
	unsigned m_associatedMember;
	time_t m_timeIn;
	Location m_loc;

public:
	unsigned getMemberId() const;
};

enum MeetingRoom
{
	ROOM1,
	ROOM2,
	ROOM3,
	ROOM4,
	ROOM5,
	ROOM6,
	ROOM7,
	ROOM8,
	ROOM9,
	ROOM10
};

struct MeetingEvent : public ActivityEvent
{
	time_t m_timeOut;
	MeetingRoom m_meetingRoom;
};