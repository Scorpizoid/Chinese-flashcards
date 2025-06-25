/*
* ============================================================================
*  Name         : KiinaContainer.h
*  Part of      : Kiina
*  Interface    : Browser Control API
*  Description  : Declares container control for Browser Control Sample application.
*  Version      : 
*
*  Copyright (c) 2005-2006 Nokia Corporation.
*  This material, including documentation and any related 
*  computer programs, is protected by copyright controlled by 
*  Nokia Corporation.
* ============================================================================
*/

#ifndef KIINACONTAINER_H
#define KIINACONTAINER_H

// INCLUDES
#include <coecntrl.h>
#include <akndef.h>
#include <fbs.h>
#include <BITSTD.H>
#include "BrCtlInterface.h"
#include <MdaAudioSamplePlayer.h>

/*
// FORWARD DECLARATIONS
class CKiinaSpecialLoadObserver;
class CKiinaLayoutObserver;
class CKiinaSoftkeysObserver;
class CKiinaLoadEventObserver;
class CKiinaLinkResolver;
class CKiinaStateChangeObserver;
class CKiinaDialogsProvider;
*/
// CLASS DECLARATION

/**
*  CKiinaContainer class.
*  This is the container control class.
*/
class CKiinaContainer : public CCoeControl, MCoeControlObserver, MBrCtlDataLoadSupplier
    {
    public: // Constructors and destructor
        
        /**
        * EPOC default constructor.
        * @param aRect Frame rectangle for container.
        */
        void ConstructL(const TRect& aRect);

        /**
        * Destructor.
        */
        ~CKiinaContainer();

    public: // New functions

        /**
        * Pass a command to the Browser Control
        * @since 2.8
        * @param aCommand The command that the Browser Control should process
        * @return void
        */
        void HandleCommandL(TInt aCommand);

        /**
        * Dynamically initialises a menu pane. The Uikon framework calls this 
        *   function, if it is implemented in a menuís observer, immediately before 
        *   the menu pane is activated. 
        * @since 2.8
        * @param aResourceId Resource ID identifying the menu pane to initialise
        * @param aMenuPane The in-memory representation of the menu pane.
        * @return void
        */
        void DynInitMenuPaneL(TInt aResourceId, CEikMenuPane* aMenuPane);

        /**
        * Handles key events
        * @since 2.8
        * @param aKeyEvent The key event that occurred.
        * @param aType The window server event type that is being handled
        * @return TKeyResponse Value indicates whether or not the key event was consumed by the control. The default implementation simply returns EKeyWasNotConsumed.
        */
        TKeyResponse HandleKeyEventL(const TKeyEvent& aKeyEvent,TEventCode aType);
        
        /**
        * Accessor method for iText
        * @since 2.8
        * @param void
        * @return TDesc& The descriptor of the text
        */
//        inline const TDesC& Text() const {return iText;}
       
        /**
        * Setter method for iText
        * @since 2.8
        * @param aText The descriptor for the text you wish to display
        * @return void
        */
        void SetText( const TDesC& aText );
        
        /**
        * Setter method for iPoint
        * @since 2.8
        * @param aPoint The point at which you want to display the text
        * @return void
        */
        void SetPoint( const TPoint& aPoint );
        
        /**
        * Accessor method iBrCtlInterface
        * @since 2.8
        * @param void
        * @return CBrCtlInterface* A pointer to the browser control interface as a convenience to the observers
        */
        inline CBrCtlInterface* BrCtlInterface() const {return iBrCtlInterface;}

		// INI-tiedoston k‰sittelyyn liittyv‰t
		// funktiot
    void ExternalizeL(RWriteStream& aOut) const;
    void InternalizeL(RReadStream& aIn);
    void SaveL();

		// Palauttaa INI-tiedoston ID:n
    TStreamId StoreL( CStreamStore& aStore) const;
		// ?
	void RestoreL(const CStreamStore& aStore, TStreamId aId);
	void FlashCardLoader() const;

	TInt FlashCardNumber;
	TInt FlashCardPinYin;
	TInt FlashCardFinnish;
	TInt MaxFlashCards;
	TInt FlashCardHanzi;
	
	// Mode = 0: hanzit ylh‰‰ll‰
	// Mode = 1: suomennos ylh‰‰ll‰
	TInt FlashCardMode;
        
        
    private: // Functions from base classes

        /**
        * From CoeControl,SizeChanged.
        */
        void SizeChanged();

        /**
        * From CoeControl,CountComponentControls.
        */
        TInt CountComponentControls() const;

        /**
        * From CCoeControl,ComponentControl.
        */
        CCoeControl* ComponentControl(TInt aIndex) const;

        /**
        * From CCoeControl,Draw.
        */
        void Draw(const TRect& aRect) const;

        /**
        * Handle key events.
        */
        TKeyResponse OfferKeyEventL(const TKeyEvent& aKeyEvent,TEventCode aType);
        void SetItems();

        /**
        * From MBrCtlDataLoadSupplier, Cancel an on-going load
        */
        void CancelLoad();

        /**
        * Create a Basic Browser Control that does not have observers with scrolling
        * and HTTP framework capabilities
        */
        //void CreateBasicBrowserControlL();

        /**
        * Create Browser Control with observers with the given capabilities
        */
       // void CreateBrowserControlWithObserversL(TUint aCapabilities);

	    /**
        * Read the file.
        */
        HBufC8* ReadFileLC(const TDesC& aFileName);

        /**
        * Handles an event from an observed control.
        */
        void HandleControlEventL(CCoeControl* aControl,TCoeEvent aEventType);
        
        /**
        * The following methods are used to demonstrate the functionality of 
        * the browser control API
        */
        void BasicBrowserControlL(TInt x, TInt y);
        void OpenAboutBoxL();
        void Laskut();
        void CheckWeek();
        
    private: //data 
        // Pointer to the browser control interface
        CBrCtlInterface* iBrCtlInterface;
        // Desired capabilities of the browser control
        TUint iBrCtlCapabilities;
        // Command Base
        TInt iCommandBase;
        // Informs whether or not CancelLoad has been called
        TBool iCancelInitDataLoad;
        
        
    	
     	// Is it running the first time?
     	TUint8 firstrun;
     	CFbsBitmap* bitmap; 
     	CFbsBitmap* FlashCard;
     	CFbsBitmap* FlashCardMask;
    };

#endif

// End of File

