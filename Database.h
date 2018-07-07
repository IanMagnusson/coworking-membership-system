/*
	Database.h
		code by Jack Magnusson 5/5/18
		Final Assignment csci-e53
*/


#pragma once

#include <iostream>
#include <map>
#include <algorithm>
#include <iterator>
#include "Account.h"
#include "Member.h"
#include "RecurringService.h"
#include "Charge.h"
#include "Product.h"
#include "CachedData.h"

/*
// helper func prototype
template<typename T>
T & allocObj(const T &obj);
*/

class Database
{
private:
	// maps with embeded objects
	std::map<unsigned, Account> m_accountMap;
	std::map<unsigned, Member> m_memberMap;
	std::map<unsigned, RecurringService> m_recurringServiceMap;
	std::map<unsigned, const Charge> m_chargeMap;
	std::map<std::string, Product> m_productMap;

	// maps to object refs for non id look up
	std::multimap<std::string, Member &> m_name2Member;
	std::map<unsigned, Account &> m_owner2Account;
	std::map<unsigned, RecurringService &> m_memberId2RecurringService;
	std::multimap<unsigned, RecurringService &> m_accountId2RecurringService;

	// private methods
	void bootProductMap();
	Account & lookUpAccount(unsigned id) { return m_accountMap.at(id); }
	Member & lookUpMember(unsigned id) { return m_memberMap.at(id); }
	RecurringService & lookUpRecurringService(unsigned id) { return m_recurringServiceMap.at(id); }
	const Charge & lookUpCharge(unsigned id) { return m_chargeMap.at(id); }
	const Product & lookUpProduct(std::string name) { return m_productMap.at(name); }
	auto lookUpMemberByNameMulti(std::string name) { return m_name2Member.equal_range(name); }
	auto lookUpServiceByAccountMulti(unsigned acctId) { return m_accountId2RecurringService.equal_range(acctId); }

public:
	Database();

	void display();

	// Cache interface methods
	void loadMember(unsigned id, CachedData &cd);
	void loadAccount(unsigned id, CachedData &cd);
	void loadRecurringService(unsigned id, CachedData &cd);
	void loadCharge(unsigned id, CachedData &cd);
	void loadProduct(std::string name, CachedData &cd);
	void loadFullMemberInfo(unsigned id, CachedData &cd);
	void loadAllRecurringServices(CachedData &cd);
	void loadAllMembers(CachedData &cd);
	void loadAllAccounts(CachedData &cd);
	void commitMember(const Member &);
	void commitAccount(const Account &);
	void commitRecurringService(const RecurringService &);

	// id to id lookups
	unsigned memberId2AcctId(unsigned memberId);
	unsigned memberId2RecurId(unsigned memberId);

	// read only user interface lookups
	const Member & lookUpMemberByName(std::string name);
	const Account & lookUpAccountByOwner(unsigned ownerId) { return m_owner2Account.at(ownerId); }
	const RecurringService & lookUpRecurringServiceByMember(unsigned memberid) { return m_memberId2RecurringService.at(memberid); }

	// helpers used in process functions to maintain secondary look up map integrity
	void updateAccountOwner(Member & newOwner, Account & acct);
	bool eraseRecurringService(unsigned recurId, unsigned membId);
	bool eraseAcctService(unsigned acctId, const std::string & name);

	// data input interface
	void addAccount(const Account &obj); 
	void addMember(const Member &obj);
	void addRecurringService(const RecurringService &obj); 
	void addCharge(const Charge & obj); 
	void addProduct(const Product & obj); 
};

/*
// used to dynamically allocate element objects loaded into CacheData object
template<typename T>
inline T & allocObj(const T & obj)
{
	try
	{
		auto p = new T(obj);
		return *p;
	}
	catch (std::bad_alloc &err)
	{
		err.what();
		throw;
	}
}

*/
