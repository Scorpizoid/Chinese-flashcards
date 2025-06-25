// INCLUDE FILES
#include "KiinaContainer.h"
#include <eiklabel.h>  // for example label control
#include <avkon.hrh>
#include <Kiina.rsg>
#include "Kiina.hrh"
#include <BrCtlInterface.h>
#include <CHARCONV.H>
#include <gdi.h>
#include <bitdev.h>
#include <eikenv.h>
#include <S32FILE.H>


// ================= MEMBER FUNCTIONS =======================

// ---------------------------------------------------------
// CKiinaContainer::ConstructL(const TRect& aRect)
// EPOC two phased constructor
// ---------------------------------------------------------
//
void CKiinaContainer::ConstructL(const TRect& aRect)
    {
	

	
	_LIT(KSunClockIniFileName,"c:\\private\\2002AA27\\settings.ini");
    TFileName iniFileName=static_cast<TFileName>(KSunClockIniFileName);

    RFs fs;
    fs.Connect();
    CFileStore* store=NULL;
    TRAPD(err,store=CDirectFileStore::OpenL(fs,iniFileName,EFileShareAny));
 	if (err==KErrNone)
	{
        CleanupStack::PushL(store);
        RStoreReadStream inStream;
        inStream.OpenLC(*store,store->Root());
        InternalizeL(inStream);
        CleanupStack::PopAndDestroy(2); // inStream + store
     }
     fs.Close();
     
 	bitmap = new (ELeave) CFbsBitmap(); 
	FlashCard = new (ELeave) CFbsBitmap(); 
	FlashCardMask = new (ELeave) CFbsBitmap(); 

	
	_LIT(KMBMbg,"C:\\private\\2002AA27\\bg.mbm");
	CleanupStack::PushL(bitmap); 
	User::LeaveIfError(bitmap->Load(KMBMbg, 0));
	CleanupStack::Pop(1);

	SetItems();
	FlashCardLoader();

	
	CreateWindowL();
    SetRect(aRect);
    ActivateL();

    iCommandBase = TBrCtlDefs::ECommandIdBase;
    }

void CKiinaContainer::FlashCardLoader() const
	{
	_LIT(KMBMFlashcard,"C:\\private\\2002AA27\\flashcard.mbm");
	CleanupStack::PushL(FlashCard); 
	CleanupStack::PushL(FlashCardMask); 
	User::LeaveIfError(FlashCard->Load(KMBMFlashcard, FlashCardNumber));
	User::LeaveIfError(FlashCardMask->Load(KMBMFlashcard, FlashCardNumber));
	CleanupStack::Pop(2);
	
	}

// Destructor
CKiinaContainer::~CKiinaContainer() 
    {
    if (iBrCtlInterface)
        {
			delete iBrCtlInterface;
        }

	delete bitmap;
	delete FlashCard;
	delete FlashCardMask;
/*	delete bitmapCursor;
	delete maskBitmap;*/
    User::Exit(0);
    }

// ---------------------------------------------------------
// CKiinaContainer::SizeChanged()
// Called by framework when the view size is changed
// ---------------------------------------------------------
//
void CKiinaContainer::SizeChanged()
    {
    if (iBrCtlInterface)
        {
        iBrCtlInterface->SetRect(Rect());
        }
    }

// ---------------------------------------------------------
// CKiinaContainer::CountComponentControls() const
// ---------------------------------------------------------
//
TInt CKiinaContainer::CountComponentControls() const
    {
    if (iBrCtlInterface)
        return 1;
    return 0;
    }

// ---------------------------------------------------------
// CKiinaContainer::ComponentControl(TInt aIndex) const
// ---------------------------------------------------------
//
CCoeControl* CKiinaContainer::ComponentControl(TInt aIndex) const
    {
    switch ( aIndex )
        {
        case 0:
            return iBrCtlInterface; // Could be NULL
        default:
            return NULL;
        }
    }

