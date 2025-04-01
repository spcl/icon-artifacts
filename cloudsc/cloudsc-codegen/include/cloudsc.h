
#ifndef __DACE_CODEGEN_CLOUDSC__
#define __DACE_CODEGEN_CLOUDSC__

#include <dace/dace.h>


struct tomcst {
    double rcpd = {};
double rd = {};
double retv = {};
double rg = {};
double rlmlt = {};
double rlstt = {};
double rlvtt = {};
double rtt = {};
double rv = {};
};


struct toethf {
    double r2es = {};
double r3ies = {};
double r3les = {};
double r4ies = {};
double r4les = {};
double r5alscp = {};
double r5alvcp = {};
double r5ies = {};
double r5les = {};
double ralfdcp = {};
double ralsdcp = {};
double ralvdcp = {};
double rkoop1 = {};
double rkoop2 = {};
double rtice = {};
double rtwat = {};
double rtwat_rtice_r = {};
};


struct tecldp {
    int laericeauto = {};
int laericesed = {};
int ncldtop = {};
int nssopt = {};
double ramid = {};
double ramin = {};
double rcl_cdenom1 = {};
double rcl_cdenom2 = {};
double rcl_cdenom3 = {};
double rcl_const1r = {};
double rcl_const1s = {};
double rcl_const2r = {};
double rcl_const3r = {};
double rcl_const4r = {};
double rcl_const5r = {};
double rcl_const6r = {};
double rcl_const7s = {};
double rcl_const8s = {};
double rcl_fac1 = {};
double rcl_fac2 = {};
double rcl_fzrab = {};
double rcl_ka273 = {};
double rcl_kk_cloud_num_land = {};
double rcl_kk_cloud_num_sea = {};
double rcl_kkaac = {};
double rcl_kkaau = {};
double rcl_kkbac = {};
double rcl_kkbaun = {};
double rcl_kkbauq = {};
double rclcrit_land = {};
double rclcrit_sea = {};
double rcldiff = {};
double rcldiff_convi = {};
double rcldtopcf = {};
double rcovpmin = {};
double rdensref = {};
double rdepliqrefdepth = {};
double rdepliqrefrate = {};
double riceinit = {};
double rkooptau = {};
double rlcritsnow = {};
double rlmin = {};
double rnice = {};
double rpecons = {};
double rprecrhmax = {};
double rsnowlin1 = {};
double rsnowlin2 = {};
double rtaumel = {};
double rthomo = {};
double rvice = {};
double rvrain = {};
double rvrfactor = {};
double rvsnow = {};
};




struct cloudsc_state_t;  // Forward declaration.

DACE_EXPORTED cloudsc_state_t *__dace_init_cloudsc(int * __restrict__ ktype, int * __restrict__ ldcum, double * __restrict__ pa, double * __restrict__ pap, double * __restrict__ paph, double * __restrict__ pccn, double * __restrict__ pclv, double * __restrict__ pcovptot, double * __restrict__ pdyna, double * __restrict__ pdyni, double * __restrict__ pdynl, double * __restrict__ pfcqlng, double * __restrict__ pfcqnng, double * __restrict__ pfcqrng, double * __restrict__ pfcqsng, double * __restrict__ pfhpsl, double * __restrict__ pfhpsn, double * __restrict__ pfplsl, double * __restrict__ pfplsn, double * __restrict__ pfsqif, double * __restrict__ pfsqitur, double * __restrict__ pfsqlf, double * __restrict__ pfsqltur, double * __restrict__ pfsqrf, double * __restrict__ pfsqsf, double * __restrict__ phrlw, double * __restrict__ phrsw, double * __restrict__ picrit_aer, double * __restrict__ plcrit_aer, double * __restrict__ plsm, double * __restrict__ plu, double * __restrict__ plude, double * __restrict__ pmfd, double * __restrict__ pmfu, double * __restrict__ pnice, double * __restrict__ pq, double * __restrict__ prainfrac_toprfz, double * __restrict__ pre_ice, double * __restrict__ psnde, double * __restrict__ psupsat, double * __restrict__ pt, double * __restrict__ ptendency_loc_a, double * __restrict__ ptendency_loc_cld, double * __restrict__ ptendency_loc_q, double * __restrict__ ptendency_loc_t, double * __restrict__ ptendency_tmp_a, double * __restrict__ ptendency_tmp_cld, double * __restrict__ ptendency_tmp_q, double * __restrict__ ptendency_tmp_t, double * __restrict__ pvervel, double * __restrict__ pvfa, double * __restrict__ pvfi, double * __restrict__ pvfl, tomcst* ydcst, tecldp* ydecldp, toethf* ydthf, int kfdia, int kfldx, int kidia, int klev, int klon, double ptsphy);
DACE_EXPORTED int __dace_exit_cloudsc(cloudsc_state_t *__state);
DACE_EXPORTED void __program_cloudsc(cloudsc_state_t *__state, int * __restrict__ ktype, int * __restrict__ ldcum, double * __restrict__ pa, double * __restrict__ pap, double * __restrict__ paph, double * __restrict__ pccn, double * __restrict__ pclv, double * __restrict__ pcovptot, double * __restrict__ pdyna, double * __restrict__ pdyni, double * __restrict__ pdynl, double * __restrict__ pfcqlng, double * __restrict__ pfcqnng, double * __restrict__ pfcqrng, double * __restrict__ pfcqsng, double * __restrict__ pfhpsl, double * __restrict__ pfhpsn, double * __restrict__ pfplsl, double * __restrict__ pfplsn, double * __restrict__ pfsqif, double * __restrict__ pfsqitur, double * __restrict__ pfsqlf, double * __restrict__ pfsqltur, double * __restrict__ pfsqrf, double * __restrict__ pfsqsf, double * __restrict__ phrlw, double * __restrict__ phrsw, double * __restrict__ picrit_aer, double * __restrict__ plcrit_aer, double * __restrict__ plsm, double * __restrict__ plu, double * __restrict__ plude, double * __restrict__ pmfd, double * __restrict__ pmfu, double * __restrict__ pnice, double * __restrict__ pq, double * __restrict__ prainfrac_toprfz, double * __restrict__ pre_ice, double * __restrict__ psnde, double * __restrict__ psupsat, double * __restrict__ pt, double * __restrict__ ptendency_loc_a, double * __restrict__ ptendency_loc_cld, double * __restrict__ ptendency_loc_q, double * __restrict__ ptendency_loc_t, double * __restrict__ ptendency_tmp_a, double * __restrict__ ptendency_tmp_cld, double * __restrict__ ptendency_tmp_q, double * __restrict__ ptendency_tmp_t, double * __restrict__ pvervel, double * __restrict__ pvfa, double * __restrict__ pvfi, double * __restrict__ pvfl, tomcst* ydcst, tecldp* ydecldp, toethf* ydthf, int kfdia, int kfldx, int kidia, int klev, int klon, double ptsphy);

#endif // __DACE_CODEGEN_CLOUDSC__
