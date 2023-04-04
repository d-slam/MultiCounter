#include <Arduino.h>

typedef enum
{
	up,
	nix,
	down
} richtung;

class Counter
{
public:
	void setMax(int m) { max = m; }
	void setMin(int m) { min = m; }
	void setStatus(richtung r) { mRichtung = r; }
	richtung getStatus() { return mRichtung; }
	int getCurrent() { return current; }


	richtung countTo(richtung r)
	{
		if (r == nix)
		{
			return nix;
		}
		if (r == up)
		{
			if (current >= max)
			{
				return nix;
			}
			else
			{
				current++;
				return up;
			}
		}
		if (r == down)
		{
			if (current <= min) // ende
			{
				return nix;
			}
			else
			{
				current--;
				return down; // in progress!!
			}
		}
	}


private:
	richtung mRichtung = nix;
	int max = 0;
	int min = 0;

	int neu = 90;
	int current = neu;
};

Counter countAlf;
Counter countBob;

void setup()
{
	Serial.begin(9600);
	Serial.println("bello bellt!");

	countAlf.setMax(166);
	countAlf.setMin(10);

	countBob.setMax(178);
	countBob.setMin(15);
}

richtung rFlagAlf = down;
richtung rFlagBob = up;

void serialHelper(Counter &m, String who)
{
	Serial.print(who);
	Serial.print("...");
	Serial.print(m.getCurrent());
	Serial.println();
}

void loop()
{

	if (rFlagAlf != nix)
	{
		if (rFlagAlf == up)
		{
			serialHelper(countAlf, "Alf up");
			rFlagAlf = countAlf.countTo(up);
		}
		else if (rFlagAlf == down)
		{
			serialHelper(countAlf, "Alf down");
			rFlagAlf = countAlf.countTo(down);
		}
	}

	if (rFlagBob != nix)
	{
		if (rFlagBob == up)
		{
			serialHelper(countBob, "Bob up");
			rFlagBob = countBob.countTo(up);
		}
		else if (rFlagBob == down)
		{
			serialHelper(countBob, "Bob down");
			rFlagBob = countBob.countTo(down);
		}
	}

	delay(100);
}
