// Make sure this file has header guards to prevent cyclical dependencies
#ifndef AIRPLANE_H
#define AIRPLANE_H
#include <string>
#include <iostream>
#include <vector>
// #include "AirportAndGate.h"
class Airport; //forward declaration

/*
 * Part 2.
 *
 * The Airplane class interacts with the Airport class to land and takeoff from it. Use information from the
 * AirportAndGate.h file as well as comments from this file to:
 *  1. **Declare** all necessary functions, constructors, destructors, and member variables in this header file (.h file)
 *  2. **Implement** all declared functions, constructors, destructors in the .cc file
 *
 * Remember, member variables should be private and only use setters/getters to access them.
 *
 * Part 3.
 *
 * Use forward declaration of the Airport class to make things easier.
 * Add any additional member variables or functions you need to work with the itinerary vector.
 */

class Airplane {
    public:
        Airplane(std::string id, std::vector<Airport*> it);
        void setState(std::string state);
        void setGate(std::string gate);
        void setCurrent(int num);
        void setPrevious(int num);
        void setReverse(bool a);
        bool getReverse();
        int getCurrentInt();
        std::string getGate();
        std::string getState();
        std::string getFlightID() const;
        std::vector<Airport*> getItinerary();
        Airport* getCurrent();
        Airport* getPrevious();

    private:
        const std::string flightID;
        int current;
        int previous;
        bool reverse;
        std::string state;
        std::string gate;
        std::vector<Airport*> itinerary;
    
    /*
    * The Airplane class is fairly simple, as most logic for the program lies in the Airport class. Here is a list
    * of details the Airplane class must follow:
    *  1. Upon creation of a new object, an alphanumeric flight ID should be stored in the class.
    *  2. Variables representing state, and gate must be private member variables be stored in the class
    *      and must be accessed using setters/getters.
    *  3. The flight ID can only be accessed after instantiation, it cannot be changed.
    *  4. Any dynamically allocated memory must be free'd in the class's destructor.
    */

};

#endif //AIRPLANE_H
