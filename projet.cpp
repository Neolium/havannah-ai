#include <iostream>
#include <cmath>
#include "projet.h"
using namespace std;

//#############################  Start  fonctions #######################

//---------------- la creation et l'affichage du plateau --------------//

void start::creationPlateau(int s)
{
	size = s;
	int lig = 0;
	int col = 0;
	lig = size * 2;		//i=1 i<lig-1
	col = size * 4 - 2; //k=1, col-1
	plateau = new char *[lig];

	for (int i = 0; i < lig; i++)
	{
		plateau[i] = new char[col];
	}

	for (int i = 0; i < lig; i++)
	{
		for (int j = 0; j < col; j++)
		{
			plateau[i][j] = ' ';
		}
	}
	CaseJouer = 0;
	int tmp = col - size;
	int j = size;

	for (int i = 1; i <= size; i++)
	{
		for (int k = j; k <= tmp + 1; k = k + 2)
		{
			plateau[i][k] = '*';
		}
		tmp++;
		j--;
	}
	j = j + 2;
	tmp = tmp - 2;

	for (int i = size + 1; i <= lig - 1; i++)
	{
		for (int k = j; k < tmp + 1; k = k + 2)
		{
			plateau[i][k] = '*';
		}
		tmp--;
		j++;
	}

	int asci_num, asci_alph;

	plateau[0][0] = 'o';
	plateau[0][1] = 'l';
	plateau[1][0] = 'l';

	asci_num = 50;
	asci_alph = 97;
	if (col > 9)
	{
		for (j = 2; j < 10; j++)
		{
			plateau[0][j] = asci_num;
			asci_num++;
		}

		for (j = 10; j < col; j++)
		{
			plateau[0][j] = asci_alph;
			asci_alph++;
		}
	}
	else
	{

		for (j = 2; j < 10; j++)
		{
			plateau[0][j] = asci_num;
			asci_num++;
		}
	}

	asci_num = 50;
	asci_alph = 97;

	if (lig > 9)
	{
		for (j = 2; j < 10; j++)
		{
			plateau[j][0] = asci_num;
			asci_num++;
		}
		for (j = 10; j < lig; j++)
		{
			plateau[j][0] = asci_alph;
			asci_alph++;
		}
	}
	else
	{
		for (j = 2; j < lig; j++)
		{
			plateau[j][0] = asci_num;
			asci_num++;
		}
	}
}

//--------------------------------------------------------------//

void start::AfficherPlateau()
{
	int lig, col;
	lig = size * 2;
	col = (size * 4) - 2;
	//clrscr();
	for (int i = 0; i < lig; i++)
	{
		cout << "\t \t";
		for (int j = 0; j < col; j++)
		{
			if (plateau[i][j] == '1' && (i != (0 && 1) && j != (0 && 1)))
			{
				cout << "\033[0;" << 41 << "m"
					 << "  " << plateau[i][j] << "\033[0m";
				;
			}
			else if (plateau[i][j] == '0' && (i != 0 && j != 0))
			{
				cout << "\033[0;" << 42 << "m"
					 << "  " << plateau[i][j] << "\033[0m";
				;
			}
			else if (plateau[i][j] == 'x' && (i != 0 && j != 0))
			{
				cout << "\033[0;" << 43 << "m"
					 << "  " << plateau[i][j] << "\033[0m";
				;
			}
			else
			{
				cout << "  " << plateau[i][j];
			}
		}
		cout << "\n\n";
	}

	cout << "\n \n  \n";
	cout << "Joueur 1 : 1            a: 10   b: 11   c: 12   d: 13   e: 14   f: 15  g: 16   h: 17  i: 18  j: 19  " << endl;
	cout << "Joueur 2 : 0            k: 20   l: 21   m: 22   n: 23   o: 24   p: 25  k: 26   r: 27  s: 28  t: 29  " << endl;
}

//---------------------------------------------------------------------//

//------------------------------------------------------//

bool start::GameBorder(int lig, int col)
{
	if ((col > size * 4 - 2) || (lig > size * 2 - 1))
	{
		return false;
	}
	else if (plateau[lig][col] == ' ')
	{
		return false;
	}
	else if (plateau[lig][col] == '*')
	{
		return true;
	}
	else
	{
		return false;
	}
}
//##########################################################//

