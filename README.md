# DayzPostApoWeatherDayzDesignators
<p>DayZ Standalone server side mod that adds Post-Apo themed weather on the server. Most of time weather is gloomy with occasional short sun light time during specific moments.</p>

### INSTALLATION AND SETUP
This is only for server. Client doesn't need it. Use -servermod=@PostApoWeather command line parameter for your server.

At server side open your mission Init.c and find void main(). Put following code instead of original weather init.

```
Weather weather = g_Game.GetWeather();

weather.MissionWeather(true);    // false = use weather controller from Weather.c

Get_ab_PostApoWeather().GOOD_WEATHER_CHANCE = 75;
Get_ab_PostApoWeather().STORM_WEATHER_CHANCE = 50;
Get_ab_PostApoWeather().ANOMALY_STORM_WEATHER_CHANCE = 50;
Get_ab_PostApoWeather().ANOMALY_STORM_WEATHER_TIMEOUT = 30 * 60;
Get_ab_PostApoWeather().CLEAR_WEATHER_DURATION_MIN = 15 * 60;
Get_ab_PostApoWeather().CLEAR_WEATHER_DURATION_MAX = 30 * 60;
Get_ab_PostApoWeather().GOOD_WEATHER_DURATION_MIN = 20 * 60;
Get_ab_PostApoWeather().GOOD_WEATHER_DURATION_MAX = 30 * 60;
Get_ab_PostApoWeather().BAD_WEATHER_DURATION_MIN = 20 * 60;
Get_ab_PostApoWeather().BAD_WEATHER_DURATION_MAX = 30 * 60;
Get_ab_PostApoWeather().STORM_WEATHER_DURATION_MIN = 5 * 60;
Get_ab_PostApoWeather().STORM_WEATHER_DURATION_MAX = 15 * 60;
Get_ab_PostApoWeather().ANOMALY_STORM_WEATHER_DURATION_MIN = 8 * 60;
Get_ab_PostApoWeather().ANOMALY_STORM_WEATHER_DURATION_MAX = 15 * 60;

Get_ab_PostApoWeather().CLEAR_WEATHER_PARAMS_OVERCAST_MIN = 0.0;
Get_ab_PostApoWeather().CLEAR_WEATHER_PARAMS_OVERCAST_MAX = 0.2;
Get_ab_PostApoWeather().CLEAR_WEATHER_PARAMS_FOG_MIN = 0.0;
Get_ab_PostApoWeather().CLEAR_WEATHER_PARAMS_FOG_MAX = 0.0;
Get_ab_PostApoWeather().CLEAR_WEATHER_PARAMS_WIND_MIN = 0.1;
Get_ab_PostApoWeather().CLEAR_WEATHER_PARAMS_WIND_MAX = 2.0;

Get_ab_PostApoWeather().GOOD_WEATHER_PARAMS_OVERCAST_MIN = 0.6;
Get_ab_PostApoWeather().GOOD_WEATHER_PARAMS_OVERCAST_MAX = 0.7;
Get_ab_PostApoWeather().GOOD_WEATHER_PARAMS_FOG_MIN = 0.0;
Get_ab_PostApoWeather().GOOD_WEATHER_PARAMS_FOG_MAX = 0.1;
Get_ab_PostApoWeather().GOOD_WEATHER_PARAMS_WIND_MIN = 0.1;
Get_ab_PostApoWeather().GOOD_WEATHER_PARAMS_WIND_MAX = 5.0;

Get_ab_PostApoWeather().BAD_WEATHER_PARAMS_OVERCAST_MIN = 0.8;
Get_ab_PostApoWeather().BAD_WEATHER_PARAMS_OVERCAST_MAX = 0.9;
Get_ab_PostApoWeather().BAD_WEATHER_PARAMS_FOG_MIN = 0.05;
Get_ab_PostApoWeather().BAD_WEATHER_PARAMS_FOG_MAX = 0.15;
Get_ab_PostApoWeather().BAD_WEATHER_PARAMS_WIND_MIN = 5.0;
Get_ab_PostApoWeather().BAD_WEATHER_PARAMS_WIND_MAX = 10.0;
Get_ab_PostApoWeather().BAD_WEATHER_PARAMS_RAIN_MIN = 0.01;
Get_ab_PostApoWeather().BAD_WEATHER_PARAMS_RAIN_MAX = 0.5;

Get_ab_PostApoWeather().STORM_WEATHER_PARAMS_OVERCAST_MIN = 0.9;
Get_ab_PostApoWeather().STORM_WEATHER_PARAMS_OVERCAST_MAX = 0.9;
Get_ab_PostApoWeather().STORM_WEATHER_PARAMS_FOG_MIN = 0.15;
Get_ab_PostApoWeather().STORM_WEATHER_PARAMS_FOG_MAX = 0.3;
Get_ab_PostApoWeather().STORM_WEATHER_PARAMS_WIND_MIN = 10.0;
Get_ab_PostApoWeather().STORM_WEATHER_PARAMS_WIND_MAX = 20.0;
Get_ab_PostApoWeather().STORM_WEATHER_PARAMS_RAIN_MIN = 0.6;
Get_ab_PostApoWeather().STORM_WEATHER_PARAMS_RAIN_MAX = 1.0;

Get_ab_PostApoWeather().ANOMALY_STORM_WEATHER_PARAMS_OVERCAST_MIN = 1.0;
Get_ab_PostApoWeather().ANOMALY_STORM_WEATHER_PARAMS_OVERCAST_MAX = 1.0;
Get_ab_PostApoWeather().ANOMALY_STORM_WEATHER_PARAMS_FOG_MIN = 0.0;
Get_ab_PostApoWeather().ANOMALY_STORM_WEATHER_PARAMS_FOG_MAX = 0.0;
Get_ab_PostApoWeather().ANOMALY_STORM_WEATHER_PARAMS_WIND_MIN = 30.0;
Get_ab_PostApoWeather().ANOMALY_STORM_WEATHER_PARAMS_WIND_MAX = 40.0;

Get_ab_PostApoWeather().WEATHER_PARAMS_RAIN_THRESHOLD_OVERCAST_MIN = 0.55;
Get_ab_PostApoWeather().WEATHER_PARAMS_RAIN_THRESHOLD_OVERCAST_MAX = 1.0;
Get_ab_PostApoWeather().WEATHER_PARAMS_RAIN_THRESHOLD_STOP_TIME = 60.0;

Get_ab_PostApoWeather().Start();
```

