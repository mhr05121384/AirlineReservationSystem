#ifndef AIRLINESYSTEM_H
#define AIRLINESYSTEM_H

#include "Passenger.h"
#include "Flight.h"
#include "Reservation.h"
#include <vector>
#include <string>

class AirlineSystem {
private:
    std::vector<Passenger> passengers;
    std::vector<Flight> flights;
    std::vector<Reservation> reservations;

    const std::string passengerFile = "data/passengers.csv";
    const std::string flightFile = "data/flights.csv";
    const std::string reservationFile = "data/reservations.csv";

    void loadPassengers();
    void loadFlights();
    void loadReservations();

    void savePassengers() const;
    void saveFlights() const;
    void saveReservations() const;
    // Utility
    std::string generateId(const std::string& prefix, int number) const;

public:
    AirlineSystem();

    // مدیریت
    void addPassenger();
    void addFlight();
    void makeReservation();

    void cancelReservation();
    void searchReservation();

    void listPassengers() const;
    void listFlights() const;
    void listReservations() const;

    void shutdown() const;
};

#endif // AIRLINESYSTEM_H