bool start::CheckWin(int player, int Lig, int Col)
{

	if (Case_De_Trois_Frere(Lig, Col))
	{
		bridge_array.push_back(Lig * 100 + Col);
	}
	Bridge(player); // test of Bridge

	//bridge_array.erase(bridge_array.end() -1);

	if (Case_De_Quatre_Frere(Lig, Col))
	{
		fork_array.push_back(Lig * 100 + Col);
	}
	Fork(player); // test of Fork

	//fork_array.erase( fork_array.end() -1);
	//ring_array.push_back(Lig*100+Col);

	//Ring(Lig,Col,player); // test of Ring

	if (CaseJouer == CaseDeJeux)
	{
		return true;
	}
	else
	{
		return false;
	}
}

//###################################################################################//
void start::Bridge(int player)
{
	//*************BRIDGE TEST**********************
	char tmp;
	if (player == 1)
	{
		tmp = '1';
	}
	else if (player == 2)
	{
		tmp = '0';
	}
	else if (player == 3)
	{
		tmp = 'x';
	}

	for (int i = 0; i < bridge_array.size(); i++)
	{
		int tmp_lig = bridge_array[i] / 100;
		int tmp_col = bridge_array[i] % 100;

		if (Bridge(tmp_lig, tmp_col, tmp_lig, tmp_col, tmp))
		{
			CaseJouer = CaseDeJeux;
			break;
		}
		else
		{
			save.clear();
		}

	} // end for
	  //********* END OF BRIDGE TEST*******************
}
//################################ Win Condition ####################################//
bool start::Bridge(int a, int b, int c, int d, char g)
{

	if (Case_De_Trois_Frere(a, b) && (Case_De_Trois_Frere(c, d)) && ((c != a) || (d != b)) && (plateau[a][b] == plateau[c][d]))
	{
		return true;
	}

	else
	{ //3
		Save_Case(c, d);
		//	show_save();
		//cout<<" 6 frere  c:  "<<c<<"  d:  "<<d<<" = "<<Visited_Case(c,d)<<endl;
		//if(Case_De_Quatre_Frere(c,d)){cout<<" 4 frere  c:  "<<c<<"  d:  "<<d<<" = "<<Visited_Case(c,d)<<endl;}
		//1
		if ((plateau[c - 1][d + 1] == g) && (Visited_Case(c - 1, d + 1) == false))
		{
			c--;
			d++;
			if (Bridge(a, b, c, d, g))
			{
				return true;
			}
			d--;
			c++;
		}
		//2
		else if ((plateau[c - 1][d - 1] == g) && (Visited_Case(c - 1, d - 1) == false))
		{
			c--;
			d--;
			if (Bridge(a, b, c, d, g))
			{
				return true;
			}
			c++;
			d++;
		}
		//3
		else if ((plateau[c][d + 2] == g) && (Visited_Case(c, d + 2) == false))
		{
			d = d + 2;
			if (Bridge(a, b, c, d, g))
			{
				return true;
			}
			d = d - 2;
		}
		//4
		else if (c != size * 2 - 1 && (plateau[c + 1][d + 1] == g) && (Visited_Case(c + 1, d + 1) == false))
		{
			c++;
			d++;
			if (Bridge(a, b, c, d, g))
			{
				return true;
			}
			c--;
			d--;
		}
		//5
		else if (c != size * 2 - 1 && (plateau[c + 1][d - 1] == g) && (Visited_Case(c + 1, d - 1) == false))
		{
			c++;
			d--;
			if (Bridge(a, b, c, d, g))
			{
				return true;
			}
			c--;
			d++;
		}
		//6
		else if ((plateau[c][d - 2] == g) && (Visited_Case(c, d - 2) == false))
		{
			d = d - 2;
			if (Bridge(a, b, c, d, g))
			{
				return true;
			}
			d = d + 2;
		}

		else
		{
			return false;
		}

	} //3
}

