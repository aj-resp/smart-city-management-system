#pragma once

const int MAX_STR = 100;
const int MAX_FACULTY = 500;
const int MAX_STUDENTS = 2000;
// Location structure
struct Location {
    double lat;
    double lon;
};

// Bus Stop
struct BusStop
{
    int id;
    char name[MAX_STR];
    Location location;
};

// Route Node -for linked list of stops in a bus route
struct RouteNode // we made it as a list cuz stops are connected linerarly, stop 5 cant be linekd with stop 1 
{   
    int stopIndex;
    RouteNode* next;

    RouteNode(int idx) : stopIndex(idx), next(nullptr) {}
};

// Bus
struct Bus
{
    char busNo[10];
    char company[MAX_STR];
    int currentStopIndex;
    RouteNode* routeHead;
    RouteNode* routeTail;
};

// School
struct School
{
    char schoolID[10];      
    char name[MAX_STR];
    char sector[20];      
    int ranking;           // rating * 10
    double lat;
    double lon;
    char subjects[5][50];
    int subjectCount;
};

// Hospital
// Hospital
struct Hospital {
    char hospitalID[10];
    char name[MAX_STR];
    char sector[20];
    Location location;
    int emergencyBeds;
    char specializations[5][50];  // Array of specializations
    int specializationCount;       //  Number of specializations
};


struct PharmacyRecord {
    char pharmacyID[10];
    char pharmacyName[100];
    char sector[20];
    char medicineName[100];
    char formula[100];
    double price;
};

struct Citizen {
    char cnic[20];
    char name[MAX_STR];
    int  age;

    char sector[20];   // e.g. "G-10"
    char street[20];   // e.g. "22"
    char houseNo[20];  // e.g. "180"

    char occupation[50];
    char gender;       // 'M'/'F'

    int sectorLetterIndex;
    int sectorNumber;
    int subSector;
    int houseRow;
    int houseCol;
};



// Product struct (for commercial sector)
struct Product {
    char name[MAX_STR];
    char category[50];
    int price;
};

//  Mall struct
struct Mall {
    char mallID[10];
    char name[MAX_STR];
    Location location;
    Product products[50];
    int productCount;
};

//Public Facility struct
struct PublicFacility
{
    char facilityID[10];
    char name[MAX_STR];
    char type[30];  // "Mosque", "Park", "Water Cooler"
    Location location;
};

struct StudentOnBus {
    int busIndex;
    char studentName[MAX_STR];
    char pickupStop[MAX_STR];
    char dropoffStop[MAX_STR];
};

struct SchoolBusTracker {
    StudentOnBus* studentsOnBuses[50];
    int count[50];
    int totalStudents;
};

//  Airport/Rail Integration
struct AirportStation
{
    char stationID[10];
    char name[MAX_STR];
    char type[20];  // "Airport" or "Railway"
    Location location;
    char connectedStops[50][10];
    int connectionCount;
};

// Doctor structure
struct Doctor
{
    char doctorID[10];
    char name[MAX_STR];
    char specialization[50];
    char hospitalID[10];  // Which hospital they work at
    int experience;       // Years of experience
};

// Patient Record structure
struct PatientRecord
{
    char patientID[10];
    char name[MAX_STR];
    char cnic[20];
    int age;
    char disease[100];
    char assignedDoctorID[10];
    char hospitalID[10];
    char admissionDate[20];
    bool isAdmitted;
};





struct FacultyMember 
{
    char facultyID[20];
    char name[MAX_STR];
    char schoolID[MAX_STR];    // Reference to which school
    int schoolIndex;           // Index in schools[] array
    char department[50];
    char subject[50];
    int experience;            // Years of experience
};

// Student
struct Student 
{
    char studentID[20];
    char name[MAX_STR];
    char schoolID[MAX_STR];    // Reference to which school
    int schoolIndex;           // Index in schools[] array
    char parentName[MAX_STR];
    char className[50];
    int rollNumber;
    int age;
};


// Sector House Map Structure
struct SectorHouseMap 
{
    int letterIndex;          // 0 for A, 1 for B, etc.
    int sectorNumber;         // 1-14
    int subSector;            // 1-4
    int** houseGrid;          // 2D array representing houses
    int rows;                 // Typically 10x10 or similar
    int cols;
    int occupiedCount;        // How many houses are occupied
};

// Sector Node for Tree
struct SectorTreeNode
{
    char letter;                     // A, B, C, etc.
    SectorTreeNode* numberChildren[15]; // 0-14 (0 unused for simplicity)
    SectorHouseMap* sectorMaps[15][5]; // [1-14][1-4] maps
};




