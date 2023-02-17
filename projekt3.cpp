#include <iostream>
#include <cstring>
using namespace std;
struct SBOARD{
    int X,Y,k,activePlayer;
    int firstPlayerPositions=0;
    int secondPlayerPositions=0;
    int emptySpaces=0;
};
int minmin(int one,int two){
    if (one>=two){
        return two;
    } else{
        return one;
    }
}
int maxmax(int one,int two){
    if (one>=two){
        return one;
    } else{
        return two;
    }
}
void reading(SBOARD *infoAboutBoard,char **board){
    char number='0';
    for (int i = 0; i < infoAboutBoard->Y; i++) {
        for (int j = 0; j < infoAboutBoard->X; j++) {
            cin>>number;
            if (number=='1') infoAboutBoard->firstPlayerPositions+=1;
            else if (number=='2')infoAboutBoard->secondPlayerPositions+=1;
            else if(number=='0')infoAboutBoard->emptySpaces+=1;
            board[i][j]=number;
        }
    }
}
int opponent(int player){
    int opponent=0;
    if (player==1)opponent=2;
    else if(player==2)opponent=1;
    return opponent;
}
int checkingWins(char **board,SBOARD infoAboutBoard,int activePlayer){//sprawdzanie czy dany gracz wygrał
    int repeat=1, repeat2=1;
    //poziomo

    for (int i = 0; i <infoAboutBoard.Y ; i++) {
        repeat=1;
        for (int j = 0; j < infoAboutBoard.X-1; j++) {
            if (board[i][j]==board[i][j+1]&&board[i][j]==(char)(activePlayer+48)) {
                repeat += 1;
            }
            else
                repeat=1;
            if (repeat==infoAboutBoard.k){
                return 1;
            }
        }
    }

    for (int i = 0; i <infoAboutBoard.X ; i++) {
        repeat=1;
        for (int j = 0; j < infoAboutBoard.Y-1; j++) {
            if (board[j][i]==board[j+1][i]&&board[j][i]==(char)(activePlayer+48)) {
                repeat += 1;
            }
            else
                repeat=1;
            if (repeat==infoAboutBoard.k){
                return 1;}
        }
    }
    for (int i = 0; i <= infoAboutBoard.Y-infoAboutBoard.k; i++) {
        for (int j = 0; j <= infoAboutBoard.X-infoAboutBoard.k; j++) {
            repeat=1;
            repeat2=1;
            for (int m = 1; m < infoAboutBoard.k; m++) {
                if (board[i+m-1][j+m-1]==board[i+m][j+m]&&board[i+m-1][j+m-1]==(char)(activePlayer+48))
                    repeat+=1;
                else
                    repeat=1;
                if (repeat==infoAboutBoard.k){
                    return 1;
                }
                if (board[i+m-1][infoAboutBoard.X-j-m]==board[i+m][infoAboutBoard.X-j-m-1]&&board[i+m-1][infoAboutBoard.X-j-m]==(char)(activePlayer+48))
                    repeat2+=1;
                else
                    repeat2=1;
                if (repeat2==infoAboutBoard.k){
                    return 1;
                }
            }
        }
    }
   return 0;
}
void genAllPosiation(SBOARD *infoAbBoard,char **board,int player){
    cout<<infoAbBoard->emptySpaces<<endl;
    int w=0,x=0,y=0;
    while(w!=infoAbBoard->emptySpaces){
        if (x==infoAbBoard->X){
            x=0;
            y+=1;
        }
        if (board[y][x]=='0'){
            for (int i = 0; i < infoAbBoard->Y; i++) {
                for (int j = 0; j < infoAbBoard->X; j++) {
                    if (x == j && i == y) {
                        printf("%d ",infoAbBoard->activePlayer);
                    } else {
                        printf("%c ",board[i][j]);
                    }
                }
                printf("\n");
            }
            w++;
        }
        x++;
    }
}
void move_cut(SBOARD *infoAbBoard,char **board,int player){
    if (checkingWins(board,*infoAbBoard, opponent(player))==1) printf("0\n");
    else {
        int w=0,x=0,y=0,t=0;
        while(w!=infoAbBoard->emptySpaces){
            if (x==infoAbBoard->X){
                x=0;
                y+=1;
            }
            if (board[y][x]=='0'){
                board[y][x]=(char)(player+48);
                infoAbBoard->emptySpaces-=1;
                if (checkingWins(board,*infoAbBoard,player)==1||infoAbBoard->emptySpaces==0) {
                    printf("%d\n",1);
                    for (int i = 0; i < infoAbBoard->Y; i++) {
                        for (int j = 0; j < infoAbBoard->X; j++) {
                            if (x == j && i == y) {
                                printf("%d ", infoAbBoard->activePlayer);
                            } else {
                                printf("%c ", board[i][j]);
                            }
                        }
                        printf("\n");
                    }
                    t=1;
                    break;
                }
                board[y][x]='0';
                infoAbBoard->emptySpaces+=1;
                w++;
            }
            x++;
        }
        if (t==0)
            genAllPosiation(infoAbBoard,board,player);
    }
}
void moves(SBOARD *infoAbBoard,char **board,int player){//wszystkie możliwe kombinacje

    if (checkingWins(board,*infoAbBoard, opponent(player))==1) printf("0\n");
    else if (infoAbBoard->emptySpaces==0) printf("0\n");
    else {
        genAllPosiation(infoAbBoard,board,player);
    }
}
int minmax(SBOARD *infoAbBoard,char **board,int player,bool m){
    if (checkingWins(board, *infoAbBoard, opponent(player))==1){
        if (m== true)
            return -1;
        else
            return 1;
    }
    if (checkingWins(board, *infoAbBoard, player)==1){
        if (m== true)
            return 1;
        else
            return -1;
    }
    if (infoAbBoard->emptySpaces==0){
        return 0;
    }
    if(m== true){
        int score=-1;
        for (int i = 0; i < infoAbBoard->Y; i++) {
            for (int j = 0; j < infoAbBoard->X; j++) {
                if (board[i][j]=='0'){
                    board[i][j]=(char)(player+48);
                    infoAbBoard->emptySpaces--;
                    score=maxmax(minmax(infoAbBoard,board, opponent(player), false),score);
                    board[i][j]='0';
                    infoAbBoard->emptySpaces++;
                    if (score==1){
                        return score;
                    }
                }
            }
        }
        return score;
    }
    else if(m== false){
        int score=1;
        for (int i = 0; i < infoAbBoard->Y; i++) {
            for (int j = 0; j < infoAbBoard->X; j++) {
                if (board[i][j]=='0'){
                    board[i][j]= (char)(player+48);
                    infoAbBoard->emptySpaces--;
                    score=minmin(minmax(infoAbBoard,board, opponent(player),true),score);
                    board[i][j]='0';
                    infoAbBoard->emptySpaces++;
                    if (score==-1)
                        return score;
                }
            }
        }
        return score;
    }
    return 0;
}

