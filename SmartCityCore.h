#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <ctime>
#include <cstdlib> 
#ifdef _WIN32
#include <windows.h>
#define SLEEP(ms) Sleep(ms)
#else
#include <unistd.h>
#define SLEEP(ms) usleep((ms) * 1000)
#endif

#include <iostream>
using namespace std;


#include "LinkedList.h"
#include "Stack.h"
#include "Queue.h"
#include "MinHeap.h"
#include "Graph.h"
#include "IntHashTable.h"
#include "Tree.h"
#include "SmartCityTypes.h"
#include "Utilities.h"

const int MAX_STOPS = 50;
const int MAX_BUSES = 50;
const int MAX_SCHOOLS = 50;
const int MAX_HOSPITALS = 50;
const int MAX_PHARMACIES = 100;
const int MAX_CITIZENS = 500;




class SmartCity
{
public:
    // Raw data arrays
    BusStop stops[MAX_STOPS];
    int stopCount;
    Bus buses[MAX_BUSES];
    int busCount;
    School schools[MAX_SCHOOLS];  // each object is a school in isb, we hard coded 
    int schoolCount;
    Hospital hospitals[MAX_HOSPITALS];
    int hospitalCount;
    PharmacyRecord pharmacies[MAX_PHARMACIES];
    int pharmacyCount;
    Citizen citizens[MAX_CITIZENS];
    int citizenCount;

    // MASTER CITY GRAPH + SUBGRAPHS
    Graph cityGraph;  // Master graph with ALL locations

    void generatePopulationHeatmap();
    //  MODULE-SPECIFIC SUBGRAPHS (Extracted from cityGraph)
    Graph medicalSubgraph;      // Hospitals + connecting bus stops
    Graph educationSubgraph;    // Schools + connecting bus stops
    Graph commercialSubgraph;   // Malls + connecting stops
    Graph facilitiesSubgraph;   // Public facilities + stops
    Graph transportSubgraph;    // Bus stops only


    void findPathBetweenHospitalAndSchool(int m, int n);
    void searchSchoolsByLevel();
    //  SUBGRAPH MAPPINGS (to translate between full graph and subgraphs)
    struct SubgraphMapping
    {
        int fullToSub[500];
        int subToFull[500];
        int nodeCount;
    };

    SubgraphMapping medicalMapping;
    SubgraphMapping educationMapping;
    SubgraphMapping commercialMapping;
    SubgraphMapping facilitiesMapping;
    SubgraphMapping transportMapping;


    int convertToGraphNode(const char* type, int index);
    void displayPath(int startNode, int endNode, int distance, int parent[]);
    void findPathBetweenAnyTwo();
    void testCrossModuleConnectivity();

    NodeInfo nodeRegistry[500];
    int totalNodes;

    // Hash tables
    IntHashTable busNumberToIndex;
    IntHashTable stopIdToIndex;
    IntHashTable hospitalIdToIndex;
    IntHashTable citizenIdToIndex;
    IntHashTable medicineNameHash;
    IntHashTable medicineFormulaHash;
    IntHashTable facilityNameHash;

    // Priority queues
    MinHeap hospitalPriorityQueue;
    MinHeap schoolRankingQueue;

    // Trees
    TreeNode* islamabadRoot;
    TreeNode* schoolSystemRoot;
    TreeNode* populationRoot;

    // Commercial & Public Facilities
    Mall malls[20];
    int mallCount;
    IntHashTable mallIdToIndex;
    IntHashTable productNameHash;
    PublicFacility facilities[50];
    int facilityCount;
    IntHashTable facilityIdToIndex;

    // Stack and Queue
    Stack routeHistoryStack;
    CircularQueue passengerQueue;

    // Bonus features
    SchoolBusTracker schoolBusTracker;
    AirportStation airportRailStations[10];
    int stationCount;

    // Medical Sector
    Doctor doctors[100];
    int doctorCount;
    PatientRecord patients[200];
    int patientCount;
    IntHashTable doctorIdToIndex;
    IntHashTable patientIdToIndex;

    // Constructor
    SmartCity();

    // Initialization
    void init();

    // SUBGRAPH BUILDING
    void buildModuleSubgraphs();

    // Map node between full graph and subgraph
    int mapToSubgraph(int fullGraphNode, const SubgraphMapping& mapping);
    int mapFromSubgraph(int subgraphNode, const SubgraphMapping& mapping);

    // Data Loading
    void loadTransportData(const char* stopsFile, const char* busesFile);
    void loadEducationData(const char* schoolsFile);
    void loadMedicalData(const char* hospitalsFile, const char* pharmaciesFile);
    void loadPopulationData(const char* populationFile);
    void loadCommercialData(const char* mallsFile);
    void loadPublicFacilitiesData(const char* facilitiesFile);

    void registerFaculty();
    void  registerStudent();
    void  compareSchoolsBySubjects();
    void generateSchoolPerformanceReport();
    void displaySchoolSystemTree();
    // DS Builders
    void buildTransportGraph();
    void buildIslamabadHierarchyTree();
    void displayIslamabadHierarchy();
    void buildSchoolSystemTree();
    void buildPopulationTree();
    void buildHashTables();
    void buildHospitalPriorityQueue();
    void buildSchoolRankingQueue();

    // Search/Query
    int findStopIndexById(int stopIdInt);
    int findBusIndexByNumber(const char* busNo);
    int findCitizenIndexByCNIC(const char* cnic);
    int findHospitalIndexById(const char* hospitalId);
    int findDoctorIndexById(const char* doctorId);
    int findPatientIndexById(const char* patientId);

    void searchMedicineByName(const char* medName);
    void searchMedicineByFormula(const char* formula);

    void shortestPathBetweenStops(int fromIndex, int toIndex);
    void findNearestHospital(int fromStopIndex);
    void findNearestSchool(int fromStopIndex);
    void findNearestMall(int fromStopIndex);

    void calculateBusRouteDistance();
    void calculateNearestDistanceToPassenger();
    void listBusesPassingThroughStop(int stopIndex);

    // Menu System
    void mainMenu();
    void transportMenu();
    void educationMenu();
    void medicalMenu();
    void commercialMenu();
    void publicFacilitiesMenu();
    void populationMenu();
    void analyticsMenu();

    // Display Functions
    void displayAllBuses();
    void displayAllStops();
    void displayBusRoute(int busIndex);
    void displayAllHospitals();
    void displayAllSchools();
    void displayAllCitizens();
    void displayTopHospitals(int n);
    void displayTopSchools(int n);
    void displayAllDoctors();
    void displayAllPatients();
    void displayAllMalls();
    void displayAllFacilities();
    void displayAllPharmacies();

    // Search Functions
    void searchCitizenByCNIC();
    void findNearestBusToPassenger();
    void searchSchoolsBySubject();
    void searchBusesByCompany();
    void findCommonStops();
    void findAllRoutesBetweenStops();
    void searchHospitalsBySpecialization();
    void findNearestBusStop();
    void searchDoctorBySpecialization();

    // Addition Functions
    void addBusStop();
    void addBus();
    void addStopToBusRoute();
    void addHospital();
    void addSchool();
    void addCitizen();
    void addMedicine();
    void addDoctor();
    void addPatient();
    void addMall();
    void addFacility();
    void addProductToMall();
    void deleteStopFromBusRoute();

    // Analytics
    void generateAgeDistributionReport();
    void generateOccupationReport();
    void generatePopulationDensityReport();
    void generateGenderRatioReport();
    void generateHospitalStatistics();
    void generateTransportStatistics();
    void generatePharmacyInventoryReport();
    void generateSystemSummary();

    // Comparisons
    void compareTwoHospitals();
    void compareTwoSchools();
    void compareMedicinePrices();

    // Operations
    void updateBusLocation();
    void assignPatientToDoctor();
    void dischargePatient();
    void validateDataIntegrity();

    // Stack & Queue
    void trackRouteHistory(int stopIndex);
    void displayRouteHistory();
    void clearRouteHistory();
    void addPassengerToQueue();
    void displayPassengerQueue();
    void simulatePassengerBoarding();

    // Commercial
    void searchProductByName();
    void displayProductsByCategory();

    // Public Facilities
    void searchFacilityByName();
    void findNearestFacilityByType();
    void findNearestFacilityToLocation();

    // Bonus Features
    void initSchoolBusTracking();
    void assignStudentToBus();
    void trackBusWithStudents();
    void displayBusPassengerList();
    void displayStudentLocation();
    void initAirportRailNetwork();
    void addAirportRailStation();
    void connectBusStopToAirport();
    void findRouteToAirport();
    void displayAirportRailNetwork();
    void simulateRealTimeRouting();
    void emergencyTransportRouting();

    // Sample Data
    void createSampleDoctors();
    void createSamplePatients();

    // Utilities
    void waitForEnter();
    int extractNumberFromCode(const char* code);
    double computeDistance(double lat1, double lon1, double lat2, double lon2);


    SectorTreeNode* sectorTreeRoot;
    SectorHouseMap**** sectorMaps;

    // Grid dimensions for houses
    const int GRID_ROWS = 10;
    const int GRID_COLS = 10;


    void buildSectorTree();
    void generateSectorReport();
    void displaySectorMap(int letterIdx, int sectorNum, int subSector);
    void addCitizenWithSector();
    bool allocateHouseInSector(int letterIdx, int sectorNum, int subSector, int& row, int& col);
    bool parseSectorCode(const char* sectorCode, int& letterIdx, int& sectorNum, int& subSector);
    void displayPopulationTree();
    void printPopulationTree(TreeNode* node, int level);
    void initializeSectorMaps();

    void simulateRealisticSchoolBusRoute();
};


// Constructor
SmartCity::SmartCity()
{
    stopCount = 0;
    busCount = 0;
    schoolCount = 0;
    hospitalCount = 0;
    pharmacyCount = 0;
    citizenCount = 0;
    mallCount = 0;
    facilityCount = 0;
    doctorCount = 0;
    patientCount = 0;
    stationCount = 0;
    totalNodes = 0;

    schoolBusTracker.totalStudents = 0;
    for (int i = 0; i < 50; i++)
    {
        schoolBusTracker.count[i] = 0;
        schoolBusTracker.studentsOnBuses[i] = nullptr;
    }

    islamabadRoot = nullptr;
    schoolSystemRoot = nullptr;
    populationRoot = nullptr;

    // Initialize mappings
    medicalMapping.nodeCount = 0;
    educationMapping.nodeCount = 0;
    commercialMapping.nodeCount = 0;
    facilitiesMapping.nodeCount = 0;
    transportMapping.nodeCount = 0;
}

void SmartCity::buildModuleSubgraphs()
{
    cout << "\n BUILDING MODULE SUBGRAPHS FROM MASTER GRAPH...\n";
    cout << " Master graph has " << totalNodes << " nodes\n\n";

    // 1. Medical Subgraph (Hospitals + connecting bus stops)
    medicalSubgraph = cityGraph.extractSubgraphWithBridges(
        "Hospital", "BusStop", nodeRegistry, totalNodes,
        medicalMapping.fullToSub, medicalMapping.subToFull
    );
    medicalMapping.nodeCount = medicalSubgraph.getVertices();
    cout << " Medical subgraph: " << medicalMapping.nodeCount
        << " nodes (Hospitals + connecting stops)\n";

    // 2. Education Subgraph
    educationSubgraph = cityGraph.extractSubgraphWithBridges(
        "School", "BusStop", nodeRegistry, totalNodes,
        educationMapping.fullToSub, educationMapping.subToFull
    );
    educationMapping.nodeCount = educationSubgraph.getVertices();
    cout << " Education subgraph: " << educationMapping.nodeCount
        << " nodes (Schools + connecting stops)\n";

    // 3. Commercial Subgraph
    commercialSubgraph = cityGraph.extractSubgraphWithBridges(
        "Mall", "BusStop", nodeRegistry, totalNodes,
        commercialMapping.fullToSub, commercialMapping.subToFull
    );
    commercialMapping.nodeCount = commercialSubgraph.getVertices();
    cout << "Commercial subgraph: " << commercialMapping.nodeCount
        << " nodes (Malls + connecting stops)\n";

    // 4. Public Facilities Subgraph
    facilitiesSubgraph = cityGraph.extractSubgraphWithBridges(
        "Facility", "BusStop", nodeRegistry, totalNodes,
        facilitiesMapping.fullToSub, facilitiesMapping.subToFull
    );
    facilitiesMapping.nodeCount = facilitiesSubgraph.getVertices();
    cout << " Facilities subgraph: " << facilitiesMapping.nodeCount
        << " nodes (Facilities + connecting stops)\n";

    // 5. Transport-Only Subgraph (Bus stops only)
    transportSubgraph = cityGraph.extractSubgraph(
        "BusStop", nodeRegistry, totalNodes,
        transportMapping.fullToSub, transportMapping.subToFull
    );
    transportMapping.nodeCount = transportSubgraph.getVertices();
    cout << " Transport subgraph: " << transportMapping.nodeCount
        << " nodes (Bus stops only)\n\n";

    cout << " ALL SUBGRAPHS EXTRACTED SUCCESSFULLY!\n";
    cout << " Google Maps architecture: 1 master + 5 filtered subgraphs\n\n";
}

int SmartCity::mapToSubgraph(int fullGraphNode, const SubgraphMapping& mapping)
{
    if (fullGraphNode < 0 || fullGraphNode >= 500) return -1;
    return mapping.fullToSub[fullGraphNode];
}

int SmartCity::mapFromSubgraph(int subgraphNode, const SubgraphMapping& mapping)
{
    if (subgraphNode < 0 || subgraphNode >= mapping.nodeCount) return -1;
    return mapping.subToFull[subgraphNode];
}

void SmartCity::searchSchoolsBySubject()
{
    char subject[50];
    cout << " SEARCH SCHOOLS BY SUBJECT\n";
    cout << "Enter subject name: ";
    cin.ignore(10000, '\n');
    cin.getline(subject, 50);

    cout << "\n Schools offering " << subject << ":\n";
    cout << "----------------------------------------\n";

    bool found = false;
    for (int i = 0; i < schoolCount; i++) {
        // Check if school offers this subject
        for (int j = 0; j < schools[i].subjectCount; j++) {
            // Simple case-insensitive comparison
            bool match = true;
            for (int k = 0; subject[k] != '\0' || schools[i].subjects[j][k] != '\0'; k++) {
                char c1 = subject[k];
                char c2 = schools[i].subjects[j][k];

                // Convert to lowercase
                if (c1 >= 'A' && c1 <= 'Z') c1 += 32;
                if (c2 >= 'A' && c2 <= 'Z') c2 += 32;

                if (c1 != c2) {
                    match = false;
                    break;
                }
                if (c1 == '\0') break;
            }

            if (match) {
                cout << "? " << schools[i].name << "\n";
                cout << "   Sector: " << schools[i].sector << "\n";
                cout << "   Rating: " << schools[i].ranking / 10.0 << "/5.0\n\n";
                found = true;
                break;
            }
        }
    }

    if (!found) {
        cout << "? No schools found offering this subject.\n";
    }
}

//Creating sample doctors
void SmartCity::createSampleDoctors()
{
    cout << " Initializing doctors system...\n";

    strCopy(doctors[0].doctorID, "D001");
    strCopy(doctors[0].name, "Dr. Ahmed Khan");
    strCopy(doctors[0].specialization, "Cardiology");
    strCopy(doctors[0].hospitalID, "H01");
    doctors[0].experience = 15;

    strCopy(doctors[1].doctorID, "D002");
    strCopy(doctors[1].name, "Dr. Fatima Ali");
    strCopy(doctors[1].specialization, "Pediatrics");
    strCopy(doctors[1].hospitalID, "H05");
    doctors[1].experience = 10;

    strCopy(doctors[2].doctorID, "D003");
    strCopy(doctors[2].name, "Dr. Hassan Raza");
    strCopy(doctors[2].specialization, "Orthopedics");
    strCopy(doctors[2].hospitalID, "H03");
    doctors[2].experience = 8;

    strCopy(doctors[3].doctorID, "D004");
    strCopy(doctors[3].name, "Dr. Sara Malik");
    strCopy(doctors[3].specialization, "General");
    strCopy(doctors[3].hospitalID, "H04");
    doctors[3].experience = 12;

    doctorCount = 4;
    cout << "? Created " << doctorCount << " sample doctors.\n";
}

void SmartCity::createSamplePatients()
{
    cout << "==== Initializing patients system ======\n";

    strCopy(patients[0].patientID, "P001");
    strCopy(patients[0].name, "Ali Imran");
    strCopy(patients[0].cnic, "61101-1234567-1");
    patients[0].age = 45;
    strCopy(patients[0].disease, "Heart Disease");
    strCopy(patients[0].assignedDoctorID, "D001");
    strCopy(patients[0].hospitalID, "H01");
    strCopy(patients[0].admissionDate, "2025-12-01");
    patients[0].isAdmitted = true;

    strCopy(patients[1].patientID, "P002");
    strCopy(patients[1].name, "Sara Ahmed");
    strCopy(patients[1].cnic, "61101-9876543-2");
    patients[1].age = 8;
    strCopy(patients[1].disease, "Fever");
    strCopy(patients[1].assignedDoctorID, "D002");
    strCopy(patients[1].hospitalID, "H05");
    strCopy(patients[1].admissionDate, "2025-12-03");
    patients[1].isAdmitted = true;

    strCopy(patients[2].patientID, "P003");
    strCopy(patients[2].name, "Usman Shah");
    strCopy(patients[2].cnic, "61101-5555555-3");
    patients[2].age = 32;
    strCopy(patients[2].disease, "Fracture");
    strCopy(patients[2].assignedDoctorID, "D003");
    strCopy(patients[2].hospitalID, "H03");
    strCopy(patients[2].admissionDate, "2025-12-02");
    patients[2].isAdmitted = false;

    patientCount = 3;
    cout << "? Created " << patientCount << " sample patients.\n";
}


void SmartCity::addDoctor()
{
    if (doctorCount >= 100)
    {
        cout << "XX Doctor array is full.\n";
        return;
    }

    cout << "\n========== ADD NEW DOCTOR ==========\n";

    char id[10], name[MAX_STR], spec[50], hospitalID[10];
    int exp;

    cout << "Enter Doctor ID (e.g., D005): ";
    cin >> id;

    // Check if ID already exists
    if (findDoctorIndexById(id) != -1)
    {
        cout << "XX Doctor with this ID already exists.\n";
        cin.ignore(10000, '\n');
        return;
    }

    cout << "Enter Doctor Name: ";
    cin.ignore(10000, '\n');
    cin.getline(name, MAX_STR);

    cout << "Enter Specialization (e.g., Cardiology): ";
    cin.getline(spec, 50);

    cout << "Enter Hospital ID (e.g., H01): ";
    cin >> hospitalID;

    // Validate hospital exists
    if (findHospitalIndexById(hospitalID) == -1)
    {
        cout << "?XX   Hospital ID not found in system.\n";
        cout << "Continue anyway? (y/n): ";
        char confirm;
        cin >> confirm;
        if (confirm != 'y' && confirm != 'Y')
        {
            cin.ignore(10000, '\n');
            return;
        }
    }

    cout << "Enter Years of Experience: ";
    cin >> exp;

    if (cin.fail())
    {
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "? Invalid experience!\n";
        return;
    }

    // Add to array
    strCopy(doctors[doctorCount].doctorID, id);
    strCopy(doctors[doctorCount].name, name);
    strCopy(doctors[doctorCount].specialization, spec);
    strCopy(doctors[doctorCount].hospitalID, hospitalID);
    doctors[doctorCount].experience = exp;

    doctorCount++;

    // Update hash table
    int key = StringHash::hash(id);
    doctorIdToIndex.insert(key, doctorCount - 1);

    cout << "\n# Doctor added successfully!\n";
    cout << "   ID: " << id << "\n";
    cout << "   Name: " << name << "\n";
    cout << "   Specialization: " << spec << "\n";
    cout << "   Hospital: " << hospitalID << "\n";
    cout << "   Experience: " << exp << " years\n";
    cout << "====================================\n";
}

//Simple adding patient using hash functions only
void SmartCity::addPatient()
{
    if (patientCount >= 200)
    {
        cout << "XX Patient array is full.\n";
        return;
    }

    cout << "\n========== ADD NEW PATIENT ==========\n";

    char id[10], name[MAX_STR], cnic[20], disease[100];
    char doctorID[10], hospitalID[10], admissionDate[20];
    int age;
    bool admitted;

    cout << "Enter Patient ID (e.g., P004): ";
    cin >> id;

    // Check if ID already exists
    if (findPatientIndexById(id) != -1)
    {
        cout << "XX Patient with this ID already exists.\n";
        cin.ignore(10000, '\n');
        return;
    }

    cout << "Enter Patient Name: ";
    cin.ignore(10000, '\n');
    cin.getline(name, MAX_STR);

    cout << "Enter CNIC (e.g., 61101-1234567-1): ";
    cin.getline(cnic, 20);

    cout << "Enter Age: ";
    cin >> age;

    if (cin.fail())
    {
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "? Invalid age!\n";
        return;
    }

    cout << "Enter Disease: ";
    cin.ignore(10000, '\n');
    cin.getline(disease, 100);

    cout << "Enter Assigned Doctor ID (e.g., D001): ";
    cin >> doctorID;

    // Validate doctor exists
    int docIdx = findDoctorIndexById(doctorID);
    if (docIdx == -1) {
        cout << "XX  Warning: Doctor ID not found in system.\n";
        cout << "Continue anyway? (y/n): ";
        char confirm;
        cin >> confirm;
        if (confirm != 'y' && confirm != 'Y')
        {
            cin.ignore(10000, '\n');
            return;
        }
        // Default hospital
        strCopy(hospitalID, "H01");
    }
    else {
        // Auto assign to doctor's hospital
        strCopy(hospitalID, doctors[docIdx].hospitalID);
        cout << "? Auto-assigned to hospital: " << hospitalID << "\n";
    }

    cout << "Enter Admission Date (e.g., 2025-12-04): ";
    cin >> admissionDate;

    cout << "Is patient admitted? (1=Yes, 0=No): ";
    int admitChoice;
    cin >> admitChoice;
    admitted = (admitChoice == 1);

    // Add to array
    strCopy(patients[patientCount].patientID, id);
    strCopy(patients[patientCount].name, name);
    strCopy(patients[patientCount].cnic, cnic);
    patients[patientCount].age = age;
    strCopy(patients[patientCount].disease, disease);
    strCopy(patients[patientCount].assignedDoctorID, doctorID);
    strCopy(patients[patientCount].hospitalID, hospitalID);
    strCopy(patients[patientCount].admissionDate, admissionDate);
    patients[patientCount].isAdmitted = admitted;

    patientCount++;

    // Update hash table
    int key = StringHash::hash(id);
    patientIdToIndex.insert(key, patientCount - 1);

    cout << "\n## Patient added successfully!\n";
    cout << "   ID: " << id << "\n";
    cout << "   Name: " << name << "\n";
    cout << "   Age: " << age << "\n";
    cout << "   Disease: " << disease << "\n";
    cout << "   Doctor: " << doctorID << "\n";
    cout << "   Hospital: " << hospitalID << "\n";
    cout << "   Status: " << (admitted ? "Admitted" : "Not Admitted") << "\n";
    cout << "=====================================\n";
}

void SmartCity::findNearestFacilityToLocation()
{
    if (facilityCount == 0)
    {
        cout << "? No facilities loaded.\n";
        return;
    }

    char locationName[MAX_STR];
    cout << "\n========== FIND NEAREST FACILITY TO LOCATION ==========\n";
    cout << "Enter location name (bus stop, hospital, school): ";
    cin.ignore(10000, '\n');
    cin.getline(locationName, MAX_STR);

    // Try to find location in stops
    int stopIdx = -1;
    for (int i = 0; i < stopCount; i++)
    {
        bool match = true;
        for (int j = 0; stops[i].name[j] != '\0' && locationName[j] != '\0'; j++)
        {
            char c1 = stops[i].name[j];
            char c2 = locationName[j];
            if (c1 >= 'A' && c1 <= 'Z') c1 += 32;
            if (c2 >= 'A' && c2 <= 'Z') c2 += 32;
            if (c1 != c2) {
                match = false;
                break;
            }
        }
        if (match && stops[i].name[0] != '\0') {
            stopIdx = i;
            break;
        }
    }

    if (stopIdx == -1)
    {
        cout << "? Location not found.\n";
        cout << "Available stops:\n";
        for (int i = 0; i < min(5, stopCount); i++)
        {
            cout << "  - " << stops[i].name << "\n";
        }
        return;
    }

    cout << "\n FINDING NEAREST FACILITY TO: " << stops[stopIdx].name << "\n\n";

    // Run Dijkstra from this stop
    static int dist[500];
    static int parent[500];
    const int INF = 1000000000;

    for (int i = 0; i < totalNodes; i++) {
        dist[i] = INF;
        parent[i] = -1;
    }

    cityGraph.dijkstra(stopIdx, dist, parent);

    // Find nearest facility (any type)
    int nearestFacilityIdx = -1;
    int minDist = INF;
    int facilityStartNode = stopCount + hospitalCount + schoolCount + mallCount;

    for (int i = 0; i < facilityCount; i++) {
        int facilityNode = facilityStartNode + i;

        if (facilityNode < totalNodes && dist[facilityNode] < minDist)
        {
            minDist = dist[facilityNode];
            nearestFacilityIdx = i;
        }
    }

    if (nearestFacilityIdx == -1 || minDist >= INF)
    {
        cout << "No facility reachable from this location.\n";
        return;
    }

    cout << " NEAREST FACILITY FOUND:\n";
    cout << "========================================\n";
    cout << "Name: " << facilities[nearestFacilityIdx].name << "\n";
    cout << "Type: " << facilities[nearestFacilityIdx].type << "\n";

    cout << "Distance: " << (minDist / 1000.0) << " km\n";
    cout << "========================================\n\n";
}


void SmartCity::displayAllPharmacies()
{
    cout << "========================================" << endl;
    cout << "       ALL PHARMACY MEDICINES          " << endl;
    cout << "========================================" << endl;

    if (pharmacyCount == 0) {
        cout << "## No pharmacy records loaded." << endl;
        return;
    }

    for (int i = 0; i < pharmacyCount; i++)
    {
        cout << "------- Medicine " << (i + 1) << " -------" << endl;
        cout << "Pharmacy ID: " << pharmacies[i].pharmacyID << endl;
        cout << "Pharmacy:    " << pharmacies[i].pharmacyName << endl;
        cout << "Sector:      " << pharmacies[i].sector << endl;
        cout << "Medicine:    " << pharmacies[i].medicineName << endl;
        cout << "Formula:     " << pharmacies[i].formula << endl;
        cout << "Price:       Rs. " << pharmacies[i].price << endl;
        cout << endl;
    }

    cout << " Total Medicines: " << pharmacyCount << endl;
    cout << "========================================" << endl;
}


//Find patient using hash table check if it is admitted and discharge it 
void SmartCity::dischargePatient()
{
    char id[10];

    cout << "\n========== DISCHARGE PATIENT ==========\n";
    cout << "Enter Patient ID: ";
    cin >> id;

    int idx = findPatientIndexById(id);

    if (idx == -1) {
        cout << "XX Patient not found.\n";
        return;
    }

    if (!patients[idx].isAdmitted) {
        cout << "XX  Patient is already discharged.\n";
        return;
    }

    patients[idx].isAdmitted = false;

    cout << "\n Patient discharged successfully!\n";
    cout << "   Patient: " << patients[idx].name << "\n";
    cout << "   ID: " << patients[idx].patientID << "\n";
    cout << "=======================================\n";
}



void SmartCity::init()
{
    //Loading data
    loadTransportData("stops.csv", "buses.csv");
    loadEducationData("schools.csv");
    loadMedicalData("hospitals.csv", "pharmacies.csv");
    loadPopulationData("population.csv");
    loadCommercialData("malls.csv");
    loadPublicFacilitiesData("facilities.csv");

    createSampleDoctors();
    createSamplePatients();

    //Building main Graph
    buildTransportGraph();
    buildModuleSubgraphs();

    //Building trees and hash tables
    buildIslamabadHierarchyTree();
    buildSchoolSystemTree();
    buildPopulationTree();
    buildHashTables();
    buildHospitalPriorityQueue();
    buildSchoolRankingQueue();
}



void SmartCity::loadPopulationData(const char* populationFile)
{
    citizenCount = 0;

    FILE* f = fopen(populationFile, "r");
    if (f == nullptr) {
        cout << "ERROR: Could not open population file: " << populationFile << endl;
        return;
    }

    char line[500];

    // Skip header
    if (fgets(line, 500, f) != nullptr) {
        cout << " Reading population CSV...\n";
    }

    while (fgets(line, 500, f) != nullptr && citizenCount < MAX_CITIZENS)
    {
        // Strip newline
        for (int i = 0; line[i] != '\0'; i++)
        {
            if (line[i] == '\n' || line[i] == '\r') {
                line[i] = '\0';
                break;
            }
        }
        if (line[0] == '\0') continue;

        // Expected: CNIC,Name,Age,Sector,Street,HouseNo,Occupation
        char fields[10][100];
        int fieldCount = 0;
        splitCSVLine(line, fields, fieldCount);

        if (fieldCount < 7) {
            cout << "⚠️ Skipping population line with " << fieldCount << " fields\n";
            continue;
        }

        for (int i = 0; i < fieldCount; i++) {
            trimSpaces(fields[i]);
        }

        Citizen& c = citizens[citizenCount];

        manualStrCopy(c.cnic, fields[0]);      // CNIC
        manualStrCopy(c.name, fields[1]);      // Name
        c.age = manualAtoi(fields[2]);         // Age

        manualStrCopy(c.sector, fields[3]);   // Sector
        manualStrCopy(c.street, fields[4]);   // Street
        manualStrCopy(c.houseNo, fields[5]);   // HouseNo

        manualStrCopy(c.occupation, fields[6]); // Occupation

        int r = std::rand() % 2;   // 0 or 1
        c.gender = (r == 0) ? 'M' : 'F';

        citizenCount++;
    }

    fclose(f);
    cout << "✅ Loaded " << citizenCount << " citizens from " << populationFile << "\n";
}



void SmartCity::waitForEnter()
{
    cout << "\nPress Enter to continue...";
    cin.ignore(1000, '\n');
    cin.get();
}

double SmartCity::computeDistance(double lat1, double lon1, double lat2, double lon2)
{
    // Simple Euclidean distance (works for small areas)
    double dx = lat2 - lat1;
    double dy = lon2 - lon1;
    double distSquared = dx * dx + dy * dy;

    if (distSquared <= 0.0) return 0.0;

    // Integer square root approximation
    double result = distSquared;
    double last;
    do {
        last = result;
        result = (result + distSquared / result) / 2.0;
    } while (result != last);

    return result * 111.0;  //SCALING FACTOR
}



int SmartCity::extractNumberFromCode(const char* code)
{
    int key = 0;
    bool foundDigit = false;

    for (int i = 0; code[i] != '\0'; i++) {
        if (code[i] >= '0' && code[i] <= '9') {
            foundDigit = true;
            key = key * 10 + (code[i] - '0');
        }
    }
    if (!foundDigit)
        return -1;
    return key;
}

// =====================================================================
//                         HASH-BASED LOOKUPS
// =====================================================================
int SmartCity::findStopIndexById(int stopIdInt)
{
    return stopIdToIndex.search(stopIdInt);  // index in stops[] or -1
}

int SmartCity::findBusIndexByNumber(const char* busNo)
{
    int key = extractNumberFromCode(busNo);  // "B101" ? 101
    if (key == -1)
        return -1;
    return busNumberToIndex.search(key);     // index in buses[] or -1
}

int SmartCity::findCitizenIndexByCNIC(const char* cnic)
{
    int key = StringHash::hash(cnic);
    return citizenIdToIndex.search(key);     // index in citizens[] or -1
}

int SmartCity::findHospitalIndexById(const char* hospitalId)
{
    int key = StringHash::hash(hospitalId);
    return hospitalIdToIndex.search(key);    // index in hospitals[] or -1
}


//Searches for a medicine by name using hash table for O(1) lookup
void SmartCity::searchMedicineByName(const char* medName)
{
    int key = StringHash::hash(medName);
    int index = medicineNameHash.search(key);

    if (index == -1)
    {
        cout << "Medicine not found.\n";
        return;
    }

    cout << "Medicine has been found:\n";
    cout << "Name: " << pharmacies[index].medicineName << "\n";
    cout << "Formula: " << pharmacies[index].formula << "\n";
    cout << "Price: " << pharmacies[index].price << "\n";
}
//Same uses hash to search
void SmartCity::searchMedicineByFormula(const char* formula)
{
    int key = StringHash::hash(formula);
    int idx = medicineFormulaHash.search(key);

    if (idx == -1)
    {
        cout << "Medicine with this formula not found.\n";
        return;
    }

    cout << "Medicine found:\n";
    cout << "Name: " << pharmacies[idx].medicineName << "\n";
    cout << "Formula: " << pharmacies[idx].formula << "\n";
    cout << "Price: " << pharmacies[idx].price << "\n";
}

//Building Hash Tables
void SmartCity::buildHashTables()
{
    // Buses hash table
    for (int i = 0; i < busCount; i++)
    {
        int key = extractNumberFromCode(buses[i].busNo);
        if (key != -1)
            busNumberToIndex.insert(key, i);
    }

    // Stops
    for (int i = 0; i < stopCount; i++)
    {
        int key = stops[i].id;
        stopIdToIndex.insert(key, i);
    }

    // Citizens
    for (int i = 0; i < citizenCount; i++)
    {
        int key = StringHash::hash(citizens[i].cnic);
        citizenIdToIndex.insert(key, i);
    }

    // Hospitals
    for (int i = 0; i < hospitalCount; i++)
    {
        int key = StringHash::hash(hospitals[i].hospitalID);
        hospitalIdToIndex.insert(key, i);
    }

    // Medicines
    for (int i = 0; i < pharmacyCount; i++)
    {
        int nameKey = StringHash::hash(pharmacies[i].medicineName);
        int formulaKey = StringHash::hash(pharmacies[i].formula);

        medicineNameHash.insert(nameKey, i);
        medicineFormulaHash.insert(formulaKey, i);
    }

    // Malls
    for (int i = 0; i < mallCount; i++)
    {
        int key = StringHash::hash(malls[i].mallID);
        mallIdToIndex.insert(key, i);
    }

    //  Facilities
    for (int i = 0; i < facilityCount; i++)
    {
        int key = StringHash::hash(facilities[i].facilityID);
        facilityIdToIndex.insert(key, i);
    }
    // Facilities by NAME
    for (int i = 0; i < facilityCount; i++) {
        int nameKey = StringHash::hash(facilities[i].name);
        facilityNameHash.insert(nameKey, i);
    }

    // Doctors
    for (int i = 0; i < doctorCount; i++) {
        int key = StringHash::hash(doctors[i].doctorID);
        doctorIdToIndex.insert(key, i);
    }

    // Patients
    for (int i = 0; i < patientCount; i++) {
        int key = StringHash::hash(patients[i].patientID);
        patientIdToIndex.insert(key, i);
    }

    cout << "All hash tables built successfully.\n";
}

//Finding doctor
int SmartCity::findDoctorIndexById(const char* doctorId) {
    int key = StringHash::hash(doctorId);
    return doctorIdToIndex.search(key);
}

//Finding patient
int SmartCity::findPatientIndexById(const char* patientId) {
    int key = StringHash::hash(patientId);
    return patientIdToIndex.search(key);
}

//Displaying doctors
void SmartCity::displayAllDoctors() {
    cout << "\n========== ALL DOCTORS ==========\n";

    if (doctorCount == 0) {
        cout << "? No doctors registered.\n";
        return;
    }

    for (int i = 0; i < doctorCount; i++) {
        cout << "\n Doctor #" << (i + 1) << ":\n";
        cout << "   ID: " << doctors[i].doctorID << "\n";
        cout << "   Name: " << doctors[i].name << "\n";
        cout << "   Specialization: " << doctors[i].specialization << "\n";
        cout << "   Hospital ID: " << doctors[i].hospitalID << "\n";
        cout << "   Experience: " << doctors[i].experience << " years\n";
    }

    cout << "\n Total Doctors: " << doctorCount << "\n";
    cout << "=================================\n";
}

