#include <iostream>
#include <string>
#include <windows.h>
#include "RootHeaderFile.h"
#include "Passenger.h"
//#include "DynamicArray.h"
#include "LinkedList.h"
#include "Heap.h"
#include "UserInterface.h"
#include "Application.h"
using namespace std;


Application::Application()
{
	mTimeElapsed = 0.0;

	InitIDLinkedLists();

	mUI.mSelectionTool.SetX(0);
	mUI.mSelectionTool.SetY(mUI.mMainMenuButton[0].GetY());
}

void Application::InitSubMenu()
{
	mUI.DrawHeader();
	mUI.SetCursorPosition(0, mUI.mHeader.GetY() + 2);
}

void Application::RescindID(int ID)
{
	for(int i = 0; i < Num__PriorityTypes; i++)
	{
		if(ID >= MAX_PASSENGERS_PER_FLIGHT * i && ID < (MAX_PASSENGERS_PER_FLIGHT * i) + MAX_PASSENGERS_PER_FLIGHT)
		{
			switch(i)
			{
			case Priority_FCEGlobalService:
				mFCEGlobalServiceIDList.Insert(ID, InsertType_Front);
				return;

			case Priority_GlobalService:
				mGlobalServiceIDList.Insert(ID, InsertType_Front);
				return;

			case Priority_FCEPremiumExecutive:
				mFCEPremiumExecutiveIDList.Insert(ID, InsertType_Front);
				return;

			case Priority_FCEPremium:
				mFCEPremiumIDList.Insert(ID, InsertType_Front);
				return;

			case Priority_FCEStandard:
				mFCEStandardIDList.Insert(ID, InsertType_Front);
				return;

			case Priority_PremiumExecutive:
				mPremiumExecutiveIDList.Insert(ID, InsertType_Front);
				return;

			case Priority_Premium:
				mPremiumIDList.Insert(ID, InsertType_Front);
				return;

			case Priority_Standard:
				mStandardIDList.Insert(ID, InsertType_Front);
				return;
			default:
				return;
			}
		}
	}
}

void Application::Update()
{
	//update elapsed time
	mTimeElapsed += .02;

	//update app
	switch( mUI.mHeader.GetMode() )
	{
	case Header_MainMenu:
		mUI.DrawMainMenu();
		mUI.UpdateMainMenuButtons();
		break;

	case Header_Add:
		AddToQueue();
		break;

	case Header_Remove:
		RemoveFromQueue();
		break;

	case Header_Change:
		ChangeStatusWithinQueue();
		break;

	case Header_Inspect:
		InspectQueue();
		break;

	case Header_Delete:
		DeleteQueue();
		break;

	case Header_Exit:
		Exit();
		break;

	default:
		//make this output red
		cout << "Application: \"Update\" ERROR";
	};
}

int Application::GetPriorityFromUser()
{
	cout << "Select the priority of the new passenger(s).\n";
	for(int i = 0; i < Num__PriorityTypes; i++)
	{
		cout << i + 1 << ":\t" << PriorityLevelName[i] << "\n";
	}
	
	string userInput = " ";
	while( !(userInput == "1" || userInput == "2" || userInput == "3" || userInput == "4"
		|| userInput == "5" || userInput == "6" || userInput == "7" || userInput == "8") )
	{
		mUI.SetCursorPosition(0, mUI.mHeader.GetY() + 2 + Num__PriorityTypes + 2);
		mUI.DrawWhiteSpace();
		cin >> userInput;
	}

	system("cls");
	return atoi(userInput.c_str()) - 1;
}

string Application::GetNameFromUser()
{
	cout << "Please enter the passenger's name.\n";
	
	string name = " ";
	while( !strcmp(name.c_str(), " ") )
	{
		mUI.SetCursorPosition(0, mUI.mHeader.GetY() + 6);
		mUI.DrawWhiteSpace();
		cin >> name;
	}

	system("cls");
	return name.c_str();
}

