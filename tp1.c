//T = 84 
//D = 68
//simCache152
//ecriture = WT
//remplacement bloc = FIFO

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct s 
{
	//si 0 alors valid, sinon non valid
    int valid;
    double index;
    double numbloc;
    double tag; 
}
bloc;

typedef bloc Cache [nbe][assoc];

void init_tab (int nbe, int assoc, Cache cache)
{
    int i, j;
    for (i=0; i<nbe; i++)
    {
        for (j=0; j<assoc; j++)
        {
            cache[i][j].valid=0;
           // Pas besoin de les init je crois
            //cache[i][j].index=0;
            //cache[i][j].numbloc=0;
            //cache[i][j].tag=0;;
        }
    }
}

void check(int arg1, int arg2, int arg3, char fichier){
	if(arg1 == Null){
		printf("taille du cache non rentrée");
		exit(0);
	}
	else{
		if(!isnumber(arg1)){
			printf("l'argument taille cache rentrer n'est pas un nombre");
			exit(0);
		}
	}
	if(arg2 == Null){
		printf("taille d'un bloc non rentrée");
		exit(0);
	}else{
		if(!isnumber(arg2)){
			printf("l'argument taille bloc rentrer n'est pas un nombre");
			exit(0);
		}
	}
	if(arg3 == Null){
		printf("degré associativité non rentrée");
		exit(0);
	}else{
		if(!isnumber(arg3)){
			printf("l'argument associativité rentrer n'est pas un nombre");
			exit(0);
		}
	}
	if(fichier == Null){
		printf("fichier vide");
		exit(0);
	}
}

//nop
void choix_affichage(Cache cache){
	int nombre = 0;
	int res;

	do{
		printf("entrée 1 si vous voulez afficher le tableau de cache, sinon 0")
		res = scanf("%d", &nombre);

	}while( res == 1 || res == 0 );

	if(res == 1){
		affichage_tab(cache);
	}
}

//ok
void affichage_tab(Cache cache){
	int i, j;
    for (i=0; i<lt;nbe; i++)
    {
        for (j=0; j<lt;assoc; j++)
        {
        	printf("index :%d ,numbloc :%d , tag :%d \n", cache[i][j].index, cache[i][j].numbloc, cache[i][j].tag);
        }
    }
}

//ok
void affichage(Cache cache,int nbr_r, int nbr_w ){

    printf("il y a eu : %d lecture \n il y a eu : %d ecriture \n", nbr_r, nbr_w);
    choix_affichage(cache);
}

void traitement (FILE *tr, Cache cache,int Cs, int Bs, int Assoc, int Nbe){
	int cs = Cs;
	int bs = Bs;
	int assoc = Assoc;
	int nbe= Nbe;
	//calcul
	int numbloc, index, tag;
	int m = 0;
	int h = 0;
	// localisation dans le bloc (bl doit etre < assoc)
	int bl = 0;
	// lecture du fichier
	char car;
	char adr;

    while (!feof(tr))
    {
        fscanf (f, "%c %X\n", &car, &adr);
        // calcul du nombre de bloc
        numbloc = adr / bs;
        //calcul de l'index (numero de la ligne du tableau Cache)
        index = numbloc % nbe;
        // calcul de l'etiquette
        tag = numbloc / nbe;
        // cherche dans les blocs de la ligne si le tag existe
        int a =0;
        int trouve=0;
	    
        // on cherche si la donnee est deja dans le cache
        while ((a<assoc) &  (trouve == 0))
        {
            //si le bloc est vide ou si le tag n'existe pas on incremente la valeur a
            if  ((cache[index][a].valid == 0) || (cache[index][a].tag != tag)) 
                {a++;}
            else
                // sinon (on trouve) on arrete la recherche et on incremente le compteur de hits
                {trouve = 1; h++;}
        }
        
        
               // si la donnee n'est pas deja dans le cache, il faut l'ajouter
        if (trouve==0) // defaut..
            //incrementer le nombre de defaut (miss) --> il faut donc ajouter la donnée au cache
        {
            m++;
            if (bl<assoc){
            cache[index][bl].valid = 1;
            cache[index][bl].tag = tag;
            bl++;
            }
            else {
                // methode FIFO
            }
        }
    }

    //return cache;
}

int main(int arg1, int arg2, int arg3, char fichier){
	
	//verif si donnees rentree en para
	check(arg1, arg2, arg3, fichier);

	int k =1024;			// taille d un octet
	int cs = arg1*k;		// taille totale de la cache (octet)
	int bs = arg2;			// taille d un bloc en octet
	int assoc = arg3;		// degre associativite
	int nbe cs/(bs*assoc);	// nombre d ensemble	
	FILE* tr= Null;			//creation d une variable file

	//print simple pour verif.
	printf("cache size : %d \nBloc size : %d \nAssociativite : %d \nNombre ensembles : %d\n", cs, bs, assoc, nbe);

    //creation du tableau correspondant au donne rentre et init a 0 de celui ci
    Cache cache;
    init_tab(nbe, assoc, cache);

    //compteur de read et write
    int nbr_r=0, nbr_w=0; 

    //ouverture du fichier passer en para avec l arg lecture seule
	tr = fopen(fichier, "r");

	//traitement du fichier
	traitement(tr, cache,cs, bs, assoc, nbe);

	//affichage
	affichage(cache, nbr_r, nbr_w);

	//fermeture fichier
	fclose(tr), tr=Null;

    return 1;
}