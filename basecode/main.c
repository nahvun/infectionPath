//
//  main.c
//  infestPath
//
//  Created by Juyeop Kim on 2022/10/20.
//

#include <stdio.h>
#include <string.h>
#include "ifct_element.h"
#include "ifct_database.h"

#define MENU_PATIENT        1
#define MENU_PLACE          2
#define MENU_AGE            3
#define MENU_TRACK          4
#define MENU_EXIT           0

#define TIME_HIDE           2


int trackInfester(int patient_no, int *detected_time, int *place);
int main(int argc, const char * argv[]) {
    
    int menu_selection;
    void *ifct_element;
    FILE* fp;
    int pIndex, age, time;
    int placeHist[N_HISTORY];
    
    //------------- 1. loading patient info file ------------------------------
    //1-1. FILE pointer open
    if (argc != 2)
    {
        printf("[ERROR] syntax : infestPath (file path).");
        return -1;
    }
    
    fp = fopen(argv[1],"r");
    if (fp == NULL)
    {
        printf("[ERROR] Failed to open database file!! (%s)\n", argv[1]);
        return -1;
    }
    
    //1-2. loading each patient informations
    
    //불러와야함 ifsele_genElement(); --> 구조체에 저장, 이제 이거를 활용. 
    

//	void ifctele_printElement(void* ifct_element);
    
 	while (3 == fscanf(fp, "%d %d %d\n", &pIndex, &age, &time))
	{
		
 		int i;
 		//printf("%d 번째 환자 감염 경로: ", pIndex);
 		int history_place[N_HISTORY];
 		
 		for (i=0;i<N_HISTORY;i++)
		{
 			fscanf(fp, "%d", &placeHist[i]);
 			history_place[i] = placeHist[i];
 			//printf(" %s(% )  ", ifctele_getPlaceName(placeHist[i]) /*, 감염시점*/ ); 		
		}
				
		//printf("\n");
//		int history_place[N_HISTORY] = {placeHist[0], placeHist[1],placeHist[2],placeHist[3],placeHist[4]};
		ifctele_genElement(pIndex, age, time, history_place);
		
	}
	
    //1-3. FILE pointer close 
    fclose(fp);
    
    
    do {
        printf("\n=============== INFECTION PATH MANAGEMENT PROGRAM (No. of patients : %i) =============\n", ifctdb_len());
        printf("1. Print details about a patient.\n");                     //MENU_PATIENT
        printf("2. Print list of patients infected at a place.\n");        //MENU_PLACE
        printf("3. Print list of patients in a range of age.\n");          //MENU_AGE
        printf("4. Track the root of the infection\n");                    //MENU_TRACK
        printf("0. Exit.\n");                                              //MENU_EXIT
        printf("=============== ------------------------------------------------------- =============\n\n");
        
        printf("Select a menu :");
        scanf("%d", &menu_selection);
        fflush(stdin);
        
        int patient_selection; 
        
        switch(menu_selection)
        {
            case MENU_EXIT:          //0
                printf("Exiting the program... Bye bye.\n");
                break;
                
            case MENU_PATIENT:        //1
            
            	/*
                printf("Patient index :");
                scanf("%d", &patient_selection);
                if (patient_selection == pIndex)
                	printf("%d %d %d", pIndex, age, time);
                /// */
                printf("-------------------------------------------------------\n");
                printf("Patient index : ");
                scanf("%d", &patient_selection);
                
                //ifsarray[patient_selection].age
                
                
			//	ifctele_printElement(ifctele_getAge(ifct_element));
				
                printf("age:%i", ifctele_getAge(ifct_element));
                
                printf("-------------------------------------------------------\n");
                break;
                
            case MENU_PLACE:           //2
                
                break;
                
            case MENU_AGE:              //3
                
                break;
                
            case MENU_TRACK:          //4
                    
                break;
                
            default:
                printf("[ERROR Wrong menu selection! (%i), please choose between 0 ~ 4\n", menu_selection);
                break;
        }
    
    } while(menu_selection != 0);
    
    
    return 0;
}
