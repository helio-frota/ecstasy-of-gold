#include <allegro5/allegro.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_ttf.h>
#include <stdio.h>

#define DISPLAY_WIDTH 800
#define DISPLAY_HEIGHT 600
#define RECT_THICKNESS 5

enum position_of_gold { LEFT_TOP, LEFT_BOTTOM, RIGHT_TOP, RIGHT_BOTTOM };

typedef struct player {
  int x;
  int y;
  int score;
  int move_speed;
  int steps;
} PLAYER;

int rand_gold_position() {
  srand(time(NULL));
  return (rand() % 4);
}

int basic_collision(
    float x, float y, float gold_x, float gold_y, int width, int height) {
  if (x + width < gold_x || x > gold_x + width || y + height < gold_y ||
      y > gold_y + height) {
    return 0;
  }
  return 1;
}

int collided(PLAYER player) {
  return basic_collision(player.x,
                         player.y,
                         DISPLAY_WIDTH - 850,
                         DISPLAY_HEIGHT - 550,
                         40,
                         40) ||
         basic_collision(player.x,
                         player.y,
                         DISPLAY_WIDTH - 850,
                         DISPLAY_HEIGHT - 200,
                         40,
                         40) ||
         basic_collision(player.x,
                         player.y,
                         DISPLAY_WIDTH - 150,
                         DISPLAY_HEIGHT - 550,
                         40,
                         40) ||
         basic_collision(player.x,
                         player.y,
                         DISPLAY_WIDTH - 150,
                         DISPLAY_HEIGHT - 200,
                         40,
                         40);
}

int gold_found(PLAYER player, int gold_position) {
  return (((player.x > 150 && player.x < 200) &&
           (player.y > 200 && player.y < 250)) &&
          gold_position == LEFT_TOP) ||
         (((player.x > 150 && player.x < 200) &&
           (player.y > 560 && player.y < 570)) &&
          gold_position == LEFT_BOTTOM) ||
         (((player.x > 870 && player.x < 880) &&
           (player.y > 200 && player.y < 250)) &&
          gold_position == RIGHT_TOP) ||
         (((player.x > 870 && player.x < 880) &&
           (player.y > 560 && player.y < 570)) &&
          gold_position == RIGHT_BOTTOM);
}

