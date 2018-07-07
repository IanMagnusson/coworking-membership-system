/*
	Account.h
		code by Jack Magnusson 5/3/18
		Final Assignment csci-e53
*/

#pragma once

#include <iostream>
#include <ctime>
#include <set>
#include "Member.h"
#include "Product.h"
#include "CachedData.h"

extern time_t currentTime;

/*
	Stores shared info and tracks shared usage allotments
*/

class Account
{
private:
	unsigned m_id, m_owner;
	std::string m_company;
	time_t m_dateCreated;
	int m_meetingRoomHoursLeft, m_meetingRoomHoursPerMonth;
	std::set<unsigned> m_members;
	

public:
	Account(const Member & memb, const Product &prod);
	Account(CachedData &cd); //NOTE: CachedData MUST CONTAIN MEMBER AND PRODUCT

	void addMember(const Member & memb, const CachedData & cd);
	void changeMembership(const Product & newProd, const Product & oldProd);
	void changeOwner(const Member & memb);

	int useMeetingRoomHoursIfAny(unsigned hoursUsed); //returns number of overages if any
	void resetMeetingRoomHours();

	void display() const;

	// get methods
	unsigned getId() const;
	unsigned getOwnerId() const;
	
};
