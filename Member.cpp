/*
	Member.h
		code by Jack Magnusson 4/29/18
		Final Assignment csci-e53
*/
#include "Member.h"

using namespace std;

// constructor
Member::Member(unsigned id, unsigned acct, const std::string & name,
		const std::string & company, const Product & membership, Location loc):
	m_id(id),
	m_accountId(acct),
	m_name(name),
	m_company(company),
	m_membershipType(membership.getName()),
	m_homeLocation(loc),
	m_joinDate(currentTime),
	m_daysLeft(membership.getDays()),
	m_daysPerMonth(m_daysLeft)
{}

// display
void Member::display() const
{
	cout << endl << "member ID: " << m_id << endl;
	cout << "associated acount ID: " << m_accountId << endl;
	cout << "name: " << m_name << endl;
	cout << "company: " << m_company << endl;
	cout << "membership type: " << m_membershipType << endl;
	cout << "location: " << loc2String(m_homeLocation) << endl;
	cout << "join date: " << m_joinDate << endl;
	cout << "days left: " << (m_daysLeft >= 0 ? to_string(m_daysLeft) : "unlimited") << endl;
}

// adjusts membershipType and usage allocations
void Member::changeMembership(const Product & newMembership)
{
	m_membershipType = newMembership.getName();
	m_daysPerMonth = m_daysLeft = newMembership.getDays();
}

// consumes day presence usage allocations, if out returns 1 to indicate overage
int Member::useDayIfAny()
{
	if (m_daysLeft)
	{
		--m_daysLeft;
		return 0;
	}
	else
		return 1; // returns overage
}

// set day usage allocation to max
void Member::resetDays()
{
	m_daysLeft = m_daysPerMonth;
}

////////////////////////////// get methods ////////////////////////////////

unsigned Member::getId() const
{
	return m_id;
}

unsigned Member::getAccountId() const
{
	return m_accountId;
}

std::string Member::getName() const
{
	return m_name;
}

std::string Member::getCompany() const
{
	return m_company;
}

std::string Member::getMembershipType() const
{
	return m_membershipType;
}
