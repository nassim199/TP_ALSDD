#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#define tailleDico 3000
//***************************************************************
//implementation du modele de LLC de la structure du dictionnaire
//***************************************************************

//le maillon contient le mot et l'indice et l'addresse du maillon suivant

typedef struct Maillon { char* mot ; int ind ; struct Maillon *next; } Maillon;

void allouer (Maillon **nouveau)
{
 	*nouveau = (Maillon*)malloc(sizeof(Maillon));
}

void aff_adr(Maillon *p, Maillon *q)
{
	p->next = q ;
}

Maillon *suivant (Maillon *p)
{
	return p->next;
}

void aff_ind(Maillon *p , int indice)
{
	p->ind = indice ;
}

int indice (Maillon *p)
{
	return p->ind ;
}

void aff_mot (Maillon *p , char* nouveauMot)
{
    p->mot = nouveauMot;
}

char* mot_maillon (Maillon *p)
{
    return p->mot;
}

void liberer (Maillon** ancien)
{
	free(*ancien);
	*ancien=NULL;
}

//************************************
//fonctions pour creer le dictionnaire
//************************************

int random(int a,int b)
{ //random genere un nombre aleatoire entre a inclu et b exclu
    int c;
    c = rand()%(b-a) + a;
    return c;
}
int alealong(int a ,int b)
{ //generer la taille du mot aleatoirement de taille entre a et b tout les deux inclus
    int c;
    if (a<=b) {
        c = random(a,b+1);
        return c;
    } else {
        exit(0);
    }
}
char alealettre(int a, int b)
{ //generer une lettre aleatoire d'ordre entre a et b
    char c;
    if (a<=b && a>=1 && b<=26) {
        c = random(a+96,b+97);
        return c;
    } else {
        exit(0);
    }
}
char* aleamot(int a, int b)
{ //genere un mot aleatoirement de taille entre a et b, retourne un pointeur vers la chaine de caractere
    char *mot=NULL;
    //on genere aleatoirement un nombre entre a et b
    int i = alealong(a,b);
    //on alloue en memoire une chaine de caractere de taille i+1
    mot = malloc((i+1)*sizeof(char));

    for (int j=0 ; j<i ; j++){ //pour chaque case on genere une lettre aleatoire
        mot[j] = alealettre(1,26);
    }
    mot[i]='\0';
    return mot;
}
int def(char* mot)
{ //donne la definition d'un mot
    int i , resu=0 , inter;

    //on parcourt la chaine de caractere
    for(i=0 ; mot[i]!='\0' ; i++) {
        //les caracteres miniscules en ascii commencent par 97 (a) donc on soustrait 96 pour avoir l'ordre
        inter = mot[i] - 96;
        resu += inter ;
    }

    return resu;
}

//type Dico est les mot avec sa definition

typedef struct Dico { char* mot ; int def ;} Dico;

//procedure de creation du dico

void creationDico (Dico dico[tailleDico])
{ //le dictionnaire est un tableau de Dico de taille tailleDico
   int i ;

   for(i=0 ; i<tailleDico ; i++) {
    //pour chaque case on associe un mot aleatoire et puis sa definition
    dico[i].mot = aleamot(2,8);
    dico[i].def = def(dico[i].mot);
   }
}

//********************************************************************************************************
//creation de la structure de base et la structure ameliore , et les fonctions de recherche et d'insertion
//********************************************************************************************************

void accesLong(Maillon *t,int L , Maillon **p, Maillon **q)
{ //donne le premier mot de longueure superieur ou egal a L dans q si il existe et NULL sinon, p est le precedent de q
	*q=t;
	*p=NULL;
	while ( (*q)!=NULL && strlen(mot_maillon(*q))<L) {
	    (*p)=(*q);
	    (*q)=suivant(*q);
	}
}

void accesLongcpt(Maillon *t,int L , Maillon **q , int *cpt )
{ //une extension de la procedure de accesLong , elle donne le nombre de comparaions faites dans le parcours
	*q=t;
	*cpt= 1 ;
	while ( (*q)!=NULL && strlen(mot_maillon(*q))<L) {
	    (*q)=suivant(*q);
	    (*cpt)++;
	}
}

