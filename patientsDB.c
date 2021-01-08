#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct pdetails{
	int id;
	char fname[20];
	char lname[20];
	int age;
	int adm[3];
	int dis[3];
	char gender;
	int area;
}query, modtmp;

char userletter;
int userdate[3], usermonth, usertruedate;

int chkleap(int year){
	year+=2000;
	if(year%400==0 || (year%4==0 && year%100!=0))
	return 1;
	else
	return 0;
}
int chkunique(int num){	
    FILE *ogfile;
	ogfile = fopen("pdetails.txt","r");
	struct pdetails tmp;
	while(fread(&tmp,sizeof(struct pdetails),1,ogfile)){
		if(num == tmp.id){
			   	return 0;
		}
	}
	return 1;	
}

void month_ad_31(){   
	if (query.adm[0] < 1 || query.adm[0] > 31){
		printf("Wrong date");
		return;
	}
}

void month_ad_30(){   
	if (query.adm[0] < 1 || query.adm[0] > 30){
		printf("Wrong date");
		return;
	}
}

void month_dis_31(){   
	if (query.adm[0] < 1 || query.adm[0] > 31){
		printf("Wrong date");
		return;
	}
}

void month_dis_30(){   
	if (query.adm[0] < 1 || query.adm[0] > 30){
		printf("Wrong date");
		return;
	}
}

