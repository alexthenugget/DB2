#pragma once
#include <iostream>
using namespace std;
#include "Album.h"
#include "Artist.h"
#include "Track.h"

struct IDTrack
{
	int ID;
	IDTrack* pPrev;
	IDTrack* pNext;

	IDTrack(int id);
	bool operator==(IDTrack Cell);
};

class ListTracks
{
	int Size;
	IDTrack* pHead;
	IDTrack* pTail;
public:
	ListTracks();
	void Add(int Cell);
	IDTrack* GetpHead();
	void DeleteNode(IDTrack Cell);
	IDTrack GetIDTrackByID(int ID);
};

struct TrackList
{
	int ID;
	int Track_Count;
	ListTracks IDs;
	string Path;
	TrackList();
	int ReCount();
	void Set(int IDd, int Count, ListTracks list, string path);
	void UploadTrackList(string path);
	bool Exists(int Name);
	bool operator==(TrackList Cell);
	void Add(int ID);
	void UpdateFile();
	void DeleteTrack(int ID);
	void PrintListOfIDs();
};