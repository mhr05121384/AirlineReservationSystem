#include "include/AirlineSystem.h"
#include <iostream>

void printMenu() {
    std::cout << "\n✈ Airline Reservation System ✈\n";
    std::cout << "1. Add Passenger\n";
    std::cout << "2. Add Flight\n";
    std::cout << "3. Make Reservation\n";
    std::cout << "4. Search Reservation\n";
    std::cout << "5. Cancel Reservation\n";
    std::cout << "6. List Passengers\n";
    std::cout << "7. List Flights\n";
    std::cout << "8. List Reservations\n";
    std::cout << "0. Exit\n";
    std::cout << "Choose: ";
}

int main() {
    AirlineSystem system;
    int choice;

    do {
        printMenu();
        std::cin >> choice;
        switch (choice) {
            case 1: system.addPassenger(); break;
            case 2: system.addFlight(); break;
            case 3: system.makeReservation(); break;
            case 6: system.listPassengers(); break;
            case 7: system.listFlights(); break;
            case 8: system.listReservations(); break;
            case 0:
                system.shutdown();
                std::cout << "Exiting...\n";
                break;
            default:
                std::cout << "Invalid option.\n";
        }
    } while (choice != 0);

    return 0;
}
