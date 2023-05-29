#include<iostream>
#include<string>
#include "confighandler.h"

using namespace HandlerNamespce;

ConfigHandler *ConfigHandler::instance = 0;
#define NULL_PTR 0

int main()
{


        ConfigHandler* myHandler = myHandler->getInstance();
        int n=1;
        std::string secName,feature,tag, str1="",str2="", str3="", str4="",str5="", val, filename, valueof;
        while(n != 0){

                std::cout<<"welcome to configManager \n";
                std::cout<<"select from the option below: \n";
                std::cout<<"0. Exit\n";
                std::cout<<"1. Read new data \n";
                std::cout<<"2. Fetch a value \n";
                std::cout<<"3. Set a value \n";
		std::cout<<"4. Modify a value \n";
                std::cout<<"5. Sync Data \n";
                std::cout<<"6. Delete key\n";
                std::cout<<"7. Delete sec\n";
                std::cout<<"8. Display values\n";
                std::cin>>n;


                if(n==0){
                        std::cout<<"Thank you";
                }
                if(n==1){
                        std::cout<<"Enter file name :";
                        std::cin>>filename;
                        std::string filepath = filename+".ini";
                        myHandler->parseData(filepath);
                }
                if(n==2){
            		cout<<"\n Enter Section\n";
            		cin>>secName;
            		cin.ignore();
                        cout<<"\n Enter feature name \n";
                        getline(cin,feature);
            		cout<<"\n Enter str1 \n";
            		getline(cin,str1);
            		cout<<"\n Enter str2 \n";
            		getline(cin,str2);
            		cout<<"\n Enter str3 \n";
            		getline(cin,str3);
            		cout<<"\n Enter str4 \n";
            		getline(cin,str4);
                        cout<<"\n Enter str5 \n";
                        getline(cin,str5);


                        std::cout<<feature<<std::endl;
                        std::cout<<"value is : ";
                        myHandler->getValue(secName, feature, str1, str2, str3, str4, str5, valueof);
                        cout<<valueof<<std::endl;
                }
                if(n==3){
                        std::cout<<"enter section name: ";
                        std::cin>>secName;
                        std::cout<<"enter tag : ";
                        std::cin>>tag;
                        std::cout<<"enter value : ";
                        std::cin>>val;
                        myHandler->setValue(secName, tag, val);
                        std::cout<<"success";
                }
                if(n==4){
                        std::cout<<"enter section name: ";
                        std::cin>>secName;
                        std::cout<<"enter tag : ";
                        std::cin>>tag;
                        std::cout<<"enter value : ";
                        std::cin>>val;
                        myHandler->editValue(secName, tag, val);
                        std::cout<<"success";
                }

                if(n==5){
                        myHandler->syncData();
                }
                if(n==6){
                        std::cout<<"Enter section Name: ";
                        std::cin>>secName;
                        std::cout<<"Enter tag: ";
                        std::cin>>tag;
                        myHandler->deleteKey(secName,tag);
                        std::cout<<"\n Key Deleted successfully! \n";
                }

                if(n==7){
                        std::cout<<"Enter section Name: ";
                        std::cin>>secName;
                        myHandler->deleteSec(secName);
                        std::cout<<"\n Section Deleted successfully! \n";
                }

                if(n==8){

                        myHandler->displayValues();
                }


        }
        return 0;

}
