#include <iostream>
#include <string>
#include <fstream>
using namespace std;
#include "DataBase.h"

void DataBase::Run()
{
	char Command;
	cout << "THE COMMANDS YOU CAN USE" << endl;
	cout << "1.Search(S) \n" << "2.Insert(I) \n" << "3.Delete(D) \n";
	cout << "To complete working with database enter Complete(C) \n";
	cout << endl;
	while (true)
	{
		cin >> Command;
		if (Command == 'I')
		{
			Insert();
		}
		else
		{
			if (Command == 'S')
			{
				Search();
			}
			else
			{
				if (Command == 'D')
				{
					Delete();
				}
				else
				{
					if (Command == 'C')
					{
						break;
					}
					else
					{
						cout << "!There is no such command!" << endl;
						cout << endl;
					}
				}
			}
		}
	}
}

void DataBase::CreateDataBase()
{
	TableArtists Ar;
	TableAlbums Al;
	TableTracks Tr;
	Ar.UploadTable("Artists.txt");
	Tr.UploadTable("Tracks.txt");
	Al.UploadTable("Albums.txt");
	Artists = Ar;
	Albums = Al;
	Tracks = Tr;
	Run();
}

void DataBase::Insert()
{
	string Entry;
	cout << "--INSERT--" << endl;
	cout << "THE OPTIONS YOU CAN USE" << endl;
	cout << "Artist(Ar) \n" << "Album(Al) \n" << "Track(Tr) \n";
	cout << "To return to menu enter End(E) \n";
	cout << endl;
	while (true)
	{
		cin >> Entry;
		if (Entry == "Ar")
		{
			InsertArtist();
		}
		else
		{
			if (Entry == "Al")
			{
				InsertAlbum();
			}
			else
			{
				if (Entry == "Tr")
				{
					InsertTrack();
				}
				else
				{
					if (Entry == "E")
					{
						break;
					}
					else
					{
						cout << "!There is no such command!" << endl;
						cout << endl;
					}
				}
			}
		}
	}
}

void DataBase::Search()
{
	string Entry;
	cout << "--SEARCH--" << endl;
	cout << "THE OPTIONS YOU CAN USE" << endl;
	cout << "1.Artist(Ar) \n" << "2.Album(Al) \n" << "3.Track(Tr) \n";
	cout << "To return to menu enter End(E) \n";
	cout << endl;
	while (true)
	{
		cin >> Entry;
		if (Entry == "Ar")
		{
			string Entry;
			cout << "WHAT TO FIND?" << endl;
			cout << "Info(In) \n" << "Tracks(Tr) \n" << "Albums(Al) \n";
			cin >> Entry;
			SearchForArtist(Entry);
		}
		else
		{
			if (Entry == "Al")
			{
				string Entry;
				cout << "WHAT TO FIND?" << endl;
				cout << "Info(In) \n" << "Tracks(Tr) \n" << "Artists(Ar) \n";
				cin >> Entry;
				SearchForAlbum(Entry);
			}
			else
			{
				if (Entry == "Tr")
				{
					string Entry;
					cout << "WHAT TO FIND?" << endl;
					cout << "Info(In) \n" << "Artist/s(Ar) \n" << "Album/s(Al) \n";
					cin >> Entry;
					SearchForTrack(Entry);
				}
				else
				{
					if (Entry == "E")
					{
						break;
					}
					else
					{
						cout << "!There is no such command!" << endl;
						cout << endl;
					}
				}
			}
		}
	}
}

void DataBase::Delete()
{
	string Entry;
	cout << "--DELETE--" << endl;
	cout << "THE OPTIONS YOU CAN USE" << endl;
	cout << "1.Artist(Ar) \n" << "2.Album(Al) \n" << "3.Track(Tr) \n";
	cout << "To return to menu enter End(E) \n";
	cout << endl;
	while (true)
	{
		cin >> Entry;
		if (Entry == "Ar")
		{
			DeleteArtist();
		}
		else
		{
			if (Entry == "Al")
			{
				DeleteAlbum();
			}
			else
			{
				if (Entry == "Tr")
				{
					DeleteTrack();
				}
				else
				{
					if (Entry == "E")
					{
						break;
					}
					else
					{
						cout << "!There is no such command!" << endl;
						cout << endl;
					}
				}
			}
		}
	}
}



