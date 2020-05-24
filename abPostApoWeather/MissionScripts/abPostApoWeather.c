static ref ab_PostApoWeather g_ab_PostApoWeather;
static ref ab_PostApoWeather Get_ab_PostApoWeather()
{
	if (!g_ab_PostApoWeather) 
	{
		g_ab_PostApoWeather = new ref ab_PostApoWeather();
	}
	return g_ab_PostApoWeather;
}

enum ab_PostApoWeatherTypes
{
	START,
	PRE_CLEAR,
	CLEAR,
	PRE_GOOD,
	GOOD,
	PRE_BAD,
	BAD,
	PRE_STORM,
	STORM,
	PRE_ANOMALY_STORM,
	ANOMALY_STORM
}

class ab_PostApoWeather
{
	int GOOD_WEATHER_CHANCE = 75;
	int STORM_WEATHER_CHANCE = 50;
	int ANOMALY_STORM_WEATHER_CHANCE = 50;
	int ANOMALY_STORM_WEATHER_TIMEOUT = 30 * 60;
	int CLEAR_WEATHER_DURATION_MIN = 15 * 60;
	int CLEAR_WEATHER_DURATION_MAX = 30 * 60;
	int GOOD_WEATHER_DURATION_MIN = 20 * 60;
	int GOOD_WEATHER_DURATION_MAX = 30 * 60;
	int BAD_WEATHER_DURATION_MIN = 20 * 60;
	int BAD_WEATHER_DURATION_MAX = 30 * 60;
	int STORM_WEATHER_DURATION_MIN = 5 * 60;
	int STORM_WEATHER_DURATION_MAX = 15 * 60;
	int ANOMALY_STORM_WEATHER_DURATION_MIN = 8 * 60;
	int ANOMALY_STORM_WEATHER_DURATION_MAX = 15 * 60;

	private bool started = false;
	private bool initialChange = true;
	private int nextChangeTime = 99999;
	private ab_PostApoWeatherTypes currentWeather = ab_PostApoWeatherTypes.START;
	private int lastAnomalyStormTime = 0;
	private float overcast;
	private float fog;
	private float wind;
	
	void ab_PostApoWeather()
	{	
			
	}
	
	void ~ab_PostApoWeather() 
	{
		
	}
	
	int GetNextChangeTime()
	{
		return nextChangeTime;
	}
	
	vector GetRandomWind(float speed)
	{
		float angle = 250;
		float x = speed * Math.Sin(angle * Math.DEG2RAD);
		float z = speed * Math.Cos(angle * Math.DEG2RAD);
		return Vector(x, 0, z);
	}
	
	void Start()
	{
		Print("PostApoWeather: Started");
		started = true;
		UpdateWeather();
	}
	
	void Stop()
	{
		Print("PostApoWeather: Stopped");
		started = false;
	}
	
	void SetRain(float forecast, float time, float minDuration)
	{
		Print("PostApoWeather: Rain forecast:" + forecast + " timeToChange:" + time + " duration:" + minDuration);
		
		if (!g_Game) return;
		
		Weather weather = g_Game.GetWeather();
		
		if (!Weather) return;
		
		weather.GetRain().Set(forecast, time, minDuration);
	}
	
	void SetOvercast(float forecast, float time, float minDuration)
	{
		Print("PostApoWeather: Overcast forecast:" + forecast + " timeToChange:" + time + " duration:" + minDuration);
		
		if (!g_Game) return;
		
		Weather weather = g_Game.GetWeather();
		
		if (!Weather) return;
		
		weather.GetOvercast().Set(forecast, time, minDuration);
	}
	
	void SetFog(float forecast, float time, float minDuration)
	{
		Print("PostApoWeather: Fog forecast:" + forecast + " timeToChange:" + time + " duration:" + minDuration);
		
		if (!g_Game) return;
		
		Weather weather = g_Game.GetWeather();
		
		if (!Weather) return;
		
		weather.GetFog().Set(forecast, time, minDuration);
	}
	
