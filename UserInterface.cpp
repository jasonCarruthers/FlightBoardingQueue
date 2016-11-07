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


string PriorityLevelName[ Num__PriorityTypes ] =
{
	"First Class Global Service",
	"Global Service",
	"First Class Premium Executive",
	"First Class Premium",
	"First Class Standard",
	"Premium Executive",
	"Premium",
	"Standard",
};

string HeaderName[ Num__Headers ] =
{
	"Main Menu",
	"Add Passengers to Queue",
	"Remove Passengers from Queue",
	"Change Status of Existing Passenger",
	"Inspect Priority of Passengers",
	"Delete Entire Queue",
	"Exit Application",
};

string MainMenuButton[ Num__MainMenuButtons ] =
{
	"Add passengers",
	"Remove passengers",
	"Change status of existing passenger",
	"Inspect priority of passengers",
	"Delete queue",
	"Exit program",
};

//Location functions
Location::Location()
{
	mX = 0;
	mY = 0;
}

int Location::GetX()
{
	return mX;
}

void Location::SetX(int x)
{
	mX = x;
}

int Location::GetY()
{
	return mY;
}

void Location::SetY(int y)
{
	mY = y;
}

//Rect functions
Rect::Rect(int x, int y, int width, int height)
{
	SetX(x);
	SetY(y);
	mWidth = width;
	mHeight = height;
}

int Rect::GetWidth()
{
	return mWidth;
}

void Rect::SetWidth(int width)
{
	mWidth = width;
}

int Rect::GetHeight()
{
	return mHeight;
}

void Rect::SetHeight(int height)
{
	mHeight = height;
}

//Button functions
Button::Button()
{
	SetX(0);
	SetY(0);
	SetWidth(0);
	SetHeight(0);
	mIsSelected = false;
	mIsPressed = false;
}

string Button::GetButtonName()
{
	return mName.c_str();
}

void Button::SetButtonName(string name)
{
	mName = name;	
}	

WORD Button::GetTextColor()
{
	return mTextColor;
}

void Button::SetTextColor(int color)
{
	mTextColor = color;
}

bool Button::IsButtonSelected()
{
	return mIsSelected;
}

void Button::SetSelectedState(bool selectedState)
{
	mIsSelected = selectedState;
}

bool Button::IsButtonPressed()
{
	return mIsPressed;
}

void Button::SetPressedState(bool pressedState)
{
	mIsPressed = pressedState;
}

//SelectionTool functions
SelectionTool::SelectionTool()
{
	SetX(0);
	SetY(0);
	SetWidth(SCREEN_WIDTH);
	SetHeight(1);

	mCurrentSelectedButtonName = "";
	mIsPressed = false;
	mTimeOfLastPress = 0.0;
}

void SelectionTool::Update(Button buttonArray[], int menuSize, double timeElapsed)
{
	int dY = 0;

	//get arrow key press, up or down
	if( GetAsyncKeyState(VK_UP) )
		dY = -1;
	else if( GetAsyncKeyState(VK_DOWN) )
		dY = 1;

	//if change, update location
	if(dY != 0)
	{
		if( !((GetY() == buttonArray[0].GetY() && dY == -1) || (GetY() == buttonArray[menuSize - 1].GetY() && dY == 1)) &&
			 mTimeOfLastPress + BUTTON_PRESS_OFFSET <= timeElapsed )
		{
			SetY( GetY() + dY );
			mTimeOfLastPress = timeElapsed;
		}
	}

	//check for "Enter" key press
	if( GetAsyncKeyState(VK_RIGHT) )
	{
		mIsPressed = true;
	}

	//update current button map
	for(int i = 0; i < menuSize; i++)
	{
		if( buttonArray[i].GetY() == GetY() )
		{
			if( strcmp(buttonArray[i].GetButtonName().c_str(), mCurrentSelectedButtonName.c_str()) )
				mCurrentSelectedButtonName = buttonArray[i].GetButtonName();
			if( mIsPressed )
				buttonArray[i].SetPressedState(true);
			break;
		}
	}
}

