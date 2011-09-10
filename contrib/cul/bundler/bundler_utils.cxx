#include <bundler/bundler_utils.h>

#include <mrc/vpgl/algo/vpgl_triangulate_points.h>
#include <mrc/vpgl/algo/vpgl_camera_compute.h>

#include <vcl_cmath.h>
#include <vcl_cstdlib.h>
#include <vcl_cassert.h>
#include <vcl_vector.h>

#include <vgl/vgl_point_2d.h>
#include <vgl/vgl_homg_point_2d.h>
#include <vgl/algo/vgl_h_matrix_2d.h>

// Generally useful function used for RANSAC.
// Randomly chooses n distinct indices into the set
void bundler_utils_get_distinct_indices(
    int n, int *idxs, int number_entries)
{
    for (int i = 0; i < n; ++i) {
        bool found;
        int idx;

        do {
            found = true;
            idx = vcl_rand() % number_entries;

            for (int j = 0; j < i; ++j) {
                if (idxs[j] == idx) {
                    found = false;
                    break;
                }
            }
        } while (!found);

        idxs[i] = idx;
    }
}


//----------------------------------------------------------------------
// A wrapper for vpgl_triangulate_points
double bundler_utils_triangulate_points(
    const bundler_inters_track_sptr &track)
{
    vcl_vector<vpgl_perspective_camera<double> > persp_cameras;
    vcl_vector<vgl_point_2d<double> > vgl_points;

    for (unsigned int i = 0; i < track->points.size(); ++i) {
        if (track->contributing_points[i]){
            vgl_points.push_back(track->points[i]->point);
            persp_cameras.push_back(track->points[i]->image->camera);
        }
    }

    // Actually do the triangulation.
    return
        vpgl_triangulate_points::triangulate(
            vgl_points, persp_cameras, track->world_point);
}


//----------------------------------------------------------------------
// Estimates a homography and returns the percentage of inliers
double bundler_utils_get_homography_inlier_percentage(
    const bundler_inters_match_set &match,
    double threshold_squared, int num_rounds)
{
    int inlier_count = 0;

    // RANSAC!
    for (int round = 0; round < num_rounds; ++round) {
        int match_idxs[4];
        bundler_utils_get_distinct_indices(
            4, match_idxs, match.num_features());

        // Fill these vectors with the points stored at the indices
        vcl_vector<vgl_homg_point_2d<double> > rhs;
        vcl_vector<vgl_homg_point_2d<double> > lhs;

        for (int i = 0; i < 4; ++i) {
            lhs.push_back(
                vgl_homg_point_2d<double>(
                    match.matches[match_idxs[i]].first->point));

            rhs.push_back(
                vgl_homg_point_2d<double>(
                    match.matches[match_idxs[i]].second->point));
        }

        // Get the homography for the points
        vgl_h_matrix_2d<double> homography(rhs, lhs);

        // Count the number of inliers
        vgl_homg_point_2d<double> lhs_pt, rhs_pt;

        int current_num_inliers = 0;

        vcl_vector<bundler_inters_feature_pair>::const_iterator m;
        for (m = match.matches.begin(); m != match.matches.end(); ++m)
        {
            lhs_pt.set(m->first->point.x(), m->first->point.y());

            rhs_pt = homography(lhs_pt);

            double dx = (rhs_pt.x() / rhs_pt.w()) - m->second->point.x();
            double dy = (rhs_pt.y() / rhs_pt.w()) - m->second->point.y();

            if (dx*dx + dy*dy <= threshold_squared) {
                ++current_num_inliers;
            }
        }

        if (inlier_count < current_num_inliers) {
            inlier_count = current_num_inliers;
        }
    }

    return ((double) inlier_count) / match.matches.size();
}


//----------------------------------------------------------------------
int bundler_utils_fill_persp_camera_ransac(
    const bundler_inters_image_sptr &image,
    int ransac_rounds,
    double inlier_threshold)
{
    const double thresh_sq = inlier_threshold * inlier_threshold;

    // Get a list of all corresponding 3d points
    vcl_vector< vgl_point_2d<double> > image_pts;
    vcl_vector< vgl_point_3d<double> > world_pts;

    // Look at every feature in the set
    vcl_vector<bundler_inters_feature_sptr>::const_iterator f;
    for (f = image->features.begin(); f != image->features.end(); ++f) {
        if ((*f)->track && (*f)->track->observed){
            //This is the image point.
            image_pts.push_back((*f)->point);

            //Now get the world point
            world_pts.push_back((*f)->track->world_point);
        }
    }

    int best_inliers = 0;

    for (int rnd = 0; rnd < ransac_rounds; ++rnd) {
        vcl_vector< vgl_point_2d<double> > curr_image_pts;
        vcl_vector< vgl_point_3d<double> > curr_world_pts;

        // Get the points to use in this RANSAC round
        int match_idxs[6];
        bundler_utils_get_distinct_indices(
            6, match_idxs, image_pts.size());

        for (int idx = 0; idx < 6; idx++) {
            curr_image_pts.push_back(image_pts[idx]);
            curr_world_pts.push_back(world_pts[idx]);
        }


        //Construct the camera from these correspondences.
        double err;
        vpgl_perspective_camera<double> camera;

        vpgl_perspective_camera_compute::compute_dlt(
            curr_image_pts, curr_world_pts, camera, err);


        // Find the inlier percentage to evaulate how good this camera
        // is.
        double inlier_count;
        for (unsigned int pt_ind = 0; pt_ind < image_pts.size(); ++pt_ind)
        {
            double u,v;
            camera.project(world_pts[pt_ind].x(), world_pts[pt_ind].y(),
                           world_pts[pt_ind].z(), u, v);

            double dx = u - image_pts[pt_ind].x();
            double dy = v - image_pts[pt_ind].y();

            if (dx*dx - dy*dy <= thresh_sq) {
                ++inlier_count;
            }
        }

        // Now see if this is the best camera so far.
        if (inlier_count > best_inliers) {
            image->camera = camera;
            best_inliers = inlier_count;
        }
    }

    return best_inliers;
}