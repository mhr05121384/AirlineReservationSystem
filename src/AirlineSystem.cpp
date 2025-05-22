#include "../include/AirlineSystem.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <iomanip>

AirlineSystem::AirlineSystem() {
    loadPassengers();
    loadFlights();
    loadReservations();
}

void AirlineSystem::loadPassengers() {
    std::ifstream file(passengerFile);
    if (!file) return;

    std::string line;
    while (std::getline(file, line)) {
        Passenger p = Passenger::fromCSV(line);
        passengers.push_back(p);
    }
}

void AirlineSystem::loadFlights() {
    std::ifstream file(flightFile);
    if (!file) return;

    std::string line;
    while (std::getline(file, line)) {
        Flight f = Flight::fromCSV(line);
        flights.push_back(f);
    }
}

void AirlineSystem::loadReservations() {
    std::ifstream file(reservationFile);
    if (!file) return;

    std::string line;
    while (std::getline(file, line)) {
        Reservation r = Reservation::fromCSV(line);
        reservations.push_back(r);
    }
}

void AirlineSystem::savePassengers() const {
    std::ofstream file(passengerFile);
    for (const auto& p : passengers)
        file << p.toCSV() << "\n";
}

void AirlineSystem::saveFlights() const {
    std::ofstream file(flightFile);
    for (const auto& f : flights)
        file << f.toCSV() << "\n";
}

void AirlineSystem::saveReservations() const {
    std::ofstream file(reservationFile);
    for (const auto& r : reservations)
        file << r.toCSV() << "\n";
}

void AirlineSystem::shutdown() const {
    savePassengers();
    saveFlights();
    saveReservations();

}

std::string AirlineSystem::generateId(const std::string& prefix, int number) const {
    std::ostringstream oss;
    oss << prefix << std::setfill('0') << std::setw(3) << number;
    return oss.str();
}

void AirlineSystem::addPassenger() {
    std::string name, passport, nationalCode, nationality;
    double wallet;

    std::cin.ignore(); // پاک کردن newline باقی‌مانده
    std::cout << "Full Name: ";
    std::getline(std::cin, name);

    std::cout << "Passport Number: ";
    std::getline(std::cin, passport);

    std::cout << "National Code: ";
    std::getline(std::cin, nationalCode);

    std::cout << "Nationality: ";
    std::getline(std::cin, nationality);

    std::cout << "Initial Wallet Balance: ";
    std::cin >> wallet;

    for (const auto& p : passengers) {
        if (p.getPassport() == passport || p.getNationalCode() == nationalCode) {
            std::cout << "Passenger already exists.\n";
            return;
        }
    }

    std::string id = generateId("P", passengers.size() + 1);

    Passenger newPassenger(id, name, passport, nationalCode, nationality, wallet);
    passengers.push_back(newPassenger);

    std::cout << "Passenger registered with ID: " << id << "\n";
}

void AirlineSystem::addFlight() {
    std::string flightNumber, origin, destination, dateTime;
    int seats;
    double price;

    std::cin.ignore();
    std::cout << "Flight Number: ";
    std::getline(std::cin, flightNumber);

    std::cout << "Origin: ";
    std::getline(std::cin, origin);

    std::cout << "Destination: ";
    std::getline(std::cin, destination);

    std::cout << "Date and Time (YYYY-MM-DD HH:MM): ";
    std::getline(std::cin, dateTime);

    std::cout << "Available Seats: ";
    std::cin >> seats;

    std::cout << "Ticket Price: ";
    std::cin >> price;

    std::string id = generateId("F", flights.size() + 1);

    Flight newFlight(id, flightNumber, origin, destination, dateTime, seats, price);
    flights.push_back(newFlight);

    std::cout << "Flight added with ID: " << id << "\n";
}

void AirlineSystem::makeReservation() {
    std::string pid, fid;
    std::cin.ignore();

    std::cout << "Enter Passenger ID: ";
    std::getline(std::cin, pid);
    std::cout << "Enter Flight ID: ";
    std::getline(std::cin, fid);

    auto it_passenger = std::find_if(passengers.begin(), passengers.end(),
                                     [&](const Passenger& p) { return p.getId() == pid && !p.deleted(); });

    if (it_passenger == passengers.end()) {
        std::cout << "❌ PassengerNotFound\n";
        return;
    }

    auto it_flight = std::find_if(flights.begin(), flights.end(),
                                  [&](const Flight& f) { return f.getId() == fid && !f.deleted(); });

    if (it_flight == flights.end()) {
        std::cout << "❌ FlightNotFound\n";
        return;
    }

    if (it_flight->isFull()) {
        std::cout << "❌ FlightFull\n";
        return;
    }
    if (it_flight->isExpired()) {
        std::cout << "❌ FlightExpired\n";
        return;
    }

    if (it_passenger->getWallet() < it_flight->getPrice()) {
        std::cout << "❌ InsufficientBalance\n";
        return;
    }

    std::cout << "\n--- Reservation Preview ---\n";
    std::cout << "Passenger: " << it_passenger->getName() << "\n";
    std::cout << "Flight: " << it_flight->getFlightNumber()
              << " (" << it_flight->getOrigin() << " -> " << it_flight->getDestination() << ")\n";
    std::cout << "Price: " << it_flight->getPrice() << "\n";
    std::cout << "Confirm? (y/n): ";
    char confirm;
    std::cin >> confirm;
    if (confirm != 'y' && confirm != 'Y') return;

    // عملیات رزرو
    it_flight->decreaseSeat();
    double price = it_flight->getPrice();
    it_passenger->setWallet(it_passenger->getWallet() - price);

    std::string rid = generateId("R", reservations.size() + 1);
    Reservation newRes(rid, pid, fid, price);
    reservations.push_back(newRes);

    std::cout << "✅ Reservation completed. ID: " << rid << "\n";
}

void AirlineSystem::listReservations() const {
    std::cout << "\n--- All Reservations ---\n";
    for (const auto& r : reservations) {
        std::cout << "ID: " << r.getId()
                  << " | Passenger: " << r.getPassengerId()
                  << " | Flight: " << r.getFlightId()
                  << " | Paid: " << r.getAmountPaid()
                  << " | Status: " << (r.cancelled() ? "Cancelled" : "Active") << "\n";
    }
}

void AirlineSystem::listFlights() const {
    std::cout << "\n--- All Flights ---\n";
    for (const auto& f : flights) {
        if (f.deleted()) continue;
        std::cout << "ID: " << f.getId()
                  << " | " << f.getFlightNumber()
                  << " | " << f.getOrigin() << " -> " << f.getDestination()
                  << " | " << f.getDateTime()
                  << " | Seats: " << f.getSeatsAvailable()
                  << " | Price: " << f.getPrice()
                  << (f.isExpired() ? " [Expired]" : "") << "\n";
    }
}

void AirlineSystem::listPassengers() const {
    std::cout << "\n--- All Passengers ---\n";
    for (const auto& p : passengers) {
        if (p.deleted()) continue;
        std::cout << "ID: " << p.getId()
                  << " | Name: " << p.getName()
                  << " | Passport: " << p.getPassport()
                  << " | Wallet: " << p.getWallet() << "\n";
    }
}
