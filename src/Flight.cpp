#include "../include/Flight.h"
#include <sstream>
#include <iomanip>
#include <chrono>

Flight::Flight()
        : seatsAvailable(0), price(0.0), isDeleted(false) {}

Flight::Flight(const std::string& id,
               const std::string& flightNumber,
               const std::string& origin,
               const std::string& destination,
               const std::string& dateTime,
               int seatsAvailable,
               double price,
               bool isDeleted)
        : id(id), flightNumber(flightNumber), origin(origin), destination(destination),
          dateTime(dateTime), seatsAvailable(seatsAvailable), price(price), isDeleted(isDeleted) {}

std::string Flight::getId() const { return id; }
std::string Flight::getFlightNumber() const { return flightNumber; }
std::string Flight::getOrigin() const { return origin; }
std::string Flight::getDestination() const { return destination; }
std::string Flight::getDateTime() const { return dateTime; }
int Flight::getSeatsAvailable() const { return seatsAvailable; }
double Flight::getPrice() const { return price; }
bool Flight::deleted() const { return isDeleted; }

void Flight::setDeleted(bool deleted) { isDeleted = deleted; }
void Flight::decreaseSeat() { if (seatsAvailable > 0) seatsAvailable--; }

bool Flight::isFull() const {
    return seatsAvailable <= 0;
}

bool Flight::isExpired() const {
    std::tm flightTime{};
    std::istringstream ss(dateTime);
    ss >> std::get_time(&flightTime, "%Y-%m-%d %H:%M");
    if (ss.fail()) return false;

    std::time_t flightEpoch = std::mktime(&flightTime);
    std::time_t now = std::time(nullptr);
    return flightEpoch < now;
}

std::string Flight::toCSV() const {
    std::ostringstream oss;
    oss << id << ","
        << flightNumber << ","
        << origin << ","
        << destination << ","
        << dateTime << ","
        << seatsAvailable << ","
        << price << ","
        << isDeleted;
    return oss.str();
}

Flight Flight::fromCSV(const std::string& line) {
    std::istringstream iss(line);
    std::string token;

    std::string id, flightNumber, origin, dest, dateTime;
    int seats;
    double price;
    bool deleted;

    std::getline(iss, id, ',');
    std::getline(iss, flightNumber, ',');
    std::getline(iss, origin, ',');
    std::getline(iss, dest, ',');
    std::getline(iss, dateTime, ',');
    std::getline(iss, token, ','); seats = std::stoi(token);
    std::getline(iss, token, ','); price = std::stod(token);
    std::getline(iss, token, ','); deleted = std::stoi(token);

    return Flight(id, flightNumber, origin, dest, dateTime, seats, price, deleted);
}
