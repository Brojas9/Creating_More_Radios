#include "AmFmRadio.h"
/*  -- Constructor Header Comment
	Name    :   AmFmRadio-- CONSTRUCTOR
	Purpose :   Constructor for the AmFmRadio class.
	Inputs  :   isOn: Boolean indicating whether the radio is initially turned on or off.
	Outputs :   Initializes the AmFmRadio object with the default initial state.
	Returns :   None
*/
AmFmRadio::AmFmRadio(bool isOn) : on(isOn), displayOutput(false)
{
	for (int i = 0; i < 5; ++i)
	{
		freq[i].AMFreq = MIN_AM_FREQ;
		freq[i].FMFreq = MIN_FM_FREQ;
	}
	// default frequencies
	frequencies.AMFreq = MIN_AM_FREQ;
	frequencies.FMFreq = MIN_FM_FREQ;

	if (on)
	{
		// default initialization
		volume = 0;
		current_station = MIN_AM_FREQ;
		strcpy(band, "AM");
	}
	else
	{	//when radio is turned off
		volume = 0;
		strcpy(band, " ");
	}
}


/*  -- Constructor Header Comment
	Name    :   AmFmRadio -- CONSTRUCTOR
	Purpose :   Constructor for the AmFmRadio class.
	Inputs  :   isOn: Boolean indicating whether the radio is initially turned on or off.
				presets: Array of Freqs representing the preset frequencies for the radio stations.
	Outputs :   Initializes the AmFmRadio object with the specified initial state and preset frequencies.
	Returns :   None
*/
AmFmRadio::AmFmRadio(bool isOn, Freqs presets[]) : displayOutput(false)
{
	for (int i = 0; i < 5; ++i)
	{
		//Validate and set the AM frequency preset
		SetCurrentStation(presets[i].AMFreq);

		//Update the frequency with validated value
		presets[i].AMFreq = GetCurrentStation();

		//Validate and set the FM frequency preset
		SetCurrentStation(presets[i].FMFreq);

		//Update the frequency with validated value
		presets[i].FMFreq = GetCurrentStation();
	}

	//default frequencies
	frequencies.AMFreq = MIN_AM_FREQ;
	frequencies.FMFreq = MIN_FM_FREQ;


}


/*  -- Destructor Header Comment
	Name    :   ~AmFmRadio -- DESTRUCTOR
	Purpose :   Destructor for the AmFmRadio class.
	Inputs  :   None
	Outputs :   Outputs a message indicating the destruction of the AmFmRadio object.
	Returns :   None
*/
AmFmRadio::~AmFmRadio(void)
{	
	if (displayOutput)
	{
		printf("\nDestroying AmFmRadio\n");
	}
}


/*  -- Member Function Header Comment
	Name    :   PowerToggle
	Purpose :   Toggle the power state of the radio (on/off).
	Inputs  :   None
	Outputs :   Updates the on attribute to the toggled state (true/false).
				Updates the volume attribute to 0 when turning off the radio.
				Restores the previous volume level when turning on the radio.
				Updates the current_station attribute with the corresponding
				frequency when turning on the radio.
	Returns :   None
*/
void AmFmRadio::PowerToggle(void)
{
	if (!on)
	{
		on = true;
		if (volume <= 0)
		{
			volume = 0;
		}

		if (strcmp(band, "AM") == 0)
		{
			current_station = frequencies.AMFreq;
		}
		else
		{
			current_station = frequencies.FMFreq;
		}
	}
	else
	{
		if (strcmp(band, "AM") == 0)
		{
			frequencies.AMFreq = current_station;
		}
		else
		{
			frequencies.FMFreq = current_station;
		}

		// Radio is being turned off
		int prevVolume = volume;
		volume = 0;
		volume = prevVolume;
		on = false;
	}
}


/*  -- Member Function Header Comment
	Name    :   ToggleBand
	Purpose :   Toggle the radio band between AM and FM.Store current AM/FM
				frequency and Restore previous FM/AM frequency
	Inputs  :   None
	Outputs :   Updates the band (AM or FM).
	Returns :   None
*/
const void AmFmRadio::ToggleFrequency(void)
{
	if (strcmp(band, "AM") == 0)
	{
		frequencies.AMFreq = current_station;
		strcpy(band, "FM");
		current_station = frequencies.FMFreq;
	}
	else
	{
		frequencies.FMFreq = current_station;
		strcpy(band, "AM");
		current_station = frequencies.AMFreq;
	}
}


