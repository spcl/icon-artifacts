/* DaCe AUTO-GENERATED FILE. DO NOT MODIFY */
#include <dace/dace.h>
#include "../../include/hash.h"

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

struct cloudsc_state_t {

};

void __program_cloudsc_internal(cloudsc_state_t*__state, int * __restrict__ ktype, int * __restrict__ ldcum, double * __restrict__ pa, double * __restrict__ pap, double * __restrict__ paph, double * __restrict__ pccn, double * __restrict__ pclv, double * __restrict__ pcovptot, double * __restrict__ pdyna, double * __restrict__ pdyni, double * __restrict__ pdynl, double * __restrict__ pfcqlng, double * __restrict__ pfcqnng, double * __restrict__ pfcqrng, double * __restrict__ pfcqsng, double * __restrict__ pfhpsl, double * __restrict__ pfhpsn, double * __restrict__ pfplsl, double * __restrict__ pfplsn, double * __restrict__ pfsqif, double * __restrict__ pfsqitur, double * __restrict__ pfsqlf, double * __restrict__ pfsqltur, double * __restrict__ pfsqrf, double * __restrict__ pfsqsf, double * __restrict__ phrlw, double * __restrict__ phrsw, double * __restrict__ picrit_aer, double * __restrict__ plcrit_aer, double * __restrict__ plsm, double * __restrict__ plu, double * __restrict__ plude, double * __restrict__ pmfd, double * __restrict__ pmfu, double * __restrict__ pnice, double * __restrict__ pq, double * __restrict__ prainfrac_toprfz, double * __restrict__ pre_ice, double * __restrict__ psnde, double * __restrict__ psupsat, double * __restrict__ pt, double * __restrict__ ptendency_loc_a, double * __restrict__ ptendency_loc_cld, double * __restrict__ ptendency_loc_q, double * __restrict__ ptendency_loc_t, double * __restrict__ ptendency_tmp_a, double * __restrict__ ptendency_tmp_cld, double * __restrict__ ptendency_tmp_q, double * __restrict__ ptendency_tmp_t, double * __restrict__ pvervel, double * __restrict__ pvfa, double * __restrict__ pvfi, double * __restrict__ pvfl, tomcst* ydcst, tecldp* ydecldp, toethf* ydthf, int kfdia, int kfldx, int kidia, int klev, int klon, double ptsphy)
{
    double *zlcond1;
    zlcond1 = new double DACE_ALIGN(64)[klon];
    double *zlcond2;
    zlcond2 = new double DACE_ALIGN(64)[klon];
    double *zrainaut;
    zrainaut = new double DACE_ALIGN(64)[klon];
    double *zsnowaut;
    zsnowaut = new double DACE_ALIGN(64)[klon];
    double *zliqcld;
    zliqcld = new double DACE_ALIGN(64)[klon];
    double *zicecld;
    zicecld = new double DACE_ALIGN(64)[klon];
    double *zfokoop;
    zfokoop = new double DACE_ALIGN(64)[klon];
    double *zfoealfa;
    zfoealfa = new double DACE_ALIGN(64)[((klev * klon) + klon)];
    double *zicenuclei;
    zicenuclei = new double DACE_ALIGN(64)[klon];
    double *zlicld;
    zlicld = new double DACE_ALIGN(64)[klon];
    double zacond;
    double *zlfinalsum;
    zlfinalsum = new double DACE_ALIGN(64)[klon];
    double *zdqs;
    zdqs = new double DACE_ALIGN(64)[klon];
    double *ztold;
    ztold = new double DACE_ALIGN(64)[klon];
    double *zqold;
    zqold = new double DACE_ALIGN(64)[klon];
    double *zdtgdp;
    zdtgdp = new double DACE_ALIGN(64)[klon];
    double *zrdtgdp;
    zrdtgdp = new double DACE_ALIGN(64)[klon];
    double *zcovpclr;
    zcovpclr = new double DACE_ALIGN(64)[klon];
    double zpreclr;
    double *zcovptot;
    zcovptot = new double DACE_ALIGN(64)[klon];
    double *zcovpmax;
    zcovpmax = new double DACE_ALIGN(64)[klon];
    double *zqpretot;
    zqpretot = new double DACE_ALIGN(64)[klon];
    double zdpevap;
    double zdtforc;
    double *ztp1;
    ztp1 = new double DACE_ALIGN(64)[((klon * (klev - 1)) + klon)];
    double *zldefr;
    zldefr = new double DACE_ALIGN(64)[klon];
    double *zldifdt;
    zldifdt = new double DACE_ALIGN(64)[klon];
    double *zlcust;
    zlcust = new double DACE_ALIGN(64)[(5 * klon)];
    double *zacust;
    zacust = new double DACE_ALIGN(64)[klon];
    double *zmf;
    zmf = new double DACE_ALIGN(64)[klon];
    double *zrho;
    zrho = new double DACE_ALIGN(64)[klon];
    double *zsolab;
    zsolab = new double DACE_ALIGN(64)[klon];
    double *zsolac;
    zsolac = new double DACE_ALIGN(64)[klon];
    double zanew;
    double *zanewm1;
    zanewm1 = new double DACE_ALIGN(64)[klon];
    double *zda;
    zda = new double DACE_ALIGN(64)[klon];
    double *zli;
    zli = new double DACE_ALIGN(64)[((klon * (klev - 1)) + klon)];
    double *za;
    za = new double DACE_ALIGN(64)[((klon * (klev - 1)) + klon)];
    double *zaorig;
    zaorig = new double DACE_ALIGN(64)[((klon * (klev - 1)) + klon)];
    int llo1;
    double *zdp;
    zdp = new double DACE_ALIGN(64)[klon];
    double zalfa;
    double zbeta;
    double zcor;
    double zcdmax;
    double *zmin;
    zmin = new double DACE_ALIGN(64)[klon];
    double zdenom;
    double zdpmxdt;
    double zdtdp;
    double zepsec;
    double zfaci;
    double zfacw;
    double zlcrit;
    double zmfdn;
    double zqe;
    double zqsat;
    double zqtmst;
    double zrdcp;
    double zrhc;
    double zzco;
    double zzrh;
    double zqadj;
    double zrg_r;
    double zgdph_r;
    double zcons1;
    double zcond;
    double zevap;
    double zfrz;
    double zvpliq;
    double zvpice;
    double zadd;
    double *zsupsat;
    zsupsat = new double DACE_ALIGN(64)[klon];
    double zrldcp;
    int *iphase;
    iphase = new int DACE_ALIGN(64)[5];
    int *imelt;
    imelt = new int DACE_ALIGN(64)[5];
    int *llfall;
    llfall = new int DACE_ALIGN(64)[5];
    int *llindex1;
    llindex1 = new int DACE_ALIGN(64)[(5 * klon)];
    int *llindex3;
    llindex3 = new int DACE_ALIGN(64)[(25 * klon)];
    int *iorder;
    iorder = new int DACE_ALIGN(64)[(5 * klon)];
    double *zliqfrac;
    zliqfrac = new double DACE_ALIGN(64)[((klon * (klev - 1)) + klon)];
    double *zicefrac;
    zicefrac = new double DACE_ALIGN(64)[((klon * (klev - 1)) + klon)];
    double *zqx;
    zqx = new double DACE_ALIGN(64)[((((4 * klev) * klon) + (klon * (klev - 1))) + klon)];
    double *zqx0;
    zqx0 = new double DACE_ALIGN(64)[((((4 * klev) * klon) + (klon * (klev - 1))) + klon)];
    double *zqxn;
    zqxn = new double DACE_ALIGN(64)[(5 * klon)];
    double *zqxfg;
    zqxfg = new double DACE_ALIGN(64)[(5 * klon)];
    double *zqxnm1;
    zqxnm1 = new double DACE_ALIGN(64)[(5 * klon)];
    double *zfluxq;
    zfluxq = new double DACE_ALIGN(64)[(5 * klon)];
    double *zpfplsx;
    zpfplsx = new double DACE_ALIGN(64)[(((klev * klon) + ((4 * klon) * (klev + 1))) + klon)];
    double *zlneg;
    zlneg = new double DACE_ALIGN(64)[((((4 * klev) * klon) + (klon * (klev - 1))) + klon)];
    double *zmeltmax;
    zmeltmax = new double DACE_ALIGN(64)[klon];
    double *zfrzmax;
    zfrzmax = new double DACE_ALIGN(64)[klon];
    double *zicetot;
    zicetot = new double DACE_ALIGN(64)[klon];
    double *zqxn2d;
    zqxn2d = new double DACE_ALIGN(64)[((((4 * klev) * klon) + (klon * (klev - 1))) + klon)];
    double *zqsmix;
    zqsmix = new double DACE_ALIGN(64)[((klon * (klev - 1)) + klon)];
    double *zqsliq;
    zqsliq = new double DACE_ALIGN(64)[((klon * (klev - 1)) + klon)];
    double *zqsice;
    zqsice = new double DACE_ALIGN(64)[((klon * (klev - 1)) + klon)];
    double *zfoeewmt;
    zfoeewmt = new double DACE_ALIGN(64)[((klon * (klev - 1)) + klon)];
    double *zfoeew;
    zfoeew = new double DACE_ALIGN(64)[((klon * (klev - 1)) + klon)];
    double *zfoeeliqt;
    zfoeeliqt = new double DACE_ALIGN(64)[((klon * (klev - 1)) + klon)];
    double *zdqsmixdt;
    zdqsmixdt = new double DACE_ALIGN(64)[klon];
    double *zcorqsice;
    zcorqsice = new double DACE_ALIGN(64)[klon];
    double *zevaplimmix;
    zevaplimmix = new double DACE_ALIGN(64)[klon];
    double *zsolqa;
    zsolqa = new double DACE_ALIGN(64)[(25 * klon)];
    double *zsolqb;
    zsolqb = new double DACE_ALIGN(64)[(25 * klon)];
    double *zqlhs;
    zqlhs = new double DACE_ALIGN(64)[(25 * klon)];
    double *zvqx;
    zvqx = new double DACE_ALIGN(64)[5];
    double zexplicit;
    double *zratio;
    zratio = new double DACE_ALIGN(64)[(5 * klon)];
    double *zsinksum;
    zsinksum = new double DACE_ALIGN(64)[(5 * klon)];
    double *zfallsink;
    zfallsink = new double DACE_ALIGN(64)[(5 * klon)];
    double *zfallsrce;
    zfallsrce = new double DACE_ALIGN(64)[(5 * klon)];
    double *zconvsrce;
    zconvsrce = new double DACE_ALIGN(64)[(5 * klon)];
    double *zconvsink;
    zconvsink = new double DACE_ALIGN(64)[(5 * klon)];
    double *zpsupsatsrce;
    zpsupsatsrce = new double DACE_ALIGN(64)[(5 * klon)];
    double zsubsat;
    double *zcldtopdist;
    zcldtopdist = new double DACE_ALIGN(64)[klon];
    double *zrainacc;
    zrainacc = new double DACE_ALIGN(64)[klon];
    double *zraincld;
    zraincld = new double DACE_ALIGN(64)[klon];
    double *zsnowcld;
    zsnowcld = new double DACE_ALIGN(64)[klon];
    double zfallcorr;
    double zlambda;
    double zconst;
    int *llrainliq;
    llrainliq = new int DACE_ALIGN(64)[klon];
    double ztmpa;
    double zzratio;
    double zepsilon;
    double zcond1;
    double zqp;
    double oka;
    double tmp_call_0;
    double tmp_call_7;
    double tmp_call_6;
    double tmp_call_28;
    double tmp_call_29;
    double tmp_call_30;
    double tmp_call_31;
    double tmp_call_32;
    double tmp_call_94;
    double tmp_call_99;
    double tmp_call_102;
    double _if_cond_1;
    double _if_cond_2;
    double _if_cond_5;
    double _if_cond_8;
    double _if_cond_9;
    double _if_cond_10;
    double _if_cond_11;
    double _if_cond_13;
    double _if_cond_15;
    int _if_cond_16;
    double _if_cond_17;
    int _if_cond_19;
    double _if_cond_28;
    double _if_cond_30;
    double _if_cond_31;
    double _if_cond_32;
    int _if_cond_34;
    int _if_cond_35;
    int _if_cond_36;
    int _if_cond_37;
    double _if_cond_38;
    double _if_cond_40;
    double _if_cond_41;
    double _if_cond_43;
    double _if_cond_44;
    double _if_cond_45;
    int _if_cond_47;
    int _if_cond_48;
    double _if_cond_50;
    int _if_cond_52;
    double _if_cond_56;
    double _if_cond_57;
    double _if_cond_58;
    double _if_cond_59;
    double _if_cond_61;
    double _if_cond_65;
    double _if_cond_66;
    double _if_cond_67;
    double _if_cond_74;
    double _if_cond_75;
    double* v_ydcst_rg;
    v_ydcst_rg = (double*)(&(ydcst->rg));
    double* v_ydcst_rcpd;
    v_ydcst_rcpd = (double*)(&(ydcst->rcpd));
    double* v_ydcst_rd;
    v_ydcst_rd = (double*)(&(ydcst->rd));
    double* v_ydecldp_rtaumel;
    v_ydecldp_rtaumel = (double*)(&(ydecldp->rtaumel));
    double* v_ydthf_ralsdcp;
    v_ydthf_ralsdcp = (double*)(&(ydthf->ralsdcp));
    double* v_ydthf_ralvdcp;
    v_ydthf_ralvdcp = (double*)(&(ydthf->ralvdcp));
    double* v_ydecldp_rlmin;
    v_ydecldp_rlmin = (double*)(&(ydecldp->rlmin));
    double* v_ydecldp_ramin;
    v_ydecldp_ramin = (double*)(&(ydecldp->ramin));
    double* v_ydcst_retv;
    v_ydcst_retv = (double*)(&(ydcst->retv));
    int* v_ydecldp_ncldtop;
    v_ydecldp_ncldtop = (int*)(&(ydecldp->ncldtop));
    double* v_ydcst_rtt;
    v_ydcst_rtt = (double*)(&(ydcst->rtt));
    int* v_ydecldp_nssopt;
    v_ydecldp_nssopt = (int*)(&(ydecldp->nssopt));
    double* v_ydecldp_rthomo;
    v_ydecldp_rthomo = (double*)(&(ydecldp->rthomo));
    double* v_ydecldp_ramid;
    v_ydecldp_ramid = (double*)(&(ydecldp->ramid));
    double* v_ydcst_rv;
    v_ydcst_rv = (double*)(&(ydcst->rv));
    double* v_ydcst_rlstt;
    v_ydcst_rlstt = (double*)(&(ydcst->rlstt));
    double* v_ydecldp_rcovpmin;
    v_ydecldp_rcovpmin = (double*)(&(ydecldp->rcovpmin));
    double* v_ydecldp_rdensref;
    v_ydecldp_rdensref = (double*)(&(ydecldp->rdensref));
    double* v_ydecldp_rcl_fac1;
    v_ydecldp_rcl_fac1 = (double*)(&(ydecldp->rcl_fac1));
    double* v_ydecldp_rcl_fac2;
    v_ydecldp_rcl_fac2 = (double*)(&(ydecldp->rcl_fac2));
    double* v_ydecldp_rprecrhmax;
    v_ydecldp_rprecrhmax = (double*)(&(ydecldp->rprecrhmax));
    toethf** ydthf_var_12_2;
    ydthf_var_12_2 = &ydthf;
    double* v_ydthf_var_12_r3les;
    v_ydthf_var_12_r3les = (double*)(&((*ydthf_var_12_2)->r3les));
    tomcst** ydcst_var_13_2;
    ydcst_var_13_2 = &ydcst;
    double* v_ydcst_var_13_rtt;
    v_ydcst_var_13_rtt = (double*)(&((*ydcst_var_13_2)->rtt));
    double* v_ydthf_var_12_r4les;
    v_ydthf_var_12_r4les = (double*)(&((*ydthf_var_12_2)->r4les));
    double* v_ydthf_var_12_r2es;
    v_ydthf_var_12_r2es = (double*)(&((*ydthf_var_12_2)->r2es));
    tomcst** ydcst_var_19_0;
    ydcst_var_19_0 = &ydcst;
    tomcst** ydcst_var_13_0;
    ydcst_var_13_0 = &(*ydcst_var_19_0);
    toethf** ydthf_var_18_0;
    ydthf_var_18_0 = &ydthf;
    toethf** ydthf_var_12_0;
    ydthf_var_12_0 = &(*ydthf_var_18_0);
    toethf** ydthf_var_15_1;
    ydthf_var_15_1 = &ydthf;
    double* v_ydthf_var_15_r3ies;
    v_ydthf_var_15_r3ies = (double*)(&((*ydthf_var_15_1)->r3ies));
    tomcst** ydcst_var_16_1;
    ydcst_var_16_1 = &ydcst;
    double* v_ydcst_var_16_rtt;
    v_ydcst_var_16_rtt = (double*)(&((*ydcst_var_16_1)->rtt));
    double* v_ydthf_var_15_r4ies;
    v_ydthf_var_15_r4ies = (double*)(&((*ydthf_var_15_1)->r4ies));
    double* v_ydthf_var_15_r2es;
    v_ydthf_var_15_r2es = (double*)(&((*ydthf_var_15_1)->r2es));
    toethf** ydthf_var_15_0;
    ydthf_var_15_0 = &(*ydthf_var_18_0);
    tomcst** ydcst_var_16_0;
    ydcst_var_16_0 = &(*ydcst_var_19_0);
    toethf** ydthf_var_8_2;
    ydthf_var_8_2 = &ydthf;
    double* v_ydthf_var_8_r4ies;
    v_ydthf_var_8_r4ies = (double*)(&((*ydthf_var_8_2)->r4ies));
    double* v_ydthf_var_8_r4les;
    v_ydthf_var_8_r4les = (double*)(&((*ydthf_var_8_2)->r4les));
    double* v_ydthf_var_8_r5alvcp;
    v_ydthf_var_8_r5alvcp = (double*)(&((*ydthf_var_8_2)->r5alvcp));
    double* v_ydthf_var_8_r5alscp;
    v_ydthf_var_8_r5alscp = (double*)(&((*ydthf_var_8_2)->r5alscp));
    toethf** ydthf_var_3_2;
    ydthf_var_3_2 = &ydthf;
    double* v_ydthf_var_3_rtwat;
    v_ydthf_var_3_rtwat = (double*)(&((*ydthf_var_3_2)->rtwat));
    double* v_ydthf_var_3_rtice;
    v_ydthf_var_3_rtice = (double*)(&((*ydthf_var_3_2)->rtice));
    double* v_ydthf_var_3_rtwat_rtice_r;
    v_ydthf_var_3_rtwat_rtice_r = (double*)(&((*ydthf_var_3_2)->rtwat_rtice_r));
    toethf** ydthf_var_5_2;
    ydthf_var_5_2 = &ydthf;
    toethf** ydthf_var_3_0;
    ydthf_var_3_0 = &(*ydthf_var_5_2);
    toethf** ydthf_var_3_1;
    ydthf_var_3_1 = &(*ydthf_var_5_2);
    double tmp_call_114_0;
    double tmp_call_113_0;
    double tmp_call_112_0;
    double tmp_call_105_0_0;
    double tmp_call_105_1_0;
    toethf** ydthf_var_8_0;
    ydthf_var_8_0 = &ydthf;
    toethf** ydthf_var_10_2;
    ydthf_var_10_2 = &ydthf;
    double* v_ydthf_var_10_ralvdcp;
    v_ydthf_var_10_ralvdcp = (double*)(&((*ydthf_var_10_2)->ralvdcp));
    double* v_ydthf_var_10_ralsdcp;
    v_ydthf_var_10_ralsdcp = (double*)(&((*ydthf_var_10_2)->ralsdcp));
    double tmp_call_116_0;
    double tmp_call_105_0_1;
    double tmp_call_105_1_1;
    toethf** ydthf_var_10_0;
    ydthf_var_10_0 = &ydthf;
    double tmp_call_114_1;
    double tmp_call_113_1;
    double tmp_call_112_1;
    double tmp_call_105_0_2;
    double tmp_call_105_1_2;
    toethf** ydthf_var_8_1;
    ydthf_var_8_1 = &ydthf;
    double* v_ydthf_var_5_r3ies;
    v_ydthf_var_5_r3ies = (double*)(&((*ydthf_var_5_2)->r3ies));
    tomcst** ydcst_var_6_2;
    ydcst_var_6_2 = &ydcst;
    double* v_ydcst_var_6_rtt;
    v_ydcst_var_6_rtt = (double*)(&((*ydcst_var_6_2)->rtt));
    double* v_ydthf_var_5_r4ies;
    v_ydthf_var_5_r4ies = (double*)(&((*ydthf_var_5_2)->r4ies));
    double* v_ydthf_var_5_r3les;
    v_ydthf_var_5_r3les = (double*)(&((*ydthf_var_5_2)->r3les));
    double* v_ydthf_var_5_r4les;
    v_ydthf_var_5_r4les = (double*)(&((*ydthf_var_5_2)->r4les));
    double* v_ydthf_var_5_r2es;
    v_ydthf_var_5_r2es = (double*)(&((*ydthf_var_5_2)->r2es));
    double tmp_call_110_0;
    double tmp_call_109_0;
    double tmp_call_108_0;
    double tmp_call_105_0_3;
    double tmp_call_105_1_3;
    tomcst** ydcst_var_6_0;
    ydcst_var_6_0 = &ydcst;
    toethf** ydthf_var_5_0;
    ydthf_var_5_0 = &ydthf;
    double tmp_call_116_1;
    double tmp_call_105_0_4;
    double tmp_call_105_1_4;
    toethf** ydthf_var_10_1;
    ydthf_var_10_1 = &ydthf;
    double tmp_call_114_2;
    double tmp_call_113_2;
    double tmp_call_112_2;
    double tmp_call_105_0_5;
    double tmp_call_105_1_5;
    double tmp_call_110_1;
    double tmp_call_109_1;
    double tmp_call_108_1;
    double tmp_call_105_0_6;
    double tmp_call_105_1_6;
    tomcst** ydcst_var_6_1;
    ydcst_var_6_1 = &ydcst;
    toethf** ydthf_var_5_1;
    ydthf_var_5_1 = &ydthf;
    double tmp_call_116_2;
    double tmp_call_105_0_7;
    double tmp_call_105_1_7;
    tomcst** ydcst_var_1_0;
    ydcst_var_1_0 = &ydcst;
    double* v_ydcst_var_1_rtt;
    v_ydcst_var_1_rtt = (double*)(&((*ydcst_var_1_0)->rtt));
    double tmp_call_103_0;
    double tmp_call_110_2;
    double tmp_call_109_2;
    double tmp_call_108_2;
    double tmp_call_105_0_8;
    double tmp_call_105_1_8;
    double tmp_call_105_0;
    int _for_it_0;
    int _for_it_1;
    int _for_it_2;
    int _for_it_3;
    int _for_it_4;
    int tmp_parfor_0;
    double _if_cond_0;
    int _for_it_5;
    int _for_it_6;
    int _for_it_7;
    int _for_it_8;
    int _for_it_9;
    int _for_it_10;
    int tmp_parfor_3;
    int tmp_parfor_2;
    int tmp_parfor_1;
    int tmp_parfor_6;
    int tmp_parfor_5;
    int tmp_parfor_4;
    int tmp_parfor_9;
    int tmp_parfor_8;
    int tmp_parfor_7;
    int tmp_parfor_10;
    int tmp_parfor_11;
    int _for_it_11;
    int _for_it_12;
    int _for_it_13;
    int _for_it_14;
    int _for_it_15;
    int _if_cond_3;
    int _if_cond_4;
    int _for_it_16;
    int _for_it_17;
    int _for_it_18;
    int _for_it_19;
    int tmp_parfor_12;
    int tmp_parfor_13;
    int tmp_parfor_14;
    int tmp_parfor_15;
    int tmp_parfor_16;
    int tmp_parfor_17;
    int jnn;
    int _for_it_23;
    int _for_it_24;
    int _for_it_25;
    int tmp_parfor_18;
    int tmp_parfor_19;
    int tmp_parfor_20;
    int tmp_parfor_21;
    int tmp_parfor_22;
    int tmp_parfor_23;
    int tmp_parfor_24;
    int tmp_parfor_25;
    int tmp_parfor_26;
    int tmp_parfor_27;
    int tmp_parfor_28;
    int tmp_parfor_31;
    int tmp_parfor_32;
    int tmp_parfor_35;
    int tmp_parfor_34;
    int tmp_parfor_33;
    int tmp_parfor_38;
    int tmp_parfor_37;
    int tmp_parfor_36;
    int tmp_parfor_40;
    int tmp_parfor_39;
    int tmp_parfor_42;
    int tmp_parfor_41;
    int tmp_parfor_44;
    int tmp_parfor_43;
    int tmp_parfor_46;
    int tmp_parfor_45;
    int tmp_parfor_48;
    int tmp_parfor_47;
    int tmp_parfor_50;
    int tmp_parfor_49;
    int tmp_parfor_51;
    double zalfaw;
    double zfac;
    int _for_it_26;
    int _for_it_27;
    int _for_it_28;
    double _if_cond_12;
    double _if_cond_14;
    int _for_it_29;
    int _if_cond_18;
    int _for_it_30;
    int _for_it_31;
    int _if_cond_20;
    int _for_it_32;
    int _for_it_33;
    int _for_it_34;
    int _if_cond_21;
    int _for_it_35;
    int _for_it_36;
    double _if_cond_22;
    int _for_it_37;
    int _for_it_38;
    double _if_cond_24;
    int _for_it_39;
    double _if_cond_25;
    int _for_it_40;
    int _for_it_41;
    int _for_it_42;
    int _for_it_43;
    double _if_cond_27;
    int _for_it_44;
    int _for_it_45;
    double _if_cond_29;
    int _for_it_46;
    double zsigk;
    double _if_cond_39;
    double _if_cond_42;
    int _for_it_47;
    int _for_it_48;
    int _if_cond_46;
    int _for_it_49;
    int _for_it_50;
    double _if_cond_49;
    int _for_it_51;
    double _if_cond_53;
    int _for_it_52;
    double _if_cond_51;
    double _if_cond_54;
    double _if_cond_55;
    int _for_it_53;
    double _if_cond_60;
    int _for_it_54;
    int _if_cond_62;
    int _for_it_55;
    double _if_cond_63;
    int _for_it_56;
    double _if_cond_64;
    int _for_it_57;
    int _if_cond_68;
    double _if_cond_69;
    int _for_it_58;
    double _if_cond_70;
    int _for_it_59;
    int _if_cond_71;
    int _for_it_60;
    int _if_cond_72;
    int _for_it_61;
    int _if_cond_73;
    int _for_it_62;
    int _for_it_63;
    int _for_it_64;
    int _for_it_65;
    int _for_it_66;
    int _for_it_67;
    int _for_it_68;
    int _for_it_69;
    int _for_it_70;
    int _for_it_71;
    int _for_it_72;
    int _for_it_73;
    int _for_it_74;
    int _for_it_75;
    int _for_it_76;
    int _for_it_77;
    int _for_it_78;
    int _for_it_79;
    int _for_it_80;
    double _if_cond_76;
    int _for_it_81;
    int tmp_index_1668;
    int _for_it_82;
    int _for_it_83;
    int _for_it_84;
    int _for_it_85;
    int jo;
    int _for_it_86;
    int _for_it_87;
    int _for_it_88;
    int _for_it_89;
    int _if_cond_77;
    int _for_it_90;
    int _for_it_91;
    int _for_it_92;
    int _for_it_93;
    int _for_it_94;
    int _for_it_95;
    int _for_it_96;
    int _for_it_97;
    int _for_it_98;
    int _for_it_99;
    int _for_it_100;
    int tmp_parfor_52;
    int _for_it_101;
    int _for_it_102;
    int _for_it_103;
    int _for_it_104;
    int tmp_parfor_53;
    int tmp_parfor_54;
    int _for_it_105;
    int _for_it_106;
    int tmp_parfor_55;
    int tmp_parfor_56;
    int _for_it_107;
    double _if_cond_79;
    int _for_it_108;
    int _for_it_109;
    int _for_it_110;
    int _for_it_111;
    int _for_it_112;
    int _for_it_113;
    double _if_cond_80;
    int _for_it_114;
    int _if_cond_81;
    int _if_cond_82;
    int _for_it_115;
    int _for_it_116;
    int _for_it_117;
    int _for_it_118;
    int _for_it_119;
    int _for_it_120;
    int _for_it_121;
    int _for_it_122;
    int _for_it_123;
    int _for_it_124;
    int _for_it_125;
    int _for_it_126;
    int _for_it_127;
    int _for_it_128;


    {

        {
            double zepsilon_out;

            ///////////////////
            // Tasklet code (T_l396_c396)
            zepsilon_out = (100.0 * 2.220446049250313e-16);
            ///////////////////

            zepsilon = zepsilon_out;
        }
        {
            double ptsphy_0_in = ptsphy;
            double zqtmst_out;

            ///////////////////
            // Tasklet code (T_l401_c401)
            zqtmst_out = (1.0 / ptsphy_0_in);
            ///////////////////

            zqtmst = zqtmst_out;
        }

    }

    {

        {
            double ydcst_0_in_rd = v_ydcst_rd[0];
            double ydcst_1_in_rcpd = v_ydcst_rcpd[0];
            double zrdcp_out;

            ///////////////////
            // Tasklet code (T_l403_c403)
            zrdcp_out = (ydcst_0_in_rd / ydcst_1_in_rcpd);
            ///////////////////

            zrdcp = zrdcp_out;
        }
        {
            double zepsec_out;

            ///////////////////
            // Tasklet code (T_l405_c405)
            zepsec_out = 1e-14;
            ///////////////////

            zepsec = zepsec_out;
        }

    }

    {

        {
            double ydcst_0_in_rg = v_ydcst_rg[0];
            double zrg_r_out;

            ///////////////////
            // Tasklet code (T_l406_c406)
            zrg_r_out = (1.0 / ydcst_0_in_rg);
            ///////////////////

            zrg_r = zrg_r_out;
        }
        {
            double ydthf_0_in_ralsdcp = v_ydthf_ralsdcp[0];
            double ydthf_1_in_ralvdcp = v_ydthf_ralvdcp[0];
            double zrldcp_out;

            ///////////////////
            // Tasklet code (T_l407_c407)
            zrldcp_out = (1.0 / (ydthf_0_in_ralsdcp - ydthf_1_in_ralvdcp));
            ///////////////////

            zrldcp = zrldcp_out;
        }
        {
            int iphase_out_0;

            ///////////////////
            // Tasklet code (T_l408_c408)
            iphase_out_0 = 0;
            ///////////////////

            iphase[4] = iphase_out_0;
        }
        {
            int iphase_out_0;

            ///////////////////
            // Tasklet code (T_l409_c409)
            iphase_out_0 = 1;
            ///////////////////

            iphase[0] = iphase_out_0;
        }
        {
            int iphase_out_0;

            ///////////////////
            // Tasklet code (T_l410_c410)
            iphase_out_0 = 1;
            ///////////////////

            iphase[2] = iphase_out_0;
        }
        {
            int iphase_out_0;

            ///////////////////
            // Tasklet code (T_l411_c411)
            iphase_out_0 = 2;
            ///////////////////

            iphase[1] = iphase_out_0;
        }
        {
            int iphase_out_0;

            ///////////////////
            // Tasklet code (T_l412_c412)
            iphase_out_0 = 2;
            ///////////////////

            iphase[3] = iphase_out_0;
        }
        {
            int imelt_out_0;

            ///////////////////
            // Tasklet code (T_l413_c413)
            imelt_out_0 = -99;
            ///////////////////

            imelt[4] = imelt_out_0;
        }
        {
            int imelt_out_0;

            ///////////////////
            // Tasklet code (T_l414_c414)
            imelt_out_0 = 2;
            ///////////////////

            imelt[0] = imelt_out_0;
        }
        {
            int imelt_out_0;

            ///////////////////
            // Tasklet code (T_l415_c415)
            imelt_out_0 = 4;
            ///////////////////

            imelt[2] = imelt_out_0;
        }
        {
            int imelt_out_0;

            ///////////////////
            // Tasklet code (T_l416_c416)
            imelt_out_0 = 3;
            ///////////////////

            imelt[1] = imelt_out_0;
        }
        {
            int imelt_out_0;

            ///////////////////
            // Tasklet code (T_l417_c417)
            imelt_out_0 = 3;
            ///////////////////

            imelt[3] = imelt_out_0;
        }

    }

    for (_for_it_0 = 1; (_for_it_0 <= klev); _for_it_0 = (_for_it_0 + 1)) {
        for (_for_it_1 = 1; (_for_it_1 <= kfdia); _for_it_1 = (_for_it_1 + 1)) {
            {

                {
                    double ptendency_loc_t_out_0;

                    ///////////////////
                    // Tasklet code (T_l420_c420)
                    ptendency_loc_t_out_0 = 0.0;
                    ///////////////////

                    ptendency_loc_t[((_for_it_1 + (klon * (_for_it_0 - 1))) - 1)] = ptendency_loc_t_out_0;
                }
                {
                    double ptendency_loc_q_out_0;

                    ///////////////////
                    // Tasklet code (T_l421_c421)
                    ptendency_loc_q_out_0 = 0.0;
                    ///////////////////

                    ptendency_loc_q[((_for_it_1 + (klon * (_for_it_0 - 1))) - 1)] = ptendency_loc_q_out_0;
                }
                {
                    double ptendency_loc_a_out_0;

                    ///////////////////
                    // Tasklet code (T_l422_c422)
                    ptendency_loc_a_out_0 = 0.0;
                    ///////////////////

                    ptendency_loc_a[((_for_it_1 + (klon * (_for_it_0 - 1))) - 1)] = ptendency_loc_a_out_0;
                }

            }

        }

    }

    for (_for_it_2 = 1; (_for_it_2 <= 4); _for_it_2 = (_for_it_2 + 1)) {
        for (_for_it_3 = 1; (_for_it_3 <= klev); _for_it_3 = (_for_it_3 + 1)) {
            for (_for_it_4 = 1; (_for_it_4 <= kfdia); _for_it_4 = (_for_it_4 + 1)) {
                {

                    {
                        double ptendency_loc_cld_out_0;

                        ///////////////////
                        // Tasklet code (T_l428_c428)
                        ptendency_loc_cld_out_0 = 0.0;
                        ///////////////////

                        ptendency_loc_cld[(((_for_it_4 + ((klev * klon) * (_for_it_2 - 1))) + (klon * (_for_it_3 - 1))) - 1)] = ptendency_loc_cld_out_0;
                    }

                }

            }

        }

    }

    {
        double* v_ydecldp_rvice;
        v_ydecldp_rvice = (double*)(&(ydecldp->rvice));
        double* v_ydecldp_rvrain;
        v_ydecldp_rvrain = (double*)(&(ydecldp->rvrain));
        double* v_ydecldp_rvsnow;
        v_ydecldp_rvsnow = (double*)(&(ydecldp->rvsnow));

        {
            double zvqx_out_0;

            ///////////////////
            // Tasklet code (T_l432_c432)
            zvqx_out_0 = 0.0;
            ///////////////////

            zvqx[4] = zvqx_out_0;
        }
        {
            double zvqx_out_0;

            ///////////////////
            // Tasklet code (T_l433_c433)
            zvqx_out_0 = 0.0;
            ///////////////////

            zvqx[0] = zvqx_out_0;
        }
        {
            double ydecldp_0_in_rvice = v_ydecldp_rvice[0];
            double zvqx_out_0;

            ///////////////////
            // Tasklet code (T_l434_c434)
            zvqx_out_0 = ydecldp_0_in_rvice;
            ///////////////////

            zvqx[1] = zvqx_out_0;
        }
        {
            double ydecldp_0_in_rvrain = v_ydecldp_rvrain[0];
            double zvqx_out_0;

            ///////////////////
            // Tasklet code (T_l435_c435)
            zvqx_out_0 = ydecldp_0_in_rvrain;
            ///////////////////

            zvqx[2] = zvqx_out_0;
        }
        {
            double ydecldp_0_in_rvsnow = v_ydecldp_rvsnow[0];
            double zvqx_out_0;

            ///////////////////
            // Tasklet code (T_l436_c436)
            zvqx_out_0 = ydecldp_0_in_rvsnow;
            ///////////////////

            zvqx[3] = zvqx_out_0;
        }

    }

    for (tmp_parfor_0 = 1; (tmp_parfor_0 <= 5); tmp_parfor_0 = (tmp_parfor_0 + 1)) {
        {

            {
                int llfall_out_0;

                ///////////////////
                // Tasklet code (T_l437_c437)
                llfall_out_0 = 0;
                ///////////////////

                llfall[(tmp_parfor_0 - 1)] = llfall_out_0;
            }

        }

    }

    for (_for_it_5 = 1; (_for_it_5 <= 5); _for_it_5 = (_for_it_5 + 1)) {

        _if_cond_0 = (zvqx[(_for_it_5 - 1)] > 0.0);
        if ((_if_cond_0 == 1)) {
            {

                {
                    int llfall_out_0;

                    ///////////////////
                    // Tasklet code (T_l439_c439)
                    llfall_out_0 = 1;
                    ///////////////////

                    llfall[(_for_it_5 - 1)] = llfall_out_0;
                }

            }
        }

    }

    {

        {
            int llfall_out_0;

            ///////////////////
            // Tasklet code (T_l441_c441)
            llfall_out_0 = 0;
            ///////////////////

            llfall[1] = llfall_out_0;
        }

    }

    for (_for_it_6 = 1; (_for_it_6 <= klev); _for_it_6 = (_for_it_6 + 1)) {
        for (_for_it_7 = 1; (_for_it_7 <= kfdia); _for_it_7 = (_for_it_7 + 1)) {
            {

                {
                    double pt_0_in_0 = pt[((_for_it_7 + (klon * (_for_it_6 - 1))) - 1)];
                    double ptendency_tmp_t_0_in_0 = ptendency_tmp_t[((_for_it_7 + (klon * (_for_it_6 - 1))) - 1)];
                    double ptsphy_0_in = ptsphy;
                    double ztp1_out_0;

                    ///////////////////
                    // Tasklet code (T_l444_c444)
                    ztp1_out_0 = (pt_0_in_0 + (ptsphy_0_in * ptendency_tmp_t_0_in_0));
                    ///////////////////

                    ztp1[((_for_it_7 + (klon * (_for_it_6 - 1))) - 1)] = ztp1_out_0;
                }
                {
                    double pq_0_in_0 = pq[((_for_it_7 + (klon * (_for_it_6 - 1))) - 1)];
                    double ptendency_tmp_q_0_in_0 = ptendency_tmp_q[((_for_it_7 + (klon * (_for_it_6 - 1))) - 1)];
                    double ptsphy_0_in = ptsphy;
                    double zqx_out_0;

                    ///////////////////
                    // Tasklet code (T_l445_c445)
                    zqx_out_0 = (pq_0_in_0 + (ptsphy_0_in * ptendency_tmp_q_0_in_0));
                    ///////////////////

                    zqx[(((_for_it_7 + ((4 * klev) * klon)) + (klon * (_for_it_6 - 1))) - 1)] = zqx_out_0;
                }
                {
                    double pq_0_in_0 = pq[((_for_it_7 + (klon * (_for_it_6 - 1))) - 1)];
                    double ptendency_tmp_q_0_in_0 = ptendency_tmp_q[((_for_it_7 + (klon * (_for_it_6 - 1))) - 1)];
                    double ptsphy_0_in = ptsphy;
                    double zqx0_out_0;

                    ///////////////////
                    // Tasklet code (T_l446_c446)
                    zqx0_out_0 = (pq_0_in_0 + (ptsphy_0_in * ptendency_tmp_q_0_in_0));
                    ///////////////////

                    zqx0[(((_for_it_7 + ((4 * klev) * klon)) + (klon * (_for_it_6 - 1))) - 1)] = zqx0_out_0;
                }
                {
                    double pa_0_in_0 = pa[((_for_it_7 + (klon * (_for_it_6 - 1))) - 1)];
                    double ptendency_tmp_a_0_in_0 = ptendency_tmp_a[((_for_it_7 + (klon * (_for_it_6 - 1))) - 1)];
                    double ptsphy_0_in = ptsphy;
                    double za_out_0;

                    ///////////////////
                    // Tasklet code (T_l447_c447)
                    za_out_0 = (pa_0_in_0 + (ptsphy_0_in * ptendency_tmp_a_0_in_0));
                    ///////////////////

                    za[((_for_it_7 + (klon * (_for_it_6 - 1))) - 1)] = za_out_0;
                }
                {
                    double pa_0_in_0 = pa[((_for_it_7 + (klon * (_for_it_6 - 1))) - 1)];
                    double ptendency_tmp_a_0_in_0 = ptendency_tmp_a[((_for_it_7 + (klon * (_for_it_6 - 1))) - 1)];
                    double ptsphy_0_in = ptsphy;
                    double zaorig_out_0;

                    ///////////////////
                    // Tasklet code (T_l448_c448)
                    zaorig_out_0 = (pa_0_in_0 + (ptsphy_0_in * ptendency_tmp_a_0_in_0));
                    ///////////////////

                    zaorig[((_for_it_7 + (klon * (_for_it_6 - 1))) - 1)] = zaorig_out_0;
                }

            }

        }

    }

    for (_for_it_8 = 1; (_for_it_8 <= 4); _for_it_8 = (_for_it_8 + 1)) {
        for (_for_it_9 = 1; (_for_it_9 <= klev); _for_it_9 = (_for_it_9 + 1)) {
            for (_for_it_10 = 1; (_for_it_10 <= kfdia); _for_it_10 = (_for_it_10 + 1)) {
                {

                    {
                        double pclv_0_in_0 = pclv[(((_for_it_10 + ((klev * klon) * (_for_it_8 - 1))) + (klon * (_for_it_9 - 1))) - 1)];
                        double ptendency_tmp_cld_0_in_0 = ptendency_tmp_cld[(((_for_it_10 + ((klev * klon) * (_for_it_8 - 1))) + (klon * (_for_it_9 - 1))) - 1)];
                        double ptsphy_0_in = ptsphy;
                        double zqx_out_0;

                        ///////////////////
                        // Tasklet code (T_l454_c454)
                        zqx_out_0 = (pclv_0_in_0 + (ptsphy_0_in * ptendency_tmp_cld_0_in_0));
                        ///////////////////

                        zqx[(((_for_it_10 + ((klev * klon) * (_for_it_8 - 1))) + (klon * (_for_it_9 - 1))) - 1)] = zqx_out_0;
                    }
                    {
                        double pclv_0_in_0 = pclv[(((_for_it_10 + ((klev * klon) * (_for_it_8 - 1))) + (klon * (_for_it_9 - 1))) - 1)];
                        double ptendency_tmp_cld_0_in_0 = ptendency_tmp_cld[(((_for_it_10 + ((klev * klon) * (_for_it_8 - 1))) + (klon * (_for_it_9 - 1))) - 1)];
                        double ptsphy_0_in = ptsphy;
                        double zqx0_out_0;

                        ///////////////////
                        // Tasklet code (T_l455_c455)
                        zqx0_out_0 = (pclv_0_in_0 + (ptsphy_0_in * ptendency_tmp_cld_0_in_0));
                        ///////////////////

                        zqx0[(((_for_it_10 + ((klev * klon) * (_for_it_8 - 1))) + (klon * (_for_it_9 - 1))) - 1)] = zqx0_out_0;
                    }

                }

            }

        }

    }

    for (tmp_parfor_3 = 1; (tmp_parfor_3 <= 5); tmp_parfor_3 = (tmp_parfor_3 + 1)) {
        for (tmp_parfor_2 = 1; (tmp_parfor_2 <= (klev + 1)); tmp_parfor_2 = (tmp_parfor_2 + 1)) {
            for (tmp_parfor_1 = 1; (tmp_parfor_1 <= klon); tmp_parfor_1 = (tmp_parfor_1 + 1)) {
                {

                    {
                        double zpfplsx_out_0;

                        ///////////////////
                        // Tasklet code (T_l459_c459)
                        zpfplsx_out_0 = 0.0;
                        ///////////////////

                        zpfplsx[(((((klon * (klev + 1)) * (tmp_parfor_3 - 1)) + (klon * (tmp_parfor_2 - 1))) + tmp_parfor_1) - 1)] = zpfplsx_out_0;
                    }

                }

            }

        }

    }

    for (tmp_parfor_6 = 1; (tmp_parfor_6 <= 5); tmp_parfor_6 = (tmp_parfor_6 + 1)) {
        for (tmp_parfor_5 = 1; (tmp_parfor_5 <= klev); tmp_parfor_5 = (tmp_parfor_5 + 1)) {
            for (tmp_parfor_4 = 1; (tmp_parfor_4 <= klon); tmp_parfor_4 = (tmp_parfor_4 + 1)) {
                {

                    {
                        double zqxn2d_out_0;

                        ///////////////////
                        // Tasklet code (T_l460_c460)
                        zqxn2d_out_0 = 0.0;
                        ///////////////////

                        zqxn2d[(((((klev * klon) * (tmp_parfor_6 - 1)) + (klon * (tmp_parfor_5 - 1))) + tmp_parfor_4) - 1)] = zqxn2d_out_0;
                    }

                }

            }

        }

    }

    for (tmp_parfor_9 = 1; (tmp_parfor_9 <= 5); tmp_parfor_9 = (tmp_parfor_9 + 1)) {
        for (tmp_parfor_8 = 1; (tmp_parfor_8 <= klev); tmp_parfor_8 = (tmp_parfor_8 + 1)) {
            for (tmp_parfor_7 = 1; (tmp_parfor_7 <= klon); tmp_parfor_7 = (tmp_parfor_7 + 1)) {
                {

                    {
                        double zlneg_out_0;

                        ///////////////////
                        // Tasklet code (T_l461_c461)
                        zlneg_out_0 = 0.0;
                        ///////////////////

                        zlneg[(((((klev * klon) * (tmp_parfor_9 - 1)) + (klon * (tmp_parfor_8 - 1))) + tmp_parfor_7) - 1)] = zlneg_out_0;
                    }

                }

            }

        }

    }

    for (tmp_parfor_10 = 1; (tmp_parfor_10 <= klon); tmp_parfor_10 = (tmp_parfor_10 + 1)) {
        {

            {
                double prainfrac_toprfz_out_0;

                ///////////////////
                // Tasklet code (T_l462_c462)
                prainfrac_toprfz_out_0 = 0.0;
                ///////////////////

                prainfrac_toprfz[(tmp_parfor_10 - 1)] = prainfrac_toprfz_out_0;
            }

        }

    }

    for (tmp_parfor_11 = 1; (tmp_parfor_11 <= klon); tmp_parfor_11 = (tmp_parfor_11 + 1)) {
        {

            {
                int llrainliq_out_0;

                ///////////////////
                // Tasklet code (T_l463_c463)
                llrainliq_out_0 = 1;
                ///////////////////

                llrainliq[(tmp_parfor_11 - 1)] = llrainliq_out_0;
            }

        }

    }

    for (_for_it_11 = 1; (_for_it_11 <= klev); _for_it_11 = (_for_it_11 + 1)) {
        for (_for_it_12 = 1; (_for_it_12 <= kfdia); _for_it_12 = (_for_it_12 + 1)) {
            {

                {
                    double ydecldp_0_in_rlmin = v_ydecldp_rlmin[0];
                    double ydecldp_1_in_ramin = v_ydecldp_ramin[0];
                    double za_0_in_0 = za[((_for_it_12 + (klon * (_for_it_11 - 1))) - 1)];
                    double zqx_0_in_0 = zqx[((_for_it_12 + (klon * (_for_it_11 - 1))) - 1)];
                    double zqx_1_in_0 = zqx[(((_for_it_12 + (klev * klon)) + (klon * (_for_it_11 - 1))) - 1)];
                    double _if_cond_1_out;

                    ///////////////////
                    // Tasklet code (T_l0_c0)
                    _if_cond_1_out = (((zqx_0_in_0 + zqx_1_in_0) < ydecldp_0_in_rlmin) || (za_0_in_0 < ydecldp_1_in_ramin));
                    ///////////////////

                    _if_cond_1 = _if_cond_1_out;
                }

            }
            if ((_if_cond_1 == 1)) {
                {

                    {
                        double zlneg_0_in_0 = zlneg[((_for_it_12 + (klon * (_for_it_11 - 1))) - 1)];
                        double zqx_0_in_0 = zqx[((_for_it_12 + (klon * (_for_it_11 - 1))) - 1)];
                        double zlneg_out_0;

                        ///////////////////
                        // Tasklet code (T_l467_c467)
                        zlneg_out_0 = (zlneg_0_in_0 + zqx_0_in_0);
                        ///////////////////

                        zlneg[((_for_it_12 + (klon * (_for_it_11 - 1))) - 1)] = zlneg_out_0;
                    }
                    {
                        double zqx_0_in_0 = zqx[(((_for_it_12 + ((4 * klev) * klon)) + (klon * (_for_it_11 - 1))) - 1)];
                        double zqx_1_in_0 = zqx[((_for_it_12 + (klon * (_for_it_11 - 1))) - 1)];
                        double zqx_out_0;

                        ///////////////////
                        // Tasklet code (T_l471_c471)
                        zqx_out_0 = (zqx_0_in_0 + zqx_1_in_0);
                        ///////////////////

                        zqx[(((_for_it_12 + ((4 * klev) * klon)) + (klon * (_for_it_11 - 1))) - 1)] = zqx_out_0;
                    }
                    {
                        double zqtmst_0_in = zqtmst;
                        double zqx_0_in_0 = zqx[((_for_it_12 + (klon * (_for_it_11 - 1))) - 1)];
                        double zqadj_out;

                        ///////////////////
                        // Tasklet code (T_l468_c468)
                        zqadj_out = (zqx_0_in_0 * zqtmst_0_in);
                        ///////////////////

                        zqadj = zqadj_out;
                    }
                    {
                        double ptendency_loc_q_0_in_0 = ptendency_loc_q[((_for_it_12 + (klon * (_for_it_11 - 1))) - 1)];
                        double zqadj_0_in = zqadj;
                        double ptendency_loc_q_out_0;

                        ///////////////////
                        // Tasklet code (T_l469_c469)
                        ptendency_loc_q_out_0 = (ptendency_loc_q_0_in_0 + zqadj_0_in);
                        ///////////////////

                        ptendency_loc_q[((_for_it_12 + (klon * (_for_it_11 - 1))) - 1)] = ptendency_loc_q_out_0;
                    }
                    {
                        double ptendency_loc_t_0_in_0 = ptendency_loc_t[((_for_it_12 + (klon * (_for_it_11 - 1))) - 1)];
                        double ydthf_0_in_ralvdcp = v_ydthf_ralvdcp[0];
                        double zqadj_0_in = zqadj;
                        double ptendency_loc_t_out_0;

                        ///////////////////
                        // Tasklet code (T_l470_c470)
                        ptendency_loc_t_out_0 = (ptendency_loc_t_0_in_0 - (ydthf_0_in_ralvdcp * zqadj_0_in));
                        ///////////////////

                        ptendency_loc_t[((_for_it_12 + (klon * (_for_it_11 - 1))) - 1)] = ptendency_loc_t_out_0;
                    }

                }
                {

                    {
                        double zqx_out_0;

                        ///////////////////
                        // Tasklet code (T_l472_c472)
                        zqx_out_0 = 0.0;
                        ///////////////////

                        zqx[((_for_it_12 + (klon * (_for_it_11 - 1))) - 1)] = zqx_out_0;
                    }
                    {
                        double zlneg_0_in_0 = zlneg[(((_for_it_12 + (klev * klon)) + (klon * (_for_it_11 - 1))) - 1)];
                        double zqx_0_in_0 = zqx[(((_for_it_12 + (klev * klon)) + (klon * (_for_it_11 - 1))) - 1)];
                        double zlneg_out_0;

                        ///////////////////
                        // Tasklet code (T_l473_c473)
                        zlneg_out_0 = (zlneg_0_in_0 + zqx_0_in_0);
                        ///////////////////

                        zlneg[(((_for_it_12 + (klev * klon)) + (klon * (_for_it_11 - 1))) - 1)] = zlneg_out_0;
                    }
                    {
                        double zqtmst_0_in = zqtmst;
                        double zqx_0_in_0 = zqx[(((_for_it_12 + (klev * klon)) + (klon * (_for_it_11 - 1))) - 1)];
                        double zqadj_out;

                        ///////////////////
                        // Tasklet code (T_l474_c474)
                        zqadj_out = (zqx_0_in_0 * zqtmst_0_in);
                        ///////////////////

                        zqadj = zqadj_out;
                    }
                    {
                        double ptendency_loc_q_0_in_0 = ptendency_loc_q[((_for_it_12 + (klon * (_for_it_11 - 1))) - 1)];
                        double zqadj_0_in = zqadj;
                        double ptendency_loc_q_out_0;

                        ///////////////////
                        // Tasklet code (T_l475_c475)
                        ptendency_loc_q_out_0 = (ptendency_loc_q_0_in_0 + zqadj_0_in);
                        ///////////////////

                        ptendency_loc_q[((_for_it_12 + (klon * (_for_it_11 - 1))) - 1)] = ptendency_loc_q_out_0;
                    }
                    {
                        double ptendency_loc_t_0_in_0 = ptendency_loc_t[((_for_it_12 + (klon * (_for_it_11 - 1))) - 1)];
                        double ydthf_0_in_ralsdcp = v_ydthf_ralsdcp[0];
                        double zqadj_0_in = zqadj;
                        double ptendency_loc_t_out_0;

                        ///////////////////
                        // Tasklet code (T_l476_c476)
                        ptendency_loc_t_out_0 = (ptendency_loc_t_0_in_0 - (ydthf_0_in_ralsdcp * zqadj_0_in));
                        ///////////////////

                        ptendency_loc_t[((_for_it_12 + (klon * (_for_it_11 - 1))) - 1)] = ptendency_loc_t_out_0;
                    }

                }
                {

                    {
                        double zqx_0_in_0 = zqx[(((_for_it_12 + ((4 * klev) * klon)) + (klon * (_for_it_11 - 1))) - 1)];
                        double zqx_1_in_0 = zqx[(((_for_it_12 + (klev * klon)) + (klon * (_for_it_11 - 1))) - 1)];
                        double zqx_out_0;

                        ///////////////////
                        // Tasklet code (T_l477_c477)
                        zqx_out_0 = (zqx_0_in_0 + zqx_1_in_0);
                        ///////////////////

                        zqx[(((_for_it_12 + ((4 * klev) * klon)) + (klon * (_for_it_11 - 1))) - 1)] = zqx_out_0;
                    }

                }
                {

                    {
                        double zqx_out_0;

                        ///////////////////
                        // Tasklet code (T_l478_c478)
                        zqx_out_0 = 0.0;
                        ///////////////////

                        zqx[(((_for_it_12 + (klev * klon)) + (klon * (_for_it_11 - 1))) - 1)] = zqx_out_0;
                    }
                    {
                        double za_out_0;

                        ///////////////////
                        // Tasklet code (T_l479_c479)
                        za_out_0 = 0.0;
                        ///////////////////

                        za[((_for_it_12 + (klon * (_for_it_11 - 1))) - 1)] = za_out_0;
                    }

                }
            }

        }

    }

    for (_for_it_13 = 1; (_for_it_13 <= 4); _for_it_13 = (_for_it_13 + 1)) {
        for (_for_it_14 = 1; (_for_it_14 <= klev); _for_it_14 = (_for_it_14 + 1)) {
            for (_for_it_15 = 1; (_for_it_15 <= kfdia); _for_it_15 = (_for_it_15 + 1)) {
                {

                    {
                        double ydecldp_0_in_rlmin = v_ydecldp_rlmin[0];
                        double zqx_0_in_0 = zqx[(((_for_it_15 + ((klev * klon) * (_for_it_13 - 1))) + (klon * (_for_it_14 - 1))) - 1)];
                        double _if_cond_2_out;

                        ///////////////////
                        // Tasklet code (T_l0_c0)
                        _if_cond_2_out = (zqx_0_in_0 < ydecldp_0_in_rlmin);
                        ///////////////////

                        _if_cond_2 = _if_cond_2_out;
                    }

                }
                if ((_if_cond_2 == 1)) {

                    _if_cond_3 = (iphase[(_for_it_13 - 1)] == 1);
                    {

                        {
                            double zlneg_0_in_0 = zlneg[(((_for_it_15 + ((klev * klon) * (_for_it_13 - 1))) + (klon * (_for_it_14 - 1))) - 1)];
                            double zqx_0_in_0 = zqx[(((_for_it_15 + ((klev * klon) * (_for_it_13 - 1))) + (klon * (_for_it_14 - 1))) - 1)];
                            double zlneg_out_0;

                            ///////////////////
                            // Tasklet code (T_l487_c487)
                            zlneg_out_0 = (zlneg_0_in_0 + zqx_0_in_0);
                            ///////////////////

                            zlneg[(((_for_it_15 + ((klev * klon) * (_for_it_13 - 1))) + (klon * (_for_it_14 - 1))) - 1)] = zlneg_out_0;
                        }
                        {
                            double zqtmst_0_in = zqtmst;
                            double zqx_0_in_0 = zqx[(((_for_it_15 + ((klev * klon) * (_for_it_13 - 1))) + (klon * (_for_it_14 - 1))) - 1)];
                            double zqadj_out;

                            ///////////////////
                            // Tasklet code (T_l488_c488)
                            zqadj_out = (zqx_0_in_0 * zqtmst_0_in);
                            ///////////////////

                            zqadj = zqadj_out;
                        }
                        {
                            double ptendency_loc_q_0_in_0 = ptendency_loc_q[((_for_it_15 + (klon * (_for_it_14 - 1))) - 1)];
                            double zqadj_0_in = zqadj;
                            double ptendency_loc_q_out_0;

                            ///////////////////
                            // Tasklet code (T_l489_c489)
                            ptendency_loc_q_out_0 = (ptendency_loc_q_0_in_0 + zqadj_0_in);
                            ///////////////////

                            ptendency_loc_q[((_for_it_15 + (klon * (_for_it_14 - 1))) - 1)] = ptendency_loc_q_out_0;
                        }

                    }
                    if ((_if_cond_3 == 1)) {
                        {

                            {
                                double ptendency_loc_t_0_in_0 = ptendency_loc_t[((_for_it_15 + (klon * (_for_it_14 - 1))) - 1)];
                                double ydthf_0_in_ralvdcp = v_ydthf_ralvdcp[0];
                                double zqadj_0_in = zqadj;
                                double ptendency_loc_t_out_0;

                                ///////////////////
                                // Tasklet code (T_l490_c490)
                                ptendency_loc_t_out_0 = (ptendency_loc_t_0_in_0 - (ydthf_0_in_ralvdcp * zqadj_0_in));
                                ///////////////////

                                ptendency_loc_t[((_for_it_15 + (klon * (_for_it_14 - 1))) - 1)] = ptendency_loc_t_out_0;
                            }

                        }
                    }
                    _if_cond_4 = (iphase[(_for_it_13 - 1)] == 2);
                    if ((_if_cond_4 == 1)) {
                        {

                            {
                                double ptendency_loc_t_0_in_0 = ptendency_loc_t[((_for_it_15 + (klon * (_for_it_14 - 1))) - 1)];
                                double ydthf_0_in_ralsdcp = v_ydthf_ralsdcp[0];
                                double zqadj_0_in = zqadj;
                                double ptendency_loc_t_out_0;

                                ///////////////////
                                // Tasklet code (T_l491_c491)
                                ptendency_loc_t_out_0 = (ptendency_loc_t_0_in_0 - (ydthf_0_in_ralsdcp * zqadj_0_in));
                                ///////////////////

                                ptendency_loc_t[((_for_it_15 + (klon * (_for_it_14 - 1))) - 1)] = ptendency_loc_t_out_0;
                            }

                        }
                    }
                    {

                        {
                            double zqx_0_in_0 = zqx[(((_for_it_15 + ((4 * klev) * klon)) + (klon * (_for_it_14 - 1))) - 1)];
                            double zqx_1_in_0 = zqx[(((_for_it_15 + ((klev * klon) * (_for_it_13 - 1))) + (klon * (_for_it_14 - 1))) - 1)];
                            double zqx_out_0;

                            ///////////////////
                            // Tasklet code (T_l492_c492)
                            zqx_out_0 = (zqx_0_in_0 + zqx_1_in_0);
                            ///////////////////

                            zqx[(((_for_it_15 + ((4 * klev) * klon)) + (klon * (_for_it_14 - 1))) - 1)] = zqx_out_0;
                        }

                    }
                    {

                        {
                            double zqx_out_0;

                            ///////////////////
                            // Tasklet code (T_l493_c493)
                            zqx_out_0 = 0.0;
                            ///////////////////

                            zqx[(((_for_it_15 + ((klev * klon) * (_for_it_13 - 1))) + (klon * (_for_it_14 - 1))) - 1)] = zqx_out_0;
                        }

                    }
                }

            }

        }

    }

    for (_for_it_16 = 1; (_for_it_16 <= klev); _for_it_16 = (_for_it_16 + 1)) {
        for (_for_it_17 = 1; (_for_it_17 <= kfdia); _for_it_17 = (_for_it_17 + 1)) {
            {
                double tmp_call_106_0;

                {
                    double ztp1_0_in_0 = ztp1[((_for_it_17 + (klon * (_for_it_16 - 1))) - 1)];
                    double oka_out;

                    ///////////////////
                    // Tasklet code (T_l500_c500)
                    oka_out = ztp1_0_in_0;
                    ///////////////////

                    oka = oka_out;
                }
                {
                    double ptare_var_2_0_in = oka;
                    double ydthf_var_3_0_in_rtwat = v_ydthf_var_3_rtwat[0];
                    double tmp_call_106_out;

                    ///////////////////
                    // Tasklet code (T_l1368_c1368)
                    tmp_call_106_out = min(ydthf_var_3_0_in_rtwat, ptare_var_2_0_in);
                    ///////////////////

                    tmp_call_106_0 = tmp_call_106_out;
                }
                {
                    double tmp_call_106_0_in = tmp_call_106_0;
                    double ydthf_var_3_0_in_rtice = v_ydthf_var_3_rtice[0];
                    double tmp_call_105_out;

                    ///////////////////
                    // Tasklet code (T_l1368_c1368)
                    tmp_call_105_out = max(ydthf_var_3_0_in_rtice, tmp_call_106_0_in);
                    ///////////////////

                    tmp_call_105_0 = tmp_call_105_out;
                }

            }
            {
                double tmp_call_104_0;
                double tmp_arg_66_0;

                {
                    double tmp_call_105_0_in = tmp_call_105_0;
                    double ydthf_var_3_0_in_rtice = v_ydthf_var_3_rtice[0];
                    double ydthf_var_3_1_in_rtwat_rtice_r = v_ydthf_var_3_rtwat_rtice_r[0];
                    double tmp_arg_66_out;

                    ///////////////////
                    // Tasklet code (T_l1368_c1368)
                    tmp_arg_66_out = ((tmp_call_105_0_in - ydthf_var_3_0_in_rtice) * ydthf_var_3_1_in_rtwat_rtice_r);
                    ///////////////////

                    tmp_arg_66_0 = tmp_arg_66_out;
                }
                {
                    double tmp_arg_66_0_in = tmp_arg_66_0;
                    double tmp_call_104_out;

                    ///////////////////
                    // Tasklet code (T_l1368_c1368)
                    tmp_call_104_out = (dace::math::ipow(tmp_arg_66_0_in, 2));
                    ///////////////////

                    tmp_call_104_0 = tmp_call_104_out;
                }
                {
                    double tmp_call_104_0_in = tmp_call_104_0;
                    double foealfa__ret_out;

                    ///////////////////
                    // Tasklet code (T_l1368_c1368)
                    foealfa__ret_out = min(1.0, tmp_call_104_0_in);
                    ///////////////////

                    tmp_call_0 = foealfa__ret_out;
                }

            }
            {
                double tmp_arg_67_2;
                double tmp_call_106_1_8;

                {
                    double tmp_call_0_0_in = tmp_call_0;
                    double zfoealfa_out_0;

                    ///////////////////
                    // Tasklet code (T_l501_c501)
                    zfoealfa_out_0 = tmp_call_0_0_in;
                    ///////////////////

                    zfoealfa[((_for_it_17 + (klon * (_for_it_16 - 1))) - 1)] = zfoealfa_out_0;
                }
                {
                    double ztp1_0_in_0 = ztp1[((_for_it_17 + (klon * (_for_it_16 - 1))) - 1)];
                    double oka_out;

                    ///////////////////
                    // Tasklet code (T_l502_c502)
                    oka_out = ztp1_0_in_0;
                    ///////////////////

                    oka = oka_out;
                }
                {
                    double ptare_var_2_0_in = oka;
                    double ydthf_var_3_0_in_rtwat = v_ydthf_var_3_rtwat[0];
                    double tmp_call_106_out;

                    ///////////////////
                    // Tasklet code (T_l1368_c1368)
                    tmp_call_106_out = min(ydthf_var_3_0_in_rtwat, ptare_var_2_0_in);
                    ///////////////////

                    tmp_call_106_1_8 = tmp_call_106_out;
                }
                {
                    double tmp_call_106_0_in = tmp_call_106_1_8;
                    double ydthf_var_3_0_in_rtice = v_ydthf_var_3_rtice[0];
                    double tmp_call_105_out;

                    ///////////////////
                    // Tasklet code (T_l1368_c1368)
                    tmp_call_105_out = max(ydthf_var_3_0_in_rtice, tmp_call_106_0_in);
                    ///////////////////

                    tmp_call_105_1_8 = tmp_call_105_out;
                }
                {
                    double ptare_var_4_0_in = oka;
                    double ptare_var_4_1_in = oka;
                    double ydcst_var_6_0_in_rtt = v_ydcst_var_6_rtt[0];
                    double ydthf_var_5_0_in_r3ies = v_ydthf_var_5_r3ies[0];
                    double ydthf_var_5_1_in_r4ies = v_ydthf_var_5_r4ies[0];
                    double tmp_arg_67_out;

                    ///////////////////
                    // Tasklet code (T_l1377_c1377)
                    tmp_arg_67_out = ((ydthf_var_5_0_in_r3ies * (ptare_var_4_0_in - ydcst_var_6_0_in_rtt)) / (ptare_var_4_1_in - ydthf_var_5_1_in_r4ies));
                    ///////////////////

                    tmp_arg_67_2 = tmp_arg_67_out;
                }
                {
                    double tmp_arg_67_0_in = tmp_arg_67_2;
                    double tmp_call_110_out;

                    ///////////////////
                    // Tasklet code (T_l1377_c1377)
                    tmp_call_110_out = exp(tmp_arg_67_0_in);
                    ///////////////////

                    tmp_call_110_2 = tmp_call_110_out;
                }

            }
            {
                double tmp_call_104_1_8;
                double tmp_arg_66_1_8;

                {
                    double tmp_call_105_0_in = tmp_call_105_1_8;
                    double ydthf_var_3_0_in_rtice = v_ydthf_var_3_rtice[0];
                    double ydthf_var_3_1_in_rtwat_rtice_r = v_ydthf_var_3_rtwat_rtice_r[0];
                    double tmp_arg_66_out;

                    ///////////////////
                    // Tasklet code (T_l1368_c1368)
                    tmp_arg_66_out = ((tmp_call_105_0_in - ydthf_var_3_0_in_rtice) * ydthf_var_3_1_in_rtwat_rtice_r);
                    ///////////////////

                    tmp_arg_66_1_8 = tmp_arg_66_out;
                }
                {
                    double tmp_arg_66_0_in = tmp_arg_66_1_8;
                    double tmp_call_104_out;

                    ///////////////////
                    // Tasklet code (T_l1368_c1368)
                    tmp_call_104_out = (dace::math::ipow(tmp_arg_66_0_in, 2));
                    ///////////////////

                    tmp_call_104_1_8 = tmp_call_104_out;
                }
                {
                    double tmp_call_104_0_in = tmp_call_104_1_8;
                    double foealfa__ret_out;

                    ///////////////////
                    // Tasklet code (T_l1368_c1368)
                    foealfa__ret_out = min(1.0, tmp_call_104_0_in);
                    ///////////////////

                    tmp_call_109_2 = foealfa__ret_out;
                }

            }
            {
                double tmp_arg_68_2;
                double tmp_call_106_0_8;

                {
                    double ptare_var_2_0_in = oka;
                    double ydthf_var_3_0_in_rtwat = v_ydthf_var_3_rtwat[0];
                    double tmp_call_106_out;

                    ///////////////////
                    // Tasklet code (T_l1368_c1368)
                    tmp_call_106_out = min(ydthf_var_3_0_in_rtwat, ptare_var_2_0_in);
                    ///////////////////

                    tmp_call_106_0_8 = tmp_call_106_out;
                }
                {
                    double tmp_call_106_0_in = tmp_call_106_0_8;
                    double ydthf_var_3_0_in_rtice = v_ydthf_var_3_rtice[0];
                    double tmp_call_105_out;

                    ///////////////////
                    // Tasklet code (T_l1368_c1368)
                    tmp_call_105_out = max(ydthf_var_3_0_in_rtice, tmp_call_106_0_in);
                    ///////////////////

                    tmp_call_105_0_8 = tmp_call_105_out;
                }
                {
                    double ptare_var_4_0_in = oka;
                    double ptare_var_4_1_in = oka;
                    double ydcst_var_6_0_in_rtt = v_ydcst_var_6_rtt[0];
                    double ydthf_var_5_0_in_r3les = v_ydthf_var_5_r3les[0];
                    double ydthf_var_5_1_in_r4les = v_ydthf_var_5_r4les[0];
                    double tmp_arg_68_out;

                    ///////////////////
                    // Tasklet code (T_l1377_c1377)
                    tmp_arg_68_out = ((ydthf_var_5_0_in_r3les * (ptare_var_4_0_in - ydcst_var_6_0_in_rtt)) / (ptare_var_4_1_in - ydthf_var_5_1_in_r4les));
                    ///////////////////

                    tmp_arg_68_2 = tmp_arg_68_out;
                }
                {
                    double tmp_arg_68_0_in = tmp_arg_68_2;
                    double tmp_call_108_out;

                    ///////////////////
                    // Tasklet code (T_l1377_c1377)
                    tmp_call_108_out = exp(tmp_arg_68_0_in);
                    ///////////////////

                    tmp_call_108_2 = tmp_call_108_out;
                }

            }
            {
                double tmp_call_1;
                double tmp_call_5;
                double tmp_arg_0;
                double tmp_call_107_2;
                double tmp_call_104_0_8;
                double tmp_arg_66_0_8;

                {
                    double tmp_call_105_0_in = tmp_call_105_0_8;
                    double ydthf_var_3_0_in_rtice = v_ydthf_var_3_rtice[0];
                    double ydthf_var_3_1_in_rtwat_rtice_r = v_ydthf_var_3_rtwat_rtice_r[0];
                    double tmp_arg_66_out;

                    ///////////////////
                    // Tasklet code (T_l1368_c1368)
                    tmp_arg_66_out = ((tmp_call_105_0_in - ydthf_var_3_0_in_rtice) * ydthf_var_3_1_in_rtwat_rtice_r);
                    ///////////////////

                    tmp_arg_66_0_8 = tmp_arg_66_out;
                }
                {
                    double tmp_arg_66_0_in = tmp_arg_66_0_8;
                    double tmp_call_104_out;

                    ///////////////////
                    // Tasklet code (T_l1368_c1368)
                    tmp_call_104_out = (dace::math::ipow(tmp_arg_66_0_in, 2));
                    ///////////////////

                    tmp_call_104_0_8 = tmp_call_104_out;
                }
                {
                    double tmp_call_104_0_in = tmp_call_104_0_8;
                    double foealfa__ret_out;

                    ///////////////////
                    // Tasklet code (T_l1368_c1368)
                    foealfa__ret_out = min(1.0, tmp_call_104_0_in);
                    ///////////////////

                    tmp_call_107_2 = foealfa__ret_out;
                }
                {
                    double tmp_call_107_0_in = tmp_call_107_2;
                    double tmp_call_108_0_in = tmp_call_108_2;
                    double tmp_call_109_0_in = tmp_call_109_2;
                    double tmp_call_110_0_in = tmp_call_110_2;
                    double ydthf_var_5_0_in_r2es = v_ydthf_var_5_r2es[0];
                    double foeewm__ret_out;

                    ///////////////////
                    // Tasklet code (T_l1377_c1377)
                    foeewm__ret_out = (ydthf_var_5_0_in_r2es * ((tmp_call_107_0_in * tmp_call_108_0_in) + ((1.0 - tmp_call_109_0_in) * tmp_call_110_0_in)));
                    ///////////////////

                    tmp_call_5 = foeewm__ret_out;
                }
                {
                    double pap_0_in_0 = pap[((_for_it_17 + (klon * (_for_it_16 - 1))) - 1)];
                    double tmp_call_5_0_in = tmp_call_5;
                    double tmp_arg_0_out;

                    ///////////////////
                    // Tasklet code (T_l503_c503)
                    tmp_arg_0_out = (tmp_call_5_0_in / pap_0_in_0);
                    ///////////////////

                    tmp_arg_0 = tmp_arg_0_out;
                }
                {
                    double tmp_arg_0_0_in = tmp_arg_0;
                    double tmp_call_1_out;

                    ///////////////////
                    // Tasklet code (T_l503_c503)
                    tmp_call_1_out = min(tmp_arg_0_0_in, 0.5);
                    ///////////////////

                    tmp_call_1 = tmp_call_1_out;
                }
                {
                    double tmp_call_1_0_in = tmp_call_1;
                    double zfoeewmt_out_0;

                    ///////////////////
                    // Tasklet code (T_l503_c503)
                    zfoeewmt_out_0 = tmp_call_1_0_in;
                    ///////////////////

                    zfoeewmt[((_for_it_17 + (klon * (_for_it_16 - 1))) - 1)] = zfoeewmt_out_0;
                }
                {
                    double zfoeewmt_0_in_0 = zfoeewmt[((_for_it_17 + (klon * (_for_it_16 - 1))) - 1)];
                    double zqsmix_out_0;

                    ///////////////////
                    // Tasklet code (T_l504_c504)
                    zqsmix_out_0 = zfoeewmt_0_in_0;
                    ///////////////////

                    zqsmix[((_for_it_17 + (klon * (_for_it_16 - 1))) - 1)] = zqsmix_out_0;
                }
                {
                    double ydcst_0_in_retv = v_ydcst_retv[0];
                    double zqsmix_0_in_0 = zqsmix[((_for_it_17 + (klon * (_for_it_16 - 1))) - 1)];
                    double zqsmix_1_in_0 = zqsmix[((_for_it_17 + (klon * (_for_it_16 - 1))) - 1)];
                    double zqsmix_out_0;

                    ///////////////////
                    // Tasklet code (T_l505_c505)
                    zqsmix_out_0 = (zqsmix_0_in_0 / (1.0 - (ydcst_0_in_retv * zqsmix_1_in_0)));
                    ///////////////////

                    zqsmix[((_for_it_17 + (klon * (_for_it_16 - 1))) - 1)] = zqsmix_out_0;
                }
                {
                    double ztp1_0_in_0 = ztp1[((_for_it_17 + (klon * (_for_it_16 - 1))) - 1)];
                    double oka_out;

                    ///////////////////
                    // Tasklet code (T_l506_c506)
                    oka_out = ztp1_0_in_0;
                    ///////////////////

                    oka = oka_out;
                }

            }
            if (((oka - *v_ydcst_var_1_rtt) >= 0.0)) {
                {

                    {
                        double tmp_call_103_out;

                        ///////////////////
                        // Tasklet code (T_l1361_c1361)
                        tmp_call_103_out = abs(1.0);
                        ///////////////////

                        tmp_call_103_0 = tmp_call_103_out;
                    }

                }
            } else {
                {
                    double tmp_call_1_0;

                    {
                        double tmp_call_1_out;

                        ///////////////////
                        // Tasklet code (T_l1361_c1361)
                        tmp_call_1_out = abs(1.0);
                        ///////////////////

                        tmp_call_1_0 = tmp_call_1_out;
                    }
                    {
                        double tmp_call_1_0_in = tmp_call_1_0;
                        double tmp_call_103_out;

                        ///////////////////
                        // Tasklet code (T_l1361_c1361)
                        tmp_call_103_out = (- tmp_call_1_0_in);
                        ///////////////////

                        tmp_call_103_0 = tmp_call_103_out;
                    }

                }
            }
            {
                double tmp_call_117_2;
                double tmp_arg_71_2;
                double tmp_call_118_1;
                double tmp_arg_72_1;

                {
                    double tmp_call_103_0_in = tmp_call_103_0;
                    double foedelta__ret_out;

                    ///////////////////
                    // Tasklet code (T_l1361_c1361)
                    foedelta__ret_out = max(0.0, tmp_call_103_0_in);
                    ///////////////////

                    zalfa = foedelta__ret_out;
                }
                {
                    double ztp1_0_in_0 = ztp1[((_for_it_17 + (klon * (_for_it_16 - 1))) - 1)];
                    double oka_out;

                    ///////////////////
                    // Tasklet code (T_l508_c508)
                    oka_out = ztp1_0_in_0;
                    ///////////////////

                    oka = oka_out;
                }
                {
                    double ptare_var_14_0_in = oka;
                    double ptare_var_14_1_in = oka;
                    double ydcst_var_16_0_in_rtt = v_ydcst_var_16_rtt[0];
                    double ydthf_var_15_0_in_r3ies = v_ydthf_var_15_r3ies[0];
                    double ydthf_var_15_1_in_r4ies = v_ydthf_var_15_r4ies[0];
                    double tmp_arg_72_out;

                    ///////////////////
                    // Tasklet code (T_l1409_c1409)
                    tmp_arg_72_out = ((ydthf_var_15_0_in_r3ies * (ptare_var_14_0_in - ydcst_var_16_0_in_rtt)) / (ptare_var_14_1_in - ydthf_var_15_1_in_r4ies));
                    ///////////////////

                    tmp_arg_72_1 = tmp_arg_72_out;
                }
                {
                    double tmp_arg_72_0_in = tmp_arg_72_1;
                    double tmp_call_118_out;

                    ///////////////////
                    // Tasklet code (T_l1409_c1409)
                    tmp_call_118_out = exp(tmp_arg_72_0_in);
                    ///////////////////

                    tmp_call_118_1 = tmp_call_118_out;
                }
                {
                    double tmp_call_118_0_in = tmp_call_118_1;
                    double ydthf_var_15_0_in_r2es = v_ydthf_var_15_r2es[0];
                    double foeeice__ret_out;

                    ///////////////////
                    // Tasklet code (T_l1409_c1409)
                    foeeice__ret_out = (ydthf_var_15_0_in_r2es * tmp_call_118_0_in);
                    ///////////////////

                    tmp_call_7 = foeeice__ret_out;
                }
                {
                    double ptare_var_11_0_in = oka;
                    double ptare_var_11_1_in = oka;
                    double ydcst_var_13_0_in_rtt = v_ydcst_var_13_rtt[0];
                    double ydthf_var_12_0_in_r3les = v_ydthf_var_12_r3les[0];
                    double ydthf_var_12_1_in_r4les = v_ydthf_var_12_r4les[0];
                    double tmp_arg_71_out;

                    ///////////////////
                    // Tasklet code (T_l1400_c1400)
                    tmp_arg_71_out = ((ydthf_var_12_0_in_r3les * (ptare_var_11_0_in - ydcst_var_13_0_in_rtt)) / (ptare_var_11_1_in - ydthf_var_12_1_in_r4les));
                    ///////////////////

                    tmp_arg_71_2 = tmp_arg_71_out;
                }
                {
                    double tmp_arg_71_0_in = tmp_arg_71_2;
                    double tmp_call_117_out;

                    ///////////////////
                    // Tasklet code (T_l1400_c1400)
                    tmp_call_117_out = exp(tmp_arg_71_0_in);
                    ///////////////////

                    tmp_call_117_2 = tmp_call_117_out;
                }
                {
                    double tmp_call_117_0_in = tmp_call_117_2;
                    double ydthf_var_12_0_in_r2es = v_ydthf_var_12_r2es[0];
                    double foeeliq__ret_out;

                    ///////////////////
                    // Tasklet code (T_l1400_c1400)
                    foeeliq__ret_out = (ydthf_var_12_0_in_r2es * tmp_call_117_0_in);
                    ///////////////////

                    tmp_call_6 = foeeliq__ret_out;
                }

            }
            {
                double tmp_call_2;
                double tmp_call_3;
                double tmp_call_4;
                double tmp_call_8;
                double tmp_arg_1;
                double tmp_arg_2;
                double tmp_call_117_1;
                double tmp_arg_71_1;
                toethf** ydthf_var_12_1;
                ydthf_var_12_1 = &ydthf;
                tomcst** ydcst_var_13_1;
                ydcst_var_13_1 = &ydcst;

                {
                    double pap_0_in_0 = pap[((_for_it_17 + (klon * (_for_it_16 - 1))) - 1)];
                    double tmp_call_6_0_in = tmp_call_6;
                    double tmp_call_7_0_in = tmp_call_7;
                    double zalfa_0_in = zalfa;
                    double zalfa_1_in = zalfa;
                    double tmp_arg_1_out;

                    ///////////////////
                    // Tasklet code (T_l509_c509)
                    tmp_arg_1_out = (((zalfa_0_in * tmp_call_6_0_in) + ((1.0 - zalfa_1_in) * tmp_call_7_0_in)) / pap_0_in_0);
                    ///////////////////

                    tmp_arg_1 = tmp_arg_1_out;
                }
                {
                    double tmp_arg_1_0_in = tmp_arg_1;
                    double tmp_call_2_out;

                    ///////////////////
                    // Tasklet code (T_l509_c509)
                    tmp_call_2_out = min(tmp_arg_1_0_in, 0.5);
                    ///////////////////

                    tmp_call_2 = tmp_call_2_out;
                }
                {
                    double tmp_call_2_0_in = tmp_call_2;
                    double zfoeew_out_0;

                    ///////////////////
                    // Tasklet code (T_l509_c509)
                    zfoeew_out_0 = tmp_call_2_0_in;
                    ///////////////////

                    zfoeew[((_for_it_17 + (klon * (_for_it_16 - 1))) - 1)] = zfoeew_out_0;
                }
                {
                    double zfoeew_0_in_0 = zfoeew[((_for_it_17 + (klon * (_for_it_16 - 1))) - 1)];
                    double tmp_call_3_out;

                    ///////////////////
                    // Tasklet code (T_l510_c510)
                    tmp_call_3_out = min(0.5, zfoeew_0_in_0);
                    ///////////////////

                    tmp_call_3 = tmp_call_3_out;
                }
                {
                    double tmp_call_3_0_in = tmp_call_3;
                    double zfoeew_out_0;

                    ///////////////////
                    // Tasklet code (T_l510_c510)
                    zfoeew_out_0 = tmp_call_3_0_in;
                    ///////////////////

                    zfoeew[((_for_it_17 + (klon * (_for_it_16 - 1))) - 1)] = zfoeew_out_0;
                }
                {
                    double ydcst_0_in_retv = v_ydcst_retv[0];
                    double zfoeew_0_in_0 = zfoeew[((_for_it_17 + (klon * (_for_it_16 - 1))) - 1)];
                    double zfoeew_1_in_0 = zfoeew[((_for_it_17 + (klon * (_for_it_16 - 1))) - 1)];
                    double zqsice_out_0;

                    ///////////////////
                    // Tasklet code (T_l511_c511)
                    zqsice_out_0 = (zfoeew_0_in_0 / (1.0 - (ydcst_0_in_retv * zfoeew_1_in_0)));
                    ///////////////////

                    zqsice[((_for_it_17 + (klon * (_for_it_16 - 1))) - 1)] = zqsice_out_0;
                }
                {
                    double ztp1_0_in_0 = ztp1[((_for_it_17 + (klon * (_for_it_16 - 1))) - 1)];
                    double oka_out;

                    ///////////////////
                    // Tasklet code (T_l512_c512)
                    oka_out = ztp1_0_in_0;
                    ///////////////////

                    oka = oka_out;
                }
                {
                    double ptare_var_11_0_in = oka;
                    double ptare_var_11_1_in = oka;
                    double ydcst_var_13_0_in_rtt = v_ydcst_var_13_rtt[0];
                    double ydthf_var_12_0_in_r3les = v_ydthf_var_12_r3les[0];
                    double ydthf_var_12_1_in_r4les = v_ydthf_var_12_r4les[0];
                    double tmp_arg_71_out;

                    ///////////////////
                    // Tasklet code (T_l1400_c1400)
                    tmp_arg_71_out = ((ydthf_var_12_0_in_r3les * (ptare_var_11_0_in - ydcst_var_13_0_in_rtt)) / (ptare_var_11_1_in - ydthf_var_12_1_in_r4les));
                    ///////////////////

                    tmp_arg_71_1 = tmp_arg_71_out;
                }
                {
                    double tmp_arg_71_0_in = tmp_arg_71_1;
                    double tmp_call_117_out;

                    ///////////////////
                    // Tasklet code (T_l1400_c1400)
                    tmp_call_117_out = exp(tmp_arg_71_0_in);
                    ///////////////////

                    tmp_call_117_1 = tmp_call_117_out;
                }
                {
                    double tmp_call_117_0_in = tmp_call_117_1;
                    double ydthf_var_12_0_in_r2es = v_ydthf_var_12_r2es[0];
                    double foeeliq__ret_out;

                    ///////////////////
                    // Tasklet code (T_l1400_c1400)
                    foeeliq__ret_out = (ydthf_var_12_0_in_r2es * tmp_call_117_0_in);
                    ///////////////////

                    tmp_call_8 = foeeliq__ret_out;
                }
                {
                    double pap_0_in_0 = pap[((_for_it_17 + (klon * (_for_it_16 - 1))) - 1)];
                    double tmp_call_8_0_in = tmp_call_8;
                    double tmp_arg_2_out;

                    ///////////////////
                    // Tasklet code (T_l513_c513)
                    tmp_arg_2_out = (tmp_call_8_0_in / pap_0_in_0);
                    ///////////////////

                    tmp_arg_2 = tmp_arg_2_out;
                }
                {
                    double tmp_arg_2_0_in = tmp_arg_2;
                    double tmp_call_4_out;

                    ///////////////////
                    // Tasklet code (T_l513_c513)
                    tmp_call_4_out = min(tmp_arg_2_0_in, 0.5);
                    ///////////////////

                    tmp_call_4 = tmp_call_4_out;
                }
                {
                    double tmp_call_4_0_in = tmp_call_4;
                    double zfoeeliqt_out_0;

                    ///////////////////
                    // Tasklet code (T_l513_c513)
                    zfoeeliqt_out_0 = tmp_call_4_0_in;
                    ///////////////////

                    zfoeeliqt[((_for_it_17 + (klon * (_for_it_16 - 1))) - 1)] = zfoeeliqt_out_0;
                }
                {
                    double zfoeeliqt_0_in_0 = zfoeeliqt[((_for_it_17 + (klon * (_for_it_16 - 1))) - 1)];
                    double zqsliq_out_0;

                    ///////////////////
                    // Tasklet code (T_l514_c514)
                    zqsliq_out_0 = zfoeeliqt_0_in_0;
                    ///////////////////

                    zqsliq[((_for_it_17 + (klon * (_for_it_16 - 1))) - 1)] = zqsliq_out_0;
                }

            }
            {

                {
                    double ydcst_0_in_retv = v_ydcst_retv[0];
                    double zqsliq_0_in_0 = zqsliq[((_for_it_17 + (klon * (_for_it_16 - 1))) - 1)];
                    double zqsliq_1_in_0 = zqsliq[((_for_it_17 + (klon * (_for_it_16 - 1))) - 1)];
                    double zqsliq_out_0;

                    ///////////////////
                    // Tasklet code (T_l515_c515)
                    zqsliq_out_0 = (zqsliq_0_in_0 / (1.0 - (ydcst_0_in_retv * zqsliq_1_in_0)));
                    ///////////////////

                    zqsliq[((_for_it_17 + (klon * (_for_it_16 - 1))) - 1)] = zqsliq_out_0;
                }

            }

        }

    }

    for (_for_it_18 = 1; (_for_it_18 <= klev); _for_it_18 = (_for_it_18 + 1)) {
        for (_for_it_19 = 1; (_for_it_19 <= kfdia); _for_it_19 = (_for_it_19 + 1)) {
            {
                double tmp_call_9;
                double tmp_call_10;

                {
                    double za_0_in_0 = za[((_for_it_19 + (klon * (_for_it_18 - 1))) - 1)];
                    double tmp_call_10_out;

                    ///////////////////
                    // Tasklet code (T_l520_c520)
                    tmp_call_10_out = min(1.0, za_0_in_0);
                    ///////////////////

                    tmp_call_10 = tmp_call_10_out;
                }
                {
                    double tmp_call_10_0_in = tmp_call_10;
                    double tmp_call_9_out;

                    ///////////////////
                    // Tasklet code (T_l520_c520)
                    tmp_call_9_out = max(0.0, tmp_call_10_0_in);
                    ///////////////////

                    tmp_call_9 = tmp_call_9_out;
                }
                {
                    double tmp_call_9_0_in = tmp_call_9;
                    double za_out_0;

                    ///////////////////
                    // Tasklet code (T_l520_c520)
                    za_out_0 = tmp_call_9_0_in;
                    ///////////////////

                    za[((_for_it_19 + (klon * (_for_it_18 - 1))) - 1)] = za_out_0;
                }
                {
                    double zqx_0_in_0 = zqx[((_for_it_19 + (klon * (_for_it_18 - 1))) - 1)];
                    double zqx_1_in_0 = zqx[(((_for_it_19 + (klev * klon)) + (klon * (_for_it_18 - 1))) - 1)];
                    double zli_out_0;

                    ///////////////////
                    // Tasklet code (T_l521_c521)
                    zli_out_0 = (zqx_0_in_0 + zqx_1_in_0);
                    ///////////////////

                    zli[((_for_it_19 + (klon * (_for_it_18 - 1))) - 1)] = zli_out_0;
                }
                {
                    double ydecldp_0_in_rlmin = v_ydecldp_rlmin[0];
                    double zli_0_in_0 = zli[((_for_it_19 + (klon * (_for_it_18 - 1))) - 1)];
                    double _if_cond_5_out;

                    ///////////////////
                    // Tasklet code (T_l0_c0)
                    _if_cond_5_out = (zli_0_in_0 > ydecldp_0_in_rlmin);
                    ///////////////////

                    _if_cond_5 = _if_cond_5_out;
                }

            }
            if ((_if_cond_5 == 1)) {
                {

                    {
                        double zli_0_in_0 = zli[((_for_it_19 + (klon * (_for_it_18 - 1))) - 1)];
                        double zqx_0_in_0 = zqx[((_for_it_19 + (klon * (_for_it_18 - 1))) - 1)];
                        double zliqfrac_out_0;

                        ///////////////////
                        // Tasklet code (T_l523_c523)
                        zliqfrac_out_0 = (zqx_0_in_0 / zli_0_in_0);
                        ///////////////////

                        zliqfrac[((_for_it_19 + (klon * (_for_it_18 - 1))) - 1)] = zliqfrac_out_0;
                    }
                    {
                        double zliqfrac_0_in_0 = zliqfrac[((_for_it_19 + (klon * (_for_it_18 - 1))) - 1)];
                        double zicefrac_out_0;

                        ///////////////////
                        // Tasklet code (T_l524_c524)
                        zicefrac_out_0 = (1.0 - zliqfrac_0_in_0);
                        ///////////////////

                        zicefrac[((_for_it_19 + (klon * (_for_it_18 - 1))) - 1)] = zicefrac_out_0;
                    }

                }
            } else {
                {

                    {
                        double zliqfrac_out_0;

                        ///////////////////
                        // Tasklet code (T_l526_c526)
                        zliqfrac_out_0 = 0.0;
                        ///////////////////

                        zliqfrac[((_for_it_19 + (klon * (_for_it_18 - 1))) - 1)] = zliqfrac_out_0;
                    }
                    {
                        double zicefrac_out_0;

                        ///////////////////
                        // Tasklet code (T_l527_c527)
                        zicefrac_out_0 = 0.0;
                        ///////////////////

                        zicefrac[((_for_it_19 + (klon * (_for_it_18 - 1))) - 1)] = zicefrac_out_0;
                    }

                }
            }

        }

    }

    for (tmp_parfor_12 = 1; (tmp_parfor_12 <= klon); tmp_parfor_12 = (tmp_parfor_12 + 1)) {
        {

            {
                double zanewm1_out_0;

                ///////////////////
                // Tasklet code (T_l543_c543)
                zanewm1_out_0 = 0.0;
                ///////////////////

                zanewm1[(tmp_parfor_12 - 1)] = zanewm1_out_0;
            }

        }

    }

    for (tmp_parfor_13 = 1; (tmp_parfor_13 <= klon); tmp_parfor_13 = (tmp_parfor_13 + 1)) {
        {

            {
                double zda_out_0;

                ///////////////////
                // Tasklet code (T_l544_c544)
                zda_out_0 = 0.0;
                ///////////////////

                zda[(tmp_parfor_13 - 1)] = zda_out_0;
            }

        }

    }

    for (tmp_parfor_14 = 1; (tmp_parfor_14 <= klon); tmp_parfor_14 = (tmp_parfor_14 + 1)) {
        {

            {
                double zcovpclr_out_0;

                ///////////////////
                // Tasklet code (T_l545_c545)
                zcovpclr_out_0 = 0.0;
                ///////////////////

                zcovpclr[(tmp_parfor_14 - 1)] = zcovpclr_out_0;
            }

        }

    }

    for (tmp_parfor_15 = 1; (tmp_parfor_15 <= klon); tmp_parfor_15 = (tmp_parfor_15 + 1)) {
        {

            {
                double zcovpmax_out_0;

                ///////////////////
                // Tasklet code (T_l546_c546)
                zcovpmax_out_0 = 0.0;
                ///////////////////

                zcovpmax[(tmp_parfor_15 - 1)] = zcovpmax_out_0;
            }

        }

    }

    for (tmp_parfor_16 = 1; (tmp_parfor_16 <= klon); tmp_parfor_16 = (tmp_parfor_16 + 1)) {
        {

            {
                double zcovptot_out_0;

                ///////////////////
                // Tasklet code (T_l547_c547)
                zcovptot_out_0 = 0.0;
                ///////////////////

                zcovptot[(tmp_parfor_16 - 1)] = zcovptot_out_0;
            }

        }

    }

    for (tmp_parfor_17 = 1; (tmp_parfor_17 <= klon); tmp_parfor_17 = (tmp_parfor_17 + 1)) {
        {

            {
                double zcldtopdist_out_0;

                ///////////////////
                // Tasklet code (T_l548_c548)
                zcldtopdist_out_0 = 0.0;
                ///////////////////

                zcldtopdist[(tmp_parfor_17 - 1)] = zcldtopdist_out_0;
            }

        }

    }

    {


    }

    for (_for_it_23 = *v_ydecldp_ncldtop; (_for_it_23 <= klev); _for_it_23 = (_for_it_23 + 1)) {
        for (_for_it_24 = 1; (_for_it_24 <= 5); _for_it_24 = (_for_it_24 + 1)) {
            for (_for_it_25 = 1; (_for_it_25 <= kfdia); _for_it_25 = (_for_it_25 + 1)) {
                {

                    {
                        double zqx_0_in_0 = zqx[(((_for_it_25 + ((klev * klon) * (_for_it_24 - 1))) + (klon * (_for_it_23 - 1))) - 1)];
                        double zqxfg_out_0;

                        ///////////////////
                        // Tasklet code (T_l552_c552)
                        zqxfg_out_0 = zqx_0_in_0;
                        ///////////////////

                        zqxfg[((_for_it_25 + (klon * (_for_it_24 - 1))) - 1)] = zqxfg_out_0;
                    }

                }

            }

        }
        for (tmp_parfor_18 = 1; (tmp_parfor_18 <= klon); tmp_parfor_18 = (tmp_parfor_18 + 1)) {
            {

                {
                    double zlicld_out_0;

                    ///////////////////
                    // Tasklet code (T_l555_c555)
                    zlicld_out_0 = 0.0;
                    ///////////////////

                    zlicld[(tmp_parfor_18 - 1)] = zlicld_out_0;
                }

            }

        }
        for (tmp_parfor_19 = 1; (tmp_parfor_19 <= klon); tmp_parfor_19 = (tmp_parfor_19 + 1)) {
            {

                {
                    double zrainaut_out_0;

                    ///////////////////
                    // Tasklet code (T_l556_c556)
                    zrainaut_out_0 = 0.0;
                    ///////////////////

                    zrainaut[(tmp_parfor_19 - 1)] = zrainaut_out_0;
                }

            }

        }
        for (tmp_parfor_20 = 1; (tmp_parfor_20 <= klon); tmp_parfor_20 = (tmp_parfor_20 + 1)) {
            {

                {
                    double zrainacc_out_0;

                    ///////////////////
                    // Tasklet code (T_l557_c557)
                    zrainacc_out_0 = 0.0;
                    ///////////////////

                    zrainacc[(tmp_parfor_20 - 1)] = zrainacc_out_0;
                }

            }

        }
        for (tmp_parfor_21 = 1; (tmp_parfor_21 <= klon); tmp_parfor_21 = (tmp_parfor_21 + 1)) {
            {

                {
                    double zsnowaut_out_0;

                    ///////////////////
                    // Tasklet code (T_l558_c558)
                    zsnowaut_out_0 = 0.0;
                    ///////////////////

                    zsnowaut[(tmp_parfor_21 - 1)] = zsnowaut_out_0;
                }

            }

        }
        for (tmp_parfor_22 = 1; (tmp_parfor_22 <= klon); tmp_parfor_22 = (tmp_parfor_22 + 1)) {
            {

                {
                    double zldefr_out_0;

                    ///////////////////
                    // Tasklet code (T_l559_c559)
                    zldefr_out_0 = 0.0;
                    ///////////////////

                    zldefr[(tmp_parfor_22 - 1)] = zldefr_out_0;
                }

            }

        }
        for (tmp_parfor_23 = 1; (tmp_parfor_23 <= klon); tmp_parfor_23 = (tmp_parfor_23 + 1)) {
            {

                {
                    double zacust_out_0;

                    ///////////////////
                    // Tasklet code (T_l560_c560)
                    zacust_out_0 = 0.0;
                    ///////////////////

                    zacust[(tmp_parfor_23 - 1)] = zacust_out_0;
                }

            }

        }
        for (tmp_parfor_24 = 1; (tmp_parfor_24 <= klon); tmp_parfor_24 = (tmp_parfor_24 + 1)) {
            {

                {
                    double zqpretot_out_0;

                    ///////////////////
                    // Tasklet code (T_l561_c561)
                    zqpretot_out_0 = 0.0;
                    ///////////////////

                    zqpretot[(tmp_parfor_24 - 1)] = zqpretot_out_0;
                }

            }

        }
        for (tmp_parfor_25 = 1; (tmp_parfor_25 <= klon); tmp_parfor_25 = (tmp_parfor_25 + 1)) {
            {

                {
                    double zlfinalsum_out_0;

                    ///////////////////
                    // Tasklet code (T_l562_c562)
                    zlfinalsum_out_0 = 0.0;
                    ///////////////////

                    zlfinalsum[(tmp_parfor_25 - 1)] = zlfinalsum_out_0;
                }

            }

        }
        for (tmp_parfor_26 = 1; (tmp_parfor_26 <= klon); tmp_parfor_26 = (tmp_parfor_26 + 1)) {
            {

                {
                    double zlcond1_out_0;

                    ///////////////////
                    // Tasklet code (T_l563_c563)
                    zlcond1_out_0 = 0.0;
                    ///////////////////

                    zlcond1[(tmp_parfor_26 - 1)] = zlcond1_out_0;
                }

            }

        }
        for (tmp_parfor_27 = 1; (tmp_parfor_27 <= klon); tmp_parfor_27 = (tmp_parfor_27 + 1)) {
            {

                {
                    double zlcond2_out_0;

                    ///////////////////
                    // Tasklet code (T_l564_c564)
                    zlcond2_out_0 = 0.0;
                    ///////////////////

                    zlcond2[(tmp_parfor_27 - 1)] = zlcond2_out_0;
                }

            }

        }
        for (tmp_parfor_28 = 1; (tmp_parfor_28 <= klon); tmp_parfor_28 = (tmp_parfor_28 + 1)) {
            {

                {
                    double zsupsat_out_0;

                    ///////////////////
                    // Tasklet code (T_l565_c565)
                    zsupsat_out_0 = 0.0;
                    ///////////////////

                    zsupsat[(tmp_parfor_28 - 1)] = zsupsat_out_0;
                }

            }

        }
        for (tmp_parfor_31 = 1; (tmp_parfor_31 <= klon); tmp_parfor_31 = (tmp_parfor_31 + 1)) {
            {

                {
                    double zsolab_out_0;

                    ///////////////////
                    // Tasklet code (T_l568_c568)
                    zsolab_out_0 = 0.0;
                    ///////////////////

                    zsolab[(tmp_parfor_31 - 1)] = zsolab_out_0;
                }

            }

        }
        for (tmp_parfor_32 = 1; (tmp_parfor_32 <= klon); tmp_parfor_32 = (tmp_parfor_32 + 1)) {
            {

                {
                    double zsolac_out_0;

                    ///////////////////
                    // Tasklet code (T_l569_c569)
                    zsolac_out_0 = 0.0;
                    ///////////////////

                    zsolac[(tmp_parfor_32 - 1)] = zsolac_out_0;
                }

            }

        }
        for (tmp_parfor_35 = 1; (tmp_parfor_35 <= 5); tmp_parfor_35 = (tmp_parfor_35 + 1)) {
            for (tmp_parfor_34 = 1; (tmp_parfor_34 <= 5); tmp_parfor_34 = (tmp_parfor_34 + 1)) {
                for (tmp_parfor_33 = 1; (tmp_parfor_33 <= klon); tmp_parfor_33 = (tmp_parfor_33 + 1)) {
                    {

                        {
                            double zsolqb_out_0;

                            ///////////////////
                            // Tasklet code (T_l570_c570)
                            zsolqb_out_0 = 0.0;
                            ///////////////////

                            zsolqb[((((klon * (tmp_parfor_34 - 1)) + ((5 * klon) * (tmp_parfor_35 - 1))) + tmp_parfor_33) - 1)] = zsolqb_out_0;
                        }

                    }

                }

            }

        }
        for (tmp_parfor_38 = 1; (tmp_parfor_38 <= 5); tmp_parfor_38 = (tmp_parfor_38 + 1)) {
            for (tmp_parfor_37 = 1; (tmp_parfor_37 <= 5); tmp_parfor_37 = (tmp_parfor_37 + 1)) {
                for (tmp_parfor_36 = 1; (tmp_parfor_36 <= klon); tmp_parfor_36 = (tmp_parfor_36 + 1)) {
                    {

                        {
                            double zsolqa_out_0;

                            ///////////////////
                            // Tasklet code (T_l571_c571)
                            zsolqa_out_0 = 0.0;
                            ///////////////////

                            zsolqa[((((klon * (tmp_parfor_37 - 1)) + ((5 * klon) * (tmp_parfor_38 - 1))) + tmp_parfor_36) - 1)] = zsolqa_out_0;
                        }

                    }

                }

            }

        }
        for (tmp_parfor_40 = 1; (tmp_parfor_40 <= 5); tmp_parfor_40 = (tmp_parfor_40 + 1)) {
            for (tmp_parfor_39 = 1; (tmp_parfor_39 <= klon); tmp_parfor_39 = (tmp_parfor_39 + 1)) {
                {

                    {
                        double zfallsrce_out_0;

                        ///////////////////
                        // Tasklet code (T_l572_c572)
                        zfallsrce_out_0 = 0.0;
                        ///////////////////

                        zfallsrce[(((klon * (tmp_parfor_40 - 1)) + tmp_parfor_39) - 1)] = zfallsrce_out_0;
                    }

                }

            }

        }
        for (tmp_parfor_42 = 1; (tmp_parfor_42 <= 5); tmp_parfor_42 = (tmp_parfor_42 + 1)) {
            for (tmp_parfor_41 = 1; (tmp_parfor_41 <= klon); tmp_parfor_41 = (tmp_parfor_41 + 1)) {
                {

                    {
                        double zfallsink_out_0;

                        ///////////////////
                        // Tasklet code (T_l573_c573)
                        zfallsink_out_0 = 0.0;
                        ///////////////////

                        zfallsink[(((klon * (tmp_parfor_42 - 1)) + tmp_parfor_41) - 1)] = zfallsink_out_0;
                    }

                }

            }

        }
        for (tmp_parfor_44 = 1; (tmp_parfor_44 <= 5); tmp_parfor_44 = (tmp_parfor_44 + 1)) {
            for (tmp_parfor_43 = 1; (tmp_parfor_43 <= klon); tmp_parfor_43 = (tmp_parfor_43 + 1)) {
                {

                    {
                        double zconvsrce_out_0;

                        ///////////////////
                        // Tasklet code (T_l574_c574)
                        zconvsrce_out_0 = 0.0;
                        ///////////////////

                        zconvsrce[(((klon * (tmp_parfor_44 - 1)) + tmp_parfor_43) - 1)] = zconvsrce_out_0;
                    }

                }

            }

        }
        for (tmp_parfor_46 = 1; (tmp_parfor_46 <= 5); tmp_parfor_46 = (tmp_parfor_46 + 1)) {
            for (tmp_parfor_45 = 1; (tmp_parfor_45 <= klon); tmp_parfor_45 = (tmp_parfor_45 + 1)) {
                {

                    {
                        double zconvsink_out_0;

                        ///////////////////
                        // Tasklet code (T_l575_c575)
                        zconvsink_out_0 = 0.0;
                        ///////////////////

                        zconvsink[(((klon * (tmp_parfor_46 - 1)) + tmp_parfor_45) - 1)] = zconvsink_out_0;
                    }

                }

            }

        }
        for (tmp_parfor_48 = 1; (tmp_parfor_48 <= 5); tmp_parfor_48 = (tmp_parfor_48 + 1)) {
            for (tmp_parfor_47 = 1; (tmp_parfor_47 <= klon); tmp_parfor_47 = (tmp_parfor_47 + 1)) {
                {

                    {
                        double zpsupsatsrce_out_0;

                        ///////////////////
                        // Tasklet code (T_l576_c576)
                        zpsupsatsrce_out_0 = 0.0;
                        ///////////////////

                        zpsupsatsrce[(((klon * (tmp_parfor_48 - 1)) + tmp_parfor_47) - 1)] = zpsupsatsrce_out_0;
                    }

                }

            }

        }
        for (tmp_parfor_50 = 1; (tmp_parfor_50 <= 5); tmp_parfor_50 = (tmp_parfor_50 + 1)) {
            for (tmp_parfor_49 = 1; (tmp_parfor_49 <= klon); tmp_parfor_49 = (tmp_parfor_49 + 1)) {
                {

                    {
                        double zratio_out_0;

                        ///////////////////
                        // Tasklet code (T_l577_c577)
                        zratio_out_0 = 0.0;
                        ///////////////////

                        zratio[(((klon * (tmp_parfor_50 - 1)) + tmp_parfor_49) - 1)] = zratio_out_0;
                    }

                }

            }

        }
        for (tmp_parfor_51 = 1; (tmp_parfor_51 <= klon); tmp_parfor_51 = (tmp_parfor_51 + 1)) {
            {

                {
                    double zicetot_out_0;

                    ///////////////////
                    // Tasklet code (T_l578_c578)
                    zicetot_out_0 = 0.0;
                    ///////////////////

                    zicetot[(tmp_parfor_51 - 1)] = zicetot_out_0;
                }

            }

        }
        for (_for_it_26 = 1; (_for_it_26 <= kfdia); _for_it_26 = (_for_it_26 + 1)) {
            {
                double *zgdp;
                zgdp = new double DACE_ALIGN(64)[klon];

                {
                    double pap_0_in_0 = pap[((_for_it_26 + (klon * (_for_it_23 - 1))) - 1)];
                    double ydcst_0_in_rd = v_ydcst_rd[0];
                    double ztp1_0_in_0 = ztp1[((_for_it_26 + (klon * (_for_it_23 - 1))) - 1)];
                    double zrho_out_0;

                    ///////////////////
                    // Tasklet code (T_l582_c582)
                    zrho_out_0 = (pap_0_in_0 / (ydcst_0_in_rd * ztp1_0_in_0));
                    ///////////////////

                    zrho[(_for_it_26 - 1)] = zrho_out_0;
                }
                {
                    double paph_0_in_0 = paph[(((_for_it_23 * klon) + _for_it_26) - 1)];
                    double paph_1_in_0 = paph[((_for_it_26 + (klon * (_for_it_23 - 1))) - 1)];
                    double zdp_out_0;

                    ///////////////////
                    // Tasklet code (T_l580_c580)
                    zdp_out_0 = (paph_0_in_0 - paph_1_in_0);
                    ///////////////////

                    zdp[(_for_it_26 - 1)] = zdp_out_0;
                }
                {
                    double ydcst_0_in_rg = v_ydcst_rg[0];
                    double zdp_0_in_0 = zdp[(_for_it_26 - 1)];
                    double zgdp_out_0;

                    ///////////////////
                    // Tasklet code (T_l581_c581)
                    zgdp_out_0 = (ydcst_0_in_rg / zdp_0_in_0);
                    ///////////////////

                    zgdp[(_for_it_26 - 1)] = zgdp_out_0;
                }
                {
                    double ptsphy_0_in = ptsphy;
                    double zgdp_0_in_0 = zgdp[(_for_it_26 - 1)];
                    double zdtgdp_out_0;

                    ///////////////////
                    // Tasklet code (T_l583_c583)
                    zdtgdp_out_0 = (ptsphy_0_in * zgdp_0_in_0);
                    ///////////////////

                    zdtgdp[(_for_it_26 - 1)] = zdtgdp_out_0;
                }
                delete[] zgdp;

            }
            {

                {
                    double ptsphy_0_in = ptsphy;
                    double ydcst_0_in_rg = v_ydcst_rg[0];
                    double zdp_0_in_0 = zdp[(_for_it_26 - 1)];
                    double zrdtgdp_out_0;

                    ///////////////////
                    // Tasklet code (T_l584_c584)
                    zrdtgdp_out_0 = (zdp_0_in_0 * (1.0 / (ptsphy_0_in * ydcst_0_in_rg)));
                    ///////////////////

                    zrdtgdp[(_for_it_26 - 1)] = zrdtgdp_out_0;
                }

            }
            if (((_for_it_23 > 1) == 1)) {
                {


                }
            }
            {
                double tmp_call_11;
                double tmp_arg_3;
                double* v_ydthf_r4les;
                v_ydthf_r4les = (double*)(&(ydthf->r4les));
                double* v_ydthf_r5les;
                v_ydthf_r5les = (double*)(&(ydthf->r5les));

                {
                    double ydthf_0_in_r4les = v_ydthf_r4les[0];
                    double ztp1_0_in_0 = ztp1[((_for_it_26 + (klon * (_for_it_23 - 1))) - 1)];
                    double tmp_arg_3_out;

                    ///////////////////
                    // Tasklet code (T_l586_c586)
                    tmp_arg_3_out = (ztp1_0_in_0 - ydthf_0_in_r4les);
                    ///////////////////

                    tmp_arg_3 = tmp_arg_3_out;
                }
                {
                    double tmp_arg_3_0_in = tmp_arg_3;
                    double tmp_call_11_out;

                    ///////////////////
                    // Tasklet code (T_l586_c586)
                    tmp_call_11_out = (dace::math::ipow(tmp_arg_3_0_in, 2));
                    ///////////////////

                    tmp_call_11 = tmp_call_11_out;
                }
                {
                    double tmp_call_11_0_in = tmp_call_11;
                    double ydthf_0_in_r5les = v_ydthf_r5les[0];
                    double zfacw_out;

                    ///////////////////
                    // Tasklet code (T_l586_c586)
                    zfacw_out = (ydthf_0_in_r5les / tmp_call_11_0_in);
                    ///////////////////

                    zfacw = zfacw_out;
                }
                {
                    double ydcst_0_in_retv = v_ydcst_retv[0];
                    double zfoeeliqt_0_in_0 = zfoeeliqt[((_for_it_26 + (klon * (_for_it_23 - 1))) - 1)];
                    double zcor_out;

                    ///////////////////
                    // Tasklet code (T_l587_c587)
                    zcor_out = (1.0 / (1.0 - (ydcst_0_in_retv * zfoeeliqt_0_in_0)));
                    ///////////////////

                    zcor = zcor_out;
                }

            }
            zalfaw = zfoealfa[((_for_it_26 + (klon * (_for_it_23 - 1))) - 1)];
            {
                double *zdqsicedt;
                zdqsicedt = new double DACE_ALIGN(64)[klon];
                double tmp_call_12;
                double tmp_arg_4;
                double* v_ydthf_r4ies;
                v_ydthf_r4ies = (double*)(&(ydthf->r4ies));
                double* v_ydthf_r5ies;
                v_ydthf_r5ies = (double*)(&(ydthf->r5ies));

                {
                    double ydthf_0_in_r4ies = v_ydthf_r4ies[0];
                    double ztp1_0_in_0 = ztp1[((_for_it_26 + (klon * (_for_it_23 - 1))) - 1)];
                    double tmp_arg_4_out;

                    ///////////////////
                    // Tasklet code (T_l590_c590)
                    tmp_arg_4_out = (ztp1_0_in_0 - ydthf_0_in_r4ies);
                    ///////////////////

                    tmp_arg_4 = tmp_arg_4_out;
                }
                {
                    double tmp_arg_4_0_in = tmp_arg_4;
                    double tmp_call_12_out;

                    ///////////////////
                    // Tasklet code (T_l590_c590)
                    tmp_call_12_out = (dace::math::ipow(tmp_arg_4_0_in, 2));
                    ///////////////////

                    tmp_call_12 = tmp_call_12_out;
                }
                {
                    double tmp_call_12_0_in = tmp_call_12;
                    double ydthf_0_in_r5ies = v_ydthf_r5ies[0];
                    double zfaci_out;

                    ///////////////////
                    // Tasklet code (T_l590_c590)
                    zfaci_out = (ydthf_0_in_r5ies / tmp_call_12_0_in);
                    ///////////////////

                    zfaci = zfaci_out;
                }
                {
                    double ydcst_0_in_retv = v_ydcst_retv[0];
                    double zfoeew_0_in_0 = zfoeew[((_for_it_26 + (klon * (_for_it_23 - 1))) - 1)];
                    double zcor_out;

                    ///////////////////
                    // Tasklet code (T_l591_c591)
                    zcor_out = (1.0 / (1.0 - (ydcst_0_in_retv * zfoeew_0_in_0)));
                    ///////////////////

                    zcor = zcor_out;
                }
                {
                    double zcor_0_in = zcor;
                    double zfaci_0_in = zfaci;
                    double zqsice_0_in_0 = zqsice[((_for_it_26 + (klon * (_for_it_23 - 1))) - 1)];
                    double zdqsicedt_out_0;

                    ///////////////////
                    // Tasklet code (T_l592_c592)
                    zdqsicedt_out_0 = ((zfaci_0_in * zcor_0_in) * zqsice_0_in_0);
                    ///////////////////

                    zdqsicedt[(_for_it_26 - 1)] = zdqsicedt_out_0;
                }
                {
                    double ydthf_0_in_ralsdcp = v_ydthf_ralsdcp[0];
                    double zdqsicedt_0_in_0 = zdqsicedt[(_for_it_26 - 1)];
                    double zcorqsice_out_0;

                    ///////////////////
                    // Tasklet code (T_l593_c593)
                    zcorqsice_out_0 = (1.0 + (ydthf_0_in_ralsdcp * zdqsicedt_0_in_0));
                    ///////////////////

                    zcorqsice[(_for_it_26 - 1)] = zcorqsice_out_0;
                }
                delete[] zdqsicedt;

            }
            zfac = ((zalfaw * zfacw) + ((1.0 - zalfaw) * zfaci));
            {
                double tmp_call_106_1_7;

                {
                    double ydcst_0_in_retv = v_ydcst_retv[0];
                    double zfoeewmt_0_in_0 = zfoeewmt[((_for_it_26 + (klon * (_for_it_23 - 1))) - 1)];
                    double zcor_out;

                    ///////////////////
                    // Tasklet code (T_l597_c597)
                    zcor_out = (1.0 / (1.0 - (ydcst_0_in_retv * zfoeewmt_0_in_0)));
                    ///////////////////

                    zcor = zcor_out;
                }
                {
                    double zcor_0_in = zcor;
                    double zqsmix_0_in_0 = zqsmix[((_for_it_26 + (klon * (_for_it_23 - 1))) - 1)];
                    double zdqsmixdt_out_0;

                    ///////////////////
                    // Tasklet code (T_l598_c598)
                    zdqsmixdt_out_0 = ((zfac * zcor_0_in) * zqsmix_0_in_0);
                    ///////////////////

                    zdqsmixdt[(_for_it_26 - 1)] = zdqsmixdt_out_0;
                }
                {
                    double ztp1_0_in_0 = ztp1[((_for_it_26 + (klon * (_for_it_23 - 1))) - 1)];
                    double oka_out;

                    ///////////////////
                    // Tasklet code (T_l599_c599)
                    oka_out = ztp1_0_in_0;
                    ///////////////////

                    oka = oka_out;
                }
                {
                    double ptare_var_2_0_in = oka;
                    double ydthf_var_3_0_in_rtwat = v_ydthf_var_3_rtwat[0];
                    double tmp_call_106_out;

                    ///////////////////
                    // Tasklet code (T_l1368_c1368)
                    tmp_call_106_out = min(ydthf_var_3_0_in_rtwat, ptare_var_2_0_in);
                    ///////////////////

                    tmp_call_106_1_7 = tmp_call_106_out;
                }
                {
                    double tmp_call_106_0_in = tmp_call_106_1_7;
                    double ydthf_var_3_0_in_rtice = v_ydthf_var_3_rtice[0];
                    double tmp_call_105_out;

                    ///////////////////
                    // Tasklet code (T_l1368_c1368)
                    tmp_call_105_out = max(ydthf_var_3_0_in_rtice, tmp_call_106_0_in);
                    ///////////////////

                    tmp_call_105_1_7 = tmp_call_105_out;
                }

            }
            {
                double tmp_call_104_1_7;
                double tmp_arg_66_1_7;

                {
                    double tmp_call_105_0_in = tmp_call_105_1_7;
                    double ydthf_var_3_0_in_rtice = v_ydthf_var_3_rtice[0];
                    double ydthf_var_3_1_in_rtwat_rtice_r = v_ydthf_var_3_rtwat_rtice_r[0];
                    double tmp_arg_66_out;

                    ///////////////////
                    // Tasklet code (T_l1368_c1368)
                    tmp_arg_66_out = ((tmp_call_105_0_in - ydthf_var_3_0_in_rtice) * ydthf_var_3_1_in_rtwat_rtice_r);
                    ///////////////////

                    tmp_arg_66_1_7 = tmp_arg_66_out;
                }
                {
                    double tmp_arg_66_0_in = tmp_arg_66_1_7;
                    double tmp_call_104_out;

                    ///////////////////
                    // Tasklet code (T_l1368_c1368)
                    tmp_call_104_out = (dace::math::ipow(tmp_arg_66_0_in, 2));
                    ///////////////////

                    tmp_call_104_1_7 = tmp_call_104_out;
                }
                {
                    double tmp_call_104_0_in = tmp_call_104_1_7;
                    double foealfa__ret_out;

                    ///////////////////
                    // Tasklet code (T_l1368_c1368)
                    foealfa__ret_out = min(1.0, tmp_call_104_0_in);
                    ///////////////////

                    tmp_call_116_2 = foealfa__ret_out;
                }

            }
            {
                double tmp_call_106_0_7;

                {
                    double ptare_var_2_0_in = oka;
                    double ydthf_var_3_0_in_rtwat = v_ydthf_var_3_rtwat[0];
                    double tmp_call_106_out;

                    ///////////////////
                    // Tasklet code (T_l1368_c1368)
                    tmp_call_106_out = min(ydthf_var_3_0_in_rtwat, ptare_var_2_0_in);
                    ///////////////////

                    tmp_call_106_0_7 = tmp_call_106_out;
                }
                {
                    double tmp_call_106_0_in = tmp_call_106_0_7;
                    double ydthf_var_3_0_in_rtice = v_ydthf_var_3_rtice[0];
                    double tmp_call_105_out;

                    ///////////////////
                    // Tasklet code (T_l1368_c1368)
                    tmp_call_105_out = max(ydthf_var_3_0_in_rtice, tmp_call_106_0_in);
                    ///////////////////

                    tmp_call_105_0_7 = tmp_call_105_out;
                }

            }
            {
                double *zcorqsmix;
                zcorqsmix = new double DACE_ALIGN(64)[klon];
                double tmp_call_13;
                double tmp_call_14;
                double tmp_call_17;
                double tmp_arg_5;
                double tmp_call_115_2;
                double tmp_call_104_0_7;
                double tmp_arg_66_0_7;

                {
                    double tmp_call_105_0_in = tmp_call_105_0_7;
                    double ydthf_var_3_0_in_rtice = v_ydthf_var_3_rtice[0];
                    double ydthf_var_3_1_in_rtwat_rtice_r = v_ydthf_var_3_rtwat_rtice_r[0];
                    double tmp_arg_66_out;

                    ///////////////////
                    // Tasklet code (T_l1368_c1368)
                    tmp_arg_66_out = ((tmp_call_105_0_in - ydthf_var_3_0_in_rtice) * ydthf_var_3_1_in_rtwat_rtice_r);
                    ///////////////////

                    tmp_arg_66_0_7 = tmp_arg_66_out;
                }
                {
                    double tmp_arg_66_0_in = tmp_arg_66_0_7;
                    double tmp_call_104_out;

                    ///////////////////
                    // Tasklet code (T_l1368_c1368)
                    tmp_call_104_out = (dace::math::ipow(tmp_arg_66_0_in, 2));
                    ///////////////////

                    tmp_call_104_0_7 = tmp_call_104_out;
                }
                {
                    double tmp_call_104_0_in = tmp_call_104_0_7;
                    double foealfa__ret_out;

                    ///////////////////
                    // Tasklet code (T_l1368_c1368)
                    foealfa__ret_out = min(1.0, tmp_call_104_0_in);
                    ///////////////////

                    tmp_call_115_2 = foealfa__ret_out;
                }
                {
                    double tmp_call_115_0_in = tmp_call_115_2;
                    double tmp_call_116_0_in = tmp_call_116_2;
                    double ydthf_var_10_0_in_ralvdcp = v_ydthf_var_10_ralvdcp[0];
                    double ydthf_var_10_1_in_ralsdcp = v_ydthf_var_10_ralsdcp[0];
                    double foeldcpm__ret_out;

                    ///////////////////
                    // Tasklet code (T_l1391_c1391)
                    foeldcpm__ret_out = ((tmp_call_115_0_in * ydthf_var_10_0_in_ralvdcp) + ((1.0 - tmp_call_116_0_in) * ydthf_var_10_1_in_ralsdcp));
                    ///////////////////

                    tmp_call_13 = foeldcpm__ret_out;
                }
                {
                    double tmp_call_13_0_in = tmp_call_13;
                    double zdqsmixdt_0_in_0 = zdqsmixdt[(_for_it_26 - 1)];
                    double zcorqsmix_out_0;

                    ///////////////////
                    // Tasklet code (T_l600_c600)
                    zcorqsmix_out_0 = (1.0 + (tmp_call_13_0_in * zdqsmixdt_0_in_0));
                    ///////////////////

                    zcorqsmix[(_for_it_26 - 1)] = zcorqsmix_out_0;
                }
                {
                    double zcorqsmix_0_in_0 = zcorqsmix[(_for_it_26 - 1)];
                    double zqsmix_0_in_0 = zqsmix[((_for_it_26 + (klon * (_for_it_23 - 1))) - 1)];
                    double zqx_0_in_0 = zqx[(((_for_it_26 + ((4 * klev) * klon)) + (klon * (_for_it_23 - 1))) - 1)];
                    double tmp_arg_5_out;

                    ///////////////////
                    // Tasklet code (T_l601_c601)
                    tmp_arg_5_out = ((zqsmix_0_in_0 - zqx_0_in_0) / zcorqsmix_0_in_0);
                    ///////////////////

                    tmp_arg_5 = tmp_arg_5_out;
                }
                {
                    double tmp_arg_5_0_in = tmp_arg_5;
                    double tmp_call_14_out;

                    ///////////////////
                    // Tasklet code (T_l601_c601)
                    tmp_call_14_out = max(tmp_arg_5_0_in, 0.0);
                    ///////////////////

                    tmp_call_14 = tmp_call_14_out;
                }
                {
                    double tmp_call_14_0_in = tmp_call_14;
                    double zevaplimmix_out_0;

                    ///////////////////
                    // Tasklet code (T_l601_c601)
                    zevaplimmix_out_0 = tmp_call_14_0_in;
                    ///////////////////

                    zevaplimmix[(_for_it_26 - 1)] = zevaplimmix_out_0;
                }
                {
                    double za_0_in_0 = za[((_for_it_26 + (klon * (_for_it_23 - 1))) - 1)];
                    double zepsec_0_in = zepsec;
                    double tmp_call_17_out;

                    ///////////////////
                    // Tasklet code (T_l604_c604)
                    tmp_call_17_out = max(za_0_in_0, zepsec_0_in);
                    ///////////////////

                    tmp_call_17 = tmp_call_17_out;
                }
                {
                    double tmp_call_17_0_in = tmp_call_17;
                    double ztmpa_out;

                    ///////////////////
                    // Tasklet code (T_l604_c604)
                    ztmpa_out = (1.0 / tmp_call_17_0_in);
                    ///////////////////

                    ztmpa = ztmpa_out;
                }
                {
                    double zqx_0_in_0 = zqx[((_for_it_26 + (klon * (_for_it_23 - 1))) - 1)];
                    double ztmpa_0_in = ztmpa;
                    double zliqcld_out_0;

                    ///////////////////
                    // Tasklet code (T_l605_c605)
                    zliqcld_out_0 = (zqx_0_in_0 * ztmpa_0_in);
                    ///////////////////

                    zliqcld[(_for_it_26 - 1)] = zliqcld_out_0;
                }
                {
                    double zqx_0_in_0 = zqx[(((_for_it_26 + (klev * klon)) + (klon * (_for_it_23 - 1))) - 1)];
                    double ztmpa_0_in = ztmpa;
                    double zicecld_out_0;

                    ///////////////////
                    // Tasklet code (T_l606_c606)
                    zicecld_out_0 = (zqx_0_in_0 * ztmpa_0_in);
                    ///////////////////

                    zicecld[(_for_it_26 - 1)] = zicecld_out_0;
                }
                {
                    double zicecld_0_in_0 = zicecld[(_for_it_26 - 1)];
                    double zliqcld_0_in_0 = zliqcld[(_for_it_26 - 1)];
                    double zlicld_out_0;

                    ///////////////////
                    // Tasklet code (T_l607_c607)
                    zlicld_out_0 = (zliqcld_0_in_0 + zicecld_0_in_0);
                    ///////////////////

                    zlicld[(_for_it_26 - 1)] = zlicld_out_0;
                }
                delete[] zcorqsmix;

            }

        }
        for (_for_it_27 = 1; (_for_it_27 <= kfdia); _for_it_27 = (_for_it_27 + 1)) {
            {

                {
                    double ydecldp_0_in_rlmin = v_ydecldp_rlmin[0];
                    double zqx_0_in_0 = zqx[((_for_it_27 + (klon * (_for_it_23 - 1))) - 1)];
                    double _if_cond_8_out;

                    ///////////////////
                    // Tasklet code (T_l0_c0)
                    _if_cond_8_out = (zqx_0_in_0 < ydecldp_0_in_rlmin);
                    ///////////////////

                    _if_cond_8 = _if_cond_8_out;
                }

            }
            if ((_if_cond_8 == 1)) {
                {

                    {
                        double zqx_0_in_0 = zqx[((_for_it_27 + (klon * (_for_it_23 - 1))) - 1)];
                        double zsolqa_out_0;

                        ///////////////////
                        // Tasklet code (T_l611_c611)
                        zsolqa_out_0 = zqx_0_in_0;
                        ///////////////////

                        zsolqa[((_for_it_27 + (4 * klon)) - 1)] = zsolqa_out_0;
                    }
                    {
                        double zqx_0_in_0 = zqx[((_for_it_27 + (klon * (_for_it_23 - 1))) - 1)];
                        double zsolqa_out_0;

                        ///////////////////
                        // Tasklet code (T_l612_c612)
                        zsolqa_out_0 = (- zqx_0_in_0);
                        ///////////////////

                        zsolqa[((_for_it_27 + (20 * klon)) - 1)] = zsolqa_out_0;
                    }

                }
            }
            {

                {
                    double ydecldp_0_in_rlmin = v_ydecldp_rlmin[0];
                    double zqx_0_in_0 = zqx[(((_for_it_27 + (klev * klon)) + (klon * (_for_it_23 - 1))) - 1)];
                    double _if_cond_9_out;

                    ///////////////////
                    // Tasklet code (T_l0_c0)
                    _if_cond_9_out = (zqx_0_in_0 < ydecldp_0_in_rlmin);
                    ///////////////////

                    _if_cond_9 = _if_cond_9_out;
                }

            }
            if ((_if_cond_9 == 1)) {
                {

                    {
                        double zqx_0_in_0 = zqx[(((_for_it_27 + (klev * klon)) + (klon * (_for_it_23 - 1))) - 1)];
                        double zsolqa_out_0;

                        ///////////////////
                        // Tasklet code (T_l615_c615)
                        zsolqa_out_0 = zqx_0_in_0;
                        ///////////////////

                        zsolqa[((_for_it_27 + (9 * klon)) - 1)] = zsolqa_out_0;
                    }
                    {
                        double zqx_0_in_0 = zqx[(((_for_it_27 + (klev * klon)) + (klon * (_for_it_23 - 1))) - 1)];
                        double zsolqa_out_0;

                        ///////////////////
                        // Tasklet code (T_l616_c616)
                        zsolqa_out_0 = (- zqx_0_in_0);
                        ///////////////////

                        zsolqa[((_for_it_27 + (21 * klon)) - 1)] = zsolqa_out_0;
                    }

                }
            }

        }
        for (_for_it_28 = 1; (_for_it_28 <= kfdia); _for_it_28 = (_for_it_28 + 1)) {
            {
                double tmp_call_18;
                double* v_ydthf_var_18_rkoop1;
                v_ydthf_var_18_rkoop1 = (double*)(&((*ydthf_var_18_0)->rkoop1));
                double* v_ydthf_var_18_rkoop2;
                v_ydthf_var_18_rkoop2 = (double*)(&((*ydthf_var_18_0)->rkoop2));
                double tmp_call_120_0;
                double tmp_call_119_0;
                double tmp_arg_73_0;
                double tmp_arg_74_0;
                double tmp_call_117_0_0;
                double tmp_arg_71_0_0;
                double tmp_call_118_0_0;
                double tmp_arg_72_0_0;

                {
                    double ztp1_0_in_0 = ztp1[((_for_it_28 + (klon * (_for_it_23 - 1))) - 1)];
                    double oka_out;

                    ///////////////////
                    // Tasklet code (T_l620_c620)
                    oka_out = ztp1_0_in_0;
                    ///////////////////

                    oka = oka_out;
                }
                {
                    double ptare_var_17_0_in = oka;
                    double ydthf_var_18_0_in_rkoop1 = v_ydthf_var_18_rkoop1[0];
                    double ydthf_var_18_1_in_rkoop2 = v_ydthf_var_18_rkoop2[0];
                    double tmp_arg_73_out;

                    ///////////////////
                    // Tasklet code (T_l1418_c1418)
                    tmp_arg_73_out = (ydthf_var_18_0_in_rkoop1 - (ydthf_var_18_1_in_rkoop2 * ptare_var_17_0_in));
                    ///////////////////

                    tmp_arg_73_0 = tmp_arg_73_out;
                }
                {
                    double ptare_var_14_0_in = oka;
                    double ptare_var_14_1_in = oka;
                    double ydcst_var_16_0_in_rtt = v_ydcst_var_16_rtt[0];
                    double ydthf_var_15_0_in_r3ies = v_ydthf_var_15_r3ies[0];
                    double ydthf_var_15_1_in_r4ies = v_ydthf_var_15_r4ies[0];
                    double tmp_arg_72_out;

                    ///////////////////
                    // Tasklet code (T_l1409_c1409)
                    tmp_arg_72_out = ((ydthf_var_15_0_in_r3ies * (ptare_var_14_0_in - ydcst_var_16_0_in_rtt)) / (ptare_var_14_1_in - ydthf_var_15_1_in_r4ies));
                    ///////////////////

                    tmp_arg_72_0_0 = tmp_arg_72_out;
                }
                {
                    double tmp_arg_72_0_in = tmp_arg_72_0_0;
                    double tmp_call_118_out;

                    ///////////////////
                    // Tasklet code (T_l1409_c1409)
                    tmp_call_118_out = exp(tmp_arg_72_0_in);
                    ///////////////////

                    tmp_call_118_0_0 = tmp_call_118_out;
                }
                {
                    double tmp_call_118_0_in = tmp_call_118_0_0;
                    double ydthf_var_15_0_in_r2es = v_ydthf_var_15_r2es[0];
                    double foeeice__ret_out;

                    ///////////////////
                    // Tasklet code (T_l1409_c1409)
                    foeeice__ret_out = (ydthf_var_15_0_in_r2es * tmp_call_118_0_in);
                    ///////////////////

                    tmp_call_120_0 = foeeice__ret_out;
                }
                {
                    double ptare_var_11_0_in = oka;
                    double ptare_var_11_1_in = oka;
                    double ydcst_var_13_0_in_rtt = v_ydcst_var_13_rtt[0];
                    double ydthf_var_12_0_in_r3les = v_ydthf_var_12_r3les[0];
                    double ydthf_var_12_1_in_r4les = v_ydthf_var_12_r4les[0];
                    double tmp_arg_71_out;

                    ///////////////////
                    // Tasklet code (T_l1400_c1400)
                    tmp_arg_71_out = ((ydthf_var_12_0_in_r3les * (ptare_var_11_0_in - ydcst_var_13_0_in_rtt)) / (ptare_var_11_1_in - ydthf_var_12_1_in_r4les));
                    ///////////////////

                    tmp_arg_71_0_0 = tmp_arg_71_out;
                }
                {
                    double tmp_arg_71_0_in = tmp_arg_71_0_0;
                    double tmp_call_117_out;

                    ///////////////////
                    // Tasklet code (T_l1400_c1400)
                    tmp_call_117_out = exp(tmp_arg_71_0_in);
                    ///////////////////

                    tmp_call_117_0_0 = tmp_call_117_out;
                }
                {
                    double tmp_call_117_0_in = tmp_call_117_0_0;
                    double ydthf_var_12_0_in_r2es = v_ydthf_var_12_r2es[0];
                    double foeeliq__ret_out;

                    ///////////////////
                    // Tasklet code (T_l1400_c1400)
                    foeeliq__ret_out = (ydthf_var_12_0_in_r2es * tmp_call_117_0_in);
                    ///////////////////

                    tmp_call_119_0 = foeeliq__ret_out;
                }
                {
                    double tmp_call_119_0_in = tmp_call_119_0;
                    double tmp_call_120_0_in = tmp_call_120_0;
                    double tmp_arg_74_out;

                    ///////////////////
                    // Tasklet code (T_l1418_c1418)
                    tmp_arg_74_out = (tmp_call_119_0_in / tmp_call_120_0_in);
                    ///////////////////

                    tmp_arg_74_0 = tmp_arg_74_out;
                }
                {
                    double tmp_arg_73_0_in = tmp_arg_73_0;
                    double tmp_arg_74_0_in = tmp_arg_74_0;
                    double fokoop__ret_out;

                    ///////////////////
                    // Tasklet code (T_l1418_c1418)
                    fokoop__ret_out = min(tmp_arg_73_0_in, tmp_arg_74_0_in);
                    ///////////////////

                    tmp_call_18 = fokoop__ret_out;
                }
                {
                    double tmp_call_18_0_in = tmp_call_18;
                    double zfokoop_out_0;

                    ///////////////////
                    // Tasklet code (T_l621_c621)
                    zfokoop_out_0 = tmp_call_18_0_in;
                    ///////////////////

                    zfokoop[(_for_it_28 - 1)] = zfokoop_out_0;
                }

            }

        }
        for (_for_it_29 = 1; (_for_it_29 <= kfdia); _for_it_29 = (_for_it_29 + 1)) {
            {

                {
                    double ydcst_0_in_rtt = v_ydcst_rtt[0];
                    int ydecldp_0_in_nssopt = v_ydecldp_nssopt[0];
                    double ztp1_0_in_0 = ztp1[((_for_it_29 + (klon * (_for_it_23 - 1))) - 1)];
                    double _if_cond_10_out;

                    ///////////////////
                    // Tasklet code (T_l0_c0)
                    _if_cond_10_out = ((ztp1_0_in_0 >= ydcst_0_in_rtt) || (ydecldp_0_in_nssopt == 0));
                    ///////////////////

                    _if_cond_10 = _if_cond_10_out;
                }

            }
            if ((_if_cond_10 == 1)) {

                zfac = 1.0;
                {

                    {
                        double zfaci_out;

                        ///////////////////
                        // Tasklet code (T_l626_c626)
                        zfaci_out = 1.0;
                        ///////////////////

                        zfaci = zfaci_out;
                    }

                }
            } else {

                zfac = (za[((_for_it_29 + (klon * (_for_it_23 - 1))) - 1)] + (zfokoop[(_for_it_29 - 1)] * (1.0 - za[((_for_it_29 + (klon * (_for_it_23 - 1))) - 1)])));
                {
                    double* v_ydecldp_rkooptau;
                    v_ydecldp_rkooptau = (double*)(&(ydecldp->rkooptau));

                    {
                        double ptsphy_0_in = ptsphy;
                        double ydecldp_0_in_rkooptau = v_ydecldp_rkooptau[0];
                        double zfaci_out;

                        ///////////////////
                        // Tasklet code (T_l629_c629)
                        zfaci_out = (ptsphy_0_in / ydecldp_0_in_rkooptau);
                        ///////////////////

                        zfaci = zfaci_out;
                    }

                }
            }
            {

                {
                    double ydecldp_0_in_ramin = v_ydecldp_ramin[0];
                    double za_0_in_0 = za[((_for_it_29 + (klon * (_for_it_23 - 1))) - 1)];
                    double _if_cond_11_out;

                    ///////////////////
                    // Tasklet code (T_l0_c0)
                    _if_cond_11_out = (za_0_in_0 > (1.0 - ydecldp_0_in_ramin));
                    ///////////////////

                    _if_cond_11 = _if_cond_11_out;
                }

            }
            if ((_if_cond_11 == 1)) {
                {
                    double tmp_call_19;
                    double tmp_arg_8;

                    {
                        double zcorqsice_0_in_0 = zcorqsice[(_for_it_29 - 1)];
                        double zqsice_0_in_0 = zqsice[((_for_it_29 + (klon * (_for_it_23 - 1))) - 1)];
                        double zqx_0_in_0 = zqx[(((_for_it_29 + ((4 * klev) * klon)) + (klon * (_for_it_23 - 1))) - 1)];
                        double tmp_arg_8_out;

                        ///////////////////
                        // Tasklet code (T_l632_c632)
                        tmp_arg_8_out = ((zqx_0_in_0 - (zfac * zqsice_0_in_0)) / zcorqsice_0_in_0);
                        ///////////////////

                        tmp_arg_8 = tmp_arg_8_out;
                    }
                    {
                        double tmp_arg_8_0_in = tmp_arg_8;
                        double tmp_call_19_out;

                        ///////////////////
                        // Tasklet code (T_l632_c632)
                        tmp_call_19_out = max(tmp_arg_8_0_in, 0.0);
                        ///////////////////

                        tmp_call_19 = tmp_call_19_out;
                    }
                    {
                        double tmp_call_19_0_in = tmp_call_19;
                        double zsupsat_out_0;

                        ///////////////////
                        // Tasklet code (T_l632_c632)
                        zsupsat_out_0 = tmp_call_19_0_in;
                        ///////////////////

                        zsupsat[(_for_it_29 - 1)] = zsupsat_out_0;
                    }

                }
            } else {
                {
                    double zqp1env;
                    double tmp_call_20;
                    double tmp_call_21;
                    double tmp_arg_9;
                    double tmp_arg_10;

                    {
                        double za_0_in_0 = za[((_for_it_29 + (klon * (_for_it_23 - 1))) - 1)];
                        double tmp_arg_9_out;

                        ///////////////////
                        // Tasklet code (T_l634_c634)
                        tmp_arg_9_out = (1.0 - za_0_in_0);
                        ///////////////////

                        tmp_arg_9 = tmp_arg_9_out;
                    }
                    {
                        double tmp_arg_9_0_in = tmp_arg_9;
                        double zepsilon_0_in = zepsilon;
                        double tmp_call_20_out;

                        ///////////////////
                        // Tasklet code (T_l634_c634)
                        tmp_call_20_out = max(tmp_arg_9_0_in, zepsilon_0_in);
                        ///////////////////

                        tmp_call_20 = tmp_call_20_out;
                    }
                    {
                        double tmp_call_20_0_in = tmp_call_20;
                        double za_0_in_0 = za[((_for_it_29 + (klon * (_for_it_23 - 1))) - 1)];
                        double zqsice_0_in_0 = zqsice[((_for_it_29 + (klon * (_for_it_23 - 1))) - 1)];
                        double zqx_0_in_0 = zqx[(((_for_it_29 + ((4 * klev) * klon)) + (klon * (_for_it_23 - 1))) - 1)];
                        double zqp1env_out;

                        ///////////////////
                        // Tasklet code (T_l634_c634)
                        zqp1env_out = ((zqx_0_in_0 - (za_0_in_0 * zqsice_0_in_0)) / tmp_call_20_0_in);
                        ///////////////////

                        zqp1env = zqp1env_out;
                    }
                    {
                        double za_0_in_0 = za[((_for_it_29 + (klon * (_for_it_23 - 1))) - 1)];
                        double zcorqsice_0_in_0 = zcorqsice[(_for_it_29 - 1)];
                        double zqp1env_0_in = zqp1env;
                        double zqsice_0_in_0 = zqsice[((_for_it_29 + (klon * (_for_it_23 - 1))) - 1)];
                        double tmp_arg_10_out;

                        ///////////////////
                        // Tasklet code (T_l635_c635)
                        tmp_arg_10_out = (((1.0 - za_0_in_0) * (zqp1env_0_in - (zfac * zqsice_0_in_0))) / zcorqsice_0_in_0);
                        ///////////////////

                        tmp_arg_10 = tmp_arg_10_out;
                    }
                    {
                        double tmp_arg_10_0_in = tmp_arg_10;
                        double tmp_call_21_out;

                        ///////////////////
                        // Tasklet code (T_l635_c635)
                        tmp_call_21_out = max(tmp_arg_10_0_in, 0.0);
                        ///////////////////

                        tmp_call_21 = tmp_call_21_out;
                    }
                    {
                        double tmp_call_21_0_in = tmp_call_21;
                        double zsupsat_out_0;

                        ///////////////////
                        // Tasklet code (T_l635_c635)
                        zsupsat_out_0 = tmp_call_21_0_in;
                        ///////////////////

                        zsupsat[(_for_it_29 - 1)] = zsupsat_out_0;
                    }

                }
            }
            _if_cond_12 = (zsupsat[(_for_it_29 - 1)] > 1e-14);
            if ((_if_cond_12 == 1)) {
                {

                    {
                        double ydecldp_0_in_rthomo = v_ydecldp_rthomo[0];
                        double ztp1_0_in_0 = ztp1[((_for_it_29 + (klon * (_for_it_23 - 1))) - 1)];
                        double _if_cond_13_out;

                        ///////////////////
                        // Tasklet code (T_l0_c0)
                        _if_cond_13_out = (ztp1_0_in_0 > ydecldp_0_in_rthomo);
                        ///////////////////

                        _if_cond_13 = _if_cond_13_out;
                    }

                }
                if ((_if_cond_13 == 1)) {
                    {

                        {
                            double zsolqa_0_in_0 = zsolqa[((_for_it_29 + (20 * klon)) - 1)];
                            double zsupsat_0_in_0 = zsupsat[(_for_it_29 - 1)];
                            double zsolqa_out_0;

                            ///////////////////
                            // Tasklet code (T_l639_c639)
                            zsolqa_out_0 = (zsolqa_0_in_0 + zsupsat_0_in_0);
                            ///////////////////

                            zsolqa[((_for_it_29 + (20 * klon)) - 1)] = zsolqa_out_0;
                        }
                        {
                            double zsolqa_0_in_0 = zsolqa[((_for_it_29 + (4 * klon)) - 1)];
                            double zsupsat_0_in_0 = zsupsat[(_for_it_29 - 1)];
                            double zsolqa_out_0;

                            ///////////////////
                            // Tasklet code (T_l640_c640)
                            zsolqa_out_0 = (zsolqa_0_in_0 - zsupsat_0_in_0);
                            ///////////////////

                            zsolqa[((_for_it_29 + (4 * klon)) - 1)] = zsolqa_out_0;
                        }
                        {
                            double zqxfg_0_in_0 = zqxfg[(_for_it_29 - 1)];
                            double zsupsat_0_in_0 = zsupsat[(_for_it_29 - 1)];
                            double zqxfg_out_0;

                            ///////////////////
                            // Tasklet code (T_l641_c641)
                            zqxfg_out_0 = (zqxfg_0_in_0 + zsupsat_0_in_0);
                            ///////////////////

                            zqxfg[(_for_it_29 - 1)] = zqxfg_out_0;
                        }

                    }
                } else {
                    {

                        {
                            double zsolqa_0_in_0 = zsolqa[((_for_it_29 + (21 * klon)) - 1)];
                            double zsupsat_0_in_0 = zsupsat[(_for_it_29 - 1)];
                            double zsolqa_out_0;

                            ///////////////////
                            // Tasklet code (T_l643_c643)
                            zsolqa_out_0 = (zsolqa_0_in_0 + zsupsat_0_in_0);
                            ///////////////////

                            zsolqa[((_for_it_29 + (21 * klon)) - 1)] = zsolqa_out_0;
                        }
                        {
                            double zsolqa_0_in_0 = zsolqa[((_for_it_29 + (9 * klon)) - 1)];
                            double zsupsat_0_in_0 = zsupsat[(_for_it_29 - 1)];
                            double zsolqa_out_0;

                            ///////////////////
                            // Tasklet code (T_l644_c644)
                            zsolqa_out_0 = (zsolqa_0_in_0 - zsupsat_0_in_0);
                            ///////////////////

                            zsolqa[((_for_it_29 + (9 * klon)) - 1)] = zsolqa_out_0;
                        }
                        {
                            double zqxfg_0_in_0 = zqxfg[((_for_it_29 + klon) - 1)];
                            double zsupsat_0_in_0 = zsupsat[(_for_it_29 - 1)];
                            double zqxfg_out_0;

                            ///////////////////
                            // Tasklet code (T_l645_c645)
                            zqxfg_out_0 = (zqxfg_0_in_0 + zsupsat_0_in_0);
                            ///////////////////

                            zqxfg[((_for_it_29 + klon) - 1)] = zqxfg_out_0;
                        }

                    }
                }
                {

                    {
                        double za_0_in_0 = za[((_for_it_29 + (klon * (_for_it_23 - 1))) - 1)];
                        double zfaci_0_in = zfaci;
                        double zsolac_out_0;

                        ///////////////////
                        // Tasklet code (T_l647_c647)
                        zsolac_out_0 = ((1.0 - za_0_in_0) * zfaci_0_in);
                        ///////////////////

                        zsolac[(_for_it_29 - 1)] = zsolac_out_0;
                    }

                }
            }
            _if_cond_14 = (psupsat[((_for_it_29 + (klon * (_for_it_23 - 1))) - 1)] > 1e-14);
            if ((_if_cond_14 == 1)) {
                {

                    {
                        double ydecldp_0_in_rthomo = v_ydecldp_rthomo[0];
                        double ztp1_0_in_0 = ztp1[((_for_it_29 + (klon * (_for_it_23 - 1))) - 1)];
                        double _if_cond_15_out;

                        ///////////////////
                        // Tasklet code (T_l0_c0)
                        _if_cond_15_out = (ztp1_0_in_0 > ydecldp_0_in_rthomo);
                        ///////////////////

                        _if_cond_15 = _if_cond_15_out;
                    }

                }
                if ((_if_cond_15 == 1)) {
                    {

                        {
                            double psupsat_0_in_0 = psupsat[((_for_it_29 + (klon * (_for_it_23 - 1))) - 1)];
                            double zsolqa_0_in_0 = zsolqa[(_for_it_29 - 1)];
                            double zsolqa_out_0;

                            ///////////////////
                            // Tasklet code (T_l651_c651)
                            zsolqa_out_0 = (zsolqa_0_in_0 + psupsat_0_in_0);
                            ///////////////////

                            zsolqa[(_for_it_29 - 1)] = zsolqa_out_0;
                        }
                        {
                            double psupsat_0_in_0 = psupsat[((_for_it_29 + (klon * (_for_it_23 - 1))) - 1)];
                            double zpsupsatsrce_out_0;

                            ///////////////////
                            // Tasklet code (T_l652_c652)
                            zpsupsatsrce_out_0 = psupsat_0_in_0;
                            ///////////////////

                            zpsupsatsrce[(_for_it_29 - 1)] = zpsupsatsrce_out_0;
                        }
                        {
                            double psupsat_0_in_0 = psupsat[((_for_it_29 + (klon * (_for_it_23 - 1))) - 1)];
                            double zqxfg_0_in_0 = zqxfg[(_for_it_29 - 1)];
                            double zqxfg_out_0;

                            ///////////////////
                            // Tasklet code (T_l653_c653)
                            zqxfg_out_0 = (zqxfg_0_in_0 + psupsat_0_in_0);
                            ///////////////////

                            zqxfg[(_for_it_29 - 1)] = zqxfg_out_0;
                        }

                    }
                } else {
                    {

                        {
                            double psupsat_0_in_0 = psupsat[((_for_it_29 + (klon * (_for_it_23 - 1))) - 1)];
                            double zsolqa_0_in_0 = zsolqa[((_for_it_29 + (6 * klon)) - 1)];
                            double zsolqa_out_0;

                            ///////////////////
                            // Tasklet code (T_l655_c655)
                            zsolqa_out_0 = (zsolqa_0_in_0 + psupsat_0_in_0);
                            ///////////////////

                            zsolqa[((_for_it_29 + (6 * klon)) - 1)] = zsolqa_out_0;
                        }
                        {
                            double psupsat_0_in_0 = psupsat[((_for_it_29 + (klon * (_for_it_23 - 1))) - 1)];
                            double zpsupsatsrce_out_0;

                            ///////////////////
                            // Tasklet code (T_l656_c656)
                            zpsupsatsrce_out_0 = psupsat_0_in_0;
                            ///////////////////

                            zpsupsatsrce[((_for_it_29 + klon) - 1)] = zpsupsatsrce_out_0;
                        }
                        {
                            double psupsat_0_in_0 = psupsat[((_for_it_29 + (klon * (_for_it_23 - 1))) - 1)];
                            double zqxfg_0_in_0 = zqxfg[((_for_it_29 + klon) - 1)];
                            double zqxfg_out_0;

                            ///////////////////
                            // Tasklet code (T_l657_c657)
                            zqxfg_out_0 = (zqxfg_0_in_0 + psupsat_0_in_0);
                            ///////////////////

                            zqxfg[((_for_it_29 + klon) - 1)] = zqxfg_out_0;
                        }

                    }
                }
                {

                    {
                        double za_0_in_0 = za[((_for_it_29 + (klon * (_for_it_23 - 1))) - 1)];
                        double zfaci_0_in = zfaci;
                        double zsolac_out_0;

                        ///////////////////
                        // Tasklet code (T_l659_c659)
                        zsolac_out_0 = ((1.0 - za_0_in_0) * zfaci_0_in);
                        ///////////////////

                        zsolac[(_for_it_29 - 1)] = zsolac_out_0;
                    }

                }
            }

        }
        {

            {
                int ydecldp_0_in_ncldtop = v_ydecldp_ncldtop[0];
                int _if_cond_16_out;

                ///////////////////
                // Tasklet code (T_l0_c0)
                _if_cond_16_out = ((_for_it_23 < klev) && (_for_it_23 >= ydecldp_0_in_ncldtop));
                ///////////////////

                _if_cond_16 = _if_cond_16_out;
            }

        }
        if ((_if_cond_16 == 1)) {
            for (_for_it_30 = 1; (_for_it_30 <= kfdia); _for_it_30 = (_for_it_30 + 1)) {
                {

                    {
                        double plude_0_in_0 = plude[((_for_it_30 + (klon * (_for_it_23 - 1))) - 1)];
                        double zdtgdp_0_in_0 = zdtgdp[(_for_it_30 - 1)];
                        double plude_out_0;

                        ///////////////////
                        // Tasklet code (T_l664_c664)
                        plude_out_0 = (plude_0_in_0 * zdtgdp_0_in_0);
                        ///////////////////

                        plude[((_for_it_30 + (klon * (_for_it_23 - 1))) - 1)] = plude_out_0;
                    }
                    {
                        int ldcum_0_in_0 = ldcum[(_for_it_30 - 1)];
                        double plu_0_in_0 = plu[(((_for_it_23 * klon) + _for_it_30) - 1)];
                        double plude_0_in_0 = plude[((_for_it_30 + (klon * (_for_it_23 - 1))) - 1)];
                        double ydecldp_0_in_rlmin = v_ydecldp_rlmin[0];
                        double _if_cond_17_out;

                        ///////////////////
                        // Tasklet code (T_l0_c0)
                        _if_cond_17_out = ((ldcum_0_in_0 && (plude_0_in_0 > ydecldp_0_in_rlmin)) && (plu_0_in_0 > 1e-14));
                        ///////////////////

                        _if_cond_17 = _if_cond_17_out;
                    }

                }
                if ((_if_cond_17 == 1)) {

                    zalfaw = zfoealfa[((_for_it_30 + (klon * (_for_it_23 - 1))) - 1)];
                    {

                        {
                            double plu_0_in_0 = plu[(((_for_it_23 * klon) + _for_it_30) - 1)];
                            double plude_0_in_0 = plude[((_for_it_30 + (klon * (_for_it_23 - 1))) - 1)];
                            double zsolac_0_in_0 = zsolac[(_for_it_30 - 1)];
                            double zsolac_out_0;

                            ///////////////////
                            // Tasklet code (T_l666_c666)
                            zsolac_out_0 = (zsolac_0_in_0 + (plude_0_in_0 / plu_0_in_0));
                            ///////////////////

                            zsolac[(_for_it_30 - 1)] = zsolac_out_0;
                        }
                        {
                            double plude_0_in_0 = plude[((_for_it_30 + (klon * (_for_it_23 - 1))) - 1)];
                            double zconvsrce_out_0;

                            ///////////////////
                            // Tasklet code (T_l668_c668)
                            zconvsrce_out_0 = (zalfaw * plude_0_in_0);
                            ///////////////////

                            zconvsrce[(_for_it_30 - 1)] = zconvsrce_out_0;
                        }
                        {
                            double plude_0_in_0 = plude[((_for_it_30 + (klon * (_for_it_23 - 1))) - 1)];
                            double zconvsrce_out_0;

                            ///////////////////
                            // Tasklet code (T_l669_c669)
                            zconvsrce_out_0 = ((1.0 - zalfaw) * plude_0_in_0);
                            ///////////////////

                            zconvsrce[((_for_it_30 + klon) - 1)] = zconvsrce_out_0;
                        }
                        {
                            double zconvsrce_0_in_0 = zconvsrce[(_for_it_30 - 1)];
                            double zsolqa_0_in_0 = zsolqa[(_for_it_30 - 1)];
                            double zsolqa_out_0;

                            ///////////////////
                            // Tasklet code (T_l670_c670)
                            zsolqa_out_0 = (zsolqa_0_in_0 + zconvsrce_0_in_0);
                            ///////////////////

                            zsolqa[(_for_it_30 - 1)] = zsolqa_out_0;
                        }
                        {
                            double zconvsrce_0_in_0 = zconvsrce[((_for_it_30 + klon) - 1)];
                            double zsolqa_0_in_0 = zsolqa[((_for_it_30 + (6 * klon)) - 1)];
                            double zsolqa_out_0;

                            ///////////////////
                            // Tasklet code (T_l671_c671)
                            zsolqa_out_0 = (zsolqa_0_in_0 + zconvsrce_0_in_0);
                            ///////////////////

                            zsolqa[((_for_it_30 + (6 * klon)) - 1)] = zsolqa_out_0;
                        }

                    }
                } else {
                    {

                        {
                            double plude_out_0;

                            ///////////////////
                            // Tasklet code (T_l673_c673)
                            plude_out_0 = 0.0;
                            ///////////////////

                            plude[((_for_it_30 + (klon * (_for_it_23 - 1))) - 1)] = plude_out_0;
                        }

                    }
                }
                _if_cond_18 = ldcum[(_for_it_30 - 1)];
                if ((_if_cond_18 == 1)) {
                    {

                        {
                            double psnde_0_in_0 = psnde[((_for_it_30 + (klon * (_for_it_23 - 1))) - 1)];
                            double zdtgdp_0_in_0 = zdtgdp[(_for_it_30 - 1)];
                            double zsolqa_0_in_0 = zsolqa[((_for_it_30 + (18 * klon)) - 1)];
                            double zsolqa_out_0;

                            ///////////////////
                            // Tasklet code (T_l675_c675)
                            zsolqa_out_0 = (zsolqa_0_in_0 + (psnde_0_in_0 * zdtgdp_0_in_0));
                            ///////////////////

                            zsolqa[((_for_it_30 + (18 * klon)) - 1)] = zsolqa_out_0;
                        }

                    }
                }

            }
        }
        {

            {
                int ydecldp_0_in_ncldtop = v_ydecldp_ncldtop[0];
                int _if_cond_19_out;

                ///////////////////
                // Tasklet code (T_l0_c0)
                _if_cond_19_out = (_for_it_23 > ydecldp_0_in_ncldtop);
                ///////////////////

                _if_cond_19 = _if_cond_19_out;
            }

        }
        if ((_if_cond_19 == 1)) {
            for (_for_it_31 = 1; (_for_it_31 <= kfdia); _for_it_31 = (_for_it_31 + 1)) {
                {
                    double tmp_call_22;
                    double tmp_arg_11;

                    {
                        double pmfd_0_in_0 = pmfd[((_for_it_31 + (klon * (_for_it_23 - 1))) - 1)];
                        double pmfu_0_in_0 = pmfu[((_for_it_31 + (klon * (_for_it_23 - 1))) - 1)];
                        double zdtgdp_0_in_0 = zdtgdp[(_for_it_31 - 1)];
                        double tmp_arg_11_out;

                        ///////////////////
                        // Tasklet code (T_l680_c680)
                        tmp_arg_11_out = ((pmfu_0_in_0 + pmfd_0_in_0) * zdtgdp_0_in_0);
                        ///////////////////

                        tmp_arg_11 = tmp_arg_11_out;
                    }
                    {
                        double tmp_arg_11_0_in = tmp_arg_11;
                        double tmp_call_22_out;

                        ///////////////////
                        // Tasklet code (T_l680_c680)
                        tmp_call_22_out = max(0.0, tmp_arg_11_0_in);
                        ///////////////////

                        tmp_call_22 = tmp_call_22_out;
                    }
                    {
                        double tmp_call_22_0_in = tmp_call_22;
                        double zmf_out_0;

                        ///////////////////
                        // Tasklet code (T_l680_c680)
                        zmf_out_0 = tmp_call_22_0_in;
                        ///////////////////

                        zmf[(_for_it_31 - 1)] = zmf_out_0;
                    }
                    {
                        double zanewm1_0_in_0 = zanewm1[(_for_it_31 - 1)];
                        double zmf_0_in_0 = zmf[(_for_it_31 - 1)];
                        double zacust_out_0;

                        ///////////////////
                        // Tasklet code (T_l681_c681)
                        zacust_out_0 = (zmf_0_in_0 * zanewm1_0_in_0);
                        ///////////////////

                        zacust[(_for_it_31 - 1)] = zacust_out_0;
                    }

                }

            }
            for (_for_it_32 = 1; (_for_it_32 <= 5); _for_it_32 = (_for_it_32 + 1)) {

                _if_cond_20 = ((1 - llfall[(_for_it_32 - 1)]) && (iphase[(_for_it_32 - 1)] > 0));
                if ((_if_cond_20 == 1)) {
                    for (_for_it_33 = 1; (_for_it_33 <= kfdia); _for_it_33 = (_for_it_33 + 1)) {
                        {

                            {
                                double zmf_0_in_0 = zmf[(_for_it_33 - 1)];
                                double zqxnm1_0_in_0 = zqxnm1[((_for_it_33 + (klon * (_for_it_32 - 1))) - 1)];
                                double zlcust_out_0;

                                ///////////////////
                                // Tasklet code (T_l686_c686)
                                zlcust_out_0 = (zmf_0_in_0 * zqxnm1_0_in_0);
                                ///////////////////

                                zlcust[((_for_it_33 + (klon * (_for_it_32 - 1))) - 1)] = zlcust_out_0;
                            }
                            {
                                double zconvsrce_0_in_0 = zconvsrce[((_for_it_33 + (klon * (_for_it_32 - 1))) - 1)];
                                double zlcust_0_in_0 = zlcust[((_for_it_33 + (klon * (_for_it_32 - 1))) - 1)];
                                double zconvsrce_out_0;

                                ///////////////////
                                // Tasklet code (T_l687_c687)
                                zconvsrce_out_0 = (zconvsrce_0_in_0 + zlcust_0_in_0);
                                ///////////////////

                                zconvsrce[((_for_it_33 + (klon * (_for_it_32 - 1))) - 1)] = zconvsrce_out_0;
                            }

                        }

                    }
                }

            }
            for (_for_it_34 = 1; (_for_it_34 <= kfdia); _for_it_34 = (_for_it_34 + 1)) {
                {

                    {
                        double paph_0_in_0 = paph[((_for_it_34 + (klon * (_for_it_23 - 1))) - 1)];
                        double zrdcp_0_in = zrdcp;
                        double ztp1_0_in_0 = ztp1[((_for_it_34 + (klon * (_for_it_23 - 2))) - 1)];
                        double ztp1_1_in_0 = ztp1[((_for_it_34 + (klon * (_for_it_23 - 1))) - 1)];
                        double zdtdp_out;

                        ///////////////////
                        // Tasklet code (T_l692_c692)
                        zdtdp_out = (((zrdcp_0_in * 0.5) * (ztp1_0_in_0 + ztp1_1_in_0)) / paph_0_in_0);
                        ///////////////////

                        zdtdp = zdtdp_out;
                    }
                    {
                        double pap_0_in_0 = pap[((_for_it_34 + (klon * (_for_it_23 - 1))) - 1)];
                        double pap_1_in_0 = pap[((_for_it_34 + (klon * (_for_it_23 - 2))) - 1)];
                        double zdtdp_0_in = zdtdp;
                        double zdtforc_out;

                        ///////////////////
                        // Tasklet code (T_l693_c693)
                        zdtforc_out = (zdtdp_0_in * (pap_0_in_0 - pap_1_in_0));
                        ///////////////////

                        zdtforc = zdtforc_out;
                    }
                    {
                        double zanewm1_0_in_0 = zanewm1[(_for_it_34 - 1)];
                        double zdqsmixdt_0_in_0 = zdqsmixdt[(_for_it_34 - 1)];
                        double zdtforc_0_in = zdtforc;
                        double zdqs_out_0;

                        ///////////////////
                        // Tasklet code (T_l694_c694)
                        zdqs_out_0 = ((zanewm1_0_in_0 * zdtforc_0_in) * zdqsmixdt_0_in_0);
                        ///////////////////

                        zdqs[(_for_it_34 - 1)] = zdqs_out_0;
                    }

                }

            }
            for (_for_it_35 = 1; (_for_it_35 <= 5); _for_it_35 = (_for_it_35 + 1)) {

                _if_cond_21 = ((1 - llfall[(_for_it_35 - 1)]) && (iphase[(_for_it_35 - 1)] > 0));
                if ((_if_cond_21 == 1)) {
                    for (_for_it_36 = 1; (_for_it_36 <= kfdia); _for_it_36 = (_for_it_36 + 1)) {
                        {
                            double zlfinal;
                            double tmp_arg_12;
                            double tmp_arg_13;

                            {
                                double zdqs_0_in_0 = zdqs[(_for_it_36 - 1)];
                                double zlcust_0_in_0 = zlcust[((_for_it_36 + (klon * (_for_it_35 - 1))) - 1)];
                                double tmp_arg_12_out;

                                ///////////////////
                                // Tasklet code (T_l699_c699)
                                tmp_arg_12_out = (zlcust_0_in_0 - zdqs_0_in_0);
                                ///////////////////

                                tmp_arg_12 = tmp_arg_12_out;
                            }
                            {
                                double tmp_arg_12_0_in = tmp_arg_12;
                                double zlfinal_out;

                                ///////////////////
                                // Tasklet code (T_l699_c699)
                                zlfinal_out = max(0.0, tmp_arg_12_0_in);
                                ///////////////////

                                zlfinal = zlfinal_out;
                            }
                            {
                                double zlcust_0_in_0 = zlcust[((_for_it_36 + (klon * (_for_it_35 - 1))) - 1)];
                                double zlfinal_0_in = zlfinal;
                                double tmp_arg_13_out;

                                ///////////////////
                                // Tasklet code (T_l700_c700)
                                tmp_arg_13_out = (zlcust_0_in_0 - zlfinal_0_in);
                                ///////////////////

                                tmp_arg_13 = tmp_arg_13_out;
                            }
                            {
                                double tmp_arg_13_0_in = tmp_arg_13;
                                double zevaplimmix_0_in_0 = zevaplimmix[(_for_it_36 - 1)];
                                double zevap_out;

                                ///////////////////
                                // Tasklet code (T_l700_c700)
                                zevap_out = min(tmp_arg_13_0_in, zevaplimmix_0_in_0);
                                ///////////////////

                                zevap = zevap_out;
                            }
                            {
                                double zevap_0_in = zevap;
                                double zlcust_0_in_0 = zlcust[((_for_it_36 + (klon * (_for_it_35 - 1))) - 1)];
                                double zlfinal_out;

                                ///////////////////
                                // Tasklet code (T_l701_c701)
                                zlfinal_out = (zlcust_0_in_0 - zevap_0_in);
                                ///////////////////

                                zlfinal = zlfinal_out;
                            }
                            {
                                double zlfinal_0_in = zlfinal;
                                double zlfinalsum_0_in_0 = zlfinalsum[(_for_it_36 - 1)];
                                double zlfinalsum_out_0;

                                ///////////////////
                                // Tasklet code (T_l702_c702)
                                zlfinalsum_out_0 = (zlfinalsum_0_in_0 + zlfinal_0_in);
                                ///////////////////

                                zlfinalsum[(_for_it_36 - 1)] = zlfinalsum_out_0;
                            }
                            {
                                double zlcust_0_in_0 = zlcust[((_for_it_36 + (klon * (_for_it_35 - 1))) - 1)];
                                double zsolqa_0_in_0 = zsolqa[((_for_it_36 + ((6 * klon) * (_for_it_35 - 1))) - 1)];
                                double zsolqa_out_0;

                                ///////////////////
                                // Tasklet code (T_l703_c703)
                                zsolqa_out_0 = (zsolqa_0_in_0 + zlcust_0_in_0);
                                ///////////////////

                                zsolqa[((_for_it_36 + ((6 * klon) * (_for_it_35 - 1))) - 1)] = zsolqa_out_0;
                            }
                            {
                                double zevap_0_in = zevap;
                                double zsolqa_0_in_0 = zsolqa[(((_for_it_36 + ((5 * klon) * (_for_it_35 - 1))) + (4 * klon)) - 1)];
                                double zsolqa_out_0;

                                ///////////////////
                                // Tasklet code (T_l704_c704)
                                zsolqa_out_0 = (zsolqa_0_in_0 + zevap_0_in);
                                ///////////////////

                                zsolqa[(((_for_it_36 + ((5 * klon) * (_for_it_35 - 1))) + (4 * klon)) - 1)] = zsolqa_out_0;
                            }
                            {
                                double zevap_0_in = zevap;
                                double zsolqa_0_in_0 = zsolqa[(((_for_it_36 + (klon * (_for_it_35 - 1))) + (20 * klon)) - 1)];
                                double zsolqa_out_0;

                                ///////////////////
                                // Tasklet code (T_l705_c705)
                                zsolqa_out_0 = (zsolqa_0_in_0 - zevap_0_in);
                                ///////////////////

                                zsolqa[(((_for_it_36 + (klon * (_for_it_35 - 1))) + (20 * klon)) - 1)] = zsolqa_out_0;
                            }

                        }

                    }
                }

            }
            for (_for_it_37 = 1; (_for_it_37 <= kfdia); _for_it_37 = (_for_it_37 + 1)) {

                _if_cond_22 = (zlfinalsum[(_for_it_37 - 1)] < 1e-14);
                if ((_if_cond_22 == 1)) {
                    {

                        {
                            double zacust_out_0;

                            ///////////////////
                            // Tasklet code (T_l710_c710)
                            zacust_out_0 = 0.0;
                            ///////////////////

                            zacust[(_for_it_37 - 1)] = zacust_out_0;
                        }

                    }
                }
                {

                    {
                        double zacust_0_in_0 = zacust[(_for_it_37 - 1)];
                        double zsolac_0_in_0 = zsolac[(_for_it_37 - 1)];
                        double zsolac_out_0;

                        ///////////////////
                        // Tasklet code (T_l711_c711)
                        zsolac_out_0 = (zsolac_0_in_0 + zacust_0_in_0);
                        ///////////////////

                        zsolac[(_for_it_37 - 1)] = zsolac_out_0;
                    }

                }

            }
        }
        for (_for_it_38 = 1; (_for_it_38 <= kfdia); _for_it_38 = (_for_it_38 + 1)) {
            if (((_for_it_23 < klev) == 1)) {
                {
                    double tmp_arg_14;

                    {
                        double pmfd_0_in_0 = pmfd[(((_for_it_23 * klon) + _for_it_38) - 1)];
                        double pmfu_0_in_0 = pmfu[(((_for_it_23 * klon) + _for_it_38) - 1)];
                        double zdtgdp_0_in_0 = zdtgdp[(_for_it_38 - 1)];
                        double tmp_arg_14_out;

                        ///////////////////
                        // Tasklet code (T_l716_c716)
                        tmp_arg_14_out = ((pmfu_0_in_0 + pmfd_0_in_0) * zdtgdp_0_in_0);
                        ///////////////////

                        tmp_arg_14 = tmp_arg_14_out;
                    }
                    {
                        double tmp_arg_14_0_in = tmp_arg_14;
                        double zmfdn_out;

                        ///////////////////
                        // Tasklet code (T_l716_c716)
                        zmfdn_out = max(0.0, tmp_arg_14_0_in);
                        ///////////////////

                        zmfdn = zmfdn_out;
                    }
                    {
                        double zmfdn_0_in = zmfdn;
                        double zconvsink_out_0;

                        ///////////////////
                        // Tasklet code (T_l720_c720)
                        zconvsink_out_0 = zmfdn_0_in;
                        ///////////////////

                        zconvsink[(_for_it_38 - 1)] = zconvsink_out_0;
                    }
                    {
                        double zmfdn_0_in = zmfdn;
                        double zconvsink_out_0;

                        ///////////////////
                        // Tasklet code (T_l721_c721)
                        zconvsink_out_0 = zmfdn_0_in;
                        ///////////////////

                        zconvsink[((_for_it_38 + klon) - 1)] = zconvsink_out_0;
                    }
                    {
                        double zmfdn_0_in = zmfdn;
                        double zsolab_0_in_0 = zsolab[(_for_it_38 - 1)];
                        double zsolab_out_0;

                        ///////////////////
                        // Tasklet code (T_l717_c717)
                        zsolab_out_0 = (zsolab_0_in_0 + zmfdn_0_in);
                        ///////////////////

                        zsolab[(_for_it_38 - 1)] = zsolab_out_0;
                    }
                    {
                        double zmfdn_0_in = zmfdn;
                        double zsolqb_0_in_0 = zsolqb[(_for_it_38 - 1)];
                        double zsolqb_out_0;

                        ///////////////////
                        // Tasklet code (T_l718_c718)
                        zsolqb_out_0 = (zsolqb_0_in_0 + zmfdn_0_in);
                        ///////////////////

                        zsolqb[(_for_it_38 - 1)] = zsolqb_out_0;
                    }
                    {
                        double zmfdn_0_in = zmfdn;
                        double zsolqb_0_in_0 = zsolqb[((_for_it_38 + (6 * klon)) - 1)];
                        double zsolqb_out_0;

                        ///////////////////
                        // Tasklet code (T_l719_c719)
                        zsolqb_out_0 = (zsolqb_0_in_0 + zmfdn_0_in);
                        ///////////////////

                        zsolqb[((_for_it_38 + (6 * klon)) - 1)] = zsolqb_out_0;
                    }

                }
            }

        }
        for (_for_it_39 = 1; (_for_it_39 <= kfdia); _for_it_39 = (_for_it_39 + 1)) {

            _if_cond_24 = ((ktype[(_for_it_39 - 1)] > 0) && (plude[((_for_it_39 + (klon * (_for_it_23 - 1))) - 1)] > 1e-14));
            {
                double* v_ydecldp_rcldiff;
                v_ydecldp_rcldiff = (double*)(&(ydecldp->rcldiff));

                {
                    double ptsphy_0_in = ptsphy;
                    double ydecldp_0_in_rcldiff = v_ydecldp_rcldiff[0];
                    double zldifdt_out_0;

                    ///////////////////
                    // Tasklet code (T_l725_c725)
                    zldifdt_out_0 = (ydecldp_0_in_rcldiff * ptsphy_0_in);
                    ///////////////////

                    zldifdt[(_for_it_39 - 1)] = zldifdt_out_0;
                }

            }
            if ((_if_cond_24 == 1)) {
                {
                    double* v_ydecldp_rcldiff_convi;
                    v_ydecldp_rcldiff_convi = (double*)(&(ydecldp->rcldiff_convi));

                    {
                        double ydecldp_0_in_rcldiff_convi = v_ydecldp_rcldiff_convi[0];
                        double zldifdt_0_in_0 = zldifdt[(_for_it_39 - 1)];
                        double zldifdt_out_0;

                        ///////////////////
                        // Tasklet code (T_l726_c726)
                        zldifdt_out_0 = (ydecldp_0_in_rcldiff_convi * zldifdt_0_in_0);
                        ///////////////////

                        zldifdt[(_for_it_39 - 1)] = zldifdt_out_0;
                    }

                }
            }

        }
        for (_for_it_40 = 1; (_for_it_40 <= kfdia); _for_it_40 = (_for_it_40 + 1)) {

            _if_cond_25 = (zli[((_for_it_40 + (klon * (_for_it_23 - 1))) - 1)] > 1e-14);
            if ((_if_cond_25 == 1)) {
                {
                    double zleros;
                    double zaeros;
                    double ze;
                    double tmp_call_23;
                    double tmp_arg_15;

                    {
                        double zqsmix_0_in_0 = zqsmix[((_for_it_40 + (klon * (_for_it_23 - 1))) - 1)];
                        double zqx_0_in_0 = zqx[(((_for_it_40 + ((4 * klev) * klon)) + (klon * (_for_it_23 - 1))) - 1)];
                        double tmp_arg_15_out;

                        ///////////////////
                        // Tasklet code (T_l730_c730)
                        tmp_arg_15_out = (zqsmix_0_in_0 - zqx_0_in_0);
                        ///////////////////

                        tmp_arg_15 = tmp_arg_15_out;
                    }
                    {
                        double tmp_arg_15_0_in = tmp_arg_15;
                        double tmp_call_23_out;

                        ///////////////////
                        // Tasklet code (T_l730_c730)
                        tmp_call_23_out = max(tmp_arg_15_0_in, 0.0);
                        ///////////////////

                        tmp_call_23 = tmp_call_23_out;
                    }
                    {
                        double tmp_call_23_0_in = tmp_call_23;
                        double zldifdt_0_in_0 = zldifdt[(_for_it_40 - 1)];
                        double ze_out;

                        ///////////////////
                        // Tasklet code (T_l730_c730)
                        ze_out = (zldifdt_0_in_0 * tmp_call_23_0_in);
                        ///////////////////

                        ze = ze_out;
                    }
                    {
                        double za_0_in_0 = za[((_for_it_40 + (klon * (_for_it_23 - 1))) - 1)];
                        double ze_0_in = ze;
                        double zleros_out;

                        ///////////////////
                        // Tasklet code (T_l731_c731)
                        zleros_out = (za_0_in_0 * ze_0_in);
                        ///////////////////

                        zleros = zleros_out;
                    }
                    {
                        double zevaplimmix_0_in_0 = zevaplimmix[(_for_it_40 - 1)];
                        double zleros_0_in = zleros;
                        double zleros_out;

                        ///////////////////
                        // Tasklet code (T_l732_c732)
                        zleros_out = min(zleros_0_in, zevaplimmix_0_in_0);
                        ///////////////////

                        zleros = zleros_out;
                    }
                    {
                        double zleros_0_in = zleros;
                        double zli_0_in_0 = zli[((_for_it_40 + (klon * (_for_it_23 - 1))) - 1)];
                        double zleros_out;

                        ///////////////////
                        // Tasklet code (T_l733_c733)
                        zleros_out = min(zleros_0_in, zli_0_in_0);
                        ///////////////////

                        zleros = zleros_out;
                    }
                    {
                        double zleros_0_in = zleros;
                        double zlicld_0_in_0 = zlicld[(_for_it_40 - 1)];
                        double zaeros_out;

                        ///////////////////
                        // Tasklet code (T_l734_c734)
                        zaeros_out = (zleros_0_in / zlicld_0_in_0);
                        ///////////////////

                        zaeros = zaeros_out;
                    }
                    {
                        double zaeros_0_in = zaeros;
                        double zsolac_0_in_0 = zsolac[(_for_it_40 - 1)];
                        double zsolac_out_0;

                        ///////////////////
                        // Tasklet code (T_l735_c735)
                        zsolac_out_0 = (zsolac_0_in_0 - zaeros_0_in);
                        ///////////////////

                        zsolac[(_for_it_40 - 1)] = zsolac_out_0;
                    }
                    {
                        double zleros_0_in = zleros;
                        double zliqfrac_0_in_0 = zliqfrac[((_for_it_40 + (klon * (_for_it_23 - 1))) - 1)];
                        double zsolqa_0_in_0 = zsolqa[((_for_it_40 + (4 * klon)) - 1)];
                        double zsolqa_out_0;

                        ///////////////////
                        // Tasklet code (T_l736_c736)
                        zsolqa_out_0 = (zsolqa_0_in_0 + (zliqfrac_0_in_0 * zleros_0_in));
                        ///////////////////

                        zsolqa[((_for_it_40 + (4 * klon)) - 1)] = zsolqa_out_0;
                    }
                    {
                        double zleros_0_in = zleros;
                        double zliqfrac_0_in_0 = zliqfrac[((_for_it_40 + (klon * (_for_it_23 - 1))) - 1)];
                        double zsolqa_0_in_0 = zsolqa[((_for_it_40 + (20 * klon)) - 1)];
                        double zsolqa_out_0;

                        ///////////////////
                        // Tasklet code (T_l737_c737)
                        zsolqa_out_0 = (zsolqa_0_in_0 - (zliqfrac_0_in_0 * zleros_0_in));
                        ///////////////////

                        zsolqa[((_for_it_40 + (20 * klon)) - 1)] = zsolqa_out_0;
                    }
                    {
                        double zicefrac_0_in_0 = zicefrac[((_for_it_40 + (klon * (_for_it_23 - 1))) - 1)];
                        double zleros_0_in = zleros;
                        double zsolqa_0_in_0 = zsolqa[((_for_it_40 + (9 * klon)) - 1)];
                        double zsolqa_out_0;

                        ///////////////////
                        // Tasklet code (T_l738_c738)
                        zsolqa_out_0 = (zsolqa_0_in_0 + (zicefrac_0_in_0 * zleros_0_in));
                        ///////////////////

                        zsolqa[((_for_it_40 + (9 * klon)) - 1)] = zsolqa_out_0;
                    }
                    {
                        double zicefrac_0_in_0 = zicefrac[((_for_it_40 + (klon * (_for_it_23 - 1))) - 1)];
                        double zleros_0_in = zleros;
                        double zsolqa_0_in_0 = zsolqa[((_for_it_40 + (21 * klon)) - 1)];
                        double zsolqa_out_0;

                        ///////////////////
                        // Tasklet code (T_l739_c739)
                        zsolqa_out_0 = (zsolqa_0_in_0 - (zicefrac_0_in_0 * zleros_0_in));
                        ///////////////////

                        zsolqa[((_for_it_40 + (21 * klon)) - 1)] = zsolqa_out_0;
                    }

                }
            }

        }
        for (_for_it_41 = 1; (_for_it_41 <= kfdia); _for_it_41 = (_for_it_41 + 1)) {
            {

                {
                    double pap_0_in_0 = pap[((_for_it_41 + (klon * (_for_it_23 - 1))) - 1)];
                    double zrdcp_0_in = zrdcp;
                    double ztp1_0_in_0 = ztp1[((_for_it_41 + (klon * (_for_it_23 - 1))) - 1)];
                    double zdtdp_out;

                    ///////////////////
                    // Tasklet code (T_l743_c743)
                    zdtdp_out = ((zrdcp_0_in * ztp1_0_in_0) / pap_0_in_0);
                    ///////////////////

                    zdtdp = zdtdp_out;
                }
                {
                    double zdp_0_in_0 = zdp[(_for_it_41 - 1)];
                    double zqtmst_0_in = zqtmst;
                    double zdpmxdt_out;

                    ///////////////////
                    // Tasklet code (T_l744_c744)
                    zdpmxdt_out = (zdp_0_in_0 * zqtmst_0_in);
                    ///////////////////

                    zdpmxdt = zdpmxdt_out;
                }
                {
                    double zmfdn_out;

                    ///////////////////
                    // Tasklet code (T_l745_c745)
                    zmfdn_out = 0.0;
                    ///////////////////

                    zmfdn = zmfdn_out;
                }

            }
            if (((_for_it_23 < klev) == 1)) {
                {

                    {
                        double pmfd_0_in_0 = pmfd[(((_for_it_23 * klon) + _for_it_41) - 1)];
                        double pmfu_0_in_0 = pmfu[(((_for_it_23 * klon) + _for_it_41) - 1)];
                        double zmfdn_out;

                        ///////////////////
                        // Tasklet code (T_l746_c746)
                        zmfdn_out = (pmfu_0_in_0 + pmfd_0_in_0);
                        ///////////////////

                        zmfdn = zmfdn_out;
                    }

                }
            }
            {
                double zdtdiab;
                double zwtot;
                double zzzdt;
                double tmp_call_24;
                double tmp_call_25;
                double tmp_call_27;
                double tmp_arg_16;
                double tmp_arg_17;
                double tmp_arg_18;
                double* v_ydthf_ralfdcp;
                v_ydthf_ralfdcp = (double*)(&(ydthf->ralfdcp));

                {
                    double pmfd_0_in_0 = pmfd[((_for_it_41 + (klon * (_for_it_23 - 1))) - 1)];
                    double pmfu_0_in_0 = pmfu[((_for_it_41 + (klon * (_for_it_23 - 1))) - 1)];
                    double pvervel_0_in_0 = pvervel[((_for_it_41 + (klon * (_for_it_23 - 1))) - 1)];
                    double ydcst_0_in_rg = v_ydcst_rg[0];
                    double zmfdn_0_in = zmfdn;
                    double zwtot_out;

                    ///////////////////
                    // Tasklet code (T_l747_c747)
                    zwtot_out = (pvervel_0_in_0 + ((0.5 * ydcst_0_in_rg) * ((pmfu_0_in_0 + pmfd_0_in_0) + zmfdn_0_in)));
                    ///////////////////

                    zwtot = zwtot_out;
                }
                {
                    double zdpmxdt_0_in = zdpmxdt;
                    double tmp_arg_16_out;

                    ///////////////////
                    // Tasklet code (T_l748_c748)
                    tmp_arg_16_out = (- zdpmxdt_0_in);
                    ///////////////////

                    tmp_arg_16 = tmp_arg_16_out;
                }
                {
                    double tmp_arg_16_0_in = tmp_arg_16;
                    double zwtot_0_in = zwtot;
                    double tmp_call_24_out;

                    ///////////////////
                    // Tasklet code (T_l748_c748)
                    tmp_call_24_out = max(tmp_arg_16_0_in, zwtot_0_in);
                    ///////////////////

                    tmp_call_24 = tmp_call_24_out;
                }
                {
                    double tmp_call_24_0_in = tmp_call_24;
                    double zdpmxdt_0_in = zdpmxdt;
                    double zwtot_out;

                    ///////////////////
                    // Tasklet code (T_l748_c748)
                    zwtot_out = min(zdpmxdt_0_in, tmp_call_24_0_in);
                    ///////////////////

                    zwtot = zwtot_out;
                }
                {
                    double phrlw_0_in_0 = phrlw[((_for_it_41 + (klon * (_for_it_23 - 1))) - 1)];
                    double phrsw_0_in_0 = phrsw[((_for_it_41 + (klon * (_for_it_23 - 1))) - 1)];
                    double zzzdt_out;

                    ///////////////////
                    // Tasklet code (T_l749_c749)
                    zzzdt_out = (phrsw_0_in_0 + phrlw_0_in_0);
                    ///////////////////

                    zzzdt = zzzdt_out;
                }
                {
                    double zdpmxdt_0_in = zdpmxdt;
                    double zdtdp_0_in = zdtdp;
                    double tmp_arg_17_out;

                    ///////////////////
                    // Tasklet code (T_l750_c750)
                    tmp_arg_17_out = (- (zdpmxdt_0_in * zdtdp_0_in));
                    ///////////////////

                    tmp_arg_17 = tmp_arg_17_out;
                }
                {
                    double tmp_arg_17_0_in = tmp_arg_17;
                    double zzzdt_0_in = zzzdt;
                    double tmp_call_27_out;

                    ///////////////////
                    // Tasklet code (T_l750_c750)
                    tmp_call_27_out = max(tmp_arg_17_0_in, zzzdt_0_in);
                    ///////////////////

                    tmp_call_27 = tmp_call_27_out;
                }
                {
                    double zdpmxdt_0_in = zdpmxdt;
                    double zdtdp_0_in = zdtdp;
                    double tmp_arg_18_out;

                    ///////////////////
                    // Tasklet code (T_l750_c750)
                    tmp_arg_18_out = (zdpmxdt_0_in * zdtdp_0_in);
                    ///////////////////

                    tmp_arg_18 = tmp_arg_18_out;
                }
                {
                    double tmp_arg_18_0_in = tmp_arg_18;
                    double tmp_call_27_0_in = tmp_call_27;
                    double tmp_call_25_out;

                    ///////////////////
                    // Tasklet code (T_l750_c750)
                    tmp_call_25_out = min(tmp_arg_18_0_in, tmp_call_27_0_in);
                    ///////////////////

                    tmp_call_25 = tmp_call_25_out;
                }
                {
                    double ptsphy_0_in = ptsphy;
                    double tmp_call_25_0_in = tmp_call_25;
                    double ydthf_0_in_ralfdcp = v_ydthf_ralfdcp[0];
                    double zldefr_0_in_0 = zldefr[(_for_it_41 - 1)];
                    double zdtdiab_out;

                    ///////////////////
                    // Tasklet code (T_l750_c750)
                    zdtdiab_out = ((tmp_call_25_0_in * ptsphy_0_in) + (ydthf_0_in_ralfdcp * zldefr_0_in_0));
                    ///////////////////

                    zdtdiab = zdtdiab_out;
                }
                {
                    double ptsphy_0_in = ptsphy;
                    double zdtdiab_0_in = zdtdiab;
                    double zdtdp_0_in = zdtdp;
                    double zwtot_0_in = zwtot;
                    double zdtforc_out;

                    ///////////////////
                    // Tasklet code (T_l751_c751)
                    zdtforc_out = (((zdtdp_0_in * zwtot_0_in) * ptsphy_0_in) + zdtdiab_0_in);
                    ///////////////////

                    zdtforc = zdtforc_out;
                }
                {
                    double zqsmix_0_in_0 = zqsmix[((_for_it_41 + (klon * (_for_it_23 - 1))) - 1)];
                    double zqold_out_0;

                    ///////////////////
                    // Tasklet code (T_l752_c752)
                    zqold_out_0 = zqsmix_0_in_0;
                    ///////////////////

                    zqold[(_for_it_41 - 1)] = zqold_out_0;
                }
                {
                    double ztp1_0_in_0 = ztp1[((_for_it_41 + (klon * (_for_it_23 - 1))) - 1)];
                    double ztold_out_0;

                    ///////////////////
                    // Tasklet code (T_l753_c753)
                    ztold_out_0 = ztp1_0_in_0;
                    ///////////////////

                    ztold[(_for_it_41 - 1)] = ztold_out_0;
                }

            }
            {
                double tmp_call_26;

                {
                    double zdtforc_0_in = zdtforc;
                    double ztp1_0_in_0 = ztp1[((_for_it_41 + (klon * (_for_it_23 - 1))) - 1)];
                    double ztp1_out_0;

                    ///////////////////
                    // Tasklet code (T_l754_c754)
                    ztp1_out_0 = (ztp1_0_in_0 + zdtforc_0_in);
                    ///////////////////

                    ztp1[((_for_it_41 + (klon * (_for_it_23 - 1))) - 1)] = ztp1_out_0;
                }
                {
                    double ztp1_0_in_0 = ztp1[((_for_it_41 + (klon * (_for_it_23 - 1))) - 1)];
                    double tmp_call_26_out;

                    ///////////////////
                    // Tasklet code (T_l755_c755)
                    tmp_call_26_out = max(ztp1_0_in_0, 160.0);
                    ///////////////////

                    tmp_call_26 = tmp_call_26_out;
                }
                {
                    double tmp_call_26_0_in = tmp_call_26;
                    double ztp1_out_0;

                    ///////////////////
                    // Tasklet code (T_l755_c755)
                    ztp1_out_0 = tmp_call_26_0_in;
                    ///////////////////

                    ztp1[((_for_it_41 + (klon * (_for_it_23 - 1))) - 1)] = ztp1_out_0;
                }

            }

        }
        for (_for_it_42 = 1; (_for_it_42 <= kfdia); _for_it_42 = (_for_it_42 + 1)) {
            {
                double tmp_arg_67_1;
                double tmp_call_106_1_6;

                {
                    double pap_0_in_0 = pap[((_for_it_42 + (klon * (_for_it_23 - 1))) - 1)];
                    double zqp_out;

                    ///////////////////
                    // Tasklet code (T_l759_c759)
                    zqp_out = (1.0 / pap_0_in_0);
                    ///////////////////

                    zqp = zqp_out;
                }
                {
                    double ztp1_0_in_0 = ztp1[((_for_it_42 + (klon * (_for_it_23 - 1))) - 1)];
                    double oka_out;

                    ///////////////////
                    // Tasklet code (T_l760_c760)
                    oka_out = ztp1_0_in_0;
                    ///////////////////

                    oka = oka_out;
                }
                {
                    double ptare_var_2_0_in = oka;
                    double ydthf_var_3_0_in_rtwat = v_ydthf_var_3_rtwat[0];
                    double tmp_call_106_out;

                    ///////////////////
                    // Tasklet code (T_l1368_c1368)
                    tmp_call_106_out = min(ydthf_var_3_0_in_rtwat, ptare_var_2_0_in);
                    ///////////////////

                    tmp_call_106_1_6 = tmp_call_106_out;
                }
                {
                    double tmp_call_106_0_in = tmp_call_106_1_6;
                    double ydthf_var_3_0_in_rtice = v_ydthf_var_3_rtice[0];
                    double tmp_call_105_out;

                    ///////////////////
                    // Tasklet code (T_l1368_c1368)
                    tmp_call_105_out = max(ydthf_var_3_0_in_rtice, tmp_call_106_0_in);
                    ///////////////////

                    tmp_call_105_1_6 = tmp_call_105_out;
                }
                {
                    double ptare_var_4_0_in = oka;
                    double ptare_var_4_1_in = oka;
                    double ydcst_var_6_0_in_rtt = v_ydcst_var_6_rtt[0];
                    double ydthf_var_5_0_in_r3ies = v_ydthf_var_5_r3ies[0];
                    double ydthf_var_5_1_in_r4ies = v_ydthf_var_5_r4ies[0];
                    double tmp_arg_67_out;

                    ///////////////////
                    // Tasklet code (T_l1377_c1377)
                    tmp_arg_67_out = ((ydthf_var_5_0_in_r3ies * (ptare_var_4_0_in - ydcst_var_6_0_in_rtt)) / (ptare_var_4_1_in - ydthf_var_5_1_in_r4ies));
                    ///////////////////

                    tmp_arg_67_1 = tmp_arg_67_out;
                }
                {
                    double tmp_arg_67_0_in = tmp_arg_67_1;
                    double tmp_call_110_out;

                    ///////////////////
                    // Tasklet code (T_l1377_c1377)
                    tmp_call_110_out = exp(tmp_arg_67_0_in);
                    ///////////////////

                    tmp_call_110_1 = tmp_call_110_out;
                }

            }
            {
                double tmp_call_104_1_6;
                double tmp_arg_66_1_6;

                {
                    double tmp_call_105_0_in = tmp_call_105_1_6;
                    double ydthf_var_3_0_in_rtice = v_ydthf_var_3_rtice[0];
                    double ydthf_var_3_1_in_rtwat_rtice_r = v_ydthf_var_3_rtwat_rtice_r[0];
                    double tmp_arg_66_out;

                    ///////////////////
                    // Tasklet code (T_l1368_c1368)
                    tmp_arg_66_out = ((tmp_call_105_0_in - ydthf_var_3_0_in_rtice) * ydthf_var_3_1_in_rtwat_rtice_r);
                    ///////////////////

                    tmp_arg_66_1_6 = tmp_arg_66_out;
                }
                {
                    double tmp_arg_66_0_in = tmp_arg_66_1_6;
                    double tmp_call_104_out;

                    ///////////////////
                    // Tasklet code (T_l1368_c1368)
                    tmp_call_104_out = (dace::math::ipow(tmp_arg_66_0_in, 2));
                    ///////////////////

                    tmp_call_104_1_6 = tmp_call_104_out;
                }
                {
                    double tmp_call_104_0_in = tmp_call_104_1_6;
                    double foealfa__ret_out;

                    ///////////////////
                    // Tasklet code (T_l1368_c1368)
                    foealfa__ret_out = min(1.0, tmp_call_104_0_in);
                    ///////////////////

                    tmp_call_109_1 = foealfa__ret_out;
                }

            }
            {
                double tmp_arg_68_1;
                double tmp_call_106_0_6;

                {
                    double ptare_var_2_0_in = oka;
                    double ydthf_var_3_0_in_rtwat = v_ydthf_var_3_rtwat[0];
                    double tmp_call_106_out;

                    ///////////////////
                    // Tasklet code (T_l1368_c1368)
                    tmp_call_106_out = min(ydthf_var_3_0_in_rtwat, ptare_var_2_0_in);
                    ///////////////////

                    tmp_call_106_0_6 = tmp_call_106_out;
                }
                {
                    double tmp_call_106_0_in = tmp_call_106_0_6;
                    double ydthf_var_3_0_in_rtice = v_ydthf_var_3_rtice[0];
                    double tmp_call_105_out;

                    ///////////////////
                    // Tasklet code (T_l1368_c1368)
                    tmp_call_105_out = max(ydthf_var_3_0_in_rtice, tmp_call_106_0_in);
                    ///////////////////

                    tmp_call_105_0_6 = tmp_call_105_out;
                }
                {
                    double ptare_var_4_0_in = oka;
                    double ptare_var_4_1_in = oka;
                    double ydcst_var_6_0_in_rtt = v_ydcst_var_6_rtt[0];
                    double ydthf_var_5_0_in_r3les = v_ydthf_var_5_r3les[0];
                    double ydthf_var_5_1_in_r4les = v_ydthf_var_5_r4les[0];
                    double tmp_arg_68_out;

                    ///////////////////
                    // Tasklet code (T_l1377_c1377)
                    tmp_arg_68_out = ((ydthf_var_5_0_in_r3les * (ptare_var_4_0_in - ydcst_var_6_0_in_rtt)) / (ptare_var_4_1_in - ydthf_var_5_1_in_r4les));
                    ///////////////////

                    tmp_arg_68_1 = tmp_arg_68_out;
                }
                {
                    double tmp_arg_68_0_in = tmp_arg_68_1;
                    double tmp_call_108_out;

                    ///////////////////
                    // Tasklet code (T_l1377_c1377)
                    tmp_call_108_out = exp(tmp_arg_68_0_in);
                    ///////////////////

                    tmp_call_108_1 = tmp_call_108_out;
                }

            }
            {
                double tmp_call_107_1;
                double tmp_call_104_0_6;
                double tmp_arg_66_0_6;

                {
                    double tmp_call_105_0_in = tmp_call_105_0_6;
                    double ydthf_var_3_0_in_rtice = v_ydthf_var_3_rtice[0];
                    double ydthf_var_3_1_in_rtwat_rtice_r = v_ydthf_var_3_rtwat_rtice_r[0];
                    double tmp_arg_66_out;

                    ///////////////////
                    // Tasklet code (T_l1368_c1368)
                    tmp_arg_66_out = ((tmp_call_105_0_in - ydthf_var_3_0_in_rtice) * ydthf_var_3_1_in_rtwat_rtice_r);
                    ///////////////////

                    tmp_arg_66_0_6 = tmp_arg_66_out;
                }
                {
                    double tmp_arg_66_0_in = tmp_arg_66_0_6;
                    double tmp_call_104_out;

                    ///////////////////
                    // Tasklet code (T_l1368_c1368)
                    tmp_call_104_out = (dace::math::ipow(tmp_arg_66_0_in, 2));
                    ///////////////////

                    tmp_call_104_0_6 = tmp_call_104_out;
                }
                {
                    double tmp_call_104_0_in = tmp_call_104_0_6;
                    double foealfa__ret_out;

                    ///////////////////
                    // Tasklet code (T_l1368_c1368)
                    foealfa__ret_out = min(1.0, tmp_call_104_0_in);
                    ///////////////////

                    tmp_call_107_1 = foealfa__ret_out;
                }
                {
                    double tmp_call_107_0_in = tmp_call_107_1;
                    double tmp_call_108_0_in = tmp_call_108_1;
                    double tmp_call_109_0_in = tmp_call_109_1;
                    double tmp_call_110_0_in = tmp_call_110_1;
                    double ydthf_var_5_0_in_r2es = v_ydthf_var_5_r2es[0];
                    double foeewm__ret_out;

                    ///////////////////
                    // Tasklet code (T_l1377_c1377)
                    foeewm__ret_out = (ydthf_var_5_0_in_r2es * ((tmp_call_107_0_in * tmp_call_108_0_in) + ((1.0 - tmp_call_109_0_in) * tmp_call_110_0_in)));
                    ///////////////////

                    tmp_call_28 = foeewm__ret_out;
                }

            }
            {
                double tmp_arg_69_2;
                double tmp_call_106_1_5;

                {
                    double tmp_call_28_0_in = tmp_call_28;
                    double zqp_0_in = zqp;
                    double zqsat_out;

                    ///////////////////
                    // Tasklet code (T_l761_c761)
                    zqsat_out = (tmp_call_28_0_in * zqp_0_in);
                    ///////////////////

                    zqsat = zqsat_out;
                }
                {
                    double zqsat_0_in = zqsat;
                    double zqsat_out;

                    ///////////////////
                    // Tasklet code (T_l762_c762)
                    zqsat_out = min(0.5, zqsat_0_in);
                    ///////////////////

                    zqsat = zqsat_out;
                }
                {
                    double ydcst_0_in_retv = v_ydcst_retv[0];
                    double zqsat_0_in = zqsat;
                    double zcor_out;

                    ///////////////////
                    // Tasklet code (T_l763_c763)
                    zcor_out = (1.0 / (1.0 - (ydcst_0_in_retv * zqsat_0_in)));
                    ///////////////////

                    zcor = zcor_out;
                }
                {
                    double zcor_0_in = zcor;
                    double zqsat_0_in = zqsat;
                    double zqsat_out;

                    ///////////////////
                    // Tasklet code (T_l764_c764)
                    zqsat_out = (zqsat_0_in * zcor_0_in);
                    ///////////////////

                    zqsat = zqsat_out;
                }
                {
                    double ztp1_0_in_0 = ztp1[((_for_it_42 + (klon * (_for_it_23 - 1))) - 1)];
                    double oka_out;

                    ///////////////////
                    // Tasklet code (T_l765_c765)
                    oka_out = ztp1_0_in_0;
                    ///////////////////

                    oka = oka_out;
                }
                {
                    double ptare_var_7_0_in = oka;
                    double ydthf_var_8_0_in_r4ies = v_ydthf_var_8_r4ies[0];
                    double tmp_arg_69_out;

                    ///////////////////
                    // Tasklet code (T_l1384_c1384)
                    tmp_arg_69_out = (ptare_var_7_0_in - ydthf_var_8_0_in_r4ies);
                    ///////////////////

                    tmp_arg_69_2 = tmp_arg_69_out;
                }
                {
                    double tmp_arg_69_0_in = tmp_arg_69_2;
                    double tmp_call_114_out;

                    ///////////////////
                    // Tasklet code (T_l1384_c1384)
                    tmp_call_114_out = (dace::math::ipow(tmp_arg_69_0_in, 2));
                    ///////////////////

                    tmp_call_114_2 = tmp_call_114_out;
                }
                {
                    double ptare_var_2_0_in = oka;
                    double ydthf_var_3_0_in_rtwat = v_ydthf_var_3_rtwat[0];
                    double tmp_call_106_out;

                    ///////////////////
                    // Tasklet code (T_l1368_c1368)
                    tmp_call_106_out = min(ydthf_var_3_0_in_rtwat, ptare_var_2_0_in);
                    ///////////////////

                    tmp_call_106_1_5 = tmp_call_106_out;
                }
                {
                    double tmp_call_106_0_in = tmp_call_106_1_5;
                    double ydthf_var_3_0_in_rtice = v_ydthf_var_3_rtice[0];
                    double tmp_call_105_out;

                    ///////////////////
                    // Tasklet code (T_l1368_c1368)
                    tmp_call_105_out = max(ydthf_var_3_0_in_rtice, tmp_call_106_0_in);
                    ///////////////////

                    tmp_call_105_1_5 = tmp_call_105_out;
                }

            }
            {
                double tmp_call_104_1_5;
                double tmp_arg_66_1_5;

                {
                    double tmp_call_105_0_in = tmp_call_105_1_5;
                    double ydthf_var_3_0_in_rtice = v_ydthf_var_3_rtice[0];
                    double ydthf_var_3_1_in_rtwat_rtice_r = v_ydthf_var_3_rtwat_rtice_r[0];
                    double tmp_arg_66_out;

                    ///////////////////
                    // Tasklet code (T_l1368_c1368)
                    tmp_arg_66_out = ((tmp_call_105_0_in - ydthf_var_3_0_in_rtice) * ydthf_var_3_1_in_rtwat_rtice_r);
                    ///////////////////

                    tmp_arg_66_1_5 = tmp_arg_66_out;
                }
                {
                    double tmp_arg_66_0_in = tmp_arg_66_1_5;
                    double tmp_call_104_out;

                    ///////////////////
                    // Tasklet code (T_l1368_c1368)
                    tmp_call_104_out = (dace::math::ipow(tmp_arg_66_0_in, 2));
                    ///////////////////

                    tmp_call_104_1_5 = tmp_call_104_out;
                }
                {
                    double tmp_call_104_0_in = tmp_call_104_1_5;
                    double foealfa__ret_out;

                    ///////////////////
                    // Tasklet code (T_l1368_c1368)
                    foealfa__ret_out = min(1.0, tmp_call_104_0_in);
                    ///////////////////

                    tmp_call_113_2 = foealfa__ret_out;
                }

            }
            {
                double tmp_arg_70_2;
                double tmp_call_106_0_5;

                {
                    double ptare_var_7_0_in = oka;
                    double ydthf_var_8_0_in_r4les = v_ydthf_var_8_r4les[0];
                    double tmp_arg_70_out;

                    ///////////////////
                    // Tasklet code (T_l1384_c1384)
                    tmp_arg_70_out = (ptare_var_7_0_in - ydthf_var_8_0_in_r4les);
                    ///////////////////

                    tmp_arg_70_2 = tmp_arg_70_out;
                }
                {
                    double tmp_arg_70_0_in = tmp_arg_70_2;
                    double tmp_call_112_out;

                    ///////////////////
                    // Tasklet code (T_l1384_c1384)
                    tmp_call_112_out = (dace::math::ipow(tmp_arg_70_0_in, 2));
                    ///////////////////

                    tmp_call_112_2 = tmp_call_112_out;
                }
                {
                    double ptare_var_2_0_in = oka;
                    double ydthf_var_3_0_in_rtwat = v_ydthf_var_3_rtwat[0];
                    double tmp_call_106_out;

                    ///////////////////
                    // Tasklet code (T_l1368_c1368)
                    tmp_call_106_out = min(ydthf_var_3_0_in_rtwat, ptare_var_2_0_in);
                    ///////////////////

                    tmp_call_106_0_5 = tmp_call_106_out;
                }
                {
                    double tmp_call_106_0_in = tmp_call_106_0_5;
                    double ydthf_var_3_0_in_rtice = v_ydthf_var_3_rtice[0];
                    double tmp_call_105_out;

                    ///////////////////
                    // Tasklet code (T_l1368_c1368)
                    tmp_call_105_out = max(ydthf_var_3_0_in_rtice, tmp_call_106_0_in);
                    ///////////////////

                    tmp_call_105_0_5 = tmp_call_105_out;
                }

            }
            {
                double tmp_call_111_2;
                double tmp_call_104_0_5;
                double tmp_arg_66_0_5;

                {
                    double tmp_call_105_0_in = tmp_call_105_0_5;
                    double ydthf_var_3_0_in_rtice = v_ydthf_var_3_rtice[0];
                    double ydthf_var_3_1_in_rtwat_rtice_r = v_ydthf_var_3_rtwat_rtice_r[0];
                    double tmp_arg_66_out;

                    ///////////////////
                    // Tasklet code (T_l1368_c1368)
                    tmp_arg_66_out = ((tmp_call_105_0_in - ydthf_var_3_0_in_rtice) * ydthf_var_3_1_in_rtwat_rtice_r);
                    ///////////////////

                    tmp_arg_66_0_5 = tmp_arg_66_out;
                }
                {
                    double tmp_arg_66_0_in = tmp_arg_66_0_5;
                    double tmp_call_104_out;

                    ///////////////////
                    // Tasklet code (T_l1368_c1368)
                    tmp_call_104_out = (dace::math::ipow(tmp_arg_66_0_in, 2));
                    ///////////////////

                    tmp_call_104_0_5 = tmp_call_104_out;
                }
                {
                    double tmp_call_104_0_in = tmp_call_104_0_5;
                    double foealfa__ret_out;

                    ///////////////////
                    // Tasklet code (T_l1368_c1368)
                    foealfa__ret_out = min(1.0, tmp_call_104_0_in);
                    ///////////////////

                    tmp_call_111_2 = foealfa__ret_out;
                }
                {
                    double tmp_call_111_0_in = tmp_call_111_2;
                    double tmp_call_112_0_in = tmp_call_112_2;
                    double tmp_call_113_0_in = tmp_call_113_2;
                    double tmp_call_114_0_in = tmp_call_114_2;
                    double ydthf_var_8_0_in_r5alvcp = v_ydthf_var_8_r5alvcp[0];
                    double ydthf_var_8_1_in_r5alscp = v_ydthf_var_8_r5alscp[0];
                    double foedem__ret_out;

                    ///////////////////
                    // Tasklet code (T_l1384_c1384)
                    foedem__ret_out = (((tmp_call_111_0_in * ydthf_var_8_0_in_r5alvcp) * (1.0 / tmp_call_112_0_in)) + (((1.0 - tmp_call_113_0_in) * ydthf_var_8_1_in_r5alscp) * (1.0 / tmp_call_114_0_in)));
                    ///////////////////

                    tmp_call_29 = foedem__ret_out;
                }

            }
            {
                double tmp_call_106_1_4;

                {
                    double tmp_call_29_0_in = tmp_call_29;
                    double zcor_0_in = zcor;
                    double zqsat_0_in = zqsat;
                    double zqsat_1_in = zqsat;
                    double zqsmix_0_in_0 = zqsmix[((_for_it_42 + (klon * (_for_it_23 - 1))) - 1)];
                    double zcond_out;

                    ///////////////////
                    // Tasklet code (T_l766_c766)
                    zcond_out = ((zqsmix_0_in_0 - zqsat_0_in) / (1.0 + ((zqsat_1_in * zcor_0_in) * tmp_call_29_0_in)));
                    ///////////////////

                    zcond = zcond_out;
                }
                {
                    double ztp1_0_in_0 = ztp1[((_for_it_42 + (klon * (_for_it_23 - 1))) - 1)];
                    double oka_out;

                    ///////////////////
                    // Tasklet code (T_l767_c767)
                    oka_out = ztp1_0_in_0;
                    ///////////////////

                    oka = oka_out;
                }
                {
                    double ptare_var_2_0_in = oka;
                    double ydthf_var_3_0_in_rtwat = v_ydthf_var_3_rtwat[0];
                    double tmp_call_106_out;

                    ///////////////////
                    // Tasklet code (T_l1368_c1368)
                    tmp_call_106_out = min(ydthf_var_3_0_in_rtwat, ptare_var_2_0_in);
                    ///////////////////

                    tmp_call_106_1_4 = tmp_call_106_out;
                }
                {
                    double tmp_call_106_0_in = tmp_call_106_1_4;
                    double ydthf_var_3_0_in_rtice = v_ydthf_var_3_rtice[0];
                    double tmp_call_105_out;

                    ///////////////////
                    // Tasklet code (T_l1368_c1368)
                    tmp_call_105_out = max(ydthf_var_3_0_in_rtice, tmp_call_106_0_in);
                    ///////////////////

                    tmp_call_105_1_4 = tmp_call_105_out;
                }

            }
            {
                double tmp_call_104_1_4;
                double tmp_arg_66_1_4;

                {
                    double tmp_call_105_0_in = tmp_call_105_1_4;
                    double ydthf_var_3_0_in_rtice = v_ydthf_var_3_rtice[0];
                    double ydthf_var_3_1_in_rtwat_rtice_r = v_ydthf_var_3_rtwat_rtice_r[0];
                    double tmp_arg_66_out;

                    ///////////////////
                    // Tasklet code (T_l1368_c1368)
                    tmp_arg_66_out = ((tmp_call_105_0_in - ydthf_var_3_0_in_rtice) * ydthf_var_3_1_in_rtwat_rtice_r);
                    ///////////////////

                    tmp_arg_66_1_4 = tmp_arg_66_out;
                }
                {
                    double tmp_arg_66_0_in = tmp_arg_66_1_4;
                    double tmp_call_104_out;

                    ///////////////////
                    // Tasklet code (T_l1368_c1368)
                    tmp_call_104_out = (dace::math::ipow(tmp_arg_66_0_in, 2));
                    ///////////////////

                    tmp_call_104_1_4 = tmp_call_104_out;
                }
                {
                    double tmp_call_104_0_in = tmp_call_104_1_4;
                    double foealfa__ret_out;

                    ///////////////////
                    // Tasklet code (T_l1368_c1368)
                    foealfa__ret_out = min(1.0, tmp_call_104_0_in);
                    ///////////////////

                    tmp_call_116_1 = foealfa__ret_out;
                }

            }
            {
                double tmp_call_106_0_4;

                {
                    double ptare_var_2_0_in = oka;
                    double ydthf_var_3_0_in_rtwat = v_ydthf_var_3_rtwat[0];
                    double tmp_call_106_out;

                    ///////////////////
                    // Tasklet code (T_l1368_c1368)
                    tmp_call_106_out = min(ydthf_var_3_0_in_rtwat, ptare_var_2_0_in);
                    ///////////////////

                    tmp_call_106_0_4 = tmp_call_106_out;
                }
                {
                    double tmp_call_106_0_in = tmp_call_106_0_4;
                    double ydthf_var_3_0_in_rtice = v_ydthf_var_3_rtice[0];
                    double tmp_call_105_out;

                    ///////////////////
                    // Tasklet code (T_l1368_c1368)
                    tmp_call_105_out = max(ydthf_var_3_0_in_rtice, tmp_call_106_0_in);
                    ///////////////////

                    tmp_call_105_0_4 = tmp_call_105_out;
                }

            }
            {
                double tmp_call_115_1;
                double tmp_call_104_0_4;
                double tmp_arg_66_0_4;

                {
                    double tmp_call_105_0_in = tmp_call_105_0_4;
                    double ydthf_var_3_0_in_rtice = v_ydthf_var_3_rtice[0];
                    double ydthf_var_3_1_in_rtwat_rtice_r = v_ydthf_var_3_rtwat_rtice_r[0];
                    double tmp_arg_66_out;

                    ///////////////////
                    // Tasklet code (T_l1368_c1368)
                    tmp_arg_66_out = ((tmp_call_105_0_in - ydthf_var_3_0_in_rtice) * ydthf_var_3_1_in_rtwat_rtice_r);
                    ///////////////////

                    tmp_arg_66_0_4 = tmp_arg_66_out;
                }
                {
                    double tmp_arg_66_0_in = tmp_arg_66_0_4;
                    double tmp_call_104_out;

                    ///////////////////
                    // Tasklet code (T_l1368_c1368)
                    tmp_call_104_out = (dace::math::ipow(tmp_arg_66_0_in, 2));
                    ///////////////////

                    tmp_call_104_0_4 = tmp_call_104_out;
                }
                {
                    double tmp_call_104_0_in = tmp_call_104_0_4;
                    double foealfa__ret_out;

                    ///////////////////
                    // Tasklet code (T_l1368_c1368)
                    foealfa__ret_out = min(1.0, tmp_call_104_0_in);
                    ///////////////////

                    tmp_call_115_1 = foealfa__ret_out;
                }
                {
                    double tmp_call_115_0_in = tmp_call_115_1;
                    double tmp_call_116_0_in = tmp_call_116_1;
                    double ydthf_var_10_0_in_ralvdcp = v_ydthf_var_10_ralvdcp[0];
                    double ydthf_var_10_1_in_ralsdcp = v_ydthf_var_10_ralsdcp[0];
                    double foeldcpm__ret_out;

                    ///////////////////
                    // Tasklet code (T_l1391_c1391)
                    foeldcpm__ret_out = ((tmp_call_115_0_in * ydthf_var_10_0_in_ralvdcp) + ((1.0 - tmp_call_116_0_in) * ydthf_var_10_1_in_ralsdcp));
                    ///////////////////

                    tmp_call_30 = foeldcpm__ret_out;
                }

            }
            {
                double tmp_arg_67_0;
                double tmp_call_106_1_3;

                {
                    double zcond_0_in = zcond;
                    double zqsmix_0_in_0 = zqsmix[((_for_it_42 + (klon * (_for_it_23 - 1))) - 1)];
                    double zqsmix_out_0;

                    ///////////////////
                    // Tasklet code (T_l769_c769)
                    zqsmix_out_0 = (zqsmix_0_in_0 - zcond_0_in);
                    ///////////////////

                    zqsmix[((_for_it_42 + (klon * (_for_it_23 - 1))) - 1)] = zqsmix_out_0;
                }
                {
                    double tmp_call_30_0_in = tmp_call_30;
                    double zcond_0_in = zcond;
                    double ztp1_0_in_0 = ztp1[((_for_it_42 + (klon * (_for_it_23 - 1))) - 1)];
                    double ztp1_out_0;

                    ///////////////////
                    // Tasklet code (T_l768_c768)
                    ztp1_out_0 = (ztp1_0_in_0 + (tmp_call_30_0_in * zcond_0_in));
                    ///////////////////

                    ztp1[((_for_it_42 + (klon * (_for_it_23 - 1))) - 1)] = ztp1_out_0;
                }
                {
                    double ztp1_0_in_0 = ztp1[((_for_it_42 + (klon * (_for_it_23 - 1))) - 1)];
                    double oka_out;

                    ///////////////////
                    // Tasklet code (T_l770_c770)
                    oka_out = ztp1_0_in_0;
                    ///////////////////

                    oka = oka_out;
                }
                {
                    double ptare_var_2_0_in = oka;
                    double ydthf_var_3_0_in_rtwat = v_ydthf_var_3_rtwat[0];
                    double tmp_call_106_out;

                    ///////////////////
                    // Tasklet code (T_l1368_c1368)
                    tmp_call_106_out = min(ydthf_var_3_0_in_rtwat, ptare_var_2_0_in);
                    ///////////////////

                    tmp_call_106_1_3 = tmp_call_106_out;
                }
                {
                    double tmp_call_106_0_in = tmp_call_106_1_3;
                    double ydthf_var_3_0_in_rtice = v_ydthf_var_3_rtice[0];
                    double tmp_call_105_out;

                    ///////////////////
                    // Tasklet code (T_l1368_c1368)
                    tmp_call_105_out = max(ydthf_var_3_0_in_rtice, tmp_call_106_0_in);
                    ///////////////////

                    tmp_call_105_1_3 = tmp_call_105_out;
                }
                {
                    double ptare_var_4_0_in = oka;
                    double ptare_var_4_1_in = oka;
                    double ydcst_var_6_0_in_rtt = v_ydcst_var_6_rtt[0];
                    double ydthf_var_5_0_in_r3ies = v_ydthf_var_5_r3ies[0];
                    double ydthf_var_5_1_in_r4ies = v_ydthf_var_5_r4ies[0];
                    double tmp_arg_67_out;

                    ///////////////////
                    // Tasklet code (T_l1377_c1377)
                    tmp_arg_67_out = ((ydthf_var_5_0_in_r3ies * (ptare_var_4_0_in - ydcst_var_6_0_in_rtt)) / (ptare_var_4_1_in - ydthf_var_5_1_in_r4ies));
                    ///////////////////

                    tmp_arg_67_0 = tmp_arg_67_out;
                }
                {
                    double tmp_arg_67_0_in = tmp_arg_67_0;
                    double tmp_call_110_out;

                    ///////////////////
                    // Tasklet code (T_l1377_c1377)
                    tmp_call_110_out = exp(tmp_arg_67_0_in);
                    ///////////////////

                    tmp_call_110_0 = tmp_call_110_out;
                }

            }
            {
                double tmp_call_104_1_3;
                double tmp_arg_66_1_3;

                {
                    double tmp_call_105_0_in = tmp_call_105_1_3;
                    double ydthf_var_3_0_in_rtice = v_ydthf_var_3_rtice[0];
                    double ydthf_var_3_1_in_rtwat_rtice_r = v_ydthf_var_3_rtwat_rtice_r[0];
                    double tmp_arg_66_out;

                    ///////////////////
                    // Tasklet code (T_l1368_c1368)
                    tmp_arg_66_out = ((tmp_call_105_0_in - ydthf_var_3_0_in_rtice) * ydthf_var_3_1_in_rtwat_rtice_r);
                    ///////////////////

                    tmp_arg_66_1_3 = tmp_arg_66_out;
                }
                {
                    double tmp_arg_66_0_in = tmp_arg_66_1_3;
                    double tmp_call_104_out;

                    ///////////////////
                    // Tasklet code (T_l1368_c1368)
                    tmp_call_104_out = (dace::math::ipow(tmp_arg_66_0_in, 2));
                    ///////////////////

                    tmp_call_104_1_3 = tmp_call_104_out;
                }
                {
                    double tmp_call_104_0_in = tmp_call_104_1_3;
                    double foealfa__ret_out;

                    ///////////////////
                    // Tasklet code (T_l1368_c1368)
                    foealfa__ret_out = min(1.0, tmp_call_104_0_in);
                    ///////////////////

                    tmp_call_109_0 = foealfa__ret_out;
                }

            }
            {
                double tmp_arg_68_0;
                double tmp_call_106_0_3;

                {
                    double ptare_var_2_0_in = oka;
                    double ydthf_var_3_0_in_rtwat = v_ydthf_var_3_rtwat[0];
                    double tmp_call_106_out;

                    ///////////////////
                    // Tasklet code (T_l1368_c1368)
                    tmp_call_106_out = min(ydthf_var_3_0_in_rtwat, ptare_var_2_0_in);
                    ///////////////////

                    tmp_call_106_0_3 = tmp_call_106_out;
                }
                {
                    double tmp_call_106_0_in = tmp_call_106_0_3;
                    double ydthf_var_3_0_in_rtice = v_ydthf_var_3_rtice[0];
                    double tmp_call_105_out;

                    ///////////////////
                    // Tasklet code (T_l1368_c1368)
                    tmp_call_105_out = max(ydthf_var_3_0_in_rtice, tmp_call_106_0_in);
                    ///////////////////

                    tmp_call_105_0_3 = tmp_call_105_out;
                }
                {
                    double ptare_var_4_0_in = oka;
                    double ptare_var_4_1_in = oka;
                    double ydcst_var_6_0_in_rtt = v_ydcst_var_6_rtt[0];
                    double ydthf_var_5_0_in_r3les = v_ydthf_var_5_r3les[0];
                    double ydthf_var_5_1_in_r4les = v_ydthf_var_5_r4les[0];
                    double tmp_arg_68_out;

                    ///////////////////
                    // Tasklet code (T_l1377_c1377)
                    tmp_arg_68_out = ((ydthf_var_5_0_in_r3les * (ptare_var_4_0_in - ydcst_var_6_0_in_rtt)) / (ptare_var_4_1_in - ydthf_var_5_1_in_r4les));
                    ///////////////////

                    tmp_arg_68_0 = tmp_arg_68_out;
                }
                {
                    double tmp_arg_68_0_in = tmp_arg_68_0;
                    double tmp_call_108_out;

                    ///////////////////
                    // Tasklet code (T_l1377_c1377)
                    tmp_call_108_out = exp(tmp_arg_68_0_in);
                    ///////////////////

                    tmp_call_108_0 = tmp_call_108_out;
                }

            }
            {
                double tmp_call_107_0;
                double tmp_call_104_0_3;
                double tmp_arg_66_0_3;

                {
                    double tmp_call_105_0_in = tmp_call_105_0_3;
                    double ydthf_var_3_0_in_rtice = v_ydthf_var_3_rtice[0];
                    double ydthf_var_3_1_in_rtwat_rtice_r = v_ydthf_var_3_rtwat_rtice_r[0];
                    double tmp_arg_66_out;

                    ///////////////////
                    // Tasklet code (T_l1368_c1368)
                    tmp_arg_66_out = ((tmp_call_105_0_in - ydthf_var_3_0_in_rtice) * ydthf_var_3_1_in_rtwat_rtice_r);
                    ///////////////////

                    tmp_arg_66_0_3 = tmp_arg_66_out;
                }
                {
                    double tmp_arg_66_0_in = tmp_arg_66_0_3;
                    double tmp_call_104_out;

                    ///////////////////
                    // Tasklet code (T_l1368_c1368)
                    tmp_call_104_out = (dace::math::ipow(tmp_arg_66_0_in, 2));
                    ///////////////////

                    tmp_call_104_0_3 = tmp_call_104_out;
                }
                {
                    double tmp_call_104_0_in = tmp_call_104_0_3;
                    double foealfa__ret_out;

                    ///////////////////
                    // Tasklet code (T_l1368_c1368)
                    foealfa__ret_out = min(1.0, tmp_call_104_0_in);
                    ///////////////////

                    tmp_call_107_0 = foealfa__ret_out;
                }
                {
                    double tmp_call_107_0_in = tmp_call_107_0;
                    double tmp_call_108_0_in = tmp_call_108_0;
                    double tmp_call_109_0_in = tmp_call_109_0;
                    double tmp_call_110_0_in = tmp_call_110_0;
                    double ydthf_var_5_0_in_r2es = v_ydthf_var_5_r2es[0];
                    double foeewm__ret_out;

                    ///////////////////
                    // Tasklet code (T_l1377_c1377)
                    foeewm__ret_out = (ydthf_var_5_0_in_r2es * ((tmp_call_107_0_in * tmp_call_108_0_in) + ((1.0 - tmp_call_109_0_in) * tmp_call_110_0_in)));
                    ///////////////////

                    tmp_call_31 = foeewm__ret_out;
                }

            }
            {
                double tmp_arg_69_1;
                double tmp_call_106_1_2;

                {
                    double tmp_call_31_0_in = tmp_call_31;
                    double zqp_0_in = zqp;
                    double zqsat_out;

                    ///////////////////
                    // Tasklet code (T_l771_c771)
                    zqsat_out = (tmp_call_31_0_in * zqp_0_in);
                    ///////////////////

                    zqsat = zqsat_out;
                }
                {
                    double zqsat_0_in = zqsat;
                    double zqsat_out;

                    ///////////////////
                    // Tasklet code (T_l772_c772)
                    zqsat_out = min(0.5, zqsat_0_in);
                    ///////////////////

                    zqsat = zqsat_out;
                }
                {
                    double ydcst_0_in_retv = v_ydcst_retv[0];
                    double zqsat_0_in = zqsat;
                    double zcor_out;

                    ///////////////////
                    // Tasklet code (T_l773_c773)
                    zcor_out = (1.0 / (1.0 - (ydcst_0_in_retv * zqsat_0_in)));
                    ///////////////////

                    zcor = zcor_out;
                }
                {
                    double zcor_0_in = zcor;
                    double zqsat_0_in = zqsat;
                    double zqsat_out;

                    ///////////////////
                    // Tasklet code (T_l774_c774)
                    zqsat_out = (zqsat_0_in * zcor_0_in);
                    ///////////////////

                    zqsat = zqsat_out;
                }
                {
                    double ztp1_0_in_0 = ztp1[((_for_it_42 + (klon * (_for_it_23 - 1))) - 1)];
                    double oka_out;

                    ///////////////////
                    // Tasklet code (T_l775_c775)
                    oka_out = ztp1_0_in_0;
                    ///////////////////

                    oka = oka_out;
                }
                {
                    double ptare_var_7_0_in = oka;
                    double ydthf_var_8_0_in_r4ies = v_ydthf_var_8_r4ies[0];
                    double tmp_arg_69_out;

                    ///////////////////
                    // Tasklet code (T_l1384_c1384)
                    tmp_arg_69_out = (ptare_var_7_0_in - ydthf_var_8_0_in_r4ies);
                    ///////////////////

                    tmp_arg_69_1 = tmp_arg_69_out;
                }
                {
                    double tmp_arg_69_0_in = tmp_arg_69_1;
                    double tmp_call_114_out;

                    ///////////////////
                    // Tasklet code (T_l1384_c1384)
                    tmp_call_114_out = (dace::math::ipow(tmp_arg_69_0_in, 2));
                    ///////////////////

                    tmp_call_114_1 = tmp_call_114_out;
                }
                {
                    double ptare_var_2_0_in = oka;
                    double ydthf_var_3_0_in_rtwat = v_ydthf_var_3_rtwat[0];
                    double tmp_call_106_out;

                    ///////////////////
                    // Tasklet code (T_l1368_c1368)
                    tmp_call_106_out = min(ydthf_var_3_0_in_rtwat, ptare_var_2_0_in);
                    ///////////////////

                    tmp_call_106_1_2 = tmp_call_106_out;
                }
                {
                    double tmp_call_106_0_in = tmp_call_106_1_2;
                    double ydthf_var_3_0_in_rtice = v_ydthf_var_3_rtice[0];
                    double tmp_call_105_out;

                    ///////////////////
                    // Tasklet code (T_l1368_c1368)
                    tmp_call_105_out = max(ydthf_var_3_0_in_rtice, tmp_call_106_0_in);
                    ///////////////////

                    tmp_call_105_1_2 = tmp_call_105_out;
                }

            }
            {
                double tmp_call_104_1_2;
                double tmp_arg_66_1_2;

                {
                    double tmp_call_105_0_in = tmp_call_105_1_2;
                    double ydthf_var_3_0_in_rtice = v_ydthf_var_3_rtice[0];
                    double ydthf_var_3_1_in_rtwat_rtice_r = v_ydthf_var_3_rtwat_rtice_r[0];
                    double tmp_arg_66_out;

                    ///////////////////
                    // Tasklet code (T_l1368_c1368)
                    tmp_arg_66_out = ((tmp_call_105_0_in - ydthf_var_3_0_in_rtice) * ydthf_var_3_1_in_rtwat_rtice_r);
                    ///////////////////

                    tmp_arg_66_1_2 = tmp_arg_66_out;
                }
                {
                    double tmp_arg_66_0_in = tmp_arg_66_1_2;
                    double tmp_call_104_out;

                    ///////////////////
                    // Tasklet code (T_l1368_c1368)
                    tmp_call_104_out = (dace::math::ipow(tmp_arg_66_0_in, 2));
                    ///////////////////

                    tmp_call_104_1_2 = tmp_call_104_out;
                }
                {
                    double tmp_call_104_0_in = tmp_call_104_1_2;
                    double foealfa__ret_out;

                    ///////////////////
                    // Tasklet code (T_l1368_c1368)
                    foealfa__ret_out = min(1.0, tmp_call_104_0_in);
                    ///////////////////

                    tmp_call_113_1 = foealfa__ret_out;
                }

            }
            {
                double tmp_arg_70_1;
                double tmp_call_106_0_2;

                {
                    double ptare_var_7_0_in = oka;
                    double ydthf_var_8_0_in_r4les = v_ydthf_var_8_r4les[0];
                    double tmp_arg_70_out;

                    ///////////////////
                    // Tasklet code (T_l1384_c1384)
                    tmp_arg_70_out = (ptare_var_7_0_in - ydthf_var_8_0_in_r4les);
                    ///////////////////

                    tmp_arg_70_1 = tmp_arg_70_out;
                }
                {
                    double tmp_arg_70_0_in = tmp_arg_70_1;
                    double tmp_call_112_out;

                    ///////////////////
                    // Tasklet code (T_l1384_c1384)
                    tmp_call_112_out = (dace::math::ipow(tmp_arg_70_0_in, 2));
                    ///////////////////

                    tmp_call_112_1 = tmp_call_112_out;
                }
                {
                    double ptare_var_2_0_in = oka;
                    double ydthf_var_3_0_in_rtwat = v_ydthf_var_3_rtwat[0];
                    double tmp_call_106_out;

                    ///////////////////
                    // Tasklet code (T_l1368_c1368)
                    tmp_call_106_out = min(ydthf_var_3_0_in_rtwat, ptare_var_2_0_in);
                    ///////////////////

                    tmp_call_106_0_2 = tmp_call_106_out;
                }
                {
                    double tmp_call_106_0_in = tmp_call_106_0_2;
                    double ydthf_var_3_0_in_rtice = v_ydthf_var_3_rtice[0];
                    double tmp_call_105_out;

                    ///////////////////
                    // Tasklet code (T_l1368_c1368)
                    tmp_call_105_out = max(ydthf_var_3_0_in_rtice, tmp_call_106_0_in);
                    ///////////////////

                    tmp_call_105_0_2 = tmp_call_105_out;
                }

            }
            {
                double tmp_call_111_1;
                double tmp_call_104_0_2;
                double tmp_arg_66_0_2;

                {
                    double tmp_call_105_0_in = tmp_call_105_0_2;
                    double ydthf_var_3_0_in_rtice = v_ydthf_var_3_rtice[0];
                    double ydthf_var_3_1_in_rtwat_rtice_r = v_ydthf_var_3_rtwat_rtice_r[0];
                    double tmp_arg_66_out;

                    ///////////////////
                    // Tasklet code (T_l1368_c1368)
                    tmp_arg_66_out = ((tmp_call_105_0_in - ydthf_var_3_0_in_rtice) * ydthf_var_3_1_in_rtwat_rtice_r);
                    ///////////////////

                    tmp_arg_66_0_2 = tmp_arg_66_out;
                }
                {
                    double tmp_arg_66_0_in = tmp_arg_66_0_2;
                    double tmp_call_104_out;

                    ///////////////////
                    // Tasklet code (T_l1368_c1368)
                    tmp_call_104_out = (dace::math::ipow(tmp_arg_66_0_in, 2));
                    ///////////////////

                    tmp_call_104_0_2 = tmp_call_104_out;
                }
                {
                    double tmp_call_104_0_in = tmp_call_104_0_2;
                    double foealfa__ret_out;

                    ///////////////////
                    // Tasklet code (T_l1368_c1368)
                    foealfa__ret_out = min(1.0, tmp_call_104_0_in);
                    ///////////////////

                    tmp_call_111_1 = foealfa__ret_out;
                }
                {
                    double tmp_call_111_0_in = tmp_call_111_1;
                    double tmp_call_112_0_in = tmp_call_112_1;
                    double tmp_call_113_0_in = tmp_call_113_1;
                    double tmp_call_114_0_in = tmp_call_114_1;
                    double ydthf_var_8_0_in_r5alvcp = v_ydthf_var_8_r5alvcp[0];
                    double ydthf_var_8_1_in_r5alscp = v_ydthf_var_8_r5alscp[0];
                    double foedem__ret_out;

                    ///////////////////
                    // Tasklet code (T_l1384_c1384)
                    foedem__ret_out = (((tmp_call_111_0_in * ydthf_var_8_0_in_r5alvcp) * (1.0 / tmp_call_112_0_in)) + (((1.0 - tmp_call_113_0_in) * ydthf_var_8_1_in_r5alscp) * (1.0 / tmp_call_114_0_in)));
                    ///////////////////

                    tmp_call_32 = foedem__ret_out;
                }

            }
            {
                double tmp_call_106_1_1;

                {
                    double tmp_call_32_0_in = tmp_call_32;
                    double zcor_0_in = zcor;
                    double zqsat_0_in = zqsat;
                    double zqsat_1_in = zqsat;
                    double zqsmix_0_in_0 = zqsmix[((_for_it_42 + (klon * (_for_it_23 - 1))) - 1)];
                    double zcond1_out;

                    ///////////////////
                    // Tasklet code (T_l776_c776)
                    zcond1_out = ((zqsmix_0_in_0 - zqsat_0_in) / (1.0 + ((zqsat_1_in * zcor_0_in) * tmp_call_32_0_in)));
                    ///////////////////

                    zcond1 = zcond1_out;
                }
                {
                    double ztp1_0_in_0 = ztp1[((_for_it_42 + (klon * (_for_it_23 - 1))) - 1)];
                    double oka_out;

                    ///////////////////
                    // Tasklet code (T_l777_c777)
                    oka_out = ztp1_0_in_0;
                    ///////////////////

                    oka = oka_out;
                }
                {
                    double ptare_var_2_0_in = oka;
                    double ydthf_var_3_0_in_rtwat = v_ydthf_var_3_rtwat[0];
                    double tmp_call_106_out;

                    ///////////////////
                    // Tasklet code (T_l1368_c1368)
                    tmp_call_106_out = min(ydthf_var_3_0_in_rtwat, ptare_var_2_0_in);
                    ///////////////////

                    tmp_call_106_1_1 = tmp_call_106_out;
                }
                {
                    double tmp_call_106_0_in = tmp_call_106_1_1;
                    double ydthf_var_3_0_in_rtice = v_ydthf_var_3_rtice[0];
                    double tmp_call_105_out;

                    ///////////////////
                    // Tasklet code (T_l1368_c1368)
                    tmp_call_105_out = max(ydthf_var_3_0_in_rtice, tmp_call_106_0_in);
                    ///////////////////

                    tmp_call_105_1_1 = tmp_call_105_out;
                }

            }
            {
                double tmp_call_104_1_1;
                double tmp_arg_66_1_1;

                {
                    double tmp_call_105_0_in = tmp_call_105_1_1;
                    double ydthf_var_3_0_in_rtice = v_ydthf_var_3_rtice[0];
                    double ydthf_var_3_1_in_rtwat_rtice_r = v_ydthf_var_3_rtwat_rtice_r[0];
                    double tmp_arg_66_out;

                    ///////////////////
                    // Tasklet code (T_l1368_c1368)
                    tmp_arg_66_out = ((tmp_call_105_0_in - ydthf_var_3_0_in_rtice) * ydthf_var_3_1_in_rtwat_rtice_r);
                    ///////////////////

                    tmp_arg_66_1_1 = tmp_arg_66_out;
                }
                {
                    double tmp_arg_66_0_in = tmp_arg_66_1_1;
                    double tmp_call_104_out;

                    ///////////////////
                    // Tasklet code (T_l1368_c1368)
                    tmp_call_104_out = (dace::math::ipow(tmp_arg_66_0_in, 2));
                    ///////////////////

                    tmp_call_104_1_1 = tmp_call_104_out;
                }
                {
                    double tmp_call_104_0_in = tmp_call_104_1_1;
                    double foealfa__ret_out;

                    ///////////////////
                    // Tasklet code (T_l1368_c1368)
                    foealfa__ret_out = min(1.0, tmp_call_104_0_in);
                    ///////////////////

                    tmp_call_116_0 = foealfa__ret_out;
                }

            }
            {
                double tmp_call_106_0_1;

                {
                    double ptare_var_2_0_in = oka;
                    double ydthf_var_3_0_in_rtwat = v_ydthf_var_3_rtwat[0];
                    double tmp_call_106_out;

                    ///////////////////
                    // Tasklet code (T_l1368_c1368)
                    tmp_call_106_out = min(ydthf_var_3_0_in_rtwat, ptare_var_2_0_in);
                    ///////////////////

                    tmp_call_106_0_1 = tmp_call_106_out;
                }
                {
                    double tmp_call_106_0_in = tmp_call_106_0_1;
                    double ydthf_var_3_0_in_rtice = v_ydthf_var_3_rtice[0];
                    double tmp_call_105_out;

                    ///////////////////
                    // Tasklet code (T_l1368_c1368)
                    tmp_call_105_out = max(ydthf_var_3_0_in_rtice, tmp_call_106_0_in);
                    ///////////////////

                    tmp_call_105_0_1 = tmp_call_105_out;
                }

            }
            {
                double tmp_call_33;
                double tmp_call_115_0;
                double tmp_call_104_0_1;
                double tmp_arg_66_0_1;

                {
                    double tmp_call_105_0_in = tmp_call_105_0_1;
                    double ydthf_var_3_0_in_rtice = v_ydthf_var_3_rtice[0];
                    double ydthf_var_3_1_in_rtwat_rtice_r = v_ydthf_var_3_rtwat_rtice_r[0];
                    double tmp_arg_66_out;

                    ///////////////////
                    // Tasklet code (T_l1368_c1368)
                    tmp_arg_66_out = ((tmp_call_105_0_in - ydthf_var_3_0_in_rtice) * ydthf_var_3_1_in_rtwat_rtice_r);
                    ///////////////////

                    tmp_arg_66_0_1 = tmp_arg_66_out;
                }
                {
                    double tmp_arg_66_0_in = tmp_arg_66_0_1;
                    double tmp_call_104_out;

                    ///////////////////
                    // Tasklet code (T_l1368_c1368)
                    tmp_call_104_out = (dace::math::ipow(tmp_arg_66_0_in, 2));
                    ///////////////////

                    tmp_call_104_0_1 = tmp_call_104_out;
                }
                {
                    double tmp_call_104_0_in = tmp_call_104_0_1;
                    double foealfa__ret_out;

                    ///////////////////
                    // Tasklet code (T_l1368_c1368)
                    foealfa__ret_out = min(1.0, tmp_call_104_0_in);
                    ///////////////////

                    tmp_call_115_0 = foealfa__ret_out;
                }
                {
                    double tmp_call_115_0_in = tmp_call_115_0;
                    double tmp_call_116_0_in = tmp_call_116_0;
                    double ydthf_var_10_0_in_ralvdcp = v_ydthf_var_10_ralvdcp[0];
                    double ydthf_var_10_1_in_ralsdcp = v_ydthf_var_10_ralsdcp[0];
                    double foeldcpm__ret_out;

                    ///////////////////
                    // Tasklet code (T_l1391_c1391)
                    foeldcpm__ret_out = ((tmp_call_115_0_in * ydthf_var_10_0_in_ralvdcp) + ((1.0 - tmp_call_116_0_in) * ydthf_var_10_1_in_ralsdcp));
                    ///////////////////

                    tmp_call_33 = foeldcpm__ret_out;
                }
                {
                    double tmp_call_33_0_in = tmp_call_33;
                    double zcond1_0_in = zcond1;
                    double ztp1_0_in_0 = ztp1[((_for_it_42 + (klon * (_for_it_23 - 1))) - 1)];
                    double ztp1_out_0;

                    ///////////////////
                    // Tasklet code (T_l778_c778)
                    ztp1_out_0 = (ztp1_0_in_0 + (tmp_call_33_0_in * zcond1_0_in));
                    ///////////////////

                    ztp1[((_for_it_42 + (klon * (_for_it_23 - 1))) - 1)] = ztp1_out_0;
                }
                {
                    double zcond1_0_in = zcond1;
                    double zqsmix_0_in_0 = zqsmix[((_for_it_42 + (klon * (_for_it_23 - 1))) - 1)];
                    double zqsmix_out_0;

                    ///////////////////
                    // Tasklet code (T_l779_c779)
                    zqsmix_out_0 = (zqsmix_0_in_0 - zcond1_0_in);
                    ///////////////////

                    zqsmix[((_for_it_42 + (klon * (_for_it_23 - 1))) - 1)] = zqsmix_out_0;
                }

            }

        }
        for (_for_it_43 = 1; (_for_it_43 <= kfdia); _for_it_43 = (_for_it_43 + 1)) {
            {

                {
                    double zqold_0_in_0 = zqold[(_for_it_43 - 1)];
                    double zqsmix_0_in_0 = zqsmix[((_for_it_43 + (klon * (_for_it_23 - 1))) - 1)];
                    double zdqs_out_0;

                    ///////////////////
                    // Tasklet code (T_l782_c782)
                    zdqs_out_0 = (zqsmix_0_in_0 - zqold_0_in_0);
                    ///////////////////

                    zdqs[(_for_it_43 - 1)] = zdqs_out_0;
                }

            }
            {

                {
                    double zqold_0_in_0 = zqold[(_for_it_43 - 1)];
                    double zqsmix_out_0;

                    ///////////////////
                    // Tasklet code (T_l783_c783)
                    zqsmix_out_0 = zqold_0_in_0;
                    ///////////////////

                    zqsmix[((_for_it_43 + (klon * (_for_it_23 - 1))) - 1)] = zqsmix_out_0;
                }
                {
                    double ztold_0_in_0 = ztold[(_for_it_43 - 1)];
                    double ztp1_out_0;

                    ///////////////////
                    // Tasklet code (T_l784_c784)
                    ztp1_out_0 = ztold_0_in_0;
                    ///////////////////

                    ztp1[((_for_it_43 + (klon * (_for_it_23 - 1))) - 1)] = ztp1_out_0;
                }

            }

        }
        for (_for_it_44 = 1; (_for_it_44 <= kfdia); _for_it_44 = (_for_it_44 + 1)) {

            _if_cond_27 = (zdqs[(_for_it_44 - 1)] > 0.0);
            if ((_if_cond_27 == 1)) {
                {
                    double zlevap;
                    double tmp_call_34;
                    double tmp_call_35;
                    double tmp_arg_19;

                    {
                        double zdqs_0_in_0 = zdqs[(_for_it_44 - 1)];
                        double zlicld_0_in_0 = zlicld[(_for_it_44 - 1)];
                        double tmp_call_34_out;

                        ///////////////////
                        // Tasklet code (T_l788_c788)
                        tmp_call_34_out = min(zdqs_0_in_0, zlicld_0_in_0);
                        ///////////////////

                        tmp_call_34 = tmp_call_34_out;
                    }
                    {
                        double tmp_call_34_0_in = tmp_call_34;
                        double za_0_in_0 = za[((_for_it_44 + (klon * (_for_it_23 - 1))) - 1)];
                        double zlevap_out;

                        ///////////////////
                        // Tasklet code (T_l788_c788)
                        zlevap_out = (za_0_in_0 * tmp_call_34_0_in);
                        ///////////////////

                        zlevap = zlevap_out;
                    }
                    {
                        double zevaplimmix_0_in_0 = zevaplimmix[(_for_it_44 - 1)];
                        double zlevap_0_in = zlevap;
                        double zlevap_out;

                        ///////////////////
                        // Tasklet code (T_l789_c789)
                        zlevap_out = min(zlevap_0_in, zevaplimmix_0_in_0);
                        ///////////////////

                        zlevap = zlevap_out;
                    }
                    {
                        double zqsmix_0_in_0 = zqsmix[((_for_it_44 + (klon * (_for_it_23 - 1))) - 1)];
                        double zqx_0_in_0 = zqx[(((_for_it_44 + ((4 * klev) * klon)) + (klon * (_for_it_23 - 1))) - 1)];
                        double tmp_arg_19_out;

                        ///////////////////
                        // Tasklet code (T_l790_c790)
                        tmp_arg_19_out = (zqsmix_0_in_0 - zqx_0_in_0);
                        ///////////////////

                        tmp_arg_19 = tmp_arg_19_out;
                    }
                    {
                        double tmp_arg_19_0_in = tmp_arg_19;
                        double tmp_call_35_out;

                        ///////////////////
                        // Tasklet code (T_l790_c790)
                        tmp_call_35_out = max(tmp_arg_19_0_in, 0.0);
                        ///////////////////

                        tmp_call_35 = tmp_call_35_out;
                    }
                    {
                        double tmp_call_35_0_in = tmp_call_35;
                        double zlevap_0_in = zlevap;
                        double zlevap_out;

                        ///////////////////
                        // Tasklet code (T_l790_c790)
                        zlevap_out = min(zlevap_0_in, tmp_call_35_0_in);
                        ///////////////////

                        zlevap = zlevap_out;
                    }
                    {
                        double zlevap_0_in = zlevap;
                        double zliqfrac_0_in_0 = zliqfrac[((_for_it_44 + (klon * (_for_it_23 - 1))) - 1)];
                        double zsolqa_0_in_0 = zsolqa[((_for_it_44 + (4 * klon)) - 1)];
                        double zsolqa_out_0;

                        ///////////////////
                        // Tasklet code (T_l793_c793)
                        zsolqa_out_0 = (zsolqa_0_in_0 + (zliqfrac_0_in_0 * zlevap_0_in));
                        ///////////////////

                        zsolqa[((_for_it_44 + (4 * klon)) - 1)] = zsolqa_out_0;
                    }
                    {
                        double zlevap_0_in = zlevap;
                        double zliqfrac_0_in_0 = zliqfrac[((_for_it_44 + (klon * (_for_it_23 - 1))) - 1)];
                        double zsolqa_0_in_0 = zsolqa[((_for_it_44 + (20 * klon)) - 1)];
                        double zsolqa_out_0;

                        ///////////////////
                        // Tasklet code (T_l794_c794)
                        zsolqa_out_0 = (zsolqa_0_in_0 - (zliqfrac_0_in_0 * zlevap_0_in));
                        ///////////////////

                        zsolqa[((_for_it_44 + (20 * klon)) - 1)] = zsolqa_out_0;
                    }
                    {
                        double zicefrac_0_in_0 = zicefrac[((_for_it_44 + (klon * (_for_it_23 - 1))) - 1)];
                        double zlevap_0_in = zlevap;
                        double zsolqa_0_in_0 = zsolqa[((_for_it_44 + (9 * klon)) - 1)];
                        double zsolqa_out_0;

                        ///////////////////
                        // Tasklet code (T_l795_c795)
                        zsolqa_out_0 = (zsolqa_0_in_0 + (zicefrac_0_in_0 * zlevap_0_in));
                        ///////////////////

                        zsolqa[((_for_it_44 + (9 * klon)) - 1)] = zsolqa_out_0;
                    }
                    {
                        double zicefrac_0_in_0 = zicefrac[((_for_it_44 + (klon * (_for_it_23 - 1))) - 1)];
                        double zlevap_0_in = zlevap;
                        double zsolqa_0_in_0 = zsolqa[((_for_it_44 + (21 * klon)) - 1)];
                        double zsolqa_out_0;

                        ///////////////////
                        // Tasklet code (T_l796_c796)
                        zsolqa_out_0 = (zsolqa_0_in_0 - (zicefrac_0_in_0 * zlevap_0_in));
                        ///////////////////

                        zsolqa[((_for_it_44 + (21 * klon)) - 1)] = zsolqa_out_0;
                    }

                }
            }

        }
        for (_for_it_45 = 1; (_for_it_45 <= kfdia); _for_it_45 = (_for_it_45 + 1)) {
            {

                {
                    double ydecldp_0_in_rlmin = v_ydecldp_rlmin[0];
                    double za_0_in_0 = za[((_for_it_45 + (klon * (_for_it_23 - 1))) - 1)];
                    double zdqs_0_in_0 = zdqs[(_for_it_45 - 1)];
                    double _if_cond_28_out;

                    ///////////////////
                    // Tasklet code (T_l0_c0)
                    _if_cond_28_out = ((za_0_in_0 > 1e-14) && (zdqs_0_in_0 <= (- ydecldp_0_in_rlmin)));
                    ///////////////////

                    _if_cond_28 = _if_cond_28_out;
                }

            }
            if ((_if_cond_28 == 1)) {

                _if_cond_29 = (za[((_for_it_45 + (klon * (_for_it_23 - 1))) - 1)] > 0.99);
                {
                    double tmp_call_36;
                    double tmp_arg_20;

                    {
                        double zdqs_0_in_0 = zdqs[(_for_it_45 - 1)];
                        double tmp_arg_20_out;

                        ///////////////////
                        // Tasklet code (T_l801_c801)
                        tmp_arg_20_out = (- zdqs_0_in_0);
                        ///////////////////

                        tmp_arg_20 = tmp_arg_20_out;
                    }
                    {
                        double tmp_arg_20_0_in = tmp_arg_20;
                        double tmp_call_36_out;

                        ///////////////////
                        // Tasklet code (T_l801_c801)
                        tmp_call_36_out = max(tmp_arg_20_0_in, 0.0);
                        ///////////////////

                        tmp_call_36 = tmp_call_36_out;
                    }
                    {
                        double tmp_call_36_0_in = tmp_call_36;
                        double zlcond1_out_0;

                        ///////////////////
                        // Tasklet code (T_l801_c801)
                        zlcond1_out_0 = tmp_call_36_0_in;
                        ///////////////////

                        zlcond1[(_for_it_45 - 1)] = zlcond1_out_0;
                    }

                }
                if ((_if_cond_29 == 1)) {
                    {
                        double tmp_arg_69_0;
                        double tmp_call_106_1_0;

                        {
                            double ydcst_0_in_retv = v_ydcst_retv[0];
                            double zqsmix_0_in_0 = zqsmix[((_for_it_45 + (klon * (_for_it_23 - 1))) - 1)];
                            double zcor_out;

                            ///////////////////
                            // Tasklet code (T_l803_c803)
                            zcor_out = (1.0 / (1.0 - (ydcst_0_in_retv * zqsmix_0_in_0)));
                            ///////////////////

                            zcor = zcor_out;
                        }
                        {
                            double ztp1_0_in_0 = ztp1[((_for_it_45 + (klon * (_for_it_23 - 1))) - 1)];
                            double oka_out;

                            ///////////////////
                            // Tasklet code (T_l804_c804)
                            oka_out = ztp1_0_in_0;
                            ///////////////////

                            oka = oka_out;
                        }
                        {
                            double ptare_var_7_0_in = oka;
                            double ydthf_var_8_0_in_r4ies = v_ydthf_var_8_r4ies[0];
                            double tmp_arg_69_out;

                            ///////////////////
                            // Tasklet code (T_l1384_c1384)
                            tmp_arg_69_out = (ptare_var_7_0_in - ydthf_var_8_0_in_r4ies);
                            ///////////////////

                            tmp_arg_69_0 = tmp_arg_69_out;
                        }
                        {
                            double tmp_arg_69_0_in = tmp_arg_69_0;
                            double tmp_call_114_out;

                            ///////////////////
                            // Tasklet code (T_l1384_c1384)
                            tmp_call_114_out = (dace::math::ipow(tmp_arg_69_0_in, 2));
                            ///////////////////

                            tmp_call_114_0 = tmp_call_114_out;
                        }
                        {
                            double ptare_var_2_0_in = oka;
                            double ydthf_var_3_0_in_rtwat = v_ydthf_var_3_rtwat[0];
                            double tmp_call_106_out;

                            ///////////////////
                            // Tasklet code (T_l1368_c1368)
                            tmp_call_106_out = min(ydthf_var_3_0_in_rtwat, ptare_var_2_0_in);
                            ///////////////////

                            tmp_call_106_1_0 = tmp_call_106_out;
                        }
                        {
                            double tmp_call_106_0_in = tmp_call_106_1_0;
                            double ydthf_var_3_0_in_rtice = v_ydthf_var_3_rtice[0];
                            double tmp_call_105_out;

                            ///////////////////
                            // Tasklet code (T_l1368_c1368)
                            tmp_call_105_out = max(ydthf_var_3_0_in_rtice, tmp_call_106_0_in);
                            ///////////////////

                            tmp_call_105_1_0 = tmp_call_105_out;
                        }

                    }
                    {
                        double tmp_call_104_1_0;
                        double tmp_arg_66_1_0;

                        {
                            double tmp_call_105_0_in = tmp_call_105_1_0;
                            double ydthf_var_3_0_in_rtice = v_ydthf_var_3_rtice[0];
                            double ydthf_var_3_1_in_rtwat_rtice_r = v_ydthf_var_3_rtwat_rtice_r[0];
                            double tmp_arg_66_out;

                            ///////////////////
                            // Tasklet code (T_l1368_c1368)
                            tmp_arg_66_out = ((tmp_call_105_0_in - ydthf_var_3_0_in_rtice) * ydthf_var_3_1_in_rtwat_rtice_r);
                            ///////////////////

                            tmp_arg_66_1_0 = tmp_arg_66_out;
                        }
                        {
                            double tmp_arg_66_0_in = tmp_arg_66_1_0;
                            double tmp_call_104_out;

                            ///////////////////
                            // Tasklet code (T_l1368_c1368)
                            tmp_call_104_out = (dace::math::ipow(tmp_arg_66_0_in, 2));
                            ///////////////////

                            tmp_call_104_1_0 = tmp_call_104_out;
                        }
                        {
                            double tmp_call_104_0_in = tmp_call_104_1_0;
                            double foealfa__ret_out;

                            ///////////////////
                            // Tasklet code (T_l1368_c1368)
                            foealfa__ret_out = min(1.0, tmp_call_104_0_in);
                            ///////////////////

                            tmp_call_113_0 = foealfa__ret_out;
                        }

                    }
                    {
                        double tmp_arg_70_0;
                        double tmp_call_106_0_0;

                        {
                            double ptare_var_7_0_in = oka;
                            double ydthf_var_8_0_in_r4les = v_ydthf_var_8_r4les[0];
                            double tmp_arg_70_out;

                            ///////////////////
                            // Tasklet code (T_l1384_c1384)
                            tmp_arg_70_out = (ptare_var_7_0_in - ydthf_var_8_0_in_r4les);
                            ///////////////////

                            tmp_arg_70_0 = tmp_arg_70_out;
                        }
                        {
                            double tmp_arg_70_0_in = tmp_arg_70_0;
                            double tmp_call_112_out;

                            ///////////////////
                            // Tasklet code (T_l1384_c1384)
                            tmp_call_112_out = (dace::math::ipow(tmp_arg_70_0_in, 2));
                            ///////////////////

                            tmp_call_112_0 = tmp_call_112_out;
                        }
                        {
                            double ptare_var_2_0_in = oka;
                            double ydthf_var_3_0_in_rtwat = v_ydthf_var_3_rtwat[0];
                            double tmp_call_106_out;

                            ///////////////////
                            // Tasklet code (T_l1368_c1368)
                            tmp_call_106_out = min(ydthf_var_3_0_in_rtwat, ptare_var_2_0_in);
                            ///////////////////

                            tmp_call_106_0_0 = tmp_call_106_out;
                        }
                        {
                            double tmp_call_106_0_in = tmp_call_106_0_0;
                            double ydthf_var_3_0_in_rtice = v_ydthf_var_3_rtice[0];
                            double tmp_call_105_out;

                            ///////////////////
                            // Tasklet code (T_l1368_c1368)
                            tmp_call_105_out = max(ydthf_var_3_0_in_rtice, tmp_call_106_0_in);
                            ///////////////////

                            tmp_call_105_0_0 = tmp_call_105_out;
                        }

                    }
                    {
                        double tmp_call_37;
                        double tmp_call_111_0;
                        double tmp_call_104_0_0;
                        double tmp_arg_66_0_0;

                        {
                            double tmp_call_105_0_in = tmp_call_105_0_0;
                            double ydthf_var_3_0_in_rtice = v_ydthf_var_3_rtice[0];
                            double ydthf_var_3_1_in_rtwat_rtice_r = v_ydthf_var_3_rtwat_rtice_r[0];
                            double tmp_arg_66_out;

                            ///////////////////
                            // Tasklet code (T_l1368_c1368)
                            tmp_arg_66_out = ((tmp_call_105_0_in - ydthf_var_3_0_in_rtice) * ydthf_var_3_1_in_rtwat_rtice_r);
                            ///////////////////

                            tmp_arg_66_0_0 = tmp_arg_66_out;
                        }
                        {
                            double tmp_arg_66_0_in = tmp_arg_66_0_0;
                            double tmp_call_104_out;

                            ///////////////////
                            // Tasklet code (T_l1368_c1368)
                            tmp_call_104_out = (dace::math::ipow(tmp_arg_66_0_in, 2));
                            ///////////////////

                            tmp_call_104_0_0 = tmp_call_104_out;
                        }
                        {
                            double tmp_call_104_0_in = tmp_call_104_0_0;
                            double foealfa__ret_out;

                            ///////////////////
                            // Tasklet code (T_l1368_c1368)
                            foealfa__ret_out = min(1.0, tmp_call_104_0_in);
                            ///////////////////

                            tmp_call_111_0 = foealfa__ret_out;
                        }
                        {
                            double tmp_call_111_0_in = tmp_call_111_0;
                            double tmp_call_112_0_in = tmp_call_112_0;
                            double tmp_call_113_0_in = tmp_call_113_0;
                            double tmp_call_114_0_in = tmp_call_114_0;
                            double ydthf_var_8_0_in_r5alvcp = v_ydthf_var_8_r5alvcp[0];
                            double ydthf_var_8_1_in_r5alscp = v_ydthf_var_8_r5alscp[0];
                            double foedem__ret_out;

                            ///////////////////
                            // Tasklet code (T_l1384_c1384)
                            foedem__ret_out = (((tmp_call_111_0_in * ydthf_var_8_0_in_r5alvcp) * (1.0 / tmp_call_112_0_in)) + (((1.0 - tmp_call_113_0_in) * ydthf_var_8_1_in_r5alscp) * (1.0 / tmp_call_114_0_in)));
                            ///////////////////

                            tmp_call_37 = foedem__ret_out;
                        }
                        {
                            double tmp_call_37_0_in = tmp_call_37;
                            double zcor_0_in = zcor;
                            double zqsmix_0_in_0 = zqsmix[((_for_it_45 + (klon * (_for_it_23 - 1))) - 1)];
                            double zqsmix_1_in_0 = zqsmix[((_for_it_45 + (klon * (_for_it_23 - 1))) - 1)];
                            double zqx_0_in_0 = zqx[(((_for_it_45 + ((4 * klev) * klon)) + (klon * (_for_it_23 - 1))) - 1)];
                            double zcdmax_out;

                            ///////////////////
                            // Tasklet code (T_l805_c805)
                            zcdmax_out = ((zqx_0_in_0 - zqsmix_0_in_0) / (1.0 + ((zcor_0_in * zqsmix_1_in_0) * tmp_call_37_0_in)));
                            ///////////////////

                            zcdmax = zcdmax_out;
                        }

                    }
                } else {
                    {

                        {
                            double za_0_in_0 = za[((_for_it_45 + (klon * (_for_it_23 - 1))) - 1)];
                            double za_1_in_0 = za[((_for_it_45 + (klon * (_for_it_23 - 1))) - 1)];
                            double zqsmix_0_in_0 = zqsmix[((_for_it_45 + (klon * (_for_it_23 - 1))) - 1)];
                            double zqx_0_in_0 = zqx[(((_for_it_45 + ((4 * klev) * klon)) + (klon * (_for_it_23 - 1))) - 1)];
                            double zcdmax_out;

                            ///////////////////
                            // Tasklet code (T_l807_c807)
                            zcdmax_out = ((zqx_0_in_0 - (za_0_in_0 * zqsmix_0_in_0)) / za_1_in_0);
                            ///////////////////

                            zcdmax = zcdmax_out;
                        }

                    }
                }
                {
                    double tmp_call_38;
                    double tmp_call_39;

                    {
                        double zcdmax_0_in = zcdmax;
                        double zlcond1_0_in_0 = zlcond1[(_for_it_45 - 1)];
                        double tmp_call_39_out;

                        ///////////////////
                        // Tasklet code (T_l809_c809)
                        tmp_call_39_out = min(zlcond1_0_in_0, zcdmax_0_in);
                        ///////////////////

                        tmp_call_39 = tmp_call_39_out;
                    }
                    {
                        double tmp_call_39_0_in = tmp_call_39;
                        double tmp_call_38_out;

                        ///////////////////
                        // Tasklet code (T_l809_c809)
                        tmp_call_38_out = max(tmp_call_39_0_in, 0.0);
                        ///////////////////

                        tmp_call_38 = tmp_call_38_out;
                    }
                    {
                        double tmp_call_38_0_in = tmp_call_38;
                        double zlcond1_out_0;

                        ///////////////////
                        // Tasklet code (T_l809_c809)
                        zlcond1_out_0 = tmp_call_38_0_in;
                        ///////////////////

                        zlcond1[(_for_it_45 - 1)] = zlcond1_out_0;
                    }
                    {
                        double za_0_in_0 = za[((_for_it_45 + (klon * (_for_it_23 - 1))) - 1)];
                        double zlcond1_0_in_0 = zlcond1[(_for_it_45 - 1)];
                        double zlcond1_out_0;

                        ///////////////////
                        // Tasklet code (T_l810_c810)
                        zlcond1_out_0 = (za_0_in_0 * zlcond1_0_in_0);
                        ///////////////////

                        zlcond1[(_for_it_45 - 1)] = zlcond1_out_0;
                    }
                    {
                        double ydecldp_0_in_rlmin = v_ydecldp_rlmin[0];
                        double zlcond1_0_in_0 = zlcond1[(_for_it_45 - 1)];
                        double _if_cond_30_out;

                        ///////////////////
                        // Tasklet code (T_l811_c811)
                        _if_cond_30_out = (zlcond1_0_in_0 < ydecldp_0_in_rlmin);
                        ///////////////////

                        _if_cond_30 = _if_cond_30_out;
                    }

                }
                if ((_if_cond_30 == 1)) {
                    {

                        {
                            double zlcond1_out_0;

                            ///////////////////
                            // Tasklet code (T_l811_c811)
                            zlcond1_out_0 = 0.0;
                            ///////////////////

                            zlcond1[(_for_it_45 - 1)] = zlcond1_out_0;
                        }

                    }
                }
                {

                    {
                        double ydecldp_0_in_rthomo = v_ydecldp_rthomo[0];
                        double ztp1_0_in_0 = ztp1[((_for_it_45 + (klon * (_for_it_23 - 1))) - 1)];
                        double _if_cond_31_out;

                        ///////////////////
                        // Tasklet code (T_l0_c0)
                        _if_cond_31_out = (ztp1_0_in_0 > ydecldp_0_in_rthomo);
                        ///////////////////

                        _if_cond_31 = _if_cond_31_out;
                    }

                }
                if ((_if_cond_31 == 1)) {
                    {

                        {
                            double zlcond1_0_in_0 = zlcond1[(_for_it_45 - 1)];
                            double zsolqa_0_in_0 = zsolqa[((_for_it_45 + (20 * klon)) - 1)];
                            double zsolqa_out_0;

                            ///////////////////
                            // Tasklet code (T_l813_c813)
                            zsolqa_out_0 = (zsolqa_0_in_0 + zlcond1_0_in_0);
                            ///////////////////

                            zsolqa[((_for_it_45 + (20 * klon)) - 1)] = zsolqa_out_0;
                        }
                        {
                            double zlcond1_0_in_0 = zlcond1[(_for_it_45 - 1)];
                            double zsolqa_0_in_0 = zsolqa[((_for_it_45 + (4 * klon)) - 1)];
                            double zsolqa_out_0;

                            ///////////////////
                            // Tasklet code (T_l814_c814)
                            zsolqa_out_0 = (zsolqa_0_in_0 - zlcond1_0_in_0);
                            ///////////////////

                            zsolqa[((_for_it_45 + (4 * klon)) - 1)] = zsolqa_out_0;
                        }
                        {
                            double zlcond1_0_in_0 = zlcond1[(_for_it_45 - 1)];
                            double zqxfg_0_in_0 = zqxfg[(_for_it_45 - 1)];
                            double zqxfg_out_0;

                            ///////////////////
                            // Tasklet code (T_l815_c815)
                            zqxfg_out_0 = (zqxfg_0_in_0 + zlcond1_0_in_0);
                            ///////////////////

                            zqxfg[(_for_it_45 - 1)] = zqxfg_out_0;
                        }

                    }
                } else {
                    {

                        {
                            double zlcond1_0_in_0 = zlcond1[(_for_it_45 - 1)];
                            double zsolqa_0_in_0 = zsolqa[((_for_it_45 + (21 * klon)) - 1)];
                            double zsolqa_out_0;

                            ///////////////////
                            // Tasklet code (T_l817_c817)
                            zsolqa_out_0 = (zsolqa_0_in_0 + zlcond1_0_in_0);
                            ///////////////////

                            zsolqa[((_for_it_45 + (21 * klon)) - 1)] = zsolqa_out_0;
                        }
                        {
                            double zlcond1_0_in_0 = zlcond1[(_for_it_45 - 1)];
                            double zsolqa_0_in_0 = zsolqa[((_for_it_45 + (9 * klon)) - 1)];
                            double zsolqa_out_0;

                            ///////////////////
                            // Tasklet code (T_l818_c818)
                            zsolqa_out_0 = (zsolqa_0_in_0 - zlcond1_0_in_0);
                            ///////////////////

                            zsolqa[((_for_it_45 + (9 * klon)) - 1)] = zsolqa_out_0;
                        }
                        {
                            double zlcond1_0_in_0 = zlcond1[(_for_it_45 - 1)];
                            double zqxfg_0_in_0 = zqxfg[((_for_it_45 + klon) - 1)];
                            double zqxfg_out_0;

                            ///////////////////
                            // Tasklet code (T_l819_c819)
                            zqxfg_out_0 = (zqxfg_0_in_0 + zlcond1_0_in_0);
                            ///////////////////

                            zqxfg[((_for_it_45 + klon) - 1)] = zqxfg_out_0;
                        }

                    }
                }
            }

        }
        for (_for_it_46 = 1; (_for_it_46 <= kfdia); _for_it_46 = (_for_it_46 + 1)) {
            {

                {
                    double ydecldp_0_in_rlmin = v_ydecldp_rlmin[0];
                    double za_0_in_0 = za[((_for_it_46 + (klon * (_for_it_23 - 1))) - 1)];
                    double zdqs_0_in_0 = zdqs[(_for_it_46 - 1)];
                    double _if_cond_32_out;

                    ///////////////////
                    // Tasklet code (T_l0_c0)
                    _if_cond_32_out = ((zdqs_0_in_0 <= (- ydecldp_0_in_rlmin)) && (za_0_in_0 < 0.99999999999999));
                    ///////////////////

                    _if_cond_32 = _if_cond_32_out;
                }

            }
            if ((_if_cond_32 == 1)) {
                {

                    {
                        double ydecldp_0_in_ramid = v_ydecldp_ramid[0];
                        double zrhc_out;

                        ///////////////////
                        // Tasklet code (T_l825_c825)
                        zrhc_out = ydecldp_0_in_ramid;
                        ///////////////////

                        zrhc = zrhc_out;
                    }

                }
                zsigk = (pap[((_for_it_46 + (klon * (_for_it_23 - 1))) - 1)] / paph[((_for_it_46 + (klev * klon)) - 1)]);
                if (((zsigk > 0.8) == 1)) {
                    {
                        double tmp_call_40;
                        double tmp_arg_21;

                        {
                            double tmp_arg_21_out;

                            ///////////////////
                            // Tasklet code (T_l828_c828)
                            tmp_arg_21_out = ((zsigk - 0.8) / 0.2);
                            ///////////////////

                            tmp_arg_21 = tmp_arg_21_out;
                        }
                        {
                            double tmp_arg_21_0_in = tmp_arg_21;
                            double tmp_call_40_out;

                            ///////////////////
                            // Tasklet code (T_l828_c828)
                            tmp_call_40_out = (dace::math::ipow(tmp_arg_21_0_in, 2));
                            ///////////////////

                            tmp_call_40 = tmp_call_40_out;
                        }
                        {
                            double tmp_call_40_0_in = tmp_call_40;
                            double ydecldp_0_in_ramid = v_ydecldp_ramid[0];
                            double ydecldp_1_in_ramid = v_ydecldp_ramid[0];
                            double zrhc_out;

                            ///////////////////
                            // Tasklet code (T_l828_c828)
                            zrhc_out = (ydecldp_0_in_ramid + ((1.0 - ydecldp_1_in_ramid) * tmp_call_40_0_in));
                            ///////////////////

                            zrhc = zrhc_out;
                        }

                    }
                }
                {

                    {
                        int ydecldp_0_in_nssopt = v_ydecldp_nssopt[0];
                        int _if_cond_34_out;

                        ///////////////////
                        // Tasklet code (T_l0_c0)
                        _if_cond_34_out = (ydecldp_0_in_nssopt == 0);
                        ///////////////////

                        _if_cond_34 = _if_cond_34_out;
                    }

                }
                if ((_if_cond_34 == 1)) {
                    {
                        double tmp_call_41;
                        double tmp_arg_22;

                        {
                            double za_0_in_0 = za[((_for_it_46 + (klon * (_for_it_23 - 1))) - 1)];
                            double tmp_arg_22_out;

                            ///////////////////
                            // Tasklet code (T_l831_c831)
                            tmp_arg_22_out = (1.0 - za_0_in_0);
                            ///////////////////

                            tmp_arg_22 = tmp_arg_22_out;
                        }
                        {
                            double tmp_arg_22_0_in = tmp_arg_22;
                            double zepsec_0_in = zepsec;
                            double tmp_call_41_out;

                            ///////////////////
                            // Tasklet code (T_l831_c831)
                            tmp_call_41_out = max(zepsec_0_in, tmp_arg_22_0_in);
                            ///////////////////

                            tmp_call_41 = tmp_call_41_out;
                        }
                        {
                            double tmp_call_41_0_in = tmp_call_41;
                            double za_0_in_0 = za[((_for_it_46 + (klon * (_for_it_23 - 1))) - 1)];
                            double zqsice_0_in_0 = zqsice[((_for_it_46 + (klon * (_for_it_23 - 1))) - 1)];
                            double zqx_0_in_0 = zqx[(((_for_it_46 + ((4 * klev) * klon)) + (klon * (_for_it_23 - 1))) - 1)];
                            double zqe_out;

                            ///////////////////
                            // Tasklet code (T_l831_c831)
                            zqe_out = ((zqx_0_in_0 - (za_0_in_0 * zqsice_0_in_0)) / tmp_call_41_0_in);
                            ///////////////////

                            zqe = zqe_out;
                        }
                        {
                            double zqe_0_in = zqe;
                            double zqe_out;

                            ///////////////////
                            // Tasklet code (T_l832_c832)
                            zqe_out = max(0.0, zqe_0_in);
                            ///////////////////

                            zqe = zqe_out;
                        }

                    }
                } else {
                    {

                        {
                            int ydecldp_0_in_nssopt = v_ydecldp_nssopt[0];
                            int _if_cond_35_out;

                            ///////////////////
                            // Tasklet code (T_l833_c833)
                            _if_cond_35_out = (ydecldp_0_in_nssopt == 1);
                            ///////////////////

                            _if_cond_35 = _if_cond_35_out;
                        }

                    }
                    if ((_if_cond_35 == 1)) {
                        {
                            double tmp_call_42;
                            double tmp_arg_23;

                            {
                                double za_0_in_0 = za[((_for_it_46 + (klon * (_for_it_23 - 1))) - 1)];
                                double tmp_arg_23_out;

                                ///////////////////
                                // Tasklet code (T_l834_c834)
                                tmp_arg_23_out = (1.0 - za_0_in_0);
                                ///////////////////

                                tmp_arg_23 = tmp_arg_23_out;
                            }
                            {
                                double tmp_arg_23_0_in = tmp_arg_23;
                                double zepsec_0_in = zepsec;
                                double tmp_call_42_out;

                                ///////////////////
                                // Tasklet code (T_l834_c834)
                                tmp_call_42_out = max(zepsec_0_in, tmp_arg_23_0_in);
                                ///////////////////

                                tmp_call_42 = tmp_call_42_out;
                            }
                            {
                                double tmp_call_42_0_in = tmp_call_42;
                                double za_0_in_0 = za[((_for_it_46 + (klon * (_for_it_23 - 1))) - 1)];
                                double zqsice_0_in_0 = zqsice[((_for_it_46 + (klon * (_for_it_23 - 1))) - 1)];
                                double zqx_0_in_0 = zqx[(((_for_it_46 + ((4 * klev) * klon)) + (klon * (_for_it_23 - 1))) - 1)];
                                double zqe_out;

                                ///////////////////
                                // Tasklet code (T_l834_c834)
                                zqe_out = ((zqx_0_in_0 - (za_0_in_0 * zqsice_0_in_0)) / tmp_call_42_0_in);
                                ///////////////////

                                zqe = zqe_out;
                            }
                            {
                                double zqe_0_in = zqe;
                                double zqe_out;

                                ///////////////////
                                // Tasklet code (T_l835_c835)
                                zqe_out = max(0.0, zqe_0_in);
                                ///////////////////

                                zqe = zqe_out;
                            }

                        }
                    } else {
                        {

                            {
                                int ydecldp_0_in_nssopt = v_ydecldp_nssopt[0];
                                int _if_cond_36_out;

                                ///////////////////
                                // Tasklet code (T_l836_c836)
                                _if_cond_36_out = (ydecldp_0_in_nssopt == 2);
                                ///////////////////

                                _if_cond_36 = _if_cond_36_out;
                            }

                        }
                        if ((_if_cond_36 == 1)) {
                            {

                                {
                                    double zqx_0_in_0 = zqx[(((_for_it_46 + ((4 * klev) * klon)) + (klon * (_for_it_23 - 1))) - 1)];
                                    double zqe_out;

                                    ///////////////////
                                    // Tasklet code (T_l837_c837)
                                    zqe_out = zqx_0_in_0;
                                    ///////////////////

                                    zqe = zqe_out;
                                }

                            }
                        } else {
                            {

                                {
                                    int ydecldp_0_in_nssopt = v_ydecldp_nssopt[0];
                                    int _if_cond_37_out;

                                    ///////////////////
                                    // Tasklet code (T_l838_c838)
                                    _if_cond_37_out = (ydecldp_0_in_nssopt == 3);
                                    ///////////////////

                                    _if_cond_37 = _if_cond_37_out;
                                }

                            }
                            if ((_if_cond_37 == 1)) {
                                {

                                    {
                                        double zli_0_in_0 = zli[((_for_it_46 + (klon * (_for_it_23 - 1))) - 1)];
                                        double zqx_0_in_0 = zqx[(((_for_it_46 + ((4 * klev) * klon)) + (klon * (_for_it_23 - 1))) - 1)];
                                        double zqe_out;

                                        ///////////////////
                                        // Tasklet code (T_l839_c839)
                                        zqe_out = (zqx_0_in_0 + zli_0_in_0);
                                        ///////////////////

                                        zqe = zqe_out;
                                    }

                                }
                            }
                        }
                    }
                }
                {

                    {
                        double ydcst_0_in_rtt = v_ydcst_rtt[0];
                        int ydecldp_0_in_nssopt = v_ydecldp_nssopt[0];
                        double ztp1_0_in_0 = ztp1[((_for_it_46 + (klon * (_for_it_23 - 1))) - 1)];
                        double _if_cond_38_out;

                        ///////////////////
                        // Tasklet code (T_l0_c0)
                        _if_cond_38_out = ((ztp1_0_in_0 >= ydcst_0_in_rtt) || (ydecldp_0_in_nssopt == 0));
                        ///////////////////

                        _if_cond_38 = _if_cond_38_out;
                    }

                }
                if ((_if_cond_38 == 1)) {

                    zfac = 1.0;

                } else {

                    zfac = zfokoop[(_for_it_46 - 1)];

                }
                _if_cond_39 = ((zqe >= ((zrhc * zqsice[((_for_it_46 + (klon * (_for_it_23 - 1))) - 1)]) * zfac)) && (zqe < (zqsice[((_for_it_46 + (klon * (_for_it_23 - 1))) - 1)] * zfac)));
                if ((_if_cond_39 == 1)) {
                    {
                        double zzdl;
                        double tmp_call_43;
                        double tmp_call_44;
                        double tmp_arg_24;
                        double tmp_arg_25;
                        double tmp_arg_26;

                        {
                            double zqe_0_in = zqe;
                            double zqsice_0_in_0 = zqsice[((_for_it_46 + (klon * (_for_it_23 - 1))) - 1)];
                            double tmp_arg_24_out;

                            ///////////////////
                            // Tasklet code (T_l847_c847)
                            tmp_arg_24_out = (2.0 * ((zfac * zqsice_0_in_0) - zqe_0_in));
                            ///////////////////

                            tmp_arg_24 = tmp_arg_24_out;
                        }
                        {
                            double tmp_arg_24_0_in = tmp_arg_24;
                            double zepsec_0_in = zepsec;
                            double tmp_call_43_out;

                            ///////////////////
                            // Tasklet code (T_l847_c847)
                            tmp_call_43_out = max(tmp_arg_24_0_in, zepsec_0_in);
                            ///////////////////

                            tmp_call_43 = tmp_call_43_out;
                        }
                        {
                            double za_0_in_0 = za[((_for_it_46 + (klon * (_for_it_23 - 1))) - 1)];
                            double tmp_arg_25_out;

                            ///////////////////
                            // Tasklet code (T_l848_c848)
                            tmp_arg_25_out = (1.0 - za_0_in_0);
                            ///////////////////

                            tmp_arg_25 = tmp_arg_25_out;
                        }
                        {
                            double tmp_call_43_0_in = tmp_call_43;
                            double za_0_in_0 = za[((_for_it_46 + (klon * (_for_it_23 - 1))) - 1)];
                            double zdqs_0_in_0 = zdqs[(_for_it_46 - 1)];
                            double zacond_out;

                            ///////////////////
                            // Tasklet code (T_l847_c847)
                            zacond_out = (- ((((1.0 - za_0_in_0) * zfac) * zdqs_0_in_0) / tmp_call_43_0_in));
                            ///////////////////

                            zacond = zacond_out;
                        }
                        {
                            double tmp_arg_25_0_in = tmp_arg_25;
                            double zacond_0_in = zacond;
                            double zacond_out;

                            ///////////////////
                            // Tasklet code (T_l848_c848)
                            zacond_out = min(zacond_0_in, tmp_arg_25_0_in);
                            ///////////////////

                            zacond = zacond_out;
                        }
                        {
                            double zacond_0_in = zacond;
                            double zdqs_0_in_0 = zdqs[(_for_it_46 - 1)];
                            double zlcond2_out_0;

                            ///////////////////
                            // Tasklet code (T_l849_c849)
                            zlcond2_out_0 = (- (((zfac * zdqs_0_in_0) * 0.5) * zacond_0_in));
                            ///////////////////

                            zlcond2[(_for_it_46 - 1)] = zlcond2_out_0;
                        }
                        {
                            double za_0_in_0 = za[((_for_it_46 + (klon * (_for_it_23 - 1))) - 1)];
                            double tmp_arg_26_out;

                            ///////////////////
                            // Tasklet code (T_l850_c850)
                            tmp_arg_26_out = (1.0 - za_0_in_0);
                            ///////////////////

                            tmp_arg_26 = tmp_arg_26_out;
                        }
                        {
                            double tmp_arg_26_0_in = tmp_arg_26;
                            double zepsec_0_in = zepsec;
                            double tmp_call_44_out;

                            ///////////////////
                            // Tasklet code (T_l850_c850)
                            tmp_call_44_out = max(zepsec_0_in, tmp_arg_26_0_in);
                            ///////////////////

                            tmp_call_44 = tmp_call_44_out;
                        }
                        {
                            double tmp_call_44_0_in = tmp_call_44;
                            double zqe_0_in = zqe;
                            double zqsice_0_in_0 = zqsice[((_for_it_46 + (klon * (_for_it_23 - 1))) - 1)];
                            double zzdl_out;

                            ///////////////////
                            // Tasklet code (T_l850_c850)
                            zzdl_out = ((2.0 * ((zfac * zqsice_0_in_0) - zqe_0_in)) / tmp_call_44_0_in);
                            ///////////////////

                            zzdl = zzdl_out;
                        }
                        {
                            double zdqs_0_in_0 = zdqs[(_for_it_46 - 1)];
                            double zzdl_0_in = zzdl;
                            double _if_cond_40_out;

                            ///////////////////
                            // Tasklet code (T_l0_c0)
                            _if_cond_40_out = ((zfac * zdqs_0_in_0) < (- zzdl_0_in));
                            ///////////////////

                            _if_cond_40 = _if_cond_40_out;
                        }

                    }
                    if ((_if_cond_40 == 1)) {
                        {
                            double zlcondlim;
                            double tmp_call_45;

                            {
                                double za_0_in_0 = za[((_for_it_46 + (klon * (_for_it_23 - 1))) - 1)];
                                double zdqs_0_in_0 = zdqs[(_for_it_46 - 1)];
                                double zqsice_0_in_0 = zqsice[((_for_it_46 + (klon * (_for_it_23 - 1))) - 1)];
                                double zqx_0_in_0 = zqx[(((_for_it_46 + ((4 * klev) * klon)) + (klon * (_for_it_23 - 1))) - 1)];
                                double zlcondlim_out;

                                ///////////////////
                                // Tasklet code (T_l852_c852)
                                zlcondlim_out = (((((za_0_in_0 - 1.0) * zfac) * zdqs_0_in_0) - (zfac * zqsice_0_in_0)) + zqx_0_in_0);
                                ///////////////////

                                zlcondlim = zlcondlim_out;
                            }
                            {
                                double zlcond2_0_in_0 = zlcond2[(_for_it_46 - 1)];
                                double zlcondlim_0_in = zlcondlim;
                                double tmp_call_45_out;

                                ///////////////////
                                // Tasklet code (T_l853_c853)
                                tmp_call_45_out = min(zlcond2_0_in_0, zlcondlim_0_in);
                                ///////////////////

                                tmp_call_45 = tmp_call_45_out;
                            }
                            {
                                double tmp_call_45_0_in = tmp_call_45;
                                double zlcond2_out_0;

                                ///////////////////
                                // Tasklet code (T_l853_c853)
                                zlcond2_out_0 = tmp_call_45_0_in;
                                ///////////////////

                                zlcond2[(_for_it_46 - 1)] = zlcond2_out_0;
                            }

                        }
                    }
                    {
                        double tmp_call_46;

                        {
                            double zlcond2_0_in_0 = zlcond2[(_for_it_46 - 1)];
                            double tmp_call_46_out;

                            ///////////////////
                            // Tasklet code (T_l855_c855)
                            tmp_call_46_out = max(zlcond2_0_in_0, 0.0);
                            ///////////////////

                            tmp_call_46 = tmp_call_46_out;
                        }
                        {
                            double tmp_call_46_0_in = tmp_call_46;
                            double zlcond2_out_0;

                            ///////////////////
                            // Tasklet code (T_l855_c855)
                            zlcond2_out_0 = tmp_call_46_0_in;
                            ///////////////////

                            zlcond2[(_for_it_46 - 1)] = zlcond2_out_0;
                        }
                        {
                            double ydecldp_0_in_rlmin = v_ydecldp_rlmin[0];
                            double za_0_in_0 = za[((_for_it_46 + (klon * (_for_it_23 - 1))) - 1)];
                            double zlcond2_0_in_0 = zlcond2[(_for_it_46 - 1)];
                            double _if_cond_41_out;

                            ///////////////////
                            // Tasklet code (T_l0_c0)
                            _if_cond_41_out = ((zlcond2_0_in_0 < ydecldp_0_in_rlmin) || ((1.0 - za_0_in_0) < 1e-14));
                            ///////////////////

                            _if_cond_41 = _if_cond_41_out;
                        }

                    }
                    if ((_if_cond_41 == 1)) {
                        {

                            {
                                double zlcond2_out_0;

                                ///////////////////
                                // Tasklet code (T_l857_c857)
                                zlcond2_out_0 = 0.0;
                                ///////////////////

                                zlcond2[(_for_it_46 - 1)] = zlcond2_out_0;
                            }
                            {
                                double zacond_out;

                                ///////////////////
                                // Tasklet code (T_l858_c858)
                                zacond_out = 0.0;
                                ///////////////////

                                zacond = zacond_out;
                            }

                        }
                    }
                    _if_cond_42 = (zlcond2[(_for_it_46 - 1)] == 0.0);
                    if ((_if_cond_42 == 1)) {
                        {

                            {
                                double zacond_out;

                                ///////////////////
                                // Tasklet code (T_l860_c860)
                                zacond_out = 0.0;
                                ///////////////////

                                zacond = zacond_out;
                            }

                        }
                    }
                    {

                        {
                            double zacond_0_in = zacond;
                            double zsolac_0_in_0 = zsolac[(_for_it_46 - 1)];
                            double zsolac_out_0;

                            ///////////////////
                            // Tasklet code (T_l861_c861)
                            zsolac_out_0 = (zsolac_0_in_0 + zacond_0_in);
                            ///////////////////

                            zsolac[(_for_it_46 - 1)] = zsolac_out_0;
                        }
                        {
                            double ydecldp_0_in_rthomo = v_ydecldp_rthomo[0];
                            double ztp1_0_in_0 = ztp1[((_for_it_46 + (klon * (_for_it_23 - 1))) - 1)];
                            double _if_cond_43_out;

                            ///////////////////
                            // Tasklet code (T_l0_c0)
                            _if_cond_43_out = (ztp1_0_in_0 > ydecldp_0_in_rthomo);
                            ///////////////////

                            _if_cond_43 = _if_cond_43_out;
                        }

                    }
                    if ((_if_cond_43 == 1)) {
                        {

                            {
                                double zlcond2_0_in_0 = zlcond2[(_for_it_46 - 1)];
                                double zsolqa_0_in_0 = zsolqa[((_for_it_46 + (20 * klon)) - 1)];
                                double zsolqa_out_0;

                                ///////////////////
                                // Tasklet code (T_l863_c863)
                                zsolqa_out_0 = (zsolqa_0_in_0 + zlcond2_0_in_0);
                                ///////////////////

                                zsolqa[((_for_it_46 + (20 * klon)) - 1)] = zsolqa_out_0;
                            }
                            {
                                double zlcond2_0_in_0 = zlcond2[(_for_it_46 - 1)];
                                double zsolqa_0_in_0 = zsolqa[((_for_it_46 + (4 * klon)) - 1)];
                                double zsolqa_out_0;

                                ///////////////////
                                // Tasklet code (T_l864_c864)
                                zsolqa_out_0 = (zsolqa_0_in_0 - zlcond2_0_in_0);
                                ///////////////////

                                zsolqa[((_for_it_46 + (4 * klon)) - 1)] = zsolqa_out_0;
                            }
                            {
                                double zlcond2_0_in_0 = zlcond2[(_for_it_46 - 1)];
                                double zqxfg_0_in_0 = zqxfg[(_for_it_46 - 1)];
                                double zqxfg_out_0;

                                ///////////////////
                                // Tasklet code (T_l865_c865)
                                zqxfg_out_0 = (zqxfg_0_in_0 + zlcond2_0_in_0);
                                ///////////////////

                                zqxfg[(_for_it_46 - 1)] = zqxfg_out_0;
                            }

                        }
                    } else {
                        {

                            {
                                double zlcond2_0_in_0 = zlcond2[(_for_it_46 - 1)];
                                double zsolqa_0_in_0 = zsolqa[((_for_it_46 + (21 * klon)) - 1)];
                                double zsolqa_out_0;

                                ///////////////////
                                // Tasklet code (T_l867_c867)
                                zsolqa_out_0 = (zsolqa_0_in_0 + zlcond2_0_in_0);
                                ///////////////////

                                zsolqa[((_for_it_46 + (21 * klon)) - 1)] = zsolqa_out_0;
                            }
                            {
                                double zlcond2_0_in_0 = zlcond2[(_for_it_46 - 1)];
                                double zsolqa_0_in_0 = zsolqa[((_for_it_46 + (9 * klon)) - 1)];
                                double zsolqa_out_0;

                                ///////////////////
                                // Tasklet code (T_l868_c868)
                                zsolqa_out_0 = (zsolqa_0_in_0 - zlcond2_0_in_0);
                                ///////////////////

                                zsolqa[((_for_it_46 + (9 * klon)) - 1)] = zsolqa_out_0;
                            }
                            {
                                double zlcond2_0_in_0 = zlcond2[(_for_it_46 - 1)];
                                double zqxfg_0_in_0 = zqxfg[((_for_it_46 + klon) - 1)];
                                double zqxfg_out_0;

                                ///////////////////
                                // Tasklet code (T_l869_c869)
                                zqxfg_out_0 = (zqxfg_0_in_0 + zlcond2_0_in_0);
                                ///////////////////

                                zqxfg[((_for_it_46 + klon) - 1)] = zqxfg_out_0;
                            }

                        }
                    }
                }
            }

        }
        for (_for_it_47 = 1; (_for_it_47 <= kfdia); _for_it_47 = (_for_it_47 + 1)) {
            {
                double* v_ydecldp_rcldtopcf;
                v_ydecldp_rcldtopcf = (double*)(&(ydecldp->rcldtopcf));

                {
                    double ydecldp_0_in_rcldtopcf = v_ydecldp_rcldtopcf[0];
                    double ydecldp_1_in_rcldtopcf = v_ydecldp_rcldtopcf[0];
                    double za_0_in_0 = za[((_for_it_47 + (klon * (_for_it_23 - 2))) - 1)];
                    double za_1_in_0 = za[((_for_it_47 + (klon * (_for_it_23 - 1))) - 1)];
                    double _if_cond_44_out;

                    ///////////////////
                    // Tasklet code (T_l0_c0)
                    _if_cond_44_out = ((za_0_in_0 < ydecldp_0_in_rcldtopcf) && (za_1_in_0 >= ydecldp_1_in_rcldtopcf));
                    ///////////////////

                    _if_cond_44 = _if_cond_44_out;
                }

            }
            if ((_if_cond_44 == 1)) {
                {

                    {
                        double zcldtopdist_out_0;

                        ///////////////////
                        // Tasklet code (T_l876_c876)
                        zcldtopdist_out_0 = 0.0;
                        ///////////////////

                        zcldtopdist[(_for_it_47 - 1)] = zcldtopdist_out_0;
                    }

                }
            } else {
                {

                    {
                        double ydcst_0_in_rg = v_ydcst_rg[0];
                        double zcldtopdist_0_in_0 = zcldtopdist[(_for_it_47 - 1)];
                        double zdp_0_in_0 = zdp[(_for_it_47 - 1)];
                        double zrho_0_in_0 = zrho[(_for_it_47 - 1)];
                        double zcldtopdist_out_0;

                        ///////////////////
                        // Tasklet code (T_l878_c878)
                        zcldtopdist_out_0 = (zcldtopdist_0_in_0 + (zdp_0_in_0 / (zrho_0_in_0 * ydcst_0_in_rg)));
                        ///////////////////

                        zcldtopdist[(_for_it_47 - 1)] = zcldtopdist_out_0;
                    }

                }
            }
            {

                {
                    double ydcst_0_in_rtt = v_ydcst_rtt[0];
                    double ydecldp_0_in_rlmin = v_ydecldp_rlmin[0];
                    double zqxfg_0_in_0 = zqxfg[(_for_it_47 - 1)];
                    double ztp1_0_in_0 = ztp1[((_for_it_47 + (klon * (_for_it_23 - 1))) - 1)];
                    double _if_cond_45_out;

                    ///////////////////
                    // Tasklet code (T_l0_c0)
                    _if_cond_45_out = ((ztp1_0_in_0 < ydcst_0_in_rtt) && (zqxfg_0_in_0 > ydecldp_0_in_rlmin));
                    ///////////////////

                    _if_cond_45 = _if_cond_45_out;
                }

            }
            if ((_if_cond_45 == 1)) {
                {
                    double tmp_call_47;
                    double tmp_call_118_0;
                    double tmp_arg_72_0;

                    {
                        double ztp1_0_in_0 = ztp1[((_for_it_47 + (klon * (_for_it_23 - 1))) - 1)];
                        double oka_out;

                        ///////////////////
                        // Tasklet code (T_l881_c881)
                        oka_out = ztp1_0_in_0;
                        ///////////////////

                        oka = oka_out;
                    }
                    {
                        double ptare_var_14_0_in = oka;
                        double ptare_var_14_1_in = oka;
                        double ydcst_var_16_0_in_rtt = v_ydcst_var_16_rtt[0];
                        double ydthf_var_15_0_in_r3ies = v_ydthf_var_15_r3ies[0];
                        double ydthf_var_15_1_in_r4ies = v_ydthf_var_15_r4ies[0];
                        double tmp_arg_72_out;

                        ///////////////////
                        // Tasklet code (T_l1409_c1409)
                        tmp_arg_72_out = ((ydthf_var_15_0_in_r3ies * (ptare_var_14_0_in - ydcst_var_16_0_in_rtt)) / (ptare_var_14_1_in - ydthf_var_15_1_in_r4ies));
                        ///////////////////

                        tmp_arg_72_0 = tmp_arg_72_out;
                    }
                    {
                        double tmp_arg_72_0_in = tmp_arg_72_0;
                        double tmp_call_118_out;

                        ///////////////////
                        // Tasklet code (T_l1409_c1409)
                        tmp_call_118_out = exp(tmp_arg_72_0_in);
                        ///////////////////

                        tmp_call_118_0 = tmp_call_118_out;
                    }
                    {
                        double tmp_call_118_0_in = tmp_call_118_0;
                        double ydthf_var_15_0_in_r2es = v_ydthf_var_15_r2es[0];
                        double foeeice__ret_out;

                        ///////////////////
                        // Tasklet code (T_l1409_c1409)
                        foeeice__ret_out = (ydthf_var_15_0_in_r2es * tmp_call_118_0_in);
                        ///////////////////

                        tmp_call_47 = foeeice__ret_out;
                    }
                    {
                        double tmp_call_47_0_in = tmp_call_47;
                        double ydcst_0_in_rv = v_ydcst_rv[0];
                        double ydcst_1_in_rd = v_ydcst_rd[0];
                        double zvpice_out;

                        ///////////////////
                        // Tasklet code (T_l882_c882)
                        zvpice_out = ((tmp_call_47_0_in * ydcst_0_in_rv) / ydcst_1_in_rd);
                        ///////////////////

                        zvpice = zvpice_out;
                    }
                    {
                        double zfokoop_0_in_0 = zfokoop[(_for_it_47 - 1)];
                        double zvpice_0_in = zvpice;
                        double zvpliq_out;

                        ///////////////////
                        // Tasklet code (T_l883_c883)
                        zvpliq_out = (zvpice_0_in * zfokoop_0_in_0);
                        ///////////////////

                        zvpliq = zvpliq_out;
                    }

                }
                {
                    double tmp_call_48;
                    double tmp_arg_27;

                    {
                        double zvpice_0_in = zvpice;
                        double zvpliq_0_in = zvpliq;
                        double zvpliq_1_in = zvpliq;
                        double tmp_arg_27_out;

                        ///////////////////
                        // Tasklet code (T_l884_c884)
                        tmp_arg_27_out = (((12.96 * (zvpliq_0_in - zvpice_0_in)) / zvpliq_1_in) - 0.639);
                        ///////////////////

                        tmp_arg_27 = tmp_arg_27_out;
                    }
                    {
                        double tmp_arg_27_0_in = tmp_arg_27;
                        double tmp_call_48_out;

                        ///////////////////
                        // Tasklet code (T_l884_c884)
                        tmp_call_48_out = exp(tmp_arg_27_0_in);
                        ///////////////////

                        tmp_call_48 = tmp_call_48_out;
                    }
                    {
                        double tmp_call_48_0_in = tmp_call_48;
                        double zicenuclei_out_0;

                        ///////////////////
                        // Tasklet code (T_l884_c884)
                        zicenuclei_out_0 = (1000.0 * tmp_call_48_0_in);
                        ///////////////////

                        zicenuclei[(_for_it_47 - 1)] = zicenuclei_out_0;
                    }
                    {
                        double ydcst_0_in_rlstt = v_ydcst_rlstt[0];
                        double ydcst_1_in_rlstt = v_ydcst_rlstt[0];
                        double ydcst_2_in_rv = v_ydcst_rv[0];
                        double ztp1_0_in_0 = ztp1[((_for_it_47 + (klon * (_for_it_23 - 1))) - 1)];
                        double ztp1_1_in_0 = ztp1[((_for_it_47 + (klon * (_for_it_23 - 1))) - 1)];
                        double zadd_out;

                        ///////////////////
                        // Tasklet code (T_l885_c885)
                        zadd_out = ((ydcst_0_in_rlstt * ((ydcst_1_in_rlstt / (ydcst_2_in_rv * ztp1_0_in_0)) - 1.0)) / (0.024 * ztp1_1_in_0));
                        ///////////////////

                        zadd = zadd_out;
                    }

                }
                {
                    double zinew;
                    double zbdd;
                    double zcvds;
                    double zice0;
                    double zdepos;
                    double zinfactor;
                    double tmp_call_49;
                    double tmp_call_50;
                    double tmp_call_51;
                    double tmp_arg_28;
                    double tmp_arg_29;
                    double tmp_arg_30;
                    double tmp_arg_31;
                    double tmp_arg_32;
                    double tmp_arg_33;
                    double* v_ydecldp_riceinit;
                    v_ydecldp_riceinit = (double*)(&(ydecldp->riceinit));
                    double* v_ydecldp_rdepliqrefrate;
                    v_ydecldp_rdepliqrefrate = (double*)(&(ydecldp->rdepliqrefrate));
                    double* v_ydecldp_rdepliqrefdepth;
                    v_ydecldp_rdepliqrefdepth = (double*)(&(ydecldp->rdepliqrefdepth));

                    {
                        double pap_0_in_0 = pap[((_for_it_47 + (klon * (_for_it_23 - 1))) - 1)];
                        double ydcst_0_in_rv = v_ydcst_rv[0];
                        double ztp1_0_in_0 = ztp1[((_for_it_47 + (klon * (_for_it_23 - 1))) - 1)];
                        double zvpice_0_in = zvpice;
                        double zbdd_out;

                        ///////////////////
                        // Tasklet code (T_l886_c886)
                        zbdd_out = (((ydcst_0_in_rv * ztp1_0_in_0) * pap_0_in_0) / (2.21 * zvpice_0_in));
                        ///////////////////

                        zbdd = zbdd_out;
                    }
                    {
                        double zicenuclei_0_in_0 = zicenuclei[(_for_it_47 - 1)];
                        double tmp_arg_32_out;

                        ///////////////////
                        // Tasklet code (T_l892_c892)
                        tmp_arg_32_out = (zicenuclei_0_in_0 / 15000.0);
                        ///////////////////

                        tmp_arg_32 = tmp_arg_32_out;
                    }
                    {
                        double tmp_arg_32_0_in = tmp_arg_32;
                        double zinfactor_out;

                        ///////////////////
                        // Tasklet code (T_l892_c892)
                        zinfactor_out = min(tmp_arg_32_0_in, 1.0);
                        ///////////////////

                        zinfactor = zinfactor_out;
                    }
                    {
                        double zicenuclei_0_in_0 = zicenuclei[(_for_it_47 - 1)];
                        double zrho_0_in_0 = zrho[(_for_it_47 - 1)];
                        double tmp_arg_28_out;

                        ///////////////////
                        // Tasklet code (T_l887_c887)
                        tmp_arg_28_out = (zicenuclei_0_in_0 / zrho_0_in_0);
                        ///////////////////

                        tmp_arg_28 = tmp_arg_28_out;
                    }
                    {
                        double tmp_arg_28_0_in = tmp_arg_28;
                        double tmp_call_49_out;

                        ///////////////////
                        // Tasklet code (T_l887_c887)
                        tmp_call_49_out = dace::math::pow(tmp_arg_28_0_in, 0.666);
                        ///////////////////

                        tmp_call_49 = tmp_call_49_out;
                    }
                    {
                        double tmp_call_49_0_in = tmp_call_49;
                        double zadd_0_in = zadd;
                        double zbdd_0_in = zbdd;
                        double zvpice_0_in = zvpice;
                        double zvpice_1_in = zvpice;
                        double zvpliq_0_in = zvpliq;
                        double zcvds_out;

                        ///////////////////
                        // Tasklet code (T_l887_c887)
                        zcvds_out = (((7.8 * tmp_call_49_0_in) * (zvpliq_0_in - zvpice_0_in)) / ((8.87 * (zadd_0_in + zbdd_0_in)) * zvpice_1_in));
                        ///////////////////

                        zcvds = zcvds_out;
                    }
                    {
                        double ydecldp_0_in_riceinit = v_ydecldp_riceinit[0];
                        double zicenuclei_0_in_0 = zicenuclei[(_for_it_47 - 1)];
                        double zrho_0_in_0 = zrho[(_for_it_47 - 1)];
                        double tmp_arg_29_out;

                        ///////////////////
                        // Tasklet code (T_l888_c888)
                        tmp_arg_29_out = ((zicenuclei_0_in_0 * ydecldp_0_in_riceinit) / zrho_0_in_0);
                        ///////////////////

                        tmp_arg_29 = tmp_arg_29_out;
                    }
                    {
                        double tmp_arg_29_0_in = tmp_arg_29;
                        double zicecld_0_in_0 = zicecld[(_for_it_47 - 1)];
                        double zice0_out;

                        ///////////////////
                        // Tasklet code (T_l888_c888)
                        zice0_out = max(zicecld_0_in_0, tmp_arg_29_0_in);
                        ///////////////////

                        zice0 = zice0_out;
                    }
                    {
                        double zice0_0_in = zice0;
                        double tmp_call_50_out;

                        ///////////////////
                        // Tasklet code (T_l889_c889)
                        tmp_call_50_out = dace::math::pow(zice0_0_in, 0.666);
                        ///////////////////

                        tmp_call_50 = tmp_call_50_out;
                    }
                    {
                        double ptsphy_0_in = ptsphy;
                        double tmp_call_50_0_in = tmp_call_50;
                        double zcvds_0_in = zcvds;
                        double tmp_arg_30_out;

                        ///////////////////
                        // Tasklet code (T_l889_c889)
                        tmp_arg_30_out = (((0.666 * zcvds_0_in) * ptsphy_0_in) + tmp_call_50_0_in);
                        ///////////////////

                        tmp_arg_30 = tmp_arg_30_out;
                    }
                    {
                        double tmp_arg_30_0_in = tmp_arg_30;
                        double zinew_out;

                        ///////////////////
                        // Tasklet code (T_l889_c889)
                        zinew_out = dace::math::pow(tmp_arg_30_0_in, 1.5);
                        ///////////////////

                        zinew = zinew_out;
                    }
                    {
                        double za_0_in_0 = za[((_for_it_47 + (klon * (_for_it_23 - 1))) - 1)];
                        double zice0_0_in = zice0;
                        double zinew_0_in = zinew;
                        double tmp_arg_31_out;

                        ///////////////////
                        // Tasklet code (T_l890_c890)
                        tmp_arg_31_out = (za_0_in_0 * (zinew_0_in - zice0_0_in));
                        ///////////////////

                        tmp_arg_31 = tmp_arg_31_out;
                    }
                    {
                        double tmp_arg_31_0_in = tmp_arg_31;
                        double zdepos_out;

                        ///////////////////
                        // Tasklet code (T_l890_c890)
                        zdepos_out = max(tmp_arg_31_0_in, 0.0);
                        ///////////////////

                        zdepos = zdepos_out;
                    }
                    {
                        double zdepos_0_in = zdepos;
                        double zqxfg_0_in_0 = zqxfg[(_for_it_47 - 1)];
                        double zdepos_out;

                        ///////////////////
                        // Tasklet code (T_l891_c891)
                        zdepos_out = min(zdepos_0_in, zqxfg_0_in_0);
                        ///////////////////

                        zdepos = zdepos_out;
                    }
                    {
                        double ydecldp_0_in_rdepliqrefrate = v_ydecldp_rdepliqrefrate[0];
                        double ydecldp_1_in_rdepliqrefdepth = v_ydecldp_rdepliqrefdepth[0];
                        double zcldtopdist_0_in_0 = zcldtopdist[(_for_it_47 - 1)];
                        double zinfactor_0_in = zinfactor;
                        double zinfactor_1_in = zinfactor;
                        double tmp_arg_33_out;

                        ///////////////////
                        // Tasklet code (T_l893_c893)
                        tmp_arg_33_out = (zinfactor_0_in + ((1.0 - zinfactor_1_in) * (ydecldp_0_in_rdepliqrefrate + (zcldtopdist_0_in_0 / ydecldp_1_in_rdepliqrefdepth))));
                        ///////////////////

                        tmp_arg_33 = tmp_arg_33_out;
                    }
                    {
                        double tmp_arg_33_0_in = tmp_arg_33;
                        double tmp_call_51_out;

                        ///////////////////
                        // Tasklet code (T_l893_c893)
                        tmp_call_51_out = min(tmp_arg_33_0_in, 1.0);
                        ///////////////////

                        tmp_call_51 = tmp_call_51_out;
                    }
                    {
                        double tmp_call_51_0_in = tmp_call_51;
                        double zdepos_0_in = zdepos;
                        double zdepos_out;

                        ///////////////////
                        // Tasklet code (T_l893_c893)
                        zdepos_out = (zdepos_0_in * tmp_call_51_0_in);
                        ///////////////////

                        zdepos = zdepos_out;
                    }
                    {
                        double zdepos_0_in = zdepos;
                        double zqxfg_0_in_0 = zqxfg[((_for_it_47 + klon) - 1)];
                        double zqxfg_out_0;

                        ///////////////////
                        // Tasklet code (T_l896_c896)
                        zqxfg_out_0 = (zqxfg_0_in_0 + zdepos_0_in);
                        ///////////////////

                        zqxfg[((_for_it_47 + klon) - 1)] = zqxfg_out_0;
                    }
                    {
                        double zdepos_0_in = zdepos;
                        double zqxfg_0_in_0 = zqxfg[(_for_it_47 - 1)];
                        double zqxfg_out_0;

                        ///////////////////
                        // Tasklet code (T_l897_c897)
                        zqxfg_out_0 = (zqxfg_0_in_0 - zdepos_0_in);
                        ///////////////////

                        zqxfg[(_for_it_47 - 1)] = zqxfg_out_0;
                    }
                    {
                        double zdepos_0_in = zdepos;
                        double zsolqa_0_in_0 = zsolqa[((_for_it_47 + klon) - 1)];
                        double zsolqa_out_0;

                        ///////////////////
                        // Tasklet code (T_l894_c894)
                        zsolqa_out_0 = (zsolqa_0_in_0 + zdepos_0_in);
                        ///////////////////

                        zsolqa[((_for_it_47 + klon) - 1)] = zsolqa_out_0;
                    }
                    {
                        double zdepos_0_in = zdepos;
                        double zsolqa_0_in_0 = zsolqa[((_for_it_47 + (5 * klon)) - 1)];
                        double zsolqa_out_0;

                        ///////////////////
                        // Tasklet code (T_l895_c895)
                        zsolqa_out_0 = (zsolqa_0_in_0 - zdepos_0_in);
                        ///////////////////

                        zsolqa[((_for_it_47 + (5 * klon)) - 1)] = zsolqa_out_0;
                    }

                }
            }

        }
        for (_for_it_48 = 1; (_for_it_48 <= kfdia); _for_it_48 = (_for_it_48 + 1)) {
            {
                double tmp_call_52;

                {
                    double za_0_in_0 = za[((_for_it_48 + (klon * (_for_it_23 - 1))) - 1)];
                    double zepsec_0_in = zepsec;
                    double tmp_call_52_out;

                    ///////////////////
                    // Tasklet code (T_l901_c901)
                    tmp_call_52_out = max(za_0_in_0, zepsec_0_in);
                    ///////////////////

                    tmp_call_52 = tmp_call_52_out;
                }
                {
                    double tmp_call_52_0_in = tmp_call_52;
                    double ztmpa_out;

                    ///////////////////
                    // Tasklet code (T_l901_c901)
                    ztmpa_out = (1.0 / tmp_call_52_0_in);
                    ///////////////////

                    ztmpa = ztmpa_out;
                }
                {
                    double zqxfg_0_in_0 = zqxfg[(_for_it_48 - 1)];
                    double ztmpa_0_in = ztmpa;
                    double zliqcld_out_0;

                    ///////////////////
                    // Tasklet code (T_l902_c902)
                    zliqcld_out_0 = (zqxfg_0_in_0 * ztmpa_0_in);
                    ///////////////////

                    zliqcld[(_for_it_48 - 1)] = zliqcld_out_0;
                }
                {
                    double zqxfg_0_in_0 = zqxfg[((_for_it_48 + klon) - 1)];
                    double ztmpa_0_in = ztmpa;
                    double zicecld_out_0;

                    ///////////////////
                    // Tasklet code (T_l903_c903)
                    zicecld_out_0 = (zqxfg_0_in_0 * ztmpa_0_in);
                    ///////////////////

                    zicecld[(_for_it_48 - 1)] = zicecld_out_0;
                }
                {
                    double zicecld_0_in_0 = zicecld[(_for_it_48 - 1)];
                    double zliqcld_0_in_0 = zliqcld[(_for_it_48 - 1)];
                    double zlicld_out_0;

                    ///////////////////
                    // Tasklet code (T_l904_c904)
                    zlicld_out_0 = (zliqcld_0_in_0 + zicecld_0_in_0);
                    ///////////////////

                    zlicld[(_for_it_48 - 1)] = zlicld_out_0;
                }

            }

        }
        for (_for_it_49 = 1; (_for_it_49 <= 5); _for_it_49 = (_for_it_49 + 1)) {

            _if_cond_46 = (llfall[(_for_it_49 - 1)] || (_for_it_49 == 2));
            if ((_if_cond_46 == 1)) {
                for (_for_it_50 = 1; (_for_it_50 <= kfdia); _for_it_50 = (_for_it_50 + 1)) {
                    {

                        {
                            int ydecldp_0_in_ncldtop = v_ydecldp_ncldtop[0];
                            int _if_cond_47_out;

                            ///////////////////
                            // Tasklet code (T_l0_c0)
                            _if_cond_47_out = (_for_it_23 > ydecldp_0_in_ncldtop);
                            ///////////////////

                            _if_cond_47 = _if_cond_47_out;
                        }

                    }
                    if ((_if_cond_47 == 1)) {
                        {

                            {
                                double zdtgdp_0_in_0 = zdtgdp[(_for_it_50 - 1)];
                                double zpfplsx_0_in_0 = zpfplsx[(((_for_it_50 + (klon * (_for_it_23 - 1))) + ((klon * (_for_it_49 - 1)) * (klev + 1))) - 1)];
                                double zfallsrce_out_0;

                                ///////////////////
                                // Tasklet code (T_l910_c910)
                                zfallsrce_out_0 = (zpfplsx_0_in_0 * zdtgdp_0_in_0);
                                ///////////////////

                                zfallsrce[((_for_it_50 + (klon * (_for_it_49 - 1))) - 1)] = zfallsrce_out_0;
                            }
                            {
                                double zfallsrce_0_in_0 = zfallsrce[((_for_it_50 + (klon * (_for_it_49 - 1))) - 1)];
                                double zsolqa_0_in_0 = zsolqa[((_for_it_50 + ((6 * klon) * (_for_it_49 - 1))) - 1)];
                                double zsolqa_out_0;

                                ///////////////////
                                // Tasklet code (T_l911_c911)
                                zsolqa_out_0 = (zsolqa_0_in_0 + zfallsrce_0_in_0);
                                ///////////////////

                                zsolqa[((_for_it_50 + ((6 * klon) * (_for_it_49 - 1))) - 1)] = zsolqa_out_0;
                            }
                            {
                                double zfallsrce_0_in_0 = zfallsrce[((_for_it_50 + (klon * (_for_it_49 - 1))) - 1)];
                                double zqxfg_0_in_0 = zqxfg[((_for_it_50 + (klon * (_for_it_49 - 1))) - 1)];
                                double zqxfg_out_0;

                                ///////////////////
                                // Tasklet code (T_l912_c912)
                                zqxfg_out_0 = (zqxfg_0_in_0 + zfallsrce_0_in_0);
                                ///////////////////

                                zqxfg[((_for_it_50 + (klon * (_for_it_49 - 1))) - 1)] = zqxfg_out_0;
                            }
                            {
                                double zqpretot_0_in_0 = zqpretot[(_for_it_50 - 1)];
                                double zqxfg_0_in_0 = zqxfg[((_for_it_50 + (klon * (_for_it_49 - 1))) - 1)];
                                double zqpretot_out_0;

                                ///////////////////
                                // Tasklet code (T_l913_c913)
                                zqpretot_out_0 = (zqpretot_0_in_0 + zqxfg_0_in_0);
                                ///////////////////

                                zqpretot[(_for_it_50 - 1)] = zqpretot_out_0;
                            }

                        }
                    }
                    {
                        int* v_ydecldp_laericesed;
                        v_ydecldp_laericesed = (int*)(&(ydecldp->laericesed));

                        {
                            int ydecldp_0_in_laericesed = v_ydecldp_laericesed[0];
                            int _if_cond_48_out;

                            ///////////////////
                            // Tasklet code (T_l0_c0)
                            _if_cond_48_out = (ydecldp_0_in_laericesed && (_for_it_49 == 2));
                            ///////////////////

                            _if_cond_48 = _if_cond_48_out;
                        }

                    }
                    if ((_if_cond_48 == 1)) {
                        {
                            double zre_ice;
                            double tmp_call_53;

                            {
                                double pre_ice_0_in_0 = pre_ice[((_for_it_50 + (klon * (_for_it_23 - 1))) - 1)];
                                double zre_ice_out;

                                ///////////////////
                                // Tasklet code (T_l916_c916)
                                zre_ice_out = pre_ice_0_in_0;
                                ///////////////////

                                zre_ice = zre_ice_out;
                            }
                            {
                                double zre_ice_0_in = zre_ice;
                                double tmp_call_53_out;

                                ///////////////////
                                // Tasklet code (T_l917_c917)
                                tmp_call_53_out = (dace::math::ipow(zre_ice_0_in, 1));
                                ///////////////////

                                tmp_call_53 = tmp_call_53_out;
                            }
                            {
                                double tmp_call_53_0_in = tmp_call_53;
                                double zvqx_out_0;

                                ///////////////////
                                // Tasklet code (T_l917_c917)
                                zvqx_out_0 = (0.002 * tmp_call_53_0_in);
                                ///////////////////

                                zvqx[1] = zvqx_out_0;
                            }

                        }
                    }
                    {
                        double zfall;

                        {
                            double zrho_0_in_0 = zrho[(_for_it_50 - 1)];
                            double zvqx_0_in_0 = zvqx[(_for_it_49 - 1)];
                            double zfall_out;

                            ///////////////////
                            // Tasklet code (T_l919_c919)
                            zfall_out = (zvqx_0_in_0 * zrho_0_in_0);
                            ///////////////////

                            zfall = zfall_out;
                        }
                        {
                            double zdtgdp_0_in_0 = zdtgdp[(_for_it_50 - 1)];
                            double zfall_0_in = zfall;
                            double zfallsink_out_0;

                            ///////////////////
                            // Tasklet code (T_l920_c920)
                            zfallsink_out_0 = (zdtgdp_0_in_0 * zfall_0_in);
                            ///////////////////

                            zfallsink[((_for_it_50 + (klon * (_for_it_49 - 1))) - 1)] = zfallsink_out_0;
                        }

                    }

                }
            }

        }
        for (_for_it_51 = 1; (_for_it_51 <= kfdia); _for_it_51 = (_for_it_51 + 1)) {

            _if_cond_49 = (zqpretot[(_for_it_51 - 1)] > 1e-14);
            if ((_if_cond_49 == 1)) {
                {
                    double tmp_call_55;
                    double tmp_call_54;
                    double tmp_call_56;
                    double tmp_call_57;
                    double tmp_call_58;
                    double tmp_arg_34;

                    {
                        double za_0_in_0 = za[((_for_it_51 + (klon * (_for_it_23 - 2))) - 1)];
                        double tmp_call_55_out;

                        ///////////////////
                        // Tasklet code (T_l926_c926)
                        tmp_call_55_out = min(za_0_in_0, 0.999999);
                        ///////////////////

                        tmp_call_55 = tmp_call_55_out;
                    }
                    {
                        double za_0_in_0 = za[((_for_it_51 + (klon * (_for_it_23 - 1))) - 1)];
                        double za_1_in_0 = za[((_for_it_51 + (klon * (_for_it_23 - 2))) - 1)];
                        double tmp_call_54_out;

                        ///////////////////
                        // Tasklet code (T_l926_c926)
                        tmp_call_54_out = max(za_0_in_0, za_1_in_0);
                        ///////////////////

                        tmp_call_54 = tmp_call_54_out;
                    }
                    {
                        double tmp_call_54_0_in = tmp_call_54;
                        double tmp_call_55_0_in = tmp_call_55;
                        double zcovptot_0_in_0 = zcovptot[(_for_it_51 - 1)];
                        double zcovptot_out_0;

                        ///////////////////
                        // Tasklet code (T_l926_c926)
                        zcovptot_out_0 = (1.0 - (((1.0 - zcovptot_0_in_0) * (1.0 - tmp_call_54_0_in)) / (1.0 - tmp_call_55_0_in)));
                        ///////////////////

                        zcovptot[(_for_it_51 - 1)] = zcovptot_out_0;
                    }
                    {
                        double ydecldp_0_in_rcovpmin = v_ydecldp_rcovpmin[0];
                        double zcovptot_0_in_0 = zcovptot[(_for_it_51 - 1)];
                        double tmp_call_56_out;

                        ///////////////////
                        // Tasklet code (T_l927_c927)
                        tmp_call_56_out = max(zcovptot_0_in_0, ydecldp_0_in_rcovpmin);
                        ///////////////////

                        tmp_call_56 = tmp_call_56_out;
                    }
                    {
                        double tmp_call_56_0_in = tmp_call_56;
                        double zcovptot_out_0;

                        ///////////////////
                        // Tasklet code (T_l927_c927)
                        zcovptot_out_0 = tmp_call_56_0_in;
                        ///////////////////

                        zcovptot[(_for_it_51 - 1)] = zcovptot_out_0;
                    }
                    {
                        double za_0_in_0 = za[((_for_it_51 + (klon * (_for_it_23 - 1))) - 1)];
                        double zcovptot_0_in_0 = zcovptot[(_for_it_51 - 1)];
                        double tmp_arg_34_out;

                        ///////////////////
                        // Tasklet code (T_l928_c928)
                        tmp_arg_34_out = (zcovptot_0_in_0 - za_0_in_0);
                        ///////////////////

                        tmp_arg_34 = tmp_arg_34_out;
                    }
                    {
                        double tmp_arg_34_0_in = tmp_arg_34;
                        double tmp_call_57_out;

                        ///////////////////
                        // Tasklet code (T_l928_c928)
                        tmp_call_57_out = max(0.0, tmp_arg_34_0_in);
                        ///////////////////

                        tmp_call_57 = tmp_call_57_out;
                    }
                    {
                        double tmp_call_57_0_in = tmp_call_57;
                        double zcovpclr_out_0;

                        ///////////////////
                        // Tasklet code (T_l928_c928)
                        zcovpclr_out_0 = tmp_call_57_0_in;
                        ///////////////////

                        zcovpclr[(_for_it_51 - 1)] = zcovpclr_out_0;
                    }
                    {
                        double zcovptot_0_in_0 = zcovptot[(_for_it_51 - 1)];
                        double zqxfg_0_in_0 = zqxfg[((_for_it_51 + (2 * klon)) - 1)];
                        double zraincld_out_0;

                        ///////////////////
                        // Tasklet code (T_l929_c929)
                        zraincld_out_0 = (zqxfg_0_in_0 / zcovptot_0_in_0);
                        ///////////////////

                        zraincld[(_for_it_51 - 1)] = zraincld_out_0;
                    }
                    {
                        double zcovptot_0_in_0 = zcovptot[(_for_it_51 - 1)];
                        double zqxfg_0_in_0 = zqxfg[((_for_it_51 + (3 * klon)) - 1)];
                        double zsnowcld_out_0;

                        ///////////////////
                        // Tasklet code (T_l930_c930)
                        zsnowcld_out_0 = (zqxfg_0_in_0 / zcovptot_0_in_0);
                        ///////////////////

                        zsnowcld[(_for_it_51 - 1)] = zsnowcld_out_0;
                    }
                    {
                        double zcovpmax_0_in_0 = zcovpmax[(_for_it_51 - 1)];
                        double zcovptot_0_in_0 = zcovptot[(_for_it_51 - 1)];
                        double tmp_call_58_out;

                        ///////////////////
                        // Tasklet code (T_l931_c931)
                        tmp_call_58_out = max(zcovptot_0_in_0, zcovpmax_0_in_0);
                        ///////////////////

                        tmp_call_58 = tmp_call_58_out;
                    }
                    {
                        double tmp_call_58_0_in = tmp_call_58;
                        double zcovpmax_out_0;

                        ///////////////////
                        // Tasklet code (T_l931_c931)
                        zcovpmax_out_0 = tmp_call_58_0_in;
                        ///////////////////

                        zcovpmax[(_for_it_51 - 1)] = zcovpmax_out_0;
                    }

                }
            } else {
                {

                    {
                        double zraincld_out_0;

                        ///////////////////
                        // Tasklet code (T_l933_c933)
                        zraincld_out_0 = 0.0;
                        ///////////////////

                        zraincld[(_for_it_51 - 1)] = zraincld_out_0;
                    }
                    {
                        double zsnowcld_out_0;

                        ///////////////////
                        // Tasklet code (T_l934_c934)
                        zsnowcld_out_0 = 0.0;
                        ///////////////////

                        zsnowcld[(_for_it_51 - 1)] = zsnowcld_out_0;
                    }
                    {
                        double zcovptot_out_0;

                        ///////////////////
                        // Tasklet code (T_l935_c935)
                        zcovptot_out_0 = 0.0;
                        ///////////////////

                        zcovptot[(_for_it_51 - 1)] = zcovptot_out_0;
                    }
                    {
                        double zcovpclr_out_0;

                        ///////////////////
                        // Tasklet code (T_l936_c936)
                        zcovpclr_out_0 = 0.0;
                        ///////////////////

                        zcovpclr[(_for_it_51 - 1)] = zcovpclr_out_0;
                    }
                    {
                        double zcovpmax_out_0;

                        ///////////////////
                        // Tasklet code (T_l937_c937)
                        zcovpmax_out_0 = 0.0;
                        ///////////////////

                        zcovpmax[(_for_it_51 - 1)] = zcovpmax_out_0;
                    }

                }
            }

        }
        for (_for_it_52 = 1; (_for_it_52 <= kfdia); _for_it_52 = (_for_it_52 + 1)) {
            {

                {
                    double ydcst_0_in_rtt = v_ydcst_rtt[0];
                    double ztp1_0_in_0 = ztp1[((_for_it_52 + (klon * (_for_it_23 - 1))) - 1)];
                    double _if_cond_50_out;

                    ///////////////////
                    // Tasklet code (T_l0_c0)
                    _if_cond_50_out = (ztp1_0_in_0 <= ydcst_0_in_rtt);
                    ///////////////////

                    _if_cond_50 = _if_cond_50_out;
                }

            }
            if ((_if_cond_50 == 1)) {

                _if_cond_51 = (zicecld[(_for_it_52 - 1)] > 1e-14);
                if ((_if_cond_51 == 1)) {
                    {
                        double tmp_call_59;
                        double tmp_arg_35;
                        double* v_ydecldp_rsnowlin2;
                        v_ydecldp_rsnowlin2 = (double*)(&(ydecldp->rsnowlin2));
                        double* v_ydecldp_rsnowlin1;
                        v_ydecldp_rsnowlin1 = (double*)(&(ydecldp->rsnowlin1));
                        int* v_ydecldp_laericeauto;
                        v_ydecldp_laericeauto = (int*)(&(ydecldp->laericeauto));

                        {
                            int ydecldp_0_in_laericeauto = v_ydecldp_laericeauto[0];
                            int _if_cond_52_out;

                            ///////////////////
                            // Tasklet code (T_l0_c0)
                            _if_cond_52_out = ydecldp_0_in_laericeauto;
                            ///////////////////

                            _if_cond_52 = _if_cond_52_out;
                        }
                        {
                            double ydcst_0_in_rtt = v_ydcst_rtt[0];
                            double ydecldp_0_in_rsnowlin2 = v_ydecldp_rsnowlin2[0];
                            double ztp1_0_in_0 = ztp1[((_for_it_52 + (klon * (_for_it_23 - 1))) - 1)];
                            double tmp_arg_35_out;

                            ///////////////////
                            // Tasklet code (T_l943_c943)
                            tmp_arg_35_out = (ydecldp_0_in_rsnowlin2 * (ztp1_0_in_0 - ydcst_0_in_rtt));
                            ///////////////////

                            tmp_arg_35 = tmp_arg_35_out;
                        }
                        {
                            double tmp_arg_35_0_in = tmp_arg_35;
                            double tmp_call_59_out;

                            ///////////////////
                            // Tasklet code (T_l943_c943)
                            tmp_call_59_out = exp(tmp_arg_35_0_in);
                            ///////////////////

                            tmp_call_59 = tmp_call_59_out;
                        }
                        {
                            double ptsphy_0_in = ptsphy;
                            double tmp_call_59_0_in = tmp_call_59;
                            double ydecldp_0_in_rsnowlin1 = v_ydecldp_rsnowlin1[0];
                            double zzco_out;

                            ///////////////////
                            // Tasklet code (T_l943_c943)
                            zzco_out = ((ptsphy_0_in * ydecldp_0_in_rsnowlin1) * tmp_call_59_0_in);
                            ///////////////////

                            zzco = zzco_out;
                        }

                    }
                    if ((_if_cond_52 == 1)) {
                        {
                            double tmp_call_60;
                            double tmp_arg_36;
                            double* v_ydecldp_rnice;
                            v_ydecldp_rnice = (double*)(&(ydecldp->rnice));

                            {
                                double picrit_aer_0_in_0 = picrit_aer[((_for_it_52 + (klon * (_for_it_23 - 1))) - 1)];
                                double zlcrit_out;

                                ///////////////////
                                // Tasklet code (T_l945_c945)
                                zlcrit_out = picrit_aer_0_in_0;
                                ///////////////////

                                zlcrit = zlcrit_out;
                            }
                            {
                                double pnice_0_in_0 = pnice[((_for_it_52 + (klon * (_for_it_23 - 1))) - 1)];
                                double ydecldp_0_in_rnice = v_ydecldp_rnice[0];
                                double tmp_arg_36_out;

                                ///////////////////
                                // Tasklet code (T_l946_c946)
                                tmp_arg_36_out = (ydecldp_0_in_rnice / pnice_0_in_0);
                                ///////////////////

                                tmp_arg_36 = tmp_arg_36_out;
                            }
                            {
                                double tmp_arg_36_0_in = tmp_arg_36;
                                double tmp_call_60_out;

                                ///////////////////
                                // Tasklet code (T_l946_c946)
                                tmp_call_60_out = dace::math::pow(tmp_arg_36_0_in, 0.333);
                                ///////////////////

                                tmp_call_60 = tmp_call_60_out;
                            }
                            {
                                double tmp_call_60_0_in = tmp_call_60;
                                double zzco_0_in = zzco;
                                double zzco_out;

                                ///////////////////
                                // Tasklet code (T_l946_c946)
                                zzco_out = (zzco_0_in * tmp_call_60_0_in);
                                ///////////////////

                                zzco = zzco_out;
                            }

                        }
                    } else {
                        {
                            double* v_ydecldp_rlcritsnow;
                            v_ydecldp_rlcritsnow = (double*)(&(ydecldp->rlcritsnow));

                            {
                                double ydecldp_0_in_rlcritsnow = v_ydecldp_rlcritsnow[0];
                                double zlcrit_out;

                                ///////////////////
                                // Tasklet code (T_l948_c948)
                                zlcrit_out = ydecldp_0_in_rlcritsnow;
                                ///////////////////

                                zlcrit = zlcrit_out;
                            }

                        }
                    }
                    {
                        double tmp_call_61;
                        double tmp_call_62;
                        double tmp_arg_37;
                        double tmp_arg_38;

                        {
                            double zicecld_0_in_0 = zicecld[(_for_it_52 - 1)];
                            double zlcrit_0_in = zlcrit;
                            double tmp_arg_37_out;

                            ///////////////////
                            // Tasklet code (T_l950_c950)
                            tmp_arg_37_out = (zicecld_0_in_0 / zlcrit_0_in);
                            ///////////////////

                            tmp_arg_37 = tmp_arg_37_out;
                        }
                        {
                            double tmp_arg_37_0_in = tmp_arg_37;
                            double tmp_call_62_out;

                            ///////////////////
                            // Tasklet code (T_l950_c950)
                            tmp_call_62_out = (dace::math::ipow(tmp_arg_37_0_in, 2));
                            ///////////////////

                            tmp_call_62 = tmp_call_62_out;
                        }
                        {
                            double tmp_call_62_0_in = tmp_call_62;
                            double tmp_arg_38_out;

                            ///////////////////
                            // Tasklet code (T_l950_c950)
                            tmp_arg_38_out = (- tmp_call_62_0_in);
                            ///////////////////

                            tmp_arg_38 = tmp_arg_38_out;
                        }
                        {
                            double tmp_arg_38_0_in = tmp_arg_38;
                            double tmp_call_61_out;

                            ///////////////////
                            // Tasklet code (T_l950_c950)
                            tmp_call_61_out = exp(tmp_arg_38_0_in);
                            ///////////////////

                            tmp_call_61 = tmp_call_61_out;
                        }
                        {
                            double tmp_call_61_0_in = tmp_call_61;
                            double zzco_0_in = zzco;
                            double zsnowaut_out_0;

                            ///////////////////
                            // Tasklet code (T_l950_c950)
                            zsnowaut_out_0 = (zzco_0_in * (1.0 - tmp_call_61_0_in));
                            ///////////////////

                            zsnowaut[(_for_it_52 - 1)] = zsnowaut_out_0;
                        }
                        {
                            double zsnowaut_0_in_0 = zsnowaut[(_for_it_52 - 1)];
                            double zsolqb_0_in_0 = zsolqb[((_for_it_52 + (8 * klon)) - 1)];
                            double zsolqb_out_0;

                            ///////////////////
                            // Tasklet code (T_l951_c951)
                            zsolqb_out_0 = (zsolqb_0_in_0 + zsnowaut_0_in_0);
                            ///////////////////

                            zsolqb[((_for_it_52 + (8 * klon)) - 1)] = zsolqb_out_0;
                        }

                    }
                }
            }
            _if_cond_53 = (zliqcld[(_for_it_52 - 1)] > 1e-14);
            if ((_if_cond_53 == 1)) {

                _if_cond_54 = (plsm[(_for_it_52 - 1)] > 0.5);
                if ((_if_cond_54 == 1)) {
                    {
                        double* v_ydecldp_rcl_kk_cloud_num_land;
                        v_ydecldp_rcl_kk_cloud_num_land = (double*)(&(ydecldp->rcl_kk_cloud_num_land));
                        double* v_ydecldp_rclcrit_land;
                        v_ydecldp_rclcrit_land = (double*)(&(ydecldp->rclcrit_land));

                        {
                            double ydecldp_0_in_rcl_kk_cloud_num_land = v_ydecldp_rcl_kk_cloud_num_land[0];
                            double zconst_out;

                            ///////////////////
                            // Tasklet code (T_l956_c956)
                            zconst_out = ydecldp_0_in_rcl_kk_cloud_num_land;
                            ///////////////////

                            zconst = zconst_out;
                        }
                        {
                            double ydecldp_0_in_rclcrit_land = v_ydecldp_rclcrit_land[0];
                            double zlcrit_out;

                            ///////////////////
                            // Tasklet code (T_l957_c957)
                            zlcrit_out = ydecldp_0_in_rclcrit_land;
                            ///////////////////

                            zlcrit = zlcrit_out;
                        }

                    }
                } else {
                    {
                        double* v_ydecldp_rcl_kk_cloud_num_sea;
                        v_ydecldp_rcl_kk_cloud_num_sea = (double*)(&(ydecldp->rcl_kk_cloud_num_sea));
                        double* v_ydecldp_rclcrit_sea;
                        v_ydecldp_rclcrit_sea = (double*)(&(ydecldp->rclcrit_sea));

                        {
                            double ydecldp_0_in_rcl_kk_cloud_num_sea = v_ydecldp_rcl_kk_cloud_num_sea[0];
                            double zconst_out;

                            ///////////////////
                            // Tasklet code (T_l959_c959)
                            zconst_out = ydecldp_0_in_rcl_kk_cloud_num_sea;
                            ///////////////////

                            zconst = zconst_out;
                        }
                        {
                            double ydecldp_0_in_rclcrit_sea = v_ydecldp_rclcrit_sea[0];
                            double zlcrit_out;

                            ///////////////////
                            // Tasklet code (T_l960_c960)
                            zlcrit_out = ydecldp_0_in_rclcrit_sea;
                            ///////////////////

                            zlcrit = zlcrit_out;
                        }

                    }
                }
                _if_cond_55 = (zliqcld[(_for_it_52 - 1)] > zlcrit);
                if ((_if_cond_55 == 1)) {
                    {
                        double tmp_call_64;
                        double tmp_call_63;
                        double tmp_call_65;
                        double* v_ydecldp_rcl_kkbaun;
                        v_ydecldp_rcl_kkbaun = (double*)(&(ydecldp->rcl_kkbaun));
                        double* v_ydecldp_rcl_kkbauq;
                        v_ydecldp_rcl_kkbauq = (double*)(&(ydecldp->rcl_kkbauq));
                        double* v_ydecldp_rcl_kkaau;
                        v_ydecldp_rcl_kkaau = (double*)(&(ydecldp->rcl_kkaau));

                        {
                            double ydecldp_0_in_rcl_kkbaun = v_ydecldp_rcl_kkbaun[0];
                            double zconst_0_in = zconst;
                            double tmp_call_64_out;

                            ///////////////////
                            // Tasklet code (T_l963_c963)
                            tmp_call_64_out = dace::math::pow(zconst_0_in, ydecldp_0_in_rcl_kkbaun);
                            ///////////////////

                            tmp_call_64 = tmp_call_64_out;
                        }
                        {
                            double ydecldp_0_in_rcl_kkbauq = v_ydecldp_rcl_kkbauq[0];
                            double zliqcld_0_in_0 = zliqcld[(_for_it_52 - 1)];
                            double tmp_call_63_out;

                            ///////////////////
                            // Tasklet code (T_l963_c963)
                            tmp_call_63_out = dace::math::pow(zliqcld_0_in_0, ydecldp_0_in_rcl_kkbauq);
                            ///////////////////

                            tmp_call_63 = tmp_call_63_out;
                        }
                        {
                            double ptsphy_0_in = ptsphy;
                            double tmp_call_63_0_in = tmp_call_63;
                            double tmp_call_64_0_in = tmp_call_64;
                            double ydecldp_0_in_rcl_kkaau = v_ydecldp_rcl_kkaau[0];
                            double za_0_in_0 = za[((_for_it_52 + (klon * (_for_it_23 - 1))) - 1)];
                            double zrainaut_out_0;

                            ///////////////////
                            // Tasklet code (T_l963_c963)
                            zrainaut_out_0 = (((((1.5 * za_0_in_0) * ptsphy_0_in) * ydecldp_0_in_rcl_kkaau) * tmp_call_63_0_in) * tmp_call_64_0_in);
                            ///////////////////

                            zrainaut[(_for_it_52 - 1)] = zrainaut_out_0;
                        }
                        {
                            double zqxfg_0_in_0 = zqxfg[(_for_it_52 - 1)];
                            double zrainaut_0_in_0 = zrainaut[(_for_it_52 - 1)];
                            double tmp_call_65_out;

                            ///////////////////
                            // Tasklet code (T_l964_c964)
                            tmp_call_65_out = min(zrainaut_0_in_0, zqxfg_0_in_0);
                            ///////////////////

                            tmp_call_65 = tmp_call_65_out;
                        }
                        {
                            double tmp_call_65_0_in = tmp_call_65;
                            double zrainaut_out_0;

                            ///////////////////
                            // Tasklet code (T_l964_c964)
                            zrainaut_out_0 = tmp_call_65_0_in;
                            ///////////////////

                            zrainaut[(_for_it_52 - 1)] = zrainaut_out_0;
                        }
                        {
                            double zrainaut_0_in_0 = zrainaut[(_for_it_52 - 1)];
                            double _if_cond_56_out;

                            ///////////////////
                            // Tasklet code (T_l965_c965)
                            _if_cond_56_out = (zrainaut_0_in_0 < 1e-14);
                            ///////////////////

                            _if_cond_56 = _if_cond_56_out;
                        }

                    }
                    if ((_if_cond_56 == 1)) {
                        {

                            {
                                double zrainaut_out_0;

                                ///////////////////
                                // Tasklet code (T_l965_c965)
                                zrainaut_out_0 = 0.0;
                                ///////////////////

                                zrainaut[(_for_it_52 - 1)] = zrainaut_out_0;
                            }

                        }
                    }
                    {
                        double tmp_call_66;
                        double tmp_call_67;
                        double tmp_arg_39;
                        double* v_ydecldp_rcl_kkbac;
                        v_ydecldp_rcl_kkbac = (double*)(&(ydecldp->rcl_kkbac));
                        double* v_ydecldp_rcl_kkaac;
                        v_ydecldp_rcl_kkaac = (double*)(&(ydecldp->rcl_kkaac));

                        {
                            double zliqcld_0_in_0 = zliqcld[(_for_it_52 - 1)];
                            double zraincld_0_in_0 = zraincld[(_for_it_52 - 1)];
                            double tmp_arg_39_out;

                            ///////////////////
                            // Tasklet code (T_l966_c966)
                            tmp_arg_39_out = (zliqcld_0_in_0 * zraincld_0_in_0);
                            ///////////////////

                            tmp_arg_39 = tmp_arg_39_out;
                        }
                        {
                            double tmp_arg_39_0_in = tmp_arg_39;
                            double ydecldp_0_in_rcl_kkbac = v_ydecldp_rcl_kkbac[0];
                            double tmp_call_66_out;

                            ///////////////////
                            // Tasklet code (T_l966_c966)
                            tmp_call_66_out = dace::math::pow(tmp_arg_39_0_in, ydecldp_0_in_rcl_kkbac);
                            ///////////////////

                            tmp_call_66 = tmp_call_66_out;
                        }
                        {
                            double ptsphy_0_in = ptsphy;
                            double tmp_call_66_0_in = tmp_call_66;
                            double ydecldp_0_in_rcl_kkaac = v_ydecldp_rcl_kkaac[0];
                            double za_0_in_0 = za[((_for_it_52 + (klon * (_for_it_23 - 1))) - 1)];
                            double zrainacc_out_0;

                            ///////////////////
                            // Tasklet code (T_l966_c966)
                            zrainacc_out_0 = ((((2.0 * za_0_in_0) * ptsphy_0_in) * ydecldp_0_in_rcl_kkaac) * tmp_call_66_0_in);
                            ///////////////////

                            zrainacc[(_for_it_52 - 1)] = zrainacc_out_0;
                        }
                        {
                            double zqxfg_0_in_0 = zqxfg[(_for_it_52 - 1)];
                            double zrainacc_0_in_0 = zrainacc[(_for_it_52 - 1)];
                            double tmp_call_67_out;

                            ///////////////////
                            // Tasklet code (T_l967_c967)
                            tmp_call_67_out = min(zrainacc_0_in_0, zqxfg_0_in_0);
                            ///////////////////

                            tmp_call_67 = tmp_call_67_out;
                        }
                        {
                            double tmp_call_67_0_in = tmp_call_67;
                            double zrainacc_out_0;

                            ///////////////////
                            // Tasklet code (T_l967_c967)
                            zrainacc_out_0 = tmp_call_67_0_in;
                            ///////////////////

                            zrainacc[(_for_it_52 - 1)] = zrainacc_out_0;
                        }
                        {
                            double zrainacc_0_in_0 = zrainacc[(_for_it_52 - 1)];
                            double _if_cond_57_out;

                            ///////////////////
                            // Tasklet code (T_l968_c968)
                            _if_cond_57_out = (zrainacc_0_in_0 < 1e-14);
                            ///////////////////

                            _if_cond_57 = _if_cond_57_out;
                        }

                    }
                    if ((_if_cond_57 == 1)) {
                        {

                            {
                                double zrainacc_out_0;

                                ///////////////////
                                // Tasklet code (T_l968_c968)
                                zrainacc_out_0 = 0.0;
                                ///////////////////

                                zrainacc[(_for_it_52 - 1)] = zrainacc_out_0;
                            }

                        }
                    }
                } else {
                    {

                        {
                            double zrainaut_out_0;

                            ///////////////////
                            // Tasklet code (T_l970_c970)
                            zrainaut_out_0 = 0.0;
                            ///////////////////

                            zrainaut[(_for_it_52 - 1)] = zrainaut_out_0;
                        }
                        {
                            double zrainacc_out_0;

                            ///////////////////
                            // Tasklet code (T_l971_c971)
                            zrainacc_out_0 = 0.0;
                            ///////////////////

                            zrainacc[(_for_it_52 - 1)] = zrainacc_out_0;
                        }

                    }
                }
                {

                    {
                        double ydcst_0_in_rtt = v_ydcst_rtt[0];
                        double ztp1_0_in_0 = ztp1[((_for_it_52 + (klon * (_for_it_23 - 1))) - 1)];
                        double _if_cond_58_out;

                        ///////////////////
                        // Tasklet code (T_l0_c0)
                        _if_cond_58_out = (ztp1_0_in_0 <= ydcst_0_in_rtt);
                        ///////////////////

                        _if_cond_58 = _if_cond_58_out;
                    }

                }
                if ((_if_cond_58 == 1)) {
                    {

                        {
                            double zrainaut_0_in_0 = zrainaut[(_for_it_52 - 1)];
                            double zsolqa_0_in_0 = zsolqa[((_for_it_52 + (3 * klon)) - 1)];
                            double zsolqa_out_0;

                            ///////////////////
                            // Tasklet code (T_l974_c974)
                            zsolqa_out_0 = (zsolqa_0_in_0 + zrainaut_0_in_0);
                            ///////////////////

                            zsolqa[((_for_it_52 + (3 * klon)) - 1)] = zsolqa_out_0;
                        }
                        {
                            double zrainacc_0_in_0 = zrainacc[(_for_it_52 - 1)];
                            double zsolqa_0_in_0 = zsolqa[((_for_it_52 + (3 * klon)) - 1)];
                            double zsolqa_out_0;

                            ///////////////////
                            // Tasklet code (T_l975_c975)
                            zsolqa_out_0 = (zsolqa_0_in_0 + zrainacc_0_in_0);
                            ///////////////////

                            zsolqa[((_for_it_52 + (3 * klon)) - 1)] = zsolqa_out_0;
                        }
                        {
                            double zrainaut_0_in_0 = zrainaut[(_for_it_52 - 1)];
                            double zsolqa_0_in_0 = zsolqa[((_for_it_52 + (15 * klon)) - 1)];
                            double zsolqa_out_0;

                            ///////////////////
                            // Tasklet code (T_l976_c976)
                            zsolqa_out_0 = (zsolqa_0_in_0 - zrainaut_0_in_0);
                            ///////////////////

                            zsolqa[((_for_it_52 + (15 * klon)) - 1)] = zsolqa_out_0;
                        }
                        {
                            double zrainacc_0_in_0 = zrainacc[(_for_it_52 - 1)];
                            double zsolqa_0_in_0 = zsolqa[((_for_it_52 + (15 * klon)) - 1)];
                            double zsolqa_out_0;

                            ///////////////////
                            // Tasklet code (T_l977_c977)
                            zsolqa_out_0 = (zsolqa_0_in_0 - zrainacc_0_in_0);
                            ///////////////////

                            zsolqa[((_for_it_52 + (15 * klon)) - 1)] = zsolqa_out_0;
                        }

                    }
                } else {
                    {

                        {
                            double zrainaut_0_in_0 = zrainaut[(_for_it_52 - 1)];
                            double zsolqa_0_in_0 = zsolqa[((_for_it_52 + (2 * klon)) - 1)];
                            double zsolqa_out_0;

                            ///////////////////
                            // Tasklet code (T_l979_c979)
                            zsolqa_out_0 = (zsolqa_0_in_0 + zrainaut_0_in_0);
                            ///////////////////

                            zsolqa[((_for_it_52 + (2 * klon)) - 1)] = zsolqa_out_0;
                        }
                        {
                            double zrainacc_0_in_0 = zrainacc[(_for_it_52 - 1)];
                            double zsolqa_0_in_0 = zsolqa[((_for_it_52 + (2 * klon)) - 1)];
                            double zsolqa_out_0;

                            ///////////////////
                            // Tasklet code (T_l980_c980)
                            zsolqa_out_0 = (zsolqa_0_in_0 + zrainacc_0_in_0);
                            ///////////////////

                            zsolqa[((_for_it_52 + (2 * klon)) - 1)] = zsolqa_out_0;
                        }
                        {
                            double zrainaut_0_in_0 = zrainaut[(_for_it_52 - 1)];
                            double zsolqa_0_in_0 = zsolqa[((_for_it_52 + (10 * klon)) - 1)];
                            double zsolqa_out_0;

                            ///////////////////
                            // Tasklet code (T_l981_c981)
                            zsolqa_out_0 = (zsolqa_0_in_0 - zrainaut_0_in_0);
                            ///////////////////

                            zsolqa[((_for_it_52 + (10 * klon)) - 1)] = zsolqa_out_0;
                        }
                        {
                            double zrainacc_0_in_0 = zrainacc[(_for_it_52 - 1)];
                            double zsolqa_0_in_0 = zsolqa[((_for_it_52 + (10 * klon)) - 1)];
                            double zsolqa_out_0;

                            ///////////////////
                            // Tasklet code (T_l982_c982)
                            zsolqa_out_0 = (zsolqa_0_in_0 - zrainacc_0_in_0);
                            ///////////////////

                            zsolqa[((_for_it_52 + (10 * klon)) - 1)] = zsolqa_out_0;
                        }

                    }
                }
            }

        }
        for (_for_it_53 = 1; (_for_it_53 <= kfdia); _for_it_53 = (_for_it_53 + 1)) {
            {

                {
                    double ydcst_0_in_rtt = v_ydcst_rtt[0];
                    double zliqcld_0_in_0 = zliqcld[(_for_it_53 - 1)];
                    double ztp1_0_in_0 = ztp1[((_for_it_53 + (klon * (_for_it_23 - 1))) - 1)];
                    double _if_cond_59_out;

                    ///////////////////
                    // Tasklet code (T_l0_c0)
                    _if_cond_59_out = ((ztp1_0_in_0 <= ydcst_0_in_rtt) && (zliqcld_0_in_0 > 1e-14));
                    ///////////////////

                    _if_cond_59 = _if_cond_59_out;
                }

            }
            if ((_if_cond_59 == 1)) {

                _if_cond_60 = ((zsnowcld[(_for_it_53 - 1)] > 1e-14) && (zcovptot[(_for_it_53 - 1)] > 0.01));
                {
                    double tmp_arg_40;

                    {
                        double ydecldp_0_in_rdensref = v_ydecldp_rdensref[0];
                        double zrho_0_in_0 = zrho[(_for_it_53 - 1)];
                        double tmp_arg_40_out;

                        ///////////////////
                        // Tasklet code (T_l988_c988)
                        tmp_arg_40_out = (ydecldp_0_in_rdensref / zrho_0_in_0);
                        ///////////////////

                        tmp_arg_40 = tmp_arg_40_out;
                    }
                    {
                        double tmp_arg_40_0_in = tmp_arg_40;
                        double zfallcorr_out;

                        ///////////////////
                        // Tasklet code (T_l988_c988)
                        zfallcorr_out = dace::math::pow(tmp_arg_40_0_in, 0.4);
                        ///////////////////

                        zfallcorr = zfallcorr_out;
                    }

                }
                if ((_if_cond_60 == 1)) {
                    {
                        double *zsnowrime;
                        zsnowrime = new double DACE_ALIGN(64)[klon];
                        double tmp_call_68;
                        double tmp_call_69;
                        double tmp_arg_41;
                        double* v_ydecldp_rcl_const1s;
                        v_ydecldp_rcl_const1s = (double*)(&(ydecldp->rcl_const1s));
                        double* v_ydecldp_rcl_const8s;
                        v_ydecldp_rcl_const8s = (double*)(&(ydecldp->rcl_const8s));
                        double* v_ydecldp_rcl_const7s;
                        v_ydecldp_rcl_const7s = (double*)(&(ydecldp->rcl_const7s));

                        {
                            double ydecldp_0_in_rcl_const1s = v_ydecldp_rcl_const1s[0];
                            double zrho_0_in_0 = zrho[(_for_it_53 - 1)];
                            double zsnowcld_0_in_0 = zsnowcld[(_for_it_53 - 1)];
                            double tmp_arg_41_out;

                            ///////////////////
                            // Tasklet code (T_l990_c990)
                            tmp_arg_41_out = ((zrho_0_in_0 * zsnowcld_0_in_0) * ydecldp_0_in_rcl_const1s);
                            ///////////////////

                            tmp_arg_41 = tmp_arg_41_out;
                        }
                        {
                            double tmp_arg_41_0_in = tmp_arg_41;
                            double ydecldp_0_in_rcl_const8s = v_ydecldp_rcl_const8s[0];
                            double tmp_call_68_out;

                            ///////////////////
                            // Tasklet code (T_l990_c990)
                            tmp_call_68_out = dace::math::pow(tmp_arg_41_0_in, ydecldp_0_in_rcl_const8s);
                            ///////////////////

                            tmp_call_68 = tmp_call_68_out;
                        }
                        {
                            double ptsphy_0_in = ptsphy;
                            double tmp_call_68_0_in = tmp_call_68;
                            double ydecldp_0_in_rcl_const7s = v_ydecldp_rcl_const7s[0];
                            double zcovptot_0_in_0 = zcovptot[(_for_it_53 - 1)];
                            double zfallcorr_0_in = zfallcorr;
                            double zsnowrime_out_0;

                            ///////////////////
                            // Tasklet code (T_l990_c990)
                            zsnowrime_out_0 = (((((0.3 * zcovptot_0_in_0) * ptsphy_0_in) * ydecldp_0_in_rcl_const7s) * zfallcorr_0_in) * tmp_call_68_0_in);
                            ///////////////////

                            zsnowrime[(_for_it_53 - 1)] = zsnowrime_out_0;
                        }
                        {
                            double zsnowrime_0_in_0 = zsnowrime[(_for_it_53 - 1)];
                            double tmp_call_69_out;

                            ///////////////////
                            // Tasklet code (T_l991_c991)
                            tmp_call_69_out = min(zsnowrime_0_in_0, 1.0);
                            ///////////////////

                            tmp_call_69 = tmp_call_69_out;
                        }
                        {
                            double tmp_call_69_0_in = tmp_call_69;
                            double zsnowrime_out_0;

                            ///////////////////
                            // Tasklet code (T_l991_c991)
                            zsnowrime_out_0 = tmp_call_69_0_in;
                            ///////////////////

                            zsnowrime[(_for_it_53 - 1)] = zsnowrime_out_0;
                        }
                        {
                            double zsnowrime_0_in_0 = zsnowrime[(_for_it_53 - 1)];
                            double zsolqb_0_in_0 = zsolqb[((_for_it_53 + (3 * klon)) - 1)];
                            double zsolqb_out_0;

                            ///////////////////
                            // Tasklet code (T_l992_c992)
                            zsolqb_out_0 = (zsolqb_0_in_0 + zsnowrime_0_in_0);
                            ///////////////////

                            zsolqb[((_for_it_53 + (3 * klon)) - 1)] = zsolqb_out_0;
                        }
                        delete[] zsnowrime;

                    }
                }
            }

        }
        for (_for_it_54 = 1; (_for_it_54 <= kfdia); _for_it_54 = (_for_it_54 + 1)) {
            {

                {
                    double zmeltmax_out_0;

                    ///////////////////
                    // Tasklet code (T_l998_c998)
                    zmeltmax_out_0 = 0.0;
                    ///////////////////

                    zmeltmax[(_for_it_54 - 1)] = zmeltmax_out_0;
                }
                {
                    double zqxfg_0_in_0 = zqxfg[((_for_it_54 + klon) - 1)];
                    double zqxfg_1_in_0 = zqxfg[((_for_it_54 + (3 * klon)) - 1)];
                    double zicetot_out_0;

                    ///////////////////
                    // Tasklet code (T_l997_c997)
                    zicetot_out_0 = (zqxfg_0_in_0 + zqxfg_1_in_0);
                    ///////////////////

                    zicetot[(_for_it_54 - 1)] = zicetot_out_0;
                }
                {
                    double ydcst_0_in_rtt = v_ydcst_rtt[0];
                    double zicetot_0_in_0 = zicetot[(_for_it_54 - 1)];
                    double ztp1_0_in_0 = ztp1[((_for_it_54 + (klon * (_for_it_23 - 1))) - 1)];
                    double _if_cond_61_out;

                    ///////////////////
                    // Tasklet code (T_l0_c0)
                    _if_cond_61_out = ((zicetot_0_in_0 > 1e-14) && (ztp1_0_in_0 > ydcst_0_in_rtt));
                    ///////////////////

                    _if_cond_61 = _if_cond_61_out;
                }

            }
            if ((_if_cond_61 == 1)) {
                {
                    double ztdmtw0;
                    double tmp_call_70;
                    double tmp_arg_42;
                    double tmp_arg_43;
                    double tmp_arg_44;

                    {
                        double zqsice_0_in_0 = zqsice[((_for_it_54 + (klon * (_for_it_23 - 1))) - 1)];
                        double zqx_0_in_0 = zqx[(((_for_it_54 + ((4 * klev) * klon)) + (klon * (_for_it_23 - 1))) - 1)];
                        double tmp_arg_42_out;

                        ///////////////////
                        // Tasklet code (T_l1000_c1000)
                        tmp_arg_42_out = (zqsice_0_in_0 - zqx_0_in_0);
                        ///////////////////

                        tmp_arg_42 = tmp_arg_42_out;
                    }
                    {
                        double tmp_arg_42_0_in = tmp_arg_42;
                        double zsubsat_out;

                        ///////////////////
                        // Tasklet code (T_l1000_c1000)
                        zsubsat_out = max(tmp_arg_42_0_in, 0.0);
                        ///////////////////

                        zsubsat = zsubsat_out;
                    }
                    {
                        double pap_0_in_0 = pap[((_for_it_54 + (klon * (_for_it_23 - 1))) - 1)];
                        double ydcst_0_in_rtt = v_ydcst_rtt[0];
                        double zsubsat_0_in = zsubsat;
                        double ztp1_0_in_0 = ztp1[((_for_it_54 + (klon * (_for_it_23 - 1))) - 1)];
                        double ztp1_1_in_0 = ztp1[((_for_it_54 + (klon * (_for_it_23 - 1))) - 1)];
                        double ztdmtw0_out;

                        ///////////////////
                        // Tasklet code (T_l1001_c1001)
                        ztdmtw0_out = ((ztp1_0_in_0 - ydcst_0_in_rtt) - (zsubsat_0_in * ((1329.31 + (0.0074615 * (pap_0_in_0 - 85000.0))) - (40.637 * (ztp1_1_in_0 - 275.0)))));
                        ///////////////////

                        ztdmtw0 = ztdmtw0_out;
                    }
                    {
                        double ptsphy_0_in = ptsphy;
                        double ydecldp_0_in_rtaumel = v_ydecldp_rtaumel[0];
                        double ztdmtw0_0_in = ztdmtw0;
                        double tmp_arg_43_out;

                        ///////////////////
                        // Tasklet code (T_l1002_c1002)
                        tmp_arg_43_out = ((ptsphy_0_in * (1.0 + (0.5 * ztdmtw0_0_in))) / ydecldp_0_in_rtaumel);
                        ///////////////////

                        tmp_arg_43 = tmp_arg_43_out;
                    }
                    {
                        double tmp_arg_43_0_in = tmp_arg_43;
                        double zcons1_out;

                        ///////////////////
                        // Tasklet code (T_l1002_c1002)
                        zcons1_out = abs(tmp_arg_43_0_in);
                        ///////////////////

                        zcons1 = zcons1_out;
                    }
                    {
                        double zcons1_0_in = zcons1;
                        double zrldcp_0_in = zrldcp;
                        double ztdmtw0_0_in = ztdmtw0;
                        double tmp_arg_44_out;

                        ///////////////////
                        // Tasklet code (T_l1003_c1003)
                        tmp_arg_44_out = ((ztdmtw0_0_in * zcons1_0_in) * zrldcp_0_in);
                        ///////////////////

                        tmp_arg_44 = tmp_arg_44_out;
                    }
                    {
                        double tmp_arg_44_0_in = tmp_arg_44;
                        double tmp_call_70_out;

                        ///////////////////
                        // Tasklet code (T_l1003_c1003)
                        tmp_call_70_out = max(tmp_arg_44_0_in, 0.0);
                        ///////////////////

                        tmp_call_70 = tmp_call_70_out;
                    }
                    {
                        double tmp_call_70_0_in = tmp_call_70;
                        double zmeltmax_out_0;

                        ///////////////////
                        // Tasklet code (T_l1003_c1003)
                        zmeltmax_out_0 = tmp_call_70_0_in;
                        ///////////////////

                        zmeltmax[(_for_it_54 - 1)] = zmeltmax_out_0;
                    }

                }
            }

        }
        for (_for_it_55 = 1; (_for_it_55 <= 5); _for_it_55 = (_for_it_55 + 1)) {

            _if_cond_62 = (iphase[(_for_it_55 - 1)] == 2);
            if ((_if_cond_62 == 1)) {

                jnn = imelt[(_for_it_55 - 1)];
                for (_for_it_56 = 1; (_for_it_56 <= kfdia); _for_it_56 = (_for_it_56 + 1)) {

                    _if_cond_63 = ((zmeltmax[(_for_it_56 - 1)] > 1e-14) && (zicetot[(_for_it_56 - 1)] > 1e-14));
                    if ((_if_cond_63 == 1)) {
                        {
                            double zmelt;
                            double tmp_arg_45;

                            {
                                double zicetot_0_in_0 = zicetot[(_for_it_56 - 1)];
                                double zqxfg_0_in_0 = zqxfg[((_for_it_56 + (klon * (_for_it_55 - 1))) - 1)];
                                double zalfa_out;

                                ///////////////////
                                // Tasklet code (T_l1011_c1011)
                                zalfa_out = (zqxfg_0_in_0 / zicetot_0_in_0);
                                ///////////////////

                                zalfa = zalfa_out;
                            }
                            {
                                double zalfa_0_in = zalfa;
                                double zmeltmax_0_in_0 = zmeltmax[(_for_it_56 - 1)];
                                double tmp_arg_45_out;

                                ///////////////////
                                // Tasklet code (T_l1012_c1012)
                                tmp_arg_45_out = (zalfa_0_in * zmeltmax_0_in_0);
                                ///////////////////

                                tmp_arg_45 = tmp_arg_45_out;
                            }
                            {
                                double tmp_arg_45_0_in = tmp_arg_45;
                                double zqxfg_0_in_0 = zqxfg[((_for_it_56 + (klon * (_for_it_55 - 1))) - 1)];
                                double zmelt_out;

                                ///////////////////
                                // Tasklet code (T_l1012_c1012)
                                zmelt_out = min(zqxfg_0_in_0, tmp_arg_45_0_in);
                                ///////////////////

                                zmelt = zmelt_out;
                            }
                            {
                                double zmelt_0_in = zmelt;
                                double zqxfg_0_in_0 = zqxfg[((_for_it_56 + (klon * (_for_it_55 - 1))) - 1)];
                                double zqxfg_out_0;

                                ///////////////////
                                // Tasklet code (T_l1013_c1013)
                                zqxfg_out_0 = (zqxfg_0_in_0 - zmelt_0_in);
                                ///////////////////

                                zqxfg[((_for_it_56 + (klon * (_for_it_55 - 1))) - 1)] = zqxfg_out_0;
                            }
                            {
                                double zmelt_0_in = zmelt;
                                double zqxfg_0_in_0 = zqxfg[((_for_it_56 + (klon * (jnn - 1))) - 1)];
                                double zqxfg_out_0;

                                ///////////////////
                                // Tasklet code (T_l1014_c1014)
                                zqxfg_out_0 = (zqxfg_0_in_0 + zmelt_0_in);
                                ///////////////////

                                zqxfg[((_for_it_56 + (klon * (jnn - 1))) - 1)] = zqxfg_out_0;
                            }
                            {
                                double zmelt_0_in = zmelt;
                                double zsolqa_0_in_0 = zsolqa[(((_for_it_56 + ((5 * klon) * (_for_it_55 - 1))) + (klon * (jnn - 1))) - 1)];
                                double zsolqa_out_0;

                                ///////////////////
                                // Tasklet code (T_l1015_c1015)
                                zsolqa_out_0 = (zsolqa_0_in_0 + zmelt_0_in);
                                ///////////////////

                                zsolqa[(((_for_it_56 + ((5 * klon) * (_for_it_55 - 1))) + (klon * (jnn - 1))) - 1)] = zsolqa_out_0;
                            }
                            {
                                double zmelt_0_in = zmelt;
                                double zsolqa_0_in_0 = zsolqa[(((_for_it_56 + (klon * (_for_it_55 - 1))) + ((5 * klon) * (jnn - 1))) - 1)];
                                double zsolqa_out_0;

                                ///////////////////
                                // Tasklet code (T_l1016_c1016)
                                zsolqa_out_0 = (zsolqa_0_in_0 - zmelt_0_in);
                                ///////////////////

                                zsolqa[(((_for_it_56 + (klon * (_for_it_55 - 1))) + ((5 * klon) * (jnn - 1))) - 1)] = zsolqa_out_0;
                            }

                        }
                    }

                }
            }

        }
        for (_for_it_57 = 1; (_for_it_57 <= kfdia); _for_it_57 = (_for_it_57 + 1)) {

            _if_cond_64 = (zqx[(((_for_it_57 + ((2 * klev) * klon)) + (klon * (_for_it_23 - 1))) - 1)] > 1e-14);
            if ((_if_cond_64 == 1)) {
                {

                    {
                        double ydcst_0_in_rtt = v_ydcst_rtt[0];
                        double ydcst_1_in_rtt = v_ydcst_rtt[0];
                        double ztp1_0_in_0 = ztp1[((_for_it_57 + (klon * (_for_it_23 - 1))) - 1)];
                        double ztp1_1_in_0 = ztp1[((_for_it_57 + (klon * (_for_it_23 - 2))) - 1)];
                        double _if_cond_65_out;

                        ///////////////////
                        // Tasklet code (T_l0_c0)
                        _if_cond_65_out = ((ztp1_0_in_0 <= ydcst_0_in_rtt) && (ztp1_1_in_0 > ydcst_1_in_rtt));
                        ///////////////////

                        _if_cond_65 = _if_cond_65_out;
                    }

                }
                if ((_if_cond_65 == 1)) {
                    {
                        double tmp_call_71;
                        double tmp_arg_46;

                        {
                            double zqx_0_in_0 = zqx[(((_for_it_57 + ((3 * klev) * klon)) + (klon * (_for_it_23 - 1))) - 1)];
                            double zqx_1_in_0 = zqx[(((_for_it_57 + ((2 * klev) * klon)) + (klon * (_for_it_23 - 1))) - 1)];
                            double tmp_arg_46_out;

                            ///////////////////
                            // Tasklet code (T_l1024_c1024)
                            tmp_arg_46_out = (zqx_0_in_0 + zqx_1_in_0);
                            ///////////////////

                            tmp_arg_46 = tmp_arg_46_out;
                        }
                        {
                            double tmp_arg_46_0_in = tmp_arg_46;
                            double zepsec_0_in = zepsec;
                            double tmp_call_71_out;

                            ///////////////////
                            // Tasklet code (T_l1024_c1024)
                            tmp_call_71_out = max(tmp_arg_46_0_in, zepsec_0_in);
                            ///////////////////

                            tmp_call_71 = tmp_call_71_out;
                        }
                        {
                            double tmp_call_71_0_in = tmp_call_71;
                            double zqpretot_out_0;

                            ///////////////////
                            // Tasklet code (T_l1024_c1024)
                            zqpretot_out_0 = tmp_call_71_0_in;
                            ///////////////////

                            zqpretot[(_for_it_57 - 1)] = zqpretot_out_0;
                        }
                        {
                            double zqpretot_0_in_0 = zqpretot[(_for_it_57 - 1)];
                            double zqx_0_in_0 = zqx[(((_for_it_57 + ((2 * klev) * klon)) + (klon * (_for_it_23 - 1))) - 1)];
                            double prainfrac_toprfz_out_0;

                            ///////////////////
                            // Tasklet code (T_l1025_c1025)
                            prainfrac_toprfz_out_0 = (zqx_0_in_0 / zqpretot_0_in_0);
                            ///////////////////

                            prainfrac_toprfz[(_for_it_57 - 1)] = prainfrac_toprfz_out_0;
                        }
                        {
                            double prainfrac_toprfz_0_in_0 = prainfrac_toprfz[(_for_it_57 - 1)];
                            double _if_cond_66_out;

                            ///////////////////
                            // Tasklet code (T_l0_c0)
                            _if_cond_66_out = (prainfrac_toprfz_0_in_0 > 0.8);
                            ///////////////////

                            _if_cond_66 = _if_cond_66_out;
                        }

                    }
                    if ((_if_cond_66 == 1)) {
                        {

                            {
                                int llrainliq_out_0;

                                ///////////////////
                                // Tasklet code (T_l1027_c1027)
                                llrainliq_out_0 = 1;
                                ///////////////////

                                llrainliq[(_for_it_57 - 1)] = llrainliq_out_0;
                            }

                        }
                    } else {
                        {

                            {
                                int llrainliq_out_0;

                                ///////////////////
                                // Tasklet code (T_l1029_c1029)
                                llrainliq_out_0 = 0;
                                ///////////////////

                                llrainliq[(_for_it_57 - 1)] = llrainliq_out_0;
                            }

                        }
                    }
                }
                {

                    {
                        double ydcst_0_in_rtt = v_ydcst_rtt[0];
                        double ztp1_0_in_0 = ztp1[((_for_it_57 + (klon * (_for_it_23 - 1))) - 1)];
                        double _if_cond_67_out;

                        ///////////////////
                        // Tasklet code (T_l0_c0)
                        _if_cond_67_out = (ztp1_0_in_0 < ydcst_0_in_rtt);
                        ///////////////////

                        _if_cond_67 = _if_cond_67_out;
                    }

                }
                if ((_if_cond_67 == 1)) {

                    _if_cond_68 = llrainliq[(_for_it_57 - 1)];
                    if ((_if_cond_68 == 1)) {
                        {
                            double ztemp;
                            double tmp_call_73;
                            double tmp_call_72;
                            double tmp_call_74;
                            double tmp_arg_47;
                            double* v_ydecldp_rcl_fzrab;
                            v_ydecldp_rcl_fzrab = (double*)(&(ydecldp->rcl_fzrab));
                            double* v_ydecldp_rcl_const6r;
                            v_ydecldp_rcl_const6r = (double*)(&(ydecldp->rcl_const6r));
                            double* v_ydecldp_rcl_const5r;
                            v_ydecldp_rcl_const5r = (double*)(&(ydecldp->rcl_const5r));

                            {
                                double ydecldp_0_in_rcl_fac1 = v_ydecldp_rcl_fac1[0];
                                double zqx_0_in_0 = zqx[(((_for_it_57 + ((2 * klev) * klon)) + (klon * (_for_it_23 - 1))) - 1)];
                                double zrho_0_in_0 = zrho[(_for_it_57 - 1)];
                                double tmp_arg_47_out;

                                ///////////////////
                                // Tasklet code (T_l1034_c1034)
                                tmp_arg_47_out = (ydecldp_0_in_rcl_fac1 / (zrho_0_in_0 * zqx_0_in_0));
                                ///////////////////

                                tmp_arg_47 = tmp_arg_47_out;
                            }
                            {
                                double tmp_arg_47_0_in = tmp_arg_47;
                                double ydecldp_0_in_rcl_fac2 = v_ydecldp_rcl_fac2[0];
                                double zlambda_out;

                                ///////////////////
                                // Tasklet code (T_l1034_c1034)
                                zlambda_out = dace::math::pow(tmp_arg_47_0_in, ydecldp_0_in_rcl_fac2);
                                ///////////////////

                                zlambda = zlambda_out;
                            }
                            {
                                double ydecldp_0_in_rcl_const6r = v_ydecldp_rcl_const6r[0];
                                double zlambda_0_in = zlambda;
                                double tmp_call_73_out;

                                ///////////////////
                                // Tasklet code (T_l1036_c1036)
                                tmp_call_73_out = dace::math::pow(zlambda_0_in, ydecldp_0_in_rcl_const6r);
                                ///////////////////

                                tmp_call_73 = tmp_call_73_out;
                            }
                            {
                                double ydcst_0_in_rtt = v_ydcst_rtt[0];
                                double ydecldp_0_in_rcl_fzrab = v_ydecldp_rcl_fzrab[0];
                                double ztp1_0_in_0 = ztp1[((_for_it_57 + (klon * (_for_it_23 - 1))) - 1)];
                                double ztemp_out;

                                ///////////////////
                                // Tasklet code (T_l1035_c1035)
                                ztemp_out = (ydecldp_0_in_rcl_fzrab * (ztp1_0_in_0 - ydcst_0_in_rtt));
                                ///////////////////

                                ztemp = ztemp_out;
                            }
                            {
                                double ztemp_0_in = ztemp;
                                double tmp_call_72_out;

                                ///////////////////
                                // Tasklet code (T_l1036_c1036)
                                tmp_call_72_out = exp(ztemp_0_in);
                                ///////////////////

                                tmp_call_72 = tmp_call_72_out;
                            }
                            {
                                double ptsphy_0_in = ptsphy;
                                double tmp_call_72_0_in = tmp_call_72;
                                double tmp_call_73_0_in = tmp_call_73;
                                double ydecldp_0_in_rcl_const5r = v_ydecldp_rcl_const5r[0];
                                double zrho_0_in_0 = zrho[(_for_it_57 - 1)];
                                double zfrz_out;

                                ///////////////////
                                // Tasklet code (T_l1036_c1036)
                                zfrz_out = (((ptsphy_0_in * (ydecldp_0_in_rcl_const5r / zrho_0_in_0)) * (tmp_call_72_0_in - 1.0)) * tmp_call_73_0_in);
                                ///////////////////

                                zfrz = zfrz_out;
                            }
                            {
                                double zfrz_0_in = zfrz;
                                double tmp_call_74_out;

                                ///////////////////
                                // Tasklet code (T_l1037_c1037)
                                tmp_call_74_out = max(zfrz_0_in, 0.0);
                                ///////////////////

                                tmp_call_74 = tmp_call_74_out;
                            }
                            {
                                double tmp_call_74_0_in = tmp_call_74;
                                double zfrzmax_out_0;

                                ///////////////////
                                // Tasklet code (T_l1037_c1037)
                                zfrzmax_out_0 = tmp_call_74_0_in;
                                ///////////////////

                                zfrzmax[(_for_it_57 - 1)] = zfrzmax_out_0;
                            }

                        }
                    } else {
                        {
                            double tmp_arg_48;

                            {
                                double ptsphy_0_in = ptsphy;
                                double ydcst_0_in_rtt = v_ydcst_rtt[0];
                                double ydecldp_0_in_rtaumel = v_ydecldp_rtaumel[0];
                                double ztp1_0_in_0 = ztp1[((_for_it_57 + (klon * (_for_it_23 - 1))) - 1)];
                                double tmp_arg_48_out;

                                ///////////////////
                                // Tasklet code (T_l1039_c1039)
                                tmp_arg_48_out = ((ptsphy_0_in * (1.0 + (0.5 * (ydcst_0_in_rtt - ztp1_0_in_0)))) / ydecldp_0_in_rtaumel);
                                ///////////////////

                                tmp_arg_48 = tmp_arg_48_out;
                            }
                            {
                                double tmp_arg_48_0_in = tmp_arg_48;
                                double zcons1_out;

                                ///////////////////
                                // Tasklet code (T_l1039_c1039)
                                zcons1_out = abs(tmp_arg_48_0_in);
                                ///////////////////

                                zcons1 = zcons1_out;
                            }

                        }
                        {
                            double tmp_call_75;
                            double tmp_arg_49;

                            {
                                double ydcst_0_in_rtt = v_ydcst_rtt[0];
                                double zcons1_0_in = zcons1;
                                double zrldcp_0_in = zrldcp;
                                double ztp1_0_in_0 = ztp1[((_for_it_57 + (klon * (_for_it_23 - 1))) - 1)];
                                double tmp_arg_49_out;

                                ///////////////////
                                // Tasklet code (T_l1040_c1040)
                                tmp_arg_49_out = (((ydcst_0_in_rtt - ztp1_0_in_0) * zcons1_0_in) * zrldcp_0_in);
                                ///////////////////

                                tmp_arg_49 = tmp_arg_49_out;
                            }
                            {
                                double tmp_arg_49_0_in = tmp_arg_49;
                                double tmp_call_75_out;

                                ///////////////////
                                // Tasklet code (T_l1040_c1040)
                                tmp_call_75_out = max(tmp_arg_49_0_in, 0.0);
                                ///////////////////

                                tmp_call_75 = tmp_call_75_out;
                            }
                            {
                                double tmp_call_75_0_in = tmp_call_75;
                                double zfrzmax_out_0;

                                ///////////////////
                                // Tasklet code (T_l1040_c1040)
                                zfrzmax_out_0 = tmp_call_75_0_in;
                                ///////////////////

                                zfrzmax[(_for_it_57 - 1)] = zfrzmax_out_0;
                            }

                        }
                    }
                    _if_cond_69 = (zfrzmax[(_for_it_57 - 1)] > 1e-14);
                    if ((_if_cond_69 == 1)) {
                        {

                            {
                                double zfrzmax_0_in_0 = zfrzmax[(_for_it_57 - 1)];
                                double zqx_0_in_0 = zqx[(((_for_it_57 + ((2 * klev) * klon)) + (klon * (_for_it_23 - 1))) - 1)];
                                double zfrz_out;

                                ///////////////////
                                // Tasklet code (T_l1043_c1043)
                                zfrz_out = min(zqx_0_in_0, zfrzmax_0_in_0);
                                ///////////////////

                                zfrz = zfrz_out;
                            }
                            {
                                double zfrz_0_in = zfrz;
                                double zsolqa_0_in_0 = zsolqa[((_for_it_57 + (13 * klon)) - 1)];
                                double zsolqa_out_0;

                                ///////////////////
                                // Tasklet code (T_l1044_c1044)
                                zsolqa_out_0 = (zsolqa_0_in_0 + zfrz_0_in);
                                ///////////////////

                                zsolqa[((_for_it_57 + (13 * klon)) - 1)] = zsolqa_out_0;
                            }
                            {
                                double zfrz_0_in = zfrz;
                                double zsolqa_0_in_0 = zsolqa[((_for_it_57 + (17 * klon)) - 1)];
                                double zsolqa_out_0;

                                ///////////////////
                                // Tasklet code (T_l1045_c1045)
                                zsolqa_out_0 = (zsolqa_0_in_0 - zfrz_0_in);
                                ///////////////////

                                zsolqa[((_for_it_57 + (17 * klon)) - 1)] = zsolqa_out_0;
                            }

                        }
                    }
                }
            }

        }
        for (_for_it_58 = 1; (_for_it_58 <= kfdia); _for_it_58 = (_for_it_58 + 1)) {
            {
                double tmp_call_76;
                double tmp_arg_50;

                {
                    double ydecldp_0_in_rthomo = v_ydecldp_rthomo[0];
                    double zrldcp_0_in = zrldcp;
                    double ztp1_0_in_0 = ztp1[((_for_it_58 + (klon * (_for_it_23 - 1))) - 1)];
                    double tmp_arg_50_out;

                    ///////////////////
                    // Tasklet code (T_l1051_c1051)
                    tmp_arg_50_out = ((ydecldp_0_in_rthomo - ztp1_0_in_0) * zrldcp_0_in);
                    ///////////////////

                    tmp_arg_50 = tmp_arg_50_out;
                }
                {
                    double tmp_arg_50_0_in = tmp_arg_50;
                    double tmp_call_76_out;

                    ///////////////////
                    // Tasklet code (T_l1051_c1051)
                    tmp_call_76_out = max(tmp_arg_50_0_in, 0.0);
                    ///////////////////

                    tmp_call_76 = tmp_call_76_out;
                }
                {
                    double tmp_call_76_0_in = tmp_call_76;
                    double zfrzmax_out_0;

                    ///////////////////
                    // Tasklet code (T_l1051_c1051)
                    zfrzmax_out_0 = tmp_call_76_0_in;
                    ///////////////////

                    zfrzmax[(_for_it_58 - 1)] = zfrzmax_out_0;
                }

            }

        }
        jnn = imelt[0];
        for (_for_it_59 = 1; (_for_it_59 <= kfdia); _for_it_59 = (_for_it_59 + 1)) {

            _if_cond_70 = ((zfrzmax[(_for_it_59 - 1)] > 1e-14) && (zqxfg[(_for_it_59 - 1)] > 1e-14));
            if ((_if_cond_70 == 1)) {
                {

                    {
                        double zfrzmax_0_in_0 = zfrzmax[(_for_it_59 - 1)];
                        double zqxfg_0_in_0 = zqxfg[(_for_it_59 - 1)];
                        double zfrz_out;

                        ///////////////////
                        // Tasklet code (T_l1057_c1057)
                        zfrz_out = min(zqxfg_0_in_0, zfrzmax_0_in_0);
                        ///////////////////

                        zfrz = zfrz_out;
                    }
                    {
                        double zfrz_0_in = zfrz;
                        double zsolqa_0_in_0 = zsolqa[((_for_it_59 + (klon * (jnn - 1))) - 1)];
                        double zsolqa_out_0;

                        ///////////////////
                        // Tasklet code (T_l1058_c1058)
                        zsolqa_out_0 = (zsolqa_0_in_0 + zfrz_0_in);
                        ///////////////////

                        zsolqa[((_for_it_59 + (klon * (jnn - 1))) - 1)] = zsolqa_out_0;
                    }
                    {
                        double zfrz_0_in = zfrz;
                        double zsolqa_0_in_0 = zsolqa[((_for_it_59 + ((5 * klon) * (jnn - 1))) - 1)];
                        double zsolqa_out_0;

                        ///////////////////
                        // Tasklet code (T_l1059_c1059)
                        zsolqa_out_0 = (zsolqa_0_in_0 - zfrz_0_in);
                        ///////////////////

                        zsolqa[((_for_it_59 + ((5 * klon) * (jnn - 1))) - 1)] = zsolqa_out_0;
                    }

                }
            }

        }
        for (_for_it_60 = 1; (_for_it_60 <= kfdia); _for_it_60 = (_for_it_60 + 1)) {
            {
                double tmp_call_77;
                double tmp_arg_51;

                {
                    double za_0_in_0 = za[((_for_it_60 + (klon * (_for_it_23 - 1))) - 1)];
                    double tmp_arg_51_out;

                    ///////////////////
                    // Tasklet code (T_l1063_c1063)
                    tmp_arg_51_out = (1.0 - za_0_in_0);
                    ///////////////////

                    tmp_arg_51 = tmp_arg_51_out;
                }
                {
                    double tmp_arg_51_0_in = tmp_arg_51;
                    double zepsec_0_in = zepsec;
                    double tmp_call_77_out;

                    ///////////////////
                    // Tasklet code (T_l1063_c1063)
                    tmp_call_77_out = max(zepsec_0_in, tmp_arg_51_0_in);
                    ///////////////////

                    tmp_call_77 = tmp_call_77_out;
                }
                {
                    double tmp_call_77_0_in = tmp_call_77;
                    double ydecldp_0_in_rprecrhmax = v_ydecldp_rprecrhmax[0];
                    double ydecldp_1_in_rprecrhmax = v_ydecldp_rprecrhmax[0];
                    double zcovpmax_0_in_0 = zcovpmax[(_for_it_60 - 1)];
                    double zzrh_out;

                    ///////////////////
                    // Tasklet code (T_l1063_c1063)
                    zzrh_out = (ydecldp_0_in_rprecrhmax + (((1.0 - ydecldp_1_in_rprecrhmax) * zcovpmax_0_in_0) / tmp_call_77_0_in));
                    ///////////////////

                    zzrh = zzrh_out;
                }

            }
            {
                double tmp_call_78;
                double tmp_call_79;

                {
                    double ydecldp_0_in_rprecrhmax = v_ydecldp_rprecrhmax[0];
                    double zzrh_0_in = zzrh;
                    double tmp_call_78_out;

                    ///////////////////
                    // Tasklet code (T_l1064_c1064)
                    tmp_call_78_out = max(zzrh_0_in, ydecldp_0_in_rprecrhmax);
                    ///////////////////

                    tmp_call_78 = tmp_call_78_out;
                }
                {
                    double tmp_call_78_0_in = tmp_call_78;
                    double zzrh_out;

                    ///////////////////
                    // Tasklet code (T_l1064_c1064)
                    zzrh_out = min(tmp_call_78_0_in, 1.0);
                    ///////////////////

                    zzrh = zzrh_out;
                }
                {
                    double zzrh_0_in = zzrh;
                    double zzrh_out;

                    ///////////////////
                    // Tasklet code (T_l1065_c1065)
                    zzrh_out = min(0.8, zzrh_0_in);
                    ///////////////////

                    zzrh = zzrh_out;
                }
                {
                    double zqsliq_0_in_0 = zqsliq[((_for_it_60 + (klon * (_for_it_23 - 1))) - 1)];
                    double zqx_0_in_0 = zqx[(((_for_it_60 + ((4 * klev) * klon)) + (klon * (_for_it_23 - 1))) - 1)];
                    double tmp_call_79_out;

                    ///////////////////
                    // Tasklet code (T_l1066_c1066)
                    tmp_call_79_out = min(zqx_0_in_0, zqsliq_0_in_0);
                    ///////////////////

                    tmp_call_79 = tmp_call_79_out;
                }
                {
                    double tmp_call_79_0_in = tmp_call_79;
                    double zqe_out;

                    ///////////////////
                    // Tasklet code (T_l1066_c1066)
                    zqe_out = max(0.0, tmp_call_79_0_in);
                    ///////////////////

                    zqe = zqe_out;
                }
                {
                    double zcovpclr_0_in_0 = zcovpclr[(_for_it_60 - 1)];
                    double zqe_0_in = zqe;
                    double zqsliq_0_in_0 = zqsliq[((_for_it_60 + (klon * (_for_it_23 - 1))) - 1)];
                    double zqxfg_0_in_0 = zqxfg[((_for_it_60 + (2 * klon)) - 1)];
                    double zzrh_0_in = zzrh;
                    int llo1_out;

                    ///////////////////
                    // Tasklet code (T_l1067_c1067)
                    llo1_out = (((zcovpclr_0_in_0 > 1e-14) && (zqxfg_0_in_0 > 1e-14)) && (zqe_0_in < (zzrh_0_in * zqsliq_0_in_0)));
                    ///////////////////

                    llo1 = llo1_out;
                }

            }
            _if_cond_71 = llo1;
            if ((_if_cond_71 == 1)) {
                {
                    double zesatliq;
                    double zevap_denom;
                    double zcorr2;
                    double tmp_call_80;
                    double tmp_call_81;
                    double tmp_call_82;
                    double tmp_call_87;
                    double tmp_call_86;
                    double tmp_call_85;
                    double tmp_call_84;
                    double tmp_call_83;
                    double tmp_call_88;
                    double tmp_call_89;
                    double tmp_arg_52;
                    double tmp_arg_53;
                    double tmp_arg_54;
                    double tmp_arg_55;
                    double tmp_arg_56;
                    double tmp_arg_57;
                    double tmp_arg_58;
                    double* v_ydecldp_rcl_cdenom1;
                    v_ydecldp_rcl_cdenom1 = (double*)(&(ydecldp->rcl_cdenom1));
                    double* v_ydecldp_rcl_cdenom2;
                    v_ydecldp_rcl_cdenom2 = (double*)(&(ydecldp->rcl_cdenom2));
                    double* v_ydecldp_rcl_cdenom3;
                    v_ydecldp_rcl_cdenom3 = (double*)(&(ydecldp->rcl_cdenom3));
                    double* v_ydecldp_rcl_const3r;
                    v_ydecldp_rcl_const3r = (double*)(&(ydecldp->rcl_const3r));
                    double* v_ydecldp_rcl_const4r;
                    v_ydecldp_rcl_const4r = (double*)(&(ydecldp->rcl_const4r));
                    double* v_ydecldp_rcl_const1r;
                    v_ydecldp_rcl_const1r = (double*)(&(ydecldp->rcl_const1r));
                    double* v_ydecldp_rcl_const2r;
                    v_ydecldp_rcl_const2r = (double*)(&(ydecldp->rcl_const2r));
                    double tmp_call_117_0;
                    double tmp_arg_71_0;

                    {
                        double zcovptot_0_in_0 = zcovptot[(_for_it_60 - 1)];
                        double zqxfg_0_in_0 = zqxfg[((_for_it_60 + (2 * klon)) - 1)];
                        double zpreclr_out;

                        ///////////////////
                        // Tasklet code (T_l1069_c1069)
                        zpreclr_out = (zqxfg_0_in_0 / zcovptot_0_in_0);
                        ///////////////////

                        zpreclr = zpreclr_out;
                    }
                    {
                        double ydecldp_0_in_rdensref = v_ydecldp_rdensref[0];
                        double zrho_0_in_0 = zrho[(_for_it_60 - 1)];
                        double tmp_arg_52_out;

                        ///////////////////
                        // Tasklet code (T_l1070_c1070)
                        tmp_arg_52_out = (ydecldp_0_in_rdensref / zrho_0_in_0);
                        ///////////////////

                        tmp_arg_52 = tmp_arg_52_out;
                    }
                    {
                        double tmp_arg_52_0_in = tmp_arg_52;
                        double zfallcorr_out;

                        ///////////////////
                        // Tasklet code (T_l1070_c1070)
                        zfallcorr_out = dace::math::pow(tmp_arg_52_0_in, 0.4);
                        ///////////////////

                        zfallcorr = zfallcorr_out;
                    }
                    {
                        double zfallcorr_0_in = zfallcorr;
                        double zrho_0_in_0 = zrho[(_for_it_60 - 1)];
                        double tmp_arg_56_out;

                        ///////////////////
                        // Tasklet code (T_l1078_c1078)
                        tmp_arg_56_out = (zrho_0_in_0 * zfallcorr_0_in);
                        ///////////////////

                        tmp_arg_56 = tmp_arg_56_out;
                    }
                    {
                        double tmp_arg_56_0_in = tmp_arg_56;
                        double tmp_call_85_out;

                        ///////////////////
                        // Tasklet code (T_l1078_c1078)
                        tmp_call_85_out = dace::math::sqrt(tmp_arg_56_0_in);
                        ///////////////////

                        tmp_call_85 = tmp_call_85_out;
                    }
                    {
                        double ydecldp_0_in_rcl_fac1 = v_ydecldp_rcl_fac1[0];
                        double zpreclr_0_in = zpreclr;
                        double zrho_0_in_0 = zrho[(_for_it_60 - 1)];
                        double tmp_arg_53_out;

                        ///////////////////
                        // Tasklet code (T_l1073_c1073)
                        tmp_arg_53_out = (ydecldp_0_in_rcl_fac1 / (zrho_0_in_0 * zpreclr_0_in));
                        ///////////////////

                        tmp_arg_53 = tmp_arg_53_out;
                    }
                    {
                        double tmp_arg_53_0_in = tmp_arg_53;
                        double ydecldp_0_in_rcl_fac2 = v_ydecldp_rcl_fac2[0];
                        double zlambda_out;

                        ///////////////////
                        // Tasklet code (T_l1073_c1073)
                        zlambda_out = dace::math::pow(tmp_arg_53_0_in, ydecldp_0_in_rcl_fac2);
                        ///////////////////

                        zlambda = zlambda_out;
                    }
                    {
                        double ydecldp_0_in_rcl_const3r = v_ydecldp_rcl_const3r[0];
                        double zlambda_0_in = zlambda;
                        double tmp_call_87_out;

                        ///////////////////
                        // Tasklet code (T_l1078_c1078)
                        tmp_call_87_out = dace::math::pow(zlambda_0_in, ydecldp_0_in_rcl_const3r);
                        ///////////////////

                        tmp_call_87 = tmp_call_87_out;
                    }
                    {
                        double ydecldp_0_in_rcl_const4r = v_ydecldp_rcl_const4r[0];
                        double zlambda_0_in = zlambda;
                        double tmp_call_84_out;

                        ///////////////////
                        // Tasklet code (T_l1078_c1078)
                        tmp_call_84_out = dace::math::pow(zlambda_0_in, ydecldp_0_in_rcl_const4r);
                        ///////////////////

                        tmp_call_84 = tmp_call_84_out;
                    }
                    {
                        double ztp1_0_in_0 = ztp1[((_for_it_60 + (klon * (_for_it_23 - 1))) - 1)];
                        double oka_out;

                        ///////////////////
                        // Tasklet code (T_l1071_c1071)
                        oka_out = ztp1_0_in_0;
                        ///////////////////

                        oka = oka_out;
                    }
                    {
                        double ztp1_0_in_0 = ztp1[((_for_it_60 + (klon * (_for_it_23 - 1))) - 1)];
                        double tmp_call_81_out;

                        ///////////////////
                        // Tasklet code (T_l1074_c1074)
                        tmp_call_81_out = (dace::math::ipow(ztp1_0_in_0, 3));
                        ///////////////////

                        tmp_call_81 = tmp_call_81_out;
                    }
                    {
                        double ztp1_0_in_0 = ztp1[((_for_it_60 + (klon * (_for_it_23 - 1))) - 1)];
                        double tmp_arg_54_out;

                        ///////////////////
                        // Tasklet code (T_l1075_c1075)
                        tmp_arg_54_out = (ztp1_0_in_0 / 273.0);
                        ///////////////////

                        tmp_arg_54 = tmp_arg_54_out;
                    }
                    {
                        double tmp_arg_54_0_in = tmp_arg_54;
                        double tmp_call_82_out;

                        ///////////////////
                        // Tasklet code (T_l1075_c1075)
                        tmp_call_82_out = dace::math::pow(tmp_arg_54_0_in, 1.5);
                        ///////////////////

                        tmp_call_82 = tmp_call_82_out;
                    }
                    {
                        double tmp_call_82_0_in = tmp_call_82;
                        double ztp1_0_in_0 = ztp1[((_for_it_60 + (klon * (_for_it_23 - 1))) - 1)];
                        double zcorr2_out;

                        ///////////////////
                        // Tasklet code (T_l1075_c1075)
                        zcorr2_out = ((tmp_call_82_0_in * 393.0) / (ztp1_0_in_0 + 120.0));
                        ///////////////////

                        zcorr2 = zcorr2_out;
                    }
                    {
                        double zcorr2_0_in = zcorr2;
                        double tmp_call_86_out;

                        ///////////////////
                        // Tasklet code (T_l1078_c1078)
                        tmp_call_86_out = dace::math::sqrt(zcorr2_0_in);
                        ///////////////////

                        tmp_call_86 = tmp_call_86_out;
                    }
                    {
                        double ztp1_0_in_0 = ztp1[((_for_it_60 + (klon * (_for_it_23 - 1))) - 1)];
                        double tmp_call_83_out;

                        ///////////////////
                        // Tasklet code (T_l1078_c1078)
                        tmp_call_83_out = (dace::math::ipow(ztp1_0_in_0, 2));
                        ///////////////////

                        tmp_call_83 = tmp_call_83_out;
                    }
                    {
                        double ptare_var_11_0_in = oka;
                        double ptare_var_11_1_in = oka;
                        double ydcst_var_13_0_in_rtt = v_ydcst_var_13_rtt[0];
                        double ydthf_var_12_0_in_r3les = v_ydthf_var_12_r3les[0];
                        double ydthf_var_12_1_in_r4les = v_ydthf_var_12_r4les[0];
                        double tmp_arg_71_out;

                        ///////////////////
                        // Tasklet code (T_l1400_c1400)
                        tmp_arg_71_out = ((ydthf_var_12_0_in_r3les * (ptare_var_11_0_in - ydcst_var_13_0_in_rtt)) / (ptare_var_11_1_in - ydthf_var_12_1_in_r4les));
                        ///////////////////

                        tmp_arg_71_0 = tmp_arg_71_out;
                    }
                    {
                        double tmp_arg_71_0_in = tmp_arg_71_0;
                        double tmp_call_117_out;

                        ///////////////////
                        // Tasklet code (T_l1400_c1400)
                        tmp_call_117_out = exp(tmp_arg_71_0_in);
                        ///////////////////

                        tmp_call_117_0 = tmp_call_117_out;
                    }
                    {
                        double tmp_call_117_0_in = tmp_call_117_0;
                        double ydthf_var_12_0_in_r2es = v_ydthf_var_12_r2es[0];
                        double foeeliq__ret_out;

                        ///////////////////
                        // Tasklet code (T_l1400_c1400)
                        foeeliq__ret_out = (ydthf_var_12_0_in_r2es * tmp_call_117_0_in);
                        ///////////////////

                        tmp_call_80 = foeeliq__ret_out;
                    }
                    {
                        double tmp_call_80_0_in = tmp_call_80;
                        double ydcst_0_in_rv = v_ydcst_rv[0];
                        double ydcst_1_in_rd = v_ydcst_rd[0];
                        double zesatliq_out;

                        ///////////////////
                        // Tasklet code (T_l1072_c1072)
                        zesatliq_out = ((ydcst_0_in_rv / ydcst_1_in_rd) * tmp_call_80_0_in);
                        ///////////////////

                        zesatliq = zesatliq_out;
                    }
                    {
                        double pap_0_in_0 = pap[((_for_it_60 + (klon * (_for_it_23 - 1))) - 1)];
                        double tmp_call_81_0_in = tmp_call_81;
                        double ydecldp_0_in_rcl_cdenom1 = v_ydecldp_rcl_cdenom1[0];
                        double ydecldp_1_in_rcl_cdenom2 = v_ydecldp_rcl_cdenom2[0];
                        double ydecldp_2_in_rcl_cdenom3 = v_ydecldp_rcl_cdenom3[0];
                        double zesatliq_0_in = zesatliq;
                        double zesatliq_1_in = zesatliq;
                        double ztp1_0_in_0 = ztp1[((_for_it_60 + (klon * (_for_it_23 - 1))) - 1)];
                        double zevap_denom_out;

                        ///////////////////
                        // Tasklet code (T_l1074_c1074)
                        zevap_denom_out = (((ydecldp_0_in_rcl_cdenom1 * zesatliq_0_in) - ((ydecldp_1_in_rcl_cdenom2 * ztp1_0_in_0) * zesatliq_1_in)) + ((ydecldp_2_in_rcl_cdenom3 * tmp_call_81_0_in) * pap_0_in_0));
                        ///////////////////

                        zevap_denom = zevap_denom_out;
                    }
                    {
                        double tmp_call_83_0_in = tmp_call_83;
                        double tmp_call_84_0_in = tmp_call_84;
                        double tmp_call_85_0_in = tmp_call_85;
                        double tmp_call_86_0_in = tmp_call_86;
                        double tmp_call_87_0_in = tmp_call_87;
                        double ydecldp_0_in_rcl_const1r = v_ydecldp_rcl_const1r[0];
                        double ydecldp_1_in_rcl_const2r = v_ydecldp_rcl_const2r[0];
                        double zcorr2_0_in = zcorr2;
                        double zesatliq_0_in = zesatliq;
                        double zevap_denom_0_in = zevap_denom;
                        double zqsliq_0_in_0 = zqsliq[((_for_it_60 + (klon * (_for_it_23 - 1))) - 1)];
                        double zbeta_out;

                        ///////////////////
                        // Tasklet code (T_l1078_c1078)
                        zbeta_out = ((((((0.5 / zqsliq_0_in_0) * tmp_call_83_0_in) * zesatliq_0_in) * ydecldp_0_in_rcl_const1r) * (zcorr2_0_in / zevap_denom_0_in)) * ((0.78 / tmp_call_84_0_in) + ((ydecldp_1_in_rcl_const2r * tmp_call_85_0_in) / (tmp_call_86_0_in * tmp_call_87_0_in))));
                        ///////////////////

                        zbeta = zbeta_out;
                    }
                    {
                        double zqe_0_in = zqe;
                        double zqsliq_0_in_0 = zqsliq[((_for_it_60 + (klon * (_for_it_23 - 1))) - 1)];
                        double zzrh_0_in = zzrh;
                        double tmp_arg_55_out;

                        ///////////////////
                        // Tasklet code (T_l1077_c1077)
                        tmp_arg_55_out = ((zzrh_0_in * zqsliq_0_in_0) - zqe_0_in);
                        ///////////////////

                        tmp_arg_55 = tmp_arg_55_out;
                    }
                    {
                        double tmp_arg_55_0_in = tmp_arg_55;
                        double zsubsat_out;

                        ///////////////////
                        // Tasklet code (T_l1077_c1077)
                        zsubsat_out = max(tmp_arg_55_0_in, 0.0);
                        ///////////////////

                        zsubsat = zsubsat_out;
                    }
                    {
                        double ptsphy_0_in = ptsphy;
                        double zbeta_0_in = zbeta;
                        double zdenom_out;

                        ///////////////////
                        // Tasklet code (T_l1079_c1079)
                        zdenom_out = (1.0 + (zbeta_0_in * ptsphy_0_in));
                        ///////////////////

                        zdenom = zdenom_out;
                    }
                    {
                        double ptsphy_0_in = ptsphy;
                        double zbeta_0_in = zbeta;
                        double zcovpclr_0_in_0 = zcovpclr[(_for_it_60 - 1)];
                        double zdenom_0_in = zdenom;
                        double zsubsat_0_in = zsubsat;
                        double zdpevap_out;

                        ///////////////////
                        // Tasklet code (T_l1080_c1080)
                        zdpevap_out = ((((zcovpclr_0_in_0 * zbeta_0_in) * ptsphy_0_in) * zsubsat_0_in) / zdenom_0_in);
                        ///////////////////

                        zdpevap = zdpevap_out;
                    }
                    {
                        double zdpevap_0_in = zdpevap;
                        double zqxfg_0_in_0 = zqxfg[((_for_it_60 + (2 * klon)) - 1)];
                        double zevap_out;

                        ///////////////////
                        // Tasklet code (T_l1081_c1081)
                        zevap_out = min(zdpevap_0_in, zqxfg_0_in_0);
                        ///////////////////

                        zevap = zevap_out;
                    }
                    {
                        double zevap_0_in = zevap;
                        double zsolqa_0_in_0 = zsolqa[((_for_it_60 + (14 * klon)) - 1)];
                        double zsolqa_out_0;

                        ///////////////////
                        // Tasklet code (T_l1082_c1082)
                        zsolqa_out_0 = (zsolqa_0_in_0 + zevap_0_in);
                        ///////////////////

                        zsolqa[((_for_it_60 + (14 * klon)) - 1)] = zsolqa_out_0;
                    }
                    {
                        double zevap_0_in = zevap;
                        double zsolqa_0_in_0 = zsolqa[((_for_it_60 + (22 * klon)) - 1)];
                        double zsolqa_out_0;

                        ///////////////////
                        // Tasklet code (T_l1083_c1083)
                        zsolqa_out_0 = (zsolqa_0_in_0 - zevap_0_in);
                        ///////////////////

                        zsolqa[((_for_it_60 + (22 * klon)) - 1)] = zsolqa_out_0;
                    }
                    {
                        double za_0_in_0 = za[((_for_it_60 + (klon * (_for_it_23 - 1))) - 1)];
                        double zcovptot_0_in_0 = zcovptot[(_for_it_60 - 1)];
                        double zevap_0_in = zevap;
                        double zqxfg_0_in_0 = zqxfg[((_for_it_60 + (2 * klon)) - 1)];
                        double tmp_arg_57_out;

                        ///////////////////
                        // Tasklet code (T_l1084_c1084)
                        tmp_arg_57_out = (((zcovptot_0_in_0 - za_0_in_0) * zevap_0_in) / zqxfg_0_in_0);
                        ///////////////////

                        tmp_arg_57 = tmp_arg_57_out;
                    }
                    {
                        double tmp_arg_57_0_in = tmp_arg_57;
                        double tmp_call_89_out;

                        ///////////////////
                        // Tasklet code (T_l1084_c1084)
                        tmp_call_89_out = max(0.0, tmp_arg_57_0_in);
                        ///////////////////

                        tmp_call_89 = tmp_call_89_out;
                    }
                    {
                        double tmp_call_89_0_in = tmp_call_89;
                        double zcovptot_0_in_0 = zcovptot[(_for_it_60 - 1)];
                        double tmp_arg_58_out;

                        ///////////////////
                        // Tasklet code (T_l1084_c1084)
                        tmp_arg_58_out = (zcovptot_0_in_0 - tmp_call_89_0_in);
                        ///////////////////

                        tmp_arg_58 = tmp_arg_58_out;
                    }
                    {
                        double tmp_arg_58_0_in = tmp_arg_58;
                        double ydecldp_0_in_rcovpmin = v_ydecldp_rcovpmin[0];
                        double tmp_call_88_out;

                        ///////////////////
                        // Tasklet code (T_l1084_c1084)
                        tmp_call_88_out = max(ydecldp_0_in_rcovpmin, tmp_arg_58_0_in);
                        ///////////////////

                        tmp_call_88 = tmp_call_88_out;
                    }
                    {
                        double tmp_call_88_0_in = tmp_call_88;
                        double zcovptot_out_0;

                        ///////////////////
                        // Tasklet code (T_l1084_c1084)
                        zcovptot_out_0 = tmp_call_88_0_in;
                        ///////////////////

                        zcovptot[(_for_it_60 - 1)] = zcovptot_out_0;
                    }

                }
                {

                    {
                        double zevap_0_in = zevap;
                        double zqxfg_0_in_0 = zqxfg[((_for_it_60 + (2 * klon)) - 1)];
                        double zqxfg_out_0;

                        ///////////////////
                        // Tasklet code (T_l1085_c1085)
                        zqxfg_out_0 = (zqxfg_0_in_0 - zevap_0_in);
                        ///////////////////

                        zqxfg[((_for_it_60 + (2 * klon)) - 1)] = zqxfg_out_0;
                    }

                }
            }

        }
        for (_for_it_61 = 1; (_for_it_61 <= kfdia); _for_it_61 = (_for_it_61 + 1)) {
            {
                double tmp_call_90;
                double tmp_arg_59;

                {
                    double za_0_in_0 = za[((_for_it_61 + (klon * (_for_it_23 - 1))) - 1)];
                    double tmp_arg_59_out;

                    ///////////////////
                    // Tasklet code (T_l1089_c1089)
                    tmp_arg_59_out = (1.0 - za_0_in_0);
                    ///////////////////

                    tmp_arg_59 = tmp_arg_59_out;
                }
                {
                    double tmp_arg_59_0_in = tmp_arg_59;
                    double zepsec_0_in = zepsec;
                    double tmp_call_90_out;

                    ///////////////////
                    // Tasklet code (T_l1089_c1089)
                    tmp_call_90_out = max(zepsec_0_in, tmp_arg_59_0_in);
                    ///////////////////

                    tmp_call_90 = tmp_call_90_out;
                }
                {
                    double tmp_call_90_0_in = tmp_call_90;
                    double ydecldp_0_in_rprecrhmax = v_ydecldp_rprecrhmax[0];
                    double ydecldp_1_in_rprecrhmax = v_ydecldp_rprecrhmax[0];
                    double zcovpmax_0_in_0 = zcovpmax[(_for_it_61 - 1)];
                    double zzrh_out;

                    ///////////////////
                    // Tasklet code (T_l1089_c1089)
                    zzrh_out = (ydecldp_0_in_rprecrhmax + (((1.0 - ydecldp_1_in_rprecrhmax) * zcovpmax_0_in_0) / tmp_call_90_0_in));
                    ///////////////////

                    zzrh = zzrh_out;
                }

            }
            {
                double tmp_call_91;
                double tmp_call_92;
                double tmp_call_93;
                double tmp_arg_60;

                {
                    double ydecldp_0_in_rprecrhmax = v_ydecldp_rprecrhmax[0];
                    double zzrh_0_in = zzrh;
                    double tmp_call_91_out;

                    ///////////////////
                    // Tasklet code (T_l1090_c1090)
                    tmp_call_91_out = max(zzrh_0_in, ydecldp_0_in_rprecrhmax);
                    ///////////////////

                    tmp_call_91 = tmp_call_91_out;
                }
                {
                    double tmp_call_91_0_in = tmp_call_91;
                    double zzrh_out;

                    ///////////////////
                    // Tasklet code (T_l1090_c1090)
                    zzrh_out = min(tmp_call_91_0_in, 1.0);
                    ///////////////////

                    zzrh = zzrh_out;
                }
                {
                    double za_0_in_0 = za[((_for_it_61 + (klon * (_for_it_23 - 1))) - 1)];
                    double tmp_arg_60_out;

                    ///////////////////
                    // Tasklet code (T_l1091_c1091)
                    tmp_arg_60_out = (1.0 - za_0_in_0);
                    ///////////////////

                    tmp_arg_60 = tmp_arg_60_out;
                }
                {
                    double tmp_arg_60_0_in = tmp_arg_60;
                    double zepsec_0_in = zepsec;
                    double tmp_call_92_out;

                    ///////////////////
                    // Tasklet code (T_l1091_c1091)
                    tmp_call_92_out = max(zepsec_0_in, tmp_arg_60_0_in);
                    ///////////////////

                    tmp_call_92 = tmp_call_92_out;
                }
                {
                    double tmp_call_92_0_in = tmp_call_92;
                    double za_0_in_0 = za[((_for_it_61 + (klon * (_for_it_23 - 1))) - 1)];
                    double zqsice_0_in_0 = zqsice[((_for_it_61 + (klon * (_for_it_23 - 1))) - 1)];
                    double zqx_0_in_0 = zqx[(((_for_it_61 + ((4 * klev) * klon)) + (klon * (_for_it_23 - 1))) - 1)];
                    double zqe_out;

                    ///////////////////
                    // Tasklet code (T_l1091_c1091)
                    zqe_out = ((zqx_0_in_0 - (za_0_in_0 * zqsice_0_in_0)) / tmp_call_92_0_in);
                    ///////////////////

                    zqe = zqe_out;
                }
                {
                    double zqe_0_in = zqe;
                    double zqsice_0_in_0 = zqsice[((_for_it_61 + (klon * (_for_it_23 - 1))) - 1)];
                    double tmp_call_93_out;

                    ///////////////////
                    // Tasklet code (T_l1092_c1092)
                    tmp_call_93_out = min(zqe_0_in, zqsice_0_in_0);
                    ///////////////////

                    tmp_call_93 = tmp_call_93_out;
                }
                {
                    double tmp_call_93_0_in = tmp_call_93;
                    double zqe_out;

                    ///////////////////
                    // Tasklet code (T_l1092_c1092)
                    zqe_out = max(0.0, tmp_call_93_0_in);
                    ///////////////////

                    zqe = zqe_out;
                }
                {
                    double zcovpclr_0_in_0 = zcovpclr[(_for_it_61 - 1)];
                    double zqe_0_in = zqe;
                    double zqsice_0_in_0 = zqsice[((_for_it_61 + (klon * (_for_it_23 - 1))) - 1)];
                    double zqxfg_0_in_0 = zqxfg[((_for_it_61 + (3 * klon)) - 1)];
                    double zzrh_0_in = zzrh;
                    int llo1_out;

                    ///////////////////
                    // Tasklet code (T_l1093_c1093)
                    llo1_out = (((zcovpclr_0_in_0 > 1e-14) && (zqxfg_0_in_0 > 1e-14)) && (zqe_0_in < (zzrh_0_in * zqsice_0_in_0)));
                    ///////////////////

                    llo1 = llo1_out;
                }

            }
            _if_cond_72 = llo1;
            if ((_if_cond_72 == 1)) {
                {
                    double tmp_call_101;
                    double tmp_arg_61;

                    {
                        double zcovptot_0_in_0 = zcovptot[(_for_it_61 - 1)];
                        double zdtgdp_0_in_0 = zdtgdp[(_for_it_61 - 1)];
                        double tmp_arg_61_out;

                        ///////////////////
                        // Tasklet code (T_l1095_c1095)
                        tmp_arg_61_out = (zcovptot_0_in_0 * zdtgdp_0_in_0);
                        ///////////////////

                        tmp_arg_61 = tmp_arg_61_out;
                    }
                    {
                        double tmp_arg_61_0_in = tmp_arg_61;
                        double tmp_call_101_out;

                        ///////////////////
                        // Tasklet code (T_l1095_c1095)
                        tmp_call_101_out = abs(tmp_arg_61_0_in);
                        ///////////////////

                        tmp_call_101 = tmp_call_101_out;
                    }
                    {
                        double tmp_call_101_0_in = tmp_call_101;
                        double zepsilon_0_in = zepsilon;
                        double tmp_call_99_out;

                        ///////////////////
                        // Tasklet code (T_l1095_c1095)
                        tmp_call_99_out = max(tmp_call_101_0_in, zepsilon_0_in);
                        ///////////////////

                        tmp_call_99 = tmp_call_99_out;
                    }

                }
                if (((zcovptot[(_for_it_61 - 1)] * zdtgdp[(_for_it_61 - 1)]) >= 0.0)) {
                    {

                        {
                            double tmp_call_99_0_in = tmp_call_99;
                            double tmp_call_94_out;

                            ///////////////////
                            // Tasklet code (T_l1095_c1095)
                            tmp_call_94_out = abs(tmp_call_99_0_in);
                            ///////////////////

                            tmp_call_94 = tmp_call_94_out;
                        }

                    }
                } else {
                    {

                        {
                            double tmp_call_99_0_in = tmp_call_99;
                            double tmp_call_0_out;

                            ///////////////////
                            // Tasklet code (T_l1095_c1095)
                            tmp_call_0_out = abs(tmp_call_99_0_in);
                            ///////////////////

                            tmp_call_0 = tmp_call_0_out;
                        }
                        {
                            double tmp_call_0_0_in = tmp_call_0;
                            double tmp_call_94_out;

                            ///////////////////
                            // Tasklet code (T_l1095_c1095)
                            tmp_call_94_out = (- tmp_call_0_0_in);
                            ///////////////////

                            tmp_call_94 = tmp_call_94_out;
                        }

                    }
                }
                {
                    double zbeta1;
                    double zdpr;
                    double tmp_call_96;
                    double tmp_call_95;
                    double tmp_call_97;
                    double tmp_call_98;
                    double tmp_call_100;
                    double tmp_arg_62;
                    double tmp_arg_63;
                    double tmp_arg_64;
                    double tmp_arg_65;
                    double* v_ydecldp_rvrfactor;
                    v_ydecldp_rvrfactor = (double*)(&(ydecldp->rvrfactor));
                    double* v_ydecldp_rpecons;
                    v_ydecldp_rpecons = (double*)(&(ydecldp->rpecons));

                    {
                        double tmp_call_94_0_in = tmp_call_94;
                        double zcovpclr_0_in_0 = zcovpclr[(_for_it_61 - 1)];
                        double zqxfg_0_in_0 = zqxfg[((_for_it_61 + (3 * klon)) - 1)];
                        double zpreclr_out;

                        ///////////////////
                        // Tasklet code (T_l1095_c1095)
                        zpreclr_out = ((zqxfg_0_in_0 * zcovpclr_0_in_0) / tmp_call_94_0_in);
                        ///////////////////

                        zpreclr = zpreclr_out;
                    }
                    {
                        double zcovpclr_0_in_0 = zcovpclr[(_for_it_61 - 1)];
                        double zepsec_0_in = zepsec;
                        double tmp_call_96_out;

                        ///////////////////
                        // Tasklet code (T_l1096_c1096)
                        tmp_call_96_out = max(zcovpclr_0_in_0, zepsec_0_in);
                        ///////////////////

                        tmp_call_96 = tmp_call_96_out;
                    }
                    {
                        double pap_0_in_0 = pap[((_for_it_61 + (klon * (_for_it_23 - 1))) - 1)];
                        double paph_0_in_0 = paph[((_for_it_61 + (klev * klon)) - 1)];
                        double tmp_arg_62_out;

                        ///////////////////
                        // Tasklet code (T_l1096_c1096)
                        tmp_arg_62_out = (pap_0_in_0 / paph_0_in_0);
                        ///////////////////

                        tmp_arg_62 = tmp_arg_62_out;
                    }
                    {
                        double tmp_arg_62_0_in = tmp_arg_62;
                        double tmp_call_95_out;

                        ///////////////////
                        // Tasklet code (T_l1096_c1096)
                        tmp_call_95_out = sqrt(tmp_arg_62_0_in);
                        ///////////////////

                        tmp_call_95 = tmp_call_95_out;
                    }
                    {
                        double tmp_call_95_0_in = tmp_call_95;
                        double tmp_call_96_0_in = tmp_call_96;
                        double ydecldp_0_in_rvrfactor = v_ydecldp_rvrfactor[0];
                        double zpreclr_0_in = zpreclr;
                        double zbeta1_out;

                        ///////////////////
                        // Tasklet code (T_l1096_c1096)
                        zbeta1_out = (((tmp_call_95_0_in / ydecldp_0_in_rvrfactor) * zpreclr_0_in) / tmp_call_96_0_in);
                        ///////////////////

                        zbeta1 = zbeta1_out;
                    }
                    {
                        double zbeta1_0_in = zbeta1;
                        double tmp_arg_63_out;

                        ///////////////////
                        // Tasklet code (T_l1097_c1097)
                        tmp_arg_63_out = zbeta1_0_in;
                        ///////////////////

                        tmp_arg_63 = tmp_arg_63_out;
                    }
                    {
                        double tmp_arg_63_0_in = tmp_arg_63;
                        double tmp_call_97_out;

                        ///////////////////
                        // Tasklet code (T_l1097_c1097)
                        tmp_call_97_out = dace::math::pow(tmp_arg_63_0_in, 0.5777);
                        ///////////////////

                        tmp_call_97 = tmp_call_97_out;
                    }
                    {
                        double tmp_call_97_0_in = tmp_call_97;
                        double ydcst_0_in_rg = v_ydcst_rg[0];
                        double ydecldp_0_in_rpecons = v_ydecldp_rpecons[0];
                        double zbeta_out;

                        ///////////////////
                        // Tasklet code (T_l1097_c1097)
                        zbeta_out = ((ydcst_0_in_rg * ydecldp_0_in_rpecons) * tmp_call_97_0_in);
                        ///////////////////

                        zbeta = zbeta_out;
                    }
                    {
                        double ptsphy_0_in = ptsphy;
                        double zbeta_0_in = zbeta;
                        double zcorqsice_0_in_0 = zcorqsice[(_for_it_61 - 1)];
                        double zdenom_out;

                        ///////////////////
                        // Tasklet code (T_l1098_c1098)
                        zdenom_out = (1.0 + ((zbeta_0_in * ptsphy_0_in) * zcorqsice_0_in_0));
                        ///////////////////

                        zdenom = zdenom_out;
                    }
                    {
                        double zbeta_0_in = zbeta;
                        double zcovpclr_0_in_0 = zcovpclr[(_for_it_61 - 1)];
                        double zdenom_0_in = zdenom;
                        double zdp_0_in_0 = zdp[(_for_it_61 - 1)];
                        double zqe_0_in = zqe;
                        double zqsice_0_in_0 = zqsice[((_for_it_61 + (klon * (_for_it_23 - 1))) - 1)];
                        double zrg_r_0_in = zrg_r;
                        double zdpr_out;

                        ///////////////////
                        // Tasklet code (T_l1099_c1099)
                        zdpr_out = (((((zcovpclr_0_in_0 * zbeta_0_in) * (zqsice_0_in_0 - zqe_0_in)) / zdenom_0_in) * zdp_0_in_0) * zrg_r_0_in);
                        ///////////////////

                        zdpr = zdpr_out;
                    }
                    {
                        double zdpr_0_in = zdpr;
                        double zdtgdp_0_in_0 = zdtgdp[(_for_it_61 - 1)];
                        double zdpevap_out;

                        ///////////////////
                        // Tasklet code (T_l1100_c1100)
                        zdpevap_out = (zdpr_0_in * zdtgdp_0_in_0);
                        ///////////////////

                        zdpevap = zdpevap_out;
                    }
                    {
                        double zdpevap_0_in = zdpevap;
                        double zqxfg_0_in_0 = zqxfg[((_for_it_61 + (3 * klon)) - 1)];
                        double zevap_out;

                        ///////////////////
                        // Tasklet code (T_l1101_c1101)
                        zevap_out = min(zdpevap_0_in, zqxfg_0_in_0);
                        ///////////////////

                        zevap = zevap_out;
                    }
                    {
                        double zevap_0_in = zevap;
                        double zsolqa_0_in_0 = zsolqa[((_for_it_61 + (19 * klon)) - 1)];
                        double zsolqa_out_0;

                        ///////////////////
                        // Tasklet code (T_l1102_c1102)
                        zsolqa_out_0 = (zsolqa_0_in_0 + zevap_0_in);
                        ///////////////////

                        zsolqa[((_for_it_61 + (19 * klon)) - 1)] = zsolqa_out_0;
                    }
                    {
                        double zevap_0_in = zevap;
                        double zsolqa_0_in_0 = zsolqa[((_for_it_61 + (23 * klon)) - 1)];
                        double zsolqa_out_0;

                        ///////////////////
                        // Tasklet code (T_l1103_c1103)
                        zsolqa_out_0 = (zsolqa_0_in_0 - zevap_0_in);
                        ///////////////////

                        zsolqa[((_for_it_61 + (23 * klon)) - 1)] = zsolqa_out_0;
                    }
                    {
                        double za_0_in_0 = za[((_for_it_61 + (klon * (_for_it_23 - 1))) - 1)];
                        double zcovptot_0_in_0 = zcovptot[(_for_it_61 - 1)];
                        double zevap_0_in = zevap;
                        double zqxfg_0_in_0 = zqxfg[((_for_it_61 + (3 * klon)) - 1)];
                        double tmp_arg_64_out;

                        ///////////////////
                        // Tasklet code (T_l1104_c1104)
                        tmp_arg_64_out = (((zcovptot_0_in_0 - za_0_in_0) * zevap_0_in) / zqxfg_0_in_0);
                        ///////////////////

                        tmp_arg_64 = tmp_arg_64_out;
                    }
                    {
                        double tmp_arg_64_0_in = tmp_arg_64;
                        double tmp_call_100_out;

                        ///////////////////
                        // Tasklet code (T_l1104_c1104)
                        tmp_call_100_out = max(0.0, tmp_arg_64_0_in);
                        ///////////////////

                        tmp_call_100 = tmp_call_100_out;
                    }
                    {
                        double tmp_call_100_0_in = tmp_call_100;
                        double zcovptot_0_in_0 = zcovptot[(_for_it_61 - 1)];
                        double tmp_arg_65_out;

                        ///////////////////
                        // Tasklet code (T_l1104_c1104)
                        tmp_arg_65_out = (zcovptot_0_in_0 - tmp_call_100_0_in);
                        ///////////////////

                        tmp_arg_65 = tmp_arg_65_out;
                    }
                    {
                        double tmp_arg_65_0_in = tmp_arg_65;
                        double ydecldp_0_in_rcovpmin = v_ydecldp_rcovpmin[0];
                        double tmp_call_98_out;

                        ///////////////////
                        // Tasklet code (T_l1104_c1104)
                        tmp_call_98_out = max(ydecldp_0_in_rcovpmin, tmp_arg_65_0_in);
                        ///////////////////

                        tmp_call_98 = tmp_call_98_out;
                    }
                    {
                        double tmp_call_98_0_in = tmp_call_98;
                        double zcovptot_out_0;

                        ///////////////////
                        // Tasklet code (T_l1104_c1104)
                        zcovptot_out_0 = tmp_call_98_0_in;
                        ///////////////////

                        zcovptot[(_for_it_61 - 1)] = zcovptot_out_0;
                    }

                }
                {

                    {
                        double zevap_0_in = zevap;
                        double zqxfg_0_in_0 = zqxfg[((_for_it_61 + (3 * klon)) - 1)];
                        double zqxfg_out_0;

                        ///////////////////
                        // Tasklet code (T_l1105_c1105)
                        zqxfg_out_0 = (zqxfg_0_in_0 - zevap_0_in);
                        ///////////////////

                        zqxfg[((_for_it_61 + (3 * klon)) - 1)] = zqxfg_out_0;
                    }

                }
            }

        }
        for (_for_it_62 = 1; (_for_it_62 <= 5); _for_it_62 = (_for_it_62 + 1)) {

            _if_cond_73 = llfall[(_for_it_62 - 1)];
            if ((_if_cond_73 == 1)) {
                for (_for_it_63 = 1; (_for_it_63 <= kfdia); _for_it_63 = (_for_it_63 + 1)) {
                    {

                        {
                            double ydecldp_0_in_rlmin = v_ydecldp_rlmin[0];
                            double zqxfg_0_in_0 = zqxfg[((_for_it_63 + (klon * (_for_it_62 - 1))) - 1)];
                            double _if_cond_74_out;

                            ///////////////////
                            // Tasklet code (T_l0_c0)
                            _if_cond_74_out = (zqxfg_0_in_0 < ydecldp_0_in_rlmin);
                            ///////////////////

                            _if_cond_74 = _if_cond_74_out;
                        }

                    }
                    if ((_if_cond_74 == 1)) {
                        {

                            {
                                double zqxfg_0_in_0 = zqxfg[((_for_it_63 + (klon * (_for_it_62 - 1))) - 1)];
                                double zsolqa_0_in_0 = zsolqa[(((_for_it_63 + ((5 * klon) * (_for_it_62 - 1))) + (4 * klon)) - 1)];
                                double zsolqa_out_0;

                                ///////////////////
                                // Tasklet code (T_l1112_c1112)
                                zsolqa_out_0 = (zsolqa_0_in_0 + zqxfg_0_in_0);
                                ///////////////////

                                zsolqa[(((_for_it_63 + ((5 * klon) * (_for_it_62 - 1))) + (4 * klon)) - 1)] = zsolqa_out_0;
                            }
                            {
                                double zqxfg_0_in_0 = zqxfg[((_for_it_63 + (klon * (_for_it_62 - 1))) - 1)];
                                double zsolqa_0_in_0 = zsolqa[(((_for_it_63 + (klon * (_for_it_62 - 1))) + (20 * klon)) - 1)];
                                double zsolqa_out_0;

                                ///////////////////
                                // Tasklet code (T_l1113_c1113)
                                zsolqa_out_0 = (zsolqa_0_in_0 - zqxfg_0_in_0);
                                ///////////////////

                                zsolqa[(((_for_it_63 + (klon * (_for_it_62 - 1))) + (20 * klon)) - 1)] = zsolqa_out_0;
                            }

                        }
                    }

                }
            }

        }
        for (_for_it_64 = 1; (_for_it_64 <= kfdia); _for_it_64 = (_for_it_64 + 1)) {
            {

                {
                    double za_0_in_0 = za[((_for_it_64 + (klon * (_for_it_23 - 1))) - 1)];
                    double zsolab_0_in_0 = zsolab[(_for_it_64 - 1)];
                    double zsolac_0_in_0 = zsolac[(_for_it_64 - 1)];
                    double zanew_out;

                    ///////////////////
                    // Tasklet code (T_l1119_c1119)
                    zanew_out = ((za_0_in_0 + zsolac_0_in_0) / (1.0 + zsolab_0_in_0));
                    ///////////////////

                    zanew = zanew_out;
                }
                {
                    double zanew_0_in = zanew;
                    double zanew_out;

                    ///////////////////
                    // Tasklet code (T_l1120_c1120)
                    zanew_out = min(zanew_0_in, 1.0);
                    ///////////////////

                    zanew = zanew_out;
                }
                {
                    double ydecldp_0_in_ramin = v_ydecldp_ramin[0];
                    double zanew_0_in = zanew;
                    double _if_cond_75_out;

                    ///////////////////
                    // Tasklet code (T_l1121_c1121)
                    _if_cond_75_out = (zanew_0_in < ydecldp_0_in_ramin);
                    ///////////////////

                    _if_cond_75 = _if_cond_75_out;
                }

            }
            if ((_if_cond_75 == 1)) {
                {

                    {
                        double zanew_out;

                        ///////////////////
                        // Tasklet code (T_l1121_c1121)
                        zanew_out = 0.0;
                        ///////////////////

                        zanew = zanew_out;
                    }

                }
            }
            {

                {
                    double zanew_0_in = zanew;
                    double zaorig_0_in_0 = zaorig[((_for_it_64 + (klon * (_for_it_23 - 1))) - 1)];
                    double zda_out_0;

                    ///////////////////
                    // Tasklet code (T_l1122_c1122)
                    zda_out_0 = (zanew_0_in - zaorig_0_in_0);
                    ///////////////////

                    zda[(_for_it_64 - 1)] = zda_out_0;
                }
                {
                    double zanew_0_in = zanew;
                    double zanewm1_out_0;

                    ///////////////////
                    // Tasklet code (T_l1123_c1123)
                    zanewm1_out_0 = zanew_0_in;
                    ///////////////////

                    zanewm1[(_for_it_64 - 1)] = zanewm1_out_0;
                }

            }

        }
        for (_for_it_65 = 1; (_for_it_65 <= 5); _for_it_65 = (_for_it_65 + 1)) {
            for (_for_it_66 = 1; (_for_it_66 <= 5); _for_it_66 = (_for_it_66 + 1)) {
                for (_for_it_67 = 1; (_for_it_67 <= kfdia); _for_it_67 = (_for_it_67 + 1)) {
                    {

                        {
                            int llindex3_out_0;

                            ///////////////////
                            // Tasklet code (T_l1128_c1128)
                            llindex3_out_0 = 0;
                            ///////////////////

                            llindex3[(((_for_it_67 + ((5 * klon) * (_for_it_65 - 1))) + (klon * (_for_it_66 - 1))) - 1)] = llindex3_out_0;
                        }

                    }

                }

            }
            for (_for_it_68 = 1; (_for_it_68 <= kfdia); _for_it_68 = (_for_it_68 + 1)) {
                {

                    {
                        double zsinksum_out_0;

                        ///////////////////
                        // Tasklet code (T_l1132_c1132)
                        zsinksum_out_0 = 0.0;
                        ///////////////////

                        zsinksum[((_for_it_68 + (klon * (_for_it_65 - 1))) - 1)] = zsinksum_out_0;
                    }

                }

            }

        }
        for (_for_it_69 = 1; (_for_it_69 <= 5); _for_it_69 = (_for_it_69 + 1)) {
            for (_for_it_70 = 1; (_for_it_70 <= 5); _for_it_70 = (_for_it_70 + 1)) {
                for (_for_it_71 = 1; (_for_it_71 <= kfdia); _for_it_71 = (_for_it_71 + 1)) {
                    {

                        {
                            double zsinksum_0_in_0 = zsinksum[((_for_it_71 + (klon * (_for_it_69 - 1))) - 1)];
                            double zsolqa_0_in_0 = zsolqa[(((_for_it_71 + (klon * (_for_it_69 - 1))) + ((5 * klon) * (_for_it_70 - 1))) - 1)];
                            double zsinksum_out_0;

                            ///////////////////
                            // Tasklet code (T_l1138_c1138)
                            zsinksum_out_0 = (zsinksum_0_in_0 - zsolqa_0_in_0);
                            ///////////////////

                            zsinksum[((_for_it_71 + (klon * (_for_it_69 - 1))) - 1)] = zsinksum_out_0;
                        }

                    }

                }

            }

        }
        for (_for_it_72 = 1; (_for_it_72 <= 5); _for_it_72 = (_for_it_72 + 1)) {
            for (_for_it_73 = 1; (_for_it_73 <= kfdia); _for_it_73 = (_for_it_73 + 1)) {
                {
                    double zmax;
                    double zrat;

                    {
                        double zepsec_0_in = zepsec;
                        double zqx_0_in_0 = zqx[(((_for_it_73 + ((klev * klon) * (_for_it_72 - 1))) + (klon * (_for_it_23 - 1))) - 1)];
                        double zmax_out;

                        ///////////////////
                        // Tasklet code (T_l1144_c1144)
                        zmax_out = max(zqx_0_in_0, zepsec_0_in);
                        ///////////////////

                        zmax = zmax_out;
                    }
                    {
                        double zmax_0_in = zmax;
                        double zsinksum_0_in_0 = zsinksum[((_for_it_73 + (klon * (_for_it_72 - 1))) - 1)];
                        double zrat_out;

                        ///////////////////
                        // Tasklet code (T_l1145_c1145)
                        zrat_out = max(zsinksum_0_in_0, zmax_0_in);
                        ///////////////////

                        zrat = zrat_out;
                    }
                    {
                        double zmax_0_in = zmax;
                        double zrat_0_in = zrat;
                        double zratio_out_0;

                        ///////////////////
                        // Tasklet code (T_l1146_c1146)
                        zratio_out_0 = (zmax_0_in / zrat_0_in);
                        ///////////////////

                        zratio[((_for_it_73 + (klon * (_for_it_72 - 1))) - 1)] = zratio_out_0;
                    }

                }

            }

        }
        for (_for_it_74 = 1; (_for_it_74 <= 5); _for_it_74 = (_for_it_74 + 1)) {
            for (_for_it_75 = 1; (_for_it_75 <= kfdia); _for_it_75 = (_for_it_75 + 1)) {
                {

                    {
                        int iorder_out_0;

                        ///////////////////
                        // Tasklet code (T_l1151_c1151)
                        iorder_out_0 = -999;
                        ///////////////////

                        iorder[((_for_it_75 + (klon * (_for_it_74 - 1))) - 1)] = iorder_out_0;
                    }

                }

            }

        }
        for (_for_it_76 = 1; (_for_it_76 <= 5); _for_it_76 = (_for_it_76 + 1)) {
            for (_for_it_77 = 1; (_for_it_77 <= kfdia); _for_it_77 = (_for_it_77 + 1)) {
                {

                    {
                        int llindex1_out_0;

                        ///////////////////
                        // Tasklet code (T_l1156_c1156)
                        llindex1_out_0 = 1;
                        ///////////////////

                        llindex1[((_for_it_77 + (klon * (_for_it_76 - 1))) - 1)] = llindex1_out_0;
                    }

                }

            }

        }
        for (_for_it_78 = 1; (_for_it_78 <= 5); _for_it_78 = (_for_it_78 + 1)) {
            for (_for_it_79 = 1; (_for_it_79 <= kfdia); _for_it_79 = (_for_it_79 + 1)) {
                {

                    {
                        double zmin_out_0;

                        ///////////////////
                        // Tasklet code (T_l1161_c1161)
                        zmin_out_0 = 1e+32;
                        ///////////////////

                        zmin[(_for_it_79 - 1)] = zmin_out_0;
                    }

                }

            }
            for (_for_it_80 = 1; (_for_it_80 <= 5); _for_it_80 = (_for_it_80 + 1)) {
                for (_for_it_81 = 1; (_for_it_81 <= kfdia); _for_it_81 = (_for_it_81 + 1)) {

                    _if_cond_76 = (llindex1[((_for_it_81 + (klon * (_for_it_80 - 1))) - 1)] && (zratio[((_for_it_81 + (klon * (_for_it_80 - 1))) - 1)] < zmin[(_for_it_81 - 1)]));
                    if ((_if_cond_76 == 1)) {
                        {

                            {
                                int iorder_out_0;

                                ///////////////////
                                // Tasklet code (T_l1166_c1166)
                                iorder_out_0 = _for_it_80;
                                ///////////////////

                                iorder[((_for_it_81 + (klon * (_for_it_78 - 1))) - 1)] = iorder_out_0;
                            }
                            {
                                double zratio_0_in_0 = zratio[((_for_it_81 + (klon * (_for_it_80 - 1))) - 1)];
                                double zmin_out_0;

                                ///////////////////
                                // Tasklet code (T_l1167_c1167)
                                zmin_out_0 = zratio_0_in_0;
                                ///////////////////

                                zmin[(_for_it_81 - 1)] = zmin_out_0;
                            }

                        }
                    }

                }

            }
            for (_for_it_82 = 1; (_for_it_82 <= kfdia); _for_it_82 = (_for_it_82 + 1)) {

                tmp_index_1668 = (iorder[((_for_it_82 + (klon * (_for_it_78 - 1))) - 1)] - 1);
                {

                    {
                        int llindex1_out_0;

                        ///////////////////
                        // Tasklet code (T_l1172_c1172)
                        llindex1_out_0 = 0;
                        ///////////////////

                        llindex1[((_for_it_82 + (klon * tmp_index_1668)) - 1)] = llindex1_out_0;
                    }

                }

            }

        }
        for (_for_it_83 = 1; (_for_it_83 <= 5); _for_it_83 = (_for_it_83 + 1)) {
            for (_for_it_84 = 1; (_for_it_84 <= kfdia); _for_it_84 = (_for_it_84 + 1)) {
                {

                    {
                        double zsinksum_out_0;

                        ///////////////////
                        // Tasklet code (T_l1177_c1177)
                        zsinksum_out_0 = 0.0;
                        ///////////////////

                        zsinksum[((_for_it_84 + (klon * (_for_it_83 - 1))) - 1)] = zsinksum_out_0;
                    }

                }

            }

        }
        for (_for_it_85 = 1; (_for_it_85 <= 5); _for_it_85 = (_for_it_85 + 1)) {
            for (_for_it_86 = 1; (_for_it_86 <= kfdia); _for_it_86 = (_for_it_86 + 1)) {

                jo = iorder[((_for_it_86 + (klon * (_for_it_85 - 1))) - 1)];
                for (_for_it_87 = 1; (_for_it_87 <= 5); _for_it_87 = (_for_it_87 + 1)) {
                    {

                        {
                            double zsolqa_0_in_0 = zsolqa[(((_for_it_86 + ((5 * klon) * (_for_it_87 - 1))) + (klon * (jo - 1))) - 1)];
                            int llindex3_out_0;

                            ///////////////////
                            // Tasklet code (T_l1184_c1184)
                            llindex3_out_0 = (zsolqa_0_in_0 < 0.0);
                            ///////////////////

                            llindex3[(((_for_it_86 + ((5 * klon) * (_for_it_87 - 1))) + (klon * (jo - 1))) - 1)] = llindex3_out_0;
                        }

                    }

                }
                {

                    {
                        double tmp_call_102_out;

                        ///////////////////
                        // Tasklet code (T_l1186_c1186)
                        tmp_call_102_out = 0;
                        ///////////////////

                        tmp_call_102 = tmp_call_102_out;
                    }

                }
                for (tmp_parfor_0 = 1; (tmp_parfor_0 <= 5); tmp_parfor_0 = (tmp_parfor_0 + 1)) {
                    {

                        {
                            double tmp_call_102_0_in = tmp_call_102;
                            double zsolqa_0_in_0 = zsolqa[(((_for_it_86 + (klon * (jo - 1))) + ((5 * klon) * (tmp_parfor_0 - 1))) - 1)];
                            double tmp_call_102_out;

                            ///////////////////
                            // Tasklet code (T_l1186_c1186)
                            tmp_call_102_out = (tmp_call_102_0_in + zsolqa_0_in_0);
                            ///////////////////

                            tmp_call_102 = tmp_call_102_out;
                        }

                    }

                }
                {

                    {
                        double tmp_call_102_0_in = tmp_call_102;
                        double zsinksum_0_in_0 = zsinksum[((_for_it_86 + (klon * (jo - 1))) - 1)];
                        double zsinksum_out_0;

                        ///////////////////
                        // Tasklet code (T_l1186_c1186)
                        zsinksum_out_0 = (zsinksum_0_in_0 - tmp_call_102_0_in);
                        ///////////////////

                        zsinksum[((_for_it_86 + (klon * (jo - 1))) - 1)] = zsinksum_out_0;
                    }

                }

            }
            for (_for_it_88 = 1; (_for_it_88 <= kfdia); _for_it_88 = (_for_it_88 + 1)) {

                jo = iorder[((_for_it_88 + (klon * (_for_it_85 - 1))) - 1)];
                {
                    double zmm;
                    double zrr;

                    {
                        double zepsec_0_in = zepsec;
                        double zqx_0_in_0 = zqx[(((_for_it_88 + ((klev * klon) * (jo - 1))) + (klon * (_for_it_23 - 1))) - 1)];
                        double zmm_out;

                        ///////////////////
                        // Tasklet code (T_l1190_c1190)
                        zmm_out = max(zqx_0_in_0, zepsec_0_in);
                        ///////////////////

                        zmm = zmm_out;
                    }
                    {
                        double zmm_0_in = zmm;
                        double zsinksum_0_in_0 = zsinksum[((_for_it_88 + (klon * (jo - 1))) - 1)];
                        double zrr_out;

                        ///////////////////
                        // Tasklet code (T_l1191_c1191)
                        zrr_out = max(zsinksum_0_in_0, zmm_0_in);
                        ///////////////////

                        zrr = zrr_out;
                    }
                    {
                        double zmm_0_in = zmm;
                        double zrr_0_in = zrr;
                        double zratio_out_0;

                        ///////////////////
                        // Tasklet code (T_l1192_c1192)
                        zratio_out_0 = (zmm_0_in / zrr_0_in);
                        ///////////////////

                        zratio[((_for_it_88 + (klon * (jo - 1))) - 1)] = zratio_out_0;
                    }

                }

            }
            for (_for_it_89 = 1; (_for_it_89 <= kfdia); _for_it_89 = (_for_it_89 + 1)) {

                jo = iorder[((_for_it_89 + (klon * (_for_it_85 - 1))) - 1)];
                {

                    {
                        double zratio_0_in_0 = zratio[((_for_it_89 + (klon * (jo - 1))) - 1)];
                        double zzratio_out;

                        ///////////////////
                        // Tasklet code (T_l1196_c1196)
                        zzratio_out = zratio_0_in_0;
                        ///////////////////

                        zzratio = zzratio_out;
                    }

                }
                for (_for_it_90 = 1; (_for_it_90 <= 5); _for_it_90 = (_for_it_90 + 1)) {

                    _if_cond_77 = llindex3[(((_for_it_89 + ((5 * klon) * (_for_it_90 - 1))) + (klon * (jo - 1))) - 1)];
                    if ((_if_cond_77 == 1)) {
                        {

                            {
                                double zsolqa_0_in_0 = zsolqa[(((_for_it_89 + ((5 * klon) * (_for_it_90 - 1))) + (klon * (jo - 1))) - 1)];
                                double zzratio_0_in = zzratio;
                                double zsolqa_out_0;

                                ///////////////////
                                // Tasklet code (T_l1199_c1199)
                                zsolqa_out_0 = (zsolqa_0_in_0 * zzratio_0_in);
                                ///////////////////

                                zsolqa[(((_for_it_89 + ((5 * klon) * (_for_it_90 - 1))) + (klon * (jo - 1))) - 1)] = zsolqa_out_0;
                            }
                            {
                                double zsolqa_0_in_0 = zsolqa[(((_for_it_89 + (klon * (_for_it_90 - 1))) + ((5 * klon) * (jo - 1))) - 1)];
                                double zzratio_0_in = zzratio;
                                double zsolqa_out_0;

                                ///////////////////
                                // Tasklet code (T_l1200_c1200)
                                zsolqa_out_0 = (zsolqa_0_in_0 * zzratio_0_in);
                                ///////////////////

                                zsolqa[(((_for_it_89 + (klon * (_for_it_90 - 1))) + ((5 * klon) * (jo - 1))) - 1)] = zsolqa_out_0;
                            }

                        }
                    }

                }

            }

        }
        for (_for_it_91 = 1; (_for_it_91 <= 5); _for_it_91 = (_for_it_91 + 1)) {
            for (_for_it_92 = 1; (_for_it_92 <= 5); _for_it_92 = (_for_it_92 + 1)) {
                if (((_for_it_92 == _for_it_91) == 1)) {
                    for (_for_it_93 = 1; (_for_it_93 <= kfdia); _for_it_93 = (_for_it_93 + 1)) {
                        {

                            {
                                double zfallsink_0_in_0 = zfallsink[((_for_it_93 + (klon * (_for_it_91 - 1))) - 1)];
                                double zqlhs_out_0;

                                ///////////////////
                                // Tasklet code (T_l1209_c1209)
                                zqlhs_out_0 = (1.0 + zfallsink_0_in_0);
                                ///////////////////

                                zqlhs[(((_for_it_93 + ((5 * klon) * (_for_it_91 - 1))) + (klon * (_for_it_92 - 1))) - 1)] = zqlhs_out_0;
                            }

                        }
                        for (_for_it_94 = 1; (_for_it_94 <= 5); _for_it_94 = (_for_it_94 + 1)) {
                            {

                                {
                                    double zqlhs_0_in_0 = zqlhs[(((_for_it_93 + ((5 * klon) * (_for_it_91 - 1))) + (klon * (_for_it_92 - 1))) - 1)];
                                    double zsolqb_0_in_0 = zsolqb[(((_for_it_93 + ((5 * klon) * (_for_it_92 - 1))) + (klon * (_for_it_94 - 1))) - 1)];
                                    double zqlhs_out_0;

                                    ///////////////////
                                    // Tasklet code (T_l1211_c1211)
                                    zqlhs_out_0 = (zqlhs_0_in_0 + zsolqb_0_in_0);
                                    ///////////////////

                                    zqlhs[(((_for_it_93 + ((5 * klon) * (_for_it_91 - 1))) + (klon * (_for_it_92 - 1))) - 1)] = zqlhs_out_0;
                                }

                            }

                        }

                    }
                } else {
                    for (_for_it_95 = 1; (_for_it_95 <= kfdia); _for_it_95 = (_for_it_95 + 1)) {
                        {

                            {
                                double zsolqb_0_in_0 = zsolqb[(((_for_it_95 + ((5 * klon) * (_for_it_91 - 1))) + (klon * (_for_it_92 - 1))) - 1)];
                                double zqlhs_out_0;

                                ///////////////////
                                // Tasklet code (T_l1216_c1216)
                                zqlhs_out_0 = (- zsolqb_0_in_0);
                                ///////////////////

                                zqlhs[(((_for_it_95 + ((5 * klon) * (_for_it_91 - 1))) + (klon * (_for_it_92 - 1))) - 1)] = zqlhs_out_0;
                            }

                        }

                    }
                }

            }

        }
        for (_for_it_96 = 1; (_for_it_96 <= 5); _for_it_96 = (_for_it_96 + 1)) {
            for (_for_it_97 = 1; (_for_it_97 <= kfdia); _for_it_97 = (_for_it_97 + 1)) {
                {

                    {
                        double zexplicit_out;

                        ///////////////////
                        // Tasklet code (T_l1223_c1223)
                        zexplicit_out = 0.0;
                        ///////////////////

                        zexplicit = zexplicit_out;
                    }

                }
                for (_for_it_98 = 1; (_for_it_98 <= 5); _for_it_98 = (_for_it_98 + 1)) {
                    {

                        {
                            double zexplicit_0_in = zexplicit;
                            double zsolqa_0_in_0 = zsolqa[(((_for_it_97 + (klon * (_for_it_96 - 1))) + ((5 * klon) * (_for_it_98 - 1))) - 1)];
                            double zexplicit_out;

                            ///////////////////
                            // Tasklet code (T_l1225_c1225)
                            zexplicit_out = (zexplicit_0_in + zsolqa_0_in_0);
                            ///////////////////

                            zexplicit = zexplicit_out;
                        }

                    }

                }
                {

                    {
                        double zexplicit_0_in = zexplicit;
                        double zqx_0_in_0 = zqx[(((_for_it_97 + ((klev * klon) * (_for_it_96 - 1))) + (klon * (_for_it_23 - 1))) - 1)];
                        double zqxn_out_0;

                        ///////////////////
                        // Tasklet code (T_l1227_c1227)
                        zqxn_out_0 = (zqx_0_in_0 + zexplicit_0_in);
                        ///////////////////

                        zqxn[((_for_it_97 + (klon * (_for_it_96 - 1))) - 1)] = zqxn_out_0;
                    }

                }

            }

        }
        for (_for_it_99 = 1; (_for_it_99 <= 4); _for_it_99 = (_for_it_99 + 1)) {
            for (_for_it_100 = (_for_it_99 + 1); (_for_it_100 <= 5); _for_it_100 = (_for_it_100 + 1)) {
                for (tmp_parfor_52 = 1; (tmp_parfor_52 <= kfdia); tmp_parfor_52 = (tmp_parfor_52 + 1)) {
                    {

                        {
                            double zqlhs_0_in_0 = zqlhs[((((klon * (_for_it_100 - 1)) + ((5 * klon) * (_for_it_99 - 1))) + tmp_parfor_52) - 1)];
                            double zqlhs_1_in_0 = zqlhs[((((6 * klon) * (_for_it_99 - 1)) + tmp_parfor_52) - 1)];
                            double zqlhs_out_0;

                            ///////////////////
                            // Tasklet code (T_l1232_c1232)
                            zqlhs_out_0 = (zqlhs_0_in_0 / zqlhs_1_in_0);
                            ///////////////////

                            zqlhs[((((klon * (_for_it_100 - 1)) + ((5 * klon) * (_for_it_99 - 1))) + tmp_parfor_52) - 1)] = zqlhs_out_0;
                        }

                    }

                }
                for (_for_it_101 = (_for_it_99 + 1); (_for_it_101 <= 5); _for_it_101 = (_for_it_101 + 1)) {
                    for (_for_it_102 = 1; (_for_it_102 <= kfdia); _for_it_102 = (_for_it_102 + 1)) {
                        {

                            {
                                double zqlhs_0_in_0 = zqlhs[(((_for_it_102 + (klon * (_for_it_100 - 1))) + ((5 * klon) * (_for_it_101 - 1))) - 1)];
                                double zqlhs_1_in_0 = zqlhs[(((_for_it_102 + (klon * (_for_it_100 - 1))) + ((5 * klon) * (_for_it_99 - 1))) - 1)];
                                double zqlhs_2_in_0 = zqlhs[(((_for_it_102 + ((5 * klon) * (_for_it_101 - 1))) + (klon * (_for_it_99 - 1))) - 1)];
                                double zqlhs_out_0;

                                ///////////////////
                                // Tasklet code (T_l1235_c1235)
                                zqlhs_out_0 = (zqlhs_0_in_0 - (zqlhs_1_in_0 * zqlhs_2_in_0));
                                ///////////////////

                                zqlhs[(((_for_it_102 + (klon * (_for_it_100 - 1))) + ((5 * klon) * (_for_it_101 - 1))) - 1)] = zqlhs_out_0;
                            }

                        }

                    }

                }

            }

        }
        for (_for_it_103 = 2; (_for_it_103 <= 5); _for_it_103 = (_for_it_103 + 1)) {
            for (_for_it_104 = 1; (_for_it_104 <= (_for_it_103 - 1)); _for_it_104 = (_for_it_104 + 1)) {
                for (tmp_parfor_53 = 1; (tmp_parfor_53 <= kfdia); tmp_parfor_53 = (tmp_parfor_53 + 1)) {
                    {

                        {
                            double zqlhs_0_in_0 = zqlhs[((((klon * (_for_it_103 - 1)) + ((5 * klon) * (_for_it_104 - 1))) + tmp_parfor_53) - 1)];
                            double zqxn_0_in_0 = zqxn[(((klon * (_for_it_103 - 1)) + tmp_parfor_53) - 1)];
                            double zqxn_1_in_0 = zqxn[(((klon * (_for_it_104 - 1)) + tmp_parfor_53) - 1)];
                            double zqxn_out_0;

                            ///////////////////
                            // Tasklet code (T_l1242_c1242)
                            zqxn_out_0 = (zqxn_0_in_0 - (zqlhs_0_in_0 * zqxn_1_in_0));
                            ///////////////////

                            zqxn[(((klon * (_for_it_103 - 1)) + tmp_parfor_53) - 1)] = zqxn_out_0;
                        }

                    }

                }

            }

        }
        for (tmp_parfor_54 = 1; (tmp_parfor_54 <= kfdia); tmp_parfor_54 = (tmp_parfor_54 + 1)) {
            {

                {
                    double zqlhs_0_in_0 = zqlhs[(((24 * klon) + tmp_parfor_54) - 1)];
                    double zqxn_0_in_0 = zqxn[(((4 * klon) + tmp_parfor_54) - 1)];
                    double zqxn_out_0;

                    ///////////////////
                    // Tasklet code (T_l1245_c1245)
                    zqxn_out_0 = (zqxn_0_in_0 / zqlhs_0_in_0);
                    ///////////////////

                    zqxn[(((4 * klon) + tmp_parfor_54) - 1)] = zqxn_out_0;
                }

            }

        }
        for (_for_it_105 = 4; (_for_it_105 >= 1); _for_it_105 = (_for_it_105 + -1)) {
            for (_for_it_106 = (_for_it_105 + 1); (_for_it_106 <= 5); _for_it_106 = (_for_it_106 + 1)) {
                for (tmp_parfor_55 = 1; (tmp_parfor_55 <= kfdia); tmp_parfor_55 = (tmp_parfor_55 + 1)) {
                    {

                        {
                            double zqlhs_0_in_0 = zqlhs[((((klon * (_for_it_105 - 1)) + ((5 * klon) * (_for_it_106 - 1))) + tmp_parfor_55) - 1)];
                            double zqxn_0_in_0 = zqxn[(((klon * (_for_it_105 - 1)) + tmp_parfor_55) - 1)];
                            double zqxn_1_in_0 = zqxn[(((klon * (_for_it_106 - 1)) + tmp_parfor_55) - 1)];
                            double zqxn_out_0;

                            ///////////////////
                            // Tasklet code (T_l1248_c1248)
                            zqxn_out_0 = (zqxn_0_in_0 - (zqlhs_0_in_0 * zqxn_1_in_0));
                            ///////////////////

                            zqxn[(((klon * (_for_it_105 - 1)) + tmp_parfor_55) - 1)] = zqxn_out_0;
                        }

                    }

                }

            }
            for (tmp_parfor_56 = 1; (tmp_parfor_56 <= kfdia); tmp_parfor_56 = (tmp_parfor_56 + 1)) {
                {

                    {
                        double zqlhs_0_in_0 = zqlhs[((((6 * klon) * (_for_it_105 - 1)) + tmp_parfor_56) - 1)];
                        double zqxn_0_in_0 = zqxn[(((klon * (_for_it_105 - 1)) + tmp_parfor_56) - 1)];
                        double zqxn_out_0;

                        ///////////////////
                        // Tasklet code (T_l1250_c1250)
                        zqxn_out_0 = (zqxn_0_in_0 / zqlhs_0_in_0);
                        ///////////////////

                        zqxn[(((klon * (_for_it_105 - 1)) + tmp_parfor_56) - 1)] = zqxn_out_0;
                    }

                }

            }

        }
        for (_for_it_107 = 1; (_for_it_107 <= 4); _for_it_107 = (_for_it_107 + 1)) {
            for (_for_it_108 = 1; (_for_it_108 <= kfdia); _for_it_108 = (_for_it_108 + 1)) {

                _if_cond_79 = (zqxn[((_for_it_108 + (klon * (_for_it_107 - 1))) - 1)] < 1e-14);
                if ((_if_cond_79 == 1)) {
                    {

                        {
                            double zqxn_0_in_0 = zqxn[((_for_it_108 + (4 * klon)) - 1)];
                            double zqxn_1_in_0 = zqxn[((_for_it_108 + (klon * (_for_it_107 - 1))) - 1)];
                            double zqxn_out_0;

                            ///////////////////
                            // Tasklet code (T_l1255_c1255)
                            zqxn_out_0 = (zqxn_0_in_0 + zqxn_1_in_0);
                            ///////////////////

                            zqxn[((_for_it_108 + (4 * klon)) - 1)] = zqxn_out_0;
                        }

                    }
                    {

                        {
                            double zqxn_out_0;

                            ///////////////////
                            // Tasklet code (T_l1256_c1256)
                            zqxn_out_0 = 0.0;
                            ///////////////////

                            zqxn[((_for_it_108 + (klon * (_for_it_107 - 1))) - 1)] = zqxn_out_0;
                        }

                    }
                }

            }

        }
        for (_for_it_109 = 1; (_for_it_109 <= 5); _for_it_109 = (_for_it_109 + 1)) {
            for (_for_it_110 = 1; (_for_it_110 <= kfdia); _for_it_110 = (_for_it_110 + 1)) {
                {

                    {
                        double zqxn_0_in_0 = zqxn[((_for_it_110 + (klon * (_for_it_109 - 1))) - 1)];
                        double zqxnm1_out_0;

                        ///////////////////
                        // Tasklet code (T_l1262_c1262)
                        zqxnm1_out_0 = zqxn_0_in_0;
                        ///////////////////

                        zqxnm1[((_for_it_110 + (klon * (_for_it_109 - 1))) - 1)] = zqxnm1_out_0;
                    }
                    {
                        double zqxn_0_in_0 = zqxn[((_for_it_110 + (klon * (_for_it_109 - 1))) - 1)];
                        double zqxn2d_out_0;

                        ///////////////////
                        // Tasklet code (T_l1263_c1263)
                        zqxn2d_out_0 = zqxn_0_in_0;
                        ///////////////////

                        zqxn2d[(((_for_it_110 + ((klev * klon) * (_for_it_109 - 1))) + (klon * (_for_it_23 - 1))) - 1)] = zqxn2d_out_0;
                    }

                }

            }

        }
        for (_for_it_111 = 1; (_for_it_111 <= 5); _for_it_111 = (_for_it_111 + 1)) {
            for (_for_it_112 = 1; (_for_it_112 <= kfdia); _for_it_112 = (_for_it_112 + 1)) {
                {

                    {
                        double zfallsink_0_in_0 = zfallsink[((_for_it_112 + (klon * (_for_it_111 - 1))) - 1)];
                        double zqxn_0_in_0 = zqxn[((_for_it_112 + (klon * (_for_it_111 - 1))) - 1)];
                        double zrdtgdp_0_in_0 = zrdtgdp[(_for_it_112 - 1)];
                        double zpfplsx_out_0;

                        ///////////////////
                        // Tasklet code (T_l1268_c1268)
                        zpfplsx_out_0 = ((zfallsink_0_in_0 * zqxn_0_in_0) * zrdtgdp_0_in_0);
                        ///////////////////

                        zpfplsx[(((_for_it_112 + (_for_it_23 * klon)) + ((klon * (_for_it_111 - 1)) * (klev + 1))) - 1)] = zpfplsx_out_0;
                    }

                }

            }

        }
        for (_for_it_113 = 1; (_for_it_113 <= kfdia); _for_it_113 = (_for_it_113 + 1)) {
            {

                {
                    double zpfplsx_0_in_0 = zpfplsx[(((_for_it_113 + (_for_it_23 * klon)) + ((3 * klon) * (klev + 1))) - 1)];
                    double zpfplsx_1_in_0 = zpfplsx[(((_for_it_113 + (_for_it_23 * klon)) + ((2 * klon) * (klev + 1))) - 1)];
                    double zqpretot_out_0;

                    ///////////////////
                    // Tasklet code (T_l1272_c1272)
                    zqpretot_out_0 = (zpfplsx_0_in_0 + zpfplsx_1_in_0);
                    ///////////////////

                    zqpretot[(_for_it_113 - 1)] = zqpretot_out_0;
                }

            }

        }
        for (_for_it_114 = 1; (_for_it_114 <= kfdia); _for_it_114 = (_for_it_114 + 1)) {

            _if_cond_80 = (zqpretot[(_for_it_114 - 1)] < 1e-14);
            if ((_if_cond_80 == 1)) {
                {

                    {
                        double zcovptot_out_0;

                        ///////////////////
                        // Tasklet code (T_l1276_c1276)
                        zcovptot_out_0 = 0.0;
                        ///////////////////

                        zcovptot[(_for_it_114 - 1)] = zcovptot_out_0;
                    }

                }
            }

        }
        for (_for_it_115 = 1; (_for_it_115 <= 4); _for_it_115 = (_for_it_115 + 1)) {
            for (_for_it_116 = 1; (_for_it_116 <= kfdia); _for_it_116 = (_for_it_116 + 1)) {
                {

                    {
                        double zconvsink_0_in_0 = zconvsink[((_for_it_116 + (klon * (_for_it_115 - 1))) - 1)];
                        double zconvsrce_0_in_0 = zconvsrce[((_for_it_116 + (klon * (_for_it_115 - 1))) - 1)];
                        double zfallsink_0_in_0 = zfallsink[((_for_it_116 + (klon * (_for_it_115 - 1))) - 1)];
                        double zfallsrce_0_in_0 = zfallsrce[((_for_it_116 + (klon * (_for_it_115 - 1))) - 1)];
                        double zpsupsatsrce_0_in_0 = zpsupsatsrce[((_for_it_116 + (klon * (_for_it_115 - 1))) - 1)];
                        double zqxn_0_in_0 = zqxn[((_for_it_116 + (klon * (_for_it_115 - 1))) - 1)];
                        double zfluxq_out_0;

                        ///////////////////
                        // Tasklet code (T_l1281_c1281)
                        zfluxq_out_0 = (((zpsupsatsrce_0_in_0 + zconvsrce_0_in_0) + zfallsrce_0_in_0) - ((zfallsink_0_in_0 + zconvsink_0_in_0) * zqxn_0_in_0));
                        ///////////////////

                        zfluxq[((_for_it_116 + (klon * (_for_it_115 - 1))) - 1)] = zfluxq_out_0;
                    }

                }

            }
            _if_cond_81 = (iphase[(_for_it_115 - 1)] == 1);
            if ((_if_cond_81 == 1)) {
                for (_for_it_117 = 1; (_for_it_117 <= kfdia); _for_it_117 = (_for_it_117 + 1)) {
                    {

                        {
                            double ptendency_loc_t_0_in_0 = ptendency_loc_t[((_for_it_117 + (klon * (_for_it_23 - 1))) - 1)];
                            double ydthf_0_in_ralvdcp = v_ydthf_ralvdcp[0];
                            double zfluxq_0_in_0 = zfluxq[((_for_it_117 + (klon * (_for_it_115 - 1))) - 1)];
                            double zqtmst_0_in = zqtmst;
                            double zqx_0_in_0 = zqx[(((_for_it_117 + ((klev * klon) * (_for_it_115 - 1))) + (klon * (_for_it_23 - 1))) - 1)];
                            double zqxn_0_in_0 = zqxn[((_for_it_117 + (klon * (_for_it_115 - 1))) - 1)];
                            double ptendency_loc_t_out_0;

                            ///////////////////
                            // Tasklet code (T_l1285_c1285)
                            ptendency_loc_t_out_0 = (ptendency_loc_t_0_in_0 + ((ydthf_0_in_ralvdcp * ((zqxn_0_in_0 - zqx_0_in_0) - zfluxq_0_in_0)) * zqtmst_0_in));
                            ///////////////////

                            ptendency_loc_t[((_for_it_117 + (klon * (_for_it_23 - 1))) - 1)] = ptendency_loc_t_out_0;
                        }

                    }

                }
            }
            _if_cond_82 = (iphase[(_for_it_115 - 1)] == 2);
            if ((_if_cond_82 == 1)) {
                for (_for_it_118 = 1; (_for_it_118 <= kfdia); _for_it_118 = (_for_it_118 + 1)) {
                    {

                        {
                            double ptendency_loc_t_0_in_0 = ptendency_loc_t[((_for_it_118 + (klon * (_for_it_23 - 1))) - 1)];
                            double ydthf_0_in_ralsdcp = v_ydthf_ralsdcp[0];
                            double zfluxq_0_in_0 = zfluxq[((_for_it_118 + (klon * (_for_it_115 - 1))) - 1)];
                            double zqtmst_0_in = zqtmst;
                            double zqx_0_in_0 = zqx[(((_for_it_118 + ((klev * klon) * (_for_it_115 - 1))) + (klon * (_for_it_23 - 1))) - 1)];
                            double zqxn_0_in_0 = zqxn[((_for_it_118 + (klon * (_for_it_115 - 1))) - 1)];
                            double ptendency_loc_t_out_0;

                            ///////////////////
                            // Tasklet code (T_l1290_c1290)
                            ptendency_loc_t_out_0 = (ptendency_loc_t_0_in_0 + ((ydthf_0_in_ralsdcp * ((zqxn_0_in_0 - zqx_0_in_0) - zfluxq_0_in_0)) * zqtmst_0_in));
                            ///////////////////

                            ptendency_loc_t[((_for_it_118 + (klon * (_for_it_23 - 1))) - 1)] = ptendency_loc_t_out_0;
                        }

                    }

                }
            }
            for (_for_it_119 = 1; (_for_it_119 <= kfdia); _for_it_119 = (_for_it_119 + 1)) {
                {

                    {
                        double ptendency_loc_cld_0_in_0 = ptendency_loc_cld[(((_for_it_119 + ((klev * klon) * (_for_it_115 - 1))) + (klon * (_for_it_23 - 1))) - 1)];
                        double zqtmst_0_in = zqtmst;
                        double zqx0_0_in_0 = zqx0[(((_for_it_119 + ((klev * klon) * (_for_it_115 - 1))) + (klon * (_for_it_23 - 1))) - 1)];
                        double zqxn_0_in_0 = zqxn[((_for_it_119 + (klon * (_for_it_115 - 1))) - 1)];
                        double ptendency_loc_cld_out_0;

                        ///////////////////
                        // Tasklet code (T_l1294_c1294)
                        ptendency_loc_cld_out_0 = (ptendency_loc_cld_0_in_0 + ((zqxn_0_in_0 - zqx0_0_in_0) * zqtmst_0_in));
                        ///////////////////

                        ptendency_loc_cld[(((_for_it_119 + ((klev * klon) * (_for_it_115 - 1))) + (klon * (_for_it_23 - 1))) - 1)] = ptendency_loc_cld_out_0;
                    }

                }

            }

        }
        for (_for_it_120 = 1; (_for_it_120 <= kfdia); _for_it_120 = (_for_it_120 + 1)) {
            {

                {
                    double ptendency_loc_q_0_in_0 = ptendency_loc_q[((_for_it_120 + (klon * (_for_it_23 - 1))) - 1)];
                    double zqtmst_0_in = zqtmst;
                    double zqx_0_in_0 = zqx[(((_for_it_120 + ((4 * klev) * klon)) + (klon * (_for_it_23 - 1))) - 1)];
                    double zqxn_0_in_0 = zqxn[((_for_it_120 + (4 * klon)) - 1)];
                    double ptendency_loc_q_out_0;

                    ///////////////////
                    // Tasklet code (T_l1298_c1298)
                    ptendency_loc_q_out_0 = (ptendency_loc_q_0_in_0 + ((zqxn_0_in_0 - zqx_0_in_0) * zqtmst_0_in));
                    ///////////////////

                    ptendency_loc_q[((_for_it_120 + (klon * (_for_it_23 - 1))) - 1)] = ptendency_loc_q_out_0;
                }
                {
                    double ptendency_loc_a_0_in_0 = ptendency_loc_a[((_for_it_120 + (klon * (_for_it_23 - 1))) - 1)];
                    double zda_0_in_0 = zda[(_for_it_120 - 1)];
                    double zqtmst_0_in = zqtmst;
                    double ptendency_loc_a_out_0;

                    ///////////////////
                    // Tasklet code (T_l1299_c1299)
                    ptendency_loc_a_out_0 = (ptendency_loc_a_0_in_0 + (zda_0_in_0 * zqtmst_0_in));
                    ///////////////////

                    ptendency_loc_a[((_for_it_120 + (klon * (_for_it_23 - 1))) - 1)] = ptendency_loc_a_out_0;
                }

            }

        }
        for (_for_it_121 = 1; (_for_it_121 <= kfdia); _for_it_121 = (_for_it_121 + 1)) {
            {

                {
                    double zcovptot_0_in_0 = zcovptot[(_for_it_121 - 1)];
                    double pcovptot_out_0;

                    ///////////////////
                    // Tasklet code (T_l1302_c1302)
                    pcovptot_out_0 = zcovptot_0_in_0;
                    ///////////////////

                    pcovptot[((_for_it_121 + (klon * (_for_it_23 - 1))) - 1)] = pcovptot_out_0;
                }

            }

        }

    }

    for (_for_it_122 = 1; (_for_it_122 <= (klev + 1)); _for_it_122 = (_for_it_122 + 1)) {
        for (_for_it_123 = 1; (_for_it_123 <= kfdia); _for_it_123 = (_for_it_123 + 1)) {
            {

                {
                    double zpfplsx_0_in_0 = zpfplsx[(((_for_it_123 + (klon * (_for_it_122 - 1))) + ((2 * klon) * (klev + 1))) - 1)];
                    double zpfplsx_1_in_0 = zpfplsx[((_for_it_123 + (klon * (_for_it_122 - 1))) - 1)];
                    double pfplsl_out_0;

                    ///////////////////
                    // Tasklet code (T_l1307_c1307)
                    pfplsl_out_0 = (zpfplsx_0_in_0 + zpfplsx_1_in_0);
                    ///////////////////

                    pfplsl[((_for_it_123 + (klon * (_for_it_122 - 1))) - 1)] = pfplsl_out_0;
                }
                {
                    double zpfplsx_0_in_0 = zpfplsx[(((_for_it_123 + (klon * (_for_it_122 - 1))) + ((3 * klon) * (klev + 1))) - 1)];
                    double zpfplsx_1_in_0 = zpfplsx[(((_for_it_123 + (klon * (_for_it_122 - 1))) + (klon * (klev + 1))) - 1)];
                    double pfplsn_out_0;

                    ///////////////////
                    // Tasklet code (T_l1308_c1308)
                    pfplsn_out_0 = (zpfplsx_0_in_0 + zpfplsx_1_in_0);
                    ///////////////////

                    pfplsn[((_for_it_123 + (klon * (_for_it_122 - 1))) - 1)] = pfplsn_out_0;
                }

            }

        }

    }

    for (_for_it_124 = 1; (_for_it_124 <= kfdia); _for_it_124 = (_for_it_124 + 1)) {
        {

            {
                double pfsqlf_out_0;

                ///////////////////
                // Tasklet code (T_l1312_c1312)
                pfsqlf_out_0 = 0.0;
                ///////////////////

                pfsqlf[(_for_it_124 - 1)] = pfsqlf_out_0;
            }
            {
                double pfsqif_out_0;

                ///////////////////
                // Tasklet code (T_l1313_c1313)
                pfsqif_out_0 = 0.0;
                ///////////////////

                pfsqif[(_for_it_124 - 1)] = pfsqif_out_0;
            }
            {
                double pfsqrf_out_0;

                ///////////////////
                // Tasklet code (T_l1314_c1314)
                pfsqrf_out_0 = 0.0;
                ///////////////////

                pfsqrf[(_for_it_124 - 1)] = pfsqrf_out_0;
            }
            {
                double pfsqsf_out_0;

                ///////////////////
                // Tasklet code (T_l1315_c1315)
                pfsqsf_out_0 = 0.0;
                ///////////////////

                pfsqsf[(_for_it_124 - 1)] = pfsqsf_out_0;
            }
            {
                double pfcqlng_out_0;

                ///////////////////
                // Tasklet code (T_l1316_c1316)
                pfcqlng_out_0 = 0.0;
                ///////////////////

                pfcqlng[(_for_it_124 - 1)] = pfcqlng_out_0;
            }
            {
                double pfcqnng_out_0;

                ///////////////////
                // Tasklet code (T_l1317_c1317)
                pfcqnng_out_0 = 0.0;
                ///////////////////

                pfcqnng[(_for_it_124 - 1)] = pfcqnng_out_0;
            }
            {
                double pfcqrng_out_0;

                ///////////////////
                // Tasklet code (T_l1318_c1318)
                pfcqrng_out_0 = 0.0;
                ///////////////////

                pfcqrng[(_for_it_124 - 1)] = pfcqrng_out_0;
            }
            {
                double pfcqsng_out_0;

                ///////////////////
                // Tasklet code (T_l1319_c1319)
                pfcqsng_out_0 = 0.0;
                ///////////////////

                pfcqsng[(_for_it_124 - 1)] = pfcqsng_out_0;
            }
            {
                double pfsqltur_out_0;

                ///////////////////
                // Tasklet code (T_l1320_c1320)
                pfsqltur_out_0 = 0.0;
                ///////////////////

                pfsqltur[(_for_it_124 - 1)] = pfsqltur_out_0;
            }
            {
                double pfsqitur_out_0;

                ///////////////////
                // Tasklet code (T_l1321_c1321)
                pfsqitur_out_0 = 0.0;
                ///////////////////

                pfsqitur[(_for_it_124 - 1)] = pfsqitur_out_0;
            }

        }

    }

    for (_for_it_125 = 1; (_for_it_125 <= klev); _for_it_125 = (_for_it_125 + 1)) {
        for (_for_it_126 = 1; (_for_it_126 <= kfdia); _for_it_126 = (_for_it_126 + 1)) {

            zalfaw = zfoealfa[((_for_it_126 + (klon * (_for_it_125 - 1))) - 1)];
            {

                {
                    double paph_0_in_0 = paph[(((_for_it_125 * klon) + _for_it_126) - 1)];
                    double paph_1_in_0 = paph[((_for_it_126 + (klon * (_for_it_125 - 1))) - 1)];
                    double zqtmst_0_in = zqtmst;
                    double zrg_r_0_in = zrg_r;
                    double zgdph_r_out;

                    ///////////////////
                    // Tasklet code (T_l1325_c1325)
                    zgdph_r_out = (- ((zrg_r_0_in * (paph_0_in_0 - paph_1_in_0)) * zqtmst_0_in));
                    ///////////////////

                    zgdph_r = zgdph_r_out;
                }
                {
                    double pfsqlf_0_in_0 = pfsqlf[((_for_it_126 + (klon * (_for_it_125 - 1))) - 1)];
                    double pfsqlf_out_0;

                    ///////////////////
                    // Tasklet code (T_l1326_c1326)
                    pfsqlf_out_0 = pfsqlf_0_in_0;
                    ///////////////////

                    pfsqlf[(((_for_it_125 * klon) + _for_it_126) - 1)] = pfsqlf_out_0;
                }
                {
                    double pfsqlf_0_in_0 = pfsqlf[((_for_it_126 + (klon * (_for_it_125 - 1))) - 1)];
                    double pfsqrf_out_0;

                    ///////////////////
                    // Tasklet code (T_l1328_c1328)
                    pfsqrf_out_0 = pfsqlf_0_in_0;
                    ///////////////////

                    pfsqrf[(((_for_it_125 * klon) + _for_it_126) - 1)] = pfsqrf_out_0;
                }
                {
                    double pfsqif_0_in_0 = pfsqif[((_for_it_126 + (klon * (_for_it_125 - 1))) - 1)];
                    double pfsqif_out_0;

                    ///////////////////
                    // Tasklet code (T_l1327_c1327)
                    pfsqif_out_0 = pfsqif_0_in_0;
                    ///////////////////

                    pfsqif[(((_for_it_125 * klon) + _for_it_126) - 1)] = pfsqif_out_0;
                }
                {
                    double pfsqif_0_in_0 = pfsqif[((_for_it_126 + (klon * (_for_it_125 - 1))) - 1)];
                    double pfsqsf_out_0;

                    ///////////////////
                    // Tasklet code (T_l1329_c1329)
                    pfsqsf_out_0 = pfsqif_0_in_0;
                    ///////////////////

                    pfsqsf[(((_for_it_125 * klon) + _for_it_126) - 1)] = pfsqsf_out_0;
                }
                {
                    double pfcqlng_0_in_0 = pfcqlng[((_for_it_126 + (klon * (_for_it_125 - 1))) - 1)];
                    double pfcqlng_out_0;

                    ///////////////////
                    // Tasklet code (T_l1330_c1330)
                    pfcqlng_out_0 = pfcqlng_0_in_0;
                    ///////////////////

                    pfcqlng[(((_for_it_125 * klon) + _for_it_126) - 1)] = pfcqlng_out_0;
                }
                {
                    double pfcqlng_0_in_0 = pfcqlng[((_for_it_126 + (klon * (_for_it_125 - 1))) - 1)];
                    double pfcqrng_out_0;

                    ///////////////////
                    // Tasklet code (T_l1332_c1332)
                    pfcqrng_out_0 = pfcqlng_0_in_0;
                    ///////////////////

                    pfcqrng[(((_for_it_125 * klon) + _for_it_126) - 1)] = pfcqrng_out_0;
                }
                {
                    double pfcqnng_0_in_0 = pfcqnng[((_for_it_126 + (klon * (_for_it_125 - 1))) - 1)];
                    double pfcqnng_out_0;

                    ///////////////////
                    // Tasklet code (T_l1331_c1331)
                    pfcqnng_out_0 = pfcqnng_0_in_0;
                    ///////////////////

                    pfcqnng[(((_for_it_125 * klon) + _for_it_126) - 1)] = pfcqnng_out_0;
                }
                {
                    double pfcqnng_0_in_0 = pfcqnng[((_for_it_126 + (klon * (_for_it_125 - 1))) - 1)];
                    double pfcqsng_out_0;

                    ///////////////////
                    // Tasklet code (T_l1333_c1333)
                    pfcqsng_out_0 = pfcqnng_0_in_0;
                    ///////////////////

                    pfcqsng[(((_for_it_125 * klon) + _for_it_126) - 1)] = pfcqsng_out_0;
                }
                {
                    double pfsqltur_0_in_0 = pfsqltur[((_for_it_126 + (klon * (_for_it_125 - 1))) - 1)];
                    double pfsqltur_out_0;

                    ///////////////////
                    // Tasklet code (T_l1334_c1334)
                    pfsqltur_out_0 = pfsqltur_0_in_0;
                    ///////////////////

                    pfsqltur[(((_for_it_125 * klon) + _for_it_126) - 1)] = pfsqltur_out_0;
                }
                {
                    double pfsqitur_0_in_0 = pfsqitur[((_for_it_126 + (klon * (_for_it_125 - 1))) - 1)];
                    double pfsqitur_out_0;

                    ///////////////////
                    // Tasklet code (T_l1335_c1335)
                    pfsqitur_out_0 = pfsqitur_0_in_0;
                    ///////////////////

                    pfsqitur[(((_for_it_125 * klon) + _for_it_126) - 1)] = pfsqitur_out_0;
                }

            }
            {

                {
                    double pfsqlf_0_in_0 = pfsqlf[(((_for_it_125 * klon) + _for_it_126) - 1)];
                    double plude_0_in_0 = plude[((_for_it_126 + (klon * (_for_it_125 - 1))) - 1)];
                    double ptsphy_0_in = ptsphy;
                    double pvfl_0_in_0 = pvfl[((_for_it_126 + (klon * (_for_it_125 - 1))) - 1)];
                    double zgdph_r_0_in = zgdph_r;
                    double zqx0_0_in_0 = zqx0[((_for_it_126 + (klon * (_for_it_125 - 1))) - 1)];
                    double zqxn2d_0_in_0 = zqxn2d[((_for_it_126 + (klon * (_for_it_125 - 1))) - 1)];
                    double pfsqlf_out_0;

                    ///////////////////
                    // Tasklet code (T_l1337_c1337)
                    pfsqlf_out_0 = (pfsqlf_0_in_0 + ((((zqxn2d_0_in_0 - zqx0_0_in_0) + (pvfl_0_in_0 * ptsphy_0_in)) - (zalfaw * plude_0_in_0)) * zgdph_r_0_in));
                    ///////////////////

                    pfsqlf[(((_for_it_125 * klon) + _for_it_126) - 1)] = pfsqlf_out_0;
                }
                {
                    double pfsqrf_0_in_0 = pfsqrf[(((_for_it_125 * klon) + _for_it_126) - 1)];
                    double zgdph_r_0_in = zgdph_r;
                    double zqx0_0_in_0 = zqx0[(((_for_it_126 + ((2 * klev) * klon)) + (klon * (_for_it_125 - 1))) - 1)];
                    double zqxn2d_0_in_0 = zqxn2d[(((_for_it_126 + ((2 * klev) * klon)) + (klon * (_for_it_125 - 1))) - 1)];
                    double pfsqrf_out_0;

                    ///////////////////
                    // Tasklet code (T_l1340_c1340)
                    pfsqrf_out_0 = (pfsqrf_0_in_0 + ((zqxn2d_0_in_0 - zqx0_0_in_0) * zgdph_r_0_in));
                    ///////////////////

                    pfsqrf[(((_for_it_125 * klon) + _for_it_126) - 1)] = pfsqrf_out_0;
                }
                {
                    double pfsqif_0_in_0 = pfsqif[(((_for_it_125 * klon) + _for_it_126) - 1)];
                    double plude_0_in_0 = plude[((_for_it_126 + (klon * (_for_it_125 - 1))) - 1)];
                    double ptsphy_0_in = ptsphy;
                    double pvfi_0_in_0 = pvfi[((_for_it_126 + (klon * (_for_it_125 - 1))) - 1)];
                    double zgdph_r_0_in = zgdph_r;
                    double zqx0_0_in_0 = zqx0[(((_for_it_126 + (klev * klon)) + (klon * (_for_it_125 - 1))) - 1)];
                    double zqxn2d_0_in_0 = zqxn2d[(((_for_it_126 + (klev * klon)) + (klon * (_for_it_125 - 1))) - 1)];
                    double pfsqif_out_0;

                    ///////////////////
                    // Tasklet code (T_l1342_c1342)
                    pfsqif_out_0 = (pfsqif_0_in_0 + ((((zqxn2d_0_in_0 - zqx0_0_in_0) + (pvfi_0_in_0 * ptsphy_0_in)) - ((1.0 - zalfaw) * plude_0_in_0)) * zgdph_r_0_in));
                    ///////////////////

                    pfsqif[(((_for_it_125 * klon) + _for_it_126) - 1)] = pfsqif_out_0;
                }
                {
                    double pfsqsf_0_in_0 = pfsqsf[(((_for_it_125 * klon) + _for_it_126) - 1)];
                    double zgdph_r_0_in = zgdph_r;
                    double zqx0_0_in_0 = zqx0[(((_for_it_126 + ((3 * klev) * klon)) + (klon * (_for_it_125 - 1))) - 1)];
                    double zqxn2d_0_in_0 = zqxn2d[(((_for_it_126 + ((3 * klev) * klon)) + (klon * (_for_it_125 - 1))) - 1)];
                    double pfsqsf_out_0;

                    ///////////////////
                    // Tasklet code (T_l1345_c1345)
                    pfsqsf_out_0 = (pfsqsf_0_in_0 + ((zqxn2d_0_in_0 - zqx0_0_in_0) * zgdph_r_0_in));
                    ///////////////////

                    pfsqsf[(((_for_it_125 * klon) + _for_it_126) - 1)] = pfsqsf_out_0;
                }
                {
                    double pfsqltur_0_in_0 = pfsqltur[(((_for_it_125 * klon) + _for_it_126) - 1)];
                    double ptsphy_0_in = ptsphy;
                    double pvfl_0_in_0 = pvfl[((_for_it_126 + (klon * (_for_it_125 - 1))) - 1)];
                    double zgdph_r_0_in = zgdph_r;
                    double pfsqltur_out_0;

                    ///////////////////
                    // Tasklet code (T_l1339_c1339)
                    pfsqltur_out_0 = (pfsqltur_0_in_0 + ((pvfl_0_in_0 * ptsphy_0_in) * zgdph_r_0_in));
                    ///////////////////

                    pfsqltur[(((_for_it_125 * klon) + _for_it_126) - 1)] = pfsqltur_out_0;
                }
                {
                    double pfsqitur_0_in_0 = pfsqitur[(((_for_it_125 * klon) + _for_it_126) - 1)];
                    double ptsphy_0_in = ptsphy;
                    double pvfi_0_in_0 = pvfi[((_for_it_126 + (klon * (_for_it_125 - 1))) - 1)];
                    double zgdph_r_0_in = zgdph_r;
                    double pfsqitur_out_0;

                    ///////////////////
                    // Tasklet code (T_l1344_c1344)
                    pfsqitur_out_0 = (pfsqitur_0_in_0 + ((pvfi_0_in_0 * ptsphy_0_in) * zgdph_r_0_in));
                    ///////////////////

                    pfsqitur[(((_for_it_125 * klon) + _for_it_126) - 1)] = pfsqitur_out_0;
                }
                {
                    double pfcqlng_0_in_0 = pfcqlng[(((_for_it_125 * klon) + _for_it_126) - 1)];
                    double zgdph_r_0_in = zgdph_r;
                    double zlneg_0_in_0 = zlneg[((_for_it_126 + (klon * (_for_it_125 - 1))) - 1)];
                    double pfcqlng_out_0;

                    ///////////////////
                    // Tasklet code (T_l1338_c1338)
                    pfcqlng_out_0 = (pfcqlng_0_in_0 + (zlneg_0_in_0 * zgdph_r_0_in));
                    ///////////////////

                    pfcqlng[(((_for_it_125 * klon) + _for_it_126) - 1)] = pfcqlng_out_0;
                }
                {
                    double pfcqrng_0_in_0 = pfcqrng[(((_for_it_125 * klon) + _for_it_126) - 1)];
                    double zgdph_r_0_in = zgdph_r;
                    double zlneg_0_in_0 = zlneg[(((_for_it_126 + ((2 * klev) * klon)) + (klon * (_for_it_125 - 1))) - 1)];
                    double pfcqrng_out_0;

                    ///////////////////
                    // Tasklet code (T_l1341_c1341)
                    pfcqrng_out_0 = (pfcqrng_0_in_0 + (zlneg_0_in_0 * zgdph_r_0_in));
                    ///////////////////

                    pfcqrng[(((_for_it_125 * klon) + _for_it_126) - 1)] = pfcqrng_out_0;
                }
                {
                    double pfcqnng_0_in_0 = pfcqnng[(((_for_it_125 * klon) + _for_it_126) - 1)];
                    double zgdph_r_0_in = zgdph_r;
                    double zlneg_0_in_0 = zlneg[(((_for_it_126 + (klev * klon)) + (klon * (_for_it_125 - 1))) - 1)];
                    double pfcqnng_out_0;

                    ///////////////////
                    // Tasklet code (T_l1343_c1343)
                    pfcqnng_out_0 = (pfcqnng_0_in_0 + (zlneg_0_in_0 * zgdph_r_0_in));
                    ///////////////////

                    pfcqnng[(((_for_it_125 * klon) + _for_it_126) - 1)] = pfcqnng_out_0;
                }
                {
                    double pfcqsng_0_in_0 = pfcqsng[(((_for_it_125 * klon) + _for_it_126) - 1)];
                    double zgdph_r_0_in = zgdph_r;
                    double zlneg_0_in_0 = zlneg[(((_for_it_126 + ((3 * klev) * klon)) + (klon * (_for_it_125 - 1))) - 1)];
                    double pfcqsng_out_0;

                    ///////////////////
                    // Tasklet code (T_l1346_c1346)
                    pfcqsng_out_0 = (pfcqsng_0_in_0 + (zlneg_0_in_0 * zgdph_r_0_in));
                    ///////////////////

                    pfcqsng[(((_for_it_125 * klon) + _for_it_126) - 1)] = pfcqsng_out_0;
                }

            }

        }

    }

    for (_for_it_127 = 1; (_for_it_127 <= (klev + 1)); _for_it_127 = (_for_it_127 + 1)) {
        for (_for_it_128 = 1; (_for_it_128 <= kfdia); _for_it_128 = (_for_it_128 + 1)) {
            {
                double* v_ydcst_rlvtt;
                v_ydcst_rlvtt = (double*)(&(ydcst->rlvtt));

                {
                    double pfplsl_0_in_0 = pfplsl[((_for_it_128 + (klon * (_for_it_127 - 1))) - 1)];
                    double ydcst_0_in_rlvtt = v_ydcst_rlvtt[0];
                    double pfhpsl_out_0;

                    ///////////////////
                    // Tasklet code (T_l1351_c1351)
                    pfhpsl_out_0 = (- (ydcst_0_in_rlvtt * pfplsl_0_in_0));
                    ///////////////////

                    pfhpsl[((_for_it_128 + (klon * (_for_it_127 - 1))) - 1)] = pfhpsl_out_0;
                }
                {
                    double pfplsn_0_in_0 = pfplsn[((_for_it_128 + (klon * (_for_it_127 - 1))) - 1)];
                    double ydcst_0_in_rlstt = v_ydcst_rlstt[0];
                    double pfhpsn_out_0;

                    ///////////////////
                    // Tasklet code (T_l1352_c1352)
                    pfhpsn_out_0 = (- (ydcst_0_in_rlstt * pfplsn_0_in_0));
                    ///////////////////

                    pfhpsn[((_for_it_128 + (klon * (_for_it_127 - 1))) - 1)] = pfhpsn_out_0;
                }

            }

        }

    }

    delete[] zlcond1;
    delete[] zlcond2;
    delete[] zrainaut;
    delete[] zsnowaut;
    delete[] zliqcld;
    delete[] zicecld;
    delete[] zfokoop;
    delete[] zfoealfa;
    delete[] zicenuclei;
    delete[] zlicld;
    delete[] zlfinalsum;
    delete[] zdqs;
    delete[] ztold;
    delete[] zqold;
    delete[] zdtgdp;
    delete[] zrdtgdp;
    delete[] zcovpclr;
    delete[] zcovptot;
    delete[] zcovpmax;
    delete[] zqpretot;
    delete[] ztp1;
    delete[] zldefr;
    delete[] zldifdt;
    delete[] zlcust;
    delete[] zacust;
    delete[] zmf;
    delete[] zrho;
    delete[] zsolab;
    delete[] zsolac;
    delete[] zanewm1;
    delete[] zda;
    delete[] zli;
    delete[] za;
    delete[] zaorig;
    delete[] zdp;
    delete[] zmin;
    delete[] zsupsat;
    delete[] iphase;
    delete[] imelt;
    delete[] llfall;
    delete[] llindex1;
    delete[] llindex3;
    delete[] iorder;
    delete[] zliqfrac;
    delete[] zicefrac;
    delete[] zqx;
    delete[] zqx0;
    delete[] zqxn;
    delete[] zqxfg;
    delete[] zqxnm1;
    delete[] zfluxq;
    delete[] zpfplsx;
    delete[] zlneg;
    delete[] zmeltmax;
    delete[] zfrzmax;
    delete[] zicetot;
    delete[] zqxn2d;
    delete[] zqsmix;
    delete[] zqsliq;
    delete[] zqsice;
    delete[] zfoeewmt;
    delete[] zfoeew;
    delete[] zfoeeliqt;
    delete[] zdqsmixdt;
    delete[] zcorqsice;
    delete[] zevaplimmix;
    delete[] zsolqa;
    delete[] zsolqb;
    delete[] zqlhs;
    delete[] zvqx;
    delete[] zratio;
    delete[] zsinksum;
    delete[] zfallsink;
    delete[] zfallsrce;
    delete[] zconvsrce;
    delete[] zconvsink;
    delete[] zpsupsatsrce;
    delete[] zcldtopdist;
    delete[] zrainacc;
    delete[] zraincld;
    delete[] zsnowcld;
    delete[] llrainliq;
}

DACE_EXPORTED void __program_cloudsc(cloudsc_state_t *__state, int * __restrict__ ktype, int * __restrict__ ldcum, double * __restrict__ pa, double * __restrict__ pap, double * __restrict__ paph, double * __restrict__ pccn, double * __restrict__ pclv, double * __restrict__ pcovptot, double * __restrict__ pdyna, double * __restrict__ pdyni, double * __restrict__ pdynl, double * __restrict__ pfcqlng, double * __restrict__ pfcqnng, double * __restrict__ pfcqrng, double * __restrict__ pfcqsng, double * __restrict__ pfhpsl, double * __restrict__ pfhpsn, double * __restrict__ pfplsl, double * __restrict__ pfplsn, double * __restrict__ pfsqif, double * __restrict__ pfsqitur, double * __restrict__ pfsqlf, double * __restrict__ pfsqltur, double * __restrict__ pfsqrf, double * __restrict__ pfsqsf, double * __restrict__ phrlw, double * __restrict__ phrsw, double * __restrict__ picrit_aer, double * __restrict__ plcrit_aer, double * __restrict__ plsm, double * __restrict__ plu, double * __restrict__ plude, double * __restrict__ pmfd, double * __restrict__ pmfu, double * __restrict__ pnice, double * __restrict__ pq, double * __restrict__ prainfrac_toprfz, double * __restrict__ pre_ice, double * __restrict__ psnde, double * __restrict__ psupsat, double * __restrict__ pt, double * __restrict__ ptendency_loc_a, double * __restrict__ ptendency_loc_cld, double * __restrict__ ptendency_loc_q, double * __restrict__ ptendency_loc_t, double * __restrict__ ptendency_tmp_a, double * __restrict__ ptendency_tmp_cld, double * __restrict__ ptendency_tmp_q, double * __restrict__ ptendency_tmp_t, double * __restrict__ pvervel, double * __restrict__ pvfa, double * __restrict__ pvfi, double * __restrict__ pvfl, tomcst* ydcst, tecldp* ydecldp, toethf* ydthf, int kfdia, int kfldx, int kidia, int klev, int klon, double ptsphy)
{
    __program_cloudsc_internal(__state, ktype, ldcum, pa, pap, paph, pccn, pclv, pcovptot, pdyna, pdyni, pdynl, pfcqlng, pfcqnng, pfcqrng, pfcqsng, pfhpsl, pfhpsn, pfplsl, pfplsn, pfsqif, pfsqitur, pfsqlf, pfsqltur, pfsqrf, pfsqsf, phrlw, phrsw, picrit_aer, plcrit_aer, plsm, plu, plude, pmfd, pmfu, pnice, pq, prainfrac_toprfz, pre_ice, psnde, psupsat, pt, ptendency_loc_a, ptendency_loc_cld, ptendency_loc_q, ptendency_loc_t, ptendency_tmp_a, ptendency_tmp_cld, ptendency_tmp_q, ptendency_tmp_t, pvervel, pvfa, pvfi, pvfl, ydcst, ydecldp, ydthf, kfdia, kfldx, kidia, klev, klon, ptsphy);
}

DACE_EXPORTED cloudsc_state_t *__dace_init_cloudsc(int * __restrict__ ktype, int * __restrict__ ldcum, double * __restrict__ pa, double * __restrict__ pap, double * __restrict__ paph, double * __restrict__ pccn, double * __restrict__ pclv, double * __restrict__ pcovptot, double * __restrict__ pdyna, double * __restrict__ pdyni, double * __restrict__ pdynl, double * __restrict__ pfcqlng, double * __restrict__ pfcqnng, double * __restrict__ pfcqrng, double * __restrict__ pfcqsng, double * __restrict__ pfhpsl, double * __restrict__ pfhpsn, double * __restrict__ pfplsl, double * __restrict__ pfplsn, double * __restrict__ pfsqif, double * __restrict__ pfsqitur, double * __restrict__ pfsqlf, double * __restrict__ pfsqltur, double * __restrict__ pfsqrf, double * __restrict__ pfsqsf, double * __restrict__ phrlw, double * __restrict__ phrsw, double * __restrict__ picrit_aer, double * __restrict__ plcrit_aer, double * __restrict__ plsm, double * __restrict__ plu, double * __restrict__ plude, double * __restrict__ pmfd, double * __restrict__ pmfu, double * __restrict__ pnice, double * __restrict__ pq, double * __restrict__ prainfrac_toprfz, double * __restrict__ pre_ice, double * __restrict__ psnde, double * __restrict__ psupsat, double * __restrict__ pt, double * __restrict__ ptendency_loc_a, double * __restrict__ ptendency_loc_cld, double * __restrict__ ptendency_loc_q, double * __restrict__ ptendency_loc_t, double * __restrict__ ptendency_tmp_a, double * __restrict__ ptendency_tmp_cld, double * __restrict__ ptendency_tmp_q, double * __restrict__ ptendency_tmp_t, double * __restrict__ pvervel, double * __restrict__ pvfa, double * __restrict__ pvfi, double * __restrict__ pvfl, tomcst* ydcst, tecldp* ydecldp, toethf* ydthf, int kfdia, int kfldx, int kidia, int klev, int klon, double ptsphy)
{
    int __result = 0;
    cloudsc_state_t *__state = new cloudsc_state_t;



    if (__result) {
        delete __state;
        return nullptr;
    }
    return __state;
}

DACE_EXPORTED int __dace_exit_cloudsc(cloudsc_state_t *__state)
{
    int __err = 0;
    delete __state;
    return __err;
}
