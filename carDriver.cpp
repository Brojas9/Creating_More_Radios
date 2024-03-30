/* -- FILEHEADER COMMENT --
   NAME    : carDriver.cpp
   PURPOSE : This header file contains the declaration of the PioneerCarRadio
   sub-class, which represents an AM/FM radio device. It provides functionalities
   to toggle power, adjust volume, set and select preset frequencies, Choose
   button radio stations.
*/
#include "AmFmRadio.h"
#include "PioneerCarRadio.h"


int main(void)
{
	bool off = true;
	PioneerCarRadio RadioPioneer(off);
	
	RadioPioneer.KeystrokeHandling();

	return 0;
}