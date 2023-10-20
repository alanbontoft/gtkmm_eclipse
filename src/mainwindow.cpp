#include "mainwindow.h"
#include <iostream>

using namespace std;
// using namespace sigc;

MainWindow::MainWindow()
{
    initWindow();
}

/*
    Handler for increase button click
*/
void MainWindow::on_btn_increase_click()
{
    _total++;

    show_message();
}

/*
    Handler for decrease button click
*/
void MainWindow::on_btn_decrease_click()
{
    if (_total > 0)
    {
        _total--;
        show_message();
    }
}

/*
    Handler for reset button click
*/
void MainWindow::on_btn_reset_click()
{
    if (_total != 0)
    {
        _total = 0;
        show_message();
    }

    StartThread();
}

void MainWindow::on_btn_toggle_click()
{
    cout << "Toggle State: " << _btnToggle->get_active() << endl;
}

/*
    Update label with message
*/
void MainWindow::show_message()
{
    _msg = Glib::ustring::sprintf("Total =  %d", _total);

    cout << _msg << endl;

    _messageLabel->set_text(_msg);
}

void* thread_function(void *param)
{
	int id = *(int*)param;

	while(true)
	{
		cout << "Thread " << id << " running" << endl;
		sleep(1);
	}

	return nullptr; // NULL;
}

void MainWindow::StartThread()
{
	_threadCounter++;
	Glib::ustring s = Glib::ustring::sprintf("Thread %d", _threadCounter);
	_thread = g_thread_new(s.c_str(), thread_function, &_threadCounter);
}

/*
    Initialise window and widgets
*/
void MainWindow::initWindow()
{

   _btnIncrease = new Gtk::Button("Inc");
   _btnDecrease = new Gtk::Button("Dec");
   _btnReset = new Gtk::Button("Reset");
   _messageLabel = new Gtk::Label();
   _btnToggle = new Gtk::ToggleButton("Toggle");

   _box = new Gtk::Box(Gtk::ORIENTATION_VERTICAL, 10);
   _box->set_margin_left(50);
   _box->set_margin_right(50);
   _box->set_margin_top(50);
   _box->set_margin_bottom(50);

   this->set_default_size(400, 300);
   this->set_title("Gtkmm Test");
   this->add(*_box);


//   _btnIncrease->set_size_request(100, 50);
   _btnIncrease->signal_clicked().connect(sigc::mem_fun(*this, &MainWindow::on_btn_increase_click));
   _btnIncrease->show();

   _btnDecrease->signal_clicked().connect(sigc::mem_fun(*this, &MainWindow::on_btn_decrease_click));
   _btnDecrease->show();

   _btnReset->signal_clicked().connect(sigc::mem_fun(*this, &MainWindow::on_btn_reset_click));
   _btnReset->show();

    _btnToggle->signal_clicked().connect(sigc::mem_fun(*this, &MainWindow::on_btn_toggle_click));
   _btnToggle->show();

   _messageLabel->set_size_request(100, 100);
   _messageLabel->show();

   _box->add(*_btnIncrease);
   _box->add(*_btnDecrease);
   _box->add(*_btnReset);
   _box->add(*_btnToggle);
   _box->add(*_messageLabel);
   _box->show();

   // show initial message
   show_message();
}
