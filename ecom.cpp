#include <iostream.h>
#include <fstream.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

class product
{
private:
int pno ; // product number
char pname[30]; // product name
int qty ; // quantity
float price ;
public:
int ret_pno();
int ret_qty();
float ret_price();
void ret_pname();
void input();
void output();
void mod_qty(int a);
void modinput();
};
void product::modinput()
{
cout << "\nENTER PRODUCT Name - " ;
gets(pname) ;
cout << "\nENTER QUANTITY - " ;
cin >> qty ;
cout << "\nENTER PRICE - " ;
cin >> price ;
}
void product::mod_qty(int a)
{
qty+=a;
}
int product::ret_pno()
{
    return pno ;
}
int product::ret_qty()
{
    return qty ;
}
float product::ret_price()
{
    return price ;
}
void product::ret_pname()
{
    cout << pname  ;
}
void product::input()
{
    cout << "\nENTER PRODUCT NO - " ;
    cin >> pno ;
    cout << "\nENTER PRODUCT Name - " ;
    gets(pname) ;
    cout << "\nENTER QUANTITY - " ;
    cin >> qty ;
    cout << "\nENTER PRICE - " ;
    cin >> price ;
}
void product::output()
{
    cout << "\nPRODUCT NO - "<<pno ;
    cout << "\nPRODUCT NAME - " <<pname ;
    cout << "\nQUANTITY - " <<qty ;
    cout << "\nPRICE - " <<price ;
}
class customer
{
private:
    int membercode; // member code
    char cname [80] ; // customer name
    char address[80];
    char disc ; // checks if member is eligible for discount Y - YES & N - NO
    int items ; //no of items ordered
    //int products[100]; // array of product codes
    float total ; //total amount after discount - 75% of total price for paid members
    int products[100];
public:
    int cnamecomp(char ch[20]);
    int ret_membercode();
    void ret_cname();
    void ret_address();
    char ret_disc();
    int ret_items();
    float ret_total();
    void input();
    void output();
    void calculate_total(); //calculate total
    void modify_total(int a); // when adding products
    void mod_items(int a);
    customer()
    {
        total = 0 ;
    }
    void modinput();
    int array_ret(int pos);
    void array_add(int pos,int val);
    void array_delete(int pos);
    
};
void customer::modify_total(int a)
{
    total+=a;
}
void customer::array_delete(int j)
{
    for(int k = j+1;k<items;++k)
        products[k-1]=products[k];
}
void customer::array_add(int pos,int val)
{
    products[pos]=val;
}
int customer::array_ret(int pos)
{
    return products[pos];
}
void customer::modinput()
{
    cout << "\nENTER CUSTOMER NAME - " ;
    gets(cname) ;
    cout << "\nENTER ADDRESS - " ;
    gets(address) ;
    cout << "\nENTER IF MEMBER IS ELIGIBLE FOR DISCOUNT-" ;
    cin >> disc ;
}
int customer::cnamecomp(char ch[])
{
    return strcmp(cname,ch);
}
void customer::mod_items(int a)
{
    items+= a;
}
float customer::ret_total()
{
    return total ;
}
char customer::ret_disc()
{
    return disc ;
}
int customer::ret_membercode()
{
    return membercode ;
}
int customer::ret_items()
{
    return items ;
}
void customer::ret_cname()
{
    cout << cname ;
}
void customer::ret_address()
{
    cout << address ;
}
void customer::input()
{
    cout << "\nENTER MEMBER CODE - " ;
    cin >> membercode ;
    cout << "\nENTER CUSTOMER NAME - " ;
    gets(cname) ;
    cout << "\nENTER ADDRESS - " ;
    gets(address) ;
    cout << "\nENTER IF MEMBER IS ELIGIBLE FOR DISCOUNT-" ;
    cin >> disc ;
    cout << "\nENTER ITEMS ORDERED - " ;
    cin >> items ;
    cout << "\nENTER PRODUCT CODES : " ;
    for(int i =0 ; i<items ; ++i)
        cin >> products[i];
    calculate_total();
}
void customer::calculate_total()
{
    ifstream fin("product.dat",ios::binary);
    product ob ;
    total = 0 ;
    while(fin.read((char*)&ob,sizeof(ob)))
    {
        for(int i=0;i<items;++i)
        {
            if(products[i]==ob.ret_pno())
                total+=ob.ret_price();
        }
    }
    if(disc=='Y') //25% off for special members
        total = total*0.75;
    fin.close();
}
void customer::output()
{
    cout << "\nMEMBER CODE - "<<membercode ;
    cout << "\nCUSTOMER NAME - " <<cname ;
    cout << "\nADDRESS - " <<address ;
    cout << "\nMEMBER IS ELIGIBLE FOR DISCOUNT - " <<disc ;
    cout << "\nITEMS ORDERED- " << items ;
    cout << "\nTOTAL- "<< total ;
}
void add_prod() //adding records to product.dat
{
    ofstream fout("product.dat",ios::binary|ios::app);
    product ob ;
    int tot ;
    cout << "Enter total products : " ;
    cin >> tot ;
    for(int i=0;i<tot;++i)
    {
        ob.input();
        fout.write((char*)&ob,sizeof(ob));
    }
    fout.close();
}
void add_cust() //adding records to customer.dat
{
    ofstream fout("customer.dat",ios::binary|ios::app);
    customer ob ;
    int tot ;
    cout << "Enter total customers : " ;
    cin >> tot ;
    for(int i=0;i<tot;++i)
    {
        ob.input();
        fout.write((char*)&ob,sizeof(ob));
    }
    fout.close();
}

