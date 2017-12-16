# UICompass 

> Версия: v0.6

![Image alt](http://tscars.narod.ru/p-w/new/N.png)

Данный инклуд предназначен для реализации компаса с стиле PUBG. Он выводит нынешнее направление включая три предыдущих и последующих. 

Все направления кратные 15. Направление выводится с интервалом. Например при [41 - 47] выведет 45. Поддерживается только нечетное количество TD!

Реализация TD на вашей стороне.

Функции
---------

**RoundCompassDirection** - округляет направление до кратного UICOMPASS_STEP.

```pawn
RoundCompassDirection(Float:angle);
```

> * **Float:angle** - нынешнее направление игрока

---------

**CreateCompassString** - создает строку с направлением игрока.

```pawn
CreateCompassString(angle);
```

> * **angle** - направление игрока полученное из RoundCompassDirection

---------

**CompassHeadingNorth** - определяет, в каком из TD будет выведено "N".

```pawn
CompassHeadingNorth(angle);
```

> * **angle** - направление игрока полученное из RoundCompassDirection

Директивы
---------

| Директивы | Описание | 
| ------------- |------------------|
| MAX_UICOMPASS_TD | Количество TD, которое будет использоваться в Вашем компасе. По умолчанию 7. |
| UICOMPASS_STEP | Минимальный шаг в градусах. По умолчанию 15. |

Применение
---------

Создаем коллбэк для таймера.

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

    //Узнаем направление игрока
    GetPlayerFacingAngle(playerid, angle);

    //Получаем направление кратное UICOMPASS_STEP
    result = RoundCompassDirection(angle);

    //Узнаем, в каком TD будет выведено "N"
    north = CompassHeadingNorth(result);

    //Три предыдущих направления
    PlayerTextDrawSetString(playerid, td_uicompass[playerid][0], CreateCompassString(result - step_3));
    PlayerTextDrawSetString(playerid, td_uicompass[playerid][1], CreateCompassString(result - step_2));
    PlayerTextDrawSetString(playerid, td_uicompass[playerid][2], CreateCompassString(result - step_1));

    //Нынешнее направление
    PlayerTextDrawSetString(playerid, td_uicompass[playerid][3], CreateCompassString(result));

    //Три последующих направления
    PlayerTextDrawSetString(playerid, td_uicompass[playerid][4], CreateCompassString(result + step_1));
    PlayerTextDrawSetString(playerid, td_uicompass[playerid][5], CreateCompassString(result + step_2));
    PlayerTextDrawSetString(playerid, td_uicompass[playerid][6], CreateCompassString(result + step_3));

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
    if (0 <= north < MAX_UICOMPASS_TD)
    {
        PlayerTextDrawColor(playerid, td_uicompass[playerid][north], 0xFFFF00FF);
        PlayerTextDrawShow(playerid, td_uicompass[playerid][north]);
    }

    return 1;
}
```
