#include <iostream>
#include <string>
using namespace std;

/* ---- Evidence 4: test harness, invoked as  ./library_adt --test ---- */
void runTests()
{
    cout << "===== TESTING RECORD =====\n";

    // T1: unsuccessful search on a populated catalogue
    {
        ArrayCatalog cat;
        cat.addBook(1004, "Computer Systems");
        cat.addBook(2004, "Data Structures");
        string t;
        bool found = cat.searchBook(9999, t);
        cout << "T1 unsuccessful search on populated catalogue\n";
        cout << "   expected: found=false, size unchanged (2)\n";
        cout << "   observed: found=" << (found ? "true" : "false")
             << ", size=" << cat.size() << "  -> "
             << ((!found && cat.size() == 2) ? "PASS" : "FAIL") << "\n\n";
    }

    // T2: operations on an EMPTY data structure
    {
        LinkedCatalog cat;
        string t;
        bool removed = cat.removeBook(1004);
        bool found   = cat.searchBook(1004, t);
        cout << "T2 operations on EMPTY catalogue (linked list)\n";
        cout << "   expected: remove=false, search=false, size=0,\n"
                "             display prints '(catalogue is empty)'\n";
        cout << "   observed: remove=" << (removed ? "true" : "false")
             << ", search=" << (found ? "true" : "false")
             << ", size=" << cat.size() << ", display:";
        cat.displayBooks();
        cout << "   -> " << ((!removed && !found && cat.size() == 0) ? "PASS" : "FAIL") << "\n";
    }
}

int main(int argc, char* argv[])
{
    // Testing mode (Evidence 4)
    if (argc > 1 && string(argv[1]) == "--test")
    {
        runTests();
        return 0;
    }

    // Normal mode: K derived from the registration number (Evidence 2)
    string reg;
    cout << "Enter your registration number (e.g., 2026-CS-104): ";
    cin >> reg;

    if (reg.empty() || !isdigit((unsigned char)reg.back()))
    {
        cerr << "Error: registration number must end with a digit.\n";
        return 1;
    }
    int K = reg.back() - '0';

    cout << "Registration number : " << reg << "\n";
    cout << "K (last digit)      : " << K << "\n";

    BookCatalogADT* catalog = nullptr;
    if (K % 2 == 0)
    {
        cout << "K is EVEN -> implementation: ARRAY (capacity 10)\n\n";
        catalog = new ArrayCatalog();
    }
    else
    {
        cout << "K is ODD  -> implementation: SINGLY LINKED LIST\n\n";
        catalog = new LinkedCatalog();
    }

    runScenario(*catalog, K);
    delete catalog;

    cout << "\n===== PART (e) DEMONSTRATION: same ADT, other implementation =====\n";
    BookCatalogADT* other = (K % 2 == 0)
        ? static_cast<BookCatalogADT*>(new LinkedCatalog())
        : static_cast<BookCatalogADT*>(new ArrayCatalog());
    runScenario(*other, K);
    delete other;

    return 0;
}