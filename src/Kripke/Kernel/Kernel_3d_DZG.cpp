#include<Kripke/Kernel/Kernel_3d_DZG.h>
#include<Kripke/User_Data.h>
#include<Kripke/SubTVec.h>

Kernel_3d_DZG::Kernel_3d_DZG() {

}

Kernel_3d_DZG::~Kernel_3d_DZG() {

}

Nesting_Order Kernel_3d_DZG::nestingPsi(void) const {
  return NEST_DZG;
}

Nesting_Order Kernel_3d_DZG::nestingPhi(void) const {
  return NEST_DZG;
}

void Kernel_3d_DZG::LTimes(Grid_Data *grid_data) {
  // Outer parameters
  int num_zones = grid_data->num_zones;
  int nidx = grid_data->nm_table.size();
  int num_directions = grid_data->ell->directions;
  int num_groups = grid_data->phi->groups;

  grid_data->phi->clear(0.0);

  // Loop over Subdomains
  int num_subdomains = grid_data->subdomains.size();
  for (int sdom_id = 0; sdom_id < num_subdomains; ++ sdom_id){
    Subdomain &sdom = grid_data->subdomains[sdom_id];

    // Get dimensioning
    int num_local_groups = sdom.num_groups;
    int group0 = sdom.group0;
    int num_local_directions = sdom.num_directions;
    int dir0 = sdom.direction0;

    /* 3D Cartesian Geometry */
    double * KRESTRICT ell = grid_data->ell->ptr(0, dir0, 0);
    double * KRESTRICT phi_ptr = grid_data->phi->ptr(group0, 0, 0);
    for(int nm_offset = 0;nm_offset < nidx;++nm_offset){
      double * KRESTRICT psi_ptr = sdom.psi->ptr();

      for (int d = 0; d < num_local_directions; d++) {
        double ell_nm_d = ell[d];


#ifdef KRIPKE_USE_OPENMP
#pragma omp parallel for
#endif
        for (int z = 0;z < num_zones;++ z){
          double * KRESTRICT phi = phi_ptr + num_groups*z;
          double * KRESTRICT psi = psi_ptr + num_local_groups*z;

          for(int group = 0;group < num_local_groups; ++ group){
            phi[group] += ell_nm_d * psi[group];
          }

        }
        psi_ptr += num_zones*num_local_groups;
      }
      ell += num_directions;
      phi_ptr += num_groups*num_zones;
    }

  } // Subdomain
}

void Kernel_3d_DZG::LPlusTimes(Grid_Data *grid_data) {
  // Outer parameters
  int num_zones = grid_data->num_zones;
  int nidx = grid_data->nm_table.size();
  int num_groups = grid_data->phi_out->groups;

  // Loop over Subdomains
  int num_subdomains = grid_data->subdomains.size();
  for (int sdom_id = 0; sdom_id < num_subdomains; ++ sdom_id){
    Subdomain &sdom = grid_data->subdomains[sdom_id];


    // Get dimensioning
    int num_local_groups = sdom.num_groups;
    int group0 = sdom.group0;
    int num_local_directions = sdom.num_directions;
    int dir0 = sdom.direction0;
    int num_groups_zones = num_local_groups*num_zones;

    // Get Variables
    sdom.rhs->clear(0.0);

    /* 3D Cartesian Geometry */
    double * KRESTRICT ell_plus = grid_data->ell_plus->ptr(0, dir0, 0);

    for (int d = 0; d < num_local_directions; d++) {
      double * KRESTRICT phi_out_ptr = grid_data->phi_out->ptr(group0, 0, 0);
      double * KRESTRICT rhs_ptr = sdom.rhs->ptr(0, d, 0);

      for(int nm_offset = 0;nm_offset < nidx;++nm_offset){
        double ell_plus_d_nm = ell_plus[nm_offset];

#ifdef KRIPKE_USE_OPENMP
#pragma omp parallel for
#endif
        for(int z = 0;z < num_zones;++ z){
          double * KRESTRICT rhs = rhs_ptr + num_local_groups*z;
          double * KRESTRICT phi_out = phi_out_ptr + num_groups*z;


          for(int group = 0;group < num_local_groups;++ group){
            rhs[group] += ell_plus_d_nm * phi_out[group];
          }
        }
        phi_out_ptr += num_groups*num_zones;
      }
      ell_plus += nidx;
    }
  } // Subdomain
}

