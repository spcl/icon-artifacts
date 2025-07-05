#define SPAWN_DIAG(prefix, name, type)                                         \
  auto fut_##name = spawn(                                                     \
      pool, [&] { return t0_t1_pair<type>(ROOT, #prefix "." #name, n); });

#define UNWRAP_DIAG(name) auto [name##_in, name##_want] = fut_##name.get();

#define DUMP_DIAG(prefix, name, type)                                          \
  pool.emplace_back([&] {                                                      \
    got_want_pair<type>(name##_in, name##_want, #prefix "." #name, n, DUMP);   \
  });

#define SPAWN_ALL_DIAGS(prefix)                                                \
  SPAWN_DIAG(prefix, global_data, global_data_type)                            \
  SPAWN_DIAG(prefix, p_nh, t_nh_state)                                         \
  SPAWN_DIAG(prefix, p_patch, t_patch)                                         \
  SPAWN_DIAG(prefix, p_int, t_int_state)                                       \
  SPAWN_DIAG(prefix, prep_adv, t_prepare_adv)                                  \
  SPAWN_DIAG(prefix, nnow, int)                                                \
  SPAWN_DIAG(prefix, nnew, int)                                                \
  SPAWN_DIAG(prefix, l_init, int)                                              \
  SPAWN_DIAG(prefix, l_recompute, int)                                         \
  SPAWN_DIAG(prefix, lsave_mflx, int)                                          \
  SPAWN_DIAG(prefix, lprep_adv, int)                                           \
  SPAWN_DIAG(prefix, lclean_mflx, int)                                         \
  SPAWN_DIAG(prefix, idyn_timestep, int)                                       \
  SPAWN_DIAG(prefix, jstep, int)                                               \
  SPAWN_DIAG(prefix, dtime, int)                                               \
  SPAWN_DIAG(prefix, lacc, int)                                                \
  SPAWN_DIAG(prefix, jb, int)                                                  \
  SPAWN_DIAG(prefix, jk, int)                                                  \
  SPAWN_DIAG(prefix, jc, int)                                                  \
  SPAWN_DIAG(prefix, je, int)                                                  \
  SPAWN_DIAG(prefix, jks, int)                                                 \
  SPAWN_DIAG(prefix, jg, int)                                                  \
  SPAWN_DIAG(prefix, nlev, int)                                                \
  SPAWN_DIAG(prefix, nlevp1, int)                                              \
  SPAWN_DIAG(prefix, i_startblk, int)                                          \
  SPAWN_DIAG(prefix, i_endblk, int)                                            \
  SPAWN_DIAG(prefix, i_startidx, int)                                          \
  SPAWN_DIAG(prefix, i_endidx, int)                                            \
  SPAWN_DIAG(prefix, ishift, int)                                              \
  SPAWN_DIAG(prefix, rl_start, int)                                            \
  SPAWN_DIAG(prefix, rl_end, int)                                              \
  SPAWN_DIAG(prefix, istep, int)                                               \
  SPAWN_DIAG(prefix, ntl1, int)                                                \
  SPAWN_DIAG(prefix, ntl2, int)                                                \
  SPAWN_DIAG(prefix, nvar, int)                                                \
  SPAWN_DIAG(prefix, nshift, int)                                              \
  SPAWN_DIAG(prefix, nshift_total, int)                                        \
  SPAWN_DIAG(prefix, z_theta_v_fl_e, double *)                                 \
  SPAWN_DIAG(prefix, z_theta_v_e, double *)                                    \
  SPAWN_DIAG(prefix, z_rho_e, double *)                                        \
  SPAWN_DIAG(prefix, z_theta_v_v, double *)                                    \
  SPAWN_DIAG(prefix, z_rho_v, double *)                                        \
  SPAWN_DIAG(prefix, z_th_ddz_exner_c, double *)                               \
  SPAWN_DIAG(prefix, z_dexner_dz_c, double *)                                  \
  SPAWN_DIAG(prefix, z_vt_ie, double *)                                        \
  SPAWN_DIAG(prefix, z_kin_hor_e, double *)                                    \
  SPAWN_DIAG(prefix, z_exner_ex_pr, double *)                                  \
  SPAWN_DIAG(prefix, z_gradh_exner, double *)                                  \
  SPAWN_DIAG(prefix, z_rth_pr, double *)                                       \
  SPAWN_DIAG(prefix, z_grad_rth, double *)                                     \
  SPAWN_DIAG(prefix, z_w_concorr_me, double *)                                 \
  SPAWN_DIAG(prefix, z_graddiv_vn, double *)                                   \
  SPAWN_DIAG(prefix, z_w_expl, double *)                                       \
  SPAWN_DIAG(prefix, z_vn_avg, double *)                                       \
  SPAWN_DIAG(prefix, z_mflx_top, double *)                                     \
  SPAWN_DIAG(prefix, z_contr_w_fl_l, double *)                                 \
  SPAWN_DIAG(prefix, z_rho_expl, double *)                                     \
  SPAWN_DIAG(prefix, z_exner_expl, double *)                                   \
  SPAWN_DIAG(prefix, z_theta_tavg_m1, double)                                  \
  SPAWN_DIAG(prefix, z_theta_tavg, double)                                     \
  SPAWN_DIAG(prefix, z_rho_tavg_m1, double)                                    \
  SPAWN_DIAG(prefix, z_rho_tavg, double)                                       \
  SPAWN_DIAG(prefix, z_alpha, double *)                                        \
  SPAWN_DIAG(prefix, z_beta, double *)                                         \
  SPAWN_DIAG(prefix, z_q, double *)                                            \
  SPAWN_DIAG(prefix, z_graddiv2_vn, double *)                                  \
  SPAWN_DIAG(prefix, z_theta_v_pr_ic, double *)                                \
  SPAWN_DIAG(prefix, z_exner_ic, double *)                                     \
  SPAWN_DIAG(prefix, z_w_concorr_mc, double *)                                 \
  SPAWN_DIAG(prefix, z_flxdiv_mass, double *)                                  \
  SPAWN_DIAG(prefix, z_flxdiv_theta, double *)                                 \
  SPAWN_DIAG(prefix, z_hydro_corr, double *)                                   \
  SPAWN_DIAG(prefix, z_a, double)                                              \
  SPAWN_DIAG(prefix, z_b, double)                                              \
  SPAWN_DIAG(prefix, z_c, double)                                              \
  SPAWN_DIAG(prefix, z_g, double)                                              \
  SPAWN_DIAG(prefix, z_gamma, double)                                          \
  SPAWN_DIAG(prefix, z_w_backtraj, double)                                     \
  SPAWN_DIAG(prefix, z_theta_v_pr_mc_m1, double)                               \
  SPAWN_DIAG(prefix, z_theta_v_pr_mc, double)                                  \
  SPAWN_DIAG(prefix, z_theta1, double)                                         \
  SPAWN_DIAG(prefix, z_theta2, double)                                         \
  SPAWN_DIAG(prefix, wgt_nnow_vel, double)                                     \
  SPAWN_DIAG(prefix, wgt_nnew_vel, double)                                     \
  SPAWN_DIAG(prefix, dt_shift, double)                                         \
  SPAWN_DIAG(prefix, wgt_nnow_rth, double)                                     \
  SPAWN_DIAG(prefix, wgt_nnew_rth, double)                                     \
  SPAWN_DIAG(prefix, dthalf, double)                                           \
  SPAWN_DIAG(prefix, r_nsubsteps, double)                                      \
  SPAWN_DIAG(prefix, r_dtimensubsteps, double)                                 \
  SPAWN_DIAG(prefix, scal_divdamp_o2, double)                                  \
  SPAWN_DIAG(prefix, alin, double)                                             \
  SPAWN_DIAG(prefix, dz32, double)                                             \
  SPAWN_DIAG(prefix, df32, double)                                             \
  SPAWN_DIAG(prefix, dz42, double)                                             \
  SPAWN_DIAG(prefix, df42, double)                                             \
  SPAWN_DIAG(prefix, bqdr, double)                                             \
  SPAWN_DIAG(prefix, aqdr, double)                                             \
  SPAWN_DIAG(prefix, zf, double)                                               \
  SPAWN_DIAG(prefix, dzlin, double)                                            \
  SPAWN_DIAG(prefix, dzqdr, double)                                            \
  SPAWN_DIAG(prefix, dt_linintp_ubc, double)                                   \
  SPAWN_DIAG(prefix, dt_linintp_ubc_nnow, double)                              \
  SPAWN_DIAG(prefix, dt_linintp_ubc_nnew, double)                              \
  SPAWN_DIAG(prefix, z_raylfac, double *)                                      \
  SPAWN_DIAG(prefix, z_ntdistv_bary_1, double)                                 \
  SPAWN_DIAG(prefix, distv_bary_1, double)                                     \
  SPAWN_DIAG(prefix, z_ntdistv_bary_2, double)                                 \
  SPAWN_DIAG(prefix, distv_bary_2, double)                                     \
  SPAWN_DIAG(prefix, scal_divdamp, double *)                                   \
  SPAWN_DIAG(prefix, bdy_divdamp, double *)                                    \
  SPAWN_DIAG(prefix, enh_divdamp_fac, double *)                                \
  SPAWN_DIAG(prefix, z_dwdz_dd, double *)                                      \
  SPAWN_DIAG(prefix, z_ddt_vn_dyn, double)                                     \
  SPAWN_DIAG(prefix, z_ddt_vn_apc, double)                                     \
  SPAWN_DIAG(prefix, z_ddt_vn_cor, double)                                     \
  SPAWN_DIAG(prefix, z_ddt_vn_pgr, double)                                     \
  SPAWN_DIAG(prefix, z_ddt_vn_ray, double)                                     \
  SPAWN_DIAG(prefix, z_d_vn_dmp, double)                                       \
  SPAWN_DIAG(prefix, z_d_vn_iau, double)                                       \
  SPAWN_DIAG(prefix, nproma_gradp, int)                                        \
  SPAWN_DIAG(prefix, nblks_gradp, int)                                         \
  SPAWN_DIAG(prefix, npromz_gradp, int)                                        \
  SPAWN_DIAG(prefix, nlen_gradp, int)                                          \
  SPAWN_DIAG(prefix, jk_start, int)                                            \
  SPAWN_DIAG(prefix, lvn_only, int)                                            \
  SPAWN_DIAG(prefix, lvn_pos, int)                                             \
  SPAWN_DIAG(prefix, l_vert_nested, int)                                       \
  SPAWN_DIAG(prefix, l_child_vertnest, int)

#define UNWRAP_ALL_DIAGS                                                       \
  UNWRAP_DIAG(alin)                                                            \
  UNWRAP_DIAG(aqdr)                                                            \
  UNWRAP_DIAG(bdy_divdamp)                                                     \
  UNWRAP_DIAG(bqdr)                                                            \
  UNWRAP_DIAG(df32)                                                            \
  UNWRAP_DIAG(df42)                                                            \
  UNWRAP_DIAG(distv_bary_1)                                                    \
  UNWRAP_DIAG(distv_bary_2)                                                    \
  UNWRAP_DIAG(dt_linintp_ubc)                                                  \
  UNWRAP_DIAG(dt_linintp_ubc_nnew)                                             \
  UNWRAP_DIAG(dt_linintp_ubc_nnow)                                             \
  UNWRAP_DIAG(dt_shift)                                                        \
  UNWRAP_DIAG(dthalf)                                                          \
  UNWRAP_DIAG(dtime)                                                           \
  UNWRAP_DIAG(dz32)                                                            \
  UNWRAP_DIAG(dz42)                                                            \
  UNWRAP_DIAG(dzlin)                                                           \
  UNWRAP_DIAG(dzqdr)                                                           \
  UNWRAP_DIAG(enh_divdamp_fac)                                                 \
  UNWRAP_DIAG(global_data)                                                     \
  UNWRAP_DIAG(i_endblk)                                                        \
  UNWRAP_DIAG(i_endidx)                                                        \
  UNWRAP_DIAG(i_startblk)                                                      \
  UNWRAP_DIAG(i_startidx)                                                      \
  UNWRAP_DIAG(idyn_timestep)                                                   \
  UNWRAP_DIAG(ishift)                                                          \
  UNWRAP_DIAG(istep)                                                           \
  UNWRAP_DIAG(jb)                                                              \
  UNWRAP_DIAG(jc)                                                              \
  UNWRAP_DIAG(je)                                                              \
  UNWRAP_DIAG(jg)                                                              \
  UNWRAP_DIAG(jk_start)                                                        \
  UNWRAP_DIAG(jk)                                                              \
  UNWRAP_DIAG(jks)                                                             \
  UNWRAP_DIAG(jstep)                                                           \
  UNWRAP_DIAG(l_child_vertnest)                                                \
  UNWRAP_DIAG(l_init)                                                          \
  UNWRAP_DIAG(l_recompute)                                                     \
  UNWRAP_DIAG(l_vert_nested)                                                   \
  UNWRAP_DIAG(lacc)                                                            \
  UNWRAP_DIAG(lclean_mflx)                                                     \
  UNWRAP_DIAG(lprep_adv)                                                       \
  UNWRAP_DIAG(lsave_mflx)                                                      \
  UNWRAP_DIAG(lvn_only)                                                        \
  UNWRAP_DIAG(lvn_pos)                                                         \
  UNWRAP_DIAG(nblks_gradp)                                                     \
  UNWRAP_DIAG(nlen_gradp)                                                      \
  UNWRAP_DIAG(nlev)                                                            \
  UNWRAP_DIAG(nlevp1)                                                          \
  UNWRAP_DIAG(nnew)                                                            \
  UNWRAP_DIAG(nnow)                                                            \
  UNWRAP_DIAG(nproma_gradp)                                                    \
  UNWRAP_DIAG(npromz_gradp)                                                    \
  UNWRAP_DIAG(nshift_total)                                                    \
  UNWRAP_DIAG(nshift)                                                          \
  UNWRAP_DIAG(ntl1)                                                            \
  UNWRAP_DIAG(ntl2)                                                            \
  UNWRAP_DIAG(nvar)                                                            \
  UNWRAP_DIAG(p_int)                                                           \
  UNWRAP_DIAG(p_nh)                                                            \
  UNWRAP_DIAG(p_patch)                                                         \
  UNWRAP_DIAG(prep_adv)                                                        \
  UNWRAP_DIAG(r_dtimensubsteps)                                                \
  UNWRAP_DIAG(r_nsubsteps)                                                     \
  UNWRAP_DIAG(rl_end)                                                          \
  UNWRAP_DIAG(rl_start)                                                        \
  UNWRAP_DIAG(scal_divdamp_o2)                                                 \
  UNWRAP_DIAG(scal_divdamp)                                                    \
  UNWRAP_DIAG(wgt_nnew_rth)                                                    \
  UNWRAP_DIAG(wgt_nnew_vel)                                                    \
  UNWRAP_DIAG(wgt_nnow_rth)                                                    \
  UNWRAP_DIAG(wgt_nnow_vel)                                                    \
  UNWRAP_DIAG(z_a)                                                             \
  UNWRAP_DIAG(z_alpha)                                                         \
  UNWRAP_DIAG(z_b)                                                             \
  UNWRAP_DIAG(z_beta)                                                          \
  UNWRAP_DIAG(z_c)                                                             \
  UNWRAP_DIAG(z_contr_w_fl_l)                                                  \
  UNWRAP_DIAG(z_d_vn_dmp)                                                      \
  UNWRAP_DIAG(z_d_vn_iau)                                                      \
  UNWRAP_DIAG(z_ddt_vn_apc)                                                    \
  UNWRAP_DIAG(z_ddt_vn_cor)                                                    \
  UNWRAP_DIAG(z_ddt_vn_dyn)                                                    \
  UNWRAP_DIAG(z_ddt_vn_pgr)                                                    \
  UNWRAP_DIAG(z_ddt_vn_ray)                                                    \
  UNWRAP_DIAG(z_dexner_dz_c)                                                   \
  UNWRAP_DIAG(z_dwdz_dd)                                                       \
  UNWRAP_DIAG(z_exner_ex_pr)                                                   \
  UNWRAP_DIAG(z_exner_expl)                                                    \
  UNWRAP_DIAG(z_exner_ic)                                                      \
  UNWRAP_DIAG(z_flxdiv_mass)                                                   \
  UNWRAP_DIAG(z_flxdiv_theta)                                                  \
  UNWRAP_DIAG(z_g)                                                             \
  UNWRAP_DIAG(z_gamma)                                                         \
  UNWRAP_DIAG(z_grad_rth)                                                      \
  UNWRAP_DIAG(z_graddiv_vn)                                                    \
  UNWRAP_DIAG(z_graddiv2_vn)                                                   \
  UNWRAP_DIAG(z_gradh_exner)                                                   \
  UNWRAP_DIAG(z_hydro_corr)                                                    \
  UNWRAP_DIAG(z_kin_hor_e)                                                     \
  UNWRAP_DIAG(z_mflx_top)                                                      \
  UNWRAP_DIAG(z_ntdistv_bary_1)                                                \
  UNWRAP_DIAG(z_ntdistv_bary_2)                                                \
  UNWRAP_DIAG(z_q)                                                             \
  UNWRAP_DIAG(z_raylfac)                                                       \
  UNWRAP_DIAG(z_rho_e)                                                         \
  UNWRAP_DIAG(z_rho_expl)                                                      \
  UNWRAP_DIAG(z_rho_tavg_m1)                                                   \
  UNWRAP_DIAG(z_rho_tavg)                                                      \
  UNWRAP_DIAG(z_rho_v)                                                         \
  UNWRAP_DIAG(z_rth_pr)                                                        \
  UNWRAP_DIAG(z_th_ddz_exner_c)                                                \
  UNWRAP_DIAG(z_theta_tavg_m1)                                                 \
  UNWRAP_DIAG(z_theta_tavg)                                                    \
  UNWRAP_DIAG(z_theta_v_e)                                                     \
  UNWRAP_DIAG(z_theta_v_fl_e)                                                  \
  UNWRAP_DIAG(z_theta_v_pr_ic)                                                 \
  UNWRAP_DIAG(z_theta_v_pr_mc_m1)                                              \
  UNWRAP_DIAG(z_theta_v_pr_mc)                                                 \
  UNWRAP_DIAG(z_theta_v_v)                                                     \
  UNWRAP_DIAG(z_theta1)                                                        \
  UNWRAP_DIAG(z_theta2)                                                        \
  UNWRAP_DIAG(z_vn_avg)                                                        \
  UNWRAP_DIAG(z_vt_ie)                                                         \
  UNWRAP_DIAG(z_w_backtraj)                                                    \
  UNWRAP_DIAG(z_w_concorr_mc)                                                  \
  UNWRAP_DIAG(z_w_concorr_me)                                                  \
  UNWRAP_DIAG(z_w_expl)                                                        \
  UNWRAP_DIAG(zf)

#define DUMP_ALL_DIAGS(prefix)                                                 \
  DUMP_DIAG(prefix, global_data, global_data_type)                             \
  DUMP_DIAG(prefix, p_nh, t_nh_state)                                          \
  DUMP_DIAG(prefix, p_patch, t_patch)                                          \
  DUMP_DIAG(prefix, p_int, t_int_state)                                        \
  DUMP_DIAG(prefix, prep_adv, t_prepare_adv)                                   \
  DUMP_DIAG(prefix, nnow, int)                                                 \
  DUMP_DIAG(prefix, nnew, int)                                                 \
  DUMP_DIAG(prefix, l_init, int)                                               \
  DUMP_DIAG(prefix, l_recompute, int)                                          \
  DUMP_DIAG(prefix, lsave_mflx, int)                                           \
  DUMP_DIAG(prefix, lprep_adv, int)                                            \
  DUMP_DIAG(prefix, lclean_mflx, int)                                          \
  DUMP_DIAG(prefix, idyn_timestep, int)                                        \
  DUMP_DIAG(prefix, jstep, int)                                                \
  DUMP_DIAG(prefix, dtime, double)                                             \
  DUMP_DIAG(prefix, lacc, int)                                                 \
  DUMP_DIAG(prefix, jb, int)                                                   \
  DUMP_DIAG(prefix, jk, int)                                                   \
  DUMP_DIAG(prefix, jc, int)                                                   \
  DUMP_DIAG(prefix, je, int)                                                   \
  DUMP_DIAG(prefix, jks, int)                                                  \
  DUMP_DIAG(prefix, jg, int)                                                   \
  DUMP_DIAG(prefix, nlev, int)                                                 \
  DUMP_DIAG(prefix, nlevp1, int)                                               \
  DUMP_DIAG(prefix, i_startblk, int)                                           \
  DUMP_DIAG(prefix, i_endblk, int)                                             \
  DUMP_DIAG(prefix, i_startidx, int)                                           \
  DUMP_DIAG(prefix, i_endidx, int)                                             \
  DUMP_DIAG(prefix, ishift, int)                                               \
  DUMP_DIAG(prefix, rl_start, int)                                             \
  DUMP_DIAG(prefix, rl_end, int)                                               \
  DUMP_DIAG(prefix, istep, int)                                                \
  DUMP_DIAG(prefix, ntl1, int)                                                 \
  DUMP_DIAG(prefix, ntl2, int)                                                 \
  DUMP_DIAG(prefix, nvar, int)                                                 \
  DUMP_DIAG(prefix, nshift, int)                                               \
  DUMP_DIAG(prefix, nshift_total, int)                                         \
  DUMP_DIAG(prefix, z_theta_v_fl_e, double *)                                  \
  DUMP_DIAG(prefix, z_theta_v_e, double *)                                     \
  DUMP_DIAG(prefix, z_rho_e, double *)                                         \
  DUMP_DIAG(prefix, z_theta_v_v, double *)                                     \
  DUMP_DIAG(prefix, z_rho_v, double *)                                         \
  DUMP_DIAG(prefix, z_th_ddz_exner_c, double *)                                \
  DUMP_DIAG(prefix, z_dexner_dz_c, double *)                                   \
  DUMP_DIAG(prefix, z_vt_ie, double *)                                         \
  DUMP_DIAG(prefix, z_kin_hor_e, double *)                                     \
  DUMP_DIAG(prefix, z_exner_ex_pr, double *)                                   \
  DUMP_DIAG(prefix, z_gradh_exner, double *)                                   \
  DUMP_DIAG(prefix, z_rth_pr, double *)                                        \
  DUMP_DIAG(prefix, z_grad_rth, double *)                                      \
  DUMP_DIAG(prefix, z_w_concorr_me, double *)                                  \
  DUMP_DIAG(prefix, z_graddiv_vn, double *)                                    \
  DUMP_DIAG(prefix, z_w_expl, double *)                                        \
  DUMP_DIAG(prefix, z_vn_avg, double *)                                        \
  DUMP_DIAG(prefix, z_mflx_top, double *)                                      \
  DUMP_DIAG(prefix, z_contr_w_fl_l, double *)                                  \
  DUMP_DIAG(prefix, z_rho_expl, double *)                                      \
  DUMP_DIAG(prefix, z_exner_expl, double *)                                    \
  DUMP_DIAG(prefix, z_theta_tavg_m1, double)                                   \
  DUMP_DIAG(prefix, z_theta_tavg, double)                                      \
  DUMP_DIAG(prefix, z_rho_tavg_m1, double)                                     \
  DUMP_DIAG(prefix, z_rho_tavg, double)                                        \
  DUMP_DIAG(prefix, z_alpha, double *)                                         \
  DUMP_DIAG(prefix, z_beta, double *)                                          \
  DUMP_DIAG(prefix, z_q, double *)                                             \
  DUMP_DIAG(prefix, z_graddiv2_vn, double *)                                   \
  DUMP_DIAG(prefix, z_theta_v_pr_ic, double *)                                 \
  DUMP_DIAG(prefix, z_exner_ic, double *)                                      \
  DUMP_DIAG(prefix, z_w_concorr_mc, double *)                                  \
  DUMP_DIAG(prefix, z_flxdiv_mass, double *)                                   \
  DUMP_DIAG(prefix, z_flxdiv_theta, double *)                                  \
  DUMP_DIAG(prefix, z_hydro_corr, double *)                                    \
  DUMP_DIAG(prefix, z_a, double)                                               \
  DUMP_DIAG(prefix, z_b, double)                                               \
  DUMP_DIAG(prefix, z_c, double)                                               \
  DUMP_DIAG(prefix, z_g, double)                                               \
  DUMP_DIAG(prefix, z_gamma, double)                                           \
  DUMP_DIAG(prefix, z_w_backtraj, double)                                      \
  DUMP_DIAG(prefix, z_theta_v_pr_mc_m1, double)                                \
  DUMP_DIAG(prefix, z_theta_v_pr_mc, double)                                   \
  DUMP_DIAG(prefix, z_theta1, double)                                          \
  DUMP_DIAG(prefix, z_theta2, double)                                          \
  DUMP_DIAG(prefix, wgt_nnow_vel, double)                                      \
  DUMP_DIAG(prefix, wgt_nnew_vel, double)                                      \
  DUMP_DIAG(prefix, dt_shift, double)                                          \
  DUMP_DIAG(prefix, wgt_nnow_rth, double)                                      \
  DUMP_DIAG(prefix, wgt_nnew_rth, double)                                      \
  DUMP_DIAG(prefix, dthalf, double)                                            \
  DUMP_DIAG(prefix, r_nsubsteps, double)                                       \
  DUMP_DIAG(prefix, r_dtimensubsteps, double)                                  \
  DUMP_DIAG(prefix, scal_divdamp_o2, double)                                   \
  DUMP_DIAG(prefix, alin, double)                                              \
  DUMP_DIAG(prefix, dz32, double)                                              \
  DUMP_DIAG(prefix, df32, double)                                              \
  DUMP_DIAG(prefix, dz42, double)                                              \
  DUMP_DIAG(prefix, df42, double)                                              \
  DUMP_DIAG(prefix, bqdr, double)                                              \
  DUMP_DIAG(prefix, aqdr, double)                                              \
  DUMP_DIAG(prefix, zf, double)                                                \
  DUMP_DIAG(prefix, dzlin, double)                                             \
  DUMP_DIAG(prefix, dzqdr, double)                                             \
  DUMP_DIAG(prefix, dt_linintp_ubc, double)                                    \
  DUMP_DIAG(prefix, dt_linintp_ubc_nnow, double)                               \
  DUMP_DIAG(prefix, dt_linintp_ubc_nnew, double)                               \
  DUMP_DIAG(prefix, z_raylfac, double *)                                       \
  DUMP_DIAG(prefix, z_ntdistv_bary_1, double)                                  \
  DUMP_DIAG(prefix, distv_bary_1, double)                                      \
  DUMP_DIAG(prefix, z_ntdistv_bary_2, double)                                  \
  DUMP_DIAG(prefix, distv_bary_2, double)                                      \
  DUMP_DIAG(prefix, scal_divdamp, double *)                                    \
  DUMP_DIAG(prefix, bdy_divdamp, double *)                                     \
  DUMP_DIAG(prefix, enh_divdamp_fac, double *)                                 \
  DUMP_DIAG(prefix, z_dwdz_dd, double *)                                       \
  DUMP_DIAG(prefix, z_ddt_vn_dyn, double)                                      \
  DUMP_DIAG(prefix, z_ddt_vn_apc, double)                                      \
  DUMP_DIAG(prefix, z_ddt_vn_cor, double)                                      \
  DUMP_DIAG(prefix, z_ddt_vn_pgr, double)                                      \
  DUMP_DIAG(prefix, z_ddt_vn_ray, double)                                      \
  DUMP_DIAG(prefix, z_d_vn_dmp, double)                                        \
  DUMP_DIAG(prefix, z_d_vn_iau, double)                                        \
  DUMP_DIAG(prefix, nproma_gradp, int)                                         \
  DUMP_DIAG(prefix, nblks_gradp, int)                                          \
  DUMP_DIAG(prefix, npromz_gradp, int)                                         \
  DUMP_DIAG(prefix, nlen_gradp, int)                                           \
  DUMP_DIAG(prefix, jk_start, int)                                             \
  DUMP_DIAG(prefix, lvn_only, int)                                             \
  DUMP_DIAG(prefix, lvn_pos, int)                                              \
  DUMP_DIAG(prefix, l_vert_nested, int)                                        \
  DUMP_DIAG(prefix, l_child_vertnest, int)
