#include <iostream>
#include <fstream>
#include <string>
#include <limits>

using namespace std;

bool rooms[11] = {false};

class Hotel {
protected:
    string name[11];
    string phone[11];
    int days[11];
    int bill[11];
    int roomType[11];

public:
    virtual void calculateBill(int r) = 0;
};

class RoomBooking : public Hotel {
public:
    void bookRoom() {
        int r;

        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        cout << "Enter Customer Name: ";
        getline(cin, nameTemp);

        cout << "Enter Phone Number: ";
        cin >> phoneTemp;

        cout << "Enter Room Number (1-10): ";
        cin >> r;

        if (r < 1 || r > 10 || rooms[r]) {
            cout << "Room not available!\n";
            return;
        }

        cout << "\nSelect Room Type:\n";
        cout << "1. Non-AC  (Rs.1000/day)\n";
        cout << "2. AC      (Rs.1500/day)\n";
        cout << "3. Deluxe  (Rs.2500/day)\n";
        cout << "Enter choice: ";
        cin >> roomType[r];

        if (roomType[r] < 1 || roomType[r] > 3) {
            cout << "Invalid room type!\n";
            return;
        }

        cout << "Enter Number of Days: ";
        cin >> days[r];

        if (days[r] <= 0) {
            cout << "Minimum stay is 1 day!\n";
            return;
        }

        name[r] = nameTemp;
        phone[r] = phoneTemp;

        calculateBill(r);
        rooms[r] = true;

        ofstream file("hotel.txt", ios::app);
        file << "----------------------------\n";
        file << "Customer Name : " << name[r] << endl;
        file << "Phone Number  : " << phone[r] << endl;
        file << "Room Number   : " << r << endl;
        file << "Room Type     : "
             << (roomType[r] == 1 ? "Non-AC" :
                 roomType[r] == 2 ? "AC" : "Deluxe") << endl;
        file << "Days Stayed   : " << days[r] << endl;
        file << "Total Bill    : Rs." << bill[r] << endl;
        file << "----------------------------\n\n";
        file.close();

        cout << "Room booked successfully!\n";
    }

    void calculateBill(int r) override {
        int rate;

        if (roomType[r] == 1)
            rate = 1000;
        else if (roomType[r] == 2)
            rate = 1500;
        else
            rate = 2500;

        bill[r] = days[r] * rate;
    }

    void showBill() {
        int r;
        cout << "Enter Room Number: ";
        cin >> r;

        if (r < 1 || r > 10 || !rooms[r]) {
            cout << "No booking found!\n";
            return;
        }

        cout << "\n--- BILL DETAILS ---\n";
        cout << "Customer Name : " << name[r] << endl;
        cout << "Phone Number  : " << phone[r] << endl;
        cout << "Room Number   : " << r << endl;
        cout << "Room Type     : "
             << (roomType[r] == 1 ? "Non-AC" :
                 roomType[r] == 2 ? "AC" : "Deluxe") << endl;
        cout << "Days Stayed   : " << days[r] << endl;
        cout << "Total Bill    : Rs." << bill[r] << endl;
    }

    void cancelBooking() {
        int r;
        cout << "Enter Room Number to Cancel: ";
        cin >> r;

        if (r < 1 || r > 10 || !rooms[r]) {
            cout << "No active booking!\n";
            return;
        }

        rooms[r] = false;
        name[r] = "";
        phone[r] = "";
        days[r] = 0;
        bill[r] = 0;
        roomType[r] = 0;

        cout << "Booking cancelled successfully.\n";
    }

    void showAvailableRooms() {
        cout << "Available Rooms: ";
        for (int i = 1; i <= 10; i++) {
            if (!rooms[i])
                cout << i << " ";
        }
        cout << endl;
    }

private:
    string nameTemp, phoneTemp;
};

int main() {
    RoomBooking hotel;
    int choice;

    // SIMPLE LOGIN
    string username, password;
    int attempts = 3;

    while (attempts--) {
        cout << "Username: ";
        cin >> username;
        cout << "Password: ";
        cin >> password;

        if (username == "admin" && password == "1234") {
            cout << "Login successful!\n";
            break;
        } else {
            cout << "Wrong credentials. Attempts left: " << attempts << endl;
        }

        if (attempts == 0) {
            cout << "Too many failed attempts. Exiting...\n";
            return 0;
        }
    }

    do {
        cout << "\n--- NAMASTE! Welcome to TAJ Hotel ---\n";
        cout << "1. Book Room\n";
        cout << "2. Show Bill\n";
        cout << "3. Cancel Booking\n";
        cout << "4. Show Available Rooms\n";
        cout << "5. Exit\n";
        cout << "Enter choice: ";

        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Enter numbers only!\n";
            continue;
        }

        switch (choice) {
            case 1: hotel.bookRoom(); break;
            case 2: hotel.showBill(); break;
            case 3: hotel.cancelBooking(); break;
            case 4: hotel.showAvailableRooms(); break;
            case 5: cout << "Thank you! Visit again.\n"; break;
            default: cout << "Invalid choice!\n";
        }

    } while (choice != 5);

    return 0;
}