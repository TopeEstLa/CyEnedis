#ifndef WAITING_SCENE_H
#define WAITING_SCENE_H

/**
@brief Init waiting scene system
 */
void init_waiting_scene();

/**
@brief Loop for rendering the waiting scene
@param varg the thread argument
 */
void* draw_waiting_scene(void* varg);

#endif //WAITING_SCENE_H
