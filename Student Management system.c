#include<stdio.h>
#include<string.h>
#include<Windows.h> //For Window Users
// #include<unistd.h>  //For Linux Users

// structure to store student record
typedef struct student{
    char name[50];
    char branch[3];
    int age;
    char gender[7];
    char roll_no[10];
    float cpi;
} stud;

void swap(stud *a, stud *b){   
    // Function to swap two pointers(to stud)
    stud temp = *a;
    *a = *b;
    *b = temp;
    return;
}

void sort_by_cpi(stud students[],int n){
    // Function to sort array of structs by cpi in ascending order
    for(int i=0; i<n-1; i++){
        for(int j=i+1; j<n; j++){
            if(students[i].cpi > students[j].cpi){
                swap(&students[i], &students[j]);
            }
        }
    }
    return;
}

void sort_by_name(stud students[],int n){  
    // Function to sort array of structs by name in ascending order
    for(int i=0; i<n-1; i++){
        for(int j=i+1; j<n; j++){
            if(strcmp(students[i].name,students[j].name)>0){
                swap(&students[i], &students[j]);
            }
        }
    }
    return;
}

void sort_by_rollno(stud students[],int n){
    // Function to sort array of structs by roll in ascending order
    for(int i=0; i<n-1; i++){
        for(int j=i+1; j<n; j++){
            if(strcmp(students[i].roll_no,students[j].roll_no)>0){
                swap(&students[i], &students[j]);
            }
        }
    }
    return;
}

void to_upper(char str[]){  // Pawan
    // Function to convert string to uppercase
    for(int i=0;str[i]!='\0';i++){
        if(str[i]>='a' && str[i]<='z'){
            str[i] = str[i] - 32;
        }
    }
    return;
}

void to_cap(char str[]){   
    // Function to Captilize first letter of each word
    int flag = 1;
    for(int i=0;i<str[i]!='\0';i++){
        if(str[i]>='a' && str[i]<='z' && flag ){
            str[i] = str[i] - 32;
            flag = 0;
        }else if(str[i]>='A' && str[i]<='Z' && !flag){
            str[i] = str[i] + 32;
            flag = 0;
        }else{
            flag =0;
        }if(str[i] == ' '){
            flag = 1;
        }
    }
    return;
}

void to_lower(char str[]){ 
    // Function to convert string to lowercase
    for(int i=0;str[i]!='\0';i++){
        if(str[i]>='A' && str[i]<='Z'){
            str[i] = str[i] + 32;
        }
    }
    return;
}

void showAnimation( char str[] ){  
    //Function to show animation
    for( int i = 0 ; i < strlen(str) ; i++ ){
        Sleep(40);
        printf("%c",str[i]);
    }
    return;
}

void quit(){   
    // Function to show quit animation
    showAnimation("\n Closing Program...\n");
    Sleep(1000);
    printf("\n Program Closed !\n");
    return;
}

int askMenu(int* choice){
    // Function to show menu after each operation
    printf("\n Select an option to proceed : \n 1. Main Menu\n 2. Repeat Operation\n 3. Exit\n Enter your choice : ");
    int option;
    scanf("%d", &option);
    if(option==1){
        return 0;
    }else if(option == 2){
        return 1;
    }else if(option == 3){
        *choice = 6;
    }else{
        printf("\n Invalid Input !\n");
        return askMenu(choice);
    }
    return 0;
}

int check(){ 
    // Function to check if file is availale or not
    FILE* file = fopen("student.csv","r");
    if(file==NULL){
        return 1;
    }
    fclose(file);
    return 0;
}

