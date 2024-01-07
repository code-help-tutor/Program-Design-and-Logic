WeChat: cstutorcs
QQ: 749389476
Email: tutorcs@163.com
#include <iostream>
#include <string>
#include <cmath>

using namespace std;

template <class T>
class vector{
public:
	vector();
	void push_back(const T& item);
	void pop_back();
	int size();
	T& operator[];
};

class Component{
public:
	Component(double price, const string& make): price_(price), make_(make){}
	virtual ~Component(){}

	double price(){return price_;}
	virtual double performance();

protected:
	double price_;
	string make_;
};

class Ram: public Component{
public:
	Ram(double price, const string& make, double size):
	  Component(price, make), size_(size){}

	virtual double performance(){
		return size_ * 8 + price_ * 0.1;
	}

private:
	double size_;
};

class IODevice: public Component{
public:
	IODevice(double price, const string& make, double responseTime):
		Component(price, make), responseTime_(responseTime){}

	virtual double performance(){
		return price_ * 0.2 + (50 / responseTime_);
	}

private:
	double responseTime_;
};

class Laptop{
public:
	Laptop(double baseCost): baseCost_(baseCost){}
	double performance(){
		double perform = .0;
		for (int i = 0 ; i < components.size(); ++i){
			perform += components[i]->performance();
		}

		return perform;
	}

	void addComponent(Component * compenent){
		components.push_back(compenent);
	}

	double price(){
		double total = .0;
		for (int i = 0 ; i < components.size(); ++i){
			total += components[i]->price();
		}
		total += baseCost_;

		return total;
	}

private:
	double baseCost_;
	vector<Component*> components;
};

class Employee{
public:
	Employee(const string& name): name_(name){
		laptop_ = NULL;
	}

	void addComponent(Component * compenent){
		laptop_->addComponent(compenent);
	}

	bool order(Laptop* laptop){
		if (laptop->price() <= 850){
			laptop_ = laptop;
			return true;
		}else{
			return false;
		}
	}

	double obtainPerformance(){
		if (laptop_ == NULL){
			return -1;
		}else{
			return laptop_->performance();
		}
	}

private:
	string name_;
	Laptop* laptop_;
};

int main(){
	Employee andrew("Andrew");

	Laptop laptop(500);
	Ram ram1(90, "Crucial", 8);
	Ram ram2(90, "Crucial", 8);
	IODevice io1(150, "Samsung", 5.5);
	laptop.addComponent(&ram1);
	laptop.addComponent(&ram2);
	laptop.addComponent(&io1);

	andrew.order(&laptop);
	cout << andrew.obtainPerformance() << endl;

	Ram ram3(50, "Corsair", 4);
	andrew.addComponent(&ram3);

	cout << andrew.obtainPerformance() << endl;

	return 0;
}