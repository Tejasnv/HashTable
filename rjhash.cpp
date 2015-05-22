#include <iostream>
#include <fstream>
#include<string>
#include <math.h>

using namespace std;

int counter = 0;
int ulternate = 0;

class hashing
{
public:
	hashing();
	~hashing();
	int hash(string key);
	void addWord(string word);

	int temp = 0;
	int sfold(char* key);
	int size();
	static const int tableSize = 4001;
	void print();
	void mostoccurring();

private:
	string word;
	string HashTable[tableSize];
	int update[tableSize];
	int cost[tableSize] ;
};

hashing::hashing()
{
	while (temp != tableSize)
	{
		HashTable[temp] = "NULL0";
		update[temp] = 0;
		cost[temp] = 0;
		temp++;
	}
}

hashing::~hashing()
{
}

int hashing::hash(string key)
{
	unsigned int hash = 0;
	int index;
	for (int i = 0; i < key.length(); i++)
	{
		hash = (hash + ((int)(key[i])) * 7);
	}
	index = hash % tableSize;
	return index;
}

void hashing::addWord(string word)
{
	string temp;
	int index = sfold((char *)word.c_str());
	if (HashTable[index] == "NULL0")
	{
		//		cout <<word<<"  "<< index << endl;
		HashTable[index] = word;
		counter++;
		update[index] = 1;
		cost[index] = 1;
	}
	else
	{
		if (word != HashTable[index])
		{
			while ((HashTable[index] != "NULL0") && (HashTable[index] != word))
			{
				index++;
				if (index == tableSize)
				{
					index = 0;
				}
				cost[index] = cost[index]++;
			}
		}
		else
		{
			cost[index] = cost[index]++;
		}
		update[index] = update[index]++; 
		HashTable[index] = word;
		ulternate++;
	}
}

int hashing::size()
{
	int arrayCounter = 0;
	for (int i = 0; i < tableSize; i++)
	{
		if (HashTable[i] != "NULL0")
		{	
			arrayCounter++;
		}
	}	
	return arrayCounter;
}

/*
long hashing::sfold(string s)
{
	int intLength = s.length() / 4;
	long sum = 0;
	for (int j = 0; j < intLength; j++) {
		char c[] = s.substring(j * 4, (j * 4) + 4).toCharArray();
		long mult = 1;
		for (int k = 0; k < c.length; k++) {
			sum += c[k] * mult;
			mult *= 256;
		}
	}

	char c[] = s.substring(intLength * 4).toCharArray();
	long mult = 1;
	for (int k = 0; k < c.length; k++) {
		sum += c[k] * mult;
		mult *= 256;
	}

	return(Math.abs(sum) % M);
}
*/

int hashing::sfold(char* key) 
{
	unsigned int* lkey = (unsigned int*)key;
	int intlength = strlen(key) / 4;
	unsigned int sum = 0;
	for (int i = 0; i<intlength; i++)
		sum += lkey[i];
	// Now deal with the extra chars at the end
	int extra = strlen(key) - intlength * 4;
	char temp[4];
	lkey = (unsigned int*)temp;
	lkey[0] = 0;
	for (int i = 0; i<extra; i++)
		temp[i] = key[intlength * 4 + i];
	sum += lkey[0];
//	cout << sum % tableSize;
	return sum % tableSize;
}

void hashing::print()
{
	int i = 0;
	int j = 0;
	float ratio;
	cout << "----------------------------------------------------\n";
	cout << "Comma separate list is : (";
	for (int k = 1; k < tableSize; k++)
	{

//		cout << endl<<HashTable[k] << "  " << update[k] << "  " << cost[k];
		i = i + update[k];
		j = j + cost[k];
		if (update[k] != 0)
		{
			ratio = (cost[k] / update[k]);
			cout << ratio ;
			if (k != tableSize - 1)
			{
				cout << ", ";
			}
		}	
	}
	cout << ")";
//	cout << "\nTotal Updat is : " << i;
//	cout << "\nTotal Cost is : " << j;
}

void hashing::mostoccurring()
{
	int tempArray[tableSize];
	for (int  i = 0; i < tableSize; i++)
	{
		tempArray[i] = update[i];
	}
	int curr, i, temp;
	for (curr = tableSize; curr > 0; curr--)
	{
		i = 0;
			while (i < curr - 1)
			{
				if (tempArray[i] > tempArray[i + 1])
				{
					temp = tempArray[i];
					tempArray[i] = tempArray[i + 1];
					tempArray[i + 1] = temp;
				}
				else
			i++;
		}
	}
	cout << "\n-------------------------------------------------------------------------------";
	cout << "\nMost Occurring words are : \n";
	int count = 0;
	for (int i = tableSize - 1; i > tableSize - 20; i--)
	{
		if (count != 12)
		{
			if (HashTable[tempArray[i]] != "NULL0")
			{
				cout <<count+1<<" )"<< HashTable[tempArray[i]] << " Occures " << tempArray[i] << " times \n";
				count++;
			}
		}
	}

}

int main()
{
	hashing hashy;
	int c = 0;
	ifstream file;
	file.open("RomeoAndJuliet.txt");
//	file.open("rnj.txt");
	string word;
	char x;
	word.clear();
	while (file >> word)
	{
//		hashy.print(word);
		hashy.addWord(word);
//		cout << word << endl;
//		c++;
		word.clear();
	}
//	cout << "Unique : " << counter << endl;
//	cout << "Others : " << ulternate << endl;
	cout << "The number of unique words in the input file :" << hashy.size()<<endl;
	hashy.print();
	hashy.mostoccurring();
}
