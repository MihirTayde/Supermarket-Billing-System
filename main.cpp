#include<iostream>
#include<fstream>
#include<cstdlib> // For exit()

using namespace std;

class shopping {
private :
    int Pcode; // P stands for Product
    float Price;
    float Discount;
    string Pname;
public :
    void menu();
    void administrator();
    void buyer();
    void add();
    void edit();
    void rem();
    void list();
    void receipt();
};

void shopping :: menu(){
    main_menu: //for goto function

    int choice;
    string email;
    string password; // corrected declaration

    cout<<"\t\t\t\t----------Supermarket Main Menu---------------\n\n\n";

    cout<<"\t[1.  Administrator ]\n\n";
    cout<<"\t[2.  Buyer ]\n\n";
    cout<<"\t[3.  Exit  ]\n\n\n\n"; 
    cout<<"\t  Please select \n\n";
    cin>>choice;

    switch(choice){
        case 1:{
            cout<<"Please Login\n";
            cout<<"Enter Email\n";
            cin>>email;
            cout<<"Enter Password\n";
            cin>>password;

            if(email == "mihir@gmail.com" && password == "mihir@123"){
                administrator();
            }
            else{
                cout<<"invalid username or password\n";
            }
            break;
        }

        case 2:{
            buyer();
            break;
        }
        case 3:{
            exit(0); // corrected exit() usage
            break;
        }
        default :{
            cout<<"Please select from the given option\n";
            break;
        }
    }
    goto main_menu; //going back to the main menu
}

