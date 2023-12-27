/*
		Programmer: Cole Clark
		Date: 2-5-2021

			Description: solutions for PA2 music orgnization

		Modified date: 2-17-2020

			Description: Updated to include solutions for PA3
*/

#include "music.h"


//Displays the Options and records the user's choice
int getChoice(void)
{
	int choice = 0;
	system("cls");

	do
	{
		printf("MENU\n\n");
		printf("(1)     Load\n(2)     Store\n(3)     Display\n(4)     Insert\n(5)     Delete\n(6)     Edit\n(7)     Sort\n(8)     Rate\n(9)     Play\n(10)    Shuffle\n(11)    Exit\n\n");

		printf("Enter the number corresponding to your choice:  ");
		scanf("%d", &choice);

		system("cls");
	} while (choice > 11 || choice <= 0);

	return choice;
}


//Creates a link for the link list
Node* makeNode(Record newData)
{
	Node* newN = NULL;
	newN = (Node*)malloc(sizeof(Node));

	if (newN != NULL)
	{
		newN->data = newData;
		newN->pNext = NULL;
		newN->pPrev = NULL;

		return newN;
	}

	return NULL;
}


//Puts a node into the list after creating one using the makeNode() function
int insert(Node **pList, Record newData)
{
	Node* newN = makeNode(newData);
	Node* current = NULL;

	if (newN->data.length.minutes < 0)
	{
		newN->data.length.minutes = 0;
	}

	if (newN->data.length.seconds > 59)
	{
		newN->data.length.seconds = 59;
	}
	if (newN->data.length.seconds < 0)
	{
		newN->data.length.seconds = 0;
	}

	if (newN->data.timesPlayed < 0)
	{
		newN->data.timesPlayed = 0;
	}

	if (newN->data.rating < 1)
	{
		newN->data.rating = 1;
	}
	if (newN->data.rating > 5)
	{
		newN->data.rating = 5;
	}

	if (*pList == NULL)
	{
		*pList = newN;
		newN->pNext = newN;
		newN->pPrev = newN;

		return 0;
	}
	else
	{
		newN->pNext = *pList;
		(*pList)->pPrev = newN;

		if ((*pList)->pNext == NULL)
		{
			(*pList)->pNext = newN;
			newN->pPrev = *pList;
		}
		else
		{

			current = *pList;

			while (current->pNext != *pList)
			{
				current = current->pNext;
			}

			current->pNext = newN;
			newN->pPrev = current;
		}

		return 1;

	}
}


//Reads the records from infile and puts them into a linked list with the putNode() function
int load(FILE* infile, Node** pList)
{
	static int count = 0;
	char delim[2] = ",";
	char colonDelim[2] = ":";
	char quoteDelim[2] = "\"";
	char c[200] = { '\0' };
	char *name;
	char *album;
	char *song;
	char *genre;
	char *minute;
	char *second;
	char *timesPlayed;
	char *rating;

	Record temp;

	int check = fgets(c, 200, infile);

	if (check == NULL)
	{
		return count;
	}
	else
	{
		if (c[0] == '"')
		{
			name = strtok(c, quoteDelim);
			strcpy(temp.artist, name);
		}
		else
		{
			name = strtok(c, delim);
			strcpy(temp.artist, name);
		}

		album = strtok(NULL, delim);
		song = strtok(NULL, delim);
		genre = strtok(NULL, delim);
		minute = strtok(NULL, colonDelim);
		second = strtok(NULL, delim);
		timesPlayed = strtok(NULL, delim);
		rating = strtok(NULL, delim);

		strcpy(temp.albumTitle, album);
		strcpy(temp.songTitle, song);
		strcpy(temp.genre, genre);
		temp.length.minutes = atoi(minute);
		temp.length.seconds = atoi(second);
		temp.timesPlayed = atoi(timesPlayed);
		temp.rating = atoi(rating);

		++count;
	}

	insert(&(*pList), temp);

	load(infile, &(*pList));
}


