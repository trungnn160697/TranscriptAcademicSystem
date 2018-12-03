#include <gtk/gtk.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


 GtkBuilder      *builder; 
void on_window_destroy (GtkWidget *object, gpointer user_data)
{
    gtk_main_quit ();
}


void showFormLogin(){
    GtkWidget       *window; 
    builder = gtk_builder_new ();
    gtk_builder_add_from_file (builder, "form-login.glade", NULL);
    window = GTK_WIDGET (gtk_builder_get_object (builder, "window1"));
    gtk_builder_connect_signals (builder, NULL);

    g_object_unref (G_OBJECT (builder));

    gtk_widget_show (window);                
    gtk_main ();
}
void p(GtkWidget *widget, gpointer *gp){
    GtkWidget       *widget1;
      widget1 = GTK_WIDGET (gtk_builder_get_object (builder, "id_student"));
    char * username = gtk_entry_get_text(GTK_ENTRY(widget));
    printf("%s\n",username);
}
void getIdAndPassword(){
       
      
       GtkWidget * loginButton = GTK_WIDGET (gtk_builder_get_object (builder, "button_login"));
       g_signal_connect(loginButton, "clicked", G_CALLBACK(p),NULL);
       

}



int main (int argc, char *argv[])
{
    gtk_init (&argc, &argv);
    showFormLogin();
    return (0);
}