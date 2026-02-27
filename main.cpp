#include<iostream>
#include<string>
#include<vector>
#include<fstream>
#include<limits>
#include<iomanip>

using namespace std;

//----------  CLIENT MANAGEMENT SYSTEM PROJECT -----------
//-------- Final Updated Version From Me (Hesham) --------

const string clientsFile = "clientFile.txt"; 
void  showMainMenu();
void showTransactionMenuScreen();

struct stClient
{
    string accountNumber;
    string pinCode;
    string clientName;
    string phone;
    double balance;
    bool mark4Delete = false;
};

//------------------ Back (Excuation Functions) -------------------

vector<string> splitString(string str, string delim = "#//#")
{
    vector<string> vStr;
    string sword = "";
    short pos = 0;

    while((pos = str.find(delim)) != string::npos)
    {
        sword = str.substr(0, pos);
        if(sword != "")
        {
            vStr.push_back(sword);
        }
        str.erase(0, pos + delim.length());
    }

    if(str != "") vStr.push_back(str);

    return vStr;
 }

 string convertRecord2Line(stClient client, string delim = "#//#")
 {
    string sword = "";

    sword += client.accountNumber + delim;
    sword += client.pinCode + delim;
    sword += client.clientName + delim;
    sword += client.phone + delim;
    sword += to_string(client.balance);

    return sword ;
 }
 stClient convertLine2Record(string line)
 {
    vector<string> vStr = splitString(line);
    stClient client;

    client.accountNumber = vStr[0];
    client.pinCode = vStr[1]; 
    client.clientName = vStr[2]; 
    client.phone = vStr[3];
    client.balance = stod(vStr[4]);

    return client;

 }

 vector<stClient> loadDataFromFile(string fileName)
 {
    fstream myFile; 
    myFile.open(fileName, ios::in); // Read Only

    vector<stClient> vClient;
    if(myFile.is_open())
    {
        string line = "";
        stClient client;
        while(getline(myFile, line))
        {
            client = convertLine2Record(line);
            vClient.push_back(client);
        }
        myFile.close();
    }

    return vClient; 
 }

 void saveLine_N_File(string fileName, string line)
 {
    fstream myFile;
    myFile.open(fileName, ios::out | ios::app);

    if(myFile.is_open())
    {
        myFile << line << endl;
        myFile.close(); 
    }
 }

 void printClientData(stClient client)
 {
    cout << " | " << setw(15) << left << client.accountNumber;
    cout << " | " << setw(15) << left << client.pinCode;
    cout << " | " << setw(30) << left << client.clientName;
    cout << " | " << setw(15) << left << client.phone;
    cout << " | " << setw(15) << left << client.balance;
 }

void printClientCard(stClient client)
{
    cout << "\n##Client Data As Following##\n";
    cout << "Client Number: " << client.accountNumber << endl;
    cout << "Client Pin Code: " << client.pinCode << endl;
    cout << "Client Name: " << client.clientName << endl;
    cout << "Client Phone: " << client.phone << endl;
    cout << "Client Balance: " << client.balance << endl;
}

 bool isClientExistByClientNumber(string accountNum, string clientsFile)
 {
    fstream myFile;
    myFile.open(clientsFile, ios::in); // read only
 

    if(myFile.is_open())
    {
        string line;
        stClient client;
        while(getline(myFile, line))
        {
            client = convertLine2Record(line);
            if(client.accountNumber == accountNum)
            {
                myFile.close();
                return true;
            }
        }
    }

    return false; 
 }
  
 stClient getClientData()
 {
    stClient client; 

    cout << "Enter Account Number: ";
    getline(cin >> ws, client.accountNumber);

    while(isClientExistByClientNumber(client.accountNumber, clientsFile))
    {
        cout << "This Account Number [ " << client.accountNumber  << " ] Already Exist!, Enter a New One: ";
        getline(cin >> ws, client.accountNumber);
    }

    cout << "Enter Client Pin Code: ";
    getline(cin, client.pinCode); 
    cout << "Enter Client Name: ";
    getline(cin, client.clientName);
    cout << "Enter Client PHone: ";
    getline(cin, client.phone);
    cout << "Enter Balance: ";
    cin >> client.balance; 

    return client;
 }

 void add_1_Client()
 {
    stClient client = getClientData();
    string line = convertRecord2Line(client);
    saveLine_N_File(clientsFile, line);
 }

 void AddAllClients()
 {
    char ans = 'y';
    do
    {
        system("clear");
        cout << "---------------------------------------\n";
        cout << "\tAdding New Client Screen\n";
        cout << "---------------------------------------\n\n";
        cout << "Enter Client Data To Add\n";
        add_1_Client();
        cout << "Client Added Successfully, Do you Want to Add More Clients ? [Y/N]: ";
        cin >> ans;
    } while (tolower(ans) == 'y');
    
 }
 string getAccountNumber()
 {
    string str;
    cout << "Enter Account Number: ";
    cin >> str;
    return str;
 }
 
