#include <iostream>
#include <windows.h>
#include <cstdlib> // For system("cls")
#include <cstdio>
#include <fstream>
#define MAX_ITEMS 100
using namespace std;

void gotoRowCol(int x, int y)
{
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}
void sleep(int m)

{

    for (int j = 0; j < m * 21000; j++)

    {
    }
}

void drawLoginBox()
{
    cout << "+-------------------------------------+" << endl;
    cout << "|    Welcome to our Inventory System  |" << endl;
    cout << "|      --------------------------     |" << endl;
    cout << "|      |        Login Box       |     |" << endl;
    cout << "|      +------------------------+     |" << endl;
    cout << "|      | User-name:             |     |" << endl;
    cout << "|      |        [           ]   |     |" << endl;
    cout << "|      |                        |     |" << endl;
    cout << "|      | Password:              |     |" << endl;
    cout << "|      |        [           ]   |     |" << endl;
    cout << "|      |                        |     |" << endl;
    cout << "|      +------------------------+     |" << endl;
    cout << "|      |          Login         |     |" << endl;
    cout << "|      +------------------------+     |" << endl;
    cout << "+-------------------------------------+" << endl;
}

void registerBox()
{
    // system("cls"); // Clear the console
    cout << "+----------------------------------+" << endl;
    cout << "|       Registering new employee   |" << endl;
    cout << "|       ------------------------   |" << endl;
    cout << "|      +------------------------+  |" << endl;
    cout << "|      | User-name:             |  |" << endl;
    cout << "|      |       [           ]    |  |" << endl;
    cout << "|      | Password:              |  |" << endl;
    cout << "|      |       [           ]    |  |" << endl;
    cout << "|      +------------------------+  |" << endl;
    cout << "|      |        (Register)      |  |" << endl;
    cout << "|      +------------------------+  |" << endl;
    cout << "+----------------------------------+" << endl;
}

void clearFile(const string &filename)
{

    ofstream fileStream("txtfile.txt", ios::trunc);

    if (fileStream.is_open())
    {

        fileStream.close();
    }
    else
    {
        cout << "Failed to open the file '" << filename << "' for clearing." << endl;
    }
}
class Item
{
public:
    int item_no;
    string name;
    int quantity;
    double sale_price;
    double purchase_price;

    Item()
    {
        item_no = 0;
        quantity = 0;
        sale_price = 0.0;
        purchase_price = 0.0;
    }
    Item(int Item_no, string Name, int Quantity, double S_Price, double P_Price)
    {
        item_no = Item_no;
        name = Name;
        quantity = Quantity;
        sale_price = S_Price;
        purchase_price = P_Price;
    }
};
class Inventory
{
public:
    int bill = 0;
    double profit;
    int no_of_items = 0;
    int itemCount = 0;
    int index = 0;
    string s_products[MAX_ITEMS];
    int s_p_q[MAX_ITEMS];
    Item array_of_items[MAX_ITEMS];
    Item *ptr_a_of_items[MAX_ITEMS];

    Inventory()
    {

        for (int i = 0; i < MAX_ITEMS; i++)
        {
            ptr_a_of_items[i] = &array_of_items[i];
        }
    }

    void addItem(int item_n, string name, int quantity, double S_price, double P_price)
    {
        if (item_n<itemCount)
        {
            cout<<"item at this position already exit"<<endl;
            sleep(16565);
        }
        else if (itemCount < MAX_ITEMS && item_n>itemCount)
        {
            loadFromFile();
            cout << itemCount;
            array_of_items[itemCount] = Item(item_n, name, quantity, S_price, P_price);
            itemCount++;
            clearFile("txtfile.txt");
            save_inventory();
        }
        else

        {
            cout << "Inventory is full. Cannot add more items." << endl;
        }
    }

    void removeItem(int item_no)
    {
        int index = -1;

        for (int i = 0; i < itemCount; i++)
        {
            if (array_of_items[i].item_no == item_no)
            {
                index = i;
                break;
            }
        }

        if (index != -1)
        {
            for (int i = index; i < itemCount - 1; i++)
            {
                array_of_items[i] = array_of_items[i + 1];
            }
            itemCount--;

            // Update item numbers after removal
            for (int i = 0; i < itemCount; i++)
            {
                array_of_items[i].item_no = i + 1;
            }
            clearFile("txtfile.txt");

            // Save the updated inventory to the file
            save_inventory();
        }
        else
        {
            cout << "Item not found in inventory." << endl;
        }
    }