//Displaying patients
void SmartCity::displayAllPatients() {
    cout << "\n========== ALL PATIENTS ==========\n";

    if (patientCount == 0) {
        cout << "? No patients registered.\n";
        return;
    }

    for (int i = 0; i < patientCount; i++) {
        cout << "\n Patient #" << (i + 1) << ":\n";
        cout << "   ID: " << patients[i].patientID << "\n";
        cout << "   Name: " << patients[i].name << "\n";
        cout << "   CNIC: " << patients[i].cnic << "\n";
        cout << "   Age: " << patients[i].age << "\n";
        cout << "   Disease: " << patients[i].disease << "\n";
        cout << "   Assigned Doctor: " << patients[i].assignedDoctorID << "\n";
        cout << "   Hospital: " << patients[i].hospitalID << "\n";
        cout << "   Admission Date: " << patients[i].admissionDate << "\n";
        cout << "   Status: " << (patients[i].isAdmitted ? "? Admitted" : "? Discharged") << "\n";
    }

    cout << "\n Total Patients: " << patientCount << "\n";
    cout << "==================================\n";
}

// Searching doctor by specialization
void SmartCity::searchDoctorBySpecialization()
{
    char spec[50];
    cout << "\n========== SEARCH DOCTORS BY SPECIALIZATION ==========\n";
    cout << "Enter specialization: ";
    cin.ignore(10000, '\n');
    cin.getline(spec, 50);

    cout << "\nXX Doctors with specialization '" << spec << "':\n";
    cout << "------------------------------------------------------\n";

    bool found = false;

    for (int i = 0; i < doctorCount; i++)
    {
        // Case insensitive comparison
        bool match = true;
        for (int j = 0; spec[j] != '\0' && doctors[i].specialization[j] != '\0'; j++)
        {
            char c1 = spec[j];
            char c2 = doctors[i].specialization[j];
            if (c1 >= 'A' && c1 <= 'Z')
                c1 += 32;
            if (c2 >= 'A' && c2 <= 'Z')
                c2 += 32;
            if (c1 != c2)
            {
                match = false;
                break;
            }
        }

        if (match) {
            cout << " " << doctors[i].name << " (ID: " << doctors[i].doctorID << ")\n";
            cout << "   Hospital: " << doctors[i].hospitalID << "\n";
            cout << "   Experience: " << doctors[i].experience << " years\n\n";
            found = true;
        }
    }

    if (!found) {
        cout << " No doctors found with this specialization.\n";
    }

    cout << "======================================================\n";
}

//Simple using hash retrieving and storing
void SmartCity::assignPatientToDoctor()
{
    char patientID[10], doctorID[10];

    cout << "\n========== ASSIGN PATIENT TO DOCTOR ==========\n";
    cout << "Enter Patient ID: ";
    cin >> patientID;
    cout << "Enter Doctor ID: ";
    cin >> doctorID;

    int pIdx = findPatientIndexById(patientID);
    int dIdx = findDoctorIndexById(doctorID);

    if (pIdx == -1) {
        cout << "XX Patient not found.\n";
        return;
    }

    if (dIdx == -1) {
        cout << "XX Doctor not found.\n";
        return;
    }

    strCopy(patients[pIdx].assignedDoctorID, doctorID);
    strCopy(patients[pIdx].hospitalID, doctors[dIdx].hospitalID);
    patients[pIdx].isAdmitted = true;

    cout << "\nXX Patient assigned successfully!\n";
    cout << "   Patient: " << patients[pIdx].name << "\n";
    cout << "   Doctor: " << doctors[dIdx].name << "\n";
    cout << "   Hospital: " << doctors[dIdx].hospitalID << "\n";
    cout << "=============================================\n";
}


/*
This is main function for our project so what it does is that it makes the graph basically the
main concept is that how we do it so firstly we registers all the stops in the graph then same goes
for the hospital, schools and other things what we do is that we register there node types and all
but still the nodes and all are empty we just knows the type of the node then after that we do
is that we connects the bus routes means when there is route that means that surely there is the
path so we connect them then further we connects the stops to the nearest three stops after that
we move forward to connecting the schools and all to the nearest three stops so that they are
interconnected and after that same goes for all other things and we connect them with the nearest
stops and all how we do is that we loop around all the stops and compute the distance for all
nodes we note down there distnaces and there indexes and after that what we do is we bubble sort the
array to sort according to the distance and then we connect three nearest stop to it so that it has
multiple ways and all

*/
void SmartCity::buildTransportGraph()
{
    cout << "###  Building unified city-wide graph\n";

    totalNodes = 0;
    int maxNodes = stopCount + hospitalCount + schoolCount + mallCount + facilityCount + 50;

    if (maxNodes <= 0)
    {
        cout << "### No locations to build graph.\n";
        return;
    }

    cityGraph.initialize(maxNodes);

    // ==================== REGISTERING ALL THE BUSSES ====================
    cout << "  ## Adding " << stopCount << " bus stops as graph nodes\n";
    for (int i = 0; i < stopCount; i++)
    {
        strCopy(nodeRegistry[totalNodes].type, "BusStop");
        nodeRegistry[totalNodes].originalIndex = i;
        totalNodes++;
    }
    int stopNodesEnd = totalNodes;
    cout << "  ## Bus stop nodes: 0 to " << (stopNodesEnd - 1) << "\n";

    // ==================== REGISTERING ALL THE HOSPITALS====================
    cout << "  ## Adding " << hospitalCount << " hospitals as graph nodes\n";
    for (int i = 0; i < hospitalCount; i++)
    {
        strCopy(nodeRegistry[totalNodes].type, "Hospital");
        nodeRegistry[totalNodes].originalIndex = i;
        totalNodes++;
    }

    int hospitalNodesEnd = totalNodes;
    if (hospitalCount > 0) {
        cout << "  ## Hospital nodes: " << stopNodesEnd << " to " << (hospitalNodesEnd - 1) << "\n";
    }

    // ==================== REGISTERING ALL THE SCHOOLS ====================
    cout << "  ## Adding " << schoolCount << " schools as graph nodes.\n";
    for (int i = 0; i < schoolCount; i++)
    {
        strCopy(nodeRegistry[totalNodes].type, "School");
        nodeRegistry[totalNodes].originalIndex = i;
        totalNodes++;
    }
    int schoolNodesEnd = totalNodes;
    if (schoolCount > 0)
    {
        cout << "  ## School nodes: " << hospitalNodesEnd << " to " << (schoolNodesEnd - 1) << "\n";
    }

    // ==================== REGISTERING ALL THE MALLS ====================
    cout << "  ## Adding " << mallCount << " malls as graph nodes\n";
    for (int i = 0; i < mallCount; i++)
    {
        strCopy(nodeRegistry[totalNodes].type, "Mall");
        nodeRegistry[totalNodes].originalIndex = i;
        totalNodes++;
    }
    int mallNodesEnd = totalNodes;
    if (mallCount > 0)
    {
        cout << "  ## Mall nodes: " << schoolNodesEnd << " to " << (mallNodesEnd - 1) << "\n";
    }

    // ==================== REGISTERING ALL THE FACILITIES ====================
    cout << "  ## Adding " << facilityCount << " facilities as graph nodes\n";
    for (int i = 0; i < facilityCount; i++)
    {
        strCopy(nodeRegistry[totalNodes].type, "Facility");
        nodeRegistry[totalNodes].originalIndex = i;
        totalNodes++;
    }
    if (facilityCount > 0)
    {
        cout << "  ## Facility nodes: " << mallNodesEnd << " to " << (totalNodes - 1) << "\n";
    }

    cout << "\n  ### Total graph nodes: " << totalNodes << "\n";
    cout << "   Connecting nodes with edges\n\n";

    // ==================== CONNECTING BUS STOPS ====================
    cout << "  ## Connecting bus stops via routes\n";
    int edgeCount = 0;
    for (int i = 0; i < busCount; i++)
    {
        RouteNode* curr = buses[i].routeHead;
        while (curr != nullptr && curr->next != nullptr)
        {
            int node1 = curr->stopIndex;
            int node2 = curr->next->stopIndex;

            if (node1 >= 0 && node1 < stopCount && node2 >= 0 && node2 < stopCount)
            {
                double d = computeDistance(stops[node1].location.lat, stops[node1].location.lon,
                    stops[node2].location.lat, stops[node2].location.lon);
                int weight = (int)(d * 1000);
                if (weight <= 0)
                    weight = 1;

                cityGraph.addEdge(node1, node2, weight);
                edgeCount++;
            }
            curr = curr->next;
        }
    }
    // ==================== CONNECTING TOP 3 BUS STOPS ====================
    cout << "@@ Connecting bus stops to each other\n";
    int stopEdgeCount = 0;

    // Connect each stop to its 3 nearest neighbors
    for (int i = 0; i < stopCount; i++)
    {
        //Struct for index of the node and the distanece means the weight
        struct StopDist
        {
            int idx;
            double dist;
        };
        StopDist nearest[50];

        // Calculating distances to all other stops
        for (int j = 0; j < stopCount; j++)
        {
            if (i == j)
            {
                nearest[j].dist = 1e9;
                continue;
            }
            nearest[j].idx = j;
            nearest[j].dist = computeDistance(stops[i].location.lat, stops[i].location.lon,
                stops[j].location.lat, stops[j].location.lon);
        }

        // Sorting the distance
        for (int a = 0; a < stopCount - 1; a++)
        {
            for (int b = a + 1; b < stopCount; b++)
            {
                if (nearest[b].dist < nearest[a].dist)
                {
                    StopDist temp = nearest[a];
                    nearest[a] = nearest[b];
                    nearest[b] = temp;
                }
            }
        }

        // Connecting to 3 nearest stops or less if there are less stops 
        int connectCount = (stopCount < 3) ? stopCount - 1 : 3;
        for (int k = 0; k < connectCount; k++)
        {
            int neighborIdx = nearest[k].idx;
            int weight = (int)(nearest[k].dist * 1000);  // Converting km to meters
            if (weight <= 0)
                weight = 1;

            if (i < neighborIdx)
            {
                cityGraph.addEdge(i, neighborIdx, weight);
                stopEdgeCount++;
            }
        }
    }

    cout << "== Added " << stopEdgeCount << " stop-to-stop edges\n\n";

    cout << "==  Added " << edgeCount << " bus route edges\n";

    // ==================== CONNECTING HOSPITALS TO NEAREST STOPS ====================
    cout << "  $$ Connecting hospitals to nearest bus stops...\n";
    edgeCount = 0;
    for (int h = 0; h < hospitalCount; h++)
    {
        int hospitalNodeID = stopNodesEnd + h;

        struct StopDist
        {
            int idx;
            double dist;
        };
        StopDist nearest[50];

        for (int s = 0; s < stopCount; s++)
        {
            nearest[s].idx = s;
            nearest[s].dist = computeDistance(hospitals[h].location.lat, hospitals[h].location.lon,
                stops[s].location.lat, stops[s].location.lon);
        }

        for (int i = 0; i < stopCount - 1 && i < 5; i++)
        {
            for (int j = i + 1; j < stopCount; j++)
            {
                if (nearest[j].dist < nearest[i].dist)
                {
                    StopDist temp = nearest[i];
                    nearest[i] = nearest[j];
                    nearest[j] = temp;
                }
            }
        }

        int connectCount = (stopCount < 3) ? stopCount : 3;
        for (int i = 0; i < connectCount; i++)
        {
            int stopIdx = nearest[i].idx;
            int weight = (int)(nearest[i].dist * 1000);
            if (weight <= 0)
                weight = 1;
            cityGraph.addEdge(hospitalNodeID, stopIdx, weight);
            edgeCount++;
        }
    }
    cout << "  ## Added " << edgeCount << " hospital-to-stop edges\n";

    // ==================== CONNECTING SCHOOLS TO NEAREST STOPS ====================
    cout << "  ## Connecting schools to nearest bus stops\n";
    edgeCount = 0;
    for (int sc = 0; sc < schoolCount; sc++)
    {
        int schoolNodeID = hospitalNodesEnd + sc;

        struct StopDist
        {
            int idx;
            double dist;
        };
        StopDist nearest[50];

        for (int s = 0; s < stopCount; s++)
        {
            nearest[s].idx = s;
            nearest[s].dist = computeDistance(schools[sc].lat, schools[sc].lon,
                stops[s].location.lat, stops[s].location.lon);
        }

        for (int i = 0; i < stopCount - 1 && i < 5; i++)
        {
            for (int j = i + 1; j < stopCount; j++)
            {
                if (nearest[j].dist < nearest[i].dist)
                {
                    StopDist temp = nearest[i];
                    nearest[i] = nearest[j];
                    nearest[j] = temp;
                }
            }
        }

        int connectCount = (stopCount < 3) ? stopCount : 3;
        for (int i = 0; i < connectCount; i++)
        {
            int weight = (int)(nearest[i].dist * 1000);
            if (weight <= 0)
                weight = 1;
            cityGraph.addEdge(schoolNodeID, nearest[i].idx, weight);
            edgeCount++;
        }
    }
    cout << "  ## Added " << edgeCount << " school-to-stop edges\n";

    // ==================== CONNECTING MALLS TO NEAREST STOPS ====================
    if (mallCount > 0)
    {
        cout << "  ## Connecting malls to nearest bus stops\n";
        edgeCount = 0;
        for (int m = 0; m < mallCount; m++)
        {
            int mallNodeID = schoolNodesEnd + m;

            struct StopDist
            {
                int idx;
                double dist;
            };
            StopDist nearest[50];

            for (int s = 0; s < stopCount; s++)
            {
                nearest[s].idx = s;
                nearest[s].dist = computeDistance(malls[m].location.lat, malls[m].location.lon,
                    stops[s].location.lat, stops[s].location.lon);
            }

            for (int i = 0; i < stopCount - 1 && i < 3; i++)
            {
                for (int j = i + 1; j < stopCount; j++)
                {
                    if (nearest[j].dist < nearest[i].dist)
                    {
                        StopDist temp = nearest[i];
                        nearest[i] = nearest[j];
                        nearest[j] = temp;
                    }
                }
            }

            int connectCount = (stopCount < 2) ? stopCount : 2;
            for (int i = 0; i < connectCount; i++)
            {
                int weight = (int)(nearest[i].dist * 1000);
                if (weight <= 0)
                    weight = 1;
                cityGraph.addEdge(mallNodeID, nearest[i].idx, weight);
                edgeCount++;
            }
        }
        cout << "  ## Added " << edgeCount << " mall-to-stop edges\n";
    }

    // ====================  CONNECT FACILITIES TO NEAREST STOPS ====================
    if (facilityCount > 0)
    {
        cout << "  ### Connecting facilities to nearest bus stops\n";
        edgeCount = 0;
        for (int f = 0; f < facilityCount; f++)
        {
            int facilityNodeID = mallNodesEnd + f;

            struct StopDist
            {
                int idx;
                double dist;
            };
            StopDist nearest[50];

            for (int s = 0; s < stopCount; s++)
            {
                nearest[s].idx = s;
                nearest[s].dist = computeDistance(facilities[f].location.lat, facilities[f].location.lon,
                    stops[s].location.lat, stops[s].location.lon);
            }

            for (int i = 0; i < stopCount - 1 && i < 3; i++)
            {
                for (int j = i + 1; j < stopCount; j++)
                {
                    if (nearest[j].dist < nearest[i].dist)
                    {
                        StopDist temp = nearest[i];
                        nearest[i] = nearest[j];
                        nearest[j] = temp;
                    }
                }
            }

            int connectCount = (stopCount < 2) ? stopCount : 2;
            for (int i = 0; i < connectCount; i++)
            {
                int weight = (int)(nearest[i].dist * 1000);
                if (weight <= 0)
                    weight = 1;
                cityGraph.addEdge(facilityNodeID, nearest[i].idx, weight);
                edgeCount++;
            }
        }
        cout << "  ## Added " << edgeCount << " facility-to-stop edges\n";
    }

    // ==================== DEBUGGING  ====================
    cout << "\n DEBUG Checking stop connectivity\n";
    for (int i = 0; i < min(3, stopCount); i++)
    {
        cout << "Stop " << i << " (" << stops[i].name << ") edges: ";
        int edgeCount = 0;

        // Manually traverse adjacency list
        AdjNode* curr = cityGraph.getAdjList(i);  // You'll need to add this getter
        while (curr)
        {
            edgeCount++;
            curr = curr->next;
        }
        cout << edgeCount << " edges\n";
    }

    cout << "\n MASTER CITY-WIDE GRAPH BUILT SUCCESSFULLY!\n";
    cout << "  Graph Summary:\n";
    cout << "   - Total nodes: " << totalNodes << "\n";
    cout << "   - Bus stops: " << stopCount << "\n";
    cout << "   - Hospitals: " << hospitalCount << "\n";
    cout << "   - Schools: " << schoolCount << "\n";
    cout << "   - Malls: " << mallCount << "\n";
    cout << "   - Facilities: " << facilityCount << "\n";
    cout << "   - All modules interconnected in ONE unified graph! ?\n\n";


    // ============================================
    //    EXTRACTING SUBGRAPHS
    // ============================================
    cout << "\n BUILDING MODULE SUBGRAPHS FROM MASTER GRAPH\n";
    cout << "Master graph has " << totalNodes << " nodes\n\n";

    // Medical
    medicalSubgraph = cityGraph.extractSubgraphWithBridges("Hospital", "BusStop", nodeRegistry, totalNodes, medicalMapping.fullToSub, medicalMapping.subToFull);
    medicalMapping.nodeCount = medicalSubgraph.getVertices();
    cout << " Medical: " << medicalMapping.nodeCount << " nodes\n";

    // Education
    educationSubgraph = cityGraph.extractSubgraphWithBridges("School", "BusStop", nodeRegistry, totalNodes, educationMapping.fullToSub, educationMapping.subToFull);
    educationMapping.nodeCount = educationSubgraph.getVertices();
    cout << " Education: " << educationMapping.nodeCount << " nodes\n";

    // Commercial
    commercialSubgraph = cityGraph.extractSubgraphWithBridges("Mall", "BusStop", nodeRegistry, totalNodes, commercialMapping.fullToSub, commercialMapping.subToFull);
    commercialMapping.nodeCount = commercialSubgraph.getVertices();
    cout << " Commercial: " << commercialMapping.nodeCount << " nodes\n";

    // Facilities
    facilitiesSubgraph = cityGraph.extractSubgraphWithBridges("Facility", "BusStop", nodeRegistry, totalNodes, facilitiesMapping.fullToSub, facilitiesMapping.subToFull);
    facilitiesMapping.nodeCount = facilitiesSubgraph.getVertices();
    cout << " Facilities: " << facilitiesMapping.nodeCount << " nodes\n";

    // Transport
    transportSubgraph = cityGraph.extractSubgraph("BusStop", nodeRegistry, totalNodes, transportMapping.fullToSub, transportMapping.subToFull);
    transportMapping.nodeCount = transportSubgraph.getVertices();
    cout << " Transport: " << transportMapping.nodeCount << " nodes\n\n";

    cout << " ===ALL SUBGRAPHS BUILT===\n\n";
}


void SmartCity::findNearestSchool(int fromStopIndex) {
    if (fromStopIndex < 0 || fromStopIndex >= stopCount) {
        cout << "? Invalid stop index.\n";
        return;
    }

    if (schoolCount == 0) {
        cout << "? No schools loaded.\n";
        return;
    }

    cout << "\n FINDING NEAREST SCHOOL (Using Education Subgraph)...\n";
    cout << "Starting from: " << stops[fromStopIndex].name << "\n";
    cout << " Searching " << educationMapping.nodeCount << " nodes\n\n";

    int subgraphStart = mapToSubgraph(fromStopIndex, educationMapping);

    if (subgraphStart == -1) {
        cout << "? Start stop not in education subgraph.\n";
        return;
    }

    static int dist[500];
    static int parent[500];
    const int INF = 1000000000;

    for (int i = 0; i < educationMapping.nodeCount; i++) {
        dist[i] = INF;
        parent[i] = -1;
    }

    educationSubgraph.dijkstra(subgraphStart, dist, parent);

    int nearestSchoolSubNode = -1;
    int minDist = INF;

    for (int i = 0; i < educationMapping.nodeCount; i++) {
        int fullNode = mapFromSubgraph(i, educationMapping);
        int schoolStartNode = stopCount + hospitalCount;
        if (fullNode >= schoolStartNode && fullNode < schoolStartNode + schoolCount) {
            if (dist[i] < minDist) {
                minDist = dist[i];
                nearestSchoolSubNode = i;
            }
        }
    }

    if (nearestSchoolSubNode == -1 || minDist >= INF) {
        cout << "? No school reachable.\n";
        return;
    }

    int fullSchoolNode = mapFromSubgraph(nearestSchoolSubNode, educationMapping);
    int schoolIndex = fullSchoolNode - stopCount - hospitalCount;

    cout << "? NEAREST SCHOOL FOUND:\n";
    cout << "   Name: " << schools[schoolIndex].name << "\n";
    cout << "   Rating: " << (schools[schoolIndex].ranking / 10.0) << "/5.0\n";
    cout << "   Distance: " << (minDist / 1000.0) << " km\n\n";
}

/*
So firstly we validate that both stops exist then we run Dijkstra from starting stop to
the endinf stop and then we check if destination is reachable if it is then we calculate
total distance and time after that we reconstruct path by backtracking through
parent[] array then we display path forward with distances between each stop
*/

void SmartCity::shortestPathBetweenStops(int node1, int node2)
{
    if (node1 < 0 || node1 >= stopCount || node2 < 0 || node2 >= stopCount)
    {
        cout << "XXX Invalid stop indices.\n";
        return;
    }

    cout << "\n FINDING SHORTEST PATH \n";
    cout << "From: " << stops[node1].name << "\n";
    cout << "To: " << stops[node2].name << "\n";

    // Runing Dijkstra on master graph
    static int dist[500];
    static int parent[500];
    const int INF = 1000000000;

    for (int i = 0; i < totalNodes; i++)
    {
        dist[i] = INF;
        parent[i] = -1;
    }

    cityGraph.dijkstra(node1, dist, parent);

    //If path doesnt exist just checking the edge cases and error handling and returning basically
    if (dist[node2] >= INF)
    {
        cout << " No path exists between these stops.\n";

        // Checking if nodes have edges
        cout << "\n DEBUG: Checking node connectivity\n";
        AdjNode* edges1 = cityGraph.getAdjList(node1);
        AdjNode* edges2 = cityGraph.getAdjList(node2);

        int count1 = 0, count2 = 0;
        while (edges1)
        {
            count1++; edges1 = edges1->next;
        }
        while (edges2)
        {
            count2++; edges2 = edges2->next;
        }

        cout << stops[node1].name << " has " << count1 << " edges\n";
        cout << stops[node2].name << " has " << count2 << " edges\n";
        return;
    }

    cout << "  SHORTEST PATH FOUND:\n";
    cout << "   Distance: " << dist[node2] / 1000.0 << " km\n";
    cout << "   Estimated time: " << (int)(dist[node2] / 416.0) << " minutes\n\n";

    // Printing path
    cout << " PATH:\n";
    int path[100];
    int length = 0;
    int curr = node2;

    //Basically simple backtracking recording the parent of current node to find the path
    while (curr != -1 && length < 100)
    {
        path[length++] = curr;
        curr = parent[curr];
    }

    // Reversing and display
    for (int i = length - 1; i >= 0; i--)
    {
        int nodeIdx = path[i];
        if (nodeIdx < stopCount)
        {
            cout << "   " << (length - i) << ". " << stops[nodeIdx].name;

            // Showing distance to next node if available
            if (i > 0)
            {
                int nextIdx = path[i - 1];
                AdjNode* edge = cityGraph.getAdjList(nodeIdx);
                while (edge)
                {
                    if (edge->vertex == nextIdx)
                    {
                        cout << " -> " << edge->weight << "m";
                        break;
                    }
                    edge = edge->next;
                }
            }
            cout << "\n";
        }
    }

    cout << "\nTotal stops: " << length << "\n";
}




// =====================================================================
//                     ISLAMABAD HIERARCHY TREE (N-ARY)
// =====================================================================
void SmartCity::buildIslamabadHierarchyTree()
{
    islamabadRoot = new TreeNode("Islamabad");

    // Sectors
    TreeNode* sectorF6 = new TreeNode("Sector F-6");
    TreeNode* sectorF7 = new TreeNode("Sector F-7");
    TreeNode* sectorG9 = new TreeNode("Sector G-9");
    TreeNode* sectorI8 = new TreeNode("Sector I-8");

    islamabadRoot->addChild(sectorF6);
    islamabadRoot->addChild(sectorF7);
    islamabadRoot->addChild(sectorG9);
    islamabadRoot->addChild(sectorI8);

    // F-6
    TreeNode* f6Street1 = new TreeNode("F-6 Street 1");
    TreeNode* f6Street2 = new TreeNode("F-6 Street 2");
    TreeNode* f6Street3 = new TreeNode("F-6 Street 3");
    sectorF6->addChild(f6Street1);
    sectorF6->addChild(f6Street2);
    sectorF6->addChild(f6Street3);

    f6Street1->addChild(new TreeNode("House 1"));
    f6Street1->addChild(new TreeNode("House 2"));
    f6Street1->addChild(new TreeNode("House 3"));
    f6Street1->addChild(new TreeNode("House 4"));
    f6Street1->addChild(new TreeNode("PIMS Hospital"));

    f6Street2->addChild(new TreeNode("House 1"));
    f6Street2->addChild(new TreeNode("House 2"));
    f6Street2->addChild(new TreeNode("House 3"));
    f6Street2->addChild(new TreeNode("Islamabad Model School"));

    f6Street3->addChild(new TreeNode("House 1"));
    f6Street3->addChild(new TreeNode("House 2"));

    // F-7
    TreeNode* f7Street1 = new TreeNode("F-7 Street 1");
    TreeNode* f7Street2 = new TreeNode("F-7 Street 2");
    sectorF7->addChild(f7Street1);
    sectorF7->addChild(f7Street2);

    f7Street1->addChild(new TreeNode("House 1"));
    f7Street1->addChild(new TreeNode("House 2"));
    f7Street1->addChild(new TreeNode("House 3"));
    f7Street1->addChild(new TreeNode("Shifa Hospital"));

    f7Street2->addChild(new TreeNode("House 1"));
    f7Street2->addChild(new TreeNode("House 2"));
    f7Street2->addChild(new TreeNode("FAST-NUCES"));

    // G-9
    TreeNode* g9Street1 = new TreeNode("G-9 Street 1");
    TreeNode* g9Street4 = new TreeNode("G-9 Street 4");
    sectorG9->addChild(g9Street1);
    sectorG9->addChild(g9Street4);

    g9Street1->addChild(new TreeNode("House 1"));
    g9Street1->addChild(new TreeNode("House 2"));
    g9Street1->addChild(new TreeNode("House 3"));

    g9Street4->addChild(new TreeNode("House 1"));
    g9Street4->addChild(new TreeNode("House 2"));
    g9Street4->addChild(new TreeNode("CDA Hospital"));

    // I-8
    TreeNode* i8Street1 = new TreeNode("I-8 Street 1");
    TreeNode* i8Margalla = new TreeNode("I-8 Margalla Road");
    sectorI8->addChild(i8Street1);
    sectorI8->addChild(i8Margalla);

    i8Street1->addChild(new TreeNode("House 1"));
    i8Street1->addChild(new TreeNode("House 2"));
    i8Street1->addChild(new TreeNode("House 3"));
    i8Street1->addChild(new TreeNode("House 4"));

    i8Margalla->addChild(new TreeNode("House 1"));
    i8Margalla->addChild(new TreeNode("House 2"));
    i8Margalla->addChild(new TreeNode("Polyclinic Hospital"));
    i8Margalla->addChild(new TreeNode("Army Public School"));

    cout << "Islamabad hierarchy tree built successfully.\n";
    cout << "Tree includes: 4 sectors, multiple streets, houses, hospitals, and schools.\n";
}

void SmartCity::displayIslamabadHierarchy()
{
    if (islamabadRoot == nullptr)
    {
        cout << "Hierarchy tree not built yet.\n";
        return;
    }

    cout << "\n========== ISLAMABAD CITY HIERARCHY ==========\n";
    TreeUtils::printTree(islamabadRoot, 0);
    cout << "==============================================\n";
}

//School tree
void SmartCity::buildSchoolSystemTree()
{
    schoolSystemRoot = new TreeNode("Islamabad Schools");

    for (int i = 0; i < schoolCount; i++)
    {
        TreeNode* schoolNode = new TreeNode(schools[i].name);
        schoolSystemRoot->addChild(schoolNode);


        TreeNode* scienceNode = new TreeNode("Science Department");
        TreeNode* artsNode = new TreeNode("Arts Department");
        TreeNode* computerNode = new TreeNode("Computer Department");

        schoolNode->addChild(scienceNode);
        schoolNode->addChild(artsNode);
        schoolNode->addChild(computerNode);


        scienceNode->addChild(new TreeNode("Class 9-Science"));
        scienceNode->addChild(new TreeNode("Class 10-Science"));
        scienceNode->addChild(new TreeNode("Class 11-Science"));
        scienceNode->addChild(new TreeNode("Class 12-Science"));


        artsNode->addChild(new TreeNode("Class 9-Arts"));
        artsNode->addChild(new TreeNode("Class 10-Arts"));
        artsNode->addChild(new TreeNode("Class 11-Arts"));
        artsNode->addChild(new TreeNode("Class 12-Arts"));


        computerNode->addChild(new TreeNode("Class 9-Computer"));
        computerNode->addChild(new TreeNode("Class 10-Computer"));
        computerNode->addChild(new TreeNode("Class 11-Computer"));
        computerNode->addChild(new TreeNode("Class 12-Computer"));
    }

    cout << "School system tree built successfully.\n";
    cout << "Tree includes: " << schoolCount << " schools, each with 3 departments and 12 classes.\n";
}


// =====================================================================
//                         POPULATION TREE
// =====================================================================
void SmartCity::buildPopulationTree()
{
    // Free old tree if needed
    if (populationRoot != nullptr)
    {
        TreeNode::deleteTree(populationRoot);
        populationRoot = nullptr;
    }

    populationRoot = new TreeNode("Population of Islamabad");

    for (int i = 0; i < citizenCount; i++) {
        Citizen& c = citizens[i];

        // Level 1: Sector
        TreeNode* sectorNode = TreeUtils::getOrCreateChild(populationRoot, c.sector);

        // Level 2: Street
        TreeNode* streetNode = TreeUtils::getOrCreateChild(sectorNode, c.street);

        // Level 3: House
        TreeNode* houseNode = TreeUtils::getOrCreateChild(streetNode, c.houseNo);

        // Level 4: Individual
        char personLabel[MAX_NAME];
        manualStrCopy(personLabel, c.name);   // you could append CNIC here if you want

        TreeNode* personNode = new TreeNode(personLabel);
        houseNode->addChild(personNode);
    }

    cout << " Population tree built: Sector -> Street -> House -> Individuals\n";
}




//Builds a min heap of hospitals based on emergency bed availability.
void SmartCity::buildHospitalPriorityQueue()
{
    hospitalPriorityQueue.clear();

    for (int i = 0; i < hospitalCount; i++)
    {
        int priority = -hospitals[i].emergencyBeds;
        hospitalPriorityQueue.insert(priority);
    }
}

void SmartCity::buildSchoolRankingQueue() {
    schoolRankingQueue.clear();

    for (int i = 0; i < schoolCount; i++) {
        int priority = -(int)(schools[i].ranking * 100);
        schoolRankingQueue.insert(priority);
    }
}


void SmartCity::listBusesPassingThroughStop(int stopIndex)
{
    //  Validation
    if (stopIndex < 0 || stopIndex >= stopCount)
    {
        cout << "XX ERROR: Invalid stop index " << stopIndex << "\n";
        cout << "Valid range: 0 to " << (stopCount - 1) << "\n";
        return;
    }

    if (busCount == 0)
    {
        cout << "XX No buses loaded in the system.\n";
        return;
    }

    cout << "\n========== Buses Passing Through " << stops[stopIndex].name << " ==========\n";

    int foundCount = 0;

    for (int i = 0; i < busCount; i++)
    {
        RouteNode* curr = buses[i].routeHead;
        bool found = false;

        // Check if this bus route contains the stop
        while (curr != nullptr)
        {
            if (curr->stopIndex == stopIndex)
            {
                found = true;
                break;
            }
            curr = curr->next;
        }

        if (found)
        {
            foundCount++;
            cout << foundCount << ". Bus " << buses[i].busNo
                << " (" << buses[i].company << ")\n";

            // Show current location of this bus
            if (buses[i].currentStopIndex >= 0 && buses[i].currentStopIndex < stopCount)
            {
                cout << "   Current Location: " << stops[buses[i].currentStopIndex].name << "\n";
            }
        }
    }

    if (foundCount == 0)
    {
        cout << " No buses pass through this stop.\n";
    }
    else
    {
        cout << "\nTotal buses: " << foundCount << "\n";
    }

    cout << "=======================================================\n";
}


// =====================================================================
//                         ANALYTICS MENU
// =====================================================================

void SmartCity::analyticsMenu()
{
    int ch;
    while (true)
    {
        cout << "\n========== ANALYTICS & REPORTS ==========\n";
        cout << "1. System Summary\n";
        cout << "2. Transport Statistics\n";
        cout << "3. Hospital Statistics\n";
        cout << "4. Pharmacy Inventory Report\n";
        cout << "5. Search Schools by Subject\n";
        cout << "6. Compare Two Hospitals\n";
        cout << "7. Compare Two Schools\n";
        cout << "8. Medicine Price Comparison\n";
        cout << "9. Validate Data Integrity\n";
        cout << "10 findPathBetweenAnyTwo " << endl;

        cout << "0. Back\n";
        cout << "Enter choice: ";
        cin >> ch;

        if (ch == 0) return;

        switch (ch)
        {
        case 1: generateSystemSummary(); break;
        case 2: generateTransportStatistics(); break;
        case 3: generateHospitalStatistics(); break;
        case 4: generatePharmacyInventoryReport(); break;
        case 5: searchSchoolsBySubject(); break;
        case 6: compareTwoHospitals(); break;
        case 7: compareTwoSchools(); break;
        case 8: compareMedicinePrices(); break;
        case 9: validateDataIntegrity(); break;
        case 10: findPathBetweenAnyTwo(); break;
        case 11: ; break;
        default: cout << "Invalid choice.\n";
        }

        waitForEnter();
    }
}


void SmartCity::educationMenu()
{
    while (true)
    {
        cout << "\n";
        cout << "═══════════════════════════════════════════════════════════\n";
        cout << "            EDUCATION SYSTEM MENU                    \n";
        cout << "═══════════════════════════════════════════════════════════\n";
        cout << "1.  Display All Schools\n";
        cout << "2.  Add New School\n";
        cout << "3.  Search Schools by Subject\n";
        cout << "4.  Search Schools by Level\n";
        cout << "5.  Find Nearest School\n";
        cout << "6.  Compare Two Schools\n";
        cout << "7.  School Performance Report\n";
        cout << "8.  Register Faculty\n";
        cout << "9.  Register Student\n";
        cout << "10. REALISTIC SCHOOL BUS TRACKING (Dijkstra)\n";  // ← NEW!
        cout << "11. Top how many schools you want to see ? " << endl;
        cout << "0.  Back to Main Menu\n";
        cout << "═══════════════════════════════════════════════════════════\n";
        cout << "Enter choice: ";

        int choice;
        cin >> choice;

        switch (choice) {
        case 1:
            displayAllSchools();
            break;

        case 2:
            addSchool();
            break;

        case 3:
            searchSchoolsBySubject();
            break;

        case 4:
            searchSchoolsByLevel();
            break;

        case 5: {
            cout << "Enter bus stop ID: ";
            int stopID;
            cin >> stopID;
            int idx = findStopIndexById(stopID);
            if (idx != -1) {
                findNearestSchool(idx);
            }
            else {
                cout << " Bus stop not found!\n";
            }
            break;
        }

        case 6:
            compareTwoSchools();
            break;

        case 7:
            generateSchoolPerformanceReport();
            break;

        case 8:
            registerFaculty();
            break;

        case 9:
            registerStudent();
            break;

        case 10:
            simulateRealisticSchoolBusRoute();
            break;
        case 11:  // Add after existing cases
        {
            int topN;
            cout << "Enter number of top schools to display: ";
            cin >> topN;
            displayTopSchools(topN);
            break;
        }
        case 0:

            return;

        default:
            cout << " Invalid choice! Please try again.\n";
        }

        waitForEnter();
    }
}