void deleteRecord(){   
    // Function to delete student record

    if(check()){
        printf(" No Record Present :(\n");
        return;
    }

    char roll_no[10];
    printf("\n Enter Roll No. to delete : ");
    scanf("%s",roll_no);
    to_upper(roll_no);

    
    int records = 0;
    int index = -1;
    stud students[100];

    FILE* file = fopen("student.csv","a+");
    int Sno = 1;
    while(!feof(file)){
        fscanf( file, "%50[^,], %3[^,], %7[^,], %d, %50[^,], %f \n", students[records].name, students[records].branch, students[records].gender, &students[records].age, students[records].roll_no, &students[records].cpi);

        if(strcmp(students[records].roll_no, roll_no) == 0){
            printf(" Record Found :)\n\n");
            printf("\n +-------+----------------------------+-------------+----------+--------+--------------+--------+\n");
            printf(" | S.No. |                       Name |      Branch |   Gender |    Age |     Roll No. |    CPI |\n");
            printf(" +-------+----------------------------+-------------+----------+--------+--------------+--------+\n");
            printf(" |%6d |%27s |%12s |%9s | %6d |%13s |%7.2f |\n", Sno++, students[records].name, students[records].branch, students[records].gender, students[records].age, students[records].roll_no, students[records].cpi);
            printf(" +-------+----------------------------+-------------+----------+--------+--------------+--------+\n\n");
            index = records;
        }
        records++;
    }

    fclose(file);

    if(index == -1){
        printf(" Record Not Found !\n");
        return;
    }

    FILE* file2 = fopen("student.csv","w");

    for(int i=0;i<records;i++){
        if(i==index){
            continue;
        }
        fprintf(file, "%s, %s, %s, %d, %s, %f \n", students[i].name, students[i].branch, students[i].gender, students[i].age, students[i].roll_no, students[i].cpi);
    }

    fclose(file2);

    printf("\n Record Deleted Successfully :)\n");

    return;
}

void updateRecord(){   
    // Function to update student record

    if(check()){
        printf(" No Record Present :(\n");
        return;
    }

    char roll_no[10];
    printf("\n Enter Roll No. to update : ");
    scanf("%s",roll_no);
    to_upper(roll_no);
    
    int records = 0;
    int index = -1;
    stud students[100];
    int Sno = 1;

    FILE* file = fopen("student.csv","a+");

    while(!feof(file)){
        fscanf( file, "%50[^,], %3[^,], %7[^,], %d, %50[^,], %f \n", students[records].name, students[records].branch, students[records].gender, &students[records].age, students[records].roll_no, &students[records].cpi);

        if(strcmp(students[records].roll_no, roll_no) == 0){
            printf(" Record Found :)\n\n");
            printf("\n +-------+----------------------------+-------------+----------+--------+--------------+--------+\n");
            printf(" | S.No. |                       Name |      Branch |   Gender |    Age |     Roll No. |    CPI |\n");
            printf(" +-------+----------------------------+-------------+----------+--------+--------------+--------+\n");
            printf(" |%6d |%27s |%12s |%9s | %6d |%13s |%7.2f |\n", Sno++, students[records].name, students[records].branch, students[records].gender, students[records].age, students[records].roll_no, students[records].cpi);
            printf(" +-------+----------------------------+-------------+----------+--------+--------------+--------+\n\n");
            index = records;
        }
        records++;
    }
    fclose(file);

    if(index == -1){
        printf(" Record Not Found !\n");
        return;
    }

    int choice;
    update:

    printf("\n Select value to be updated: \n 1. Name\n 2. Branch\n 3. Gender\n 4. Age\n 5. Roll No.\n 6. CPI\n 7. Cancel Operation \n Enter your Choice : ");
    scanf("%d",&choice);

    char ch;
    switch (choice){
        case 1:
            printf(" Name : ");
            scanf("%c",&ch);
            scanf( "%[^\n]s" , (students[index].name) );
            to_cap(students[index].name);
            break;
        case 2:
            printf(" Branch (CS/AI/MC/EE/ME/CE/MM/PH) : ");
            scanf( "%s" , (students[index].branch) );
            to_upper(students[index].branch);
            break;
        case 3:
            printf(" Gender (M/F) : ");
            scanf( "%s" , (students[index].gender));
            to_upper(students[index].gender);
            break;
        case 4:
            printf(" Age : ");
            scanf( "%d" , &students[index].age);
            break;
        case 5:
            printf(" Roll No. : ");
            scanf( "%s" , (students[index].roll_no) );
            to_upper(students[index].roll_no);
            break;
        case 6:
            printf(" CPI : ");
            scanf("%f" , &students[index].cpi);
            break;
        case 7:
            return;
        default:
            printf("\n Invalid Choice !\n");
            break;
    }
    if(!(choice==1 || choice==2 || choice==3 || choice==4 || choice==5 || choice==6 || choice==7)){
        goto update;
    }

    FILE* file2 = fopen("student.csv","w");

    for(int i=0;i<records;i++){
        fprintf(file, "%s, %s, %s, %d, %s, %f \n", students[i].name, students[i].branch, students[i].gender, students[i].age, students[i].roll_no, students[i].cpi);
    }

    fclose(file2);

    printf("\n Record Updated Successfully :)\n ");

    return;
}

