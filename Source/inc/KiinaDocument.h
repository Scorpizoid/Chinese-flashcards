/*
* ============================================================================
*  Name         : KiinaDocument.h
*  Part of      : Kiina
*  Interface    : Browser Control API
*  Description  : Declares document for application.
*  Version      : 
*
*  Copyright (c) 2005-2006 Nokia Corporation.
*  This material, including documentation and any related 
*  computer programs, is protected by copyright controlled by 
*  Nokia Corporation.
* ============================================================================
*/

#ifndef KIINADOCUMENT_H
#define KIINADOCUMENT_H

// INCLUDES
#include <akndoc.h>
   
// CONSTANTS

// FORWARD DECLARATIONS
class  CEikAppUi;

// CLASS DECLARATION

/**
*  CKiinaDocument application class.
*/
class CKiinaDocument : public CAknDocument
    {
    public: // Constructors and destructor
        /**
        * Two-phased constructor.
        */
        static CKiinaDocument* NewL(CEikApplication& aApp);

        /**
        * Destructor.
        */
        virtual ~CKiinaDocument();

    public: // New functions

    protected:  // New functions

    protected:  // Functions from base classes

    private:

        /**
        * EPOC default constructor.
        */
        CKiinaDocument(CEikApplication& aApp);
        void ConstructL();

    private:

        /**
        * From CEikDocument, create CKiinaAppUi "App UI" object.
        */
        CEikAppUi* CreateAppUiL();
    };

#endif

// End of File

