#include "jsonite_widget.h"
#include "jsonite_calculator.h"

/* Custom log handler that removes extra newlines */
static void
jsonite_daemon_log_handler(const gchar      *log_domain,
                           GLogLevelFlags   log_level,
                           const gchar      *message,
                           gpointer         user_data) {

    gchar *msg = g_strdup(message);
    while (msg[0] && msg[strlen(msg)-1] == '\n')
        msg[strlen(msg)-1] = '\0';

    fprintf (stderr, "[%s] %s\n", log_domain, msg);
    g_free(msg);
}


void on_bus_acquired_handler(GDBusConnection* connection,
                             const gchar* name,
                             gpointer user_data) {

    printf("[%s]: Bus acquisition complete\n", __func__);

    // jsonite calculator
    ComJsoniteDaemonCalculator *calculator_skeleton = com_jsonite_daemon_calculator_skeleton_new();
    g_signal_connect(calculator_skeleton, "handle-add",      G_CALLBACK(handle_add_method),      NULL);
    g_signal_connect(calculator_skeleton, "handle-divide",   G_CALLBACK(handle_divide_method),   NULL);
    g_signal_connect(calculator_skeleton, "handle-subtract", G_CALLBACK(handle_subtract_method), NULL);
    g_signal_connect(calculator_skeleton, "handle-multiply", G_CALLBACK(handle_multiply_method), NULL);

    GError *calculator_err = NULL;
    if(!g_dbus_interface_skeleton_export(G_DBUS_INTERFACE_SKELETON(calculator_skeleton),
                                         connection,
                                         OBJECT_PATH,
                                         &calculator_err)) {
        printf("[%s]: Failed to export dbus interface %s\n", __func__, calculator_err->message);
        exit(-1);
    }
    // jsonite widget
    ComJsoniteDaemonKonfabulatorWidget *widget_skeleton = com_jsonite_daemon_konfabulator_widget_skeleton_new();
    g_signal_connect(widget_skeleton, "handle-create-window", G_CALLBACK(handle_create_window), NULL);
    g_signal_connect(widget_skeleton, "handle-create-image",  G_CALLBACK(handle_create_image),  NULL);
    g_signal_connect(widget_skeleton, "handle-create-text",   G_CALLBACK(handle_create_text),   NULL);

    GError *widget_err = NULL;
    if(!g_dbus_interface_skeleton_export(G_DBUS_INTERFACE_SKELETON(widget_skeleton),
                                         connection,
                                         OBJECT_PATH,
                                         &widget_err)) {
        printf("[%s]: Failed to export dbus interface %s\n", __func__, widget_err->message);
        exit(-1);
    }
    printf("[%s]: Methods are registered with dbus interface\n", __func__);
}

void on_name_acquired_handler(GDBusConnection* connection,
                              const gchar* name,
                              gpointer user_data) {

    printf("[%s]: Name acquisition complete, daemon active..\n", __func__);
}

void on_name_lost_handler(GDBusConnection* connection,
                          const gchar* name,
                          gpointer user_data) {

        printf("[%s]: Bus name Lost!\n", __func__);
        //TODO: using registrationID & InterfaceInfo gracefully close
}

int main(void) {

    g_log_set_default_handler(jsonite_daemon_log_handler, NULL);

    GMainLoop * loop = g_main_loop_new(NULL, FALSE);
    guint dbus_id = 0;
    dbus_id = g_bus_own_name(G_BUS_TYPE_SESSION,
                             BUS_NAME,
                             G_BUS_NAME_OWNER_FLAGS_DO_NOT_QUEUE,
                             on_bus_acquired_handler,
                             on_name_acquired_handler,
                             on_name_lost_handler,
                             NULL,
                             NULL);
    if(dbus_id == 0) {
        printf("[%s]: failed to initialize daemon [Bus name: %s]\n", 
                __func__,
                BUS_NAME);
        exit(-1);
    }
    printf("[%s]: g_main_loop_run is invoked\n", __func__);
    g_main_loop_run(loop);

    g_bus_unown_name(dbus_id);
    g_main_loop_unref(loop);
    return 0;
}
