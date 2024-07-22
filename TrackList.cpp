#include <iostream>
#include <fstream>
#include <string>
using namespace std;
#include "Album.h"
#include "Artist.h"
#include "Track.h"
#include "TrackList.h"

TrackList::TrackList()
{
	ID = 0;
	Track_Count = 0;
}

int TrackList::ReCount()
{
	IDTrack* IDTr = IDs.GetpHead();
	int i = 0;
	while (IDTr)
	{
		i++;
		IDTr = IDTr->pNext;
	}
	Track_Count = i;
	return Track_Count;
}

void TrackList::Set(int IDd, int Count, ListTracks list, string path)
{
	ID = IDd;
	Track_Count = Count;
	IDs = list;
	Path = path;
}

void TrackList::UploadTrackList(string path)
{
	ifstream file(path);
	if (!file.is_open())
	{
		throw "Tracklist table is not open";
	}
	else
	{
		int pos1;
		string str;
		getline(file, str);
		pos1 = str.find('|');
		int IDAl = stoi(str.substr(0, pos1));
		int Count = stoi(str.substr(pos1 + 1, str.length() - pos1 - 1));
		ListTracks list = ListTracks();
		int i = 0;
		while (i < Count)
		{
			getline(file, str);
			list.Add(stoi(str));
			i++;
		}
		Set(IDAl, Count, list, path);
	}
	Path = path;
	file.close();
}

bool TrackList::Exists(int Name)
{
	IDTrack* NodeCell = IDs.GetpHead();
	while (NodeCell)
	{
		int Cell = NodeCell->ID;
		if (Name == Cell)
		{
			return true;
		}
		NodeCell = NodeCell->pNext;
	}
	return false;
}

bool TrackList::operator==(TrackList Cell)
{
	if (ID == Cell.ID)
		return true;
	return false;
}

void TrackList::Add(int IDTr)
{
	IDs.Add(IDTr);
}

void TrackList::UpdateFile()
{
	ofstream file;
	file.open(Path, std::ofstream::out | std::ofstream::trunc);
	if (!file.is_open())
	{
		throw "Tracklist table is not open";
	}
	file << to_string(ID) + '|' + to_string(ReCount());
	IDTrack* IDTr = IDs.GetpHead();
	while (IDTr)
	{
		cout << IDTr << endl;
		file << '\n';
		file << to_string(IDTr->ID);
		IDTr = IDTr->pNext;
	}
	file.close();
}

void TrackList::DeleteTrack(int ID)
{
	IDTrack IDTr = IDs.GetIDTrackByID(ID);
	IDs.DeleteNode(IDTr);
	cout << "The track deleted from tracklist" << endl;
}

void TrackList::PrintListOfIDs()
{
	IDTrack* NodeCell = IDs.GetpHead();
	while (NodeCell)
	{
		cout << NodeCell->ID << endl;
		NodeCell = NodeCell->pNext;
	}
}

IDTrack::IDTrack(int id)
{
	ID = id;
	pNext = nullptr;
	pPrev = nullptr;
}

ListTracks::ListTracks()
{
	pHead = nullptr;
	pTail = nullptr;
	Size = 0;
}

void ListTracks::Add(int Cell)
{
	IDTrack* newTail = new IDTrack(Cell);
	if (pTail == nullptr)
	{
		pHead = pTail = newTail;
		Size++;
		return;
	}
	pTail->pNext = newTail;
	newTail->pPrev = pTail;
	pTail = newTail;
	Size++;
	return;
}

IDTrack* ListTracks::GetpHead()
{
	return pHead;
}

void ListTracks::DeleteNode(IDTrack Cell)
{
	IDTrack* Curr = pHead;
	while (Curr) {
		if (Curr->ID == Cell.ID)
		{
			if (Curr == pHead)
			{
				IDTrack* Del = Curr->pNext->pPrev;
				Curr->pNext->pPrev = Curr->pPrev;
				pHead = Curr->pNext;
				delete Del;
				break;

			}
			else
			{
				if (Curr == pTail)
				{
					IDTrack* Del = Curr->pPrev->pNext;
					Curr->pPrev->pNext = Curr->pNext;
					pTail = Curr->pPrev;
					delete Del;
					break;
				}
				else
				{
					IDTrack* Del = Curr->pPrev->pNext;
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

IDTrack ListTracks::GetIDTrackByID(int ID)
{
	IDTrack* NodeCell = GetpHead();
	while (NodeCell)
	{
		if (ID == NodeCell->ID)
		{
			return *NodeCell;
		}
		NodeCell = NodeCell->pNext;
	}
}

bool IDTrack::operator==(IDTrack Cell)
{
	if (ID == Cell.ID)
		return true;
	return false;
}