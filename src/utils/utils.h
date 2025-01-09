#ifndef UTILS_H
#define UTILS_H

typedef struct {
    int width;
    int height;
} WindowDims;

typedef struct {
    int x;
    int y;
} IntVector2;

typedef struct {
    int thickness;
    int cell_size;
    IntVector2 margin;
    WindowDims window;
} Grid;

Grid create_grid(int cells_width, int cells_height, int thickness);
int _cell_size(Grid* grid, int cells_width, int cells_height);
int _margin_x(Grid* grid, int cells_width);
int _margin_y(Grid* grid, int cells_height);

#endif