/*  -- Member Function Header Comment
	Name    :   SelectPresetFreq
	Purpose :   Set the current station to the preset frequency corresponding
				to the given frequency number.
	Inputs  :   int freq_num: The number corresponding to the preset frequency
				to be selected.
	Outputs :   Updates the current_station with the selected frequency.
	Returns :   int
*/
int AmFmRadio::SelectPresetFreq(int freq_num)
{
	if ((freq_num >= 0) && (freq_num <= 4))
	{
		if (strcmp("AM", band) == 0)
		{
			current_station = freq[freq_num].AMFreq;
		}
		else
		{
			current_station = freq[freq_num].FMFreq;
		}
		return 1;
	}
	return 0;
}


/*  -- Member Function Header Comment
	Name    :   ShowCurrentSettings
	Purpose :   Display the current settings of the radio, including the radio band, volume, and current station.
				Also displays the preset frequency settings for both AM and FM bands.
	Inputs  :   None
	Outputs :   Prints the current settings of the radio.
	Returns :   None
*/
void AmFmRadio::ShowCurrentSettings(void)
{
	int volCero = 0;

	if (on)
	{
		printf("\nRadio is on \n");
	}
	else
	{
		printf("\nRadio is off \n");
	}


	printf("\nRadio Band: %s\n", band);


	if (on)
	{
		printf("Volume: %d\n", volume);
	}
	else
	{
		printf("Volume: %d\n", volCero);
	}

	if (strcmp("AM", band) == 0)
	{
		printf("Current Station: %.f %s\n", current_station, band);
	}
	else
	{
		printf("Current Station: %.1f %s\n", current_station, band);
	}

	printf("AM Freq Settings:");
	for (int i = 0; i < 5; ++i)
	{
		printf("%2d) %5d ", i + 1, freq[i].AMFreq);
	}

	printf("\nFM Freq Settings:");
	for (int j = 0; j < 5; ++j)
	{
		printf("%2d) %5.1f ", j + 1, freq[j].FMFreq);
	}
}


/*  -- Member Function Header Comment
	Name    :   ScanUp
	Purpose :   Increase the current station frequency when tuning up the radio band.
				If current_station is 1700, the current_station becomes 530, if
				current_station is 107.9, the current_station becomes 87.9
	Inputs  :   None
	Outputs :   Updates the current station frequency.
	Returns :   None
*/
void AmFmRadio::ScanUp(void)
{
	if (strcmp("AM", band) == 0)
	{
		if (current_station == MAX_AM_FREQ)
		{
			current_station = MIN_AM_FREQ;
		}
		else
		{
			current_station = current_station + 10;
		}
	}
	else
	{
		//FM band		
		if (current_station >= MAX_FM_FREQ)
		{
			current_station = MIN_FM_FREQ;
		}
		else
		{
			current_station = current_station + 0.2;
		}
	}
	if (displayOutput)
	{
		printf("\nCurrent station: %f %s\n", current_station, band);
	}
}


/*  -- Member Function Header Comment
	Name    :   ScanDown
	Purpose :   Decrease the current station frequency when tuning down the radio band.
	Inputs  :   None
	Outputs :   Updates the current station frequency.
	Returns :   None
*/
void AmFmRadio::ScanDown(void)
{
	if (strcmp("AM", band) == 0)
	{
		//if current_station is 530, the current_station becomes 1700
		if (current_station == MIN_AM_FREQ)
		{
			current_station = MAX_AM_FREQ;
		}
		else
		{
			current_station = current_station -= 10;
		}
	}
	else
	{
		//if the current_station is 107.9, the current_station becomes 87.9
		//Note: car radios jump .2 for the FM. That's how it's modeled here.
		if (current_station <= MIN_FM_FREQ)
		{
			current_station = MAX_FM_FREQ;
		}
		else
		{
			current_station = current_station -= 0.2;
		}
	}
	if (displayOutput)
	{
		printf("\nCurrent station: %f %s\n", current_station, band);
	}
}


/*  -- Accessor Method Header Comment
	Name    :   GetFreq
	Purpose :   Retrieve the array of frequency settings.
	Inputs  :   None
	Outputs :   None
	Returns :   Freqs* to the array of frequency settings.
*/
Freqs* AmFmRadio::GetFreq(void)
{
	return freq;
}


/*  -- Accessor Method Header Comment
	Name    :   GetCurrentFreqs
	Purpose :   Retrieve the current frequencies of the radio.
	Inputs  :   None
	Outputs :   None
	Returns :   Freqs - The current frequencies as an instance.
*/
Freqs AmFmRadio::GetCurrentFreqs(void)
{
	return frequencies;
}