string SelectionTool::GetCurrentSelectedButtonName()
{
	return mCurrentSelectedButtonName;
}

void SelectionTool::SetCurrentSelectedButtonName(string buttonName)
{
	mCurrentSelectedButtonName = buttonName;
}

bool SelectionTool::GetPressedState()
{
	return mIsPressed;
}

void SelectionTool::SetPressedState(bool pressedState)
{
	mIsPressed = pressedState;
}

//Header functions
Header::Header()
{
	SetX(0);
	SetY(0);
	SetWidth(SCREEN_WIDTH);
	SetHeight(1);
}

string Header::GetName()
{
	return mName.c_str();
}

void Header::SetName(string name)
{
	mName = name;
}

int Header::GetMode()
{
	return mMode;
}

void Header::SetMode(int mode)
{
	mMode = mode;
}

//UserInterface functions
UserInterface::UserInterface()
{
	PCONSOLE_SCREEN_BUFFER_INFO startingScreenInfo = (PCONSOLE_SCREEN_BUFFER_INFO) malloc(sizeof(PCONSOLE_SCREEN_BUFFER_INFO));
	GetConsoleScreenBufferInfo( GetStdHandle(STD_OUTPUT_HANDLE), startingScreenInfo );
	mStandardTextColor = startingScreenInfo->wAttributes;

	mCurrentForegroundColor = mStandardTextColor;
	mCurrentBackgroundColor = mStandardTextColor;
	
	mCursorPosition.X = 0;
	mCursorPosition.Y = 0;

	mHeader.SetMode(Header_MainMenu);
	mHeader.SetName(HeaderName[ mHeader.GetMode() ]);
	mHeader.SetX(SCREEN_WIDTH/2 - strlen(mHeader.GetName().c_str())/2);
	mHeader.SetY(1);

	mCurrentMenuSize = Num__MainMenuButtons;
	for(int i = 0; i < mCurrentMenuSize; i++)
	{
		mMainMenuButton[i].SetButtonName( MainMenuButton[i].c_str() );
		mMainMenuButton[i].SetWidth(strlen(MainMenuButton[i].c_str()));
		mMainMenuButton[i].SetHeight(1);
		mMainMenuButton[i].SetX((SCREEN_WIDTH / 2) - mMainMenuButton[i].GetWidth()/2);
		mMainMenuButton[i].SetY(mHeader.GetY() + 2 + i);
	}
}

int UserInterface::GetCurrentMenuSize()
{
	return mCurrentMenuSize;
}

void UserInterface::SetCurrentMenuSize(int currentMenuSize)
{
	mCurrentMenuSize = currentMenuSize;
}

WORD UserInterface::GetStandardTextColor()
{
	return mStandardTextColor;
}

COORD UserInterface::GetCursorPosition()
{
	return mCursorPosition;
}

void UserInterface::SetCursorPosition(int x, int y)
{
	mCursorPosition.X = x;
	mCursorPosition.Y = y;
	SetConsoleCursorPosition( GetStdHandle(STD_OUTPUT_HANDLE), mCursorPosition );
}

void UserInterface::SetModeFromMainMenu(int mainMenuButton)
{
	switch(mainMenuButton)
	{
	case MainMenuButton_Add:
		mHeader.SetMode(Header_Add);
		mHeader.SetName(HeaderName[mHeader.GetMode()]);
		break;

	case MainMenuButton_Remove:
		mHeader.SetMode(Header_Remove);
		mHeader.SetName(HeaderName[mHeader.GetMode()]);
		break;

	case MainMenuButton_Change:
		mHeader.SetMode(Header_Change);
		mHeader.SetName(HeaderName[mHeader.GetMode()]);
		break;

	case MainMenuButton_Inspect:
		mHeader.SetMode(Header_Inspect);
		mHeader.SetName(HeaderName[mHeader.GetMode()]);
		break;

	case MainMenuButton_Delete:
		mHeader.SetMode(Header_Delete);
		mHeader.SetName(HeaderName[mHeader.GetMode()]);
		break;

	case MainMenuButton_Exit:
		mHeader.SetMode(Header_Exit);
		mHeader.SetName(HeaderName[mHeader.GetMode()]);
		break;

	default:
		break;
	};

	system("cls");
}