// =====================================================================
//                         POPULATION MENU
// =====================================================================
void SmartCity::populationMenu()
{
    int ch;
    while (true)
    {
        cout << "\n========== POPULATION MENU ==========\n";
        cout << "1. Display all citizens\n";
        cout << "2. Search citizen by CNIC\n";
        cout << "3. Display population tree\n";
        cout << "4. Add new citizen\n";
        cout << "5. Age distribution report\n";
        cout << "6. hahahahahaha";
        cout << "7. Population density by sector\n";
        cout << "8. Gender ratio report\n";
        cout << "9 Heat map for population\n";
        cout << "0. Back\n";
        cout << "Enter choice: ";
        cin >> ch;

        if (ch == 0) return;

        switch (ch) {
        case 1: displayAllCitizens(); break;
        case 2: searchCitizenByCNIC(); break;
        case 3: displayPopulationTree(); break;
        case 4: {
            addCitizen();
            buildPopulationTree();
            break;;
        }

        case 5: generateAgeDistributionReport(); break;
        case 6:  break;
        case 7: generatePopulationDensityReport(); break;
        case 8: generateGenderRatioReport(); break;
        case 9:
            generatePopulationHeatmap();
            break;
        default: cout << "Invalid choice.\n";
        }

        waitForEnter();
    }
}



// =====================================================================
//                         MEDICAL MENU
// =====================================================================
void SmartCity::medicalMenu() {
    int choice;
    while (true) {
        cout << "\n========================================" << endl;
        cout << "           MEDICAL SECTOR MENU          " << endl;
        cout << "========================================" << endl;
        cout << "1.  Display All Hospitals" << endl;
        cout << "2.  Display Top Hospitals (Emergency Beds)" << endl;
        cout << "3.  Find Nearest Hospital from Stop" << endl;
        cout << "4.  Compare Two Hospitals" << endl;
        cout << "5.  Search Hospitals by Specialization" << endl;
        cout << "----------------------------------------" << endl;
        cout << "6.  Display All Doctors" << endl;
        cout << "7.  Add New Doctor" << endl;
        cout << "8.  Search Doctor by Specialization" << endl;
        cout << "----------------------------------------" << endl;
        cout << "9.  Display All Patients" << endl;
        cout << "10. Add New Patient" << endl;
        cout << "11. Assign Patient to Doctor" << endl;
        cout << "12. Discharge Patient" << endl;
        cout << "----------------------------------------" << endl;
        cout << "13. Display All Pharmacies & Medicines" << endl;
        cout << "14. Search Medicine by Name" << endl;
        cout << "15. Search Medicine by Formula" << endl;
        cout << "16. Add New Medicine to Pharmacy" << endl;
        cout << "17. Compare Medicine Prices" << endl;
        cout << "18. Pharmacy Inventory Report" << endl;
        cout << "----------------------------------------" << endl;
        cout << "19. Generate Hospital Statistics" << endl;
        cout << "0.  Back to Main Menu" << endl;
        cout << "========================================" << endl;
        cout << "Enter choice: ";
        cin >> choice;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << " Invalid input!" << endl;
            continue;
        }

        switch (choice) {
        case 1:
            displayAllHospitals();
            break;
        case 2: {
            int n;
            cout << "Enter number of top hospitals to display: ";
            cin >> n;
            displayTopHospitals(n);
            break;
        }
        case 3: {
            int stopIdx;
            cout << "Enter stop index (0 to " << (stopCount - 1) << "): ";
            cin >> stopIdx;
            findNearestHospital(stopIdx);
            break;
        }
        case 4:
            compareTwoHospitals();
            break;
        case 5:
            searchHospitalsBySpecialization();
            break;
        case 6:
            displayAllDoctors();
            break;
        case 7:
            addDoctor();
            break;
        case 8:
            searchDoctorBySpecialization();
            break;
        case 9:
            displayAllPatients();
            break;
        case 10:
            addPatient();
            break;
        case 11:
            assignPatientToDoctor();
            break;
        case 12:
            dischargePatient();
            break;
        case 13:
            displayAllPharmacies();
            break;
        case 14: {
            char medName[100];
            cout << "Enter medicine name: ";
            cin.ignore(10000, '\n');
            cin.getline(medName, 100);
            searchMedicineByName(medName);
            break;
        }
        case 15: {
            char formula[100];
            cout << "Enter formula: ";
            cin.ignore(10000, '\n');
            cin.getline(formula, 100);
            searchMedicineByFormula(formula);
            break;
        }
        case 16:
            addMedicine();
            break;
        case 17:
            compareMedicinePrices();
            break;
        case 18:
            generatePharmacyInventoryReport();
            break;
        case 19:
            generateHospitalStatistics();
            break;
        case 0:
            return;
        default:
            cout << "? Invalid choice!" << endl;
        }

        waitForEnter();
    }
}

void SmartCity::addMedicine() {
    if (pharmacyCount >= MAX_PHARMACIES) {
        cout << "? Pharmacy records array is full!" << endl;
        return;
    }

    cout << "\n========================================" << endl;
    cout << "        ADD NEW MEDICINE RECORD         " << endl;
    cout << "========================================" << endl;

    char pharmacyID[10], pharmacyName[100], sector[20];
    char medicineName[100], formula[100];
    double price;

    cout << "Enter Pharmacy ID (e.g., P06): ";
    cin >> pharmacyID;

    cout << "Enter Pharmacy Name: ";
    cin.ignore(10000, '\n');
    cin.getline(pharmacyName, 100);

    cout << "Enter Sector (e.g., F-8): ";
    cin.getline(sector, 20);

    cout << "Enter Medicine Name: ";
    cin.getline(medicineName, 100);

    cout << "Enter Formula: ";
    cin.getline(formula, 100);

    cout << "Enter Price (Rs.): ";
    cin >> price;

    if (cin.fail()) {
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "? Invalid price!" << endl;
        return;
    }

    // Check if medicine already exists
    int existingKey = StringHash::hash(medicineName);
    int existingIdx = medicineNameHash.search(existingKey);
    if (existingIdx != -1) {
        cout << " WARNING: Medicine with this name already exists!" << endl;
        cout << "Existing: " << pharmacies[existingIdx].medicineName
            << " at " << pharmacies[existingIdx].pharmacyName << endl;
        cout << "Continue adding? (y/n): ";
        char confirm;
        cin >> confirm;
        if (confirm != 'y' && confirm != 'Y') {
            return;
        }
    }

    // Add to array
    PharmacyRecord& pr = pharmacies[pharmacyCount];
    manualStrCopy(pr.pharmacyID, pharmacyID);
    manualStrCopy(pr.pharmacyName, pharmacyName);
    manualStrCopy(pr.sector, sector);
    manualStrCopy(pr.medicineName, medicineName);
    manualStrCopy(pr.formula, formula);
    pr.price = price;

    // Update hash tables
    int nameKey = StringHash::hash(medicineName);
    int formulaKey = StringHash::hash(formula);
    medicineNameHash.insert(nameKey, pharmacyCount);
    medicineFormulaHash.insert(formulaKey, pharmacyCount);

    pharmacyCount++;

    cout << "\n? Medicine added successfully!" << endl;
    cout << "Pharmacy:  " << pharmacyName << endl;
    cout << "Medicine:  " << medicineName << endl;
    cout << "Formula:   " << formula << endl;
    cout << "Price:     Rs. " << price << endl;
    cout << "========================================" << endl;
}




// =====================================================================
//                         TRANSPORT MENU
// =====================================================================
void SmartCity::transportMenu()
{
    int ch;
    while (true)
    {
        cout << "\n========== TRANSPORT MENU ==========\n";
        cout << "1. Display all buses\n";
        cout << "2. Display all stops\n";
        cout << "3. Display specific bus route\n";
        cout << "4. List buses passing through a stop\n";
        cout << "5. Shortest path between stops\n";
        cout << "6. Find nearest bus to your location\n";
        cout << "7. Add new bus stop\n";
        cout << "8. Add new bus\n";
        cout << "9. Add stop to bus route\n";
        cout << "10. Update bus location\n";
        cout << "11. Delete stop from bus route\n";
        cout << "12. Search buses by company\n";
        cout << "13. Find common stops between buses\n";
        cout << "14. Calculate bus route distance\n";
        cout << "15. Find all routes between stops\n";
        cout << "16. Find nearest bus stop\n";
        cout << "17. Add Passenger to Queue\n";
        cout << "18. Display Passenger Queue\n";
        cout << "19. Simulate Passenger Boarding\n";
        cout << "20. Calculate Nearest Distance to Passenger\n";
        cout << "21 trnasport simulation" << endl;
        cout << "0. Back\n";
        cout << "Enter choice: ";
        cin >> ch;

        if (ch == 0) return;

        switch (ch) {
        case 1: displayAllBuses(); break;
        case 2: displayAllStops(); break;
        case 3: {
            char busNo[10];
            cout << "Enter bus number: ";
            cin >> busNo;
            int idx = findBusIndexByNumber(busNo);
            if (idx != -1) displayBusRoute(idx);
            else cout << "Bus not found.\n";
            break;
        }
        case 4: {
            int stopId;
            cout << "Enter Stop ID: ";
            cin >> stopId;
            int idx = findStopIndexById(stopId);
            if (idx != -1) listBusesPassingThroughStop(idx);
            else cout << "Stop not found.\n";
            break;
        }
        case 5: {
            int s, e;
            cout << "Enter source stop ID: ";
            cin >> s;
            cout << "Enter destination stop ID: ";
            cin >> e;
            int sIdx = findStopIndexById(s);
            int eIdx = findStopIndexById(e);
            if (sIdx != -1 && eIdx != -1) shortestPathBetweenStops(sIdx, eIdx);
            else cout << "Invalid stop IDs.\n";
            break;
        }
        case 6: findNearestBusToPassenger(); break;
        case 7: addBusStop(); break;
        case 8: addBus(); break;
        case 9: addStopToBusRoute(); break;
        case 10: updateBusLocation(); break;
        case 11: deleteStopFromBusRoute(); break;
        case 12: searchBusesByCompany(); break;
        case 13: findCommonStops(); break;
        case 14: calculateBusRouteDistance(); break;
        case 15: findAllRoutesBetweenStops(); break;
        case 16: findNearestBusStop(); break;
        case 17: addPassengerToQueue(); break;              // 
        case 18: displayPassengerQueue(); break;            // 
        case 19: simulatePassengerBoarding(); break;        // 
        case 20: calculateNearestDistanceToPassenger(); break; 
        case 21:simulateRealTimeRouting(); break;
        default: cout << "Invalid choice.\n";
        }

        waitForEnter();
    }
}



// =====================================================================
//                         MAIN MENU
// =====================================================================
void SmartCity::mainMenu() {
    int ch;
    while (true) {
        cout << "\n=============== SMART CITY SYSTEM ===============\n";
        cout << "Master Graph: " << totalNodes << " nodes\n";
        cout << "Subgraphs: Medical(" << medicalMapping.nodeCount
            << ") | Education(" << educationMapping.nodeCount
            << ") | Transport(" << transportMapping.nodeCount << ")\n";
        cout << "=================================================\n";
        cout << "1. Transport System\n";
        cout << "2. Education System\n";
        cout << "3. Medical System\n";
        cout << "4. Population System\n";
        cout << "5. Commercial Sector\n";
        cout << "6. Public Facilities\n";
        cout << "7. Display Islamabad Hierarchy\n";
        cout << "8. Analytics & Reports\n";
        cout << "9. Bonus Features\n";
        cout << "0. Exit\n";
        cout << "Enter choice: ";
        cin >> ch;

        if (ch == 0) return;

        switch (ch) {
        case 1: transportMenu(); break;
        case 2: educationMenu(); break;
        case 3: medicalMenu(); break;
        case 4:populationMenu(); break;
        case 5: commercialMenu(); break;
        case 6: publicFacilitiesMenu(); break;
        case 7: displayIslamabadHierarchy(); break;
        case 8: analyticsMenu(); break;
        case 9: {
            findRouteToAirport(); break;
            break;
        }
        default: cout << "Invalid choice.\n";
        }
    }
}


// =====================================================================
//                        LOAD EDUCATION DATA (CSV)
// =====================================================================
void SmartCity::loadEducationData(const char* schoolsFile)
{
    FILE* f = fopen(schoolsFile, "r");
    if (!f) {
        cout << " Schools file '" << schoolsFile << "' not found.\n";
        return;
    }

    char line[500];
    char parts[10][100];
    int n;

    schoolCount = 0;

    if (fgets(line, 500, f) == NULL)
    {
        fclose(f);
        cout << " Empty schools file.\n";
        return;
    }

    cout << "\n========== LOADING SCHOOLS ==========\n";

    while (fgets(line, 500, f))
    {
        // Remove trailing newline
        for (int i = 0; line[i] != '\0'; i++) {
            if (line[i] == '\n' || line[i] == '\r') {
                line[i] = '\0';
                break;
            }
        }

        // Use parseCSVLine instead of splitCSVLine
        splitCSVLine(line, parts, n);

        if (n < 5) {
            cout << "Skipping incomplete line\n";
            continue;
        }

        // Field 1: Name
        strCopy(schools[schoolCount].name, parts[1]);
        trimSpaces(schools[schoolCount].name);

        // Field 2: Sector
        strCopy(schools[schoolCount].sector, parts[2]);
        trimSpaces(schools[schoolCount].sector);

        // Field 3: Rating
        char ratingStr[20];
        strCopy(ratingStr, parts[3]);
        trimSpaces(ratingStr);
        double ratingValue = manualAtof(ratingStr);
        schools[schoolCount].ranking = (int)(ratingValue * 10);

        // Field 4: Subjects 
        schools[schoolCount].subjectCount = 0;

        char subjectsStr[200];
        strCopy(subjectsStr, parts[4]);
        trimSpaces(subjectsStr);

        // Remove quotes
        char cleanSubjects[200];
        int cleanIdx = 0;
        for (int i = 0; subjectsStr[i] != '\0'; i++) {
            if (subjectsStr[i] != '"') {
                cleanSubjects[cleanIdx++] = subjectsStr[i];
            }
        }
        cleanSubjects[cleanIdx] = '\0';

        // Parse subjects by comma
        char* saveptr = nullptr;
        char* token = manualStrtok(cleanSubjects, ",", &saveptr);

        while (token != nullptr && schools[schoolCount].subjectCount < 5) {
            trimSpaces(token);
            if (strLength(token) > 0) {
                strCopy(schools[schoolCount].subjects[schools[schoolCount].subjectCount], token);
                schools[schoolCount].subjectCount++;
            }
            token = manualStrtok(nullptr, ",", &saveptr);
        }

        // Fields 5 & 6 are Coordinates
        if (n >= 7) {
            schools[schoolCount].lat = manualAtof(parts[5]);
            schools[schoolCount].lon = manualAtof(parts[6]);
        }
        else {
            schools[schoolCount].lat = 33.6 + (schoolCount * 0.05);
            schools[schoolCount].lon = 73.0 + (schoolCount * 0.05);
        }

        schoolCount++;
        if (schoolCount >= MAX_SCHOOLS) break;
    }

    fclose(f);
    cout << "Education data loaded: " << schoolCount << " schools.\n";
}

// =====================================================================
//                        LOAD MEDICAL DATA (CSV)
// =====================================================================
void SmartCity::loadMedicalData(const char* hospitalsFile, const char* pharmaciesFile) {

    hospitalCount = 0;

    FILE* hFile = fopen(hospitalsFile, "r");
    if (hFile == nullptr) {
        cout << "ERROR: Could not open hospitals file: " << hospitalsFile << endl;
    }
    else {
        char line[500];

        if (fgets(line, 500, hFile) != nullptr) {
            cout << "Reading hospitals CSV..." << endl;
        }

        while (fgets(line, 500, hFile) != nullptr && hospitalCount < MAX_HOSPITALS) {
            for (int i = 0; line[i] != '\0'; i++) {
                if (line[i] == '\n' || line[i] == '\r') {
                    line[i] = '\0';
                    break;
                }
            }

            if (line[0] == '\0') continue;

            char fields[10][100];
            int fieldCount = 0;
            parseCSVLine(line, fields, fieldCount);

            cout << "Hospital line: " << fieldCount << " fields" << endl;

            if (fieldCount < 5) {
                cout << "WARNING: Skipping line with only " << fieldCount << " fields" << endl;
                continue;
            }

            for (int i = 0; i < fieldCount; i++) {
                trimSpaces(fields[i]);
            }

            Hospital& h = hospitals[hospitalCount];

            // Field 0: HospitalID
            manualStrCopy(h.hospitalID, fields[0]);

            // Field 1: Name
            manualStrCopy(h.name, fields[1]);

            // Field 2: Sector
            manualStrCopy(h.sector, fields[2]);

            // Field 3: Emergency Beds
            h.emergencyBeds = manualAtoi(fields[3]);


            h.specializationCount = 0;

            char specCopy[200];
            manualStrCopy(specCopy, fields[4]);

            char* saveptr = nullptr;
            char* token = manualStrtok(specCopy, ",", &saveptr);
            while (token != nullptr && h.specializationCount < 5) {
                trimSpaces(token);
                if (token[0] != '\0') {  // Not empty
                    manualStrCopy(h.specializations[h.specializationCount], token);
                    h.specializationCount++;
                }
                token = manualStrtok(nullptr, ",", &saveptr);
            }

            // Set default location (you don't have Lat/Lon in CSV)
            h.location.lat = 33.65 + (hospitalCount * 0.02);
            h.location.lon = 73.00 + (hospitalCount * 0.02);

            cout << "Loaded: " << h.name << " (" << h.hospitalID << ") - "
                << h.emergencyBeds << " beds" << endl;

            hospitalCount++;
        }

        fclose(hFile);
        cout << "Loaded " << hospitalCount << " hospitals from " << hospitalsFile << endl;
    }


    pharmacyCount = 0;

    FILE* pFile = fopen(pharmaciesFile, "r");
    if (pFile == nullptr) {
        cout << "ERROR: Could not open pharmacies file: " << pharmaciesFile << endl;
        return;
    }

    char line[500];

    if (fgets(line, 500, pFile) != nullptr) {
    }

    while (fgets(line, 500, pFile) != nullptr && pharmacyCount < MAX_PHARMACIES) {
        for (int i = 0; line[i] != '\0'; i++) {
            if (line[i] == '\n' || line[i] == '\r') {
                line[i] = '\0';
                break;
            }
        }

        if (line[0] == '\0') continue;

        char fields[10][100];
        int fieldCount = 0;
        splitCSVLine(line, fields, fieldCount);

        if (fieldCount < 6) {
            cout << "WARNING: Skipping pharmacy line with only " << fieldCount << " fields" << endl;
            continue;
        }

        for (int i = 0; i < fieldCount; i++) {
            trimSpaces(fields[i]);
        }

        PharmacyRecord& pr = pharmacies[pharmacyCount];

        // Field 0: PharmacyID
        manualStrCopy(pr.pharmacyID, fields[0]);

        // Field 1: Pharmacy Name
        manualStrCopy(pr.pharmacyName, fields[1]);

        // Field 2: Sector
        manualStrCopy(pr.sector, fields[2]);

        // Field 3: Medicine Name
        manualStrCopy(pr.medicineName, fields[3]);

        // Field 4: Formula
        manualStrCopy(pr.formula, fields[4]);

        // Field 5: Price
        pr.price = manualAtof(fields[5]);

        pharmacyCount++;
    }

    fclose(pFile);
    cout << "Loaded " << pharmacyCount << " pharmacy medicine records from " << pharmaciesFile << endl;
}

// =====================================================================
//                        LOAD TRANSPORT DATA (CSV)
// =====================================================================
void SmartCity::loadTransportData(const char* stopsFile, const char* busesFile)
{
    // ---------------------- LOAD STOPS ------------------------
    FILE* f1 = fopen(stopsFile, "r");
    if (!f1) {
        cout << "Stops file missing.\n";
        return;
    }

    char line[300];
    char parts[10][100];
    int n;
    stopCount = 0;

    fgets(line, 300, f1);

    cout << "\n========== LOADING STOPS ==========\n";

    while (fgets(line, 300, f1))
    {
        splitCSVLine(line, parts, n);

        if (n < 3) continue;

        int stopNum = manualAtoi(parts[0] + 4);
        stops[stopCount].id = stopNum;

        manualStrCopy(stops[stopCount].name, parts[1]);
        trimSpaces(stops[stopCount].name);

        char fullCoords[100];

        if (n >= 4) {
            int idx = 0;

            for (int i = 0; parts[2][i] != '\0'; i++) {
                fullCoords[idx++] = parts[2][i];
            }

            fullCoords[idx++] = ',';

            for (int i = 0; parts[3][i] != '\0'; i++) {
                fullCoords[idx++] = parts[3][i];
            }

            fullCoords[idx] = '\0';
        }
        else {
            manualStrCopy(fullCoords, parts[2]);
        }

        // Now clean the combined string: remove quotes, spaces, newlines
        char cleanCoords[50];
        int writeIdx = 0;

        for (int i = 0; fullCoords[i] != '\0'; i++) {
            char c = fullCoords[i];
            // Keep only digits, dots, and commas
            if ((c >= '0' && c <= '9') || c == '.' || c == ',') {
                cleanCoords[writeIdx++] = c;
            }
        }
        cleanCoords[writeIdx] = '\0';

        int commaIndex = -1;
        for (int i = 0; cleanCoords[i] != '\0'; i++) {
            if (cleanCoords[i] == ',') {
                commaIndex = i;
                break;
            }
        }

        if (commaIndex > 0) {
            char latStr[30];
            char lonStr[30];

            // Copy latitude 
            int j = 0;
            for (int i = 0; i < commaIndex; i++) {
                latStr[j++] = cleanCoords[i];
            }
            latStr[j] = '\0';

            // Copy longitude 
            j = 0;
            for (int i = commaIndex + 1; cleanCoords[i] != '\0'; i++) {
                lonStr[j++] = cleanCoords[i];
            }
            lonStr[j] = '\0';

            // Convert using standard atof
            stops[stopCount].location.lat = atof(latStr);
            stops[stopCount].location.lon = atof(lonStr);

            cout << "Stop" << stopNum << " [" << stops[stopCount].name << "] at ("
                << stops[stopCount].location.lat << ", "
                << stops[stopCount].location.lon << ")\n";
        }
        else {
            stops[stopCount].location.lat = 0.0;
            stops[stopCount].location.lon = 0.0;
            cout << "WARNING: Could not parse coordinates for Stop" << stopNum << "\n";
        }

        stopCount++;
        if (stopCount >= MAX_STOPS) break;
    }
    fclose(f1);

    cout << "\nTotal stops loaded: " << stopCount << "\n\n";

    cout << "Building stop index hash table...\n";
    for (int i = 0; i < stopCount; i++)
    {
        int key = stops[i].id;
        stopIdToIndex.insert(key, i);
    }
    cout << "Stop hash table ready.\n\n";

    // ---------------------- LOAD BUSES ------------------------
    FILE* f2 = fopen(busesFile, "r");
    if (!f2) {
        cout << "Buses file missing.\n";
        return;
    }

    busCount = 0;
    fgets(line, 300, f2);

    cout << "========== LOADING BUSES ==========\n";

    while (fgets(line, 300, f2))
    {
        splitCSVLine(line, parts, n);

        //  BusNo, Company, CurrentStop, Route
        if (n < 4) {
            cout << "Skipping incomplete bus line (need 4 fields)\n";
            continue;
        }

        //  Bus Number
        manualStrCopy(buses[busCount].busNo, parts[0]);
        trimSpaces(buses[busCount].busNo);

        // Company
        manualStrCopy(buses[busCount].company, parts[1]);
        trimSpaces(buses[busCount].company);

        // Current Stop (e.g., "Stop3")
        char currentStopStr[50];
        manualStrCopy(currentStopStr, parts[2]);
        trimSpaces(currentStopStr);

        // Extract number from "Stop3" -> 3
        int currStopNum = manualAtoi(currentStopStr + 4);
        buses[busCount].currentStopIndex = findStopIndexById(currStopNum);

        if (buses[busCount].currentStopIndex == -1) {
            cout << "WARNING: Bus " << buses[busCount].busNo
                << " has invalid current stop: " << currentStopStr << "\n";
        }

        // Route
        buses[busCount].routeHead = nullptr;
        buses[busCount].routeTail = nullptr;

        char routeCopy[200];
        manualStrCopy(routeCopy, parts[3]);
        trimSpaces(routeCopy);

        // Remove " > " separators and extract stop numbers
        for (int i = 0; routeCopy[i] != '\0'; i++) {
            if (routeCopy[i] == '>' || routeCopy[i] == '\n' || routeCopy[i] == '\r') {
                routeCopy[i] = ' ';
            }
        }

        // Now parse: "Stop1  Stop2  Stop3  Stop4"
        char* saveptr;
        char* token = manualStrtok(routeCopy, " ", &saveptr);

        while (token != nullptr)
        {
            if (token[0] == '\0') {
                token = manualStrtok(nullptr, " ", &saveptr);
                continue;
            }

            // Extract stop number from "Stop1" -> 1
            if (token[0] == 'S' && token[1] == 't' && token[2] == 'o' && token[3] == 'p') {
                int stopNum = manualAtoi(token + 4);
                int stopIdx = findStopIndexById(stopNum);

                if (stopIdx >= 0) {
                    RouteNode* rn = new RouteNode(stopIdx);

                    if (buses[busCount].routeHead == nullptr) {
                        buses[busCount].routeHead = rn;
                        buses[busCount].routeTail = rn;
                    }
                    else {
                        buses[busCount].routeTail->next = rn;
                        buses[busCount].routeTail = rn;
                    }
                }
            }

            token = manualStrtok(nullptr, " ", &saveptr);
        }

        //  Debug output
        cout << " Bus " << buses[busCount].busNo
            << " (" << buses[busCount].company << ")";

        if (buses[busCount].currentStopIndex >= 0 &&
            buses[busCount].currentStopIndex < stopCount) {
            cout << " - Currently at: " << stops[buses[busCount].currentStopIndex].name;
        }
        cout << "\n";

        // Show route
        cout << "   Route: ";
        RouteNode* curr = buses[busCount].routeHead;
        while (curr != nullptr) {
            if (curr->stopIndex >= 0 && curr->stopIndex < stopCount) {
                cout << stops[curr->stopIndex].name;
                if (curr->next != nullptr) cout << " > ";
            }
            curr = curr->next;
        }
        cout << "\n";

        busCount++;
        if (busCount >= MAX_BUSES) break;
    }
    fclose(f2);

    cout << "\nTotal buses loaded: " << busCount << "\n";
    cout << "? Transport data loaded successfully!\n\n";
}


// =========================================
//   DISPLAYING FUNCTIONS
// =========================================
void SmartCity::displayAllBuses() {
    cout << "\n========== ALL BUSES ==========\n";

    if (busCount == 0) {
        cout << "No buses loaded.\n";
        return;
    }

    for (int i = 0; i < busCount; i++) {
        cout << "Bus #" << (i + 1) << ":\n";
        cout << "  Bus Number: " << buses[i].busNo << "\n";
        cout << "  Company: " << buses[i].company << "\n";

        if (buses[i].currentStopIndex >= 0 && buses[i].currentStopIndex < stopCount) {
            cout << "  Current Stop: " << stops[buses[i].currentStopIndex].name << "\n";
        }
        else {
            cout << "  Current Stop: Unknown\n";
        }

        cout << "  Route: ";
        RouteNode* curr = buses[i].routeHead;
        while (curr != nullptr) {
            if (curr->stopIndex >= 0 && curr->stopIndex < stopCount) {
                cout << stops[curr->stopIndex].name;
                if (curr->next != nullptr) cout << " > ";
            }
            curr = curr->next;
        }
        cout << "\n\n";
    }
}

void SmartCity::displayAllStops() {
    cout << "\n========== ALL BUS STOPS ==========\n";

    if (stopCount == 0) {
        cout << "No stops loaded.\n";
        return;
    }

    for (int i = 0; i < stopCount; i++) {
        cout << "Stop #" << (i + 1) << ":\n";
        cout << "  ID: " << stops[i].id << "\n";
        cout << "  Name: " << stops[i].name << "\n";
        cout << "  Coordinates: (" << stops[i].location.lat
            << ", " << stops[i].location.lon << ")\n\n";
    }
}


/*
Validating the bus index and then displaying bus details (number, company) and then
starting at route head we traverse the singly linked list for each node displaying
stop information and continuing it until reaching end of route
*/
void SmartCity::displayBusRoute(int busIndex)
{
    if (busIndex < 0 || busIndex >= busCount)
    {
        cout << "XX ERROR: Invalid bus index " << busIndex << "\n";
        cout << "Valid range: 0 to " << (busCount - 1) << "\n";
        return;
    }

    if (busCount == 0)
    {
        cout << "XX No buses loaded in the system.\n";
        return;
    }

    cout << "\n========== Bus Route Details ==========\n";
    cout << "Bus Number: " << buses[busIndex].busNo << "\n";
    cout << "Company: " << buses[busIndex].company << "\n";
    cout << "Route Stops:\n";
    cout << "---------------------------------------\n";

    RouteNode* curr = buses[busIndex].routeHead;
    int stopNum = 1;

    if (curr == nullptr)
    {
        cout << "XX No route defined for this bus.\n";
        return;
    }

    while (curr != nullptr)
    {
        int idx = curr->stopIndex;

        if (idx >= 0 && idx < stopCount)
        {
            cout << stopNum << ". " << stops[idx].name << " (Stop ID: " << stops[idx].id << ")\n";
        }
        else
        {
            cout << "XX Invalid stop index " << idx << " found in route \n";
        }

        stopNum++;
        curr = curr->next;
    }

    cout << "=======================================\n";
}



void SmartCity::displayAllHospitals() {
    cout << "\n========== ALL HOSPITALS ==========\n";

    if (hospitalCount == 0) {
        cout << "? No hospitals loaded.\n";
        return;
    }

    for (int i = 0; i < hospitalCount; i++) {
        cout << "\n Hospital #" << (i + 1) << ":\n";
        cout << "   ID: " << hospitals[i].hospitalID << "\n";
        cout << "   Name: " << hospitals[i].name << "\n";
        cout << "   Sector: " << hospitals[i].sector << "\n";
        cout << "   Emergency Beds: " << hospitals[i].emergencyBeds << "\n";

        cout << "   Specializations: ";
        for (int j = 0; j < hospitals[i].specializationCount; j++) {
            cout << hospitals[i].specializations[j];
            if (j < hospitals[i].specializationCount - 1) cout << ", ";
        }
        cout << "\n";

        cout << "   Location: (" << hospitals[i].location.lat
            << ", " << hospitals[i].location.lon << ")\n";
    }

    cout << "\nTotal Hospitals: " << hospitalCount << "\n";
    cout << "===================================\n";
}



void SmartCity::displayAllSchools() {
    cout << "\n========== ALL SCHOOLS ==========\n";

    if (schoolCount == 0) {
        cout << "No schools loaded.\n";
        return;
    }

    for (int i = 0; i < schoolCount; i++) {
        cout << "School #" << (i + 1) << ":\n";
        cout << "  Name: " << schools[i].name << "\n";
        cout << "  Ranking: " << (schools[i].ranking / 10.0) << "/5.0\n\n";
    }
}

void SmartCity::displayAllCitizens() {
    cout << "\n========== ALL CITIZENS ==========\n";

    if (citizenCount == 0) {
        cout << "No citizens loaded.\n";
        return;
    }

    for (int i = 0; i < citizenCount; i++) {
        cout << "Citizen #" << (i + 1) << ":\n";
        cout << "  CNIC: " << citizens[i].cnic << "\n";
        cout << "  Name: " << citizens[i].name << "\n";
        cout << "Sector: " << citizens[i].sector << "\n";
        cout << "Street: " << citizens[i].street << "\n";
        cout << "House No: " << citizens[i].houseNo << "\n";
    }
}


// =========================================
//   SEARCHING FUNCTIONS
// =========================================

void SmartCity::searchCitizenByCNIC() {
    char cnic[20];
    cout << "Enter CNIC (e.g., 61101-1111111-1): ";
    cin >> cnic;

    int idx = findCitizenIndexByCNIC(cnic);

    if (idx == -1) {
        cout << "Citizen not found.\n";
        return;
    }

    cout << "\n========== CITIZEN DETAILS ==========\n";
    cout << "CNIC: " << citizens[idx].cnic << "\n";
    cout << "Name: " << citizens[idx].name << "\n";
    cout << "Sector: " << citizens[idx].sector << "\n";
    cout << "Street: " << citizens[idx].street << "\n";
    cout << "House No: " << citizens[idx].houseNo << "\n";


}
/*
Basic simple logic as for the stops that first we validate and then we run Dijkstra
from that stop to calculate distances to ALL nodes and then we extract distances to all
hospitals after that we insert hospital distances into MinHeap (for priority ranking) and
sort hospitals by distance and lastly display top 3 nearest hospitals with full details
*/
void SmartCity::findNearestHospital(int fromStopIndex)
{
    if (fromStopIndex < 0 || fromStopIndex >= stopCount)
    {
        cout << "Invalid stop index." << endl;
        return;
    }

    if (hospitalCount == 0)
    {
        cout << "No hospitals loaded." << endl;
        return;
    }

    cout << "FINDING NEAREST HOSPITAL" << endl;
    cout << "Starting from: " << stops[fromStopIndex].name << endl;

    static int dist[500];
    static int parent[500];
    const int INF = 1000000000;

    for (int i = 0; i < totalNodes; i++)
    {
        dist[i] = INF;
        parent[i] = -1;
    }

    cityGraph.dijkstra(fromStopIndex, dist, parent);

    MinHeap hospitalDistHeap(hospitalCount);

    struct HospitalInfo
    {
        int index;
        int distance;
    };

    HospitalInfo hospitalData[MAX_HOSPITALS];
    int validCount = 0;

    int hospitalStartNode = stopCount;
    for (int i = 0; i < hospitalCount; i++)
    {
        int hospitalNode = hospitalStartNode + i;

        if (hospitalNode < totalNodes && dist[hospitalNode] < INF)
        {
            hospitalData[validCount].index = i;
            hospitalData[validCount].distance = dist[hospitalNode];
            hospitalDistHeap.insert(dist[hospitalNode]);
            validCount++;
        }
    }

    if (validCount == 0)
    {
        cout << "No reachable hospitals from this stop." << endl;
        return;
    }

    for (int i = 0; i < validCount - 1; i++)
    {
        for (int j = i + 1; j < validCount; j++)
        {
            if (hospitalData[j].distance < hospitalData[i].distance)
            {
                HospitalInfo temp = hospitalData[i];
                hospitalData[i] = hospitalData[j];
                hospitalData[j] = temp;
            }
        }
    }

    cout << "\nTOP 3 NEAREST HOSPITALS" << endl;
    cout << "======================================" << endl;

    int displayCount = (validCount < 3) ? validCount : 3;
    for (int i = 0; i < displayCount; i++)
    {
        int idx = hospitalData[i].index;

        cout << "\n" << (i + 1) << ". " << hospitals[idx].name << endl;
        cout << "   Sector: " << hospitals[idx].sector << endl;
        cout << "   Distance: " << (hospitalData[i].distance / 1000.0) << " km" << endl;
        cout << "   Emergency Beds: " << hospitals[idx].emergencyBeds << endl;
        cout << "   Specializations: ";
        for (int s = 0; s < hospitals[idx].specializationCount; s++)
        {
            cout << hospitals[idx].specializations[s];
            if (s < hospitals[idx].specializationCount - 1)
                cout << ", ";
        }
        cout << endl;
    }
}


/*
Same logic just that now we take the coordinates as the location input from the user
and just tell them the distance from the nearest bus stop here we are using simple
distance formula as we dont know that location of user is on graph path or not
*/
/*This function identifies which bus is closest to the passenger’s current GPS location. First, it takes the passenger’s latitude and longitude as input and validates them. Then it loops through every bus stored in the system, and for each bus it retrieves the currentStopIndex, which tells us which bus stop that bus is presently located at. Using this index, the function accesses the stop’s stored GPS coordinates (latitude and longitude) and calculates the real-world distance between the passenger and that bus stop using the computeDistance() function, which applies the Haversine formula to compute distance in kilometers. The function keeps track of the bus with the smallest distance found so far, updating it whenever a closer bus is discovered. After checking all buses, it prints the details of the closest bus—its number, company, current stop name, and the computed distance. If no bus has a valid stop index, it reports that no nearest bus could be found. Overall, this function performs a simple linear scan through all buses and selects the one whose current stop is geographically closest to the passenger.*/
void SmartCity::findNearestBusToPassenger()
{
    double passengerLat, passengerLon;

    cout << "Enter your latitude: ";
    cin >> passengerLat;

    //Inputting the variables
    if (cin.fail())
    {
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "? Invalid latitude!\n";
        return;
    }

    cout << "Enter your longitude: ";
    cin >> passengerLon;

    if (cin.fail())
    {
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "? Invalid longitude!\n";
        return;
    }

    int bestBusIdx = -1;
    double bestDist = -1.0;

    //Simple looping through each bus stop and calculating the distance and storing the minimum one
    for (int i = 0; i < busCount; i++)
    {
        int currStop = buses[i].currentStopIndex;

        // Validate current stop index
        if (currStop < 0 || currStop >= stopCount)
        {
            continue;
        }

        double d = computeDistance(passengerLat, passengerLon, stops[currStop].location.lat,
            stops[currStop].location.lon);

        if (bestBusIdx == -1 || d < bestDist)
        {
            bestBusIdx = i;
            bestDist = d;
        }
    }

    //Displaying the result
    if (bestBusIdx != -1 && bestDist >= 0)
    {
        cout << "\n========== NEAREST BUS ==========\n";
        cout << "Bus Number: " << buses[bestBusIdx].busNo << "\n";
        cout << "Company: " << buses[bestBusIdx].company << "\n";

        int currStop = buses[bestBusIdx].currentStopIndex;
        if (currStop >= 0 && currStop < stopCount)
        {
            cout << "Current Stop: " << stops[currStop].name << "\n";
        }

        cout << "Distance: " << bestDist << " km\n";
        cout << "=================================\n";
    }
    else
    {
        cout << " No buses found or no buses at valid stops.\n";
    }
}