//###################################################################################
void start::Fork(int player)
{

	//******************* FORK TEST *************************
	char tmp;
	if (player == 1)
	{
		tmp = '1';
	}
	else if (player == 2)
	{
		tmp = '0';
	}
	else if (player == 3)
	{
		tmp = 'x';
	}
	for (int i = 0; i < fork_array.size(); i++)
	{
		int tmp_lig = fork_array[i] / 100;
		int tmp_col = fork_array[i] % 100;

		if (half_fork('A', tmp_lig, tmp_col, tmp_lig, tmp_col, tmp))
		{
			save.clear();
			for (int i = 0; i < fork_array.size(); i++)
			{ // for2
				int tmp_lig = fork_array[i] / 100;
				int tmp_col = fork_array[i] % 100;
				if (zone(tmp_lig, tmp_col) != zone(A, B) && zone(tmp_lig, tmp_col) != zone(C, D))
				{
					if (half_fork('B', tmp_lig, tmp_col, tmp_lig, tmp_col, tmp))

					{
						CaseJouer = CaseDeJeux;
						break;
					}
				}
			} // end for 2
		}

		else
		{
			save.clear();
		}

	} // end for1
	  //***************** END OF FORK TEST *************
}
//##################################################################################

bool start::half_fork(char Type, int a, int b, int c, int d, char g)
{

	if (Type == 'A' && Case_De_Quatre_Frere(a, b) && Case_De_Quatre_Frere(c, d) && zone(a, b) != zone(c, d) && (plateau[a][b] == plateau[c][d]))
	{
		A = a;
		B = b;
		C = c;
		D = d;
		return true;
	}

	else if (Type == 'B' && Case_De_Quatre_Frere(a, b) && Case_De_Quatre_Frere(c, d) && zone(a, b) != zone(c, d) && (plateau[a][b] == plateau[c][d]) && ((c == A && d == B) || (c == C && d == D)))
	{
		return true;
	}

	else
	{
		Save_Case(c, d);

		//1
		if ((plateau[c - 1][d + 1] == g) && (Visited_Case(c - 1, d + 1) == false))
		{
			c--;
			d++;
			if (half_fork(Type, a, b, c, d, g))
			{
				return true;
			}
			d--;
			c++;
		}
		//2
		else if ((plateau[c - 1][d - 1] == g) && (Visited_Case(c - 1, d - 1) == false))
		{
			c--;
			d--;
			if (half_fork(Type, a, b, c, d, g))
			{
				return true;
			}
			c++;
			d++;
		}
		//3
		else if ((plateau[c][d + 2] == g) && (Visited_Case(c, d + 2) == false))
		{
			d = d + 2;
			if (half_fork(Type, a, b, c, d, g))
			{
				return true;
			}
			d = d - 2;
		}
		//4
		else if (c != size * 2 - 1 && plateau[c + 1][d + 1] == g && (Visited_Case(c + 1, d + 1) == false))
		{
			c++;
			d++;
			if (half_fork(Type, a, b, c, d, g))
			{
				return true;
			}
			c--;
			d--;
		}
		//5
		else if (c != size * 2 - 1 && (plateau[c + 1][d - 1] == g) && (Visited_Case(c + 1, d - 1) == false))
		{
			c++;
			d--;
			if (half_fork(Type, a, b, c, d, g))
			{
				return true;
			}
			c--;
			d++;
		}
		//6
		else if ((plateau[c][d - 2] == g) && (Visited_Case(c, d - 2) == false))
		{
			d = d - 2;
			if (half_fork(Type, a, b, c, d, g))
			{
				return true;
			}
			d = d + 2;
		}

		else
		{
			return false;
		}
	}
}
//################################################################################# //
void start::Ring(int lig, int col, int player)
{
	char tmp;
	if (player == 1)
	{
		tmp = '1';
	}
	else if (player == 2)
	{
		tmp = '0';
	}
	else if (player == 3)
	{
		tmp = 'x';
	}

	int tt = lig * 100 + col;
	int k = 0;
	for (int j = 0; j < save.size(); j++)
	{
		if (save[j] == tt)
		{
			k = j;
		}
	}

	for (int i = 0; i < ring_array.size(); i++)
	{ //for1

		int t_lig = ring_array[i] / 100;
		int t_col = ring_array[i] % 100;
		if ((t_lig != lig) && (t_col != col) && ((t_lig > lig + 1 || t_lig < lig - 1) || (t_col > col + 2 || t_col < col - 2)))
		{
			//cout<<"lig = "<<lig<<" col = "<<col<<endl;
			//cout<<"t-lig = "<<t_lig<<" t_col = "<<t_col<<endl;
			//show_save();
			if (half_Ring(lig, col, lig, col, t_lig, t_col, tmp))
			{   //if 2
				//		cout<<"before erase: ";show_save();
				save.erase(save.begin() + k);
				//		cout<<"After erase: ";show_save();
				if (half_Ring(t_lig, t_col, t_lig, t_col, lig, col, tmp))
				{ //if 3
					CaseJouer = CaseDeJeux;
				} // if3

				else
				{
					save.insert(save.begin() + k, tt);
				}

			} // if 2

		} // end if 1
		if (CaseJouer == CaseDeJeux)
		{
			break;
		}
		else
		{
			save.clear();
		}
	} //end for1
}

