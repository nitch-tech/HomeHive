#include "GuiHelpers.h"

/**
 * Add a custom CSS class name to some widget
 * @brief Add a custom CSS class name to some widget
 * @param widget The widget to add the class to
 * @param className The CSS class name to add
 * @author David Tkachuk
 */
void addClass(GtkWidget* widget, std::string className) {
	GtkStyleContext* context = gtk_widget_get_style_context(widget);
	gtk_style_context_add_class(context, className.c_str());
}

/**
 * Remove a custom CSS class name from some widget
 *
 * @brief Remove a custom CSS class name from some widget
 * @param widget The widget to remove the class from
 * @param className The CSS class name to remove
 * @author David Tkachuk
 */
void removeClass(GtkWidget* widget, std::string className) {
	GtkStyleContext* context = gtk_widget_get_style_context(widget);
	gtk_style_context_remove_class(context, className.c_str());
}
