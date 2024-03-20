#include <TrafficLights.h>
#define G	0
#define Y	1
#define R	2
#define periodicity_sec 2

runnable_t Traffic_Lights={
		.name="runnable1",
		.priority=0,
		.periodicity=2,
		.CB=traffic_lights
};
void traffic_lights ()
{
	static uint32_t state=G;
	static uint32_t TimeSec=0;
	static uint32_t prev=0;
	switch (state)
	{
	case G:
		LED_SetStatus(LED_Green,LED_STAT_ON);
		LED_SetStatus(LED_Yellow,LED_STAT_OFF);
		LED_SetStatus(LED_Red,LED_STAT_OFF);
		if (TimeSec==6)
		{
			state=Y;
			TimeSec=0;
			prev=G;
		}
		break;
	case Y:
		LED_SetStatus(LED_Green,LED_STAT_OFF);
		LED_SetStatus(LED_Yellow,LED_STAT_ON);
		LED_SetStatus(LED_Red,LED_STAT_OFF);
		if (TimeSec==2 && prev==G)
		{
			state=R;
			TimeSec=0;
		}
		else if (TimeSec==2 && prev==R)
		{
			state=G;
			TimeSec=0;
		}
		break;
	case R:
		LED_SetStatus(LED_Green,LED_STAT_OFF);
		LED_SetStatus(LED_Yellow,LED_STAT_OFF);
		LED_SetStatus(LED_Red,LED_STAT_ON);
		if (TimeSec==20)
		{
			state=Y;
			TimeSec=0;
			prev=R;
		}
		break;
	default:
		break;
	}
	TimeSec += periodicity_sec;
}