bool findClientByAccountNumber(string accountNum, vector<stClient> vClient, stClient & client)
{
    for(stClient & c : vClient)
    {
        if(c.accountNumber == accountNum)
        {
            client = c;
            return true;
        }
    }
    return false;
}

bool mark4Delete(string accountNum, vector<stClient> & vClient)
{
    for(stClient & c : vClient)
    {
        if(c.accountNumber == accountNum)
        {
            c.mark4Delete = true;
            return true;
        }
    }
    return false;
}

stClient changeClientRecord(string accountNum)
{
    stClient client; 
    client.accountNumber = accountNum;

    cout << "Enter Client Pin Code: ";
    getline(cin >> ws, client.pinCode);
    cout << "Enter Client Name: ";
    getline(cin, client.clientName);
    cout << "Enter Client Phone: ";
    getline(cin, client.phone);
    cout << "Enter Client Balance: ";
    cin >> client.balance;

    return client;
}

vector<stClient> saveClient_N_File(string fileName, vector<stClient> vClient)
{
    fstream myFile;
    myFile.open(fileName, ios::out);

    if(myFile.is_open())
    {        
        for(stClient & c : vClient)
        {
            if(c.mark4Delete == false)
            {
                myFile << convertRecord2Line(c) << endl;
            }
        }
        myFile.close();
    }

    return vClient;
}

void deleteClientByAccountNumber(string accountNum, vector<stClient> vClient)
{
    char ans = 'y';
    stClient client;

    if(findClientByAccountNumber(accountNum, vClient, client))
    {
        printClientCard(client);
        cout << "\nDo You Want to Delete this Client? [Y/N]: ";
        cin >> ans;
        if(tolower(ans) == 'y')
        {
            mark4Delete(accountNum, vClient);
            saveClient_N_File(clientsFile, vClient);

            //Refresh Screen -> To see delete Result
            vClient = loadDataFromFile(clientsFile);
            cout << "Client Deleted Successfully.\n";
        }
    }else
    {
        cout <<"This Account Number [ " << accountNum << " ] Not Found!.\n";
    }
}

void updateClientDataByAccountNumber(string accountNum, vector<stClient> &vClient)
{
    char ans = 'n';
    stClient client;

    if(findClientByAccountNumber(accountNum, vClient, client))
    {
        printClientCard(client);
        cout << "\nDo You Want To update This Client? [Y/N]: "; 
        cin >> ans;
        if(tolower(ans) == 'y')
        {
            for(stClient & c : vClient)
            {
                if(c.accountNumber == accountNum)
                {
                    c = changeClientRecord(accountNum);
                    break;
                }
            }
            saveClient_N_File(clientsFile, vClient);
            cout << "\nClient Updated Successfully\n";
        }

    }else
    {
        cout << "This Account Number [ " << accountNum << " ] Not Found\n";
    }
}
//-------------------------  New Feature for Client Program --------------------------



void printClientBalance(stClient client)
{
    cout << " | " << setw(15) << left  << client.accountNumber;
    cout << " | " << setw(30) << left  << client.clientName;
    cout << " | " << setw(15) << left  << client.balance;
}

void totalBalanceList()
{
    long double totalBalance  = 0;

    vector<stClient> vClient = loadDataFromFile(clientsFile);
    cout << "\n\t\t\t Balances List [ " << vClient.size() << " ] Client(s).\n";
    cout << "\n----------------------------------------------------------------------\n";
    cout << " | " << left << setw(15) << "Account Number ";
    cout << " | " << left << setw(30) << "Client Name ";
    cout << " | " << left << setw(15) << "Client Balance ";
    cout << "\n----------------------------------------------------------------------\n";
    
    if(vClient.size() == 0)
    {
        cout << "No client found in this account Number\n";
    }else
    {
        for(stClient & c : vClient)
        {
            printClientBalance(c);
            cout << endl;
            totalBalance+= c.balance;
        }
    }
    cout << "\n----------------------------------------------------------------------\n";
    cout << "\t\t Total Balance : " << totalBalance << endl;
}

