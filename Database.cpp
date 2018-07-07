/*
	Database.cpp
		code by Jack Magnusson 5/5/18
		Final Assignment csci-e53
*/

#include "Database.h"

using namespace std;

// constructor

Database::Database()
{
	bootProductMap();
}

// display

void Database::display()
{
	for (auto & obj : m_accountMap)
		obj.second.display();
	for (auto & obj : m_memberMap)
		obj.second.display();
	for (auto & obj : m_recurringServiceMap)
		obj.second.display();
	for (auto & obj : m_chargeMap)
		obj.second.display();
}

///////////////////////////////////////Cache interface methods////////////////////////////////////////////

// these methods load the CachedData object with dynamically allocated copies of element objects
// NOTE: PRODUCT AND CHARGE OBJECTS ARE NOT READ ONLY REFS AND NOT DYNAMICALLY ALLOCATED

void Database::loadMember(unsigned id, CachedData & cd)
{
	cd.pushMemb(this->lookUpMember(id));
	cd.setDBFrom(this);// set db to commit back to
}

void Database::loadAccount(unsigned id, CachedData & cd)
{ 
	cd.pushAcct(this->lookUpAccount(id));
	cd.setDBFrom(this);// set db to commit back to
}

void Database::loadRecurringService(unsigned id, CachedData & cd)
{
	cd.pushRecur(this->lookUpRecurringService(id));
	cd.setDBFrom(this);// set db to commit back to
}

void Database::loadCharge(unsigned id, CachedData & cd)
{
	cd.pushCharge(this->lookUpCharge(id));
	cd.setDBFrom(this);// set db to commit back to
}

void Database::loadProduct(std::string name, CachedData & cd)
{
	cd.pushProd(this->lookUpProduct(name));
	cd.setDBFrom(this);// set db to commit back to
}

void Database::loadFullMemberInfo(unsigned id, CachedData &cd)
{
	cd.pushMemb(this->lookUpMember(id));
	cd.pushAcct(this->lookUpAccount(cd.getMemb().getAccountId()));
	cd.pushRecur(this->lookUpRecurringServiceByMember(id));
	cd.pushProd(this->lookUpProduct(cd.getMemb().getMembershipType()));
	cd.setDBFrom(this);// set db to commit back to

}

void Database::loadAllRecurringServices(CachedData & cd)
{
	for (auto it = m_recurringServiceMap.begin(); it != m_recurringServiceMap.end(); ++it)
		cd.pushRecur(it->second);
	cd.setDBFrom(this);// set db to commit back to
}

void Database::loadAllMembers(CachedData & cd)
{
	for (auto it = m_memberMap.begin(); it != m_memberMap.end(); ++it)
		cd.pushMemb(it->second);
	cd.setDBFrom(this);// set db to commit back to
}

void Database::loadAllAccounts(CachedData & cd)
{
	for (auto it = m_accountMap.begin(); it != m_accountMap.end(); ++it)
		cd.pushAcct(it->second);
	cd.setDBFrom(this);// set db to commit back to
}

// Methods automatically called by CachedData destructor: copies dyn alloced element objs back to DB

void Database::commitMember(const Member &memb)
{
	this->lookUpMember(memb.getId()) = memb;
}

void Database::commitAccount(const Account &acct)
{
	this->lookUpAccount(acct.getId()) = acct;
}

void Database::commitRecurringService(const RecurringService &recur)
{
	this->lookUpRecurringService(recur.getId()) = recur;
}

///////////////////////////////// id to id lookups ////////////////////////////////////

unsigned Database::memberId2AcctId(unsigned memberId)
{
	return lookUpMember(memberId).getAccountId();
}

unsigned Database::memberId2RecurId(unsigned memberId)
{
	return lookUpRecurringServiceByMember(memberId).getId();
}

////////////////////////////////// read only user interface lookups ////////////////////////////////
const Member & Database::lookUpMemberByName(std::string name)
{
	auto p = lookUpMemberByNameMulti(name); // returns range if multiple with same name
	int dist = distance(p.first, p.second);

	if (dist > 1)
		throw exception("lookUpMemberByName failed: mutliple member with this name, use lookUpMemberByNameMulti");
	
	else if (dist == 0)
		throw out_of_range("lookUpMemberByName failed: no such name");
	
	else
		return p.first->second; // only one member at this name
}

