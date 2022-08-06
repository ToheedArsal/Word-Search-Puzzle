#include <iostream>
#include <fstream>
#include<ctime>
using namespace std;

void Menu();
bool fileOpen(ifstream& fin);
char** initial(char** arr, int row, int col);
char** Read(ifstream& fin, char** board, int row, int col);
void gridDisplay(char** board);
void getName(char userName[], const int SIZE);
void getWord(char word[], const int SIZE);
bool checkWordInDictionary(ifstream& fin, char word[]);
int getLength(char arr[]);
bool comparison(char user_word[], char dic_word[]);
void randoGrid(char** arr);
bool horizontal_search(char** ptr, char array[], int row, int col);
bool horizontal_search_reverse(char** ptr, char array[], int row, int col);
bool vertical_search(char** ptr, char array[], int row, int col);
void Diagonal_search(char** ptr, char array[], int row, int col);
bool vertical_search_reverse(char** ptr, char array[], int row, int col);
char temp(char a);
void gridDisplayPause(char** board);
void WriteGrid(ofstream&, char**, int, int);
void TopMenu();
void easygame(char** board, char userWord[], const int SIZE, char choice, ifstream& fin, ofstream& fout, int row, int col, int score, int lives, char userName[]);
void medgame(char** board, char userWord[], const int SIZE, char choice, ifstream& fin, ofstream& fout, int row, int col, int score, int lives, char userName[]);
void hardgame(char** board, char userWord[], const int SIZE, char choice, ifstream& fin, ofstream& fout, int row, int col, int score, int lives, char userName[]);

void pauseGame();