### API
**_Get_ab_PostApoWeather().Start()_**

Starts weather manager and generates first weather update if necessary.

**_Get_ab_PostApoWeather().Stop()_**
  
Stops or pauses weather manager. For example if you want plug your own weather effect for a while. Resume weather manager with Start();

**_Confuguration properties_**

Properties can be changed anytime during runtime. Meaing is self-explanatory.
First, good weather chance is decided. Second, if bad weather is selected, rain or storm weather chance is decided. On top of that checks for anomaly storm is running.

**_Get_ab_PostApoWeather().GOOD_WEATHER_CHANCE_** - int percentage 0 - 100%
**_Get_ab_PostApoWeather().STORM_WEATHER_CHANCE_** - int percentage 0 - 100%
**_Get_ab_PostApoWeather().ANOMALY_STORM_WEATHER_CHANCE_** - int percentage 0 - 100%
**_Get_ab_PostApoWeather().ANOMALY_STORM_WEATHER_TIMEOUT_** - int time in seconds
**_Get_ab_PostApoWeather().CLEAR_WEATHER_DURATION_MIN_** - int time in seconds
**_Get_ab_PostApoWeather().CLEAR_WEATHER_DURATION_MAX_** - int time in seconds
**_Get_ab_PostApoWeather().GOOD_WEATHER_DURATION_MIN_** - int time in seconds
**_Get_ab_PostApoWeather().GOOD_WEATHER_DURATION_MAX_** - int time in seconds
**_Get_ab_PostApoWeather().BAD_WEATHER_DURATION_MIN_** - int time in seconds
**_Get_ab_PostApoWeather().BAD_WEATHER_DURATION_MAX_** - int time in seconds
**_Get_ab_PostApoWeather().STORM_WEATHER_DURATION_MIN_** - int time in seconds
**_Get_ab_PostApoWeather().STORM_WEATHER_DURATION_MAX_** - int time in seconds
**_Get_ab_PostApoWeather().ANOMALY_STORM_WEATHER_DURATION_MIN_** - int time in seconds
**_Get_ab_PostApoWeather().ANOMALY_STORM_WEATHER_DURATION_MAX_** - int time in seconds

**_Get_ab_PostApoWeather().CLEAR_WEATHER_PARAMS_OVERCAST_MIN_** - float 0.0 - 1.0
**_Get_ab_PostApoWeather().CLEAR_WEATHER_PARAMS_OVERCAST_MAX_** - float 0.0 - 1.0
**_Get_ab_PostApoWeather().CLEAR_WEATHER_PARAMS_FOG_MIN_** - float 0.0 - 1.0
**_Get_ab_PostApoWeather().CLEAR_WEATHER_PARAMS_FOG_MAX_** - float 0.0 - 1.0
**_Get_ab_PostApoWeather().CLEAR_WEATHER_PARAMS_WIND_MIN_** - float
**_Get_ab_PostApoWeather().CLEAR_WEATHER_PARAMS_WIND_MAX_** - float

