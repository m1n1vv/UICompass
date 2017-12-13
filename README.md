# UICompass 
> Версия: V3

![Image alt](http://tscars.narod.ru/p-w/new/N.png)

Данный инклуд предназначен для реализации компаса с стиле PUBG. Он выводит нынешнее направление включая три предыдущих и последующих. 

Все направления кратные 15. Направление выводится с интервалом. Например при [41 - 47] выведет 45. Поддерживается только нечетное количество TD!

Реализация TD на вашей стороне.

Функции
---------

**GetDirectionCompass** - округляет направление до кратного 15.

```pawn
GetDirectionCompass(Float:angle);
```

> * **Float:angle** - нынешнее направление игрока

---------

**CompassSetString** - создает строку с направлением игрока.

```pawn
CompassSetString(angle);
```

> * **angle** - направление игрока полученное из GetDirectionCompass

---------

**CompassHeadingNorth** - определяет, в каком из TD будет выведено "N".

```pawn
CompassHeadingNorth(angle);
```

> * **angle** - направление игрока полученное из GetDirectionCompass

Директивы
---------
Директивы|Описание
---|---
UICOMPASS_MAX_TD|Количество TD, которое будет использоваться в Вашем компасе. По умолчанию 7.

Применение
---------
Создаем коллбэк для таймера.

![Image alt](http://tscars.narod.ru/p-w/new/compass.png)

```pawn
forward UICompassTimer(playerid);
public UICompassTimer(playerid)
{
    static
        north,
        result,
        Float:angle;

    north = 0;

    //Узнаем направление игрока
    GetPlayerFacingAngle(playerid, angle);

    //Получаем направление кратное 15
    result = GetDirectionCompass(angle);

    //Узнаем, в каком TD будет выведено "N"
    north = CompassHeadingNorth(result);

    //Три предыдущих направления
    PlayerTextDrawSetString(playerid, td_uicompass[playerid][0], CompassSetString(result-45));
    PlayerTextDrawSetString(playerid, td_uicompass[playerid][1], CompassSetString(result-30));
    PlayerTextDrawSetString(playerid, td_uicompass[playerid][2], CompassSetString(result-15));

    //Нынешнее направление
    PlayerTextDrawSetString(playerid, td_uicompass[playerid][3], CompassSetString(result));

    //Три последующих направления
    PlayerTextDrawSetString(playerid, td_uicompass[playerid][4], CompassSetString(result+15));
    PlayerTextDrawSetString(playerid, td_uicompass[playerid][5], CompassSetString(result+30));
    PlayerTextDrawSetString(playerid, td_uicompass[playerid][6], CompassSetString(result+45));

    //Устанавливаем всем TD изначальный цвет (Готов выслушать предложения по упрощению)
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
    
    //Устанавливаем нужному TD желтый цвет, где будет выведено "N"
    if (0 <= north < UICOMPASS_MAX_TD)
    {
        PlayerTextDrawColor(playerid, td_uicompass[playerid][north], 0xFFFF00FF);
        PlayerTextDrawShow(playerid, td_uicompass[playerid][north]);
    }

    return 1;
}
```
