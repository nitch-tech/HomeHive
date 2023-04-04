/**
* @file SettingsEvent.h
* @brief Header file for the SettingsEvent class.
* This file contains the declaration of the SettingsEvent class, which is responsible
* for updating the HomeView and subscribing to its events.
* @author Nick
* @date March 28th
*/
#ifndef SETTINGSEVENT_H
#define SETTINGSEVENT_H

#include <iostream>
#include <string>
#include "../gui/HomeView.h"
/**

* @class SettingsEvent
* @brief A class for handling events related to the settings.
* The SettingsEvent class is responsible for updating the HomeView and subscribing to
* its events. It contains a static instance of itself and a static pointer to a HomeView
* object that it subscribes to.
*/
class SettingsEvent{
 
    public:
       /**
    * @brief Get the singleton instance of the SettingsEvent class.
    * @return A pointer to the singleton instance of the SettingsEvent class.
    */
        static SettingsEvent* getInstance();
    /**
    * @brief Update the main label in the HomeView.
    *
    * This function calls the updateLabel() function in the HomeView class to
    * update the main label with the latest settings.
    */
        void update_main();
        
    /**
    * @brief Subscribe to a HomeView object.
    *
    * This function sets the static pointer to the HomeView object that the
    * SettingsEvent class subscribes to.
    *
    * @param view A pointer to the HomeView object to subscribe to.
    */
        void subscribe(HomeView* view);

    private:
    /**
    * @brief Private constructor for the SettingsEvent class.
    *
    * The constructor is made private to ensure that only one instance of the
    * SettingsEvent class can be created.
    */
        SettingsEvent();
    /**
      * @brief Private destructor for the SettingsEvent class.
      *
      * The destructor is made private to ensure that the SettingsEvent object
      * can only be destroyed through the getInstance() function.
      */
        ~SettingsEvent();
     static SettingsEvent* eventptr; /**< Pointer to the singleton instance of the SettingsEvent class. */
     static HomeView* view; /**< Pointer to the HomeView object that the SettingsEvent class subscribes to. */
};



#endif // SETTINGSEVENT_H