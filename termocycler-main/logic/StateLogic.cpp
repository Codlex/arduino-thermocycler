#include "StateLogic.h"
#include "Thermocycler.h"

StateLogic::StateLogic(Thermocycler* thermocycler) {
	this->thermocycler = thermocycler;
}


void StateLogic::changeState(State state) {
	this->currentState = state;
	switch (state) {
	case State::HotBath:
		this->hotBathImmersionCount++;
		break;
	case State::ColdBath:
		this->coldBathImmersionCount++;
		break;
	// do nothing for the rest
	}
}

long StateLogic::toMillis(int seconds) {
	return seconds * 1000;
}

void StateLogic::processNotReady() {
	bool hotBathReady = this->thermocycler->hotBath->isReady();
	bool coldBathReady = this->thermocycler->coldBath->isReady();
	if (hotBathReady && coldBathReady) {
		changeState(State::HotBath);
	}
}


long StateLogic::getTargetImmersionTime() {
	// ASSERT state in (ColdBath, HotBath)
	if (this->currentState == State::ColdBath) {
		return toMillis(this->thermocycler->coldBath->time);
	} else { // this->currentState == HotBath
		return toMillis(this->thermocycler->hotBath->time);
	}
}

void StateLogic::doCycle() {
	if (this->currentState == State::ColdBath) {
		changeState(State::HotBath);
	} else {
		changeState(State::ColdBath);
	}
}

bool StateLogic::isLastCycle() {
	int targetCycles = this->thermocycler->cycles;
	bool hotFinished = this->hotBathImmersionCount == targetCycles;
	bool coldFinished = this->coldBathImmersionCount == targetCycles;
	return hotFinished && coldFinished;
}

void StateLogic::processCycling() {
	// ASSERT state in (ColdBath, HotBath)
	long currentImmersionTime = this->time - this->immersionStart;

	if (currentImmersionTime > getTargetImmersionTime()) {
		if (!isLastCycle()) {
			// reset start time
			this->immersionStart = this->time;

			// invert state
			doCycle();
		} else {
			changeState(State::Finished);
		}

	}
}


State StateLogic::getCurrentState() {
	return this->currentState;
}

void StateLogic::update(long delta) {
	this->time += delta;

	switch (this->currentState) {
	case State::NotReady:
		processNotReady();
		break;
	case State::HotBath:
		processCycling();
		break;
	case State::ColdBath:
		processCycling();
		break;

	}
}