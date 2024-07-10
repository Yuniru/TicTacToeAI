#include <iostream>
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

// minimax�㷨
int minimax(char board[][SIDE], int depth, bool isAI, int alpha, int beta)
{
	int score = 0;
	int bestScore = 0;
	if (gameOver(board) == true)
	{
		if (isAI == true)
			return -1;
		if (isAI == false)
			return +1;
	}
	else
	{
		if (depth < 9)
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
							board[i][j] = AIMOVE;
							score = minimax(board, depth + 1, false, alpha, beta);
							board[i][j] = ' ';
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
							board[i][j] = PlayerMOVE;
							score = minimax(board, depth + 1, true, alpha, beta);
							board[i][j] = ' ';
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
int bestMove(char board[][SIDE], int moveIndex)
{
	int x = -1, y = -1; // ��߷�λ��
	int score = 0, bestScore = -999;
	for (int i = 0; i < SIDE; i++)
	{
		for (int j = 0; j < SIDE; j++)
		{
			if (board[i][j] == ' ')
			{ // ����Ϊ��
				board[i][j] = AIMOVE;
				score = minimax(board, moveIndex + 1, false, -999, 999);
				board[i][j] = ' ';
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
	char board[SIDE][SIDE];
	int moveIndex = 0, x = 0, y = 0;

	initialise(board);
	int Steps[10000];
	int cnt_step = 0;
	// �����û�н�����ƽ��
	while (gameOver(board) == false) //&& moveIndex != SIDE * SIDE)
	{
		int n;
		if (whoseTurn == AI)
		{
			n = bestMove(board, moveIndex);
			x = n / SIDE;
			y = n % SIDE;
			board[x][y] = AIMOVE;

			cout << "��" << cnt_step << "�����ӣ�" << n + 1 << endl;

			Steps[cnt_step] = n;
			cnt_step++;
			if (cnt_step >= SIDE*2)
			{
				n = Steps[cnt_step - SIDE*2];
				x = n / SIDE;
				y = n % SIDE;
				board[x][y] = ' ';
				cout <<n+1 << "��ʧ��" << endl;

				n = Steps[cnt_step - SIDE*2-1];
				x = n / SIDE;
				y = n % SIDE;
				// board[x][y] = '��';
				cout  <<n+1 << "������ʧ��" << endl;
			}

			showBoard(board);
			cout << endl;
			moveIndex++;
			whoseTurn = Player;
		}

		else if (whoseTurn == Player)
		{
			for (int i = 0; i < SIDE; i++)
				for (int j = 0; j < SIDE; j++)
					if (board[i][j] == ' ')
						cout << (i * 3 + j) + 1 << ' ';
			cout << "������ӣ� " << endl;
			cin >> n;
			n--;
			x = n / SIDE;
			y = n % SIDE;

			if (board[x][y] == ' ' && n < 9 && n >= 0)
			{
				board[x][y] = PlayerMOVE;

				Steps[cnt_step] = n;
				cnt_step++;
				cout << "��" << cnt_step << "�����ӣ�" << n + 1 << endl;

				if (cnt_step >= SIDE*2)
				{
					n = Steps[cnt_step - SIDE*2];
					x = n / SIDE;
					y = n % SIDE;
					board[x][y] = ' ';
					cout  <<n+1 << "��ʧ��" << endl;

					n = Steps[cnt_step - SIDE*2-1];
					x = n / SIDE;
					y = n % SIDE;
					// board[x][y] = '��';
					cout  <<n+1 << "������ʧ��" << endl;
				}

				showBoard(board);
				cout << endl;
				moveIndex++;
				whoseTurn = AI;
			}
			else if (board[x][y] != ' ' && n < 9 && n >= 0)
			{
				cout << "�˴������Ӳ������ӡ�" << endl;
			}
			else if (n < 0 || n > 8)
			{
				cout << "����ȷ���롣" << endl;
				;
			}
		}
	}

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
