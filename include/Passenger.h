#ifndef PASSENGER_H
#define PASSENGER_H

#include <string>

class Passenger {
private:
    std::string id;
    std::string fullName;
    std::string passportNumber;
    std::string nationalCode;
    std::string nationality;
    double wallet;
    bool isDeleted;

public:
    Passenger();  // Constructor
    Passenger(const std::string& id,
              const std::string& name,
              const std::string& passport,
              const std::string& nationalCode,
              const std::string& nationality,
              double wallet,
              bool isDeleted = false);

    // Getters
    std::string getId() const;
    std::string getName() const;
    std::string getPassport() const;
    std::string getNationalCode() const;
    std::string getNationality() const;
    double getWallet() const;
    bool deleted() const;

    // Setters
    void setWallet(double newAmount);
    void setPassport(const std::string& newPassport);
    void setDeleted(bool deleted);

    std::string toCSV() const;

    static Passenger fromCSV(const std::string& line);
};

#endif // PASSENGER_H
