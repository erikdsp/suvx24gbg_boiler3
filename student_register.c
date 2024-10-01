#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct mailing_address
{                               
    char street_name[80];
    char post_code[10];         
    char city_name[80];
};

typedef struct student
{
    int id;
    char name [80];
    char email[80];
    char phone_number[20];       
    struct mailing_address address;
}Student;

void clear_input_buffer();

int create_new_student(Student* student);
int add_student_by_position(Student* destination, int position, int sizeof_students, Student* student);
int add_student_lazy(Student* destination, int sizeof_students, Student* student);
int change_student_by_id(Student* students, int sizeof_students, int id, Student* updated_info);
int remove_student_by_id(Student* students, int sizeof_students, int id);
int find_student_by_id( Student* students, int sizeof_students, int id );

void initialize_student_list(Student* student_list, int sizeof_students);

int main ()
{

    int id_base = 100;
    int register_size = 10;
    int student_index = 0;
    int validation = 0;
    int validate_add = 0;
    int op;
    Student student_input;

    printf("How many users");
    scanf(" %d", &register_size);

    Student students[register_size];
    initialize_student_list(students, register_size);

    while(1) 
    {
        printf("---Student registration ---\n");
        printf("1. Add new student\n");
        printf("2. Print student ids\n");
        printf("3. Change student by id\n ");
        printf("4. Remove student by id\n ");
        printf("5. Exit\n ");
        scanf(" %d", &op);
        switch (op)
    
        {
            case 1:
                validation = create_new_student(&student_input);
                validate_add = add_student_lazy(students, register_size, &student_input);
                if (validate_add >=0)
                printf("Student added at position %d\n", student_index);
                else 
                printf("Error, student not added.\n");
                break;
            case 2:
                for (int i = 0;i < register_size;i++)
                {
                    printf("%i) %s\n", i, students[i].name);
                }
                break;
            case 3:
                printf("Select Id: ");      // Function currently not working. 
                scanf(" %d", &student_index);
                validation = create_new_student(&student_input);
                validate_add = change_student_by_id(students, register_size, student_index, &student_input);
                break;
            case 4:
                printf("Select Id: ");
                scanf(" %d", &student_index);
                remove_student_by_id(students, register_size, student_index);
            break;
            case 5:
                exit(0);
        default:
            break;
        }
    }

    return 0;
}



void clear_input_buffer()
{
    char c;
    while ((c=getchar()) != '\n' && c != EOF);
    
}
int add_student_by_position(Student* destination, int position, int sizeof_students, Student* student)   
{   
    if (position>=0 && position<sizeof_students)
    {   
        destination[position] = *student;
        return position;
    }   
    else return -1;
}

int create_new_student(Student* student){
        printf("Enter student name: ");
        scanf("%s",student->name);
        printf("Enter email: ");
        scanf("%s",student->email);
        printf("Enter phone number: ");
        scanf("%s",student->phone_number);
        printf("Enter street name: ");
        scanf("%s",student->address.street_name);
        printf("Enter post code: ");
        scanf("%s",student->address.post_code);
        printf("Enter city name: ");
        scanf("%s",student->address.city_name);
        return 0;
}

void initialize_student_list(Student* student_list, int sizeof_students){
    for ( int i = 0; i < sizeof_students; i++ ){
        student_list[i].id = -1;
        strcpy(student_list[i].name, "");
        strcpy(student_list[i].email, "");
        strcpy(student_list[i].phone_number, "");
        strcpy(student_list[i].address.street_name, "");
        strcpy(student_list[i].address.post_code, "");
        strcpy(student_list[i].address.city_name, "");
    }
}

int add_student_lazy ( Student* destination, int sizeof_students, Student* student )
{
    return add_student_by_position(destination, find_student_by_id(destination, sizeof_students, -1), sizeof_students, student);
}

int remove_student_by_id(Student* students, int sizeof_students, int id)
{
    int index = find_student_by_id(students, sizeof_students, id);
    
    if ( index < 0 ){
        return -1;
    } else {
        
        students[index].id = -1;
        strcpy(students[index].name, "");
        strcpy(students[index].email, "");
        strcpy(students[index].phone_number, "");
        strcpy(students[index].address.street_name, "");
        strcpy(students[index].address.post_code, "");
        strcpy(students[index].address.city_name, "");

        return 1;
    }
}

int change_student_by_id(Student* students, int sizeof_students, int id, Student* updated_info)
{
    int index = find_student_by_id(students, sizeof_students, id);

    if ( index < 0 ){
        return -1;
    } else {
        strcpy(students[index].name, updated_info->name);
        strcpy(students[index].email, updated_info->email);
        strcpy(students[index].phone_number, updated_info->phone_number);
        strcpy(students[index].address.street_name, updated_info->address.street_name);
        strcpy(students[index].address.post_code, updated_info->address.post_code);
        strcpy(students[index].address.city_name, updated_info->address.city_name);

        return 1;
    }
}

int find_student_by_id(Student* students, int sizeof_students, int id)
{
    for ( int i = 0; i < sizeof_students; i++ ){
        if ( students[i].id == id ){
            return i;
        } 
    }

    return -1;
}


// int find_student_by_id(Student* students, int sizeof_students, int id)
// {
//     for ( int i = 0; i < sizeof_students; i++ ){
//         if ( students[i].id == id ){
//             return i;
//         } 
// }


    // students[find_student(id)].id = -1;