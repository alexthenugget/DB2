#include <iostream>
#include <stdio.h>
#include <fstream>
using namespace std;
#include "Album.h"
#include "Artist.h"
#include "Track.h"
#include <string>
#include "TrackList.h"

Album::Album()
{
	ID = 0;
	Name = "undefined";
	ID_Artist = 0;
	Rating_Album = 0;
	Info_Album = "undefined";
	Genre_Album = "undefined";
	Path_TrackList = "undefined";
	Tracklist = TrackList();
}

void Album::Set(string str)
{
	int pos1, pos2, pos3, pos4, pos5, pos6;
	pos1 = str.find('|');
	int newID = stoi(str.substr(0, pos1));
	pos2 = str.find('|', pos1 + 1);
	string newName = str.substr(pos1 + 1, pos2 - pos1 - 1);
	pos3 = str.find('|', pos2 + 1);
	int ID_Ar = stoi(str.substr(pos2 + 1, pos3 - pos2 - 1));
	pos4 = str.find('|', pos3 + 1);
	double Rating = stod(str.substr(pos3 + 1, pos4 - pos3 - 1));
	pos5 = str.find('|', pos4 + 1);
	string Info = str.substr(pos4 + 1, pos5 - pos4 - 1);
	pos6 = str.find('|', pos5 + 1);
	string Genre = str.substr(pos5 + 1, pos6 - pos5 - 1);
	string Path = str.substr(pos6 + 1, str.length() - pos6 - 1);
	TrackList TrL = TrackList();
	TrL.UploadTrackList(Path);
	ID = newID;
	Name = newName;
	ID_Artist = ID_Ar;
	Rating_Album = Rating;
	Info_Album = Info;
	Genre_Album = Genre;
	Path_TrackList = Path;
	Tracklist = TrL;
}

void Album::PrintInfo()
{
	cout << "Rating of the album: " << Rating_Album << endl;
	cout << "Info of the album: " << Info_Album << endl;
	cout << "Genre of the album: " << Genre_Album << endl;
}

string Album::AllString()
{
	return to_string(ID) + '|' + Name + '|' + to_string(ID_Artist) + '|' + to_string(Rating_Album) + '|' + Info_Album + '|' + Genre_Album + '|' + Path_TrackList;
}

bool Album::operator==(Album Cell)
{
	if (ID == Cell.ID)
		return true;
	return false;
}

void Album::AddToTrackList(int IDTr)
{
	Tracklist.Add(IDTr);
	Tracklist.UpdateFile();
}

void Album::CreateNewAlbum(string str)
{
	int pos1, pos2, pos3, pos4, pos5, pos6;
	pos1 = str.find('|');
	int newID = stoi(str.substr(0, pos1));
	pos2 = str.find('|', pos1 + 1);
	string newName = str.substr(pos1 + 1, pos2 - pos1 - 1);
	pos3 = str.find('|', pos2 + 1);
	int ID_Ar = stoi(str.substr(pos2 + 1, pos3 - pos2 - 1));
	pos4 = str.find('|', pos3 + 1);
	double Rating = stod(str.substr(pos3 + 1, pos4 - pos3 - 1));
	pos5 = str.find('|', pos4 + 1);
	string Info = str.substr(pos4 + 1, pos5 - pos4 - 1);
	pos6 = str.find('|', pos5 + 1);
	string Genre = str.substr(pos5 + 1, pos6 - pos5 - 1);
	string Path = str.substr(pos6 + 1, str.length() - pos6 - 1);
	TrackList TrL = TrackList();
	ListTracks LTr = ListTracks();
	TrL.Set(newID, 0, LTr, Path);
	CreateTrackList(TrL);
	ID = newID;
	Name = newName;
	ID_Artist = ID_Ar;
	Rating_Album = Rating;
	Info_Album = Info;
	Genre_Album = Genre;
	Path_TrackList = Path;
	Tracklist = TrL;
}

void Album::CreateTrackList(TrackList TrL)
{
	ofstream tracklist(TrL.Path);
	tracklist << (to_string(TrL.ID) + '|' + '0');
	tracklist.close();
}

void Album::DeleteTrackList()
{
	const char* Path = Path_TrackList.c_str();
	remove(Path);
}

NodeAlbum::NodeAlbum(Album Cell)
{
	thisCell = Cell;
	pNext = nullptr;
	pPrev = nullptr;
}

inline ListAlbum::ListAlbum()
{
	pHead = nullptr;
	pTail = nullptr;
	Size = 0;
}

