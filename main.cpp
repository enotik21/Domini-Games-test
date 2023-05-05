#include <SFML/Graphics.hpp>
#include <iostream>
#include <locale>

#define LUNGIME 8
#define pawnBLACK 6
#define pawnWHITE -6

using namespace sf;

struct poz
{
	int x, y;
}oldPoz, pawnWHT, pawnBLK;

int  size = 100, move = 0, x, y;
int board[8][8] =
{ 6, 6, 6, 0, 0, 0, 0, 0,
  6, 6, 6, 0, 0, 0, 0, 0,
  6, 6, 6, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0,-6,-6,-6,
  0, 0, 0, 0, 0,-6,-6,-6,
  0, 0, 0, 0, 0,-6,-6,-6, };

int pawnWhite = 0;
int pawnBlack = 0;
int merge = 0; 
int chekW = 0, chekB = 0;







int PawnBlackCheck(int posPawnx, int posPawny)
{
	int ok = 0;
	for (int i = 0; i < LUNGIME; i++)
	{
		for (int j = 0; j < LUNGIME; j++)
		{
			if (board[i][j] < 0)
			{
				
				
				if (ok == 1)
				{
					return 0;
				}
			}
		}
	}
	return 1;
}

int PawnB(int ox, int oy, int nx, int ny)
{
	
	if (oy - 1 >= 0 && nx == ox && ny == oy - 1 && board[ny][nx] <= 0)
	{
		int ok = PawnBlackCheck(ox, oy - 1);
		if (ok == 1)
		{
			return 1; // вниз
		}
	}
	
	if (ox + 1 < LUNGIME && ny == oy && nx == ox + 1 && board[ny][nx] <= 0)
	{
		int ok = PawnBlackCheck(ox + 1, oy);
		if (ok == 1)
		{
			return 1; // вправо
		}
	}
	
	if (oy + 1 < LUNGIME && ny == oy + 1 && nx == ox && board[ny][nx] <= 0)
	{
		int ok = PawnBlackCheck(ox, oy + 1);
		if (ok == 1)
		{
			return 1; // вверх
		}
	}
	
	if (ox - 1 >= 0 && ny == oy && nx == ox - 1 && board[ny][nx] <= 0)
	{
		int ok = PawnBlackCheck(ox - 1, oy);
		if (ok == 1)
		{
			return 1; // влево
		}
	}
	
	
	return 0;
}


int PawnWhiteCheck(int posPawnx, int posPawny)
{
	int ok = 0;
	for (int i = 0; i < LUNGIME; i++)
	{
		for (int j = 0; j < LUNGIME; j++)
		{
			if (board[i][j] > 0)
			{
				
				
				if (ok == 1)
				{
					
					return 0;
				}
			}
		}
	}
	return 1;
}

int PawnW(int ox, int oy, int nx, int ny)
{
	
	if (oy - 1 >= 0 && nx == ox && ny == oy - 1 && board[ny][nx] >= 0)
	{
		int ok = PawnWhiteCheck(ox, oy - 1);
		if (ok == 1)
		{
			return 1; // вниз
		}
	}
	
	if (ox + 1 < LUNGIME && ny == oy && nx == ox + 1 && board[ny][nx] >= 0)
	{
		int ok = PawnWhiteCheck(ox + 1, oy);
		if (ok == 1)
		{
			return 1; // вправо
		}
	}
	
	
	if (oy + 1 < LUNGIME && ny == oy + 1 && nx == ox && board[ny][nx] >= 0)
	{
		int ok = PawnWhiteCheck(ox, oy + 1);
		if (ok == 1)
		{
			return 1; // вверх
		}
	}
	
	
	if (ox - 1 >= 0 && ny == oy && nx == ox - 1 && board[ny][nx] >= 0)
	{
		int ok = PawnWhiteCheck(ox - 1, oy);
		if (ok == 1)
		{
			return 1; // влево
		}
	}
	
	return 0;
}


void pozPawnWhite()
{
	for (int i = 0; i < LUNGIME; i++)
	{
		for (int j = 0; j < LUNGIME; j++)
		{
			if (board[i][j] == pawnWHITE)
			{
				pawnWHT.x = j;
				pawnWHT.y = i;
				break;
			}
		}
	}
}

void pozPawnBlack()
{
	for (int i = 0; i < LUNGIME; i++)
	{
		for (int j = 0; j < LUNGIME; j++)
		{
			if (board[i][j] == pawnBlack)
			{
				pawnBLK.y = i;
				pawnBLK.x = j;
				break;
			}
		}
	}
}

