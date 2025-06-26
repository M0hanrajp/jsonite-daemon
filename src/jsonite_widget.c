#include "jsonite_widget.h"

void handle_create_window(
            ComJsoniteDaemonKonfabulatorWidget *object,
            GDBusMethodInvocation *invocation,
            const gchar *arg_title,
            const gchar *arg_name,
            guint arg_width,
            guint arg_height) {

    /* TODO: add the data to database and then send complete invocation
     * currently the entered data is logged
     */
    typedef struct create_window {
        const gchar *arg_title;
        const gchar  *arg_name;
              guint  arg_width;
              guint arg_height;
    } create_window;

    //copy the arguments to struct
    create_window args = {.arg_title  = arg_title, .arg_name   =  arg_name,
                          .arg_width  = arg_width, .arg_height = arg_height};

    // build json
    JsonBuilder *builder = json_builder_new();
    json_builder_begin_object (builder);
    json_builder_set_member_name(builder, "window");// window: {
    json_builder_begin_object(builder);
    json_builder_set_member_name(builder, "title"); // title: (s),
    json_builder_add_string_value(builder, args.arg_title);
    json_builder_set_member_name(builder, "name");  // name: (s),
    json_builder_add_string_value(builder, args.arg_name);
    json_builder_set_member_name(builder, "width"); // width: (i),
    json_builder_add_int_value(builder, args.arg_width);
    json_builder_set_member_name(builder, "height");// height:(i),
    json_builder_add_int_value(builder, args.arg_height);
    json_builder_end_object(builder);               // }
    json_builder_end_object(builder);
    JsonGenerator *generator = json_generator_new ();
    JsonNode *root = json_builder_get_root (builder);
    json_generator_set_root (generator, root);
    json_generator_set_pretty(generator, PRETTY_PRINT_JSON_TRUE);
    gchar *json_object = json_generator_to_data (generator, NULL);

    printf("[%s] update data in DB\n", __func__);
    printf("%s\n", json_object);

    g_object_unref(builder);
    g_object_unref(generator);
    json_node_free(root);
    free(json_object);

    com_jsonite_daemon_konfabulator_widget_complete_create_window(object, invocation);
}

void handle_create_image(
            ComJsoniteDaemonKonfabulatorWidget *object,
            GDBusMethodInvocation *invocation,
            const gchar *arg_src,
            const gchar *arg_name,
            gint arg_hOffset,
            gint arg_vOffset,
            const gchar *arg_alignment) {

    /* TODO: add the data to database and then send complete invocation
     * currently the entered data is logged
     */
    typedef struct create_image {
        const gchar    *arg_src;
        const gchar   *arg_name;
              gint  arg_hOffset;
              guint arg_vOffset;
        const gchar *arg_alignment;
    } create_image;

    //copy the arguments to struct
    create_image args = {.arg_src = arg_src, .arg_name = arg_name, .arg_hOffset = arg_hOffset, 
                         .arg_vOffset = arg_vOffset, .arg_alignment = arg_alignment};

    // build json
    JsonBuilder *builder = json_builder_new();
    json_builder_begin_object (builder);
    json_builder_set_member_name(builder, "image");     // image: {
    json_builder_begin_object(builder);
    json_builder_set_member_name(builder, "src");       // src: (s),
    json_builder_add_string_value(builder, args.arg_src);
    json_builder_set_member_name(builder, "name");      // name: (s),
    json_builder_add_string_value(builder, args.arg_name);
    json_builder_set_member_name(builder, "hOffset");   // hOffset: (i),
    json_builder_add_int_value(builder, args.arg_hOffset);
    json_builder_set_member_name(builder, "vOffset");   // vOffset: (i),
    json_builder_add_int_value(builder, args.arg_vOffset);
    json_builder_set_member_name(builder, "alignment"); // alignment:(s),
    json_builder_add_string_value(builder, args.arg_alignment);
    json_builder_end_object(builder);                   // }
    json_builder_end_object(builder);
    JsonGenerator *generator = json_generator_new ();
    JsonNode *root = json_builder_get_root (builder);
    json_generator_set_root (generator, root);
    json_generator_set_pretty(generator, PRETTY_PRINT_JSON_TRUE);
    gchar *json_object = json_generator_to_data (generator, NULL);

    printf("[%s] update data in DB\n", __func__);
    printf("%s\n", json_object);

    g_object_unref(builder);
    g_object_unref(generator);
    json_node_free(root);
    free(json_object);

    com_jsonite_daemon_konfabulator_widget_complete_create_image(object, invocation);
}

void handle_create_text(
            ComJsoniteDaemonKonfabulatorWidget *object,
            GDBusMethodInvocation *invocation,
            const gchar *arg_data,
            guint arg_size,
            const gchar *arg_style,
            const gchar *arg_name,
            gint arg_hOffset,
            gint arg_vOffset,
            const gchar *arg_alignment) {

    /* TODO: add the data to database and then send complete invocation
     * currently the entered data is logged
     */
    typedef struct create_text {
        const gchar    *arg_data;
              guint     arg_size;
        const gchar   *arg_style;
        const gchar    *arg_name;
              gint  arg_hOffset;
              gint  arg_vOffset;
        const gchar *arg_alignment;
    } create_text;

    //copy the arguments to struct
    create_text args = {.arg_data = arg_data, .arg_size = arg_size, .arg_style = arg_style,
                        .arg_name = arg_name, .arg_hOffset = arg_hOffset, 
                        .arg_vOffset = arg_vOffset, .arg_alignment = arg_alignment};

    // build json
    JsonBuilder *builder = json_builder_new();
    json_builder_begin_object (builder);
    json_builder_set_member_name(builder, "text");  // text: {
    json_builder_begin_object(builder);
    json_builder_set_member_name(builder, "data");      // data: (s),
    json_builder_add_string_value(builder, args.arg_data);
    json_builder_set_member_name(builder, "size");      // size: (s),
    json_builder_add_int_value(builder, args.arg_size);
    json_builder_set_member_name(builder, "style");     // style: (s),
    json_builder_add_string_value(builder, args.arg_style);
    json_builder_set_member_name(builder, "name");      // name: (s),
    json_builder_add_string_value(builder, args.arg_name);
    json_builder_set_member_name(builder, "hOffset");   // hOffset: (i),
    json_builder_add_int_value(builder, args.arg_hOffset);
    json_builder_set_member_name(builder, "vOffset");   // vOffset: (i),
    json_builder_add_int_value(builder, args.arg_vOffset);
    json_builder_set_member_name(builder, "alignment");// alignment:(s),
    json_builder_add_string_value(builder, args.arg_alignment);
    json_builder_end_object(builder);               // }
    json_builder_end_object(builder);
    JsonGenerator *generator = json_generator_new ();
    JsonNode *root = json_builder_get_root (builder);
    json_generator_set_root (generator, root);
    json_generator_set_pretty(generator, PRETTY_PRINT_JSON_TRUE);
    gchar *json_object = json_generator_to_data (generator, NULL);

    printf("[%s] update data in DB\n", __func__);
    printf("%s\n", json_object);

    g_object_unref(builder);
    g_object_unref(generator);
    json_node_free(root);
    free(json_object);

    com_jsonite_daemon_konfabulator_widget_complete_create_text(object, invocation);
}
