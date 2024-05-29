#include<Windows.h>
#include<iostream>
#include<conio.h>
#include<thread>
using namespace std;
using std::cin;
using std::cout;
using std::endl;

#define Escape	27
#define Enter	13

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

#define MIN_ENGINE_CONSUMPTION 3
#define MAX_ENGINE_CONSUMPTION 30

class Engine
{
	const double CONSUMPTION;
	double consumption_per_second;
	bool is_started;
public:
	double get_CONSUMPTION()const
	{
		return CONSUMPTION;
	}
	double get_consumption_per_second()const
	{
		return consumption_per_second;
	}
	void start()
	{
		//if (!is_started)
		is_started = true;
	}
	void stop()
	{
		is_started = false;
	}
	bool started()
	{
		return is_started;
	}

	void set_consumption_per_second()
	{
		consumption_per_second = CONSUMPTION * 3e-5;
	}

	//				Constructor
	Engine(int consumption) :CONSUMPTION
	(
		consumption < MIN_ENGINE_CONSUMPTION ? MIN_ENGINE_CONSUMPTION :
		consumption > MAX_ENGINE_CONSUMPTION ? MAX_ENGINE_CONSUMPTION :
		consumption
	)
	{
		//this->CONSUMPTION = consumption;
		set_consumption_per_second();
		is_started = false;
		cout << "Engine is ready: " << this << endl;
	}
	~Engine()
	{
		cout << "Engine is over: " << this << endl;
	}

	void info()const
	{
		cout << "Consumption:\n";
		cout << CONSUMPTION << " liters/100km\n";
		cout << consumption_per_second << " liters/second\n";
	}
};

#define MAX_SPEED_LOW_LIMIT		120
#define MAX_SPEED_HIGH_LIMIT	400

class Car
{
	Engine engine;
	Tank tank;
	int speed;
	const int MAX_SPEED;
	bool driver_inside;
	struct
	{
		//Эта структура группирует потоки
		std::thread panel_thread;
	}control_threads;
public:
	Car(int max_speed, double consumption, int volume) :engine(consumption), tank(volume),
		MAX_SPEED
		(
			max_speed < MAX_SPEED_LOW_LIMIT ? MAX_SPEED_LOW_LIMIT :
			max_speed > MAX_SPEED_HIGH_LIMIT ? MAX_SPEED_HIGH_LIMIT :
			max_speed
		)
	{
		speed = 0;
		driver_inside = false;
		cout << "Your car is ready " << this << endl;
		cout << "Press Enter to get in : " << endl;
	}
	~Car()
	{
		cout << "Car is over " << this << endl;
	}

	void control()
	{
		char key;
		do
		{
			key = _getch();
			switch (key)
			{
			case Enter: driver_inside ? get_out() : get_in(); break;
			case Escape:
				get_out();
			}
		} while (key != Escape);
	}

	void get_in()
	{
		driver_inside = true;
		//panel();
		//Для того что бы запустить в потоке метод, конструктору потока нужно передать
		//указатель на этот метод (&Class::method),
		//поскольку метод может быть вызван только для какого-то объекта,
		//конструктор потока в обязательном порядке принимает указатель на объект,
		//для которого мы хотим вызвать этот метод.
		control_threads.panel_thread = std::thread(&Car::panel, this);
	}
	void get_out()
	{
		driver_inside = false;
		//Потоки обязательно нужно синхронизировать с родительским потоком при завершении,
		//для синхронизации используется метод join(), но предварительно нужно проверить,
		//можно ли синхронизировать этот поток при помощи метода joinable().
		//Поток можно синхронизировать только если он запущен.
		if (control_threads.panel_thread.joinable())control_threads.panel_thread.join();
		system("CLS");
		cout << "Вы вышли из машины" << endl;
	}
	void panel()
	{
		while (driver_inside)
		{
			system("CLS");
			cout << "Speed: " << speed << " km/h\n";
			cout << "Engine is " << (engine.started() ? "started " : "stopped ") << endl;
			cout << "Fuel level: " << tank.get_fuel_level() << " liters" << endl;
			cout << "Consiumption: " << engine.get_consumption_per_second() << " liters/second";
			Sleep(200);
		}
	}

	void info()const
	{
		engine.info();
		tank.info();
		cout << "Max speed: " << MAX_SPEED << " km/h\n";
	}
};

//#define TANK_CHECK
//define - ОПРЕДЕЛИТЬ
//Директива #define создает макроопределение (макрос)
//Директива - это указание компилятору на выполнение некоторых действий
//#define ENGINE_CHECK

void main()
{
	setlocale(LC_ALL, "");

#if defined TANK_CHECK
	Tank tank(3000);
	int fuel;
	do
	{
		tank.info();
		cout << "Введите объем топлива: "; cin >> fuel;
		tank.fill(fuel);
	} while (fuel);
#endif

#ifdef ENGINE_CHECK
	Engine engine(10);
	engine.info();
#endif // ENGINE_CHECK

	cout << "Car check" << endl;

	Car bmw(250, 10, 80);
	//bmw.info();

	bmw.control();
}