#include <iostream>
#include <ctime>
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


//Global container object
Application *App;


//Function prototypes
void InitProgram();
string GetRandomPassengerName();
//Function prototypes: Test functions
void TestRandomlyGeneratedNames();



//Functions
void InitProgram()
{
	srand(static_cast<int>(time(0)));

	App = new Application();
}

int main()
{
	InitProgram();
	
	//main loop
	while( true /*until user presses the exit button*/ )
	{
		//Update functions
		App->mUI.mSelectionTool.Update(App->mUI.mMainMenuButton, App->mUI.GetCurrentMenuSize(), App->mTimeElapsed);
		App->Update();
	}

	system("pause");
	return 0;
}



//Functions for testing
void TestRandomlyGeneratedNames()
{
	Passenger testPassenger;

	for(int i = 0; i < 20; i++)
	{
		cout << testPassenger.GetName() << "\n";
		testPassenger.SetName( GetRandomPassengerName() );
	}
}