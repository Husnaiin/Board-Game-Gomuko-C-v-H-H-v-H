#include<iostream>
#include<conio.h>
#include<iomanip>
#include<Windows.h>
using namespace std;
#define rows 85
#define cols 117
#define capa 50
#define ss 'O'
void  out(int a[capa][capa], int s)
{
	for (int i = 0; i < s; i++)
	{
		for (int j = 0; j < s; j++)
		{
			cout << setw(3) << a[i][j] << " ";
		}
		cout << endl;
	}
}
void getRowColbyLeftClick(int& rpos, int& cpos)
{
	HANDLE hInput = GetStdHandle(STD_INPUT_HANDLE);
	DWORD Events;
	INPUT_RECORD InputRecord;
	SetConsoleMode(hInput, ENABLE_PROCESSED_INPUT | ENABLE_MOUSE_INPUT | ENABLE_EXTENDED_FLAGS);
	do
	{
		ReadConsoleInput(hInput, &InputRecord, 1, &Events);
		if (InputRecord.Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED)
		{
			cpos = InputRecord.Event.MouseEvent.dwMousePosition.X;
			rpos = InputRecord.Event.MouseEvent.dwMousePosition.Y;
			break;
		}
	} while (true);
}
void gotoRowCol(int rpos, int cpos)
{
	COORD scrn;
	HANDLE hOuput = GetStdHandle(STD_OUTPUT_HANDLE);
	scrn.X = cpos;
	scrn.Y = rpos;
	SetConsoleCursorPosition(hOuput, scrn);
}
void SetClr(int clr)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), clr);
}





/////////////////////////////////////////////////////////////////////////////////////////////////////
bool iswin(char board[][capa], int dim, int winC, char sym)
{
		//h
	for (int r = 0; r < dim; r++) {
		for (int c = 0; c <= dim - winC; c++) {
			int count = 0;
			for (int i = 0; i < winC; i++) {
				if (board[r][c + i] == sym) {
					count++;
				}
				if (count == winC) {
					return true;
				}
			}
		}
	}
		//v
	for (int c = 0; c < dim; c++) {
		for (int r = 0; r <= dim - winC; r++) {
			int count = 0;
			for (int i = 0; i < winC; i++) {
				if (board[r + i][c] == sym)
					count++;
				if (count == winC)
					return true;
			}
		}
	}
		//d1
	for (int r = 0; r <= dim - winC; r++) {
		for (int c = 0; c <= dim - winC; c++) {
			int count = 0;
			for (int i = 0; i < winC; i++) {
				if (board[r + i][c + i] == sym)
					count++;
				if (count == winC)
					return true;
			}
		}
	}
		//d2
	for (int r = 0; r < dim; r++) {
		for (int c = winC - 1; c < dim; c++) {
			int count = 0;
			for (int i = 0; i < winC; i++) {
				if (board[r + i][c - i] == sym)
					count++;
				if (count == winC)
					return true;
			}
		}
	}




	return false;
	
}
void init(char bx[][capa], int& dim, int& nop, char sym[], string  pname[], int& turn,int &w)
{
	cout << "Dimension: ";
	cin >> dim;
	cout << "No of players: ";
	cin >> nop;
	for (int i = 0; i < nop; i++)
	{
		cout << i + 1 << " Player's name: ";
		cin >> pname[i];
		cout << i + 1 << " Player's symbol: ";
		cin >> sym[i];
	}
	cout << "Winning Length: ";
	cin >> w;
	for (int i = 0; i < dim; i++)
	{
		for (int j = 0; j < dim; j++)
		{
			bx[i][j] = ss;
		}
	}
	
	turn = rand() % (nop - 1);

}
void printb(char b[][capa], int dim)
{
	system("cls");
	for (int i = 0; i < dim; i++)
	{
		for (int j = 0; j < dim; j++)
		{
			cout << b[i][j] ;
		}
		cout << endl;
	}

}
void turnmsg(string n)
{
	cout << n << "'s turn: ";
}
bool isvalid(char b[][capa],int dim, int pr, int pc)
{
	if (pr > dim || pc > dim || pr < 0 || pc < 0)
	{
		return false;
	}
	if (b[pr][pc] == ss && pr<dim && pc<dim)
	{
		return true;
	}
	return false;
}
void spos(char b[][capa],int dim, int& pr, int& pc)
{
	do
	{

		getRowColbyLeftClick(pr, pc);
	} while (!isvalid(b, dim, pr, pc));
	
}
void pm(char b[][capa], int pr, int pc,char sym)
{
	b[pr][pc] = sym;
}