//Prints all of the songs in the list with all the information
void showSongs(const Node** pList)
{
	Node *current = pList;

	do
	{
		printf("Artist: %s\n", current->data.artist);
		printf("Album: %s\n", current->data.albumTitle);
		printf("Song: %s\n", current->data.songTitle);
		printf("Genre: %s\n", current->data.genre);
		printf("Duration: %d:%d\n", current->data.length.minutes, current->data.length.seconds);
		printf("Times Played: %d\n", current->data.timesPlayed);
		printf("Rating: %d\n\n", current->data.rating);

		current = current->pNext;

	} while (current != pList);
}


//Writes the song information in outfile
int storeSongs(FILE* outfile, const Node** pList)
{
	Node* current = pList;
	int count = 0;

	do
	{
		fprintf(outfile, "%s,%s,%s,%s,%d:%d,%d,%d\n", current->data.artist, current->data.albumTitle, current->data.songTitle, current->data.genre, current->data.length.minutes, current->data.length.seconds, current->data.timesPlayed, current->data.rating);

		++count;
		current = current->pNext;

	} while (current != pList);

	return count;
}


//Gives the user an option between seeing all of the songs or just songs from one artist then completes the selected option with showSongs() or ShowArtists()
void display(Node** pList)
{
	int response = 0;

	do
	{
		system("cls");
		printf("(1)     Print All\n(2)     Choose Artist\n\n");
		printf("Enter the number corresponding to your choice:  ");
		scanf("%d", &response);

	} while (response != 1 && response != 2);

	system("cls");

	if (response == 1)
	{
		showSongs(pList);
		system("pause");
	}
	else
	{
		showArtists(pList);
	}
}


//Shows the artists and gives the user an option to choose one. After the user selects an artists, the songs from that artist will print
void showArtists(Node** pList)
{
	Node* current = pList;
	int count = 0;
	char names[50][100] = { '\0' };
	int check = 0;
	int same = 0;
	int choice = 0;

	do
	{
		++count;
		strcpy(names[count], current->data.artist);
		current = current->pNext;

	}while (current != pList);

	current = pList;

	for (int i = 1; i != count; ++i)
	{
		for (int j = i + 1; j != count; ++j)
		{
			same = strcmp(names[i], names[j]);

			if (same == 0)
			{
				for (int h = j; h != count; ++h)
				{
					strcpy(names[h], names[h + 1]);
				}

			}

		}
	}

	/*for (int j = 0; j != count - 1; ++j)
	{
		for (int h = j + 1; h != count; ++h)
		{
			same = strcmp(names[j], names[h]);

			if (same == 0)
			{
				strcpy(names[h], names[h + 1]);
			}
		}

	}*/
	do
	{
		do
		{
			system("cls");
			for (int i = 1; i != count - 1; ++i)
			{
				printf("(%d)     %s\n", i, names[i]);
			}

			printf("\n\n");

			printf("Enter the number corresponding to your choice or %d to return to the menu:  ", count - 1);
			scanf("%d", &choice);

		} while (choice > count - 1 || choice < 1);

		if (choice != count - 1)
		{
			system("cls");
			Node* newCurrent = pList;

			do
			{
				check = strcmp(names[choice], newCurrent->data.artist);

				if (check == 0)
				{
					printf("Artist: %s\n", newCurrent->data.artist);
					printf("Album: %s\n", newCurrent->data.albumTitle);
					printf("Song: %s\n", newCurrent->data.songTitle);
					printf("Genre: %s\n", newCurrent->data.genre);
					printf("Duration: %d:%d\n", newCurrent->data.length.minutes, current->data.length.seconds);
					printf("Times Played: %d\n", newCurrent->data.timesPlayed);
					printf("Rating: %d\n\n", newCurrent->data.rating);
					printf("\n\n");
				}

				newCurrent = newCurrent->pNext;

			} while (newCurrent != pList);

			system("pause");
		}
	} while (choice != count - 1);
}