void insertion(char* mot , Maillon **t , int i)
{ //insere un mot dans une liste par longueur
    int L = strlen(mot) ;

    Maillon *r = NULL  , *p = NULL, *q = NULL;
    accesLong(*t, L , &p , &q);
    allouer(&r);
    aff_adr(r,q);
    aff_ind(r,i); //i est l'indice
    aff_mot(r,mot);
    if (q==(*t)) {
    	*t = r;
    } else {
    	aff_adr(p,r);
    }

}

void dicoStructure (Dico dico[tailleDico], Maillon* T[26])
{ //creation de la structure du dictionnaire
    int i , ordre;
    for (i=0 ; i <tailleDico ; i++)
    {
     //on cherche l'ordre de la premiere lettre en prenant 'a' a l'ordre 0
     ordre = dico[i].mot[0] -97;
     //on insere le mot dans le structure
     insertion(dico[i].mot , &T[ordre] , i);
    }
}
void dicoStructurePlus ( Dico dico[tailleDico] , Maillon* T2 [26][26])
{   // creation de la structure améliorée
    int i , ordrelig , ordrecol ;
    for (i=0 ; i < tailleDico ;i++ )
    {
        ordrelig = dico[i].mot[0]-97;
        //ordrelig est l'ordre de la premiere lettre du mot
        ordrecol = dico[i].mot[1]-97;
        //ordrecol est l'ordre de la deuxieme lettre du mot
        insertion (dico[i].mot , &T2[ordrelig][ordrecol] , i );
        // on insere le mot dans la nouvelle structure selon l'ordre de ses deux premiers lettres
    }

}

void Recherche (  char* mot ,  int  *i , Maillon* T[26] , int *cpt  )
{ //recherche un mot dans la structure de base , si il existe renvoie son indice + le nombre de comparaisons faites
    int ordre ;
    ordre = mot[0] - 97 ;
    *cpt = 1 ;
    // cpt est le compteur de nombre de comparaisons faites pour la recherche
    Maillon* p = T[ordre] ;
    accesLongcpt(T[ordre], strlen(mot), &p , cpt);
    // accés au premier maillon qui a un  mot de longueure superieur ou egal a la longueur de MOT
    while (  p!=NULL && strcmp( mot , mot_maillon(p))!= 0 && strlen(mot)== strlen(mot_maillon(p))  )
    { // on parcourt le reste de la liste jusqu'a trouver le mot si il existe
        (*cpt)++ ;
        p=suivant(p);
    }
    if ( p == NULL || strcmp(mot , mot_maillon(p))!= 0 )
    { // donc le mot n'existe pas
        *cpt = 0 ;
        *i = -1 ;
        // cpt=0 et i=-1 indique que le mot n'existe pas
    }
    else
    {
        *i = indice(p) ; // mot est dans la maillon  pointé par p
    }
}

void RecherchePlus (  char* mot ,  int  *i , Maillon* T2[26][26] , int *cpt  )
{ //meme role que recherche mais dans la structure ameliore
    int ordrecol , ordrelig ;
    ordrelig = mot[0] - 97 ;
    ordrecol = mot[1] - 97 ;
    *cpt = 1 ;
    Maillon* p = T2[ordrelig][ordrecol] ;
    accesLongcpt(T2[ordrelig][ordrecol], strlen(mot), &p , cpt);
    while (  p!=NULL && strcmp( mot , mot_maillon(p))!= 0 && strlen(mot)==strlen(mot_maillon(p))  )
    {
        (*cpt)++ ;
        p=suivant(p);
    }
    if ( p == NULL || strcmp(mot , mot_maillon(p))!= 0 )
    {
        *cpt = 0;
        *i = -1;
    }
    else
    {
        *i = indice(p) ;
    }
}

