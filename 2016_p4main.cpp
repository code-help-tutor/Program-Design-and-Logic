WeChat: cstutorcs
QQ: 749389476
Email: tutorcs@163.com
#include <iostream>
#include <string>
#include <cmath>

using namespace std;

template <typename T>
class stack{
public:
	stack();
	void push(const T& item);
	T & top();
	void pop();
	int size();
};

class AF{
public:
	AF(string applicantName, int yearOfBirth, double moduleMarkOfOperatingSystem):
	  applicantName_(applicantName), yearOfBirth_(yearOfBirth), moduleMarkOfOperatingSystem_(moduleMarkOfOperatingSystem){}
	virtual ~AF(){}
	virtual double score();


protected:
	string applicantName_;
	int yearOfBirth_;
	double moduleMarkOfOperatingSystem_;
};

class NAF: public AF{
public:
	NAF(string applicantName, int yearOfBirth, double moduleMarkOfOperatingSystem, double moduleMarkOfComputerNetwork):
	  AF(applicantName, yearOfBirth, moduleMarkOfOperatingSystem), moduleMarkOfComputerNetwork_(moduleMarkOfComputerNetwork){}

	double score(){
		return (moduleMarkOfOperatingSystem_ + moduleMarkOfComputerNetwork_) / 2;
	}
private:
	double moduleMarkOfComputerNetwork_;
};

class PAF: public AF{
public:
	PAF(string applicantName, int yearOfBirth, double moduleMarkOfOperatingSystem, double moduleMarkOfProgramming):
	  AF(applicantName, yearOfBirth, moduleMarkOfOperatingSystem), moduleMarkOfProgramming_(moduleMarkOfProgramming){}

	  double score(){
		  return (moduleMarkOfOperatingSystem_ + moduleMarkOfProgramming_) / 2;
	  }
private:
	double moduleMarkOfProgramming_;
};

class HR{
public:
	HR(string name, int yearOfBirth, int maximumSize):
	name_(name), yearOfBirth_(yearOfBirth), maximumSize_(maximumSize){
		letterTray = new stack<AF*>;
	}

	~HR(){
		if (letterTray != NULL){
			delete letterTray;
			letterTray = NULL;
		}
	}

	void check(){
		stack<AF*> * tmpTray = new stack<AF*>;
		int size = letterTray->size();
		int i = 0;
		for (int i = 0; i < size; ++i){
			AF* af = letterTray->top();
			if (af->score() >= 66){
				tmpTray->push(af);
			}
			letterTray->pop();
		}
		delete letterTray;
		letterTray = tmpTray;
	}

	void receiveAF(AF* af){
		if (letterTray->size() < maximumSize_){
			letterTray->push(af);
		}
	}

	int countTray(){
		return letterTray->size();
	}

private:
	string name_;
	int yearOfBirth_;
	stack<AF*> * letterTray;
	int maximumSize_;
};

int main(){
	HR helen("Helen", 1975, 50);

	NAF naf1("Peter", 1986, 65, 75);
	PAF paf1("Susan", 1989, 70, 60);
	NAF naf2("Susan", 1989, 70, 80);

	helen.receiveAF(&naf1);
	helen.receiveAF(&paf1);
	helen.receiveAF(&naf2);


	cout << helen.countTray() << endl;

	system("pause");
	return 0;
}