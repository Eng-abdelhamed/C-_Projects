#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "clinic_sys.h"

int Entering_Status(void) {
    int pass;
    int attempts = 0;

    while (attempts < 3) {
        printf("Enter Password: ");
        scanf("%i", &pass);
        if (pass == PASSWORD) {
            return 1;
        }
        attempts++;
        printf("Wrong Pass. Attempts left: %d\n", 3 - attempts);
    }
    printf("Access Denied. Closed system.\n");

    return 0;
}

void ADD_Patient(void) {
    if (patient_counter == max_patient) {
        printf("Patient list is full.\n");
        return;
    }
    int id;
    printf("Enter Patient ID: ");
    scanf("%i", &id);
    for (int i = 0; i < patient_counter; i++) {
        if (patients[i].id == id) {
            printf("The ID already exists.\n");
            return;
        }
    }
    patients[patient_counter].id = id;
    printf("Patient Name: ");
    scanf("%s", patients[patient_counter].name);
    printf("Patient Age: ");
    scanf("%i", patients[patient_counter].age);
    printf("Patient Gender: ");
    scanf("%s", patients[patient_counter].gender);
    patient_counter++;
    printf("Patient added successfully.\n");
}

void edit_Patient(void) {
    int id, found = 0;

    printf("Enter the ID to edit: ");
    scanf("%i", &id);
    for (int i = 0; i < patient_counter; i++) {
        if (patients[i].id == id) {
            printf("Enter New Name: ");
            scanf("%s", patients[i].name);
            printf("Enter New Age: ");
            scanf("%i", patients[i].age);
            printf("Enter New Gender: ");
            scanf("%s", patients[i].gender);
            found = 1;
            printf("Patient record updated.\n");
            break;
        }
    }
    if (!found) {
        printf("The ID not found.\n");
    }
}

void reserve_slot(void) {
    int id, slot_choice;

    printf("Available slots:\n");
    for (int i = 0; i < max_slot; i++) {
        if (!slot[i].is_reserved) {
            printf("Slot %d: %s\n", slot[i].slot_id, slot[i].time);
        }
    }
    printf("Enter Patient ID for reservation: ");
    scanf("%i", &id);

    int patient_flag = 0; // Patient not found
    for (int i = 0; i < patient_counter; i++) {
        if (patients[i].id == id) {
            patient_flag = 1;
            break;
        }
    }
    if (!patient_flag) {
        printf("ID not found.\n");
        return;
    }
    printf("Enter the desired slot: ");
    scanf("%i", &slot_choice);

    if (slot_choice < 1 || slot_choice > max_slot || slot[slot_choice - 1].is_reserved) {
        printf("Invalid slot choice.\n");
        return;
    }

    slot[slot_choice - 1].is_reserved = 1;
    slot[slot_choice - 1].patient_id = id;
    printf("Slot reserved successfully.\n");
}

void cancel_reservation(void) {
    int id;
    printf("Enter Patient ID to cancel reservation: ");
    scanf("%i", &id);
    for (int i = 0; i < max_slot; i++) {
        if (slot[i].is_reserved && slot[i].patient_id == id) {
            slot[i].is_reserved = 0;
            slot[i].patient_id = -1;
            printf("Reservation canceled.\n");
            return;
        }
    }
    printf("No reservation found for this ID.\n");
}

void view_reservation(void) {
    printf("Viewed reservations:\n");
    for (int i = 0; i < max_slot; i++) {
        if (slot[i].is_reserved) {
            printf("Slot %d: %s\n", slot[i].slot_id, slot[i].time);
        }
    }
}

void view_patient_record(void) {
    int id;
    printf("Enter ID: ");
    scanf("%i", &id);

    for (int i = 0; i < patient_counter; i++) {
        if (patients[i].id == id) {
            printf("Patient Name: %s\n", patients[i].name);
            printf("Patient ID: %i\n", patients[i].id);
            printf("Patient Age: %i\n", patients[i].age);
            printf("Patient Gender: %s\n", patients[i].gender);
            return;
        }
    }
    printf("Patient ID not found.\n");
}

void admin_mode(void) {
    if (!Entering_Status()) {
        return;
    }
    int choice;
    do {
        printf("-------ADMIN_MODE-------\n");
        printf("1- Add new patient record\n");
        printf("2- Edit patient record\n");
        printf("3- Reserve a slot with the doctor\n");
        printf("4- Cancel reservation\n");
        printf("5- Log out\n");
        printf("Enter Choice: ");
        scanf("%i", &choice);
        switch (choice) {
            case 1:
                ADD_Patient();
                break;
            case 2:
                edit_Patient();
                break;
            case 3:
                reserve_slot();
                break;
            case 4:
                cancel_reservation();
                break;
            case 5:
                printf("SEE YOU LATER...\n");
                break;
            default:
                printf("Invalid choice, try again.\n");
        }
    } while (choice != 5);
}

void user_mode(void) {
    int choice;
    do {
        printf("-------USER_MODE-------\n");
        printf("1- View patient record.\n");
        printf("2- View today’s reservations\n");
        printf("3- Exit\n");
        printf("Enter Choice: ");
        scanf("%i", &choice);
        switch (choice) {
            case 1:
                view_patient_record();
                break;
            case 2:
                view_reservation();
                break;
            case 3:
                printf("SEE YOU LATER...\n");
                break;
            default:
                printf("Invalid choice, try again.\n");
        }
    } while (choice != 3);
}

int main() {
    int mode;
    while (1) {
        printf("-------CLINIC_SYSTEM-------\n");
        printf("1- ADMIN mode\n");
        printf("2- USER mode\n");
        printf("3- EXIT\n");
        printf("Enter Choice: ");
        scanf("%i", &mode);
        switch (mode) {
            case 1:
                admin_mode();
                break;
            case 2:
                user_mode();
                break;
            case 3:
                printf("CLOSING SYSTEM\n");
                return 0;  // Exit the program
            default:
                printf("ENTER CORRECT CHOICE\n");
                break;
        }
    }
}
