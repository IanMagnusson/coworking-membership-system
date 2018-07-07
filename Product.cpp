/*
	Product.cpp
		code by Jack Magnusson 5/4/18
		Final Assignment csci-e53
*/

#include "Product.h"

using namespace std;

// constructor

Product::Product(std::string name, double price, int days, int meetingRoomHours, time_t billingPeriod):
	m_name(name),
	m_price(price),
	m_days(days),
	m_meetingRoomHours(meetingRoomHours),
	m_billingPeriod(billingPeriod)
{}

// display

void Product::display() const
{
	std::cout << m_name << m_price << m_days <<
		m_meetingRoomHours << m_billingPeriod << std::endl;
}

// get mehtods

string Product::getName() const
{
	return m_name;
}

double Product::getPrice() const
{
	return m_price;
}

int Product::getDays() const
{
	return m_days;
}

int Product::getMeetingRoomHours() const
{
	return m_meetingRoomHours;
}

time_t Product::getBillingPeriod() const
{
	return m_billingPeriod;
}

// enum helpers

const Product enum2Prod(DefaultProd dp)
{
	static const Product DefaultProds[] =
	{
	// one time Products
	Product("BWPrint", .05),
	Product("ColorPrint", .25),
	Product("GuestPass", 25),
	Product("DayOverage", 30),
	Product("MeetingRoomOverage", 25),
	Product("Inactive", 0),

	// recuring fee products
	Product("Community", 30, 1, 1, 2592000),
	Product("PartTime", 130, 5, 5, 2592000),
	Product("FullTime", 350, -1, 20, 2592000),
	Product("Office", 600, -1, 20, 15552000),
	Product("Mailing", 40, 0, 0, 2592000),
	Product("Storage", 20, 0, 0, 2592000)
	};
	return DefaultProds[dp];
}

std::string enum2String(DefaultProd dp)
{
	return enum2Prod(dp).getName();
}