void DataBase::InsertArtist()
{
	string str;
	cout << "Enter the data in this form: " << endl;
	cout << "Artist's name|Artist's year|Artist's country|Artist's producer" << endl;
	cin.ignore();
	getline(cin, str);

	Artist newArtist = Artist();
	newArtist.Set(to_string(Artists.GenerateID()) + '|' + str);
	if (Artists.Exists(newArtist.Name_Artist))
	{
		cout << "The artist is already exist" << endl;
		return;
	}
	Artists.AddToList(newArtist);
	Artists.AddToFile(newArtist);
	cout << endl;
	cout << "Artist added successfully" << endl;
	cout << endl;
}

void DataBase::InsertTrack()
{
	string str;
	cout << "Enter the data in this form: " << endl;
	cout << "Track's name|Track's time" << endl;
	cin.ignore();
	getline(cin, str);
	Track newTrack = Track();
	newTrack.Set(to_string(Tracks.GenerateID()) + '|' + str);
	if (Tracks.Exists(newTrack.Name_Track))
	{
		cout << "The track is already exist" << endl;
		return;
	}
	Tracks.AddToList(newTrack);
	Tracks.AddToFile(newTrack);
	cout << "--Choose an album--" << endl;
	string NameOfAlbum;
	Albums.PrintListOfNames();
	cout << "--Print name of the album--" << endl;
	getline(cin, str);
	NameOfAlbum = str;
	Album Al;
	if (Albums.Exists(NameOfAlbum))
	{
		Al = Albums.GetByName(NameOfAlbum);
		Al.AddToTrackList(newTrack.ID_Track);
	}
	else
	{
		cout << "!There is no such album!" << endl;
		return;
	}
	cout << endl;
	cout << "Track added successfully" << endl;
	cout << endl;
}

void DataBase::InsertAlbum()
{
	string str;
	cout << "Enter the data in this form: " << endl;
	cout << "Album's name|Album's artist|Album's rating|Album's info|Album's genre" << endl;
	cin.ignore();
	getline(cin, str);
	int pos1, pos2;
	pos1 = str.find('|');
	pos2 = str.find('|', pos1 + 1);
	string NameAr = str.substr(pos1 + 1, pos2 - pos1 - 1);
	if (!Artists.Exists(NameAr))
	{
		cout << "!There is no such artist!" << endl;
		return;
	}
	Artist Ar = Artists.GetByName(NameAr);
	Album newAlbum = Album();
	newAlbum.CreateNewAlbum(to_string(Albums.GenerateID()) + '|' + str.replace(pos1 + 1, pos2 - pos1 - 1, to_string(Ar.ID_Artist)) + '|' + Albums.GeneratePath(str.substr(0, pos1)));
	if (Albums.Exists(newAlbum.Name))
	{
		cout << "The album is already exist" << endl;
		return;
	}
	Albums.AddToList(newAlbum);
	Albums.AddToFile(newAlbum);

	cout << endl;
	cout << "Album added successfully" << endl;
	cout << endl;
}



void DataBase::SearchForArtist(string Entry)
{
	string NameAr;
	string str;
	cout << "THE LIST OF EXISTING ARTISTS" << endl;
	Artists.PrintListOfNames();
	cout << "--Enter artist's name--" << endl;
	cin.ignore();
	getline(cin, str);
	NameAr = str;
	if (!Artists.Exists(NameAr))
	{
		cout << "!There is no such artist!" << endl;
		return;
	}
	Artist Ar = Artists.GetByName(NameAr);
	if (Entry == "In")
	{
		cout << "Artist's info: " << endl;
		Ar.PrintInfo();
	}
	else
	{
		if (Entry == "Al")
		{
			cout << "Artist's albums: " << endl;
			Albums.PrintByArtistID(Ar.ID_Artist);
		}
		else
		{
			if (Entry == "Tr")
			{
				cout << "Artist's tracks: " << endl;
				PrintTracksByArtistID(Ar.ID_Artist);
			}
		}
	}

}

