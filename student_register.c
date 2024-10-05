#include <stdio.h>  // Branch fileio_simple
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
void initialize_student_list(Student* student_list, int sizeof_students);
int get_students_from_file(Student* students, int sizeof_students);

int select_id(Student* students, int sizeof_students, int* sel_id);
int create_new_student(Student* student);
int add_student_by_position(Student* destination, int position, int sizeof_students, Student* student, int* id);
int add_student_lazy(Student* destination, int sizeof_students, Student* student, int* id);
int change_student_by_id(Student* students, int sizeof_students, int id, Student* updated_info);
int remove_student_by_id(Student* students, int sizeof_students, int id);
int print_student_by_id(Student* students, int sizeof_students, int id);
int find_student_by_id(Student* students, int sizeof_students, int id );
void update_id_list(Student* students, int sizeof_students, int dest_array[]);
void sort_array(int array[], int size);

int main ()
{

    int next_student_id = 100;
    int register_size = 10;
    int sel_student_id = 0;
    int validation = 0;
    int validate_add = 0;
    int op;
    Student student_input;

    printf("How many users: ");
    scanf(" %d", &register_size);

    Student students[register_size];
    int id_list[register_size];
    int id_index = 0;

    initialize_student_list(students, register_size);

    while(1) 
    {
        printf("\n---Student registration ---\n");
        printf("1. Add new student\n");
        printf("2. Print student ids\n");
        printf("3. Change student by id\n");
        printf("4. Remove student by id\n");
        printf("5. Print student by id\n");
        printf("6. Exit\n");
        printf("--> ");
        scanf(" %d", &op);
        switch (op)
    
        {
            case 1:
                validation = create_new_student(&student_input);
                validate_add = add_student_lazy(students, register_size, &student_input, &next_student_id);
                if (validate_add >=0)
                printf("Student added with ID: %d\n", students[validate_add].id);
                else 
                printf("Error, student not added.\n");
                break;
            case 2:
                printf("Registered students:\n");
                update_id_list(students, register_size, id_list);
                for (int i = 0;i < register_size;i++)
                {
                    if (id_list[i] != -1) 
                    {
                        id_index = find_student_by_id(students, register_size, id_list[i]);
                        printf("ID: %i  Name: %s\n", students[id_index].id, students[id_index].name);
                    }

                }
                printf("\n");
                break;
            case 3:
                if (select_id(students, register_size, &sel_student_id) >= 0)  
                {
                    validation = create_new_student(&student_input);
                    validate_add = change_student_by_id(students, register_size, sel_student_id, &student_input);
                    if (validate_add < 0) printf("Change to student %d unsuccessful\n", sel_student_id);
                    else printf("Student %d successfully updated\n", sel_student_id);
                }
                break;
            case 4:
                if (select_id(students, register_size, &sel_student_id) >= 0)
                {
                    remove_student_by_id(students, register_size, sel_student_id);
                }                
                break;
            case 5:
                if (select_id(students, register_size, &sel_student_id) >= 0)
                {
                    print_student_by_id(students, register_size, sel_student_id);
                }                
                break;
            case 6:
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

int select_id(Student* students, int sizeof_students, int* sel_id)
{
    printf("Select Id: ");     
    scanf(" %d", sel_id);
    if (find_student_by_id(students, sizeof_students, *sel_id) < 0)
    {
        printf("No student registered with that ID\n");
        return -1;
    }
    else return *sel_id;
}

int create_new_student(Student* student){
        printf("Enter student name: ");
        scanf(" %[^\n]", student->name);
        clear_input_buffer();
        printf("Enter email: ");
        scanf("%s",student->email);
        clear_input_buffer();
        printf("Enter phone number: ");
        scanf("%s",student->phone_number);
        clear_input_buffer();
        printf("Enter street name: ");
        scanf(" %[^\n]",student->address.street_name);
        clear_input_buffer();
        printf("Enter post code: ");
        scanf("%s",student->address.post_code);
        clear_input_buffer();
        printf("Enter city name: ");
        scanf(" %[^\n]",student->address.city_name);
        clear_input_buffer();
        return 0;
}

int add_student_by_position(Student* destination, int position, int sizeof_students, Student* student, int* id)   
{   
    if (position>=0 && position<sizeof_students)
    {   
        student->id = *id;
        destination[position] = *student;
        (*id)++;
        return position;
    }   
    else return -1;
}


int add_student_lazy ( Student* destination, int sizeof_students, Student* student, int* id)
{
    return add_student_by_position(destination, find_student_by_id(destination, sizeof_students, -1), sizeof_students, student, id);
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

int print_student_by_id(Student* students, int sizeof_students, int id)
{
    int index = find_student_by_id(students, sizeof_students, id);
    if (index < 0) return -1;
    else 
    {
    printf("---------------------------\n");
    printf("Student ID: %d\n", students[index].id);
    printf("Student name: %s\n", students[index].name);
    printf("Email: %s\n", students[index].email);
    printf("Phone Number: %s\n", students[index].phone_number);
    printf("Post Address: %s\n", students[index].address.street_name);
    printf("Post Code: %s\n", students[index].address.post_code);
    printf("City: %s\n", students[index].address.city_name);
    printf("\n");
    return 1;
    }
}

int find_student_by_id(Student* students, int sizeof_students, int id)
{
    for ( int i = 0; i < sizeof_students; i++ )
    {
        if ( students[i].id == id ){
            return i;
        } 
    }

    return -1;
}

void update_id_list(Student* students, int sizeof_students, int dest_array[])
{
    for ( int i = 0; i < sizeof_students; i++ )
    {
        dest_array[i] = students[i].id;
    }
    sort_array(dest_array, sizeof_students);
}

void sort_array(int array[], int size)
{
   for(int i = 0; i < size - 1; i++)
   {
      for(int j = 0; j < size - i - 1; j++)
      {
         if(array[j] > array[j+1])
         {
            int temp = array[j];
            array[j] = array[j+1];
            array[j+1] = temp;
         }
      }
   }
}