void searchRecord(){   
    // Function to search student record

    if(check()){
        printf(" No Record Present :(\n");
        return;
    }

    search:

    printf("\n Search by: \n 1. Roll No.\n 2. Name\n\n Enter Choice : ");

    int choice;
    scanf("%d",&choice);

    char roll_no[10] = "";
    char name[50] = "";

    char ch;
    if(choice==1){
        printf("\n Enter Roll No. to search : ");
        scanf("%s",roll_no);
        to_upper(roll_no);
    }else if(choice==2){
        printf("\n Enter Name to search : ");
        scanf("%c",&ch);
        scanf("%[^\n]s",name);
        to_cap(name);
    }else{
        printf(" Invalid Choice :(\n");
        goto search;

    }

    int records = 0;
    int index = -1;
    stud curr_student;
    int Sno = 1;
    FILE* file = fopen("student.csv","r");

    while(!feof(file)){
        fscanf( file, "%50[^,], %3[^,], %7[^,], %d, %50[^,], %f \n", curr_student.name, curr_student.branch, curr_student.gender, &curr_student.age, curr_student.roll_no, &curr_student.cpi);

        if(((choice==2) &&  strcmp(curr_student.name, name)==0) || (choice==1 && strcmp(curr_student.roll_no, roll_no)==0)){
            printf(" Record Found :)\n\n");
            printf("\n +-------+----------------------------+-------------+----------+--------+--------------+--------+\n");
            printf(" | S.No. |                       Name |      Branch |   Gender |    Age |     Roll No. |    CPI |\n");
            printf(" +-------+----------------------------+-------------+----------+--------+--------------+--------+\n");
            printf(" |%6d |%27s |%12s |%9s | %6d |%13s |%7.2f |\n", Sno++, curr_student.name, curr_student.branch, curr_student.gender, curr_student.age, curr_student.roll_no, curr_student.cpi);
            printf(" +-------+----------------------------+-------------+----------+--------+--------------+--------+\n\n");

            index = records;
        }
        records++;
    }
    fclose(file);

    if(index == -1){
        printf(" Record Not Found !\n");
    }  
    return;
}