float feecalc(int pno) // returns price of specific product
{
    ifstream fin ("product.dat",ios::binary);
    product ob ;
    while(fin.read((char*)&ob,sizeof(ob)))
    {
        if(ob.ret_pno()==pno)
        { fin.close();
            return ob.ret_price();}
    }
    fin.close();
    return 0 ;
    
    
}
void modify_quantity(int pno) //to modify quantity of products - subtract
{
    ifstream fin ("product.dat",ios::binary);
    ofstream fout ("temp.dat",ios::binary);
    product pr ;
    while(fin.read((char*)&pr,sizeof(pr)))
    {
        if(pno==pr.ret_pno())
        {
            pr.mod_qty(-1) ;
            
            
            
        }
        fout.write((char*)&pr,sizeof(pr));
    }
    fin.close();
    fout.close();
    remove("product.dat");
    rename("temp.dat","product.dat");
    
}
void modify_quantity_add(int pno) //to modify quantity of products - add
{
    ifstream fin ("product.dat",ios::binary);
    ofstream fout ("temp.dat",ios::binary);
    product pr ;
    while(fin.read((char*)&pr,sizeof(pr)))
    {
        if(pno==pr.ret_pno())
        {
            pr.mod_qty(1) ;
        }
        fout.write((char*)&pr,sizeof(pr));
    }
    fin.close();
    fout.close();
    remove("product.dat");
    rename("temp.dat","product.dat");
}

void addpr(int pno)
{
    ifstream fin_p("product.dat",ios::binary);
    ofstream fout_p("temp_p.dat",ios::binary);
    product ob ;
    while(fin_p.read((char*)&ob,sizeof(ob)))
    {
        if(ob.ret_pno()==pno)
        {
            ob.mod_qty(1);
        }
        fout_p.write((char*)&ob,sizeof(ob));
    }
    fin_p.close();
    fout_p.close();
    remove("product.dat");
    rename("temp_p.dat","product.dat");
}