    void updateQuantity(int item_no, int newQuantity)
    {
        for (int i = 0; i < itemCount; i++)
        {
            if (array_of_items[i].item_no == item_no)
            {
                array_of_items[i].quantity = newQuantity;
                return;
            }
        }
        cout << "Item not found in inventory." << endl;
    }
    void displayInventory()
    {
        system("cls");
        loadFromFile();
        gotoRowCol(0, 0);
        cout << "--------------------------------------------------------------------" << endl;
        cout << "| Item No. | Item Name   | Quantity | Sale Price  |  Purchase Price |" << endl;
        cout << "---------------------------------------------------------------------" << endl;
        int row = 3;
        for (int i = 0; i < itemCount; i++)
        {
            gotoRowCol(0, row);
            cout << "| " << array_of_items[i].item_no;
            gotoRowCol(11, row);
            cout << "| " << array_of_items[i].name;
            gotoRowCol(24, row);
            cout << "| " << array_of_items[i].quantity;
            gotoRowCol(35, row);
            cout << "| " << array_of_items[i].sale_price;
            gotoRowCol(50, row);
            cout << "|  " << array_of_items[i].purchase_price;
            gotoRowCol(68, row);
            cout << "|" << endl;
            row++;
        }
        gotoRowCol(0, row);
        cout << "--------------------------------------------------------------------" << endl;
    }
    void loadFromFile()
    {
        ifstream inventory_file("txtfile.txt");
        if (inventory_file.is_open())
        {
            int i = 0;
            while (!inventory_file.eof())
            {
                int it_n;
                string name;
                int quantity;
                double S_price, P_price;

                inventory_file >> it_n >> name >> quantity >> S_price >> P_price;

                ptr_a_of_items[i]->item_no = it_n;
                ptr_a_of_items[i]->name = name;
                ptr_a_of_items[i]->quantity = quantity;
                ptr_a_of_items[i]->sale_price = S_price;
                ptr_a_of_items[i]->purchase_price = P_price;

                i++;
            }

            itemCount = i;
            inventory_file.close();
        }
        else
        {
            cout << "Unable to open the file for reading." << endl;
        }
    }
    void save_inventory()
    {

        ofstream savefile("txtfile.txt", ios::app);
        string n;
        int q;
        double p_p;
        double s_p;

        for (int i = 0; i < itemCount; i++)
        {
            n = array_of_items[i].name;
            q = array_of_items[i].quantity;
            p_p = array_of_items[i].purchase_price;
            s_p = array_of_items[i].sale_price;
            savefile << endl
                     << i << " " << n << " " << q << " " << s_p << " " << p_p;
        }
    }