void RechercheMultiple(char* mot,Dico dico[tailleDico],Maillon* T[26],Maillon* T2[26][26] )
{//affiche tout les mots qui commencent par la chaine de caractere mot , la chaine doit terminer avec un asterisque
    int l=strlen(mot),k=0;
    if (mot[l-1]=='*') {
        //on verifie que la chaine se termine avec '*'
        mot[l-1]='\0';
        //on supprime le dernier caractere '*'
        l--;
        int ord1=mot[0]-97;
        Maillon *p,*q,*t;
        if (l==1){
            //si il n'a qu'un seul caractere on utilise la premiere structure
            t=T[ord1];
        } else {
            //sinon on utilise la deuxieme qui est mieux
            int ord2=mot[1]-97;
            t=T2[ord1][ord2];
        }
        accesLong(t,l,&p,&q);
        if (q!=NULL) {
            //donc on a des mots qui ont une taille superieure ou egal a l (la taille de mot)
            do{
               //on parcourt tout le reste de la liste
               if (strncmp(mot,mot_maillon(q),l)==0) {
                    //si le debut du mot maillon est le meme que le mot on l'affiche
                    printf("%s : %d \n",mot_maillon(q),dico[indice(q)].def);
                    k++;
               }
               q=suivant(q);
            } while(q!=NULL);
            if (k==0) printf("Aucun resultat..\n");
            //si aucun mot n'a ete affiche donc y'a aucun resultat
        } else {
            //aucun mot de cette taille n'existe
            printf("Aucun resultat..\n");
        }
    }
}

void RechercheMots(char* mot,Dico dico[tailleDico],Maillon* T[26],Maillon* T2[26][26])
{//affiche tout les mots qui commencent par la chaine de caractere mot ou un mot exacte + la definition
    int l=strlen(mot);
    int i,j,cpt;
    Maillon* p;
    if (l<=8 && l>=1){
        //on verifie que la taille du mot est entre 1 et 8
        char lastChar = mot[l-1];
        if (lastChar=='*' && l!=1) {
            //si le dernier caractere est '*' et contient au moins un caractere
            RechercheMultiple(mot,dico,T,T2);
        } else {
            //on cherche un mot exacte
            if (l!=1){
                //le mot qu'il cherche a au moins 2 caracteres
                RecherchePlus(mot,&i,T2,&cpt);
                if ( cpt ) {
                    //si le mot existe
                    printf("%s : %d \n",mot,dico[i].def);
                } else {
                    //donc le mot n'existe pas (cpt=0)
                    printf("Aucun resultat..\n");
                }
            } else {
                if(mot[0]!='*'){
                    printf("Aucun resultat.. \n");
                } else {
                    //puisque mot='*' donc on affiche tout les mots existants
                    for(i=0;i<26;i++) {
                        for (j=0;j<26;j++){
                            p=T2[i][j];
                            afficher(p,dico);
                        }
                    }
                }
            }
        }
    } else {
        if (l>8) {
            printf("un mot ne doit pas depasser 8 caracteres\n");
        } else {
            printf("le mot doit contenir au moins un caractere\n");
        }
    }
}

//**************************************************************
//la procedure qui fait la comparaison entre les deux structures
//**************************************************************

void RechercheCmp (Dico dico[tailleDico],Maillon* T[26],Maillon* T2[26][26])
{//parcourt le tableau dico et fait la recherche de chaque mot dans les deux structures et ecrit les resultats dans
 // un fichier en format xml (pour pouvoir les exploiter directement avec excel)
 int cpt1,cpt2,i,k;
 FILE* fichier;
 //les ecritures faites dans le fichier je ne vais pas les expliquer car se sont des details du langage xml
 //qui va me servir juste pour importet les donnees dans le fichier excel
 fichier = fopen("recherche_cmp.xml","w");
 fprintf(fichier,"<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"yes\" ?>\n<dico>\n");
 for (i=0;i<tailleDico;i++) {
    Recherche(dico[i].mot,&k,T,&cpt1);
    RecherchePlus(dico[i].mot,&k,T2,&cpt2);
    fprintf(fichier,"<mot>\n   <indice>%d</indice>\n   <cpt1>%d</cpt1>\n   <cpt2>%d</cpt2>\n</mot>\n",i,cpt1,cpt2);
    //on ecrit dans le fichier l'indice accompagne avec le nombre de comparaisons dans les deux structures
 }
 fprintf(fichier,"</dico>");
 fclose(fichier);
}
//****************
//autres fonctions
//****************

