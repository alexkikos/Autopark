#pragma once
#include <iostream>
#include <list>
#include <iterator>
#include <fstream>
using namespace std;

namespace car
{
	class Device //
	{
	protected:
		int amount;
		string color;
		double length;
		double width;

	public:
		void SetAmount(int n)
		{
			amount = n;
		}
		int GetAmount() const
		{
			return amount;
		}
		void SetLength(double s)
		{
			length = s;
		}
		auto GetLength()
		{
			return length;
		}
		void SetWidth(double s)
		{
			width = s;
		}
		auto GetWidth()const
		{
			return width;
		}

		virtual void Save(ofstream& save)
		{
			save.write((char*)& amount, sizeof(int));
			int n = color.length() + 1;
			save.write((char*)&n, sizeof(int));
			save.write(color.c_str(), n);
			save.write((char*)& length, sizeof(double));
			save.write((char*)& width, sizeof(double));
		}

		virtual void Load(ifstream& load)
		{
			load.read((char*)& amount, sizeof(int));
			int n;
			load.read((char*)& n, sizeof(int));
			char buff[300];
			load.read(buff, n);
			color = buff;
			load.read((char*)& length, sizeof(double));
			load.read((char*)& width, sizeof(double));
		}
		virtual void ShowParam() const
		{
			cout << "\nКоличество: " << amount;
			cout << "\nЦвет: " << color;
			cout << "\nДлина: " << length;
			cout << "\nШирина: " << width;
		}

		virtual void FillParam()
		{
			cout << "\nКоличество(число): ";
			cin >> amount;
			cout << "\nЦвет(строка): ";
			cin >> color;
			cout << "\nДлина(число): ";
			cin >> length;
			cout << "\nШирина(число): ";
			cin >> width;
		}
	
		Device(int amount = 1, string color = "1", double length = 1, double width = 1);
		virtual ~Device() = default;
	};



	class Door : public Device
	{

	public:
		virtual void OpenDoor(int number)
		{
			if (number <= amount) cout << "\n Door is open";
		}

		virtual void CloseDoor(int number)
		{
			if (number <= amount) cout << "\nDoor is closed";
		}
		virtual void FillParam() override;

		Door(int amount = 4, string color = "black", double length = 1, double width = 1);
	};


	class Wheels : public Device
	{

	protected:
		double diametr_disk;

	public:
		void SetDiskDiametr(double s);
		auto GetDiametrDisks() const;
		void ShowParam() const override;
		virtual void FillParam() override;
		virtual void Load(ifstream& load) override;
		virtual void Save(ofstream& save) override;
		Wheels(int amount = 4, string color = "black", double length = 1, double width = 1, double diametr_disk = 0);
	};




	class Transmition : public Device
	{
	protected:
		string type_transmition;
		string manufacturer;


	public:
		void SetType(string s);
		string GetType() const;

		void SetManufacturer(string s);
		string GetManufacturer() const;

		virtual void FillParam() override;
		void ShowParam() const override;
		virtual void Load(ifstream& load) override;
		virtual void Save(ofstream& save) override;


		Transmition(int amount = 1, string color = "black", double length = 1, double width = 1, string type = "no", string manufacturer = "no");
	};


	class  Car : virtual public Wheels, virtual public Door, virtual public Transmition
	{
	protected:
		string name_car;
		string color_car;
	public:
		virtual void Load(ifstream& load) override;
		virtual void Save(ofstream& save) override;
		void SetName(string s);
		string GetName() const;
		void SetColor(string s);
		string GetColor() const;
		void ShowParam() const override;
		virtual void FillParam() override;
		explicit Car(string name_car = " ", string color_car = " ", int amount_whels = 1, string color_whels = " ", double length_whels = 1, double width_whels = 1, double diametr_disk_whels = 1, int amount_doors = 1, string color_doors = " ", double length_doors = 1, double width_doors = 1, int amount_transm = 1, string color_transm = " ", double length_trans = 1, double width_trans = 1, string type_trans = " ", string manufacturer = " ");
		virtual ~Car() = default;
	};





	class AutoPark final : public Car
	{
		list<Car*> my;
		int total_cars;
		void AddCar();
		void SaveCar();
		void LoadCar();
		void ShowCars() const;
		void RemoveCar(int number);


	public:
		void Menu();
		~AutoPark();
		AutoPark();
	};

}