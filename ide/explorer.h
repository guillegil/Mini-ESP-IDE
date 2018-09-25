/******************************************************
* Compile this file with:
*		 g++ `pkg-config --cflags gtk+-3.0` -o gtk_main gtk_main.cpp `pkg-config --libs gtk+-3.0`
*
* File name: 
* Author:
* Date:
*
*******************************************************/

#ifndef __EXPLORER_H__
#define __EXPLORER_H__



#include <gtkmm/treeview.h>



class Explorer : public Gtk::TreeView
{
	public:
		Explorer();
		virtual ~Explorer();
	
	protected:
		// Signal Handlers

		void new_file_button_clicked();
		void new_folder_button_clicked();
		void delete_selected_button_clicked();
		void save_button_clicked();
		void save_as_button_clicked();
		void git_button_clicked();
		void new_project_button_clicked();
		void open_project_button_clicked();
		void close_project_button_clicked();		

};


#endif