void solve_game(SBOARD *infoAbBoard,char **board,int player){
    int score=("%d\n", minmax(infoAbBoard,board,player, true));
    if (score==1){
        if (player==1){
            printf("FIRST_PLAYER_WINS\n");
        }
        else if(player==2){
            printf("SECOND_PLAYER_WINS\n");
        }
    }
    else if(score==-1){
        if (player==2){
            printf("FIRST_PLAYER_WINS\n");
        }
        else if(player==1){
            printf("SECOND_PLAYER_WINS\n");
        }
    }
    else{
        printf("BOTH_PLAYERS_TIE\n");
    }
}
void delatememory(char **board,SBOARD *infoAbBoard) {
    for (int i = 0; i < infoAbBoard->Y; ++i) {
        delete[] board[i];
    }
    delete board;
}
int main() {
    char buff[40];
    while(cin>>buff){
        if(feof(stdin)!=0) {
            break;
        }
        if (strcmp(buff,"GEN_ALL_POS_MOV")==0){
            SBOARD infoAbBoard;
            int Y,X,K,player;
            cin>>Y>>X>>K>>player;
            infoAbBoard.Y=Y;
            infoAbBoard.X=X;
            infoAbBoard.k=K;
            infoAbBoard.activePlayer=player;
            char **tab=new char*[infoAbBoard.Y];
            for (int i = 0; i < infoAbBoard.Y; i++) {
                tab[i]=new char[infoAbBoard.X];
            }
            reading(&infoAbBoard,tab);
            moves(&infoAbBoard,tab,player);
            delatememory(tab,&infoAbBoard);
        }
        else if (strcmp(buff,"GEN_ALL_POS_MOV_CUT_IF_GAME_OVER")==0){
            SBOARD infoAbBoard;
            int Y,X,K,player;
            cin>>Y>>X>>K>>player;
            infoAbBoard.Y=Y;
            infoAbBoard.X=X;
            infoAbBoard.k=K;
            infoAbBoard.activePlayer=player;
            char **tab=new char*[infoAbBoard.Y];
            for (int i = 0; i < infoAbBoard.Y; i++) {
                tab[i]=new char[infoAbBoard.X];
            }
            reading(&infoAbBoard,tab);
            move_cut(&infoAbBoard,tab,infoAbBoard.activePlayer);
            delatememory(tab,&infoAbBoard);
        }
        else if (strcmp(buff,"SOLVE_GAME_STATE")==0){
            SBOARD infoAbBoard;
            int Y,X,K,player;
            cin>>Y>>X>>K>>player;
            infoAbBoard.Y=Y;
            infoAbBoard.X=X;
            infoAbBoard.k=K;
            infoAbBoard.activePlayer=player;
            char **tab=new char*[infoAbBoard.Y];
            for (int i = 0; i < infoAbBoard.Y; i++) {
                tab[i]=new char[infoAbBoard.X];
            }
            reading(&infoAbBoard,tab);
            solve_game(&infoAbBoard,tab,player);
            delatememory(tab,&infoAbBoard);
        }
    }
    return 0;
}
