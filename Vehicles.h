#ifndef Vehicles_h
#define Vehicles_h
#include <iostream>

class Vehicles
{
public:
	Vehicles();
	~Vehicles();

	std::string GetCode() {
		return code;
	}

	int GetScaleOne() {
		return scaleOne;
	}

	int GetScaleTwo() {
		return scaleTwo;
	}

	int GetScaleThree() {
		return scaleThree;
	}

	int GetScaleFour() {
		return scaleFour;
	}

	int GetScaleTotal() {
		return total;
	}


	void SetCode(std::string value) {
		code = value;
	}

	void SetScaleOne(int value) {
		scaleOne = value;
	}

	void SetScaleTwo(int value) {
		 scaleTwo = value;
	}

	void SetScaleThree(int value) {
		scaleThree = value;
	}

	void SetScaleFour(int value) {
		scaleFour = value;
	}

	void SetScaleTotal(int value) {
		total = value;
	}
private:
	std::string code = "";
	int scaleOne = 0;
	int scaleTwo = 0;
	int scaleThree = 0;
	int scaleFour = 0;
	int total = 0;
};



#endif
