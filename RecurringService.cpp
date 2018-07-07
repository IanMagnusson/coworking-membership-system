/*
	RecurringService.cpp
		code by Jack Magnusson 5/3/18
		Final Assignment csci-e53
*/

#include "RecurringService.h"

using namespace std;


////////////////////////// constructors /////////////////////////////

RecurringService::RecurringService(unsigned id, unsigned acctId, const Product & prod, unsigned membId) :
	m_id(id),
	m_associatedAccount(acctId),
	m_associatedMember(membId),
	m_productName(prod.getName()),
	m_price(prod.getPrice()),
	m_billingPeriod(prod.getBillingPeriod()),
	m_lastBilledOn(-m_billingPeriod),		// so it always bills the first time
	m_startedOn(currentTime)
{
	if (m_productName == "Inactive")
		m_endingOn = 0;
}

RecurringService::RecurringService(unsigned id, const Member & memb, const Product & prod):
	m_id(id),
	m_associatedAccount(memb.getAccountId()),
	m_associatedMember(memb.getId()),
	m_productName(prod.getName()),
	m_price(prod.getPrice()),
	m_billingPeriod(prod.getBillingPeriod()),
	m_lastBilledOn(-m_billingPeriod),		// so it always bills the first time
	m_startedOn(currentTime)
{
	if (m_productName == "Inactive")
		m_endingOn = 0;
}

// WARNING: memb and prod must be Cached!!!!
RecurringService::RecurringService(unsigned id, CachedData &cd) :
	m_id(id),
	m_associatedAccount(cd.getMemb().getAccountId()),
	m_associatedMember(cd.getMemb().getId()),
	m_productName(cd.getProd().getName()),
	m_price(cd.getProd().getPrice()),
	m_billingPeriod(cd.getProd().getBillingPeriod()),
	m_lastBilledOn(-m_billingPeriod),		// so it always bills the first time
	m_startedOn(currentTime)
{
	if (m_productName == "Inactive")
		m_endingOn = 0;
}

// display
void RecurringService::display() const
{
	cout << endl << "recurring service ID: " << m_id << endl;
	cout << "associated account ID: " << m_associatedAccount << endl;
	cout << "associated member ID: " << m_associatedMember << endl;
	cout << "product type: " << m_productName << endl;
	cout << "price: " << m_price << endl;
	cout << "billing Period: " << m_billingPeriod << endl;
	cout << "last billed on: " << m_lastBilledOn << endl;
	cout << "started on: " << m_startedOn << endl;
	cout << "ending on: " << (m_endingOn >= 0 ? to_string(m_endingOn) : "not set") << endl;
}

// returns true if billing needed; assumes billing carried out and updates lastBilledOn
bool RecurringService::billMeIfTime()
{
	// check RecurringService is still active
	if (!(m_endingOn < 0) && m_endingOn <= currentTime)
		return false;

	// check if billing period has elapse since last billing
	if ((currentTime - m_lastBilledOn) >= m_billingPeriod)
	{
		m_lastBilledOn = currentTime;
		return true;
	}
	else
		return false;
}

////////////////////////// set methods ////////////////////////////

void RecurringService::setPrice(double newPrice)
{
	m_price = newPrice;
}

void RecurringService::setBillingPeriod(time_t newBillingPeriod)
{
	m_billingPeriod = newBillingPeriod;
}

void RecurringService::setEndingOn(time_t newEndingOn)
{
	m_endingOn = newEndingOn;
}

//////////////////////////////// get methods ///////////////////////////////////////////

unsigned RecurringService::getId() const
{
	return m_id;
}

unsigned RecurringService::getAccount() const
{
	return m_associatedAccount;
}

unsigned RecurringService::getMember() const
{
	return m_associatedMember;
}

std::string RecurringService::getProductName()
{
	return m_productName;
}

double RecurringService::getPrice()
{
	return m_price;
}

time_t RecurringService::getBillingPeriod()
{
	return m_billingPeriod;
}

time_t RecurringService::getLastBilledOn()
{
	return m_lastBilledOn;
}
