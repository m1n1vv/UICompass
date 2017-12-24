/*==========================================================================

	Copyright (c) 2017 Yakovlev Ivan.

This software is provided 'as-is', without any express or implied warranty.
In no event will the authors be held liable for any damages arising from the
use of this software.

Permission is granted to anyone to use this software for
any purpose, including commercial applications, and to alter it and
redistribute it freely, subject to the following restrictions:

1.	The origin of this software must not be misrepresented; you must not
	claim that you wrote the original software. If you use this software in
	a product, an acknowledgment in the product documentation would be
	appreciated but is not required.

2.	Altered source versions must be plainly marked as such, and must not be
	misrepresented as being the original software.

3.	This notice may not be removed or altered from any source distribution.

=========================================================================*/

#if  defined UICOMPASS
	#endinput
#endif
#define UICOMPASS

#if !defined MAX_UICOMPASS_TD
	#define MAX_UICOMPASS_TD			7
#endif

#if MAX_UICOMPASS_TD % 2 == 0
	#error only supported with odd number of TD
#endif

#if !defined MAX_UICOMPASS_STEP
	#define MAX_UICOMPASS_STEP			15
#endif

#if !defined MIN_UICOMPASS_STEP
	#define MIN_UICOMPASS_STEP			5
#endif

#if !defined FIX_UICOMPASS_VALUE
	#define FIX_UICOMPASS_VALUE(%0)			(%0 / 3 + 5)
#endif

static const
	uic__scale = 360,
	uic__interval_main_directions = 360 / 8,
	uic__max_directions = 360 / MAX_UICOMPASS_STEP,
	uic__get_n = (MAX_UICOMPASS_TD + 1) / 2,
	uic__str_main_direction[][] =
	{
		"NE", "E", "SE", "S", "SW", "W", "NW", "N"
	};

static
	uic__min_n,
	uic__max_n,
	uic__number_main_direction,
	uic__round,
	uic__multiple,
	uic__error,
	uic__result,
	uic__string[4];

stock RoundCompassDirection(Float:angle, round = MAX_UICOMPASS_STEP)
{
	uic__round = floatround(angle);
	uic__error = FIX_UICOMPASS_VALUE(round);
	uic__multiple = uic__round / round;
	uic__result = uic__multiple * round;

	if (uic__round - uic__result > uic__error)
		uic__result = ++uic__multiple * round;

	uic__result = uic__scale - uic__result;

	return uic__result;
}

stock CreateCompassString(angle, round = MAX_UICOMPASS_STEP)
{
	uic__number_main_direction = 0;

	angle %= uic__scale;

	if (angle == 0)
		angle = uic__scale;
	
	if (angle % uic__interval_main_directions == 0  && round == MAX_UICOMPASS_STEP)
		uic__number_main_direction = angle / uic__interval_main_directions;

	if (uic__number_main_direction != 0)
		strcat((uic__string[0] = EOS, uic__string), uic__str_main_direction[uic__number_main_direction - 1]);
 	else
		valstr(uic__string, angle);

	return uic__string;
}

stock CompassHeadingNorth(angle)
{
	angle /= MAX_UICOMPASS_STEP;

	if (angle >= uic__max_n)
		angle = uic__max_directions - angle + uic__min_n;
	else
		angle = ~(angle - uic__min_n) + 1;

	return angle;
}

public OnGameModeInit()
{
	uic__min_n = uic__get_n - 1;
	uic__max_n = uic__max_directions - uic__get_n;

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

/*
	UICompass v0.7
	by m1n1vv
*/
