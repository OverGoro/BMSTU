#include "manager.h"

int manage(const manager_params_t &params, manager_command_t command)
{
    static figure_t figure = figure_init_empty();

    int rc = ERR_UNKNOWN_COMMAND;
    if (command == COMMAND_READ)
    {
        rc = figure_read_file(figure, params.filename);
    }
    else if (command == COMMAND_SAVE)
    {
        rc = figure_save_file(figure, params.filename);
    }
    else if (command == COMMAND_MOVE)
    {
        rc = figure_move(figure,  params.move_params);
    }
    else if (command == COMMAND_ROTATE)
    {
        rc = figure_rotate(figure, params.center, params.rotation_angle);
    }
    else if (command == COMMAND_SCALE)
    {
        rc = figure_scale(figure, params.center, params.scale_params);
    }
    else if (command == COMMAND_DRAW)
    {
        rc = drawer_draw_figure(params.drawer_params, figure);
    }
    else if (command == COMMAND_EXIT)
    {
        figure_clear(figure);
        rc = OK;
    }

    return rc;
}