//Prints out all of the songs and artists, then allows the user to choose one to edit, play, or rate and returns the answer
int showCondensed(Node** pList)
{

	int result = 0;
	int num = 0;

	do
	{
		Node* current = pList;
		num = 0;

		system("cls");

		do
		{
			++num;
			printf("(%d)\t%s\n\t%s\n\n", num, current->data.artist, current->data.songTitle);

			current = current->pNext;

		} while (current != pList);

		printf("Enter the number of the song you would like to rate or edit:  ");
		scanf("%d", &result);

	} while (result > num || result < 1);

	return result;
}


//Allows the user to rate the song selected in showCondensed() function
void rateSong(Node** pList, int song)
{
	Node* current = pList;
	int newR = 0;

	for (int i = 0; i != song - 1; ++i)
	{
		current = current->pNext;
	}

	do
	{
		system("cls");
		printf("Artist:\t%s\nSong:\t%s\nRating:\t%d\n\n", current->data.artist, current->data.songTitle, current->data.rating);

		printf("Please enter a new rating for this song between 1 and 5:   ");
		scanf("%d", &newR);

	} while (newR > 5 || newR < 1);

	current->data.rating = newR;

	system("cls");
	printf("Artist:\t%s\nSong:\t%s\nRating:\t%d\n\n", current->data.artist, current->data.songTitle, current->data.rating);
}


//Allows the user to edit any value for the song selected in showCondensed() function
void editSong(Node** pList, int song)
{
	Node* current = pList;
	int choice = 0;
	char newValue[100] = { '\0' };
	char dummy[5] = { '\0' };
	int l = 0;
	int newMinutes = 0;
	int newSeconds = 0;
	int newTimesPlayed = 0;
	int newR = 0;

	for (int i = 0; i != song - 1; ++i)
	{
		current = current->pNext;
	}

	do
	{
		system("cls");
		printf("(1)  Artist: %s\n", current->data.artist);
		printf("(2)  Album: %s\n", current->data.albumTitle);
		printf("(3)  Song: %s\n", current->data.songTitle);
		printf("(4)  Genre: %s\n", current->data.genre);
		printf("(5)  Duration: %d:%d\n", current->data.length.minutes, current->data.length.seconds);
		printf("(6)  Times Played: %d\n", current->data.timesPlayed);
		printf("(7)  Rating: %d\n\n", current->data.rating);

		printf("Enter the number for the value to be edited:  ");
		scanf("%d", &choice);

	} while (choice < 1 || choice > 7);
	system("cls");

	if (choice == 1) //Artist edit
	{
		printf("Artist: %s\n\n", current->data.artist);
		printf("Enter the edited artist name:   ");
		fgets(dummy, sizeof(dummy), stdin);
		fgets(newValue, sizeof(newValue), stdin);
		l = strlen(newValue);
		newValue[l - 1] = '\0';
		strcpy(current->data.artist, newValue);
	}
	else if (choice == 2) //Album edit
	{
		printf("Album: %s\n\n", current->data.albumTitle);
		printf("Enter the edited album title:   ");
		fgets(dummy, sizeof(dummy), stdin);
		fgets(newValue, sizeof(newValue), stdin);
		l = strlen(newValue);
		newValue[l - 1] = '\0';
		strcpy(current->data.albumTitle, newValue);
	}
	else if (choice == 3) //Song edit
	{
		printf("Song: %s\n\n", current->data.songTitle);
		printf("Enter the edited song name:   ");
		fgets(dummy, sizeof(dummy), stdin);
		fgets(newValue, sizeof(newValue), stdin);
		l = strlen(newValue);
		newValue[l - 1] = '\0';
		strcpy(current->data.songTitle, newValue);
	}
	else if (choice == 4) //Genre edit
	{
		printf("Genre: %s\n\n", current->data.genre);
		printf("Enter the edited Genre:   ");
		fgets(dummy, sizeof(dummy), stdin);
		fgets(newValue, sizeof(newValue), stdin);
		l = strlen(newValue);
		newValue[l - 1] = '\0';
		strcpy(current->data.genre, newValue);
	}
	else if (choice == 5) //Duration edit
	{
		do
		{
			system("cls");
			printf("Duration %d:%d\n\n", current->data.length.minutes, current->data.length.seconds);
			printf("Enter new minute value:   ");
			scanf("%d", &newMinutes);
			printf("Enter new second Value:   ");
			scanf("%d", &newSeconds);
		} while (newMinutes < 0 || newSeconds < 0 || newSeconds > 59);
		current->data.length.minutes = newMinutes;
		current->data.length.seconds = newSeconds;
	}
	else if (choice == 6) //Times Played edit
	{
		do
		{
			system("cls");
			printf("Times Played: %d\n\n", current->data.timesPlayed);
			printf("Enter new times played:   ");
			scanf("%d", &newTimesPlayed);
		} while (newTimesPlayed < 0);

		current->data.timesPlayed = newTimesPlayed;
	}
	else if (choice == 7) //Rating edit
	{
		do
		{
			system("cls");
			printf("Rating: %d\n\n", current->data.rating);
			printf("Enter new rating between 1 and 5:   ");
			scanf("%d", &newR);
		} while (newR < 1 || newR > 5);

		current->data.rating = newR;
	}

	system("cls");
	printf("Artist: %s\n", current->data.artist);
	printf("Album: %s\n", current->data.albumTitle);
	printf("Song: %s\n", current->data.songTitle);
	printf("Genre: %s\n", current->data.genre);
	printf("Duration: %d:%d\n", current->data.length.minutes, current->data.length.seconds);
	printf("Times Played: %d\n", current->data.timesPlayed);
	printf("Rating: %d\n\n", current->data.rating);

}


