/********************************
  Name: Player
  Copyright:
  Author: Jorge Marino
  Date: 09/07/08 18:15
  Description: Clock
********************************/

class Clock
{
	DWORD start;
public:

	void Init()
	{
		start = GetTickCount();
	};

	float GetEllapsedSeconds()
	{
		DWORD t = GetTickCount();
		float g = (float)(t-start);
		start = t;
		return g/1000.0f;
	};
}; 
