//U19CS050
/*Program to manage covid patient data of Surat city using a single text file
through the menu options*/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

struct pdetails{
	int id;
	char fname[20];
	char lname[20];
	int age;
	int adm[3];
	int dis[3];
	char gender;
	int area;
}query, modtmp, saviour;

char userletter;
int userdate[3], usermonth, usertruedate, modify=0;

//checks whether year is leap or not
int chkleap(int year){
	year+=2000;
	if(year%400==0 || (year%4==0 && year%100!=0))
	return 1;
	else
	return 0;
}

//checks whether patient ID is UNIQUE or not
int chkunique(int num){	
    FILE *ogfile;
	ogfile = fopen("pdetails.txt","r");
	struct pdetails tmp;
	while(fread(&tmp,sizeof(struct pdetails),1,ogfile)){
		if(num == tmp.id){
			fclose(ogfile);
			return 0;
		}
	}
	fclose(ogfile);
	return 1;	
}

//Helper function to input all details of a record
void inputdetails(){
	int i;
	//while loops are used for error handling. User is asked for input until valid input is received
	//id
	while(1 && !modify){//doesnt ask for ID if record is being modified
		printf("Enter ID: ");
		scanf("%d", &query.id);
		if(chkunique(query.id)){
			modify=0;
			break;
		}
		printf("Error: Invalid ID / ID already exists ID must be unique\n");
	}
	
	//first name
	printf("Enter patient's firstname: ");
	scanf("%s", query.fname);
	for(i = 0; query.fname[i]; i++){
    	query.fname[i] = tolower(query.fname[i]);
	}
	
	//last name
	printf("Enter patient's lastname: ");
	scanf("%s", query.lname);
	for(i = 0; query.lname[i]; i++){
    	query.lname[i] = tolower(query.lname[i]);
	}
	
	//age
	while(1){
		printf("Enter patient's age: ");
		scanf("%d", &query.age);
		if(query.age > 0 && query.age < 120)
		break;
		printf("Error: Invalid Age Entered\n");
	}
	
	//gender
	while(1){
		fflush(stdin);
		printf("Enter gender(M/F): ");
		scanf("%c", &query.gender);
		if(query.gender=='M' || query.gender=='F')
		break;
		printf("Error: Enter either M or F\n");
	}
	
	//area
	while(1){
		printf("Enter area code: ");
		scanf("%d", &query.area);
		if(query.area >=394000 && query.area <= 395999)
		break;
		printf("Error: Invalid area code entered\n");
	}
	
	//Admission Date
	while(1){
		//Admission month
		while(1){
			printf("Enter Admission Month(mm): ");
			scanf("%d", &query.adm[1]);
			if (query.adm[1] >= 1 && query.adm[1] <= 12)
			break;
			printf("Wrong Month Entered\n");
		}
		
		//Admission year
		while(1){
			printf("Enter Admission Year(yy): ");
				scanf("%d", &query.adm[2]);
			if(query.adm[2]>=20 && query.adm[2]<=99)
			break;
			printf("Error: Invalid year(Years before 2020 not applicable)\n");	
		}
		
		//Admission day
		while(1){
			printf("Enter Admission Day(dd): ");
			scanf("%d", &query.adm[0]);
			//nested if-else to check whether day lies within given month
			if(query.adm[1]==2){
				if(chkleap(query.adm[2])){
					if(query.adm[0]>=1 && query.adm[0]<=29)
					break;
					printf("Error: Invalid Date\n");
				}else{
					if(query.adm[0]>=1 && query.adm[0]<=28)
					break;
					printf("Error: Invalid Date\n");
				}
			}else if(query.adm[1]==2 || query.adm[1]==4 || query.adm[1]==6 || query.adm[1]==9 || query.adm[1]==11){
				if(query.adm[1]>=1 && query.adm[1]<=30)
				break;
				printf("Error: Invalid Date\n");
			}else{
				if(query.adm[1]>=1 && query.adm[1]<=31)
				break;
				printf("Error: Invalid Date\n");
			}
		}
		
		//Discharge Month
		while(1){
			printf("Enter Discharge Month(mm): ");
			scanf("%d", &query.dis[1]);
			if (query.dis[1] >= 1 && query.dis[1] <= 12)
			break;
			printf("Wrong Month Entered");
		}
	
		//Discharge Year
		while(1){
			printf("Enter Discharge Year(yy): ");
			scanf("%d", &query.dis[2]);
			if(query.dis[2]>=20 && query.dis[2]<=99)
			break;
			printf("Error: Invalid year(Years before 2020 not applicable)");	
		}
		
		//Discharge Day
		while(1){
			printf("Enter Discharge Day(dd): ");
			scanf("%d", &query.dis[0]);
			//nested if-else to check whether day lies within given month
			if(query.dis[1]==2){
				if(chkleap(query.dis[2])){
					if(query.dis[0]>=1 && query.dis[0]<=29)
					break;
					printf("Error: Invalid Date\n");
				}else{
					if(query.dis[0]>=1 && query.dis[0]<=28)
					break;
					printf("Error: Invalid Date\n");
				}
			}else if(query.dis[1]==2 || query.dis[1]==4 || query.dis[1]==6 || query.dis[1]==9 || query.dis[1]==11){
				if(query.dis[1]>=1 && query.dis[1]<=30)
				break;
				printf("Error: Invalid Date\n");
			}else{
				if(query.dis[1]>=1 && query.dis[1]<=31)
				break;
				printf("Error: Invalid Date\n");
			}
		}
		//checks whether admission date is not before discharge date
		if(numofdays(query.adm)<=numofdays(query.dis))
		break;
		printf("Error: Admission Date cannot be after Discharge date\n");	
	}
}

