/*
	process.cpp
		code by Jack Magnusson 5/5/18
		Final Assignment csci-e53
*/

#include "process.h"
using namespace std;

//////////////////////////////////// add new ///////////////////////////////////////
void processNewMember(Database & data, const Member & memb)
{
	// add member to Database
	data.addMember(memb);
	// cashe corresponding Product
	CachedData cd;
	data.loadProduct(memb.getMembershipType(), cd);
	// create RecurringService and add to Database
	int recurId = getNewId();
	data.addRecurringService(RecurringService(recurId, memb, cd.getProd()));
	// issue onboarding charge
	data.loadRecurringService(recurId,cd);
	processCharge(data, cd.getRecur());
	// add member to account
	data.loadAccount(memb.getAccountId(), cd);
	cd.getAcct().addMember(memb, cd);
}

void processNewAccount(Database & data, const Member & memb)
{
	// add member to Database
	data.addMember(memb);
	// cashe corresponding Product
	CachedData cd;
	data.loadProduct(memb.getMembershipType(), cd);
	// create RecurringService and add to Database
	int recurId = getNewId();
	data.addRecurringService(RecurringService(recurId, memb, cd.getProd()));
	// issue onboarding charge
	data.loadRecurringService(recurId,cd);
	processCharge(data, cd.getRecur());
	// construct and add new account to Database
	data.addAccount(Account(memb,cd.getProd()));
}

void processAddService(Database & data, unsigned acctId, const std::string & newService)
{
	// cache prod
	CachedData cd;
	data.loadProduct(newService, cd);
	// add new Recur
	unsigned recurId = getNewId();
	data.addRecurringService(RecurringService(recurId, acctId, cd.getProd()));
	// issue onboarding charge
	data.loadRecurringService(recurId,cd);
	processCharge(data, cd.getRecur());
}

///////////////////////////////////////// change or remove //////////////////////////////////////////


void processMembershipChange(Database & data, unsigned membId, const string & newMembership)
{
	// erase old recur
	data.eraseRecurringService(data.memberId2RecurId(membId), membId);
	// cache newProduct
	CachedData cd;
	data.loadProduct(newMembership, cd);
	// create RecurringService based on new Product and add to Database
	data.addRecurringService(RecurringService(getNewId(), data.memberId2AcctId(membId), cd.getProd(), membId));
	// cache the rest; ProdVec[0] is new and [1] old
	data.loadFullMemberInfo(membId, cd);
	// issue onboarding charge
	processCharge(data, cd.getRecur());
	// change meeting room hours in account
	cd.getAcct().changeMembership(*(cd.getProdVec()[0]), *(cd.getProdVec()[1]));
	// change refs in Member
	cd.getMemb().changeMembership(*(cd.getProdVec()[0]));
}

void processAccountOwnerChange(Database & data, unsigned newOwnerId)
{
	// cache newOwner and their Account
	CachedData cd;
	data.loadMember(newOwnerId, cd);
	data.loadAccount(cd.getMemb().getAccountId(), cd);
	// update owner2Account map
	data.updateAccountOwner(cd.getMemb(), cd.getAcct());
	// update account object
	cd.getAcct().changeOwner(cd.getMemb());
}

void processRemoveService(Database & data, unsigned acctId, const std::string & service)
{
	// wrapper for standardization of interface
	data.eraseAcctService(acctId, service);
}

////////////////////////////////////// incidental fees ///////////////////////////////////////////

// used with BWPrint, ColorPrint, GuestPass, or other user defined incidental fees
void processOneTimeProduct(Database & data, unsigned membId, const std::string & prod, unsigned quant /*=1*/)
{
	// cache memb and prod
	CachedData cd;
	data.loadMember(membId, cd);
	data.loadProduct(prod, cd);
	data.addCharge(Charge(getNewId(), quant, cd));
}

// when member's presence is recored, this function handles usage accounting and overages
void processDayUsage(Database & data, unsigned membId)
{
	// cache member
	CachedData cd;
	data.loadMember(membId, cd);
	
	// proccess member day use allocation and charge overage if needed
	if (cd.getMemb().useDayIfAny())
	{
		//cache DayOverage Product
		data.loadProduct(enum2String(DayOverage), cd);
		data.addCharge(Charge(getNewId(), 1, cd));
	}
		
}

// when member uses a meeting room, this function handles usage accounting and overages
void processMeetingRoomUsage(Database & data, unsigned memberId, unsigned hrsUsed)
{
	// cashe account of given member
	CachedData cd;
	data.loadAccount(data.memberId2AcctId(memberId), cd);
	// proccess meeting room use allocation and charge overage if needed
	unsigned hrs2Charge;
	if (hrs2Charge = cd.getAcct().useMeetingRoomHoursIfAny(hrsUsed))
	{
		//cache Member and MeetingRoomOverage Product
		data.loadMember(memberId, cd);
		data.loadProduct(enum2String(MeetingRoomOverage), cd);
		data.addCharge(Charge(getNewId(), hrs2Charge, cd));
	}
}

//////////////////////////////////// monthly processes ////////////////////////////////////////

// generates a Charge for all active RecurringServices past their billing period
void processRecurringFees(Database & data)
{
	// cache all recurs
	CachedData cd;
	data.loadAllRecurringServices(cd);
	auto vec = cd.getRecurVec();
	// for each RecurringService check if past billing period, charge if yes
	for (auto it = vec.begin(); it != vec.end(); ++it)
		processCharge(data, **it);
}

// resets day presence and meeting room hour usage allocations for all members and accounts
void processUsageAllocationReset(Database & data)
{
	// Cache all Members and Accounts
	CachedData cd;
	data.loadAllMembers(cd);
	data.loadAllAccounts(cd);
	auto acctVec = cd.getAcctVec();
	auto membVec = cd.getMembVec();
	// for each account, reset meeting room hours
	for (auto it = acctVec.begin(); it != acctVec.end(); ++it)
		(*it)->resetMeetingRoomHours();
	// for each member, reset days
	for (auto it = membVec.begin(); it != membVec.end(); ++it)
		(*it)->resetDays();
}


////////////////////////////////////////// Helpers ///////////////////////////////////////////////
/*
	processCharge
		purpose:	a helper for other process functions to generate a Charge from a RecurringService
		WARNING:	RecurringService parameter intended to be retrieved from CachedData object!!
*/

static bool processCharge(Database & data, RecurringService & rs)
{
	// check if past billing period, charge if yes
	if (rs.billMeIfTime())
	{
		data.addCharge(Charge(getNewId(), rs));
		return true;
	}
	else
		return false;
}

/*
	getNewId
		purpose:	a simple method for generating unique ids starting at 1 and increasing
		note:		this function is for demonstration purposes only and not meant to
					be a fully functional id generator
*/

unsigned getNewId()
{
	static unsigned n = 0;
	return ++n;
}
