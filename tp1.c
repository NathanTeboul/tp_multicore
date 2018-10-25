//T = 84 
//D = 68
//simCache152
//ecriture = WT
//remplacement bloc = FIFO

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//variable global
int nbr_r=0;
int nbr_w=0; 

int miss_r=0;
int miss_w=0;

int hit_r=0;
int hit_w=0;

typedef struct t_bloc t_bloc;
struct t_bloc{
	//si 0 alors vide, sinon non vide
    int valid;
    double index;
    double tag; 
};

//typedef struct t_bloc Cache;
void init_tab (int nbe, int assoc, t_bloc cache[nbe][assoc], int *incr){
	
    int i, j;
    for (i=0; i<nbe; i++){	
    	incr[i]=0;

        for (j=0; j<assoc; j++){
            cache[i][j].valid=0;
            cache[i][j].index=i;
            cache[i][j].tag=0;

        }
    }
}

/*
void check(int arg1, int arg2, int arg3, char fichier){
	if(arg1 == NULL){
		printf("taille du cache non rentrée");
		exit(0);
	}
	else{
		if(!isnumber(arg1)){
			printf("l'argument taille cache rentrer n'est pas un nombre");
			exit(0);
		}
	}
	if(arg2 == NULL){
		printf("taille d'un bloc non rentrée");
		exit(0);
	}else{
		if(!isnumber(arg2)){
			printf("l'argument taille bloc rentrer n'est pas un nombre");
			exit(0);
		}
	}
	if(arg3 == NULL){
		printf("degré associativité non rentrée");
		exit(0);
	}else{
		if(!isnumber(arg3)){
			printf("l'argument associativité rentrer n'est pas un nombre");
			exit(0);
		}
	}
	if(fichier == NULL){
		printf("fichier vide");
		exit(0);
	}
}
*/

void affichage_tab(int nbe, int assoc, t_bloc cache[nbe][assoc]){
	printf("-----------------------------------------\n");
	int i, j;
	for (i=0; i<7; i++){	
		printf("ligne %d : \n",i);
        for (j=0; j<assoc; j++){
        	printf("index :%lf , tag :%lf , valide : %d \n", cache[i][j].index, cache[i][j].tag,cache[i][j].valid);
        }
    }
}

void affichage_tab_temp(int *incr){
	printf("-----------------------------------------\n");
	printf("tableau tempo :\n");
	for (int i=0; i<7; i++){
		printf("ligne %d : %d \n",i, incr[i]);
    }	
}

void affichage_rw(){
	printf("-----------------------------------------\n");
    printf("il y a eu : %d lecture \nil y a eu : %d ecriture \n", nbr_r, nbr_w);
}

void affichage_miss(){
	printf("-----------------------------------------\n");
	printf("il y a eu : %d miss en ecriture \nil y a eu : %d miss en lecture \n", miss_w, miss_r);
}

void affichage_hit(){
	printf("-----------------------------------------\n");
	printf("il y a eu : %d hit en ecriture \nil y a eu : %d hit en lecture \n", hit_w, hit_r);
}

