#include <gtk/gtk.h>
#include <cmath>
#include <cstdlib>
#include <iostream>

struct run_struct
{
	GObject *menu;
	GObject *label;
	GObject *dialog;
};

void run_menu(GtkWidget *widget, run_struct *data);
void print_hello();
void bench();
void hide_window(GtkWidget *widget, gpointer data);
void show_window(GtkWidget *widget, gpointer data);

int main(int argc, char **argv)
{
	GtkBuilder *builder;
	GObject *window, *grid, *title, *menu, *button, *error, 
	*dialog, *vbox, *b_box, *d_none, *d_quit, *d_label, *title_menu,
	*m_file, *m_help, *file, *m_quit, *help, *about, *hbox,
	 *about_text, *about_close, *m_about;
		
	gtk_init(&argc, &argv);

	builder = gtk_builder_new();
	gtk_builder_add_from_file(builder, "dropdown.ui", NULL);

	// main window 
	window 		= gtk_builder_get_object(builder, "window"); 
	grid 			= gtk_builder_get_object(builder, "grid"); 
	title 		= gtk_builder_get_object(builder, "title"); 
	menu 			= gtk_builder_get_object(builder, "menu"); 
	button 		= gtk_builder_get_object(builder, "button"); 
	error			= gtk_builder_get_object(builder, "error");

	// dialogue window
	dialog		= gtk_builder_get_object(builder, "dialog");
	vbox			= gtk_builder_get_object(builder, "vbox");
	b_box			= gtk_builder_get_object(builder, "b_box");
	d_none		= gtk_builder_get_object(builder, "d_none");
	d_quit		= gtk_builder_get_object(builder, "d_quit");
	d_label  	= gtk_builder_get_object(builder, "d_label");

	// menu 
	title_menu	= gtk_builder_get_object(builder, "title_menu");
	m_file		= gtk_builder_get_object(builder, "m_file");
	file			= gtk_builder_get_object(builder, "file");
	m_quit 		= gtk_builder_get_object(builder, "m_quit");
	m_help		= gtk_builder_get_object(builder, "m_help");
	help			= gtk_builder_get_object(builder, "help");
	m_about		= gtk_builder_get_object(builder, "m_about");

	// about window
	about			= gtk_builder_get_object(builder, "about");
	hbox			= gtk_builder_get_object(builder, "hbox");
	about_text	= gtk_builder_get_object(builder, "about_text");
	about_close	= gtk_builder_get_object(builder, "about_close");

	gtk_combo_box_set_active(GTK_COMBO_BOX(menu), 0);
	gtk_window_set_transient_for(GTK_WINDOW(dialog), GTK_WINDOW(window));
	gtk_window_set_transient_for(GTK_WINDOW(about), GTK_WINDOW(window));

	run_struct rs;
	rs.menu = menu;
	rs.label = error;
	rs.dialog = dialog;

	g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);
	g_signal_connect(button, "clicked", G_CALLBACK(run_menu), &rs);
	g_signal_connect(d_quit, "clicked", G_CALLBACK(hide_window), dialog);
	g_signal_connect(m_quit, "activate", G_CALLBACK(gtk_main_quit), NULL); // activate used for menu bar items 
	g_signal_connect(m_about, "activate", G_CALLBACK(show_window), about);
	g_signal_connect(about_close, "clicked", G_CALLBACK(hide_window), about);

	gtk_main();

	return 0;
}

void run_menu(GtkWidget *widget, run_struct *data)
{
	gtk_widget_hide(GTK_WIDGET(data->label)); // so the error goes away on subsequent clicks
	if(*(gtk_combo_box_get_active_id(GTK_COMBO_BOX(data->menu))) == '0')
		print_hello();
	else if(*(gtk_combo_box_get_active_id(GTK_COMBO_BOX(data->menu))) == '1')
		bench();
	else if(*(gtk_combo_box_get_active_id(GTK_COMBO_BOX(data->menu))) == '2')
		gtk_main_quit();
	else if(*(gtk_combo_box_get_active_id(GTK_COMBO_BOX(data->menu))) == '3')
		gtk_widget_show(GTK_WIDGET(data->dialog));
	else
		gtk_widget_show(GTK_WIDGET(data->label));
}

void print_hello()
{
	std::cout << "Hello World!\n";
}

void bench()
{
	for(int i = 0; i < 300000000; ++i)
		sqrt(rand());
}

// needed for G_CALLBACK
void hide_window(GtkWidget *widget, gpointer data)
{
	gtk_widget_hide(GTK_WIDGET(data));
}

void show_window(GtkWidget *widget, gpointer data)
{
	gtk_widget_show(GTK_WIDGET(data));
}