//helper function designed to return number of days given date is ahead of 1st Jan 2020
int numofdays(int date[]){
	int days=date[0]+(date[2]-20)*365;
	if(date[1]>=3 && date[2]==20){
		days++;
	}else if(date[1]>=3){
		days+=((date[2]-20+4)/4);
	}
	switch(date[1]){
		case 1: days+=0;
				break;
		case 2: days+=31;
				break;
		case 3: days+=59;
				break;
		case 4: days+=90;
				break;
		case 5: days+=120;
				break;
		case 6: days+=151;
				break;
		case 7: days+=181;
				break;
		case 8: days+=212;
				break;
		case 9: days+=243;
				break;
		case 10: days+=273;
				break;
		case 11: days+=304;
				break;
		case 12: days+=334;
				break;
	}
	return --days;
}

//Used at various places to print details of patient record
void printdetails(struct pdetails tmp){
	printf("Patient ID: %d\n", tmp.id);
	printf("Name: %s %s\n", tmp.fname, tmp.lname);
	printf("Gender: %c\n", tmp.gender);
	printf("Age: %d\n", tmp.age);
	printf("Admission Date(ddmmyyyy): %2d-%2d-%d\n", tmp.adm[0], tmp.adm[1], tmp.adm[2]+2000);
	printf("Discharge Date(ddmmyyyy): %2d-%2d-%d\n", tmp.dis[0], tmp.dis[1], tmp.dis[2]+2000);
	printf("ZIP Code: %d\n", tmp.area);
}

