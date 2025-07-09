#define SPAWN_READERS(prefix, name, type, namespc)                             \
  auto fut_##name = spawn(pool, [&] {                                          \
    return namespc::t0_t1_pair<type>(ROOT, #prefix "." #name, n);              \
  });

#define UNWRAP_DATA_PAIR(name) auto [name##_in, name##_want] = fut_##name.get();

#define SPAWN_WRITERS(prefix, name, type, namespc)                             \
  pool.emplace_back([&] {                                                      \
    namespc::got_want_pair<type>(name##_in, name##_want, #prefix "." #name, n, \
                                 DUMP);                                        \
  });

#define SPAWN_ALL_READERS(prefix, namespc)                                     \
  SPAWN_READERS(prefix, global_data, namespc::global_data_type, namespc)       \
  SPAWN_READERS(prefix, p_nh, namespc::t_nh_state, namespc)                    \
  SPAWN_READERS(prefix, p_nh_prog_nnow, namespc::t_nh_prog, namespc)           \
  SPAWN_READERS(prefix, p_nh_prog_nnew, namespc::t_nh_prog, namespc)           \
  SPAWN_READERS(prefix, p_patch, namespc::t_patch, namespc)                    \
  SPAWN_READERS(prefix, p_int, namespc::t_int_state, namespc)                  \
  SPAWN_READERS(prefix, prep_adv, namespc::t_prepare_adv, namespc)             \
  SPAWN_READERS(prefix, nnow, int, namespc)                                    \
  SPAWN_READERS(prefix, nnew, int, namespc)                                    \
  SPAWN_READERS(prefix, l_init, int, namespc)                                  \
  SPAWN_READERS(prefix, l_recompute, int, namespc)                             \
  SPAWN_READERS(prefix, lsave_mflx, int, namespc)                              \
  SPAWN_READERS(prefix, lprep_adv, int, namespc)                               \
  SPAWN_READERS(prefix, lclean_mflx, int, namespc)                             \
  SPAWN_READERS(prefix, idyn_timestep, int, namespc)                           \
  SPAWN_READERS(prefix, jstep, int, namespc)                                   \
  SPAWN_READERS(prefix, dtime, double, namespc)                                \
  SPAWN_READERS(prefix, lacc, int, namespc)                                    \
  SPAWN_READERS(prefix, jb, int, namespc)                                      \
  SPAWN_READERS(prefix, jk, int, namespc)                                      \
  SPAWN_READERS(prefix, jc, int, namespc)                                      \
  SPAWN_READERS(prefix, je, int, namespc)                                      \
  SPAWN_READERS(prefix, jks, int, namespc)                                     \
  SPAWN_READERS(prefix, jg, int, namespc)                                      \
  SPAWN_READERS(prefix, nlev, int, namespc)                                    \
  SPAWN_READERS(prefix, nlevp1, int, namespc)                                  \
  SPAWN_READERS(prefix, i_startblk, int, namespc)                              \
  SPAWN_READERS(prefix, i_endblk, int, namespc)                                \
  SPAWN_READERS(prefix, i_startidx, int, namespc)                              \
  SPAWN_READERS(prefix, i_endidx, int, namespc)                                \
  SPAWN_READERS(prefix, ishift, int, namespc)                                  \
  SPAWN_READERS(prefix, rl_start, int, namespc)                                \
  SPAWN_READERS(prefix, rl_end, int, namespc)                                  \
  SPAWN_READERS(prefix, istep, int, namespc)                                   \
  SPAWN_READERS(prefix, ntl1, int, namespc)                                    \
  SPAWN_READERS(prefix, ntl2, int, namespc)                                    \
  SPAWN_READERS(prefix, nvar, int, namespc)                                    \
  SPAWN_READERS(prefix, nshift, int, namespc)                                  \
  SPAWN_READERS(prefix, nshift_total, int, namespc)                            \
  SPAWN_READERS(prefix, z_theta_v_fl_e, double *, namespc)                     \
  SPAWN_READERS(prefix, z_theta_v_e, double *, namespc)                        \
  SPAWN_READERS(prefix, z_rho_e, double *, namespc)                            \
  SPAWN_READERS(prefix, z_theta_v_v, double *, namespc)                        \
  SPAWN_READERS(prefix, z_rho_v, double *, namespc)                            \
  SPAWN_READERS(prefix, z_th_ddz_exner_c, double *, namespc)                   \
  SPAWN_READERS(prefix, z_dexner_dz_c, double *, namespc)                      \
  SPAWN_READERS(prefix, z_vt_ie, double *, namespc)                            \
  SPAWN_READERS(prefix, z_kin_hor_e, double *, namespc)                        \
  SPAWN_READERS(prefix, z_exner_ex_pr, double *, namespc)                      \
  SPAWN_READERS(prefix, z_gradh_exner, double *, namespc)                      \
  SPAWN_READERS(prefix, z_rth_pr, double *, namespc)                           \
  SPAWN_READERS(prefix, z_grad_rth, double *, namespc)                         \
  SPAWN_READERS(prefix, z_w_concorr_me, double *, namespc)                     \
  SPAWN_READERS(prefix, z_graddiv_vn, double *, namespc)                       \
  SPAWN_READERS(prefix, z_w_expl, double *, namespc)                           \
  SPAWN_READERS(prefix, z_vn_avg, double *, namespc)                           \
  SPAWN_READERS(prefix, z_mflx_top, double *, namespc)                         \
  SPAWN_READERS(prefix, z_contr_w_fl_l, double *, namespc)                     \
  SPAWN_READERS(prefix, z_rho_expl, double *, namespc)                         \
  SPAWN_READERS(prefix, z_exner_expl, double *, namespc)                       \
  SPAWN_READERS(prefix, z_theta_tavg_m1, double, namespc)                      \
  SPAWN_READERS(prefix, z_theta_tavg, double, namespc)                         \
  SPAWN_READERS(prefix, z_rho_tavg_m1, double, namespc)                        \
  SPAWN_READERS(prefix, z_rho_tavg, double, namespc)                           \
  SPAWN_READERS(prefix, z_alpha, double *, namespc)                            \
  SPAWN_READERS(prefix, z_beta, double *, namespc)                             \
  SPAWN_READERS(prefix, z_q, double *, namespc)                                \
  SPAWN_READERS(prefix, z_graddiv2_vn, double *, namespc)                      \
  SPAWN_READERS(prefix, z_theta_v_pr_ic, double *, namespc)                    \
  SPAWN_READERS(prefix, z_exner_ic, double *, namespc)                         \
  SPAWN_READERS(prefix, z_w_concorr_mc, double *, namespc)                     \
  SPAWN_READERS(prefix, z_flxdiv_mass, double *, namespc)                      \
  SPAWN_READERS(prefix, z_flxdiv_theta, double *, namespc)                     \
  SPAWN_READERS(prefix, z_hydro_corr, double *, namespc)                       \
  SPAWN_READERS(prefix, z_a, double, namespc)                                  \
  SPAWN_READERS(prefix, z_b, double, namespc)                                  \
  SPAWN_READERS(prefix, z_c, double, namespc)                                  \
  SPAWN_READERS(prefix, z_g, double, namespc)                                  \
  SPAWN_READERS(prefix, z_gamma, double, namespc)                              \
  SPAWN_READERS(prefix, z_w_backtraj, double, namespc)                         \
  SPAWN_READERS(prefix, z_theta_v_pr_mc_m1, double, namespc)                   \
  SPAWN_READERS(prefix, z_theta_v_pr_mc, double, namespc)                      \
  SPAWN_READERS(prefix, z_theta1, double, namespc)                             \
  SPAWN_READERS(prefix, z_theta2, double, namespc)                             \
  SPAWN_READERS(prefix, wgt_nnow_vel, double, namespc)                         \
  SPAWN_READERS(prefix, wgt_nnew_vel, double, namespc)                         \
  SPAWN_READERS(prefix, dt_shift, double, namespc)                             \
  SPAWN_READERS(prefix, wgt_nnow_rth, double, namespc)                         \
  SPAWN_READERS(prefix, wgt_nnew_rth, double, namespc)                         \
  SPAWN_READERS(prefix, dthalf, double, namespc)                               \
  SPAWN_READERS(prefix, r_nsubsteps, double, namespc)                          \
  SPAWN_READERS(prefix, r_dtimensubsteps, double, namespc)                     \
  SPAWN_READERS(prefix, scal_divdamp_o2, double, namespc)                      \
  SPAWN_READERS(prefix, alin, double, namespc)                                 \
  SPAWN_READERS(prefix, dz32, double, namespc)                                 \
  SPAWN_READERS(prefix, df32, double, namespc)                                 \
  SPAWN_READERS(prefix, dz42, double, namespc)                                 \
  SPAWN_READERS(prefix, df42, double, namespc)                                 \
  SPAWN_READERS(prefix, bqdr, double, namespc)                                 \
  SPAWN_READERS(prefix, aqdr, double, namespc)                                 \
  SPAWN_READERS(prefix, zf, double, namespc)                                   \
  SPAWN_READERS(prefix, dzlin, double, namespc)                                \
  SPAWN_READERS(prefix, dzqdr, double, namespc)                                \
  SPAWN_READERS(prefix, dt_linintp_ubc, double, namespc)                       \
  SPAWN_READERS(prefix, dt_linintp_ubc_nnow, double, namespc)                  \
  SPAWN_READERS(prefix, dt_linintp_ubc_nnew, double, namespc)                  \
  SPAWN_READERS(prefix, z_raylfac, double *, namespc)                          \
  SPAWN_READERS(prefix, z_ntdistv_bary_1, double, namespc)                     \
  SPAWN_READERS(prefix, distv_bary_1, double, namespc)                         \
  SPAWN_READERS(prefix, z_ntdistv_bary_2, double, namespc)                     \
  SPAWN_READERS(prefix, distv_bary_2, double, namespc)                         \
  SPAWN_READERS(prefix, scal_divdamp, double *, namespc)                       \
  SPAWN_READERS(prefix, bdy_divdamp, double *, namespc)                        \
  SPAWN_READERS(prefix, enh_divdamp_fac, double *, namespc)                    \
  SPAWN_READERS(prefix, z_dwdz_dd, double *, namespc)                          \
  SPAWN_READERS(prefix, z_ddt_vn_dyn, double, namespc)                         \
  SPAWN_READERS(prefix, z_ddt_vn_apc, double, namespc)                         \
  SPAWN_READERS(prefix, z_ddt_vn_cor, double, namespc)                         \
  SPAWN_READERS(prefix, z_ddt_vn_pgr, double, namespc)                         \
  SPAWN_READERS(prefix, z_ddt_vn_ray, double, namespc)                         \
  SPAWN_READERS(prefix, z_d_vn_dmp, double, namespc)                           \
  SPAWN_READERS(prefix, z_d_vn_iau, double, namespc)                           \
  SPAWN_READERS(prefix, nproma_gradp, int, namespc)                            \
  SPAWN_READERS(prefix, nblks_gradp, int, namespc)                             \
  SPAWN_READERS(prefix, npromz_gradp, int, namespc)                            \
  SPAWN_READERS(prefix, nlen_gradp, int, namespc)                              \
  SPAWN_READERS(prefix, jk_start, int, namespc)                                \
  SPAWN_READERS(prefix, lvn_only, int, namespc)                                \
  SPAWN_READERS(prefix, lvn_pos, int, namespc)                                 \
  SPAWN_READERS(prefix, l_vert_nested, int, namespc)                           \
  SPAWN_READERS(prefix, l_child_vertnest, int, namespc)

