# Finds allegro5 on fedora 28.

find_path(ALLEGRO_INCLUDE_DIR allegro5/allegro.h)

find_library(ALLEGRO_LIBRARY NAMES allegro)

set(ALLEGRO_LIBRARIES ${ALLEGRO_LIBRARY})

set(ALLEGRO_INCLUDE_DIRS ${ALLEGRO_INCLUDE_DIR})
