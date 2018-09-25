#include <gtkmm/button.h>
#include <gtkmm/togglebutton.h>
#include <iostream>
#include <string.h>
#include <gtkmm.h>

#include "esp_specific.h"
#include "paths.hpp"


Gtk::ToggleButton *build_toggle_button, *flash_toggle_button;

Gtk::Entry *device_port_entry;
Gtk::ComboBox *device_chip_cbox;

Gtk::Label *task_label;
Gtk::Spinner *task_spiner;
Gtk::Image *task_status_image;

std::string device_port, device_chip;   

EspSpecific::EspSpecific(Glib::RefPtr<Gtk::Builder> refBuilder)
{
    EspSpecific::build_button = nullptr;
    EspSpecific::flash_button = nullptr;

    build_toggle_button = nullptr;
    flash_toggle_button = nullptr;

    device_chip_cbox = nullptr;
    device_port_entry = nullptr;

    task_label = nullptr; 
    task_spiner = nullptr;

    task_status_image = nullptr;

	device_chip = "ESP8266";
    device_port = "/dev/ttyUSB0";

    refBuilder -> get_widget("BuildButton_Main", EspSpecific::build_button);
    if(build_button)
    {
        EspSpecific::build_button -> signal_clicked().connect(sigc::ptr_fun(EspSpecific::build_button_clicked));
        //EspSpecific::build_button -> set_sensitive(false);
    }

    refBuilder -> get_widget("FlashButton_Main", EspSpecific::flash_button);
    {
        EspSpecific::flash_button -> signal_clicked().connect(sigc::ptr_fun(EspSpecific::flash_button_clicked));
        EspSpecific::flash_button -> set_sensitive(false);
    }

    refBuilder -> get_widget("AllForBuildTButton_Main", build_toggle_button);
    refBuilder -> get_widget("AllForFlashTButton_Main", flash_toggle_button);

    refBuilder -> get_widget("DeviceChipComboBox_Main", device_chip_cbox);
    if(device_chip_cbox)
    {
        device_chip_cbox -> signal_changed().connect(sigc::ptr_fun(EspSpecific::device_chip_changed));
    }

    refBuilder -> get_widget("PortEntry_Main", device_port_entry);
    if(device_port_entry)
    {
        device_port_entry -> signal_changed().connect(sigc::ptr_fun(EspSpecific::device_port_changed));
    }

    refBuilder -> get_widget("TaskLabel_Main", task_label);
    if(task_label)
        task_label -> set_text("Instantiated!");

    refBuilder -> get_widget("TaskSpinner_Main", task_spiner);
    if(task_spiner)
        task_spiner -> stop();

    refBuilder -> get_widget("TaskStatusImg_Main", task_status_image);
    if(task_status_image)
        task_status_image -> set("../img/utilities-system-monitor-symbolic.svg");
    
    set_path(ESP8266_IDF_PATH);
}

EspSpecific::~EspSpecific()
{
    delete build_button;
    delete flash_button;
    delete build_toggle_button;
    delete flash_toggle_button;
}

void EspSpecific::build_button_clicked()
{
    if(EspSpecific::allForBuildPressed())
        std::cout << "The build button has been clicked and all is active" << std::endl;
    else 
        std::cout << "The build button has been clicked and all is inactive" << std::endl;  
}

void EspSpecific::flash_button_clicked()
{

    if(EspSpecific::allForFlashPressed())
        std::cout << "The flash button has been clicked and all is active" << std::endl;
    else 
        std::cout << "The flash button has been clicked and all is inactive" << std::endl;
}

void EspSpecific::device_chip_changed()
{
    if(device_chip_cbox -> get_active_row_number())
        device_chip = "ESP32";
    else
        device_chip = "ESP8266";

    std::cout << "Current device: " << device_chip << std::endl;  
}

void EspSpecific::device_port_changed()
{
    device_port = device_port_entry -> get_text();

    std::cout << "Current port: " << device_port << std::endl; 
}



bool EspSpecific::allForBuildPressed()
{ 
    return build_toggle_button -> get_active();
}

bool EspSpecific::allForFlashPressed()
{
    return flash_toggle_button -> get_active();
}

void EspSpecific::set_path(std::string path) const
{
    std::string command = "export " + path;

    std::cout << command << std::endl;
    system(command.c_str());
}