//Lists all records according to order choosen by user(Point 5 and 6) 
void megafunc(int switchreq){ 
    char ch;
	FILE *ogfile;
	FILE *tmpfile;
	ogfile=fopen("pdetails.txt","r");
	tmpfile=fopen("ordering.txt","w");
//	while( ( ch = fgetc(ogfile) ) != EOF )
//        fputc(ch, tmpfile);//created a copy of original file(pdetails.txt) in ordering.txt
    while(fread(&query,sizeof(struct pdetails),1,ogfile)){
		fwrite(&query,sizeof(struct pdetails),1,tmpfile);
	}
	fseek(ogfile, 0 , SEEK_SET);    
    fclose(tmpfile);
	fclose(ogfile);
	int count = totalcount(), index=1;
	struct pdetails temp;
	while (count!=0){   
		ogfile=fopen("pdetails.txt","r");
		fread(&temp,sizeof(struct pdetails),1,ogfile);
		fclose(ogfile);
		ogfile=fopen("pdetails.txt","r");
		printf("\nSr No. %d:\n", index++);
		switch(switchreq){
			//5a: List all records in ascending order according to patient's first name
			case 0: while(fread(&query,sizeof(struct pdetails),1,ogfile)){
			   			if (strcmp(query.fname,temp.fname)<0){
			   				temp = query;
						}
					}
					break;
			//5b: List all records in ascending order according to patient's last name
			case 1: while(fread(&query,sizeof(struct pdetails),1,ogfile)){
			   			if (strcmp(query.lname,temp.lname)<0){
			   				temp = query;
						}
					}
					break;
			//5c: List all records in ascending order according to patient's age
			case 2: while(fread(&query,sizeof(struct pdetails),1,ogfile)){
			   			if (query.age<temp.age){
			   				temp = query;
						}
					}
					break;
			//5d: List all records in ascending order according to patient's admission date
			case 3: while(fread(&query,sizeof(struct pdetails),1,ogfile)){
			   			if (numofdays(query.adm)<numofdays(temp.adm)){
			   				temp = query;
						}
					}
					break;
			//6a: List all records in descending order according to patient's first name
			case 4: while(fread(&query,sizeof(struct pdetails),1,ogfile)){
			   			if (strcmp(query.fname,temp.fname)>0){
			   				temp = query;
						}
					}
					break;
			//6b: List all records in descending order according to patient's last name
			case 5: while(fread(&query,sizeof(struct pdetails),1,ogfile)){
			   			if (strcmp(query.lname,temp.lname)>0){
			   				temp = query;
						}
					}
					break;
			//6c: List all records in descending order according to patient's age
			case 6: while(fread(&query,sizeof(struct pdetails),1,ogfile)){
			   			if (query.age>temp.age){
			   				temp = query;
						}
					}
					break;
			//6d: List all records in descending order according to patient's discharge date
			case 7: while(fread(&query,sizeof(struct pdetails),1,ogfile)){
			   			if (numofdays(query.dis)>numofdays(temp.dis)){
			   				temp = query;
						}
					}
					break;
		}
		fclose(ogfile);
		printdetails(temp);
		//remove record stored in temp from pdetails
		ogfile=fopen("pdetails.txt","r");
		tmpfile=fopen("copy.txt","w");
		while(fread(&query,sizeof(struct pdetails),1,ogfile)){
			if(query.id!=temp.id){
				fwrite(&query,sizeof(struct pdetails),1,tmpfile);
			}
		}
		count--;
		fclose(ogfile);
		fclose(tmpfile);
		remove("pdetails.txt");
		rename("copy.txt","pdetails.txt");
	}
	remove("pdetails.txt");
	rename("ordering.txt","pdetails.txt");
}

//Lists all records according to range choosen by user(Point 7)
void seventhfunc(int switchreq){ 
	FILE *ogfile;
	int i;
	ogfile=fopen("pdetails.txt","r");
	switch(switchreq){
		//7a: prints all records with first letter of first name at most 10 letters ahead of user's given letter
	case 0:	while(fread(&query, sizeof(struct pdetails), 1, ogfile)){
				if(query.fname[0]-userletter<=10 && query.fname[0]-userletter>=0){
					printdetails(query);
				}
			}
			break;
		//7b: prints all records with admission dates at most 10 days ahead of user's given date
	case 1:	while(fread(&query, sizeof(struct pdetails), 1, ogfile)){
				if(numofdays(query.adm)-usertruedate<=10 && numofdays(query.adm)-usertruedate>=0){
					printdetails(query);
				}
			}
			break;
		//7b: prints all records with admission dates lying in next 5 months ahead of user's given month
	case 2:	for(i=0; i<=5; i++){
				if(usermonth==13){
					usermonth=1;
				}
				fseek(ogfile, 0 , SEEK_SET); 
				while(fread(&query, sizeof(struct pdetails), 1, ogfile)){
					if(usermonth==query.adm[1]){
						printdetails(query);
					}
				}
				usermonth++;
			}
			break;
	}
	fclose(ogfile);
}

