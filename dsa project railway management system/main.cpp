#include <iostream>
#include <string>
#include <cstdlib>
#include <limits>
using namespace std;
// Total number of seats in the train
const int TOTAL_SEATS = 30;
// Structure to store passenger details
struct Passenger
{
    int seatNumber;
    string name;
    int age;
    char gender;

    Passenger* next;
};
// Pointer to the first passenger in the linked list
Passenger* head = nullptr;
// Array pointer to track seat availability
int* seats = nullptr;
// Function to clear invalid input
void clearInput()
{
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}
// Function to initialize the seat array
void initializeSeats()
{
    // Allocate memory dynamically using malloc
    seats = (int*)malloc(TOTAL_SEATS * sizeof(int));

    if (seats == nullptr)
    {
        cout << "Memory allocation failed!" << endl;
        exit(1);
    }
 // Initially, all seats are available
    for (int i = 0; i < TOTAL_SEATS; i++)
    {
        seats[i] = 0;
    }
}
// Function to find the first available seat
int findAvailableSeat()
{
    for (int i = 0; i < TOTAL_SEATS; i++)
    {
        if (seats[i] == 0)
        {
            return i + 1;
        }
    }

    return -1;
}
// Function to book a ticket
void bookTicket()
{
    // Find an available seat
    int seatNumber = findAvailableSeat();

    if (seatNumber == -1)
    {
        cout << "\nSorry! No seats are available." << endl;
        return;
    }

    string name;
    int age;
    char gender;

    cout << "\nEnter Passenger Name: ";
    getline(cin >> ws, name);

    if (name.empty())
    {
        cout << "Name cannot be empty." << endl;
        return;
    }

    cout << "Enter Age: ";

    if (!(cin >> age))
    {
        cout << "Invalid age input." << endl;
        clearInput();
        return;
    }

    if (age <= 0 || age > 120)
    {
        cout << "Please enter a valid age between 1 and 120." << endl;
        return;
    }

    cout << "Enter Gender (M/F/O): ";
    cin >> gender;

    if (gender == 'm')
        gender = 'M';
    else if (gender == 'f')
        gender = 'F';
    else if (gender == 'o')
        gender = 'O';

    if (gender != 'M' && gender != 'F' && gender != 'O')
    {
        cout << "Invalid gender. Please enter M, F, or O." << endl;
        return;
    }
// Create a new passenger node
    Passenger* newPassenger = new Passenger;
 // Store passenger information
    newPassenger->seatNumber = seatNumber;
    newPassenger->name = name;
    newPassenger->age = age;
    newPassenger->gender = gender;
    newPassenger->next = nullptr;
// Insert the new passenger at the end of the linked list
    if (head == nullptr)
    {
        head = newPassenger;
    }
    else
    {
        Passenger* temp = head;

        while (temp->next != nullptr)
        {
            temp = temp->next;
        }

        temp->next = newPassenger;
    }
 // Mark the seat as booked
    seats[seatNumber - 1] = 1;

    cout << "\nTicket booked successfully!" << endl;
    cout << "Seat Number: " << seatNumber << endl;
    cout << "Passenger Name: " << name << endl;
}
// Function to cancel a ticket
void cancelTicket()
{
    int seatNumber;

    cout << "\nEnter Seat Number to Cancel: ";

    if (!(cin >> seatNumber))
    {
        cout << "Invalid seat number." << endl;
        clearInput();
        return;
    }
// Check whether the seat number is valid
    if (seatNumber < 1 || seatNumber > TOTAL_SEATS)
    {
        cout << "Invalid seat number! Please enter 1 to "
             << TOTAL_SEATS << "." << endl;
        return;
    }
// Check whether the seat is booked
    if (seats[seatNumber - 1] == 0)
    {
        cout << "This seat is already available." << endl;
        return;
    }

    Passenger* temp = head;
    Passenger* previous = nullptr;

    // Search for the passenger with the given seat number
    while (temp != nullptr &&
           temp->seatNumber != seatNumber)
    {
        previous = temp;
        temp = temp->next;
    }
// If the passenger was not found
    if (temp == nullptr)
    {
        cout << "Passenger record not found." << endl;
        return;
    }
// Remove the passenger node from the linked list
    if (previous == nullptr)
    {
 // The first node is being removed
        head = temp->next;
    }
    else
    {
        // Remove a node from the middle or end
        previous->next = temp->next;
    }
// Free the memory used by the passenger node
    delete temp;
 // Mark the seat as available
    seats[seatNumber - 1] = 0;

    cout << "Ticket cancelled successfully!" << endl;
    cout << "Seat Number " << seatNumber
         << " is now available." << endl;
}


// Function to display train seat status
void viewTrainStatus()
{
    cout << "\n========== TRAIN STATUS ==========" << endl;

    for (int i = 0; i < TOTAL_SEATS; i++)
    {
        cout << "Seat " << i + 1 << ": ";

        if (seats[i] == 0)
        {
            cout << "Available";
        }
        else
        {
            cout << "Booked";
        }

        cout << endl;
    }

    cout << "==================================" << endl;
}


// Function to display all passenger details
void viewPassengerList()
{
    if (head == nullptr)
    {
        cout << "\nNo passengers have booked tickets yet." << endl;
        return;
    }

    Passenger* temp = head;

    cout << "\n========== PASSENGER LIST ==========" << endl;

    while (temp != nullptr)
    {
        cout << "Seat No: " << temp->seatNumber
             << " | Name: " << temp->name
             << " | Age: " << temp->age
             << " | Gender: " << temp->gender
             << endl;

        temp = temp->next;
    }

    cout << "====================================" << endl;
}


// Function to free all passenger nodes
void freePassengerList()
{
    Passenger* temp = head;

    while (temp != nullptr)
    {
        Passenger* nextPassenger = temp->next;

        delete temp;

        temp = nextPassenger;
    }

    head = nullptr;
}


// Function to release all dynamically allocated memory
void cleanup()
{
    // Free all linked-list nodes
    freePassengerList();

    // Release the dynamically allocated seat array
    free(seats);

    seats = nullptr;

    cout << "\nAll allocated memory has been released." << endl;
    cout << "Thank you for using the Railway Reservation System!"
         << endl;
}


// Main function
int main()
{
    // Initialize the seat array
    initializeSeats();
    int choice;
    do
    {
        cout << "\n";
        cout << "====================================" << endl;
        cout << "     RAILWAY RESERVATION SYSTEM     " << endl;
        cout << "====================================" << endl;

        cout << "1. Book Ticket" << endl;
        cout << "2. Cancel Ticket" << endl;
        cout << "3. View Train Status" << endl;
        cout << "4. View Passenger List" << endl;
        cout << "5. Exit" << endl;

        cout << "Enter your choice: ";

        if (!(cin >> choice))
        {
            cout << "Invalid input! Please enter a number." << endl;
            clearInput();
            continue;
        }

        switch (choice)
        {
            case 1:
                bookTicket();
                break;

            case 2:
                cancelTicket();
                break;

            case 3:
                viewTrainStatus();
                break;

            case 4:
                viewPassengerList();
                break;

            case 5:
                cleanup();
                break;

            default:
                cout << "Invalid choice! Please select 1 to 5."
                     << endl;
        }

    } while (choice != 5);

    return 0;
}