void ListAlbum::Add(Album Cell)
{
	NodeAlbum* nTail = new NodeAlbum(Cell);
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

NodeAlbum* ListAlbum::GetpHead()
{
	return pHead;
}

void ListAlbum::PrintNames()
{
	NodeAlbum* NodeName = pHead;
	while (NodeName)
	{
		cout << NodeName->thisCell.Name << endl;
		NodeName = NodeName->pNext;
	}
}

void ListAlbum::DeleteNode(Album Cell)
{
	NodeAlbum* Curr = pHead;
	while (Curr) {
		if (Curr->thisCell == Cell)
		{
			if (Curr == pHead)
			{
				NodeAlbum* Del = Curr->pNext->pPrev;
				Curr->pNext->pPrev = Curr->pPrev;
				pHead = Curr->pNext;
				delete Del;
				break;

			}
			else
			{
				if (Curr == pTail)
				{
					NodeAlbum* Del = Curr->pPrev->pNext;
					Curr->pPrev->pNext = Curr->pNext;
					pTail = Curr->pPrev;
					delete Del;
					break;
				}
				else
				{
					NodeAlbum* Del = Curr->pPrev->pNext;
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

TableAlbums::TableAlbums()
{
	Path = "undefined";
	LastID = 0;
}

void TableAlbums::UploadTable(string path)
{
	Album Cell;
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
		LastID = Cell.ID;
		file.close();
	}
	else
	{
		throw "File is not opened";
	}
	cout << "Albums table uploaded successfully" << endl;
}

void TableAlbums::PrintListOfNames()
{
	cout << "The list of names: " << endl;
	TableList.PrintNames();
}

ListAlbum TableAlbums::GetList()
{
	return TableList;
}

int TableAlbums::GenerateID()
{
	LastID += 1;
	return LastID;
}

string TableAlbums::GeneratePath(string nName)
{
	string Path = "Tracklist_";
	string substr;
	int i = 0;
	for (int i = 0; i < nName.length() + 1; ++i)
	{
		if (nName[i] != ' ' and (i != nName.length()))
		{
			substr += nName[i];
		}
		else
		{
			Path += substr;
			Path += '_';
			substr = "";
		}
	}
	Path = Path.substr(0, Path.length() - 1);
	Path += ".txt";
	return Path;
}

bool TableAlbums::Exists(string Name)
{
	Album Cell = Album();
	string thisName;
	NodeAlbum* NodeCell = TableList.GetpHead();
	while (NodeCell)
	{
		Cell = NodeCell->thisCell;
		thisName = Cell.Name;
		if (Name == thisName)
		{
			return true;
		}
		NodeCell = NodeCell->pNext;
	}
	return false;
}

Album TableAlbums::GetByName(string Name)
{
	Album Cell = Album();
	string thisName;
	NodeAlbum* NodeCell = TableList.GetpHead();
	while (NodeCell)
	{
		Cell = NodeCell->thisCell;
		thisName = Cell.Name;
		if (Name == thisName)
		{
			return Cell;
		}
		NodeCell = NodeCell->pNext;
	}
}

Album TableAlbums::GetByID(int ID)
{
	Album Cell = Album();
	int thisID;
	NodeAlbum* NodeCell = TableList.GetpHead();
	while (NodeCell)
	{
		Cell = NodeCell->thisCell;
		thisID = Cell.ID;
		if (ID == thisID)
		{
			return Cell;
		}
		NodeCell = NodeCell->pNext;
	}
}

void TableAlbums::PrintByArtistID(int ID)
{
	Album Cell = Album();
	int thisID;
	NodeAlbum* NodeCell = TableList.GetpHead();
	while (NodeCell)
	{
		Cell = NodeCell->thisCell;
		thisID = Cell.ID_Artist;
		if (thisID == ID)
		{
			cout << Cell.Name << endl;
		}
		NodeCell = NodeCell->pNext;
	}
}

void TableAlbums::PrintByTrackID(int ID)
{
	Album Cell = Album();
	int thisID;
	NodeAlbum* NodeCell = TableList.GetpHead();
	while (NodeCell)
	{
		Cell = NodeCell->thisCell;
		if (Cell.Tracklist.Exists(ID))
		{
			cout << Cell.Name << endl;
		}
		NodeCell = NodeCell->pNext;
	}
}

void TableAlbums::AddToList(Album Al)
{
	TableList.Add(Al);
}

void TableAlbums::AddToFile(Album Al)
{
	ofstream file;
	file.open(Path, ios::app);
	if (!file.is_open())
	{
		throw "Albums table is not open";
	}
	file << '\n';
	file << Al.AllString();
	file.close();
}

void TableAlbums::UpdateFile()
{
	ofstream file;
	file.open(Path, std::ofstream::out | std::ofstream::trunc);
	NodeAlbum* Al = TableList.GetpHead();
	file << Al->thisCell.AllString();
	Al = Al->pNext;
	while (Al)
	{
		file << '\n';
		file << Al->thisCell.AllString();
		Al = Al->pNext;
	}
	file.close();
}
