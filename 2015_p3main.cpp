WeChat: cstutorcs
QQ: 749389476
Email: tutorcs@163.com
#include <iostream>
#include <string>
#include <cmath>

using namespace std;

template <class T>
class List{
public:
	void append(const T& item);
	void remove(const T& item);
	int size();
	T* front();
	T* next();
};

class Property;

class MotionDetector{
public:
	MotionDetector(const string& location): location_(location){
		property_ = NULL;
	}

	void setProperty(Property* property);

	void alarm();

private:
	string location_;
	Property* property_;
};

class SecurityGuard{
public:
	SecurityGuard(const string& name): name_(name){}

	void setProperty(Property* property);

	void receiveTask(const string& msg){
		cout << "Handle " << msg << endl;
	}

private:
	string name_;
	Property* property_;
};

class Property{
public:
	Property(const string& name): name_(name){}

	void addMotionDetector(MotionDetector& item){
		detectorLists_.append(item);
		item.setProperty(this);
	}

	void removeMotionDetector(MotionDetector& item){
		detectorLists_.remove(item);
	}

	void addSecurityGuard(SecurityGuard& item){
		guardLists_.append(item);
	}

	void removeSecurityGuard(SecurityGuard& item){
		guardLists_.remove(item);
	}

	void notify(const string& msg){
		guardLists_.front();
		SecurityGuard* guard = guardLists_.next();
		while(guard != NULL){
			guard->receiveTask(msg);
			guard = guardLists_.next();
		}
	}

private:
	string name_;
	List<MotionDetector> detectorLists_;
	List<SecurityGuard> guardLists_;
};

void MotionDetector::setProperty( Property* property ){
	if(property_ != NULL){
		property_->removeMotionDetector(*this);
	}
	property_ = property;
}

void SecurityGuard::setProperty( Property* property ){
	if(property_ != NULL){
		property_->removeSecurityGuard(*this);
	}
	property_ = property;
}

void MotionDetector::alarm(){
	property_->notify(location_);
}

int main(){
	Property property1("Kensington Palace");
	MotionDetector detector1("Hallway East");
	MotionDetector detector2("Hallway West");
	MotionDetector detector3("Crown Jewels Display Case");
	property1.addMotionDetector(detector1);
	property1.addMotionDetector(detector2);
	property1.addMotionDetector(detector3);

	Property property2("Imperial College");
	MotionDetector detector4("Rector's Office");
	property2.addMotionDetector(detector4);

	SecurityGuard alice("Alice");
	SecurityGuard bob("Bob");
	property2.addSecurityGuard(alice);
	property2.addSecurityGuard(bob);

	detector1.alarm();

	property1.addSecurityGuard(alice);
	detector3.alarm();

	return 0;
}

