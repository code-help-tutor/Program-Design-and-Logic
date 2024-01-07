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

class Position{
public:
	Position(double x, double y): x_(x), y_(y){
	}

	double X(){
		return x_;
	}

	double Y(){
		return y_;
	}
private:
	double x_;
	double y_;

};

class Message{
public:
	Message(double radius, const string& text): radius_(radius), text_(text){
	}

	double radius() const{
		return radius_;
	}

	const string& getText() const{
		return text_;
	}

private:
	double radius_;
	string text_;
};

class Users{
public:
	Users(const Position& pos, int messageCredit): cPos_(pos), messageCredit_(messageCredit){
	}

	void acceptMessage(const Message& msg){

	}

	Message generate(double radius, const string& text){
		Message msg(radius, text);
		return msg;
	}

	bool broadcast(const Message& msg, List<Users>& userList){
		userList.front();
		Users* cUser = userList.next();
		int personNumber = 0;
		while(cUser != NULL){
			if (cUser == this){
			}else{
				double distance = sqrt(pow(cPos_.X() - cUser->cPos_.X(), 2) + pow(cPos_.Y() - cUser->cPos_.Y(), 2));
				if(distance < msg.radius()){
					++personNumber;
				}
			}
			cUser = userList.next();
		}
		if (personNumber <= messageCredit_){
			userList.front();
			cUser = userList.next();
			while(cUser != NULL){
				if (cUser == this){
				}else{
					send(cUser, msg);
				}
				cUser = userList.next();
			}

			messageCredit_ -= personNumber;
			return true;
		}else{
			return false;
		}
	}

	void buyCredit(int credit){
		messageCredit_ += credit;
	}

	void move(const Position& pos){
		cPos_ = pos;
	}

	int getMessageCredit(){
		return messageCredit_;
	}

private:
	void send(Users* user, const Message& msg){
		user->acceptMessage(msg);
	}

private:
	Position cPos_; // current position p
	int messageCredit_;
};

int main(){
	List<Users> userList;
	Users alice(Position(3.5, 0.5), 5);
	Users bob(Position(10, 5), 0);
	Users charles(Position(7, 7), 2);

	userList.append(alice);
	userList.append(bob);
	userList.append(charles);

	Message aliceMsg = alice.generate(10, "Hello!");
	alice.broadcast(aliceMsg, userList);
	alice.move(Position(3,3));
	cout << "The number of message credits Alice has is " << alice.getMessageCredit() << endl;

	Message charlesMsg = charles.generate(5, "Come to my party at the Royal Albert Hall");
	charles.broadcast(charlesMsg, userList);

	bob.buyCredit(10);

	return 0;
}