void depositOperation(string accountNum, double amount,  vector<stClient> &vClient)
{
    char ans = 'n';

    cout <<"Are You sure You Want to Deposit This Transaction? [Y/N]: ";
    cin >> ans;

    if(tolower(ans) == 'y')
    {
        for(stClient & c : vClient)
        {
            if(c.accountNumber == accountNum)
            {
                c.balance += amount;
                saveClient_N_File(clientsFile, vClient);
                cout << "\nDone Successfully, New Balance is: " << c.balance << endl;
                return;
            }
        }
    }

}


void showDepositeScreen()
{
    system("clear");
    cout <<"--------------------------------\n";
    cout <<"\t Deposit Screen\n";
    cout <<"--------------------------------\n";

    string accountNum  = getAccountNumber();
    stClient client;
    vector<stClient> vClient = loadDataFromFile(clientsFile);

    while(findClientByAccountNumber(accountNum, vClient, client) == false)
    {
        cout << "Accont Number Not Found, Enter Another One!!!\n";
        accountNum = getAccountNumber();
    }

    printClientCard(client);

    double depositAmount = 0;
    cout << "\nPlease Enter Deposite Amount: ";
    cin >> depositAmount;

    depositOperation(accountNum, depositAmount, vClient);


}

void showWithdrawScreen()
{
    system("clear");
    cout <<"--------------------------------\n";
    cout <<"\t WithDraw Screen\n";
    cout <<"--------------------------------\n";

    string accountNum  = getAccountNumber();
    vector<stClient> vClient = loadDataFromFile(clientsFile);
    stClient client;

    while(findClientByAccountNumber(accountNum, vClient, client) == false)
    {
        cout << "Accont Number[ " << accountNum << " ] Not Found, Enter Another One!!!\n";
        accountNum = getAccountNumber();
    }

    printClientCard(client);

    double amount = 0;
    cout << "\nPlease Enter Withdraw Amount: ";
    cin >> amount;

    // Valida that the Input number doesn't Exceed the Balance
    while(amount > client.balance)
    {
        cout << "\nAmount Exceeds the Balance, You can Withdraw up to: " << client.balance << endl;
        cout << "Please Enter another Amount: ";
        cin >> amount;
    }

    depositOperation(accountNum, amount * -1 , vClient);

}

void showTotalBalanceScreen()
{
    system("clear");
    totalBalanceList();
}

void goToHomeScreen()
{
    showMainMenu();
}


enum enTransactionMenu
{
    eDeposit = 1, eWithdraw  = 2, 
    eTotalBalances = 3, eMainMenu = 4
};

short  readTransactionOption()
{
    short num;
    cout <<"Choose What do you want to do ? [1 to 4]: ";
    cin >> num;
    return num;
}

void goBack2TransactionScreen()
{
    cout << "\nPress Enter to Go to Transaction Menu....";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get(); 
    showTransactionMenuScreen();
}


void performTransactionMenu(enTransactionMenu option)
{
    switch(option)
    {
        case enTransactionMenu::eDeposit :
        {
            showDepositeScreen();
            goBack2TransactionScreen();
            break;
        }

        case enTransactionMenu::eWithdraw :
        {
            showWithdrawScreen();
            goBack2TransactionScreen();
            break;
        }

        case enTransactionMenu::eTotalBalances : 
        {
           totalBalanceList();
           goBack2TransactionScreen();
           break;
        }

        case enTransactionMenu::eMainMenu :
        {
            goToHomeScreen();
            break; 
        }
            
    }
}
 
//-----------------------------------------------------------------------------------

void showAllClientScreen()
 {
    system("clear");
    vector<stClient> vClient = loadDataFromFile(clientsFile);
    cout << "\n\t\t\tClients List " << vClient.size() << " Client(s)\n";
    cout << "\n---------------------------------------------------------------------------------------------------\n";
    cout << " | " << left << setw(15) << "Account Number";
    cout << " | " << left << setw(15) << "Pin Code";
    cout << " | " << left << setw(30) << "Client Name";
    cout << " | " << left << setw(15) << "Client Phone";
    cout << " | " << left << setw(15) << "Client Balance";
    cout << "\n---------------------------------------------------------------------------------------------------\n";
    if(vClient.size() == 0)
    {
        cout << "NO Client Found In This File!\n";

    }else 
    {
        for(stClient & c : vClient)
        {
            printClientData(c);
            cout << endl;
        }
    }

 }

