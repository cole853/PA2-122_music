# PA2-122_music
A linked list project for CPTS 122 programming assignment 2. Completed on 2/5/2021.

This program starts by running tests on some of the functions then a menu is displayed with 11 options.

1 loads the song information from MusicPlayList.csv and stores it as a linked list of structs. The number of songs loaded is displayed.

2 stores the song information from the linked list to MusicPlayList.csv.

3 gives an option to display all songs or songs from one artist.

4 allows the user to add a new song to the list.

5 allows the user to delete a song from the list.

6 allows the user to edit a song's information.

7 allows the user to sort the list by alphabetical order of artist, alphabetical order of album, rating, or times played.

8 allows the user to change the rating of a song.

9 displays each song for 10 seconds in order.

10 displays each song for 10 seconds in a random order.

11 stores the song list and exits the program.

# Six Files Are Required:

testFunctions.h: contains the declarations for test functions defined in testFunctions.c.

testFunction.c: contains the definitions for test functions declared in testFunctions.h.

music.h: contains declarations for the functions defined in music.c.

music.c: contains definitions for the functions declared in music.h.

main.c: contains the main function for the program in the terminal.

MusicPlayList.csv: contains the songs that will be loaded as a linked list and their information. This is also where the song linked list is stored.
