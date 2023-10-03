#include <iostream>
#include <vector>
#include "Airplane.h"
#include "AirportAndGate.h"

/*
 * Part 1.
 *
 * See AirportAndGate.h
 *
 * Part 2.
 * See Airplane.h. Use this file to test functionality.
 *
 * Part 3.
 * Add functionality to the main code below to let Airplanes follow an itinerary of Airports that they
 * should land at. Airplanes will start at the first airport in their itinerary, then land and takeoff at each
 * Airport in their itinerary until they land at their last destination. Then, the Airplane will follow the itinerary
 * in REVERSE order until it reaches its original starting Airport.
 *
 * You will create a new vector called "itinerary" that will contain pointers to Airport objects. This vector
 * represents the Airports the Airplane will fly to, in order. The Airplane class will contain this new "itinerary" vector.
 * The vector should be created and populated in this main file, then passed into the Airplane class via its constructor.
 *
 * In this file, you will add a loop that will run until every plane has returned to its first Airport. In this loop,
 * each plane will try to land at the next Airport in its itinerary. Also in this loop, "cout" which Airport each
 * Airplane is currently at. It may be helpful to add additional variables to the Airplane class to keep track of the
 * current and previous Airport the Airplane has been at, as well as which direction you are iterating through the
 * vector. Make sure to use setters/getters to access class member variables. All member variables should be private.
 * Use the landPlane and launchPlane functions in this main.cc file to make Airplanes interact with Airports.
 *
 * The Airplanes, Airports, and itineraries are shown below. The itineraries are for the forward trip only:
 *
 * flightID AC1111: MSP -> YYZ
 * flightID AC2222: YYZ -> YQB -> MSP
 * flightID AC3333: YYZ -> YQB -> MSP
 * flightID JB1111: BOS -> TPA -> MSP
 * flightID JB2222: MSP -> BOS
 * flightID JB3333: BOS -> MSP
 *
 *
 */

int main() {

    // ===================== BEGIN Part 2 testing code =====================
    // Airport msp("MSP");

    // Airplane a1("a1-123");
    // Airplane a2("a2-123");
    // Airplane a3("a3-123");

    // msp.gateStatuses();
    // msp.landAirplane(a1);
    // msp.landAirplane(a2);
    // msp.gateStatuses();
    // msp.landAirplane(a1); // <- Cannot land the same flightID twice, only 1 copy of the flightID will show up in gateStatuses
    // msp.landAirplane(a3);
    // msp.gateStatuses();
    // msp.launchAirplane(a1);
    // msp.gateStatuses();
    // ===================== END Part 2 testing code =====================
    
    /*
     * Implement part 3 code below. You may choose to work off of the provided example/notes below
     *
     * msp = Airport("MSP");
     * Airport yyz("YYZ");
     * ...
     * ...
     *
     * std::vector<Airport*> it1{&msp, &yyz};
     * ...
     * ...
     *
     * Airplane ac1("AC1111", it1);
     * ...
     * ...
     *
     * Add airplanes to a vector
     *
     * While all planes are not at their original airport:
     *      for each airplane in the airplanes vector:
     *          if the airplane has landed at desired airport:
     *              launch the airplane from the previous airport
     *              increment itinerary index by 1
     *              ...
     *              ...
     *          cout the flight ID and current airport of the airplane
     */
    Airport msp("MSP");                                                 //making the airports
    Airport yyz("YYZ");
    Airport yqb("YQB");
    Airport bos("BOS");
    Airport tpa("TPA");

    std::vector<Airport*> it1{&msp, &yyz};                              //making the itineraries
    std::vector<Airport*> it2{&yyz, &yqb, &msp};
    std::vector<Airport*> it3{&yyz, &yqb, &msp};
    std::vector<Airport*> it4{&bos, &tpa, &msp};
    std::vector<Airport*> it5{&msp, &bos};
    std::vector<Airport*> it6{&bos, &msp};
    Airplane a1("AC1111", it1);                                         //making the airplanes and giving them their itineraries
    Airplane a2("AC2222", it2);
    Airplane a3("AC3333", it3);
    Airplane j1("JB1111", it4);
    Airplane j2("JB2222", it5);
    Airplane j3("JB3333", it6);  
    
    msp.landAirplane(a1);                                               //landing the airplanes at their initial airports
    yyz.landAirplane(a2);
    yyz.landAirplane(a3);
    bos.landAirplane(j1);
    msp.landAirplane(j2);
    bos.landAirplane(j3);

    std::vector<Airplane*> airplanes{&a1, &a2, &a3, &j1, &j2, &j3};     //creating a vector to hold all plane objects so i can iterate through it
    std::cout << "Round 0 of Flights:" << std::endl;                    //printing out all initial flight locations/ids
    for (Airplane* a: airplanes) {
        std::cout << a->getFlightID() << ": " << a->getCurrent()->getLocationID() << std::endl;
    }

    std::cout << std::endl;

    bool orig_state = false;                                            
    int round = 1;
    while (!orig_state) {                                               //orig_state is false until finished_count equals the amount of planes, meaning the planes have returned and the while loop can finish
        std::cout << "Round " << round << " of Flights:" << std::endl;  //printing and incrementing the round number to track it easier

        for (Airplane* a: airplanes) {                                  //iterates through the list of planes, 
            int current = a->getCurrentInt();

            if (current == int(a->getItinerary().size()-1)) {           //sets reverse to true if the plane has gone through its whole list already and needs to turn around
                    a->setReverse(true);
            }
            bool reverse = a->getReverse(); 

            if (!reverse && current != int(a->getItinerary().size())-1 && a->getItinerary().at(current+1)->landAirplane(*a)) {  //forwards logic
                a->setCurrent(current+1);
                a->setPrevious(current);
                a->getPrevious()->launchAirplane(*a);
            } 
            
            if (reverse && current !=0 && a->getItinerary().at(current-1)->landAirplane(*a)) {  //backwards logic
                a->setCurrent(current-1);
                a->setPrevious(current);
                a->getPrevious()->launchAirplane(*a);
            }

            std::cout << a->getFlightID() << ": " << a->getCurrent()->getLocationID() << std::endl; //printing id and location
        }

        int finished_count = 0;
        for (Airplane* a: airplanes) {
            int current = a->getCurrentInt();                           //increments finished_count for each plane that is done
            bool reverse = a->getReverse();                             
            if (reverse && (current == 0)){
                finished_count = finished_count + 1;
            }
        }

        if (finished_count == int(airplanes.size())) {                  //sets orig_state to true when everything is done
            orig_state = true;
        }
        round++;
        std::cout << std::endl;
    }

    return 0;
};