//Delays the program for number of seconds that was entered
void delay(int seconds)
{

	int currentTime = time(NULL);

	currentTime += seconds;

	while (time(NULL) != currentTime);

}


//Prints each song's information for 10 seconds then shows the next song until all songs have been printted
void playMusic(Node** pList, int song)
{
	Node* current = pList;
	Node* start;
	int check = 0;

	for (int i = 0; i != song - 1; ++i)
	{
		current = current->pNext;
	}

	start = current;
	do
	{
		system("cls");

		++current->data.timesPlayed;

		printf("Artist: %s\n", current->data.artist);
		printf("Album: %s\n", current->data.albumTitle);
		printf("Song: %s\n", current->data.songTitle);
		printf("Genre: %s\n", current->data.genre);
		printf("Duration: %d:%d\n", current->data.length.minutes, current->data.length.seconds);
		printf("Times Played: %d\n", current->data.timesPlayed);
		printf("Rating: %d\n\n", current->data.rating);

		delay(10);

		current = current->pNext;

	} while (current != start);

}


//allows the user to input information for a new song
Record getRecord(void)
{
	Record temp;
	char dummy[5] = { '\0' };
	Node* newN = NULL;
	char delim[2] = "\n";

	//get artist name
	printf("Enter the artist name:   ");
	fgets(dummy, sizeof(dummy), stdin);
	fgets(temp.artist, sizeof(temp.artist), stdin);
	strtok(temp.artist, delim);
	system("cls");

	//get album title
	printf("Artist: %s\n\n", temp.artist);
	printf("Enter the album title:   ");
	fgets(temp.albumTitle, sizeof(temp.albumTitle), stdin);
	strtok(temp.albumTitle, delim);
	system("cls");

	//get song title
	printf("Artist: %s\n", temp.artist);
	printf("Album: %s\n\n", temp.albumTitle);
	printf("Enter the song name:   ");
	fgets(temp.songTitle, sizeof(temp.songTitle), stdin);
	strtok(temp.songTitle, delim);
	system("cls");

	//get genre
	printf("Artist: %s\n", temp.artist);
	printf("Album: %s\n", temp.albumTitle);
	printf("Song: %s\n\n", temp.songTitle);
	printf("Enter the genre:   ");
	fgets(temp.genre, sizeof(temp.genre), stdin);
	strtok(temp.genre, delim);

	//get duration
	do
	{
		system("cls");
		printf("Artist: %s\n", temp.artist);
		printf("Album: %s\n", temp.albumTitle);
		printf("Song: %s\n", temp.songTitle);
		printf("Genre: %s\n\n", temp.genre);
		printf("Enter minute value:   ");
		scanf("%d", &temp.length.minutes);
		printf("Enter second Value:   ");
		scanf("%d", &temp.length.seconds);
	} while (temp.length.minutes < 0 || temp.length.seconds < 0 || temp.length.seconds > 59);

	//get times played
	do
	{
		system("cls");
		printf("Artist: %s\n", temp.artist);
		printf("Album: %s\n", temp.albumTitle);
		printf("Song: %s\n", temp.songTitle);
		printf("Genre: %s\n", temp.genre);
		printf("Duration: %d:%d\n\n", temp.length.minutes, temp.length.seconds);
		printf("Enter times played:   ");
		scanf("%d", &temp.timesPlayed);
	} while (temp.timesPlayed < 0);

	//get rating
	do
	{
		system("cls");
		printf("Artist: %s\n", temp.artist);
		printf("Album: %s\n", temp.albumTitle);
		printf("Song: %s\n", temp.songTitle);
		printf("Genre: %s\n", temp.genre);
		printf("Duration: %d:%d\n", temp.length.minutes, temp.length.seconds);
		printf("Times played: %d\n\n", temp.timesPlayed);
		printf("Enter new rating between 1 and 5:   ");
		scanf("%d", &temp.rating);
	} while (temp.rating < 1 || temp.rating > 5);

	system("cls");
	printf("Artist: %s\n", temp.artist);
	printf("Album: %s\n", temp.albumTitle);
	printf("Song: %s\n", temp.songTitle);
	printf("Genre: %s\n", temp.genre);
	printf("Duration: %d:%d\n", temp.length.minutes, temp.length.seconds);
	printf("Times played: %d\n", temp.timesPlayed);
	printf("Rating: %d\n\n", temp.rating);

	return temp;
}


