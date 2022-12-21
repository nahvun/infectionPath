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
int isMet(int p1, int p2);
int printisMet(int p1, int p2);
int placeInTime(int patient, int time);
int convertTimeToIndex(int time, int infestedTime);
int longestTime(void);

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
    
    //1-2. loading each patient informations and store in linked list
    
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
		ifctdb_addTail(ifct_element);
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
                
                //print error message if patient_selection is too big
                if (patient_selection > ifctdb_len()-1)
                {
                	printf("[ERROR] Your input for the patient index (%d) is wrong! input must be 0 ~ %d\n", patient_selection, ifctdb_len()-1);
                	break;	
				}
				//print elements about selected patient's data
                ifctele_printElement(ifctdb_getData(patient_selection));
                
                break;
                
            case MENU_PLACE:           //2
                				
                printf("Place name : ");
                scanf("%s", &place_selection); 
                
                //compare place_selection and every patient's infected place
                for(i=0;i<ifctdb_len();i++)
                {	
                	char* placeName = ifctele_getPlaceName(ifctele_getHistPlaceIndex(ifctdb_getData(i), 4));
                
                	//print patient's data if place_selection and patient's infected place is same
					if (strcmp(&place_selection, placeName)==0)
					{
						ifctele_printElement(ifctdb_getData(i));
						cnt++;
					}
				}
				printf("There are %d patients detected in %s. \n\n", cnt, &place_selection);
                break;
                
            case MENU_AGE:              //3
                
                printf("Min age: ");
                scanf("%d", &minAge_selection);
                printf("Max age: ");
                scanf("%d", &maxAge_selection);
                
                //get every patient's age and find out if it is in the range minAge ~ maxAge
                for(i=0;i<ifctdb_len();i++)
                {
                	int getAge = ifctele_getAge(ifctdb_getData(i));
                	
					if ((getAge>=minAge_selection) && (getAge<=maxAge_selection))
					{
						ifctele_printElement(ifctdb_getData(i));
						cnt++;
					}																	
				}
				printf("There are %d patients whose age is between %d and %d. \n\n ", cnt, minAge_selection, maxAge_selection );  
				
                break;
                
            case MENU_TRACK:          //4
            
            	printf("Patient index : ");
                scanf("%d", &patient_selection);
                
                //print error message if patient_selection is too big
                if (patient_selection > ifctdb_len()-1)
                {
                	printf("[ERROR] Your input for the patient index (%d) is wrong! input must be 0 ~ %d\n", patient_selection, ifctdb_len()-1);
                	break;	
				}
				
				int current_p = patient_selection;
				int first_p=-1, infection_p=-1;
        		/* 
        		 	description : get current patient's data and track who that patient met, find out where and when they met
        							getdata(current_p)            trackInfecter()                isMet()
 				    
 				    1. put patient_selection in current_p
 				    2. find if there is a infector (infection_p)
 				       if there is, return infector's number and if not, returns -1
 				    3. print the tracking process and put infection_p in current_p to find the previous infecter
 				    4. continue until there is no infection_p, put current_p in first_p
 				    5. finish and print first infecter
 				    
  					print value: tracking process and the first infecter
        		*/
        	    while(current_p != first_p) 
                {
                	infection_p = trackInfecter(current_p);
                	if (infection_p != -1)
                	{
                		printf(" --> [TRACKING] patient %d is infected by %d " , current_p, infection_p);
                		printisMet(current_p, infection_p);
						current_p = infection_p;	
					}
                	else
                		first_p = current_p;
                	cnt ++;
				}
				
				if (cnt == 1)
					printf("%d is the first infector!! \n", patient_selection);
				else
					printf("The first infector of %d is %d \n", patient_selection, first_p);
					
                break;
                
            default:
                printf("[ERROR] Wrong menu selection! (%i), please choose between 0 ~ 4\n", menu_selection);
                break;
        }
    
    } while(menu_selection != 0);
    
    
    return 0;
}

