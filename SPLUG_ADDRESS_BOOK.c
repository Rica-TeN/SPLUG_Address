#include "RC_LinkedList.h"
#include "SPLUG_ADDRESS_BOOK.h"


int iCount = 0 ;


/*
 * Load File and add to LinkedList
 */
void File_Load ( FILE * fAddress )
{
	int i = 0 ;
	int iTemp = 0 ;
	char cTemp [ 150 ] ;
	char cNum [ 11 ] ;


	while ( ( NULL != fAddress ) && ( fgets ( cTemp , 149 , fAddress ) ) )
	{
		/*if ( 0 != feof ( fAddress ) )						//////// FFFFFFFFFUCCCCCCCCCCCCCCCKKKKKKKKKKKKKKK YYOOOOOOOOOOOOOOOOOOOUUUUUUUUUUU EEEEEEEEEEOOOOOOOOOOOFFFFF
		{
			break ;
		}*/


		pTail -> m_pPrev -> m_pNext = ( RC_LinkedList * ) malloc ( sizeof ( RC_LinkedList ) ) ;							// pNode -> m_pNext = pNew


		pTail -> m_pPrev -> m_pNext -> m_pNext = pTail ;																// pNew -> m_pNext = pTail
		pTail -> m_pPrev -> m_pNext -> m_pPrev = pTail -> m_pPrev ;														// pNew -> m_pPrev = pNode
		pTail -> m_pPrev = pTail -> m_pPrev -> m_pNext ;																// pTail -> m_pPrev = pNew


		//fscanf ( fAddress , "%s\t\t%s\t\t%ld\n" , pTail -> m_pPrev -> m_crgName , pTail -> m_pPrev -> m_crgAddress , & pTail -> m_pPrev -> m_lNumber ) ;
	//	fgets ( cTemp , 149 , fAddress ) ;
		printf ( "feof : %lf\n" , feof ( fAddress ) ) ;
		puts ( cTemp ) ;

		while ( '\n' != cTemp [ i ] )
		{
			++ i ;


			if ( ( '\t' == cTemp [ i - 1 ] ) && ( '\t' == cTemp [ i ] ) && ( ! iTemp ) )
			{
				cTemp [ i - 1 ] = '\0' ;
				RC_Copy_Nto0 ( cTemp , pTail -> m_pPrev -> m_crgName , 0 , 0 , i ) ;
				iTemp = i + 1 ;
			}
			else if ( ( '\t' == cTemp [ i - 1 ] ) && ( '\t' == cTemp [ i ] ) )
			{
				cTemp [ i - 1 ] = '\0' ;
				RC_Copy_Nto0 ( cTemp , pTail -> m_pPrev -> m_crgAddress , iTemp , 0 , i - iTemp ) ;
				iTemp = i + 1 ;
			}
		}

		RC_Copy_Nto0 ( cTemp , cNum , iTemp , 0 , i - iTemp ) ;

		pTail -> m_pPrev -> m_lNumber = atol ( cNum ) ;

		++ iCount ;
	}
}

 /*
  * Save File.
  */
void File_Save ( FILE * fAddress )
{
	if ( iCount )
	{
		RC_LinkedList * pNode = pHead -> m_pNext ;
		int i = 0 ;


		for ( i = 0 ; i < iCount ; ++i )
		{
			fprintf ( fAddress , "%s\t\t%s\t\t0%ld\n" , pNode -> m_crgName , pNode -> m_crgAddress , pNode -> m_lNumber ) ;
			pNode = pNode -> m_pNext ;
		}
	}
}


/*
 * Print all member's information.
 */
void Print_All ()
{
	int i = 0 ;
	RC_LinkedList * pNode = pHead -> m_pNext ;


	if ( iCount )
	{
		for ( i = 0 ; i < iCount ; ++i )
		{
			printf ( "#%d\n" , i + 1 ) ;
			Print_One_Member ( pNode ) ;
			pNode = pNode -> m_pNext ;
		}
	}
	else
	{
		printf ( "There's no member.\n" ) ;
	}
}

/*
 * Register Function.
 * Modify one member's information, or Register new member.
 */