/* Sweep routine for Diamond-Difference */
/* Macros for offsets with fluxes on cell faces */
#define I_PLANE_INDEX(j, k) (k)*(local_jmax) + (j)
#define J_PLANE_INDEX(i, k) (k)*(local_imax) + (i)
#define K_PLANE_INDEX(i, j) (j)*(local_imax) + (i)
#define Zonal_INDEX(i, j, k) (i) + (local_imax)*(j) \
  + (local_imax)*(local_jmax)*(k)

void Kernel_3d_DZG::sweep(Grid_Data *grid_data, Subdomain *sdom,
    double *i_plane_ptr, double *j_plane_ptr, double *k_plane_ptr) {
  int num_directions = sdom->num_directions;
  int num_groups = sdom->num_groups;
  int num_zones = grid_data->num_zones;

  Directions *direction = sdom->directions;

  int local_imax = grid_data->nzones[0];
  int local_jmax = grid_data->nzones[1];
  int local_kmax = grid_data->nzones[2];
  int local_imax_1 = local_imax + 1;
  int local_jmax_1 = local_jmax + 1;

  double * dx = &grid_data->deltas[0][0];
  double * dy = &grid_data->deltas[1][0];
  double * dz = &grid_data->deltas[2][0];

  // Alias the MPI data with a SubTVec for the face data
  SubTVec i_plane(nestingPsi(), num_groups, num_directions,
      local_jmax * local_kmax, i_plane_ptr);
  SubTVec j_plane(nestingPsi(), num_groups, num_directions,
      local_imax * local_kmax, j_plane_ptr);
  SubTVec k_plane(nestingPsi(), num_groups, num_directions,
      local_imax * local_jmax, k_plane_ptr);

  // All directions have same id,jd,kd, since these are all one Direction Set
  // So pull that information out now
  int octant = direction[0].octant;
  Grid_Sweep_Block const &extent = grid_data->octant_extent[octant];

#ifdef KRIPKE_USE_OPENMP
#pragma omp parallel for
#endif
  for (int d = 0; d < num_directions; ++d) {
    double xcos = direction[d].xcos;
    double ycos = direction[d].ycos;
    double zcos = direction[d].zcos;

    /*  Perform transport sweep of the grid 1 cell at a time.   */
    for (int k = extent.start_k; k != extent.end_k; k += extent.inc_k) {
      double dzk = dz[k + 1];
      double zcos_dzk = 2.0 * zcos / dzk;
      for (int j = extent.start_j; j != extent.end_j; j += extent.inc_j) {
        double dyj = dy[j + 1];
        double ycos_dyj = 2.0 * ycos / dyj;
        for (int i = extent.start_i; i != extent.end_i; i += extent.inc_i) {
          double dxi = dx[i + 1];
          double xcos_dxi = 2.0 * xcos / dxi;

          int z = Zonal_INDEX(i, j, k);
          double * KRESTRICT psi_d_z = sdom->psi->ptr(0, d, z);
          double * KRESTRICT rhs_d_z = sdom->rhs->ptr(0, d, z);

          double * KRESTRICT psi_lf_d_z = i_plane.ptr(0, d, I_PLANE_INDEX(j, k));
          double * KRESTRICT psi_fr_d_z = j_plane.ptr(0, d, J_PLANE_INDEX(i, k));
          double * KRESTRICT psi_bo_d_z = k_plane.ptr(0, d, K_PLANE_INDEX(i, j));

          double * KRESTRICT sigt_z = grid_data->sigt->ptr(sdom->group0, 0, z);

          for (int group = 0; group < num_groups; ++group) {
            /* Calculate new zonal flux */
            double psi_d_z_g = (rhs_d_z[group]
                + psi_lf_d_z[group] * xcos_dxi
                + psi_fr_d_z[group] * ycos_dyj
                + psi_bo_d_z[group] * zcos_dzk)
                / (xcos_dxi + ycos_dyj + zcos_dzk + sigt_z[group]);

            psi_d_z[group] = psi_d_z_g;

            /* Apply diamond-difference relationships */
            psi_lf_d_z[group] = 2.0 * psi_d_z_g - psi_lf_d_z[group];
            psi_fr_d_z[group] = 2.0 * psi_d_z_g - psi_fr_d_z[group];
            psi_bo_d_z[group] = 2.0 * psi_d_z_g - psi_bo_d_z[group];
          }
        }
      }
    }
  }
}

