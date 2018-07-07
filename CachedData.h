/*
	CachedData.h
		code by Jack Magnusson 5/10/18
		Final Assignment csci-e53
*/
#pragma once

#include <stdexcept>
#include <vector>

class Database;
class Product;
class Member;
class Account;
class RecurringService;
class Charge;

// helper func prototype
template<typename T>
T * allocObj(const T &obj);

/*
	Stores data looked up from Database object
*/

class CachedData
{
private:
	std::vector<const Product *> m_prod;
	std::vector<const Charge *> m_charge;
	std::vector<Member *> m_memb;
	std::vector<Account *> m_acct;
	std::vector<RecurringService *> m_recur;
	Database * m_dbFrom;

	
	
public:
	~CachedData();

	// add dynamically alloced copied of objects to storage
	CachedData & pushProd(const Product &prod); 
	CachedData & pushCharge(const Charge &charge); 
	CachedData & pushMemb(const Member &memb); 
	CachedData & pushAcct(const Account &acct);
	CachedData & pushRecur(const RecurringService &recur);
	void setDBFrom(Database *db) { m_dbFrom = db; }

	// get last element
	const Product & getProd() const;
	const Charge & getCharge() const;
	Member & getMemb();
	Account & getAcct();
	RecurringService & getRecur();

	// get const version of whole vector
	const std::vector<const Product *> & getProdVec() const { return m_prod; }
	const std::vector<const Charge *> & getChargeVec() const { return m_charge; }
	const std::vector<Member *> & getMembVec() { return m_memb; }
	const std::vector<Account *> & getAcctVec() { return m_acct; }
	const std::vector<RecurringService *> & getRecurVec() { return m_recur; }
};


// used to dynamically allocate element objects loaded into CacheData object
template<typename T>
inline T * allocObj(const T & obj)
{
	try
	{
		auto p = new T(obj);
		return p;
	}
	catch (std::bad_alloc &err)
	{
		err.what();
		throw;
	}
}