void DataBase::SearchForTrack(string Entry)
{
	string NameTr;
	string str;
	cout << "THE LIST OF EXISTING TRACKS" << endl;
	Tracks.PrintListOfNames();
	cout << "--Enter track's name--" << endl;
	cin.ignore();
	getline(cin, str);
	NameTr = str;
	if (!Tracks.Exists(NameTr))
	{
		cout << "!There is no such track!" << endl;
		return;
	}
	Track Tr = Tracks.GetByName(NameTr);
	if (Entry == "In")
	{
		cout << "Track's info: " << endl;
		Tr.PrintInfo();
	}
	else
	{
		if (Entry == "Al")
		{
			cout << "Track's albums: " << endl;
			Albums.PrintByTrackID(Tr.ID_Track);
		}
		else
		{
			if (Entry == "Ar")
			{
				cout << "Track's artists: " << endl;
				PrintArtistsByTrackID(Tr.ID_Track);
			}
		}
	}

}

void DataBase::SearchForAlbum(string Entry)
{
	string NameAl;
	string str;
	cout << "THE LIST OF EXISTING ALBUMS" << endl;
	Albums.PrintListOfNames();
	cout << "--Enter album's name--" << endl;
	cin.ignore();
	getline(cin, str);
	NameAl = str;
	if (!Albums.Exists(NameAl))
	{
		cout << "!There is no such album!" << endl;
		return;
	}
	Album Al = Albums.GetByName(NameAl);
	if (Entry == "In")
	{
		cout << "Album's info: " << endl;
		Al.PrintInfo();
	}
	else
	{
		if (Entry == "Ar")
		{
			cout << "Album's artists: " << endl;
			Artists.PrintByAlbumID(Al.ID_Artist);
		}
		else
		{
			if (Entry == "Tr")
			{
				cout << "Album's tracks: " << endl;
				PrintTracksByAlbumID(Al.ID);
			}
		}
	}

}



void DataBase::DeleteArtist()
{
	string del = "3";
	string NameAr;
	string str;
	cout << "THE LIST OF EXISTING ARTISTS" << endl;
	Artists.PrintListOfNames();
	cout << "--Enter artist's name--" << endl;
	cin.ignore();
	getline(cin, str);
	NameAr = str;
	if (!Artists.Exists(NameAr))
	{
		cout << "!There is no such artist!" << endl;
		return;
	}
	int CountAr = 0;
	Artist Ar = Artists.GetByName(NameAr);
	NodeAlbum* NodeAl2 = Albums.GetList().GetpHead();
	while (NodeAl2)
	{
		if (NodeAl2->thisCell.ID_Artist == Ar.ID_Artist) 
		{
			Album Al = NodeAl2->thisCell;
			IDTrack* NodeTrID = Al.Tracklist.IDs.GetpHead();
			NodeAlbum* NodeAl = Albums.GetList().GetpHead();
			while (NodeTrID)
			{
				while (NodeAl)
				{
					if (NodeAl->thisCell.Tracklist.Exists(NodeTrID->ID))
					{
						del += '|' + NodeAl->thisCell.AllString();
						CountAr++;
					}
					NodeAl = NodeAl->pNext;
				}
				if (CountAr == 1)
				{
					Track Tr = Tracks.GetByID(NodeTrID->ID);
					del += '|' + Tr.AllString();
					Tracks.GetList().DeleteNode(Tr);
					Tracks.UpdateFile();
				}
				CountAr = 0;
				NodeTrID = NodeTrID->pNext;
			}
			Al.DeleteTrackList();
			Albums.GetList().DeleteNode(Al);
			Albums.UpdateFile();
		}
		NodeAl2 = NodeAl2->pNext;
	}
	Artists.GetList().DeleteNode(Ar);
	Artists.UpdateFile();
	ControlDeletion(del);
	cout << endl;
	cout << "Artist deleted successfully" << endl;
	cout << endl;
}

void DataBase::DeleteTrack()
{
	string NameTr;
	string str;
	string del = "1";
	cout << "THE LIST OF EXISTING TRACKS" << endl;
	Tracks.PrintListOfNames();
	cout << "--Enter track's name--" << endl;
	cin.ignore();
	getline(cin, str);
	NameTr = str;
	int CountAr = 0;
	if (!Tracks.Exists(NameTr))
	{
		cout << "!There is no such track!" << endl;
		return;
	}
	Track Tr = Tracks.GetByName(NameTr);
	NodeAlbum* NodeCell = Albums.GetList().GetpHead();
	TrackList TrL;
	while (NodeCell)
	{
		TrL = NodeCell->thisCell.Tracklist;
		if (TrL.Exists(Tr.ID_Track))
		{
			CountAr += 1;
			TrL.DeleteTrack(Tr.ID_Track);
			del += '|' + TrL.Path;
			TrL.UpdateFile();
		}
		NodeCell = NodeCell->pNext;
	}
	del += '|' + Tr.AllString();
	Tracks.DeleteTrack(Tr);
	Tracks.UpdateFile();
	ControlDeletion(del);
	cout << endl;
	cout << "Track deleted successfully" << endl;
	cout << endl;
}

