#pragma once
using namespace std;


class Application
{
public:
 	Application();

	double mTimeElapsed;
	UserInterface mUI;
	//linked list of all IDs; each priority has MAX_PASSENGERS_PER_FLIGHT number of IDs
	LinkedList<int> mFCEGlobalServiceIDList;
	LinkedList<int> mGlobalServiceIDList;
	LinkedList<int> mFCEPremiumExecutiveIDList;
	LinkedList<int> mFCEPremiumIDList;
	LinkedList<int> mFCEStandardIDList;
	LinkedList<int> mPremiumExecutiveIDList;
	LinkedList<int> mPremiumIDList;
	LinkedList<int> mStandardIDList;
	//Two different heaps
	BinaryTree<Passenger> mOnFlightHeap;
	BinaryTree<Passenger> mWaitingListHeap;

	void InitSubMenu();
	void RescindID(int ID);
	void Update();
	void SortPassengerIntoQueue(Passenger sortPassenger);
	int GetPriorityFromUser();
	string GetNameFromUser();
	void InitIDLinkedLists();
	void ResetIDLinkedLists();
	void AddToQueue();
	void RemoveFromQueue();
	void ChangeStatusWithinQueue();
	void InspectQueue();
	void DeleteQueue();
	void Exit();
};

//only use this line if App is used in .cpp files other than Main.cpp
extern Application *App;