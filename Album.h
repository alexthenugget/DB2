#pragma once
#include <iostream>
using namespace std;
#include "Artist.h"
#include "Track.h"
#include "TrackList.h"

struct Album
{
	int ID;
	string Name;
	int ID_Artist;
	double Rating_Album;
	string Info_Album;
	string Genre_Album;
	string Path_TrackList;
	TrackList Tracklist;

	Album();
	void Set(string str);
	void PrintInfo();
	string AllString();
	bool operator==(Album Cell);
	void AddToTrackList(int IDTr);
	void CreateNewAlbum(string str);
	void CreateTrackList(TrackList TrL);
	void DeleteTrackList();
};

struct NodeAlbum
{
	NodeAlbum(Album Cell);
	Album thisCell;
	NodeAlbum* pPrev;
	NodeAlbum* pNext;
};

class ListAlbum
{
	int Size;
	NodeAlbum* pHead;
	NodeAlbum* pTail;
public:
	ListAlbum();
	void Add(Album Cell);
	NodeAlbum* GetpHead();
	void PrintNames();
	void DeleteNode(Album Cell);
};

class TableAlbums
{
public:
	TableAlbums();
	void UploadTable(string path);
	void PrintListOfNames();
	ListAlbum GetList();
	int GenerateID();
	string GeneratePath(string nName);
	bool Exists(string Name);
	Album GetByName(string Name);
	Album GetByID(int ID);

	void PrintByArtistID(int ID);
	void PrintByTrackID(int ID);
	void AddToList(Album Al);
	void AddToFile(Album Al);
	void UpdateFile();

private:
	ListAlbum TableList;
	string Path;
	int LastID;
};