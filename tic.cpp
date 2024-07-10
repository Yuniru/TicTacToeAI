#include <iostream>
#include <stdio.h>
#include <time.h>
using namespace std;

#define AI 1
#define Player 2
#define SIDE 3 // ���̱߳�
#define AIMOVE 'O'
#define PlayerMOVE 'X'

void showBoard(char board[][SIDE])
{
	cout << "\t\t\t " << board[0][0] << " | " << board[0][1] << " | " << board[0][2] << endl;
	cout << "\t\t\t����������������������" << endl;
	cout << "\t\t\t " << board[1][0] << " | " << board[1][1] << " | " << board[1][2] << endl;
	cout << "\t\t\t����������������������" << endl;
	cout << "\t\t\t " << board[2][0] << " | " << board[2][1] << " | " << board[2][2] << endl;
}

void showInstructions()
{
	cout << "\t\t\t 1 | 2 | 3 " << endl;
	cout << "\t\t\t����������������������" << endl;
	cout << "\t\t\t 4 | 5 | 6 " << endl;
	cout << "\t\t\t����������������������" << endl;
	cout << "\t\t\t 7 | 8 | 9 " << endl;
}

// ��ʼ��
void initialise(char board[][SIDE])
{
	for (int i = 0; i < SIDE; i++)
	{
		for (int j = 0; j < SIDE; j++)
			board[i][j] = ' ';
	}
}

// ����Ӯ��
void declareWinner(int whoseTurn)
{
	if (whoseTurn == AI)
		cout << "AIʤ��" << endl;
	else
		cout << "Playerʤ��" << endl;
}

// ��һ��
bool rowCrossed(char board[][SIDE])
{
	for (int i = 0; i < SIDE; i++)
	{
		if (board[i][0] == board[i][1] &&
			board[i][1] == board[i][2] &&
			board[i][0] != ' ')
			return (true);
	}
	return (false);
}

// ��һ��
bool columnCrossed(char board[][SIDE])
{
	for (int i = 0; i < SIDE; i++)
	{
		if (board[0][i] == board[1][i] &&
			board[1][i] == board[2][i] &&
			board[0][i] != ' ')
			return (true);
	}
	return (false);
}

// ��б��
bool diagonalCrossed(char board[][SIDE])
{
	if (board[0][0] == board[1][1] &&
		board[1][1] == board[2][2] &&
		board[0][0] != ' ')
		return (true);

	if (board[0][2] == board[1][1] &&
		board[1][1] == board[2][0] &&
		board[0][2] != ' ')
		return (true);

	return (false);
}

// ��Ϸ����
bool gameOver(char board[][SIDE])
{
	return (rowCrossed(board) || columnCrossed(board) || diagonalCrossed(board));
}
bool legalMove(int code, int newmove)
{
	int n = 5;
	while (n-- > 0)
	{
		int move = code & ((1 << 4) - 1);
		if (move == newmove)
			return false;

		code >>= 5;
	}
	return true ;
}

void decode(char board[][SIDE], int code)
{
	initialise(board);
	int n = 5;
	while (n-- > 0)
	{
		int move = code & ((1 << 4) - 1);
		int isAI = (code >> 4) & 1;
		if (move != ((1 << 4) - 1))
			board[move / SIDE][move % SIDE] = isAI ? AIMOVE : PlayerMOVE;
		code >>= 5;
	}
}

// minimax�㷨
int minimax(int code, int depth, bool isAI, int alpha, int beta)
{
	int score = 0;
	int bestScore = 0;
	char board[SIDE][SIDE];
	decode(board, code);
	if (gameOver(board) == true)
	{
		if (isAI == true)
			return -1;
		else
			return +1;
	}
	else
	{
		if (depth < 10)
		{
			if (isAI == true)
			{
				bestScore = -999;
				for (int i = 0; i < SIDE; i++)
				{
					for (int j = 0; j < SIDE; j++)
					{
						if (board[i][j] == ' ')
						{
							// board[i][j] = AIMOVE;
							code <<= 5;
							code += (1 << 4) + i * 3 + j;
							score = minimax(code, depth + 1, false, alpha, beta);
							// board[i][j] = ' ';
							code >>= 5;
							if (score > bestScore)
							{
								bestScore = score;
							}
							if (bestScore > alpha)
							{
								alpha = bestScore;
							}
							if (beta <= alpha)
								break;
						}
					}
				}
				return bestScore;
			}
			else
			{
				bestScore = 999;
				for (int i = 0; i < SIDE; i++)
				{
					for (int j = 0; j < SIDE; j++)
					{
						if (board[i][j] == ' ')
						{
							// board[i][j] = PlayerMOVE;
							code <<= 5;
							code += i * 3 + j;
							score = minimax(code, depth + 1, true, alpha, beta);
							// board[i][j] = ' ';
							code >>= 5;
							if (score < bestScore)
							{
								bestScore = score;
							}
							if (bestScore < beta)
							{
								beta = bestScore;
							}
							if (beta <= alpha)
								break;
						}
					}
				}
				return bestScore;
			}
		}
		else
		{
			return 0;
		}
	}
}

