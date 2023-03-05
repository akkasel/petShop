#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define SIZE 25

struct data{
	char nama[105];
	int hari, bulan, tahun;
	char umur[255];
	char jenisKelamin[255];
	double berat;
	
	data* next;
}*head[SIZE];

// untuk mentotalkan nilai ascii dari semua karakter!!
int hashFunction(char name[]){
	int counter = 0;
	int length = strlen(name);
	for(int i=0;i<length;i++){
		counter = counter + name[i];
	}
	// total nilai ascii text yang dimasukan modulo size
	return counter % SIZE;
}

void menuPetShop();
void petManagementSystem();
void removePetMenu();

// INSERT / PUSH [ add new pet data ]
void push(char name[], int day, int month, int year,
			char age[], char gender[], double weight){
	data* newnode = (data*) malloc(sizeof(data));
	strcpy(newnode->nama, name);
	newnode->hari = day;
	newnode->bulan = month;
	newnode->tahun = year;
	strcpy(newnode->umur, age);
	strcpy(newnode->jenisKelamin, gender);
	newnode->berat = weight;
	
	newnode->next = NULL;
	
	// sebelum push data, kita harus tau dulu mau masukin data ke index tabel ke berapa.
	int key = hashFunction(name);
	
	if(head[key] == NULL){
		head[key] = newnode;
	} 
	else{
		data* temp = head[key];
		while(temp->next != NULL){
			temp = temp->next;
		}
		temp->next = newnode;
	}
}

// Menu : Add Pet
void addPetMenu(){

	char petName[255];
	int day, month, year;
	char age[255];
	char gender[255];
	double weight;
	
	printf("Insert pet name [5 - 30 characters] : ");
	scanf("%s", petName);
	int lenPetName = strlen(petName);
	while(lenPetName < 5 || lenPetName > 30){
		printf("Please input a valid name\n");
		printf("Insert pet name [5 - 30 characters] : ");
		scanf("%[^\n]", petName);
		getchar();
		lenPetName = strlen(petName);
	}
	
	printf("Insert pet Date of Birth [dd-mm-yyyy] : ");
	scanf("%d-%d-%d", &day, &month, &year);
	while(day < 1 || day > 31 || month < 1 || month > 12 || year < 0 || year > 9999){
		printf("Plese input a valid date of birth\n");
		printf("Insert pet Date of Birth [dd-mm-yyyy] : ");
		scanf("%d-%d-%d", &day, &month, &year);
	}
	
	printf("Insert pet age [Must be a number] : ");
	scanf("%s", age);
	int lenAge = strlen(age);
	int isNotNumber = 0;
	for(int i=0;i<lenAge;i++){
		if(age[i] < '0' || age[i] > '9'){
			isNotNumber++;
		}
	}
	while(isNotNumber != 0){
		printf("Input must be a number!\n");
		printf("Insert pet age [Must be a number] : ");
		scanf("%s", age);
	}
	
	printf("Insert pet gender [Male | Female] (Case Insensitive) : ");
	scanf("%s", gender);
	while(strcmpi(gender, "Male") != 0 && strcmpi(gender, "Female") != 0){
		printf("Insert pet gender [Male | Female] (Case Insensitive) : ");
		scanf("%s", gender);
	}
	
	printf("Insert pet weight (not more than 80kg) : ");
	scanf("%lf", &weight);
	while(!(weight >= 0 && weight <= 80)){
		printf("Insert pet weight (not more than 80kg) : ");
		scanf("%lf", &weight);
	}
	
	// add node hash table
	push(petName, day, month, year, age, gender, weight);
	
	printf("Data has been recorded :D\n");
	printf("Press enter to continue");
	
	char prev = 0;
	while(1){
		char press = getchar();
		
		if(press == '\n' && prev == press){
			system("cls");
			petManagementSystem();
			break;
		}
		prev = press;
	}
}

// POP / DELETE [ to remove pet data ]
void pop(char name[]){
	// kita ambil key nya dulu
	int key = hashFunction(name);
	
	data* temp = head[key];
	
	// jika data tidak ketemu
	if(head[key] == NULL){
		printf("Name are not available on the list !\n");
		removePetMenu();
		// nanti minta input lagi!! [ bisa pake function ]
	}
	if(strcmp(head[key]->nama, name) == 0){
		// pindahin pointer head nya ke next node.
		head[key] = head[key]->next;
		// hapus temp nya
		temp = NULL;
		// free memory yang dipake buat nampung temp
		free(temp);
		// setelah delete :
		printf("Pet has been removed!");
		system("cls");
		return petManagementSystem();
	}
	
	// selama name yang ada di next node != text yang mau dihapus
	while(temp->next != NULL && strcmp(temp->next->nama, name) != 0){
		temp = temp->next;
	}
	
	data *wantToDelete = temp->next;
	temp->next = temp->next->next;
	free(wantToDelete);
}