//#################################################################################//
bool start::half_Ring(int a, int b, int c, int d, int e, int f, char g)
{

	if ( // ( (c>a+1) || (c<a-1) ) &&
		//( (d>b+2) || (d<b-2 ) ) &&
		((c == e) && (d == f)) &&
		(plateau[a][b] == plateau[c][d]))
	{
		return true;
	}

	else
	{ //3

		Save_Case(c, d);
		//	cout<<"ring = "<<ring<<endl;
		//cout<<"de half-ring:";show_save();

		//1
		if ((plateau[c - 1][d + 1] == g) && (Visited_Case(c - 1, d + 1) == false))
		{
			c--;
			d++;
			if (half_Ring(a, b, c, d, e, f, g))
			{
				return true;
			}
			d--;
			c++;
		}
		//2
		else if ((plateau[c - 1][d - 1] == g) && (Visited_Case(c - 1, d - 1) == false))
		{

			c--;
			d--;
			if (half_Ring(a, b, c, d, e, f, g))
			{
				return true;
			}
			c++;
			d++;
		}
		//3
		else if ((plateau[c][d + 2] == g) && (Visited_Case(c, d + 2) == false))
		{
			//			cout<<"howa ana khatini"<<endl;
			d = d + 2;
			if (half_Ring(a, b, c, d, e, f, g))
			{
				return true;
			}
			d = d - 2;
		}
		//4
		else if (c != size * 2 - 1 && (plateau[c + 1][d + 1] == g) && (Visited_Case(c + 1, d + 1) == false))
		{
			//cout<<"howa ana khatini taht"<<endl;
			c++;
			d++;
			if (half_Ring(a, b, c, d, e, f, g))
			{
				return true;
			}
			c--;
			d--;
		}
		//5
		else if (c != size * 2 - 1 && (plateau[c + 1][d - 1] == g) && (Visited_Case(c + 1, d - 1) == false))
		{
			c++;
			d--;
			if (half_Ring(a, b, c, d, e, f, g))
			{
				return true;
			}
			c--;
			d++;
		}
		//6
		else if ((plateau[c][d - 2] == g) && (Visited_Case(c, d - 2) == false))
		{
			d = d - 2;
			if (half_Ring(a, b, c, d, e, f, g))
			{
				return true;
			}
			d = d + 2;
		}

		else
		{
			return false;
		}
		//}
	}
}
//##############################################################################
bool start::Case_De_Quatre_Frere(int lig, int col)
{

	if (((lig != 1) && (lig < size)) && (col < size))
	{
		return true;
	}
	else if ((lig > size) && (col <= size - 1))
	{
		return true;
	}
	else if (((lig != 1) && (lig < size)) && (col > size * 4 - 2 - size))
	{
		return true;
	}
	else if ((lig > size) && (col > size * 4 - 2 - size))
	{
		return true;
	}
	else if ((lig == 1) && (col > size) && (col < size * 4 - 2 - size))
	{
		return true;
	}
	else if ((lig == size * 2 - 1) && (col > size) && (col < size * 4 - 2 - size))
	{
		return true;
	}
	else
	{
		return false;
	}
}

int start::zone(int lig, int col)
{

	if ((lig == 1) && (col > size) && (col < size * 4 - 2 - size))
	{
		return 1;
	}
	else if (((lig != 1) && (lig < size)) && (col > size * 4 - 2 - size))
	{
		return 2;
	}
	else if ((lig > size) && (col > size * 4 - 2 - size))
	{
		return 3;
	}
	else if ((lig == size * 2 - 1) && (col > size) && (col < size * 4 - 2 - size))
	{
		return 4;
	}
	else if ((lig > size) && (col <= size - 1))
	{
		return 5;
	}
	else if (((lig != 1) && (lig < size)) && (col < size))
	{
		return 6;
	}
	// else { return 0;}
}

