/*********************************************
 - File Name : main.c
 - Author    : Hatem Desoky
 - Date      : Jul 8, 2024     
*********************************************/

#include <stdio.h>

//------------------- use Engine Temp feature or not -------------------//
#define WITH_ENGINE_TEMP_CONTROLLER 1

//------------------- make enum to use 0 with off and 1 with on -------------------//
typedef enum{
	off = 0,
	on = 1
}bool;

//-------------------  put all the date in one structre -------------------//
struct states {
	bool engineState;
	bool AC;
	unsigned short vehicleSpeed;
	unsigned short roomT;

	//control feature on or off--
#if WITH_ENGINE_TEMP_CONTROLLER
	bool engineTCtrl;
	unsigned short engineT;
#endif
	//---------------------------
};

//------------------- set initial values to the data with feature on -------------------//
#if (WITH_ENGINE_TEMP_CONTROLLER == 1)
struct states a = {on, off, 60, 35, off, 90};

//------------------- set initial values to the data with feature off -------------------//
#elif (WITH_ENGINE_TEMP_CONTROLLER == 0)
struct states a = {on, off, 60, 35};

#endif

//------------------- make a pointer to structure to access the data and edit -------------------//
struct states* s_ptr = &a;

//------------------- my header functions -------------------//
int mainMenu (void);
int setMenu (void);
void showCurrentStates(struct states *ptr);
void setTraffic (struct states *ptr);
void setRoomTemp (struct states *ptr);
void checkIf30km (struct states *ptr);

#if WITH_ENGINE_TEMP_CONTROLLER
void setEngineT (struct states *ptr);
#endif


//------------------- start the main -------------------//
int main(void) {

	//for print in eclipse
	setvbuf(stdout, NULL, _IONBF, 0);
	setvbuf(stderr, NULL, _IONBF, 0);

	unsigned char r2;
	while(1)
	{
		if (mainMenu())
		{
			while (1)
			{

				r2 = setMenu();
				if (r2 == 2)
				{
					setTraffic (&a);
				}
				else if (r2 == 3)
				{
					setRoomTemp (&a);
				}
//------------------- here using the #if to control the code -------------------//
#if WITH_ENGINE_TEMP_CONTROLLER
				else if (r2 == 4)
				{
					setEngineT (&a);
				}
#endif
//------------------- here using the #endif to control the code -------------------//
				else
				{
					break; //in case turn of the engine
				}
				checkIf30km(&a);
				showCurrentStates(&a);
			}
		}
		else break; //in case quit the system
	}

	return 0;
}

//------------------- mainMenu the function to -display the Main Menu and get the input- -------------------//
int mainMenu (void)
{
	char choice;
	printf("a. Turn on the vehicle engine\n");
	printf("b. Turn off the vehicle engine\n");
	printf("c. Quit the system\n");
	scanf(" %c", &choice);

	switch (choice)
	{
	case 'a':
		printf("Turn on the vehicle engine\n");
		s_ptr-> engineState = on;
		printf("\n");
		return 1;
		break;
	case 'b':
		printf("Turn off the vehicle engine\n");
		s_ptr-> engineState = off;
		printf("\n");
		return 2;
		break;
	case 'c':
		printf("Quit the system\n");
		printf("\n");
		return 0;
	}
	return 0;
}

//------------------- setMenu the function to -display the Set Menu Options and get the input- -------------------//
int setMenu (void)
{
	char choice;
	printf("a. Turn off the engine\n");
	printf("b. Set the traffic light color.\n");
	printf("c. Set the room temperature (Temperature Sensor)\n");
	//------------------- here using the #if to control the code -------------------//
#if WITH_ENGINE_TEMP_CONTROLLER
	printf("d. Set the engine temperature (Engine Temperature Sensor)\n");
#endif
	//------------------- here using the #endif to control the code -------------------//
	scanf(" %c", &choice);

	switch (choice)
	{
	case 'a':
		printf("Turn off the engine\n");
		s_ptr-> engineState = off;
		printf("\n");
		return 1;
		break;
	case 'b':
		printf("Set the traffic light color.\n");
		printf("\n");
		return 2;
		break;
	case 'c':
		printf("Set the room temperature (Temperature Sensor)\n");
		printf("\n");
		return 3;
		break;
		//------------------- here using the #if to control the code -------------------//
#if WITH_ENGINE_TEMP_CONTROLLER
	case 'd':
		printf("Set the engine temperature (Engine Temperature Sensor)\n");
		printf("\n");
		return 4;
		break;
#endif
		//------------------- here using the #endif to control the code -------------------//
	}
	return 0;
}

//------------------- setTraffic the function to -show the current system states- -------------------//
void showCurrentStates(struct states *ptr)
{
	if (ptr->engineState)
		printf("Engine is ON\n");
	else
		printf("Engine is OFF\n");

	if (ptr->AC)
		printf("AC is ON\n");
	else
		printf("AC is OFF\n");

	printf("Vehicle Speed: %d Km/Hr\n", ptr->vehicleSpeed);
	printf("Room Temperature: %d C\n", ptr->roomT);
	//------------------- here using the #if to control the code -------------------//
#if WITH_ENGINE_TEMP_CONTROLLER
	if (ptr->engineTCtrl)
		printf("Engine T. CTRL is ON\n");
	else
		printf("Engine T. CTRL is OFF\n");

	printf("Engine Temperature: %d C\n", ptr->engineT);
	printf("\n");
#endif
}

//------------------- setTraffic the function to -control the speed depends on the traffic- -------------------//
void setTraffic (struct states *ptr)
{
	char ch;
	printf("Enter the required color: \n");
	scanf(" %c", &ch);
	if (ch == 'g' || ch == 'G')
	{
		ptr->vehicleSpeed = 100;
	}
	else if (ch == 'o' || ch == 'O')
	{
		ptr->vehicleSpeed = 30;
	}
	else
	{
		ptr->vehicleSpeed = 0;
	}
}

//------------------- checkIf30km the function to -check if the speed 30km or not and do actions- -------------------//
void checkIf30km (struct states *ptr)
{
	if (ptr->vehicleSpeed == 30)
	{

		if (ptr->AC == off)
		{
			ptr->AC = on;
		}
		ptr->roomT = ((ptr->roomT * 5)/4) + 1;
#if WITH_ENGINE_TEMP_CONTROLLER
		if (ptr->engineTCtrl == off)
		{
			ptr->engineTCtrl = on;
		}
		ptr->engineT = ((ptr->engineT * 5)/4) + 1;
#endif
	}
}

//------------------- setRoomTemp the function to -control the room temp- -------------------//
void setRoomTemp (struct states *ptr)
{
	int ch;
	printf("Enter the required room temperature: \n");
	scanf(" %d", &ch);
	if (ch < 10 || ch > 30)
	{
		ptr->AC = 1;
		ptr->roomT = 20;
	}
	else
	{
		ptr->AC = 0;
		ptr->roomT = ch;
	}
}

//------------------- setEngineT the function to -control the Engine temp if the feature is on- -------------------//
#if WITH_ENGINE_TEMP_CONTROLLER
void setEngineT (struct states *ptr)
{
	int ch;
	printf("Enter the required engine temperature: \n");
	scanf(" %d", &ch);
	if (ch < 100 || ch > 150)
	{
		ptr->engineTCtrl = on;
		ptr->engineT = 125;
	}
	else
	{
		ptr->engineTCtrl = 0;
		ptr->engineT = ch;
	}
}
#endif