void afficher(Maillon *p, Dico dico[tailleDico]) {
while (p != NULL) {
    printf("%s : %d \n",mot_maillon(p),dico[indice(p)].def);
    p=suivant(p);
}
}
void viderBuffer()
{
    int c = 0;
    while (c != '\n' && c != EOF)
    {
        c = getchar();
    }
}

int lire(char *chaine, int longueur)
{
    char *positionEntree = NULL;

    if (fgets(chaine, longueur, stdin) != NULL)
    {
        positionEntree = strchr(chaine, '\n');
        if (positionEntree != NULL)
        {
            *positionEntree = '\0';
        }
        else
        {
            viderBuffer();
        }
        return 1;
    }
    else
    {
        viderBuffer();
        return 0;
    }
}
int main()
{
    int a=1;
    char motRecherche[9];
    Dico dico[tailleDico];
    Maillon* T[26]={NULL};
    Maillon* T2 [26][26]={NULL};
    printf("Bienvenue \nSi vous voulez generer un dictionnaire aleatoire tapez entree..");
    getchar();
    printf("Dictionnaire en cours de creation ...");
    srand(time(NULL));
    creationDico(dico);
    dicoStructure(dico ,T);
    dicoStructurePlus(dico , T2 );
    do {
    if (a==1 || a==2){
        system("cls");
        printf("\nMenu : \n\n 1 - Lancer une recherche. \n 2 - Comparer l'efficacite des deux structures crees. \n 3 - EXIT.");
    }
    printf("\n\n Votre choix est : ");
    scanf("%d",&a);
    viderBuffer();
    if (a==1) {
        system("cls");
        printf("Un petit man :\n");
        printf(" Si vous voulez chercher la definition d'un mot exacte tapez le mot exacte\n Attention la taille du mot doit etre entre 2 et 8\n");
        printf("\n Pour chercher afficher tout les mots qui commencent par une chaine de caractere ajoutez un asterisque a la fin de la chaine '*'\n");
        printf(" Par exemple si vous voulez chercher tout les mots qui commencent par 'a' ou 'ph' vous tapez 'a*' ou 'ph*'\n");
        printf(" Si vous tapez seulement '*' tout les mots seront affiches\n");
        printf("pour lancer votre recherche tapez entree..\n");
        getchar();
        printf("Le mot est : ");
        lire(motRecherche,9);
        RechercheMots(motRecherche,dico,T,T2);
        printf("\nPour retourner au menu tapez entree..");
        getchar();
    } else if (a==2) {
        RechercheCmp(dico,T,T2);
        system("cls");
        printf("\nRemarque : Pour pouvoir voir le resultat et le graphe de comparaison vous devez posseder le logiciel excel\n");
        printf("Lorsque le fichier excel s'ouvre vous devrez mettre a jour les donnees\n");
        printf("Pour cela vous allez a developpeur et dans le champs XML 'appuyer sur actualiser les donnees'\n");
        printf("(Si vous ne voyez pas l'onglet developpeur allez dans options et puis dans Onglets principaux et vous cochez 'developpeur')\n");
        printf("(Si le bouton de 'actualiser les donnees' n'est pas cliquable assurez vous de selectionner d'abords sur le tableau des donnees)\n");
        printf("Si vous voudrez revenir en interaction avec la console vous devez d'abords fermer le fichier excel\n");
        printf("Appuyer sur entree pour ouvrir le fichier excel ..");
        getchar();
        system("cls");
        printf("Veuillez patienter un peu s'il vous plait !");
        system("analyseRecherche.xlsx");
    } else if (a!=3) {
        printf("Veuillez choisir une des options possibles seulement .");
    }
    } while (a!=3);
    return 0;
}
