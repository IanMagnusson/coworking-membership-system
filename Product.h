/*
	Product.h
		code by Jack Magnusson 5/4/18
		Final Assignment csci-e53
*/

#pragma once
#include <iostream>
#include <string>
#include <ctime>
#include <map>

/*
	Product stores defualt values for both one time products and recurring services
*/

class Product
{
private:
	std::string m_name;
	double m_price;
	int m_days, m_meetingRoomHours;
	time_t m_billingPeriod;

public:
	Product(std::string name, double price, int days = 0, int meetingRoomHours = 0, time_t billingPeriod = 0);
	
	void display() const;

	// get methods
	std::string getName() const;
	double getPrice() const;
	int getDays() const;
	int getMeetingRoomHours() const;
	time_t getBillingPeriod() const;
};

// an enum for built in products

enum DefaultProd {
	// one time Products
	BWPrint,
	ColorPrint,
	GuestPass,
	DayOverage,
	MeetingRoomOverage,

	// recuring fee Products
	Inactive,
	Community,
	PartTime,
	FullTime,
	Office,
	Mailing,
	Storage
};

// enum helpers
const Product enum2Prod(DefaultProd dp);
std::string enum2String(DefaultProd dp);