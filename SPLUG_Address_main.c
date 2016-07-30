#include "RC_LinkedList.h"
#include "SPLUG_ADDRESS_BOOK.h"


int _tmain ()
{
	int iInput = 0 ;
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
		printf ( "============================\n" ) ;
		printf ( "선택할 기능을 입력하세요 : " ) ;


		scanf ( "%d" , & iInput ) ;

		fflush ( stdin ) ;


		switch ( iInput )
		{
			case 1 :
				Menu_Print () ;
				printf ( "============================\n" ) ;
				printf ( "선택할 기능을 입력하세요 : %d\n" , iInput ) ;
				printf ( "============================\n" ) ;
				Print_All () ;
				break ;
			case 2 :
				Menu_Print () ;
				printf ( "============================\n" ) ;
				printf ( "선택할 기능을 입력하세요 : %d\n" , iInput ) ;
				printf ( "============================\n" ) ;
				Register_Member ( false , NULL ) ;
				break ;
			case 3 :
				Menu_Print () ;
				printf ( "============================\n" ) ;
				printf ( "선택할 기능을 입력하세요 : %d\n" , iInput ) ;
				printf ( "============================\n" ) ;
				Search_Member () ;
				break ;
			case 4 :
				Menu_Print () ;
				printf ( "============================\n" ) ;
				printf ( "선택할 기능을 입력하세요 : %d\n" , iInput ) ;
				printf ( "============================\n" ) ;
				Modify_Member () ;
				break ;
			case 5 :
				Menu_Print () ;
				printf ( "============================\n" ) ;
				printf ( "선택할 기능을 입력하세요 : %d\n" , iInput ) ;
				printf ( "============================\n" ) ;
				Delete_Member () ;
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

