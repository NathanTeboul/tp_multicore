//T = 84 
//D = 68
//simCache152
//ecriture = WT
//remplacement bloc = FIFO

typedef struct s 
{
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
    for (i=0; i<lt;nbe; i++)
    {
        for (j=0; j<lt;assoc; j++)
        {
            cache[i][j].valid=0;
        }
    }
}
void check(arg1, arg2, arg3, fichier){
	if(arg1 == null){
		printf("taille du cache non rentrée");
		exit(0);
	}
	if(arg2 == null){
		printf("taille d'un bloc non rentrée");
		exit(0);
	}
	if(arg3 == null){
		printf("degré associativité non rentrée");
		exit(0);
	}
	if(fichier == null){
		printf("fichier vide");
		exit(0);
	}
}

void init (){

}

int main(int arg1, int arg2, int arg3, char fichier){
	
	//verif si donnees rentree en para
	check(arg1, arg2, arg3, fichier);

	int k =1024;			// taille d un octet
	int cs = arg1*k;		// taille totale de la cache (octet)
	int bs = arg2;			// taille d un bloc en octet
	int assoc = arg3;		// degre associativite
	int nbe cs/(bs*assoc);	// nombre d ensemble

	//print simple pour verif.
	printf("cache size : %d \nBloc size : %d \nAssociativite : %d \nNombre ensembles : %d\n", cs, bs, assoc, nbe);

    //creation du tableau correspondant au donné rentre et init a 0
    Cache cache;
    init_tab(nbe, assoc, cache);

    //compteur de read et write
    int nbr_r=0, nbr_w=0; 



    printf("il y a eu : %d lecture \n il y a eu : %d ecriture \n", nbr_r, nbr_w);
    return 1;
}