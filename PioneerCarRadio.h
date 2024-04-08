#include "AmFmRadio.h"
#ifndef PIONEERCARRADIO_H
#define PIONEERCARRADIO_H

//Constants
#define INIT_VOL 4
#define INIT_STN 800


/* -- This is a SUB-CLASS comment --
	NAME	:	PioneerCarRadio
	PURPOSE :	Represents a PioneerCarRadio object,
				extending functionality from the
				AmFmRadio Super-class.
*/
class PioneerCarRadio : public AmFmRadio
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

			
	PioneerCarRadio(bool isOn = false);					     //Constructor								
	virtual ~PioneerCarRadio(void) override;					         //Destructor

	
	virtual void ShowCurrentSettings(void);
	virtual void KeystrokeHandling(void);

};
#endif