void Application::SortPassengerIntoQueue(Passenger sortPassenger)
{
	if(mOnFlightHeap.IsFull())
	{
		Passenger leastValuableOnFlight = mOnFlightHeap.GetLeastValuable();
		//if the new passenger has a higher priority than the lowest-priority passenger on-flight
		if(leastValuableOnFlight.GetPriority() < sortPassenger.GetPriority())
		{
			//find leastValuablePassenger in mOnFlightHeap, remove
			mOnFlightHeap.Remove(leastValuableOnFlight.GetName());
			RescindID( leastValuableOnFlight.GetID() );

			//add sortPassenger to mOnFlightHeap
			mOnFlightHeap.Insert(sortPassenger);

			//if there's room, add leastValuablePassenger to mWaitingListHeap
			if( mWaitingListHeap.IsFull() )
			{
				Passenger leastValuableWaiting = mWaitingListHeap.GetLeastValuable();
				if(leastValuableWaiting.GetPriority() < leastValuableOnFlight.GetPriority())
				{
					//remove least valuable on waiting list
					mWaitingListHeap.Remove(leastValuableWaiting.GetName());
					RescindID( leastValuableWaiting.GetID() );

					//add least valuable from on flight heap
					mWaitingListHeap.Insert(leastValuableOnFlight);
				}
				//otherwise don't do anything with leastValuableOnFlight
			}
			else
				mWaitingListHeap.Insert(leastValuableOnFlight);
		}
		else
		{
			//if there's room, add sortPassenger to mWaitingListHeap
			Passenger leastValuableWaiting = mWaitingListHeap.GetLeastValuable();
			if(leastValuableWaiting.GetPriority() < sortPassenger.GetPriority())
			{
				//remove least valuable on waiting list
				mWaitingListHeap.Remove(leastValuableWaiting.GetName());
				RescindID( leastValuableWaiting.GetID() );

				//add least valuable from on flight heap
				mWaitingListHeap.Insert(sortPassenger);
			}
		}
	}
	else
	{
		mOnFlightHeap.Insert(sortPassenger);
	}
}

void Application::InitIDLinkedLists()
{
	//Priority_FCEGlobalService
	for(int i = 0; i < MAX_PASSENGERS_PER_FLIGHT; i++)
	{
		mFCEGlobalServiceIDList.Insert((MAX_PASSENGERS_PER_FLIGHT * Priority_FCEGlobalService) + i,
			InsertType_Back);
	}

	//Priority_GlobalService
	for(int i = 0; i < MAX_PASSENGERS_PER_FLIGHT; i++)
	{
		mGlobalServiceIDList.Insert((MAX_PASSENGERS_PER_FLIGHT * Priority_GlobalService) + i,
			InsertType_Back);
	}

	//Priority_FCEPremiumExecutive
	for(int i = 0; i < MAX_PASSENGERS_PER_FLIGHT; i++)
	{
		mFCEPremiumExecutiveIDList.Insert((MAX_PASSENGERS_PER_FLIGHT * Priority_FCEPremiumExecutive) + i,
			InsertType_Back);
	}

	//Priority_FCEPremium
	for(int i = 0; i < MAX_PASSENGERS_PER_FLIGHT; i++)
	{
		mFCEPremiumIDList.Insert((MAX_PASSENGERS_PER_FLIGHT * Priority_FCEPremium) + i,
			InsertType_Back);
	}

	//Priority_FCEStandard
	for(int i = 0; i < MAX_PASSENGERS_PER_FLIGHT; i++)
	{
		mFCEStandardIDList.Insert((MAX_PASSENGERS_PER_FLIGHT * Priority_FCEStandard) + i,
			InsertType_Back);
	}

	//Priority_PremiumExecutive
	for(int i = 0; i < MAX_PASSENGERS_PER_FLIGHT; i++)
	{
		mPremiumExecutiveIDList.Insert((MAX_PASSENGERS_PER_FLIGHT * Priority_PremiumExecutive) + i,
			InsertType_Back);
	}

	//Priority_Premium
	for(int i = 0; i < MAX_PASSENGERS_PER_FLIGHT; i++)
	{
		mPremiumIDList.Insert((MAX_PASSENGERS_PER_FLIGHT * Priority_Premium) + i,
			InsertType_Back);
	}

	//Priority_Standard
	for(int i = 0; i < MAX_PASSENGERS_PER_FLIGHT; i++)
	{
		mStandardIDList.Insert((MAX_PASSENGERS_PER_FLIGHT * Priority_Standard) + i,
			InsertType_Back);
	}
}