void Register_Member ( bool bModify , struct RC_LinkedList * pModify )
{
	if ( bModify )
	{
		RC_LinkedList * pTemp = ( RC_LinkedList * ) malloc ( sizeof ( RC_LinkedList ) ) ;
		char cTemp = 0 ;
		bool bCheck = true ;				// bCheck is true, then ask modify.


		printf ( "Name : " ) ;
		scanf ( "%s" , pTemp -> m_crgName ) ;
		fflush ( stdin ) ;
		printf ( "Address : " ) ;		
		fgets ( pTemp -> m_crgAddress , 99 , stdin ) ;
		printf ( "Number : " ) ;
		scanf ( "%ld" , & pTemp -> m_lNumber ) ;

		fflush ( stdin ) ;

		printf ( "Save? ( Y or N ) : " ) ;
		scanf ( "%c" , & cTemp ) ;


		while ( bCheck )
		{
			// Modify
			if ( ( 'Y' == cTemp ) || ( 'y' == cTemp ) )
			{
				pModify -> m_pNext -> m_pPrev = pTemp ;
				pModify -> m_pPrev -> m_pNext = pTemp ;
				pTemp -> m_pNext = pModify -> m_pNext ;
				pTemp -> m_pPrev = pModify -> m_pPrev ;
				bCheck = false ;
				Remove_Line_Escape_Sequence ( pTemp ) ;

				free ( pModify ) ;
			

				printf ( "Modify Finished.\n" ) ;
			}
			// Ignore
			else if ( ( 'N' == cTemp ) || ( 'n' == cTemp ) )
			{
				bCheck = false ;

				free ( pTemp ) ;


				printf ( "Modify Cancel.\n" ) ;
			}
			else
			{
				printf ( "Input Y or N : " ) ;
				scanf ( "%c" , cTemp ) ;
			}
		}
	}
	else
	{
		RC_LinkedList * pNode = ( RC_LinkedList * ) malloc ( sizeof ( RC_LinkedList ) ) ;
		RC_LinkedList * pSort ; 

			
		printf ( "Name : " ) ;
		scanf ( "%s" , pNode -> m_crgName ) ;
		
		printf ( "Address : " ) ;
		fflush ( stdin ) ;
		fgets ( pNode -> m_crgAddress , 99 , stdin ) ;
		fflush ( stdin ) ;
		printf ( "Number : " ) ;
		scanf ( "%ld" , & pNode -> m_lNumber ) ;

		pSort = Sort_Name_Find_Member ( pNode ) ;
		Remove_Line_Escape_Sequence ( pNode ) ;

		pSort -> m_pNext -> m_pPrev = pNode ;
		pNode -> m_pNext = pSort -> m_pNext ;
		pSort -> m_pNext = pNode ;
		pNode -> m_pPrev = pSort ;

		++ iCount ;
	}
}


/*
 * Print Member. It's Menu function.
 * TODO Additional Implementation 1 , 2	
 */
void Search_Member ()
{
	int iMenu = 0 ;
	RC_LinkedList * pNode = pHead ;
	char cName [ 10 ] ;


	printf ( "Search Member. Choose Method\n" ) ;
	printf ( "1. Name\n" ) ;
	printf ( "2. Address\n" ) ;
	printf ( "3. Number\n" ) ;
	printf ( "Input : " ) ;

	scanf ( "%d" , & iMenu ) ;

	while ( NULL != pNode )
	{
		switch ( iMenu )
		{
			case 1 :
				pNode = Find_Member ( 1 , pHead , cName ) ;


				if ( NULL != pNode )
				{
					while ( NULL != pNode )
					{
						Print_One_Member ( pNode ) ;


						if ( strcmp ( pNode -> m_crgName , pNode -> m_pNext -> m_crgName ) )
							pNode = NULL ;
						else
							pNode = pNode -> m_pNext ;
					}
				}
				else
				{
					pNode = pHead ;


					while ( NULL != pNode )
					{
						pNode = Find_Member ( 4 , pNode , cName ) ;

						if ( NULL != pNode )
						{
							Print_One_Member ( pNode ) ;
							iMenu = 0 ;
						}
					}
				}


				break ;

			case 2 :
				pNode = Find_Member ( 2 , pNode , NULL ) ;


				break ;

			case 3 :
				pNode = Find_Member ( 3 , pNode , NULL ) ;


				break ;

			default :
				break ;
		}
	}
}

/*
 * Modify one member's information.
 */

