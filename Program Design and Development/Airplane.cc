#include "Airplane.h"
#include <string>
#include <vector>
#include <iostream>



/*
 * Implement the Airplane class here. Refer to Airplane.h for class details.
 */
Airplane::Airplane(std::string id, std::vector<Airport*> it) : flightID(id), itinerary(it) {
    setState("landed");
    setCurrent(0);
    setReverse(false);
    setCurrent(0);
};

void Airplane::setCurrent(int num) {
    this->current = num;
};
void Airplane::setPrevious(int num){
    this->previous = num;
};

void Airplane::setState(std::string state){
    this->state = state;
};

void Airplane::setGate(std::string gate){
    this->gate = gate;
};

void Airplane::setReverse(bool a) {
    this->reverse = a;
};

bool Airplane::getReverse() {
    return this->reverse;
};

int Airplane::getCurrentInt() {
    return this->current;
};

std::string Airplane::getGate(){
    return this->gate;
};

std::string Airplane::getState(){
    return this->state;
}

std::string Airplane::getFlightID() const{
    return this->flightID;
};

std::vector<Airport*> Airplane::getItinerary() {
    return this->itinerary;
};

Airport* Airplane::getCurrent(){
    return this->itinerary.at(current);
};

Airport* Airplane::getPrevious(){
    return this->itinerary.at(previous);
};
