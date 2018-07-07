/*
	process.h
		code by Jack Magnusson 5/5/18
		Final Assignment csci-e53
*/


#pragma once
#include <vector> // for CachedData getVec methods
#include "CachedData.h"
#include "Database.h"

/*
	these are a collection of utilities for processing data from
	Database and coordinating the methods of its element classes
*/

// add new
void processNewMember(Database &data, const Member &memb);
void processNewAccount(Database &data, const Member &memb);
void processAddService(Database &data, unsigned acctId, const std::string & newService);

// change or remove
void processMembershipChange(Database &data, unsigned membId, const std::string & newMembership);
void processAccountOwnerChange(Database &data, unsigned newOwnerId);
void processRemoveService(Database &data, unsigned acctId, const std::string & service);

// incidental fees
void processOneTimeProduct(Database &data, unsigned membId, const std::string & prod, unsigned quant = 1);
void processDayUsage(Database &data, unsigned membId);
void processMeetingRoomUsage(Database &data, unsigned memberId, unsigned hrsUsed);

// monthly processes
void processUsageAllocationReset(Database &data);
void processRecurringFees(Database &data);

// helpers
static bool processCharge(Database &data, RecurringService &rs);
unsigned getNewId();