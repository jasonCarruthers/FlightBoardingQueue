#pragma once
using namespace std;


template <typename GenericType>
class BinaryTree
{
public:
	BinaryTree();

	//Accessors
	int GetCurrentSize();
	GenericType GetLeastValuable();
	GenericType GetMostValuable();
	GenericType GetLinearSortObject(int index);
	bool IsEmpty();
	bool IsFull();

	//Mutators
	Passenger Remove(string removeObj);
	void Insert(GenericType insertObj);
	void MakeHeap();
	void Delete();
private:
	void SortAsHeap(int rootIndex);
	void InsertIntoLinearSort(GenericType insertObj);
	void RemoveFromLinearSort(string removeObj);

	GenericType mArray[MAX_PASSENGERS_PER_FLIGHT];
	GenericType mLinearSort[MAX_PASSENGERS_PER_FLIGHT];
	int mCurrentSize;
};



template <typename GenericType>
BinaryTree<GenericType>::BinaryTree()
{
	mCurrentSize = 0;
}

//Accessors
template <typename GenericType>
int BinaryTree<GenericType>::GetCurrentSize()
{
	return mCurrentSize;
}

template <typename GenericType>
GenericType BinaryTree<GenericType>::GetMostValuable()
{
	return mLinearSort[0];
}

template <typename GenericType>
GenericType BinaryTree<GenericType>::GetLeastValuable()
{
	return mLinearSort[mCurrentSize - 1];
}

template <typename GenericType>
GenericType BinaryTree<GenericType>::GetLinearSortObject(int index)
{
	return mLinearSort[index];
}

template <typename GenericType>
bool BinaryTree<GenericType>::IsEmpty()
{
	if(mCurrentSize == 0)
		return true;
	return false;
}

template <typename GenericType>
bool BinaryTree<GenericType>::IsFull()
{
	if(mCurrentSize == MAX_PASSENGERS_PER_FLIGHT)
		return true;
	return false;
}

//Mutators
template <typename GenericType>
void BinaryTree<GenericType>::Insert(GenericType insertObj)
{
	if( !IsFull() )
	{
		//insert into linearly sorted arry
		InsertIntoLinearSort(insertObj);

		//insert into binary tree array
		mArray[ mCurrentSize ] = insertObj;
		mCurrentSize++;

		//make heap
		MakeHeap();
	}
}

template <typename GenericType>
Passenger BinaryTree<GenericType>::Remove(string removeObj)
{
	Passenger passenger;	

	if( !IsEmpty() )
	{
		//remove from linearly sorted arry
		RemoveFromLinearSort(removeObj);

		//find removeObj, remove from binary tree array
		//swap "right-most" leaf into empty slot (where item was removed)
		for(int i = 0; i < mCurrentSize; i++)
		{
			if(mArray[i].GetName() == removeObj)
			{
				passenger.SetName(mArray[i].GetName());
				passenger.SetPriority(mArray[i].GetPriority());
				passenger.SetTimeOfTicketPurchase(mArray[i].GetTimeOfTicketPurchase());
				passenger.SetID();

				mArray[i] = mArray[mCurrentSize - 1];
				break;
			}
		}
		mCurrentSize--;
		
		//make heap
		MakeHeap();
	}
	
	//return removeObj's passenger (for adding to the waiting list queue)
	return passenger;
}

template <typename GenericType>
void BinaryTree<GenericType>::MakeHeap()
{
	//sort binary tree into a heap
	for(int i = mCurrentSize - 1; i >= 0; i--)
		SortAsHeap( i );
}

template <typename GenericType>
void BinaryTree<GenericType>::SortAsHeap(int rootIndex)
{
	//if rootIndex is a leaf, return
	if( (rootIndex * 2) + 1 >= mCurrentSize && (rootIndex * 2) + 2 >= mCurrentSize )
		return;
	
	//get the largest child of the given root
	int largestChildIndex = -1;
	if( (rootIndex * 2) + 2 >= mCurrentSize )
		largestChildIndex = (rootIndex * 2) + 1;
	else
		largestChildIndex = (mArray[(rootIndex * 2) + 1].GetID() > mArray[(rootIndex * 2) + 2].GetID()) ? (rootIndex * 2) + 1 : (rootIndex * 2) + 2;
	GenericType largestChild = mArray[largestChildIndex];

	//if the root at rootIndex is smaller than the largest child, swap
	if( largestChild.GetID() > mArray[rootIndex].GetID() )
	{
		GenericType temp = mArray[rootIndex];
		mArray[rootIndex] = largestChild;
		mArray[largestChildIndex] = temp;
		
		//then recurrsion
		SortAsHeap(largestChildIndex);
	}
	//otherwise, return
	else
		return;
}

template <typename GenericType>
void BinaryTree<GenericType>::InsertIntoLinearSort(GenericType insertObj)
{
	int index = GARBAGE_VALUE;

	//search for index to insert obj at
	if(!IsEmpty())
	{
		for(int i = 0; i < mCurrentSize; i++)
		{
			if((mLinearSort[i].GetPriority() == insertObj.GetPriority() && insertObj.GetTimeOfTicketPurchase() < mLinearSort[i].GetTimeOfTicketPurchase()) ||
				mLinearSort[i].GetID() > insertObj.GetID())
			{
				index = i;
				break;
			}
		}
	}
	else
		index = 0;

	if(index == GARBAGE_VALUE)
		index = mCurrentSize;

	//insert
	for(int i = mCurrentSize - 1; i >= index; i--)
	{
		mLinearSort[i + 1] = mLinearSort[i];
	}
	mLinearSort[index] = insertObj;
}

template <typename GenericType>
void BinaryTree<GenericType>::RemoveFromLinearSort(string removeObj)
{
	int index = GARBAGE_VALUE;

	for(int i = 0; i < mCurrentSize; i++)
	{
		if(mLinearSort[i].GetName() == removeObj)
		{
			index = i;
			break;
		}
	}

	//remove
	for(int i = index + 1; i < mCurrentSize; i++)
	{
		mLinearSort[i - 1] = mLinearSort[i];
	}
}

template <typename GenericType>
void BinaryTree<GenericType>::Delete()
{
	Passenger voidPassenger;

	for(int i = 0; i < mCurrentSize; i++)
	{
		mArray[i] = voidPassenger;
		mLinearSort[i] = voidPassenger;
	}

	mCurrentSize = 0;
}