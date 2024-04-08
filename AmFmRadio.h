#ifndef AMFMRADIO_H
#define AMFMRADIO_H
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <stdbool.h>
#include <string>
#include <conio.h>
#include <new>
#pragma warning(disable: 4996) // required by Visual Studio


//Constants
#define STATIONS 5
#define AM_FM 3
#define MAX_AM_FREQ 1700
#define MIN_AM_FREQ 530
#define MAX_FM_FREQ 107.9
#define MIN_FM_FREQ 87.9
#define MIN_VOLUME 0
#define MAX_VOLUME 2


/* -- This is a Strut Comment --
	NAME	:	Freqs
	PURPOSE :	The purpose of this structure is to represent
				the frequency of the radio.
*/
struct Freqs
{
	int AMFreq;
	double FMFreq;
};
/* -- This is a SUPER-CLASS comment --
	NAME	:	AmFmRadio
	PURPOSE :	The AmFmRadio class models an AM/FM radio with
	preset frequencies, allowing users to toggle power, switch
	between AM and FM bands, select preset frequencies and
	control volume. It encapsulates the radio's state, including
	current station, band, volume level, and power status, while
	providing methods to access and modify these attributes.
*/
class AmFmRadio
{
	/* ====================================== */
	/*              PRIVATE                   */
	/* ====================================== */
private:

	/* -------------- CONSTANTS ------------- */
	/* -------------- ATTRIBUTES ------------ */
	Freqs	freq[STATIONS];
	Freqs frequencies;	
	char	band[AM_FM];
	double	current_station;
	int		volume;
	bool	on;
	bool displayOutput;
	
	


	/* ====================================== */
	/*              PUBLIC                    */
	/* ====================================== */
public:
	/* -------------- ATTRIBUTES ------------ */
	/* - MEMBER FUNCTIONS/METHOD PROTOTYPES - */
	void PowerToggle(void);
	int SelectPresetFreq(int freq_num);
	void ShowCurrentSettings(void);




	AmFmRadio(bool isOn = false);										//Constructor
	AmFmRadio(bool isOn, Freqs presets[]);								//Constructor
	virtual ~AmFmRadio(void);						                    //Destructor


	/* ---------- ACCESSOR METHODS PROTOTYPES --------- */
	Freqs* GetFreq(void);
	Freqs GetCurrentFreqs(void);
	double GetCurrentStation(void);
	char* GetBand(void);
	int GetVolume(void);
	bool IsRadioOn(void);
	bool GetDisplayOutput(void);
	


	/* ---------- MUTATOR PROTOTYPES --------- */

	int SetPresetFreq(int freq_num);
	int SetVolume(void);
	int SetVolume(int secondVolume);
	void SetCurrentStation(double station);
	void SetDisplayOutput(bool display);


	virtual const void ToggleFrequency(void);
	virtual void ScanUp(void);
	virtual void ScanDown(void);

};
#endif
