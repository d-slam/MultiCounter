#include <Arduino.h>
#include <Servo.h>

class ServoHold
{
public:
	ServoHold(int p) : pin(p) {}
	void setup() { mServo.attach(pin); }
	void doWrite() { mServo.write(winkel); }
	void setWinkel(int w) { winkel = w; }

	bool fkt(int goTill)
	{
		static int count = goTill;

		count--;
		if (count <= 0)
		{
			count = 0;
			return false;
		}
		else
		{
			return fkt(count);
		}
	}

private:
	int pin;
	int winkel;
	Servo mServo;
};

ServoHold GierPlaneServo(6);

void setup()
{
	Serial.begin(9600);
	Serial.println("serial da!");
	GierPlaneServo.setup();
}

void loop()
{
	if (GierPlaneServo.fkt(50) == false)
	{
		GierPlaneServo.fkt(50);
	}
	delay(50);
}