#define UNWRAP_ALL_DATA_PAIRS()                                                \
  UNWRAP_DATA_PAIR(alin)                                                       \
  UNWRAP_DATA_PAIR(aqdr)                                                       \
  UNWRAP_DATA_PAIR(bdy_divdamp)                                                \
  UNWRAP_DATA_PAIR(bqdr)                                                       \
  UNWRAP_DATA_PAIR(df32)                                                       \
  UNWRAP_DATA_PAIR(df42)                                                       \
  UNWRAP_DATA_PAIR(distv_bary_1)                                               \
  UNWRAP_DATA_PAIR(distv_bary_2)                                               \
  UNWRAP_DATA_PAIR(dt_linintp_ubc)                                             \
  UNWRAP_DATA_PAIR(dt_linintp_ubc_nnew)                                        \
  UNWRAP_DATA_PAIR(dt_linintp_ubc_nnow)                                        \
  UNWRAP_DATA_PAIR(dt_shift)                                                   \
  UNWRAP_DATA_PAIR(dthalf)                                                     \
  UNWRAP_DATA_PAIR(dtime)                                                      \
  UNWRAP_DATA_PAIR(dz32)                                                       \
  UNWRAP_DATA_PAIR(dz42)                                                       \
  UNWRAP_DATA_PAIR(dzlin)                                                      \
  UNWRAP_DATA_PAIR(dzqdr)                                                      \
  UNWRAP_DATA_PAIR(enh_divdamp_fac)                                            \
  UNWRAP_DATA_PAIR(global_data)                                                \
  UNWRAP_DATA_PAIR(i_endblk)                                                   \
  UNWRAP_DATA_PAIR(i_endidx)                                                   \
  UNWRAP_DATA_PAIR(i_startblk)                                                 \
  UNWRAP_DATA_PAIR(i_startidx)                                                 \
  UNWRAP_DATA_PAIR(idyn_timestep)                                              \
  UNWRAP_DATA_PAIR(ishift)                                                     \
  UNWRAP_DATA_PAIR(istep)                                                      \
  UNWRAP_DATA_PAIR(jb)                                                         \
  UNWRAP_DATA_PAIR(jc)                                                         \
  UNWRAP_DATA_PAIR(je)                                                         \
  UNWRAP_DATA_PAIR(jg)                                                         \
  UNWRAP_DATA_PAIR(jk_start)                                                   \
  UNWRAP_DATA_PAIR(jk)                                                         \
  UNWRAP_DATA_PAIR(jks)                                                        \
  UNWRAP_DATA_PAIR(jstep)                                                      \
  UNWRAP_DATA_PAIR(l_child_vertnest)                                           \
  UNWRAP_DATA_PAIR(l_init)                                                     \
  UNWRAP_DATA_PAIR(l_recompute)                                                \
  UNWRAP_DATA_PAIR(l_vert_nested)                                              \
  UNWRAP_DATA_PAIR(lacc)                                                       \
  UNWRAP_DATA_PAIR(lclean_mflx)                                                \
  UNWRAP_DATA_PAIR(lprep_adv)                                                  \
  UNWRAP_DATA_PAIR(lsave_mflx)                                                 \
  UNWRAP_DATA_PAIR(lvn_only)                                                   \
  UNWRAP_DATA_PAIR(lvn_pos)                                                    \
  UNWRAP_DATA_PAIR(nblks_gradp)                                                \
  UNWRAP_DATA_PAIR(nlen_gradp)                                                 \
  UNWRAP_DATA_PAIR(nlev)                                                       \
  UNWRAP_DATA_PAIR(nlevp1)                                                     \
  UNWRAP_DATA_PAIR(nnew)                                                       \
  UNWRAP_DATA_PAIR(nnow)                                                       \
  UNWRAP_DATA_PAIR(nproma_gradp)                                               \
  UNWRAP_DATA_PAIR(npromz_gradp)                                               \
  UNWRAP_DATA_PAIR(nshift_total)                                               \
  UNWRAP_DATA_PAIR(nshift)                                                     \
  UNWRAP_DATA_PAIR(ntl1)                                                       \
  UNWRAP_DATA_PAIR(ntl2)                                                       \
  UNWRAP_DATA_PAIR(nvar)                                                       \
  UNWRAP_DATA_PAIR(p_int)                                                      \
  UNWRAP_DATA_PAIR(p_nh)                                                       \
  UNWRAP_DATA_PAIR(p_nh_prog_nnow)                                             \
  UNWRAP_DATA_PAIR(p_nh_prog_nnew)                                             \
  UNWRAP_DATA_PAIR(p_patch)                                                    \
  UNWRAP_DATA_PAIR(prep_adv)                                                   \
  UNWRAP_DATA_PAIR(r_dtimensubsteps)                                           \
  UNWRAP_DATA_PAIR(r_nsubsteps)                                                \
  UNWRAP_DATA_PAIR(rl_end)                                                     \
  UNWRAP_DATA_PAIR(rl_start)                                                   \
  UNWRAP_DATA_PAIR(scal_divdamp_o2)                                            \
  UNWRAP_DATA_PAIR(scal_divdamp)                                               \
  UNWRAP_DATA_PAIR(wgt_nnew_rth)                                               \
  UNWRAP_DATA_PAIR(wgt_nnew_vel)                                               \
  UNWRAP_DATA_PAIR(wgt_nnow_rth)                                               \
  UNWRAP_DATA_PAIR(wgt_nnow_vel)                                               \
  UNWRAP_DATA_PAIR(z_a)                                                        \
  UNWRAP_DATA_PAIR(z_alpha)                                                    \
  UNWRAP_DATA_PAIR(z_b)                                                        \
  UNWRAP_DATA_PAIR(z_beta)                                                     \
  UNWRAP_DATA_PAIR(z_c)                                                        \
  UNWRAP_DATA_PAIR(z_contr_w_fl_l)                                             \
  UNWRAP_DATA_PAIR(z_d_vn_dmp)                                                 \
  UNWRAP_DATA_PAIR(z_d_vn_iau)                                                 \
  UNWRAP_DATA_PAIR(z_ddt_vn_apc)                                               \
  UNWRAP_DATA_PAIR(z_ddt_vn_cor)                                               \
  UNWRAP_DATA_PAIR(z_ddt_vn_dyn)                                               \
  UNWRAP_DATA_PAIR(z_ddt_vn_pgr)                                               \
  UNWRAP_DATA_PAIR(z_ddt_vn_ray)                                               \
  UNWRAP_DATA_PAIR(z_dexner_dz_c)                                              \
  UNWRAP_DATA_PAIR(z_dwdz_dd)                                                  \
  UNWRAP_DATA_PAIR(z_exner_ex_pr)                                              \
  UNWRAP_DATA_PAIR(z_exner_expl)                                               \
  UNWRAP_DATA_PAIR(z_exner_ic)                                                 \
  UNWRAP_DATA_PAIR(z_flxdiv_mass)                                              \
  UNWRAP_DATA_PAIR(z_flxdiv_theta)                                             \
  UNWRAP_DATA_PAIR(z_g)                                                        \
  UNWRAP_DATA_PAIR(z_gamma)                                                    \
  UNWRAP_DATA_PAIR(z_grad_rth)                                                 \
  UNWRAP_DATA_PAIR(z_graddiv_vn)                                               \
  UNWRAP_DATA_PAIR(z_graddiv2_vn)                                              \
  UNWRAP_DATA_PAIR(z_gradh_exner)                                              \
  UNWRAP_DATA_PAIR(z_hydro_corr)                                               \
  UNWRAP_DATA_PAIR(z_kin_hor_e)                                                \
  UNWRAP_DATA_PAIR(z_mflx_top)                                                 \
  UNWRAP_DATA_PAIR(z_ntdistv_bary_1)                                           \
  UNWRAP_DATA_PAIR(z_ntdistv_bary_2)                                           \
  UNWRAP_DATA_PAIR(z_q)                                                        \
  UNWRAP_DATA_PAIR(z_raylfac)                                                  \
  UNWRAP_DATA_PAIR(z_rho_e)                                                    \
  UNWRAP_DATA_PAIR(z_rho_expl)                                                 \
  UNWRAP_DATA_PAIR(z_rho_tavg_m1)                                              \
  UNWRAP_DATA_PAIR(z_rho_tavg)                                                 \
  UNWRAP_DATA_PAIR(z_rho_v)                                                    \
  UNWRAP_DATA_PAIR(z_rth_pr)                                                   \
  UNWRAP_DATA_PAIR(z_th_ddz_exner_c)                                           \
  UNWRAP_DATA_PAIR(z_theta_tavg_m1)                                            \
  UNWRAP_DATA_PAIR(z_theta_tavg)                                               \
  UNWRAP_DATA_PAIR(z_theta_v_e)                                                \
  UNWRAP_DATA_PAIR(z_theta_v_fl_e)                                             \
  UNWRAP_DATA_PAIR(z_theta_v_pr_ic)                                            \
  UNWRAP_DATA_PAIR(z_theta_v_pr_mc_m1)                                         \
  UNWRAP_DATA_PAIR(z_theta_v_pr_mc)                                            \
  UNWRAP_DATA_PAIR(z_theta_v_v)                                                \
  UNWRAP_DATA_PAIR(z_theta1)                                                   \
  UNWRAP_DATA_PAIR(z_theta2)                                                   \
  UNWRAP_DATA_PAIR(z_vn_avg)                                                   \
  UNWRAP_DATA_PAIR(z_vt_ie)                                                    \
  UNWRAP_DATA_PAIR(z_w_backtraj)                                               \
  UNWRAP_DATA_PAIR(z_w_concorr_mc)                                             \
  UNWRAP_DATA_PAIR(z_w_concorr_me)                                             \
  UNWRAP_DATA_PAIR(z_w_expl)                                                   \
  UNWRAP_DATA_PAIR(zf)

