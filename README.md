<h1 align="center"> Jsonite Daemon</h1>

**Jsonite Daemon** is a lightweight D-Bus service built with GDBus and JSON-GLib. It provides a modular interface for UI-driven configuration and control of widget-based components using a structured JSON payload format.

- The daemon provides two examples, calculator & [Konfabulator Widget](https://json.org/example.html#:~:text=%3Cwidget%3E-,%3Cdebug%3Eon%3C/debug%3E,-%3Cwindow%20title%3D%22Sample), please use `gdbus introspect` to check the methods and properties offered by the daemon.
- _Currently the repository does not come with a UI application that interacts with daemon, `gdbus call` is used to test methods & properties_
- _Sqlite database will be used in future to improve persistence_

```bash
+----------------------+        D-Bus       +-----------------------+
|                      | <----------------> |                       |
|   UI Application     |                    |    jsonite-daemon     |
|                      |                    |  (GDBus + JSON-GLib)  |
|                      | -----------------> |                       |
+----------------------+  signals & calls   +-----------------------+
													   |   ^
													   v   |
												+-----------------+
												| Persistence DB  |
												|  (e.g. SQLite)  |
												+-----------------+
```
### Features

- **Modular D-Bus Interfaces**: Designed using introspection XML and `gdbus-codegen`.
- **Widget Configuration**: Exposes properties and methods to get/set widget attributes (e.g. window size, image source, text content).
- **Calculator Service**: Offers basic computation via a separate D-Bus interface.
- **JSON Integration**: Uses `json-glib` to serialize and store widget state from UI applications.

### Build
```bash
$ git clone https://github.com/M0hanrajp/jsonite-daemon.git
$ cd <project directory>
$ mkdir -p build && cd build
$ cmake ..
$ make
```
### Examples

Running the application
```bash
~/jsonite-daemon$ ./jsonite-daemon
[main]: g_main_loop_run is invoked
[on_bus_acquired_handler]: Bus acquisition complete
[on_bus_acquired_handler]: Methods are registered with dbus interface
[on_name_acquired_handler]: Name acquisition complete, daemon active..
```
`gdbus call` method `create window` over `com.jsoniteDaemon.Konfabulator.Widget` interface
```bash
$ gdbus call --session 
             --dest com.jsoniteDaemon 
             --object-path /com/jsoniteDaemon 
             --method com.jsoniteDaemon.Konfabulator.Widget.CreateWindow 
             "Sample Konfabulator Widget" "main_window" 500 400
```
reflected in `./jsonite-daemon`'s `stdout`
```bash
[handle_create_window] update data in DB
{
  "window" : {
    "title" : "Sample Konfabulator Widget",
    "name" : "main_window",
    "width" : 500,
    "height" : 400
  }
}
```
`gdbus call` to add two numbers over `com.jsoniteDaemon.Calculator` interface
```bash
gdbus call --session 
           --dest com.jsoniteDaemon 
           --object-path /com/jsoniteDaemon 
           --method com.jsoniteDaemon.Calculator.Subtract 
           '{"a":10, "b":20}'
```
response
```bash
('{"[handle_add_method] result":30}',)
```
---
Thanks.
