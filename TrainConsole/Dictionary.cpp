
#include "pch.h"
#include "Dictionary.h"	// firstNodeer file


// constructor
Dictionary::Dictionary()
{
	for (int i = 0; i < MAX_SIZE; i++)
		items[i] = NULL;
	size = 0;
}

// destructor
Dictionary::~Dictionary()
{
	for (int i = 0; i < MAX_SIZE; i++)
	{
		if (items[i] != NULL)
		{
			Node *current = items[i];
			Node *previous = NULL;
			while (current != NULL)
			{
				//previous = current;
				//current = current->next;
				//delete previous;
				delete current;
			}
		}
	}
}

int charvalue(char c)
{
	if (isalpha(c))
	{
		if (isupper(c))
			return (int)c - (int) 'A';
		else
			return (int)c - (int) 'a'; //ignore case
	}
	else
		return -1;
}

// get the hash value for the given search key
int Dictionary::hash(KeyType key)
{
	int total = charvalue(key[0]);

	for (int i = 1; i < key.size(); i++)
	{
		if (charvalue(key[i]) < 0)  // not an alphabet
		{
			total = total*10 + key[i] - '0';
		}
		else
		{
			total = total * 26 + charvalue(key[i]);
		}

		total %= MAX_SIZE;
	}
	//	cout << total << endl;

	return total;
}

void Dictionary::insertEdge(int fromIndex, int toIndex, int distance)
{
	Edge *newEdge = new Edge;
	newEdge->distance = distance;
	newEdge->item = items[toIndex];
	newEdge->next = NULL;

	if (items[fromIndex]->edge == NULL) // no edge
	{
		items[fromIndex]->edge = newEdge;
	}
	else
	{
		//insertion sort
		Edge *current = items[fromIndex]->edge;

		if (current->distance > distance) //new distance shorter
		{
			newEdge->next = current;
			items[fromIndex]->edge = newEdge;
		}
		else
		{
			while (current->next != NULL && current->next->distance < distance)
				current = current->next;

			newEdge->next = current->next;
			current->next = newEdge;
		}
	}
}

// add edge to item with the specified key in the Dictionary
bool Dictionary::addEdge(KeyType fromKey, KeyType toKey, int distance)
{
	int fromIndex = hash(fromKey);
	int toIndex = hash(toKey);
	
	if (items[fromIndex] == NULL || items[toIndex] == NULL)
		return false;

	insertEdge(fromIndex, toIndex, distance);
	insertEdge(toIndex, fromIndex, distance);

	return true;
}

// add a new item with a specified key in the Dictionary
bool Dictionary::add(KeyType newKey, ItemType newItem)
{
	int index = hash(newKey);

	if (items[index] == NULL) // space is empty - start new list
	{
		items[index] = new Node;
		items[index]->key = newKey;
		items[index]->item = newItem;
		items[index]->edge = NULL;
	}
	else // collision
	{
		cout << "Collision at " << index << " - " << newKey << " and " << items[index]->key << endl;
		return false;

		////		cout << "Collision at " << index << " - " << newKey << " and " << items[index]->key << endl;
		//		// check for duplicate key while traversing list
		//Node *current = items[index];

		//if (current->key == newKey) // duplicate key
		//	return false;

		//while (current->next != NULL)
		//{
		//	cout << current->key << endl;
		//	current = current->next;
		//	if (current->item == newItem) // duplicate key
		//		return false;
		//}

		//// Add new node to end of list
		//Node *newNode = new Node;
		//newNode->key = newKey;
		//newNode->item = newItem;
		//newNode->next = NULL;
		//current->next = newNode;
	}

	size++;
	return true;
}


// remove an item with the given search key in the Dictionary
void Dictionary::remove(KeyType key)
{
	int index = hash(key);

	if (items[index] != NULL)
	{
		Node *current = items[index];

		if (current->key == key)
		{
			//items[index] = items[index]->next;
			delete current;
			size--;
		}
		/*else
		{
			//no collisions
			while ((current->next != NULL) && (current->next->key != key))
			{
				current = current->next;
			}
			if (current->next != NULL)
			{
				Node *temp = current->next;
				current->next = temp->next;
				delete temp;
				size--;
			}
		}*/
	}
}


// get an item with the specified key from the Dictionary (retrieve)
ItemType Dictionary::get(KeyType key)
{
	int index = hash(key);

	if (items[index] != NULL)
	{
		Node *current = items[index];

		//while ((current->key != key) && (current != NULL))
		//	current = current->next;

		if (current != NULL)
			return current->item;
	}

	return "NULL";
}

// check if the specified key is in the Dictionary
/*bool Dictionary::contains(KeyType key)
{
	int index = hash(key);

	if (items[index] != NULL)
	{
		Node *current = items[index];

		while ((current->key != key) && (current != NULL))
			current = current->next;

		if (current != NULL)
			return true;
	}
	return false;
}*/


// check if the Dictionary is empty
bool Dictionary::isEmpty()
{
	return size == 0;
}

// check the size of the Dictionary
int Dictionary::getLength()
{
	return size;
}

//------------------- Other useful functions -----------------
void Dictionary::print()
{
	for (int i = 0; i < MAX_SIZE; i++)
		if (items[i] != NULL)
		{
			Node *current = items[i];
			cout << current->key << " - " << current->item;

			Edge *edge = current->edge;
			while (edge)
			{
				cout << " || " << edge->item->key << "(" << edge->distance << ")";
				edge = edge->next;
			}

			cout << endl;
		}
}



