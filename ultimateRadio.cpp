/* -- FILE HEADER COMMENT --
   NAME    : ultimateRadio.cpp
   PURPOSE : This file implements a program for controlling different types of 
   Pioneer radios including car, AM, and world radios. It allows users to interact
   with the radios by selecting options from the command line and performing 
   operations such as changing stations and adjusting volume.
*/
#include "AmFmRadio.h"
#include "PioneerCarRadio.h"
#include "PioneerAM.h"
#include "PioneerWorld.h"

#define ERROR 1

PioneerCarRadio* createRadio(const char* choice);
void runRadio(PioneerCarRadio* pRadio);

int main(int argc, char* argv[])
{	
	if (argc != 2) 
	{
		printf("\nThere are not arguments in Command-line: %s\n", argv[1]);
		return ERROR;
	}
	
	char* choice = argv[1];
	
	PioneerCarRadio* pRadio = NULL;

	try 
	{
		pRadio = createRadio(choice);
		runRadio(pRadio);
	}
	catch (const std::exception &e)
	{
		printf("Exception detected %s\n", e.what());
	}

	delete pRadio;

	return 0;
}


/*  -- Function Header Comment
	Name    :   createRadio(const char* choice)
	Purpose :   Creates a Pioneer radio based on the user's choice.
	Inputs  :   choice - A pointer to a string indicating the type  
				of radio to create ("-car" for car radio, "-am" for 
				AM radio, "-world" for world radio).
	Outputs :   None
	Returns :   A pointer to the created Pioneer radio.
*/
PioneerCarRadio* createRadio(const char* choice)
{
	if (strcmp(choice, "-car") == 0)
	{
		PioneerCarRadio* carRadio = new PioneerCarRadio(true); // Instantiate a new PioneerCarRadio
		carRadio->KeystrokeHandling();
		return carRadio;

	}
	else if (strcmp(choice, "-am") == 0)
	{
		PioneerAM* amRadio = new PioneerAM(true); // Instantiate a new PioneerAM
		amRadio->KeystrokeHandling(); 
		return amRadio;
	}
	else if (strcmp(choice, "-world") == 0)
	{
		PioneerWorld* worldRadio = new PioneerWorld(true); // Instantiate a new PioneerWorld
		worldRadio->KeystrokeHandling(); 
		return worldRadio;
	}
	else
	{
		// Invalid choice, return nullptr
		fprintf(stderr, "Command-line Error: Invalid choice\n");
		return nullptr;
	}
}


/*  -- Function Header Comment
	Name    :   runRadio(PioneerCarRadio* pRadio) 
	Purpose :	Runs the interaction loop for controlling the Pioneer radio.
	Inputs  :	pRadio - A pointer to a PioneerCarRadio object.
	Outputs :	None
	Returns :	None
*/
void runRadio(PioneerCarRadio* pRadio) 
{
	char userInput;

	while (1)
	{		
		printf("\n c => PioneerCarRadio\n a => PioneerAM\n w => PioneerWorld\n x => quit\n");
		printf("\nEnter an letter:");
		userInput = _getch();

		system("cls");
		switch (userInput)
		{
		case 'c':
			createRadio("-car");
			break;
		case 'a':
			createRadio("-am");
			break;
		case 'w':
			createRadio("-world");
			break;
		case 'x':
			printf("\nExiting program...\n");
			exit(1);
		default:
			printf("\n\nInvalid choice, please try again\n");
			break;
		}
	}	
}