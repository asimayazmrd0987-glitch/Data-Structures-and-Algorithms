#include <iostream>
#include <string>
using namespace std;

class BookCatalogADT
{
public:
    virtual ~BookCatalogADT() {}
    virtual bool addBook(int id, const string& title) = 0;
    virtual bool removeBook(int id) = 0;
    virtual bool searchBook(int id, string& outTitle) const = 0;
    virtual void displayBooks() const = 0;
    virtual int  size() const = 0;
};

class ArrayCatalog : public BookCatalogADT
{
    static const int CAPACITY = 10;
    int    ids[CAPACITY];
    string titles[CAPACITY];
    int    count;

    int find(int id) const
    {
        for (int i = 0; i < count; ++i)
            if (ids[i] == id) return i;
        return -1;
    }

public:
    ArrayCatalog() : count(0) {}

    bool addBook(int id, const string& title) override
    {
        if (count == CAPACITY || find(id) != -1) return false;
        ids[count] = id;
        titles[count] = title;
        ++count;
        return true;
    }

    bool removeBook(int id) override
    {
        int i = find(id);
        if (i == -1) return false;
        for (int j = i; j < count - 1; ++j)      // shift left to close gap
        {
            ids[j] = ids[j + 1];
            titles[j] = titles[j + 1];
        }
        --count;
        return true;
    }

    bool searchBook(int id, string& outTitle) const override
    {
        int i = find(id);
        if (i == -1) return false;
        outTitle = titles[i];
        return true;
    }

    void displayBooks() const override
    {
        if (count == 0) { cout << "     (catalogue is empty)\n"; return; }
        for (int i = 0; i < count; ++i)
            cout << "     " << ids[i] << "  " << titles[i] << "\n";
    }

    int size() const override { return count; }
};

class LinkedCatalog : public BookCatalogADT
{
    struct Node
    {
        int    id;
        string title;
        Node*  next;
        Node(int i, const string& t) : id(i), title(t), next(nullptr) {}
    };
    Node* head;
    int   count;

public:
    LinkedCatalog() : head(nullptr), count(0) {}

    ~LinkedCatalog() override
    {
        while (head) { Node* n = head->next; delete head; head = n; }
    }

    bool addBook(int id, const string& title) override
    {
        for (Node* c = head; c; c = c->next)
            if (c->id == id) return false;             // duplicate ID
        Node* n = new Node(id, title);
        if (!head) head = n;
        else { Node* c = head; while (c->next) c = c->next; c->next = n; }
        ++count;
        return true;
    }

    bool removeBook(int id) override
    {
        Node* cur = head;
        Node* prev = nullptr;
        while (cur && cur->id != id) { prev = cur; cur = cur->next; }
        if (!cur) return false;
        if (prev) prev->next = cur->next; else head = cur->next;
        delete cur;
        --count;
        return true;
    }

    bool searchBook(int id, string& outTitle) const override
    {
        for (Node* c = head; c; c = c->next)
            if (c->id == id) { outTitle = c->title; return true; }
        return false;
    }

    void displayBooks() const override
    {
        if (!head) { cout << "     (catalogue is empty)\n"; return; }
        for (Node* c = head; c; c = c->next)
            cout << "     " << c->id << "  " << c->title << "\n";
    }

    int size() const override { return count; }
};

const char* ok(bool b) { return b ? "success" : "failed"; }

void runScenario(BookCatalogADT& cat, int K)
{
    int B1 = 1000 + K, B2 = 2000 + K, B3 = 3000 + K, B4 = 4000 + K;
    cout << "Book IDs : B1=" << B1 << ", B2=" << B2
         << ", B3=" << B3 << ", B4=" << B4 << "\n\n";

    cout << "1. addBook(B1, \"Computer Systems\")        -> "
         << ok(cat.addBook(B1, "Computer Systems")) << "\n";
    cout << "2. addBook(B2, \"Data Structures\")         -> "
         << ok(cat.addBook(B2, "Data Structures")) << "\n";
    cout << "3. addBook(B3, \"Algorithms\")              -> "
         << ok(cat.addBook(B3, "Algorithms")) << "\n";

    string title;
    cout << "4. searchBook(B2)                         -> ";
    if (cat.searchBook(B2, title)) cout << "found, title = \"" << title << "\"\n";
    else                           cout << "not found\n";

    cout << "5. addBook(B4, \"Artificial Intelligence\") -> "
         << ok(cat.addBook(B4, "Artificial Intelligence")) << "\n";
    cout << "6. removeBook(B1)                         -> "
         << ok(cat.removeBook(B1)) << "\n";

    cout << "7. displayBooks():\n";
    cat.displayBooks();

    cout << "8. size()                               -> " << cat.size() << "\n";
}


int main()
{
    int K;
    cout << "Enter K (digit from your registration number): ";
    cin >> K;

    BookCatalogADT* catalog = nullptr;
    if (K % 2 == 0)
    {
        cout << "\nK = " << K << " is EVEN -> implementation: ARRAY (capacity 10)\n\n";
        catalog = new ArrayCatalog();
    }
    else
    {
        cout << "\nK = " << K << " is ODD  -> implementation: SINGLY LINKED LIST\n\n";
        catalog = new LinkedCatalog();
    }

    runScenario(*catalog, K);          // PART (c): the eight operations
    delete catalog;

    cout << "\n===== PART (e) DEMONSTRATION: same ADT, other implementation =====\n";
    BookCatalogADT* other = (K % 2 == 0)
                            ? static_cast<BookCatalogADT*>(new LinkedCatalog())
                            : static_cast<BookCatalogADT*>(new ArrayCatalog());
    runScenario(*other, K);
    delete other;

    return 0;
}