//deletes a record with a songname matching the users input returns TRUE if song was deleted False if it wasnt
Boolean deleteSong(Node** pList, char* song)
{

	Node* current = *pList;
	char songTitle[100] = { '\0' };
	int check = 0;

	do
	{

		check = strcmp(current->data.songTitle, song);

		if (check == 0)
		{
			if (*pList == (*pList)->pNext && *pList == (*pList)->pPrev)
			{
				free(*pList);
				*pList = NULL;
				current = NULL;
				return TRUE;
			}
			else
			{
				if (current == *pList)
				{
					*pList = current->pNext;
				}
				current->pPrev->pNext = current->pNext;
				current->pNext->pPrev = current->pPrev;
				free(current);
				current = NULL;
				return TRUE;
			}
		}

		current = current->pNext;

	} while (current != *pList);

	return FALSE;
}


//plays the songs in a random order that was made in makeOrder() function
void shuffle(Node** pList, int order[100], int count)
{
	Node* current = pList;
	int difference = 0;

	for (int i = 0; i != count; ++i)
	{
		if (i == 0)
		{
			for (int h = 0; h != order[i] - 1; ++h)
			{
				current = current->pNext;
			}
		}
		else if (order[i] > order[i - 1])
		{
			difference = order[i] - order[i - 1];

			for (int h = 0; h != difference; ++h)
			{
				current = current->pNext;
			}
		}
		else if (order[i] < order[i - 1])
		{
			difference = order[i - 1] - order[i];

			for (int h = 0; h != difference; ++h)
			{
				current = current->pPrev;
			}
		}

		printf("Artist: %s\n", current->data.artist);
		printf("Album: %s\n", current->data.albumTitle);
		printf("Song: %s\n", current->data.songTitle);
		printf("Genre: %s\n", current->data.genre);
		printf("Duration: %d:%d\n", current->data.length.minutes, current->data.length.seconds);
		printf("Times Played: %d\n", current->data.timesPlayed);
		printf("Rating: %d\n\n", current->data.rating);
		printf("\n\n");

		delay(10);

		system("cls");
	}
}


