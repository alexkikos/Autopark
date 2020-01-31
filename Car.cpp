#include "Car.h"

using namespace car;
void Wheels::SetDiskDiametr(double s)
{
	diametr_disk = s;
}

auto Wheels::GetDiametrDisks() const
{
	return diametr_disk;
}

void Wheels::ShowParam() const
{
	Device::ShowParam();
	cout << "\nÄèàìåòð äèñêîâ: " << diametr_disk;
}

void car::Wheels::FillParam()
{
	Device::FillParam();
	cout << "\nÄèàìåòð äèñêà (÷èñëî): ";
	cin >> diametr_disk;
}

void car::Wheels::Load(ifstream& load)
{
	Device::Load(load);
	load.read((char*)& diametr_disk, sizeof(double));
}

void car::Wheels::Save(ofstream& save)
{
	Device::Save(save);
	save.write((char*)& diametr_disk, sizeof(double));
}

Wheels::Wheels(int amount, string color, double length, double width, double diametr_disk) : Device(amount, color, length, width)
{
	this->diametr_disk = diametr_disk;
}

void Transmition::SetType(string s)
{
	type_transmition = s;
}

string Transmition::GetType() const
{
	return type_transmition;
}

void Transmition::SetManufacturer(string s)
{
	manufacturer = s;
}

string Transmition::GetManufacturer() const
{
	return manufacturer;
}

void car::Transmition::FillParam()
{
	Device::FillParam();
	cout << "\nÒèï êîðîáêè ïåðåäà÷(ñòðîêà):";
	cin >> type_transmition;
	cout << "\nÏðîèçâîäèòåëü(ñòðîêà): ";
	cin >> manufacturer;
}

void Transmition::ShowParam() const
{
	Device::ShowParam();
	cout << "\nÒèï êîðîáêè ïåðåäà÷: " << type_transmition;
	cout << "\nÏðîèçâîäèòåëü: " << manufacturer;
}

void car::Transmition::Load(ifstream& load)
{
	Device::Load(load);
	char b[400];
	int n;
	load.read((char*)& n, sizeof(int));
	load.read(b, n);
	type_transmition = b;
	char s[400];
	load.read((char*)& n, sizeof(int));
	load.read(s, n);
	manufacturer = s;
}

void car::Transmition::Save(ofstream& save)
{
	Device::Save(save);
	int n;
	n = type_transmition.length() + 1;
	save.write((char*)&n, sizeof(int));
	save.write(type_transmition.c_str(), n);
	save.write((char*)&n, sizeof(int));
	save.write(manufacturer.c_str(), n);
}

Transmition::Transmition(int amount, string color, double length, double width, string type, string manufacturer) : Device(amount, color, length, width)
{
	type_transmition = type;
	this->manufacturer = manufacturer;
}

void car::Door::FillParam()
{
	Device::FillParam();
}

Door::Door(int amount, string color, double length, double width) :Device(amount, color, length, width)
{
}

void car::Car::Load(ifstream& load)
{
	char s[500], b[500];
	int n;
	load.read((char*)& n, sizeof(int));
	load.read(s, n);
	name_car = s;
	load.read((char*)& n, sizeof(int));
	load.read(b, n);
	color_car = b;
	Wheels::Load(load);
	Door::Load(load);
	Transmition::Load(load);

}



void Car::Save(ofstream& save)
{
	int n = name_car.length() + 1;
	save.write((char*)&n, sizeof(int));
	save.write(name_car.c_str(), n);
	n = color_car.length() + 1;
	save.write((char*)&n, sizeof(int));
	save.write(color_car.c_str(), n);
	Wheels::Save(save);
	Door::Save(save);
	Transmition::Save(save);
}

void Car::SetName(string s)
{
	name_car = s;
}

string Car::GetName() const
{
	return name_car;
}

void Car::SetColor(string s)
{
	color_car = s;
}

string Car::GetColor() const
{
	return color_car;
}

void Car::ShowParam() const
{

	cout << "\nÍàçâàíèå ìàøèíû: " << name_car;
	cout << "\nÖâåò ìàøèíû: " << color_car;
	cout << "\nÊÎÐÎÁÊÀ ÏÅÐÅÄÀ×";
	Transmition::ShowParam();
	cout << "\n=================================================";
	cout << "\nÄÂÅÐÈ";
	Door::ShowParam();
	cout << "\n=================================================";
	cout << "\nÊÎËÅÑÀ";
	Wheels::ShowParam();
	cout << "\n=========================================================================================\n";
}

