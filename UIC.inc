/*
	UICompass v0.6
	by m1n1vv
*/

#if  defined UICOMPASS
	#endinput
#endif
#define UICOMPASS

#if !defined MAX_UICOMPASS_TD
	#define MAX_UICOMPASS_TD		7
#endif

#if !defined UICOMPASS_STEP
	#define UICOMPASS_STEP			15
#endif

#if MAX_UICOMPASS_TD % 2 == 0
	#error only an odd number of TextDraws is supported
#endif

static const
	uic__scale = 360,
	uic__interval_main_directions = 360 / 8,
	uic__max_directions = 360 / UICOMPASS_STEP,
	uic__error = UICOMPASS_STEP / 3 + 1,
	uic__str_main_direction[][] =
	{
		"NE", "E", "SE", "S", "SW", "W", "NW", "N"
	};

static
	uic__min_N,
	uic__max_N,
	uic__number_main_direction,
	uic__round,
	uic__multiple,
	uic__result,
	uic__string[4];

stock GetCompassDirection(Float:angle)
{
	uic__round = floatround(angle);
	uic__multiple = uic__round / UICOMPASS_STEP;
	uic__result = uic__multiple * UICOMPASS_STEP;

	if (uic__round - uic__result > uic__error)
		uic__result = ++uic__multiple * UICOMPASS_STEP;

	uic__result = uic__scale - uic__result;

	return uic__result;
}

stock CreateCompassString(angle)
{
	uic__number_main_direction = 0;

	angle %= uic__scale;

	if (angle == 0)
		angle = uic__scale;
	
	if (angle % uic__interval_main_directions == 0)
		uic__number_main_direction = angle / uic__interval_main_directions;

	if (uic__number_main_direction != 0)
		strcat((uic__string[0] = EOS, uic__string), uic__str_main_direction[uic__number_main_direction - 1]);
 	else
		valstr(uic__string, angle);

	return uic__string;
}

stock CompassHeadingNorth(angle)
{
	angle /= UICOMPASS_STEP;

	if (angle >= uic__max_N)
		angle = uic__max_directions - angle + uic__min_N;
	else
		angle = ~(angle - uic__min_N) | 1;

	return angle;
}

public OnGameModeInit()
{
	static const
		getN = (MAX_UICOMPASS_TD + 1) / 2; 

	uic__min_N = getN - 1;
	uic__max_N = uic__max_directions - getN;

#if defined uic__OnGameModeInit
	uic__OnGameModeInit();
#endif
	return 1;
}

#if defined _ALS_OnGameModeInit
	#undef OnGameModeInit
#else
	#define _ALS_OnGameModeInit
#endif
#define  OnGameModeInit uic__OnGameModeInit
#if defined uic__OnGameModeInit
	forward uic__OnGameModeInit();
#endif