void DataBase::DeleteAlbum()
{
	string del = "2";
	string NameAl;
	string str;
	cout << "THE LIST OF EXISTING ALBUMS" << endl;
	Albums.PrintListOfNames();
	cout << "--Enter album's name--" << endl;
	cin.ignore();
	getline(cin, str);
	NameAl = str;
	int CountAr = 0;
	if (!Albums.Exists(NameAl))
	{
		cout << "!There is no such album!" << endl;
		return;
	}
	Album Al = Albums.GetByName(NameAl);
	IDTrack* NodeTrID = Al.Tracklist.IDs.GetpHead();
	NodeAlbum* NodeAl = Albums.GetList().GetpHead();
	while(NodeTrID)
	{
		while (NodeAl)
		{
			if (NodeAl->thisCell.Tracklist.Exists(NodeTrID->ID))
			{
				del += '|' + NodeAl->thisCell.AllString();
				CountAr++;
			}
			NodeAl = NodeAl->pNext;
		}
		if (CountAr == 1)
		{
			Track Tr = Tracks.GetByID(NodeTrID->ID);
			del += '|' + Tr.AllString();
			Tracks.GetList().DeleteNode(Tr);
			Tracks.UpdateFile();
		}
		CountAr = 0;
		NodeTrID = NodeTrID->pNext;
	}
	Al.DeleteTrackList();
	Albums.GetList().DeleteNode(Al);
	Albums.UpdateFile();
	ControlDeletion(del);
	cout << endl;
	cout << "Album deleted successfully" << endl;
	cout << endl;
}



void DataBase::PrintTracksByArtistID(int ID)
{
	Album Cell = Album();
	int thisID;
	NodeAlbum* NodeCell = Albums.GetList().GetpHead();
	while (NodeCell)
	{
		Cell = NodeCell->thisCell;
		thisID = Cell.ID_Artist;
		if (thisID == ID)
		{
			TrackList TrL = Cell.Tracklist;
			ListTracks LTr = TrL.IDs;
			int IID;
			IDTrack* IDTr = LTr.GetpHead();
			while (IDTr)
			{
				IID = IDTr->ID;
				Tracks.PrintByTrackID(IID);
				IDTr = IDTr->pNext;
			}
		}
		NodeCell = NodeCell->pNext;
	}
}

void DataBase::PrintArtistsByTrackID(int ID)
{
	Album Cell = Album();
	int thisID;
	NodeAlbum* NodeCell = Albums.GetList().GetpHead();
	while (NodeCell)
	{
		Cell = NodeCell->thisCell;
		if (Cell.Tracklist.Exists(ID))
		{
			thisID = Cell.ID_Artist;
			NodeArtist* NodeAr = Artists.GetList().GetpHead();
			while (NodeAr)
			{
				if (thisID == NodeAr->thisCell.ID_Artist)
				{
					cout << NodeAr->thisCell.Name_Artist << endl;
				}
				NodeAr = NodeAr->pNext;
			}
		}
		NodeCell = NodeCell->pNext;
	}
}

void DataBase::PrintTracksByAlbumID(int ID)
{
	Album Cell = Album();
	Cell = Albums.GetByID(ID);
	int thisID;
	TrackList TrL = Cell.Tracklist;
	ListTracks LTr = TrL.IDs;
	int IID;
	IDTrack* IDTr = LTr.GetpHead();
	NodeTrack* NodeCell = Tracks.GetList().GetpHead();
	while (IDTr)
	{
		while (NodeCell)
		{
			IID = IDTr->ID;
			if (IID == NodeCell->thisCell.ID_Track)
			{
				cout << NodeCell->thisCell.Name_Track << endl;
			}
			NodeCell = NodeCell->pNext;
		}
		IDTr = IDTr->pNext;
	}

}


void DataBase::ControlDeletion(string delStr)
{
	ofstream file;
	file.open("Deleted_Cells.txt", ios::app);
	file << '\n' + delStr;
	file.close();
}

