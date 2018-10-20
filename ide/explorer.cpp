/******************************************************
* Compile this file with:
*		 g++ program.cc -o program `pkg-config --cflags --libs gtkmm-3.0`
*
* File name:  explorer.cpp
* Author: Guillermo Gil Rodríguez
* Date:
*
*******************************************************/

#include "explorer.h"
#include "dir.h"
#include <string>
#include <vector>
#include <gtkmm.h>

using namespace std;

Dir dir;

Gtk::Window *ParentWindow;

Gtk::TreeView *TreeView;
Gtk::FileChooserDialog *ChooseDialog;
Gtk::Button *CDCancelButton, *CDSelectButton;

Gtk::Button *OpenProjectButton;

string CurrentProjectLocation = "/";
vector<string> Projects;

Explorer::Explorer(Glib::RefPtr<Gtk::Builder> refBuilder)
{
    refBuilder -> get_widget("ProjectExplorerTreeView_Main", TreeView);
    if(TreeView)
    {
        refBuilder -> get_widget("ProjectExplorerTreeView_Main", TreeView);
        Glib::RefPtr<Gdk::Pixbuf> folder_icon = Gdk::Pixbuf::create_from_file("img/folder-symbolic.svg");
        Glib::RefPtr<Gtk::TreeStore> m_refTreeModel;

        m_refTreeModel = Gtk::TreeStore::create(Explorer::m_Columns);
        TreeView -> set_model(m_refTreeModel);

        TreeView -> append_column("", m_Columns.m_col_ticon);           // Set column for icons
        TreeView -> append_column("File name", m_Columns.m_col_name);   // Set column for names called "File name"

        Gtk::TreeModel::Row row = *(m_refTreeModel -> append());        // Add a Titles row
        row[m_Columns.m_col_name] = "This is a folder project";         // Add a "name" in column "File name"
        row[m_Columns.m_col_ticon] = folder_icon;                       // Add a icon for the element in the row (for this line has been added a folder icon)

        row = *(m_refTreeModel -> append());                            // Add last row objects to the firs row

    // Start signal function assigment

        refBuilder -> get_widget("ProjectChooseDialog", ChooseDialog);
        if(ChooseDialog)
        {
            refBuilder -> get_widget("MainWindow", ParentWindow);
            ChooseDialog -> set_transient_for(*ParentWindow);
            ChooseDialog -> set_modal(true);

            refBuilder -> get_widget("ChooseDialogCancelButton", CDCancelButton);
            if(CDCancelButton)
                CDCancelButton -> signal_clicked().connect(sigc::ptr_fun(Explorer::cd_cancel_button_clicked));
            

            refBuilder -> get_widget("ChooseDialogSelectButton", CDSelectButton);
            if(CDSelectButton)
                CDSelectButton -> signal_clicked().connect(sigc::ptr_fun(Explorer::cd_select_button_clicked));    
            

            ChooseDialog -> set_visible(false);
        }
        
        refBuilder -> get_widget("OpenProjectButton_Main",OpenProjectButton);
        if(refBuilder)
            OpenProjectButton -> signal_clicked().connect(sigc::ptr_fun(Explorer::open_project_button_clicked));
        
    }
}

Explorer::~Explorer(){}


void Explorer::add_tree(string path)
{
    dir.set_path(path);

    int num_files = dir.get_num_files();

    // if no error

    vector<string> files = dir.get_filenames();

    for(int i = 0; i < num_files; ++i)
        cout << "File num " << i << " --> " << files[i] << endl;


}

void Explorer::open_project_button_clicked()
{
    ChooseDialog -> set_visible(true);
}

void Explorer::cd_cancel_button_clicked()
{
    ChooseDialog -> close();
}

void Explorer::cd_select_button_clicked()
{

    Projects = ChooseDialog -> get_filenames();
    for(unsigned i = 0; i < Projects.size(); ++i)
        cout << "Project path " << i << " = " << Projects[i] << endl;

    cout << endl;

    CurrentProjectLocation = Projects[0];
    cout << "Current project = " << CurrentProjectLocation << endl;
}