//makes a random order for songs to be played in the shuffle() function
int makeOrder(Node** pList, int order[100])
{
	Node* current = *pList;
	int count = 0;
	int check = 0;


	do
	{
		++count;

		current = current->pNext;

	} while (current != *pList);

	for (int i = 0; i != count; ++i)
	{
		do
		{

			check = 0;

			order[i] = rand() % count + 1;

			for (int j = 0; j != i; ++j)
			{
				if (order[j] == order[i])
				{
					check = 1;
				}
			}

		} while (check == 1);
	}

	return count;

}


//lets the user choose a way to sort the list then sorts it
void sortList(Node** pList)
{
	int choice = 0;

	do
	{
		system("cls");
		printf("(1)    Sort based on artist (A-Z)\n(2)    Sort based on album title(A - Z)\n(3)    Sort based on rating(1 - 5)\n(4)    Sort based on times played(largest - smallest)\n\n");

		printf("Enter the number for your chosen sorting method:  ");
		scanf("%d", &choice);

	} while (choice > 4 || choice < 1);

	system("cls");

	if (choice == 1)
	{
		artistSort(&(*pList));
		printf("\nSongs have been sorted in alphabetical order based on artist name\n\n");
	}
	else if (choice == 2)
	{
		albumSort(&(*pList));
		printf("\nSongs have been sorted in alphabetical order based on album title\n\n");
	}
	else if (choice == 3)
	{
		ratingSort(&(*pList));
		printf("\nSongs have been sorted based on rating from 1 to 5\n\n");
	}
	else if (choice == 4)
	{
		timesPlayedSort(&(*pList));
		printf("\nSongs have been sorted based on times played from most to least\n\n");
	}

}


//Sorts the artists in alphabetical order
void artistSort(Node** pList)
{
	Node* current = *pList;
	char currentArtist[50] = { '\0' };
	char nextArtist[50] = { '\0' };
	int e = 0;

	do
	{

		e = 0;
		current = *pList;

		do
		{
			strcpy(currentArtist, current->data.artist);
			strcpy(nextArtist, current->pNext->data.artist);

			stringToLower(&currentArtist);
			stringToLower(&nextArtist);

			int check = strcmp(currentArtist, nextArtist);

			if (check > 0)
			{
				Node* currentNext = current->pNext;
				Node* currentPrev = current->pPrev;


				current->pNext = currentNext->pNext;
				current->pNext->pPrev = current;
				current->pPrev = currentNext;
				currentNext->pNext = current;
				currentNext->pPrev = currentPrev;
				currentPrev->pNext = currentNext;

				if (current == *pList)
				{
					*pList = currentNext;
				}

			}
			else
			{
				current = current->pNext;
			}

		} while (current->pNext != *pList && current != *pList);

		current = *pList;

		do
		{
			strcpy(currentArtist, current->data.artist);
			strcpy(nextArtist, current->pNext->data.artist);

			stringToLower(&currentArtist);
			stringToLower(&nextArtist);

			int check2 = strcmp(currentArtist, nextArtist);

			if (check2 > 0)
			{
				e = 1;
			}

			current = current->pNext;

		} while (current->pNext != *pList);

	} while (e == 1);
}