void SmartCity::searchBusesByCompany() {
    char company[MAX_STR];

    cout << "\n========== SEARCH BUSES BY COMPANY ==========\n";
    cout << "Enter company name: ";
    cin.ignore();
    cin.getline(company, MAX_STR);

    cout << "\nBuses operated by '" << company << "':\n";
    cout << "--------------------------------------------\n";

    bool found = false;

    for (int i = 0; i < busCount; i++) {
        // Case-insensitive comparison
        bool match = true;
        int j = 0;

        while (buses[i].company[j] != '\0' || company[j] != '\0') {
            char c1 = buses[i].company[j];
            char c2 = company[j];

            // Convert to lowercase
            if (c1 >= 'A' && c1 <= 'Z') c1 = c1 + 32;
            if (c2 >= 'A' && c2 <= 'Z') c2 = c2 + 32;

            if (c1 != c2) {
                match = false;
                break;
            }

            if (c1 == '\0' && c2 == '\0') break;
            j++;
        }

        if (match) {
            cout << "- Bus " << buses[i].busNo;
            if (buses[i].currentStopIndex >= 0 && buses[i].currentStopIndex < stopCount) {
                cout << " (Currently at: " << stops[buses[i].currentStopIndex].name << ")";
            }
            cout << "\n";
            found = true;
        }
    }

    if (!found) {
        cout << "No buses found for this company.\n";
    }

    cout << "=============================================\n";
}

void SmartCity::findCommonStops()
{
    if (busCount < 2)
    {
        cout << "? Need at least 2 buses to find common stops.\n";
        return;
    }

    // Display all buses
    cout << "\n========== ALL BUSES ==========\n";
    for (int i = 0; i < busCount; i++)
    {
        cout << (i + 1) << ". " << buses[i].busNo << " - " << buses[i].company << "\n";
    }
    cout << "================================\n";

    int bus1Num, bus2Num;
    cout << "\nEnter first bus number (1-" << busCount << "): ";
    cin >> bus1Num;
    cout << "Enter second bus number (1-" << busCount << "): ";
    cin >> bus2Num;

    // Validation
    if (bus1Num < 1 || bus1Num > busCount || bus2Num < 1 || bus2Num > busCount)
    {
        cout << "? Invalid bus selection.\n";
        return;
    }

    if (bus1Num == bus2Num)
    {
        cout << "Please select two different buses.\n";
        return;
    }

    int bus1Index = bus1Num - 1;
    int bus2Index = bus2Num - 1;

    cout << "\n========== Common Stops ==========\n";
    cout << "Between Bus " << buses[bus1Index].busNo
        << " and Bus " << buses[bus2Index].busNo << "\n";
    cout << "----------------------------------\n";

    int commonCount = 0;

    // Check each stop in bus1's route
    RouteNode* curr1 = buses[bus1Index].routeHead;

    while (curr1 != nullptr)
    {
        int stopIdx1 = curr1->stopIndex;

        // Search for this stop in bus2's route
        RouteNode* curr2 = buses[bus2Index].routeHead;
        bool found = false;

        while (curr2 != nullptr)
        {
            if (curr2->stopIndex == stopIdx1)
            {
                found = true;
                break;
            }
            curr2 = curr2->next;
        }

        if (found)
        {
            //  Validate stop index
            if (stopIdx1 >= 0 && stopIdx1 < stopCount)
            {
                commonCount++;
                cout << commonCount << ". " << stops[stopIdx1].name
                    << " (Stop ID: " << stops[stopIdx1].id << ")\n";
            }
        }

        curr1 = curr1->next;
    }

    if (commonCount == 0)
    {
        cout << "No common stops found between these buses.\n";
    }
    else
    {
        cout << "\nTotal common stops: " << commonCount << "\n";
    }

    cout << "==================================\n";
}


void SmartCity::calculateBusRouteDistance()
{
    if (busCount == 0)
    {
        cout << "? No buses loaded.\n";
        return;
    }

    // Display all buses
    cout << "\n========== ALL BUSES ==========\n";
    for (int i = 0; i < busCount; i++)
    {
        cout << (i + 1) << ". " << buses[i].busNo << " - " << buses[i].company << "\n";
    }
    cout << "================================\n";

    int busNum;
    cout << "\nEnter bus number (1-" << busCount << "): ";
    cin >> busNum;

    //  Validation
    if (busNum < 1 || busNum > busCount)
    {
        cout << "? Invalid selection.\n";
        return;
    }

    int busIndex = busNum - 1;

    RouteNode* curr = buses[busIndex].routeHead;

    if (curr == nullptr || curr->next == nullptr)
    {
        cout << "Bus has insufficient route data (need at least 2 stops).\n";
        return;
    }

    cout << "\n========== Bus Route Distance Calculation ==========\n";
    cout << "Bus: " << buses[busIndex].busNo << " (" << buses[busIndex].company << ")\n";
    cout << "----------------------------------------------------\n";

    double totalDistance = 0.0;
    int segmentNum = 1;

    while (curr != nullptr && curr->next != nullptr)
    {
        int idx1 = curr->stopIndex;
        int idx2 = curr->next->stopIndex;

        //  Validate indices
        if (idx1 < 0 || idx1 >= stopCount || idx2 < 0 || idx2 >= stopCount)
        {
            cout << "Segment " << segmentNum << ": Invalid stop index (skipped)\n";
            curr = curr->next;
            continue;
        }

        double dist = computeDistance(
            stops[idx1].location.lat, stops[idx1].location.lon,
            stops[idx2].location.lat, stops[idx2].location.lon
        );

        cout << segmentNum << ". " << stops[idx1].name << " ? " << stops[idx2].name
            << " : " << dist << " km\n";

        totalDistance += dist;
        segmentNum++;
        curr = curr->next;
    }

    cout << "----------------------------------------------------\n";
    cout << "Total Route Distance: " << totalDistance << " km\n";
    cout << "====================================================\n";
}


void SmartCity::findAllRoutesBetweenStops() {
    int stop1, stop2;

    cout << "\n========== FIND ALL ROUTES BETWEEN STOPS ==========\n";
    cout << "Enter first stop ID: ";
    cin >> stop1;
    cout << "Enter second stop ID: ";
    cin >> stop2;

    int idx1 = findStopIndexById(stop1);
    int idx2 = findStopIndexById(stop2);

    if (idx1 == -1 || idx2 == -1) {
        cout << "One or both stops not found.\n";
        return;
    }

    cout << "\nBuses connecting " << stops[idx1].name
        << " to " << stops[idx2].name << ":\n";
    cout << "----------------------------------------------------\n";

    bool found = false;

    for (int i = 0; i < busCount; i++) {
        bool hasStop1 = false;
        bool hasStop2 = false;

        RouteNode* curr = buses[i].routeHead;

        while (curr != nullptr) {
            if (curr->stopIndex == idx1) hasStop1 = true;
            if (curr->stopIndex == idx2) hasStop2 = true;
            curr = curr->next;
        }

        if (hasStop1 && hasStop2) {
            cout << "- Bus " << buses[i].busNo
                << " (" << buses[i].company << ")\n";
            found = true;
        }
    }

    if (!found) {
        cout << "No direct bus route found between these stops.\n";
    }

    cout << "====================================================\n";
}
/*
Firstly we get specialization from user then for each hospital we check for each specializations if match found
then we displays teh hospital details and all and we count and display the total matches
*/
void SmartCity::searchHospitalsBySpecialization()
{
    char searchSpec[MAX_STR];

    cout << "\n========== SEARCH HOSPITALS BY SPECIALIZATION ==========\n";
    cout << "Enter specialization (e.g., Cardiology, General): ";
    cin.ignore(10000, '\n');
    cin.getline(searchSpec, MAX_STR);

    cout << "\n## Hospitals with '" << searchSpec << "':\n";
    cout << "-------------------------------------------------------\n";

    bool found = false;

    for (int i = 0; i < hospitalCount; i++)
    {
        // Check each specialization for this hospital
        for (int j = 0; j < hospitals[i].specializationCount; j++)
        {
            bool match = false;

            char specLower[MAX_STR];
            char searchLower[MAX_STR];

            // Convert to lowercase for comparison
            int k = 0;
            for (int m = 0; hospitals[i].specializations[j][m] != '\0'; m++)
            {
                char c = hospitals[i].specializations[j][m];
                specLower[k++] = (c >= 'A' && c <= 'Z') ? (c + 32) : c;
            }
            specLower[k] = '\0';

            k = 0;
            for (int m = 0; searchSpec[m] != '\0'; m++)
            {
                char c = searchSpec[m];
                searchLower[k++] = (c >= 'A' && c <= 'Z') ? (c + 32) : c;
            }
            searchLower[k] = '\0';

            // Check if searchLower is in specLower
            for (int m = 0; specLower[m] != '\0'; m++)
            {
                bool submatch = true;
                for (int n = 0; searchLower[n] != '\0'; n++)
                {
                    if (specLower[m + n] != searchLower[n])
                    {
                        submatch = false;
                        break;
                    }
                }
                if (submatch)
                {
                    match = true;
                    break;
                }
            }

            if (match) {
                cout << "## " << hospitals[i].name << "\n";
                cout << "   Sector: " << hospitals[i].sector << "\n";
                cout << "   Specializations: ";
                for (int s = 0; s < hospitals[i].specializationCount; s++)
                {
                    cout << hospitals[i].specializations[s];
                    if (s < hospitals[i].specializationCount - 1) cout << ", ";
                }
                cout << "\n";
                cout << "   Emergency Beds: " << hospitals[i].emergencyBeds << "\n\n";
                found = true;
                break;
            }
        }
    }

    if (!found)
    {
        cout << "## No hospitals found with this specialization.\n";
    }

    cout << "========================================================\n";
}


// Calculate and find nearest bus stop to a passenger's location
void SmartCity::findNearestBusStop() {
    cout << "\n========== FIND NEAREST BUS STOP TO PASSENGER ==========\n";

    if (stopCount == 0) {
        cout << "? No bus stops available in the system.\n";
        return;
    }

    double passengerLat, passengerLon;

    cout << "Enter passenger location:\n";
    cout << "Latitude: ";
    cin >> passengerLat;
    cout << "Longitude: ";
    cin >> passengerLon;

    int nearestStopIdx = -1;
    double minDistance = -1.0;

    // Find nearest stop
    for (int i = 0; i < stopCount; i++) {
        double dist = computeDistance(
            passengerLat, passengerLon,
            stops[i].location.lat, stops[i].location.lon
        );

        if (nearestStopIdx == -1 || dist < minDistance) {
            nearestStopIdx = i;
            minDistance = dist;
        }
    }

    if (nearestStopIdx != -1) {
        cout << "\n NEAREST BUS STOP FOUND:\n";
        cout << "   Stop Name: " << stops[nearestStopIdx].name << "\n";
        cout << "   Stop ID: " << stops[nearestStopIdx].id << "\n";
        cout << "   Distance: " << minDistance << " km\n";
        cout << "   Location: (" << stops[nearestStopIdx].location.lat
            << ", " << stops[nearestStopIdx].location.lon << ")\n";
        cout << "   Walking time (approx): " << (int)(minDistance * 12) << " minutes\n";

        // List buses passing through this stop
        cout << "\n Buses passing through this stop:\n";
        listBusesPassingThroughStop(nearestStopIdx);
    }

    cout << "========================================================\n";
}
// Calculate nearest distance for a passenger by passenger number
void SmartCity::calculateNearestDistanceToPassenger() {
    cout << "\n========== CALCULATE NEAREST DISTANCE TO PASSENGER ==========\n";

    if (citizenCount == 0) {
        cout << "? No citizens/passengers registered in system.\n";
        return;
    }

    int passengerNum;
    cout << "Enter Passenger Number (1-" << citizenCount << "): ";
    cin >> passengerNum;

    if (passengerNum < 1 || passengerNum > citizenCount) {
        cout << "? Invalid passenger number!\n";
        return;
    }

    int passengerIdx = passengerNum - 1;

    cout << "\n PASSENGER DETAILS:\n";
    cout << "   Name: " << citizens[passengerIdx].name << "\n";
    cout << "   CNIC: " << citizens[passengerIdx].cnic << "\n";
    cout << "Sector: " << citizens[passengerIdx].sector << "\n";
    cout << "Street: " << citizens[passengerIdx].street << "\n";
    cout << "House No: " << citizens[passengerIdx].houseNo << "\n";

    // For simplicity, we'll use a sample location based on sector
    // In real implementation, you'd have exact coordinates for each citizen
    double passengerLat = 33.700;  // Default Islamabad center
    double passengerLon = 73.050;

    // Find nearest bus stop
    int nearestStopIdx = -1;
    double minStopDist = -1.0;

    for (int i = 0; i < stopCount; i++) {
        double dist = computeDistance(
            passengerLat, passengerLon,
            stops[i].location.lat, stops[i].location.lon
        );

        if (nearestStopIdx == -1 || dist < minStopDist) {
            nearestStopIdx = i;
            minStopDist = dist;
        }
    }

    // Find nearest hospital
    int nearestHospitalIdx = -1;
    double minHospitalDist = -1.0;

    for (int i = 0; i < hospitalCount; i++) {
        double dist = computeDistance(
            passengerLat, passengerLon,
            hospitals[i].location.lat, hospitals[i].location.lon
        );

        if (nearestHospitalIdx == -1 || dist < minHospitalDist) {
            nearestHospitalIdx = i;
            minHospitalDist = dist;
        }
    }

    //Find nearest school using lat/lon instead of location
    int nearestSchoolIdx = -1;
    double minSchoolDist = -1.0;

    for (int i = 0; i < schoolCount; i++) {
        double dist = computeDistance(
            passengerLat, passengerLon,
            schools[i].lat, schools[i].lon
        );

        if (nearestSchoolIdx == -1 || dist < minSchoolDist) {
            nearestSchoolIdx = i;
            minSchoolDist = dist;
        }
    }

    // Display results
    cout << "\nNEAREST FACILITIES TO PASSENGER:\n";
    cout << "=====================================================\n";

    if (nearestStopIdx != -1) {
        cout << "   Nearest Bus Stop:\n";
        cout << "   Name: " << stops[nearestStopIdx].name << "\n";
        cout << "   Distance: " << minStopDist << " km\n";
        cout << "   Walking time: ~" << (int)(minStopDist * 12) << " minutes\n\n";
    }

    if (nearestHospitalIdx != -1) {
        cout << "   Nearest Hospital:\n";
        cout << "   Name: " << hospitals[nearestHospitalIdx].name << "\n";
        cout << "   Distance: " << minHospitalDist << " km\n";
        cout << "   Travel time: ~" << (int)(minHospitalDist * 3) << " minutes\n\n";
    }

    if (nearestSchoolIdx != -1) {
        cout << "   Nearest School:\n";
        cout << "   Name: " << schools[nearestSchoolIdx].name << "\n";
        cout << "   Distance: " << minSchoolDist << " km\n";
        cout << "   Travel time: ~" << (int)(minSchoolDist * 4) << " minutes\n\n";
    }

    cout << "=====================================================\n";
}

/*
Just building an heap and using it as priority queue we are entering the negative value of heap so that
it can work as max heap as max emergency bed availability means max priority
*/
void SmartCity::displayTopHospitals(int n)
{
    if (n <= 0 || hospitalCount == 0)
    {
        cout << "No hospitals to display." << endl;
        return;
    }

    cout << " TOP " << n << " HOSPITALS BY EMERGENCY BEDS" << endl;
    cout << "=================================================" << endl;

    //Building a min heap for that
    MinHeap bedHeap(hospitalCount);

    struct HospitalBedInfo
    {
        int beds;
        int index;
    };

    HospitalBedInfo bedData[MAX_HOSPITALS];

    // Build heap AND array
    for (int i = 0; i < hospitalCount; i++)
    {
        bedData[i].beds = hospitals[i].emergencyBeds;
        bedData[i].index = i;
        bedHeap.insert(-hospitals[i].emergencyBeds);  // Heap for priority
    }

    //Edge case handling if the user demanded number is more than the number of hospitals we have
    int displayCount = (n < hospitalCount) ? n : hospitalCount;

    for (int i = 0; i < displayCount; i++)
    {
        if (bedHeap.isEmpty())
            break;

        int maxBeds = -bedHeap.extractMin();  // Get hospital with most beds

        // Find this hospital in array
        for (int j = 0; j < hospitalCount; j++)
        {
            if (bedData[j].beds == maxBeds)
            {
                int idx = bedData[j].index;

                cout << "\n" << (i + 1) << ". " << hospitals[idx].name << endl;
                cout << "   Sector: " << hospitals[idx].sector << endl;
                cout << "   Emergency Beds: " << hospitals[idx].emergencyBeds << endl;
                cout << "   Specializations: ";
                for (int s = 0; s < hospitals[idx].specializationCount; s++)
                {
                    cout << hospitals[idx].specializations[s];
                    if (s < hospitals[idx].specializationCount - 1)
                        cout << ", ";
                }
                cout << endl;

                bedData[j].beds = -1;  // Just so that dont extract it again 
                break;
            }
        }
    }
}


void SmartCity::addBusStop() {
    if (stopCount >= MAX_STOPS) {
        cout << "Stop array is full. Cannot add more stops.\n";
        return;
    }

    int id;
    char name[MAX_STR];
    double lat, lon;

    cout << "\n========== ADD NEW BUS STOP ==========\n";

    cout << "Enter Stop ID (number): ";
    cin >> id;

    if (cin.fail()) {
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "? Invalid input! Please enter a numeric ID.\n";
        return;
    }

    // Check if ID already exists
    if (findStopIndexById(id) != -1) {
        cout << "? Stop with this ID already exists.\n";
        cin.ignore(10000, '\n');
        return;
    }

    cout << "Enter Stop Name: ";
    cin.ignore(10000, '\n');
    cin.getline(name, MAX_STR);

    cout << "Enter Latitude: ";
    cin >> lat;

    if (cin.fail()) {
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "? Invalid latitude!\n";
        return;
    }

    cout << "Enter Longitude: ";
    cin >> lon;

    if (cin.fail()) {
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "? Invalid longitude!\n";
        return;
    }

    // Add to array
    stops[stopCount].id = id;
    strCopy(stops[stopCount].name, name);
    stops[stopCount].location.lat = lat;
    stops[stopCount].location.lon = lon;
    stopCount++;

    // Update hash table
    stopIdToIndex.insert(id, stopCount - 1);

    cout << "\n? Bus stop added successfully!\n";
    cout << "   ID: " << id << "\n";
    cout << "   Name: " << name << "\n";
    cout << "   Location: (" << lat << ", " << lon << ")\n";
    cout << "======================================\n";
}

void SmartCity::compareTwoHospitals() {
    char id1[10], id2[10];

    cout << "\n========== COMPARE TWO HOSPITALS ==========\n";
    cout << "Enter first hospital ID: ";
    cin >> id1;
    cout << "Enter second hospital ID: ";
    cin >> id2;

    int idx1 = findHospitalIndexById(id1);
    int idx2 = findHospitalIndexById(id2);

    if (idx1 == -1 || idx2 == -1) {
        cout << "? One or both hospitals not found.\n";
        return;
    }

    cout << "\n?? COMPARISON\n";
    cout << "--------------------------------------------\n";

    cout << "\n1??  " << hospitals[idx1].name << "\n";
    cout << "   ID: " << hospitals[idx1].hospitalID << "\n";
    cout << "   Sector: " << hospitals[idx1].sector << "\n";
    cout << "   Emergency Beds: " << hospitals[idx1].emergencyBeds << "\n";
    cout << "   Specializations: ";
    for (int i = 0; i < hospitals[idx1].specializationCount; i++) {
        cout << hospitals[idx1].specializations[i];
        if (i < hospitals[idx1].specializationCount - 1) cout << ", ";
    }
    cout << "\n";
    cout << "   Location: (" << hospitals[idx1].location.lat << ", "
        << hospitals[idx1].location.lon << ")\n";

    cout << "\n2??  " << hospitals[idx2].name << "\n";
    cout << "   ID: " << hospitals[idx2].hospitalID << "\n";
    cout << "   Sector: " << hospitals[idx2].sector << "\n";
    cout << "   Emergency Beds: " << hospitals[idx2].emergencyBeds << "\n";
    cout << "   Specializations: ";
    for (int i = 0; i < hospitals[idx2].specializationCount; i++) {
        cout << hospitals[idx2].specializations[i];
        if (i < hospitals[idx2].specializationCount - 1) cout << ", ";
    }
    cout << "\n";
    cout << "   Location: (" << hospitals[idx2].location.lat << ", "
        << hospitals[idx2].location.lon << ")\n";

    cout << "\n?? ANALYSIS\n";
    cout << "--------------------------------------------\n";

    if (hospitals[idx1].emergencyBeds > hospitals[idx2].emergencyBeds) {
        cout << "? " << hospitals[idx1].name << " has MORE emergency beds.\n";
    }
    else if (hospitals[idx2].emergencyBeds > hospitals[idx1].emergencyBeds) {
        cout << "? " << hospitals[idx2].name << " has MORE emergency beds.\n";
    }
    else {
        cout << "? Both hospitals have EQUAL emergency beds.\n";
    }

    cout << "============================================\n";
}


void SmartCity::addBus() {
    if (busCount >= MAX_BUSES) {
        cout << "Bus array is full. Cannot add more buses.\n";
        return;
    }

    char busNo[10];
    char company[MAX_STR];

    cout << "\n========== ADD NEW BUS ==========\n";
    cout << "Enter Bus Number (e.g., B101): ";
    cin >> busNo;

    // Check if bus already exists
    if (findBusIndexByNumber(busNo) != -1) {
        cout << "Bus with this number already exists.\n";
        return;
    }

    cout << "Enter Company Name: ";
    cin.ignore();
    cin.getline(company, MAX_STR);

    // Add to array
    manualStrCopy(buses[busCount].busNo, busNo);
    manualStrCopy(buses[busCount].company, company);
    buses[busCount].currentStopIndex = -1;
    buses[busCount].routeHead = nullptr;
    buses[busCount].routeTail = nullptr;

    busCount++;

    // Update hash table
    int key = extractNumberFromCode(busNo);
    if (key != -1) {
        busNumberToIndex.insert(key, busCount - 1);
    }

    cout << "Bus added successfully!\n";
    cout << "Note: Use 'Add Stop to Bus Route' to define the route.\n";
}


/*
Simple just asking which stop to append then checking weather it is already in the
route or not if not just inserting at tail function for linked list only
*/
void SmartCity::addStopToBusRoute()
{
    if (busCount == 0)
    {
        cout << "? No buses available. Add a bus first.\n";
        return;
    }

    if (stopCount == 0)
    {
        cout << "? No stops available. Add stops first.\n";
        return;
    }

    // Displaying all buses
    cout << "\n========== ALL BUSES ==========\n";
    for (int i = 0; i < busCount; i++)
    {
        cout << (i + 1) << ". " << buses[i].busNo << " - " << buses[i].company << "\n";
    }
    cout << "================================\n";

    int busNum;
    cout << "\nEnter bus number (1-" << busCount << "): ";
    cin >> busNum;

    // Validating the input
    if (busNum < 1 || busNum > busCount)
    {
        cout << " Invalid bus selection.\n";
        return;
    }

    int busIndex = busNum - 1;

    // Displaying current route
    cout << "\n========== Current Route for " << buses[busIndex].busNo << " ==========\n";
    RouteNode* curr = buses[busIndex].routeHead;
    int stopNum = 1;
    while (curr != nullptr)
    {
        if (curr->stopIndex >= 0 && curr->stopIndex < stopCount)
        {
            cout << stopNum << ". " << stops[curr->stopIndex].name << "\n";
        }
        stopNum++;
        curr = curr->next;
    }
    cout << "=============================================\n";

    // Displaying all stops
    cout << "\n========== ALL STOPS ==========\n";
    for (int i = 0; i < stopCount; i++)
    {
        cout << (i + 1) << ". " << stops[i].name << " (ID: " << stops[i].id << ")\n";
    }
    cout << "================================\n";

    int stopNum2;
    cout << "\nEnter stop number to add (1-" << stopCount << "): ";
    cin >> stopNum2;

    // Validating the stop
    if (stopNum2 < 1 || stopNum2 > stopCount)
    {
        cout << "XX  Invalid stop selection.\n";
        return;
    }

    int stopIndex = stopNum2 - 1;

    // Checking for duplicate
    curr = buses[busIndex].routeHead;
    while (curr != nullptr)
    {
        if (curr->stopIndex == stopIndex)
        {
            cout << "## This stop is already in the route!\n";
            return;
        }
        curr = curr->next;
    }

    // Adding stop to end of route
    RouteNode* newNode = new RouteNode(stopIndex);

    if (buses[busIndex].routeHead == nullptr)
    {
        buses[busIndex].routeHead = newNode;
        buses[busIndex].routeTail = newNode;
    }
    else
    {
        buses[busIndex].routeTail->next = newNode;
        buses[busIndex].routeTail = newNode;
    }

    cout << "## Stop '" << stops[stopIndex].name << "' added to bus "
        << buses[busIndex].busNo << " route successfully!\n";
}


void SmartCity::addHospital() {
    if (hospitalCount >= MAX_HOSPITALS) {
        cout << "? Hospital array is full.\n";
        return;
    }

    cout << "\n========== ADD NEW HOSPITAL ==========\n";

    char id[10], name[MAX_STR], sector[20];
    int beds;
    double lat, lon;

    cout << "Enter Hospital ID (e.g., H06): ";
    cin >> id;

    // Check if ID already exists
    if (findHospitalIndexById(id) != -1) {
        cout << "? Hospital with this ID already exists.\n";
        cin.ignore(10000, '\n');
        return;
    }

    cout << "Enter Hospital Name: ";
    cin.ignore(10000, '\n');
    cin.getline(name, MAX_STR);

    cout << "Enter Sector (e.g., G-8, F-10): ";
    cin >> sector;

    cout << "Enter Emergency Beds: ";
    cin >> beds;

    if (cin.fail()) {
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "? Invalid number!\n";
        return;
    }

    cout << "How many specializations? (1-5): ";
    int numSpecs;
    cin >> numSpecs;

    if (cin.fail() || numSpecs < 1 || numSpecs > 5) {
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "? Invalid number of specializations!\n";
        return;
    }

    cin.ignore(10000, '\n');

    hospitals[hospitalCount].specializationCount = numSpecs;

    for (int i = 0; i < numSpecs; i++) {
        cout << "Enter specialization " << (i + 1) << ": ";
        cin.getline(hospitals[hospitalCount].specializations[i], 50);
    }

    cout << "Enter Latitude: ";
    cin >> lat;

    if (cin.fail()) {
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "? Invalid latitude!\n";
        return;
    }

    cout << "Enter Longitude: ";
    cin >> lon;

    if (cin.fail()) {
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "? Invalid longitude!\n";
        return;
    }

    // Add to array
    strCopy(hospitals[hospitalCount].hospitalID, id);
    strCopy(hospitals[hospitalCount].name, name);
    strCopy(hospitals[hospitalCount].sector, sector);
    hospitals[hospitalCount].emergencyBeds = beds;
    hospitals[hospitalCount].location.lat = lat;
    hospitals[hospitalCount].location.lon = lon;

    hospitalCount++;

    // Update hash table
    int key = StringHash::hash(id);
    hospitalIdToIndex.insert(key, hospitalCount - 1);

    cout << "\n? Hospital added successfully!\n";
    cout << "   Name: " << name << "\n";
    cout << "   Sector: " << sector << "\n";
    cout << "   Emergency Beds: " << beds << "\n";
    cout << "   Specializations: ";
    for (int i = 0; i < numSpecs; i++) {
        cout << hospitals[hospitalCount - 1].specializations[i];
        if (i < numSpecs - 1) cout << ", ";
    }
    cout << "\n======================================\n";
}


void SmartCity::addSchool() {
    if (schoolCount >= MAX_SCHOOLS) {
        cout << "School array is full. Cannot add more schools.\n";
        return;
    }

    char name[MAX_STR];
    double rating;

    cout << "\n========== ADD NEW SCHOOL ==========\n";
    cout << "Enter School Name: ";
    cin.ignore();
    cin.getline(name, MAX_STR);

    cout << "Enter Rating (0.0 - 5.0): ";
    cin >> rating;

    if (rating < 0.0 || rating > 5.0) {
        cout << "Invalid rating. Must be between 0.0 and 5.0.\n";
        return;
    }

    // Add to array
    manualStrCopy(schools[schoolCount].name, name);
    schools[schoolCount].ranking = (int)(rating * 10);

    schoolCount++;

    cout << "School added successfully!\n";
}



//MOVING BUS
void SmartCity::updateBusLocation() {
    char busNo[10];
    int stopId;

    cout << "\n========== UPDATE BUS LOCATION ==========\n";
    cout << "Enter Bus Number: ";
    cin >> busNo;

    int busIdx = findBusIndexByNumber(busNo);
    if (busIdx == -1) {
        cout << "Bus not found.\n";
        return;
    }

    cout << "Enter Current Stop ID: ";
    cin >> stopId;

    int stopIdx = findStopIndexById(stopId);
    if (stopIdx == -1) {
        cout << "Stop not found.\n";
        return;
    }

    buses[busIdx].currentStopIndex = stopIdx;

    cout << "Bus " << busNo << " location updated to: " << stops[stopIdx].name << "\n";
}

void SmartCity::deleteStopFromBusRoute() {
    char busNo[10];
    int stopId;

    cout << "\n========== DELETE STOP FROM BUS ROUTE ==========\n";
    cout << "Enter Bus Number: ";
    cin >> busNo;

    int busIdx = findBusIndexByNumber(busNo);
    if (busIdx == -1) {
        cout << "Bus not found.\n";
        return;
    }

    cout << "Enter Stop ID to remove: ";
    cin >> stopId;

    int stopIdx = findStopIndexById(stopId);
    if (stopIdx == -1) {
        cout << "Stop not found.\n";
        return;
    }

    // Find and remove from linked list
    RouteNode* curr = buses[busIdx].routeHead;
    RouteNode* prev = nullptr;

    bool found = false;

    while (curr != nullptr) {
        if (curr->stopIndex == stopIdx) {
            found = true;

            if (prev == nullptr) {
                // Removing head
                buses[busIdx].routeHead = curr->next;
                if (buses[busIdx].routeTail == curr) {
                    buses[busIdx].routeTail = nullptr;
                }
            }
            else {
                prev->next = curr->next;
                if (buses[busIdx].routeTail == curr) {
                    buses[busIdx].routeTail = prev;
                }
            }

            delete curr;
            cout << "Stop removed from bus route.\n";
            break;
        }

        prev = curr;
        curr = curr->next;
    }

    if (!found) {
        cout << "Stop not found in this bus route.\n";
    }
}



void SmartCity::generateAgeDistributionReport()
{
    cout << "\n========== AGE DISTRIBUTION REPORT ==========\n";

    if (citizenCount == 0) {
        cout << "No citizens data available.\n";
        return;
    }

    // Age groups: 0-18, 19-30, 31-50, 51-65, 65+
    int ageGroups[5] = { 0, 0, 0, 0, 0 };

    for (int i = 0; i < citizenCount; i++) {
        int age = citizens[i].age;

        if (age <= 18)              ageGroups[0]++;
        else if (age <= 30)         ageGroups[1]++;
        else if (age <= 50)         ageGroups[2]++;
        else if (age <= 65)         ageGroups[3]++;
        else                        ageGroups[4]++;
    }

    cout << "Age Group Distribution:\n";
    cout << "  0-18 years  : " << ageGroups[0] << " citizens\n";
    cout << "  19-30 years : " << ageGroups[1] << " citizens\n";
    cout << "  31-50 years : " << ageGroups[2] << " citizens\n";
    cout << "  51-65 years : " << ageGroups[3] << " citizens\n";
    cout << "  65+ years   : " << ageGroups[4] << " citizens\n";

    cout << "\nTotal Citizens: " << citizenCount << "\n";
    cout << "==============================================\n";
}


void SmartCity::generateOccupationReport()
{
    cout << "\n========== OCCUPATION SUMMARY REPORT ==========\n";

    if (citizenCount == 0)
    {
        cout << "No citizens data available.\n";
        return;
    }

    // Count occurrences of each occupation
    // Since we don't have occupation in current struct, this is placeholder

    int engineers = 0;
    int teachers = 0;
    int doctors = 0;
    int students = 0;
    int business = 0;
    int others = 0;

    // Manual counting (you need to add occupation field to CSV/struct)
    // For now showing structure

    cout << "Occupation Breakdown:\n";
    cout << "  Engineers    : " << engineers << "\n";
    cout << "  Teachers     : " << teachers << "\n";
    cout << "  Doctors      : " << doctors << "\n";
    cout << "  Students     : " << students << "\n";
    cout << "  Business     : " << business << "\n";
    cout << "  Others       : " << others << "\n";

    cout << "\nTotal Citizens: " << citizenCount << "\n";
    cout << "===============================================\n";
}

void SmartCity::generatePopulationDensityReport() {
    cout << "\n========== POPULATION DENSITY REPORT ==========\n";

    if (citizenCount == 0) {
        cout << "No citizens data available.\n";
        return;
    }

    // Max distinct sectors we expect (adjust if needed)
    const int MAX_SECTORS = 50;

    char sectorNames[MAX_SECTORS][20];  // unique sector names
    int  sectorCounts[MAX_SECTORS];     // counts per sector
    int  sectorUsed = 0;

    // Initialize counts
    for (int i = 0; i < MAX_SECTORS; i++) {
        sectorCounts[i] = 0;
        sectorNames[i][0] = '\0';
    }

    // Collect counts per unique sector
    for (int i = 0; i < citizenCount; i++) {
        const char* sec = citizens[i].sector;

        // Find existing sector index (if any)
        int idx = -1;
        for (int j = 0; j < sectorUsed; j++) {
            if (manualStrCmp(sectorNames[j], sec) == 0) {
                idx = j;
                break;
            }
        }

        // If not found, add as new sector
        if (idx == -1) {
            if (sectorUsed < MAX_SECTORS) {
                manualStrCopy(sectorNames[sectorUsed], sec);
                sectorCounts[sectorUsed] = 1;
                sectorUsed++;
            }
            else {
                // Too many sectors lump into last one
                sectorCounts[sectorUsed - 1]++;
            }
        }
        else {
            sectorCounts[idx]++;
        }
    }

    // Print distribution
    cout << "Population Distribution by Sector:\n";
    cout << "--------------------------------------------\n";
    for (int i = 0; i < sectorUsed; i++) {
        cout << "  " << sectorNames[i] << " : " << sectorCounts[i] << " citizens\n";
    }

    cout << "\nTotal Population: " << citizenCount << "\n";

    // Find most populated sector
    if (sectorUsed > 0) {
        int maxPop = sectorCounts[0];
        int maxIdx = 0;
        for (int i = 1; i < sectorUsed; i++) {
            if (sectorCounts[i] > maxPop) {
                maxPop = sectorCounts[i];
                maxIdx = i;
            }
        }

        cout << "\nMost Populated Sector: " << sectorNames[maxIdx]
            << " (" << maxPop << " citizens)\n";
    }

    cout << "===============================================\n";
}

