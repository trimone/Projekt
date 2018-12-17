#pragma once

using namespace System;

ref class CurrentSource
{

private:
	String^ deviceName;
	String^ deviceType;
	String^ serialNumber;
	bool polarity;	// 1 = Bipolar
	int maxCur;
	int maxV;
	double actCurrent;
	double frequency;
	double amplitude;
	int phase;
	String^ port;
	bool enable;
	static int count = 0;

	array <wchar_t>^ BCS;// = gcnew array <wchar_t, 1>(3);

	   	 

public:
	CurrentSource()
	{
		count++;

		deviceName = "Current Source " + Convert::ToString(count);
		//deviceName = "Current Source " , count + 1;
		deviceType = "BCS 3/12";
		serialNumber = "-";
		polarity = 1;
		maxCur = 3.0;	// +/-
		maxV = 12.0;
		actCurrent = 0.0;
		frequency = 0;
		amplitude = 0;
		phase = 0;
		port = "COM " + Convert::ToString(99+count);
		enable = false;


	}
	CurrentSource(String^ id)
	{
		
		count++;
		
		BCS = gcnew array <wchar_t, 1>(6);
		deviceName = "Current Source " + Convert::ToString(count);
		id->CopyTo(2, BCS, 0 ,3);
		
		if (id->Contains("BCS"))
		{
			//count++;
			polarity = 1;
		}
		else //if (id->Contains("UCS"))
			polarity = 0;



		int length = id->Length;
		String^ rest;
		rest = "SD";

		for (int i = 14; i < length ; i++)
		{
			while (id[i] != '/')
			{
				
				//rest[i] = 'E';
				rest=rest->Insert(0, "E");
				
			}

		}

		/*polarity = 1;
		if (BCS[0] != 'B')
		{
			polarity = 0;
		}*/


		

		// "HighFinesse BCS3/12 S/N1121347-20181212\r"
		// "HighFinesse BCS255/255 S/N4294967295-20181212\r"

		actCurrent = 0.0;
		frequency = 0;
		amplitude = 0;
		phase = 0;
		port = "COM " + Convert::ToString(99 + count);
		enable = false;

	}
	~CurrentSource()
	{
		count--;
	}
/*
	String^ getName()
	{
		return (deviceName);
	}
	void setName(String^ name)
	{

	}
	String^ getType()
	{

	}
	///<summary> Liefert Serienmummer </summary>
	String^ getSN()
	{

	}
	bool getPolarity()
	{

	}
	double getMaxCur()
	{

	}
	void setCur(double cur)
	{

	}
	double getCur()
	{

	}
	void setFreq(double freq)
	{

	}
	double getFreq()
	{

	}
	void setAmp(double amplitude)
	{

	}
	double getAmp()
	{

	}
	void setPhase(int phase)
	{

	}
	int getPhase()
	{

	}
	void setPort(String^ port)
	{

	}
	String^ getPort()
	{

	}
	void enable()
	{

	}
	void disable()
	{

	}
	*/
	static int getCount()
	{
		return count;
	}
};

