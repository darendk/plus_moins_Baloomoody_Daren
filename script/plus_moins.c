#include<stdio.h>
#include<stdlib.h>
#include<time.h>

//Programme qui génére le jeu plus moins

void plus_moins(int choix_joueur, int valeur_a_trouver)  //compare la réponse de joueur à la valeur à trouver
{
   if (choix_joueur < valeur_a_trouver)
	printf("Plus\n");
   else if (choix_joueur > valeur_a_trouver)
	printf("Moins\n");
   else
	printf("Bingo!\n\n");
}

int difficulty(int niveau_diff)   //permet de définir les modes de difficultés 
{
   switch(niveau_diff)
   {
   	case 1: //Facile
		return 10000; //Infinité d'essai
		break;
	case 2: //Moyen
		return 25;
		break;
	case 3: //Difficile
		return 10;
		break;
   }
}

int guess(int val,int limit)   //génère les devinettes 
{
   printf("Je pense à un chiffre entre 0 et 100.\n");
   int essai=0;
   int essai_restant=limit;
   int prop;  //proposition du joueur
   do
   {
     printf("Essaie de deviner: \n");
     scanf("%d",&prop);
     plus_moins(prop,val);
     essai++;
     essai_restant--;
     if (essai == limit)
       {
          printf("Perdu!\n\n");
          break;
       }
   }
   while((prop !=  val) && (essai<=limit));
   return essai_restant;  //retourne le nombre d'essai restant 
}

int turn(int id_joueur )  //permet au 2 joueurs de passer à tour de rôle
{
   srand(time(NULL));  //va réinitialiser rand() à chaque passage des joueurs
   int val2=rand()%100;   //une autre valeur à trouver différente de celle dans main()
   printf("Joueur %d, défie ton adversaire.\n",id_joueur);
   int nbr_coup;
   printf("Limite ses nombres d'essais (minimum 10):\n");
   scanf("%d",&nbr_coup);
   switch(id_joueur)  //pour rappeler à qui le tour 
   {
	case 1:  //si c'est joueur1 qui set le nombre d'essai
	    printf("Joueur 2 à toi de jouer!\n");  //c'est au joueur2 de deviner
	    break;
	case 2:  //vice versa
	    printf("Joueur 1 à toi de jouer!\n");
	    break;
   }

   int score;
   score=guess(val2,nbr_coup);  //récupère les points de la fonction guess()
   return score;  //renvoie le score pour la totalisation des points à la fin du jeu
}
int main()
{
   printf("Bienvenu dans le jeu Plus ou Moins!\n");
   int val;  //valeur à trouver
   //Initialisation de l'algorithme générateur de la fonction rand()
   srand(time(NULL));
   val=rand()%100;  //le %100 permet de limiter les chiffres entre 0 et 100
   int mode;
   printf("Mode:\n 1-Solo\n 2-2 joueurs\n");
   scanf("%d",&mode);
   if (mode==1)
   {
     int level;
     printf("Choisissez un mode de difficulté:\n 1-Facile\n 2-Moyen\n 3-Difficile\n");
     scanf("%d",&level);
     int limit,attempt;
     limit=difficulty(level);
     attempt=limit-guess(val,limit);  //représente les nombres de tentatives du joueur
     printf("Vous avez fait %d essais.\n",attempt);
   }
   else   //mode 2 joueurs
   {
     int nbr_tour;
     printf("Combien de tour voulez-vous faire?\n");
     scanf("%d",&nbr_tour);
     int score1,score2;  //score des joueur 1 et 2 respectivement
     for(int tour=1; tour<=nbr_tour; tour++)  //tour représente les rounds
     {
	printf("Round: %d\n\n",tour);
	score1+=turn(1);  //la fonction turn() retourne les scores de chaque joueur
	score2+=turn(2);  //et l'opérateur += va permettre de rajouter les scores à chaque round
     }
     if (score1>score2)
	printf("Scores: %d -- %d\nJoueur 1 a gagné!\n",score1,score2);
     else if (score1<score2)
	printf("Scores: %d -- %d\nJoueur 2 a gagné!\n",score1,score2);
     else
	printf("Scores: %d -- %d\nEgalité\n",score1,score2);
   }
}