bool start::Case_De_Trois_Frere(int lig, int col)
{
	if (((lig == 1) && ((col == size) || (col == size * 4 - 2 - size))) || ((lig == size) && ((col == 1) || (col == size * 4 - 3))) ||
		((lig == size * 2 - 1) && ((col == size) || (col == size * 4 - 2 - size))))
	{
		return true;
	}
	else
	{
		return false;
	}
}

//################################################################################//
void start::Save_Case(int c, int d)
{
	int tmp;
	tmp = c * 100 + d;
	save.push_back(tmp);
}

bool start::Visited_Case(int i, int j)
{
	bool rep = false;
	int tmp;
	tmp = i * 100 + j;

	for (int k = 0; k < save.size(); k++)
	{
		if (save[k] == tmp)
		{
			rep = true;
		}
	}
	return rep;
}

//#################################################################################//
void start::show_save()
{
	for (int k = 0; k < save.size(); k++)
	{
		cout << save[k] << ",";
	}
	cout << "\n ";
}

//################################# MINIMAX ############################"/

bool start::gameOver()
{
	bool res = true;
	int lig = size * 2;
	int col = size * 4 - 2;
	int tmp = col - size;
	int j = size;

	for (int i = 1; i <= size; i++)
	{
		for (int k = j; k <= tmp + 1; k = k + 2)
		{
			if (plateau[i][k] == '*')
			{
				res = false;
			};
		}
		tmp++;
		j--;
	}
	j = j + 2;
	tmp = tmp - 2;

	for (int i = size + 1; i <= lig - 1; i++)
	{
		for (int k = j; k < tmp + 1; k = k + 2)
		{
			if (plateau[i][k] == '*')
			{
				res = false;
			};
		}
		tmp--;
		j++;
	}
	return res;
}

void start::play()
{
	int Lig, Col;
	int turn = 0;
	string trn;
	int compteur = 0;
	test_Max = 0;
	test_Min = 0;
	test_mini = 0;
	while (trn != "Y" && trn != "y" && trn != "N" && trn != "n")
	{
		cout << "  \n \t do you want to start first ? (Y or N)   " << endl;
		cin >> trn;
	}

	if (trn == "Y" || trn == "y")
	{
		turn = 0;
	}
	else if (trn == "N" || trn == "n")
	{
		turn = 1;
	}

	AfficherPlateau();
	while (CaseJouer != CaseDeJeux)
	{
		// human move

		if (turn % 2 == 0)
		{
			cout << "\nJoueur  1 :" << endl;
			cout << "ligne :" << endl;
			cin >> Lig;
			cout << "col: " << endl;
			cin >> Col;
			if (GameBorder(Lig, Col))
			{
				plateau[Lig][Col] = '1';
				compteur++;
				//	AfficherPlateau();
				if (CheckWin(1, Lig, Col) == true)
				{
					AfficherPlateau();

					cout << "compteur= " << compteur << endl;
					for (int i = 0; i < fork_array.size(); i++)
					{
						cout << " - " << fork_array[i];
					}

					cout << "\n bridge:" << endl;
					for (int i = 0; i < bridge_array.size(); i++)
					{
						cout << " - " << bridge_array[i];
					}
					cout << "\n Human Player Wins" << endl;
					break;
				}
				turn++;
				AfficherPlateau();
			}
			else
			{
				cout << "la ligne ou la col entre n'appartient pas a la zone de jeux merci de Reverifier " << endl;
			}
		}
		else
		{

			cout << endl << "Computer Player Move:" << endl;
			
			Move AImove = monte_carlo(plateau);

			plateau[AImove.x][AImove.y] = '0';

			if (CheckWin(2, AImove.x, AImove.y))
			{
				AfficherPlateau();

				cout << " \nComputer Player Wins" << endl;

				break;
			}

			turn++;

			AfficherPlateau();
		}
	}
}

//-------------------------------------------------

