#ifndef RC_LINKEDLIST_H
#define RC_LINKEDLIST_H



#include <Windows.h>
#include <tchar.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>


typedef struct RC_LinkedList
{
	char m_crgName [ 9 ] ;
	char m_crgAddress [ 100 ] ;
	long m_lNumber ;

	struct RC_LinkedList * m_pPrev ;
	struct RC_LinkedList * m_pNext ;
} RC_LinkedList ;


#endif