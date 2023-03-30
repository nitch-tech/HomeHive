#include "SettingsEvent.h"
SettingsEvent* SettingsEvent::eventptr = nullptr;
HomeView* SettingsEvent::view = nullptr;
SettingsEvent::SettingsEvent(){

}
SettingsEvent::~SettingsEvent(){

}

SettingsEvent* SettingsEvent::getInstance() {
    if (eventptr == nullptr) {
        eventptr = new SettingsEvent();
    }
    return eventptr;
}
void SettingsEvent::subscribe(HomeView* v){
    view = v;
}
void SettingsEvent::update_main(){
    view->update_labels();
}