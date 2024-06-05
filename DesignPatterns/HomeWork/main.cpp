#include<windows.h>
#include<iostream>

using namespace std;

//#define MIN_SIZE		50
//#define MAX_SIZE		800
//#define MIN_LINE_WIDTH	1
//#define MAX_LINE_WIDTH	25
//
//#define MAX_HORIZONTAL_RESOLUTION	800
//#define MAX_VERTICAL_RESOLUTION		600



namespace MyGeometry
{
	enum Color
	{
		RED = 0x000000FF,
		GREEN = 0x0000FF00,
		BLUE = 0x00FF0000,
		GREY = 0x00AAAAAA,
		YELLOW = 0x0000FFFF
	};
	class Shape
	{
	protected:
		static const int MIN_SIZE = 50;
		static const int MAX_SIZE = 800;
		static const int MIN_LINE_WIDTH = 1;
		static const int MAX_LINE_WIDTH = 25;
		static const int MAX_HORIZONTAL_RESOLUTION = 800;
		static const int MAX_VERTICAL_RESOLUTION = 600;

		unsigned int x;
		unsigned int y;
		unsigned int line_width;
		Color color;
	public:

		unsigned int get_x()const {
			return x;
		}
		unsigned int get_y()const {
			return y;
		}
		unsigned int get_line_width()const {
			return line_width;
		}
		unsigned int set_size(unsigned int size) {
			return
				size < MIN_SIZE ? MIN_SIZE :
				size > MAX_SIZE ? MAX_SIZE :
				size;
		}
		void set_x(unsigned int x) {
			this->x = x < MAX_HORIZONTAL_RESOLUTION ? x : MAX_HORIZONTAL_RESOLUTION;
		}
		void set_y(unsigned int y) {
			this->y = y < MAX_VERTICAL_RESOLUTION ? y : MAX_VERTICAL_RESOLUTION;
		}
		void set_line_width(unsigned int line_width) {
			if (line_width < MIN_LINE_WIDTH)line_width = MIN_LINE_WIDTH;
			if (line_width > MAX_LINE_WIDTH)line_width = MAX_LINE_WIDTH;
			this->line_width = line_width;
		}

		//				Constructors:
		Shape(unsigned int x, unsigned int y, unsigned int line_width = 5, Color color = Color::GREY) :color(color) {
			set_x(x);
			set_y(y);
			set_line_width(line_width);
		}
		virtual ~Shape() {}

		//				Methods:
		virtual double get_area()const = 0;
		virtual double get_perimeter()const = 0;
		virtual void draw()const = 0;

		virtual void info()const {
			cout << "Площадь фигуры: " << get_area() << endl;
			cout << "Периметр фигуры: " << get_perimeter() << endl;
			draw();
		}
	};

	class Rectangle :public Shape
	{
		double width;
		double height;
	public:
		double get_width()const {
			return width;
		}
		double get_height()const {
			return height;
		}
		void set_width(double width) {
			this->width = set_size(width);
		}
		void set_height(double height) {
			this->height = set_size(height);
		}

		//				Constructors:
		Rectangle(double width, double height, unsigned int x, unsigned int y, unsigned int line_width, Color color) :
			Shape(x, y, line_width, color)
		{
			set_width(width);
			set_height(height);
		}
		~Rectangle() {}

		//				Methods:
		double get_area()const override {
			return width * height;
		}
		double get_perimeter()const override {
			return (width + height) * 2;
		}

		void draw()const override {


			HWND hwnd = GetConsoleWindow();

			HDC hdc = GetDC(hwnd);


			HPEN hPen = CreatePen(PS_SOLID, line_width, color);	//Карандаш рисует контур фигуры
			HBRUSH hBrush = CreateSolidBrush(color);	//Кисть заливает фигуру

			SelectObject(hdc, hPen);
			SelectObject(hdc, hBrush);

			::Rectangle(hdc, x, y, x + width, y + height);



			DeleteObject(hPen);
			DeleteObject(hBrush);

			ReleaseDC(hwnd, hdc);


		}
		void info()const override {
			cout << typeid(*this).name() << endl;
			cout << "Ширина: " << width << endl;
			cout << "Высота: " << height << endl;
			Shape::info();
		}
	};



	class Square : public Shape
	{

		double size;


	public:

		double get_size()const {
			return size;
		}

		void set_size_for_Square(double size) {
			this->size = set_size(size);
		}

		//Constructpor
		Square(double size, unsigned int x, unsigned int y, unsigned int line_width, Color color) :Shape(x, y, line_width, color) {
			set_size_for_Square(size);
		}
		~Square() {}

		//metods


		double get_area()const override {
			return size * size;
		}
		double get_perimeter()const override {
			return size * 4;
		}
		void  draw()const override {

			for (int i = 0; i < size; i++)
			{
				for (int j = 0; j < size; j++)
				{
					cout << "*";
				}
				cout << endl;
			}




		}
		void info()const override {
			cout << typeid(*this).name() << endl;

			cout << "размер: " << size << "x" << size << endl;
			Shape::info();
		}

	};

	class Triangle :public Shape {

		double hypotenuse;
		double Leg1, Leg2;
	public:

		double get_hypotenuse()const {

			return hypotenuse;
		}
		double get_leg1()const {
			return Leg1;
		}

		double get_leg2()const {

			return Leg2;
		}



	};
}





void main() {
	setlocale(LC_ALL, "");

	MyGeometry::Rectangle rect(100, 50, 100, 200, 8, MyGeometry::Color::RED);
	rect.info(); cout << endl;


	MyGeometry::Square square(100, 100, 200, 8, MyGeometry::Color::GREEN);
	/*square.info();*/
}