    void generate_report(int it_count, int quantity)
    {
        bool productFound = false;

        for (int i = 0; i < index; i++)
        {
            if (s_products[i] == array_of_items[it_count].name)
            {
                s_p_q[i] += quantity;
                productFound = true;
                break;
            }
        }

        if (!productFound)
        {
            s_products[index] = array_of_items[it_count].name;
            s_p_q[index] = quantity;
            index++;
        }
    }
    void print_bill()
    {
        system("cls");

        gotoRowCol(0, 0);
        cout << "-------------------------------------------" << endl;
        cout << "|               Invoice # " << bill << "              |" << endl;
        cout << "-------------------------------------------" << endl;
        cout << "| Product Name      | Quantity | Total   |" << endl;
        cout << "-------------------------------------------" << endl;
        bill++;
        int row = 4;
        double grandTotal = 0.0;

        for (int i = 0; i < index; i++)
        {
            gotoRowCol(0, row);
            cout << "| " << s_products[i];
            gotoRowCol(20, row);
            cout << "| " << s_p_q[i];
            double total = s_p_q[i] * array_of_items[i].sale_price;
            gotoRowCol(33, row);
            cout << "| " << total;
            grandTotal += total;
            row++;
        }

        gotoRowCol(0, row + 0);
        cout << "-------------------------------------------" << endl;
        gotoRowCol(22, row + 1);
        cout << "Grand Total: " << grandTotal << endl;

        gotoRowCol(0, row + 2);
        cout << "+-----------------------------------------+" << endl;
        gotoRowCol(2, row + 3);
        cout << "| All rights reserved by DevTriDynasty |" << endl;
        gotoRowCol(0, row + 4);
        cout << "+-----------------------------------------+" << endl;
        sleep(16565);
    }
    void report()
    {
        system("cls");
        gotoRowCol(1, 0);
        cout << "-------------------Today Report-----------------" << endl;

        cout << "-------------------------------------------------" << endl;
        cout << "| Product Name            | Product Quantity    |" << endl;
        cout << "-------------------------------------------------" << endl;

        int row = 4;
        for (int i = 0; i < index; i++)
        {
            gotoRowCol(0, row);
            cout << "| " << s_products[i];
            gotoRowCol(26, row);
            cout << "| " << s_p_q[i];
            row++;
        }
        gotoRowCol(0, row);
        cout << endl;
        cout << "Today Profit:" << profit << endl;
        cout << "-------------------------------------------------" << endl;
        sleep(2222);
    }
    void calculate_profit(int it_count, int quantity)
    {
        int increment = 0;
        increment = increment + (array_of_items[it_count].sale_price - array_of_items[it_count].purchase_price);
        increment = increment * quantity;
        profit = profit + increment;
    }
    void sale_product(int it_count, int qtity)
    {
        loadFromFile();
        if (qtity <= array_of_items[it_count].quantity)
        {
            clearFile("txtfile.txt");
            array_of_items[it_count].quantity = array_of_items[it_count].quantity - qtity;
            calculate_profit(it_count, qtity);
            generate_report(it_count, qtity);
            save_inventory();
        }
        else
        {
            cout << "We are running out of stock!!!!" << endl;
            sleep(39999);
        }
    }
};

void Emp_registration()
{
    string nam, passw;
    gotoRowCol(16, 5);
    cin >> nam;
    gotoRowCol(16, 7);
    cin >> passw;
    ofstream writing("Employee.txt", ios::app);
    writing << nam << " " << passw << endl;
    writing.close();
}

class Admin : public Inventory
{
public:
    void admin_id(string un, string pass)
    {
    string nam, passw;
    bool loginSuccess = false;

    do
    {
        ifstream reader("Admins.txt");
        while (reader >> nam >> passw)
        {
            if (nam == un && passw == pass)
            {
                gotoRowCol(0,15);
                cout << "Login successfully!!" << endl;
                sleep(49999);

                int chk;
                do
                {
                    system("cls");
                    cout << "1. Register new Employee" << endl;
                    cout << "2. Sell item" << endl;
                    cout << "3. Check Report" << endl;
                    cout << "4. Add items" << endl;
                    cout << "5. Remove items" << endl;
                    cout << "6. Exit" << endl;
                    cout << "Enter: ";
                    cin >> chk;

                    if (chk == 1)
                    {
                        system("cls");
                        registerBox();
                        Emp_registration();
                        gotoRowCol(1,14);
                        cout << "Employee registered successfully!!" << endl;
                        sleep(3999);
                    }
                    else if (chk == 2)
                    {
                        int I_NO, QUAN;
                        loadFromFile();
                        displayInventory();
                        cout << "Enter the item number you want to purchase: ";
                        cin >> I_NO;
                        cout << "Enter the item quantity you want to purchase: ";
                        cin >> QUAN;
                        sale_product(I_NO, QUAN);
                        cout << "Item sold successfully!!" << endl;
                        sleep(15999);
                        print_bill();
                        sleep(67999);
                    }
                    else if (chk == 3)
                    {
                        report();
                        sleep(59999);
                    }
                    else if (chk == 4)
                    {
                        int it_no,quant;
                        string name;
                        double sale_p, purchase_p;
                        loadFromFile();
                        displayInventory();
                        cout << "Enter item number: ";
                        cin >> it_no;
                        cout << "Enter item name: ";
                        cin.ignore(); // Ignore newline character from previous input
                        getline(cin, name);
                        cout << "Enter item quantity: ";
                        cin >> quant;
                        cout << "Enter purchase price: ";
                        cin >> purchase_p;
                        cout << "Enter sale price: ";
                        cin >> sale_p;
                        addItem(it_no+1, name, quant, sale_p, purchase_p);
                        cout << "Item added successfully" << endl;
                        loadFromFile();
                        displayInventory();
                        sleep(59999);
                    }
                    else if (chk == 5)
                    {
                        displayInventory();
                        int remove_item_no;
                        cout << "Enter item number to remove: ";
                        cin >> remove_item_no;
                        removeItem(remove_item_no);
                        loadFromFile();
                        displayInventory();
                        sleep(59999);
                    }
                    else if (chk == 6)
                    {
                        cout << "Exiting..." << endl;
                    }
                    else
                    {
                        cout << "Invalid choice! Please enter a valid option." << endl;
                    }
                } while (chk != 6);
                loginSuccess = true;
                reader.close();
                break;
            }
        }

        // Invalid login
        if (!loginSuccess)
        {
            system("cls");
            drawLoginBox();
            gotoRowCol(0, 15);
            cout << "Invalid user-name or password" << endl;
            gotoRowCol(17, 6);
            cin >> un;
            gotoRowCol(17, 9);
            cin >> pass;
        }

        reader.close();
    } while (!loginSuccess);
}

};