////////////// helpers used in process functions to maintain secondary look up map integrity ///////////////

void Database::updateAccountOwner(Member & newOwner, Account & acct)
{
	// save reference to embeded acct obj in db
	auto & acctInDb = lookUpAccount(acct.getId());
	// erase old owner2Account entry
	if (!m_owner2Account.erase(acct.getOwnerId()))
		throw out_of_range("updateAccountOwner failed: no such owner id");

	// make new owner2Account entry using ref to embeded acct obj in db
	if (!m_owner2Account.emplace(newOwner.getId(), acctInDb).second)
		throw exception("updateAccountOwner falied: this member already owns another account");
}

bool Database::eraseRecurringService(unsigned recurId, unsigned membId)
{
	m_memberId2RecurringService.erase(membId);
	return m_recurringServiceMap.erase(recurId); // true if anything erased, else false
}

bool Database::eraseAcctService(unsigned acctId, const std::string & name)
{
	auto p = lookUpServiceByAccountMulti(acctId);
	// search non member specific services associated with account for FIRST with same prod name
	for (auto it = p.first; it != p.second; ++it)
		if ((*it).second.getProductName() == name)
		{
			// erase in all maps
			int retval = m_recurringServiceMap.erase((*it).second.getId());
			m_accountId2RecurringService.erase(it);
			return retval; // true if anything erased
		}
	return false; // not found	
}

///////////////////////////////////// data input interface ////////////////////////////////////////

void Database::addAccount(const Account & obj)
{
	auto p = m_accountMap.emplace(obj.getId(), obj); // try to put in map
	if (!p.second)
		throw out_of_range("addAccount failed: id already present");
	else
	{	// update secondary look up maps
		m_owner2Account.emplace(p.first->second.getOwnerId(), p.first->second);
	}
}

void Database::addMember(const Member & obj)
{
	auto p = m_memberMap.emplace(obj.getId(), obj); // try to put in map
	if (!p.second)
		throw out_of_range("addAccount failed: id already present");
	else	
	{	// update secondary look up maps
		m_name2Member.emplace(p.first->second.getName(), p.first->second);
	}
}

void Database::addRecurringService(const RecurringService & obj)
{
	auto p = m_recurringServiceMap.emplace(obj.getId(), obj); // try to put in map
	if (!p.second)
		throw out_of_range("addAccount failed: id already present");
	else
	{	// update secondary look up maps
		// if member specific service, add to memberId2RecurringService
		if (obj.getMember() != 0) 
			m_memberId2RecurringService.emplace(p.first->second.getMember(), p.first->second);
		// if membId is 0, this is a non-member specific service
		else
			m_accountId2RecurringService.emplace(p.first->second.getAccount(), p.first->second);
	}
}

void Database::addCharge(const Charge & obj)
{
	auto p = m_chargeMap.emplace(obj.getId(), obj); // try to put in map
	if (!p.second)
		throw out_of_range("addAccount failed: id already present");
}


void Database::addProduct(const Product & obj)
{
	auto p = m_productMap.emplace(obj.getName(), obj); // try to put in map
	if (!p.second)
		throw out_of_range("addAccount failed: id already present");
}


///////////////////////////////////////////// private methods //////////////////////////////////////

// this method is called by constructor to load defualt products defined in Product.h
void Database::bootProductMap()
{
	addProduct(enum2Prod(BWPrint));
	addProduct(enum2Prod(ColorPrint));
	addProduct(enum2Prod(GuestPass));
	addProduct(enum2Prod(DayOverage));
	addProduct(enum2Prod(MeetingRoomOverage));
	addProduct(enum2Prod(Inactive));
	addProduct(enum2Prod(Community));
	addProduct(enum2Prod(PartTime));
	addProduct(enum2Prod(FullTime));
	addProduct(enum2Prod(Office));
	addProduct(enum2Prod(Mailing));
	addProduct(enum2Prod(Storage));
}