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

struct relation{
	int patientid;
	int docid;
}queryrelation;

struct ddetails{
	int id;
	char fname[20];
	char lname[20];
	int age;
	char gender;
	int area;
}querydoc;
