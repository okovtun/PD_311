#include<iostream>
using namespace std;

// i'm not sure how realistic these numbers are but pls bear with me i'm not a car person
#define MIN_ENGINE_VOLUME 1.0
#define MAX_ENGINE_VOLUME 6.0
#define MIN_CONSUMPTION_IDLE 0.0001 // liter per second
#define MAX_CONSUMPTION_IDLE 0.0004
#define MAX_CONSUMPTION 0.001


class Engine
{
	const double VOLUME;
	const double CONSUMPTION;
	double consumptionPerSec;
	bool isStarted;

public:
	Engine(double volume, double consumption) :VOLUME
	(
		volume < MIN_ENGINE_VOLUME ? MIN_ENGINE_VOLUME :
		volume > MAX_ENGINE_VOLUME ? MAX_ENGINE_VOLUME :
		volume
	),
		CONSUMPTION
		(
			consumption < MIN_CONSUMPTION_IDLE ? MIN_CONSUMPTION_IDLE :
			consumption > MAX_CONSUMPTION_IDLE ? MAX_CONSUMPTION_IDLE :
			consumption
		)
	{
		consumptionPerSec = 0;
		isStarted = false;
		cout << this << ": engine created\n";
	}

	~Engine()
	{
		cout << this << ": engine destroyed\n";
	}

	void start()
	{
		if (!isStarted)
		{
			isStarted = true;
			consumptionPerSec = CONSUMPTION;
			cout << this << ": engine started\n";
		}
	}

	void stop()
	{
		if (isStarted)
		{
			isStarted = false;
			consumptionPerSec = 0;
			cout << this << ": engine stopped\n";
		}
	}

	bool started() const { return isStarted; }

	void printInfo() const
	{
		cout << "Volume: " << VOLUME << " liters\n";
		cout << "Idle consumption: " << CONSUMPTION << " liters/second\n";
		cout << "Current consumption: " << consumptionPerSec << " liters/second\n";
		cout << "Is started: ";
		if (isStarted) { cout << "Yes\n"; }
		else { cout << "No\n"; }
	}
};

void main()
{
	setlocale(LC_ALL, "");
	Engine testEngine(2.0, 0.0003);
	char choice;

	do
	{
		cout << "Press 1 to start engine\n";
		cout << "Press 2 to stop engine\n";
		cout << "Press 3 to view engine status\n";
		cout << "Press Q to exit\n";
		cin >> choice;

		switch (choice)
		{
		case '1':
			testEngine.start();
			break;
		case '2':
			testEngine.stop();
			break;
		case '3':
			testEngine.printInfo();
		default:
			break;
		}
		if (choice != 'q' && choice != 'Q')
		{
			system("pause");
			system("cls");
		}
	} while (choice != 'q' && choice != 'Q');
}
