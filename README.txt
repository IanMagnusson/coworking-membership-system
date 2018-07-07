FinalAssignment
CSCI-e53
5/10/18
code by Jack Magnusson


Files:

header		
		- proccess.h
		- Database.h
		- Product.h
		- Member.h
		- Account.h
		- RecurringService.h
		- Charge.h
		- Location.h
		- CachedData.h
	
souces files	
		- FinalAssignment.cpp (contains main)
		- proccess.cpp
		- Database.cpp
		- Product.cpp
		- Member.cpp
		- Account.cpp
		- RecurringService.cpp
		- Charge.cpp
		- Location.cpp
		- CachedData.cpp

a quick map of the over all structure:

 there are 5 element classes:
1. Product - stores default values for all products and services both recurring and onetime
2. Member - stores info about individuals and tracks individual usage allotments (day presences)
3. Account - stores shared info of a group paying together and tracks shared allotments (meeting room hours)
4. RecurringService - records the modifiable values (price, billing period, etc) of a specific service contract,
 used to generate Charges
5. Charge - an invoice for a onetime product (e.g. a guest pass) or a specific fee for a recurring service (e.g.
 monthly membership fee)

 All instances of these classes are stored by their ID keys in maps in a Database object. Data are retrieved from
 the Database object using a CachedData Object. The Data are passed by value to dynamicaly allocated coppies 
 which are then copied back to the Database and dealocated. This inefficiency is done intentionally to simulate
 retrieving data from an actual database. the processing of Database data retrieved by CachedData objects is
 coordinated by the functions from the process file with the help of element classes methods.

NOTES:
 * I #include database in the CachedData.cpp rather than CachedData.h to avoid circular dependencies. This feels
   wrong and but I can't figure out a reason not to do it and it helps a lot.
 * Though attempting to simulate a database, I have not attempted to deal with concurrency issues as I have yet
   to formally study this issue.
 * RecurringServices are designed to allow the future implimentation of an interface to modify them so that
   discounts and special deals can be worked out with customers.
 * Likewise RecurringServices are set up for the future implimenetation of feature to plan cancelations in advance.
 * The architecture is designed with a mind to the kinds of business analytics reports that are important at my
   work, such as generating estimated recurring revenue and comparing it to actual receipts.
 * That said, I have avoided putting too much tangential effort into the business strategy of the billing cycle
   design in particular, and instead opted for a functionality convenient for programing.