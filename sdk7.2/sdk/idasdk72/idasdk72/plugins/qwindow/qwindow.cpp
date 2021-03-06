/*
 *  This is a sample plugin module. It demonstrates how to create your
 *  own window and populate it with Qt widgets.
 *
 */

#include <QtWidgets>

#include <ida.hpp>
#include <idp.hpp>
#include <loader.hpp>
#include <kernwin.hpp>

#include "myactions.h"

//--------------------------------------------------------------------------
//lint -e1762
void MyActions::clicked()
{
  info("Button is clicked");
}

//--------------------------------------------------------------------------
static ssize_t idaapi ui_callback(void *user_data, int notification_code, va_list va)
{
  if ( notification_code == ui_widget_visible )
  {
    TWidget *widget = va_arg(va, TWidget *);
    if ( widget == user_data )
    {
      QWidget *w = (QWidget *) widget;
      MyActions *actions = new MyActions(w);

      // create a widget
      QPushButton *b = new QPushButton("Click here", w);

      // connect the button to a slot
      QObject::connect(b, SIGNAL(clicked()), actions, SLOT(clicked()));

      // position and display it
      b->move(50, 50);
      b->show();
      msg("Qt widget is displayed\n");
      //lint -esym(429, actions, b) not freed
    }
  }
  else if ( notification_code == ui_widget_invisible )
  {
    TWidget *widget = va_arg(va, TWidget *);
    if ( widget == user_data )
    {
      // user defined widget is closed, destroy its controls
      // (to be implemented)
      msg("Qt widget is closed\n");
    }
  }
  return 0;
}

//--------------------------------------------------------------------------
int idaapi init(void)
{
  // the plugin works only with idaq
  return is_idaq() ? PLUGIN_OK : PLUGIN_SKIP;
}

//--------------------------------------------------------------------------
void idaapi term(void)
{
  unhook_from_notification_point(HT_UI, ui_callback);
}

//--------------------------------------------------------------------------
bool idaapi run(size_t)
{
  TWidget *widget = find_widget("Sample Qt subwindow");
  if ( widget == NULL )
  {
    widget = create_empty_widget("Sample Qt subwindow");
    hook_to_notification_point(HT_UI, ui_callback, widget);
    display_widget(widget, WOPN_TAB|WOPN_RESTORE);
  }
  else
  {
    close_widget(widget, WCLS_SAVE);
  }
  return true;
}

//--------------------------------------------------------------------------
static const char comment[] = "This is a sample Qt plugin.";
static const char help[] =
  "A sample plugin module\n"
  "\n"
  "This module shows you how to create a Qt window.";

//--------------------------------------------------------------------------
// This is the preferred name of the plugin module in the menu system
// The preferred name may be overriden in plugins.cfg file

static const char wanted_name[] = "Create Qt subwindow";

// This is the preferred hotkey for the plugin module
// The preferred hotkey may be overriden in plugins.cfg file
// Note: IDA won't tell you if the hotkey is not correct
//       It will just disable the hotkey.

static const char wanted_hotkey[] = "";

//--------------------------------------------------------------------------
//
//      PLUGIN DESCRIPTION BLOCK
//
//--------------------------------------------------------------------------
plugin_t PLUGIN =
{
  IDP_INTERFACE_VERSION,
  0,                    // plugin flags
  init,                 // initialize

  term,                 // terminate. this pointer may be NULL.

  run,                  // invoke plugin

  comment,              // long comment about the plugin
                        // it could appear in the status line
                        // or as a hint

  help,                 // multiline help about the plugin

  wanted_name,          // the preferred short name of the plugin
  wanted_hotkey         // the preferred hotkey to run the plugin
};