void inputdetails(){
	int i;
	
	while(1){
		printf("Enter ID: ");
		scanf("%d", &query.id);
		if(chkunique(query.id))
		break;
		printf("Error: ID already exists. ID must be unique\n");
	}

	printf("Enter patient's firstname: ");
	scanf("%s", query.fname);
	for(i = 0; query.fname[i]; i++){
    	query.fname[i] = tolower(query.fname[i]);
	}
	
	printf("Enter patient's lastname: ");
	scanf("%s", query.lname);
	for(i = 0; query.lname[i]; i++){
    	query.lname[i] = tolower(query.lname[i]);
	}
	
	while(1){
		printf("Enter patient's age: ");
		scanf("%d", &query.age);
		if(query.age > 0 && query.age < 120)
		break;
		printf("Error: Invalid Age Entered\n");
	}
	
	while(1){
		fflush(stdin);
		printf("Enter gender(M/F): ");
		scanf("%c", &query.gender);
		if(query.gender=='M' || query.gender=='F')
		break;
		printf("Error: Enter either M or F\n");
	}
	
	while(1){
		while(1){
			printf("Enter Admission Month(mm): ");
			scanf("%d", &query.adm[1]);
			if (query.adm[1] >= 1 && query.adm[1] <= 12)
			break;
			printf("Wrong Month Entered");
		}
		
		while(1){
			printf("Enter Admission Year(yy): ");
				scanf("%d", &query.adm[2]);
			if(query.adm[2]>=20 && query.adm[2]<=99)
			break;
			printf("Error: Invalid year(Years before 2020 not applicable)");	
		}
	
			while(1){
			printf("Enter Admission Day(dd): ");
			scanf("%d", &query.adm[0]);
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
	
		while(1){
			printf("Enter Discharge Month(mm): ");
			scanf("%d", &query.dis[1]);
			if (query.dis[1] >= 1 && query.dis[1] <= 12)
			break;
			printf("Wrong Month Entered");
		}
	
		while(1){
			printf("Enter Discharge Year(yy): ");
			scanf("%d", &query.dis[2]);
			if(query.dis[2]>=20 && query.dis[2]<=99)
			break;
			printf("Error: Invalid year(Years before 2020 not applicable)");	
		}
		
		while(1){
			printf("Enter Discharge Day(dd): ");
			scanf("%d", &query.dis[0]);
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
		if(numofdays(query.adm)<numofdays(query.dis))
		break;
		printf("Error: Admission Date cannot be after Discharge date\n");	
	}
}

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

void megafunc(int switchreq){ 
    char ch;
	FILE *ogfile;
	FILE *writeonly;
	ogfile=fopen("pdetails.txt","r");
	writeonly=fopen("ordering.txt","w");
	while( ( ch = fgetc(ogfile) ) != EOF )
        fputc(ch, writeonly);
    fseek(ogfile, 0 , SEEK_SET);    
    fclose(writeonly);
	fclose(ogfile);
	int count = totalcount();
	struct pdetails temp;
	while (count!=0){   
		ogfile=fopen("pdetails.txt","r");
		fread(&temp,sizeof(struct pdetails),1,ogfile);
		fclose(ogfile);
		ogfile=fopen("pdetails.txt","r");
		switch(switchreq){
			case 0: while(fread(&query,sizeof(struct pdetails),1,ogfile)){
			   			if (strcmp(query.fname,temp.fname)<0){
			   				temp = query;
						}
					}
					break;
			case 1: while(fread(&query,sizeof(struct pdetails),1,ogfile)){
			   			if (strcmp(query.lname,temp.lname)<0){
			   				temp = query;
						}
					}
					break;
			case 2: while(fread(&query,sizeof(struct pdetails),1,ogfile)){
			   			if (query.age<temp.age){
			   				temp = query;
						}
					}
					break;
			case 3: while(fread(&query,sizeof(struct pdetails),1,ogfile)){
			   			if (numofdays(query.adm)<numofdays(temp.adm)){
			   				temp = query;
						}
					}
					break;
			case 4: while(fread(&query,sizeof(struct pdetails),1,ogfile)){
			   			if (strcmp(query.fname,temp.fname)>0){
			   				temp = query;
						}
					}
					break;
			case 5: while(fread(&query,sizeof(struct pdetails),1,ogfile)){
			   			if (strcmp(query.lname,temp.lname)>0){
			   				temp = query;
						}
					}
					break;
			case 6: while(fread(&query,sizeof(struct pdetails),1,ogfile)){
			   			if (query.age>temp.age){
			   				temp = query;
						}
					}
					break;
			case 7: while(fread(&query,sizeof(struct pdetails),1,ogfile)){
			   			if (numofdays(query.dis)>numofdays(temp.dis)){
			   				temp = query;
						}
					}
					break;
		}
		fclose(ogfile);
		printf("%s\n", temp.fname);
		ogfile=fopen("pdetails.txt","r");
		writeonly=fopen("copy.txt","w");
		while(fread(&query,sizeof(struct pdetails),1,ogfile)){
			if(query.id!=temp.id){
				fwrite(&query,sizeof(struct pdetails),1,writeonly);
			}
		}
		count--;
		fclose(ogfile);
		fclose(writeonly);
		remove("pdetails.txt");
		rename("copy.txt","pdetails.txt");
	}
	remove("pdetails.txt");
	rename("ordering.txt","pdetails.txt");
}

void seventhfunc(int switchreq){ 
	FILE *ogfile;
	int i;
	ogfile=fopen("pdetails.txt","r");
	switch(switchreq){
	case 0:	while(fread(&query, sizeof(struct pdetails), 1, ogfile)){
				if(query.fname[0]-userletter<=10){
					printf("%s\n", query.fname);
				}
			}
			break;
	case 1:	while(fread(&query, sizeof(struct pdetails), 1, ogfile)){
				if(numofdays(query.adm)-usertruedate<=10){
					printf("%s\n", query.fname);
				}
			}
			break;
	case 2:	for(i=0; i<=5; i++){
				if(usermonth==13){
					usermonth=1;
				}
				fseek(ogfile, 0 , SEEK_SET); 
				while(fread(&query, sizeof(struct pdetails), 1, ogfile)){
					if(usermonth==query.adm[1]){
						printf("%s\n", query.fname);
					}
				}
				usermonth++;
			}
			break;
	}
	fclose(ogfile);
}

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
}

void addrec(){
	inputdetails();
	FILE *file;
	file = fopen ("pdetails.txt", "a");
	fwrite (&query, sizeof(struct pdetails), 1, file);
	fclose(file);
}


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

void modrec(){
	int n,flag=0;
	printf("\nEnter patient ID to be modify : ");
	scanf("%d",&n);
	FILE *ogfile;
	FILE *tmpfile;
	ogfile=fopen("pdetails.txt","r");
	tmpfile=fopen("tmp.txt","w");
	while(fread(&query,sizeof(struct pdetails),1,ogfile)){
		if(query.id==n){
			   	flag = 1;
		}
	}
    fclose(ogfile);
    ogfile=fopen("pdetails.txt","r");
	if(flag==0)
		printf("No such ID found!\n");
	else{
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

int gendercount(){
	struct pdetails tmp;
	int gendercount=0;
	FILE *file;
	file=fopen("pdetails.txt", "r");
	while(fread(&tmp, sizeof(struct pdetails), 1, file)){
		if(tmp.gender=='F'){
			gendercount++;
		}
	}
	fclose(file);
	return gendercount;
}
void agecount(){
	struct pdetails tmp;
	int i,agecount[125]={0};
	FILE *file;
	file=fopen("pdetails.txt", "r");
	while(fread(&tmp, sizeof(struct pdetails), 1, file)){
		agecount[tmp.age]++;
	}
	for(i=0; i<125; i++){
		if(agecount[i]!=0)
		printf("There is/are %d people of age %d\n", agecount[i], i);
	}
	fclose(file);
}
void areacount(){
	int i=0,areacount[100][2];
	struct pdetails tmp;
}
int main(){
	int carryon=1, req, subreq;
	while(carryon!=0){
		printf("Which operation would you like to perform?[(1)Add/(2)Delete/(3)Modify/(4)Display summary reports/(5)List in ascending order/(6)List in descending order/(7)List records for specific range/(8)Seperate male and female into different files]");
		scanf("%d", &req);
		switch(req){
		case 1: addrec();
		    	break;
		case 2:	delrec();
				break;
		case 3:	modrec();
				break;
		case 4: printf("(1)Count of patients/(2)Count(based on gender)/(3)Age wise count/(4)Area wise count: ");
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
		case 5: printf("List all Records in ascending order according to (1)First Name/(2)Last Name/(3)Age/(4)Admission Date: ");
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
		case 6: printf("List all Records in descending order according to (1)First Name/(2)Last Name/(3)Age/(4)Discharge Date: ");
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
		case 7: printf("List Records in specific range(1)First Name/(2)Admission date/(3)Month: ");
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