void order() // MAIN OPERATION  - ORDERING PRODUCTS VIA ONLINE SERVICE
{
    ifstream fin_c("customer.dat",ios::binary);
    ofstream fout_c("tempc.dat",ios::binary);
    
    int key , pno ;
    cout << "Enter Customer No : " ;
    cin >> key ;
    customer ob ;
    int no;
    cout << "Enter no of products : " ;
    cin >> no ;
    while(fin_c.read((char*)&ob,sizeof(ob)))
    {
        if(ob.ret_membercode()==key)
        {
            
            for(int i = 1 ; i<=no ; ++i)
            {
                cout << "\nEnter PRODUCT CODE : " ;
                cin >> pno ;
                ob.array_add(ob.ret_items(),pno);
                ob.mod_items(1);
                modify_quantity(pno);
                if(ob.ret_disc()=='Y')
                    ob.modify_total((0.75*feecalc(pno)));
                else if(ob.ret_disc()=='N')
                    ob.modify_total(feecalc(pno));
            }
            
        }
        fout_c.write((char*)&ob,sizeof(ob));
    }
    fin_c.close();
    fout_c.close();
    remove("customer.dat");
    rename("tempc.dat","customer.dat");
}
void cancel()// MAIN OPERATION-CANCELLING PRODUCTS VIA ONLINE SERVICE
{
    ifstream fin_c("customer.dat",ios::binary);
    ofstream fout_c("temp_c.dat",ios::binary);
    ifstream fin_p("product.dat",ios::binary);
    customer ob ;
    product pr ;
    int key , pno , no ;
    cout << "Enter Customer No : " ;
    cin >> key ;
    cout << "LIST OF ORDERED ITEMS :\n " ;
    while(fin_c.read((char*)&ob,sizeof(ob)))
    {
        if(ob.ret_membercode()==key)
        {

            while(fin_p.read((char*)&pr,sizeof(pr)))
            {
                for(int i=0;i<ob.ret_items();++i)
                {
                    if(ob.array_ret(i)==pr.ret_pno())
                    {
                        cout << "\n"<<pr.ret_pno();
                        cout<<":";
                        pr.ret_pname();
                    }
                }
            }
            
        }
    }
    cout << "Enter no of products to be cancelled : " ;
    cin >> no ;
    fin_c.seekg(0,ios::beg);
    while(fin_c.read((char*)&ob,sizeof(ob)))
    {
        if(ob.ret_membercode()==key)
        {
            int k ;
            for(int i=0;i<no;++i)
            {
                cout << "\nEnter PRODUCT CODE : " ;
                cin >> pno ;
                for(int j=0;j<ob.ret_items();++j)
                {
                    if(pno==ob.array_ret(j))
                    {
                        ob.array_delete(j);
                        ob.mod_items(-1);
                        ++k;
                        
                    }
                    else if(j==ob.ret_items()-1&&k==0)
                    {
                        cout << "PRODUCT NOT FOUND";
                        --i;
                    }
                }
                ob.calculate_total();
                addpr(pno);
                
            }
        }
        
        fout_c.write((char*)&ob,sizeof(ob));
        
    }
    fin_c.close();
    fout_c.close();
    remove("customer.dat");
    rename("temp_c.dat","customer.dat");
}
void print_prod() // MAIN OPERATION  - PRINTING PRODUCT DETAILS
{
    ifstream fin("product.dat",ios::binary);
    product ob ;
    while(fin.read((char*)&ob,sizeof(ob)))
    {
        ob.output();
    }
    fin.close();
    
}
void print_cust() // MAIN OPERATION  - PRINTING CUSTOMER DETAILS

{
    ifstream fin("customer.dat",ios::binary);
    customer ob ;
    while(fin.read((char*)&ob,sizeof(ob)))
    {
        ob.output();
    }
    fin.close();
    
}
void order_report() // MAIN OPERATION  - PRINTING ORDER SUMMARY

{
    cout << "Enter Customer No : ";
    int key ;
    cin >> key ;
    ifstream fin("customer.dat",ios::binary);
    ifstream fin1("product.dat",ios::binary);
    customer ob ;
    product pr;
    while(fin.read((char*)&ob,sizeof(ob)))
    {
        if(key==ob.ret_membercode())
        {
            break;
        }
    }
    cout << "----------------------------\nORDER SUMMARY\nNAME : " ;
    ob.ret_cname();
    cout << "\nDelivery Address: ";
    ob.ret_address();
    cout << "\nPRODUCTS\n";
    
    while(fin1.read((char*)&pr,sizeof(pr)))
    {
        for(int i=0;i<ob.ret_items();++i)
        {
            if(ob.array_ret(i)==pr.ret_pno())
            { pr.ret_pname();
                cout << "\n" ;
            }
        }
    }
    cout << "\n----------\n"<<ob.ret_total()<<"\n----------\n" ;
    fin.close();
    fin1.close();
    
    
}
void paid_members() // MAIN OPERATION  - PRINTING REPORT OF PAID MEMBERS
{
    ifstream fin ("customer.dat",ios::binary);
    customer ob ;
    cout << "\nPAID MEMBERS : " << endl ;
    while(fin.read((char*)&ob,sizeof(ob)))
    {
        if(ob.ret_disc()=='Y')
        {
            ob.ret_cname();
            cout << "\n";
        }
    }
    fin.close();
    
}
void searchbyname() // MAIN OPERATION  - SEARCHING CUSTOMER BY NAME

