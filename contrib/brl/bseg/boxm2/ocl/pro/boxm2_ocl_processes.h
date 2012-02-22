#ifndef boxm2_ocl_processes_h_
#define boxm2_ocl_processes_h_

#include <bprb/bprb_func_process.h>
#include <bprb/bprb_macros.h>

//the init functions
DECLARE_FUNC_CONS(boxm2_create_opencl_cache_process);
DECLARE_FUNC_CONS(boxm2_ocl_render_expected_image_process);
DECLARE_FUNC_CONS(boxm2_ocl_render_gl_expected_image_process);
DECLARE_FUNC_CONS(boxm2_ocl_render_expected_depth_process);
DECLARE_FUNC_CONS(boxm2_ocl_render_expected_z_image_process); // 3-d to dem
DECLARE_FUNC_CONS(boxm2_ocl_render_expected_height_map_process); // 3-d to dem
DECLARE_FUNC_CONS(boxm2_ocl_ingest_dem_process); // dem to 3-d.
DECLARE_FUNC_CONS(boxm2_ocl_ingest_buckeye_dem_process);
DECLARE_FUNC_CONS(boxm2_ocl_update_process);
DECLARE_FUNC_CONS(boxm2_ocl_refine_process);
DECLARE_FUNC_CONS(boxm2_ocl_merge_process);
DECLARE_FUNC_CONS(boxm2_ocl_update_histogram_process);
DECLARE_FUNC_CONS(boxm2_ocl_query_hist_data_process);
DECLARE_FUNC_CONS(boxm2_ocl_batch_probability_process);
DECLARE_FUNC_CONS(boxm2_ocl_query_cell_data_process);
DECLARE_FUNC_CONS(boxm2_ocl_render_expected_color_process);
DECLARE_FUNC_CONS(boxm2_ocl_update_color_process);
DECLARE_FUNC_CONS(boxm2_ocl_render_gl_expected_color_process);
DECLARE_FUNC_CONS(boxm2_ocl_change_detection_process);
DECLARE_FUNC_CONS(boxm2_ocl_visualize_change_process);
DECLARE_FUNC_CONS(boxm2_ocl_probability_of_image_process);
DECLARE_FUNC_CONS(boxm2_ocl_probability_of_image_gl_process);
DECLARE_FUNC_CONS(boxm2_ocl_convert_float_image_to_rgba_process);
DECLARE_FUNC_CONS(boxm2_ocl_render_cone_expected_image_process);
DECLARE_FUNC_CONS(boxm2_ocl_filter_process);
DECLARE_FUNC_CONS(boxm2_clear_opencl_cache_process); 
DECLARE_FUNC_CONS(boxm2_ocl_cone_update_process); 
DECLARE_FUNC_CONS(boxm2_ocl_adaptive_cone_update_process); 
DECLARE_FUNC_CONS(boxm2_ocl_adaptive_cone_render_expected_process); 

DECLARE_FUNC_CONS(boxm2_ocl_update_aux_per_view_process); 
DECLARE_FUNC_CONS(boxm2_ocl_aux_update_view_direction_process); 
DECLARE_FUNC_CONS(boxm2_ocl_batch_synoptic_function_process); 
DECLARE_FUNC_CONS(boxm2_ocl_update_alpha_wcubic_process);
DECLARE_FUNC_CONS(boxm2_ocl_uncertainty_per_image_process);
DECLARE_FUNC_CONS(boxm2_ocl_batch_uncertainty_process);

DECLARE_FUNC_CONS(boxm2_ocl_update_sun_visibilities_process); 
DECLARE_FUNC_CONS(boxm2_ocl_render_expected_shadow_map_process); 
DECLARE_FUNC_CONS(boxm2_ocl_create_norm_intensities_process); 
DECLARE_FUNC_CONS(boxm2_ocl_create_aux_process); 
DECLARE_FUNC_CONS(boxm2_ocl_flip_normals_using_vis_process);

DECLARE_FUNC_CONS(boxm2_ocl_paint_batch_process); 
DECLARE_FUNC_CONS(boxm2_ocl_paint_online_process);

DECLARE_FUNC_CONS(boxm2_ocl_update_alpha_naa_process);
DECLARE_FUNC_CONS(boxm2_ocl_render_expected_image_naa_process);
DECLARE_FUNC_CONS(boxm2_ocl_render_expected_albedo_normal_process);
DECLARE_FUNC_CONS(boxm2_ocl_batch_compute_normal_albedo_array_process);

#endif
