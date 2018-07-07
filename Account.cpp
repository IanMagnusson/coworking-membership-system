/*
	Account.cpp
		code by Jack Magnusson 5/3/18
		Final Assignment csci-e53
*/

#include "Account.h"

using namespace std;

// constructor
Account::Account(const Member & memb, const Product &prod) :
	m_id(memb.getAccountId()),
	m_owner(memb.getId()),
	m_company(memb.getCompany()),
	m_dateCreated(currentTime),
	m_meetingRoomHoursLeft(prod.getMeetingRoomHours()),
	m_meetingRoomHoursPerMonth(m_meetingRoomHoursLeft),
	m_members({ memb.getId() })
{}

// constructor NOTE: CachedData MUST CONTAIN MEMBER AND PRODUCT
Account::Account(CachedData & cd) :
	m_id(cd.getMemb().getAccountId()),
	m_owner(cd.getMemb().getId()),
	m_company(cd.getMemb().getCompany()),
	m_dateCreated(currentTime),
	m_meetingRoomHoursLeft(cd.getProd().getMeetingRoomHours()),
	m_meetingRoomHoursPerMonth(m_meetingRoomHoursLeft),
	m_members({ cd.getMemb().getId() })
{}

// adds member to account and adjusts usage allocations
void Account::addMember(const Member & memb, const CachedData & cd)
{
	m_meetingRoomHoursPerMonth += cd.getProd().getMeetingRoomHours();
	m_meetingRoomHoursLeft += cd.getProd().getMeetingRoomHours();
	m_members.insert(memb.getId());
}

// adjusts usage allocations
void Account::changeMembership(const Product & newProd, const Product & oldProd)
{
	int changeInHours = newProd.getMeetingRoomHours() - oldProd.getMeetingRoomHours();
	m_meetingRoomHoursPerMonth += changeInHours;
	if ((m_meetingRoomHoursLeft += changeInHours) < 0)
		m_meetingRoomHoursLeft = 0;
}

void Account::changeOwner(const Member & memb)
{
	// check that new owner is in account
	if (m_members.find(memb.getId()) == m_members.end())
		throw out_of_range("changeOwner failed: member not in account");
	// set
	m_owner = memb.getId();
	m_company = memb.getCompany();
}

// consumes meeting room usage allocations, if out returns number of overages
int Account::useMeetingRoomHoursIfAny(unsigned hoursUsed)
{
	// if enough hours left to cover, consume hours 
	if ((m_meetingRoomHoursLeft - static_cast<int>(hoursUsed)) >= 0)
	{
		m_meetingRoomHoursLeft -= hoursUsed;
		return 0;
	}
	else	// if not enough, set hours to zero and calculate overage
	{ 
		int retval = hoursUsed - m_meetingRoomHoursLeft; 
		m_meetingRoomHoursLeft = 0;
		return retval;
	}	
}

void Account::resetMeetingRoomHours()
{
	m_meetingRoomHoursLeft = m_meetingRoomHoursPerMonth;
}

void Account::display() const
{
	cout << endl << "account ID: " << m_id << endl;
	cout << "account owner: " << m_owner << endl;
	cout << "company: " << m_company << endl;
	cout << "date created: " << m_dateCreated << endl;
	cout << "meeting room hours left: " << m_meetingRoomHoursLeft << endl;
	cout << "members (by ID): " << endl;
	for (auto &i : m_members)
		cout << i << endl;
}

/////////////////////////////////// get methods ///////////////////////////

unsigned Account::getId() const
{
	return m_id;
}

unsigned Account::getOwnerId() const
{
	return m_owner;
}