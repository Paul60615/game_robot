/*
 * Robot_Timer.cpp
 *
 *  Created on: Dec 24, 2015
 *      Author: zhangyalei
 */

#include "Robot_Timer.h"
#include "Robot_Manager.h"

Robot_Timer_Handler::Robot_Timer_Handler(void) { }

Robot_Timer_Handler::~Robot_Timer_Handler(void) { }

int Robot_Timer_Handler::handle_timeout(const Time_Value &tv) {
	return ROBOT_MANAGER->push_tick(1);
}

Robot_Timer::Robot_Timer(void) { }

Robot_Timer::~Robot_Timer(void) { }

Robot_Timer *Robot_Timer::instance_;

Robot_Timer *Robot_Timer::instance(void) {
	if (instance_ == 0)
		instance_ = new Robot_Timer;
	return instance_;
}

void Robot_Timer::register_handler(void) {
	Time_Value timeout_tv(0, 10 * 1000);
	watcher_.add(&timer_handler_, EVENT_TIMEOUT, &timeout_tv);
}

void Robot_Timer::run_handler(void) {
	register_handler();
	watcher_.loop();
}

Epoll_Watcher &Robot_Timer::watcher(void) {
	return watcher_;
}
