#ifndef MLSERVER_ROUTES_HPP
#define MLSERVER_ROUTES_HPP

#include "MLServer.hpp"

int getPORTenv();

bool checkCustomheader(std::string_view header);

bool checkContentlength(std::string_view strn);

void modelpredToString(int classes, std::string &values);
#endif