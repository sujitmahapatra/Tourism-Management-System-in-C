#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TOURS 100
#define MAX_NAME_LENGTH 50

// Structure to represent a tour
typedef struct {
    int id;
    char name[MAX_NAME_LENGTH];
    int capacity;
    int booked;
} Tour;

// Function prototypes
void displayMenu();
void addTour();
void displayTours();
void bookTour();

// Global array to store tours
Tour tours[MAX_TOURS];
int numTours = 0;

int main() {
    int choice;

    // Main menu loop
    do {
        displayMenu();
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar(); // Consume newline character

        switch(choice) {
            case 1:
                addTour();
                break;
            case 2:
                displayTours();
                break;
            case 3:
                bookTour();
                break;
            case 4:
                printf("Exiting the program.\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while(choice != 4);

    return 0;
}

// Function to display the main menu
void displayMenu() {
    printf("\nTourism Management System\n");
    printf("1. Add a new tour\n");
    printf("2. Display available tours\n");
    printf("3. Book a tour\n");
    printf("4. Exit\n");
}

// Function to add a new Tour
void addTour() {
    if (numTours >= MAX_TOURS) {
        printf("Cannot add more tours. Maximum limit reached.\n");
        return;
    }

    Tour newTour;
    printf("Enter tour name: ");
    fgets(newTour.name, MAX_NAME_LENGTH, stdin);
    newTour.name[strcspn(newTour.name, "\n")] = '\0'; // Remove trailing newline
    printf("Enter tour capacity: ");
    scanf("%d", &newTour.capacity);

    newTour.id = numTours + 1;
    newTour.booked = 0;
    tours[numTours++] = newTour;

    printf("Tour added successfully.\n");
}

// Function to display available tours
void displayTours() {
    if (numTours == 0) {
        printf("No tours available.\n");
        return;
    }

    printf("Available Tours:\n");
    for (int i = 0; i < numTours; i++) {
        printf("%d. %s (Capacity: %d, Booked: %d)\n", tours[i].id, tours[i].name, tours[i].capacity, tours[i].booked);
    }
}

// Function to book a tour
void bookTour() {
    int tourId;
    printf("Enter tour ID(Tour Serial no.) to book: ");
    scanf("%d", &tourId);

    if (tourId <= 0 || tourId > numTours) {
        printf("Invalid tour ID.\n");
        return;
    }

    Tour *selectedTour = &tours[tourId - 1];

    int numBookings;
    printf("Enter the number of bookings for tour '%s' (ID: %d): ", selectedTour->name, selectedTour->id);
    scanf("%d", &numBookings);

    if (numBookings <= 0) {
        printf("Invalid number of bookings.\n");
        return;
    }

    if (selectedTour->booked + numBookings > selectedTour->capacity) {
        printf("Sorry, the tour '%s' does not have enough capacity for %d bookings.\n", selectedTour->name, numBookings);
        return;
    }

    selectedTour->booked += numBookings;
    printf("%d bookings for tour '%s' (ID: %d) have been successfully booked.\n", numBookings, selectedTour->name, selectedTour->id);
}