void traitement (FILE *tr,int cs, int bs, int assoc, int nbe, t_bloc cache[nbe][assoc], int *incr){

	//calcul
	int numbloc=0;
	int index=0;
	int tag=0;
	int m = 0;
	int h = 0;

    int place_col=0;

	// localisation dans le bloc (bl doit etre < assoc)
	int bl = 0;

	// lecture du fichier
	char car;
	char adr[10];
	
	//printf("-----------------------------------------\n");

    while (!feof(tr)){
        fscanf (tr, "%c %s\n", &car, &adr[0]);
        // calcul du nombre de bloc
        numbloc = strtol(adr,NULL,16) / bs;
        //calcul de l'index (numero de la ligne du tableau Cache)
        index = numbloc % nbe;
        // calcul de l'etiquette
        tag = numbloc / nbe;
        // cherche dans les blocs de la ligne si le tag existe
        int a =0;
        int trouve=0;

        //test
        //printf("numbloc = %d, index = %d, tag = %d \n", numbloc,index,tag);
	    //printf("%c %s \n", car, adr);

	    //gestion du r et w
	    if(car=='R'){
	    	nbr_r++;
	    }
	    if(car=='W'){
	    	nbr_w++;
	    }

        // on cherche si la donnee est deja dans le cache
        while((a<assoc) && (trouve == 0)){
            //si le bloc est vide ou si le tag n'existe pas on incremente la valeur a
            if((cache[index][a].valid == 0) || (cache[index][a].tag != tag)){
            	a++;
            }
            else{
                // sinon (on trouve) on arrete la recherche et on incremente le compteur de hits
                trouve = 1; 
                h++;
                if(car=='R'){
	    			hit_r++;
	    		}
	    		if(car=='W'){
	    			hit_w++;
	    		}
            }
        }
        
        // si la donnee n'est pas deja dans le cache, il faut l'ajouter
        if(trouve==0){
            //incrementer le nombre de defaut (miss) --> il faut donc ajouter la donnée au cache
            m++;
            if(car=='R'){
	    		miss_r++;
	    	}
	    	if(car=='W'){
	    		miss_w++;
	    	}

            place_col=(incr[index]%assoc);

            cache[index][place_col].valid=1;
            cache[index][place_col].tag=tag;

            incr[index]++;
        }
    }
}

void test(FILE *tr){
	// lecture du fichier
	char car;
	char adr[10];
	int numbloc;
	int bs = 64;

    while (!feof(tr)){  
    	fscanf (tr, "%c %s \n", &car, &adr[0]);

		printf("%c %s \n", car, adr);

		numbloc = strtol(adr,NULL,16) / bs;
		
			printf("valeur du atoi de adre : %ld \n", strtol(&adr[0],NULL,16));
		
		printf("numbloc %d \n", numbloc);
		if(car == 'R'){
	    	nbr_r++;
	    }
	    else if(car == 'W'){
	    	nbr_w++;
	    }

	}
}

int main (int argc,char **argv){

	//argv[0]= nomfile
	//argv[1]= cs
	//argv[2]= bs
	//argv[3]= assoc
	//argv[4]= filepara
	int arg1 = atoi(argv[1]);
	int arg2 = atoi(argv[2]);
	int arg3 = atoi(argv[3]);

	//verif si donnees rentree en para
	//check(arg1, arg2, arg3, argv[4]);

	int k =1024;			// taille d un octet
	//int cs = arg1*k;		// taille ttl cache si on ne mult pas par 1024
	int cs = arg1;			// taille totale de la cache (octet)
	int bs = arg2;			// taille d un bloc en octet
	int assoc = arg3;		// degre associativite
	int nbe = cs/(bs*assoc);	// nombre d ensemble
	FILE *tr= NULL;			//creation d une variable file

	//print simple pour verif.
	printf("cache size : %d \nBloc size : %d \nAssociativite : %d \nNombre d'ensembles : %d\n", cs, bs, assoc, nbe);

    //creation du tableau correspondant au donne rentre et init a 0 de celui ci
    t_bloc cache[nbe][assoc];

    //tableau de int pour le compteur.
    int incr[nbe];

    //init des 2 tableau
    init_tab(nbe, assoc, cache, incr);
 
    //ouverture du fichier passer en para avec l arg lecture seule
	tr = fopen(argv[4], "r");

	//traitement du fichier
	//traitement(tr, cache,cs, bs, assoc, nbe);
	traitement (tr,cs,bs,assoc,nbe,cache,incr);

	//test(tr);
	
	//affichages
	affichage_rw();	
	affichage_miss();
	affichage_hit();

	//affichage_tab_temp(incr);
	//affichage_tab(nbe,assoc,cache);

	//fermeture fichier
	fclose(tr), tr=NULL;

    return 999;
}