void SmartCity::generateGenderRatioReport() {
    cout << "\n========== GENDER RATIO REPORT ==========\n";

    if (citizenCount == 0) {
        cout << "No citizens data available.\n";
        return;
    }

    int male = 0;
    int female = 0;
    int other = 0;

    for (int i = 0; i < citizenCount; i++) {
        char g = citizens[i].gender;
        if (g == 'M' || g == 'm')      male++;
        else if (g == 'F' || g == 'f') female++;
        else                           other++;
    }

    cout << "Gender Distribution:\n";
    cout << "  Male   : " << male
        << " (" << (male * 100.0 / citizenCount) << "%)\n";
    cout << "  Female : " << female
        << " (" << (female * 100.0 / citizenCount) << "%)\n";
    cout << "  Other  : " << other
        << " (" << (other * 100.0 / citizenCount) << "%)\n";

    if (female > 0) {
        double ratio = (double)male / female;
        cout << "\nMale to Female Ratio: " << ratio << " : 1\n";
    }

    cout << "\nTotal Citizens: " << citizenCount << "\n";
    cout << "==========================================\n";
}


void SmartCity::generateHospitalStatistics() {
    cout << "\n========== HOSPITAL STATISTICS ==========\n";

    if (hospitalCount == 0) {
        cout << "No hospital data available.\n";
        return;
    }

    // Calculate total beds
    int totalBeds = 0;
    int minBeds = hospitals[0].emergencyBeds;
    int maxBeds = hospitals[0].emergencyBeds;

    for (int i = 0; i < hospitalCount; i++) {
        totalBeds += hospitals[i].emergencyBeds;

        if (hospitals[i].emergencyBeds < minBeds) {
            minBeds = hospitals[i].emergencyBeds;
        }

        if (hospitals[i].emergencyBeds > maxBeds) {
            maxBeds = hospitals[i].emergencyBeds;
        }
    }

    double avgBeds = (double)totalBeds / hospitalCount;

    cout << "\n?? HOSPITAL CAPACITY:\n";
    cout << "----------------------------------------\n";
    cout << "  Total Hospitals      : " << hospitalCount << "\n";
    cout << "  Total Emergency Beds : " << totalBeds << "\n";
    cout << "  Average Beds/Hospital: " << avgBeds << "\n";
    cout << "  Minimum Beds         : " << minBeds << "\n";
    cout << "  Maximum Beds         : " << maxBeds << "\n";

    // List top 3 hospitals
    cout << "\n?? TOP HOSPITALS BY CAPACITY:\n";
    cout << "----------------------------------------\n";

    // Simple bubble sort top 3
    int topIndices[3] = { -1, -1, -1 };
    int topBeds[3] = { 0, 0, 0 };

    for (int i = 0; i < hospitalCount; i++) {
        int beds = hospitals[i].emergencyBeds;

        if (beds > topBeds[0]) {
            topBeds[2] = topBeds[1];
            topIndices[2] = topIndices[1];
            topBeds[1] = topBeds[0];
            topIndices[1] = topIndices[0];
            topBeds[0] = beds;
            topIndices[0] = i;
        }
        else if (beds > topBeds[1]) {
            topBeds[2] = topBeds[1];
            topIndices[2] = topIndices[1];
            topBeds[1] = beds;
            topIndices[1] = i;
        }
        else if (beds > topBeds[2]) {
            topBeds[2] = beds;
            topIndices[2] = i;
        }
    }

    for (int i = 0; i < 3 && topIndices[i] != -1; i++) {
        cout << "  " << (i + 1) << ". " << hospitals[topIndices[i]].name
            << " - " << topBeds[i] << " beds\n";
    }

    cout << "\n==========================================\n";
}


void SmartCity::generateTransportStatistics() {
    cout << "\n========== TRANSPORT STATISTICS ==========\n";

    if (busCount == 0 || stopCount == 0) {
        cout << "No transport data available.\n";
        return;
    }

    // Count buses by company
    int daewoo = 0, niazi = 0, bilal = 0, others = 0;

    for (int i = 0; i < busCount; i++) {
        char* company = buses[i].company;

        // Simple string matching
        if (company[0] == 'D' || company[0] == 'd') {
            daewoo++;
        }
        else if (company[0] == 'N' || company[0] == 'n') {
            niazi++;
        }
        else if (company[0] == 'B' || company[0] == 'b') {
            bilal++;
        }
        else {
            others++;
        }
    }

    cout << "\n BUSES BY COMPANY:\n";
    cout << "----------------------------------------\n";
    cout << "  Daewoo Express : " << daewoo << " buses\n";
    cout << "  Niazi Express  : " << niazi << " buses\n";
    cout << "  Bilal Travels  : " << bilal << " buses\n";
    cout << "  Others         : " << others << " buses\n";

    // Calculate average route length
    int totalStopsInRoutes = 0;
    int validRoutes = 0;

    for (int i = 0; i < busCount; i++) {
        int routeLength = 0;
        RouteNode* curr = buses[i].routeHead;

        while (curr != nullptr) {
            routeLength++;
            curr = curr->next;
        }

        if (routeLength > 0) {
            totalStopsInRoutes += routeLength;
            validRoutes++;
        }
    }

    if (validRoutes > 0) {
        double avgLength = (double)totalStopsInRoutes / validRoutes;
        cout << "\n ROUTE STATISTICS:\n";
        cout << "  Average stops per route: " << avgLength << "\n";
    }

    cout << "\n TOTAL BUS STOPS: " << stopCount << "\n";
    cout << " TOTAL BUSES: " << busCount << "\n";

    cout << "\n==========================================\n";
}


void SmartCity::generatePharmacyInventoryReport() {
    cout << "\n========================================" << endl;
    cout << "    PHARMACY INVENTORY REPORT          " << endl;
    cout << "========================================" << endl;

    if (pharmacyCount == 0) {
        cout << "? No pharmacy data available." << endl;
        return;
    }

    // Total medicines
    cout << "?? Total Medicines in System: " << pharmacyCount << endl;

    // Find most/least expensive
    int maxIdx = 0, minIdx = 0;
    for (int i = 1; i < pharmacyCount; i++) {
        if (pharmacies[i].price > pharmacies[maxIdx].price) {
            maxIdx = i;
        }
        if (pharmacies[i].price < pharmacies[minIdx].price) {
            minIdx = i;
        }
    }

    cout << "\n Most Expensive:" << endl;
    cout << "  Medicine: " << pharmacies[maxIdx].medicineName << endl;
    cout << "  Price:    Rs. " << pharmacies[maxIdx].price << endl;
    cout << "  Pharmacy: " << pharmacies[maxIdx].pharmacyName << endl;

    cout << "\nLeast Expensive:" << endl;
    cout << "  Medicine: " << pharmacies[minIdx].medicineName << endl;
    cout << "  Price:    Rs. " << pharmacies[minIdx].price << endl;
    cout << "  Pharmacy: " << pharmacies[minIdx].pharmacyName << endl;

    // Average price
    double totalPrice = 0.0;
    for (int i = 0; i < pharmacyCount; i++) {
        totalPrice += pharmacies[i].price;
    }
    double avgPrice = totalPrice / pharmacyCount;

    cout << "\n? Average Medicine Price: Rs. " << avgPrice << endl;

    cout << "========================================" << endl;
}


void SmartCity::generateSystemSummary() {
    cout << "\n============ SMART CITY SYSTEM SUMMARY ============\n";

    cout << "\n?? SYSTEM STATISTICS:\n";
    cout << "---------------------------------------------\n";

    // Transport
    cout << "?? TRANSPORT SYSTEM:\n";
    cout << "   Total Bus Stops       : " << stopCount << "\n";
    cout << "   Total Buses           : " << busCount << "\n";
    cout << "   Graph Vertices        : " << cityGraph.getVertices() << "\n";

    // Education
    cout << "\n?? EDUCATION SYSTEM:\n";
    cout << "   Total Schools         : " << schoolCount << "\n";

    // Medical
    cout << "\n?? MEDICAL SYSTEM:\n";
    cout << "   Total Hospitals       : " << hospitalCount << "\n";
    cout << "   Total Medicines       : " << pharmacyCount << "\n";

    // Population
    cout << "\n?? POPULATION SYSTEM:\n";
    cout << "   Total Citizens        : " << citizenCount << "\n";

    // Commercial
    cout << "\n?? COMMERCIAL SECTOR:\n";
    cout << "   Total Malls           : " << mallCount << "\n";
    int totalProducts = 0;
    for (int i = 0; i < mallCount; i++) {
        totalProducts += malls[i].productCount;
    }
    cout << "   Total Products        : " << totalProducts << "\n";

    // Public Facilities
    cout << "\n??? PUBLIC FACILITIES:\n";
    cout << "   Total Facilities      : " << facilityCount << "\n";

    // Data Structures Summary
    cout << "\n?? DATA STRUCTURES IN USE:\n";
    cout << "   ? Graph (Adjacency List)\n";
    cout << "   ? N-ary Trees (3 types)\n";
    cout << "   ? Hash Tables (Separate Chaining)\n";
    cout << "   ? Priority Queue (Min Heap)\n";
    cout << "   ? Singly Linked Lists\n";
    cout << "   ? Stack (Route History)\n";
    cout << "   ? Circular Queue (Passengers)\n";

    cout << "\n===================================================\n";
}



// =====================================================================
//                         COMPARISONS
// =====================================================================



void SmartCity::compareTwoSchools() {
    int num1, num2;

    cout << "\n========== COMPARE TWO SCHOOLS ==========\n";

    if (schoolCount < 2) {
        cout << "Need at least 2 schools to compare.\n";
        return;
    }

    displayAllSchools();

    cout << "\nEnter first school number (1-" << schoolCount << "): ";
    cin >> num1;
    cout << "Enter second school number (1-" << schoolCount << "): ";
    cin >> num2;

    if (num1 < 1 || num1 > schoolCount || num2 < 1 || num2 > schoolCount) {
        cout << "Invalid school numbers.\n";
        return;
    }

    int idx1 = num1 - 1;
    int idx2 = num2 - 1;

    cout << "\n========== COMPARISON ==========\n";
    cout << "\nSchool 1: " << schools[idx1].name << "\n";
    cout << "  Rating: " << (schools[idx1].ranking / 10.0) << "/5.0\n";

    cout << "\nSchool 2: " << schools[idx2].name << "\n";
    cout << "  Rating: " << (schools[idx2].ranking / 10.0) << "/5.0\n";

    cout << "\n========== ANALYSIS ==========\n";

    if (schools[idx1].ranking > schools[idx2].ranking) {
        cout << schools[idx1].name << " has HIGHER rating.\n";
    }
    else if (schools[idx2].ranking > schools[idx1].ranking) {
        cout << schools[idx2].name << " has HIGHER rating.\n";
    }
    else {
        cout << "Both schools have EQUAL rating.\n";
    }

    cout << "================================\n";
}
//Compares prices of a specific medicine across all pharmacies
void SmartCity::compareMedicinePrices()
{
    if (pharmacyCount < 2)
    {
        cout << "XX Need at least 2 medicines to compare." << endl;
        return;
    }

    char med1[100], med2[100];

    cout << "COMPARE MEDICINE PRICES" << endl;
    cout << "Enter first medicine name: ";
    cin.ignore(10000, '\n');
    cin.getline(med1, 100);

    cout << "Enter second medicine name: ";
    cin.getline(med2, 100);

    int key1 = StringHash::hash(med1);
    int key2 = StringHash::hash(med2);

    int idx1 = medicineNameHash.search(key1);
    int idx2 = medicineNameHash.search(key2);

    if (idx1 == -1)
    {
        cout << "XXFirst medicine not found." << endl;
        return;
    }
    if (idx2 == -1) {
        cout << "XX Second medicine not found." << endl;
        return;
    }

    cout << "\n========== COMPARISON ==========" << endl;

    cout << "\n? Medicine 1:" << endl;
    cout << "  Name:     " << pharmacies[idx1].medicineName << endl;
    cout << "  Formula:  " << pharmacies[idx1].formula << endl;
    cout << "  Pharmacy: " << pharmacies[idx1].pharmacyName << endl;
    cout << "  Sector:   " << pharmacies[idx1].sector << endl;
    cout << "  Price:    Rs. " << pharmacies[idx1].price << endl;

    cout << "\n? Medicine 2:" << endl;
    cout << "  Name:     " << pharmacies[idx2].medicineName << endl;
    cout << "  Formula:  " << pharmacies[idx2].formula << endl;
    cout << "  Pharmacy: " << pharmacies[idx2].pharmacyName << endl;
    cout << "  Sector:   " << pharmacies[idx2].sector << endl;
    cout << "  Price:    Rs. " << pharmacies[idx2].price << endl;

    cout << "\n## Price Difference: Rs. ";
    if (pharmacies[idx1].price > pharmacies[idx2].price)
    {
        cout << (pharmacies[idx1].price - pharmacies[idx2].price);
        cout << " (" << pharmacies[idx1].medicineName << " is more expensive)" << endl;
    }
    else if (pharmacies[idx2].price > pharmacies[idx1].price)
    {
        cout << (pharmacies[idx2].price - pharmacies[idx1].price);
        cout << " (" << pharmacies[idx2].medicineName << " is more expensive)" << endl;
    }
    else
    {
        cout << "0 (Same price)" << endl;
    }

    cout << "================================" << endl;
}



void SmartCity::validateDataIntegrity()
{
    cout << "\n========== DATA INTEGRITY CHECK ==========\n";

    int issues = 0;

    // Check for buses with empty routes
    for (int i = 0; i < busCount; i++) {
        if (buses[i].routeHead == nullptr) {
            cout << "Warning: Bus " << buses[i].busNo << " has no route defined.\n";
            issues++;
        }
    }

    // Check for invalid current stop indices
    for (int i = 0; i < busCount; i++) {
        if (buses[i].currentStopIndex >= stopCount) {
            cout << "Error: Bus " << buses[i].busNo << " has invalid current stop index.\n";
            issues++;
        }
    }

    // Check for duplicate stop IDs
    for (int i = 0; i < stopCount; i++) {
        for (int j = i + 1; j < stopCount; j++) {
            if (stops[i].id == stops[j].id) {
                cout << "Warning: Duplicate stop ID " << stops[i].id << "\n";
                issues++;
            }
        }
    }

    // Check for duplicate bus numbers
    for (int i = 0; i < busCount; i++) {
        for (int j = i + 1; j < busCount; j++) {
            bool match = true;
            int k = 0;
            while (buses[i].busNo[k] != '\0' || buses[j].busNo[k] != '\0') {
                if (buses[i].busNo[k] != buses[j].busNo[k]) {
                    match = false;
                    break;
                }
                if (buses[i].busNo[k] == '\0') break;
                k++;
            }

            if (match) {
                cout << "Warning: Duplicate bus number " << buses[i].busNo << "\n";
                issues++;
            }
        }
    }

    if (issues == 0) {
        cout << "? All data integrity checks passed!\n";
    }
    else {
        cout << "\n" << issues << " issue(s) found.\n";
    }

    cout << "==========================================\n";
}


//Records a visited stop by pushing it onto a history stack.
void SmartCity::trackRouteHistory(int stopIndex)
{
    if (stopIndex >= 0 && stopIndex < stopCount)
    {
        routeHistoryStack.push(stopIndex);
        cout << "## Visited: " << stops[stopIndex].name << "\n";
    }
}


//Displays all visited stops in the route history most recent one is displayed first
void SmartCity::displayRouteHistory()
{
    cout << "\n========== ROUTE TRAVEL HISTORY ==========\n";

    if (routeHistoryStack.isEmpty())
    {
        cout << "No route history available.\n";
        return;
    }

    cout << "Recent stops (most recent first):\n";
    cout << "----------------------------------------\n";

    // Create temporary stack to preserve original
    Stack tempStack;
    int count = 1;

    while (!routeHistoryStack.isEmpty())
    {
        int stopIdx = routeHistoryStack.pop();
        tempStack.push(stopIdx);

        if (stopIdx >= 0 && stopIdx < stopCount)
        {
            cout << count << ". " << stops[stopIdx].name << "\n";
        }
        count++;
    }

    while (!tempStack.isEmpty())
    {
        routeHistoryStack.push(tempStack.pop());
    }

    cout << "==========================================\n";
}



void SmartCity::clearRouteHistory()
{
    while (!routeHistoryStack.isEmpty())
    {

        routeHistoryStack.pop();
    }
    cout << "? Route history cleared.\n";
}


/*
Get passenger ID from user then checks if queue is full if not full then it store
passenger at rear position and increment size counter
*/
void SmartCity::addPassengerToQueue()
{
    char passengerName[50];

    cout << "\n========== ADD PASSENGER TO QUEUE ==========\n";
    cout << "Enter passenger name: ";
    cin.ignore();
    cin.getline(passengerName, 50);

    static int passengerID = 1;

    if (!passengerQueue.isFull())
    {
        passengerQueue.enqueue(passengerID);
        cout << "## Passenger '" << passengerName << "' (ID: " << passengerID
            << ") added to boarding queue.\n";
        passengerID++;
    }
    else
    {
        cout << "## Queue is full. Cannot add passenger.\n";
    }
}




//Displays all passengers currently in the boarding queue without removing them
void SmartCity::displayPassengerQueue()
{
    cout << "\n========== PASSENGER QUEUE STATUS ==========\n";

    if (passengerQueue.isEmpty())
    {
        cout << "No passengers in queue.\n";
        return;
    }

    cout << "Passengers waiting (in order):\n";
    cout << "----------------------------------------\n";
    passengerQueue.display();
    cout << "\nTotal passengers in queue: " << passengerQueue.size() << "\n";
    cout << "============================================\n";
}

//Removes passengers from the queue as they board the bus(dequeue operation).
void SmartCity::simulatePassengerBoarding()
{
    cout << "\n========== PASSENGER BOARDING SIMULATION ==========\n";

    if (passengerQueue.isEmpty())
    {
        cout << "No passengers waiting to board.\n";
        return;
    }

    cout << "## Boarding passengers...\n\n";

    int boardCount = 0;
    int maxBoarding = 5; // Board up to 5 passengers

    while (!passengerQueue.isEmpty() && boardCount < maxBoarding)
    {
        int passengerID = passengerQueue.dequeue();
        cout << "## Passenger ID " << passengerID << " boarded successfully.\n";
        boardCount++;
    }

    cout << "\n## Boarding Summary:\n";
    cout << "   Total boarded: " << boardCount << " passengers\n";
    cout << "   Remaining in queue: " << passengerQueue.size() << "\n";

    if (passengerQueue.isEmpty())
    {
        cout << "   Status: Queue is now empty ?\n";
    }
    else {
        cout << "   Status: More passengers waiting...\n";
    }

    cout << "===================================================\n";
}

// Reads mall information from malls.csv file into the malls[] array
// If file doesn't exist, creating 2 sample malls.Each mall can hold up to 50 products

void SmartCity::loadCommercialData(const char* mallsFile)
{
    FILE* f = fopen(mallsFile, "r");
    if (!f) {
        cout << "Malls file missing. Creating sample data...\n";

        // Create sample malls if file doesn't exist
        manualStrCopy(malls[0].mallID, "M01");
        manualStrCopy(malls[0].name, "Centaurus Mall");
        malls[0].location.lat = 33.708;
        malls[0].location.lon = 73.041;
        malls[0].productCount = 0;

        manualStrCopy(malls[1].mallID, "M02");
        manualStrCopy(malls[1].name, "Safa Gold Mall");
        malls[1].location.lat = 33.720;
        malls[1].location.lon = 73.065;
        malls[1].productCount = 0;

        mallCount = 2;
        return;
    }

    char line[300];
    char parts[10][100];
    int n;

    mallCount = 0;

    fgets(line, 300, f);

    while (fgets(line, 300, f))
    {
        splitCSVLine(line, parts, n);

        if (n < 4)
            continue;

        manualStrCopy(malls[mallCount].mallID, parts[0]);
        trimSpaces(malls[mallCount].mallID);

        manualStrCopy(malls[mallCount].name, parts[1]);
        trimSpaces(malls[mallCount].name);

        malls[mallCount].location.lat = manualAtof(parts[2]);
        malls[mallCount].location.lon = manualAtof(parts[3]);
        malls[mallCount].productCount = 0;

        mallCount++;
        if (mallCount >= 20)
            break;
    }

    fclose(f);
    cout << "Commercial data loaded: " << mallCount << " malls.\n";
}



void SmartCity::displayAllMalls()
{
    cout << "\n========== ALL SHOPPING MALLS ==========\n";

    if (mallCount == 0)
    {
        cout << "No malls registered.\n";
        return;
    }

    for (int i = 0; i < mallCount; i++)
    {
        cout << "Mall #" << (i + 1) << ":\n";
        cout << "  ID: " << malls[i].mallID << "\n";
        cout << "  Name: " << malls[i].name << "\n";
        cout << "  Products Available: " << malls[i].productCount << "\n";
        cout << "  Location: (" << malls[i].location.lat
            << ", " << malls[i].location.lon << ")\n\n";
    }

    cout << "========================================\n";
}
// Inserting a new mall into the malls[] array at position mallCount.Checks for duplicate mallID 
// Updates mallIdToIndex hash table for the lookups

void SmartCity::addMall() {
    if (mallCount >= 20) {
        cout << "Mall array is full. Cannot add more malls.\n";
        return;
    }

    char mallID[10];
    char name[MAX_STR];
    double lat, lon;

    cout << "\n========== ADD NEW MALL ==========\n";
    cout << "Enter Mall ID (e.g., M01): ";
    cin >> mallID;

    // Check if ID already exists
    for (int i = 0; i < mallCount; i++) {
        bool match = true;
        int j = 0;
        while (malls[i].mallID[j] != '\0' || mallID[j] != '\0') {
            if (malls[i].mallID[j] != mallID[j]) {
                match = false;
                break;
            }
            if (malls[i].mallID[j] == '\0') break;
            j++;
        }

        if (match) {
            cout << "Mall with this ID already exists.\n";
            return;
        }
    }

    cout << "Enter Mall Name: ";
    cin.ignore();
    cin.getline(name, MAX_STR);

    cout << "Enter Latitude: ";
    cin >> lat;

    cout << "Enter Longitude: ";
    cin >> lon;

    // Add to array
    manualStrCopy(malls[mallCount].mallID, mallID);
    manualStrCopy(malls[mallCount].name, name);
    malls[mallCount].location.lat = lat;
    malls[mallCount].location.lon = lon;
    malls[mallCount].productCount = 0;

    mallCount++;

    // Update hash table
    int key = StringHash::hash(mallID);
    mallIdToIndex.insert(key, mallCount - 1);

    cout << "? Mall added successfully!\n";
}
//Taking a product (name, category, price) and adds it to specific mall
void SmartCity::addProductToMall() {
    char mallID[10];

    cout << "\n========== ADD PRODUCT TO MALL ==========\n";

    if (mallCount == 0) {
        cout << "No malls available. Please add a mall first.\n";
        return;
    }

    // Display all malls
    displayAllMalls();

    cout << "Enter Mall ID: ";
    cin >> mallID;

    // Find mall
    int mallIdx = -1;
    int key = StringHash::hash(mallID);
    mallIdx = mallIdToIndex.search(key);

    if (mallIdx == -1) {
        cout << "Mall not found.\n";
        return;
    }

    if (malls[mallIdx].productCount >= 50) {
        cout << "Product limit reached for this mall.\n";
        return;
    }

    char productName[MAX_STR];
    char category[50];
    int price;

    cout << "Enter Product Name: ";
    cin.ignore();
    cin.getline(productName, MAX_STR);

    cout << "Enter Category (Electronics/Clothing/Food/Books): ";
    cin.getline(category, 50);

    cout << "Enter Price: ";
    cin >> price;

    // Add product to mall
    int pIdx = malls[mallIdx].productCount;
    manualStrCopy(malls[mallIdx].products[pIdx].name, productName);
    manualStrCopy(malls[mallIdx].products[pIdx].category, category);
    malls[mallIdx].products[pIdx].price = price;

    malls[mallIdx].productCount++;

    // Add to product hash table (for quick search)
    int productKey = StringHash::hash(productName);
    productNameHash.insert(productKey, mallIdx); // Store mall index

    cout << "? Product added to " << malls[mallIdx].name << " successfully!\n";
}

// Findinga product by name across all malls using linear search
// Performs case insensitive string matching
void SmartCity::searchProductByName() {
    char productName[MAX_STR];

    cout << "\n========== SEARCH PRODUCT BY NAME ==========\n";
    cout << "Enter product name: ";
    cin.ignore();
    cin.getline(productName, MAX_STR);

    cout << "\nSearching for '" << productName << "'...\n";
    cout << "--------------------------------------------\n";

    bool found = false;

    // Search in all malls
    for (int i = 0; i < mallCount; i++) {
        for (int j = 0; j < malls[i].productCount; j++) {
            // Case insensitive comparison
            bool match = true;
            int k = 0;

            while (malls[i].products[j].name[k] != '\0' || productName[k] != '\0') {
                char c1 = malls[i].products[j].name[k];
                char c2 = productName[k];

                if (c1 >= 'A' && c1 <= 'Z') c1 = c1 + 32;
                if (c2 >= 'A' && c2 <= 'Z') c2 = c2 + 32;

                if (c1 != c2) {
                    match = false;
                    break;
                }

                if (c1 == '\0' && c2 == '\0') break;
                k++;
            }

            if (match) {
                cout << "\n? FOUND at " << malls[i].name << ":\n";
                cout << "   Product: " << malls[i].products[j].name << "\n";
                cout << "   Category: " << malls[i].products[j].category << "\n";
                cout << "   Price: PKR " << malls[i].products[j].price << "\n";
                found = true;
            }
        }
    }

    if (!found) {
        cout << "? Product not found in any mall.\n";
    }

    cout << "============================================\n";
}



void SmartCity::findNearestMall(int fromStopIndex) {
    if (fromStopIndex < 0 || fromStopIndex >= stopCount) {
        cout << "? Invalid stop index.\n";
        return;
    }

    if (mallCount == 0) {
        cout << "? No malls loaded.\n";
        return;
    }

    cout << "\n?? FINDING NEAREST MALL (Using Commercial Subgraph)...\n";
    cout << "Starting from: " << stops[fromStopIndex].name << "\n";
    cout << "?? Searching " << commercialMapping.nodeCount << " nodes\n\n";

    int subgraphStart = mapToSubgraph(fromStopIndex, commercialMapping);

    if (subgraphStart == -1) {
        cout << "? Start stop not in commercial subgraph.\n";
        return;
    }

    static int dist[500];
    static int parent[500];
    const int INF = 1000000000;

    for (int i = 0; i < commercialMapping.nodeCount; i++) {
        dist[i] = INF;
        parent[i] = -1;
    }

    commercialSubgraph.dijkstra(subgraphStart, dist, parent);

    int nearestMallSubNode = -1;
    int minDist = INF;

    for (int i = 0; i < commercialMapping.nodeCount; i++) {
        int fullNode = mapFromSubgraph(i, commercialMapping);
        int mallStartNode = stopCount + hospitalCount + schoolCount;
        if (fullNode >= mallStartNode && fullNode < mallStartNode + mallCount) {
            if (dist[i] < minDist) {
                minDist = dist[i];
                nearestMallSubNode = i;
            }
        }
    }

    if (nearestMallSubNode == -1 || minDist >= INF) {
        cout << "? No mall reachable.\n";
        return;
    }

    int fullMallNode = mapFromSubgraph(nearestMallSubNode, commercialMapping);
    int mallIndex = fullMallNode - stopCount - hospitalCount - schoolCount;

    cout << "? NEAREST MALL FOUND:\n";
    cout << "   Name: " << malls[mallIndex].name << "\n";
    cout << "   Distance: " << (minDist / 1000.0) << " km\n";
    cout << "   Products: " << malls[mallIndex].productCount << "\n\n";
}

void SmartCity::displayProductsByCategory() {
    char category[50];

    cout << "\n========== PRODUCTS BY CATEGORY ==========\n";
    cout << "Enter category (Electronics/Clothing/Food/Books): ";
    cin.ignore();
    cin.getline(category, 50);

    cout << "\nProducts in category '" << category << "':\n";
    cout << "-------------------------------------------\n";

    bool found = false;

    for (int i = 0; i < mallCount; i++) {
        for (int j = 0; j < malls[i].productCount; j++) {
            // Case-insensitive comparison
            bool match = true;
            int k = 0;

            while (malls[i].products[j].category[k] != '\0' || category[k] != '\0') {
                char c1 = malls[i].products[j].category[k];
                char c2 = category[k];

                if (c1 >= 'A' && c1 <= 'Z') c1 = c1 + 32;
                if (c2 >= 'A' && c2 <= 'Z') c2 = c2 + 32;

                if (c1 != c2) {
                    match = false;
                    break;
                }

                if (c1 == '\0' && c2 == '\0') break;
                k++;
            }

            if (match) {
                cout << "• " << malls[i].products[j].name
                    << " - PKR " << malls[i].products[j].price
                    << " (at " << malls[i].name << ")\n";
                found = true;
            }
        }
    }

    if (!found) {
        cout << "No products found in this category.\n";
    }

    cout << "===========================================\n";
}

void SmartCity::commercialMenu() {
    int ch;
    while (true) {
        cout << "\n========== COMMERCIAL SECTOR MENU ==========\n";
        cout << "1. Display all malls\n";
        cout << "2. Add new mall\n";
        cout << "3. Add product to mall\n";
        cout << "4. Search product by name\n";
        cout << "5. Find nearest mall to your location\n";
        cout << "6. Display products by category\n";
        cout << "0. Back\n";
        cout << "Enter choice: ";
        cin >> ch;

        if (ch == 0) return;

        switch (ch) {
        case 1: displayAllMalls(); break;
        case 2: addMall(); break;
        case 3: addProductToMall(); break;
        case 4: searchProductByName(); break;
        case 5: {
            int stopId;
            cout << "Enter your stop ID: ";
            cin >> stopId;
            int idx = findStopIndexById(stopId);
            if (idx != -1) {
                findNearestMall(idx);  //pass stop index
            }
            else {
                cout << "? Stop not found.\n";
            }
            break;
        }

        case 6: displayProductsByCategory(); break;
        default: cout << "Invalid choice.\n";
        }

        waitForEnter();
    }
}



void SmartCity::loadPublicFacilitiesData(const char* facilitiesFile)
{
    FILE* f = fopen(facilitiesFile, "r");
    if (!f) {
        cout << "Facilities file missing. Creating sample data...\n";

        // Create sample facilities
        manualStrCopy(facilities[0].facilityID, "F01");
        manualStrCopy(facilities[0].name, "Faisal Mosque");
        manualStrCopy(facilities[0].type, "Mosque");
        facilities[0].location.lat = 33.729;
        facilities[0].location.lon = 73.038;

        manualStrCopy(facilities[1].facilityID, "F02");
        manualStrCopy(facilities[1].name, "F-9 Park");
        manualStrCopy(facilities[1].type, "Park");
        facilities[1].location.lat = 33.695;
        facilities[1].location.lon = 73.025;

        manualStrCopy(facilities[2].facilityID, "F03");
        manualStrCopy(facilities[2].name, "Community Water Cooler G-10");
        manualStrCopy(facilities[2].type, "Water Cooler");
        facilities[2].location.lat = 33.684;
        facilities[2].location.lon = 73.025;

        facilityCount = 3;
        return;
    }

    char line[300];
    char parts[10][100];
    int n;

    facilityCount = 0;

    fgets(line, 300, f);

    while (fgets(line, 300, f))
    {
        splitCSVLine(line, parts, n);

        // Expected: FacilityID, Name, Type, Lat, Lon
        if (n < 5) continue;

        manualStrCopy(facilities[facilityCount].facilityID, parts[0]);
        trimSpaces(facilities[facilityCount].facilityID);

        manualStrCopy(facilities[facilityCount].name, parts[1]);
        trimSpaces(facilities[facilityCount].name);

        manualStrCopy(facilities[facilityCount].type, parts[2]);
        trimSpaces(facilities[facilityCount].type);

        facilities[facilityCount].location.lat = manualAtof(parts[3]);
        facilities[facilityCount].location.lon = manualAtof(parts[4]);

        facilityCount++;
        if (facilityCount >= 50) break;
    }

    fclose(f);
    cout << "Public facilities data loaded: " << facilityCount << " facilities.\n";
}

void SmartCity::displayAllFacilities() {
    cout << "\n========== ALL PUBLIC FACILITIES ==========\n";

    if (facilityCount == 0) {
        cout << "No facilities registered.\n";
        return;
    }

    // Group by type
    cout << "\n?? MOSQUES:\n";
    for (int i = 0; i < facilityCount; i++) {
        if (facilities[i].type[0] == 'M' || facilities[i].type[0] == 'm') {
            cout << "  • " << facilities[i].name << "\n";
        }
    }

    cout << "\n?? PARKS:\n";
    for (int i = 0; i < facilityCount; i++) {
        if (facilities[i].type[0] == 'P' || facilities[i].type[0] == 'p') {
            cout << "  • " << facilities[i].name << "\n";
        }
    }

    cout << "\n?? WATER COOLERS:\n";
    for (int i = 0; i < facilityCount; i++) {
        if (facilities[i].type[0] == 'W' || facilities[i].type[0] == 'w') {
            cout << "  • " << facilities[i].name << "\n";
        }
    }

    cout << "\nTotal Facilities: " << facilityCount << "\n";
    cout << "===========================================\n";
}
// Creating new public facilities ie. mosque, park, water cooler, etc.
// Updates facilityIdToIndex hash table

void SmartCity::addFacility() {
    if (facilityCount >= 50) {
        cout << "Facility array is full. Cannot add more facilities.\n";
        return;
    }

    char facilityID[10];
    char name[MAX_STR];
    char type[30];
    double lat, lon;

    cout << "\n========== ADD NEW PUBLIC FACILITY ==========\n";
    cout << "Enter Facility ID (e.g., F01): ";
    cin >> facilityID;

    cout << "Enter Facility Name: ";
    cin.ignore();
    cin.getline(name, MAX_STR);

    cout << "Enter Type (Mosque/Park/Water Cooler): ";
    cin.getline(type, 30);

    cout << "Enter Latitude: ";
    cin >> lat;

    cout << "Enter Longitude: ";
    cin >> lon;

    // Add to array
    manualStrCopy(facilities[facilityCount].facilityID, facilityID);
    manualStrCopy(facilities[facilityCount].name, name);
    manualStrCopy(facilities[facilityCount].type, type);
    facilities[facilityCount].location.lat = lat;
    facilities[facilityCount].location.lon = lon;

    facilityCount++;

    // Update hash table
    int key = StringHash::hash(facilityID);
    facilityIdToIndex.insert(key, facilityCount - 1);

    cout << "? Facility added successfully!\n";
}

// Useing master cityGraph to find closest facility of specified type
// Filters results by type 
// Runs Dijkstra from user's bus stop to all facility nodes

void SmartCity::findNearestFacilityByType() {
    if (facilityCount == 0) {
        cout << "? No facilities loaded.\n";
        return;
    }

    if (stopCount == 0) {
        cout << "? No bus stops loaded.\n";
        return;
    }

    // Get stop index
    int stopIndex;
    cout << "\n========== FIND NEAREST FACILITY BY TYPE ==========\n";
    cout << "Enter stop index (0 to " << (stopCount - 1) << "): ";
    cin >> stopIndex;

    if (stopIndex < 0 || stopIndex >= stopCount) {
        cout << "? Invalid stop index.\n";
        return;
    }

    // Get facility type
    char facilityType[50];
    cout << "Enter facility type (e.g., Mosque, Park, Water Cooler): ";
    cin.ignore(10000, '\n');
    cin.getline(facilityType, 50);

    cout << "\n?? FINDING NEAREST " << facilityType << "...\n";
    cout << "Starting from: " << stops[stopIndex].name << "\n\n";

    //  Simple approach using master graph
    static int dist[500];
    static int parent[500];
    const int INF = 1000000000;

    for (int i = 0; i < totalNodes; i++) {
        dist[i] = INF;
        parent[i] = -1;
    }

    // Run Dijkstra on master graph
    cityGraph.dijkstra(stopIndex, dist, parent);

    // Find nearest facility of matching type
    int nearestFacilityIdx = -1;
    int minDist = INF;
    int facilityStartNode = stopCount + hospitalCount + schoolCount + mallCount;

    for (int i = 0; i < facilityCount; i++) {
        // Check if type matches (case-insensitive)
        bool typeMatch = true;
        int j = 0;

        while (facilities[i].type[j] != '\0' && facilityType[j] != '\0') {
            char c1 = facilities[i].type[j];
            char c2 = facilityType[j];

            // Convert to lowercase
            if (c1 >= 'A' && c1 <= 'Z') c1 += 32;
            if (c2 >= 'A' && c2 <= 'Z') c2 += 32;

            if (c1 != c2) {
                typeMatch = false;
                break;
            }
            j++;
        }

        // Check if both strings ended (same length)
        if (facilities[i].type[j] != '\0' || facilityType[j] != '\0') {
            typeMatch = false;
        }

        if (typeMatch) {
            int facilityNode = facilityStartNode + i;

            if (facilityNode < totalNodes && dist[facilityNode] < minDist) {
                minDist = dist[facilityNode];
                nearestFacilityIdx = i;
            }
        }
    }

    if (nearestFacilityIdx == -1 || minDist >= INF) {
        cout << "? No " << facilityType << " reachable from this stop.\n";
        cout << "Available facility types:\n";
        for (int i = 0; i < facilityCount; i++) {
            cout << "  - " << facilities[i].type << "\n";
        }
        return;
    }

    cout << "? NEAREST " << facilityType << " FOUND:\n";
    cout << "========================================\n";
    cout << "Name: " << facilities[nearestFacilityIdx].name << "\n";
    cout << "Type: " << facilities[nearestFacilityIdx].type << "\n";

    cout << "Distance: " << (minDist / 1000.0) << " km\n";
    cout << "Estimated Time: " << (int)(minDist / 416.0) << " minutes\n";
    cout << "========================================\n";

    // Show path
    cout << "\n??? ROUTE:\n";
    int facilityNode = facilityStartNode + nearestFacilityIdx;
    int pathLength = 0;
    int tempPath[100];
    int curr = facilityNode;

    while (curr != -1 && pathLength < 100) {
        tempPath[pathLength++] = curr;
        curr = parent[curr];
    }

    for (int i = pathLength - 1; i >= 0; i--) {
        int node = tempPath[i];

        if (node < stopCount) {
            cout << "   " << (pathLength - i) << ". " << stops[node].name << " [Stop]\n";
        }
        else if (node >= facilityStartNode && node < facilityStartNode + facilityCount) {
            int fIdx = node - facilityStartNode;
            cout << "   " << (pathLength - i) << ". " << facilities[fIdx].name
                << " [" << facilities[fIdx].type << "] ??\n";
        }
    }
    cout << "\n";
}

