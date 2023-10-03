#ifndef AIRPORTANDGATE_H
#define AIRPORTANDGATE_H
#include <string>
#include <vector>
class Airplane; // forward declaration
#include "Airplane.h"
#include <iostream>


/*
 * Part 1.
 *
 * Create descriptive documentation of the Gate and Airport classes. For each class, provide a summary of the functionality
 * and purpose. This summary should be a MINIMUM of three full sentences. For each constructor and function of the class,
 * using a MINIMUM of two full sentences, describe:
 * 1. Parameter names, types, what the purpose of the parameter is
 * 2. What this function/constructor does. If it only assigns/returns variables, what is the purpose of this variable?
 *    Make sure to clearly explain the functionality and logic of the more complicated sections.
 * 3. What the return type and data is.
 *
 * Write documentation in this file as block comments, like this, ABOVE the class/function/constructor you are describing.
 *
 */

/*
This "Gate" class has 3 public methods (getName, setFlight, and getFlight)  2 private string variables (flight, and gate_name), and a constructor.
The function of this class is to create a gate at an airport. You can name it or retrieve its name, and you can to be able to set or get the
current flights assigned to it. It interacts with airports and airplanes, meaning, airplanes land and take off from assigned gates, and airports have gates.
*/

class Gate {
public:
/*
This is the constructor for the gate class. As an argument, it takes in a const string 
reference as name. The constructor sets the private class variable gate_name to name and there is no return type. 
 */
    Gate(const std::string& name) {
        this->gate_name = name;
    }

/*
This function, getName, takes in no parameters, and is meant to retrieve the name of the gate.
When called, it returns a const string reference "gate_name".
 */
    const std::string& getName() const {
        return this->gate_name;
    }

/*
This function, setFlight, takes a const string reference in as flight_name. Flight_name is then assigned to flight,
the flight assigned to the gate. It returns nothing.
 */
    void setFlight(const std::string& flight_name) {
        this->flight = flight_name;
    }

/*
getFlight will return a const string reference and has no arguments. 
It will return the flights name from the gate it's called on.
 */
    const std::string& getFlight() const {
        return this->flight;
    }

private:
    std::string flight;
    std::string gate_name;
};


/*
Airport is a class meant to represent an airport with planes landing, and taking off, as well as gates with statuses and names.
Airport has a constructor and methods, landAirplane, launchAirplane, gateStatuses, getTotalGates, getFreeGates, and getLocationID.
Airport has 2 private methods called assignGate and removeGate, and 1 private variable, a  string called location_id, and a private 
vector called that holds gates called gates. It interacts with gates and airplanes, meaning there are gates in airports and airplanes 
come and go from airports
 */
class Airport {
public:
/*
Airports constructor takes in a const string ref as location_id, and sets it to the private const class variable called location_id.
It doesn't return anything. This will be the name of the airport.
 */
    Airport(const std::string& location_id) {
        this->location_id = location_id;
    };
/*
landAirplane takes in a reference to an Airplane object, stores it in "ap," and returns a boolean. If there are any free gates 
open, otherwise returning false, then a for loop iterates over all the gates in the vector "gates." 
If any gate in gates has the same flight name/id as the airplane ap, the function returns false. Else, assignGate is called on ap,
ap is assigned to the first open gate whose name is stored in assigned_gate. Then the airplane is marked as landed and the airplane 
is marked as being at that gate, returning true.
 */
    bool landAirplane(Airplane& ap) {
        if (getFreeGates() > 0) {

            for (const Gate& g: this->gates) {
                if (g.getFlight() == ap.getFlightID()) {
                    return false;
                }
            }

            std::string assigned_gate = assignGate(ap);
            ap.setState("landed");
            ap.setGate(assigned_gate);
            return true;
        } else {
            return false;
        }
    }
/*
launchAirplane takes in an airplane object as ap and returns a boolean. If removeGate can successfully clear the flight to go, 
the airplanes state is set to flying, its gate is cleared, and the function returns true. if removeGate can't successfully 
clear it, this function returns false.
 */
    bool launchAirplane(Airplane& ap) {
        if (removeGate(ap)) {
            ap.setState("flying");
            ap.setGate("");
            return true;
        } else {
            return false;
        }
    }
/*
gateStatuses doesn't return anything. It prints out all the gate statuses for the airport, looping through every gate in gates,
printing their name, and flight.
 */
    void gateStatuses() const {
        std::cout << "Gate statuses for airport " << this->location_id << ":\n";
        for (const Gate& g: this->gates) {
            std::cout << "\tGate " << g.getName() << ": " << g.getFlight() << "\n";
        }
    };
/*
getTotalGates returns the total size of the gates vector as an int.
 */
    int getTotalGates() const {
        return gates.size();
    };
/*
getFreeGates returns the number of gates without assigned flights as an int by iterating over the gates vector.
It has an initial value of zero.
 */
    int getFreeGates() const {
        int free_gates = 0;
        for (const Gate& g: this->gates) {
            if (g.getFlight().length() == 0) {
                free_gates += 1;
            }
        }
        return free_gates;
    };
/*
getLocationID returns a string reference to the location_id of the airport
 */
    std::string& getLocationID(){
        return this->location_id;
    }


private:
/*
assignGate takes in an airplane object as ap and iterates over all gates and checks for the first with an unnaissigned flight. 
It assigns the flight by calling set flight on ap's flight id, and returns the name of that gate as a string. if there are no 
gates open, an empty string is returned. 
 */
    std::string assignGate(const Airplane& ap) {
        for (Gate& g: this->gates) {
            if (g.getFlight().length() == 0) {
                g.setFlight(ap.getFlightID());
                return g.getName();
            }
        }
        return "";
    };
/*
removeGate takes an airplane object as ap and iterates over all gates to check for the gate with ap's flight id assigned to it, then clears
that gate's flight assigment with an empty string. A boolean is returned as true if there is an assigned gate that is removed, and false if 
there isn't.
 */
    bool removeGate(const Airplane& ap) {
        for (Gate& g: this->gates) {
            if (g.getFlight() == ap.getFlightID()) {
                g.setFlight("");
                return true;
            }
        }
        return false;
    }

    std::string location_id;
    std::vector<Gate> gates{Gate("a1"), Gate("a2"), Gate("b1")};

};

#endif //AIRPORTANDGATE_H
