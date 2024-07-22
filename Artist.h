#pragma once
#include <iostream>
using namespace std;
#include "Album.h"
#include "Track.h"
#include "TrackList.h"

struct Artist
{
	int ID_Artist;
	string Name_Artist;
	int Year_Artist;
	string Country_Artist;
	string Producer_Artist;

	Artist();
	void Set(string str);
	void PrintInfo();
	string AllString();
	bool operator==(Artist Cell);
};

struct NodeArtist
{
	NodeArtist(Artist Cell);
	Artist thisCell;
	NodeArtist* pPrev;
	NodeArtist* pNext;
};

class ListArtist
{
	int Size;
	NodeArtist* pHead;
	NodeArtist* pTail;
public:
	ListArtist();
	void Add(Artist Cell);
	NodeArtist* GetpHead();
	void PrintNames();
	void DeleteNode(Artist Cell);
};

class TableArtists
{
public:
	TableArtists();
	void UploadTable(string path);
	void PrintListOfNames();
	ListArtist GetList();
	int GenerateID();
	bool Exists(string Name);
	Artist GetByName(string Name);

	void PrintByAlbumID(int ID);
	void AddToList(Artist Ar);
	void AddToFile(Artist Ar);
	void UpdateFile();
private:
	ListArtist TableList;
	string Path;
	int LastID;
};