//Point 8:Entering male and female patients records seperately in two seperate files
void seperate(){
	struct pdetails tmp;
	FILE *ogfile;
	FILE *mfile;
	FILE *ffile;
	ogfile = fopen("pdetails.txt", "r");
	mfile = fopen("mdetails.txt", "w");
	ffile = fopen("fdetails.txt", "w");
	while(fread(&query, sizeof(struct pdetails), 1, ogfile)){
		if(query.gender=='M'){
			fwrite(&query, sizeof(struct pdetails),1,mfile);
		}else{
			fwrite(&query, sizeof(struct pdetails),1,ffile);
		}
	}
	fclose(ogfile);
	fclose(mfile);
	fclose(ffile);
	printf("Two seperate files created successfully\n");
	mfile = fopen("mdetails.txt", "r");
	printf("Records of Male patients:\n");
	while(fread(&query, sizeof(struct pdetails), 1, mfile)){
		printdetails(query);
	}
	fclose(mfile);
	ffile = fopen("fdetails.txt", "r");
	printf("\nRecords of Female patients:\n");
	while(fread(&query, sizeof(struct pdetails), 1, ffile)){
		printdetails(query);
	}
	fclose(ffile);
}

//adds patient record to main file
void addrec(){
	inputdetails();
	FILE *file;
	file = fopen ("pdetails.txt", "a");
	fwrite (&query, sizeof(struct pdetails), 1, file);
	fclose(file);
}

//deletes record from main file
void delrec(){
	int n,flag=0;
	printf("Enter patient ID to be delete : ");
	scanf("%d",&n);
	FILE *ogfile;
	FILE *tmpfile;
	ogfile=fopen("pdetails.txt","r");
	tmpfile=fopen("tmp.txt","w");
	while(fread(&query,sizeof(struct pdetails),1,ogfile))
		if(query.id==n)
			flag = 1;
    fclose(ogfile);
    ogfile=fopen("pdetails.txt","r");
	if(flag==0){
		printf("No such ID found!\n");
	}else{
		//remove record with given ID from pdetails
		while(fread(&query,sizeof(struct pdetails),1,ogfile)){
			if(query.id!=n){
			   	fwrite(&query,sizeof(struct pdetails),1,tmpfile);
			}
		}
		printf("Deleted patient details with id: %d\n", n);
    }  
	fclose(ogfile);
	fclose(tmpfile);
	remove("pdetails.txt");
	rename("tmp.txt","pdetails.txt");
}

//modify record data of patient by patient ID
void modrec(){
	int n,idfound=0;
	printf("Enter patient ID to be modify : ");
	scanf("%d",&n);
	FILE *ogfile;
	FILE *tmpfile;
	ogfile=fopen("pdetails.txt","r");
	tmpfile=fopen("tmp.txt","w");
	while(fread(&query,sizeof(struct pdetails),1,ogfile)){
		if(query.id==n){
			   	idfound = 1;
		}
	}
    fclose(ogfile);
    ogfile=fopen("pdetails.txt","r");
	if(idfound==0)
		printf("No such ID found!\n");
	else{
		modify=1;
		struct pdetails tmp;
		inputdetails();
		while(fread(&tmp,sizeof(struct pdetails),1,ogfile)){
		   	if(tmp.id!=n){
			   	fwrite(&tmp,sizeof(struct pdetails),1,tmpfile);
			}else{
			   	fwrite(&query,sizeof(struct pdetails),1,tmpfile);
				printf("\nModified record!");
			}
		}
    }  
	fclose(ogfile);
	fclose(tmpfile);
	remove("pdetails.txt");
	rename("tmp.txt","pdetails.txt");
}

//returns total count of patients
int totalcount(){
	struct pdetails tmp;
	int totalcount=0;
	FILE *file;
	file=fopen("pdetails.txt", "r");
	while(fread(&tmp, sizeof(struct pdetails), 1, file)){
		totalcount++;
	}
	fclose(file);
	return totalcount;
}

//returns total count of male patients
int gendercount(){
	struct pdetails tmp;
	int gendercount=0;
	FILE *file;	
	file=fopen("pdetails.txt", "r");
	while(fread(&tmp, sizeof(struct pdetails), 1, file)){
		if(tmp.gender=='M'){
			gendercount++;
		}
	}
	fclose(file);
	return gendercount;
}

