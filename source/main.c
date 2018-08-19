#include <stdio.h>
#include <allegro5/allegro.h>

int main()
{

    ALLEGRO_DISPLAY *display = NULL;

    if (!al_init())
    {
        printf("Failed to initialize allegro 5.\n");
        return -1;
    }

    display = al_create_display(800, 600);

    if (!display)
    {
        printf("Failed to create display.\n");
        return -1;
    }

    // keep showing for 5 seconds only.
    al_rest(5.0);

    al_destroy_display(display);

    return 0;
}