// ---------------------------------------------------------
// CKiinaContainer::Draw(const TRect& aRect) const
// ---------------------------------------------------------
//
void CKiinaContainer::Draw(const TRect& aRect) const
    {
    
    CWindowGc& gc = SystemGc();
    // Start with a clear screen
	gc.Clear();

	FlashCardLoader();
			// piirrä tausta
	TPoint pos(0,0);//6,15); 
	TPoint pos2(0,16);//6,15); 
	TPoint pos3(0,79);//6,15); 
	TPoint pos4(0,203);//6,15); 
	gc.BitBlt(pos, bitmap);
	if (FlashCardMode == 0)
		{
	//Piirrä kortti
	gc.BitBltMasked(pos,FlashCard,TRect(1,1,800,124),FlashCardMask,EFalse);
	if (FlashCardFinnish == 1) { gc.BitBltMasked(pos,FlashCard,TRect(1,1,800,284),FlashCardMask,EFalse); }
	if (FlashCardPinYin == 1) { gc.BitBltMasked(pos,FlashCard,TRect(1,1,800,200),FlashCardMask,EFalse); }
		}
	
	if (FlashCardMode == 1)
		{
	gc.BitBltMasked(pos2,FlashCard,TRect(1,211,800,284),FlashCardMask,EFalse);
	if (FlashCardHanzi == 1) { gc.BitBltMasked(pos3,FlashCard,TRect(1,23,800,133),FlashCardMask,EFalse); }
	if (FlashCardPinYin == 1) { gc.BitBltMasked(pos4,FlashCard,TRect(1,144,800,200),FlashCardMask,EFalse); }
		}
	
	TRect textRect(15,250,110,280);
	const CFont*     titleFont;
	titleFont = iEikonEnv->LegendFont();
	gc.UseFont(titleFont);
	gc.SetPenColor(KRgbGray);  
			   // Draw the text in the middle of the rectangle.
	TBuf<256> FlashCard;
	FlashCard.Format(_L("Kortti %d/%d"),FlashCardNumber+1,MaxFlashCards);
	gc.DrawText(FlashCard,textRect,30,CGraphicsContext::ELeft, 0);
			   // Finished using the font
	gc.DiscardFont();

	
	
	

	
	
	
    }

// ---------------------------------------------------------
// CKiinaContainer::HandleControlEventL(
//     CCoeControl* aControl,TCoeEvent aEventType)
// ---------------------------------------------------------
//
void CKiinaContainer::HandleControlEventL(
    CCoeControl* /*aControl*/,TCoeEvent /*aEventType*/)
    {
    // TODO: Add your control event handler code here
    }

// ----------------------------------------------------
// CKiinaContainer::HandleKeyEventL(
//     const TKeyEvent& aKeyEvent,TEventCode /*aType*/)
// ----------------------------------------------------
//
TKeyResponse CKiinaContainer::HandleKeyEventL(
    const TKeyEvent& /*aKeyEvent*/,TEventCode /*aType*/)
    {
    return EKeyWasNotConsumed;
    }

// ----------------------------------------------------
// CKiinaContainer::CancelLoad()
// ----------------------------------------------------
//
void CKiinaContainer::CancelLoad()
    {
    iCancelInitDataLoad = ETrue;
    }

// ----------------------------------------------------
// CKiinaContainer::HandleCommandL(TInt aCommand)
// ----------------------------------------------------
//
void CKiinaContainer::HandleCommandL(TInt aCommand)
{
    switch ( aCommand )
    {
       	case EAknSoftkeyBack:
            {
                if (iBrCtlInterface != NULL)
                {
                iBrCtlInterface = NULL;
                     DrawNow();
                }
                break;
            }
/*        case EKiinaCmdAppOpen:
        {
            if (iBrCtlInterface == NULL)
            {
				BasicBrowserControlL(x, y);
            }
			break;
        }*/
        case EKiinaCmdAppAbout:
        {
            if (iBrCtlInterface != NULL)
            {
				iBrCtlInterface = NULL;
				DrawNow();
            }
			OpenAboutBoxL();
 			break;
       }
   }
}

// ----------------------------------------------------
// CKiinaContainer::DynInitMenuPaneL(
//           TInt aResourceId, CEikMenuPane* aMenuPane)
// ----------------------------------------------------
//
void 
CKiinaContainer::DynInitMenuPaneL(TInt aResourceId, CEikMenuPane* aMenuPane)
    {
    if (iBrCtlInterface && aResourceId == R_KIINA_MENU )
        {
        iBrCtlInterface->AddOptionMenuItemsL(*aMenuPane, aResourceId);
        RPointerArray<TBrCtlWmlServiceOption>* options;
        options = iBrCtlInterface->WMLOptionMenuItemsL();
        TInt i;
        TInt count = options->Count();
        for (i = 0; i < count; i++)
            {
            TBrCtlWmlServiceOption* option = (*options)[i];
            if (option != NULL)
                {
                CEikMenuPaneItem::SData item;
                item.iText.Copy(option->Text());
                item.iCommandId = option->ElemID();
                item.iFlags = 0;
                item.iCascadeId = 0;
                aMenuPane->InsertMenuItemL(item, 0);
                }
            }
        }
    }


