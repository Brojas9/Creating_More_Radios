#include "PioneerAM.h"
#ifndef PIONEERWORLD_H
#define PIONEERWORLD_H


/* -- This is a SUB-CLASS comment --
	NAME	:	PioneerWorld
	PURPOSE :	Represents a PioneerWorld object, 
                inheriting from the PioneerAM class.
*/
class PioneerWorld : public PioneerAM
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
	


    /*  -- Constructor Header Comment
    Name    :   PioneerWorld-- CONSTRUCTOR
    Purpose :   Constructs a PioneerWorld object with optional initial state.
    Inputs  :   isOn - Boolean flag indicating initial power state (default: false).
    Outputs :   None
    Returns :   None
    */
	PioneerWorld(bool isOn = false) : PioneerAM(isOn) 
    {
        SetCurrentStation(531);

        //Initial values for AM Buttons
        int initialAMFreq[5] = { 531, 531, 531, 531, 531 };

        for (int i = 0; i < 5; ++i)
        {
            //Set the initial values for AM Buttons
            GetFreq()[i].AMFreq = initialAMFreq[i];
        }    
    }							

        /*  -- Destructor Header Comment
    Name    :   ~PioneerWorld -- DESTRUCTOR
    Purpose :   Destructs a PioneerWorld object
    Inputs  :   None
    Outputs :   Prints a message indicating the destruction of the object.
    Returns :   None
    */
	virtual ~PioneerWorld() override
	{
		printf("\nDestroying Pioneer XS440-WRLD Radio\n");
	}												


    /*  -- Virtual Function Header Comment
    Name    :   KeystrokeHandling
    Purpose :   Handles user input to control the radio.
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
                printf("\nPioneer XS440-WRLD");
                printf("\nRadios is off ");
                keyboard = _getch();

            }
            else
            {
                printf("\nPioneer XS440-WRLD");
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
                PioneerWorld::~PioneerWorld();
                return;
            }
        } while (1);
    }


    /*  -- Virtual Function Header Comment
    Name    :   ScanUp
    Purpose :   Increases the current station frequency.
    Inputs  :   None
    Outputs :   Updates the current station frequency.
    Returns :   None
    */
	virtual void ScanUp(void) override
	{
		if (strcmp("AM", band) == 0)
		{
			if (current_station == 1602)
			{
				current_station = 531;
			}
			else
			{
				current_station = current_station + 9;
			}
		}
	}


    /*  -- Virtual Function Header Comment
    Name    :   ScanDown
    Purpose :   Decreases the current station frequency.
    Inputs  :   None
    Outputs :   Updates the current station frequency.
    Returns :   None
    */
    virtual void ScanDown(void) override
    {
        if (strcmp("AM", band) == 0)
        {
            //if current_station is 531, the current_station becomes 1602
            if (current_station == 531)
            {
                current_station = 1602;
            }
            else
            {
                current_station = current_station -= 9;
            }
        }
       
    }

};
#endif
