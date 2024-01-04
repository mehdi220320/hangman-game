//score mahoch mreguel choflo 7al

#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include <string.h>

 struct Player{
     int id , Ts [100], n , Ms;
    char nom[40];
    char psw[40];
};
struct cellule {
    struct Player p;
    struct cellule *next ;
    struct cellule *prev ;
} cellule ;
typedef struct cellule Cellule;

struct liste {
        Cellule * first;
        Cellule * last;

};
typedef struct liste Liste;
//------------------------Initialisation du la liste------------------------------------------
void Init(Liste *l)
{
   l->first = NULL;
   l->last = NULL;
}
//----------------------------------Insertion d'un joueur----------------------------------------
void addFin(Liste *l,struct Player pl)
{
   Cellule *p = malloc(sizeof(Cellule));
   if(!p) exit(EXIT_FAILURE);
    p->p = pl;
   p->prev = l->last;
   p->next = NULL;
   if(l->last){
        p->p.id=l->last->p.id+1;
        l->last->next = p;
   }
   else
   {
        p->p.id=1;
       l->first = p;
   }
   l->last = p;
}
//------------------------------Afficher la liste des joueurs-----------------------------------------

void Affiche(Liste l){
    if(l.first==NULL){
        printf("Empty");
    }else{
        Cellule *p=l.first;
        while(p!=NULL){
            AfficherPlayer(p->p);
            p=p->next;
        }
    }
}
//------------------------------------Supprimer un joueur-----------------------------------------------
void supprimer (Liste *l,char *s){
    Cellule *p;
    if(strcmp(l->first->p.nom,s)==0){
        p=l->first;
        l->first=p->next;
        free(p);
    }else if (strcmp(l->last->p.nom,s)==0){
        p=l->last;
        l->last=p->prev;
        l->last->next=NULL;
        free(p);
    }else{
        while(p!=NULL && strcmp(p->p.nom,s)!=0){
            p=p->next;
        }
        Cellule *prev=p->prev;
        Cellule *next=p->next;
        prev->next=next;
        next->prev=prev;
        free(p);
    }
}

