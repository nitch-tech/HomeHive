#include "GuiHelpers.h"

/**
 * Add a custom CSS class name to some widget
 *
 * @param widget The widget to add the class to
 * @param className The CSS class name to add
 */
void addClass(GtkWidget* widget, std::string className) {
	GtkStyleContext* context = gtk_widget_get_style_context(widget);
	gtk_style_context_add_class(context, className.c_str());
}

/**
 * Remove a custom CSS class name from some widget
 *
 * @param widget The widget to remove the class from
 * @param className The CSS class name to remove
 */
void removeClass(GtkWidget* widget, std::string className) {
	GtkStyleContext* context = gtk_widget_get_style_context(widget);
	gtk_style_context_remove_class(context, className.c_str());
}
