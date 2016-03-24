#ifndef BATH_H
#define BATH_H

#include "../Settings.cpp"
#include "sensors/TemperatureSensor.cpp"
#include "sensors/LevelSensor.cpp"
#include "WaterPump.cpp"

class Bath {
private:
    void keepLevel() {
      if (this->level->getPercentageFilled() < Settings::BathMinimumLevel) {
        this->pump->turnOn();
      } else {
        this->pump->turnOff();
      }
    }

	TemperatureSensor* temperatureSensor1;
	TemperatureSensor* temperatureSensor2;

	bool isTemperatureOK() {
		float minTemperature = this->temperature - Settings::TemperatureEpsilon;
		float maxTemperature = this->temperature + Settings::TemperatureEpsilon;
		float currentTemperature = getCurrentTemperature();
		return minTemperature <= currentTemperature
				&& currentTemperature <= maxTemperature;
	}

	bool isLevelOK() {
		int minimumLevel = Settings::BathMinimumLevel - Settings::LevelEpsilon;
		return this->level->getPercentageFilled() > minimumLevel;
	}

protected:
	LevelSensor* level;
	WaterPump* pump;

	float getCurrentTemperature() {
		float sum = this->temperatureSensor1->getTemperature();
		sum += this->temperatureSensor2->getTemperature();
		return sum / 2;
	}

public:
	int temperature = 0;
	int time = 0;

	Bath(int temperatureSensorIndex1, int temperatureSensorIndex2, int levelEchoPin, int levelTriggerPin) {
		this->temperatureSensor1 = new TemperatureSensor(
				temperatureSensorIndex1);
		this->temperatureSensor2 = new TemperatureSensor(
				temperatureSensorIndex2);
		this->level = new LevelSensor(levelEchoPin, levelTriggerPin, Settings::BathDepth);
	}

	void update() {
		keepTemperature();
		keepLevel();
	}

	virtual void keepTemperature() = 0;

	bool isReady() {
		return isTemperatureOK() && isLevelOK();
	}

};

#endif