void car::Car::FillParam()
{
	cout << "\nÂâåäèòå íàçâàíèå ìàøèíû: ";
	cin >> name_car;
	cout << "\nÂâåäèòå öâåò ìàøèíû: ";
	cin >> color_car;
	cout << "\nÈÍÔÎÐÌÀÖÈß Î ÊÎËÅÑÀÕ: ";
	Wheels::FillParam();
	cout << "\nÈÍÔÎÐÌÀÖÈß Î Äâåðÿõ: ";
	Door::FillParam();
	cout << "\nÈÍÔÎÐÌÀÖÈß Î ÊÎÐÎÁÊÅ ÏÅÐÅÄÀ×: ";
	Transmition::FillParam();

}

Car::Car(string name_car, string color_car, int amount_whels, string color_whels, double length_whels, double width_whels, double diametr_disk_whels, int amount_doors, string color_doors, double length_doors, double width_doors, int amount_transm, string color_transm, double length_trans, double width_trans, string type_trans, string manufacturer) : Wheels(amount_whels, color_whels, length_whels, width_whels, diametr_disk_whels), Door(amount_doors, color_doors, length_doors, width_doors), Transmition(amount_transm, color_transm, length_trans, width_trans, type_trans, manufacturer)
{
	this->name_car = name_car;
	this->color_car = color_car;
}

car::Device::Device(int amount, string color, double length, double width)
{
	this->amount = amount;
	this->color = color;
	this->length = length;
	this->width = width;
}



void car::AutoPark::AddCar()
{
	Car* b = new Car;
	b->FillParam();
	my.push_back(b);
	total_cars++;
}

void car::AutoPark::SaveCar()
{
	if (total_cars > 0)
	{
		ofstream save("base.bin", ios::binary);
		if (save.is_open())
		{
			list<Car*> tmp = my;
			save.write((char*)& total_cars, sizeof(int));
			for (int i = 0; i < total_cars; i++)
			{
				tmp.back()->Save(save);
				tmp.pop_back();
			}
		}
		save.close();
	}
}

void car::AutoPark::LoadCar()
{
	ifstream load("base.bin", ios::binary);
	if (load.is_open())
	{
		load.read((char*)& total_cars, sizeof(int));
		if (total_cars > 0)
		{
			for (int i = 0; i < total_cars; i++)
			{
				Car* b = new Car;
				b->Load(load);
				my.push_front(b);
			}
		}
	}
	load.close();
}

void car::AutoPark::ShowCars() const
{
	list<Car*> c;
	c = my;
	int b = c.size();
	for (int i = 0; i < b; i++)
	{
		cout << "\n=========================================" << i + 1 << "================================================";
		c.front()->ShowParam();
		c.pop_front();
	}
}

void car::AutoPark::RemoveCar(int number)
{
	if (number <= my.size())
	{
		list <Car*>::iterator it = my.begin();
		int c = 1;
		while (c != my.size()) { it++; c++; };
		my.remove(*it);
		total_cars--;
	}
	else cout << "\n Wron number";
}

void car::AutoPark::Menu()
{
	char a = ' ';
	int n;
	while (a != '5')
	{
		switch (a)
		{
		case '1': system("cls"); AddCar(); break;
		case '2':
			cout << "\nÂâåäèòå íîìåð ìàøèíû ïî æóðíàëó: ";
			cin >> n;
			RemoveCar(n);
			system("cls");
			break;
		case '3': ShowCars(); break;
		case '4': SaveCar(); break;
		case '5': break;
		default:
			break;
		}
		cout << "1. Add car" << endl;
		cout << "2. Remove car" << endl;
		cout << "3. Show all car" << endl;
		cout << "4. Save" << endl;
		cout << "5. Exit" << endl;
		cin >> a;
	}
}

car::AutoPark::~AutoPark()
{

	SaveCar();
	my.clear();
}

car::AutoPark::AutoPark()
{
	total_cars = 0;
	LoadCar();
}

