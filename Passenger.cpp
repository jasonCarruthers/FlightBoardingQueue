#include <iostream>
#include <sstream>
#include <string>
#include "RootHeaderFile.h"
#include "Passenger.h"
//#include "DynamicArray.h"
#include "LinkedList.h"
#include "Heap.h"
#include "UserInterface.h"
#include "Application.h"
using namespace std;


//string arrays
string PassengerFirstName[Num__PassengerFirstNames] =
{
	//Male first names
	"",
	"Aiden",
	"Jacob",
	"Jackson",
	"Santiago",
	"Jayden",
	"Ryan",
	"Elijah",
	"Robert",
	"Mia",
	"Malfegor",

	//Female first names
	"",
	"Ximena",
	"Emma",
	"Chloe",
	"Rachel",
	"Sarah",
	"Sofia",
	"Leah",
	"Barbara",
	"Anya",
	"Alexis",
};

string PassengerMiddleName[Num__PassengerMiddleNames] =
{
	//Male middle names
	"",
	"Gray",
	"Grey",
	"James",
	"Lou",
	"Reid",
	"Stephen",
	"Van",
	"William",

	//Female middle names
	"",
	"Dawn",
	"Day",
	"Ignatia",
	"Jade",
	"Leigh",
	"Lynn",
	"Jane",
	"Thi",
};

string PassengerLastName[Num__PassengerLastNames] =
{
	//Unisex last names
	"Smith",
	"Johnson",
	"Williams",
	"Brown",
	"Jones",
	"Miller",
	"Davis",
	"Garcia",
	"Rodriguez",
	"Wilson",
};


string GetRandomPassengerName()
{
	stringstream stringStream;

	const int MALE = 0;
	const int FEMALE = 1;
	int sexOfName = rand() % 2; //0 is male, 1 is female

	//generate first, middle, and last names randomly
	int firstNameNum = 1 + (rand() % (Pre__FemaleFirstNames - Pre__MaleFirstNames - 1));
	string firstName = (sexOfName == MALE) ? PassengerFirstName[ firstNameNum ] :
		PassengerFirstName[ Pre__FemaleFirstNames + firstNameNum ];

	int middleNameNum = 1 + (rand() % (Pre__FemaleMiddleNames - Pre__MaleMiddleNames - 1));
	string middleName = (sexOfName == MALE) ? PassengerMiddleName[ middleNameNum ] :
		PassengerMiddleName[ Pre__FemaleMiddleNames + middleNameNum ];
	
	string lastName = PassengerLastName[ rand() % Num__PassengerLastNames ];

	//put all three names into one stringstream
	stringStream << firstName.c_str() << " " << middleName.c_str() << " " << lastName.c_str();

	return stringStream.str();
}

//Passenger functions
Passenger::Passenger(string name, int priority, double timeOfTicketPurchase)
{
	mName = name;
	mPriority = priority;
	mTimeOfTicketPurchase = timeOfTicketPurchase;
	//mID = SetID(mPriority);

	if(mName == "")
	{
		mName = GetRandomPassengerName();
	}
}

string Passenger::GetName()
{
	return mName;
}

void Passenger::SetName(string newName)
{
	mName = newName;
}

int Passenger::GetPriority()
{
	return mPriority;
}

void Passenger::SetPriority(int priority)
{
	mPriority = priority;
}

int Passenger::GetID()
{
	return mID;
}

void Passenger::SetID()
{
	if(mPriority >= 0 && mPriority < Num__PriorityTypes)
	{
		if(mPriority == Priority_FCEGlobalService)
		{
			mID = App->mFCEGlobalServiceIDList.GetFirstObject();
			App->mFCEGlobalServiceIDList.Remove(mID);
		}

		else if(mPriority == Priority_GlobalService)
		{
			mID = App->mGlobalServiceIDList.GetFirstObject();
			App->mGlobalServiceIDList.Remove(mID);
		}

		else if(mPriority == Priority_FCEPremiumExecutive)
		{
			mID = App->mFCEPremiumExecutiveIDList.GetFirstObject();
			App->mFCEPremiumExecutiveIDList.Remove(mID);
		}

		else if(mPriority == Priority_FCEPremium)
		{
			mID = App->mFCEPremiumIDList.GetFirstObject();
			App->mFCEPremiumIDList.Remove(mID);
		}

		else if(mPriority == Priority_FCEStandard)
		{
			mID = App->mFCEStandardIDList.GetFirstObject();
			App->mFCEStandardIDList.Remove(mID);
		}

		else if(mPriority == Priority_PremiumExecutive)
		{
			mID = App->mPremiumExecutiveIDList.GetFirstObject();
			App->mPremiumExecutiveIDList.Remove(mID);
		}

		else if(mPriority == Priority_Premium)
		{
			mID = App->mPremiumIDList.GetFirstObject();
			App->mPremiumIDList.Remove(mID);
		}

		else if(mPriority == Priority_Standard)
		{
			mID = App->mStandardIDList.GetFirstObject();
			App->mStandardIDList.Remove(mID);
		}
	}
}

double Passenger::GetTimeOfTicketPurchase()
{
	return mTimeOfTicketPurchase;
}

void Passenger::SetTimeOfTicketPurchase(double timeOfTicketPurchase)
{
	mTimeOfTicketPurchase = timeOfTicketPurchase;
}