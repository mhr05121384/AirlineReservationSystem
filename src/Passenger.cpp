#include "../include/Passenger.h"
#include <sstream>

Passenger::Passenger() : wallet(0.0), isDeleted(false) {}

Passenger::Passenger(const std::string& id,
                     const std::string& name,
                     const std::string& passport,
                     const std::string& nationalCode,
                     const std::string& nationality,
                     double wallet,
                     bool isDeleted)
        : id(id), fullName(name), passportNumber(passport),
          nationalCode(nationalCode), nationality(nationality),
          wallet(wallet), isDeleted(isDeleted) {}

std::string Passenger::getId() const { return id; }
std::string Passenger::getName() const { return fullName; }
std::string Passenger::getPassport() const { return passportNumber; }
std::string Passenger::getNationalCode() const { return nationalCode; }
std::string Passenger::getNationality() const { return nationality; }
double Passenger::getWallet() const { return wallet; }
bool Passenger::deleted() const { return isDeleted; }

void Passenger::setWallet(double newAmount) { wallet = newAmount; }
void Passenger::setPassport(const std::string& newPassport) { passportNumber = newPassport; }
void Passenger::setDeleted(bool deleted) { isDeleted = deleted; }

std::string Passenger::toCSV() const {
    std::ostringstream oss;
    oss << id << ","
        << fullName << ","
        << passportNumber << ","
        << nationalCode << ","
        << nationality << ","
        << wallet << ","
        << isDeleted;
    return oss.str();
}

Passenger Passenger::fromCSV(const std::string& line) {
    std::istringstream iss(line);
    std::string token;

    std::string id, name, passport, ncode, nationality;
    double wallet;
    bool deleted;

    std::getline(iss, id, ',');
    std::getline(iss, name, ',');
    std::getline(iss, passport, ',');
    std::getline(iss, ncode, ',');
    std::getline(iss, nationality, ',');
    std::getline(iss, token, ','); wallet = std::stod(token);
    std::getline(iss, token, ','); deleted = std::stoi(token);

    return Passenger(id, name, passport, ncode, nationality, wallet, deleted);
}
