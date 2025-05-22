#ifndef RESERVATION_H
#define RESERVATION_H

#include <string>

class Reservation {
private:
    std::string id;
    std::string passengerId;
    std::string flightId;
    double amountPaid;
    bool isCancelled;

public:
    Reservation();
    Reservation(const std::string& id,
                const std::string& passengerId,
                const std::string& flightId,
                double amountPaid,
                bool isCancelled = false);

    // Getters
    std::string getId() const;
    std::string getPassengerId() const;
    std::string getFlightId() const;
    double getAmountPaid() const;
    bool cancelled() const;

    // Setters
    void setCancelled(bool cancelled);
    void setAmountPaid(double newAmount);

    // CSV conversion
    std::string toCSV() const;
    static Reservation fromCSV(const std::string& line);
};

#endif // RESERVATION_H
