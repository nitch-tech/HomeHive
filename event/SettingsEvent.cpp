
/**
* @file SettingsEvent.h
* @brief This file contains the implementation of the SettingsEvent class.
*/
#include "SettingsEvent.h"
SettingsEvent* SettingsEvent::eventptr = nullptr;
HomeView* SettingsEvent::view = nullptr;
/**
* @brief Default constructor of the SettingsEvent class
*/
SettingsEvent::SettingsEvent(){

}
/**
* @brief Destructor of the SettingsEvent class
*/
SettingsEvent::~SettingsEvent(){

}
/**
* @brief Get the instance of the SettingsEvent singleton class
* @return SettingsEvent* - pointer to the instance of the SettingsEvent class
*/
SettingsEvent* SettingsEvent::getInstance() {
    if (eventptr == nullptr) {
        eventptr = new SettingsEvent();
    }
    return eventptr;
}
/**
* @brief Subscribe a HomeView object to the SettingsEvent
* @param v - pointer to the HomeView object
*/
void SettingsEvent::subscribe(HomeView* v){
    view = v;
}
/**
* @brief Update the HomeView object associated with the SettingsEvent
*/
void SettingsEvent::update_main(){
    view->update();
}