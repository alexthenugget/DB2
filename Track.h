#pragma once
#include <iostream>
using namespace std;
#include "Album.h"
#include "Artist.h"
#include "TrackList.h"

struct Track
{
	int ID_Track;
	string Name_Track;
	int Time_Track;

	Track();
	void Set(string str);
	void PrintInfo();
	string AllString();
	bool operator==(Track Cell);
};

struct NodeTrack
{
	NodeTrack(Track Cell);
	Track thisCell;
	NodeTrack* pPrev;
	NodeTrack* pNext;
};

class ListTrack
{
	int Size;
	NodeTrack* pHead;
	NodeTrack* pTail;
public:
	ListTrack();
	void Add(Track Cell);
	NodeTrack* GetpHead();
	void PrintNames();
	void DeleteNode(Track Cell);
};

class TableTracks
{
public:
	TableTracks();
	void UploadTable(string path);
	void PrintListOfNames();
	ListTrack GetList();
	int GenerateID();
	bool Exists(string Name);
	Track GetByName(string Name);
	Track GetByID(int ID);

	void PrintByTrackID(int IDTr);
	void AddToList(Track Tr);
	void AddToFile(Track Tr);
	void DeleteTrack(Track Tr);
	void UpdateFile();
private:
	ListTrack TableList;
	string Path;
	int LastID;
};