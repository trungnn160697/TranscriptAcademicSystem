#include <gtk/gtk.h>
#include <string.h>
#include <stdio.h>
#include "string-constant.c"
#include "GUI.c"




GtkWidget *window;
GtkWidget *frame;
GtkWidget *chatArea;
GtkWidget *messageInput;




int main(int argc, char const *argv[])
{
	// Khoi tao GTK
	gtk_init(&argc, &argv);
	

	showLogin();




	return 0;
}
