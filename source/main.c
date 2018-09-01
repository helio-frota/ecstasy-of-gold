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

    ALLEGRO_COLOR blue = al_map_rgb(38, 139, 210);
    ALLEGRO_COLOR darkgreen = al_map_rgb(0, 43, 54);
    ALLEGRO_COLOR yellow = al_map_rgb(181, 137, 0);

    ALLEGRO_DISPLAY *display = al_create_display(DISPLAY_WIDTH, DISPLAY_HEIGHT);
    al_set_new_display_flags(ALLEGRO_FULLSCREEN);
    al_clear_to_color(darkgreen);

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
    al_install_keyboard();

    ALLEGRO_FONT *font = al_load_font("fonts/OpenSans-Regular.ttf", 36, 0);
    ALLEGRO_EVENT_QUEUE *event_queue = al_create_event_queue();
    ALLEGRO_EVENT_QUEUE *timer_queue = al_create_event_queue();
    ALLEGRO_TIMER *timer = al_create_timer(1.0);
    al_register_event_source(event_queue, al_get_keyboard_event_source());
    al_register_event_source(timer_queue, al_get_timer_event_source(timer));
    al_start_timer(timer);

    al_set_window_title(display, "Ecstasy of gold");

    int done = 0;
    int x = DISPLAY_WIDTH / 2;
    int y = DISPLAY_HEIGHT / 2;
    int move_speed = 40;
    int steps = 0;
    int seconds = 60;

    al_draw_text(font, blue, 10, 1, ALLEGRO_ALIGN_LEFT, "SCORE: 0");
    al_draw_text(font, blue, (DISPLAY_WIDTH / 2) - 200, 1, ALLEGRO_ALIGN_LEFT, "STEPS: 0");
    al_draw_text(font, blue, DISPLAY_WIDTH - 360, 1, ALLEGRO_ALIGN_LEFT, "TIME REMAINING: 60");
    al_draw_line(1, 50, DISPLAY_WIDTH - 1, 50, blue, RECT_THICKNESS);

    while (!done)
    {
        ALLEGRO_EVENT events;
        al_wait_for_event(event_queue, &events);

        if (events.type == ALLEGRO_EVENT_KEY_DOWN)
        {
            switch (events.keyboard.keycode)
            {
            case ALLEGRO_KEY_J:
                steps += 1;
                y += move_speed;
                break;
            case ALLEGRO_KEY_K:
                steps += 1;
                y -= move_speed;
                break;
            case ALLEGRO_KEY_L:
                steps += 1;
                x += move_speed;
                break;
            case ALLEGRO_KEY_H:
                steps += 1;
                x -= move_speed;
                break;
            case ALLEGRO_KEY_ESCAPE:
                done = 1;
                break;
            }
        }

        if (!al_is_event_queue_empty(timer_queue))
        {
            ALLEGRO_EVENT evento;
            al_wait_for_event(timer_queue, &evento);

            if (evento.type == ALLEGRO_EVENT_TIMER)
            {
                seconds--;
                if (seconds == 0)
                {
                    return EXIT_SUCCESS;
                }
            }
        }

        al_draw_text(font, blue, x, y, ALLEGRO_ALIGN_CENTER, "X");
        al_flip_display();
        al_clear_to_color(darkgreen);

        al_draw_text(font, blue, 10, 1, ALLEGRO_ALIGN_LEFT, "SCORE: 0");

        al_draw_textf(font, blue, (DISPLAY_WIDTH / 2) - 150, 1, ALLEGRO_ALIGN_LEFT, "STEPS: %d", steps);
        al_draw_textf(font, blue, DISPLAY_WIDTH - 360, 1, ALLEGRO_ALIGN_LEFT, "TIME REMAINING: %d", seconds);
        al_draw_line(1, 50, DISPLAY_WIDTH - 1, 50, blue, RECT_THICKNESS);

        al_draw_rectangle(40, 80, 240, 280, blue, RECT_THICKNESS);
        al_draw_rectangle(40, 480, 240, 680, blue, RECT_THICKNESS);
        al_draw_rectangle(DISPLAY_WIDTH - 40, 80, DISPLAY_WIDTH - 240, 280, blue, RECT_THICKNESS);
        al_draw_rectangle(DISPLAY_WIDTH - 40, 480, DISPLAY_WIDTH - 240, 680, blue, RECT_THICKNESS);
    }

    al_destroy_font(font);
    al_destroy_display(display);
    al_destroy_timer(timer);
    al_destroy_event_queue(event_queue);
    al_destroy_event_queue(timer_queue);

    return EXIT_SUCCESS;
}
