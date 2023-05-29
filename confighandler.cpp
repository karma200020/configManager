/******************************************************************************
 *                                                                            *
 *                      Copyright ( C ) 2000, 2001                            *
 *                    Tejas Networks India Pvt. Ltd                           *
 *                                                                            *
 *              Proprietary and Confidential. All Rights Reserved             *
 *                                                                            *
 ******************************************************************************/
/******************************************************************************
 *   Name    : app/common/nm/nm/ConfigHandler.cpp                             *
 *   Desc    : Common utility functions to perform action like read, write,   *
 *             edit, delete data from .ini configuration files.Includes       *
 *             declaration of each function.                                  *
 *   History :                                                                *
 *             - Initial version : Abhishek Kumar Mishra                      *
 *                                                                            *
 * ****************************************************************************/


#include<iostream>
#include<string>
#include "iniparser.hpp"
#include "confighandler.h"

using namespace HandlerNamespce;

#define NULL_PTR 0




// In the constructor define initial variables 
ConfigHandler::ConfigHandler()
{
    ConfigHandler::delay = 60000;								// Change the timing between each sync
    ConfigHandler::threadlist.push_back(std::thread(&ConfigHandler::reinit, this));		// List storing all the asyn operations

}

// In the destructor we intend to close all the running operations including threads
 ConfigHandler::~ConfigHandler()
{

    for(auto& t: threadlist)
    {
        if(t.joinable()){
            t.join();
        }
        
    }
}

ConfigHandler *ConfigHandler::instance = 0;



ConfigHandler* ConfigHandler::getInstance(void) {
     if (!instance) {
         instance = new ConfigHandler();
     }
     return instance;
}

// Function for parsing data from given file
bool ConfigHandler::parseData(std::string filePath)
{
    if(filePath == ""){
        return false;
    }
    ConfigHandler::fileName = filePath;
    if (!ConfigHandler::file.Load(filePath))
	{
		// Loading from stream
		std::ifstream op("opts.ini",std::ios::in);
		if (op.is_open())
			op >> file;
	}
    return true;
}

  // Function for reading the data from the file in a certain interval
bool ConfigHandler::reinit(){
 bool unload_prev = true;

 if(ConfigHandler::getInstance()->fileName == ""){ return NULL; }    ConfigHandler::getInstance()->file.Unload();

 ConfigHandler::getInstance()->file.Load(ConfigHandler::getInstance()->fileName, unload_prev);
}


// Function for fetching a value using sectionName and feature specifications value is then stored in value arguement
bool ConfigHandler::getValue(std::string sectionName, 
                                        std::string featureName, 
                                            std::string str1, 
                                                std::string str2, 
                                                    std::string str3,
                                                        std::string str4, 
                                                            std::string str5,
                                                                std::string &value)
{
    ConfigHandler::errorstate = "insufficient information \n";
    if(sectionName ==""||featureName=="")
    {
        cout<<errorstate;
        return false;
    }

    string args[5];
    std::string tag="";
    tag = tag + featureName;
    args[0]= str1;
    args[1]= str2;
    args[2]= str3;
    args[3]= str4;
    args[4]= str5;
    for(int i = 0; i< 5; i++){
        if(args[i] != ""){
            tag += "_";
            tag += args[i];
        }
        else
            break;
    }
    value = ConfigHandler::file.GetSection(sectionName)->GetValue(tag,1).AsString();

    return true;
}


// Function for setting a value using sectionName and tag
void ConfigHandler::setValue(std::string sectionName,
                                std::string tag, 
                                    std::string& value)
{
    ConfigHandler::file.GetSection(sectionName)->SetValue(tag,value);
}


// Function for modifying value of a feature  using tag and sectionName
void ConfigHandler::editValue(std::string sectionName, 
                                std::string tag, 
                                    std::string& value)
{

    ConfigHandler::file.GetSection(sectionName)->SetValue(tag,value);
}


// Function to remove a key value pair from the store using sectionName and key
void ConfigHandler::deleteKey(std::string sectionName, std::string key)
{
        if(sectionName == ""|| key == "")
    {
        std::cout<<"Please enter sectionName and key correctly \n";
        return;
    }

    ConfigHandler::file.GetSection(sectionName)->RemoveValue(key);

}

// Function to remove a section from the file
void ConfigHandler::deleteSec(std::string sectionName)
{
    if(sectionName == "")
    {
	std::cout<<"Please enter sectionName correctly \n";
	return;
    }
    ConfigHandler::file.DeleteSection(sectionName);

}


// Function to display all the from the data store.
void ConfigHandler::displayValues(){
    for (INI::File::sections_iter it = ConfigHandler::file.SectionsBegin(); it != ConfigHandler::file.SectionsEnd(); ++it)
	{
		std::cout << "Section name: " << it->first << std::endl;
		INI::Section* sect = it->second;
		// iterate over all entries in specific section
		for (INI::Section::values_iter it2 = sect->ValuesBegin(); it2 != sect->ValuesEnd(); ++it2)
			std::cout << "Entry name: " << it2->first << ", Entry value: " 
					  << it2->second.AsString() << std::endl;
	}
}


// Function for manually sync all the data from datastore to file
void ConfigHandler::syncData()
{
    ConfigHandler::file.Save(fileName);
}