int main() {
  if (!al_init()) {
    al_show_native_message_box(al_get_current_display(),
                               "EOG",
                               "Error:",
                               "Failed to initialize allegro 5.",
                               NULL,
                               ALLEGRO_MESSAGEBOX_ERROR);
    return EXIT_FAILURE;
  }

  ALLEGRO_COLOR blue = al_map_rgb(38, 139, 210);
  ALLEGRO_COLOR darkgreen = al_map_rgb(0, 43, 54);
  ALLEGRO_COLOR yellow = al_map_rgb(181, 137, 0);

  al_set_new_display_flags(ALLEGRO_WINDOWED);
  ALLEGRO_DISPLAY* display = al_create_display(DISPLAY_WIDTH, DISPLAY_HEIGHT);
  al_clear_to_color(darkgreen);

  if (!display) {
    al_show_native_message_box(al_get_current_display(),
                               "EOG",
                               "Error:",
                               "Failed to create display.",
                               NULL,
                               ALLEGRO_MESSAGEBOX_ERROR);
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
  ALLEGRO_SAMPLE* sound_gold = al_load_sample("sounds/sound_gold.wav");
  ALLEGRO_SAMPLE* song_gold = al_load_sample("sounds/song_gold.wav");
  ALLEGRO_SAMPLE_INSTANCE* song_instance = al_create_sample_instance(song_gold);
  al_set_sample_instance_playmode(song_instance, ALLEGRO_PLAYMODE_LOOP);
  al_attach_sample_instance_to_mixer(song_instance, al_get_default_mixer());

  ALLEGRO_FONT* font = al_load_font("fonts/OpenSans-Regular.ttf", 36, 0);

  ALLEGRO_EVENT_QUEUE* event_queue = al_create_event_queue();
  ALLEGRO_TIMER* timer = al_create_timer(1.0);
  al_register_event_source(event_queue, al_get_keyboard_event_source());
  al_register_event_source(event_queue, al_get_timer_event_source(timer));

  al_play_sample_instance(song_instance);
  al_start_timer(timer);

  al_set_window_title(display, "Ecstasy of gold");

  PLAYER player;
  player.x = DISPLAY_WIDTH / 2;
  player.y = DISPLAY_HEIGHT / 2;
  player.score = 0;
  player.move_speed = 45;
  player.steps = 0;

  int done = 0;
  int seconds = 60;
  int gold_position = rand_gold_position();

  do {
    al_draw_textf(
        font, blue, 10, 1, ALLEGRO_ALIGN_LEFT, "SCORE: %d", player.score);
    al_draw_textf(font,
                  blue,
                  (DISPLAY_WIDTH / 2) - 150,
                  1,
                  ALLEGRO_ALIGN_LEFT,
                  "STEPS: %d",
                  player.steps);
    al_draw_textf(font,
                  blue,
                  DISPLAY_WIDTH - 360,
                  1,
                  ALLEGRO_ALIGN_LEFT,
                  "TIME REMAINING: %d",
                  seconds);
    al_draw_line(1, 50, DISPLAY_WIDTH - 1, 50, blue, RECT_THICKNESS);

    ALLEGRO_EVENT events;
    al_wait_for_event(event_queue, &events);

    if (events.type == ALLEGRO_EVENT_KEY_DOWN) {
      if (events.keyboard.keycode == ALLEGRO_KEY_ESCAPE) {
        done = 1;
        continue;
      }

      al_get_keyboard_state(&keyboard_state);
      if (al_key_down(&keyboard_state, ALLEGRO_KEY_J)) {
        if (player.y < DISPLAY_HEIGHT - 100) {
          player.steps += 1;
          player.y += player.move_speed;
          if (collided(player)) {
            if (gold_found(player, gold_position)) {
              al_play_sample(
                  sound_gold, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, 0);
              player.score++;
              gold_position = rand_gold_position();
            }
          }
        }
      } else if (al_key_down(&keyboard_state, ALLEGRO_KEY_K)) {
        if (player.y > 100) {
          player.steps += 1;
          player.y -= player.move_speed;
          if (collided(player)) {
            if (gold_found(player, gold_position)) {
              al_play_sample(
                  sound_gold, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, 0);
              gold_position = rand_gold_position();
              player.score++;
            }
          }
        }
      } else if (al_key_down(&keyboard_state, ALLEGRO_KEY_L)) {
        if (player.x < DISPLAY_WIDTH - 40) {
          player.steps += 1;
          player.x += player.move_speed;
          if (collided(player)) {
            if (gold_found(player, gold_position)) {
              al_play_sample(
                  sound_gold, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, 0);
              gold_position = rand_gold_position();
              player.score++;
            }
          }
        }
      } else if (al_key_down(&keyboard_state, ALLEGRO_KEY_H)) {
        if (player.x > 40) {
          player.steps += 1;
          player.x -= player.move_speed;
          if (collided(player)) {
            if (gold_found(player, gold_position)) {
              al_play_sample(
                  sound_gold, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, 0);
              gold_position = rand_gold_position();
              player.score++;
            }
          }
        }
      }
    }

    if (events.type == ALLEGRO_EVENT_TIMER) {
      seconds--;
      if (seconds == 0) {
        return EXIT_SUCCESS;
      }
    }

    al_draw_text(font, blue, player.x, player.y, ALLEGRO_ALIGN_CENTER, "X");
    al_flip_display();
    al_clear_to_color(darkgreen);

    al_draw_rectangle(80, 140, 280, 340, blue, RECT_THICKNESS);
    al_draw_rectangle(80, 480, 280, 680, blue, RECT_THICKNESS);
    al_draw_rectangle(DISPLAY_WIDTH - 80,
                      140,
                      DISPLAY_WIDTH - 280,
                      340,
                      blue,
                      RECT_THICKNESS);
    al_draw_rectangle(DISPLAY_WIDTH - 80,
                      480,
                      DISPLAY_WIDTH - 280,
                      680,
                      blue,
                      RECT_THICKNESS);

    if (gold_position == LEFT_TOP) {
      al_draw_filled_rectangle(DISPLAY_WIDTH - 864,
                               DISPLAY_HEIGHT - 504,
                               DISPLAY_WIDTH - 824,
                               DISPLAY_HEIGHT - 544,
                               yellow);
    } else if (gold_position == LEFT_BOTTOM) {
      al_draw_filled_rectangle(DISPLAY_WIDTH - 864,
                               DISPLAY_HEIGHT - 208,
                               DISPLAY_WIDTH - 824,
                               DISPLAY_HEIGHT - 164,
                               yellow);
    } else if (gold_position == RIGHT_TOP) {
      al_draw_filled_rectangle(DISPLAY_WIDTH - 160,
                               DISPLAY_HEIGHT - 508,
                               DISPLAY_WIDTH - 200,
                               DISPLAY_HEIGHT - 548,
                               yellow);
    } else if (gold_position == RIGHT_BOTTOM) {
      al_draw_filled_rectangle(DISPLAY_WIDTH - 160,
                               DISPLAY_HEIGHT - 208,
                               DISPLAY_WIDTH - 200,
                               DISPLAY_HEIGHT - 168,
                               yellow);
    }
  } while (!done);

  al_destroy_font(font);
  al_destroy_display(display);
  al_destroy_timer(timer);
  al_destroy_sample(sound_gold);
  al_destroy_sample(song_gold);
  al_destroy_sample_instance(song_instance);
  al_destroy_event_queue(event_queue);

  return EXIT_SUCCESS;
}
