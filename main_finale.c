#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<math.h>
#include<time.h>
#include <dirent.h>
#include <assert.h>
#include <openssl/sha.h>
#include"seance_1.h"
#include"seance_2.h"
#include"seance_3.h"
#include"seance_4.h"
#include"seance_5.h"
#include"seance_6.h"
#include"seance_7.h"



/********** !!!!!! Il faut supprimer les fichiers Block[i].txt dans le dossier Blockchain avant de lancer ce main une deuxième fois   ********/


int main()
{
	srand(time(NULL));

	//Génération des données
	generate_random_data(1000,5);

	//Création des 3 listes : Elécteurs, Candidats et Déclarations
	char *fichier_voters="keys.txt";
	char *fichier_candidates="candidates.txt";
	char *fichier_decl="declarations.txt";
	CellKey* voters=read_public_keys(fichier_voters);
	CellKey* candidates=read_public_keys(fichier_candidates);	
	CellProtected* decl=read_protected(fichier_decl);

	//Declarations
	CellProtected * tmpD=decl;
	CellKey* tmpV=voters;
	CellTree* tree=NULL;
	CellTree * tmpTree=NULL;
	int i=0;
	char nb[6];
	char fichier[20];

	while (tmpD){
		submit_vote(tmpD->data);	//Soumission d'un vote
		tmpD=tmpD->next;
		i++;				//Compte le nb de vote
		if (i%10==0){ 			//Chaque 10 votes, on crée un Block
			
			createBlock(tree,tmpV->data, 2);	//Creation de Block avec un author quelconque
			tmpV=tmpV->next;			
			
			
			//Mettre en place le nom du fichier dans lequel ecrire les Block : Block1.txt BLock2.txt ...
			sprintf(fichier,"%s","Block");
			sprintf(nb,"%d",i/10);
			strcat(fichier, nb);
			strcat(fichier,".txt");

			add_block(2,fichier);			//Ajout du Block dans un fichier dans le rep Blockchain
			tmpTree=tree;
			
			//Libération du tree retourné par read_tree() au tour de boucle précedent
			while (tmpTree){
				delete_list_protected(tmpTree->block->votes);
				tmpTree->block->votes=NULL;
				free(tmpTree->block->author);
				tmpTree=tmpTree->firstChild;
			}
			delete_tree(tree);
			
			//Lecture de l'arbre pour avoir accès à la valeur haché du dernier Block ajouté
			tree=read_tree();
		}
		
	}
	tmpTree=tree;
	while (tmpTree){
		delete_list_protected(tmpTree->block->votes);
		tmpTree->block->votes=NULL;
		free(tmpTree->block->author);
		tmpTree=tmpTree->firstChild;
	}
	delete_tree(tree);
	
	
	//Arbre Final
	tree=read_tree();
	
	//Affichage de l'abre
	tmpTree=tree;
	print_tree(tmpTree);

	//Recherche du gagnant et affichage de sa serialisation
	Key * winner=compute_winner_BT(tree,candidates,voters,7,1200);
	char * gagnant=key_to_str(winner);
	printf("\n\n-------------------- LE GAGNANT EST : %s ---------------------\n\n",gagnant);

	
	//Liberation de mémoire
	free(winner);
	free(gagnant);
	
	delete_list_protected(tree->block->votes);
	tmpTree=tree;
	while (tmpTree){
		tmpTree->block->votes=NULL;
		free(tmpTree->block->author);
		tmpTree=tmpTree->firstChild;
		
	}
	delete_tree(tree);
	
	delete_list_keys(voters);
	delete_list_keys(candidates);
	delete_list_protected(decl);
	
	return 0;
}
