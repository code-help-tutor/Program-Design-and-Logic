WeChat: cstutorcs
QQ: 749389476
Email: tutorcs@163.com
#include <iostream>
#include <string>
#include <cmath>

using namespace std;

template <typename T> class list {
public:
	list(); //constructor that creates an empty list
	void push_back(const T& item); //adds item to the end
	int size(); //returns the number of items
	//members that return a static iterator to the
	//beginning or the end of the list:
	list<T>::const_iterator begin();
	list<T>::const_iterator end();
};

class Nut{
public:
	Nut(double weight): weight_(weight){}
	virtual ~Nut(){}

	double getEnergy(){
		return calcEnergy(getFat(), getNonFat());
	}
	virtual double getFat();
	virtual double getNonFat();
	double getWeight(){return weight_;}
	
protected:
	double calcEnergy(double fat, double non_fat){
		return 9 * fat + 4 * non_fat;
	}

protected:
	double weight_;
};

class Walnut: public Nut{
public:
	Walnut(double weight): Nut(weight){}
	~Walnut(){}

	double getFat(){
		return weight_ * 0.6521;
	}

	double getNonFat(){
		return weight_ - getFat();
	}
};

class Almond: public Nut{
public:
	Almond(double weight): Nut(weight){}
	~Almond(){}

	double getFat(){
		return weight_ * 0.5064;
	}

	double getNonFat(){
		return weight_ - getFat();
	}
};

class Bag{
public:
	Bag(int limitedNumber): limitedNumber_(limitedNumber){}
	void addNut(Nut* nut){list_.push_back(nut);}

	void stickLabel(){
		double totalEnergy = getTotalEnergy();
		double totalFat = getTotalFat();

		label_ = "Total of " + to_string(totalEnergy) + " kcal";
		label_ += "(" + to_string(totalFat) + " g fat)";
		if (totalFat > 20){
			label_ += "[high in fat]";
		}
	}

private:
	double getTotalEnergy(){
		double result = .0;
		list<Nut*>::const_iterator iter = list_.begin();
		while(iter != list_.end()){
			result += iter->getEnergy();
			++iter;
		}

		return result;
	}

	double getTotalFat(){
		double result = .0;
		list<Nut*>::const_iterator iter = list_.begin();
		while(iter != list_.end()){
			result += iter->getFat();
			++iter;
		}

		return result;
	}

private:
	int limitedNumber_;
	string label_;
	list<Nut*> list_;
};

int main(){
	Bag bag(5);
	Walnut nut1(8);
	Walnut nut2(13);
	Almond nut3(1.5);

	bag.addNut(&nut1);
	bag.addNut(&nut3);
	bag.stickLabel();

	bag.addNut(&nut2);
	bag.stickLabel();


	return 0;
}