void UserInterface::DrawHeader()
{
	//draw first divider line
	SetCursorPosition(0, 0);
	SetBackgroundTextColor(Color_Red, Intensity_Normal);
	SetForegroundTextColor(Color_Green, Intensity_Light);
	DrawDividerLine();

	//draw header name
	SetCursorPosition(mHeader.GetX(), mHeader.GetY());
	cout << mHeader.GetName().c_str();

	//draw second divider line
	SetCursorPosition(0, 2);
	SetForegroundTextColor(Color_Green, Intensity_Light);
	DrawDividerLine();
	NormalizeTextColor();
}

//call this function from the InspectQueue function
void UserInterface::DrawQueueInfo()
{
	SetCursorPosition(0, 0);
	cout << "Total passengers assigned to queue: FOO";
	SetCursorPosition(SCREEN_WIDTH/2, 0);
	cout << "Available seats: BAR";

	SetCursorPosition(0, 1);
	for(int i = 0; i < Num__PriorityTypes; i++)
	{
		cout << PriorityLevelName[i].c_str() << "  \n";
	}

	DrawDividerLine();
}

void UserInterface::DrawDividerLine()
{
	for(int i = 0; i < SCREEN_WIDTH; i++)
		cout << "-";
}

void UserInterface::DrawWhiteSpace()
{
	for(int i = 0; i < SCREEN_WIDTH; i++)
		cout << " ";
	SetCursorPosition(static_cast<int>(mCursorPosition.X), static_cast<int>(mCursorPosition.Y));
}

void UserInterface::DrawMainMenu()
{
	DrawHeader();
	DrawMainMenuOptions();
}

void UserInterface::DrawMainMenuOptions()
{
	for(int i = 0; i < Num__MainMenuButtons; i++)
	{
		SetCursorPosition(mMainMenuButton[i].GetX(), mMainMenuButton[i].GetY());
		SetForegroundTextColor(mMainMenuButton[i].GetTextColor(), Intensity_Light);
		cout << mMainMenuButton[i].GetButtonName().c_str();
		NormalizeTextColor();
	}
}

void UserInterface::NormalizeTextColor()
{
	SetConsoleTextAttribute( GetStdHandle(STD_OUTPUT_HANDLE), mStandardTextColor );
	mCurrentForegroundColor = mStandardTextColor;
	mCurrentBackgroundColor = mStandardTextColor;
}

void UserInterface::SetForegroundTextColor(int color, int intensity)
{
	if( color < 0 || color >= Num__AvailableColors || color == Color_Black )
		color = Color_White;
	if(intensity < 0 || intensity >= Num__ColorIntensities)
		intensity = Intensity_Normal;

	switch( color )
	{
	case Color_White:
		NormalizeTextColor();
		break;

	case Color_Red:
		if( intensity == Intensity_Normal )
			mCurrentForegroundColor = FOREGROUND_RED;
		else
			mCurrentForegroundColor = FOREGROUND_RED | FOREGROUND_INTENSITY;
		break;

	case Color_Green:
		if( intensity == Intensity_Normal )
			mCurrentForegroundColor = FOREGROUND_GREEN;
		else
			mCurrentForegroundColor = FOREGROUND_GREEN | FOREGROUND_INTENSITY;
		break;

	case Color_Blue:
		if( intensity == Intensity_Normal )
			mCurrentForegroundColor = FOREGROUND_BLUE;
		else
			mCurrentForegroundColor = FOREGROUND_BLUE | FOREGROUND_INTENSITY;
		break;

	case Color_Yellow:
		if( intensity == Intensity_Normal )
			mCurrentForegroundColor = FOREGROUND_RED | FOREGROUND_GREEN;
		else
			mCurrentForegroundColor = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY;
		break;

	case Color_Purple:
		if( intensity == Intensity_Normal )
			mCurrentForegroundColor = FOREGROUND_RED | FOREGROUND_BLUE;
		else
			mCurrentForegroundColor = FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_INTENSITY;
		break;
	
	default:
		NormalizeTextColor();
		break;
	}

	if( mCurrentBackgroundColor != mStandardTextColor )
		SetConsoleTextAttribute( GetStdHandle(STD_OUTPUT_HANDLE), mCurrentForegroundColor | mCurrentBackgroundColor );
	else
		SetConsoleTextAttribute( GetStdHandle(STD_OUTPUT_HANDLE), mCurrentForegroundColor );
}

