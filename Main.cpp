#include <iostream>
#include <fstream>
#include <cctype>
#include <string>
#include <cstring>
#include <vector>
using namespace std;
void enterVehicleInfo();
void updateVehicleInfo();
void viewVehicleInfo();
void saveToFile();
void saveToFileStruct();
void getFromFile();
void sortDataByName();
void sortDataByType();
void deleteRecord();
void generateId();
struct vehicle
{
    string id;
    string name;
    string type;
    string status;
};
static vector<vehicle>allinfo;
static string name,type,word;
string search_name,search_type,status={};
int ans,ans1,delete_id,search_id,current_id,id=0,max_id=0;
int main()
{
    int choice=0;
    do
    {
        choice=0;
        cout<<"1.Enter Vehicle Info: "<<endl;
        cout<<"2.Update Vehicle Info: "<<endl;
        cout<<"3.View Vehicle Info: "<<endl;
        cout<<"4.Sort data by Name: "<<endl;
        cout<<"5.Sort data by Type: "<<endl;
        cout<<"6.Delete Record: "<<endl;
        cin>>choice;
        switch (choice)
        {
            case 1:
            enterVehicleInfo();
            break;
            case 2:
            updateVehicleInfo();
            break;
            case 3:
            viewVehicleInfo();
            break;
            case 4:
            sortDataByName();
            break;
            case 5:
            sortDataByType();
            break;
            case 6:
            deleteRecord();
            break;
            default:
            cout<<"Ending program: "<<endl;
            break;

         }
    }while(choice!=7);
    return 0;
}


void generateId()
{
    id++;
}


void enterVehicleInfo()
{
    cout<<"Enter Vehicle Info: "<<endl;
    getFromFile();
    cout<<"Enter the name of Vehicle: ";
    getline(cin>>ws,name);
    cout<<"Enter the type of Vehicle: ";
    getline(cin>>ws,type);
    cout<<"Enter the status of Vehicle: "<<endl;
    cout<<"1.For checkedin and 2.For Checked out: "<<endl;
    cin>>ans;
    if(ans==1)
    {
        status="checkedin";
    }
    if(ans==2)
    {
        status="checkedout";
    }
    generateId();
    
    saveToFile();
}


void updateVehicleInfo()
{
    
    int choice=0;
    getFromFile();
    cout<<"Enter the ID Rcord you want to update: ";
    cin>>search_id;
    for(int i=0;i<allinfo.size();i++)
    {
        int num=stoi(allinfo[i].id);
        if(search_id==num)
        {
            cout<<"1.To Change Name.\n2.To Change Type\n3.To Change Status\n4.Press any number to exit"<<endl;
            cin>>choice;
            switch (choice)
        {
        case 1:
        cout<<"Enter new name to change: ";
        getline(cin>>ws,search_name);
        allinfo[i].name=search_name;
        cout<<"Name changed"<<endl;
        break;
        case 2:
        cout<<"Enter new type to change: ";
        getline(cin>>ws,search_type);
        allinfo[i].type=search_type;
        cout<<"Type changed"<<endl;
        break;
        case 3:
        cout<<"Enter the new status: "<<endl;
        cout<<"1.For checkedin and 2.For Checked out: "<<endl;
        cin>>ans1;
        if(ans1==1)
        {
            allinfo[i].status="checkedin";
        }
        if(ans1==2)
        {
            allinfo[i].status="checkedout";
        }
        break;
        default:
        cout<<"Exiting program"<<endl;
        break;
        }
        break;
        }
        else
        {
            cout<<"Cannot Update"<<endl;
            break;
        }
    }
    saveToFileStruct();

}


void deleteRecord()
{
    getFromFile();
    cout<<"Enter the id you want to delete: ";
    cin>>delete_id;
    for(int i=0;i<allinfo.size();i++)
    {
        int num=stoi(allinfo[i].id);
        if(delete_id==num)
        {
            if(allinfo[i].status=="checkedout")
            {
            allinfo.erase(allinfo.begin()+i);
            cout<<"Record Deleted "<<endl;
            }
            else
            {
                cout<<"Cannot Delete Record"<<endl;
            }
            break;
        }
    }
    saveToFileStruct();
}


void sortDataByName()
{
    getFromFile();
    for(int i=0;i<allinfo.size()+1;i++)
    {
        for(int j=i+1;j<allinfo.size();j++)
        {
            vehicle temp3;
            vehicle temp1=allinfo[i];
            vehicle temp2=allinfo[j];
            if(temp1.name>temp2.name)
            {
                temp3=allinfo[i];
				allinfo[i]=allinfo[j];
				allinfo[j]=temp3;
            }
            
        }
    }
    saveToFileStruct();
}


void sortDataByType()
{
    getFromFile();
    for(int i=0;i<allinfo.size()+1;i++)
    {
        for(int j=i+1;j<allinfo.size();j++)
        {
            vehicle temp3;
            vehicle temp1=allinfo[i];
            vehicle temp2=allinfo[j];
            if(temp1.type>temp2.type)
            {
                temp3=allinfo[i];
				allinfo[i]=allinfo[j];
				allinfo[j]=temp3;
            }
            
        }
    }
    saveToFileStruct();
}


void getFromFile()
{

    allinfo.clear();
    vehicle vehicleinfo;
    fstream fin;
    fin.open("vehicle.txt",ios::in);
    int maxId=0;
    while(!fin.eof())
    {
        getline(fin,word);
        int i=word.find(":");
        string pre=word.substr(0,i);
        string pos=word.substr(i+1,word.size());
        int z=pos.find('\n');
        pos=pos.substr(0,z);
        if (pre=="ID")
        {
           vehicleinfo.id=pos;
            int currentId = stoi(pos);
            if (currentId > maxId)
            {
                maxId = currentId;
            }
        }
        else if (pre=="NAME")
        {
            vehicleinfo.name=pos;
        }
        else if (pre=="TYPE")
        {
            vehicleinfo.type=pos;
        }
        else if (pre=="STATUS")
        {
            vehicleinfo.status=pos;
            allinfo.push_back(vehicleinfo);
            vehicleinfo={};
        }
    }
    fin.close();
    id = maxId;
       
}


void viewVehicleInfo()
{
    getFromFile();
    for(int i=0;i<allinfo.size();i++)
    {
        cout<<allinfo[i].id<<endl;
        cout<<allinfo[i].name<<endl;
        cout<<allinfo[i].type<<endl;
        cout<<allinfo[i].status<<endl;
    }
}


void saveToFileStruct()
{
    fstream fout;
    fout.open("vehicle.txt",ios::out);
    for(int i=0;i<allinfo.size();i++)
	{
		fout<<"ID:"<<allinfo[i].id<<endl;
		fout<<"NAME:"<<allinfo[i].name<<endl;
		fout<<"TYPE:"<<allinfo[i].type<<endl;
		fout<<"STATUS:"<<allinfo[i].status<<endl;
	}

    fout.close();
}


void saveToFile()
{
    fstream fout;
    fout.open("vehicle.txt",ios::app);
    fout<<"ID:"<<id<<endl;
    fout<<"NAME:"<<name<<endl;
    fout<<"TYPE:"<<type<<endl;
    fout<<"STATUS:"<<status<<endl;
    fout.close();
}