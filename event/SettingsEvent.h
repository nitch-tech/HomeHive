//
// Created by Nick on Mar 28th 
//
#ifndef SETTINGSEVENT_H
#define SETTINGSEVENT_H

#include <iostream>
#include <string>
#include "../gui/HomeView.h"
class SettingsEvent{
    
    public:
        static SettingsEvent* getInstance();
        void update_main();// call update label in homeview
        void subscribe(HomeView* view);

    private:
        SettingsEvent();
        ~SettingsEvent();
        static SettingsEvent* eventptr;
        static HomeView* view;
};



#endif // SETTINGSEVENT_H