{
    ifstream fin("customer.dat",ios::binary);
    customer ob ;
    char key[20];
    int i = 1 ;
    cout << "Enter name to be searched : " ;
    cin >> key ;
    while(fin.read((char*)&ob,sizeof(ob)))
    {
        if(ob.cnamecomp(key)==0)
        {
            ob.output();
            ++i;
        }
    }
    if(i==1)
        cout << "DETAILS NOT FOUND";
    fin.close();
    
    
}
void searchbypcode() // MAIN OPERATION  - SEARCHING PRODUCT BY CODE
{
    ifstream fin("product.dat",ios::binary);
    int key ;
    cout << "Enter PCODE TO BE SEARCHED : " ;
    cin >> key ;
    product ob ;
    int i=1 ;
    while(fin.read((char*)&ob,sizeof(ob)))
    {	
        if(key==ob.ret_pno())
        {
            ob.output();
            ++i;
        }
    }
    if(i==1)
        cout << "DETAILS NOT FOUND";
    fin.close();
    
}
void mod_cus() // MAIN OPERATION  - MODIFY CUSTOMER DETAILS
{
    //MODIFY NAME,ADDRESS,MEMBERSHIP CHANGE
    int key ;
    cout << "ENTER CUSTOMER CODE : ";
    cin >> key ;
    customer ob ;
    ifstream fin ("customer.dat",ios::binary);
    ofstream fout ("temp.dat",ios::binary);
    
    while(fin.read((char*)&ob,sizeof(ob)))
    {
        if(ob.ret_membercode()==key)
        {
            ob.modinput();
            ob.calculate_total();
            
        }
        fout.write((char*)&ob,sizeof(ob));
    }
    fin.close();
    fout.close();
    remove("customer.dat");
    rename("temp.dat","customer.dat");
}
void mod_prod() // MAIN OPERATION  - MODIFY PRODUCT DETAILS
{
    int key ;
    cout << "ENTER PRODUCT CODE : ";
    cin >> key ;
    product ob ;
    ifstream fin("product.dat",ios::binary);
    ofstream fout ("temp.dat",ios::binary);
    while(fin.read((char*)&ob,sizeof(ob)))
    {
        if(ob.ret_pno()==key)
        {
            ob.modinput();
        }
        fout.write((char*)&ob,sizeof(ob));
    }
    fin.close();
    fout.close();
    remove("product.dat");
    rename("temp.dat","product.dat");
    fin.open("customer.dat",ios::binary);
    fout.open("temp.dat",ios::binary);
    customer cu ;
    while(fin.read((char*)&cu,sizeof(cu)))
    {
        cu.calculate_total();
        fout.write((char*)&cu,sizeof(cu));
    }
    fin.close();
    fout.close();
    remove("customer.dat");
    rename("temp.dat","customer.dat");
    
}
int main()
{
    char c ;
    cout << “PRESS ANY KEY TO CONTINUE -----”;
    cin >> c ;
    char ch ;
    int chc ;
    do {
        cout << "------------------------------------------------------------------------------WELCOME TO E-MANAGEMENT----------------------------------------------------------------------------------\n1.ADD PRODUCT\n2.ADD CUSTOMERS\n3.MODIFY PRODUCT\n4.MODIFY CUSTOMERS\n5.PLACE ORDER\n6.CANCEL ORDER\n7.SEARCH BY CUSTOMER NAME\n8.SEARCH BY PRODUCT CODE\n9.PRINT PRODUCT\n10.PRINT CUSTOMER\n11.PRINT REPORT\n";
        cout << "\nEnter Choice : ";
        cin >> chc ;
        switch(chc)
        {
            case 1 : add_prod();
                break ;
            case 2 : add_cust();
                break ;
            case 3 : mod_prod();
                break ;
            case 4 : mod_cus();
                break ;
            case 5 : order();
                break ;
            case 6 : cancel();
                break ;
            case 7 : searchbyname();
                break ;
            case 8 : searchbypcode();
                break ;
            case 9 : print_prod();
                break ;
            case 10 : print_cust();
                break ;
            case 11 :
                char choice ;
                cout << "\nREPORT MENU\nA.FINAL ORDER\nB.PAID MEMBERS\nENTER CHOICE : " ;
                cin >> choice ;
                switch (choice) {
                        
                    case 'A': order_report();
                        break;
                    case 'B': paid_members();
                        break;
                }
                break;
        }
        cout << "\nDo you wish to continue ? " ;
        cin >> ch ;
    } while(ch=='y'||ch=='Y');
}




