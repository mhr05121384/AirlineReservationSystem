#ifndef FLIGHT_H
#define FLIGHT_H

#include <string>
#include <ctime>

class Flight {
private:
    std::string id;
    std::string flightNumber;
    std::string origin;
    std::string destination;
    std::string dateTime; // YYYY-MM-DD HH:MM
    int seatsAvailable;
    double price;
    bool isDeleted;

public:
    Flight();
    Flight(const std::string& id,
           const std::string& flightNumber,
           const std::string& origin,
           const std::string& destination,
           const std::string& dateTime,
           int seatsAvailable,
           double price,
           bool isDeleted = false);

    // Getters
    std::string getId() const;
    std::string getFlightNumber() const;
    std::string getOrigin() const;
    std::string getDestination() const;
    std::string getDateTime() const;
    int getSeatsAvailable() const;
    double getPrice() const;
    bool deleted() const;

    // Setters
    void setDeleted(bool deleted);
    void decreaseSeat();

    // Check
    bool isFull() const;
    bool isExpired() const;

    // CSV conversion
    std::string toCSV() const;
    static Flight fromCSV(const std::string& line);
};

#endif // FLIGHT_H
