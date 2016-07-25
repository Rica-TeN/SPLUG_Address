#ifndef SPLUG_ADDRESS_BOOK_H
#define SPLUG_ADDRESS_BOOK_H



#include "RC_LinkedList.h"

void File_Load ( FILE * fAddress ) ;
void File_Save ( FILE * fAddress ) ;

void Print_All () ;
void Register_Member ( bool bModify , RC_LinkedList * pNode ) ;
void Search_Member () ;
void Modify_Member () ;
void Delete_Member () ;
void Print_One_Member ( RC_LinkedList * pNode ) ;
RC_LinkedList * Find_Member ( int iMenu , RC_LinkedList * pInput , char * cNameInput ) ;
RC_LinkedList * Sort_Name_Find_Member ( RC_LinkedList * pNode ) ;
void RC_Copy_Nto0 ( char * cpOrigin , char * cpCopy , int iOrigin_Index , int iCopy_Index , int iLength ) ;
void Remove_Line_Escape_Sequence ( RC_LinkedList * pNode ) ;


All_free ( RC_LinkedList * pNode ) ;


RC_LinkedList * pHead ;
RC_LinkedList * pTail ;



#endif