//----------------------------------Creation d un joueur-----------------------------------------
struct Player CreatePlayer(){
    struct Player p;
    printf("Create your name :\n");
    scanf("%s",p.nom);
    printf("Create your password\n");
    scanf("%s",p.psw);
    p.n=0;
    return p;
}
//----------------------------------------------------------------------------------------------
void AfficherPlayer(struct Player p){
    printf("------------------------------------------------\n");
    printf("Player id : %i \n",p.id);
    printf("Name : %s \n",p.nom);
    if(p.n>0){
        printf("Scores are : \n");
        for(int i=0;i<p.n;i++){
            printf("Score %i : %i \n",i+1,p.Ts[i]);
        }
        printf ("His average is %i \n",p.Ms);
    }
    printf("------------------------------------------------\n");

}
//-------------------------------------------SHELL LOSE PRINT ---------------------------------------------------
void SLPrint(int i){
   char lose [][40] ={"================Y=\n",
                      "||\n",
                      "|| \n",
                      "||  \n",
                      "||   \n",
                      "||    \n",
                      "===================\n",
                      "================Y==\n",
                      "||              O \n",
                      "||    \n",
                      "||    \n",
                      "||    \n",
                      "||    \n",
                      "===================\n",
                      "================Y==\n",
                      "||              O \n",
                      "||             /|\\ \n",
                      "||               \n",
                      "||              \n",
                      "||    \n",
                      "===================\n",
                      "================Y==\n",
                      "||              O \n",
                      "||             /|\\ \n",
                      "||              | \n",
                      "||              \n",
                      "||    \n",
                      "===================\n",
                      "================Y=\n",
                      "||              O \n",
                      "||             /|\\ \n",
                      "||              | \n",
                      "||             / \\ \n",
                      "||    \n",
                      "===================\n",
                      };
     for(int j=7*(i-1);j<(i*7);j++){
                printf("%s",lose[j]);
    }
    if(i==5){
        printf("Loser \n");
    }
}
//-------------------------------------------Calcul du score -----------------
int calcul(char ch[],float i,bool t){
    if (t==true){
        return 100;
    }
    else{
        return (i-5)/strlen(ch)*100;
    }
}
//-------------------------------------------Moy du score -----------------
int moyScore(struct Player p){
    int s=0;
    if(p.n==1){
        return p.Ts[0];
    }
    for(int i=0;i<p.n;i++){
        s+=p.Ts[i];
    }
    return s/p.n;
}
//-----------------------------------------Start The Game -----------------
struct Player startTheGame(struct Player p,char s[]){
    char c,raw;
    char ts[50]="";
     for(int i=0;i<strlen(s);i++){
        ts[i]='-';
     }
    int k=1,j=0;
    int help=0;
    do{

        printf("------------------------------- \n");
        printf("write ur char : \n");
        scanf("\n%c",&c);
        if(strchr(s,c)!=NULL){
            for(int i=0;i<strlen(s);i++){
                if(s[i]==c){
                    ts[i]=c;
                }
            }
        }else{
            SLPrint(k);
            k++;
        }
        printf("%s \n",ts);
        j++;
        if((k==4)&&(help==0)){
            help+=1;
            printf("A quick help :\nThe word start with %c and it ends with %c\n",s[0],s[strlen(s)-1]);
        }
    }while((k<6)&&(strcmp(s,ts)!=0));
    if(strcmp(s,ts)==0){
            printf("Winner \n");
            p.Ts[p.n]=calcul(s,j,true);
    }
    else{
            printf("%s \n",s);
            p.Ts[p.n]=calcul(s,j,false);
    }
    p.n++;
    p.Ms=moyScore(p);
    return p;
}
//-------------------------------------------Update------------------------------
void Update(Liste *l,struct Player pl){
    if(l->first==NULL){
        printf("Empty\n");
    }else{
        Cellule *p=l->first;
        while(p!=NULL && strcmp(p->p.nom,pl.nom)!=0 ){
            p=p->next;
        }
        if(!p)
        {
            printf("Error Does not exist \n");
        }
        else{
                p->p=pl;
        }
    }
}
//-------------------------------------------Recherche --------------------------
struct Player  Recherche(Liste *l,char s[40]){
    struct Player pl;
    strcpy(pl.nom,"");
    strcpy(pl.psw,"");
    if(l->first==NULL){
        printf("Empty\n");
        return pl;
    }else{
        Cellule *p=l->first;
        while(p!=NULL && strcmp(p->p.nom,s)!=0 ){
            p=p->next;
        }
        if(!p)
        {
            return pl;
        }
        return p->p;
    }
}
//-----------------------------------Login---------------------------------------------
struct Player login (Liste *l){
    char username[40],psw[40];
    struct Player p;
    do{
        printf("Write your username (0 to go BACK)\n");
        scanf("%s",&username);
        p=Recherche(l,username);
    }while(strcmp(p.nom,username)!=0 && strcmp(username,"0")!=0 );
    if(strcmp(p.nom,username)==0){
        do{
            if(strcmp(p.nom,username)==0){
                printf("Write your password (0 to go BACK)\n");
                scanf("%s",&psw);
            }
            else
                printf("user does not exist \n");
            }
        while(strcmp(p.psw,psw)!=0 && strcmp(psw,"0")!=0 );
    }
    if(strcmp(psw,"0")==0 || strcmp(username,"0")==0  ) {
        strcpy(p.nom,"");
        strcpy(p.psw,"");
    }
    return p;
}