	void SetWind(float speed, float time)
	{
		Print("PostApoWeather: Wind speed:" + speed + " time:" + time);
		
		if (!g_Game) return;
		
		Weather weather = g_Game.GetWeather();
		
		if (!Weather) return;
		
		weather.SetWindMaximumSpeed(speed);
		weather.SetWind(GetRandomWind(speed));
		weather.SetWindSpeed(speed);
		weather.SetWindFunctionParams(0.5, 1.0, time);
	}
	
	void UpdateWeather()
	{
		if (!started) return;
		
		Print("PostApoWeather: Update");
		
		if (!g_Game) return;
		
		Weather weather = g_Game.GetWeather();
		
		if (!Weather) return;
		
		float chance = Math.RandomIntInclusive(0, 100);
		
		if(currentWeather == ab_PostApoWeatherTypes.START)
		{
			currentWeather = ab_PostApoWeatherTypes.PRE_GOOD;
		}
		else if(currentWeather == ab_PostApoWeatherTypes.PRE_CLEAR)
		{
			currentWeather = ab_PostApoWeatherTypes.CLEAR;
		}
		else if(currentWeather == ab_PostApoWeatherTypes.PRE_GOOD)
		{
			currentWeather = ab_PostApoWeatherTypes.GOOD;
		}
		else if(currentWeather == ab_PostApoWeatherTypes.PRE_BAD)
		{
			currentWeather = ab_PostApoWeatherTypes.BAD;
		}
		else if(currentWeather == ab_PostApoWeatherTypes.PRE_STORM)
		{
			currentWeather = ab_PostApoWeatherTypes.STORM;
		}
		else if(currentWeather == ab_PostApoWeatherTypes.PRE_ANOMALY_STORM)
		{
			currentWeather = ab_PostApoWeatherTypes.ANOMALY_STORM;
		}
		else if(currentWeather == ab_PostApoWeatherTypes.ANOMALY_STORM)
		{
			currentWeather = ab_PostApoWeatherTypes.PRE_CLEAR;
		}
		else
		{
			if (lastAnomalyStormTime == -1)
			{
				lastAnomalyStormTime = GetGame().GetTime();
			}
			
			if (GetGame().GetTime() - lastAnomalyStormTime >= ANOMALY_STORM_WEATHER_TIMEOUT * 1000 && chance < ANOMALY_STORM_WEATHER_CHANCE)
			{
				currentWeather = ab_PostApoWeatherTypes.PRE_ANOMALY_STORM;
			}
			else if (chance < GOOD_WEATHER_CHANCE)
			{
				currentWeather = ab_PostApoWeatherTypes.PRE_GOOD;
			}
			else
			{
				chance = Math.RandomIntInclusive(0, 100);
				
				if (chance < STORM_WEATHER_CHANCE)
				{
					if(currentWeather == ab_PostApoWeatherTypes.PRE_BAD || currentWeather == ab_PostApoWeatherTypes.PRE_STORM)
					{
						currentWeather = ab_PostApoWeatherTypes.STORM;
					}
					else
					{
						currentWeather = ab_PostApoWeatherTypes.PRE_STORM;
					}
				}
				else
				{
					if(currentWeather == ab_PostApoWeatherTypes.PRE_BAD || currentWeather == ab_PostApoWeatherTypes.PRE_STORM)
					{
						currentWeather = ab_PostApoWeatherTypes.BAD;
					}
					else
					{
						currentWeather = ab_PostApoWeatherTypes.PRE_BAD;
					}
				}
			}
			
			if (GetGame().GetTime() - lastAnomalyStormTime >= ANOMALY_STORM_WEATHER_TIMEOUT * 1000)
			{
				lastAnomalyStormTime = GetGame().GetTime();
			}
		}
		
		float speedOfChange;
		weather.SetRainThresholds(0.55, 1.0, 60);
		
		switch(currentWeather)
		{
			case ab_PostApoWeatherTypes.PRE_CLEAR:
				Print("PostApoWeather: PRE_CLEAR selected");
				nextChangeTime = 10;
				break;
			case ab_PostApoWeatherTypes.CLEAR:
				Print("PostApoWeather: CLEAR selected");
				nextChangeTime = Math.RandomIntInclusive(CLEAR_WEATHER_DURATION_MIN, CLEAR_WEATHER_DURATION_MAX);
				
				if (initialChange)
				{
					speedOfChange = 0;
				}
				else
				{
					speedOfChange = nextChangeTime * 0.1;
					speedOfChange = Math.Min(12 * 60, speedOfChange);
				}
				
				weather.SetStorm(0.0, 1.0, 45);
				SetOvercast(Math.RandomFloatInclusive(0.0, 0.2), speedOfChange, nextChangeTime);
				SetRain(0, speedOfChange, nextChangeTime);
				SetFog(0, speedOfChange, nextChangeTime);
				SetWind(Math.RandomFloatInclusive(0.1, 2.0), speedOfChange);
				break;
			case ab_PostApoWeatherTypes.PRE_GOOD:
				Print("PostApoWeather: PRE_GOOD selected");
				nextChangeTime = Math.RandomIntInclusive(GOOD_WEATHER_DURATION_MIN * 0.1, GOOD_WEATHER_DURATION_MAX * 0.1);
				nextChangeTime = Math.Min(12 * 60, nextChangeTime);
				
				if (initialChange)
				{
					speedOfChange = 0;
				}
				else
				{
					speedOfChange = nextChangeTime * 0.8;
				}
				
				overcast = Math.RandomFloatInclusive(0.6, 0.7);
				fog = Math.RandomFloatInclusive(0.0, 0.1);
				wind = Math.RandomFloatInclusive(0.1, 5.0);
				
				weather.SetStorm(0.0, 1.0, 45);
				SetOvercast(overcast, speedOfChange, nextChangeTime);
				SetRain(0, speedOfChange, nextChangeTime);
				SetFog(fog, speedOfChange, nextChangeTime);
				SetWind(wind, speedOfChange);
				break;
			case ab_PostApoWeatherTypes.GOOD:
				Print("PostApoWeather: GOOD selected");
				nextChangeTime = Math.RandomIntInclusive(GOOD_WEATHER_DURATION_MIN, GOOD_WEATHER_DURATION_MAX);
				
				if (initialChange)
				{
					speedOfChange = 0;
				}
				else
				{
					speedOfChange = nextChangeTime * 0.1;
					speedOfChange = Math.Min(12 * 60, speedOfChange);
				}
				
				weather.SetStorm(0.0, 1.0, 45);
				SetOvercast(overcast, speedOfChange, nextChangeTime);
				SetRain(0, speedOfChange, nextChangeTime);
				SetFog(fog, speedOfChange, nextChangeTime);
				SetWind(wind, speedOfChange);
				break;
			case ab_PostApoWeatherTypes.PRE_BAD:
				Print("PostApoWeather: PRE_BAD selected");
				nextChangeTime = Math.RandomIntInclusive(BAD_WEATHER_DURATION_MIN * 0.1, BAD_WEATHER_DURATION_MAX * 0.1);
				nextChangeTime = Math.Min(12 * 60, nextChangeTime);
				
				if (initialChange)
				{
					speedOfChange = 0;
				}
				else
				{
					speedOfChange = nextChangeTime * 0.8;
				}
				
				overcast = Math.RandomFloatInclusive(0.8, 0.9);
				fog = Math.RandomFloatInclusive(0.05, 0.15);
				wind = Math.RandomFloatInclusive(5.0, 10.0);
				
				weather.SetStorm(0.0, 1.0, 45);
				SetOvercast(overcast, speedOfChange, nextChangeTime);
				SetFog(fog, speedOfChange, nextChangeTime);
				SetWind(wind, speedOfChange);
				break;
			case ab_PostApoWeatherTypes.BAD:
				Print("PostApoWeather: BAD selected");
				nextChangeTime = Math.RandomIntInclusive(BAD_WEATHER_DURATION_MIN, BAD_WEATHER_DURATION_MAX);
				
				if (initialChange)
				{
					speedOfChange = 0;
				}
				else
				{
					speedOfChange = nextChangeTime * 0.1;
					speedOfChange = Math.Min(12 * 60, speedOfChange);
				}
				
				weather.SetStorm(0.0, 1.0, 45);
				SetOvercast(overcast, speedOfChange, nextChangeTime);
				SetRain(Math.RandomFloatInclusive(0.01, 0.5), speedOfChange, nextChangeTime);
				SetFog(fog, speedOfChange, nextChangeTime);
				SetWind(wind, speedOfChange);
				break;
			case ab_PostApoWeatherTypes.PRE_STORM:
				Print("PostApoWeather: PRE_STORM selected");
				nextChangeTime = Math.RandomIntInclusive(STORM_WEATHER_DURATION_MIN * 0.1, STORM_WEATHER_DURATION_MIN * 0.1);
				nextChangeTime = Math.Min(6 * 60, nextChangeTime);
				
				if (initialChange)
				{
					speedOfChange = 0;
				}
				else
				{
					speedOfChange = nextChangeTime * 0.8;
				}
				
				fog = Math.RandomFloatInclusive(0.15, 0.3);
				wind = Math.RandomFloatInclusive(10.0, 20.0);
				
				weather.SetStorm(1.0, 0.85, 45);
				SetOvercast(9.0, speedOfChange, nextChangeTime);
				SetFog(fog, speedOfChange, nextChangeTime);
				SetWind(wind, speedOfChange);
				break;
			case ab_PostApoWeatherTypes.STORM:
				Print("PostApoWeather: STORM selected");
				nextChangeTime = Math.RandomIntInclusive(STORM_WEATHER_DURATION_MIN, STORM_WEATHER_DURATION_MAX);
				
				if (initialChange)
				{
					speedOfChange = 0;
				}
				else
				{
					speedOfChange = nextChangeTime * 0.1;
					speedOfChange = Math.Min(6 * 60, speedOfChange);
				}
				
				weather.SetStorm(1.0, 0.85, Math.RandomFloatInclusive(20, 45));
				SetOvercast(9.0, speedOfChange, nextChangeTime);
				SetRain(Math.RandomFloatInclusive(0.6, 1.0), speedOfChange, nextChangeTime);
				SetFog(fog, speedOfChange, nextChangeTime);
				SetWind(wind, speedOfChange);
				break;
			case ab_PostApoWeatherTypes.PRE_ANOMALY_STORM:
				Print("PostApoWeather: PRE_ANOMALY_STORM selected");
				nextChangeTime = Math.RandomIntInclusive(30, 50);
				
				if (initialChange)
				{
					speedOfChange = 0;
				}
				else
				{
					speedOfChange = nextChangeTime * 0.8;
				}
				
				wind = Math.RandomFloatInclusive(30.0, 40.0);
				
				weather.GetOvercast().Set(1.0, speedOfChange, nextChangeTime);
				SetRain(0, speedOfChange, nextChangeTime);
				SetFog(0, speedOfChange, nextChangeTime);
				SetWind(wind, speedOfChange);
				break;
			case ab_PostApoWeatherTypes.ANOMALY_STORM:
				Print("PostApoWeather: ANOMALY_STORM selected");
				nextChangeTime = Math.RandomIntInclusive(ANOMALY_STORM_WEATHER_DURATION_MIN, ANOMALY_STORM_WEATHER_DURATION_MAX);
				
				if (initialChange)
				{
					speedOfChange = 0;
				}
				else
				{
					speedOfChange = 20;
				}
				
				weather.SetStorm(1.0, 0.85, 2.5);
				SetOvercast(1.0, speedOfChange, nextChangeTime);
				SetRain(0, speedOfChange, nextChangeTime);
				SetFog(0, speedOfChange, nextChangeTime);
				SetWind(wind, speedOfChange);
				break;
			default:
				break;
		}
		
		initialChange = false;
	}
}