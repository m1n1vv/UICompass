#if defined SPAWNAIRCRAFT
	#endinput
#endif
#define SPAWNAIRCRAFT

#if !defined S_AIR__DISTANCE
	#define S_AIR__DISTANCE			(4000.0)
#endif

#if !defined S_AIR__FLIGHT
	#define S_AIR__FLIGHT			(450.0)
#endif

#if !defined floatrandom
	#define floatrandom(%0) (float(random(%0))+float(random(1000))/1000)
#endif

stock GetDirectionOfAircraft(&Float:angle, &Float:x, &Float:y, &Float:z, &Float:fpoint_x, &Float:fpoint_y, Float:fault = 0.0)
{
    static
        Float:distance = S_AIR__DISTANCE;

    z = S_AIR__FLIGHT;
    angle = floatrandom(360);
    x = 0.0 + distance * -floatsin(angle, degrees);
    y = 0.0 + distance * floatcos(angle, degrees);
    
    distance *= 2.0;
    angle += fault + floatrandom(90) - 45.0;
    fpoint_x = x + distance * -floatsin(angle, degrees);
    fpoint_y = y + distance * floatcos(angle, degrees);
    distance = S_AIR__DISTANCE;
    
    return 1;
}

//Пример:

static
    obj,
    Float:x,
    Float:y,
    Float:z,
    Float:a,
    Float:x_m,
    Float:y_m;

//Узнаем все необходимые значения
GetDirectionOfAircraft(a, x, y, z, x_m, y_m, 180.0);

//Создаем объект
obj = CreateObject(1681, x, y, z, 0.0, 0.0, a);

//Направляем его к конечной точке
MoveObject(obj, x_m, y_m, z, 200.00, 0.0, 0.0, a);
