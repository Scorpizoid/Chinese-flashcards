/*
* ============================================================================
*  Name         : Kiina.cpp
*  Part of      : Kiina
*  Interface    : Browser Control API
*  Description  : Implements the main application class.
*  Version      : 
*
*  Copyright (c) 2005-2006 Nokia Corporation.
*  This material, including documentation and any related 
*  computer programs, is protected by copyright controlled by 
*  Nokia Corporation. 
* ============================================================================
*/

// INCLUDE FILES
#include "Kiina.h"
#include "KiinaDocument.h"
#include <eikstart.h>

// ================= MEMBER FUNCTIONS =======================

// ---------------------------------------------------------
// CKiina::AppDllUid()
// Returns application UID
// ---------------------------------------------------------
//
TUid CKiina::AppDllUid() const
    {
    return KUidKiina;
    }

// ---------------------------------------------------------
// CDictionaryStore* CKiina::OpenIniFileLC(RFs& aFs) const
// overrides CAknApplication::OpenIniFileLC to enable INI file support
// ---------------------------------------------------------
//
CDictionaryStore* CKiina::OpenIniFileLC(RFs& aFs) const
{
    return CEikApplication::OpenIniFileLC(aFs);
}
   
// ---------------------------------------------------------
// CKiina::CreateDocumentL()
// Creates CKiinaDocument object
// ---------------------------------------------------------
//
CApaDocument* CKiina::CreateDocumentL()
    {
    return CKiinaDocument::NewL( *this );
    }

// ================= OTHER EXPORTED FUNCTIONS ==============
//
// ---------------------------------------------------------
// NewApplication() 
// Constructs CKiina
// Returns: created application object
// ---------------------------------------------------------
//
LOCAL_C CApaApplication* NewApplication( )
	{
    return new CKiina;
    }
    

// ---------------------------------------------------------
//    E32Main
//    Main function for Symbian OS v9 EXE application
//    Returns: TInt
// ---------------------------------------------------------
GLDEF_C TInt E32Main()
    {
    return EikStart::RunApplication( NewApplication );
    }

// End of File  