// ----------------------------------------------------
// CKiinaContainer::ReadFileLC(const TDesC& aFileName)
// ----------------------------------------------------
//
HBufC8* 
CKiinaContainer::ReadFileLC(const TDesC& aFileName)
    {
    RFs rfs;
    RFile file;
    User::LeaveIfError(rfs.Connect());
    CleanupClosePushL(rfs);
    User::LeaveIfError(file.Open(rfs, aFileName, EFileRead));
    CleanupClosePushL(file);
    TInt size;
    User::LeaveIfError(file.Size(size));
    HBufC8* buf = HBufC8::NewLC(size);
    TPtr8 bufPtr(buf->Des());
    User::LeaveIfError(file.Read(bufPtr));
    CleanupStack::Pop(); // buf
    CleanupStack::PopAndDestroy(2); // file, rfs
    CleanupStack::PushL(buf);
    return buf;
    }

// ----------------------------------------------------
// CKiinaContainer::BasicBrowserControlL()
// ----------------------------------------------------
//
void 
CKiinaContainer::BasicBrowserControlL(TInt x, TInt y)
    {
   }


void 
CKiinaContainer::OpenAboutBoxL()
    {
    if (iBrCtlInterface == NULL) {
    
    
				TRect rect(120,10, 640,264);//Position(), Size());
				iBrCtlInterface = CreateBrowserControlL( this, 
				rect, 
				TBrCtlDefs::ECapabilityDisplayScrollBar,
				iCommandBase, 
				NULL, 
				NULL,
				NULL, 
				NULL,
				NULL);
				
				_LIT(KUrl, "file:///C:\\private\\2002AA27\\about.html");
				iBrCtlInterface->LoadUrlL(KUrl);
	
		}
   }




// INI-tiedoston ID
TStreamId CKiinaContainer::StoreL(CStreamStore& aStore) const
{
RStoreWriteStream outStream;
TStreamId id=outStream.CreateLC(aStore);
ExternalizeL(outStream);
outStream.CommitL();
CleanupStack::PopAndDestroy();  // outStream
return id;
}


// Avataan INI-tiedosto?
void CKiinaContainer::RestoreL(const CStreamStore& aStore, TStreamId aId)
{
RStoreReadStream inStream;
inStream.OpenLC(aStore,aId);
InternalizeL(inStream);
CleanupStack::PopAndDestroy(); // inStream
}



// Kirjoitetaan arvot INI-tiedostoon
void CKiinaContainer::ExternalizeL(RWriteStream& aOut) const
{
	aOut.WriteInt32L(static_cast<TInt>(FlashCardNumber));
	aOut.WriteInt32L(static_cast<TInt>(FlashCardMode));
}


// Ladataan arvot INI-tiedostosta
void CKiinaContainer::InternalizeL(RReadStream& aIn)
{
	FlashCardNumber=static_cast<TInt>(aIn.ReadInt32L());
	FlashCardMode=static_cast<TInt>(aIn.ReadInt32L());
DrawNow();
}


// Tallennetaan INI-tiedosto tiedostojärjestelmään
void CKiinaContainer::SaveL()
{
_LIT(KRulerIniFileName,"c:\\private\\2002AA27\\settings.ini");
RFs fs;
fs.Connect();

CFileStore* store=NULL;;

TParse parse;
parse.Set(KRulerIniFileName,NULL,NULL);

TRAPD(replaceErrorCode,store=CDirectFileStore::ReplaceL(fs,KRulerIniFileName,EFileShareAny|EFileWrite));

if (replaceErrorCode!=KErrNone)
{
store=CDirectFileStore::CreateL(fs,KRulerIniFileName,EFileShareAny|EFileWrite);
}

CleanupStack::PushL(store);
store->SetTypeL(KDirectFileStoreLayoutUid);
RStoreWriteStream outStream;
TStreamId id=outStream.CreateLC(*store);
ExternalizeL(outStream);
outStream.CommitL();
store->SetRootL(id);
store->CommitL();
CleanupStack::PopAndDestroy(2); // outStream + store
fs.Close();
}





// End of File  

