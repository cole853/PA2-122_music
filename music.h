/*
		Programmer: Cole Clark
		Date: 2-5-2021

			Description: solutions for PA2 music orgnization

		Modified date: 2-17-2020

			Description: Updated to include solutions for PA3
*/

#define _CRT_SECURE_NO_WARNINGS

#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#ifndef MUSIC_H
#define MUSIC_H

typedef enum boolean
{

	FALSE, TRUE

} Boolean;

typedef struct duration
{
	int minutes;

	int seconds;

} Duration;

typedef struct record
{
	char artist[50];

	char albumTitle[100];

	char songTitle[100];

	char genre[50];

	Duration length;

	int timesPlayed;

	int rating;

} Record;

typedef struct node
{
	struct node* pPrev;

	struct node* pNext;

	Record data;

} Node;

//Displays the Options and records the user's choice
int getChoice(void);


//Creates a link for the link list
Node* makeNode(Record newData);


//Puts a node into the list after creating one using the makeNode() function
int insert(Node** pList, Record newData);


//Reads the records from infile and puts them into a linked list with the putNode() function
int load(FILE* infile, Node** pList);


//Prints all of the songs in the list with all the information
void showSongs(const Node **pList);


//Writes the song information in outfile
int storeSongs(FILE* outfile, const Node** pList);


//Gives the user an option between seeing all of the songs or just songs from one artist then completes the selected option with showSongs() or ShowArtists()
void display(Node** pList);


//Shows the artists and gives the user an option to choose one. After the user selects an artists, the songs from that artist will print
void showArtists(Node** pList);


//Prints out all of the songs and artists, then allows the user to choose one to edit, play, or rate and returns the answer
int showCondensed(Node** pList);


//Allows the user to rate the song selected in showCondensed() function
void rateSong(Node** pList, int song);


//Allows the user to edit any value for the song selected in showCondensed() function
void editSong(Node** pList, int song);


//Delays the program for number of seconds that was entered
void delay(int seconds);


//Prints each song's information for 10 seconds then shows the next song until all songs have been printted
void playMusic(Node** pList, int song);

//allows the user to input information for a new song
Record getRecord(void);

//deletes a record with a songname matching the users input returns TRUE if song was deleted False if it wasnt
Boolean deleteSong(Node** pList, char* song);

//plays the songs in a random order that was made in makeOrder() function
void shuffle(Node** pList, int order[100], int count);

//makes a random order for songs to be played in the shuffle() function
int makeOrder(Node** pList, int order[100]);

//lets the user choose a way to sort the list then sorts it
void sortList(Node** pList);

//Sorts the artists in alphabetical order
void artistSort(Node** pList);

//Sorts the albums in alphabetical order
void albumSort(Node** pList);

//Sorts the rating from 1 to 5 
void ratingSort(Node** pList);

//Sorts the times played from largest to smallest
void timesPlayedSort(Node** pList);

//changes all characters in a string to lowercase
void stringToLower(char* str);

#endif