// �����������λ��
int bestMove(int code, int moveIndex)
{
	char board[SIDE][SIDE];
	decode(board, code);
	int x = -1, y = -1; // ��߷�λ��
	int score = 0, bestScore = -999;
	for (int i = 0; i < SIDE; i++)
	{
		for (int j = 0; j < SIDE; j++)
		{
			if (board[i][j] == ' ')
			{ // ����Ϊ��
				// board[i][j] = AIMOVE;
				// score = minimax(board, moveIndex + 1, false, -999, 999);
				// board[i][j] = ' ';

				code <<= 5;
				code += (1 << 4) + i * 3 + j;
				score = minimax(code, 1, false, -999, 999);
				// board[i][j] = ' ';
				code >>= 5;

				if (score > bestScore)
				{
					bestScore = score;
					x = i;
					y = j;
				}
			}
		}
	}
	return x * 3 + y;
}

void playTicTacToe(int whoseTurn)
{

	int code = -1;
	int moveIndex = 0, x = 0, y = 0;

	char board[SIDE][SIDE];
	decode(board, code);
	int cnt_step = 0;
	// �����û�н�����ƽ��
	while (gameOver(board) == false) //&& moveIndex != SIDE * SIDE)
	{
		int n;
		if (whoseTurn == AI)
		{
			n = bestMove(code, moveIndex);
			x = n / SIDE;
			y = n % SIDE;
			code <<= 5;
			// code += 1<<4 + x * 3 + y;
			code += (1 << 4) + n;
			cnt_step++;
			cout << "��" << cnt_step << "�����ӣ�" << n + 1 << endl;

			if (cnt_step >= 6)
			{
				n = code & ((1 << 30) - (1 << 25));
				n >>= 25;
				cout << n + 1 << "��ʧ��" << endl;

				n = code & ((1 << 25) - (1 << 20));
				n >>= 20;
				cout << n + 1 << "������ʧ��" << endl;
			}
			decode(board, code);
			showBoard(board);
			cout << endl;
			moveIndex++;
			whoseTurn = Player;
		}

		else if (whoseTurn == Player)
		{
			// for (int i = 0; i < SIDE; i++)
			// 	for (int j = 0; j < SIDE; j++)
			// 		if (board[i][j] == ' ')
			// 			cout << (i * 3 + j) + 1 << ' ';
			// �� ������ҾͲ�ʵ����, �鷳
			cout << "������ӣ� " << endl;
			cin >> n;
			n--;
			x = n / SIDE;
			y = n % SIDE;

			if (n >= 0 && n < 9 && legalMove(code, n))
			{
				code <<= 5;
				code += +n;
				cnt_step++;
				cout << "��" << cnt_step << "�����ӣ�" << n + 1 << endl;

				if (cnt_step >= 6)
				{
					n = code & ((1 << 30) - (1 << 25));
					n >>= 25;
					cout << n + 1 << "��ʧ��" << endl;

					n = code & ((1 << 25) - (1 << 20));
					n >>= 20;
					cout << n + 1 << "������ʧ��" << endl;
				}
				decode(board, code);
				showBoard(board);
				// printf("%x",code);
				cout << endl;
				moveIndex++;
				whoseTurn = AI;
			}
			else if (n < 0 || n > 8)
			{
				cout << "����ȷ���롣" << endl;
				;
			}
			else
			{
				printf("%x", code);
				cout << "�˴������Ӳ������ӡ�" << endl;
			}
		}
	}
	decode(board, code);
	// ƽ��
	if (gameOver(board) == false) //&& moveIndex == SIDE * SIDE)
	{
		showBoard(board);
		cout << "ƽ�֡�" << endl;
	}

	else
	{
		// ����ʤ��
		showBoard(board);

		if (whoseTurn == AI)
			whoseTurn = Player;
		else if (whoseTurn == Player)
			whoseTurn = AI;

		declareWinner(whoseTurn);
	}
}

int main()
{
	char cho;
	srand((unsigned int)time(NULL));
	do
	{
		int r = rand() % 2;
		cout << "rand() % 2=" << r;
		if (r)
		{
			cout << ",AI����!" << endl;
			playTicTacToe(AI);
		}
		else
		{
			cout << ",�������!" << endl;
			showInstructions();
			playTicTacToe(Player);
		}
		cout << "�Ƿ��˳�?y/n" << endl;
		cin >> cho;
	} while (cho == 'n');
	return (0);
}