//prints age and respective count of all patients
void agecount(){
	struct pdetails tmp;
	int i,agecount[125]={0};
	FILE *ogfile;
	ogfile=fopen("pdetails.txt", "r");
	while(fread(&tmp, sizeof(struct pdetails), 1, ogfile)){
		agecount[tmp.age]++;
	}
	for(i=0; i<120; i++){
		if(agecount[i]!=0)
		printf("%d person(s) of age %d\n", agecount[i], i);
	}
	fclose(ogfile);
}

//prints area and respective count of all patients
void areacount(){
	struct pdetails tmp;
	int i,flag=0,iteration=0,count=0,areacount[100][2],zip, distinct=0;
	FILE *ogfile;
	ogfile=fopen("pdetails.txt", "r");
	while(fread(&tmp, sizeof(struct pdetails), 1, ogfile)){
		zip=tmp.area;
		flag=0;
		for(i=0; i<distinct; i++){
			if(areacount[i][0]==zip){
				areacount[i][1]++;
				flag=1;
			}
		}
		if(flag==0){
			areacount[distinct][0]=zip;
			areacount[distinct][1]=1;
			distinct++;
		}
	}
	for(i=0; i<distinct; i++){
		printf("Person(s) in ZIP code %d: %d\n", areacount[i][0], areacount[i][1]);
	}
	fclose(ogfile);
}

//driver function
int main(){
	int carryon=1, req, subreq;
	while(carryon!=0){
		printf("Which operation would you like to perform?\n(1)Add\n(2)Delete\n(3)Modify\n(4)Display summary reports\n(5)List in ascending order\n(6)List in descending order\n(7)List records for specific range\n(8)Seperate male and female into different files\n: ");
		scanf("%d", &req);
		switch(req){
		case 1: addrec();
		    	break;
		case 2:	delrec();
				break;
		case 3:	modrec();
				break;
		case 4: printf("(1)Count of patients\n(2)Count(based on gender)\n(3)Age wise count\n(4)Area wise count\n: ");
				scanf("%d", &subreq);
				switch(subreq){
				case 1: printf("Total number of patients: %d\n", totalcount());
		    			break;
				case 2:	printf("Male patients: %d Female patients: %d\n", gendercount(), totalcount()-gendercount());
						break;
				case 3:	agecount();
						break;
				case 4:	areacount();
						break;						
				default:printf("Invalid req!\n");
						break;
				}
				break;
		case 5: printf("List all Records in ascending order according to:\n(1)First Name\n(2)Last Name\n(3)Age\n(4)Admission Date\n: ");
				scanf("%d", &subreq);
				switch(subreq){
				case 1: megafunc(0);
		    			break;
				case 2:	megafunc(1);
						break;
				case 3:	megafunc(2);
						break;
				case 4:	megafunc(3);
						break;						
				default:printf("Invalid req!\n");
						break;
				}
				break;
		case 6: printf("List all Records in descending order according to:\n(1)First Name\n(2)Last Name\n(3)Age\n(4)Discharge Date\n: ");
				scanf("%d", &subreq);
				switch(subreq){
				case 1: megafunc(4);
		    			break;
				case 2:	megafunc(5);
						break;
				case 3:	megafunc(6);
						break;
				case 4:	megafunc(7);
						break;						
				default:printf("Invalid req!\n");
						break;
				}
				break;
		case 7: printf("List Records in specific range:\n(1)First Name\n(2)Admission date\n(3)Month\n: ");
				scanf("%d", &subreq);
				switch(subreq){
				case 1: printf("Enter first name: ");
						fflush(stdin);
						scanf("%c", &userletter);
						seventhfunc(0);
		    			break;
				case 2:	printf("Enter date:\ndd: ");
						scanf("%d", &userdate[0]);
						printf("mm: ");
						scanf("%d", &userdate[1]);
						printf("yy: ");
						scanf("%d", &userdate[2]);
						usertruedate = numofdays(userdate);
						seventhfunc(1);
						break;
				case 3:	printf("Enter month: ");
						scanf("%d", &usermonth);
						seventhfunc(2);
						break;
				default:printf("Invalid req!\n");
						break;
				}
				break;
		case 8: seperate();
				break;
		default:printf("Invalid req!\n");
				break;
			}
			printf("Would you like to continue?(1/0)");
			scanf("%d", &carryon);
    }
    
}

