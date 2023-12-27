/*
		Programmer: Cole Clark
		Date: 2-5-2021

			Description: solutions for PA2 music orgnization

		Modified date: 2-17-2020

			Description: Updated to include solutions for PA3
*/

#include "music.h"
#include "testFunctions.h"

int main(void)
{
	testInsert();
	testDelete();

	printf("\n\n Continuing will test the shuffle() function. Songs should play in the order 3, 1, 2.\n\n");

	system("pause");
	system("cls");

	testShuffle();

	system("pause");
	system("cls");

	srand((unsigned int)time(NULL));
	
	Node* pList = NULL;
	int count = 0;

	int choice = 0;
	do
	{
		choice = getChoice();

		if (choice == 1)
		{
			FILE* infile = fopen("MusicPlayList.csv", "r");

			if (infile == NULL)
			{
				printf("Load file did not open properly.\n");
			}
			else
			{
				count = load(infile, &pList);

				if (pList == NULL)
				{
					printf("list is empty\n\n");
				}
				else
				{
					printf("list is FULL!\n\n");
				}

				//showSongs(pList);
				printf("%d Songs Loaded\n\n", count);
				system("pause");

			}

			fclose(infile);
		}
		else if (choice == 2)
		{
			if (pList == NULL)
			{
				printf("There are no songs in the list\n\n");
			}
			else
			{

				FILE* outfile = fopen("MusicPlayList.csv", "w");

				if (outfile == NULL)
				{
					printf("Store file did not open properly.\n");
				}
				else
				{
					int storeCount = storeSongs(outfile, pList);

					printf("%d Songs stored\n\n", storeCount);
				}

				fclose(outfile);

			}
			system("pause");
		}
		else if (choice == 3)
		{

			if (pList == NULL)
			{
				printf("There are no songs in the list\n\n");
				system("pause");
			}
			else
			{
				display(pList);
			}
		}
		else if (choice == 4)
		{
			Record data = getRecord();
			insert(&pList, data);
			pList = pList->pPrev;
			system("pause");
		}
		else if (choice == 5)
		{
			if (pList == NULL)
			{
				printf("There are no songs in the list\n\n");
			}
			else
			{
				char dummy[5] = { '\0' };
				char delim[2] = "\n";
				char song[100] = { '\0' };

				printf("Enter the name of the song to delete:   ");
				fgets(dummy, sizeof(dummy), stdin);
				fgets(song, sizeof(song), stdin);
				strtok(song, delim);

				Boolean success = deleteSong(&pList, song);

				if (success == TRUE)
				{
					printf("\nSong has been successfully deleted\n\n");
				}
				else
				{
					printf("\nEntered song could not be found. No songs were deleted\n\n");
				}
			}
			system("pause");
		}
		else if (choice == 6)
		{
			if (pList == NULL)
			{
				printf("There are no songs in the list\n\n");
			}
			else
			{
				int editChoice = showCondensed(pList);
				editSong(pList, editChoice);
			}
			system("pause");
		}
		else if (choice == 7)
		{
			if (pList == NULL)
			{
				printf("There are no songs in the list\n\n");
			}
			else
			{
				sortList(&pList);
			}
			system("pause");
		}
		else if (choice == 8)
		{
			if (pList == NULL)
			{
				printf("There are no songs in the list\n\n");
			}
			else
			{
				int rateChoice = showCondensed(pList);
				rateSong(pList, rateChoice);
			}
			system("pause");
		}
		else if (choice == 9)
		{
			if (pList == NULL)
			{
				printf("There are no songs in the list\n\n");
			}
			else
			{
				int songChoice = showCondensed(pList);
				playMusic(pList, songChoice);
			}
			system("pause");
		}
		else if (choice == 10)
		{
			if (pList == NULL)
			{
				printf("There are no songs in the list\n\n");
			}
			else
			{
				int shuffleCount = 0;
				int order[100] = { '\0' };

				shuffleCount = makeOrder(pList, &order);
				shuffle(pList, order, shuffleCount);
			}
			system("pause");
		}
		else if (choice == 11)
		{
			FILE* outfile = fopen("MusicPlayList.csv", "w");

			if (outfile == NULL)
			{
				printf("File did not open properly.\n");
			}
			else
			{
				int storeCount = storeSongs(outfile, pList);

				printf("%d Songs stored\n\n", storeCount);
			}

			fclose(outfile);

			printf("Goodbye...\n\n");
		}
	} while (choice != 11);

		
		return 0;
}