#pragma once
#include <iostream>
using namespace std;
#include "Album.h"
#include "Artist.h"
#include "Track.h"
#include "TrackList.h"

class DataBase
{
public:
	void Run();
	void CreateDataBase();

	void Insert();
	void Search();
	void Delete();

	void InsertArtist();
	void InsertTrack();
	void InsertAlbum();

	void SearchForArtist(string Entry);
	void SearchForTrack(string Entry);
	void SearchForAlbum(string Entry);

	void DeleteArtist();
	void DeleteTrack();
	void DeleteAlbum();

	void PrintTracksByArtistID(int ID);
	void PrintArtistsByTrackID(int ID);
	void PrintTracksByAlbumID(int ID);

	void ControlDeletion(string delStr);
private:
	TableArtists Artists;
	TableAlbums Albums;
	TableTracks Tracks;
};