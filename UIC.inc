#if  defined UICOMPASS
    #endinput
#endif
#define UICOMPASS

#if !defined UICOMPASS_MAX_TD
	#define UICOMPASS_MAX_TD	7
#endif

static const
	uic__str[][] =
	{
	    "NE", "E", "SE", "S", "SW", "W", "NW", "N"
	};

static
	uic__N,
	uic__min_N,
	uic__max_N,
	uic__diff,
	uic__round,
	uic__multiple,
	uic__result,
	uic__string[4];

stock GetDirectionCompass(Float:angle)
{
	uic__round = floatround(angle);
	uic__multiple = uic__round / 15;
	uic__result = uic__multiple * 15;

	if (uic__round - uic__result > 5)
	    uic__result = ++uic__multiple * 15;

	uic__result = 360 - uic__result;

	return uic__result;
}

stock CompassSetString(angle)
{
	uic__diff = 0;

	if (angle > 360)
	    angle -= 360;
	else if (angle < 0)
	    angle += 360;

	if (!angle)
	    angle = 360;
	
	if (angle % 45 == 0)
		uic__diff = angle / 45;

	if (uic__diff)
	    strcat((uic__string[0] = EOS, uic__string), uic__str[uic__diff-1]);
 	else
		valstr(uic__string, angle);

	return uic__string;
}

stock CompassHeadingNorth(angle)
{
	uic__N = angle / 15;

	if (!(uic__min_N < uic__N <= uic__max_N))
	{
		if (uic__N >= uic__max_N)
			uic__N = 24 - uic__N + uic__min_N;
		else
		{
			uic__N -= uic__min_N ;
			uic__N = ~uic__N + 1; 
		}

	}

	return uic__N;
}

public OnGameModeInit()
{
	static
		getN;

	getN = (UICOMPASS_MAX_TD + 1) / 2; 

	uic__min_N = getN - 1;
	uic__max_N = 24 - getN;

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