//hash table lookup to find facility by exact name

void SmartCity::searchFacilityByName() {
    char searchName[MAX_STR];

    cout << "\n========== SEARCH FACILITY BY NAME ==========\n";
    cout << "Enter facility name: ";
    cin.ignore(10000, '\n');
    cin.getline(searchName, MAX_STR);

    // USING HASH TABLE
    int key = StringHash::hash(searchName);
    int idx = facilityNameHash.search(key);

    if (idx != -1) {
        cout << "\n? FACILITY FOUND:\n";
        cout << "========================================\n";
        cout << "Name: " << facilities[idx].name << "\n";
        cout << "Type: " << facilities[idx].type << "\n";
        //cout << "Sector: " << facilities[idx].sector << "\n";
        cout << "Location: " << facilities[idx].location.lat
            << ", " << facilities[idx].location.lon << "\n";
        cout << "========================================\n";
    }
    else {
        cout << "\n? Facility '" << searchName << "' not found.\n";
        cout << "Note: Search is case-sensitive. Try exact name.\n";
    }
}


void SmartCity::publicFacilitiesMenu() {
    int ch;
    while (true) {
        cout << "\n========================================\n";
        cout << "      PUBLIC FACILITIES MENU\n";
        cout << "========================================\n";
        cout << "1.  Display All Facilities\n";
        cout << "2.  Add New Facility\n";
        cout << "3.  Search Facility by Name (Hash Table)\n";
        cout << "4.  Find Nearest Facility by Type (Graph)\n";
        cout << "5.  Find Nearest Facility to Location (Graph)\n";
        cout << "0.  Back to Main Menu\n";
        cout << "========================================\n";
        cout << "Enter choice: ";
        cin >> ch;

        if (ch == 0) return;

        switch (ch) {
        case 1:
            displayAllFacilities();
            break;
        case 2:
            addFacility();
            break;
        case 3:
            searchFacilityByName();  // Uses hash table
            break;
        case 4:
            findNearestFacilityByType();  //Uses graph
            break;
        case 5:
            findNearestFacilityToLocation();  //New function
            break;
        default:
            cout << "Invalid choice.\n";
        }

        waitForEnter();
    }
}


void SmartCity::initSchoolBusTracking() {
    cout << "\n========== INITIALIZE SCHOOL BUS TRACKING ==========\n";

    schoolBusTracker.totalStudents = 0;
    for (int i = 0; i < 50; i++) {
        schoolBusTracker.count[i] = 0;
        schoolBusTracker.studentsOnBuses[i] = nullptr;
    }

    cout << "? School bus tracking system initialized.\n";
    cout << "====================================================\n";
}

void SmartCity::assignStudentToBus() {
    if (busCount == 0) {
        cout << "? No buses available.\n";
        return;
    }

    cout << "\n========== ASSIGN STUDENT TO BUS ==========\n";

    // Display all buses
    cout << "\n?? AVAILABLE BUSES:\n";
    for (int i = 0; i < busCount; i++) {
        cout << (i + 1) << ". Bus " << buses[i].busNo
            << " (" << buses[i].company << ")\n";
    }

    int busNum;
    cout << "\nEnter bus number (1-" << busCount << "): ";
    cin >> busNum;

    if (busNum < 1 || busNum > busCount) {
        cout << "? Invalid selection.\n";
        return;
    }

    int busIdx = busNum - 1;

    if (schoolBusTracker.count[busIdx] >= 50) {
        cout << "? Bus is full (max 50 students).\n";
        return;
    }

    char studentName[MAX_STR];
    char pickup[MAX_STR];
    char dropoff[MAX_STR];

    cout << "\nEnter student name: ";
    cin.ignore();
    cin.getline(studentName, MAX_STR);

    cout << "Enter pickup stop name: ";
    cin.getline(pickup, MAX_STR);

    cout << "Enter dropoff stop name: ";
    cin.getline(dropoff, MAX_STR);

    // Allocate memory if needed
    if (schoolBusTracker.studentsOnBuses[busIdx] == nullptr) {
        schoolBusTracker.studentsOnBuses[busIdx] = new StudentOnBus[50];
    }

    // Add student
    int idx = schoolBusTracker.count[busIdx];
    schoolBusTracker.studentsOnBuses[busIdx][idx].busIndex = busIdx;
    strCopy(schoolBusTracker.studentsOnBuses[busIdx][idx].studentName, studentName);
    strCopy(schoolBusTracker.studentsOnBuses[busIdx][idx].pickupStop, pickup);
    strCopy(schoolBusTracker.studentsOnBuses[busIdx][idx].dropoffStop, dropoff);

    schoolBusTracker.count[busIdx]++;
    schoolBusTracker.totalStudents++;

    cout << "\n? Student '" << studentName << "' assigned to Bus "
        << buses[busIdx].busNo << "\n";
    cout << "===========================================\n";
}

void SmartCity::trackBusWithStudents() {
    cout << "\n========== BUSES WITH ASSIGNED STUDENTS ==========\n";

    if (schoolBusTracker.totalStudents == 0) {
        cout << "?? No students assigned to any bus.\n";
        return;
    }

    for (int i = 0; i < busCount; i++) {
        if (schoolBusTracker.count[i] > 0) {
            cout << "\n?? Bus " << buses[i].busNo << " (" << buses[i].company << ")\n";
            cout << "   Students on board: " << schoolBusTracker.count[i] << "\n";

            if (buses[i].currentStopIndex >= 0 && buses[i].currentStopIndex < stopCount) {
                cout << "   Current Location: " << stops[buses[i].currentStopIndex].name << "\n";
            }
            else {
                cout << "   Current Location: Unknown\n";
            }
        }
    }

    cout << "\n==================================================\n";
}

void SmartCity::displayBusPassengerList() {
    char busNo[10];

    cout << "\n========== BUS PASSENGER LIST ==========\n";
    cout << "Enter Bus Number: ";
    cin >> busNo;

    int busIdx = findBusIndexByNumber(busNo);
    if (busIdx == -1) {
        cout << " Bus not found.\n";
        return;
    }

    cout << "\n Passengers on Bus " << buses[busIdx].busNo << ":\n";
    cout << "----------------------------------------\n";

    if (schoolBusTracker.count[busIdx] == 0) {
        cout << "?? No students assigned to this bus.\n";
    }
    else {
        for (int i = 0; i < schoolBusTracker.count[busIdx]; i++) {
            cout << (i + 1) << ". " << schoolBusTracker.studentsOnBuses[busIdx][i].studentName << "\n";
            cout << "   Pickup: " << schoolBusTracker.studentsOnBuses[busIdx][i].pickupStop << "\n";
            cout << "   Dropoff: " << schoolBusTracker.studentsOnBuses[busIdx][i].dropoffStop << "\n\n";
        }
        cout << "Total passengers: " << schoolBusTracker.count[busIdx] << "\n";
    }

    cout << "========================================\n";
}

void SmartCity::displayStudentLocation() {
    char studentName[MAX_STR];

    cout << "\n========== FIND STUDENT LOCATION ==========\n";
    cout << "Enter Student Name: ";
    cin.ignore();
    cin.getline(studentName, MAX_STR);

    bool found = false;

    for (int i = 0; i < busCount; i++) {
        for (int j = 0; j < schoolBusTracker.count[i]; j++) {
            // Case-insensitive comparison
            bool match = true;
            int k = 0;

            while (schoolBusTracker.studentsOnBuses[i][j].studentName[k] != '\0' || studentName[k] != '\0') {
                char c1 = schoolBusTracker.studentsOnBuses[i][j].studentName[k];
                char c2 = studentName[k];

                if (c1 >= 'A' && c1 <= 'Z') c1 = c1 + 32;
                if (c2 >= 'A' && c2 <= 'Z') c2 = c2 + 32;

                if (c1 != c2) {
                    match = false;
                    break;
                }

                if (c1 == '\0' && c2 == '\0') break;
                k++;
            }

            if (match) {
                cout << "\n?? Student Found!\n";
                cout << "   Name: " << schoolBusTracker.studentsOnBuses[i][j].studentName << "\n";
                cout << "   Bus: " << buses[i].busNo << " (" << buses[i].company << ")\n";

                if (buses[i].currentStopIndex >= 0 && buses[i].currentStopIndex < stopCount) {
                    cout << "   Current Location: " << stops[buses[i].currentStopIndex].name << "\n";
                }
                else {
                    cout << "   Current Location: Unknown\n";
                }

                cout << "   Pickup Stop: " << schoolBusTracker.studentsOnBuses[i][j].pickupStop << "\n";
                cout << "   Dropoff Stop: " << schoolBusTracker.studentsOnBuses[i][j].dropoffStop << "\n";

                found = true;
                break;
            }
        }
        if (found) break;
    }

    if (!found) {
        cout << "? Student not found on any bus.\n";
    }

    cout << "===========================================\n";
}



void SmartCity::initAirportRailNetwork() {
    cout << "\n========== INITIALIZE AIRPORT/RAIL NETWORK ==========\n";

    stationCount = 0;

    strCopy(airportRailStations[0].stationID, "ISB01");
    strCopy(airportRailStations[0].name, "Islamabad International Airport");
    strCopy(airportRailStations[0].type, "Airport");
    airportRailStations[0].location.lat = 33.616;
    airportRailStations[0].location.lon = 72.993;
    airportRailStations[0].connectionCount = 0;

    strCopy(airportRailStations[1].stationID, "RWP01");
    strCopy(airportRailStations[1].name, "Rawalpindi Railway Station");
    strCopy(airportRailStations[1].type, "Railway");
    airportRailStations[1].location.lat = 33.599;
    airportRailStations[1].location.lon = 73.054;
    airportRailStations[1].connectionCount = 0;

    stationCount = 2;

    cout << "? Airport/Rail network initialized with " << stationCount << " stations.\n";
    cout << "=====================================================\n";
}

void SmartCity::addAirportRailStation() {
    if (stationCount >= 10) {
        cout << "? Station array is full (max 10).\n";
        return;
    }

    cout << "\n========== ADD AIRPORT/RAILWAY STATION ==========\n";

    char stationID[10];
    char name[MAX_STR];
    char type[20];
    double lat, lon;

    cout << "Enter Station ID (e.g., ISB02): ";
    cin >> stationID;

    cout << "Enter Station Name: ";
    cin.ignore();
    cin.getline(name, MAX_STR);

    cout << "Enter Type (Airport/Railway): ";
    cin.getline(type, 20);

    cout << "Enter Latitude: ";
    cin >> lat;

    cout << "Enter Longitude: ";
    cin >> lon;

    // Add to array
    strCopy(airportRailStations[stationCount].stationID, stationID);
    strCopy(airportRailStations[stationCount].name, name);
    strCopy(airportRailStations[stationCount].type, type);
    airportRailStations[stationCount].location.lat = lat;
    airportRailStations[stationCount].location.lon = lon;
    airportRailStations[stationCount].connectionCount = 0;

    stationCount++;

    cout << "? Station added successfully!\n";
    cout << "=================================================\n";
}

void SmartCity::connectBusStopToAirport() {
    if (stationCount == 0) {
        cout << "? No stations available. Add a station first.\n";
        return;
    }

    if (stopCount == 0) {
        cout << "? No bus stops available.\n";
        return;
    }

    cout << "\n========== CONNECT BUS STOP TO STATION ==========\n";

    // Display stations
    cout << "\n?? AVAILABLE STATIONS:\n";
    for (int i = 0; i < stationCount; i++) {
        cout << (i + 1) << ". " << airportRailStations[i].name
            << " (" << airportRailStations[i].type << ")\n";
    }

    int stationNum;
    cout << "\nEnter station number (1-" << stationCount << "): ";
    cin >> stationNum;

    if (stationNum < 1 || stationNum > stationCount) {
        cout << "? Invalid selection.\n";
        return;
    }

    int stationIdx = stationNum - 1;

    if (airportRailStations[stationIdx].connectionCount >= 50) {
        cout << "? Station connection limit reached.\n";
        return;
    }

    // Display stops
    cout << "\n?? AVAILABLE BUS STOPS:\n";
    for (int i = 0; i < stopCount; i++) {
        cout << (i + 1) << ". " << stops[i].name << " (ID: " << stops[i].id << ")\n";
    }

    int stopNum;
    cout << "\nEnter stop number (1-" << stopCount << "): ";
    cin >> stopNum;

    if (stopNum < 1 || stopNum > stopCount) {
        cout << "? Invalid selection.\n";
        return;
    }

    int stopIdx = stopNum - 1;

    // Add connection
    char stopIDStr[10];
    sprintf(stopIDStr, "%d", stops[stopIdx].id);
    strCopy(airportRailStations[stationIdx].connectedStops[airportRailStations[stationIdx].connectionCount],
        stopIDStr);
    airportRailStations[stationIdx].connectionCount++;

    cout << "\n? Connected " << stops[stopIdx].name << " to "
        << airportRailStations[stationIdx].name << "\n";
    cout << "=================================================\n";
}



void SmartCity::displayAirportRailNetwork() {
    cout << "\n========== AIRPORT/RAIL NETWORK MAP ==========\n";

    if (stationCount == 0) {
        cout << "?? No stations in network.\n";
        return;
    }

    for (int i = 0; i < stationCount; i++) {
        cout << "\n" << (i + 1) << ". " << airportRailStations[i].name << "\n";
        cout << "   Type: " << airportRailStations[i].type << "\n";
        cout << "   ID: " << airportRailStations[i].stationID << "\n";
        cout << "   Location: (" << airportRailStations[i].location.lat
            << ", " << airportRailStations[i].location.lon << ")\n";

        if (airportRailStations[i].connectionCount > 0) {
            cout << "   Connected Bus Stops:\n";
            for (int j = 0; j < airportRailStations[i].connectionCount; j++) {
                int stopId = manualAtoi(airportRailStations[i].connectedStops[j]);
                int stopIdx = findStopIndexById(stopId);

                if (stopIdx != -1) {
                    cout << "     • " << stops[stopIdx].name << "\n";
                }
            }
        }
        else {
            cout << "   Connected Stops: None\n";
        }
    }

    cout << "\n==============================================\n";
}



void SmartCity::findPathBetweenHospitalAndSchool(int hospitalIndex, int schoolIndex) {
    int hospitalNodeID = stopCount + hospitalIndex;  // Hospital nodes start after stops
    int schoolNodeID = stopCount + hospitalCount + schoolIndex;  // School nodes

    // Run Dijkstra on MASTER graph
    static int dist[500];
    static int parent[500];
    const int INF = 1000000000;

    for (int i = 0; i < totalNodes; i++) {
        dist[i] = INF;
        parent[i] = -1;
    }

    cityGraph.dijkstra(hospitalNodeID, dist, parent);

    if (dist[schoolNodeID] >= INF) {
        cout << "? No path found.\n";
        return;
    }

    // Reconstruct path
    cout << " Path found: " << (dist[schoolNodeID] / 1000.0) << " km\n";

    int path[100];
    int length = 0;
    int curr = schoolNodeID;

    while (curr != -1)
    {
        path[length++] = curr;
        curr = parent[curr];
    }

    for (int i = length - 1; i >= 0; i--) {
        int node = path[i];
        if (node < stopCount) {
            cout << "  " << stops[node].name << " [Bus Stop]\n";
        }
        else if (node < stopCount + hospitalCount) {
            int hospIdx = node - stopCount;
            cout << "  " << hospitals[hospIdx].name << " [HOSPITAL]\n";
        }
        else if (node < stopCount + hospitalCount + schoolCount) {
            int schIdx = node - stopCount - hospitalCount;
            cout << "  " << schools[schIdx].name << " [SCHOOL]\n";
        }
    }
}




// =====================================================================
//              CROSS-MODULE PATH FINDING HELPERS
// =====================================================================

int SmartCity::convertToGraphNode(const char* type, int index) {
    //  Consistent with your nodeRegistry structure in buildTransportGraph()
    if (manualStrCmp(type, "BusStop") == 0) {
        if (index >= 0 && index < stopCount) return index;
    }
    else if (manualStrCmp(type, "Hospital") == 0) {
        if (index >= 0 && index < hospitalCount)
            return stopCount + index;
    }
    else if (manualStrCmp(type, "School") == 0) {
        if (index >= 0 && index < schoolCount)
            return stopCount + hospitalCount + index;
    }
    else if (manualStrCmp(type, "Mall") == 0) {
        if (index >= 0 && index < mallCount)
            return stopCount + hospitalCount + schoolCount + index;
    }
    else if (manualStrCmp(type, "Facility") == 0) {
        if (index >= 0 && index < facilityCount)
            return stopCount + hospitalCount + schoolCount + mallCount + index;
    }
    return -1;
}

void SmartCity::displayPath(int startNode, int endNode, int distance, int parent[]) {
    cout << " PATH FOUND!\n";
    cout << "  Total Distance: " << distance / 1000.0 << " km\n";
    cout << "  Estimated Time: " << int(distance / 416.67) << " minutes\n";

    cout << " ROUTE:\n";

    // Reconstruct path (consistent with your existing path reconstruction)
    int path[100];
    int length = 0;
    int curr = endNode;

    while (curr != -1 && length < 100) {
        path[length++] = curr;
        curr = parent[curr];
    }

    // Display in reverse order (start to end)
    for (int i = length - 1; i >= 0; i--) {
        int node = path[i];

        //  Consistent with your nodeRegistry indexing
        if (node < stopCount) {
            cout << "  " << (length - i) << ". " << stops[node].name << " [Bus Stop]\n";
        }
        else if (node < stopCount + hospitalCount) {
            int hospIdx = node - stopCount;
            cout << "  " << (length - i) << ". " << hospitals[hospIdx].name << " [HOSPITAL] ?\n";
        }
        else if (node < stopCount + hospitalCount + schoolCount) {
            int schIdx = node - stopCount - hospitalCount;
            cout << "  " << (length - i) << ". " << schools[schIdx].name << " [SCHOOL] ?\n";
        }
        else if (node < stopCount + hospitalCount + schoolCount + mallCount) {
            int mallIdx = node - stopCount - hospitalCount - schoolCount;
            cout << "  " << (length - i) << ". " << malls[mallIdx].name << " [MALL] ?\n";
        }
        else if (node < stopCount + hospitalCount + schoolCount + mallCount + facilityCount) {
            int facIdx = node - stopCount - hospitalCount - schoolCount - mallCount;
            cout << "  " << (length - i) << ". " << facilities[facIdx].name << " [FACILITY]\n";
        }
    }
    cout << "\n";
}

void SmartCity::findPathBetweenAnyTwo() {
    cout << "\n========== FIND PATH BETWEEN ANY TWO LOCATIONS ==========\n";

    if (totalNodes == 0) {
        cout << "? Graph not built yet.\n";
        return;
    }

    // Display available types
    cout << "\n?? AVAILABLE LOCATION TYPES:\n";
    cout << "1. Bus Stop\n";
    cout << "2. Hospital\n";
    cout << "3. School\n";
    cout << "4. Mall\n";
    cout << "5. Facility\n";

    int type1, type2, idx1, idx2;

    // Get first location
    cout << "\n? SELECT FIRST LOCATION\n";
    cout << "Enter type (1-5): ";
    cin >> type1;

    const char* typeStr1 = "";
    int maxCount1 = 0;

    switch (type1) {
    case 1: typeStr1 = "BusStop"; maxCount1 = stopCount; break;
    case 2: typeStr1 = "Hospital"; maxCount1 = hospitalCount; break;
    case 3: typeStr1 = "School"; maxCount1 = schoolCount; break;
    case 4: typeStr1 = "Mall"; maxCount1 = mallCount; break;
    case 5: typeStr1 = "Facility"; maxCount1 = facilityCount; break;
    default: cout << "? Invalid type.\n"; return;
    }

    if (maxCount1 == 0) {
        cout << "? No " << typeStr1 << "s available.\n";
        return;
    }

    cout << "Enter " << typeStr1 << " number (1-" << maxCount1 << "): ";
    cin >> idx1;
    idx1--;  // Convert to 0-based index

    if (idx1 < 0 || idx1 >= maxCount1) {
        cout << "? Invalid index.\n";
        return;
    }

    // Get second location
    cout << "\n? SELECT SECOND LOCATION\n";
    cout << "Enter type (1-5): ";
    cin >> type2;

    const char* typeStr2 = "";
    int maxCount2 = 0;

    switch (type2) {
    case 1: typeStr2 = "BusStop"; maxCount2 = stopCount; break;
    case 2: typeStr2 = "Hospital"; maxCount2 = hospitalCount; break;
    case 3: typeStr2 = "School"; maxCount2 = schoolCount; break;
    case 4: typeStr2 = "Mall"; maxCount2 = mallCount; break;
    case 5: typeStr2 = "Facility"; maxCount2 = facilityCount; break;
    default: cout << "? Invalid type.\n"; return;
    }

    if (maxCount2 == 0) {
        cout << "? No " << typeStr2 << "s available.\n";
        return;
    }

    cout << "Enter " << typeStr2 << " number (1-" << maxCount2 << "): ";
    cin >> idx2;
    idx2--;  // Convert to 0-based index

    if (idx2 < 0 || idx2 >= maxCount2) {
        cout << "? Invalid index.\n";
        return;
    }

    // Convert to graph nodes
    int node1 = convertToGraphNode(typeStr1, idx1);
    int node2 = convertToGraphNode(typeStr2, idx2);

    if (node1 == -1 || node2 == -1) {
        cout << "? Could not convert to graph nodes.\n";
        return;
    }

    // Run Dijkstra consistent with your existing Dijkstra calls
    static int dist[500];
    static int parent[500];
    const int INF = 1000000000;

    for (int i = 0; i < totalNodes; i++) {
        dist[i] = INF;
        parent[i] = -1;
    }

    cityGraph.dijkstra(node1, dist, parent);

    if (dist[node2] >= INF) {
        cout << "\n? NO PATH FOUND\n";
        cout << "  These locations are not connected in the transport network.\n";
    }
    else {
        displayPath(node1, node2, dist[node2], parent);
    }

    cout << "=========================================================\n";
}

void SmartCity::testCrossModuleConnectivity() {
    cout << "\n?? TESTING CROSS-MODULE CONNECTIVITY\n";
    cout << "?? Master graph has " << totalNodes << " nodes\n\n";

    // Test connections
    int connectedPairs = 0;
    int totalPairs = 0;

    // Test Hospital -> School connections
    if (hospitalCount > 0 && schoolCount > 0) {
        cout << "?? Testing Hospital ↔ School connections...\n";

        for (int h = 0; h < min(3, hospitalCount); h++) {
            for (int s = 0; s < min(3, schoolCount); s++) {
                int hospitalNode = stopCount + h;
                int schoolNode = stopCount + hospitalCount + s;

                static int dist[500];
                const int INF = 1000000000;

                for (int i = 0; i < totalNodes; i++) dist[i] = INF;

                cityGraph.dijkstra(hospitalNode, dist, nullptr);

                if (dist[schoolNode] < INF) {
                    cout << "  ? " << hospitals[h].name << " → "
                        << schools[s].name << ": "
                        << (dist[schoolNode] / 1000.0) << " km\n";
                    connectedPairs++;
                }
                totalPairs++;
            }
        }
    }


    cout << "\n?? SUMMARY: " << connectedPairs << "/" << totalPairs
        << " test pairs are connected\n";

    if (connectedPairs == totalPairs && totalPairs > 0) {
        cout << " EXCELLENT! All modules are properly connected! ?\n";
    }
    else if (connectedPairs > 0) {
        cout << " GOOD! Some cross-module connections exist.\n";
    }
    else if (totalPairs > 0) {
        cout << " XX No cross-module connections found!\n";
        cout << "  Check your graph building in buildTransportGraph()\n";
    }
}


void SmartCity::displaySchoolSystemTree()
{
    if (schoolSystemRoot == nullptr)
    {
        cout << "?? School system tree not built yet.\n";
        return;
    }

    cout << "\n===============================================\n";
    cout << "=    ISLAMABAD EDUCATION SYSTEM HIERARCHY       =\n";
    cout << "=================================================\n\n";

    TreeUtils::printTree(schoolSystemRoot, 0);

    cout << "\n===================================================\n";
}
void SmartCity::searchSchoolsByLevel()
{
    char sector[20];

    cout << "\n========== SEARCH SCHOOLS BY SECTOR ==========\n";
    cout << "Enter sector (e.g., F-6, G-10, F-8): ";
    cin.ignore();
    cin.getline(sector, 20);

    cout << "\nSchools in sector " << sector << ":\n";
    cout << "---------------------------------------------\n";

    bool found = false;

    for (int i = 0; i < schoolCount; i++)
    {
        // Case-insensitive comparison
        bool match = true;
        int k = 0;

        while (schools[i].sector[k] != '\0' || sector[k] != '\0')
        {
            char c1 = schools[i].sector[k];
            char c2 = sector[k];

            if (c1 >= 'a' && c1 <= 'z') c1 -= 32;
            if (c2 >= 'a' && c2 <= 'z') c2 -= 32;

            if (c1 != c2) {
                match = false;
                break;
            }

            if (c1 == '\0' && c2 == '\0') break;
            k++;
        }

        if (match)
        {
            cout << (found ? "" : "\n") << "• " << schools[i].name
                << " - Rating: " << (schools[i].ranking / 10.0) << "/5.0\n";
            cout << "  Subjects: ";

            for (int j = 0; j < schools[i].subjectCount; j++)
            {
                cout << schools[i].subjects[j];
                if (j < schools[i].subjectCount - 1) cout << ", ";
            }
            cout << "\n";
            found = true;
        }
    }

    if (!found) {
        cout << "?? No schools found in sector " << sector << ".\n";
    }

    cout << "=============================================\n";
}




void SmartCity::registerFaculty() {
    if (schoolCount == 0) {
        cout << "? No schools available. Please add schools first.\n";
        return;
    }

    cout << "\n========== REGISTER NEW FACULTY MEMBER ==========\n";

    // Display available schools
    cout << "\n?? AVAILABLE SCHOOLS:\n";
    for (int i = 0; i < schoolCount; i++) {
        cout << (i + 1) << ". " << schools[i].name
            << " (" << schools[i].sector << ")\n";
    }

    int schoolChoice;
    cout << "\nSelect school (1-" << schoolCount << "): ";
    cin >> schoolChoice;

    if (schoolChoice < 1 || schoolChoice > schoolCount) {
        cout << "? Invalid selection.\n";
        return;
    }

    int schoolIdx = schoolChoice - 1;

    char facultyName[MAX_STR];
    char facultyID[20];
    char department[50];
    char subject[50];
    int experience;

    cout << "\nEnter Faculty Details:\n";
    cout << "Faculty ID (e.g., FAC001): ";
    cin >> facultyID;

    cout << "Faculty Name: ";
    cin.ignore(10000, '\n');
    cin.getline(facultyName, MAX_STR);

    cout << "Department (e.g., Science, Arts, Computer): ";
    cin.getline(department, 50);

    cout << "Main Subject: ";
    cin.getline(subject, 50);

    cout << "Years of Experience: ";
    cin >> experience;

    if (cin.fail()) {
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "? Invalid experience value!\n";
        return;
    }

    cout << "\n? Faculty registered successfully!\n";
    cout << "   School: " << schools[schoolIdx].name << "\n";
    cout << "   Faculty: " << facultyName << "\n";
    cout << "   ID: " << facultyID << "\n";
    cout << "   Department: " << department << "\n";
    cout << "   Subject: " << subject << "\n";
    cout << "   Experience: " << experience << " years\n";
    cout << "================================================\n";
}

void SmartCity::compareSchoolsBySubjects() {
    if (schoolCount < 2) {
        cout << " Need at least 2 schools to compare.\n";
        return;
    }

    cout << "\n========== COMPARE SCHOOLS BY SUBJECTS ==========\n";

    // Display all schools
    displayAllSchools();

    int school1, school2;
    cout << "\nEnter first school number (1-" << schoolCount << "): ";
    cin >> school1;
    cout << "Enter second school number (1-" << schoolCount << "): ";
    cin >> school2;

    if (school1 < 1 || school1 > schoolCount ||
        school2 < 1 || school2 > schoolCount) {
        cout << " Invalid school numbers.\n";
        return;
    }

    int idx1 = school1 - 1;
    int idx2 = school2 - 1;

    cout << "\n==================================================\n";
    cout << "      COMPARING SCHOOLS BY SUBJECT OFFERINGS\n";
    cout << "==================================================\n\n";

    // Display school 1 details
    cout << " SCHOOL 1: " << schools[idx1].name << "\n";
    cout << "   Sector: " << schools[idx1].sector << "\n";
    cout << "   Rating: " << (schools[idx1].ranking / 10.0) << "/5.0\n";
    cout << "   Subjects (" << schools[idx1].subjectCount << "):\n";
    for (int i = 0; i < schools[idx1].subjectCount; i++) {
        cout << "     • " << schools[idx1].subjects[i] << "\n";
    }

    // Display school 2 details
    cout << "\n?? SCHOOL 2: " << schools[idx2].name << "\n";
    cout << "   Sector: " << schools[idx2].sector << "\n";
    cout << "   Rating: " << (schools[idx2].ranking / 10.0) << "/5.0\n";
    cout << "   Subjects (" << schools[idx2].subjectCount << "):\n";
    for (int i = 0; i < schools[idx2].subjectCount; i++) {
        cout << "     • " << schools[idx2].subjects[i] << "\n";
    }

    // Find common subjects
    cout << "\n?? COMMON SUBJECTS:\n";
    bool foundCommon = false;

    for (int i = 0; i < schools[idx1].subjectCount; i++) {
        for (int j = 0; j < schools[idx2].subjectCount; j++) {
            // Case insensitive comparison
            bool match = true;
            int k = 0;

            while (schools[idx1].subjects[i][k] != '\0' &&
                schools[idx2].subjects[j][k] != '\0') {
                char c1 = schools[idx1].subjects[i][k];
                char c2 = schools[idx2].subjects[j][k];

                if (c1 >= 'A' && c1 <= 'Z') c1 += 32;
                if (c2 >= 'A' && c2 <= 'Z') c2 += 32;

                if (c1 != c2) {
                    match = false;
                    break;
                }
                k++;
            }

            if (match &&
                schools[idx1].subjects[i][k] == '\0' &&
                schools[idx2].subjects[j][k] == '\0') {
                if (!foundCommon) {
                    foundCommon = true;
                }
                cout << "     • " << schools[idx1].subjects[i] << "\n";
                break;
            }
        }
    }

    if (!foundCommon) {
        cout << "     No common subjects found.\n";
    }

    // Find unique subjects
    cout << "\n UNIQUE TO " << schools[idx1].name << ":\n";
    bool foundUnique1 = false;

    for (int i = 0; i < schools[idx1].subjectCount; i++) {
        bool isUnique = true;

        for (int j = 0; j < schools[idx2].subjectCount; j++) {
            // Case insensitive comparison
            bool match = true;
            int k = 0;

            while (schools[idx1].subjects[i][k] != '\0' &&
                schools[idx2].subjects[j][k] != '\0') {
                char c1 = schools[idx1].subjects[i][k];
                char c2 = schools[idx2].subjects[j][k];

                if (c1 >= 'A' && c1 <= 'Z') c1 += 32;
                if (c2 >= 'A' && c2 <= 'Z') c2 += 32;

                if (c1 != c2) {
                    match = false;
                    break;
                }
                k++;
            }

            if (match &&
                schools[idx1].subjects[i][k] == '\0' &&
                schools[idx2].subjects[j][k] == '\0') {
                isUnique = false;
                break;
            }
        }

        if (isUnique) {
            if (!foundUnique1) {
                foundUnique1 = true;
            }
            cout << "     • " << schools[idx1].subjects[i] << "\n";
        }
    }

    if (!foundUnique1) {
        cout << "     No unique subjects.\n";
    }

    cout << "\n?? UNIQUE TO " << schools[idx2].name << ":\n";
    bool foundUnique2 = false;

    for (int i = 0; i < schools[idx2].subjectCount; i++) {
        bool isUnique = true;

        for (int j = 0; j < schools[idx1].subjectCount; j++) {
            // Case insensitive comparison
            bool match = true;
            int k = 0;

            while (schools[idx2].subjects[i][k] != '\0' &&
                schools[idx1].subjects[j][k] != '\0') {
                char c1 = schools[idx2].subjects[i][k];
                char c2 = schools[idx1].subjects[j][k];

                if (c1 >= 'A' && c1 <= 'Z') c1 += 32;
                if (c2 >= 'A' && c2 <= 'Z') c2 += 32;

                if (c1 != c2) {
                    match = false;
                    break;
                }
                k++;
            }

            if (match &&
                schools[idx2].subjects[i][k] == '\0' &&
                schools[idx1].subjects[j][k] == '\0') {
                isUnique = false;
                break;
            }
        }

        if (isUnique) {
            if (!foundUnique2) {
                foundUnique2 = true;
            }
            cout << "     • " << schools[idx2].subjects[i] << "\n";
        }
    }

    if (!foundUnique2) {
        cout << "     No unique subjects.\n";
    }

    cout << "\n==================================================\n";
}


void SmartCity::registerStudent() {
    if (schoolCount == 0) {
        cout << "? No schools available. Please add schools first.\n";
        return;
    }

    cout << "\n========== REGISTER NEW STUDENT ==========\n";

    // Display available schools
    cout << "\n?? AVAILABLE SCHOOLS:\n";
    for (int i = 0; i < schoolCount; i++) {
        cout << (i + 1) << ". " << schools[i].name
            << " (" << schools[i].sector << ")"
            << " - Rating: " << (schools[i].ranking / 10.0) << "/5.0\n";
    }

    int schoolChoice;
    cout << "\nSelect school (1-" << schoolCount << "): ";
    cin >> schoolChoice;

    if (schoolChoice < 1 || schoolChoice > schoolCount) {
        cout << "? Invalid selection.\n";
        return;
    }

    int schoolIdx = schoolChoice - 1;

    char studentName[MAX_STR];
    char studentID[20];
    char parentName[MAX_STR];
    char className[50];
    int rollNumber;
    int age;

    cout << "\nEnter Student Details:\n";
    cout << "Student ID (e.g., STU001): ";
    cin >> studentID;

    cout << "Student Name: ";
    cin.ignore(10000, '\n');
    cin.getline(studentName, MAX_STR);

    cout << "Parent/Guardian Name: ";
    cin.getline(parentName, MAX_STR);

    cout << "Class (e.g., Class 10-Science): ";
    cin.getline(className, 50);

    cout << "Roll Number: ";
    cin >> rollNumber;

    if (cin.fail()) {
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "? Invalid roll number!\n";
        return;
    }

    cout << "Age: ";
    cin >> age;

    if (cin.fail()) {
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "? Invalid age!\n";
        return;
    }

    cout << "\n? Student registered successfully!\n";
    cout << "   School: " << schools[schoolIdx].name << "\n";
    cout << "   Student: " << studentName << "\n";
    cout << "   ID: " << studentID << "\n";
    cout << "   Class: " << className << "\n";
    cout << "   Roll #: " << rollNumber << "\n";
    cout << "   Age: " << age << " years\n";
    cout << "   Parent: " << parentName << "\n";
    cout << "================================================\n";
}



