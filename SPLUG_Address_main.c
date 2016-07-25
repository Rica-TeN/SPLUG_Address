#include "RC_LinkedList.h"
#include "SPLUG_ADDRESS_BOOK.h"


int _tmain ()
{
	int iInput = 0 ;
	int iCnt = 0 ;
	pHead = ( RC_LinkedList * ) malloc ( sizeof ( RC_LinkedList ) ) ;
	pTail = ( RC_LinkedList * ) malloc ( sizeof ( RC_LinkedList ) ) ;
	FILE * fAddress = fopen ( "Address.txt" , "r+" ) ;
	
	
	if ( NULL == fAddress)
	{
		fAddress = fopen ( "Address.txt" , "w+" ) ;
	}


	pHead -> m_pPrev = NULL ;
	pHead -> m_pNext = pTail ;
	pTail -> m_pPrev = pHead ;
	pTail -> m_pNext = NULL ;


	File_Load ( fAddress ) ;
	fclose ( fAddress ) ;

	Menu_Print () ;


	while ( 6 != iInput )
	{
		if ( 2 == iCnt )
		{
			Menu_Print () ;
			iCnt = 0 ;
		}


		printf ( "============================\n" ) ;
		printf ( "선택할 기능을 입력하세요 : " ) ;


		scanf ( "%d" , & iInput ) ;

		fflush ( stdin ) ;


		switch ( iInput )
		{
			case 1 :
				printf ( "============================\n" ) ;
				Print_All () ;
				++ iCnt ;
				break ;
			case 2 :
				printf ( "============================\n" ) ;
				Register_Member ( false , NULL ) ;
				++ iCnt ;
				break ;
			case 3 :
				printf ( "============================\n" ) ;
				Search_Member () ;
				++ iCnt ;
				break ;
			case 4 :
				printf ( "============================\n" ) ;
				Modify_Member () ;
				++ iCnt ;
				break ;
			case 5 :
				printf ( "============================\n" ) ;
				Delete_Member () ;
				++ iCnt ;
				break ;
			case 6 :
			default :
				break ;
		}
	}


	fAddress = fopen ( "Address.txt" , "w+" ) ;


	File_Save ( fAddress ) ;


	fclose ( fAddress ) ;
	All_free ( pHead ) ;
}

