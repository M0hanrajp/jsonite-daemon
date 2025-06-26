#ifndef JSONITE_CALCULATOR_H
#define JSONITE_CALCULATOR_H

#include <stdio.h>
#include "gdbus_calculator.h"
#include <json-glib/json-glib.h>

#define BUS_NAME "com.jsoniteDaemon"
#define OBJECT_PATH "/com/jsoniteDaemon"
#define PRETTY_PRINT_JSON_TRUE  1
#define PRETTY_PRINT_JSON_FALSE 0


void handle_add_method(ComJsoniteDaemonCalculator *object,
                       GDBusMethodInvocation *invocation,
                       const gchar *arg_json_request,
                       gpointer user_data);

void handle_divide_method(ComJsoniteDaemonCalculator *object,
                          GDBusMethodInvocation *invocation,
                          const gchar *arg_json_request,
                          gpointer user_data);

void handle_multiply_method(ComJsoniteDaemonCalculator *object,
                            GDBusMethodInvocation *invocation,
                            const gchar *arg_json_request,
                            gpointer user_data);

void handle_subtract_method(ComJsoniteDaemonCalculator *object,
                            GDBusMethodInvocation *invocation,
                            const gchar *arg_json_request,
                            gpointer user_data);

#endif
