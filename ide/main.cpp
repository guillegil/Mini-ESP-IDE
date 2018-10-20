/******************************************************
* Compile this file with:
*		 g++ program.cc -o program `pkg-config --cflags --libs gtkmm-3.0`
*
* File name:  main.cpp
* Author: Guillermo Gil Rodríguez
* Date:
*
*******************************************************/

#include "esp_specific.hpp"
#include "explorer.h"
#include <stdlib.h>
#include <iostream>
#include <gtkmm.h>


Gtk::Window *pWindow = nullptr;
void on_button_clicked();	

int main (int   argc, char *argv[])
{

    //Glib::RefPtr<Gtk::Builder> builder = Gtk::Builder::create_from_file("esp_builder.glade");
	
   auto app = Gtk::Application::create(argc, argv, "org.gtkmm.example");
 
	auto refBuilder = Gtk::Builder::create();
	try
	{
		refBuilder -> add_from_file("../interface/main.glade");
	}
	catch(const Glib::FileError &ex)
	{
		std::cerr << "FileError: " << ex.what() << std::endl;
		return 1;
	}
	catch(const Glib::MarkupError& ex)
	{
    	std::cerr << "MarkupError: " << ex.what() << std::endl;
    	return 1;
	}
	catch(const Gtk::BuilderError& ex)
	{
		std::cerr << "BuilderError: " << ex.what() << std::endl;
    	return 1;
	}

	Explorer exp(refBuilder);
	EspSpecific esp_device(refBuilder);
 

	refBuilder->get_widget("MainWindow", pWindow);
	if(pWindow)
	{
		Gtk::Button *pButton = nullptr;
		refBuilder -> get_widget("NewFileButton_Main", pButton);
		if(pButton)
		{
			pButton->signal_clicked().connect(sigc::ptr_fun(on_button_clicked));
		}		


		app -> run(*pWindow);
	}

	delete pWindow;
	return 0;
}


void on_button_clicked()
{
	std::cout << "New file created" << std::endl;
}

