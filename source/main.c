#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_ttf.h>

#define DISPLAY_WIDTH 1024
#define DISPLAY_HEIGHT 768
#define RECT_THICKNESS 4.0

int main()
{

    if (!al_init())
    {
        al_show_native_message_box(al_get_current_display(),
                                   "EOG",
                                   "Error:",
                                   "Failed to initialize allegro 5.",
                                   NULL, ALLEGRO_MESSAGEBOX_ERROR);
        return EXIT_FAILURE;
    }

    ALLEGRO_DISPLAY *display = al_create_display(DISPLAY_WIDTH, DISPLAY_HEIGHT);
    al_set_new_display_flags(ALLEGRO_FULLSCREEN);
    al_clear_to_color(al_map_rgb(0, 43, 54));

    if (!display)
    {
        al_show_native_message_box(al_get_current_display(),
                                   "EOG",
                                   "Error:",
                                   "Failed to create display.",
                                   NULL, ALLEGRO_MESSAGEBOX_ERROR);
        return EXIT_FAILURE;
    }

    al_init_font_addon();
    al_init_ttf_addon();
    al_init_primitives_addon();

    al_set_window_title(display, "Ecstasy of gold");

    ALLEGRO_COLOR blue = al_map_rgb(38, 139, 210);
    ALLEGRO_COLOR yellow = al_map_rgb(181, 137, 0);

    ALLEGRO_FONT *font = al_load_font("fonts/OpenSans-Regular.ttf", 36, 0);
    al_draw_text(font, blue, DISPLAY_WIDTH / 2, DISPLAY_HEIGHT / 2,
                 ALLEGRO_ALIGN_CENTER, "X");

    al_draw_text(font, blue, 10, 1, ALLEGRO_ALIGN_LEFT, "SCORE:");
    al_draw_text(font, blue, DISPLAY_WIDTH - 360, 1, ALLEGRO_ALIGN_LEFT, "TIME REMAINING: 99");
    al_draw_line(1, 50, DISPLAY_WIDTH - 1, 50, blue, RECT_THICKNESS);
    al_draw_rectangle(40, 80, 240, 280, blue, RECT_THICKNESS);
    al_draw_rectangle(40, 480, 240, 680, blue, RECT_THICKNESS);
    al_draw_rectangle(DISPLAY_WIDTH - 40, 80, DISPLAY_WIDTH - 240, 280, blue, RECT_THICKNESS);
    al_draw_rectangle(DISPLAY_WIDTH - 40, 480, DISPLAY_WIDTH - 240, 680, blue, RECT_THICKNESS);

    al_flip_display();
    al_rest(15.0);
    al_destroy_font(font);
    al_destroy_display(display);

    return EXIT_SUCCESS;
}
