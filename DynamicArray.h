#pragma once
using namespace std;


//-----------------------
//THIS CLASS NEEDS WORK. currentLength should start at zero
//-----------------------

//Template class
template <typename GenericType>
class DynamicArray
{
public:
	DynamicArray(int maxCapacity = 0);
	DynamicArray(const DynamicArray& copy_object); //copy constructor
	void operator= (const DynamicArray equal_object); //operator overloader
	~DynamicArray();

	//Accessor methods
	bool IsEmpty();
	bool IsFull();
	GenericType Search(GenericType search_object);

	//Mutator methods
	void Allocate(int maxCapacity);
	void Insert(GenericType insert_object);
	void Remove(GenericType remove_object);

	GenericType *mList;
private:
	int mMaxCapacity;
	int mCurrentLength;
};


//Template functions
//-----------------------------------
template <typename GenericType>
DynamicArray<GenericType>::DynamicArray(int maxCapacity)
{
	mMaxCapacity = maxCapacity;
	mCurrentLength = 0;

	mList = new GenericType [mMaxCapacity];
}

template <typename GenericType>
DynamicArray<GenericType>::DynamicArray(const DynamicArray& copy_object)
{
	if(copy_object.mMaxCapacity > 0)
	{
		//if(copy_object.mMaxCapacity > 1)
		//{
		//	mList = new GenericType [copy_object.mMaxCapacity];

		//	for(int i = 0; i <= copy_object.mCurrentLength; i++)
		//		*mList[i] = *(copy_object.mList[i]);
		//}
		//else
		//{
			mMaxCapacity = copy_object.mMaxCapacity;
			mCurrentLength = copy_object.mCurrentLength;
			mList = new GenericType [mMaxCapacity];
			*mList = *(copy_object.mList);
		//}
	}
}

template <typename GenericType>
void DynamicArray<GenericType>::operator= (const DynamicArray equal_object)
{
	if(this != &equal_object)
	{
		//if(equal_object.mMaxCapacity > 1)
		//{
		//	delete[] mList;
		//	mList = new GenericType [equal_object.mMaxCapacity];

		//	for(int i = 0; i <= equal_object.mCurrentLength; i++)
		//		*mList[i] = *(equal_object.mList[i]);

		//	return;
		//}

		//delete mList;
		//mList = new GenericType;

		if( equal_object.mMaxCapacity > 0 )
			delete[] mList;

		mMaxCapacity = equal_object.mMaxCapacity;
		mCurrentLength = equal_object.mCurrentLength;
		mList = new GenericType [mMaxCapacity];
		*mList = *(equal_object.mList);
	}
}

template <typename GenericType>
DynamicArray<GenericType>::~DynamicArray()
{
	if(mMaxCapacity > 0)
	{
		mMaxCapacity = 0;
		mCurrentLength = 0;

		if(mMaxCapacity > 1)
			delete[] mList;
		else
			delete mList;
	}
}

//Accessor methods
template <typename GenericType>
bool DynamicArray<GenericType>::IsEmpty()
{
	if(mMaxCapacity > 0)
	{
		if(mCurrentLength == 0)
			return true;

		return false;
	}

	//make output text red
	cout << "DynamicArray: \"IsEmpty()\" ERROR.\n";
	return false;
}

template <typename GenericType>
bool DynamicArray<GenericType>::IsFull()
{
	if(mMaxCapacity > 0)
	{
		if(mCurrentLength == mMaxCapacity)
			return true;

		return false;
	}

	//make output text red
	cout << "DynamicArray: \"IsFull()\" ERROR.\n";
	return false;
}

template <typename GenericType>
GenericType DynamicArray<GenericType>::Search(GenericType search_object)
{
	if( mMaxCapacity > 0 && !IsEmpty() )
	{
		for(int i = 0; i < mCurrentLength; i++)
		{
			//if match is found
			if(mList[i] == search_object)
			{
				return search_object;
			}
		}
	}
}

//Mutator methods
template <typename GenericType>
void DynamicArray<GenericType>::Allocate(int maxCapactity)
{
	if(mMaxCapacity == 0 && maxCapacity > 0)
	{
		mMaxCapacity = maxCapacity;
		mCurrentLength = 0;
		mList = new GenericType [mMaxCapacity];
	}
}

template <typename GenericType>
void DynamicArray<GenericType>::Insert(GenericType insert_object)
{
	int i = mCurrentLength;
	int j = mCurrentLength;

	if( mMaxCapacity > 0 && !IsFull() )
	{
		if( IsEmpty() )
			mList[0] = insert_object;
		else
		{
			//find out which index to start pushing forward at, represented by i + 1
			for(; i >= 0; i--)
				if(insert_object >= mList[i])
					break;

			//push list contents past i forward
			for(; j >= i + 1; j--)
				mList[j + 1] = mList[j];

			mList[i + 1] = insert_object;
		}

		mCurrentLength++;
	}
}

template <typename GenericType>
void DynamicArray<GenericType>::Remove(GenericType insert_object)
{
	//write this later, it's not used in the rest of the code yet..
}