void showRecord(){ 
    // Function to show student record(s)

    FILE* file = fopen("student.csv","r");

    if(file == NULL){
        printf(" No Record Present :(\n");
        return;
    }

    stud students[100];
    int records = 0;

    while(!feof(file)){
        fscanf( file, "%50[^,], %3[^,], %7[^,], %d, %50[^,], %f \n", students[records].name, students[records].branch, students[records].gender, &students[records].age, students[records].roll_no, &students[records].cpi);
        records++;
    }
    fclose(file);

    int sNo = 1;
    printf("\n +-------+----------------------------+-------------+----------+--------+--------------+--------+\n");
    printf(" | S.No. |                       Name |      Branch |   Gender |    Age |     Roll No. |    CPI |\n");
    printf(" +-------+----------------------------+-------------+----------+--------+--------------+--------+\n");

    for(int i=0; i<records; i++){
        printf(" |%6d |%27s |%12s |%9s | %6d |%13s |%7.2f |\n", sNo, students[i].name, students[i].branch, students[i].gender, students[i].age, students[i].roll_no, students[i].cpi);
        sNo++ ;
    }

    printf(" +-------+----------------------------+-------------+----------+--------+--------------+--------+\n");

    search:
    printf("\n Sort By : \n 1. Name\n 2. Roll No.\n 3. CPI\n 4. Return to Menu\n Enter your choice : ");
    int choice;
    scanf("%d",&choice);

    if(choice==1){
        sort_by_name(students,records);
    }else if(choice==2){
        sort_by_rollno(students,records);
    }else if(choice==3){
        sort_by_cpi(students,records);
    }else if(choice==4){
        return;
    }else{
        printf("\n Invalid Input :(\n");
        goto search;
    }

    search2:
    printf("\n 1. Ascending Order\n 2. Descending Order\n Enter your choice : ");
    int x;
    scanf("%d",&x);

    if(x!=1 && x!=2){
        printf("\n Invalid Choice :)\n");
        goto search2;
    }


    printf("\n +-------+----------------------------+-------------+----------+--------+--------------+--------+\n");
    printf(" | S.No. |                       Name |      Branch |   Gender |    Age |     Roll No. |    CPI |\n");
    printf(" +-------+----------------------------+-------------+----------+--------+--------------+--------+\n");

    sNo = 1;
    if(x==1){
        for(int i=0; i<records; i++){
            printf(" |%6d |%27s |%12s |%9s | %6d |%13s |%7.2f |\n", sNo, students[i].name, students[i].branch, students[i].gender, students[i].age, students[i].roll_no, students[i].cpi);
            sNo++ ;
        }
    }else if(x==2){
        for(int i=records-1; i>=0; i--){
            printf(" |%6d |%27s |%12s |%9s | %6d |%13s |%7.2f |\n", sNo, students[i].name, students[i].branch, students[i].gender, students[i].age, students[i].roll_no, students[i].cpi);
            sNo++ ;
        }
    }

    printf(" +-------+----------------------------+-------------+----------+--------+--------------+--------+\n");
    return;
}

void addRecord(){  
    //Function to add Student Record

    printf("\n Enter the following details : \n");

    FILE* file = fopen("student.csv","a+");
    if(file == NULL){
        printf("Error opening the file.\n");
        return;
    }

    stud newStudent;
    char ch;

    printf(" Name : ");
    scanf("%c",&ch);
    scanf( "%[^\n]s" , (newStudent.name) );
    printf(" Branch (CS/AI/MC/EE/ME/CE/MM/PH) : ");
    scanf( "%s" , (newStudent.branch) );
    printf(" Gender (M/F) : ");
    scanf( "%s" , (newStudent.gender));
    printf(" Age : ");
    scanf( "%d" , &(newStudent.age));
    printf(" Roll No. : ");
    scanf( "%s" , (newStudent.roll_no) );
    printf(" CPI : ");
    scanf("%f" , &newStudent.cpi);

    to_upper(newStudent.roll_no);
    to_upper(newStudent.branch);
    to_upper(newStudent.gender);
    to_cap(newStudent.name);

    fprintf(file, "%s, %s, %s, %d, %s, %f \n", newStudent.name, newStudent.branch, newStudent.gender, newStudent.age, newStudent.roll_no, newStudent.cpi);

    fclose(file);

    printf(" \n Record Added Successfully :) \n");

    return;
}

int main(){

    system("cls");      // To clear terminal

    showAnimation("\n -------------- Welcome to Student Management System -------------- \n\n");
    Sleep(500);
    int choice = 0;
    int x = 0;    

    while(choice!=6){
        if(x == 0){
            printf("\n Select an option to proceed : \n");
            printf("\n 1. Add Record \n 2. Show Record \n 3. Update Record \n 4. Delete Record \n 5. Search Record \n 6. Exit \n\n");
            printf(" Enter your Choice : ");
            scanf( "%d" , &choice );
        }
        
        if( choice == 1 ){
            addRecord();
            x = askMenu(&choice);
        }else if( choice == 2 ){
            showRecord();
            x = askMenu(&choice);// x = 1
        }else if( choice == 3){
            updateRecord();
            x = askMenu(&choice);
        }else if( choice == 4){
            deleteRecord();
            x = askMenu(&choice);
        }else if( choice == 5){
            searchRecord();
            x = askMenu(&choice);
        }else if( choice == 6){
            break;
        }else{
            printf("\n Invalid Input :(\n");
        }
    }

    quit();
    
    return 0;
}