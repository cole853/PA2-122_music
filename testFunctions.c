/*
		Programmer: Cole Clark
		Date: 2-5-2021

			Description: solutions for PA2 music orgnization

		Modified date: 2-17-2020

			Description: Updated to include solutions for PA3
*/

#include "testFunctions.h"
#include "music.h"


//tests the insert function and prints the results
void testInsert(void)
{
	Node* pList = NULL;
	Record test;
	strcpy(test.artist, "Perry, Katy");
	strcpy(test.albumTitle, "Witness");
	strcpy(test.songTitle, "Chained to the Rhythm");
	strcpy(test.genre, "pop");
	test.length.minutes = 4;
	test.length.seconds = 36;
	test.timesPlayed = -1;
	test.rating = 6;

	insert(&pList, test);

	if (pList == NULL)
	{
		printf("List returned NULL in insert()\n");
	}
	else
	{
		int artist = strcmp(pList->data.artist, "Perry, Katy");
		int album = strcmp(pList->data.albumTitle, "Witness");
		int song = strcmp(pList->data.songTitle, "Chained to the Rhythm");
		int genre = strcmp(pList->data.genre, "pop");

		if (artist == 0 && album == 0 && song == 0 && genre == 0)
		{
			if (pList->data.length.minutes == 4 && pList->data.length.seconds == 36 && pList->data.timesPlayed == 0 && pList->data.rating == 5)
			{
				printf("insert() tested successfully\n");
			}
			else
			{
				printf("At least one int failed to be inserted in insert()\n");
			}
		}
		else
		{
			printf("At least one string failed to be inserted in insert()\n");
		}
	}
}

//tests the delete function and prints the results
void testDelete(void)
{
	Node* pList = NULL;
	Record test;
	strcpy(test.artist, "Perry, Katy");
	strcpy(test.albumTitle, "Witness");
	strcpy(test.songTitle, "Chained to the Rhythm");
	strcpy(test.genre, "pop");
	test.length.minutes = 4;
	test.length.seconds = 36;
	test.timesPlayed = -1;
	test.rating = 6;

	insert(&pList, test);

	char testSong[25] = "Chained to the Rhythm";

	Boolean testB = deleteSong(&pList, testSong);

	if (testB == TRUE)
	{
		if (pList == NULL)
		{
			printf("deleteSong() tested successfully\n");
		}
		else
		{
			printf("List did not return NULL\n");
		}
	}
	else
	{
		printf("Memory was not freed in deleteSong()\n");
	}
}

//tests the shuffle function and prints the results
void testShuffle(void)
{
	Node* pList = NULL;
	Record testA;
	Record testB;
	Record testC;
	int order[3] = { 3, 1, 2 };

	strcpy(testA.artist, "Billy Joel (1st song)");
	strcpy(testA.albumTitle, "The Stranger");
	strcpy(testA.songTitle, "Only the Good Die Young");
	strcpy(testA.genre, "rock");
	testA.length.minutes = 3;
	testA.length.seconds = 55;
	testA.timesPlayed = 10;
	testA.rating = 5;

	strcpy(testB.artist, "The Killers (2nd song)");
	strcpy(testB.albumTitle, "Sam's Town");
	strcpy(testB.songTitle, "Exitlude");
	strcpy(testB.genre, "rock");
	testB.length.minutes = 2;
	testB.length.seconds = 24;
	testB.timesPlayed = 8;
	testB.rating = 4;

	strcpy(testC.artist, "Rise Against (3rd song)");
	strcpy(testC.albumTitle, "Appeal To Reason");
	strcpy(testC.songTitle, "Savior");
	strcpy(testC.genre, "rock");
	testC.length.minutes = 4;
	testC.length.seconds = 2;
	testC.timesPlayed = 9;
	testC.rating = 4;

	insert(&pList, testA);
	insert(&pList, testB);
	insert(&pList, testC);

	shuffle(pList, order, 3);
}