#include <gtk/gtk.h>
#include "handle-event.c"




extern GtkWidget *window;
extern GtkWidget *frame;
extern GtkWidget *chatArea;
extern GtkWidget *messageInput;
extern char *you;
extern char *onlineUsers[];
extern int onlineUserCount;
GtkWidget *userListBox;

void set_size(GtkWidget * gw, int width, int height) {
	gtk_widget_set_size_request(gw, width, height);
}

void set_pos(GtkWidget * gw, int x, int y) {
	gtk_fixed_put(GTK_FIXED(frame), gw, x, y);
}

void destroySomething(GtkWidget * widget, gpointer gp) {
	gtk_widget_destroy(gp);
}



void showMessage(GtkWidget * parent , GtkMessageType type,  char * mms, char * content) {
	GtkWidget *mdialog;
	mdialog = gtk_message_dialog_new(GTK_WINDOW(parent),
	                                 GTK_DIALOG_DESTROY_WITH_PARENT,
	                                 type,
	                                 GTK_BUTTONS_OK,
	                                 "%s", mms);
	gtk_message_dialog_format_secondary_text(GTK_MESSAGE_DIALOG(mdialog), "%s",  content);
	gtk_dialog_run(GTK_DIALOG(mdialog));
	gtk_widget_destroy(mdialog);
}

void showLogin() {
	GtkWidget *loginDialog;
	loginDialog = gtk_dialog_new_with_buttons(LOGIN, GTK_WINDOW(window),
	                                        GTK_DIALOG_MODAL | GTK_DIALOG_DESTROY_WITH_PARENT, NULL, NULL);

	GtkWidget *dialog_ground = gtk_fixed_new();
	GtkWidget* tframe = gtk_frame_new(USERNAME);
	GtkWidget* bframe = gtk_frame_new(PASSWORD);
	GtkWidget* box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
	GtkWidget * loginButton =  gtk_button_new_with_label(BUTTON_LOGIN);
	GtkWidget * cancelButton = gtk_button_new_with_label(CANCEL);
	GtkWidget* inputUsername = gtk_entry_new();
	GtkWidget* inputPassword = gtk_entry_new();
	gtk_entry_set_visibility (inputPassword, FALSE);

	gtk_box_pack_start(GTK_BOX(box), loginButton, TRUE, TRUE, 2);
	gtk_box_pack_start(GTK_BOX(box), cancelButton, TRUE, TRUE, 2);

	set_size(tframe, 300, 50);
	set_size(bframe, 300, 50);
	set_size(box, 300, 50);
	set_size(loginButton, 100, 30);
	set_size(cancelButton, 100, 30);

	gtk_widget_set_margin_left(inputUsername, 2);
	gtk_widget_set_margin_right(inputUsername, 2);
	gtk_widget_set_margin_left(inputPassword, 2);
	gtk_widget_set_margin_right(inputPassword, 2);

	gtk_fixed_put(GTK_FIXED(dialog_ground), tframe, 0, 20);
	gtk_fixed_put(GTK_FIXED(dialog_ground), bframe, 0, 80);
	gtk_fixed_put(GTK_FIXED(dialog_ground), box, 0, 220);

	gtk_container_add(GTK_CONTAINER(tframe), inputUsername);
	gtk_container_add(GTK_CONTAINER(bframe), inputPassword);

	gtk_box_pack_start(GTK_BOX(gtk_dialog_get_content_area(GTK_DIALOG(loginDialog))), dialog_ground,  TRUE, TRUE, 0);
	
	GtkWidget * data_array[3];
	data_array[0] = inputUsername;
	data_array[1] = inputPassword;
	data_array[2] = loginDialog;
	g_signal_connect(loginButton, "clicked", G_CALLBACK(onLoginButtonClicked), data_array);
	g_signal_connect(cancelButton, "clicked", G_CALLBACK(destroySomething), loginDialog);
	gtk_widget_show_all(loginDialog);
	gtk_dialog_run(GTK_DIALOG(loginDialog));
	gtk_widget_destroy(loginDialog);
}












void showMainWindow(){
	// Khoi tao cua so
	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
	//gtk_window_set_default_size(GTK_WINDOW(window), -1, -1);
	gtk_window_set_title(GTK_WINDOW(window), APP_TITLE);
	gtk_window_set_resizable(GTK_WINDOW(window), FALSE);
	//Khoi tao nen
	frame = gtk_fixed_new();
	gtk_container_add(GTK_CONTAINER(window), frame);
	gtk_widget_set_margin_bottom(frame, 5);
	gtk_widget_set_margin_right(frame, 5);


	/*initCurrentUserBox(5,4);
	initPublicChannelBox(5, 94);
	initUserList(5, 154, onlineUsers, 7);
	initChatArea(120, 10);
	initMessageInput(120, 280);*/


	gtk_widget_show_all(window);

	g_signal_connect(window, "destroy", G_CALLBACK (gtk_main_quit), NULL);//Ket thuc chuong trinh khi dong cua so chinh

	gtk_main();
}