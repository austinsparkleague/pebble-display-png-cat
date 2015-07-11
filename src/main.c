/*
 * main.c
 * Sets up a Window and BitmapLayer, then loads and displays a PNG as a GBitmap
 */

#include <pebble.h>

static Window *window;
static GBitmap *seasick_the_cat_png;
static BitmapLayer *image_layer;

static void main_window_load(Window *window) {
  Layer *window_layer = window_get_root_layer(window);
  GRect bounds = layer_get_bounds(window_layer);

  seasick_the_cat_png = gbitmap_create_with_resource(RESOURCE_ID_CAT_PIC);

  image_layer = bitmap_layer_create(bounds);
  bitmap_layer_set_background_color(image_layer, GColorClear);
  bitmap_layer_set_bitmap(image_layer, seasick_the_cat_png);
  //bitmap_layer_set_compositing_mode(image_layer, GCompOpAssign);

  layer_add_child(window_layer, bitmap_layer_get_layer(image_layer));
}

static void main_window_unload(Window *window) {
  bitmap_layer_destroy(image_layer);
  gbitmap_destroy(seasick_the_cat_png);
}

static void init() {
  window = window_create();
  window_set_background_color(window, COLOR_FALLBACK(GColorBlue, GColorBlack));
  window_set_window_handlers(window, (WindowHandlers) {
    .load = main_window_load,
    .unload = main_window_unload,
  });
  window_stack_push(window, true);
}

static void deinit() {
  window_destroy(window);
}

int main() {
  init();
  app_event_loop();
  deinit();
}