int main()
{
	ifstream fin;
	ofstream fout;
	const int SIZE = 50;
	char fileName[SIZE]{ "board.txt" };
	char userName[SIZE]{};
	char userWord[SIZE]{};
	char** board = nullptr;
	int row = 15;
	int col = 15;
	int opt = 0;
	char level = '\0';
	char menu = '\0';
	char choice = '\0';
	int score = 0;
	int lives = 3;
	board = initial(board, row, col);
	TopMenu();

	do
	{
		cout << "\n\n";
		Menu();
		cin >> menu;
		system("cls");

		fin.open(fileName);
		if (fileOpen(fin))
		{
			board = Read(fin, board, row, col);
		}
		fin.close();

		if (menu == 'n')
		{
			cin.ignore();
			getName(userName, SIZE);
			int score = 0;
			int lives = 3;

			do
			{
				gridDisplay(board);
				cin.ignore();
				getWord(userWord, SIZE);

				cout << "Enter 'W' for word or 'p/P' to pause : ";
				cin >> choice;

				if (choice == 'W')
				{
					bool flag = false;


					if (checkWordInDictionary(fin, userWord))
					{
						cout << "\tWord Founded in Dictionary\n";
					}
					else
					{
						cout << "\tWord Not Found\n";
					}

					// Checking if word is found in any direction
					// If not then print not found
					if (horizontal_search(board, userWord, row, col) == true)
					{
						flag = true;
					}
					else if (horizontal_search_reverse(board, userWord, row, col) == true)
					{
						flag = true;
					}
					else if (vertical_search(board, userWord, row, col) == true)
					{
						flag = true;
					}
					else if (vertical_search_reverse(board, userWord, row, col) == true)
					{
						flag = true;
					}

					// All functions(Direction Search) will return a flag it means all will be of bool type
					if (flag == true)
					{
						score = score + 10;
						cout << "Your Score is " << score << endl;
						cout << "Remaining Lives : " << lives << endl;
					}
					else
					{

						lives--;

						cout << "Your Score is " << score << endl;

						cout << "Remaining Lives : " << lives << endl;
					}
					if (lives == 0)
					{
						fout.open("HighRecord.txt");
						fout << userName << "," << score << endl;
						fout.close();
						break;
					}
				}
				else if (choice == 'P' || choice == 'p')
				{
					char choice1 = '\0';

					fout.open("Pausegame.txt");
					WriteGrid(fout, board, row, col);
					fout.close();

					cout << "Press e to exit the game\n";
					cout << "Press r to resume the game\n";
					cin >> choice1;
					if (choice == 'e')
					{
						break;
					}
				}
				else
				{
					cout << "Invalid Input!!\n";
				}
			} while (choice != 'e');
			randoGrid(board);
		}
		else if (menu == 'r')
		{
			fin.open("Pausegame.txt");
			board = Read(fin, board, row, col);
			fin.close();

			gridDisplay(board);

			cin.ignore();
			getWord(userWord, SIZE);

			cout << "Enter 'W' for word or 'p/P' to pause : ";
			cin >> choice;

			if (choice == 'W')
			{
				bool flag = false;
				int score = 0;
				int lives = 3;

				checkWordInDictionary(fin, userWord);

				// Checking if word is found in any direction
				// If not then print not found
				if (horizontal_search(board, userWord, row, col) == true)
				{
					flag = true;
				}
				else if (horizontal_search_reverse(board, userWord, row, col) == true)
				{
					flag = true;
				}
				else if (vertical_search(board, userWord, row, col) == true)
				{
					flag = true;
				}
				else if (vertical_search_reverse(board, userWord, row, col) == true)
				{
					flag = true;
				}

				// All functions(Direction Search) will return a flag it means all will be of bool type
				if (flag == true)
				{
					score = score + 10;
				}
				else
				{
					score = score - 10;
					lives--;
				}
				if (lives == 0)
				{
					fout.open("HighRecord.txt");
					fout << userName << "\t" << score << endl;
					fout.close();
				}
			}
			else if (choice == 'P' || choice == 'p')
			{
				char choice1 = '\0';

				fout.open("Pausegame.txt");
				WriteGrid(fout, board, row, col);
				fout.close();

				cout << "Press e to exit the game\n";
				cout << "Press r to resume the game\n";
				cin >> choice1;
				if (choice == 'e')
				{
					break;
				}
				else if (choice == 'r')
				{
					fin.open("Pausegame.txt");
					Read(fin, board, row, col);
					fin.close();
					// Continue
				}
			}
			else
			{
				cout << "Invalid Input!!\n";
			}
		}
		else if (menu == 'l')
		{
			cout << "Press 1 for easy \n";
			cout << "press 2 for Medium\n";
			cout << "press 3 for Hard \n";
			cin >> opt;
			if (opt == 1)
			{
				easygame(board, userWord, SIZE, choice, fin, fout, row, col, score, lives, userName); //Function call for easy mode
			}
			else if (opt == 2)
			{
				medgame(board, userWord, SIZE, choice, fin, fout, row, col, score, lives, userName);
			}
			else if (opt == 3)
			{
				hardgame(board, userWord, SIZE, choice, fin, fout, row, col, score, lives, userName);
			}
		}
		else if (menu == 'h')
		{
			char readname[SIZE] = { '\0' };
			int scr = 0;

			fin.open("HighRecord.txt");
			while (fin.getline(readname, SIZE, ','))
			{

				fin >> scr;
				fin.ignore();
				cout << "\t\t**High Score**\n\n";
				cout << "Name \tScore\n";
				cout << readname << "\t  " << scr << endl;
			}
			fin.close();
		}
		else if (menu == 'e')
		{
			cout << "Thank you for Using this program Good bye\n";
			exit(-1);
		}
		else
		{
			cout << "Invalid Input!!!\n";
		}
	} while (menu != 'e');


	for (int i = 0; i < 15; i++)
	{
		delete[]board[i];
	}
	delete[]board;

	return 0;
}