void SmartCity::generateSchoolPerformanceReport() {
    if (schoolCount == 0) {
        cout << "? No schools available.\n";
        return;
    }

    cout << "\n========== SCHOOL PERFORMANCE REPORT ==========\n";

    // Calculate statistics
    int totalRating = 0;
    int maxRating = schools[0].ranking;
    int minRating = schools[0].ranking;
    int bestSchoolIdx = 0;
    int worstSchoolIdx = 0;

    for (int i = 0; i < schoolCount; i++) {
        totalRating += schools[i].ranking;

        if (schools[i].ranking > maxRating) {
            maxRating = schools[i].ranking;
            bestSchoolIdx = i;
        }

        if (schools[i].ranking < minRating) {
            minRating = schools[i].ranking;
            worstSchoolIdx = i;
        }
    }

    double avgRating = (double)totalRating / schoolCount / 10.0;

    // Display overall statistics
    cout << "\n?? OVERVIEW\n";
    cout << "   Total Schools: " << schoolCount << "\n";
    cout << "   Average Rating: " << avgRating << "/5.0\n";
    cout << "   Highest Rating: " << (maxRating / 10.0) << "/5.0\n";
    cout << "   Lowest Rating: " << (minRating / 10.0) << "/5.0\n";

    // Display top 3 schools
    cout << "\n?? TOP 3 SCHOOLS\n";

    // Create indices array for sorting
    int indices[MAX_SCHOOLS];
    for (int i = 0; i < schoolCount; i++) {
        indices[i] = i;
    }

    // Sort by rating (descending)
    for (int i = 0; i < schoolCount - 1; i++) {
        for (int j = i + 1; j < schoolCount; j++) {
            if (schools[indices[i]].ranking < schools[indices[j]].ranking) {
                int temp = indices[i];
                indices[i] = indices[j];
                indices[j] = temp;
            }
        }
    }

    // Display top 3
    int displayCount = (schoolCount < 3) ? schoolCount : 3;
    for (int i = 0; i < displayCount; i++) {
        int idx = indices[i];
        cout << "   " << (i + 1) << ". " << schools[idx].name << "\n";
        cout << "      Sector: " << schools[idx].sector << "\n";
        cout << "      Rating: " << (schools[idx].ranking / 10.0) << "/5.0\n";
        cout << "      Subjects: ";
        for (int j = 0; j < schools[idx].subjectCount; j++) {
            cout << schools[idx].subjects[j];
            if (j < schools[idx].subjectCount - 1) cout << ", ";
        }
        cout << "\n\n";
    }

    // Display rating distribution
    int excellent = 0, good = 0, average = 0, poor = 0;

    for (int i = 0; i < schoolCount; i++) {
        double rating = schools[i].ranking / 10.0;

        if (rating >= 4.5) {
            excellent++;
        }
        else if (rating >= 4.0) {
            good++;
        }
        else if (rating >= 3.0) {
            average++;
        }
        else {
            poor++;
        }
    }

    cout << "\n?? RATING DISTRIBUTION\n";
    cout << "   Excellent (4.5+): " << excellent << " schools\n";
    cout << "   Good (4.0-4.4):   " << good << " schools\n";
    cout << "   Average (3.0-3.9):" << average << " schools\n";
    cout << "   Needs Improvement (<3.0): " << poor << " schools\n";

    // Display subject popularity
    cout << "\n?? SUBJECT POPULARITY\n";

    // Count subject occurrences
    struct SubjectCount {
        char name[50];
        int count;
    };

    SubjectCount subjectCounts[50];
    int subjectCountsSize = 0;

    for (int i = 0; i < schoolCount; i++) {
        for (int j = 0; j < schools[i].subjectCount; j++) {
            bool found = false;

            // Check if subject already exists in our list
            for (int k = 0; k < subjectCountsSize; k++) {
                // Case-insensitive comparison
                bool match = true;
                int l = 0;

                while (schools[i].subjects[j][l] != '\0' &&
                    subjectCounts[k].name[l] != '\0') {
                    char c1 = schools[i].subjects[j][l];
                    char c2 = subjectCounts[k].name[l];

                    if (c1 >= 'A' && c1 <= 'Z') c1 += 32;
                    if (c2 >= 'A' && c2 <= 'Z') c2 += 32;

                    if (c1 != c2) {
                        match = false;
                        break;
                    }
                    l++;
                }

                if (match &&
                    schools[i].subjects[j][l] == '\0' &&
                    subjectCounts[k].name[l] == '\0') {
                    subjectCounts[k].count++;
                    found = true;
                    break;
                }
            }

            // Add new subject if not found
            if (!found && subjectCountsSize < 50) {
                strCopy(subjectCounts[subjectCountsSize].name, schools[i].subjects[j]);
                subjectCounts[subjectCountsSize].count = 1;
                subjectCountsSize++;
            }
        }
    }

    // Sort subjects by popularity
    for (int i = 0; i < subjectCountsSize - 1; i++) {
        for (int j = i + 1; j < subjectCountsSize; j++) {
            if (subjectCounts[i].count < subjectCounts[j].count) {
                SubjectCount temp = subjectCounts[i];
                subjectCounts[i] = subjectCounts[j];
                subjectCounts[j] = temp;
            }
        }
    }

    // Display top subjects
    int displaySubjects = (subjectCountsSize < 5) ? subjectCountsSize : 5;
    for (int i = 0; i < displaySubjects; i++) {
        cout << "   " << (i + 1) << ". " << subjectCounts[i].name
            << " (" << subjectCounts[i].count << " schools)\n";
    }

    cout << "\n===============================================\n";
}


// Initialize the 4D sector map array
void SmartCity::initializeSectorMaps() {
    cout << "\n?? Initializing Islamabad Sector Map System...\n";

    // Allocate 4D array: [26 letters][15 numbers][5 subsectors][grid]
    sectorMaps = new SectorHouseMap * **[26]; // A-Z

    for (int letter = 0; letter < 26; letter++) {
        sectorMaps[letter] = new SectorHouseMap * *[15]; // 0-14 (0 unused)

        for (int num = 0; num < 15; num++) {
            sectorMaps[letter][num] = new SectorHouseMap * [5]; // 0-4 (0 unused)

            for (int sub = 0; sub < 5; sub++) {
                sectorMaps[letter][num][sub] = nullptr;
            }
        }
    }

    char commonLetters[] = { 'F', 'G', 'H', 'I' };

    for (char letter : commonLetters) {
        int letterIdx = letter - 'A';
        for (int num = 1; num <= 14; num++) {
            for (int sub = 1; sub <= 4; sub++) {
                sectorMaps[letterIdx][num][sub] = new SectorHouseMap;
                sectorMaps[letterIdx][num][sub]->letterIndex = letterIdx;
                sectorMaps[letterIdx][num][sub]->sectorNumber = num;
                sectorMaps[letterIdx][num][sub]->subSector = sub;
                sectorMaps[letterIdx][num][sub]->rows = GRID_ROWS;
                sectorMaps[letterIdx][num][sub]->cols = GRID_COLS;
                sectorMaps[letterIdx][num][sub]->occupiedCount = 0;

                // Allocate 2D grid
                sectorMaps[letterIdx][num][sub]->houseGrid = new int* [GRID_ROWS];
                for (int i = 0; i < GRID_ROWS; i++) {
                    sectorMaps[letterIdx][num][sub]->houseGrid[i] = new int[GRID_COLS];
                    for (int j = 0; j < GRID_COLS; j++) {
                        sectorMaps[letterIdx][num][sub]->houseGrid[i][j] = 0; // 0 = empty
                    }
                }
            }
        }
    }

    cout << " Sector map system initialized.\n";
}

// Parse sector code like "G7/3"
bool SmartCity::parseSectorCode(const char* sectorCode, int& letterIdx, int& sectorNum, int& subSector) {

    if (strLength(sectorCode) < 4) return false;

    // Get letter
    char letter = sectorCode[0];
    if (letter < 'A' || letter > 'Z') return false;
    letterIdx = letter - 'A';

    // Find slash position
    const char* slash = strchr(sectorCode, '/');
    if (!slash) return false;

    // Get sector number (between letter and slash)
    char numStr[10];
    int numLen = slash - sectorCode - 1;
    if (numLen <= 0 || numLen >= 10) return false;

    strncpy(numStr, sectorCode + 1, numLen);
    numStr[numLen] = '\0';

    sectorNum = atoi(numStr);
    if (sectorNum < 1 || sectorNum > 14) return false;

    // Get sub sector (after slash)
    subSector = atoi(slash + 1);
    if (subSector < 1 || subSector > 4) return false;

    return true;
}

// Allocate a house in the sector grid
/*When a new citizen is added to the population system, the program needs to place them into a house inside their specified sector
(e.g., G-10/2). The allocateHouseInSector() function handles this automatically. It first checks whether a housing grid has already
been created for that sector and subsector. If not, it creates a new 10×10 matrix of houses where every cell represents one house.

Once the grid exists, the function simply scans the matrix from the top-left towards the bottom-right to find the first empty house
(marked as 0). When it finds an empty house, it marks it as occupied (1), returns the row and column of that house, and increases the
occupation count. If all 100 houses are full, it returns false.*/

bool SmartCity::allocateHouseInSector(int letterIdx, int sectorNum, int subSector, int& row, int& col) {
    // Check if sector map exists
    if (!sectorMaps[letterIdx][sectorNum][subSector]) {
        // Create it if it doesn't exist
        sectorMaps[letterIdx][sectorNum][subSector] = new SectorHouseMap;
        sectorMaps[letterIdx][sectorNum][subSector]->letterIndex = letterIdx;
        sectorMaps[letterIdx][sectorNum][subSector]->sectorNumber = sectorNum;
        sectorMaps[letterIdx][sectorNum][subSector]->subSector = subSector;
        sectorMaps[letterIdx][sectorNum][subSector]->rows = GRID_ROWS;
        sectorMaps[letterIdx][sectorNum][subSector]->cols = GRID_COLS;
        sectorMaps[letterIdx][sectorNum][subSector]->occupiedCount = 0;

        // Allocate grid
        sectorMaps[letterIdx][sectorNum][subSector]->houseGrid = new int* [GRID_ROWS];
        for (int i = 0; i < GRID_ROWS; i++) {
            sectorMaps[letterIdx][sectorNum][subSector]->houseGrid[i] = new int[GRID_COLS];
            for (int j = 0; j < GRID_COLS; j++) {
                sectorMaps[letterIdx][sectorNum][subSector]->houseGrid[i][j] = 0;
            }
        }
    }

    // Find first available house
    SectorHouseMap* map = sectorMaps[letterIdx][sectorNum][subSector];

    for (row = 0; row < map->rows; row++) {
        for (col = 0; col < map->cols; col++) {
            if (map->houseGrid[row][col] == 0) {
                map->houseGrid[row][col] = 1; // Mark as occupied
                map->occupiedCount++;
                return true;
            }
        }
    }

    return false; // No available houses
}

void SmartCity::addCitizen() {
    if (citizenCount >= MAX_CITIZENS) {
        cout << " Citizen array is full.\n";
        return;
    }

    cout << "\n========== ADD NEW CITIZEN ==========\n";

    char cnic[20];
    char name[MAX_STR];
    int age;
    char gender;
    char occupation[50];
    char sector[20];
    char street[20];
    char houseNo[20];

    // CNIC
    cout << "Enter CNIC (e.g., 61101-1111111-1): ";
    cin >> cnic;

    if (findCitizenIndexByCNIC(cnic) != -1) {
        cout << " Citizen with this CNIC already exists.\n";
        return;
    }

    // Name
    cout << "Enter Name: ";
    cin.ignore();
    cin.getline(name, MAX_STR);

    // Age
    cout << "Enter Age: ";
    cin >> age;
    if (cin.fail() || age < 0 || age > 120) {
        cin.clear();
        cin.ignore(10000, '\n');
        cout << " Invalid age.\n";
        return;
    }

    // Gender
    cout << "Enter Gender (M/F): ";
    cin >> gender;
    // manual toupper
    if (gender >= 'a' && gender <= 'z') gender = gender - 32;
    if (gender != 'M' && gender != 'F') {
        cout << " Invalid gender. Use M or F.\n";
        return;
    }

    // Occupation
    cout << "Enter Occupation: ";
    cin.ignore();
    cin.getline(occupation, 50);

    // Address: Sector / Street / House
    cout << "\n=== ADDRESS INFORMATION ===\n";
    cout << "Enter Sector (e.g., G-10, F-8, Blue Area): ";
    cin.getline(sector, 20);

    cout << "Enter Street (e.g., 22): ";
    cin.getline(street, 20);

    cout << "Enter House Number (e.g., 180): ";
    cin.getline(houseNo, 20);

    // Store in array
    Citizen& c = citizens[citizenCount];

    manualStrCopy(c.cnic, cnic);
    manualStrCopy(c.name, name);
    c.age = age;
    c.gender = gender;
    manualStrCopy(c.occupation, occupation);

    manualStrCopy(c.sector, sector);
    manualStrCopy(c.street, street);
    manualStrCopy(c.houseNo, houseNo);

    // Optional grid fields, if unused set to -1
    c.sectorLetterIndex = -1;
    c.sectorNumber = -1;
    c.subSector = -1;
    c.houseRow = -1;
    c.houseCol = -1;

    citizenCount++;

    // Update CNIC hash table
    int key = StringHash::hash(cnic);
    citizenIdToIndex.insert(key, citizenCount - 1);

    cout << "\n Citizen added successfully!\n";
    cout << "   Name : " << name << "\n";
    cout << "   CNIC : " << cnic << "\n";
    cout << "   Age  : " << age << "\n";
    cout << "   Gender: " << gender << "\n";
    cout << "   Occupation: " << occupation << "\n";
    cout << "   Address: " << sector << ", Street " << street << ", House " << houseNo << "\n";
    cout << "======================================\n";
}

// Display sector map
void SmartCity::displaySectorMap(int letterIdx, int sectorNum, int subSector) {
    if (!sectorMaps[letterIdx][sectorNum][subSector]) {
        cout << "? Sector not initialized yet.\n";
        return;
    }

    SectorHouseMap* map = sectorMaps[letterIdx][sectorNum][subSector];
    char letter = 'A' + letterIdx;

    cout << "\n========== SECTOR MAP: " << letter << sectorNum << "/" << subSector << " ==========\n";
    cout << "Occupied: " << map->occupiedCount << "/" << (map->rows * map->cols) << " houses\n\n";

    cout << "  ";
    for (int col = 0; col < map->cols; col++) {
        printf("%2d ", col + 1);
    }
    cout << "\n";

    for (int row = 0; row < map->rows; row++) {
        printf("%2d ", row + 1);
        for (int col = 0; col < map->cols; col++) {
            if (map->houseGrid[row][col] == 0) {
                cout << "[ ] ";
            }
            else {
                cout << "[X] ";
            }
        }
        cout << "\n";
    }

    // Show legend
    cout << "\n[ ] = Available house\n";
    cout << "[X] = Occupied house\n";
    cout << "========================================\n";
}

// Generate sector report
void SmartCity::generateSectorReport() {
    cout << "\n========== ISLAMABAD SECTOR OCCUPANCY REPORT ==========\n";

    int totalHouses = 0;
    int occupiedHouses = 0;

    // Common Islamabad sectors
    char letters[] = { 'F', 'G', 'H', 'I' };

    for (char letter : letters) {
        int letterIdx = letter - 'A';
        cout << "\n SECTOR GROUP " << letter << ":\n";
        cout << "----------------------------------------\n";

        for (int num = 1; num <= 14; num++) {
            for (int sub = 1; sub <= 4; sub++) {
                if (sectorMaps[letterIdx][num][sub]) {
                    SectorHouseMap* map = sectorMaps[letterIdx][num][sub];
                    int capacity = map->rows * map->cols;
                    int occupied = map->occupiedCount;

                    totalHouses += capacity;
                    occupiedHouses += occupied;

                    float occupancyRate = (capacity > 0) ? (occupied * 100.0 / capacity) : 0;

                    cout << letter << num << "/" << sub << ": "
                        << occupied << "/" << capacity << " houses ("
                        << (int)occupancyRate << "%)\n";
                }
            }
        }
    }

    cout << "\n SUMMARY:\n";
    cout << "Total Houses Available: " << totalHouses << "\n";
    cout << "Total Occupied Houses: " << occupiedHouses << "\n";
    cout << "Overall Occupancy Rate: "
        << (totalHouses > 0 ? (occupiedHouses * 100 / totalHouses) : 0) << "%\n";

    // Find most populated sector
    char mostPopulatedLetter = 'F';
    int mostPopulatedNum = 1;
    int mostPopulatedSub = 1;
    int maxOccupied = 0;

    for (char letter : letters) {
        int letterIdx = letter - 'A';
        for (int num = 1; num <= 14; num++) {
            for (int sub = 1; sub <= 4; sub++) {
                if (sectorMaps[letterIdx][num][sub]) {
                    int occupied = sectorMaps[letterIdx][num][sub]->occupiedCount;
                    if (occupied > maxOccupied) {
                        maxOccupied = occupied;
                        mostPopulatedLetter = letter;
                        mostPopulatedNum = num;
                        mostPopulatedSub = sub;
                    }
                }
            }
        }
    }

    if (maxOccupied > 0) {
        cout << "\n Most Populated Sector: "
            << mostPopulatedLetter << mostPopulatedNum << "/" << mostPopulatedSub
            << " (" << maxOccupied << " houses occupied)\n";
    }

    cout << "======================================================\n";
}

// Population specific print with labels
void SmartCity::displayPopulationTree() {
    if (populationRoot == nullptr) {
        cout << "Population tree not built yet.\n";
        return;
    }

    cout << "\n========== POPULATION HIERARCHY ==========\n";
    printPopulationTree(populationRoot, 0);
    cout << "==========================================\n";
}

void SmartCity::printPopulationTree(TreeNode* node, int level) {
    if (!node) return;

    // Determine level labels
    const char* label = "";
    if (level == 1) label = "Sector: ";
    else if (level == 2) label = "  Street: ";
    else if (level == 3) label = "    House: ";
    else if (level == 4) label = "      Family Members: ";

    // Print current node with label
    cout << label << node->name << "\n";

    // Print children
    for (int i = 0; i < node->childCount; i++) {
        printPopulationTree(node->children[i], level + 1);
    }
}

void SmartCity::simulateRealisticSchoolBusRoute()
{
    // Check if we have enough schools
    if (schoolCount < 2)
    {
        cout << "XX Need at least 2 schools!\n";
        return;
    }

    // Displaying menu
    cout << "\n===============================================================\n";
    cout << "        REALISTIC SCHOOL BUS TRACKING SYSTEM                  \n";
    cout << "===============================================================\n\n";

    cout << "Available Schools:\n";
    cout << "---------------------------------------------------------------\n";
    for (int i = 0; i < schoolCount; i++) {
        cout << "  " << (i + 1) << ". " << schools[i].name
            << " (" << schools[i].sector << ")\n";
    }
    cout << "---------------------------------------------------------------\n\n";

    // Get user input
    int choice;
    cout << "Select starting school (1-" << schoolCount << "): ";
    cin >> choice;

    if (choice < 1 || choice > schoolCount)
    {
        cout << "XX Invalid choice!\n";
        return;
    }

    int startSchoolIdx = choice - 1;

    cout << "\n Starting from: " << schools[startSchoolIdx].name << "\n";
    cout << "\nPress Enter to START simulation...";
    cin.ignore(10000, '\n');
    cin.get();

    // Initialize simulation state
    cout << "\n\n===============================================================\n";
    cout << "                  BUS IS NOW RUNNING!                         \n";
    cout << "===============================================================\n\n";

    int totalDistance = 0;
    int totalTime = 0;
    int currentSchool = startSchoolIdx;
    bool visitedSchools[50] = { false };
    visitedSchools[currentSchool] = true;
    int schoolsVisited = 1;

    // Maping school index to graph node
    int schoolNodesStart = stopCount + hospitalCount;
    int currentNode = schoolNodesStart + currentSchool;
    int nameLen = 0;

    // Displaying starting position
    cout << "===============================================================\n";
    cout << " STARTING SCHOOL                                              \n";
    cout << "===============================================================\n";
    cout << " School: " << schools[currentSchool].name << "\n";
    cout << " Sector: " << schools[currentSchool].sector << "\n";
    cout << " Time: 0 seconds\n";
    cout << "===============================================================\n\n";

    SLEEP(3000);

    // Main loop  visiting all schools
    while (schoolsVisited < schoolCount)
    {

        // Find nearest unvisited school
        double minDist = 1e9;
        int nextSchool = -1;

        for (int i = 0; i < schoolCount; i++)
        {
            if (!visitedSchools[i])
            {
                double dist = computeDistance(schools[currentSchool].lat, schools[currentSchool].lon,
                    schools[i].lat, schools[i].lon);

                if (dist < minDist)
                {
                    minDist = dist;
                    nextSchool = i;
                }
            }
        }

        if (nextSchool == -1)
            break;

        int targetNode = schoolNodesStart + nextSchool;

        cout << "Target: " << schools[nextSchool].name << "\n";
        cout << "Finding shortest path via bus stops...\n\n";

        // Run Dijkstra
        static int dist[500];
        static int parent[500];
        const int INF = 1000000000;

        for (int i = 0; i < totalNodes; i++)
        {
            dist[i] = INF;
            parent[i] = -1;
        }

        cityGraph.dijkstra(currentNode, dist, parent);

        if (dist[targetNode] >= INF)
        {
            cout << "XX No path found to " << schools[nextSchool].name << "!\n";
            break;
        }

        // Reconstructing the  path
        int path[100];
        int pathLength = 0;
        int curr = targetNode;

        while (curr != -1) {
            path[pathLength++] = curr;
            curr = parent[curr];
        }

        // Reversing path
        for (int i = 0; i < pathLength / 2; i++)
        {
            int temp = path[i];
            path[i] = path[pathLength - 1 - i];
            path[pathLength - 1 - i] = temp;
        }

        cout << "Route Summary: " << (pathLength - 1) << " segments to travel\n";
        cout << "---------------------------------------------------------------\n\n";

        // Showing bus traveling
        int stopNumber = 1;

        for (int i = 0; i < pathLength; i++)
        {
            int node = path[i];
            int len = 0;

            bool shouldDisplay = true;
            if (i == 0 && node == currentNode)
            {
                shouldDisplay = false;
            }

            if (shouldDisplay)
            {

                if (node < stopCount)
                {
                    cout << "===============================================================\n";
                    cout << " BUS STOP #" << stopNumber << "\n";
                    cout << "===============================================================\n";
                    cout << " Location: " << stops[node].name << "\n";
                    cout << " Stop ID: " << stops[node].id << "\n";

                }
                else if (node >= schoolNodesStart && node < schoolNodesStart + schoolCount)
                {
                    int schoolIdx = node - schoolNodesStart;

                    cout << "===============================================================\n";
                    cout << " SCHOOL REACHED!\n";
                    cout << "===============================================================\n";
                    cout << " School: " << schools[schoolIdx].name << "\n";
                    cout << " Sector: " << schools[schoolIdx].sector << "\n";

                }
                else if (node >= stopCount && node < stopCount + hospitalCount)
                {
                    int hospitalIdx = node - stopCount;

                    cout << "===============================================================\n";
                    cout << " PASSING HOSPITAL\n";
                    cout << "===============================================================\n";
                    cout << " Hospital: " << hospitals[hospitalIdx].name << "\n";

                }
                else
                {
                    cout << "===============================================================\n";
                    cout << " PASSING NODE " << node << "\n";
                    cout << "===============================================================\n";
                }

                if (i < pathLength - 1)
                {
                    AdjNode* edge = cityGraph.getAdjList(node);
                    int edgeWeight = 0;

                    while (edge != nullptr)
                    {
                        if (edge->vertex == path[i + 1])
                        {
                            edgeWeight = edge->weight;
                            break;
                        }
                        edge = edge->next;
                    }

                    cout << " Distance to next: " << (edgeWeight / 1000.0) << " km\n";
                    cout << " Elapsed time: " << totalTime << " seconds\n";
                    cout << "===============================================================\n";
                    cout << "         >> Traveling to next location... >>\n";
                    cout << "===============================================================\n\n";

                    totalDistance += edgeWeight;
                    totalTime += 5;

                    SLEEP(5000);

                }
                else
                {
                    cout << " Total elapsed time: " << totalTime << " seconds\n";
                    cout << "===============================================================\n\n";
                }

                if (node < stopCount || (node >= stopCount && node < stopCount + hospitalCount))
                {
                    stopNumber++;
                }
            }
        }

        // Update state
        currentSchool = nextSchool;
        currentNode = targetNode;
        visitedSchools[currentSchool] = true;
        schoolsVisited++;

        cout << "\n Arrived at " << schools[currentSchool].name << "!\n";
        cout << "   Schools visited: " << schoolsVisited << "/" << schoolCount << "\n\n";

        if (schoolsVisited < schoolCount)
        {
            cout << "Waiting 3 seconds before finding next school...\n\n";
            SLEEP(3000);
        }

    }

    // Returning to starting school
    cout << "\n===============================================================\n";
    cout << "            RETURNING TO STARTING SCHOOL                      \n";
    cout << "===============================================================\n\n";

    int startNode = schoolNodesStart + startSchoolIdx;

    static int dist2[500];
    static int parent2[500];
    const int INF = 1000000000;

    for (int i = 0; i < totalNodes; i++)
    {
        dist2[i] = INF;
        parent2[i] = -1;
    }

    cityGraph.dijkstra(currentNode, dist2, parent2);

    if (dist2[startNode] < INF)
    {
        int returnPath[100];
        int returnLength = 0;
        int curr = startNode;

        while (curr != -1)
        {
            returnPath[returnLength++] = curr;
            curr = parent2[curr];
        }

        for (int i = 0; i < returnLength / 2; i++)
        {
            int temp = returnPath[i];
            returnPath[i] = returnPath[returnLength - 1 - i];
            returnPath[returnLength - 1 - i] = temp;
        }

        cout << "Return route summary: " << (returnLength - 1) << " segments\n";
        cout << "---------------------------------------------------------------\n\n";

        for (int i = 1; i < returnLength; i++)
        {
            int node = returnPath[i];

            if (node < stopCount)
            {
                cout << " >> " << stops[node].name;
            }
            else if (node >= schoolNodesStart && node < schoolNodesStart + schoolCount)
            {
                int schoolIdx = node - schoolNodesStart;
                cout << " >> " << schools[schoolIdx].name;
            }
            else if (node >= stopCount && node < stopCount + hospitalCount)
            {
                int hospitalIdx = node - stopCount;
                cout << " >> " << hospitals[hospitalIdx].name;
            }

            if (i < returnLength - 1)
            {
                AdjNode* edge = cityGraph.getAdjList(returnPath[i - 1]);
                int edgeWeight = 0;
                while (edge != nullptr)
                {
                    if (edge->vertex == node)
                    {
                        edgeWeight = edge->weight;
                        break;
                    }
                    edge = edge->next;
                }

                totalDistance += edgeWeight;
                totalTime += 5;

                cout << " (" << (edgeWeight / 1000.0) << " km)\n";
                SLEEP(5000);
            }
            else
            {
                cout << " - ARRIVED!\n";
            }
        }
    }

    // Final summary
    cout << "\n\n===============================================================\n";
    cout << "               BUS ROUTE COMPLETED!                           \n";
    cout << "===============================================================\n";
    cout << " Returned to: " << schools[startSchoolIdx].name << "\n";
    cout << " Total Schools Visited: " << schoolCount << "\n";
    cout << " Total Distance: " << (totalDistance / 1000.0) << " km\n";
    cout << " Total Time: " << totalTime << " seconds\n";
    cout << "===============================================================\n\n";

}

void SmartCity::displayTopSchools(int n) {
    if (n <= 0 || schoolCount == 0) {
        cout << "No schools to display." << endl;
        return;
    }

    cout << "\n TOP " << n << " SCHOOLS BY RATING 🏆" << endl;
    cout << "=================================================" << endl;

    // Build heap AND array for tracking
    MinHeap ratingHeap(schoolCount);

    struct SchoolRatingInfo {
        int rating;
        int index;
    };

    SchoolRatingInfo ratingData[MAX_SCHOOLS];

    // Build heap with negative ratings (for max heap behavior)
    for (int i = 0; i < schoolCount; i++) {
        ratingData[i].rating = schools[i].ranking;
        ratingData[i].index = i;
        ratingHeap.insert(-schools[i].ranking);  // Negative for max heap
    }

    // Sort array by rating (descending)
    for (int i = 0; i < schoolCount - 1; i++) {
        for (int j = i + 1; j < schoolCount; j++) {
            if (ratingData[j].rating > ratingData[i].rating) {
                SchoolRatingInfo temp = ratingData[i];
                ratingData[i] = ratingData[j];
                ratingData[j] = temp;
            }
        }
    }

    int displayCount = (n < schoolCount) ? n : schoolCount;

    for (int i = 0; i < displayCount; i++) {
        int idx = ratingData[i].index;

        cout << "\n" << (i + 1) << ". 🏫 " << schools[idx].name << endl;
        cout << "    Sector: " << schools[idx].sector << endl;
        cout << "    Rating: " << (schools[idx].ranking / 10.0) << "/5.0" << endl;
        cout << "    Subjects (" << schools[idx].subjectCount << "): ";

        for (int j = 0; j < schools[idx].subjectCount; j++) {
            cout << schools[idx].subjects[j];
            if (j < schools[idx].subjectCount - 1) cout << ", ";
        }
        cout << endl;

        // Location info
        cout << "     Location: (" << schools[idx].lat << ", " << schools[idx].lon << ")" << endl;
    }

    cout << "\n=================================================" << endl;
}

void SmartCity::generatePopulationHeatmap()
{
    cout << endl;
    cout << "ISLAMABAD POPULATION DENSITY HEATMAP " << endl;
    cout << "==========================================================" << endl;

    if (citizenCount == 0) {
        cout << "No population data available." << endl;
        return;
    }

    // Use same sector counting logic as your existing generatePopulationDensityReport()
    const int MAX_SECTORS = 50;

    struct SectorInfo {
        char sectorName[20];
        int population;
        char letter;
        int number;
    };

    SectorInfo sectors[MAX_SECTORS];
    int sectorCount = 0;

    // Count population per sector (same logic as your existing code)
    for (int i = 0; i < citizenCount; i++) {
        const char* sec = citizens[i].sector;

        // Find existing sector
        int idx = -1;
        for (int j = 0; j < sectorCount; j++) {
            if (manualStrCmp(sectors[j].sectorName, sec) == 0) {
                idx = j;
                break;
            }
        }

        // Add new sector or increment count
        if (idx == -1) {
            if (sectorCount < MAX_SECTORS) {
                manualStrCopy(sectors[sectorCount].sectorName, sec);
                sectors[sectorCount].population = 1;

                // Parse letter and number from sector (e.g., "G-10" or "F-8")
                sectors[sectorCount].letter = sec[0];

                // Extract number after dash or directly after letter
                int num = 0;
                int startIdx = 1;
                if (sec[1] == '-') startIdx = 2;  // Skip dash if present

                for (int k = startIdx; sec[k] != '\0' && sec[k] >= '0' && sec[k] <= '9'; k++) {
                    num = num * 10 + (sec[k] - '0');
                }
                sectors[sectorCount].number = num;

                sectorCount++;
            }
        }
        else {
            sectors[idx].population++;
        }
    }

    if (sectorCount == 0) {
        cout << " No valid sector data found." << endl;
        return;
    }

    // Find max population for scaling
    int maxPopulation = 0;
    for (int i = 0; i < sectorCount; i++) {
        if (sectors[i].population > maxPopulation) {
            maxPopulation = sectors[i].population;
        }
    }

    // Create grid for visualization
    const int GRID_ROWS = 10;  // Letters (rows)
    const int GRID_COLS = 15;  // Numbers (columns)
    int heatmapGrid[GRID_ROWS][GRID_COLS];
    char rowLetters[GRID_ROWS];

    // Initialize grid
    for (int i = 0; i < GRID_ROWS; i++) {
        rowLetters[i] = '\0';
        for (int j = 0; j < GRID_COLS; j++) {
            heatmapGrid[i][j] = 0;
        }
    }

    // Populate grid from sector data
    int usedRows = 0;
    for (int i = 0; i < sectorCount; i++) {
        char letter = sectors[i].letter;
        int number = sectors[i].number;

        if (number < 1 || number > GRID_COLS) continue;

        // Find or add row for this letter
        int rowIdx = -1;
        for (int r = 0; r < usedRows; r++) {
            if (rowLetters[r] == letter) {
                rowIdx = r;
                break;
            }
        }

        if (rowIdx == -1 && usedRows < GRID_ROWS) {
            rowIdx = usedRows;
            rowLetters[usedRows] = letter;
            usedRows++;
        }

        if (rowIdx >= 0 && rowIdx < GRID_ROWS) {
            heatmapGrid[rowIdx][number - 1] = sectors[i].population;
        }
    }

    // Sort rows alphabetically
    for (int i = 0; i < usedRows - 1; i++) {
        for (int j = i + 1; j < usedRows; j++) {
            if (rowLetters[i] > rowLetters[j]) {
                // Swap letters
                char tempLetter = rowLetters[i];
                rowLetters[i] = rowLetters[j];
                rowLetters[j] = tempLetter;

                // Swap entire rows
                for (int k = 0; k < GRID_COLS; k++) {
                    int temp = heatmapGrid[i][k];
                    heatmapGrid[i][k] = heatmapGrid[j][k];
                    heatmapGrid[j][k] = temp;
                }
            }
        }
    }

    // Display heatmap
    cout << "\n Population Distribution (Total: " << citizenCount << " citizens)" << endl;
    cout << "Max per sector: " << maxPopulation << " citizens" << endl;
    cout << "\n LEGEND (Population Ranges):" << endl;
    cout << "─────────────────────────────────────────────────────────" << endl;
    cout << "  [ . ] = Empty (0)           | [ A ] = Very Low (1-10)" << endl;
    cout << "  [ B ] = Low (11-30)         | [ C ] = Medium-Low (31-50)" << endl;
    cout << "  [ D ] = Medium (51-70)      | [ E ] = Medium-High (71-90)" << endl;
    cout << "  [ F ] = High (91-110)       | [ G ] = Very High (111-130)" << endl;
    cout << "  [ H ] = Extremely High (131-150) | [ I ] = Maximum (151+)" << endl;
    cout << "─────────────────────────────────────────────────────────" << endl;
    cout << "\n    ";

    // Column headers (sector numbers 1-15)
    for (int j = 0; j < GRID_COLS; j++) {
        if (j + 1 < 10) {
            cout << " " << (j + 1) << " ";
        }
        else {
            cout << (j + 1) << " ";
        }
    }
    cout << "\n";

    // Display grid rows with letter-based density
    for (int i = 0; i < usedRows; i++) {
        cout << " " << rowLetters[i] << "  ";

        for (int j = 0; j < GRID_COLS; j++) {
            int population = heatmapGrid[i][j];

            char densityChar;

            // Map population to density letters
            if (population == 0) {
                densityChar = '.';  // Empty
            }
            else if (population >= 1 && population <= 10) {
                densityChar = 'A';  // Very Low (1-10)
            }
            else if (population >= 11 && population <= 30) {
                densityChar = 'B';  // Low (11-30)
            }
            else if (population >= 31 && population <= 50) {
                densityChar = 'C';  // Medium-Low (31-50)
            }
            else if (population >= 51 && population <= 70) {
                densityChar = 'D';  // Medium (51-70)
            }
            else if (population >= 71 && population <= 90) {
                densityChar = 'E';  // Medium-High (71-90)
            }
            else if (population >= 91 && population <= 110) {
                densityChar = 'F';  // High (91-110)
            }
            else if (population >= 111 && population <= 130) {
                densityChar = 'G';  // Very High (111-130)
            }
            else if (population >= 131 && population <= 150) {
                densityChar = 'H';  // Extremely High (131-150)
            }
            else {
                densityChar = 'I';  // Maximum (151+)
            }

            cout << "[ " << densityChar << " ]";
        }
        cout << "\n";
    }

    // Statistics (reuse your existing sorting logic)
    cout << endl;
    cout << " DETAILED STATISTICS:" << endl;
    cout << "──────────────────────────────────────────────────────────" << endl;

    // Sort sectors by population (descending)
    for (int i = 0; i < sectorCount - 1; i++) {
        for (int j = i + 1; j < sectorCount; j++) {
            if (sectors[j].population > sectors[i].population) {
                SectorInfo temp = sectors[i];
                sectors[i] = sectors[j];
                sectors[j] = temp;
            }
        }
    }

    cout << endl;
    // Display top 10 populated sectors with density grade
    cout << " TOP 10 MOST POPULATED SECTORS:" << endl;
    int displayTop = (sectorCount < 10) ? sectorCount : 10;

    for (int i = 0; i < displayTop; i++) {
        float percentage = (sectors[i].population * 100.0) / citizenCount;

        // Determine density grade
        char grade;
        const char* gradeDesc;

        int pop = sectors[i].population;
        if (pop >= 151) {
            grade = 'I';
            gradeDesc = "Maximum";
        }
        else if (pop >= 131) {
            grade = 'H';
            gradeDesc = "Extremely High";
        }
        else if (pop >= 111) {
            grade = 'G';
            gradeDesc = "Very High";
        }
        else if (pop >= 91) {
            grade = 'F';
            gradeDesc = "High";
        }
        else if (pop >= 71) {
            grade = 'E';
            gradeDesc = "Medium-High";
        }
        else if (pop >= 51) {
            grade = 'D';
            gradeDesc = "Medium";
        }
        else if (pop >= 31) {
            grade = 'C';
            gradeDesc = "Medium-Low";
        }
        else if (pop >= 11) {
            grade = 'B';
            gradeDesc = "Low";
        }
        else {
            grade = 'A';
            gradeDesc = "Very Low";
        }

        // Create visual bar
        int barLength = (int)((sectors[i].population * 30.0) / maxPopulation);

        cout << "   " << (i + 1) << ". " << sectors[i].sectorName << ": ";

        // Padding for alignment
        int nameLen = 0;
        while (sectors[i].sectorName[nameLen] != '\0') nameLen++;
        for (int k = nameLen; k < 10; k++) cout << " ";

        cout << "[" << grade << "] " << gradeDesc;

        // Padding for grade description
        int gradeLen = 0;
        while (gradeDesc[gradeLen] != '\0') gradeLen++;
        for (int k = gradeLen; k < 15; k++) cout << " ";

        cout << " - " << sectors[i].population << " citizens (" << (int)percentage << "%) ";

        // Visual bar
        cout << "[";
        for (int b = 0; b < barLength; b++) cout << "█";
        for (int b = barLength; b < 30; b++) cout << " ";
        cout << "]" << endl;
    }

    // Distribution by density grade
    cout << "\n DISTRIBUTION BY DENSITY GRADE:" << endl;
    int gradeCount[9] = { 0 }; // A through I

    for (int i = 0; i < sectorCount; i++) {
        int pop = sectors[i].population;

        if (pop >= 151) gradeCount[8]++;          // I
        else if (pop >= 131) gradeCount[7]++;     // H
        else if (pop >= 111) gradeCount[6]++;     // G
        else if (pop >= 91) gradeCount[5]++;      // F
        else if (pop >= 71) gradeCount[4]++;      // E
        else if (pop >= 51) gradeCount[3]++;      // D
        else if (pop >= 31) gradeCount[2]++;      // C
        else if (pop >= 11) gradeCount[1]++;      // B
        else if (pop >= 1) gradeCount[0]++;       // A
    }

    cout << "   Grade I (151+):      " << gradeCount[8] << " sectors" << endl;
    cout << "   Grade H (131-150):   " << gradeCount[7] << " sectors" << endl;
    cout << "   Grade G (111-130):   " << gradeCount[6] << " sectors" << endl;
    cout << "   Grade F (91-110):    " << gradeCount[5] << " sectors" << endl;
    cout << "   Grade E (71-90):     " << gradeCount[4] << " sectors" << endl;
    cout << "   Grade D (51-70):     " << gradeCount[3] << " sectors" << endl;
    cout << "   Grade C (31-50):     " << gradeCount[2] << " sectors" << endl;
    cout << "   Grade B (11-30):     " << gradeCount[1] << " sectors" << endl;
    cout << "   Grade A (1-10):      " << gradeCount[0] << " sectors" << endl;

    // Distribution summary
    cout << "\n GENERAL SUMMARY:" << endl;
    cout << "   Total occupied sectors: " << sectorCount << endl;

    if (sectorCount > 0) {
        float avgPop = (float)citizenCount / sectorCount;
        cout << "   Average per sector: " << (int)avgPop << " citizens" << endl;
    }

    // Find most/least populated
    if (sectorCount > 0) {
        cout << "   Most populated: " << sectors[0].sectorName
            << " (" << sectors[0].population << " citizens)" << endl;
        cout << "   Least populated: " << sectors[sectorCount - 1].sectorName
            << " (" << sectors[sectorCount - 1].population << " citizens)" << endl;
    }

    cout << "==========================================================" << endl;
}



