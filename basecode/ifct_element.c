//
//  ifs_element.c
//  InfestPath
//
//  Created by Juyeop Kim on 2020/10/20.
//

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "ifct_element.h"

typedef enum place {
    Seoul,          //0
    Jeju,           //1
    Tokyo,          //2
    LosAngeles,     //3
    NewYork,        //4
    Texas,          //5
    Toronto,        //6
    Paris,          //7
    Nice,           //8
    Rome,           //9
    Milan,          //10
    London,         //11
    Manchester,     //12
    Basel,          //13
    Luzern,         //14
    Munich,         //15
    Frankfurt,      //16
    Berlin,         //17
    Barcelona,      //18
    Madrid,         //19
    Amsterdam,      //20
    Stockholm,      //21
    Oslo,           //22
    Hanoi,          //23
    Bangkok,        //24
    KualaLumpur,    //25
    Singapore,      //26
    Sydney,         //27
    SaoPaulo,       //28
    Cairo,          //29
    Beijing,        //30
    Nairobi,        //31
    Cancun,         //32
    BuenosAires,    //33
    Reykjavik,      //34
    Glasgow,        //35
    Warsow,         //36
    Istanbul,       //37
    Dubai,          //38
    CapeTown        //39
} place_t;
	 
char countryName[N_PLACE+1][MAX_PLACENAME] =
{   "Seoul",
    "Jeju",
    "Tokyo",
    "LosAngeles",
    "NewYork",
    "Texas",
    "Toronto",
    "Paris",
    "Nice",
    "Rome",
    "Milan",
    "London",
    "Manchester",
    "Basel",
    "Luzern",
    "Munich",
    "Frankfurt",
    "Berlin",
    "Barcelona",
    "Madrid",
    "Amsterdam",
    "Stockholm",
    "Oslo",
    "Hanoi",
    "Bangkok",
    "KualaLumpur",
    "Singapore",
    "Sydney",
    "SaoPaulo",
    "Cairo",
    "Beijing",
    "Nairobi",
    "Cancun",
    "BuenosAires",
    "Reykjavik",
    "Glasgow",
    "Warsow",
    "Istanbul",
    "Dubai",
    "CapeTown",
    "Unrecognized"
};

char* ifctele_getPlaceName(int placeIndex)
{
	return countryName[placeIndex];
}

typedef struct ifs_ele			//���������� ���� ����ü  
{
	int index;
	int age;
	int detected_time;
	//int place_t[N_HISTORY];         //�ٽ�üũ   !!!!!!!!!==> place_t history_place[N_HISTORY]�� �����ϱ�  !!!!!!
	place_t place[N_HISTORY];
	
} ifs_ele_t;

static ifs_ele_t ifsarray[20];    //�迭 19�� ��(����)  
static int ifs_cnt = 0;			//����� ȯ�� ���� -1


//fscanf�� ������ ������ ����ü �ȿ� ����  
void* ifctele_genElement(int index, int age, unsigned int detected_time, int history_place[N_HISTORY])
{
	int i;
	
	ifsarray[ifs_cnt].index = index;
	ifsarray[ifs_cnt].age = age;
	ifsarray[ifs_cnt].detected_time = detected_time;
	//if i=0����i=N_HISTORY 
	for(i=0;i<N_HISTORY;i++)
	//	ifsarray[ifs_cnt].place_t[i] = history_place[i];
		ifsarray[ifs_cnt].place[i] = history_place[i];
		
///	for(i=0;i<N_HISTORY;i++)    ����  
///		ifsarray[ifs_cnt].place_t[N_HISTORY] = history_place[N_HISTORY];  �길 ����ų� ������ �� �� �ϳ�.  
	
//	printf("%s", ifsarray[ifs_cnt]);
	ifs_cnt++;
	
	printf("%d\n", ifsarray[ifs_cnt-1].index ); //Ȯ�� ��� ����. 
	return (void *)&ifsarray[ifs_cnt-1];
}

//static int patient_selection;					//����. ���ο� ���� �������ص���? main.c���� ��� patientselection�Ѱܿ�? element.c�� �����ص� �ǳ�? 


int ifctele_getAge(void* obj)
{
	ifs_ele_t *strPtr = (ifs_ele_t *)obj; 	//����. ifs_ele_t[ifs_cnt]ó�� �迭 ?? 


	//printf("%d\n", ifsarray[ifs_cnt-1].index );		//�굵 main.c while�� �ȿ� ������ ��µǱ� ��. index�� ���� ���ϴ� �� �⤩���ϱ� �ؾ���. 
//	printf("%d\n", ifsarray[ifs_cnt-1].age );
	
//	scanf("%i", &patient_selection);
	strPtr = &ifsarray[ifs_cnt-1];
	return strPtr->age;
}

unsigned int ifctele_getinfestedTime(void* obj)
{
	ifs_ele_t *strPtr = (ifs_ele_t *)obj;
	strPtr = &ifsarray[ifs_cnt-1];
	return strPtr->detected_time;
}

int ifctele_getHistPlaceIndex(void* obj, int index)
{
	ifs_ele_t *strPtr = (ifs_ele_t *)obj;
	strPtr = &ifsarray[ifs_cnt-1];
	//return strPtr->place_t[index]; 
	return strPtr->place[index]; 
}



void ifctele_printElement(void* obj)
{
	ifs_ele_t *strPtr = (ifs_ele_t *)obj;
//	strPtr = (ifs_ele_t*)ifsarray[ifs_cnt-1].age ;
	
	////////printf("Age: %i\n", strPtr->age);
	
	printf("printElement_age: %i\n", ifctele_getAge(strPtr) );
	printf("printElement_time: %i\n", ifctele_getinfestedTime(strPtr) );
	//printf("printElement_place: %i\n", ifctele_getHistPlaceIndex(strPtr) );     //Q. �갡 ����. �޾ƿ��� ���� ������ �ٸ�. ��� ? if?  
//	strPtr = &ifsarray[ifs_cnt-1];
	//printf("%d\n", ifsarray[ifs_cnt-1].index );
		
//	ifs_ele_t.ifsarray[ifs_cnt-1] = strPtr;
//	printf("%s", );
	//printf("age: %i", ifctele_getAge( obj ) );
	//getElement�� �̿��ؼ� ���������� sample.txt�� �޾ƿ��� �ڵ� �����ϸ� ���õ�..! 
	//print element
}


