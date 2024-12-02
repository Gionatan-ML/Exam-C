#include <gtk/gtk.h>
#include <stdlib.h>
#include <time.h>

#define CELL_SIZE 20
#define GRID_WIDTH 30
#define GRID_HEIGHT 20

typedef struct {
    int x;
    int y;
} Point;

typedef enum {
    UP,
    DOWN,
    LEFT,
    RIGHT
} Direction;

static Point snake[GRID_WIDTH * GRID_HEIGHT];
static int snake_length;
static Direction dir;
static Point food;
static gboolean game_over = FALSE;

static gboolean on_draw(GtkWidget *widget, cairo_t *cr, gpointer data);
static gboolean on_key_press(GtkWidget *widget, GdkEventKey *event, gpointer data);
static gboolean on_timer(gpointer data);
static void reset_game();

int main(int argc, char *argv[]) {
    gtk_init(&argc, &argv);

    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Snake Game");
    gtk_window_set_default_size(GTK_WINDOW(window), CELL_SIZE * GRID_WIDTH, CELL_SIZE * GRID_HEIGHT);
    gtk_window_set_resizable(GTK_WINDOW(window), FALSE);

    GtkWidget *drawing_area = gtk_drawing_area_new();
    gtk_container_add(GTK_CONTAINER(window), drawing_area);

    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);
    g_signal_connect(drawing_area, "draw", G_CALLBACK(on_draw), NULL);
    g_signal_connect(window, "key-press-event", G_CALLBACK(on_key_press), NULL);

    srand(time(NULL));
    reset_game();

    g_timeout_add(100, on_timer, drawing_area);

    gtk_widget_show_all(window);
    gtk_main();

    return 0;
}

static gboolean on_draw(GtkWidget *widget, cairo_t *cr, gpointer data) {
    cairo_set_source_rgb(cr, 0, 0, 0);
    cairo_paint(cr);

    cairo_set_source_rgb(cr, 0, 1, 0);
    for (int i = 0; i < snake_length; i++) {
        cairo_rectangle(cr, snake[i].x * CELL_SIZE, snake[i].y * CELL_SIZE, CELL_SIZE, CELL_SIZE);
        cairo_fill(cr);
    }

    cairo_set_source_rgb(cr, 1, 0, 0);
    cairo_rectangle(cr, food.x * CELL_SIZE, food.y * CELL_SIZE, CELL_SIZE, CELL_SIZE);
    cairo_fill(cr);

    if (game_over) {
        cairo_set_source_rgb(cr, 1, 1, 1);
        cairo_select_font_face(cr, "Sans", CAIRO_FONT_SLANT_NORMAL, CAIRO_FONT_WEIGHT_BOLD);
        cairo_set_font_size(cr, 40);
        cairo_move_to(cr, CELL_SIZE * GRID_WIDTH / 4, CELL_SIZE * GRID_HEIGHT / 2);
        cairo_show_text(cr, "Game Over");
    }

    return FALSE;
}

static gboolean on_key_press(GtkWidget *widget, GdkEventKey *event, gpointer data) {
    switch (event->keyval) {
        case GDK_KEY_Up:
            if (dir != DOWN) dir = UP;
            break;
        case GDK_KEY_Down:
            if (dir != UP) dir = DOWN;
            break;
        case GDK_KEY_Left:
            if (dir != RIGHT) dir = LEFT;
            break;
        case GDK_KEY_Right:
            if (dir != LEFT) dir = RIGHT;
            break;
        case GDK_KEY_space:
            if (game_over) {
                reset_game();
                gtk_widget_queue_draw(widget);
            }
            break;
    }
    return FALSE;
}

static gboolean on_timer(gpointer data) {
    if (game_over) return FALSE;

    for (int i = snake_length - 1; i > 0; i--) {
        snake[i] = snake[i - 1];
    }

    switch (dir) {
        case UP:
            snake[0].y--;
            break;
        case DOWN:
            snake[0].y++;
            break;
        case LEFT:
            snake[0].x--;
            break;
        case RIGHT:
            snake[0].x++;
            break;
    }

    if (snake[0].x < 0 || snake[0].x >= GRID_WIDTH ||
        snake[0].y < 0 || snake[0].y >= GRID_HEIGHT) {
        game_over = TRUE;
    }

    for (int i = 1; i < snake_length; i++) {
        if (snake[0].x == snake[i].x && snake[0].y == snake[i].y) {
            game_over = TRUE;
            break;
        }
    }

    if (snake[0].x == food.x && snake[0].y == food.y) {
        snake_length++;
        food.x = rand() % GRID_WIDTH;
        food.y = rand() % GRID_HEIGHT;
    }

    gtk_widget_queue_draw(GTK_WIDGET(data));
    return TRUE;
}

static void reset_game() {
    snake_length = 5;
    dir = RIGHT;
    for (int i = 0; i < snake_length; i++) {
        snake[i].x = snake_length - i - 1;
        snake[i].y = 0;
    }
    food.x = rand() % GRID_WIDTH;
    food.y = rand() % GRID_HEIGHT;
    game_over = FALSE;
}