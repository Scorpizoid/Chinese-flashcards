/*
* ============================================================================
*  Name         : KiinaDocument.h
*  Part of      : Kiina
*  Interface   	: Browser Control API 
*  Description  : Implements the document for application.
*  Version      : 
*
*  Copyright (c) 2005-2006 Nokia Corporation.
*  This material, including documentation and any related 
*  computer programs, is protected by copyright controlled by 
*  Nokia Corporation.
* ============================================================================
*/

// INCLUDE FILES
#include "KiinaDocument.h"
#include "KiinaUi.h"

// ================= MEMBER FUNCTIONS =======================

// constructor
CKiinaDocument::CKiinaDocument(CEikApplication& aApp)
: CAknDocument(aApp)    
    {
    }

// destructor
CKiinaDocument::~CKiinaDocument()
    {
    }

// EPOC default constructor can leave.
void CKiinaDocument::ConstructL()
    {
    }

// Two-phased constructor.
CKiinaDocument* CKiinaDocument::NewL(
        CEikApplication& aApp)     // CKiina reference
    {
    CKiinaDocument* self = new (ELeave) CKiinaDocument( aApp );
    CleanupStack::PushL( self );
    self->ConstructL();
    CleanupStack::Pop();

    return self;
    }
    
// ----------------------------------------------------
// CKiinaDocument::CreateAppUiL()
// constructs CKiinaUi
// ----------------------------------------------------
//
CEikAppUi* CKiinaDocument::CreateAppUiL()
    {
    return new (ELeave) CKiinaUi;
    }

// End of File  