void Menu()
{
	cout << "\tMain Menu\n";
	cout << "Press n for new Game\n";
	cout << "Press r for resume Game\n";
	cout << "Press l for level Choices\n";
	cout << "Press h for High score\n";
	cout << "Press e for exist\n";
}
void TopMenu()
{
	cout << "\t\n *********************************************************************************\n";
	cout << "\t\n*                                                                                *\n";
	cout << "\t\n*                               Word Search Puzzle                               *\n";
	cout << "\t\n*                                                                                *\n";
	cout << "\t\n**********************************************************************************\n";
}
bool fileOpen(ifstream& fin)
{
	bool flag = true;
	if (fin.is_open())
	{
		flag = true;
	}
	else
	{
		flag = false;
	}
	return flag;
}
char** initial(char** arr, int row, int col)
{
	arr = new char*[row];
	for (int i = 0; i < row; i++)
	{
		arr[i] = new char[col];
	}
	return arr;
}
char** Read(ifstream& fin, char** board, int row, int col)
{
	int j = 0;
	for (int i = 0; i < row; i++)	//OUTER LOOP FOR ROWS
	{
		for (j = 0; j < col; j++)	//INNER LOOP FOR COLUMNS
		{
			fin >> board[i][j];
		}
		board[i][j] = NULL;
	}

	return board;
}
void WriteGrid(ofstream& fout, char** arr, int row, int col)
{
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			fout << arr[i][j] << " ";
		}
		fout << endl;
	}
}
void gridDisplay(char** board)
{
	for (int i = 0; i < 15; i++)
	{
		for (int j = 0; j < 15; j++)
		{
			cout << board[i][j] << " ";
		}
		cout << endl;
	}
}
void getName(char userName[], const int SIZE)
{
	cout << "Enter your name: ";
	cin.getline(userName, SIZE);
}
void getWord(char word[], const int SIZE)
{
	cout << "Enter word in lower case to search : ";
	cin.getline(word, SIZE);
}
bool checkWordInDictionary(ifstream& fin, char word[])
{
	bool flag = false;
	char arr[50] = { '\0' };

	fin.open("Dictionary.txt");
	if (!fin.is_open())
	{
		cout << "Dictionary not found !!! " << endl;
	}
	else
	{
		while (fin.getline(arr, 49))
		{
			if (comparison(word, arr))
			{
				flag = true;
				break;
			}
		}
	}
	fin.close();

	return flag;
}
int getLength(char arr[])
{
	int count = 0;
	if (arr != nullptr)
	{
		while (arr[count] != '\0')
		{
			count++;
		}
	}
	return count;
}
bool comparison(char user_word[], char dic_word[])
{
	bool flag = true;
	if (getLength(user_word) == getLength(dic_word))
	{
		for (int i = 0; i < getLength(user_word); i++)
		{
			if (user_word[i] != dic_word[i])
			{
				flag = false;
				break;
			}
		}
	}
	else
	{
		flag = false;
	}

	return flag;
}
void randoGrid(char** arr)
{
	srand(time(0));
	for (int i = 0; i < 500; i++)
	{
		int num1 = rand() % 14;
		int num2 = rand() % 14;
		int num3 = rand() % 14;
		int num4 = rand() % 14;

		char ch = arr[num1][num2];
		arr[num1][num2] = arr[num3][num4];
		arr[num3][num4] = ch;
	}
}
bool horizontal_search(char** ptr, char array[], int row, int col)
{
	int size = 0;
	int score = 0;
	int j = 0;
	int x = 0;
	int flag = 0;
	bool flag2 = 0;

	size = getLength(array);

	for (int i = 0; i < col; i++)
	{
		for (int k = 0; k < row; k++)
		{
			x = k;
			flag = 0;
			for (j = 0; j < size; j++)
			{
				array[j] = temp(array[j]);
				if (array[j] != ptr[i][x])
				{
					flag = 1;
					break;
				}
				else
				{
					x++;
				}
			}
			if (array[j] == '\0')
			{
				cout << "Word found in Grid" << "\n";
				cout << "Row : " << i << "\n";
				cout << "Starting col : " << k << "\n";
				cout << "Ending col : " << k + size - 1 << "\n";
				flag2 = true;
			}
		}
	}
	return flag2;
}
bool horizontal_search_reverse(char** ptr, char array[], int row, int col)
{
	int size = 0;
	int score = 0;
	int j = 0;
	int x = 0;
	int count = 0;
	bool flag2 = false;

	size = getLength(array);

	for (int i = 0; i < row; i++)
	{
		for (int k = col; k >= 0; k--)
		{
			x = k;
			count = 0;
			for (j = size - 1; j >= 0; j--)
			{
				array[j] = temp(array[j]);
				if (array[j] != ptr[i][x])
				{
					break;
				}
				else
				{
					count++;
					x++;
				}
			}
			if (count == size)
			{
				cout << "Word found in Grid" << "\n";
				cout << "Row : " << i << "\n";
				cout << "Starting col : " << k << "\n";
				cout << "Ending col : " << k + size - 1 << "\n";
				flag2 = true;
			}
		}
	}
	return flag2;
}
bool vertical_search(char** ptr, char array[], int row, int col)
{
	int size = 0;
	int score = 0;
	int count = 0;
	int j = 0;
	int x = 0;
	bool flag = false;

	size = getLength(array);

	for (int i = 0; i < row; i++)
	{
		for (int k = 0; k < col; k++)
		{
			x = k;
			count = 0;
			for (j = 0; j < size; j++)
			{
				array[j] = temp(array[j]);
				if (array[j] != ptr[k][i])
				{
					k++;
					break;
				}
				else
				{
					x++;
					k++;
					count++;
				}
			}
			if (count == size)
			{
				cout << "Word Found in Grid" << "\n";
				cout << "Col : " << i << "\n";
				cout << "Starting row : " << k << "\n";
				cout << "Ending row : " << k + size - 1 << "\n";
				flag = true;
			}
		}
	}
	return flag;
}
bool vertical_search_reverse(char** ptr, char array[], int row, int col)
{
	int size = 0;
	int score = 0;
	int count = 0;
	int x = 0;
	bool flag = false;

	size = getLength(array);

	for (int i = 0; i < row; i++)
	{
		for (int k = col - 1; k >= 0;)
		{
			x = k;
			count = 0;
			for (int j = 0; j < size; j++)
			{
				array[j] = temp(array[j]);
				if (array[j] != ptr[k][i])
				if (array[j] != ptr[k][i])
				{
					k--;
					break;
				}
				else
				{
					x++;
					count++;
					k--;
				}
			}
			if (count == size)
			{
				cout << "Word Found in Grid" << "\n";
				cout << "Col : " << i << "\n";
				cout << "Starting row : " << k + size - 1 << "\n";
				cout << "Ending row : " << k << "\n";
				flag = true;
			}
		}
	}
	return flag;
}
void Diagonal_search(char** ptr, char array[], int row, int col)
{
	int size = 0;
	int score = 0;
	size = getLength(array);

	int j = 0;
	for (int i = 0; i < col; i++)
	{
		for (int k = 0; k < row; k++)
		{
			for (int j = 0; array[j] != '\0'; j++)
			{
				array[j] = temp(array[j]);
				if (array[j] != ptr[i][k])
				{
					break;
				}
				else
				{
					k = k + 1;
					i++;
				}
			}
			if (array[j] == '\0')
			{
				cout << " word found " << "\n";

				cout << "Start the colume : " << k - size + 1 << "\n";
				cout << "Start the row : " << i - size + 1 << "\n";
				cout << "End the colume : " << k << "\n";
				cout << "End the row : " << i << "\n";
			}
		}
	}

}
char temp(char a)
{

	if (a >= 'a' && a <= 'z')
	{
		a = a - 32;
	}
	return a;
}
void gridDisplayPause(char** board)
{
	ofstream fout;
	for (int i = 0; i < 15; i++)
	{
		for (int j = 0; j < 15; j++)
		{
			fout << board[i][j] << " ";
		}
		cout << endl;
	}
}
void easygame(char**board, char userWord[], const int SIZE, char choice, ifstream& fin, ofstream& fout, int row, int col, int score, int lives, char userName[])
{

	system("cls");
	randoGrid(board);
	do
	{
		gridDisplay(board);
		cin.ignore();
		getWord(userWord, SIZE);

		cout << "Enter 'W' for word or 'p/P' to pause : ";
		cin >> choice;

		if (choice == 'W')
		{
			bool flag = false;


			if (checkWordInDictionary(fin, userWord))
			{
				cout << "\tWord Founded in Dictionary\n";
			}
			else
			{
				cout << "\tWord Not Found\n";
			}

			if (horizontal_search(board, userWord, row, col) == true)
			{
				flag = true;
			}
			else if (horizontal_search_reverse(board, userWord, row, col) == true)
			{
				flag = true;
			}

			if (flag == true)
			{
				score = score + 10;
				cout << "Your Score is " << score << endl;
				cout << "Remaining Lives : " << lives << endl;
			}
			else
			{
				lives--;
				cout << "Your Score is " << score << endl;
				cout << "Remaining Lives : " << lives << endl;
			}
			if (lives == 0)
			{
				fout.open("HighRecord.txt");
				fout << userName << "," << score << endl;
				fout.close();
				break;
			}
		}
		else if (choice == 'P' || choice == 'p')
		{
			char choice1 = '\0';

			fout.open("Pausegame.txt");
			WriteGrid(fout, board, row, col);
			fout.close();

			cout << "Press e to exit the game\n";

			cin >> choice1;
			if (choice == 'e')
			{
				break;
			}

		}
		else
		{
			cout << "Invalid Input!!\n";
		}
	} while (choice != 'e');


}
void medgame(char** board, char userWord[], const int SIZE, char choice, ifstream& fin, ofstream& fout, int row, int col, int score, int lives, char userName[])
{
	system("cls");
	randoGrid(board);
	do
	{
		gridDisplay(board);
		cin.ignore();
		getWord(userWord, SIZE);

		cout << "Enter 'W' for word or 'p/P' to pause : ";
		cin >> choice;

		if (choice == 'W')
		{
			bool flag = false;


			if (checkWordInDictionary(fin, userWord))
			{
				cout << "\tWord Founded in Dictionary\n";
			}
			else
			{
				cout << "\tWord Not Found\n";
			}

			if (horizontal_search(board, userWord, row, col) == true)
			{
				flag = true;
			}
			else if (horizontal_search_reverse(board, userWord, row, col) == true)
			{
				flag = true;
			}
			else if (vertical_search(board, userWord, row, col) == true)
			{
				flag = true;
			}
			else if (vertical_search_reverse(board, userWord, row, col) == true)
			{
				flag = true;
			}

			if (flag == true)
			{
				score = score + 10;
				cout << "Your Score is " << score << endl;
				cout << "Remaining Lives : " << lives << endl;
			}
			else
			{
				lives--;
				cout << "Your Score is " << score << endl;
				cout << "Remaining Lives : " << lives << endl;
			}
			if (lives == 0)
			{
				fout.open("HighRecord.txt");
				fout << userName << "," << score << endl;
				fout.close();
				break;
			}
		}
		else if (choice == 'P' || choice == 'p')
		{
			char choice1 = '\0';

			fout.open("Pausegame.txt");
			WriteGrid(fout, board, row, col);
			fout.close();

			cout << "Press e to exit the game\n";

			cin >> choice1;
			if (choice == 'e')
			{
				break;
			}

		}
		else
		{
			cout << "Invalid Input!!\n";
		}
	} while (choice != 'e');


}
void hardgame(char** board, char userWord[], const int SIZE, char choice, ifstream& fin, ofstream& fout, int row, int col, int score, int lives, char userName[])
{
	system("cls");
	randoGrid(board);
	do
	{
		gridDisplay(board);
		cin.ignore();
		getWord(userWord, SIZE);

		cout << "Enter 'W' for word or 'p/P' to pause : ";
		cin >> choice;

		if (choice == 'W')
		{
			bool flag = false;


			if (checkWordInDictionary(fin, userWord))
			{
				cout << "\tWord Founded in Dictionary\n";
			}
			else
			{
				cout << "\tWord Not Found\n";
			}

			if (horizontal_search(board, userWord, row, col) == true)
			{
				flag = true;
			}
			else if (horizontal_search_reverse(board, userWord, row, col) == true)
			{
				flag = true;
			}
			else if (vertical_search(board, userWord, row, col) == true)
			{
				flag = true;
			}
			else if (vertical_search_reverse(board, userWord, row, col) == true)
			{
				flag = true;
			}

			if (flag == true)
			{
				score = score + 10;
				cout << "Your Score is " << score << endl;
				cout << "Remaining Lives : " << lives << endl;
			}
			else
			{
				lives--;
				cout << "Your Score is " << score << endl;
				cout << "Remaining Lives : " << lives << endl;
			}
			if (lives == 0)
			{
				fout.open("HighRecord.txt");
				fout << userName << "," << score << endl;
				fout.close();
				break;
			}
		}
		else if (choice == 'P' || choice == 'p')
		{
			char choice1 = '\0';

			fout.open("Pausegame.txt");
			WriteGrid(fout, board, row, col);
			fout.close();

			cout << "Press e to exit the game\n";

			cin >> choice1;
			if (choice == 'e')
			{
				break;
			}

		}
		else
		{
			cout << "Invalid Input!!\n";
		}
	} while (choice != 'e');

}
void pauseGame()
{
	ifstream fin;
	ofstream fout;
	const int SIZE = 50;
	char fileName[SIZE]{ "board.txt" };
	char userName[SIZE]{};
	char userWord[SIZE]{};
	char** board = nullptr;
	int row = 15;
	int col = 15;
	int opt = 0;

	system("cls");
	fin.open("board.txt");
	board = initial(board, row, col);
	fin.close();

	gridDisplay(board);
	cin.ignore();
	getName(userName, SIZE);
	getWord(userWord, SIZE);

	if (checkWordInDictionary(fin, userWord))
	{
		cout << "Word Found in Dictionary!!!" << endl;
	}
	else
	{
		cout << "Word not found not found in dictionary!!!" << endl;
	}

	cout << endl << endl;
	cout << "Row Wise : \n";
	horizontal_search(board, userWord, row, col);
	cout << "R O W   B A C K W A R D\n";
	horizontal_search_reverse(board, userWord, row, col);

	cout << "C O L U M N    F O R W A R D\n";
	vertical_search_reverse(board, userWord, row, col);

	cout << "Column Wise : \n";
	fout.open("Pause.txt");
	vertical_search(board, userWord, row, col);
}