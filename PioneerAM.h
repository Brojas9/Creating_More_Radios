#include "PioneerCarRadio.h"
#ifndef PIONEERAM_H
#define PIONEERAM_H


/* -- This is a SUB-CLASS comment --
	NAME	:	PioneerAM
	PURPOSE :	Represents a PioneerAM object, 
                extending functionality from the 
                PioneerCarRadio parent-class.

*/
class PioneerAM : public PioneerCarRadio
{
	/* ====================================== */
	/*              PRIVATE                   */
	/* ====================================== */
private:


	/* -------------- CONSTANTS ------------- */
	/* -------------- ATTRIBUTES ------------ */


	/* ====================================== */
	/*              PUBLIC                    */
	/* ====================================== */
public:
	/* -------------- ATTRIBUTES ------------ */
	/* - MEMBER FUNCTIONS/METHOD PROTOTYPES - */



    PioneerAM(bool isOn = false) : PioneerCarRadio(isOn) {}		                  //Constructor	


    /*  -- Destructor Header Comment
    Name    :   ~PioneerAM -- DESTRUCTOR
    Purpose :   Destructor for the PioneerAM sub-class.
    Inputs  :   None
    Outputs :   Outputs a message indicating the destruction of the Pioneer XS440-AM Radio object.
    Returns :   None
    */
    virtual ~PioneerAM(void) override
    {
        printf("\nDestroying Pioneer XS440-AM Radio\n");        
    }

    /* -------------- OVERRIDING FUNCTIONS ------------ */
  
    /*  -- Virtual Function Header Comment
    Name    :   ShowCurrentSettings
    Purpose :   Display current settings of the radio, including 
                volume, current station, and preset frequencies.
    Inputs  :   None
    Outputs :   Prints the current settings of the radio.
    Returns :   None
    */
	virtual void ShowCurrentSettings(void) override
	{
		printf("\nVolume: %d\n", GetVolume());

		if (strcmp("AM", GetBand()) == 0)
		{
			printf("Current Station: %5.f %s\n", GetCurrentStation(), GetBand());
		}

		printf("AM Buttons:\n");
		for (int i = 0; i < 5; ++i)
		{
			printf("%d: %5d", i + 1, GetFreq()[i].AMFreq);
			if (i < 4)
			{
				printf(", ");
			}
		}
		printf("\n");
	}
	
    /*  -- Virtual Function Header Comment
    Name    :   KeystrokeHandling
    Purpose :   Handle user input to control the radio.
    Inputs  :   None
    Outputs :   Modifies radio settings based on user input.
    Returns :   None
    */
    virtual void KeystrokeHandling(void) override
    {
        char keyboard = 0;

        do
        {
            system("cls");

            if (IsRadioOn())
            {
                printf("\nPioneer XS440-AM");
                printf("\nRadios is off ");
                keyboard = _getch();

            }
            else
            {
                printf("\nPioneer XS440-AM");
                printf("\nRadios is on ");
                ShowCurrentSettings();
                keyboard = _getch();
            }

            switch (keyboard)
            {
            case 'o':
                // Turn off the radio              
                PowerToggle();
                break;
            case '+':
                // Volume up            
                SetVolume(GetVolume() + 1);
                break;
            case '_':
                // Volume down
                SetVolume(GetVolume() - 1);
                break;
            case '=':
                // Scan up
                ScanUp();
                break;
            case '-':
                // Scan down
                ScanDown();
                break;
            case 'b':
                // Toggle band
                ToggleFrequency();
                break;
            case '1':
            case '2':
            case '3':
            case '4':
            case '5':
                //Select preset frequency
                SelectPresetFreq(keyboard - '1');//Keyboard digit conversion
                break;
            case '!':
                SetPresetFreq(0);
                break;
            case '@':
                SetPresetFreq(1);
                break;
            case '#':
                SetPresetFreq(2);
                break;
            case '$':
                SetPresetFreq(3);
                break;
            case '%':
                SetPresetFreq(4);
                break;
            case 'x':
                PioneerAM::~PioneerAM();
                return;
            }
        } while (1);
    }
            /*  -- Virtual Function Header Comment
    Name    :   ToggleFrequency
    Purpose :   Toggles the frequency between AM.
    Inputs  :   None    
    Outputs :   Modifies the frequency settings of the radio.
    Returns :   None
    */										
	virtual const void ToggleFrequency(void) override
	{
		if (strcmp(band, "AM") == 0)
		{
			frequencies.AMFreq = current_station;
		}	
	}    

};
#endif
