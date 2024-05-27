#include<iostream>
using namespace std;

#define MIN_TANK_VOLUME 20	//SMART for two
#define MAX_TANK_VOLUME	150	//Dodge RAM

class Tank
{
	const int VOLUME;	//Объем бака является его характеристикой
	double fuel_level;	//Уровень топлива отображает состояние бака
public:
	int get_VOLUME()const
	{
		return VOLUME;
	}
	double get_fuel_level()const
	{
		return fuel_level;
	}
	void fill(double amount)
	{
		if (amount < 0)return;
		fuel_level += amount;
		if (fuel_level > VOLUME)fuel_level = VOLUME;
	}
	double give_fuel(double amount)
	{
		fuel_level -= amount;
		if (fuel_level < 0)fuel_level = 0;
		return fuel_level;
	}
	Tank(int volume) :
		VOLUME
		(
			volume < MIN_TANK_VOLUME ? MIN_TANK_VOLUME :
			volume > MAX_TANK_VOLUME ? MAX_TANK_VOLUME :
			volume
		)
	{
		//l-value = r-value;
		//VOLUME = volume;
		fuel_level = 0;
		cout << "Tank is ready " << this << endl;
	}
	~Tank()
	{
		cout << "Tank is over " << this << endl;
	}
	void info()const
	{
		cout << "Volume:   " << VOLUME << " liters;\n";
		cout << "Fuel leve:" << get_fuel_level() << " liters;\n";
	}
};

void main()
{
	setlocale(LC_ALL, "");

	Tank tank(3000);
	int fuel;
	do
	{
		tank.info();
		cout << "Введите объем топлива: "; cin >> fuel;
		tank.fill(fuel);
	} while (fuel);
}