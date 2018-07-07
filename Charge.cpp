/*
	Charge.cpp
		code by Jack Magnusson 5/3/18
		Final Assignment csci-e53
*/

#include "Charge.h"

using namespace std;

////////////////////////////// constructors ////////////////////////////////////////////

Charge::Charge(unsigned id, RecurringService & source) :
	m_id(id),
	m_associatedAccount(source.getAccount()),
	m_associatedMember(source.getMember()),
	m_quantity(1),	// recurs don't have quantity
	m_unitPrice(source.getPrice()),
	m_productName(source.getProductName()),
	m_issuedOn(currentTime)
{}

Charge::Charge(unsigned id, unsigned acctID, unsigned memberID, unsigned quantity, const Product & source) :
	m_id(id),
	m_associatedAccount(acctID),
	m_associatedMember(memberID),
	m_quantity(quantity),
	m_unitPrice(source.getPrice()),
	m_productName(source.getName()),
	m_issuedOn(currentTime)
{}

// WARNING: Memb and Prod must be loaded in Cache
Charge::Charge(unsigned id, unsigned quantity, CachedData & cd) :
	m_id(id),
	m_associatedAccount(cd.getMemb().getAccountId()),
	m_associatedMember(cd.getMemb().getId()),
	m_quantity(quantity),
	m_unitPrice(cd.getProd().getPrice()),
	m_productName(cd.getProd().getName()),
	m_issuedOn(currentTime)
{}

// display
void Charge::display() const
{
	cout << endl << "charge for: " << m_productName << endl;
	cout << "issued on: " << m_issuedOn << endl;
	cout << "charge #: " << m_id << endl;
	cout << "associated account #: " << m_associatedAccount << endl;
	cout << "associated member #: " << m_associatedMember << endl;
	cout << "quantity: " << m_quantity << endl;
	cout.setf(ios::fixed, ios::floatfield);
	cout.precision(2);
	cout << "unit price: $" << m_unitPrice << endl;
	cout << "total price: $" << m_unitPrice * m_quantity << endl;
}

//////////////////////////////// get methods /////////////////////////////////

unsigned Charge::getId() const
{
	return m_id;
}
