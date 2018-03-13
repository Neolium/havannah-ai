#ifndef PROJET_H
#define PROJET_H
#define clrscr() cout << "\033[H\033[2J"
#include <vector>
using namespace std;

const int CaseDeJeux = 50;
const int CaseDeJeux_minimax = 50;
const int dix = 10;

// Move est utiliser dans le minimax pour retourner les meilleur case a jouer
struct Move
{
	int x;
	int y;
};

class start
{

  public:
	//const int CaseDeJeux =5;
	int CaseJouer;
	char **plateau;
	int size; // Table size
	int Joueur;
	vector<int> save;
	vector<int> bridge_array;
	vector<int> fork_array;
	vector<int> ring_array;

	void creationPlateau(int s);

	void AfficherPlateau();

	bool GameBorder(int lig, int col);

	bool Case_De_Quatre_Frere(int lig, int col);

	bool Case_De_Trois_Frere(int lig, int col);

	void show_save();

	bool Visited_Case(int i, int j);

	void Save_Case(int i, int j);

	//#####################  Win Condition  ####################//
	bool CheckWin(int player, int Lig, int Col);
	//                        *                         //
	//                        *'
	//------------------     * ------------------------//
	void Bridge(int player);

	//------------------------------------//
	void Fork(int player);

	//------------------------------------//
	//	void Ring(int lig,int col,int player);
	//		bool half_Ring(int a,int b,int c,int d,int e,int f,char g);
	//int ring_a,ring_b,ring_c,ring_d;
	//###########################################################//

	//###########################" MINIMAX ###############################

	vector<int> bridge_array_minimax;
	// ce vector est sepcialment pour le test de minimax
	// il supprime  tous les cases enregistré apres chaque test

	vector<int> fork_array_minimax;
	// ce vector est sepcialment pour le test de minimax
	// il supprime  tous les cases enregistré apres chaque test

	int CaseJouer_minimax;

	bool Gameover_minimax();

	int follow;
	// ce variavle est un suivi il égale 1 si le human gagne sinon si le Coputer gagne il égale 2
	//----> est un complement de la fonctin score();

	bool gameOver();
	// test si il ne y a pas des Cases vides

	int score();
	// Returns 10 si  human gagne , -10 si Computer gagne, 0 for Nulle

	Move minimax(char **plateau);
	// retourn la meilleur case a jouer via l'algorithme Minimax

	int minSearch(char **plateau);
	// pour trouver le prochain case jouer par Computer (AI) et elle retourn le dernier score possible

	int maxSearch(char **plateau);
	// pour trouver le prochain case jouer par l'human et elle retourn le dernier score possible

	void play();
	// la methode Play c'est pour Lancer le jeux

	bool CheckWin(int Player);

	bool CheckWin_minimax(int Player, int Lig, int Col);
	//                      *                       //
	//                      *                       //
	//                      *                       //
	/*  1 */ void Bridge_minimax(int Player);
	bool Bridge(int a, int b, int c, int d, char g);

	/* 2 */ void Fork_minimax(int Player);
	bool half_fork(char Type, int a, int b, int c, int d, char g);
	int zone(int lig, int col);
	int A, B, C, D;
	//FUNCTION 1 AND 2 ARE COMPLEMENT OF THE FORK FUNCTION

	/* 3 */ void Ring(int lig, int col, int player);
	bool half_Ring(int a, int b, int c, int d, int e, int f, char g);

	//-----------------------------------------------//

	vector<int> tmp_save;

	// ces 3 var pour suivre le test de Minimax
	int test_Max;
	int test_Min;
	int test_mini;
};

#endif
