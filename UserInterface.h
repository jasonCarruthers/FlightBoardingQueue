#pragma once
#include <windows.h>
using namespace std;


//class Mouse
//{
//public:
//	Mouse();
//
//	bool IsMousePressed();
//	void SetMousePressState(bool isPressed);
//	double GetTimeOfLastMousePress();
//	void SetTimeOfLastMousePress(double timePressed);
//	BOOL IsMouseMoving();
//	void SetMouseMoveState(BOOL isMoving);
//	int GetX();
//	int GetY();
//	void SetMouseLocation(int x, int y);
//	void Update(double appTimeElapsed);
//private:
//	LPPOINT mLoc;
//	BOOL mIsMoving;
//	bool mIsPressed;
//	double mTimeOfLastMousePress;
//};

class Location
{
public:
	Location();

	int GetX();
	void SetX(int x);
	int GetY();
	void SetY(int y);
private:
	int mX;
	int mY;
};

class Rect : public Location
{
public:
	Rect(int x = 0, int y = 0, int width = 0, int height = 0);

	int GetWidth();
	void SetWidth(int width);
	int GetHeight();
	void SetHeight(int height);
private:
	int mWidth;
	int mHeight;
};

class Button : public Rect
{
public:
	Button();

	string GetButtonName();
	void SetButtonName(string name);
	WORD GetTextColor();
	void SetTextColor(int color);
	bool IsButtonSelected();
	void SetSelectedState(bool selectedState);
	bool IsButtonPressed();
	void SetPressedState(bool pressedState);
private:
	string mName;
	WORD mTextColor;
	bool mIsSelected;
	bool mIsPressed;
};

class SelectionTool : public Rect
{
public:
	SelectionTool();

	string GetCurrentSelectedButtonName();
	void SetCurrentSelectedButtonName(string buttonName);
	bool GetPressedState();
	void SetPressedState(bool pressedState);

	void Update(Button buttonArray[], int menuSize, double timeElapsed);
private:
	string mCurrentSelectedButtonName;
	bool mIsPressed;
	double mTimeOfLastPress;
};

class Header : public Rect
{
public:
	Header();

	string GetName();
	void SetName(string name);
	int GetMode();
	void SetMode(int mode);
private:
	string mName;
	int mMode;
};

class UserInterface
{
public:
	UserInterface();

	Header mHeader;
	SelectionTool mSelectionTool;
	Button mMainMenuButton[ Num__MainMenuButtons ];

	int GetCurrentMenuSize();
	void SetCurrentMenuSize(int currentMenuSize);
	WORD GetStandardTextColor();
	COORD GetCursorPosition();
	void SetModeFromMainMenu(int mainMenuButton);
	void SetCursorPosition(int x, int y);
	void SetForegroundTextColor(int color, int intensity = Intensity_Normal);
	void SetBackgroundTextColor(int color, int intensity = Intensity_Normal);
	void NormalizeTextColor();
	void UpdateMainMenuButtons();
	void DrawHeader();
	void DrawQueueInfo();
	void DrawDividerLine();
	void DrawWhiteSpace();
	void DrawMainMenu();
	void DrawMainMenuOptions();
private:
	int mCurrentMenuSize; //needs to update in program still; never changes from Num__MainMenuButtons
	WORD mStandardTextColor;
	WORD mCurrentForegroundColor;
	WORD mCurrentBackgroundColor;
	COORD mCursorPosition;
};