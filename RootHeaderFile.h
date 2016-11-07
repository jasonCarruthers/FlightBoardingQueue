#pragma once
using namespace std;


const int SCREEN_WIDTH = 80;
const int SCREEN_HEIGHT = 20;
const int FONT_WIDTH = 8;
const int FONT_HEIGHT = 12;
const double BUTTON_PRESS_OFFSET = 0.2;
const int GARBAGE_VALUE = -9999;
const int MAX_PASSENGERS_PER_FLIGHT = 200;


enum InsertTypes
{
	InsertType_Front,
	InsertType_Back,

	Num__InsertTypes,
};

//enum RemoveTypes
//{
//	RemoveType_First,
//	//RemoveType_Unique,
//	RemoveType_All,
//
//	Num__RemoveTypes,
//};

enum PriorityTypeOrder
{
	Priority_FCEGlobalService, //FCE stands for first-class price for an economy seat
	Priority_GlobalService,
	Priority_FCEPremiumExecutive,
	Priority_FCEPremium,
	Priority_FCEStandard, //passenger with no special status
	Priority_PremiumExecutive,
	Priority_Premium,
	Priority_Standard, //passenger with no special status who buys an economy ticket

	Num__PriorityTypes,
};

enum Headers
{
	Header_MainMenu,
	Header_Add,
	Header_Remove,
	Header_Change,
	Header_Inspect,
	Header_Delete,
	Header_Exit,
	
	Num__Headers,
};

enum MainMenuButtons
{
	MainMenuButton_Add,
	MainMenuButton_Remove,
	MainMenuButton_Change,
	MainMenuButton_Inspect,
	MainMenuButton_Delete,
	MainMenuButton_Exit,

	Num__MainMenuButtons,
};

enum AddMenuButtons
{
	AddMenuButton_AddOne,
	AddMenuButton_AddMany,

	Num__AddMenuButtons,
};

enum RemoveMenuButtons
{
	RemoveMenuButton_RemoveOne,
	RemoveMenuButton_RemoveMany,

	Num__RemoveMenuButtons,
};

enum ChangeMenuButtons
{
	Num__ChangeMenuButtons,
};

enum InspectMenuButtons
{
	Num__InspectMenuButtons,
};

enum DeleteMenuButtons
{
	Num__DeleteMenuButtons,
};

enum AvailablePalette
{
	Color_Black,
	Color_White,
	Color_Red,
	Color_Green,
	Color_Blue,
	Color_Yellow,
	Color_Purple,

	Num__AvailableColors,
};

enum ColorIntensities
{
	Intensity_Normal,
	Intensity_Light,

	Num__ColorIntensities,
};

//For both the first and middle name enums, the number of male and female names must be equivalent
enum PassengerFirstNames
{
	//Males
	Pre__MaleFirstNames,
	FirstName_Aiden,
	FirstName_Jacob,
	FirstName_Jackson,
	FirstName_Santiago,
	FirstName_Jayden,
	FirstName_Ryan,
	FirstName_Elijah,
	FirstName_Robert,
	FirstName_Mia,
	FirstName_Malfegor,

	//Females
	Pre__FemaleFirstNames,
	FirstName_Ximena,
	FirstName_Emma,
	FirstName_Chloe,
	FirstName_Rachel,
	FirstName_Sarah,
	FirstName_Sofia,
	FirstName_Leah,
	FirstName_Barbara,
	FirstName_Anya,
	FirstName_Alexis,

	Num__PassengerFirstNames,
};

enum PassengerMiddleNames
{
	//Males
	Pre__MaleMiddleNames,
	MiddleName_Gray,
	MiddleName_Grey,
	MiddleName_James,
	MiddleName_Lou,
	MiddleName_Reid,
	MiddleName_Stephen,
	MiddleName_Van,
	MiddleName_William,

	//Females
	Pre__FemaleMiddleNames,
	MiddleName_Dawn,
	MiddleName_Day,
	MiddleName_Ignatia,
	MiddleName_Jade,
	MiddleName_Leigh,
	MiddleName_Lynn,
	MiddleName_Jane,
	MiddleName_Thi,

	Num__PassengerMiddleNames,
};

enum PassengerLastNames
{
	//Unisex
	LastName_Smith,
	LastName_Johnson,
	LastName_Williams,
	LastName_Brown,
	LastName_Jones,
	LastName_Miller,
	LastName_Davis,
	LastName_Garcia,
	LastName_Rodriguez,
	LastName_Wilson,

	Num__PassengerLastNames,
};


//extern string PassengerFirstName[Num__PassengerFirstNames];
//extern string PassengerMiddleName[Num__PassengerMiddleNames];
//extern string PassengerLastName[Num__PassengerLastNames];
extern string PriorityLevelName[ Num__PriorityTypes ];
extern string HeaderName[ Num__Headers ];