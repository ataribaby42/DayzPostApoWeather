class CfgPatches
{
	class abPostApoWeather
	{
		units[]={};
		weapons[]={};
		requiredVersion=0.1;
		requiredAddons[]=
		{
			"DZ_Data"
		};
	};
};

class CfgMods
{
	class abPostApoWeather
	{
		type="mod";
		dependencies[] = {"Game"};
		
		class defs
		{
			class missionScriptModule
			{
				value="";
				files[]={"abPostApoWeather/MissionScripts"};
			};
		};
	};

};