int main()
{
	setlocale(LC_ALL, "RUSSIAN");
	RenderWindow window(VideoMode(800, 800), "Pawns  ва");
	Texture a1, a2, a3;

	a1.loadFromFile("images/board.png");	
	a2.loadFromFile("images/pawnB.png");
	a3.loadFromFile("images/pawnW.png");
	

	Sprite desk(a1);	
	Sprite PawnBlack(a2);
	Sprite PawnWhite(a3);
	Sprite Merge;
	

	float dx = 0, dy = 0;
	int Number = 0;

	while (window.isOpen())
	{
		Vector2i pos = Mouse::getPosition(window);
		x = pos.x / size;
		y = pos.y / size;
		Event e;
		while (window.pollEvent(e))
		{
			if (e.type == Event::Closed)
			{
				window.close();
			}
			window.clear();
			if (e.type == Event::MouseButtonPressed)
			{
				if (e.key.code == Mouse::Left)
				{
					
					
					if (board[y][x] != 0)
					{
						dx = pos.x - x * 100;
						dy = pos.y - y * 100;
						
						if (board[y][x] == pawnBLACK && merge == 1)
						{
							Number = pawnBLACK;
							Merge = PawnBlack;
							board[y][x] = 0;
						}
						if (board[y][x] == pawnWHITE && merge == 0)
						{
							Number = pawnWHITE;
							Merge = PawnWhite;
							board[y][x] = 0;
						}
						if (board[y][x] == 0)
						{
							move = 1;
							oldPoz.x = x;
							oldPoz.y = y;
						}
					}
				}
			}
			if (e.type == Event::MouseButtonReleased)
			{
				if (e.key.code == Mouse::Left)
				{
					int ok = 2;
					
					if (Number == pawnBLACK && move == 1)
					{
						ok = PawnB(oldPoz.x, oldPoz.y, x, y);
						if (ok == 1 && pawnBlack == 0)
						{
							pawnBlack = 1;
						
						}
					}
					if (Number == pawnWHITE && move == 1)
					{
						ok = PawnW(oldPoz.x, oldPoz.y, x, y);
						if (ok == 1 && pawnWhite == 0)
						{
							pawnWhite = 1;
							
						}
					}
					if (ok == 1)
					{
						int nr = board[y][x];
						board[y][x] = Number;
						
						if (merge == 0) // белые сходили, ход чёрных
						{
							if (chekW == 1)
							{
								pozPawnWhite();
								int s = PawnWhiteCheck(pawnWHT.x, pawnWHT.y);
								if (s == 0)
								{
									board[oldPoz.y][oldPoz.x] = Number;
									board[y][x] = nr;
								}
								else
								{
									chekW = 0;
									pozPawnBlack();
									int chek = PawnBlackCheck(pawnBLK.x, pawnBLK.y);
									if (chek == 0)
									{
										chekB = 1;
									}
									merge = 1;
								}
							}
							else
							{
								pozPawnWhite();
								int sa = PawnWhiteCheck(pawnWHT.x, pawnWHT.y);
								if (sa == 0)
								{
									board[oldPoz.y][oldPoz.x] = Number;
									board[y][x] = nr;
								}
								else
								{
									pozPawnBlack();
									int chek = PawnBlackCheck(pawnBLK.x, pawnBLK.y);
									if (chek == 0)
									{
										chekB = 1;
									}
									merge = 1;
								}
							}
						}
						else // чёрние сходили, ход белых
						{
							if (chekB == 1)
							{
								pozPawnBlack();
								int s = PawnBlackCheck(pawnBLK.x, pawnBLK.y);
								if (s == 0)
								{
									board[oldPoz.y][oldPoz.x] = Number;
									board[y][x] = nr;
								}
								else
								{
									chekB = 0;
									pozPawnWhite();
									int chek = PawnWhiteCheck(pawnWHT.x, pawnWHT.y);
									if (chek == 0)
									{
										chekW = 1;
									}
									merge = 0;
								}
							}
							else
							{
								pozPawnBlack();
								int sa = PawnBlackCheck(pawnBLK.x, pawnBLK.y);
								if (sa == 0)
								{
									board[oldPoz.y][oldPoz.x] = Number;
									board[y][x] = nr;
								}
								else
								{
									pozPawnWhite();
									int chek = PawnWhiteCheck(pawnWHT.x, pawnWHT.y);
									if (chek == 0)
									{
										chekW = 1;
									}
									merge = 0;
								}
							}
						}
					}
					else if (ok == 0)
					{
						board[oldPoz.y][oldPoz.x] = Number;
					}
					move = 0;
				}
			}
		}
		/*отображение*/
		window.clear();
		window.draw(desk);
		
		if (move == 1)
		{
			Merge.setPosition(pos.x - dx, pos.y - dy);
			window.draw(Merge);
		}
		for (int i = 0; i < LUNGIME; i++)
		{
			for (int j = 0; j < LUNGIME; j++)
			{

				if (board[i][j] != 0)
				{
					
					if (board[i][j] == pawnBLACK)
					{
						PawnBlack.setPosition(j * size, i * size);
						window.draw(PawnBlack);
					}
					if (board[i][j] == pawnWHITE)
					{
						PawnWhite.setPosition(j * size, i * size);
						window.draw(PawnWhite);
					}
					
				}
			}
		}
		window.display();
	}
	return 0;
}