#include "PioneerCarRadio.h"
/*  -- Constructor Header Comment
    Name    :   PioneerCarRadio-- CONSTRUCTOR
    Purpose :   Constructor for the PioneerCarRadio sub-class. Initializes the
                PioneerCarRadio object with default settings and preset frequencies.
    Inputs  :   isOn: Boolean indicating whether the radio is initially turned on or off.
    Outputs :   None
    Returns :   None
*/
PioneerCarRadio::PioneerCarRadio(bool isOn) : AmFmRadio(isOn)
{
    //Initial volume
    SetVolume(INIT_VOL);
    //Initial station
    SetCurrentStation(INIT_STN);


    //Initial values for AM Buttons
    int initialAMFreq[5] = { 1000, 1210, 800, 700, 1300 };

    for (int i = 0; i < 5; ++i)
    {
        //Set the initial values for AM Buttons
        GetFreq()[i].AMFreq = initialAMFreq[i];
    }

    //Initial value for FM Buttons
    double initialFMFreq[5] = { 102.1, 104.3, 100.1, 99.3, 89.7 };

    for (int j = 0; j < 5; ++j)
    {
        //Set the initial values for FM Buttons
        GetFreq()[j].FMFreq = initialFMFreq[j];
    }
}


/*  -- Destructor Header Comment
    Name    :   ~PioneerCarRadio -- DESTRUCTOR
    Purpose :   Destructor for the PioneerCarRadio sub-class.
    Inputs  :   None
    Outputs :   Outputs a message indicating the destruction of the PioneerCarRadio object.
    Returns :   None
*/
PioneerCarRadio::~PioneerCarRadio()
{
    printf("\n\nDestroying PioneerCarRadio\n");
}


/*  -- Member Function Header Comment
    Name    :   KeystrokeHandling
    Purpose :   Handles user input for controlling the PioneerCarRadio.
                Displays current settings and performs actions based on user input
                toggle power, adjust volume, set and select preset frequencies, Choose
                button radio stations.
    Inputs  :   None
    Outputs :   Displays current radio settings and prompts for user input.
    Returns :   None
*/
void PioneerCarRadio::KeystrokeHandling(void)
{
    char keyboard = 0;

    do
    {
        system("cls");
        //Radio off
        if (IsRadioOn())
        {
            printf("\nPioneer XS440");
            printf("\nRadios is off");
            keyboard = _getch();
        }
        else//Radio on
        {
            printf("\nPioneer XS440");
            printf("\nRadios is on ");
            printf("\nVolume: %d\n", GetVolume());

            if (strcmp("AM", GetBand()) == 0)
            {
                printf("Current Station: %5.f %s\n", GetCurrentStation(), GetBand());
            }
            else
            {
                printf("Current Station: %5.1f %s\n", GetCurrentStation(), GetBand());
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

            printf("\nFM Buttons:\n");
            for (int j = 0; j < 5; ++j)
            {
                printf("%d: %5.1f", j + 1, GetFreq()[j].FMFreq);
                if (j < 4)
                {
                    printf(", ");
                }
            }
            printf("\n");

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
            ToggleBand();
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
            PioneerCarRadio::~PioneerCarRadio();
            exit(1);
        }
    } while (1);

}