// Menu : Remove Pet
void removePetMenu(){
	int checker = 0;
	
	for(int i=0;i<SIZE;i++){
		if(head[i] != NULL){
			// printf("No %d\n", i);
			printf("===================\n");
			printf("|       Pet List     |\n");
			printf("===================\n");
			data* curr = head[i];
			while(curr != NULL){
				printf("| %s             |\n", curr->nama);
				printf("====================================\n");
				
				curr = curr->next;
			}
			checker = 1;
		}
	}
	
	// if there are no data.
	if(checker != 1){
		printf("Theres no pet yet :D\n");
	}
	
	printf("Please input pet name to be removed [0 to exit]...");
	
	char inputPetNameToDelete[255];
	getchar();
	
	scanf("%[^\n]", inputPetNameToDelete);
	getchar();
	if(strcmp(inputPetNameToDelete, "0") == 0){
		system("cls");
		petManagementSystem();
	}
	else{
		pop(inputPetNameToDelete);
	}

}

// 1. Pet Management
void petManagementSystem(){
	int inputPadaMenuPetManagementSystem;
	
	do{
		printf("Welcome to Pet Management System\n");
		printf("=================\n");
		printf("1. Add a new pet\n");
		printf("2. Remove a pet\n");
		printf("3. Back\n");
	
		printf("Choose [1-3] >> ");
	
		scanf("%d", &inputPadaMenuPetManagementSystem);
		
		switch(inputPadaMenuPetManagementSystem){
			case 1:{
				system("cls");
				addPetMenu();
				break;
			}
			case 2:{
				system("cls");
				removePetMenu();
				break;
			}
			case 3:{
				system("cls");
				menuPetShop();
				break;
			}
			default:{
				printf("\nMenu dengan angka tersebut tidak tersedia!!\n");
				printf("Masukan angka 1 / 2 / 3!\n");
				printf("\n");
				break;
			}
		}
	}while(inputPadaMenuPetManagementSystem != 3);
}

// 2. View Pet
void viewAllPet(){
	int checker = 0;
	for(int i=0;i<SIZE;i++){
		if(head[i] != NULL){
			printf("No %d\n", i);
			data* curr = head[i];
			while(curr != NULL){
				printf("Pet Name    : %s\n", curr->nama);
				printf("Pet DOB     : %d-%d-%d\n", curr->hari, curr->bulan, curr->tahun);
				printf("Pet Age     : %s\n", curr->umur);
				printf("Pet Sex     : %s\n", curr->jenisKelamin);
				printf("Pet Weight  : %.2lf\n", curr->berat);
				printf("====================================\n");
				
				curr = curr->next;
			}
			checker = 1;
		}
	}
	
	// if there are no data.
	if(checker != 1){
		printf("Theres no pet yet :D\n");
	}
	
	printf("Press enter to continue...");
	
	// press enter to back to Menu
	char prev = 0;
	while(1){
		char press = getchar();
		if(press == '\n' && prev == press){
			system("cls");
			menuPetShop();
			break;
		}
		prev = press;
	}
}

// 3. Exit
void exit(){
	printf("Terima kasih dan sampai jumpa kembali!\n");
}

void menuPetShop(){
	int inputPadaMenuPetShop;

	/*
	do{
		printf("%s", "PetShop\n");
		printf("=================\n");
		printf("1. Pet Management\n");
		printf("2. View all pet\n");
		printf("3. Exit\n");
	
		printf("Choose [1-3] >> ");
	
		scanf("%d", &inputPadaMenuPetShop);
	
		switch(inputPadaMenuPetShop){
			case 1:{
				system("cls");
				petManagementSystem();
				break;
			}
			case 2:{
				system("cls");
				viewAllPet();
				break;
			}
			case 3:{
				exit();
				break;
			}
			default:{
				printf("\nMenu dengan angka tersebut tidak tersedia!!\n");
				printf("Masukan angka 1 / 2 / 3!\n");
				printf("\n");
				break;
			}
		}
	}while(inputPadaMenuPetShop != 3);
	*/
	
	while(inputPadaMenuPetShop != 3){
		printf("%s", "PetShop\n");
		printf("=================\n");
		printf("1. Pet Management\n");
		printf("2. View all pet\n");
		printf("3. Exit\n");
	
		printf("Choose [1-3] >> ");
	
		scanf("%d", &inputPadaMenuPetShop);
	
		switch(inputPadaMenuPetShop){
			case 1:{
				system("cls");
				petManagementSystem();
				break;
			}
			case 2:{
				system("cls");
				viewAllPet();
				break;
			}
			case 3:{
				system("cls");
				exit();
				break;
			}
			default:{
				printf("\nMenu dengan angka tersebut tidak tersedia!!\n");
				printf("Masukan angka 1 / 2 / 3!\n");
				printf("\n");
				break;
			}
		}
	}
	
}

int main(){
	
	menuPetShop();
	
		
	return 0;
}