/*
    description : tracking the infecter
    input parameters : patient number
    return value : infecter number
    
	if there is infecter, trackInfecter() return infecter's number(patient_i) and if not, return -1.
*/
int trackInfecter(int patient_c)
{
	int i, patient_i=-1; 
	int met_time=0, first_met_time=longestTime();
	
	for(i=0;i<ifctdb_len();i++)
	{
		if(i != patient_c)
		{
			met_time = isMet(patient_c, i);
			if(met_time > 0 && met_time < first_met_time)
			{
				first_met_time = met_time;
				patient_i = i;
			}
		}
	}
	return patient_i;	
}

/*
    description : get the time and place where two patients are met
    input parameters : two number of patients(p1, p2)
    return value : time when two people met(metTime)
    
    1. p1_place has to be in infection available time (i=0,1,2 if N_HISTORY is 5)
	2. in p1's infection available time, find out where p2 is (p2_place)
	3. if p1_place and p2_place is same (met in the same time, same place),
	   and p2 is in infect available time, p1 is infected by p2
*/

int isMet(int p1, int p2) 
{	
	int i, metTime = -1;
	int p1_place, p1_time, p2_place, p2_dtime;
	
	for(i=0;i<N_HISTORY-2;i++)
	{
		p1_place = ifctele_getHistPlaceIndex(ifctdb_getData(p1), i);
		p1_time = ifctele_getinfestedTime(ifctdb_getData(p1)) - (N_HISTORY-1 - i);
		p2_place = placeInTime(p2, p1_time);
		p2_dtime = ifctele_getinfestedTime(ifctdb_getData(p2));
		
		if ((p1_place == p2_place) && (p1_time == p2_dtime || p1_time == p2_dtime-1))
			metTime = p1_time;
	}
	return metTime;
}

/*
    description : get the time and place where two patients are met
    			  function act as same as isMet() but it prints time and place to tell when and where they met
    input parameters : two number of patients(p1, p2)
    print value : time and place when two people met
*/
int printisMet(int p1, int p2) 
{	
	int i, metTime = -1;
	int p1_place, p1_time, p2_place, p2_dtime;
	
	for(i=0;i<N_HISTORY-2;i++)
	{
		p1_place = ifctele_getHistPlaceIndex(ifctdb_getData(p1), i);
		p1_time = ifctele_getinfestedTime(ifctdb_getData(p1)) - (N_HISTORY-1 - i);
		p2_place = placeInTime(p2, p1_time);
		p2_dtime = ifctele_getinfestedTime(ifctdb_getData(p2));
		
		if ((p1_place == p2_place) && (p1_time == p2_dtime || p1_time == p2_dtime-1))
		{
			metTime = p1_time;
			printf("( time: %d  place: %s )\n", p1_time, ifctele_getPlaceName(p1_place));
		}
	}
	return 0;
}

/*
    description : get the place where patient were in specific time
    input parameters : patient number, time
    return value : place index 
    
*/
int placeInTime(int patient, int time)      //특정 시점에서 환자가 있던 장소 출력 함수.
{
	return ifctele_getHistPlaceIndex(ifctdb_getData(patient), convertTimeToIndex(time, ifctele_getinfestedTime(ifctdb_getData(patient))));
}

/*
    description : convert time to index
    input parameters : time, patient's infested time
    return value : index - index of patient's place history
    
*/
int convertTimeToIndex(int time, int infestedTime) 
{
	int index = -1;
	
	if (time <= infestedTime && time > infestedTime - N_HISTORY)
	{
		index = N_HISTORY - (infestedTime - time) -1;
	}
	return index;
}

/*
    description : get the longest time in patient's file
    return value : place index 
    
    find the longest time in file to find the first_met_time in trackInfecter()
*/
int longestTime(void) 
{
	int i, time, longtime=0;
	for(i=0;i<ifctdb_len();i++)
	{
		time = ifctele_getinfestedTime(ifctdb_getData(i));
		if (time > longtime)
			longtime = time;
	}
	return longtime;
}
