#ifndef SETTINGS_H
#define SETTINGS_H

#include "Arduino.h"

class Settings {
public:
	/**
	 * Bath.
	 */
	const static int BathMinimumLevel = 80;
	const static int BathDepth = 23;
	const static int LevelEpsilon = 1;
	const static int TemperatureEpsilon = 1;
	const static int OneWireTemperatureSensor = A11;

	/**
	 * Hot Bath.
	 */
	const static int HotBathLevelEchoPin = A15;
	const static int HotBathLevelTriggerPin = A14;
	const static int HotBathHeaterPin = A7;
	const static int HotBathWaterPump = A5;
	const static int HotBathCirculationWaterPump = A4;

	// indices for one wire



	static byte HotBathTemperatureSensor1[8];
	static byte HotBathTemperatureSensor2[8];
	// for security only
	static byte HotBathTemperatureSensor3[8];


	/**
	 * ColdBath.
	 */
	const static int ColdBathLevelEchoPin = A13;
	const static int ColdBathLevelTriggerPin = A12;
	const static int ColdBathCoolerPin = A0;
	const static int ColdBathWaterPump = A2;

	// indices for one wire
	static byte ColdBathTemperatureSensor1[8];
	static byte ColdBathTemperatureSensor2[8];

	static byte ColdBathTemperatureSensorAntifriz[8];



	/**
	 * Translator
	 */
	const static int TranslatorPowerPin = A6;
	const static int TranslatorPulsePin = A1;
	const static int TranslatorToColdDirection = A3;

	/**
	 * Logger.
	 */
	const static int SDSelectChip = 53;
	constexpr static char* LogFile = "debug2.log";
	const static bool LogToFile = true;
	const static bool LogToSerial = true;

};


#endif
