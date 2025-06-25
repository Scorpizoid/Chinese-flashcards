#include "KiinaContainer.h"
#include <Kiina.rsg>
#include "Kiina.hrh"

void CKiinaContainer::SetItems()
	{

	MaxFlashCards = 26;
	
	
	
	FlashCardFinnish = 0;
	FlashCardPinYin = 0;
	FlashCardHanzi = 0;

	}
	





// ----------------------------------------------------
// CKiinaContainer::OfferKeyEventL(const 
//               TKeyEvent& aKeyEvent,TEventCode aType)
// ----------------------------------------------------
//
TKeyResponse CKiinaContainer::OfferKeyEventL(const TKeyEvent& aKeyEvent,
		TEventCode aType)
	{
	TInt code = aKeyEvent.iCode;

	// five-way navigation middle button handler
	if (aKeyEvent.iScanCode == EStdKeyDevice3)
		{
	//Mene nyt prkl
	if (FlashCardMode == 0)
		{
		if (FlashCardPinYin == 1) { FlashCardFinnish = 1; }
		FlashCardPinYin = 1;
		DrawNow();
		}
	if (FlashCardMode == 1)
		{
		if (FlashCardHanzi == 1) { FlashCardPinYin = 1; }
		FlashCardHanzi = 1;
		DrawNow();
		}
		return EKeyWasConsumed;
		}

	switch (code)
		{
   	 case EKeyLineFeed:
   	 case EKeyEnter:
			{
			
			if (FlashCardMode == 0)
				{
				if (FlashCardPinYin == 1) { FlashCardFinnish = 1; }
				FlashCardPinYin = 1;
				DrawNow();
				break;
				}
			if (FlashCardMode == 1)
				{
			if (FlashCardHanzi == 1) { FlashCardPinYin = 1; }
				FlashCardHanzi = 1;
				DrawNow();
				break;
				}
			}

		case EKeyLeftArrow:
			{
			FlashCardNumber= FlashCardNumber - 1;
			if (FlashCardNumber<0) { FlashCardNumber = MaxFlashCards-1; }
			FlashCardFinnish = 0;
			FlashCardPinYin = 0;
			FlashCardHanzi = 0;
			DrawNow();
			break;

			}

		case EKeyRightArrow:
			{
			FlashCardNumber= FlashCardNumber + 1;
			if (FlashCardNumber>=MaxFlashCards) { FlashCardNumber = 0; }
			FlashCardFinnish = 0;
			FlashCardPinYin = 0;
			FlashCardHanzi = 0;
			DrawNow();
			break;

			}


		case EKeySpace:
			{
			switch (FlashCardMode)
				{
			case 0: { FlashCardMode = 1; break; }
			case 1: { FlashCardMode = 0; break; }
				}
			DrawNow();
			break;

			}


		case EKeyBackspace:
			{
	        if (iBrCtlInterface != NULL)
	            {
	            iBrCtlInterface = NULL;
	            DrawNow();
	            }
	        break;
			}
		}
	if (iBrCtlInterface)
        {
        return iBrCtlInterface->OfferKeyEventL(aKeyEvent, aType);
        } 

	return EKeyWasConsumed;
	}

void CKiinaContainer::Laskut()
	{



	}

void CKiinaContainer::CheckWeek()
{
	
}
