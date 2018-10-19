/******************************************************
* Compile this file with:
*		 g++ `pkg-config --cflags gtk+-3.0` -o gtk_main gtk_main.cpp `pkg-config --libs gtk+-3.0`
*
* File name: esp_specific.hpp
* Author: Guillermo Gil Rodríguez
* Date: 26-Sep-2018
*
*******************************************************/

#ifndef __ESP_SPECIFIC_HPP__
#define __ESP_SPECIFIC_HPP__



//#include <gtkmm/button.h>
//#include <gtkmm/togglebutton.h>
#include <gtkmm.h>
#include <gtkmm/button.h>
#include <gtkmm/togglebutton.h>
#include <gtkmm/combobox.h>
#include <gtkmm/entry.h>
#include <string.h>
#include "paths.hpp"

class EspSpecific
{
	public:
		EspSpecific(Glib::RefPtr<Gtk::Builder> refBuilder);
		virtual ~EspSpecific();
		
	protected:
		// Signal Handlers
		
		static void flash_button_clicked();
		static void build_button_clicked();
		
		static void device_chip_changed();
		static void device_port_changed();			

		void run_build();
		// Widgets	

		Gtk::Button *build_button, *flash_button;
			
		// Other functions

		static bool allForBuildPressed();
		static bool allForFlashPressed();

			//string getChip();
			//string getPort();
	private:
		void set_path(std::string path) const;
};


#endif //__ESP_SPECIFIC_H__