void Application::ResetIDLinkedLists()
{
	mFCEGlobalServiceIDList.DeleteList();
	mGlobalServiceIDList.DeleteList();
	mFCEPremiumExecutiveIDList.DeleteList();
	mFCEPremiumIDList.DeleteList();
	mFCEStandardIDList.DeleteList();
	mPremiumExecutiveIDList.DeleteList();
	mPremiumIDList.DeleteList();
	mStandardIDList.DeleteList();

	InitIDLinkedLists();
}

void Application::AddToQueue()
{
	InitSubMenu();


	//get passenger info
	Passenger newPassenger;
	//get priority
	newPassenger.SetPriority( GetPriorityFromUser() );
	//set passenger ID, time of purchase
	newPassenger.SetTimeOfTicketPurchase(mTimeElapsed);
	newPassenger.SetID();
	
	//draw header
	mUI.DrawHeader();
	mUI.SetCursorPosition(0, mUI.mHeader.GetY() + 2);


	//get name
	newPassenger.SetName( GetNameFromUser() );
	//sort into heap
	SortPassengerIntoQueue(newPassenger);
	


	mUI.mHeader.SetMode(Header_MainMenu);
	mUI.mHeader.SetName( HeaderName[mUI.mHeader.GetMode()].c_str() );
	cout << "Queue updated.\n";
	system("pause");
	system("cls");
}

void Application::RemoveFromQueue()
{
	InitSubMenu();

	//get name of passenger to remove
	string userInput = GetNameFromUser();
	InitSubMenu();

	//search on flight queue, remove if found
	int initialSize = mOnFlightHeap.GetCurrentSize();
	Passenger removedPassenger = mOnFlightHeap.Remove(userInput);
	bool wasFound = false;
	if(removedPassenger.GetPriority() >= 0 && removedPassenger.GetPriority() < Num__PriorityTypes)
	{
		RescindID(removedPassenger.GetID());
		wasFound = true;
	}
	
	//if on flight WAS full, and there's at least someone waiting, move them from waiting to on flight
	if(wasFound && initialSize == MAX_PASSENGERS_PER_FLIGHT)
	{
		if( !mWaitingListHeap.IsEmpty() )
			mOnFlightHeap.Insert(mWaitingListHeap.GetMostValuable());
	}
	//if not found, search waiting list
	else if(!wasFound)
	{
		removedPassenger = mWaitingListHeap.Remove(userInput);
		if(removedPassenger.GetPriority() >= 0 && removedPassenger.GetPriority() < Num__PriorityTypes)
			RescindID(removedPassenger.GetID());
	}

	mUI.mHeader.SetMode(Header_MainMenu);
	mUI.mHeader.SetName( HeaderName[mUI.mHeader.GetMode()].c_str() );
	cout << "\n\n";
	system("pause");
	system("cls");
}

void Application::ChangeStatusWithinQueue()
{
	InitSubMenu();

	string name = GetNameFromUser();
	InitSubMenu();

	InitSubMenu();
	int priority = GetPriorityFromUser();

	//update passenger info
	Passenger updatedPassenger;
	updatedPassenger.SetName(name);
	updatedPassenger.SetPriority(priority);
	updatedPassenger.SetTimeOfTicketPurchase(mTimeElapsed);
	updatedPassenger.SetID();

	//remove passenger from queue
	int initialOnFlightSize = mOnFlightHeap.GetCurrentSize();
	int initialWaitingListSize = mWaitingListHeap.GetCurrentSize();
	Passenger removedPassenger = mOnFlightHeap.Remove(name);
	
	if(initialOnFlightSize == mOnFlightHeap.GetCurrentSize())
	{
		removedPassenger = mWaitingListHeap.Remove(name);
		if(initialWaitingListSize != mWaitingListHeap.GetCurrentSize())
			RescindID(removedPassenger.GetID());
	}
	else
		RescindID(removedPassenger.GetID());

	//re-insert passenger with updated status
	if( initialOnFlightSize != mOnFlightHeap.GetCurrentSize() || initialWaitingListSize != mWaitingListHeap.GetCurrentSize() )
		SortPassengerIntoQueue(updatedPassenger);


	mUI.mHeader.SetMode(Header_MainMenu);
	mUI.mHeader.SetName( HeaderName[mUI.mHeader.GetMode()].c_str() );
	cout << "\n\n";
	system("pause");
	system("cls");
}

