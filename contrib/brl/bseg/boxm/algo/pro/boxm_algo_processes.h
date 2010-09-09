#ifndef boxm_algo_processes_h_
#define boxm_algo_processes_h_

#include <bprb/bprb_func_process.h>
#include <bprb/bprb_macros.h>

//the init functions
DECLARE_FUNC_CONS(boxm_describe_scene_process);
DECLARE_FUNC_CONS(boxm_init_scene_process);
DECLARE_FUNC_CONS(boxm_line_backproject_process);
DECLARE_FUNC_CONS(boxm_refine_scene_process);
DECLARE_FUNC_CONS(boxm_replace_const_app_process);
DECLARE_FUNC_CONS(boxm_roi_init_process);
DECLARE_FUNC_CONS(boxm_roi_init_rational_camera_process);
DECLARE_FUNC_CONS(boxm_save_occupancy_raw_process);
DECLARE_FUNC_CONS(boxm_render_expected_edge_vrml_process);
DECLARE_FUNC_CONS(boxm_compute_scene_difference_process);
#endif
