#pragma once
using namespace std;


class Passenger
{
public:
	Passenger(string name = "", int priority = GARBAGE_VALUE, double timeOfTicketPurchase = static_cast<double>(GARBAGE_VALUE));

	string GetName();
	void SetName(string newName);
	int GetPriority();
	void SetPriority(int priority);
	int GetID();
	void SetID(); //priority level must be set before ID is assigned
	double GetTimeOfTicketPurchase();
	void SetTimeOfTicketPurchase(double timeOfTicketPurchase);
private:
	string mName;
	int mPriority;
	int mID;
	double mTimeOfTicketPurchase;
};