#include "jsonite_calculator.h"

int *parse_arg_json_request(const gchar *json_request) {

    GError *add_method_err = NULL;
    gssize json_request_len = strlen(json_request);
    if(json_request_len < 1) {
        printf("[%s]: Invalid argument size, abort\n", __func__);
        exit(-1);
    }
    JsonParser *parser = json_parser_new();
    json_parser_load_from_data(parser, json_request, json_request_len,
                                                     &add_method_err);
    if(add_method_err) {
        printf("[%s]: %s\n", __func__, add_method_err->message);
        exit(-1);
    }
    JsonNode   *root =  json_parser_get_root(parser);
    JsonObject *obj  =  json_node_get_object(root);
    // TODO: parse members int, float based on method invoked
    gint64     argA  =  json_object_get_int_member(obj, "a");
    gint64     argB  =  json_object_get_int_member(obj, "b");

    int *args = calloc(2, sizeof(int));
    args[0] = argA;
    args[1] = argB;

    g_object_unref(parser);
    return args;
}

gchar *build_arg_json_response(gdouble method_result, const gchar *method_name) {
    JsonBuilder *builder = json_builder_new();
    json_builder_begin_object(builder);

    gchar *arg_json_response = calloc(128, sizeof(char));
    if(arg_json_response == NULL) {
        printf("[%s] Failed to allocate memory to response string\n", __func__);
    }
    sprintf(arg_json_response, "[%s] result", method_name);
    json_builder_set_member_name(builder, arg_json_response);
    json_builder_add_int_value(builder, method_result);
    json_builder_end_object(builder);
    free(arg_json_response);

    JsonGenerator *generator = json_generator_new();
    JsonNode *root_arg_json_response = json_builder_get_root(builder);
    json_generator_set_root(generator, root_arg_json_response);
    /* Set pretty print to true or false
     * ('{\n  "[handle_add_method] 10 + 32 " : 42\n}',) pretty print true
     * ('{"[handle_add_method] 10 + 32 ":42}',) pretty print false
     */
    json_generator_set_pretty(generator, PRETTY_PRINT_JSON_FALSE);
    arg_json_response = json_generator_to_data(generator, NULL);

    g_object_unref(builder);
    g_object_unref(generator);
    json_node_free(root_arg_json_response);
    return arg_json_response;
}

void handle_add_method(ComJsoniteDaemonCalculator *object,
                       GDBusMethodInvocation *invocation,
                       const gchar *arg_json_request,
                       gpointer user_data) {

    gssize json_request_len = strlen(arg_json_request);
    if(json_request_len < 1) {
        printf("[%s]: Invalid argument size, abort\n", __func__);
        exit(-1);
    }

    int *operand = parse_arg_json_request(arg_json_request);
    gint64   sum = operand[0] + operand[1];

    const gchar *arg_json_response = build_arg_json_response(sum, __func__);
    com_jsonite_daemon_calculator_complete_add(object,
                                               invocation,
                                               arg_json_response);
    free(operand);
    free((void *)arg_json_response);
}

void handle_divide_method(ComJsoniteDaemonCalculator *object,
                          GDBusMethodInvocation *invocation,
                          const gchar *arg_json_request,
                          gpointer user_data) {

    gssize json_request_len = strlen(arg_json_request);
    if(json_request_len < 1) {
        printf("[%s]: Invalid argument size, abort\n", __func__);
        exit(-1);
    }

    int   *operand = parse_arg_json_request(arg_json_request);
    // TODO: handle divide by 0 case
    gdouble divide = (gdouble)operand[0] / (gdouble)operand[1];

    const gchar *arg_json_response = build_arg_json_response(divide, __func__);
    com_jsonite_daemon_calculator_complete_divide(object,
                                                  invocation,
                                                  arg_json_response);
    free(operand);
    free((void *)arg_json_response);
}

void handle_multiply_method(ComJsoniteDaemonCalculator *object,
                            GDBusMethodInvocation *invocation,
                            const gchar *arg_json_request,
                            gpointer user_data) {

    gssize json_request_len = strlen(arg_json_request);
    if(json_request_len < 1) {
        printf("[%s]: Invalid argument size, abort\n", __func__);
        exit(-1);
    }

    int    *operand = parse_arg_json_request(arg_json_request);
    gint64 multiply = operand[0] * operand[1];

    const gchar *arg_json_response = build_arg_json_response(multiply, __func__);
    com_jsonite_daemon_calculator_complete_multiply(object,
                                                    invocation,
                                                    arg_json_response);
    free(operand);
    free((void *)arg_json_response);
}

void handle_subtract_method(ComJsoniteDaemonCalculator *object,
                            GDBusMethodInvocation *invocation,
                            const gchar *arg_json_request,
                            gpointer user_data) {

    gssize json_request_len = strlen(arg_json_request);
    if(json_request_len < 1) {
        printf("[%s]: Invalid argument size, abort\n", __func__);
        exit(-1);
    }

    int    *operand = parse_arg_json_request(arg_json_request);
    gint64 subtract = operand[0] - operand[1];

    const gchar *arg_json_response = build_arg_json_response(subtract, __func__);
    com_jsonite_daemon_calculator_complete_subtract(object,
                                                    invocation,
                                                    arg_json_response);
    free(operand);
    free((void *)arg_json_response);
}
