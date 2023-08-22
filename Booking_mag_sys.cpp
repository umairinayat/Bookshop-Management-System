#include <iostream>
#include <fstream>
#include <string>
using namespace std;
//-------------------------------Gobal variables----------------------------------------------------//
string book_ID[20], book_name[20], book_author[20];
int book_pr[20];
int total = 0;
//------------------------------Function for Show Books data----------------------------------------//
void showdata()
{
    ifstream rfile("books.txt");
    int i = 0;
    total = 0;
    if (rfile.is_open())
    {
        while (rfile >> book_name[i] >> book_author[i] >> book_ID[i] >> book_pr[i])
        {
            i++;
            total++;
        }
    }
    for (int i = 0; i < total; i++)
    {
        cout << "\t\tThe detail of book\t" << i + 1 << "\n\n";
        cout << "\tBook ID:\t";
        cout << book_ID[i] << endl;
        cout << "\tbook Author:\t";
        cout << book_author[i] << endl;
        cout << "\tBook price:\t";
        cout << book_pr[i] << endl;
        cout << "\tBook Name:\t";
        cout << book_name[i] << endl;
        cout << "\n\n";
    }
}
//----------------------------------------------Function for Add books-----------------------------------//
void addbook()
{
    int ch = 0;
    // Open file in append mode we want to write the data from last line in file
    fstream upfile("books.txt", ios::out | ios::app);
    cout << "Enter number of books you want to add: ";
    cin >> ch;
    // If Books are already stored
    if (total != 0)
    {
        total = total + ch;
        for (int i = total - ch; i < total; i++)
        {
            cout << "\t\tEnter the detail of book\n\n";
            cout << "\tBook Name: ";
            cin >> book_name[i];
            cout << "\tBook ID: ";
            cin >> book_ID[i];
            cout << "\tEnter book author: ";
            cin >> book_author[i];
            cout << "\tEnter book price: ";
            cin >> book_pr[i];
            upfile << book_name[i] << "\t" << book_author[i] << "\t" << book_ID[i] << "\t" << book_pr[i] << "\n";
        }
    }
    // If books are not stored in file
    else
    {
        for (int i = 0; i < ch; i++)
        {
            cout << "\t\tEnter the detail of book\n\n";
            cout << "\tBook Name: ";
            cin >> book_name[i];
            cout << "\tBook ID: ";
            cin >> book_ID[i];
            cout << "\tEnter book author: ";
            cin >> book_author[i];
            cout << "\tEnter book price: ";
            cin >> book_pr[i];
            upfile << book_name[i] << "\t" << book_author[i] << "\t" << book_ID[i] << "\t" << book_pr[i] << "\n";
        }
        total = total + ch;
    }
    upfile.close();
}
//-----------------------------------------------Function for Serach Data------------------------------//
void searchdata()
{
    string bookno;
    cout << "Enter book ID to search data:";
    cin >> bookno;
    for (int i = 0; i < total; i++)
    {
        if (bookno == book_ID[i])
        {
            cout << "\t\t\tThe book number is \n\n"
                 << i + 1 << endl;
            cout << "\tBook ID: " << book_ID[i] << endl;
            cout << "\tbook Author: " << book_author[i] << endl;
            cout << "\tBook number: " << book_pr[i] << endl;
            cout << "\tBook Name: " << book_name[i] << endl;
        }
    }
}
//------------------------------------------Function for updating data-------------------------------------//
void update()
{
    string bookno;
    cout << "Enter book ID:";
    cin >> bookno;
    string line;
    bool flag = false;
    for (int i = 0; i < total; i++)
    {
        if (bookno == book_ID[i])
        {
            cout << "\t\tThe pervioues data of book " << i + 1 << " is"
                 << "\n\n";
            cout << "\tBook Name:\t";
            cout << book_name[i] << endl;
            cout << "\tBook Author:\t ";
            cout << book_author[i] << endl;
            cout << "\tBook ID:\t";
            cout << book_ID[i] << endl;
            cout << "\tBook Price:\t";
            cout << book_pr[i] << endl;
            cout << endl;
            cout << "\t\tEnter the detail of book\n\n";
            cout << "\tBook Name: ";
            cin >> book_name[i];
            cout << "\tBook ID: ";
            cin >> book_ID[i];
            cout << "\tEnter book author: ";
            cin >> book_author[i];
            cout << "\tEnter book price: ";
            cin >> book_pr[i];
            cout << endl;
            flag = true;
        }
    }
    if (flag == false)
    {
        cout << "Book not found" << endl;
        return;
    }
    else
    {
        ofstream dfile("books.txt");
        for (int i = 0; i < total; i++)
        {
            dfile << book_name[i] << "\t" << book_author[i] << "\t" << book_ID[i] << "\t" << book_pr[i] << "\n";
        }
        dfile.close();

        cout << "\t\tBook updated successfully" << endl;
    }
}
//-------------------------------------------Function for deleteing data----------------------------------//

void deletedata()
{
    // To confirm deletion from user
    int s;
    cout << "\tEnter 1 to delete data: ";
    cin >> s;
    if (s != 1)
    {
        cout << "\tDeletion cancelled" << endl;
        return;
    }

    string bookno;
    cout << "Enter book number to delete that book: ";
    cin >> bookno;

    bool found = false;
    int i;
    for (i = 0; i < total; i++)
    {
        if (bookno == book_ID[i])
        {
            // Shift books up by one index to remove deleted book and store data of next index in perviews
            for (int j = i; j < total - 1; j++)
            {
                book_ID[j] = book_ID[j + 1];
                book_name[j] = book_name[j + 1];
                book_author[j] = book_author[j + 1];
                book_pr[j] = book_pr[j + 1];
            }
            total--;
            found = true;
            break;
        }
    }
    if (found == false)
    {
        cout << "Book not found" << endl;
    }
    else
    {
        ofstream lfile("books.txt");
        if (!lfile.is_open())
        {
            cout << "\tError: could not open file" << endl;
        }
        else
        {
            for (i = 0; i < total; i++)
            {
                if (i == total - 1)
                {
                    lfile << book_name[i] << "\t" << book_author[i] << "\t" << book_ID[i] << "\t" << book_pr[i];
                }
                else
                {
                    lfile << book_name[i] << "\t" << book_author[i] << "\t" << book_ID[i] << "\t" << book_pr[i] << endl;
                }
            }
            cout << "Book deleted successfully" << endl;
            lfile.close();
        }
    }
}
//--------------------------------------------Main function-----------------------------------------------//
int main()
{
    int value;
    while (true)
    {
        cout << "\n~~~~~~~~~~~~~~~~~~~~~~~~~~"
             << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~"
             << "~WELCOME~~~~~~~~~~~~~~~~"
             << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~"
             << "~~~~~~~~~\n\n";
        cout << "Enter your choice\n";
        cout << "\t1. Show data\n";
        cout << "\t2. Enter book-name, book-ID, book-authr, book-no \n";
        cout << "\t3. Serachdata \n";
        cout << "\t4. Update \n";
        cout << "\t5. Delete \n";
        cin >> value;
        switch (value)
        {
        case 1:
            showdata();
            break;
        case 2:
            addbook();
            break;
        case 3:
            searchdata();
            break;
        case 4:
            update();
            break;
        case 5:
            deletedata();
            break;
        default:
            cout << "Invalid input" << endl;
            break;
        }
    }
    return 0;
}
