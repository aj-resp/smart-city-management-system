#define _CRT_SECURE_NO_WARNINGS

#include "SmartCityCore.h"

int main() 
{

    cout << "\n";
    cout << "====================================================\n";
    cout << "                                                    \n";
    cout << "    ???  SMART CITY MANAGEMENT SYSTEM  ???          \n";
    cout << "                                                    \n";
    cout << "        Islamabad Digital Transformation            \n";
    cout << "        Data Structures Project - Fall 2025         \n";
    cout << "                                                    \n";
    cout << "====================================================\n";
    cout << "\n";

    cout << "? Initializing Smart City System...\n\n";

    SmartCity city;


    cout << "?? Loading data from files...\n";
    cout << "----------------------------------------\n";

    city.loadTransportData("stops.csv", "buses.csv");
    city.loadEducationData("schools.csv");
    city.loadMedicalData("hospitals.csv", "pharmacies.csv");
    city.loadPopulationData("population.csv");
    city.loadCommercialData("malls.csv");              // 
    city.loadPublicFacilitiesData("facilities.csv");  //

    cout << "----------------------------------------\n";
    cout << "? All data files loaded successfully!\n\n";


    cout << "?? Building data structures...\n";
    cout << "----------------------------------------\n";

    cout << "  ? Building transport graph...\n";
    city.buildTransportGraph();

    cout << "  ? Building Islamabad hierarchy tree...\n";
    city.buildIslamabadHierarchyTree();

    cout << "  ? Building school system tree...\n";
    city.buildSchoolSystemTree();

    cout << "  ? Building population tree...\n";
    city.buildPopulationTree();

    cout << "  ? Building hash tables...\n";
    city.buildHashTables();

    cout << "  ? Building hospital priority queue...\n";
    city.buildHospitalPriorityQueue();

    cout << "  ? Building school ranking queue...\n";
    city.buildSchoolRankingQueue();

    cout << "----------------------------------------\n";
    cout << "? All data structures built successfully!\n\n";


    cout << "? SYSTEM INITIALIZATION COMPLETE!\n";
    cout << "====================================================\n";
    cout << "\n?? SYSTEM STATUS:\n";
    cout << "   ?? Transport System    : " << city.busCount << " buses, "
        << city.stopCount << " stops\n";
    cout << "   ?? Education System    : " << city.schoolCount << " schools\n";
    cout << "   ?? Medical System      : " << city.hospitalCount << " hospitals, "
        << city.pharmacyCount << " medicines\n";
    cout << "   ?? Population System   : " << city.citizenCount << " citizens\n";
    cout << "   ?? Commercial Sector   : " << city.mallCount << " malls\n";
    cout << "   ???  Public Facilities   : " << city.facilityCount << " facilities\n";
    cout << "\n?? DATA STRUCTURES ACTIVE:\n";
    cout << "   ? Graph (Adjacency List) - " << city.cityGraph.getVertices() << " vertices\n";
    cout << "   ? N-ary Trees (3 types)\n";
    cout << "   ? Hash Tables (7 tables)\n";
    cout << "   ? Priority Queues (2 heaps)\n";
    cout << "   ? Linked Lists (Routes)\n";
    cout << "   ? Stack (Route History)\n";
    cout << "   ? Circular Queue (Passengers)\n";
    cout << "\n====================================================\n";
    cout << "\n?? Starting Main Menu...\n\n";


    city.mainMenu();


    cout << "\n";
    cout << "====================================================\n";
    cout << "                                                    \n";
    cout << "    ?? Thank you for using Smart City System!      \n";
    cout << "                                                    \n";
    cout << "    System shutdown complete.                      \n";
    cout << "    All data structures cleaned up successfully.   \n";
    cout << "                                                    \n";
    cout << "====================================================\n";
    cout << "\n";

    return 0;
}




