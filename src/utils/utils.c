#include "utils.h"

#include "raylib.h"

Grid
create_grid(int cells_width, int cells_height, int thickness)
{
    Grid grid = {};

    grid.window.width = GetScreenWidth();
    grid.window.height = GetScreenHeight();
    grid.thickness = thickness;
    grid.cell_size = _cell_size(&grid, cells_width, cells_height);
    grid.margin.x = _margin_x(&grid, cells_width);
    grid.margin.y = _margin_y(&grid, cells_height);

    return grid;
}

int
_cell_size(Grid* grid, int cells_width, int cells_height)
{
    int cell_size_w =
        (grid->window.width - (cells_width + 1) * grid->thickness) /
        cells_width;
    int cell_size_h =
        (grid->window.height - (cells_height + 1) * grid->thickness) /
        cells_height;

    if (cell_size_w < cell_size_h) { return cell_size_w; }
    else { return cell_size_h; }
}

int
_margin_x(Grid* grid, int cells_width)
{
    int thick_total = grid->thickness * (cells_width + 1);
    int cell_total = grid->cell_size * cells_width;
    return (grid->window.width - thick_total - cell_total) / 2;
}

int
_margin_y(Grid* grid, int cells_height)
{
    int thick_total = grid->thickness * (cells_height + 1);
    int cell_total = grid->cell_size * cells_height;
    return (grid->window.height - thick_total - cell_total) / 2;
}
