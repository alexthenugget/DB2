#include <iostream>
#include <fstream>
using namespace std;
#include "Album.h"
#include "Artist.h"
#include "Track.h"
#include <string>
#include "TrackList.h"

Artist::Artist()
{
	ID_Artist = 0;
	Name_Artist = "undefined";
	Year_Artist = 0;
	Country_Artist = "undefined";
	Producer_Artist = "undefined";
}

void Artist::Set(string str)
{
	int pos1, pos2, pos3, pos4;
	pos1 = str.find('|');
	int newID = stoi(str.substr(0, pos1));
	pos2 = str.find('|', pos1 + 1);
	string newName = str.substr(pos1 + 1, pos2 - pos1 - 1);
	pos3 = str.find('|', pos2 + 1);
	int Year = stoi(str.substr(pos2 + 1, pos3 - pos2 - 1));
	pos4 = str.find('|', pos3 + 1);
	string Country = str.substr(pos3 + 1, pos4 - pos3 - 1);
	string Producer = str.substr(pos4 + 1, str.length() - pos4 - 1);
	ID_Artist = newID;
	Name_Artist = newName;
	Year_Artist = Year;
	Country_Artist = Country;
	Producer_Artist = Producer;
}

void Artist::PrintInfo()
{
	cout << "Year of the artist: " << Year_Artist << endl;
	cout << "Country of the artist: " << Country_Artist << endl;
	cout << "Producer of the artist: " << Producer_Artist << endl;
}

string Artist::AllString()
{
	return to_string(ID_Artist) + '|' + Name_Artist + '|' + to_string(Year_Artist) + '|' + Country_Artist + '|' + Producer_Artist;
}

bool Artist::operator==(Artist Cell)
{
	if (ID_Artist == Cell.ID_Artist)
		return true;
	return false;
}

inline ListArtist::ListArtist()
{
	pHead = nullptr;
	pTail = nullptr;
	Size = 0;
}

void ListArtist::Add(Artist Cell)
{
	NodeArtist* nTail = new NodeArtist(Cell);
	if (pTail == nullptr)
	{
		pHead = pTail = nTail;
		Size++;
		return;
	}
	pTail->pNext = nTail;
	nTail->pPrev = pTail;
	pTail = nTail;
	Size++;
	return;
}

NodeArtist* ListArtist::GetpHead()
{
	return pHead;
}

void ListArtist::PrintNames()
{
	NodeArtist* NodeName = pHead;
	while (NodeName)
	{
		cout << NodeName->thisCell.Name_Artist << endl;
		NodeName = NodeName->pNext;
	}
}

void ListArtist::DeleteNode(Artist Cell)
{
	NodeArtist* Curr = pHead;
	while (Curr) {
		if (Curr->thisCell == Cell)
		{
			if (Curr == pHead)
			{
				NodeArtist* Del = Curr->pNext->pPrev;
				Curr->pNext->pPrev = Curr->pPrev;
				pHead = Curr->pNext;
				delete Del;
				break;

			}
			else
			{
				if (Curr == pTail)
				{
					NodeArtist* Del = Curr->pPrev->pNext;
					Curr->pPrev->pNext = Curr->pNext;
					pTail = Curr->pPrev;
					delete Del;
					break;
				}
				else
				{
					NodeArtist* Del = Curr->pPrev->pNext;
					Curr->pNext->pPrev = Curr->pPrev;
					Curr->pPrev->pNext = Curr->pNext;
					delete Del;
					break;
				}
			}
		}
		Curr = Curr->pNext;
	}
}

TableArtists::TableArtists()
{
	Path = "undefined";
	LastID = 0;
}

void TableArtists::UploadTable(string path)
{
	Artist Cell;
	ifstream file(path);
	if (file.is_open())
	{
		Path = path;
		while (!file.eof())
		{
			string str;
			getline(file, str);
			Cell.Set(str);
			TableList.Add(Cell);
		}
		LastID = Cell.ID_Artist;
		file.close();
	}
	else
	{
		throw "File is not opened";
	}
	cout << "Artists table uploaded successfully" << endl;
}

void TableArtists::PrintListOfNames()
{
	cout << "The list of names: " << endl;
	TableList.PrintNames();
}

ListArtist TableArtists::GetList()
{
	return TableList;
}

int TableArtists::GenerateID()
{
	LastID += 1;
	return LastID;
}

NodeArtist::NodeArtist(Artist Cell)
{
	thisCell = Cell;
	pNext = nullptr;
	pPrev = nullptr;
}

bool TableArtists::Exists(string Name)
{
	Artist Cell = Artist();
	string thisName;
	NodeArtist* NodeCell = TableList.GetpHead();
	while (NodeCell)
	{
		Cell = NodeCell->thisCell;
		thisName = Cell.Name_Artist;
		if (Name == thisName)
		{
			return true;
		}
		NodeCell = NodeCell->pNext;
	}
	return false;
}

Artist TableArtists::GetByName(string Name)
{
	Artist Cell = Artist();
	string thisName;
	NodeArtist* NodeCell = TableList.GetpHead();
	while (NodeCell)
	{
		Cell = NodeCell->thisCell;
		thisName = Cell.Name_Artist;
		if (Name == thisName)
		{
			return Cell;
		}
		NodeCell = NodeCell->pNext;
	}
}

void TableArtists::PrintByAlbumID(int ID)
{
	Artist Cell = Artist();
	int thisID;
	NodeArtist* NodeCell = TableList.GetpHead();
	while (NodeCell)
	{
		Cell = NodeCell->thisCell;
		thisID = Cell.ID_Artist;
		if (thisID == ID)
		{
			cout << Cell.Name_Artist << endl;
		}
		NodeCell = NodeCell->pNext;
	}
}

void TableArtists::AddToList(Artist Ar)
{
	TableList.Add(Ar);
}

void TableArtists::AddToFile(Artist Ar)
{
	ofstream file;
	file.open(Path, ios::app);
	if (!file.is_open())
	{
		throw "Artists table is not open";
	}
	file << '\n';
	file << Ar.AllString();
	file.close();
}

void TableArtists::UpdateFile()
{
	ofstream file;
	file.open(Path, std::ofstream::out | std::ofstream::trunc);
	NodeArtist* Ar = TableList.GetpHead();
	file << Ar->thisCell.AllString();
	Ar = Ar->pNext;
	while (Ar)
	{
		file << '\n';
		file << Ar->thisCell.AllString();
		Ar = Ar->pNext;
	}
	file.close();
}
