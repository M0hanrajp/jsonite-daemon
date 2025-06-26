#ifndef JSONITE_WIDGET_H
#define JSONITE_WIDGET_H

#include <stdio.h>
#include "gdbus_widget.h"
#include <json-glib/json-glib.h>

#define BUS_NAME "com.jsoniteDaemon"
#define OBJECT_PATH "/com/jsoniteDaemon"
#define PRETTY_PRINT_JSON_TRUE 1
#define PRETTY_PRINT_JSON_FALSE 0

void handle_create_window(
            ComJsoniteDaemonKonfabulatorWidget *object,
            GDBusMethodInvocation *invocation,
            const gchar *arg_title,
            const gchar *arg_name,
            guint arg_width,
            guint arg_height);

void handle_create_image(
            ComJsoniteDaemonKonfabulatorWidget *object,
            GDBusMethodInvocation *invocation,
            const gchar *arg_src,
            const gchar *arg_name,
            gint arg_hOffset,
            gint arg_vOffset,
            const gchar *arg_alignment);

void handle_create_text(
            ComJsoniteDaemonKonfabulatorWidget *object,
            GDBusMethodInvocation *invocation,
            const gchar *arg_data,
            guint arg_size,
            const gchar *arg_style,
            const gchar *arg_name,
            gint arg_hOffset,
            gint arg_vOffset,
            const gchar *arg_alignment);
#endif