Move start::monte_carlo(char **plateau) {
	cout << "MonteCarlo" << endl;

	int wins = 0;
	bool AIWins = false;
	int probability = 0;
	int simulations = 100;
	Move move;

	// Selecting all free nodes, we'll play a simulation for each (MC is depth 1)
	for (int i = 1; i < size * 2; i++) {
		for (int j = 1; j < size * 4 - 2; j++) {

			// If the node is free to play
			if (plateau[i][j] == '*') {

				// TODO: Add plateau fork
				// 1 - Fork the plateau
				// 2 - Set the current node as AI move

				wins = 0; // Count the number of wins in the simulations

				// Do the simulations on this node:
				for (int k = 0; k < simulations; k++) {

					// We'll Simulate the game
					while(!AIWins && !CheckWin(1)) {

						// TODO: Add random moves generation
						// 1 - Random other player (OP) move
						// 2 - Random AI player move
						
						AIWins = CheckWin(0);
					}

					if(AIWins) wins++; // If AI wins, we increment the wins counter
				}

				// If simulations offer a better probability, we'll select the current node as a move
				if((wins / simulations) > probability) {
					move.x = i;
					move.y = j;
				}
			}
		}
	}

	return move;
}

Move start::minimax(char **plateau)
{
	cout << "Minimax" << endl;
	int bestMoveScore = 9999; // -100 is arbitrary
	Move bestMove;

	for (int i = 1; i < size * 2; i++)
	{
		for (int j = 1; j < size * 4 - 2; j++)
		{
			if (plateau[i][j] == '*')
			{
				test_mini++;
				plateau[i][j] = '0';

				for (int x = 1; x < size * 2; x++)
				{
					for (int y = 1; y < size * 4 - 2; y++)
					{
						if (plateau[x][y] != ' ')
						{
							if (Case_De_Trois_Frere(x, y))
							{
								bridge_array_minimax.push_back(x * 100 + y);
							}
							else if (Case_De_Quatre_Frere(x, y))
							{
								fork_array_minimax.push_back(x * 100 + y);
							}
						}
					}
				}

				int tempMoveScore = maxSearch(plateau);

				//CaseJouer_minimax=0;
				follow = 0;

				if (tempMoveScore < bestMoveScore)
				{
					bestMoveScore = tempMoveScore;
					bestMove.x = i;
					bestMove.y = j;
				}

				bridge_array_minimax.clear();
				fork_array_minimax.clear();

				plateau[i][j] = '*'; //break;
			}						 //end if 1
		}							 //end for2
	}								 // end for1

	return bestMove;
}
//--------------------------------------

int start::maxSearch(char **plateau)
{
	cout << "Maxsearch" << endl;
	if (Gameover_minimax())
	{   //bridge_array_minimax.clear();
		//fork_array_minimax.clear();
		return score();
	}
	Move bestMove;

	int bestMoveScore = -9999;

	for (int i = 1; i < size * 2; i++)
	{
		for (int j = 1; j < size * 4 - 2; j++)
		{
			if (plateau[i][j] == '*')
			{
				test_Max++;
				plateau[i][j] = '1';

				bridge_array_minimax.clear();
				fork_array_minimax.clear();

				for (int x = 1; x < size * 2; x++)
				{
					for (int y = 1; y < size * 4 - 2; y++)
					{
						if (plateau[x][y] != ' ')
						{
							if (Case_De_Trois_Frere(x, y))
							{
								bridge_array_minimax.push_back(x * 100 + y);
							}
							else if (Case_De_Quatre_Frere(x, y))
							{
								fork_array_minimax.push_back(x * 100 + y);
							}
						}
					}
				}

				int tempMoveScore = minSearch(plateau);
				CaseJouer_minimax = 0;
				follow = 0;
				if (tempMoveScore > bestMoveScore)
				{
					bestMoveScore = tempMoveScore;
					bestMove.x = i;
					bestMove.y = j;
				}
				//				bridge_array_minimax.clear();
				//				fork_array_minimax.clear();

				plateau[i][j] = '*';
			}
		}
	}

	return bestMoveScore;
}
//---------------------------------------------

int start::minSearch(char **plateau)
{
	cout << "MINIsearch" << endl;
	if (Gameover_minimax())
	{   //bridge_array_minimax.clear();
		//fork_array_minimax.clear();
		return score();
	}
	Move bestMove;

	int bestMoveScore = 9999;

	//bridge_array_minimax.clear();
	//fork_array_minimax.clear();

	for (int i = 1; i < size * 2; i++)
	{
		for (int j = 1; j < size * 4 - 2; j++)
		{
			if (plateau[i][j] == '*')
			{
				test_Min++;
				plateau[i][j] = '0';

				bridge_array_minimax.clear();
				fork_array_minimax.clear();

				for (int x = 1; x < size * 2; x++)
				{
					for (int y = 1; y < size * 4 - 2; y++)
					{
						if (plateau[x][y] != ' ')
						{
							if (Case_De_Trois_Frere(x, y))
							{
								bridge_array_minimax.push_back(x * 100 + y);
							}
							else if (Case_De_Quatre_Frere(x, y))
							{
								fork_array_minimax.push_back(x * 100 + y);
							}
						}
					}
				}

				int tempMove = maxSearch(plateau);

				CaseJouer_minimax = 0;
				follow = 0;

				if (tempMove < bestMoveScore)
				{
					bestMoveScore = tempMove;
					bestMove.x = i;
					bestMove.y = j;
				}
				//bridge_array_minimax.clear();
				//fork_array_minimax.clear();
				//	CaseJouer_minimax=0;
				//	follow=0;
				plateau[i][j] = '*';
			}
		}
	}

	return bestMoveScore;
}

