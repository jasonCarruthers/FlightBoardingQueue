#pragma once
using namespace std;


template <typename GenericType>
class LinkedList
{
public:
	//Constructor and The Big-3 
	LinkedList();
	LinkedList(const LinkedList &copy_obj);
	void operator= (const LinkedList equal_obj);
	~LinkedList();

	//Accessor methods
	GenericType GetFirstObject();
	bool IsEmpty();
	void Print();
	//Search function

	//Mutator methods
	void CreateFirstNode(GenericType data = NULL);
	void DeleteList();
	void CopyList(LinkedList copy_obj);
	void Insert(GenericType insert_obj, int insert_type);
	void Remove(GenericType remove_obj);
	//void Move(); //iter pointing to obj to move, iter pointing to obj dest
	//			//obj value, enum type specifying move dest
	//			//obj value, iter pointing to obj dest
	void Update();
private:
	class Node
	{
	public:
		Node()
		{
			mLink = NULL;
		}
	public:
		GenericType mData;
		Node *mLink;
	};

	int mCurrentLength;
	Node *mHeadPtr;
	Node *mTailPtr;
};

//The Big-3
template <typename GenericType>
LinkedList<GenericType>::LinkedList()
{
	mHeadPtr = NULL;
	mTailPtr = NULL;

	mCurrentLength = 0;
}

template <typename GenericType>
LinkedList<GenericType>::LinkedList(const LinkedList &copy_obj)
{
	CopyList( copy_obj );
}

template <typename GenericType>
void LinkedList<GenericType>::operator =(const LinkedList equal_obj)
{
	if(this != &equal_obj && !equal_obj.IsEmpty())
	{
		//delete current linked list
		DeleteList();

		//copy equal_obj into linked list
		CopyList(equal_obj);
	}
}

template <typename GenericType>
LinkedList<GenericType>::~LinkedList()
{
	DeleteList();
}

//Accessor methods
template <typename GenericType>
GenericType LinkedList<GenericType>::GetFirstObject()
{
	return mHeadPtr->mData;
}

template <typename GenericType>
bool LinkedList<GenericType>::IsEmpty()
{
	if( mHeadPtr->mLink == NULL )
		return true;
	return false;
}

template <typename GenericType>
void LinkedList<GenericType>::Print()
{
	if( mHeadPtr != NULL )
	{
		Node *node_iter = mHeadPtr;
		while( node_iter != NULL )
		{
			node_iter->mData.PrintData();
			node_iter = node_iter->mLink;
		}
	}
}

//Mutator methods
template <typename GenericType>
void LinkedList<GenericType>::CreateFirstNode(GenericType data)
{
	mHeadPtr = new Node;
	mHeadPtr->mData = data;
	mHeadPtr->mLink = NULL;

	mTailPtr = new Node;
	mTailPtr = mHeadPtr;

	mCurrentLength = 1;
}

template <typename GenericType>
void LinkedList<GenericType>::DeleteList()
{
	Node *node_iter = mHeadPtr;

	//delete current linked list
	while(node_iter != NULL)
	{
		mHeadPtr = mHeadPtr->mLink;
		delete node_iter;
		node_iter = mHeadPtr;

		mCurrentLength--;
	}

	mHeadPtr = NULL;
	mTailPtr = NULL;
}

template <typename GenericType>
void LinkedList<GenericType>::CopyList(LinkedList copy_obj)
{
	Node *node_iter = copy_obj.mHeadPtr;

	//iterate through copy_obj's list from the front
	while(node_iter != NULL)
	{
		//insert data at back of mList
		Insert(node_iter->mData, InsertType_Back);
		node_iter = node_iter->mLink;
	}
}

template <typename GenericType>
void LinkedList<GenericType>::Insert(GenericType insert_obj, int insert_type)
{
	if(mCurrentLength == 0)
	{
		CreateFirstNode(insert_obj);
		return;
	}

	Node *insert_node = new Node;
	insert_node->mData = insert_obj;
	insert_node->mLink = NULL;

	if(insert_type == InsertType_Front)
	{
		insert_node->mLink = mHeadPtr;
		mHeadPtr = insert_node;
		
		mCurrentLength++;
	}
	else if(insert_type == InsertType_Back)
	{
		mTailPtr->mLink = insert_node;
		insert_node->mLink = NULL;
		mTailPtr = insert_node;

		mCurrentLength++;
	}
	else
		cout << "Not a valid insert_type!\n";
}

template <typename GenericType>
void LinkedList<GenericType>::Remove(GenericType remove_obj)
{
	if(mHeadPtr != NULL)
	{
		Node *garbage = new Node;
		Node *movePtr = mHeadPtr;
		
		if(movePtr->mData == remove_obj)
		{
			garbage = mHeadPtr;
			mHeadPtr = mHeadPtr->mLink;
			delete garbage;
			garbage = NULL;
			
			mCurrentLength--;	
			return;
		}
		if(movePtr->mLink != NULL)
			movePtr = movePtr->mLink;

		//removing duplicates from the rest of the list
		while( movePtr != NULL )
		{	
			while( movePtr->mLink != NULL )
			{
				if( movePtr->mData == remove_obj )
				{
					garbage = movePtr;
					movePtr = movePtr->mLink;
					delete garbage;
					garbage = NULL;

					mCurrentLength--;
					return;
				}
				else if( movePtr->mLink->mLink == NULL && movePtr->mLink->mData == remove_obj )
				{
					movePtr->mLink = NULL;
					garbage = movePtr->mLink;
					delete garbage;

					mCurrentLength--;
					return;
				}
			}
		}
	}
}

template <typename GenericType>
void LinkedList<GenericType>::Update()
{
	if( mHeadPtr != NULL )
	{
		Node *node_iter = mHeadPtr;
		while( node_iter != NULL )
		{
			node_iter->mData.Update();
			node_iter = node_iter->mLink;
		}
	}
}