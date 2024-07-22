#include <iostream>
#include <fstream>
using namespace std;
#include <string>
#include "Album.h"
#include "Artist.h"
#include "Track.h"
#include "TrackList.h"

Track::Track()
{
	ID_Track = 0;
	Name_Track = "undefined";
	Time_Track = 0;
}

void Track::Set(string str)
{
	int pos1, pos2;
	pos1 = str.find('|');
	int newID = stoi(str.substr(0, pos1));
	pos2 = str.find('|', pos1 + 1);
	string newName = str.substr(pos1 + 1, pos2 - pos1 - 1);
	int Trackime = stoi(str.substr(pos2 + 1, str.length() - pos2 - 1));
	ID_Track = newID;
	Name_Track = newName;
	Time_Track = Trackime;
}

void Track::PrintInfo()
{
	cout << "Name of track: " << Name_Track << endl;
	cout << "Time of track: " << Time_Track << endl;
}

string Track::AllString()
{
	return to_string(ID_Track) + '|' + Name_Track + '|' + to_string(Time_Track);
}

bool Track::operator==(Track Cell)
{
	if (ID_Track == Cell.ID_Track)
		return true;
	return false;
}

inline ListTrack::ListTrack()
{
	pHead = nullptr;
	pTail = nullptr;
	Size = 0;
}

void ListTrack::Add(Track Cell)
{
	NodeTrack* nTail = new NodeTrack(Cell);
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

NodeTrack* ListTrack::GetpHead()
{
	return pHead;
}

void ListTrack::PrintNames()
{
	NodeTrack* NodeName = pHead;
	while (NodeName)
	{
		cout << NodeName->thisCell.Name_Track << endl;
		NodeName = NodeName->pNext;
	}
}

void ListTrack::DeleteNode(Track Cell)
{
	NodeTrack* Curr = pHead;
	while (Curr) {
		if (Curr->thisCell == Cell)
		{
			if (Curr == pHead)
			{
				NodeTrack* Del = Curr->pNext->pPrev;
				Curr->pNext->pPrev = Curr->pPrev;
				pHead = Curr->pNext;
				delete Del;
				break;

			}
			else
			{
				if (Curr == pTail)
				{
					NodeTrack* Del = Curr->pPrev->pNext;
					Curr->pPrev->pNext = Curr->pNext;
					pTail = Curr->pPrev;
					delete Del;
					break;
				}
				else
				{
					NodeTrack* Del = Curr->pPrev->pNext;
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

TableTracks::TableTracks()
{
	Path = "undefined";
	LastID = 0;
}

void TableTracks::UploadTable(string path)
{
	Track Cell;
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
		LastID = Cell.ID_Track;
		file.close();
	}
	else
	{
		throw "File is not opened";
	}
	cout << "Tracks table uploaded successfully" << endl;
}

void TableTracks::PrintListOfNames()
{
	cout << "The list of names: " << endl;
	TableList.PrintNames();
}

ListTrack TableTracks::GetList()
{
	return TableList;
}

int TableTracks::GenerateID()
{
	LastID += 1;
	return LastID;
}

bool TableTracks::Exists(string Name)
{
	Track Cell = Track();
	string thisName;
	NodeTrack* NodeCell = TableList.GetpHead();
	while (NodeCell)
	{
		Cell = NodeCell->thisCell;
		thisName = Cell.Name_Track;
		if (Name == thisName)
		{
			return true;
		}
		NodeCell = NodeCell->pNext;
	}
	return false;
}

NodeTrack::NodeTrack(Track Cell)
{
	thisCell = Cell;
	pNext = nullptr;
	pPrev = nullptr;
}

Track TableTracks::GetByName(string Name)
{
	Track Cell = Track();
	string thisName;
	NodeTrack* NodeCell = TableList.GetpHead();
	while (NodeCell)
	{
		Cell = NodeCell->thisCell;
		thisName = Cell.Name_Track;
		if (Name == thisName)
		{
			return Cell;
		}
		NodeCell = NodeCell->pNext;
	}
}

Track TableTracks::GetByID(int ID)
{
	Track Cell = Track();
	int thisID;
	NodeTrack* NodeCell = TableList.GetpHead();
	while (NodeCell)
	{
		Cell = NodeCell->thisCell;
		thisID = Cell.ID_Track;
		if (ID == thisID)
		{
			return Cell;
		}
		NodeCell = NodeCell->pNext;
	}
}

void TableTracks::PrintByTrackID(int IDTr)
{
	Track Cell = Track();
	int thisID;
	NodeTrack* NodeCell = TableList.GetpHead();
	while (NodeCell)
	{
		Cell = NodeCell->thisCell;
		thisID = Cell.ID_Track;
		if (thisID == IDTr)
		{
			cout << Cell.Name_Track << endl;
		}
		NodeCell = NodeCell->pNext;
	}
}

void TableTracks::AddToList(Track Tr)
{
	TableList.Add(Tr);
}

void TableTracks::AddToFile(Track Tr)
{
	ofstream file;
	file.open(Path, ios::app);
	if (!file.is_open())
	{
		throw "Tracks table is not open";
	}
	file << '\n';
	file << Tr.AllString();
	file.close();
}

void TableTracks::DeleteTrack(Track Tr)
{
	TableList.DeleteNode(Tr);
}

void TableTracks::UpdateFile()
{
	ofstream file;
	file.open(Path, std::ofstream::out | std::ofstream::trunc);
	NodeTrack* Tr = TableList.GetpHead();
	file << Tr->thisCell.AllString();
	Tr = Tr->pNext;
	while (Tr)
	{
		file << '\n';
		file << Tr->thisCell.AllString();
		Tr = Tr->pNext;
	}
	file.close();
}