#define SPAWN_ALL_WRITERS(prefix, namespc)                                     \
  SPAWN_WRITERS(prefix, global_data, namespc::global_data_type, namespc)       \
  SPAWN_WRITERS(prefix, p_nh, namespc::t_nh_state, namespc)                    \
  SPAWN_WRITERS(prefix, p_nh_prog_nnow, namespc::t_nh_prog, namespc)           \
  SPAWN_WRITERS(prefix, p_nh_prog_nnew, namespc::t_nh_prog, namespc)           \
  SPAWN_WRITERS(prefix, p_patch, namespc::t_patch, namespc)                    \
  SPAWN_WRITERS(prefix, p_int, namespc::t_int_state, namespc)                  \
  SPAWN_WRITERS(prefix, prep_adv, namespc::t_prepare_adv, namespc)             \
  SPAWN_WRITERS(prefix, nnow, int, namespc)                                    \
  SPAWN_WRITERS(prefix, nnew, int, namespc)                                    \
  SPAWN_WRITERS(prefix, l_init, int, namespc)                                  \
  SPAWN_WRITERS(prefix, l_recompute, int, namespc)                             \
  SPAWN_WRITERS(prefix, lsave_mflx, int, namespc)                              \
  SPAWN_WRITERS(prefix, lprep_adv, int, namespc)                               \
  SPAWN_WRITERS(prefix, lclean_mflx, int, namespc)                             \
  SPAWN_WRITERS(prefix, idyn_timestep, int, namespc)                           \
  SPAWN_WRITERS(prefix, jstep, int, namespc)                                   \
  SPAWN_WRITERS(prefix, dtime, double, namespc)                                \
  SPAWN_WRITERS(prefix, lacc, int, namespc)                                    \
  SPAWN_WRITERS(prefix, jb, int, namespc)                                      \
  SPAWN_WRITERS(prefix, jk, int, namespc)                                      \
  SPAWN_WRITERS(prefix, jc, int, namespc)                                      \
  SPAWN_WRITERS(prefix, je, int, namespc)                                      \
  SPAWN_WRITERS(prefix, jks, int, namespc)                                     \
  SPAWN_WRITERS(prefix, jg, int, namespc)                                      \
  SPAWN_WRITERS(prefix, nlev, int, namespc)                                    \
  SPAWN_WRITERS(prefix, nlevp1, int, namespc)                                  \
  SPAWN_WRITERS(prefix, i_startblk, int, namespc)                              \
  SPAWN_WRITERS(prefix, i_endblk, int, namespc)                                \
  SPAWN_WRITERS(prefix, i_startidx, int, namespc)                              \
  SPAWN_WRITERS(prefix, i_endidx, int, namespc)                                \
  SPAWN_WRITERS(prefix, ishift, int, namespc)                                  \
  SPAWN_WRITERS(prefix, rl_start, int, namespc)                                \
  SPAWN_WRITERS(prefix, rl_end, int, namespc)                                  \
  SPAWN_WRITERS(prefix, istep, int, namespc)                                   \
  SPAWN_WRITERS(prefix, ntl1, int, namespc)                                    \
  SPAWN_WRITERS(prefix, ntl2, int, namespc)                                    \
  SPAWN_WRITERS(prefix, nvar, int, namespc)                                    \
  SPAWN_WRITERS(prefix, nshift, int, namespc)                                  \
  SPAWN_WRITERS(prefix, nshift_total, int, namespc)                            \
  SPAWN_WRITERS(prefix, z_theta_v_fl_e, double *, namespc)                     \
  SPAWN_WRITERS(prefix, z_theta_v_e, double *, namespc)                        \
  SPAWN_WRITERS(prefix, z_rho_e, double *, namespc)                            \
  SPAWN_WRITERS(prefix, z_theta_v_v, double *, namespc)                        \
  SPAWN_WRITERS(prefix, z_rho_v, double *, namespc)                            \
  SPAWN_WRITERS(prefix, z_th_ddz_exner_c, double *, namespc)                   \
  SPAWN_WRITERS(prefix, z_dexner_dz_c, double *, namespc)                      \
  SPAWN_WRITERS(prefix, z_vt_ie, double *, namespc)                            \
  SPAWN_WRITERS(prefix, z_kin_hor_e, double *, namespc)                        \
  SPAWN_WRITERS(prefix, z_exner_ex_pr, double *, namespc)                      \
  SPAWN_WRITERS(prefix, z_gradh_exner, double *, namespc)                      \
  SPAWN_WRITERS(prefix, z_rth_pr, double *, namespc)                           \
  SPAWN_WRITERS(prefix, z_grad_rth, double *, namespc)                         \
  SPAWN_WRITERS(prefix, z_w_concorr_me, double *, namespc)                     \
  SPAWN_WRITERS(prefix, z_graddiv_vn, double *, namespc)                       \
  SPAWN_WRITERS(prefix, z_w_expl, double *, namespc)                           \
  SPAWN_WRITERS(prefix, z_vn_avg, double *, namespc)                           \
  SPAWN_WRITERS(prefix, z_mflx_top, double *, namespc)                         \
  SPAWN_WRITERS(prefix, z_contr_w_fl_l, double *, namespc)                     \
  SPAWN_WRITERS(prefix, z_rho_expl, double *, namespc)                         \
  SPAWN_WRITERS(prefix, z_exner_expl, double *, namespc)                       \
  SPAWN_WRITERS(prefix, z_theta_tavg_m1, double, namespc)                      \
  SPAWN_WRITERS(prefix, z_theta_tavg, double, namespc)                         \
  SPAWN_WRITERS(prefix, z_rho_tavg_m1, double, namespc)                        \
  SPAWN_WRITERS(prefix, z_rho_tavg, double, namespc)                           \
  SPAWN_WRITERS(prefix, z_alpha, double *, namespc)                            \
  SPAWN_WRITERS(prefix, z_beta, double *, namespc)                             \
  SPAWN_WRITERS(prefix, z_q, double *, namespc)                                \
  SPAWN_WRITERS(prefix, z_graddiv2_vn, double *, namespc)                      \
  SPAWN_WRITERS(prefix, z_theta_v_pr_ic, double *, namespc)                    \
  SPAWN_WRITERS(prefix, z_exner_ic, double *, namespc)                         \
  SPAWN_WRITERS(prefix, z_w_concorr_mc, double *, namespc)                     \
  SPAWN_WRITERS(prefix, z_flxdiv_mass, double *, namespc)                      \
  SPAWN_WRITERS(prefix, z_flxdiv_theta, double *, namespc)                     \
  SPAWN_WRITERS(prefix, z_hydro_corr, double *, namespc)                       \
  SPAWN_WRITERS(prefix, z_a, double, namespc)                                  \
  SPAWN_WRITERS(prefix, z_b, double, namespc)                                  \
  SPAWN_WRITERS(prefix, z_c, double, namespc)                                  \
  SPAWN_WRITERS(prefix, z_g, double, namespc)                                  \
  SPAWN_WRITERS(prefix, z_gamma, double, namespc)                              \
  SPAWN_WRITERS(prefix, z_w_backtraj, double, namespc)                         \
  SPAWN_WRITERS(prefix, z_theta_v_pr_mc_m1, double, namespc)                   \
  SPAWN_WRITERS(prefix, z_theta_v_pr_mc, double, namespc)                      \
  SPAWN_WRITERS(prefix, z_theta1, double, namespc)                             \
  SPAWN_WRITERS(prefix, z_theta2, double, namespc)                             \
  SPAWN_WRITERS(prefix, wgt_nnow_vel, double, namespc)                         \
  SPAWN_WRITERS(prefix, wgt_nnew_vel, double, namespc)                         \
  SPAWN_WRITERS(prefix, dt_shift, double, namespc)                             \
  SPAWN_WRITERS(prefix, wgt_nnow_rth, double, namespc)                         \
  SPAWN_WRITERS(prefix, wgt_nnew_rth, double, namespc)                         \
  SPAWN_WRITERS(prefix, dthalf, double, namespc)                               \
  SPAWN_WRITERS(prefix, r_nsubsteps, double, namespc)                          \
  SPAWN_WRITERS(prefix, r_dtimensubsteps, double, namespc)                     \
  SPAWN_WRITERS(prefix, scal_divdamp_o2, double, namespc)                      \
  SPAWN_WRITERS(prefix, alin, double, namespc)                                 \
  SPAWN_WRITERS(prefix, dz32, double, namespc)                                 \
  SPAWN_WRITERS(prefix, df32, double, namespc)                                 \
  SPAWN_WRITERS(prefix, dz42, double, namespc)                                 \
  SPAWN_WRITERS(prefix, df42, double, namespc)                                 \
  SPAWN_WRITERS(prefix, bqdr, double, namespc)                                 \
  SPAWN_WRITERS(prefix, aqdr, double, namespc)                                 \
  SPAWN_WRITERS(prefix, zf, double, namespc)                                   \
  SPAWN_WRITERS(prefix, dzlin, double, namespc)                                \
  SPAWN_WRITERS(prefix, dzqdr, double, namespc)                                \
  SPAWN_WRITERS(prefix, dt_linintp_ubc, double, namespc)                       \
  SPAWN_WRITERS(prefix, dt_linintp_ubc_nnow, double, namespc)                  \
  SPAWN_WRITERS(prefix, dt_linintp_ubc_nnew, double, namespc)                  \
  SPAWN_WRITERS(prefix, z_raylfac, double *, namespc)                          \
  SPAWN_WRITERS(prefix, z_ntdistv_bary_1, double, namespc)                     \
  SPAWN_WRITERS(prefix, distv_bary_1, double, namespc)                         \
  SPAWN_WRITERS(prefix, z_ntdistv_bary_2, double, namespc)                     \
  SPAWN_WRITERS(prefix, distv_bary_2, double, namespc)                         \
  SPAWN_WRITERS(prefix, scal_divdamp, double *, namespc)                       \
  SPAWN_WRITERS(prefix, bdy_divdamp, double *, namespc)                        \
  SPAWN_WRITERS(prefix, enh_divdamp_fac, double *, namespc)                    \
  SPAWN_WRITERS(prefix, z_dwdz_dd, double *, namespc)                          \
  SPAWN_WRITERS(prefix, z_ddt_vn_dyn, double, namespc)                         \
  SPAWN_WRITERS(prefix, z_ddt_vn_apc, double, namespc)                         \
  SPAWN_WRITERS(prefix, z_ddt_vn_cor, double, namespc)                         \
  SPAWN_WRITERS(prefix, z_ddt_vn_pgr, double, namespc)                         \
  SPAWN_WRITERS(prefix, z_ddt_vn_ray, double, namespc)                         \
  SPAWN_WRITERS(prefix, z_d_vn_dmp, double, namespc)                           \
  SPAWN_WRITERS(prefix, z_d_vn_iau, double, namespc)                           \
  SPAWN_WRITERS(prefix, nproma_gradp, int, namespc)                            \
  SPAWN_WRITERS(prefix, nblks_gradp, int, namespc)                             \
  SPAWN_WRITERS(prefix, npromz_gradp, int, namespc)                            \
  SPAWN_WRITERS(prefix, nlen_gradp, int, namespc)                              \
  SPAWN_WRITERS(prefix, jk_start, int, namespc)                                \
  SPAWN_WRITERS(prefix, lvn_only, int, namespc)                                \
  SPAWN_WRITERS(prefix, lvn_pos, int, namespc)                                 \
  SPAWN_WRITERS(prefix, l_vert_nested, int, namespc)                           \
  SPAWN_WRITERS(prefix, l_child_vertnest, int, namespc)
