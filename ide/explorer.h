/******************************************************
* Compile this file with:
*		 g++ program.cc -o program `pkg-config --cflags --libs gtkmm-3.0`
*
* File name:  explorer.h
* Author: Guillermo Gil Rodríguez
* Date:
*
*******************************************************/

#ifndef __EXPLORER_H__
#define __EXPLORER_H__

#include <string>
#include <gtkmm.h>
#include <gtkmm/image.h>
#include <gtk/gtk.h>
class Explorer
{
	public:
		Explorer(Glib::RefPtr<Gtk::Builder> refBuilder);
		virtual ~Explorer();
	
		class ModelColumns : public Gtk::TreeModel::ColumnRecord	// Create a class to manage columns 
  		{
			public:
				Gtk::TreeModelColumn<Glib::RefPtr<Gdk::Pixbuf>> m_col_ticon; 
				Gtk::TreeModelColumn<Glib::ustring> m_col_name;

				ModelColumns() 		// Constructor
				{
					add(m_col_ticon); 	// This add "objects" icons to a new tree view column
					add(m_col_name);	// This add "objects" names to a new tree view column
				}
		};

		ModelColumns m_Columns; /


		void add_tree(std::string path);
	private:
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
		

		// Methots
};


#endif
