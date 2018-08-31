#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_native_dialog.h>

int main()
{

    ALLEGRO_DISPLAY *display = NULL;

    if (1)
    {
        al_show_native_message_box(al_get_current_display(),
                                 "EOG",
                                 "Error:",
                                 "Failed to initialize allegro 5.",
                                 NULL, ALLEGRO_MESSAGEBOX_ERROR);
        return EXIT_FAILURE;
    }

    display = al_create_display(800, 600);

    if (!display)
    {
        al_show_native_message_box(al_get_current_display(),
                                 "EOG",
                                 "Error:",
                                 "Failed to create display.",
                                 NULL, ALLEGRO_MESSAGEBOX_ERROR);
        return EXIT_FAILURE;
    }

    // keep showing for 5 seconds only.
    al_rest(5.0);

    al_destroy_display(display);

    return EXIT_SUCCESS;
}