void shopping :: administrator (){
    main_menu: //for goto function

    int choice;
    cout<<"\t Administrator-Menu\n";
    cout<<"1. ADD THE PRODUCT\n";
    cout<<"2. EDIT THE PRODUCT\n";
    cout<<"3. REMOVE THE PRODUCT\n";
    cout<<"4. Main Menu\n";
    cout<<"Please enter your choice\n\n\n";
    cin>>choice;

    switch(choice){
        case 1:{
            add();
            break;
        }
        case 2:{
            edit();
            break;
        }
        case 3:{
            rem();
            break;
        }
        case 4: {
            menu();
            break;
        }
        default: {
            cout<<"Invalid Choice\n";
            break;
        }
    }
    goto main_menu; //going back to the main menu
}
void shopping :: buyer(){
    main_menu:
    int choice;
    cout<<"1. Buy Product\n";
    cout<<"2. Go Back\n";
    cout<<"Enter the choice";
    cin>>choice;

    switch(choice){
        case 1: {
            receipt();
            break;
        }
        case 2: {
            menu();
            break;
        }
        default : {
            cout<<"Invalid Choice\n";
            break;
        }
    }
    goto main_menu;
}
void shopping ::add(){
    main_menu:
    fstream data;
    int c;
    int token = 0;
    float p;
    float d;
    string n;

    cout<<"\t\t Add new Product\n";
    cout<<"product code\n";
    cin>>Pcode;
    cout<<"Name of the product\n";
    cin>>Pname;
    cout<<"Price of the product\n";
    cin>>Price;
    cout<<"Discount on the product\n";
    cin>>Discount;

    data.open("database.txt",ios :: in); // in stands for read mode
    if(!data){
        data.open("database.txt",ios :: app | ios :: out); // app stands for append mode && out stands for writing mode 
        data<<"    "<<Pcode<<"     "<<Pname<<"     "<<Price<<"     "<<Discount<<"\n";
        data.close();    
    }
    else {
        data>>c>>n>>p>>d;
        while(!data.eof()){
            if(c==Pcode){
                token++;
            }
            data>>c>>n>>p>>d; // corrected semicolon and variable name
        }
        data.close();
    }
    if(token == 1){
        goto main_menu;
    }
    else{
        data.open("database.txt",ios :: app | ios :: out);
        data<<"    "<<Pcode<<"     "<<Pname<<"     "<<Price<<"     "<<Discount<<"\n";
        data.close();
    }
    cout<<"Record Inserted";
}
void shopping :: edit(){
    main_menu:
    fstream data,data1;
    int Pkey;
    int token = 0;
    int c;
    float p;
    float d;
    string n;
    cout<<"\tModify the Product\n";
    cout<<"Enter the product code\n";
    cin>>Pkey;
    data.open("database.txt", ios::in);
    if(!data){
        cout<<"File dosen't exist\n";
    }
    else{
        data1.open("database1.txt", ios::app | ios::out);
        data>>Pcode>>Pname>>Price>>Discount;
        while(!data.eof()){
            if(Pkey == Pcode){
                cout<<"Enter new product code\n";
                cin>>c;
                cout<<"Name of the product\n";
                cin>>n;
                cout<<"Enter the price\n";
                cin>>p;
                cout<<"Enter the discount\n";
                cin>>d;
                data1<<" "<<c<<" "<<n<<" "<<p<<" "<<d<<"\n";
                cout<<"Record edited";
                token++;
            }
            else{
                data1<<" "<<Pcode<<" "<<Pname<<" "<<Price<<" "<<Discount<<"\n";
            }
            data>>Pcode>>Pname>>Price>>Discount;
        }
        data.close();
        data1.close(); //here data is stored in data1() and we have to store the edited data back to data()
        remove("database.txt");
        rename("database1.txt", "database.txt"); // remove and rename are the inbuilt function

        if(token == 0){
            cout<<"Record not found\n";
        }
    }
}
void shopping :: rem(){
    fstream data, data1;
    int Pkey;
    int token = 0;
    cout<<"\t\t\t\t DELETE PRODUCT\n";
    cout<<"Product Code\n";
    cin>>Pkey;
    data.open("database.txt",ios::in);
    if(!data){
        cout<<"File not found";
    }
    else {
        data1.open("database1.txt", ios::app|ios::out);
        data>>Pcode>>Pname>>Price>>Discount;
        while(!data.eof()){
            if(Pcode==Pkey){
                cout<<"Product deleted successfully\n";
                token++;
            }
            else{
                data1<<" "<<Pcode<<" "<<Pname<<" "<<Price<<" "<<Discount<<"\n";
            }
            data>>Pcode>>Pname>>Price>>Discount;    
        }
        data.close();
        data1.close();
        remove("database.txt");
        rename("database1.txt", "database.txt");
        if(token==0){
            cout<<"record not found\n";
        }
    }
}
void shopping :: list(){
    fstream data;
    data.open("database.txt",ios::in);
    cout<<"\t Product Number \t\t\t\t\t\t\t\t\t Product Name \t\t\t\t\t\t\t\t\t Price\n";
    data>>Pcode>>Pname>>Price>>Discount;
    while(!data.eof()){
        cout<<Pcode<<"\t\t\t\t\t"<<Pname<<"\t\t\t\t\t"<<Price<<"\n";
        data>>Pcode>>Pname>>Price>>Discount;
    }
    data.close();
}
void shopping :: receipt(){
	main_menu:
    fstream data;
    int arrc[100];     //array of Product Code
    int arrq[100];     //array of quantity
    char choice;
    int c=0;
    float amount;
    float discount = 0;
    float total = 0;

    cout<<"\t\t\t\t\t\t Receipt \n\n\n\n";
    data.open("database.txt", ios::in);
    if(!data){
        cout<<"Empty database\n";
    }
    else{
        data.close();
        list();
        cout<<"\n Please Place the Order.\n";
        do{
            cout<<"Enter the product code: ";
            cin>>arrc[c];
            cout<<"Enter the quantity: ";
            cin>>arrq[c];
            for(int i=0;i<c;i++){
                if(arrc[c] == arrc[i]){
                    cout<<"Duplicate product code, Please try again";
                    goto main_menu;
                }
            }
            c++;
            cout<<"Do you want to buy another product if Yes, press Y  if No, press N";
            cin>>choice;
        }
        while(choice == 'Y' || choice == 'y');

        cout<<" \t\t\t\t\t\t Receipt \n\n\n";
        cout<<"Product no.\t\t Product Name \t\t Product Quantity \t\t Price \t\t Amount \t\t Amount with discount";

        for(int i=0;i<c;i++){
            data.open("database.txt",ios::in);
            data>>Pcode>>Pname>>Price>>Discount;
            while(!data.eof()){
                if(Pcode == arrc[i]){
                    amount = Price*arrq[i];
                    discount = amount - (amount*Discount/100);
                    total = total + discount;
                    cout<<"\n"<<Pcode<<"\t\t\t"<<Pname<<"\t\t\t"<<arrq[i]<<"\t\t\t"<<Price<<"\t\t\t"<<amount<<"\t\t\t"<<discount;
                }
                data>>Pcode>>Pname>>Price>>Discount;
            }
            data.close();       
        }

    }
    cout<<"\nTotal Amount : "<<total;
}

int main(){
    shopping s;
    s.menu();
    return 0;   
}
