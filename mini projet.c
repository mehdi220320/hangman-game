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
            printf("Score %i : %i \n",i,p.Ts[i]);
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
        return (strlen(ch)/i)*100;
    }
    else{
        return (i-5)/strlen(ch)*50;
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
        //printf("test\n");
        return p->p;
    }
}
//--------------------------------------------------------------------------------
struct Player login (Liste *l){
    char username[40],psw[40];
    struct Player p;
    do{
        printf("Write your username (0 to go BACK)\n");
        scanf("%s",&username);
        p=Recherche(l,username);
        printf("username : %s \n",Recherche(l,username).nom);
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
    /*
    printf("---/$$---------/$$---------------------------/$$----------------------------------------------------------------------------------\n");
    printf("-/$$$$--------|-$$--------------------------|__/----------------------------------------------------------------------------------\n");
    printf("|_--$$--------|-$$--------/$$$$$$---/$$$$$$--/$$-/$$$$$$$-------------------------------------------------------------------------\n");
    printf("--|-$$-/$$$$$$|-$$-------/$$__--$$-/$$__--$$|-$$|-$$__--$$------------------------------------------------------------------------\n");
    printf("--|-$$|______/|-$$------|-$$--\\-$$|-$$--\\$$|-$$|-$$--\\$$--------------------------------------------------------------------------\n");
    printf("--|-$$--------|-$$------|-$$--|-$$|-$$--|-$$|-$$|-$$--|-$$------------------------------------------------------------------------\n");
    printf("--|-$$--------|-$$------|-$$--|-$$|-$$--|-$$|-$$|-$$--|-$$------------------------------------------------------------------------\n");
    printf("-/$$$$$$------|-$$$$$$$$|--$$$$$$/|--$$$$$$|-$$|-$$--|-$$-------------------------------------------------------------------------\n");
    printf("|______/------|________/-\\______/--\\____--$$|__/|__/--|__/------------------------------------------------------------------------\n");
    printf("-----------------------------------/$$--\\$$---------------------------------------------------------------------------------------\n");
    printf("----------------------------------|--$$$$$$/--------------------------------------------------------------------------------------\n");
    printf("-----------------------------------\\______/---------------------------------------------------------------------------------------\n\n\n");
    printf("--/$$$$$$----------/$$$$$$--/$$---------------------------/$$---/$$---------------------------------------------------------------\n");
    printf("-/$$__--$$--------/$$__--$$|__/--------------------------|-$$--|-$$---------------------------------------------------------------\n");
    printf("|__/--\\-$$-------|-$$--\\__/-/$$--/$$$$$$--/$$$$$$$-------|-$$--|-$$--/$$$$$$------------------------------------------------------\n");
    printf("--/$$$$$$//$$$$$$|--$$$$$$-|-$$-/$$__--$$|-$$__--$$------|-$$--|-$$-/$$__--$$-----------------------------------------------------\n");
    printf("-/$$____/|______/-\\____--$$|-$$|-$$--\\$$|-$$--\\$$------|-$$--|-$$|-$$\\$$----------------------------------------------------------\n");
    printf("|-$$--------------/$$--\\$$|-$$|-$$--|-$$|-$$--|-$$------|-$$--|-$$|-$$--|-$$------------------------------------------------------\n");
    printf("|-$$$$$$$$-------|--$$$$$$/|-$$|--$$$$$$$|-$$--|-$$------|--$$$$$$/|-$$$$$$/------------------------------------------------------\n");
    printf("|________/--------\\______/-|__/-\\____--$$|__/--|__/-------\\______/-|-$$____/------------------------------------------------------\n");
    printf("--------------------------------/$$--\\$$--------------------------|-$$------------------------------------------------------------\n");
    printf("-------------------------------|--$$$$$$/--------------------------|-$$-----------------------------------------------------------\n");
    printf("--------------------------------\\______/---------------------------|__/-----------------------------------------------------------\n");
    */
}
//------------------------------------------------------------
char* chooseRandomWord(const char* filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    char buffer[50];
    int wordCount = 0;

    // Count the number of words in the file
    while (fscanf(file, "%s", buffer) == 1) {
        wordCount++;
    }

    // Generate a random index to choose a word
    srand(time(NULL));
    int randomIndex = rand() % wordCount;

    // Reset file pointer to the beginning of the file
    rewind(file);

    // Get the word at the random index
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
        printf("press 1 for login // 2 for sign up // Else for END \n");
        scanf("%i",&i);
        printf("------------------------------------------------\n");
        switch (i){
            case 1:
                p=login(l);
                if (strcasecmp(p.nom,"")!=0){
                    do{ printf("------------------------------------------------\n");
                        printf("1-Check list of players\n2-Start a game\n3-Check your account\n0-Back\n");
                        scanf("%i",&j);
                        printf("------------------------------------------------\n");
                        printf("------------------------------------------------\n");

                        switch(j){
                            case 1: Affiche(*l);
                                    break;
                            case 2: p=startTheGame(p,chooseRandomWord("words.txt"));
                                    Update(l,p);
                                    break;
                            case 3: AfficherPlayer(p);
                                    break;
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
