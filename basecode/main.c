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
    
 	while (3 == fscanf(fp, "%d %d %d\n", &pIndex, &age, &time))
	{
		
 		int i;
 		int history_place[N_HISTORY];
 		
 		for (i=0;i<N_HISTORY;i++)
		{
 			fscanf(fp, "%d", &placeHist[i]);
 			history_place[i] = placeHist[i];	
		}
				
		ifct_element = ifctele_genElement(pIndex, age, time, history_place);
		ifctdb_addTail(ifct_element);     //while문 한번 돌 때 구조체를 만들어서 linkedtolist에 넣ㄴ음.  
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
        char place_selection;
        int maxAge_selection, minAge_selection;
        int i;
        int cnt = 0;
        
        switch(menu_selection)
        {
            case MENU_EXIT:          //0
                printf("Exiting the program... Bye bye.\n");
                break;
                
            case MENU_PATIENT:        //1
            
                printf("Patient index : ");
                scanf("%d", &patient_selection);
                ifctele_printElement(ifctdb_getData(patient_selection));
                
                break;
                
            case MENU_PLACE:           //2
                				
                printf("Place name : ");
                scanf("%s", &place_selection);  ////받아온 정보들 중에서 장소를 이름으로 바꾼 후 비교. 
                
                for(i=0;i<5;i++)////몇명의 정보를 가져온지 아직 모름. 그만큼 돌려야 함(5 수정)  -->while 문 안에서 몇번 돌았는지 세면 될듯 
                {	
                	char* placeName = ifctele_getPlaceName(ifctele_getHistPlaceIndex(ifctdb_getData(i), 4));
                
					if (strcmp(&place_selection, placeName)==0)
					{
						ifctele_printElement(ifctdb_getData(i));
						cnt++;
					}             										
				}
				printf("there are %d patients in %s", cnt, &place_selection);
                break;
                
            case MENU_AGE:              //3
                
                printf("Min age: ");
                scanf("%d", &minAge_selection);
                printf("Max age: ");
                scanf("%d", &maxAge_selection);
                                
                for(i=0;i<5;i++)		////몇명의 정보를 가져온지 아직 모름. 그만큼 돌려야 함(5 수정)  
                {	                	
                	int getAge = ifctele_getAge(ifctdb_getData(i));
                	
					if ((getAge>=minAge_selection) && (getAge<=maxAge_selection))			//등호에 따라. 제출 전 나이 경계부분 확인하기.  
					{
						ifctele_printElement(ifctdb_getData(i));
						cnt++;
					}																	
				}
				printf("there are %d patients between age from %d to %d \n\n ", cnt, minAge_selection, maxAge_selection ); //ㅊcnt수정 필요  
				
                break;
                
            case MENU_TRACK:          //4
            
            	printf("Patient index : ");
                scanf("%d", &patient_selection);
                int current_p = patient_selection;
				int first_p=-1, infection_p=-1;
        		
        		printf("0and 2 is met : %d", isMet(0,2));
        		/* Pseudocoding
        		해야하는 것: 환자 정보 받아와서   그사람이 누구를 만났는지 추적.     같은 장소에 있었던 사람이 추적되면 같은 시간에 있었는지까지 확인. 
        			getdata(current_p)                    trackInfecter()                     isMet()
        		
        		ifctdb_getData(int index);   받아올 환자 번호 입력하면 그 구조체 전달 
        		ifctele_getHistPlaceIndex(void* obj, int index);   환자의 몇번째 장소 가져옴. obj 자리에  ifctdb_getData(int index)
				ifctele_getinfestedTime(void* obj);   환자가 몇번째 장소에서 감염된건지 가져옴
				
				isMet(int p1, int p2)  p1과 p2가 만난 시간 가져오는 함수  
        		
        		
        		*/
        		
        	//	detectedTime(current_p, ifctele_getHistPlaceIndex(current_p, 1));
                //printf("%d", ifctele_getinfestedTime(ifctdb_getData(patient_selection))); //선택한 환자의 detected time 
                /*
                while(current_p != first_p) 
                {
                	infection_p = trackInfecter(current_p);
                	if (infection_p != 0)
                		printf("%i환자는 %i 환자에게 전파됨\n", current_p, infection_p);
                   	else
                		first_p = current_p;
                		
                	current_p = infection_p;                	
				}
				printf("The first infector of %d is %d",patient_selection, current_p);   
                */
                
                
                break;
                
            default:
                printf("[ERROR Wrong menu selection! (%i), please choose between 0 ~ 4\n", menu_selection);
                break;
        }
    
    } while(menu_selection != 0);
    
    
    return 0;
}
/*
int trackInfecter(int patient_c)		//prototyping 필요.  
{
	int i, patient_i; 
	
	for(i=0;i<5;i++)		//5를 받아오는 총 환자수를 while문에서 받아온걸로 바꿔야 함 
	{
		if(patient_c != i)
		{
			int met_time;
			met_time = isMet(patient_c, i);
			
			if(met_time>0) 	//만났다면  //위의 !=i와 &&로 묶어도 될듯. 
			{
				patient_i = i;		
				return patient_i;
			} 
			else
				return 0;
		}
	}
}
*/

int isMet(int p1, int p2)     	//prototyping 필요.  unfinished //시점에 대한 함수도 추가로 필요. 
{	
	int i, metTime;
	int p1_place, p1_time, p2_place;
	
	for(i=0;i<N_HISTORY-2;i++)
	{
		p1_place = ifctele_getHistPlaceIndex(ifctdb_getData(p1), i);
		p1_time = ifctele_getinfestedTime(ifctdb_getData(p1)) - (N_HISTORY-1 - i);
		p2_place = placeInTime(p2, p1_time);
		
		if (p1_place == p2_place)
		{
			metTime = p1_place;
			//printf("p1_place is: %d\n", p1_place);
		}
	}
		
	return metTime;
}
/*
int detectedTime(void* patient, int place)  //입력된 사람이 어떤 장소에서 있었던 시간이 언젠지 알려주는 함수. 
{
	int i;
	int time;
	for(i=0;i<N_HISTORY;i++)
	{
		
	}
	return time;
}
*/

int placeInTime(int patient, int time) //특정 시점에서 환자가 있던 장소 출력 함수.
{
	return ifctele_getHistPlaceIndex(ifctdb_getData(patient), convertTimeToIndex(time, ifctele_getinfestedTime(ifctdb_getData(patient))));
}

int convertTimeToIndex(int time, int infestedTime)//시점에 대한 index 출력 함 
{
	int index = -1;
	
	if (time <= infestedTime && time > infestedTime - N_HISTORY)
	{
		index = N_HISTORY - (infestedTime - time) -1;
	}
	return index;
}