void Begin(){
     printf("-__-------------------------------------------------------------------------------------------------------------------------------\n");
    printf("|--\\------------------------------------------------------------------------------------------------------------------------------\n");
    printf("|-$$____----______---_______----______---______-____----______---_______----------______----______---______-____----______--------\n");
    printf("|-$$----\\--|------\\-|-------\\--/------\\-|------\\----\\--|------\\-|-------\\--------/------\\--|------\\-|------\\----\\--/------\\-------\n");
    printf("|-$$$$$$$\\--\\$$$$$$\\|-$$$$$$$\\|--$$$$$$\\|-$$$$$$\\$$$$\\--\\$$$$$$\\|-$$$$$$$\\------|--$$$$$$\\--\\$$$$$$\\|-$$$$$$\\$$$$\\|--$$$$$$\\------\n");
    printf("|-$$--|-$$/-      $$|-$$--|-$$|-$$--|-$$|-$$-|-$$-|-$$/-      $$|-$$--|-$$------|-$$--|-$$/-      $$|-$$-|-$$-|-$$|-$$----$$------\n");
    printf("|-$$--|-$$|--$$$$$$$|-$$--|-$$|-$$__|-$$|-$$-|-$$-|-$$|--$$$$$$$|-$$--|-$$------|-$$__|-$$|--$$$$$$$|-$$-|-$$-|-$$|-$$$$$$$$------\n");
    printf("|-$$--|-$$-\\$$----$$|-$$--|-$$-\\$$----$$|-$$-|-$$-|-$$-\\$$----$$|-$$--|-$$-------\\$$----$$-\\$$----$$|-$$-|-$$-|-$$-\\$$-----\\------\n");
    printf("-\\$$---\\$$--\\$$$$$$$-\\$$---\\$$-\\_$$$$$$$-\\$$--\\$$--\\$$--\\$$$$$$$-\\$$---\\$$-------\\_$$$$$$$--\\$$$$$$$-\\$$--\\$$--\\$$--\\$$$$$$$------\n");
    printf("------------------------------|--\\__|-$$----------------------------------------|--\\__|-$$----------------------------------------\n");
    printf("-------------------------------\\$$----$$-----------------------------------------\\$$----$$----------------------------------------\n");
    printf("---------------------------------\\$$$$$$-------------------------------------------\\$$$$$$----------------------------------------\n\n\n");
}
//--------------------------------CHERCHER UNE MOT RANDOMLY----------------------------
char* chooseRandomWord() {
    char* filename;
    int random= rand() % 3;
    switch(random){
        case 0:
            filename="FOOD.txt";
            printf(" It s a food word \n");
            break;
        case 1:
            filename="CAR.txt";
            printf(" It s a car word \n");
            break;
        case 2:
            filename="SPORT.txt";
            printf("It s a sport word \n");
            break;
    }
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }
    char buffer[50];
    int wordCount = 0;

    while (fscanf(file, "%s", buffer) == 1) {
        wordCount++;
    }

    srand(time(NULL));
    int randomIndex = rand() % wordCount;

    rewind(file);

    for (int i = 0; i < randomIndex; i++) {
        if (fscanf(file, "%s", buffer) != 1) {
            perror("Error reading file");
            exit(EXIT_FAILURE);
        }
    }

    // Close the file
    fclose(file);

    // Return the chosen word
    return strdup(buffer);
}


void main(){
    int i,j;
    struct Player p,p2,p3;
    Liste *l = malloc(sizeof(Liste));
    Init(l);
    Begin();
    do{
        printf("------------------------------------------------\n");
        printf("Press:\n1 for login \n2 for sign up \nElse for END \n");
        scanf("%i",&i);
        printf("------------------------------------------------\n");
        switch (i){
            case 1:
                p=login(l);
                if (strcasecmp(p.nom,"")!=0){
                    do{ printf("------------------------------------------------\n");
                        printf("1-Check list of players\n2-Start a game\n3-Check your account\n4-Delete your account\n0-Back\n");
                        scanf("%i",&j);
                        printf("------------------------------------------------\n");
                        printf("------------------------------------------------\n");

                        switch(j){
                            case 1: Affiche(*l);
                                    break;
                            case 2: p=startTheGame(p,chooseRandomWord());
                                    Update(l,p);
                                    break;
                            case 3: AfficherPlayer(p);
                                    break;
                            case 4: supprimer(l,p.nom);
                                    j=0;
                            default: printf("GG Nice game \n");j=0;
                        }
                    }while(j!=0);
                }
                break;
            case 2:
                p=CreatePlayer();
                addFin(l,p);
                printf("Welcome to our game %s\nyou can login now\n",p.nom);
                break;
            default :
                i=0;
        }
    }while(i!=0);

}
