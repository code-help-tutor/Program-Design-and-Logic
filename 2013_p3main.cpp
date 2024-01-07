WeChat: cstutorcs
QQ: 749389476
Email: tutorcs@163.com
#include <iostream>
#include <string>
#include <cmath>

using namespace std;

template <class T1, class T2>
class Table{
public:
	Table();
	void set(const T1&x, T2 y);
	T2 *get(const T1&x);
};

class Customer{
public:
	Customer(const string& name): name_(name){
		balance_ = 0;
	}

	double getBalance(){return balance_;}
	void increaseBalance(double value){ balance_ += value;}
	void decreaseBalance(double value){balance_ -= value;}

private:
	string name_;
	double balance_;
};

class Bicycle{
public:
	Bicycle(const string& identifier, const string& make, double price):
	  identifier_(identifier), make_(make), price_(price){
		  serviceTimes_ = 0;
	}

	int getServiceTimes(){return serviceTimes_;}
	void increaseServiceTimes(){++serviceTimes_;}

	double getPrice(){return price_;}

private:
	string identifier_;
	string make_;
	double price_;

	int serviceTimes_;
};

class Shop{
public:
	Shop(){}
	bool sellBicycle(Customer& customer, Bicycle& bicycle){
		if(customer.getBalance() > bicycle.getPrice()){
			customer.decreaseBalance(bicycle.getPrice());
			table_.set(bicycle, customer);
		}else{

		}
	}

	void service(Bicycle & bicycle){
		Customer* customer = table_.get(bicycle);
		if (customer == NULL){
			return;
		}else{
			int times = bicycle.getServiceTimes();
			if (times == 0){
			}else if (times == 1){
				customer->decreaseBalance(20);
			}else if(times == 2){
				customer->decreaseBalance(40);
			}

			bicycle.increaseServiceTimes();
		}
	}

private:
	Table<Bicycle, Customer> table_;
};

int main(){
	Shop shop;

	Customer lance("Lance");
	lance.increaseBalance(2000);

	Bicycle b1("TK15895", "Trek", 475);
	Bicycle b2("SS82300", "Specialized", 1600);

	shop.sellBicycle(lance, b1);
	shop.sellBicycle(lance, b2);

	shop.service(b1);
	shop.service(b2);

	return 0;
}