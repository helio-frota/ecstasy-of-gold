#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>

#define DISPLAY_WIDTH 1024
#define DISPLAY_HEIGHT 768
#define RECT_THICKNESS 5

int basic_collision(float x, float y, float gold_x, float gold_y, int width, int height)
{
    if (x + width < gold_x || x > gold_x + width || y + height < gold_y || y > gold_y + height)
    {
        return 0;
    }
    return 1;
}

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

    al_install_audio();
    al_install_keyboard();
    al_init_font_addon();
    al_init_ttf_addon();
    al_init_primitives_addon();
    al_init_acodec_addon();

    ALLEGRO_KEYBOARD_STATE keyboard_state;

    al_reserve_samples(2);
    ALLEGRO_SAMPLE *sound_gold = al_load_sample("sounds/sound_gold.wav");
    ALLEGRO_SAMPLE *song_gold = al_load_sample("sounds/song_gold.wav");
    ALLEGRO_SAMPLE_INSTANCE *song_instance = al_create_sample_instance(song_gold);
    al_set_sample_instance_playmode(song_instance, ALLEGRO_PLAYMODE_LOOP);
    al_attach_sample_instance_to_mixer(song_instance, al_get_default_mixer());

    ALLEGRO_FONT *font = al_load_font("fonts/OpenSans-Regular.ttf", 36, 0);

    ALLEGRO_EVENT_QUEUE *event_queue = al_create_event_queue();
    ALLEGRO_TIMER *timer = al_create_timer(1.0);
    al_register_event_source(event_queue, al_get_keyboard_event_source());
    al_register_event_source(event_queue, al_get_timer_event_source(timer));

    al_play_sample_instance(song_instance);
    al_start_timer(timer);

    al_set_window_title(display, "Ecstasy of gold");

    int done = 0;
    int x = DISPLAY_WIDTH / 2;
    int y = DISPLAY_HEIGHT / 2;
    int score = 0;
    int move_speed = 40;
    int steps = 0;
    int seconds = 60;

    al_draw_textf(font, blue, 10, 1, ALLEGRO_ALIGN_LEFT, "SCORE: %d", score);
    al_draw_text(font, blue, (DISPLAY_WIDTH / 2) - 200, 1, ALLEGRO_ALIGN_LEFT, "STEPS: 0");
    al_draw_text(font, blue, DISPLAY_WIDTH - 360, 1, ALLEGRO_ALIGN_LEFT, "TIME REMAINING: 60");
    al_draw_line(1, 50, DISPLAY_WIDTH - 1, 50, blue, RECT_THICKNESS);

    while (!done)
    {
        ALLEGRO_EVENT events;
        al_wait_for_event(event_queue, &events);

        if (events.type == ALLEGRO_EVENT_KEY_UP)
        {
            if (events.keyboard.keycode == ALLEGRO_KEY_ESCAPE)
            {
                done = 1;
            }
        }

        if (events.type == ALLEGRO_EVENT_KEY_DOWN)
        {
            al_get_keyboard_state(&keyboard_state);
            if (al_key_down(&keyboard_state, ALLEGRO_KEY_J))
            {
                if (y < DISPLAY_HEIGHT - 100)
                {
                    steps += 1;
                    y += move_speed;
                    if (basic_collision(x, y, 165, 205, 45, 45))
                    {
                        al_play_sample(sound_gold, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, 0);
                        score++;
                    }
                }
            }
            else if (al_key_down(&keyboard_state, ALLEGRO_KEY_K))
            {
                if (y > 100)
                {
                    steps += 1;
                    y -= move_speed;
                    if (basic_collision(x, y, 165, 205, 45, 45))
                    {
                        al_play_sample(sound_gold, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, 0);
                        score++;
                    }
                }
            }
            else if (al_key_down(&keyboard_state, ALLEGRO_KEY_L))
            {
                if (x < DISPLAY_WIDTH - 40)
                {
                    steps += 1;
                    x += move_speed;
                    if (basic_collision(x, y, 165, 205, 45, 45))
                    {
                        al_play_sample(sound_gold, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, 0);
                        score++;
                    }
                }
            }
            else if (al_key_down(&keyboard_state, ALLEGRO_KEY_H))
            {
                if (x > 40)
                {
                    steps += 1;
                    x -= move_speed;
                    if (basic_collision(x, y, 165, 205, 45, 45))
                    {
                        al_play_sample(sound_gold, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, 0);
                        score++;
                    }
                }
            }
        }

        if (events.type == ALLEGRO_EVENT_TIMER)
        {
            seconds--;
            if (seconds == 0)
            {
                return EXIT_SUCCESS;
            }
        }

        al_draw_text(font, blue, x, y, ALLEGRO_ALIGN_CENTER, "X");
        al_flip_display();
        al_clear_to_color(darkgreen);

        al_draw_textf(font, blue, 10, 1, ALLEGRO_ALIGN_LEFT, "SCORE: %d", score);

        al_draw_textf(font, blue, (DISPLAY_WIDTH / 2) - 150, 1, ALLEGRO_ALIGN_LEFT, "STEPS: %d", steps);
        al_draw_textf(font, blue, DISPLAY_WIDTH - 360, 1, ALLEGRO_ALIGN_LEFT, "TIME REMAINING: %d", seconds);
        al_draw_line(1, 50, DISPLAY_WIDTH - 1, 50, blue, RECT_THICKNESS);

        al_draw_rectangle(80, 140, 280, 340, blue, RECT_THICKNESS);
        al_draw_rectangle(80, 480, 280, 680, blue, RECT_THICKNESS);
        al_draw_rectangle(DISPLAY_WIDTH - 80, 140, DISPLAY_WIDTH - 280, 340, blue, RECT_THICKNESS);
        al_draw_rectangle(DISPLAY_WIDTH - 80, 480, DISPLAY_WIDTH - 280, 680, blue, RECT_THICKNESS);

        // the gold.
        al_draw_filled_rectangle(160, 220, 200, 260, yellow);
        al_draw_filled_rectangle(160, 560, 200, 600, yellow);
        al_draw_filled_rectangle(DISPLAY_WIDTH - 160, 220, DISPLAY_WIDTH - 200, 260, yellow);
        al_draw_filled_rectangle(DISPLAY_WIDTH - 160, 560, DISPLAY_WIDTH - 200, 600, yellow);
    }

    al_destroy_font(font);
    al_destroy_display(display);
    al_destroy_timer(timer);
    al_destroy_sample(sound_gold);
    al_destroy_sample(song_gold);
    al_destroy_sample_instance(song_instance);
    al_destroy_event_queue(event_queue);

    return EXIT_SUCCESS;
}