void Application::InspectQueue()
{
	InitSubMenu();

	Passenger highestPriority;
	Passenger lowestPriority;

	if( !mOnFlightHeap.IsEmpty() )
	{
		//display top and bottom 3 passengers in the OnFlightHeap
		Passenger passenger;
		
		cout << "The three highest priority passengers, from most to least valued-priority:\n";
		for(int i = 0; i < 3; i++)
		{
			if( mOnFlightHeap.GetCurrentSize() >= i+1 )
			{
				passenger = mOnFlightHeap.GetLinearSortObject(i);
				cout << "Passenger " << i+1 << ":\t";
				cout << passenger.GetName() << "\t" << PriorityLevelName[ passenger.GetPriority() ] << "\n";
			}
		}
		cout << "\n";

		cout << "The three lowest priority passengers, from least to most valued-priority:\n";
		for(int i = 0; i < 3; i++)
		{
			if( mOnFlightHeap.GetCurrentSize() >= i+1 )
			{
				passenger = mOnFlightHeap.GetLinearSortObject(mOnFlightHeap.GetCurrentSize() - (i+1));
				cout << "Passenger " << mOnFlightHeap.GetCurrentSize() - i << ":\t";
				cout << passenger.GetName() << "\t" << PriorityLevelName[ passenger.GetPriority() ] << "\n";
			}
		}
		cout << "\n";
	}
	else
		cout << "No passengers assigned to flight yet.\n";

	mUI.DrawDividerLine();
	cout << "\n";

	if( !mWaitingListHeap.IsEmpty() )
	{
		//display highest, lowest priority on waiting list
		highestPriority = mWaitingListHeap.GetMostValuable();
		lowestPriority = mWaitingListHeap.GetLeastValuable();

		cout << "Highest priority on waiting list queue:\n";
		cout << highestPriority.GetName() << "\t" << PriorityLevelName[ highestPriority.GetPriority() ] << "\n\n";

		cout << "Lowest priority on waiting list queue:\n";
		cout << lowestPriority.GetName() << "\t" << PriorityLevelName[ lowestPriority.GetPriority() ] << "\n\n";
	}
	else
		cout << "No passengers on the waiting list.\n";



	mUI.mHeader.SetMode(Header_MainMenu);
	mUI.mHeader.SetName( HeaderName[mUI.mHeader.GetMode()].c_str() );
	cout << "\n\n";
	system("pause");
	system("cls");
}

void Application::DeleteQueue()
{
	InitSubMenu();
	
	cout << "Are you sure you want to delete the queue?\n";
	cout << "Y/y for yes\n";
	cout << "N/n for no\n";

	char userInput = ' ';
	while( userInput != 'n' && userInput != 'N' &&
			userInput != 'y' && userInput != 'Y' )
	{
		mUI.SetCursorPosition(0, mUI.mHeader.GetY() + 6);
		mUI.DrawWhiteSpace();
		cin >> userInput;
	}

	if(userInput == 'y' || userInput == 'Y')
	{
		//delete on flight queue
		mOnFlightHeap.Delete();
		//delete waiting list queue
		mWaitingListHeap.Delete();

		//reset all id linked lists
		ResetIDLinkedLists();

		cout << "\nPriority queue deleted.\n";
	}

	mUI.mHeader.SetMode(Header_MainMenu);
	mUI.mHeader.SetName( HeaderName[mUI.mHeader.GetMode()].c_str() );
	cout << "\n\n";
	system("pause");
	system("cls");
}

void Application::Exit()
{
	mUI.DrawHeader();
	mUI.SetCursorPosition(0, mUI.mHeader.GetY() + 2);

	cout << "You are about to exit the program. Are you sure you wish to exit?\n";
	cout << "Y/y for yes\n";
	cout << "N/n for no\n";

	char userInput = ' ';
	while( userInput != 'n' && userInput != 'N' &&
			userInput != 'y' && userInput != 'Y' )
	{
		mUI.SetCursorPosition(0, mUI.mHeader.GetY() + 6);
		mUI.DrawWhiteSpace();
		cin >> userInput;
	}

	if(userInput == 'y' || userInput == 'Y')
	{
		cout << "\nThank you for using this application.\n";
		system("pause");
		exit(0);
	}

	mUI.mHeader.SetMode(Header_MainMenu);
	mUI.mHeader.SetName( HeaderName[mUI.mHeader.GetMode()].c_str() );
	cout << "\n\n";
	system("pause");
	system("cls");
}