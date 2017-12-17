# UICompass 

> Version: v0.6

![Image alt](http://tscars.narod.ru/p-w/new/N.png)

This include designed to implement the compass in PUBG-style. It displays the current direction including the three previous directions and subsequent direstion.

All directions are multiples of 15. The direction is displayed with the interval. For example, in [41 - 47] will bring 45. Only supported with odd number of TD!

The implementation of the TD on your side.

Functions
---------

**RoundCompassDirection** - rounds the direction to a multiple of UICOMPASS_STEP.

```pawn
RoundCompassDirection(Float:angle);
```

> * **Float:angle** - the current player's direction

---------

**CreateCompassString** - creates a line with the player's direction.

```pawn
CreateCompassString(angle);
```

> * **angle** - the player's direction, obtained from RoundCompassDirection

---------

**CompassHeadingNorth** - determines which of the TD will be displayed "N".

```pawn
CompassHeadingNorth(angle);
```

> * **angle** - the player's direction, obtained from RoundCompassDirection

Directives
---------

| Directives | Description | 
| ------------- |------------------|
| MAX_UICOMPASS_TD | The amount of TD that will be used in Your compass. Default value: 7. |
| UICOMPASS_STEP | The minimum step in degrees. The default value is 15. |

Example
---------

Create callback for the timer.

![Image alt](http://tscars.narod.ru/p-w/new/compass.png)

```pawn
forward UICompassTimer(playerid);
public UICompassTimer(playerid)
{
    static const
        step_1 = UICOMPASS_STEP * 1,
        step_2 = UICOMPASS_STEP * 2,
        step_3 = UICOMPASS_STEP * 3;
        
    static
        north,
        result,
        Float:angle;

    //Find out the player's direction
    GetPlayerFacingAngle(playerid, angle);

    //Get the direction of fold UICOMPASS_STEP
    result = RoundCompassDirection(angle);

    //Find out what TD will be displayed "N"
    north = CompassHeadingNorth(result);

    //Three previous directions
    PlayerTextDrawSetString(playerid, td_uicompass[playerid][0], CreateCompassString(result - step_3));
    PlayerTextDrawSetString(playerid, td_uicompass[playerid][1], CreateCompassString(result - step_2));
    PlayerTextDrawSetString(playerid, td_uicompass[playerid][2], CreateCompassString(result - step_1));

    //The current direction
    PlayerTextDrawSetString(playerid, td_uicompass[playerid][3], CreateCompassString(result));

    //Three next directions
    PlayerTextDrawSetString(playerid, td_uicompass[playerid][4], CreateCompassString(result + step_1));
    PlayerTextDrawSetString(playerid, td_uicompass[playerid][5], CreateCompassString(result + step_2));
    PlayerTextDrawSetString(playerid, td_uicompass[playerid][6], CreateCompassString(result + step_3));

    //Installed all the TD the original color (Ready to listen some proposals for simplify)
    PlayerTextDrawColor(playerid, td_uicompass[playerid][0], 0xFFFFFFFF);
    PlayerTextDrawShow(playerid, td_uicompass[playerid][0]);
    PlayerTextDrawColor(playerid, td_uicompass[playerid][1], 0xFFFFFFFF);
    PlayerTextDrawShow(playerid, td_uicompass[playerid][1]);
    PlayerTextDrawColor(playerid, td_uicompass[playerid][2], 0xFFFFFFFF);
    PlayerTextDrawShow(playerid, td_uicompass[playerid][2]);
    PlayerTextDrawColor(playerid, td_uicompass[playerid][3], 0xFFFFFFFF);
    PlayerTextDrawShow(playerid, td_uicompass[playerid][3]);
    PlayerTextDrawColor(playerid, td_uicompass[playerid][4], 0xFFFFFFFF);
    PlayerTextDrawShow(playerid, td_uicompass[playerid][4]);
    PlayerTextDrawColor(playerid, td_uicompass[playerid][5], 0xFFFFFFFF);
    PlayerTextDrawShow(playerid, td_uicompass[playerid][5]);
    PlayerTextDrawColor(playerid, td_uicompass[playerid][6], 0xFFFFFFFF);
    PlayerTextDrawShow(playerid, td_uicompass[playerid][6]);
    
    //Set the TD yellow color, where it will be displayed "N"
    if (0 <= north < MAX_UICOMPASS_TD)
    {
        PlayerTextDrawColor(playerid, td_uicompass[playerid][north], 0xFFFF00FF);
        PlayerTextDrawShow(playerid, td_uicompass[playerid][north]);
    }

    return 1;
}
```