/*  -- Accessor Method Header Comment
	Name    :   GetCurrentStation
	Purpose :   Retrieve the current station of the radio.
	Inputs  :   None
	Outputs :   None
	Returns :   double - The current station frequency.
*/
double AmFmRadio::GetCurrentStation(void)
{
	return current_station;
}


/*  -- Accessor Method Header Comment
	Name    :   GetBand
	Purpose :   Retrieve the current band of the radio.
	Inputs  :   None
	Outputs :   None
	Returns :   char* bandCopy.
*/
char* AmFmRadio::GetBand(void)
{
	char* bandCopy = new char[AM_FM];

	memcpy(bandCopy, band, sizeof(band));
	bandCopy[AM_FM];

	return bandCopy;
}


/*  -- Accessor Method Header Comment
	Name    :   GetVolume
	Purpose :   Retrieve the current volume level of the radio.
	Inputs  :   None
	Outputs :   None
	Returns :   int - the current volume level (0 - 100).
*/
int AmFmRadio::GetVolume(void)
{
	return volume;
}


/*  -- Accessor Method Header Comment
	Name    :   IsRadioOn
	Purpose :   Check if the radio is currently turned on.
	Inputs  :   None
	Outputs :   None
	Returns :   A boolean value indicating whether the radio is on (true) or off (false).
*/
bool AmFmRadio::IsRadioOn(void)
{
	return on;
}


/*  -- Accessor Method Header Comment
	Name    :   GetDisplayOutput
	Purpose :   Retrieve the current display output status.
	Inputs  :   None
	Outputs :   None
	Returns :   bool.
*/
bool AmFmRadio::GetDisplayOutput(void)
{
	return displayOutput;
}


/* -- Mutator Header Comment
	Name    :   SetPresetFreq
	Purpose :   Set the preset frequency for a specific preset number.
	Inputs  :   freq_num - the preset number of the frequency to be set.
	Outputs :   None
	Returns :   kSuccess if the preset frequency is set successfully within the valid range,
				kFailure if the preset number is out of range.
*/
int AmFmRadio::SetPresetFreq(int freq_num)
{
	if ((freq_num >= 0) && (freq_num <= 4))
	{
		if (strcmp("AM", band) == 0)
		{
			freq[freq_num].AMFreq = current_station;
		}
		else
		{
			freq[freq_num].FMFreq = current_station;
		}
		return 1;
	}
	return 0;
}


/*  -- Mutator Header Comment
	Name	:	SetVolume
	Purpose :	Set the volume level of the radio.
	Inputs	:	User input
	Outputs	:	NONE
	Returns	:	kMinVol if the volume is set to the minimum volume,
				kSetToMax if the volume is set to the maximum volume,
				kSuccess if the volume is set successfully within the valid range.
*/
int AmFmRadio::SetVolume(void)
{
	char buf[20] = "";

	printf("\nEnter the volume level (0 - 100) : ");
	fgets(buf, sizeof buf, stdin);
	volume = atoi(buf);

	if (volume < 0)
	{
		volume = 0;
		return MIN_VOLUME;
	}

	if (volume > 100)
	{
		volume = 100;
		return MAX_VOLUME;
	}
	return 1;
}


/*  -- Mutator Header Comment
	Name	:	SetVolume
	Purpose :	This us the second version of SetVolume (overloaded functions).
	Inputs	:	secondVolume
	Outputs	:	NONE
	Returns	:	int
*/
int AmFmRadio::SetVolume(int secondVolume)
{
	volume = secondVolume;

	if (volume < 0)
	{
		volume = 0;
	}
	else if (volume > 100)
	{
		volume = 100;
	}
	return 1;
}


/*  -- Mutator Header Comment
	Name    :   SetCurrentStation
	Purpose :   To modify the current_station attribute of the class,
				allowing the user to set the current station frequency
				of the radio.
	Inputs  :   station - The frequency value to be set as the current station.
	Outputs :   None
	Returns :   None
*/
void AmFmRadio::SetCurrentStation(double station)
{
	if (strcmp(band, "AM") == 0)
	{
		// Validate station for AM band
		if (station >= MIN_AM_FREQ && station <= MAX_AM_FREQ)
		{
			current_station = station;
		}
	}
	else
	{
		// Validate station for FM band
		if (station >= MIN_FM_FREQ && station <= MAX_FM_FREQ)
		{
			current_station = station;
		}
	}
}


/*  -- Mutator Header Comment
	Name	:	SetDisplayOutput
	Purpose :	To modify displayOutput attribute of the class, allowing
				the user to control whether the output should be displayed.
	Inputs	:	display
	Outputs	:	NONE
	Returns	:	bool
*/
void AmFmRadio::SetDisplayOutput(bool display)
{
	displayOutput = display;
}