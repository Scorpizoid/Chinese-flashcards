/*
* ============================================================================
*  Name        : KiinaUi.cpp
*  Part of     : Kiina
*  Interface   : Browser Control API
*  Description : The Ui class for the Browser Control Sample Application
*  Version     : 
*
*  Copyright (c) 2005-2006 Nokia Corporation.
*  This material, including documentation and any related 
*  computer programs, is protected by copyright controlled by 
*  Nokia Corporation.
* ============================================================================
*/

// INCLUDE FILES
#include "KiinaUi.h"
#include "KiinaContainer.h" 
#include <Kiina.rsg>
#include "Kiina.hrh"
#include <S32FILE.H>

#include <avkon.hrh>


// ================= MEMBER FUNCTIONS =======================
//
// ----------------------------------------------------------
// CKiinaUi::ConstructL()
// ?implementation_description
// ----------------------------------------------------------
//
void CKiinaUi::ConstructL()
    {
    BaseConstructL(CAknAppUi::EAknEnableSkin);
    iAppContainer = new (ELeave) CKiinaContainer;
    iAppContainer->SetMopParent(this);
    iAppContainer->ConstructL( ClientRect() );
    
    
    
	// INI-tiedoston muuttujat
    
_LIT(KSunClockIniFileName,"c:\\private\\2002AA27\\settings.ini");
TFileName iniFileName=static_cast<TFileName>(KSunClockIniFileName);
RFs fs;


	// Käynnistettäessä ohjelmaa, avataan INI-tiedosto, tai jos sitä
	// ei ole, luodaan se (OpenL()-funktio)
/////////////////////////////////////////////////////////////////////////
fs.Connect();
CFileStore* store=NULL;
TRAPD(err,store=CDirectFileStore::OpenL(fs,iniFileName,EFileShareAny));
if (err==KErrNone)
{
CleanupStack::PushL(store);
RStoreReadStream inStream;
inStream.OpenLC(*store,store->Root());
iAppContainer->InternalizeL(inStream);
CleanupStack::PopAndDestroy(2); // inStream + store
}




fs.Close();    AddToStackL( iAppContainer );
    }

// ----------------------------------------------------
// CKiinaUi::~CKiinaUi()
// Destructor
// Frees reserved resources
// ----------------------------------------------------
//
CKiinaUi::~CKiinaUi()
    {
    if (iAppContainer)
        {
        RemoveFromStack( iAppContainer );
        delete iAppContainer;
        }

   }

// ------------------------------------------------------------------------------
// CKiinaUi::::DynInitMenuPaneL(TInt aResourceId,CEikMenuPane* aMenuPane)
//  This function is called by the EIKON framework just before it displays
//  a menu pane. Its default implementation is empty, and by overriding it,
//  the application can set the state of menu items dynamically according
//  to the state of application data.
// ------------------------------------------------------------------------------
//
void CKiinaUi::DynInitMenuPaneL(
    TInt aResourceId,CEikMenuPane* aMenuPane)
    {
    iAppContainer->DynInitMenuPaneL(aResourceId, aMenuPane);
    }

// ----------------------------------------------------
// CKiinaUi::HandleKeyEventL(
//     const TKeyEvent& aKeyEvent,TEventCode /*aType*/)
// ?implementation_description
// ----------------------------------------------------
//
TKeyResponse CKiinaUi::HandleKeyEventL(
    const TKeyEvent& aKeyEvent,TEventCode aType)
    {
    return iAppContainer->HandleKeyEventL(aKeyEvent, aType);;
    }

// ----------------------------------------------------
// CKiinaUi::HandleCommandL(TInt aCommand)
// ?implementation_description
// ----------------------------------------------------
//
void CKiinaUi::HandleCommandL(TInt aCommand)
    {
    switch ( aCommand )
        {
        case EEikCmdExit:
        case EAknSoftkeyExit:
            {
    		iAppContainer->SaveL();
           Exit();
            break;
            }

      default:
            iAppContainer->HandleCommandL(aCommand);
            break;      
        }
    }

// End of File  