//Sorts the albums in alphabetical order
void albumSort(Node** pList)
{
	Node* current = *pList;
	char currentAlbum[100] = { '\0' };
	char nextAlbum[100] = { '\0' };
	int e = 0;

	do
	{

		e = 0;
		current = *pList;

		do
		{

			strcpy(currentAlbum, current->data.albumTitle);
			strcpy(nextAlbum, current->pNext->data.albumTitle);

			stringToLower(&currentAlbum);
			stringToLower(&nextAlbum);

			int check = strcmp(currentAlbum, nextAlbum);

			if (check > 0)
			{
				Node* currentNext = current->pNext;
				Node* currentPrev = current->pPrev;


				current->pNext = currentNext->pNext;
				current->pNext->pPrev = current;
				current->pPrev = currentNext;
				currentNext->pNext = current;
				currentNext->pPrev = currentPrev;
				currentPrev->pNext = currentNext;

				if (current == *pList)
				{
					*pList = currentNext;
				}

			}
			else
			{
				current = current->pNext;
			}

		} while (current->pNext != *pList && current != *pList);

		current = *pList;

		do
		{
			strcpy(currentAlbum, current->data.albumTitle);
			strcpy(nextAlbum, current->pNext->data.albumTitle);

			stringToLower(&currentAlbum);
			stringToLower(&nextAlbum);

			int check2 = strcmp(currentAlbum, nextAlbum);

			if (check2 > 0)
			{
				e = 1;
			}

			current = current->pNext;

		} while (current->pNext != *pList);

	} while (e == 1);
}


//Sorts the rating from 1 to 5 
void ratingSort(Node** pList)
{
	Node* current = *pList;
	int e = 0;


	do
	{

		e = 0;
		current = *pList;

		do
		{
			
			if (current->data.rating > current->pNext->data.rating)
			{
				Node* currentNext = current->pNext;
				Node* currentPrev = current->pPrev;


				current->pNext = currentNext->pNext;
				current->pNext->pPrev = current;
				current->pPrev = currentNext;
				currentNext->pNext = current;
				currentNext->pPrev = currentPrev;
				currentPrev->pNext = currentNext;

				if (current == *pList)
				{
					*pList = currentNext;
				}

			}
			else
			{
				current = current->pNext;
			}

		} while (current->pNext != *pList && current != *pList);

			current = *pList;

		do
		{

			if (current->data.rating > current->pNext->data.rating)
			{
				e = 1;
			}

			current = current->pNext;

		} while (current->pNext != *pList);

	} while (e == 1);
}


//Sorts the times played from largest to smallest
void timesPlayedSort(Node** pList)
{
	Node* current = *pList;
	int e = 0;


	do
	{

		e = 0;
		current = *pList;

		do
		{

			if (current->data.timesPlayed < current->pNext->data.timesPlayed)
			{
				Node* currentNext = current->pNext;
				Node* currentPrev = current->pPrev;


				current->pNext = currentNext->pNext;
				current->pNext->pPrev = current;
				current->pPrev = currentNext;
				currentNext->pNext = current;
				currentNext->pPrev = currentPrev;
				currentPrev->pNext = currentNext;

				if (current == *pList)
				{
					*pList = currentNext;
				}

			}
			else
			{
				current = current->pNext;
			}

		} while (current->pNext != *pList && current != *pList);

		current = *pList;

		do
		{

			if (current->data.timesPlayed < current->pNext->data.timesPlayed)
			{
				e = 1;
			}

			current = current->pNext;

		} while (current->pNext != *pList);

	} while (e == 1);
}


//changes all characters in a string to lowercase
void stringToLower(char* str)
{
	int l = 0;
	l = strlen(str);

	for (int i = 0; i != l; ++i)
	{
		if (str[i] >= 65 && str[i] <= 90)
		{
			str[i] = str[i] + 32;
		}
	}
}