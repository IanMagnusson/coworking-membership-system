/*
	RecurringService.h
		code by Jack Magnusson 5/3/18
		Final Assignment csci-e53
*/

#pragma once

#include <iostream>
#include <string>
#include <ctime>
#include "Product.h"
#include "Member.h"
#include "CachedData.h"

extern time_t currentTime;

/*
	a record of an individual service contract that allows modification of default values. Also
	used to generage Charges at regular billing periods. Use with mailing, storage, memberships.
*/

class RecurringService
{
private:
	unsigned m_id, m_associatedAccount, m_associatedMember;
	std::string m_productName;
	double m_price;
	time_t m_billingPeriod, m_lastBilledOn, m_startedOn, m_endingOn = -1;	// end defualts to max time;

public:
	RecurringService(unsigned id, unsigned acctId, const Product & prod, unsigned membId = 0);
	RecurringService(unsigned id, const Member &memb, const Product &prod);
	RecurringService(unsigned id, CachedData &cd); // NOTE: memb and prod must be Cached

	void display() const;
	bool billMeIfTime();	// returns true if billing needed

	// set methods
	void setPrice(double newPrice);	// cant go negative and round to cents
	void setBillingPeriod(time_t newBillingPeriod);
	void setEndingOn(time_t newEndingOn);
	// get methods
	unsigned getId() const;
	unsigned getAccount() const;
	unsigned getMember() const;
	std::string getProductName();
	double getPrice();
	time_t getBillingPeriod();
	time_t getLastBilledOn();
};