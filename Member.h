/*
	Member.h
		code by Jack Magnusson 4/29/18
		Final Assignment csci-e53
*/

#pragma once

#include <iostream>
#include <string>
#include <ctime>
#include "Location.h"
#include "Product.h"

extern time_t currentTime;

/*
	Stores info about an individual and tracks individual usage alotments (day presence)
*/

class Member
{
private:
	unsigned m_id, m_accountId;
	std::string m_name, m_company, m_membershipType;
	Location m_homeLocation;
	time_t m_joinDate;
	int m_daysLeft, m_daysPerMonth;

public:
	Member(unsigned id, unsigned acct, const std::string & name,
		const std::string & company, const Product &membership, Location loc);

	void display() const;

	void changeMembership(const Product &newMembership);
	int useDayIfAny();		// returns 1 if overage, 0 if not
	void resetDays();

	// get methods
	unsigned getId() const;
	unsigned getAccountId() const;
	std::string getName() const;
	std::string getCompany() const;
	std::string getMembershipType() const;
};