void turnchange(int &turn,int nop)
{
	turn = (turn+1) % (nop);
}


bool isdraw(char b[][capa], int dim)
{
	for (int i = 0; i < dim; i++)
	{
		for (int j = 0; j < dim; j++)
		{
			if (b[i][j] == ss)
			{
				return false;
			}
		}
	}
	return true;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void init2(char bx[][capa], int& dim, int& nop, char sym[], string  pname[], int& turn, int& w)
{
	cout << "Dimension: ";
	cin >> dim;
	//cout << "No of players: ";
	nop=2;
	cout <<" Player's name: ";
	cin >> pname[1];
	cout <<" Player's symbol: ";
	cin >> sym[1];

	pname[0] = "Computer";
	sym[0] = '+';
	
	cout << "Winning Length: ";
	cin >> w;
	for (int i = 0; i < dim; i++)
	{
		for (int j = 0; j < dim; j++)
		{
			bx[i][j] = ss;
		}
	}

	turn = rand() % (nop - 1);

}
void cmove(char b[][capa], int dim, int& pr, int& pc,char sym[],int w)
{
	srand(time(0));
	for (int wc = w; wc >0; wc--)
	{
		for (int ri = 0; ri < dim; ri++)
		{
			for (int ci = 0; ci < dim; ci++)
			{
				
				if (isvalid(b, dim, ri, ci))
				{
					b[ri][ci] = sym[1];
					if (iswin(b, dim, wc, sym[1]))
					{
						b[ri][ci] = ss;
						pr = ri;
						pc = ci;
						return;
					}
					b[ri][ci] = ss;
				}
			}
		}
	

	
	
		for (int ri = 0; ri < dim; ri++)
		{
			for (int ci = 0; ci < dim; ci++)
			{
				
				if (iswin(b, dim, ri, ci))
				{
					b[ri][ci] = sym[0];
					if (iswin(b, dim, wc, sym[0]))
					{
						b[ri][ci] = ss;
						pr = ri;
						pc = ci;
						return;
					}
					b[ri][ci] = ss;
				}
			}
		}
	}
	do
	{
		pr = rand() % dim;
		pc = rand() % dim;

	} while (!isvalid(b, dim, pr, pc));

	
}
void spos2(char b[][capa], int dim, int& pr, int& pc,int turn,char sym[],int w)
{
	do
	{
		if (turn == 1)
		{
			getRowColbyLeftClick(pr, pc);
		}
		if (turn == 0)
		{
			cmove(b,dim,pr, pc,sym,w);
		}
	} while (!isvalid(b, dim, pr, pc));

}
int main()
{
	
	int ch;
	cout << "\nFor human verses human press 1\n ";
	cout << "\nFor human verses computer press 2\n ";
	cin >> ch;
	if (ch == 1)
	{
		int dim, nop, turn, pr, pc, w;
		char  b[capa][capa], sym[capa];
		string pn[capa];
		init(b, dim, nop, sym, pn, turn, w);

		printb(b, dim);
		while (true)
		{
			turnmsg(pn[turn]);
			spos(b, dim, pr, pc);
			pm(b, pr, pc, sym[turn]);
			printb(b, dim);
			//wincheck(b,dim, w, sym[turn],pn[turn]);
			if (iswin(b, dim, w, sym[turn]))
			{
				cout << endl;
				cout << pn[turn] << " is winner!";
				break;
			}
			if (isdraw(b, dim))
			{
				cout << endl << "Draw!";
				break;
			}
			turnchange(turn, nop);

		}
	}
	if (ch == 2)
	{
		int dim, nop, turn, pr, pc, w;
		char  b[capa][capa], sym[capa];
		string pn[capa];
		init2(b, dim, nop, sym, pn, turn, w);

		printb(b, dim);
		while (true)
		{
			turnmsg(pn[turn]);
			spos2(b, dim, pr, pc,turn,sym,w);
			pm(b, pr, pc, sym[turn]);
			printb(b, dim);
			//wincheck(b, dim, w, sym[turn]);
			if (iswin(b, dim, w, sym[turn]))
			{
				cout << endl;
				cout << pn[turn] << " is winner!";
				break;
			}
			if (isdraw(b, dim))
			{
				cout << endl << "Draw!";
				break;
			}
			turnchange(turn, nop);

		}
	}
}



///////////////////////////////////////////////////////
