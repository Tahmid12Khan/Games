#include<stdio.h>
#include<stdlib.h>

char row[32], row1[32], waste;
int check[500];
int pcWin = 0, playerWin = 0, playerTurn = 0;
void makeBoard(){
    int i = 0, j = 0;
    for(i = 0; i < 4; i++){
        for(j = 0; j < 7; j++){
            if(j % 2 == 0)
                row[i * 8 + j] = '.';
            else row[i * 8 + j] = ' ';

            row1[i * 8 + j] = ' ';
        }
    }
}

void showBoard(){
    int i = 0, j = 0;
    char ch = 'a';
    printf("  1 2 3 4\n");
    for(i = 0; i < 4; i++){
        printf("%c ", ch);
        ch++;
        for(j = 0; j < 7; j++){
            printf("%c", row[i * 8 + j]);
        }
        printf("\n  ");
        for(j = 0; j < 7; j++){
            printf("%c", row1[i * 8 + j]);
        }
        printf("\n");
    }
}

void doCheck(int x, int y){
    check[16 * x + y] = 1;
    check[16 * y + x] = 1;
  //  printf("xxx = %d yyy = %d\n", 16 * x + y, 16 * y + x);
}
void isBox(char ch){
    int i = 0;
    for(i = 0; i < 16; i++){
        if(check[i * 16 + (i + 1)] && check[i * 16 + i + 4] && check[(i + 1) * 16 + i + 5] && check [(i + 4) * 16 + i + 5]){
            if(row1[(i * 2) + 1] == ' '){
                row1[(i * 2) + 1] = ch;
                if(ch == 'P'){
                    pcWin++;
                }
                else{
                    playerWin++;
                }
         //       printf("Sammy\n");
            }
        }
    }
}
int max(int x, int y){
    if(x > y)
        return x;
    return y;
}

int min(int x, int y){
    if(x < y)
        return x;
    return y;
}
unsigned int m_w = 0;
unsigned int m_z = 0;
unsigned int get_random(){
    m_z = 36969 * (m_z & 65535) + (m_z >> 16);
    m_w = 18000 * (m_w & 65535) + (m_w >> 16);
    return ((m_z << 16) + m_w);
}

int checkValid(int val1, int val2){
    int dif = val2 - val1;
    if(val1 % 4 == 3 && dif != 4){
        return 0;
    }
    if(check[16* val1 + val2] == 0){
             //   printf("222\n");

        if(dif == 1){
        //     printf("333\n");
            doCheck(val1, val2);
            row[val1 * 2 + 1] = '_';
            return 1;
        }
        else if(dif == 4){
            //   printf("444\n");
            doCheck(val1, val2);
            row1[val1 * 2] = '|';
            return 1;
        }
    }
    return 0;
}
void pc(){
    while(1){
        unsigned int val1 = get_random();

        unsigned int val2 = get_random();
        //printf("val1 = %ud val2 = %ud\n", val1, val2);
        val1 = val1 % 16;
        val2 = val2 % 16;
        int mini = min(val1, val2);
        int maxi = max(val1, val2);
        val1 = mini;
        val2 = maxi;
        if(checkValid(val1, val2)){
          //  printf("inside pc: val1 %d, val2 %d\n", val1, val2);
            int row1 = val1 / 4;
            int row2 = val2 / 4;
            int col1 = val1 % 4;
            int col2 = val2 % 4;
            char ch1 = row1 + 97;
            char ch2 = row2 + 97;
            col1++;
            col2++;
            printf("I draw a line between %c%d and %c%d.\n\n", ch1, col1, ch2, col2);
            break;
        }
    }
}
void intro(){
    printf("\t\t\tWelcome\n\t\t\t  To \n\t\t    Tahmid and Shammy's \n\t\t     DOTS AND BOXES\n\t\t       Version 1.0\n\n");
}

