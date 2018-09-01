#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>

#define DISPLAY_WIDTH 1024
#define DISPLAY_HEIGHT 768

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

    al_set_new_display_flags(ALLEGRO_FULLSCREEN);

    ALLEGRO_DISPLAY *display = al_create_display(DISPLAY_WIDTH, DISPLAY_HEIGHT);

    al_set_window_title(display, "Ecstasy of gold");

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

    ALLEGRO_FONT *font = al_load_font("fonts/OpenSans-Regular.ttf", 36, 0);
    al_draw_text(font, al_map_rgb(44, 117, 255), DISPLAY_WIDTH / 2,
                 DISPLAY_HEIGHT / 2, ALLEGRO_ALIGN_CENTER, "Ecstasy of gold");

    al_flip_display();
    al_rest(5.0);
    al_destroy_font(font);
    al_destroy_display(display);

    return EXIT_SUCCESS;
}