class Employee : public Inventory
{
public:

    void employee_id(string un, string pass)
{
    string nam, passw;
    bool loginSuccess = false;

    do
    {
        ifstream reader("Employee.txt");

        while (reader >> nam >> passw)
        {
            if (nam == un && passw == pass)
            {
                gotoRowCol(10, 15);
                cout << "Login successfully" << endl;
                reader.close();

                do
                {
                    system("cls");
                    cout << "1. Sell item" << endl;
                    cout << "2. Exit" << endl;
                    cout << "Enter your selection: ";
                    int chk;
                    cin >> chk;

                    switch (chk)
                    {
                        case 1:
                        {
                            int I_NO, QUAN;
                            displayInventory();
                            cout << "Enter your item number which you want to purchase: ";
                            cin >> I_NO;
                            cout << "Enter the item quantity which you want to purchase: ";
                            cin >> QUAN;
                            sale_product(I_NO, QUAN);
                            cout << "Item sold successfully!!" << endl;
                            getchar();
                            print_bill();
                            getchar();
                            break;
                        }
                        case 2:
                            cout << "Exiting..." << endl;
                            return;
                        default:
                            cout << "Invalid choice! Please enter a valid option." << endl;
                            break;
                    }

                } while (true);
                loginSuccess = true;
                reader.close();
                break;
            }
        }
        if (!loginSuccess)
        {
            system("cls");
            drawLoginBox();
            gotoRowCol(0, 16);
            cout << "Invalid user-name or password" << endl;
            gotoRowCol(17, 6);
            cin >> un;
            gotoRowCol(17, 9);
            cin >> pass;
        }

        reader.close();
    } while (!loginSuccess);
}


};

int main()
{
    Admin admin;
    Employee employee;
    string name, password;
    int check;

    do
    {
        gotoRowCol(40, 0);
        cout << "+--------------------------+" << endl;
        gotoRowCol(40, 1);
        cout << "|       1.Admin            |" << endl;
        gotoRowCol(40, 2);
        cout << "|       2.Employee         |" << endl;
        gotoRowCol(40, 3);
        cout << "|       Select:            |" << endl;
        gotoRowCol(40, 4);
        cout << "+--------------------------+" << endl;
        gotoRowCol(55, 3);
        cin >> check;

        if (check == 1)
        {
            system("cls");
            drawLoginBox();
            gotoRowCol(17, 6);
            cin >> name;
            gotoRowCol(17, 9);
            cin >> password;
            admin.admin_id(name, password);

        }
        else if (check == 2)
        {
            system("cls");
            drawLoginBox();
            gotoRowCol(17, 6);
            cin >> name;
            gotoRowCol(17, 9);
            cin >> password;
            employee.employee_id(name, password);
        }
        else
        {
            gotoRowCol(38,5);
            cout << "Wrong input! Please enter 1 or 2." << endl;
        }

    } while (check != 1 && check != 2);

    return 0;
}
