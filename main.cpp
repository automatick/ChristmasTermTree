#include <ncurses.h>
#include <cstdlib>
#include <cstdint>
#include <locale.h>
#include <ctime>

void inline end() {
    getch();
    endwin();
}

void inline init() {
    setlocale(LC_ALL, "");
    initscr();
    cbreak();
    noecho();
    curs_set(0);
    keypad(stdscr, TRUE);
    start_color();
    if (COLORS >= 256) {
        init_pair(1, 94, COLOR_BLACK);
        init_pair(2, COLOR_GREEN, COLOR_BLACK);
        init_pair(3, 22, COLOR_BLACK);
        init_pair(4, 196, COLOR_BLACK);
        init_pair(5, 226, COLOR_BLACK);
        init_pair(6, 46, COLOR_BLACK);
        init_pair(7, 51, COLOR_BLACK);
    } else if (can_change_color()) {
        init_color(16, 0, 255 * 4, 0);
        init_color(17, 0 * 4, 100 * 4, 0 * 4);
        init_pair(1, 94, COLOR_BLACK);
        init_pair(2, COLOR_GREEN, COLOR_BLACK);
        init_pair(3, 17, COLOR_BLACK);
    } else {
        init_pair(1, COLOR_YELLOW, COLOR_BLACK);
        init_pair(2, COLOR_GREEN, COLOR_BLACK);
        init_pair(3, COLOR_GREEN, COLOR_BLACK);
        init_pair(4, COLOR_RED, COLOR_BLACK);
        init_pair(5, COLOR_YELLOW, COLOR_BLACK);
        init_pair(6, COLOR_GREEN, COLOR_BLACK);
        init_pair(7, COLOR_BLUE, COLOR_BLACK);
    }
}

void draw_rectangle(uint16_t startx, uint16_t starty, uint16_t width, uint16_t height, int color_pair) {
    attron(COLOR_PAIR(color_pair));
    for (uint8_t y = 0; y < height; y++) {
        for (uint8_t x = 0; x < width; x++) {
            mvaddwstr(starty + y, startx + x, L"█");
        }
    }
    attroff(COLOR_PAIR(color_pair));
}

void draw_trunk(uint16_t maxx, uint16_t maxy) {
    uint16_t trunk_width = maxx / 20;
    uint16_t trunk_height = maxy / 4;
    uint16_t startx = maxx / 2 - trunk_width / 2;
    uint16_t starty = maxy - trunk_height;
    draw_rectangle(startx, starty, trunk_width, trunk_height, 1);
}

void draw_tree(uint16_t maxx, uint16_t maxy) {
    const uint16_t starty = maxy / 1.2;
    const uint16_t initx = maxx / 2;
    const uint16_t max_width = maxx / 4;

    for (uint16_t i = 0; i < starty; i++) {
        uint16_t current_width = (max_width * (starty - i)) / starty + (rand() % 3 - 1);
        for (int16_t offset = -current_width; offset <= current_width; offset++) {
            if (rand() % 10 != 0) {
                int color = (rand() % 2) ? 2 : 3;
                attron(COLOR_PAIR(color));
                mvaddwstr(starty - i, initx + offset, L"█");
                attroff(COLOR_PAIR(color));
            }
        }
    }
}


void draw_garland(uint16_t maxx, uint16_t maxy, wchar_t** tree_symbols, int** tree_colors) {
    const uint16_t starty = maxy / 1.2;
    const uint16_t initx = maxx / 2;
    const uint16_t max_width = maxx / 4;
    const uint16_t lights_count = 50;

    while (true) {
        for (uint16_t i = 0; i < lights_count; i++) {
            uint16_t level = rand() % (uint16_t)(starty * 0.9);
            uint16_t current_width = (max_width * (starty - level)) / starty;
            int16_t offset = rand() % (current_width * 2 + 1) - current_width;
            uint16_t x = initx + offset;
            uint16_t y = starty - level;

            if (offset >= -current_width && offset <= current_width && tree_symbols[y][x] == L'█') {
                int color = rand() % 4 + 4;
                attron(COLOR_PAIR(color));
                mvaddwstr(y, x, L"█");
                attroff(COLOR_PAIR(color));
            }
        }
        refresh();
        napms(200);

        for (uint16_t i = 0; i < maxy; i++) {
            for (uint16_t j = 0; j < maxx; j++) {
                if (tree_symbols[i][j] == L'█') {
                    attron(COLOR_PAIR(tree_colors[i][j]));
                    mvaddwstr(i, j, &tree_symbols[i][j]);
                    attroff(COLOR_PAIR(tree_colors[i][j]));
                }
            }
        }
    }
}


int main() {
    std::srand(std::time(0));
    init();

    uint16_t maxx, maxy;
    getmaxyx(stdscr, maxy, maxx);

    wchar_t** tree_symbols = new wchar_t*[maxy];
    int** tree_colors = new int*[maxy];
    for (uint16_t i = 0; i < maxy; i++) {
        tree_symbols[i] = new wchar_t[maxx];
        tree_colors[i] = new int[maxx];
    }

    draw_trunk(maxx, maxy);
    draw_tree(maxx, maxy);

    cchar_t ch;
    for (uint16_t y = 0; y < maxy; y++) {
        for (uint16_t x = 0; x < maxx; x++) {
            if (mvin_wch(y, x, &ch) == OK) {
                tree_symbols[y][x] = ch.chars[0];
                tree_colors[y][x] = PAIR_NUMBER(ch.attr);
            }
        }
    }

    draw_garland(maxx, maxy, tree_symbols, tree_colors);

    for (uint16_t i = 0; i < maxy; i++) {
        delete[] tree_symbols[i];
        delete[] tree_colors[i];
    }
    delete[] tree_symbols;
    delete[] tree_colors;

    end();
}

