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

typedef struct ifs_ele			//감염자정보 저장 구조체  
{
	int index;
	int age;
	int detected_time;
	//int place_t[N_HISTORY];         //다시체크   !!!!!!!!!==> place_t history_place[N_HISTORY]로 변경하기  !!!!!!
	place_t place[N_HISTORY];
	
} ifs_ele_t;

static ifs_ele_t ifsarray[20];    //배열 19개 씀(변경)  
static int ifs_cnt = 0;			//저장된 환자 갯수 -1


//fscanf로 가져온 정보를 구조체 안에 저장  
void* ifctele_genElement(int index, int age, unsigned int detected_time, int history_place[N_HISTORY])
{
	int i;
	
	ifsarray[ifs_cnt].index = index;
	ifsarray[ifs_cnt].age = age;
	ifsarray[ifs_cnt].detected_time = detected_time;
	//if i=0부터i=N_HISTORY 
	for(i=0;i<N_HISTORY;i++)
	//	ifsarray[ifs_cnt].place_t[i] = history_place[i];
		ifsarray[ifs_cnt].place[i] = history_place[i];
		
///	for(i=0;i<N_HISTORY;i++)    삭제  
///		ifsarray[ifs_cnt].place_t[N_HISTORY] = history_place[N_HISTORY];  얘만 남기거나 위에꺼 둘 중 하나.  
	
//	printf("%s", ifsarray[ifs_cnt]);
	ifs_cnt++;
	
	printf("%d\n", ifsarray[ifs_cnt-1].index ); //확인 결과 성공. 
	return (void *)&ifsarray[ifs_cnt-1];
}

//static int patient_selection;					//질문. 새로운 변수 설정ㅇ해도됨? main.c에서 어떻게 patientselection넘겨옴? element.c에 선언해도 되나? 


int ifctele_getAge(void* obj)
{
	ifs_ele_t *strPtr = (ifs_ele_t *)obj; 	//생각. ifs_ele_t[ifs_cnt]처럼 배열 ?? 


	//printf("%d\n", ifsarray[ifs_cnt-1].index );		//얘도 main.c while문 안에 넣으면 출력되긴 함. index에 따라서 원하는 값 출ㄹ력하기 해야함. 
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
	//printf("printElement_place: %i\n", ifctele_getHistPlaceIndex(strPtr) );     //Q. 얘가 문제. 받아오는 값의 갯수가 다름. 어떻게 ? if?  
//	strPtr = &ifsarray[ifs_cnt-1];
	//printf("%d\n", ifsarray[ifs_cnt-1].index );
		
//	ifs_ele_t.ifsarray[ifs_cnt-1] = strPtr;
//	printf("%s", );
	//printf("age: %i", ifctele_getAge( obj ) );
	//getElement를 이용해서 감염자정보 sample.txt를 받아오는 코드 구현하면 나올듯..! 
	//print element
}


