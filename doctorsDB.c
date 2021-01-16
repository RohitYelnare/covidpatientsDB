//U19CS050
/*Program to manage covid doctor data of Surat city using a single text file
through the menu options*/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include "structures.h"


//checks whether patient ID is UNIQUE or not
int chkunique(int num){	
    FILE *ogfile;
	ogfile = fopen("ddetails.txt","r");
	struct ddetails tmp;
	while(fread(&tmp,sizeof(struct ddetails),1,ogfile)){
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
	while(1){//doesnt ask for ID if record is being modified
		printf("Enter Doctor ID: ");
		scanf("%d", &querydoc.id);
		if(chkunique(querydoc.id)){
			break;
		}
		printf("Error: Invalid ID / ID already exists ID must be unique\n");
	}
	
	//first name
	printf("Enter doctor's firstname: ");
	scanf("%s", querydoc.fname);
	for(i = 0; querydoc.fname[i]; i++){
    	querydoc.fname[i] = tolower(querydoc.fname[i]);
	}
	
	//last name
	printf("Enter doctor's lastname: ");
	scanf("%s", querydoc.lname);
	for(i = 0; querydoc.lname[i]; i++){
    	querydoc.lname[i] = tolower(querydoc.lname[i]);
	}
	
	//age
	while(1){
		printf("Enter doctor's age: ");
		scanf("%d", &querydoc.age);
		if(querydoc.age > 18 && querydoc.age < 120)
		break;
		printf("Error: Invalid Age Entered\n");
	}
	
	//gender
	while(1){
		fflush(stdin);
		printf("Enter gender(M/F): ");
		scanf("%c", &querydoc.gender);
		if(querydoc.gender=='M' || querydoc.gender=='F')
		break;
		printf("Error: Enter either M or F\n");
	}
	
	//area
	while(1){
		printf("Enter area code: ");
		scanf("%d", &querydoc.area);
		if(querydoc.area >=394000 && querydoc.area <= 395999)
		break;
		printf("Error: Invalid area code entered\n");
	}
}

//Used at various places to print details of patient record
void printdetails(struct ddetails tmp){
	printf("Doctor ID: %d\n", tmp.id);
	printf("Name: %s %s\n", tmp.fname, tmp.lname);
	printf("Gender: %c\n", tmp.gender);
	printf("Age: %d\n", tmp.age);
	printf("ZIP Code: %d\n", tmp.area);
}

//adds doctor record to main file
void addrec(){
	inputdetails();
	FILE *file;
	file = fopen ("ddetails.txt", "a");
	fwrite (&querydoc, sizeof(struct ddetails), 1, file);
	fclose(file);
}

void totalpatientcount(){
    int patientcount = 0; 
    FILE* ogfile;
    FILE* ogfiledoc;
    FILE* relationdoc;
    ogfiledoc = fopen("ddetails.txt","r");
    struct pdetails tmppatient;
    struct ddetails tmpdoc;
    struct relation reln;
    while(fread(&tmpdoc,sizeof(struct ddetails),1,ogfiledoc)){
    	ogfile = fopen("pdetails.txt","r");
    	relationdoc = fopen("relations.txt","r");
        while(fread(&reln,sizeof(struct relation),1,relationdoc))
            if(reln.docid == tmpdoc.id){
                while(fread(&tmppatient,sizeof(struct pdetails),1,ogfile))
                    if (reln.patientid == tmppatient.id)
                        patientcount++;
            }
        printf("Doctor (ID: %d) has %d patients.\n",tmpdoc.id,patientcount);
        patientcount = 0;
    	fclose(ogfile);
    	fclose(relationdoc);
    }
    fclose(ogfiledoc);
}

void gender_count(){   
    int male = 0 , female = 0; 
    FILE* ogfile;
    FILE* ogfiledoc;
    FILE* relationdoc;
    ogfiledoc = fopen("ddetails.txt","r");
    struct pdetails tmppatient;
    struct ddetails tmpdoc;
    struct relation reln;
    while(fread(&tmpdoc,sizeof(struct ddetails),1,ogfiledoc)){
    	ogfile = fopen("pdetails.txt","r");
    	relationdoc = fopen("relations.txt","r");
        while(fread(&reln,sizeof(struct relation),1,relationdoc))
            if(reln.docid == tmpdoc.id){
                while(fread(&tmppatient,sizeof(struct pdetails),1,ogfile))
                    if (tmppatient.gender=='M' && reln.patientid == tmppatient.id)
                        male++;
                    else if (tmppatient.gender=='F' && reln.patientid == tmppatient.id) 
                        female++;

            }
        printf("Doctor (ID: %d) has %d female and %d male patient(s).\n",tmpdoc.id,female,male);
        male = 0;
        female = 0;
    	fclose(ogfile);
    	fclose(relationdoc);
    }
    fclose(ogfiledoc);
}

void age_count(){
	int i, zip, flag, agecount[100][2], distinct=0, patientcount=0;
    FILE* ogfile;
    FILE* ogfiledoc;
    FILE* relationdoc;
    ogfiledoc = fopen("ddetails.txt","r");
    struct pdetails tmppatient;
    struct ddetails tmpdoc;
    struct relation reln;
    while(fread(&tmpdoc,sizeof(struct ddetails),1,ogfiledoc)){
    	ogfile = fopen("pdetails.txt","r");
    	relationdoc = fopen("relations.txt","r");
        while(fread(&reln,sizeof(struct relation),1,relationdoc))
            if(reln.docid == tmpdoc.id){
                while(fread(&tmppatient,sizeof(struct pdetails),1,ogfile))
                    if (reln.patientid == tmppatient.id){
                    	patientcount++;
						zip = tmppatient.age;
						flag=0;
						for(i=0; i<distinct; i++){
							if(agecount[i][0]==zip){
								agecount[i][1]++;
								flag=1;
							}
						}	
						if(flag==0){
							agecount[distinct][0]=zip;
							agecount[distinct][1]=1;
							distinct++;
						}                  	
					}
            }
        printf("Doctor (ID: %d) has %d patients.\n",tmpdoc.id,patientcount);
        for(i=0; i<distinct; i++){
			printf("Person(s) with age of %d: %d\n", agecount[i][0], agecount[i][1]);
		}
        patientcount = 0;
        distinct = 0;
    	fclose(ogfile);
    	fclose(relationdoc);
    }
    fclose(ogfiledoc);
}

void area_count(){
	int i, zip, flag, areacount[100][2], distinct=0, patientcount=0;
    FILE* ogfile;
    FILE* ogfiledoc;
    FILE* relationdoc;
    ogfiledoc = fopen("ddetails.txt","r");
    struct pdetails tmppatient;
    struct ddetails tmpdoc;
    struct relation reln;
    while(fread(&tmpdoc,sizeof(struct ddetails),1,ogfiledoc)){
    	ogfile = fopen("pdetails.txt","r");
    	relationdoc = fopen("relations.txt","r");
        while(fread(&reln,sizeof(struct relation),1,relationdoc))
            if(reln.docid == tmpdoc.id){
                while(fread(&tmppatient,sizeof(struct pdetails),1,ogfile))
                    if (reln.patientid == tmppatient.id){
                    	patientcount++;
						zip = tmppatient.area;
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
            }
        printf("Doctor (ID: %d) has %d patients.\n",tmpdoc.id,patientcount);
        for(i=0; i<distinct; i++){
			printf("Person(s) in ZIP code %d: %d\n", areacount[i][0], areacount[i][1]);
		}
        patientcount = 0;
        distinct = 0;
    	fclose(ogfile);
    	fclose(relationdoc);
    }
    fclose(ogfiledoc);
}

//driver function
int main(){
	int carryon=1, req, subreq;
	while(carryon!=0){
		printf("Which operation would you like to perform?\n(1)Add\n(2)Display list of doctors treating number of patients\n(4)Summary Reports\n: ");
		scanf("%d", &req);
		switch(req){
		case 1: addrec();
		    	break;
		case 2: totalpatientcount();
		    	break;
		    	
		case 4: printf("Doctor wise Summary reports: (1)Count of patients/(2)Gender wise count/(3)Age wise count/(4)Area wise count:");
				scanf("%d", &subreq);
				switch(subreq){
				case 1: totalpatientcount();
						break;
				case 2: gender_count();
		    			break;
		    	case 3: age_count();
		    			break;
		    	case 4: area_count();
		    			break;
				}
				break;
		default:printf("Invalid option!\n");
				break;
		}
			printf("Would you like to continue?(1/0)");
			scanf("%d", &carryon);
    }
    
}

