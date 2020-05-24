// for singleplayer / offline mode
modded class MissionGameplay
{
	private int ab_PostApoWeatherTime = -1;
	
	void MissionGameplay()
	{
		
	}
	
	void ~MissionGameplay() 
	{
		
	}
	
	override void OnInit()
	{
		super.OnInit();
	}

	override void OnUpdate(float timeslice)
	{
		super.OnUpdate(timeslice);
		
		if (GetGame() && GetGame().IsServer())	
		{
			if ((GetGame().GetTime() - ab_PostApoWeatherTime >= Get_ab_PostApoWeather().GetNextChangeTime() * 1000) || ab_PostApoWeatherTime == -1)
			{
				Get_ab_PostApoWeather().UpdateWeather();
				ab_PostApoWeatherTime = GetGame().GetTime();
			}
		}
	}
}