void UserInterface::SetBackgroundTextColor(int color, int intensity)
{
	if( color < 0 || color >= Num__AvailableColors || color == Color_Black )
		color = Color_White;
	if(intensity < 0 || intensity >= Num__ColorIntensities)
		intensity = Intensity_Normal;

	switch( color )
	{
	case Color_White:
		NormalizeTextColor();
		break;

	case Color_Red:
		if( intensity == Intensity_Normal )
			mCurrentBackgroundColor = BACKGROUND_RED;
		else
			mCurrentBackgroundColor = BACKGROUND_RED | BACKGROUND_INTENSITY;
		break;

	case Color_Green:
		if( intensity == Intensity_Normal )
			mCurrentBackgroundColor = BACKGROUND_GREEN;
		else
			mCurrentBackgroundColor = BACKGROUND_GREEN | BACKGROUND_INTENSITY;
		break;

	case Color_Blue:
		if( intensity == Intensity_Normal )
			mCurrentBackgroundColor = BACKGROUND_BLUE;
		else
			mCurrentBackgroundColor = BACKGROUND_BLUE | BACKGROUND_INTENSITY;
		break;

	case Color_Yellow:
		if( intensity == Intensity_Normal )
			mCurrentBackgroundColor = BACKGROUND_RED | BACKGROUND_GREEN;
		else
			mCurrentBackgroundColor = BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_INTENSITY;
		break;

	case Color_Purple:
		if( intensity == Intensity_Normal )
			mCurrentBackgroundColor = BACKGROUND_RED | BACKGROUND_BLUE;
		else
			mCurrentBackgroundColor = BACKGROUND_RED | BACKGROUND_BLUE | BACKGROUND_INTENSITY;
		break;
	
	default:
		NormalizeTextColor();
		break;
	}

	if( mCurrentForegroundColor != mStandardTextColor )
		SetConsoleTextAttribute( GetStdHandle(STD_OUTPUT_HANDLE), mCurrentForegroundColor | mCurrentBackgroundColor );
	else
		SetConsoleTextAttribute( GetStdHandle(STD_OUTPUT_HANDLE), mCurrentBackgroundColor );
}

void UserInterface::UpdateMainMenuButtons()
{
	for(int i = 0; i < Num__MainMenuButtons; i++)
	{
		//check to see if any main menu button is moused over
		if( !strcmp(MainMenuButton[i].c_str(), mSelectionTool.GetCurrentSelectedButtonName().c_str()) )
		{
			if(!mMainMenuButton[i].IsButtonSelected())
			{
				mMainMenuButton[i].SetSelectedState(true);
				mMainMenuButton[i].SetTextColor(Color_Yellow);
			}
		}
		else
		{
			if(mMainMenuButton[i].IsButtonSelected())
			{
				mMainMenuButton[i].SetSelectedState(false);
				mMainMenuButton[i].SetTextColor(Color_White);
			}
		}

		//check to see if any main menu button is pressed
		if(mMainMenuButton[i].IsButtonSelected() && mSelectionTool.GetPressedState())
		{
			SetModeFromMainMenu(i);

			mMainMenuButton[i].SetSelectedState(false);
			mSelectionTool.SetPressedState(false);
		}
	}
}