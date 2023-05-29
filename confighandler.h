/******************************************************************************
 *                                                                            *
 *                      Copyright ( C ) 2000, 2001                            *
 *                    Tejas Networks India Pvt. Ltd                           *
 *                                                                            *
 *              Proprietary and Confidential. All Rights Reserved             *
 *                                                                            *
 ******************************************************************************/
/******************************************************************************
 *   Name    : app/common/nm/nm/ConfigHandler.h                               *
 *   Desc    : Common utility functions to perform action like read, write,   *
 *             edit, delete data from .ini configuration files.               *
 *                                                                            *
 *   History :                                                                *
 *             - Initial version : Abhishek Kumar Mishra                      *
 *                                                                            *
 * ****************************************************************************/

#ifndef _CONFIG_HANDLER_H_
#define _CONFIG_HANDLER_H_
#include<iostream>
#include<map>
#include<vector>
#include<thread>
#include"iniparser.hpp"

#define NULL_PTR 0


using namespace std;

namespace HandlerNamespce
{
        class ConfigHandler
        {
                private:
/************************************************** locally declared varilables **************************************************/
                        static ConfigHandler                                    *instance;			// Instance for class
                        INI::File                                               file;				// Instance for file class
                        std::string                                             fileName;			// Storing name of file
                        std::vector<std::thread>                                threadlist;			// List of threads in this instance
                        std::string                                             errorstate;			// Last occured error as string
                        int                                                     delay;				// delay between each read operation


                        // Define constructor in the private section to make this
                        // class as singleton.
                        ConfigHandler();


         // Define destructor in private section, so no one can delete
         // the instance of this class.
         ~ConfigHandler();

         // Define copy constructor in the private section, so that no one can
         // voilate the singleton policy of this class
         ConfigHandler(const ConfigHandler& obj) = delete;

         // Define assignment operator in the private section, so that no one can
         // voilate the singleton policy of this class
         void operator=(const ConfigHandler& obj) = delete;

         // Helper function to trim the tag and value. These helper function is
         // calling to trim the un-necessary spaces.
         std::string trim(const std::string& str, const std::string& whitespace = " \t");
         
         std::string reduce(const std::string& str,
               const std::string& fill = " ",
               const std::string& whitespace = " \t");


                public:

                        static ConfigHandler*   getInstance()
                                                {

                                                // No need to use double re-check lock mechanism here
                                                // because this getInstance() will call at the time of
                                                // initialization only and mostly, at the time of
                                                // initialization, there will be only one thread.

                                                if (!instance)
                                                {
                                                        instance = new ConfigHandler;
                                                }
                                                return instance;
                                                }
                        // Function for re reading the data from file in async manner
                        bool                    reinit();

			// Function to parse data from given file name
			// arguements - filepath
                        bool                    parseData(std::string filePath);
			
			// Function to fetch the value of a feature using sectionName, featurename, str1,.. str5
			// as additiona arguement, stored the value in the value arguement
                        bool                    getValue(std::string sectionName, 
                                                                std::string featureName, 
                                                                        std::string str1, 
                                                                                std::string str2, 
                                                                                        std::string str3,
                                                                                                std::string str4, 
                                                                                                        std::string str5,
                                                                                                                std::string &value);

			// Function to set the value of a feature using sectionName, tag and value
                        void                    setValue(std::string tag,
                                                                std::string sectionName, 
                                                                        std::string& value);
			// Function to modify values of a feature using tag, sectionName, and stores the result in value
                        void                    editValue(std::string tag, 
                                                                std::string sectionName, 
                                                                        std::string& value);
	
			// Function to delete a feature in a section by passing the sectionName and Key.
                        void                    deleteKey(std::string sectionName, 
                                                                std::string key);

			// Function to delete a complete section from the configuration file
                        void                    deleteSec(std::string sectionName);
	
			// Function to print out all the values and sections present in the file
                        void                    displayValues();
			
			// Function for manually sync the data between file and datastore
                        void                    syncData();

   };

} //End of namespace

#endif 
// End of _CONFIG_HANDLER_H_