**_Get_ab_PostApoWeather().GOOD_WEATHER_PARAMS_OVERCAST_MIN_** - float 0.0 - 1.0
**_Get_ab_PostApoWeather().GOOD_WEATHER_PARAMS_OVERCAST_MAX_** - float 0.0 - 1.0
**_Get_ab_PostApoWeather().GOOD_WEATHER_PARAMS_FOG_MIN_** - float 0.0 - 1.0
**_Get_ab_PostApoWeather().GOOD_WEATHER_PARAMS_FOG_MAX_** - float 0.0 - 1.0
**_Get_ab_PostApoWeather().GOOD_WEATHER_PARAMS_WIND_MIN_** - float
**_Get_ab_PostApoWeather().GOOD_WEATHER_PARAMS_WIND_MAX_** - float

**_Get_ab_PostApoWeather().BAD_WEATHER_PARAMS_OVERCAST_MIN_** - float 0.0 - 1.0
**_Get_ab_PostApoWeather().BAD_WEATHER_PARAMS_OVERCAST_MAX_** - float 0.0 - 1.0
**_Get_ab_PostApoWeather().BAD_WEATHER_PARAMS_FOG_MIN_** - float 0.0 - 1.0
**_Get_ab_PostApoWeather().BAD_WEATHER_PARAMS_FOG_MAX_** - float 0.0 - 1.0
**_Get_ab_PostApoWeather().BAD_WEATHER_PARAMS_WIND_MIN_** - float
**_Get_ab_PostApoWeather().BAD_WEATHER_PARAMS_WIND_MAX_** - float
**_Get_ab_PostApoWeather().BAD_WEATHER_PARAMS_RAIN_MIN_** - float 0.0 - 1.0
**_Get_ab_PostApoWeather().BAD_WEATHER_PARAMS_RAIN_MAX_** - float 0.0 - 1.0

**_Get_ab_PostApoWeather().STORM_WEATHER_PARAMS_OVERCAST_MIN_** - float 0.0 - 1.0
**_Get_ab_PostApoWeather().STORM_WEATHER_PARAMS_OVERCAST_MAX_** - float 0.0 - 1.0
**_Get_ab_PostApoWeather().STORM_WEATHER_PARAMS_FOG_MIN_** - float 0.0 - 1.0
**_Get_ab_PostApoWeather().STORM_WEATHER_PARAMS_FOG_MAX_** - float 0.0 - 1.0
**_Get_ab_PostApoWeather().STORM_WEATHER_PARAMS_WIND_MIN_** - float
**_Get_ab_PostApoWeather().STORM_WEATHER_PARAMS_WIND_MAX_** - float
**_Get_ab_PostApoWeather().STORM_WEATHER_PARAMS_RAIN_MIN_** - float 0.0 - 1.0
**_Get_ab_PostApoWeather().STORM_WEATHER_PARAMS_RAIN_MAX_** - float 0.0 - 1.0

**_Get_ab_PostApoWeather().ANOMALY_STORM_WEATHER_PARAMS_OVERCAST_MIN_** - float 0.0 - 1.0
**_Get_ab_PostApoWeather().ANOMALY_STORM_WEATHER_PARAMS_OVERCAST_MAX_** - float 0.0 - 1.0
**_Get_ab_PostApoWeather().ANOMALY_STORM_WEATHER_PARAMS_FOG_MIN_** - float 0.0 - 1.0
**_Get_ab_PostApoWeather().ANOMALY_STORM_WEATHER_PARAMS_FOG_MAX_** - float 0.0 - 1.0
**_Get_ab_PostApoWeather().ANOMALY_STORM_WEATHER_PARAMS_WIND_MIN_** - float
**_Get_ab_PostApoWeather().ANOMALY_STORM_WEATHER_PARAMS_WIND_MAX_** - float

**_Get_ab_PostApoWeather().WEATHER_PARAMS_RAIN_THRESHOLD_OVERCAST_MIN_** - float 0.0 - 1.0
**_Get_ab_PostApoWeather().WEATHER_PARAMS_RAIN_THRESHOLD_OVERCAST_MAX_** - float 0.0 - 1.0
**_Get_ab_PostApoWeather().WEATHER_PARAMS_RAIN_THRESHOLD_STOP_TIME_** - float time in seconds

### CREDITS
<ul>
  <li>Code by ataribaby.</li>
</ul>

### LICENSE
Mod is open source and you are free to modify, repack and publish. If you fix or enhance it please consider push it to me for intergration into official version.

Steam Workshop link: https://steamcommunity.com/sharedfiles/filedetails/?id=2106737468