void Modify_Member ()
{
	RC_LinkedList * pNode = Find_Member ( 1 , pHead , NULL ) ;


	if ( NULL != pNode )
		Register_Member ( true , pNode ) ;
	else
		printf ( "Member doesn't exist.\n" ) ;
}

/*
 * Delete Member.
 */

void Delete_Member ()
{
	RC_LinkedList * pDelete = Find_Member ( 1 , pHead , NULL ) ;
	RC_LinkedList * pDelPrev = NULL ;
	RC_LinkedList * pDelNext = NULL ;


	if ( NULL != pDelete )
	{
		pDelPrev = pDelete -> m_pPrev ;
		pDelNext = pDelete -> m_pNext ;
		pDelPrev -> m_pNext = pDelNext ;
		pDelNext -> m_pPrev = pDelPrev ;
		-- iCount ;


		free ( pDelete ) ;
	}
	else
		printf ( "Member doesn't exist.\n" ) ;
}

/*
 * Print only one Member.
 */
void Print_One_Member ( struct RC_LinkedList * pNode )
{
	printf ( "Name : %s\n" , pNode -> m_crgName ) ;
	printf ( "Address : %s\n" , pNode -> m_crgAddress ) ;
	printf ( "Number : 0%ld\n" , pNode -> m_lNumber ) ;
}

/*
 * Find specific Member.
 * 1 is Name
 * 2 is Address
 * 3 is Number
 * return value is specific Node or NULL.
 */
RC_LinkedList * Find_Member ( int iMenu , RC_LinkedList * pInput , char * cNameInput )
{
	char crgInput [ 100 ] ;
	char crgTemp [ 50 ] ;
	RC_LinkedList * pNode = pInput ;
	bool bCheck = false ;
	int i = 0 ;
	long lTemp = 0 ;


	if ( 1 == iMenu )
	{
		printf ( "Input Name : " ) ;

		scanf ( "%s" , crgInput ) ;


		if ( iCount )
		{
			if ( NULL != cNameInput )
			{
				strncpy ( cNameInput , crgInput , 9 ) ;
			}


			while ( NULL != pNode )
			{
				pNode = pNode -> m_pNext ;

				if ( strcmp ( pNode -> m_crgName , crgInput ) > 0 )								// Input is Echo, pNode's name is Foxtro.
				{
					pNode = NULL ;
					break ;
				}
				else if ( ( NULL == pNode ) || ( ! strcmp ( pNode -> m_crgName , crgInput ) ) )
				{
					break ;
				}
			}
		}
		else
		{
			pNode = NULL ;
		}
	}
	else if ( 2 == iMenu )
	{
		printf ( "Input Address : " ) ;
		
		fflush ( stdin ) ;
		fgets ( crgInput , 99 , stdin ) ;
		fflush ( stdin ) ;


		while ( '\n' != crgInput [ i ] )
		{
			++ i ;
		}


		crgInput [ i ] = '\0' ;

		while ( NULL != pNode )
		{
			if ( iCount )
			{
				pNode = pNode -> m_pNext ;


				if ( pTail == pNode )
				{
					pNode = NULL ;
					break ;
				}

				for ( i = 0 ; i < strlen ( pNode -> m_crgAddress ) - strlen ( crgInput ) + 1 ; ++i  )
				{
					RC_Copy_Nto0 ( pNode -> m_crgAddress , crgTemp , i , 0 , strlen ( crgInput ) ) ;
					
					
					if ( ! strcmp ( crgInput , crgTemp ) )
					{
						Print_One_Member ( pNode ) ;
						iMenu = 0 ;
						break ;
					}
				}

			}
			else
				pNode = NULL ;
		}

		if ( iMenu )
			printf ( "Member doesn't exist.\n" ) ;


	}
	else if ( 3 == iMenu )
	{
		printf ( "Input Number : " ) ;
		
		scanf ( "%ld" , & lTemp ) ;


		while ( NULL != pNode )
		{
			if ( iCount )
			{
				pNode = pNode -> m_pNext ;

				
				if ( pTail == pNode )
				{
					pNode = NULL ;
				}
				else if ( lTemp == pNode -> m_lNumber )
				{
					Print_One_Member ( pNode ) ;
					iMenu = 0 ;
				}
			}
			else
				pNode = NULL ;
		}

		if ( iMenu )
			printf ( "Member doesn't exist.\n" ) ;


	}
	else if ( 4 == iMenu )
	{
		if ( iCount )
		{
			while ( ( NULL != pNode ) && ( iMenu ) )
			{
				pNode = pNode -> m_pNext ;

				for ( i = 0 ; i < strlen ( pNode -> m_crgName ) - strlen ( cNameInput ) + 1 ; ++i  )
				{
					RC_Copy_Nto0 ( pNode -> m_crgName , crgTemp , i , 0 , strlen ( cNameInput ) ) ;
					
					
					if ( pTail == pNode )
					{
						pNode = NULL ;
						break ;
					}
					else if ( ! strcmp ( cNameInput , crgTemp ) )
					{
						iMenu = 0 ;
						break ;
					}
				}
			}
		}
		else if ( iMenu )
		{
			printf ( "Member doesn't exist.\n" ) ;
			pNode = NULL ;
		}
	}
	

	return pNode ;
}

