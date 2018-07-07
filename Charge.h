/*
	Charge.h
		code by Jack Magnusson 5/3/18
		Final Assignment csci-e53
*/

#pragma once

#include <iostream>
#include <ctime>
#include <set>
#include <string>
#include "Product.h"
#include "RecurringService.h"

extern time_t currentTime;

/*
	an invoice for a particular product or service fee
*/

class Charge
{
private:
	unsigned m_id, m_associatedAccount, m_associatedMember, m_quantity;
	double m_unitPrice;
	std::string m_productName;
	time_t m_issuedOn;

public:
	Charge(unsigned id, RecurringService &source);
	Charge(unsigned id, unsigned acctID, unsigned memberID, unsigned quantity, const Product &source);
	Charge(unsigned id, unsigned quantity, CachedData &cd);	// WARNING: Memb and Prod must be loaded in Cache
	void display() const;
	unsigned getId() const;
};
