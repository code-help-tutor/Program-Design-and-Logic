WeChat: cstutorcs
QQ: 749389476
Email: tutorcs@163.com
#include <iostream>
#include <string>
#include <cmath>

using namespace std;

class Point{
public:
	Point(double x, double y): x_(x), y_(y){}

	double x(){return x_;}
	double y(){return y_;}

	double getDistance(const Point& p){
		return sqrt(pow(x_ - p.x_ , 2) + pow(y_ - p.y_ , 2));
	}

private:
	double x_;
	double y_;
};

class Player{
public:
	Player(const Point& pos, double skillFactor):
	  currentPosition_(pos), skillFactor_(skillFactor){}

	void takeBall(){ hasBall_ = true;}

	void move(const Point& pos){
		currentPosition_ = pos;
	}

	void passBall(Player* player){
		player->takeBall();
		hasBall_ = false;
	}

	bool isOutsideThreePointLine(){
		double distance = currentPosition_.getDistance(Point(7.5, 1.575));
		if (distance < 6.6){
			return false;
		}else{
			return true;
		}
	}

	void shoot(){
		double a = 0.62;
		double b = 6.84;
		Point p3(7.5, 1.575);
		double x = currentPosition_.getDistance(p3);
		double s = skillFactor_;

		double probability = 1 - 1/(1 + exp(-a * ( x - b * s)));
		double rate = drand48();
		if (rate > probability){
			if(isOutsideThreePointLine()){
				cout << "Successful shots taken outside the three point line and earn 3 points" << endl;
			}else{
				cout << "Successful shots taken inside the three point line and earn 2 points" << endl;
			}
		}else{
			cout << "Failed shots, earn 0 points" << endl;
		}
	}

private:
	Point currentPosition_;
	double skillFactor_;
	bool hasBall_;
};

int main(){
	Player larry(Point(4.5, 3.5), 0.9);
	Player michael(Point(10.5, 5.1), 0.95);

	michael.takeBall();
	larry.move(Point(0.25, 2.2));
	michael.passBall(&larry);
	larry.shoot();

	return 0;
}