void showAddNewClientScreen()
{
    AddAllClients();
}

void showDeleteClientScreen()
{
    system("clear");
    cout << "---------------------------------------\n";
    cout << "\t Delete Client Screen\n";
    cout << "---------------------------------------\n";
    string accountNumber = getAccountNumber();
    vector<stClient> vClient = loadDataFromFile(clientsFile);

    deleteClientByAccountNumber(accountNumber, vClient);
}

void showUpdateClientInfoScreen()
{
    system("clear");
    cout << "---------------------------------------------\n";
    cout << "\t Update Client Info Screen.\n";
    cout << "---------------------------------------------\n";

    string accountNum = getAccountNumber();
    vector<stClient> vClient = loadDataFromFile(clientsFile);
    updateClientDataByAccountNumber(accountNum, vClient);
}

void showFindClientScreen()
{
    system("clear");
    cout << "---------------------------------------\n";
    cout << "\t Find Client Screen\n";
    cout << "---------------------------------------\n";
    string accountNumber = getAccountNumber();
    vector<stClient> vClient = loadDataFromFile(clientsFile);
    stClient client;
   
    if(findClientByAccountNumber(accountNumber, vClient, client))
    {
        printClientCard(client);
    }else{
        cout << "Client Account Number [ "<< accountNumber << " ] Not Found.\n";
    }
 
}

void showTransactionMenuScreen()
{
    system("clear");
    cout << "=============================================\n";
    cout << "\t Transaction Menu Screen.\n";
    cout << "=============================================\n";
    cout << "\t[1] Deposit.\n";
    cout << "\t[2] Withdraw.\n";
    cout << "\t[3] Total Balances.\n";
    cout << "\t[4] Main Menu.\n";
    cout << "=============================================\n";
   performTransactionMenu((enTransactionMenu)readTransactionOption());
}

void showExitScreen()
{
    system("clear");
    cout << "\n-----------------------------------\n";
    cout << "\n\tProgram Ends :-)\n";
    cout << "\n------------------------------------\n";
}
 
//------------------------ Front GUI -------------------------------

enum enMenuOperations
{
    eclientList = 1, eAddNewClient = 2,
    eDeleteClient = 3, eUpdateClient = 4, 
    eFindClient = 5, eTransactions = 6 ,
    eExit = 7
};

short readMenuOption()
{
    short num;
    cout <<"Which Operation You Want to Do? [1:6] : ";
    cin >> num;

    return num;
}

void goBacktoMainMenu()
{
    cout << "\nPress Enter to Go to Main Menu....";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
    showMainMenu();
}

//--------------------- Connect Front & Back (API) ----------------------

void performShowMenuScreen(enMenuOperations option)
{
    switch(option)
    {
        case enMenuOperations::eclientList :
            showAllClientScreen();
            goBacktoMainMenu();
            break;

        case enMenuOperations::eAddNewClient :
            showAddNewClientScreen();
            goBacktoMainMenu();
            break;

        case enMenuOperations::eDeleteClient : 
            showDeleteClientScreen();
            goBacktoMainMenu();
            break;

        case enMenuOperations::eUpdateClient :
            showUpdateClientInfoScreen();
            goBacktoMainMenu();
            break;

        case enMenuOperations::eFindClient :
            showFindClientScreen();
            goBacktoMainMenu();
            break;

        case enMenuOperations::eTransactions :
            showTransactionMenuScreen();
            break;

        case enMenuOperations::eExit : 
            showExitScreen();
            break;

        default :
           cout <<"Please Enter a Valid Number From 1 : 6\n";
            
    }
}

void showMainMenu()
{
    system("clear");
    cout <<"----------------------------------\n";
    cout <<"\t Main Menu Screen\n";
    cout <<"----------------------------------\n";
    cout <<"\t[1] Show Client List.\n";
    cout <<"\t[2] Add New Client.\n";
    cout <<"\t[3] Delete Client.\n";
    cout <<"\t[4] Update Client Info.\n";
    cout <<"\t[5] Find Client\n";
    cout <<"\t[6] Transaxtions.\n";
    cout <<"\t[7] Exit.\n";
    cout <<"----------------------------------\n";
    performShowMenuScreen((enMenuOperations)readMenuOption());
}


int main()
{
    showMainMenu(); 
    return 0;
}


