#pragma once
class Time
{
	unsigned sec;
	unsigned min;
	unsigned hour;

public:
	Time(unsigned sec = 0, unsigned min = 0, unsigned hour = 0)
	{
		setSec(sec);
		setMin(min);
		setHour(hour);
	}

	unsigned getSec()const { return sec; }
	unsigned getMin()const { return min; }
	unsigned getHour()const { return hour; }

	void setSec(unsigned sec)
	{
		if (sec <= 60)
			this->sec = sec;
	}

	void setMin(unsigned min)
	{
		if (min <= 60)
			this->min = min;
	}

	void setHour(unsigned hour)
	{
		if (hour <= 24)
			this->hour = hour;
	}

	unsigned convertToSec()
	{
		double second;
		second = (double)sec + 60 * (double)min + 3600 * (double)hour;
		return second;
	}

};
