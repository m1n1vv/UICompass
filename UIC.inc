#if  defined UICOMPASS
    #endinput
#endif
#define UICOMPASS

static const
	uic__str[][] =
	{
	    "NE", "E", "SE", "S", "SW", "W", "NW", "N"
	};

static
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

stock CompassSetString(value)
{
	uic__diff = 0;
	
	if (value > 360)
        value -= 360;
	else if (value < 0)
        value += 360;

	if (!value)
	    value = 360;
	
	if (value % 45 == 0)
		uic__diff = value / 45;

	if (uic__diff)
	    strcat((uic__string[0] = EOS, uic__string), uic__str[uic__diff-1]);
 	else
		valstr(uic__string, value);

	return uic__string;
}
