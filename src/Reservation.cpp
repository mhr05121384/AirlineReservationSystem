#include "../include/Reservation.h"
#include <sstream>

Reservation::Reservation()
        : amountPaid(0.0), isCancelled(false) {}

Reservation::Reservation(const std::string& id,
                         const std::string& passengerId,
                         const std::string& flightId,
                         double amountPaid,
                         bool isCancelled)
        : id(id), passengerId(passengerId), flightId(flightId),
          amountPaid(amountPaid), isCancelled(isCancelled) {}

std::string Reservation::getId() const { return id; }
std::string Reservation::getPassengerId() const { return passengerId; }
std::string Reservation::getFlightId() const { return flightId; }
double Reservation::getAmountPaid() const { return amountPaid; }
bool Reservation::cancelled() const { return isCancelled; }

void Reservation::setCancelled(bool cancelled) { isCancelled = cancelled; }
void Reservation::setAmountPaid(double newAmount) { amountPaid = newAmount; }

std::string Reservation::toCSV() const {
    std::ostringstream oss;
    oss << id << ","
        << passengerId << ","
        << flightId << ","
        << amountPaid << ","
        << isCancelled;
    return oss.str();
}

Reservation Reservation::fromCSV(const std::string& line) {
    std::istringstream iss(line);
    std::string token;

    std::string id, passengerId, flightId;
    double paid;
    bool cancelled;

    std::getline(iss, id, ',');
    std::getline(iss, passengerId, ',');
    std::getline(iss, flightId, ',');
    std::getline(iss, token, ','); paid = std::stod(token);
    std::getline(iss, token, ','); cancelled = std::stoi(token);

    return Reservation(id, passengerId, flightId, paid, cancelled);
}
