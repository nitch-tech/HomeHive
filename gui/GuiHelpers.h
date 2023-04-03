//
// Created by dave on 03/04/23.
//

#ifndef HOMEHIVE_GUIHELPERS_H
#define HOMEHIVE_GUIHELPERS_H

#include <gtk/gtk.h>
#include <string>

/**
 * Add a custom CSS class name to some widget
 *
 * @param widget The widget to add the class to
 * @param className The CSS class name to add
 */
void addClass(GtkWidget* widget, std::string className);

/**
 * Remove a custom CSS class name from some widget
 *
 * @param widget The widget to remove the class from
 * @param className The CSS class name to remove
 */
void removeClass(GtkWidget* widget, std::string className);

#endif //HOMEHIVE_GUIHELPERS_H