//----------------------------------------

int start::score()
{
	//if(CheckWin(1)) {if(follow==1){ return 10;} }
	//else if(CheckWin(2)) { if(follow==2){ return -10;} }
	if (follow == 1)
	{
		return 10;
	}
	else if (follow == 2)
	{
		return -10;
	}
	return 0; // draw
}

//----------------------------------------

bool start::CheckWin(int Player)
{
	Bridge_minimax(Player);
	if (CaseJouer_minimax == CaseDeJeux_minimax)
	{
		follow = Player;
		return true;
	}
	Fork_minimax(Player);
	if (CaseJouer_minimax == CaseDeJeux_minimax)
	{
		follow = Player;
		return true;
	}
	//if (CaseJouer==CaseDeJeux){ return true;  }

	else
	{
		return false;
	}
}

// ----------------------------------------

bool start::Gameover_minimax()
{
	cout << "GaME OVER TEST" << endl;
	if (CheckWin(1))
	{
		cout << "GaME OVER TEST Human" << endl;
		return true;
	}
	else if (CheckWin(2))
	{
		cout << "GaME OVER TEST pc" << endl;
		return true;
	}

	bool emptySpace = false;
	for (int i = 1; i < size * 2; i++)
	{
		for (int j = 1; j < size * 4 - 3; j++)
		{
			if (plateau[i][j] == '*')
				emptySpace = true;
		}
	}
	return !emptySpace;
}

//###################################################################################//
void start::Bridge_minimax(int player)
{
	//*************BRIDGE TEST**********************
	char tmp;
	if (player == 1)
	{
		tmp = '1';
	}
	else if (player == 2)
	{
		tmp = '0';
	}
	else if (player == 3)
	{
		tmp = 'x';
	}

	for (int i = 0; i < bridge_array_minimax.size(); i++)
	{
		int tmp_lig = bridge_array_minimax[i] / 100;
		int tmp_col = bridge_array_minimax[i] % 100;

		if (Bridge(tmp_lig, tmp_col, tmp_lig, tmp_col, tmp))
		{
			CaseJouer_minimax = CaseDeJeux_minimax;
			break;
		}
		else
		{
			save.clear();
		}

	} // end for
	  //********* END OF BRIDGE TEST*******************
}

//###################################################################################
void start::Fork_minimax(int player)
{

	//******************* FORK TEST *************************
	char tmp;
	if (player == 1)
	{
		tmp = '1';
	}
	else if (player == 2)
	{
		tmp = '0';
	}
	else if (player == 3)
	{
		tmp = 'x';
	}
	for (int i = 0; i < fork_array_minimax.size(); i++)
	{
		int tmp_lig = fork_array_minimax[i] / 100;
		int tmp_col = fork_array_minimax[i] % 100;

		if (half_fork('A', tmp_lig, tmp_col, tmp_lig, tmp_col, tmp))
		{
			save.clear();
			for (int i = 0; i < fork_array_minimax.size(); i++)
			{ // for2
				int tmp_lig = fork_array_minimax[i] / 100;
				int tmp_col = fork_array_minimax[i] % 100;
				if (zone(tmp_lig, tmp_col) != zone(A, B) && zone(tmp_lig, tmp_col) != zone(C, D))
				{
					if (half_fork('B', tmp_lig, tmp_col, tmp_lig, tmp_col, tmp))

					{
						CaseJouer_minimax = CaseDeJeux_minimax;
						break;
					}
				}
			} // end for 2
		}

		else
		{
			save.clear();
		}

	} // end for1
	  //***************** END OF FORK TEST *************
}