/*
	CachedData.cpp
		code by Jack Magnusson 5/10/18
		Final Assignment csci-e53
*/

#include "CachedData.h"
#include "Database.h"	// this feels wrong but is avoid circular dependencies
using namespace std;

// Destructor

CachedData::~CachedData()
{
	for (Member *memb : m_memb)
	{
		m_dbFrom->commitMember(*memb);
		delete memb;
	}
	
	for (Account *acct : m_acct)
	{
		m_dbFrom->commitAccount(*acct);
		delete acct;
	}	
	for (RecurringService *recur : m_recur)
	{
		m_dbFrom->commitRecurringService(*recur);
		delete recur;
	}
}


// get last element methods

const Product & CachedData::getProd() const
{
	if (m_prod.size())
		return *(m_prod.back());
	else
		throw out_of_range("CachedData::getProd failed: no pointer Cached");
}

Member & CachedData::getMemb() 
{
	if (m_memb.size())
		return *(m_memb.back());
	else
		throw out_of_range("CachedData::getMemb failed: no pointer Cached");
}

Account & CachedData::getAcct() 
{
	if (m_acct.size())
		return *(m_acct.back());
	else
		throw out_of_range("CachedData::getAcct failed: no pointer Cached");
}

RecurringService & CachedData::getRecur() 
{
	if (m_recur.size())
		return *(m_recur.back());
	else
		throw out_of_range("CachedData::getRecur failed: no pointer Cached");
}

const Charge & CachedData::getCharge() const
{
	if (m_charge.size())
		return *(m_charge.back());
	else
		throw out_of_range("CachedData::getCharge failed: no pointer Cached");
}


// adds objects to storage ( dynamically alloced copies for Memb, acct, recur )

CachedData & CachedData::pushProd(const Product & prod)
{
	m_prod.push_back(&prod);
	return *this;
}

CachedData & CachedData::pushCharge(const Charge & charge)
{
	m_charge.push_back(&charge);
	return *this;
}

CachedData & CachedData::pushMemb(const Member & memb)
{
	m_memb.push_back(allocObj(memb));
	return *this;
}

CachedData & CachedData::pushAcct(const Account & acct)
{
	m_acct.push_back(allocObj(acct));
	return *this;
}

CachedData & CachedData::pushRecur(const RecurringService & recur)
{
	 m_recur.push_back(allocObj(recur));
	 return *this;
}
