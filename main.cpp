#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <iomanip>

using namespace std;

struct Expense {
    string description;
    double amount;
};

void showMenu() {
    cout << "\n===============================" << endl;
    cout << "   PERSONAL EXPENSE TRACKER   " << endl;
    cout << "===============================" << endl;
    cout << "1. Add New Expense" << endl;
    cout << "2. View All Expenses" << endl;
    cout << "3. Show Total Spending" << endl;
    cout << "4. Clear All Data" << endl;
    cout << "5. Exit" << endl;
    cout << "-------------------------------" << endl;
    cout << "Choose an option (1-5): ";
}

int main() {
    vector<Expense> expenses;
    int choice;
    string desc;
    double amt;

    // قراءة البيانات مع معالجة ثغرة المسافات
    ifstream readFile("expenses.txt");
    if (readFile.is_open()) {
        while (readFile >> ws && getline(readFile, desc, ',') && readFile >> amt) {
            expenses.push_back({desc, amt});
        }
        readFile.close();
    }

    while (true) {
        showMenu();
        if (!(cin >> choice)) { // حماية البرنامج من إدخال حروف بدلاً من أرقام
            cin.clear();
            cin.ignore(1000, '\n');
            continue;
        }

        if (choice == 1) {
            cout << "Enter expense description (can include spaces): ";
            cin >> ws; // تنظيف الـ Buffer لقراءة النص بشكل صحيح
            getline(cin, desc); // تعديل الثغرة: قراءة السطر كاملاً حتى مع المسافات
            
            cout << "Enter amount: ";
            cin >> amt;
            
            expenses.push_back({desc, amt});
            
            // الحفظ باستخدام الفاصلة (,) للفصل بين الوصف والرقم لضمان القراءة الصحيحة لاحقاً
            ofstream writeFile("expenses.txt", ios::app);
            writeFile << desc << "," << amt << endl;
            writeFile.close();
            cout << "Success: Added!" << endl;
            
        } else if (choice == 2) {
            if (expenses.empty()) cout << "No records found." << endl;
            else {
                cout << "\n--- Expense List ---" << endl;
                cout << left << setw(20) << "Item" << "Price" << endl;
                cout << "-------------------------------" << endl;
                for (const auto& e : expenses) {
                    cout << left << setw(20) << e.description << e.amount << "$" << endl;
                }
            }
        } else if (choice == 3) {
            double total = 0;
            for (const auto& e : expenses) total += e.amount;
            cout << "\nTotal Spending: " << total << "$" << endl;
        } else if (choice == 4) {
            expenses.clear();
            ofstream clearFile("expenses.txt", ios::trunc);
            clearFile.close();
            cout << "Data cleared." << endl;
        } else if (choice == 5) {
            break;
        }
    }
    return 0;
}
