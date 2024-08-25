#ifndef CLINIC_SYS_H
#define CLINIC_SYS_H

#define PASSWORD 1234
#define ADMIN 1
#define USER 2
#define max_patient 100
#define max_slot 5
int patient_counter = 0;
typedef struct
{
     char name[30];
     int id;
     int age;
     char gender[30];

}new_patient;

new_patient patients[max_patient];

typedef struct
{
    int slot_id;
    int is_reserved ;
    int patient_id;
    char time[20];
}slots;

slots slot[max_slot]=
{
  {1,0 ,-1 ,"2:00pm to 2:30pm"},
  {2,0 ,-1 ,"2:30pm to 3:00pm"},
  {3,0 ,-1 ,"3:00pm to 3:30pm"},
  {4,0 ,-1 ,"3:30pm to 4:00pm"},
  {5,0 ,-1 ,"4:00pm to 4:30pm"}
};




int Entering_Status(void);
void admin_mode(void);
void user_mode(void);
void ADD_Patient(void);
void edit_Patient(void);
void reserve_slot(void);
void cancel_reservation(void);
void view_reservation(void);
void view_patient_record(void);



#endif // CLINIC_SYS_h
