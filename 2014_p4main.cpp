WeChat: cstutorcs
QQ: 749389476
Email: tutorcs@163.com
#include <iostream>
#include <string>
#include <cmath>

using namespace std;

class Engine{
public:
	enum EngineType{
		TurboCharge2000, SupermanV3
	};

public:
	Engine(EngineType type, double mass, double powerFactor, int numberOfCylinder):
	type_(type), mass_(mass), powerFactor_(powerFactor), numberOfCylinder_(numberOfCylinder){
	}

	double Mass(){return mass_;}
	double PowerFactor(){return powerFactor_;}
	int NumberOfCylinder(){return numberOfCylinder_;}
	EngineType getEngineType(){return type_;}

private:
	double mass_;
	double powerFactor_;
	int numberOfCylinder_;
	EngineType type_;
};

class Chassis{
public:
	Chassis(double mass): mass_(mass){}

	double Mass(){return mass_;}

private:
	double mass_;
};

class Driver{
public:
	Driver(double mass, string name): mass_(mass), name_(name){}
	double Mass(){return mass_;}
	string Name(){return name_;}

private:
	double mass_;
	string name_;
};

class RacingCar{
public:
	RacingCar(const Driver& driver, const Chassis& chassis, const Engine& engine, const string& name):
	driver_(driver), chassis_(chassis), engine_(engine), modelName_(name){
	}

	void RestrictMass(double minimum){
		mass_ = chassis_.Mass() + engine_.Mass() + driver_.Mass();
		if (mass_ < minimum){
			mass_ = minimum;
		}
	}

	double Time(double D){
		double M = mass_;
		double P = engine_.PowerFactor();
		int C = engine_.NumberOfCylinder();

		switch(engine_.getEngineType()){
		case Engine::SupermanV3:{
			return (M * D * (1 - log(1 + exp(-D))))/(P * C * C);
								}
		case Engine::TurboCharge2000:{
			return sqrt((2 * M * D)/(P * C));
									 }
		default:{
			return 0;
				}
		}
	}

	double Mass(){return mass_;}

private:
	Driver driver_;
	Chassis chassis_;
	Engine engine_;
	string modelName_;

	double mass_;
};

int main(){
	double minimumBefore = 642;
	Driver hamilton(67, "Lewis Hamilton");
	RacingCar racingCar_NR14(hamilton, Chassis(582), 
		Engine(Engine::TurboCharge2000, 91, 250, 5), "NR-14");
	racingCar_NR14.RestrictMass(minimumBefore);

	RacingCar racingCar_TFD2(hamilton, Chassis(411),
		Engine(Engine::SupermanV3, 87, 175, 4), "TFD-2");
	racingCar_TFD2.RestrictMass(minimumBefore);

	cout << racingCar_NR14.Time(1000) << endl;
	cout << racingCar_TFD2.Time(1500) << endl;
	cout << endl;

	double minimumAfter = 550;
	racingCar_NR14.RestrictMass(minimumAfter);
	racingCar_TFD2.RestrictMass(minimumAfter);
	cout << racingCar_NR14.Time(1000) << endl;
	cout << racingCar_TFD2.Time(1500) << endl;

	return 0;
}