void SmartCity::emergencyTransportRouting() {
    cout << "\n";
    cout << "===============================================================\n";
    cout << "           EMERGENCY TRANSPORT ROUTING SYSTEM                 \n";
    cout << "===============================================================\n\n";


    cout << "Emergency Type:\n";
    cout << "---------------------------------------------------------------\n";
    cout << "1. Heart Attack / Cardiac Arrest (CRITICAL)\n";
    cout << "2. Severe Trauma / Major Injury (CRITICAL)\n";
    cout << "3. Stroke / Breathing Problem (URGENT)\n";
    cout << "4. Severe Pain / Burns (URGENT)\n";
    cout << "5. Fracture / Minor Injury (STANDARD)\n";
    cout << "6. Illness / Fever (STANDARD)\n";
    cout << "---------------------------------------------------------------\n";
    cout << "Select emergency type (1-6): ";

    int emergencyType;
    cin >> emergencyType;

    if (emergencyType < 1 || emergencyType > 6) {
        cout << "XX Invalid type!\n";
        return;
    }

    // Determine priority
    int priority;
    const char* typeDescription;
    const char* priorityLabel;

    switch (emergencyType) {
    case 1:
        typeDescription = "Heart Attack";
        priority = 1;
        priorityLabel = "CRITICAL";
        break;
    case 2:
        typeDescription = "Severe Trauma";
        priority = 1;
        priorityLabel = "CRITICAL";
        break;
    case 3:
        typeDescription = "Stroke";
        priority = 2;
        priorityLabel = "URGENT";
        break;
    case 4:
        typeDescription = "Severe Pain/Burns";
        priority = 2;
        priorityLabel = "URGENT";
        break;
    case 5:
        typeDescription = "Fracture";
        priority = 3;
        priorityLabel = "STANDARD";
        break;
    case 6:
        typeDescription = "Illness";
        priority = 3;
        priorityLabel = "STANDARD";
        break;
    default:
        typeDescription = "Unknown";
        priority = 3;
        priorityLabel = "STANDARD";
    }

    cout << "\nEmergency Pickup Location:\n";
    cout << "---------------------------------------------------------------\n";
    cout << "\n[BUS STOPS]\n";
    for (int i = 0; i < stopCount; i++) {
        cout << "  " << (i + 1) << ". " << stops[i].name << "\n";
    }

    cout << "\n[SCHOOLS]\n";
    for (int i = 0; i < schoolCount; i++) {
        cout << "  " << (stopCount + i + 1) << ". " << schools[i].name << "\n";
    }
    cout << "---------------------------------------------------------------\n\n";

    int totalLocations = stopCount + schoolCount;
    int choice;

    cout << "Enter emergency location (1-" << totalLocations << "): ";
    cin >> choice;

    if (choice < 1 || choice > totalLocations) {
        cout << "XX Invalid choice!\n";
        return;
    }

    int emergencyNode = -1;
    const char* emergencyLocation = nullptr;

    if (choice <= stopCount) {
        emergencyNode = choice - 1;
        emergencyLocation = stops[emergencyNode].name;
    }
    else {
        int schoolIdx = choice - stopCount - 1;
        int schoolNodesStart = stopCount + hospitalCount;
        emergencyNode = schoolNodesStart + schoolIdx;
        emergencyLocation = schools[schoolIdx].name;
    }

    cout << "\n===============================================================\n";
    cout << " EMERGENCY CALL RECEIVED                                      \n";
    cout << "===============================================================\n";
    cout << " Type: " << typeDescription << "\n";
    cout << " Priority: " << priorityLabel << "\n";
    cout << " Location: " << emergencyLocation << "\n";
    cout << "===============================================================\n";
    cout << " Analyzing hospitals and dispatching ambulance...\n";
    cout << "===============================================================\n\n";

    SLEEP(2000);

    cout << "Scanning all hospitals...\n\n";

    static int dist[500];
    static int parent[500];
    const int INF = 1000000000;

    for (int i = 0; i < totalNodes; i++) {
        dist[i] = INF;
        parent[i] = -1;
    }

    cityGraph.dijkstra(emergencyNode, dist, parent);

    // Display all reachable hospitals with scoring
    cout << "---------------------------------------------------------------\n";
    cout << "Hospital Analysis:\n";
    cout << "---------------------------------------------------------------\n";

    struct HospitalScore {
        int index;
        int distance;
        int beds;
        int score;
        int node;
    };

    HospitalScore scores[50];
    int scoreCount = 0;

    for (int i = 0; i < hospitalCount; i++) {
        int hNode = stopCount + i;

        if (dist[hNode] >= INF) continue;

        scores[scoreCount].index = i;
        scores[scoreCount].distance = dist[hNode];
        scores[scoreCount].beds = hospitals[i].emergencyBeds;
        scores[scoreCount].node = hNode;

        // SCORING ALGORITHM:
        // Has beds: +1000 points
        // Distance: -(distance/100) points
        // Priority bonus cases prioritize closer hospitals

        int score = 0;

        if (hospitals[i].emergencyBeds > 0) {
            score += 1000;
        }

        score -= (dist[hNode] / 100);

        if (priority == 1) {
            score += (10000 - dist[hNode]) / 50;
        }

        scores[scoreCount].score = score;

        cout << "  " << hospitals[i].name << "\n";
        cout << "    Distance: " << (dist[hNode] / 1000.0) << " km\n";
        cout << "    Beds Available: " << hospitals[i].emergencyBeds << "\n";
        cout << "    Score: " << score << (score == 0 ? " (NO BEDS)" : "") << "\n\n";

        scoreCount++;
    }

    // Find best score
    int bestIdx = -1;
    int bestScore = -1000000;

    for (int i = 0; i < scoreCount; i++) {
        if (scores[i].score > bestScore) {
            bestScore = scores[i].score;
            bestIdx = i;
        }
    }

    if (bestIdx == -1) {
        cout << "XX ERROR: No reachable hospitals!\n";
        return;
    }

    int selectedHospital = scores[bestIdx].index;
    int hospitalNode = scores[bestIdx].node;
    int nearestDistance = scores[bestIdx].distance;

    cout << "---------------------------------------------------------------\n\n";
    cout << "===============================================================\n";
    cout << " OPTIMAL HOSPITAL SELECTED                                   \n";
    cout << "===============================================================\n";
    cout << " Hospital: " << hospitals[selectedHospital].name << "\n";
    cout << " Sector: " << hospitals[selectedHospital].sector << "\n";
    cout << " Distance: " << (nearestDistance / 1000.0) << " km\n";
    cout << " Emergency Beds: " << hospitals[selectedHospital].emergencyBeds << "\n";
    cout << " Selection Score: " << bestScore << " (BEST MATCH)\n";
    cout << " Estimated ETA: " << ((nearestDistance / 1000.0) * 1.5) << " minutes\n";
    cout << "===============================================================\n";
    cout << " Reason: ";

    if (hospitals[selectedHospital].emergencyBeds > 0) {
        cout << "Beds available + ";
    }
    cout << "Optimal distance for " << priorityLabel << " case\n";
    cout << "===============================================================\n\n";

    SLEEP(3000);

    int pathToEmergency[100];
    int pathLength = 0;
    int curr = hospitalNode;

    while (curr != -1) {
        pathToEmergency[pathLength++] = curr;
        curr = parent[curr];
    }

    cout << "===============================================================\n";
    cout << "     LEG 1: AMBULANCE DISPATCH FROM HOSPITAL                 \n";
    cout << "===============================================================\n";
    cout << " Route: " << (pathLength - 1) << " segments\n";
    cout << " Priority: " << priorityLabel << "\n";
    cout << "---------------------------------------------------------------\n\n";

    cout << "Press Enter to START emergency dispatch...";
    cin.ignore(10000, '\n');
    cin.get();

    cout << "\n\n";
    cout << "===============================================================\n";
    cout << "      AMBULANCE EN ROUTE TO EMERGENCY - " << priorityLabel << "       \n";
    cout << "===============================================================\n\n";

    int totalTime = 0;
    int totalDistance = 0;

    for (int i = 0; i < pathLength; i++) {
        int node = pathToEmergency[i];

        cout << "===============================================================\n";

        if (i == 0) {
            cout << " AMBULANCE DISPATCH - LEAVING HOSPITAL                       \n";
        }
        else if (i == pathLength - 1) {
            cout << " EMERGENCY LOCATION REACHED                                  \n";
        }
        else {
            cout << " CHECKPOINT #" << i << " - EN ROUTE                                  \n";
        }

        cout << "===============================================================\n";

        // Display location info
        if (node < stopCount) {
            cout << " Location: " << stops[node].name << "\n";
            cout << " Type: Bus Stop\n";

        }
        else if (node >= stopCount && node < stopCount + hospitalCount) {
            int hospIdx = node - stopCount;
            cout << " Location: " << hospitals[hospIdx].name << "\n";
            cout << " Type: Hospital\n";

        }
        else {
            int schoolNodesStart = stopCount + hospitalCount;
            if (node >= schoolNodesStart && node < schoolNodesStart + schoolCount) {
                int schoolIdx = node - schoolNodesStart;
                cout << " Location: " << schools[schoolIdx].name << "\n";
                cout << " Type: School\n";
            }
        }

        cout << " Elapsed Time: " << totalTime << " seconds\n";

        if (i < pathLength - 1) {
            AdjNode* edge = cityGraph.getAdjList(node);
            int edgeWeight = 0;

            while (edge != nullptr) {
                if (edge->vertex == pathToEmergency[i + 1]) {
                    edgeWeight = edge->weight;
                    break;
                }
                edge = edge->next;
            }

            totalDistance += edgeWeight;

            cout << " Distance to next: " << (edgeWeight / 1000.0) << " km\n";
            cout << "===============================================================\n";

            if (priority == 1) {
                cout << "    >> CRITICAL EMERGENCY >> FULL SPEED >> SIRENS >>\n";
            }
            else if (priority == 2) {
                cout << "    >> URGENT RESPONSE >> FAST ROUTE >> LIGHTS ON >>\n";
            }
            else {
                cout << "    >> STANDARD RESPONSE >> NORMAL SPEED >>\n";
            }

            cout << "===============================================================\n\n";

            totalTime += 3;
            SLEEP(3000);

        }
        else {
            cout << "===============================================================\n";
            cout << "    PARAMEDICS ON SCENE - PATIENT STABILIZATION\n";
            cout << "===============================================================\n\n";
            SLEEP(3000);
        }
    }

    for (int i = 0; i < totalNodes; i++) {
        dist[i] = INF;
        parent[i] = -1;
    }

    cityGraph.dijkstra(emergencyNode, dist, parent);

    int returnPath[100];
    int returnLength = 0;
    curr = hospitalNode;

    while (curr != -1) {
        returnPath[returnLength++] = curr;
        curr = parent[curr];
    }

    for (int i = 0; i < returnLength / 2; i++) {
        int temp = returnPath[i];
        returnPath[i] = returnPath[returnLength - 1 - i];
        returnPath[returnLength - 1 - i] = temp;
    }

    cout << "\n===============================================================\n";
    cout << "     LEG 2: TRANSPORTING PATIENT TO HOSPITAL                 \n";
    cout << "===============================================================\n";
    cout << " Patient Status: ";

    if (priority == 1) {
        cout << "CRITICAL - MONITORING VITALS\n";
    }
    else if (priority == 2) {
        cout << "URGENT - STABILIZED\n";
    }
    else {
        cout << "STABLE\n";
    }

    cout << " Destination: " << hospitals[selectedHospital].name << "\n";
    cout << "===============================================================\n\n";

    for (int i = 1; i < returnLength; i++) {
        int node = returnPath[i];

        cout << "===============================================================\n";

        if (i == returnLength - 1) {
            cout << " HOSPITAL ARRIVAL - EMERGENCY WARD READY                    \n";
        }
        else {
            cout << " RETURNING - CHECKPOINT #" << i << "                                 \n";
        }

        cout << "===============================================================\n";

        if (node < stopCount) {
            cout << " Location: " << stops[node].name << "\n";
        }
        else if (node >= stopCount && node < stopCount + hospitalCount) {
            int hospIdx = node - stopCount;
            cout << " Location: " << hospitals[hospIdx].name << "\n";
        }
        else {
            int schoolNodesStart = stopCount + hospitalCount;
            if (node >= schoolNodesStart) {
                int schoolIdx = node - schoolNodesStart;
                cout << " Location: " << schools[schoolIdx].name << "\n";
            }
        }

        cout << " Elapsed Time: " << totalTime << " seconds\n";

        if (i < returnLength - 1) {
            AdjNode* edge = cityGraph.getAdjList(returnPath[i - 1]);
            int edgeWeight = 0;

            while (edge != nullptr) {
                if (edge->vertex == node) {
                    edgeWeight = edge->weight;
                    break;
                }
                edge = edge->next;
            }

            totalDistance += edgeWeight;

            cout << " Distance to next: " << (edgeWeight / 1000.0) << " km\n";
            cout << "===============================================================\n";

            if (priority == 1) {
                cout << "    >> CRITICAL PATIENT >> RUSHING TO ER >>\n";
            }
            else {
                cout << "    >> PATIENT TRANSPORT >> MEDICAL CARE ONGOING >>\n";
            }

            cout << "===============================================================\n\n";

            totalTime += 3;
            SLEEP(3000);

        }
        else {
            cout << "===============================================================\n";
            cout << "    PATIENT HANDOFF TO EMERGENCY DEPARTMENT\n";
            cout << "===============================================================\n\n";
        }
    }

    cout << "\n\n";
    cout << "===============================================================\n";
    cout << "      EMERGENCY TRANSPORT MISSION COMPLETED                  \n";
    cout << "===============================================================\n";
    cout << " Emergency Type: " << typeDescription << "\n";
    cout << " Priority: " << priorityLabel << "\n";
    cout << " Pickup Location: " << emergencyLocation << "\n";
    cout << " Hospital: " << hospitals[selectedHospital].name << "\n";
    cout << "---------------------------------------------------------------\n";
    cout << " Total Distance Traveled: " << (totalDistance / 1000.0) << " km\n";
    cout << " Total Time: " << totalTime << " seconds (" << (totalTime / 60.0) << " min)\n";
    cout << " Route Segments: " << (pathLength + returnLength - 2) << "\n";
    cout << "---------------------------------------------------------------\n";
    cout << " Patient Status: ADMITTED AND RECEIVING CARE ?\n";
    cout << " Medical Team: ON DUTY\n";
    cout << " Ambulance: AVAILABLE FOR NEXT CALL\n";
    cout << "===============================================================\n\n";

    // Update hospital beds
    if (hospitals[selectedHospital].emergencyBeds > 0) {
        hospitals[selectedHospital].emergencyBeds--;
        cout << " Hospital bed allocated\n";
        cout << "  Remaining emergency beds at " << hospitals[selectedHospital].name
            << ": " << hospitals[selectedHospital].emergencyBeds << "\n\n";
    }
    else {
        cout << "XX Hospital at capacity - patient in overflow care\n\n";
    }

    cout << "Mission ID: EM-" << (rand() % 9000 + 1000) << "\n";
    cout << "Status: CLOSED - SUCCESSFUL\n\n";
}


void SmartCity::findRouteToAirport() {
    cout << "\n===============================================================\n";
    cout << "           AIRPORT TRANSFER ROUTING SYSTEM                    \n";
    cout << "===============================================================\n\n";

    const char* airportName = "Islamabad International Airport";

    int airportNode = stopCount + hospitalCount + schoolCount;

    cout << "Destination: " << airportName << "\n\n";

    cout << "Select Your Current Location:\n";
    cout << "---------------------------------------------------------------\n";
    cout << "[BUS STOPS]\n";
    for (int i = 0; i < stopCount; i++)
    {
        cout << "  " << (i + 1) << ". " << stops[i].name << "\n";
    }
    cout << "\n[SCHOOLS]\n";
    for (int i = 0; i < schoolCount; i++)
    {
        cout << "  " << (stopCount + i + 1) << ". " << schools[i].name << "\n";
    }
    cout << "\n[HOSPITALS]\n";
    for (int i = 0; i < hospitalCount; i++)
    {
        cout << "  " << (stopCount + schoolCount + i + 1) << ". " << hospitals[i].name << "\n";
    }
    cout << "---------------------------------------------------------------\n\n";

    int totalLocs = stopCount + schoolCount + hospitalCount;
    int choice;
    cout << "Enter location (1-" << totalLocs << "): ";
    cin >> choice;

    if (choice < 1 || choice > totalLocs)
    {
        cout << "XX Invalid choice!\n";
        return;
    }


    int startNode = -1;
    const char* startLocation = nullptr;

    if (choice <= stopCount)
    {
        // Bus stop
        startNode = choice - 1;
        startLocation = stops[startNode].name;
    }
    else if (choice <= stopCount + schoolCount) \
    {
        // School
        int schoolIdx = choice - stopCount - 1;
        int schoolNodesStart = stopCount + hospitalCount;
        startNode = schoolNodesStart + schoolIdx;
        startLocation = schools[schoolIdx].name;
    }
    else
    {
        // Hospital
        int hospitalIdx = choice - stopCount - schoolCount - 1;
        startNode = stopCount + hospitalIdx;
        startLocation = hospitals[hospitalIdx].name;
    }

    cout << "\n===============================================================\n";
    cout << " ROUTE PLANNING                                               \n";
    cout << "===============================================================\n";
    cout << " From: " << startLocation << "\n";
    cout << " To: " << airportName << "\n";
    cout << "===============================================================\n";
    cout << " Calculating optimal route...\n";
    cout << "===============================================================\n\n";

    SLEEP(2000);


    // Connect airport to last 2 , 3 bus stops as airport shuttles
    int airportConnections[10];
    int connectionCount = 0;

    // Connect to last few stops simulating shuttle routes
    for (int i = stopCount - 1; i >= 0 && connectionCount < 3; i--) {
        int distance = 12000 + (connectionCount * 2000); // 12-16 km
        cityGraph.addEdge(i, airportNode, distance);
        cityGraph.addEdge(airportNode, i, distance);
        airportConnections[connectionCount++] = i;
    }

    static int dist[500];
    static int parent[500];
    const int INF = 1000000000;

    for (int i = 0; i <= airportNode; i++)
    {
        dist[i] = INF;
        parent[i] = -1;
    }

    cityGraph.dijkstra(startNode, dist, parent);

    if (dist[airportNode] >= INF)
    {
        cout << "XX No route found to airport!\n";

        // Remove temporary connections
        for (int i = 0; i < connectionCount; i++) {

        }
        return;
    }

    int path[100];
    int pathLength = 0;
    int curr = airportNode;

    while (curr != -1)
    {
        path[pathLength++] = curr;
        curr = parent[curr];
    }

    // Reverse path
    for (int i = 0; i < pathLength / 2; i++)
    {
        int temp = path[i];
        path[i] = path[pathLength - 1 - i];
        path[pathLength - 1 - i] = temp;
    }

    cout << "===============================================================\n";
    cout << " OPTIMAL ROUTE FOUND                                          \n";
    cout << "===============================================================\n";
    cout << " Total Distance: " << (dist[airportNode] / 1000.0) << " km\n";
    cout << " Estimated Time: " << ((dist[airportNode] / 1000.0) * 2.5) << " minutes\n";
    cout << " Number of Stops: " << (pathLength - 1) << "\n";

    // Check if shuttle is available
    bool hasShuttle = false;
    for (int i = 0; i < connectionCount; i++)
    {
        if (path[pathLength - 2] == airportConnections[i])
        {
            hasShuttle = true;
            break;
        }
    }

    cout << " Transfer Type: " << (hasShuttle ? "AIRPORT SHUTTLE" : "REGULAR BUS") << "\n";
    if (hasShuttle)
    {
        cout << " Shuttle Fare: PKR 250\n";
        cout << " Frequency: Every 30 minutes\n";
    }
    cout << "===============================================================\n\n";

    cout << "Press Enter to view detailed route...";
    cin.ignore(10000, '\n');
    cin.get();

    cout << "\n\n===============================================================\n";
    cout << "           JOURNEY TO AIRPORT - STEP BY STEP                  \n";
    cout << "===============================================================\n\n";

    int totalTime = 0;

    for (int i = 0; i < pathLength; i++)
    {
        int node = path[i];

        cout << "===============================================================\n";
        cout << " STEP " << (i + 1) << " / " << pathLength << "\n";
        cout << "===============================================================\n";

        // Display node info
        if (node == airportNode)
        {
            cout << " Location: " << airportName << "\n";
            cout << " Type: AIRPORT TERMINAL\n";
            cout << " Status: ARRIVAL\n";

        }
        else if (node < stopCount)
        {
            cout << " Location: " << stops[node].name << "\n";
            cout << " Type: Bus Stop\n";
            cout << " Stop ID: " << stops[node].id << "\n";

            // Check if this is shuttle transfer point
            bool isShuttleStop = false;
            for (int j = 0; j < connectionCount; j++)
            {
                if (node == airportConnections[j] && i == pathLength - 2)
                {
                    isShuttleStop = true;
                    break;
                }
            }

            if (isShuttleStop)
            {
                cout << " ** TRANSFER TO AIRPORT SHUTTLE HERE **\n";
            }

        }
        else if (node >= stopCount && node < stopCount + hospitalCount)
        {
            int hospIdx = node - stopCount;
            cout << " Location: " << hospitals[hospIdx].name << "\n";
            cout << " Type: Hospital\n";

        }
        else {
            int schoolNodesStart = stopCount + hospitalCount;
            if (node >= schoolNodesStart && node < schoolNodesStart + schoolCount)
            {
                int schoolIdx = node - schoolNodesStart;
                cout << " Location: " << schools[schoolIdx].name << "\n";
                cout << " Type: School\n";
            }
        }

        cout << " Time Elapsed: " << totalTime << " seconds\n";

        // Get distance to next stop
        if (i < pathLength - 1)
        {
            AdjNode* edge = cityGraph.getAdjList(node);
            int edgeWeight = 0;

            while (edge != nullptr)
            {
                if (edge->vertex == path[i + 1])
                {
                    edgeWeight = edge->weight;
                    break;
                }
                edge = edge->next;
            }

            cout << " Distance to Next: " << (edgeWeight / 1000.0) << " km\n";
            cout << "===============================================================\n";

            if (i == pathLength - 2)
            {
                cout << "    >> BOARDING AIRPORT SHUTTLE >>\n";
            }
            else
            {
                cout << "    >> TRAVELING TO NEXT STOP >>\n";
            }

            cout << "===============================================================\n\n";

            totalTime += 5;
            SLEEP(3000);

        }
        else {
            cout << "===============================================================\n";
            cout << "    ARRIVED AT AIRPORT - CHECK-IN COUNTERS AHEAD\n";
            cout << "===============================================================\n\n";
        }
    }

    cout << "\n===============================================================\n";
    cout << "           JOURNEY COMPLETE - AIRPORT REACHED                 \n";
    cout << "===============================================================\n";
    cout << " Departure: " << startLocation << "\n";
    cout << " Arrival: " << airportName << "\n";
    cout << " Total Distance: " << (dist[airportNode] / 1000.0) << " km\n";
    cout << " Total Time: " << totalTime << " seconds (" << (totalTime / 60) << " min)\n";
    cout << " Stops Passed: " << (pathLength - 1) << "\n";

    if (hasShuttle)
    {
        cout << " Shuttle Used: YES\n";
        cout << " Total Fare: PKR 250 (Shuttle) + PKR 50 (City Bus)\n";
    }
    else
    {
        cout << " Transport: Regular City Bus\n";
        cout << " Fare: PKR 100\n";
    }

    cout << "===============================================================\n";
    cout << " Recommended Arrival: 2 hours before flight departure\n";
    cout << " Terminal Info: Check ticket for terminal number\n";
    cout << " Facilities: Cafes, Duty-Free, Lounges available\n";
    cout << "===============================================================\n\n";


    cout << "Route ID: APT-" << (rand() % 9000 + 1000) << "\n";
    cout << "Status: PLANNING COMPLETE\n\n";
}

void SmartCity::simulateRealTimeRouting() {
    if (busCount == 0) {
        cout << " No buses available.\n";
        return;
    }

    cout << "\n=========================================================\n";
    cout << "|        REAL-TIME BUS ROUTE SIMULATION 🚌                |\n";
    cout << "=========================================================\n\n";

    cout << " AVAILABLE BUSES:\n";
    cout << "============================================================\n";
    for (int i = 0; i < busCount; i++) {
        cout << "  " << (i + 1) << ". Bus " << buses[i].busNo
            << " (" << buses[i].company << ")";

        // Show current location
        if (buses[i].currentStopIndex >= 0 && buses[i].currentStopIndex < stopCount) {
            cout << " - Currently at: " << stops[buses[i].currentStopIndex].name;
        }
        cout << "\n";
    }
    cout << "================================================================\n\n";

    int busNum;
    cout << " Select bus to simulate (1-" << busCount << "): ";
    cin >> busNum;

    if (busNum < 1 || busNum > busCount) {
        cout << " Invalid selection.\n";
        return;
    }

    int busIdx = busNum - 1;

    if (buses[busIdx].routeHead == nullptr) {
        cout << " This bus has no route defined.\n";
        return;
    }

    cout << "\n SIMULATION SETTINGS:\n";
    cout << "─────────────────────────────────────────────────────────\n";
    cout << "1.  Slow (5 seconds per stop)\n";
    cout << "2.  Fast (2 seconds per stop)\n";
    cout << "3.  Instant (no delay)\n";
    cout << "─────────────────────────────────────────────────────────\n";

    int speedChoice;
    cout << "Select speed (1-3): ";
    cin >> speedChoice;

    int delayTime;
    switch (speedChoice) {
    case 1: delayTime = 5000; break;
    case 2: delayTime = 2000; break;
    case 3: delayTime = 0; break;
    default: delayTime = 3000;
    }

    cout << "\n===========================================================\n";
    cout << "|   STARTING SIMULATION FOR BUS " << buses[busIdx].busNo << " | \n";
    cout << "============================================================== |\n\n";

    cout << " Bus: " << buses[busIdx].busNo << "\n";
    cout << " Company: " << buses[busIdx].company << "\n";

    // Count total stops
    RouteNode* counter = buses[busIdx].routeHead;
    int totalStops = 0;
    while (counter != nullptr) {
        totalStops++;
        counter = counter->next;
    }

    cout << " Total Stops: " << totalStops << "\n\n";

    cout << "Press Enter to START simulation...";
    cin.ignore(10000, '\n');
    cin.get();

    RouteNode* curr = buses[busIdx].routeHead;
    int stopNum = 1;
    int totalDistance = 0;
    int totalTime = 0;
    int passengers = rand() % 30 + 10;

    while (curr != nullptr)
    {
        int stopIdx = curr->stopIndex;

        if (stopIdx >= 0 && stopIdx < stopCount)
        {
            buses[busIdx].currentStopIndex = stopIdx;


            cout << "\n=============================================================\n";
            cout << "|   STOP #" << stopNum << "/" << totalStops;
            if (stopNum < 10) cout << " ";
            cout << "                                                |\n";
            cout << "=================================================================\n";

            cout << "|||  Location: " << stops[stopIdx].name;

            // Padding for alignment
            int nameLen = 0;
            while (stops[stopIdx].name[nameLen] != '\0') nameLen++;
            for (int j = nameLen; j < 39; j++) cout << " ";
            cout << "||\n";

            cout << "||  Stop ID: " << stops[stopIdx].id;
            for (int j = 0; j < 43; j++) cout << " ";
            cout << "||\n";

            cout << "||  GPS: (" << stops[stopIdx].location.lat << ", "
                << stops[stopIdx].location.lon << ")";

            // Calculate padding for GPS coordinates
            int coordLen = 10; // Approximate
            for (int j = coordLen; j < 29; j++) cout << " ";
            cout << "||\n";

            cout << "||  Passengers: " << passengers;
            for (int j = 0; j < 40; j++) cout << " ";
            cout << "||\n";

            cout << "||   Elapsed Time: " << totalTime << " seconds";
            int timeLen = 0;
            int temp = totalTime;
            if (temp == 0) timeLen = 1;
            else while (temp > 0) { timeLen++; temp /= 10; }
            for (int j = timeLen; j < 33; j++) cout << " ";
            cout << "||\n";

            int boarding = rand() % 8;
            int alighting = rand() % 5;
            passengers = passengers + boarding - alighting;
            if (passengers < 0) passengers = 0;
            if (passengers > 50) passengers = 50;

            cout << "║  Boarding: " << boarding << " passengers";
            for (int j = 0; j < 35; j++) cout << " ";
            cout << "║\n";

            cout << "║ ➖ Alighting: " << alighting << " passengers";
            for (int j = 0; j < 34; j++) cout << " ";
            cout << "║\n";

            //Distance and time to next stop
            if (curr->next != nullptr && curr->next->stopIndex >= 0 &&
                curr->next->stopIndex < stopCount)
            {

                double dist = computeDistance(
                    stops[stopIdx].location.lat, stops[stopIdx].location.lon,
                    stops[curr->next->stopIndex].location.lat,
                    stops[curr->next->stopIndex].location.lon
                );

                int distMeters = (int)(dist * 1000);
                totalDistance += distMeters;

                int timeToNext = (int)(dist * 3); // 3 min per km

                cout << "|===========================================|\n";
                cout << "|  Distance to next stop: " << dist << " km";
                for (int j = 0; j < 26; j++) cout << " ";
                cout << "|\n";

                cout << "|  Estimated time: " << timeToNext << " minutes";
                for (int j = 0; j < 32; j++) cout << " ";
                cout << "|\n";

                cout << "|  Next stop: " << stops[curr->next->stopIndex].name;

                int nextNameLen = 0;
                while (stops[curr->next->stopIndex].name[nextNameLen] != '\0')
                    nextNameLen++;
                for (int j = nextNameLen; j < 37; j++) cout << " ";
                cout << "|\n";
            }

            cout << "==========================================================\n";

            cout << "\n Progress: [";
            int progress = (stopNum * 40) / totalStops;
            for (int i = 0; i < progress; i++) cout << "█";
            for (int i = progress; i < 40; i++) cout << "░";
            cout << "] " << ((stopNum * 100) / totalStops) << "%\n\n";

            trackRouteHistory(stopIdx);
        }

        if (delayTime > 0) {
            cout << " Moving to next stop";
            for (int i = 0; i < 3; i++) {
                cout << ".";
                cout.flush();
                SLEEP(delayTime / 3);
            }
            cout << "\n";
        }
        else {
            cout << "Press Enter to continue (or 'q' to quit): ";
            char input;
            cin.get(input);
            if (input == 'q' || input == 'Q') break;
        }

        curr = curr->next;
        stopNum++;
        totalTime += (delayTime / 1000);
    }

    cout << "\n|========================================================|\n";
    cout << "|  SIMULATION COMPLETED!                                   |\n";
    cout << "|==========================================================|\n";
    cout << "|  Bus: " << buses[busIdx].busNo << " (" << buses[busIdx].company << ")";

    int companyLen = 0;
    while (buses[busIdx].company[companyLen] != '\0') companyLen++;
    for (int j = companyLen + 10; j < 44; j++) cout << " ";
    cout << "|\n";

    cout << "|  Stops Visited: " << (stopNum - 1) << "/" << totalStops;
    for (int j = 0; j < 36; j++) cout << " ";
    cout << "|\n";

    cout << "| Total Distance: " << (totalDistance / 1000.0) << " km";
    for (int j = 0; j < 33; j++) cout << " ";
    cout << "|\n";

    cout << "|   Total Time: " << totalTime << " seconds";
    for (int j = 0; j < 37; j++) cout << " ";
    cout << "|\n";

    cout << "|  Final Passengers: " << passengers;
    for (int j = 0; j < 36; j++) cout << " ";
    cout << "|\n";

    cout << "|============================================================|\n\n";
}