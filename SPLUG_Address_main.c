#include "RC_LinkedList.h"
#include "SPLUG_ADDRESS_BOOK.h"


int _tmain ()
{
	int iInput = 0 ;
	pHead = ( RC_LinkedList * ) malloc ( sizeof ( RC_LinkedList ) ) ;
	pTail = ( RC_LinkedList * ) malloc ( sizeof ( RC_LinkedList ) ) ;
	FILE * fAddress ;
	

	fAddress = fopen ( "Address.txt" , "r+" ) ;
	
	
	if ( NULL == fAddress)
	{
		fAddress = fopen ( "Address.txt" , "w+" ) ;
	}


	pHead -> m_pPrev = NULL ;
	pHead -> m_pNext = pTail ;
	pTail -> m_pPrev = pHead ;
	pTail -> m_pNext = NULL ;


	File_Load ( fAddress ) ;


	while ( 6 != iInput )
	{
		printf ( "Menu\n" ) ;
		printf ( "1. Print all address information.\n" ) ;
		printf ( "2. Register member.\n" ) ;
		printf ( "3. Find member information.\n" ) ;
		printf ( "4. Modify member information.\n" ) ;
		printf ( "5. Remove Member\n" ) ;
		printf ( "6. Exit Program\n" ) ;
		printf ( "Input : " ) ;

		scanf ( "%d" , & iInput ) ;

		fflush ( stdin ) ;


		switch ( iInput )
		{
			case 1 :
				Print_All () ;
				break ;
			case 2 :
				Register_Member ( false , NULL ) ;
				break ;
			case 3 :
				Search_Member () ;
				break ;
			case 4 :
				Modify_Member () ;
				break ;
			case 5 :
				Delete_Member () ;
				break ;
			case 6 :
			default :
				break ;
		}
	}


	File_Save ( fAddress ) ;


	fclose ( fAddress ) ;
	All_free ( pHead ) ;
}

