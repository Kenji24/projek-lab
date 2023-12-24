#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
#include <windows.h>

struct Leaderboard{
	char Username[30];
	int score;
};

struct Leaderboard easy[10], medium[10], hard[10];
int countEasy = 0, countMedium = 0, countHard = 0;

FILE *easyfile;
FILE *mediumfile;
FILE *hardfile;

COORD coord = {0, 0};

void gotoxy(int x, int y){
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void addleaderboard(struct Leaderboard board[], int *many, FILE *fp, int newScore) {
	gotoxy(48, 11);
    printf("ENTER USERNAME: ");
    scanf("%s", board[*many].Username);
    
	board[*many].score = newScore;
    fprintf(fp, "%s %d\n", board[*many].Username, board[*many].score);
    (*many)++;
    fflush(fp);
}

void bubbleSort(struct Leaderboard board[], int n) {
    int i, j;
    struct Leaderboard temp;

    for (i = 0; i < n - 1; i++) {
        for (j = 0; j < n - i - 1; j++) {
            if (board[j].score > board[j + 1].score) {
                temp = board[j];
                board[j] = board[j + 1];
                board[j + 1] = temp;
            }
        }
    }
}

void showleaderboard(struct Leaderboard board[], int many) {
    bubbleSort(board, many);
    int Entri = (many < 5) ? many : 5;
    
    for (int i = 0; i < 5; i++) {
    	if(i < Entri){
	    	gotoxy(53, i+4);
	        printf("#%d %s %d\n", i+1, board[i].Username, board[i].score);
		}
		else{
			gotoxy(53, i+4);
	        printf("#%d - -\n", i+1);
		}
    }
}

void loadLeaderboard(struct Leaderboard board[], int *many, FILE *fp) {
    if (fp != NULL) {
        while (fscanf(fp, "%s %d", board[*many].Username, &board[*many].score) == 2) {
            (*many)++;
        }
    } else {
        printf("FAIL");
    }
}

void UI(){
	gotoxy(33, 1);
	printf("================================================\n");
	gotoxy(52, 2);
	printf("TEBAK ANGKA\n");
	gotoxy(33, 3);
	printf("================================================\n");
	gotoxy(33, 10);
	printf("================================================\n");
}

void easyMode(){
	int angkaTebakan, tebakan;
	int jumlahTebakan = 0;
	char yeahno, chose3, term;
	
	
	while(1){
		
		angkaTebakan = rand() % 10 + 1;
		system("cls");
		
		while (1) {
			UI();
//			printf("%d\n", angkaTebakan);
			
			gotoxy(43, 7);
			printf("INSERT YOUR GUESS (1-10): ");
			scanf("%d", &tebakan); getchar();
			jumlahTebakan++;
			
			if(tebakan == angkaTebakan) {
				
				here:
				system("cls");
				UI();
				
				gotoxy(34, 9);
				printf("CONGRATS! YOU GUESS THE NUMBER %d WITH %d GUESS.\n", angkaTebakan, jumlahTebakan);
				gotoxy(33, 10);		        
				printf("================================================\n");
				gotoxy(48, 11);
				printf("CONTINUE? (Y/N): ");
				yeahno = getch();
				
				if(yeahno == 'Y' || yeahno == 'y'){
					jumlahTebakan = 0;
					break;
				}
				else if(yeahno == 'N' || yeahno == 'n'){
					gotoxy(33, 10);	
					printf("================================================\n");
					gotoxy(33, 11);
					printf(" DO YOU WANT TO PUT IT IN LEADERBOARD? (Y/N): ");
					chose3 = getch();
					
					if(chose3 == 'Y' || chose3 == 'y'){
						system("cls");
						UI();
						addleaderboard(easy, &countEasy, easyfile, jumlahTebakan);
						
						return;
					}
					else if(chose3 == 'N' || chose3 == 'n'){
						printf("OK\n");
						sleep(1);
						return;
					}
					else{
						printf("WRONG INPUT");
						sleep(1);
						
					} 
				}
				else{
					printf("WRONG INPUT");
					sleep(1);
					goto here;
				} 
			} 
			else if(tebakan < angkaTebakan) {
				system("cls");
				UI();
				gotoxy(40, 6);
				printf("YOUR GUESS IS TO LOW. TRY AGAIN!\n");
			} 
			else if(tebakan > angkaTebakan) {
				system("cls");
				UI();
				gotoxy(40, 6);
				printf("YOUR GUESS IS TO HIGH. TRY AGAIN!\n");
			}
			else {
				system("cls");
				gotoxy(40, 6);
				printf("WRONG INPUT");
			}
		}
	}
}

void mediumMode(){
	int angkaTebakan, tebakan;
	int jumlahTebakan = 0;
	char yeahno, chose3, term;
	
	while(1){
		angkaTebakan = rand() % 50 + 1;
		system("cls");
		
		while (1) {
			UI();
//			printf("%d\n", angkaTebakan);
			
			gotoxy(43, 7);
			printf("INSERT YOUR GUESS (1-50): ");
			scanf("%d", &tebakan); getchar();
			jumlahTebakan++;
			
			if (tebakan == angkaTebakan) {
				
				here:
				system("cls");
				UI();
				
				gotoxy(34, 9);
				printf("CONGRATS! YOU GUESS THE NUMBER %d WITH %d GUESS.\n", angkaTebakan, jumlahTebakan);
				gotoxy(33, 10);
				printf("================================================\n");
				gotoxy(48, 11);
				printf("CONTINUE? (Y/N): ");
				yeahno = getch();
	
				if(yeahno == 'Y' || yeahno == 'y'){
					jumlahTebakan = 0;
					break;
				}
				else if(yeahno == 'N'|| yeahno == 'n'){
					gotoxy(33, 10);	
					printf("================================================\n");
					gotoxy(33, 11);
					printf(" DO YOU WANT TO PUT IT IN LEADERBOARD? (Y/N): ");
					chose3 = getch();
					
					if(chose3 == 'Y' || chose3 == 'y'){
						system("cls");
						UI();
						addleaderboard(medium, &countMedium, mediumfile, jumlahTebakan);
						
						return;
					}
					else if(chose3 == 'N' || chose3 == 'n'){
						printf("OK\n");
						sleep(1);
						return;
					}
					else{
						printf("WRONG INPUT");
						sleep(1);
					} 
				}
				else{
					printf("WRONG INPUT");
					sleep(1);
					goto here;
				} 
			} 
			else if (tebakan < angkaTebakan) {
				system("cls");
				UI();
				gotoxy(40, 6);
				printf("YOUR GUESS IS TO LOW. TRY AGAIN!\n");
			} 
			else if(tebakan > angkaTebakan) {
				system("cls");
				UI();
				gotoxy(40, 6);
				printf("YOUR GUESS IS TO HIGH. TRY AGAIN!\n");
			}
		}
	}
}

void hardMode(){
	int continu = 0;
	int angkaTebakan, tebakan, berhasil;
	int jumlahTebakan = 0;
	char yeahno, chose3;
	
	while(1){
		angkaTebakan = rand() % 100 + 1;
		system("cls");
		
		while (1) {
			UI();
//			printf("%d\n", angkaTebakan);
			
			gotoxy(43, 7);
			printf("INSERT YOUR GUESS (1-100): ");
			scanf("%d", &tebakan); getchar();
			jumlahTebakan++;
			
			if (tebakan == angkaTebakan) {
				
				here:
				system("cls");
				UI();
				
				gotoxy(34, 9);
				printf("CONGRATS! YOU GUESS THE NUMBER %d WITH %d GUESS.\n", angkaTebakan, jumlahTebakan);
				gotoxy(33, 10);	
				printf("================================================\n");
				gotoxy(48, 11);
				printf("CONTINUE? (Y/N): ");
				yeahno = getch();
				
				if(yeahno == 'Y' || yeahno == 'y'){
					jumlahTebakan = 0;
					break;
				}
				else if(yeahno == 'N' || yeahno == 'n'){
					gotoxy(33, 10);
					printf("================================================\n");
					gotoxy(33, 11);
					printf(" DO YOU WANT TO PUT IT IN LEADERBOARD? (Y/N): ");
					chose3 = getch();
					
					if(chose3 == 'Y' || chose3 == 'y'){
						system("cls");
						UI();
						addleaderboard(hard, &countHard, hardfile, jumlahTebakan);
						
						return;
					}
					else if(chose3 == 'N' || chose3 == 'n'){
						printf("OK\n");
						sleep(1);
						return;
					}
					else{
						printf("WRONG INPUT");
						sleep(1);
					} 
				}
				else {
					printf("WRONG INPUT");
					sleep(1);
					goto here;
				}
			} 
			else if (tebakan < angkaTebakan) {
				system("cls");
				UI();
				gotoxy(40, 6);
				printf("YOUR GUESS IS TO LOW. TRY AGAIN!\n");
			} 
			else {
				system("cls");
				UI();
				gotoxy(40, 6);
				printf("YOUR GUESS IS TO HIGH. TRY AGAIN!\n");
			}
		}
	}
}

int main() {
	
    easyfile = fopen("leaderboard_easy.txt", "a+");
    mediumfile = fopen("leaderboard_medium.txt", "a+");
    hardfile = fopen("leaderboard_hard.txt", "a+");
    
    loadLeaderboard(easy, &countEasy, easyfile);
    loadLeaderboard(medium, &countMedium, mediumfile);
    loadLeaderboard(hard, &countHard, hardfile);
    
    int berhasil = 0;
    char choise, chose1, chose2, chos;
    int continu = 0;
    char yesno = ' ';
    int lead = 0;
    

	while(1){
		
		srand(time(0));
		
		system("cls");
		choise = ' ';
		UI();
		
		gotoxy(54, 5);
		printf("1. PLAY\n");
		gotoxy(54, 6);
		printf("2. CREDIT\n");
		gotoxy(54, 7);
		printf("3. LEADERBOARD\n");
		gotoxy(54, 8);
		printf("4. EXIT\n");
		gotoxy(48, 11);
		printf("ENTER YOUR CHOICE: ");
		gotoxy(67, 11);
		choise = getch();
		
		if(choise == '1'){
			do{
				system("cls");
				chose1 = 0;
				UI();
				gotoxy(50, 5);
				printf("1. EASY (1-10)\n");
				gotoxy(50, 6);
				printf("2. MEDIUM (1-50)\n");
				gotoxy(50, 7);
				printf("3. HARD(1-100)\n");
				gotoxy(50, 8);
				printf("4. MAIN MENU\n");
				gotoxy(48, 11);
				printf("ENTER YOUR CHOICE: ");
				gotoxy(67, 11);
				chose1 = getch();
		
				switch(chose1){
					case '1':
						easyMode();	
						continue;
					case '2':	
						mediumMode();
						continue;
					case '3':
						hardMode();
						continue;
					case '4':
						break;
					default:
						printf("WRONG INPUT\n");
						sleep(1);
				}
				break;
			}while(1);
		}
		else if(choise == '2'){
			while (1){
				system("cls");
				UI();
				
				gotoxy(54, 5);
				printf("MADE BY:\n");
				gotoxy(54, 7);
				printf("Bhimo\n");
				gotoxy(54, 8);
				printf("Kenzie\n");
				gotoxy(48, 11);
				printf("BACK? (Y/N)? ");
				gotoxy(61, 11);
				yesno = getch();	   
				 
				if(yesno == 'Y' || yesno == 'y'){
					break;
				}
				else if(yesno == 'N' || yesno == 'n'){
					continue;
				}
				else printf("WRONG INPUT");
				sleep(1);
			}
		}
		else if(choise == '3'){
			do{
				system("cls");
				chos = 0;
				UI();
				gotoxy(55, 5);
				printf("1. EASY\n");
				gotoxy(55, 6);
				printf("2. MEDIUM\n");
				gotoxy(55, 7);
				printf("3. HARD\n");
				gotoxy(55, 8);
				printf("4. MAIN MENU\n");
				gotoxy(48, 11);
				printf("ENTER YOUR CHOICE: ");
				gotoxy(67, 11);
				chos = getch();
		
				switch(chos){
					case '1':
						system("cls");
						UI();
						
						showleaderboard(easy, countEasy);
						gotoxy(48, 11);
						printf("BACK? (Y/N)? ");
						gotoxy(61, 11);
						yesno = getch();	   
				 
						if(yesno == 'Y' || yesno == 'y'){
							break;
						}
						else if(yesno == 'N' || yesno == 'n'){
							continue;
						}
						else printf("WRONG INPUT");
						sleep(1);
						continue;
					case '2':	
						system("cls");
						UI();
						
						showleaderboard(medium, countMedium);
						gotoxy(48, 11);
						printf("BACK? (Y/N)? ");
						gotoxy(61, 11);
						yesno = getch();	   
				 
						if(yesno == 'Y' || yesno == 'y'){
							break;
						}
						else if(yesno == 'N' || yesno == 'n'){
							continue;
						}
						else printf("WRONG INPUT");
						sleep(1);
						continue;
					case '3':
						system("cls");
						UI();
						
						showleaderboard(hard, countHard);
						gotoxy(48, 11);
						printf("BACK? (Y/N)? ");
						gotoxy(61, 11);
						yesno = getch();	   
				 
						if(yesno == 'Y' || yesno == 'y'){
							break;
						}
						else if(yesno == 'N' || yesno == 'n'){
							continue;
						}
						else printf("WRONG INPUT");
						sleep(1);
						continue;
					case '4':
						break;
					default:
						printf("WRONG INPUT\n");
						sleep(1);
				}
				break;
			}while(1);	
		}
		else if(choise == '4'){
			system("cls");
			gotoxy(33, 3);
			printf("================================================\n");
			gotoxy(46, 4);
			printf("THANK YOU FOR PLAYING!\n");
			break;
		} 
		else printf("WRONG INPUT");
		sleep(1);
	}
	
	fclose(easyfile);
    fclose(mediumfile);
    fclose(hardfile);
	
	return 0;
}