void credits(){
    printf("\t\t    Tahmid and Shammy's \n\t\t     DOTS AND BOXES\n\t\t       Version 1.0\n\n\nCREDITS\n\n");
    printf("1. Tahmid Khan, Roll: BSSE0801, 2nd Year, IIT, DU\n");
    printf("2. Sumaya Shammy, Roll: BSSE0821, 2nd Year, IIT, DU\n");
}
void turn(){
    while(1){
        printf("Enter the first seed (Range any valid integer number but not zero): ");
        scanf("%d", &m_w);
        if(m_w != 0){
            break;
        }
        printf("Number can't be zero. Try again\n");
    }
    while(1){
        printf("Enter the second seed (Range any valid integer number but not zero): ");
        scanf("%d%c", &m_z, &waste);
    //    scanf("%s", &waste);
        //printf("%d", waste[0]);
        if(m_z != 0){
                break;
            }
        printf("Number can't be zero. Try again\n");
    }
    playerTurn = get_random() % 2;
    if(playerTurn == 0){
        printf("\n\nFirst turn is yours.\n\n");
    }
    else{
        printf("\n\nFirst turn goes to me. :) \n\n");
    }
}

void result(){
    printf("Your Score: %d\n PC Score: %d\n", playerWin, pcWin);
}

void playGame(){
    char ch, ch1, ch2;
    int x, y;
    int val1, val2;
    int i = 0;
    //intro();
    turn();
    while(1){
        if(pcWin + playerWin == 9){
            break;
        }
        //showBoard();
        if(i % 2 != playerTurn){
            printf("\n\nMy Turn.\n\n\n");
            pc();
            i++;
            isBox('P');
            continue;
        }

        while(1){
            char input[200];
            int r, r1;
            result();
            showBoard();
            printf("\n\nYour Turn\n");
            printf("\nEnter the first coordinate: ");
           // scanf("%c%d%c", &ch, &y, &waste);
            scanf("%s", input);
            x = input[0] - 97;
            y = input[1] - 48;
            y--;
            r = y;
            ch = input[0];
            if(input[2] != '\0'){
                ch = 'z';
            }
            if(ch < 'a' || ch > 'd' || r < 0 || r > 3){
                printf("Invalid move. Try Again\n");
                continue;

            }
            val1 = x * 4 + y;
            printf("\nEnter the second coordinate: ");
           // scanf("%c%d%c", &ch1, &y, &waste);
            scanf("%s", input);
            ch1 = input[0];
            y = input[1] - 48;
            x = ch1 - 97;
            y--;
            r1 = y;
            if(input[2] != '\0'){
                ch1 = 'z';
            }
            if(ch1 < 'a' || ch1 > 'd' || r1 < 0 || r1 > 3){
                printf("Invalid move. Try Again\n");
                continue;

            }
            val2 = x * 4 + y;
            //printf("val2 = %d\n", val2);
            int mini = min(val1, val2);
            int maxi = max(val1, val2);
            val1 = mini;
            val2 = maxi;
            if(ch == ch1 || r == r1){
                if(checkValid(val1, val2)){
                   // printf("Invalid move. Try Again.!!!\n");
                    printf("\nYou drew a line between %c%d and %c%d.\n\n", ch, r + 1, ch1, r1 + 1);
                    break;
                }
                else{
                    printf("Invalid move.\n");
                    continue;
                }
            }
            printf("The points must be adjacent. Try Again!!! \n");

         //   printf("x = %d, y = %d, val1 = %d, val2 = %d\n", x, y, val1, val2);
           // printf("111\n");
        }

        isBox('I');
        showBoard();
     //   printf("checked\n");
        i++;
    }
    showBoard();
}



int main(){
  // system("COLOR F0");
    makeBoard();
    intro();
    playGame();
    result();
    if(pcWin < playerWin){
        printf("You Win\n");

    }
    else printf("PC Won\n");
    scanf("%c", &waste);
    credits();

    return 0;

}


