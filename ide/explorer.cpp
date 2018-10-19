#include "explorer.h"
#include "dir.h"
#include <string>
#include <vector>
#include <gtkmm.h>
#include <gtkmm/treeview.h>
#include <gtkmm/treemodelcolumn.h>
#include <gdkmm/pixbuf.h>

using namespace std;

Dir dir;
Gtk::TreeView *treeview;


Explorer::Explorer(Glib::RefPtr<Gtk::Builder> refBuilder)
{
    refBuilder -> get_widget("ProjectExplorerTreeView_Main", treeview);
    if(refBuilder)
    {
        Glib::RefPtr<Gdk::Pixbuf> folder_icon = Gdk::Pixbuf::create_from_file("img/folder-symbolic.svg");
        Glib::RefPtr<Gtk::TreeStore> m_refTreeModel;

        m_refTreeModel = Gtk::TreeStore::create(Explorer::m_Columns);
        treeview -> set_model(m_refTreeModel);

        treeview -> append_column("", m_Columns.m_col_ticon);           // Set column for icons
        treeview -> append_column("File name", m_Columns.m_col_name);   // Set column for names called "File name"

        Gtk::TreeModel::Row row = *(m_refTreeModel -> append());        // Add a Titles row
        row[m_Columns.m_col_name] = "This is a folder project";         // Add a "name" in column "File name"
        row[m_Columns.m_col_ticon] = folder_icon;                       // Add a icon for the element in the row (for this line has been added a folder icon)

        row = *(m_refTreeModel -> append());                            // Add last row objects to the firs row
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