/*
 * Parameter Node need to be sorted.
 * Compare Node's name, and find sequence.
 * return value is pSort.
 * pSort -> m_pNext = pNode
 */
RC_LinkedList * Sort_Name_Find_Member ( RC_LinkedList * pNode )
{
	RC_LinkedList * pSort = pHead ;
	char cSort_Name [ 3 ] ;
	char cNode_Name [ 3 ] ;
	int iRec_cnt = 0 ;

	
	cSort_Name [ 2 ] = '\0' ;
	cNode_Name [ 2 ] = '\0' ;


	while ( pSort -> m_pNext != pTail )
	{
		pSort = pSort -> m_pNext ;
		strncpy ( cSort_Name , pSort -> m_crgName , 2 ) ;
		strncpy ( cNode_Name , pNode -> m_crgName , 2 ) ;


		while ( ! strcmp ( cSort_Name , cNode_Name ) )			// cSort is B?? , cNode is B??
		{
			iRec_cnt += 2 ;


			if ( 0 == ( strlen ( pSort -> m_crgName ) - iRec_cnt ) && ( 0 == ( strlen ( pNode -> m_crgName ) - iRec_cnt ) ) )			// cSort is Badc, cNode is Badc.	
			{
				// Can't get in here.
			}
			else if ( 0 == ( strlen ( pSort -> m_crgName ) - iRec_cnt ) )				// cSort is B , cNode is Ba
			{
				break ;
			}
			else if ( 0 == ( strlen ( pNode -> m_crgName ) - iRec_cnt ) )				// cSort is Bb , cNode is B
			{
				cSort_Name [ 0 ] = 'B' ;
				cNode_Name [ 0 ] = 'A' ;

				break ;
			}
			else
			{
				RC_Copy_Nto0 ( pSort -> m_crgName , cSort_Name , iRec_cnt , 0 , 2 ) ;
				RC_Copy_Nto0 ( pNode -> m_crgName , cNode_Name , iRec_cnt , 0 , 2 ) ;
			}
		}
		
		if ( strcmp ( cSort_Name , cNode_Name ) > 0 )			// cSort is B , cNode is A
		{
			pSort = pSort -> m_pPrev ;							// then pSort needed to moved left.
			break ;
		}
		else if ( iRec_cnt )									// cSort is Ba , cNode is Bb
		{
			iRec_cnt = 0 ;
		}
	}
	

	 return pSort ;
}

/*
 * Made by RC.
 * strcpy, [ n ] to [ 0 ]
 */
void RC_Copy_Nto0 ( char * cpOrigin , char * cpCopy , int iOrigin_Index , int iCopy_Index , int iLength )
{
	int i = 0 ;


	for ( i = 0 ; i < iLength ; ++i )
	{
		cpCopy [ iCopy_Index + i ] = cpOrigin [ iOrigin_Index + i ] ;
	}


	cpCopy [ i ] = '\0' ;
}

/*
 * Remove \n. gets () save \n.
 */
void Remove_Line_Escape_Sequence ( RC_LinkedList * pNode )
{
	int i = 0 ;


	while ( '\n' != pNode -> m_crgAddress [ i ] )
	{
		++ i ;
	}

	pNode -> m_crgAddress [ i ] = '\0' ;
}

/*
 * free or delete all malloc or new.
 */
All_free ( RC_LinkedList * pNode )
{
	while ( pTail != pNode )
	{
		pNode = pNode -> m_pNext ;

		free ( pNode -> m_pPrev ) ;
	}

	free ( pNode ) ;
}