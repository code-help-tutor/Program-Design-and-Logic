WeChat: cstutorcs
QQ: 749389476
Email: tutorcs@163.com
#include <iostream>
#include <string>
#include <cmath>

using namespace std;

class RunningEvent;
class ThrowingEvent;
class JumpEvent;

class Event{
public:
	Event(){
		finish = false;
	}
	virtual ~Event() {}

	virtual double point() = 0;
	bool isFinished(){return finish;}
	void finishEvent(double v){value = v; finish = true;}

protected:
	double a, b, c;
	bool finish;
	double value;
};

class ThrowingEvent: public Event{
public:
	enum Type{
		Shotput, Javelin
	};

	virtual ~ThrowingEvent(){}

	ThrowingEvent(Type type): type_(type){
		switch(type_){
		case Shotput:{
			a = 56.02;
			b = 1.5;
			c = 1.05;
			break;
					 }
		case Javelin:{
			a = 15.98;
			b = 3.8;
			c = 1.04;
			break;
					 }
		}
	}

	double point(){
		return a * pow(value - b, c);
	}

private:
	Type type_;
};

class JumpEvent: public Event{
public:
	enum Type{
		HighJump, LongJump
	};
	virtual ~JumpEvent(){}

	JumpEvent(Type type): type_(type){
		switch(type_){
		case HighJump:{
			a = 1.85;
			b = 75;
			c = 1.348;
			break;
					  }
		case LongJump:{
			a = 0.1889;
			b = 210;
			c = 1.41;
			break;
					  }
		}
	}
	double point(){
		return a * pow(value - b, c);
	}

private:
	Type type_;
};

class RunningEvent: public Event{
public:
	enum Type{
		Metre100, Metre200, Metre800
	};
	virtual ~RunningEvent(){}

	RunningEvent(Type type): type_(type){
		switch(type_){
		case Metre100:{
			a = 9.23;
			b = 26.7;
			c = 1.835;
			break;
					  }
		case Metre200:{
			a = 4.99;
			b = 42.5;
			c = 1.81;
			break;
					  }
		case Metre800:{
			a = 0.112;
			b = 254;
			c = 1.88;
			break;
					  }
		}
	}

	double point(){
		return a * pow(b - value, c);
	}

private:
	Type type_;
};


class Competitor{
public:
	Competitor(const string& name, int age): name_(name), age_(age), 
		metre100(RunningEvent::Metre100),
		metre200(RunningEvent::Metre200),
		metre800(RunningEvent::Metre800),
		highJump(JumpEvent::HighJump),
		longJump(JumpEvent::LongJump),
		shotPut(ThrowingEvent::Shotput),
		javelinThrow(ThrowingEvent::Javelin){
	}

	void finishMetre100(double value){
		metre100.finishEvent(value);
	}

	void finishMetre200(double value){
		metre200.finishEvent(value);
	}

	void finishMetre800(double value){
		metre800.finishEvent(value);
	}

	void finishHighJump(double value){
		highJump.finishEvent(value);
	}

	void finishLongJump(double value){
		longJump.finishEvent(value);
	}

	void finishShotPut(double value){
		shotPut.finishEvent(value);
	}

	void finishJavelinThrow(double value){
		javelinThrow.finishEvent(value);
	}

	double currentPoint(){
		double point = .0;
		if (metre100.isFinished()){
			point += metre100.point();
		}
		if (metre200.isFinished()){
			point += metre200.point();
		}
		if (metre800.isFinished()){
			point += metre800.point();
		}
		if (highJump.isFinished()){
			point += highJump.point();
		}
		if (longJump.isFinished()){
			point += longJump.point();
		}
		if(shotPut.isFinished()){
			point += shotPut.point();
		}
		if (javelinThrow.isFinished()){
			point += javelinThrow.point();
		}
		return point;
	}

private:
	string name_;
	int age_;

	RunningEvent metre100;
	RunningEvent metre200;
	RunningEvent metre800;

	JumpEvent highJump;
	JumpEvent longJump;

	ThrowingEvent shotPut;
	ThrowingEvent javelinThrow;
};

int main(){
	Competitor jessica("Jessica Ennis", 28);
	jessica.finishMetre100(12.54);
	jessica.finishHighJump(186);
	jessica.finishShotPut(14.28);
	jessica.finishMetre200(22.88);
	cout << jessica.currentPoint() << endl;

	jessica.finishLongJump(648);
	jessica.finishJavelinThrow(47.49);
	jessica.finishMetre800(128.65);
	cout << jessica.currentPoint() << endl;

	return 0;
}
