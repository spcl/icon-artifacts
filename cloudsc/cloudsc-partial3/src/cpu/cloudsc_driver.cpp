/* DaCe AUTO-GENERATED FILE. DO NOT MODIFY */
#include <dace/dace.h>

#include "../../../struct_defs.h"
#include "../../include/hash.h"

inline void mycloudsc0_1_3_123(
    cloudsc_driver_state_t* __state, const int* __restrict__ kfldx_var_28, const int* __restrict__ klev, const int* __restrict__ klon, int* __restrict__ ktype_var_21, int* __restrict__ ldcum_var_20,
    double* __restrict__ pa_var_27, double* __restrict__ pap_var_17, double* __restrict__ paph_var_18, double* __restrict__ pccn_var_3, double* __restrict__ pclv_var_29,
    double* __restrict__ pdyna_var_11, double* __restrict__ pdyni_var_13, double* __restrict__ pdynl_var_12, double* __restrict__ phrlw_var_15, double* __restrict__ phrsw_var_14,
    double* __restrict__ picrit_aer_var_1, double* __restrict__ plcrit_aer_var_0, double* __restrict__ plsm_var_19, double* __restrict__ plu_var_22, double* __restrict__ pmfd_var_26,
    double* __restrict__ pmfu_var_25, double* __restrict__ pnice_var_4, double* __restrict__ pq_var_7, double* __restrict__ pre_ice_var_2, double* __restrict__ psnde_var_24,
    double* __restrict__ psupsat_var_30, double* __restrict__ pt_var_6, double* __restrict__ ptendency_tmp_a, double* __restrict__ ptendency_tmp_cld, double* __restrict__ ptendency_tmp_q,
    double* __restrict__ ptendency_tmp_t, const double* __restrict__ ptsphy_var_5, double* __restrict__ pvervel_var_16, double* __restrict__ pvfa_var_8, double* __restrict__ pvfi_var_10,
    double* __restrict__ pvfl_var_9, double* __restrict__ pcovptot_var_31, double* __restrict__ pfcqlng_var_35, double* __restrict__ pfcqnng_var_36, double* __restrict__ pfcqrng_var_39,
    double* __restrict__ pfcqsng_var_40, double* __restrict__ pfhpsl_var_45, double* __restrict__ pfhpsn_var_46, double* __restrict__ pfplsl_var_43, double* __restrict__ pfplsn_var_44,
    double* __restrict__ pfsqif_var_34, double* __restrict__ pfsqitur_var_42, double* __restrict__ pfsqlf_var_33, double* __restrict__ pfsqltur_var_41, double* __restrict__ pfsqrf_var_37,
    double* __restrict__ pfsqsf_var_38, double* __restrict__ plude_var_23, double* __restrict__ prainfrac_toprfz_var_32, double* __restrict__ ptendency_loc_a, double* __restrict__ ptendency_loc_cld,
    double* __restrict__ ptendency_loc_q, double* __restrict__ ptendency_loc_t, tomcst* __restrict__ ydcst_var_47, tecldp* __restrict__ ydecldp_var_49, toethf* __restrict__ ydthf_var_48, int icend,
    int sym_klev, int sym_klon) {
    double* zlcond1;
    zlcond1 = new double DACE_ALIGN(64)[sym_klon];
    double* zlcond2;
    zlcond2 = new double DACE_ALIGN(64)[sym_klon];
    double* zrainaut;
    zrainaut = new double DACE_ALIGN(64)[sym_klon];
    double* zsnowaut;
    zsnowaut = new double DACE_ALIGN(64)[sym_klon];
    double* zliqcld;
    zliqcld = new double DACE_ALIGN(64)[sym_klon];
    double* zicecld;
    zicecld = new double DACE_ALIGN(64)[sym_klon];
    double* zfokoop;
    zfokoop = new double DACE_ALIGN(64)[sym_klon];
    double* zfoealfa;
    zfoealfa = new double DACE_ALIGN(64)[((sym_klev * sym_klon) + sym_klon)];
    double* zicenuclei;
    zicenuclei = new double DACE_ALIGN(64)[sym_klon];
    double* zlicld;
    zlicld = new double DACE_ALIGN(64)[sym_klon];
    double zacond;
    double* zlfinalsum;
    zlfinalsum = new double DACE_ALIGN(64)[sym_klon];
    double* zdqs;
    zdqs = new double DACE_ALIGN(64)[sym_klon];
    double* ztold;
    ztold = new double DACE_ALIGN(64)[sym_klon];
    double* zqold;
    zqold = new double DACE_ALIGN(64)[sym_klon];
    double* zdtgdp;
    zdtgdp = new double DACE_ALIGN(64)[sym_klon];
    double* zrdtgdp;
    zrdtgdp = new double DACE_ALIGN(64)[sym_klon];
    double* zcovpclr;
    zcovpclr = new double DACE_ALIGN(64)[sym_klon];
    double zpreclr;
    double* zcovptot;
    zcovptot = new double DACE_ALIGN(64)[sym_klon];
    double* zcovpmax;
    zcovpmax = new double DACE_ALIGN(64)[sym_klon];
    double* zqpretot;
    zqpretot = new double DACE_ALIGN(64)[sym_klon];
    double zdpevap;
    double zdtforc;
    double* ztp1;
    ztp1 = new double DACE_ALIGN(64)[((sym_klon * (sym_klev - 1)) + sym_klon)];
    double* zldefr;
    zldefr = new double DACE_ALIGN(64)[sym_klon];
    double* zldifdt;
    zldifdt = new double DACE_ALIGN(64)[sym_klon];
    double* zlcust;
    zlcust = new double DACE_ALIGN(64)[(5 * sym_klon)];
    double* zacust;
    zacust = new double DACE_ALIGN(64)[sym_klon];
    double* zmf;
    zmf = new double DACE_ALIGN(64)[sym_klon];
    double* zrho;
    zrho = new double DACE_ALIGN(64)[sym_klon];
    double* zsolab;
    zsolab = new double DACE_ALIGN(64)[sym_klon];
    double* zsolac;
    zsolac = new double DACE_ALIGN(64)[sym_klon];
    double zanew;
    double* zanewm1;
    zanewm1 = new double DACE_ALIGN(64)[sym_klon];
    double* zda;
    zda = new double DACE_ALIGN(64)[sym_klon];
    double* zli;
    zli = new double DACE_ALIGN(64)[((sym_klon * (sym_klev - 1)) + sym_klon)];
    double* za;
    za = new double DACE_ALIGN(64)[((sym_klon * (sym_klev - 1)) + sym_klon)];
    double* zaorig;
    zaorig = new double DACE_ALIGN(64)[((sym_klon * (sym_klev - 1)) + sym_klon)];
    int llo1;
    double* zdp;
    zdp = new double DACE_ALIGN(64)[sym_klon];
    double zalfa;
    double zbeta;
    double zcor;
    double zcdmax;
    double* zmin;
    zmin = new double DACE_ALIGN(64)[sym_klon];
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
    double* zsupsat;
    zsupsat = new double DACE_ALIGN(64)[sym_klon];
    double zrldcp;
    int iphase[5] DACE_ALIGN(64);
    int imelt[5] DACE_ALIGN(64);
    int llfall[5] DACE_ALIGN(64);
    int* llindex1;
    llindex1 = new int DACE_ALIGN(64)[(5 * sym_klon)];
    int* llindex3;
    llindex3 = new int DACE_ALIGN(64)[(25 * sym_klon)];
    int* iorder;
    iorder = new int DACE_ALIGN(64)[(5 * sym_klon)];
    double* zliqfrac;
    zliqfrac = new double DACE_ALIGN(64)[((sym_klon * (sym_klev - 1)) + sym_klon)];
    double* zicefrac;
    zicefrac = new double DACE_ALIGN(64)[((sym_klon * (sym_klev - 1)) + sym_klon)];
    double* zqx;
    zqx = new double DACE_ALIGN(64)[((((4 * sym_klev) * sym_klon) + (sym_klon * (sym_klev - 1))) + sym_klon)];
    double* zqx0;
    zqx0 = new double DACE_ALIGN(64)[((((4 * sym_klev) * sym_klon) + (sym_klon * (sym_klev - 1))) + sym_klon)];
    double* zqxn;
    zqxn = new double DACE_ALIGN(64)[(5 * sym_klon)];
    double* zqxfg;
    zqxfg = new double DACE_ALIGN(64)[(5 * sym_klon)];
    double* zqxnm1;
    zqxnm1 = new double DACE_ALIGN(64)[(5 * sym_klon)];
    double* zfluxq;
    zfluxq = new double DACE_ALIGN(64)[(5 * sym_klon)];
    double* zpfplsx;
    zpfplsx = new double DACE_ALIGN(64)[(((sym_klev * sym_klon) + ((4 * sym_klon) * (sym_klev + 1))) + sym_klon)];
    double* zlneg;
    zlneg = new double DACE_ALIGN(64)[((((4 * sym_klev) * sym_klon) + (sym_klon * (sym_klev - 1))) + sym_klon)];
    double* zmeltmax;
    zmeltmax = new double DACE_ALIGN(64)[sym_klon];
    double* zfrzmax;
    zfrzmax = new double DACE_ALIGN(64)[sym_klon];
    double* zicetot;
    zicetot = new double DACE_ALIGN(64)[sym_klon];
    double* zqxn2d;
    zqxn2d = new double DACE_ALIGN(64)[((((4 * sym_klev) * sym_klon) + (sym_klon * (sym_klev - 1))) + sym_klon)];
    double* zqsmix;
    zqsmix = new double DACE_ALIGN(64)[((sym_klon * (sym_klev - 1)) + sym_klon)];
    double* zqsliq;
    zqsliq = new double DACE_ALIGN(64)[((sym_klon * (sym_klev - 1)) + sym_klon)];
    double* zqsice;
    zqsice = new double DACE_ALIGN(64)[((sym_klon * (sym_klev - 1)) + sym_klon)];
    double* zfoeewmt;
    zfoeewmt = new double DACE_ALIGN(64)[((sym_klon * (sym_klev - 1)) + sym_klon)];
    double* zfoeew;
    zfoeew = new double DACE_ALIGN(64)[((sym_klon * (sym_klev - 1)) + sym_klon)];
    double* zfoeeliqt;
    zfoeeliqt = new double DACE_ALIGN(64)[((sym_klon * (sym_klev - 1)) + sym_klon)];
    double* zdqsmixdt;
    zdqsmixdt = new double DACE_ALIGN(64)[sym_klon];
    double* zcorqsice;
    zcorqsice = new double DACE_ALIGN(64)[sym_klon];
    double* zevaplimmix;
    zevaplimmix = new double DACE_ALIGN(64)[sym_klon];
    double* zsolqa;
    zsolqa = new double DACE_ALIGN(64)[(25 * sym_klon)];
    double* zsolqb;
    zsolqb = new double DACE_ALIGN(64)[(25 * sym_klon)];
    double* zqlhs;
    zqlhs = new double DACE_ALIGN(64)[(25 * sym_klon)];
    double zvqx[5] DACE_ALIGN(64);
    double zexplicit;
    double* zratio;
    zratio = new double DACE_ALIGN(64)[(5 * sym_klon)];
    double* zsinksum;
    zsinksum = new double DACE_ALIGN(64)[(5 * sym_klon)];
    double* zfallsink;
    zfallsink = new double DACE_ALIGN(64)[(5 * sym_klon)];
    double* zfallsrce;
    zfallsrce = new double DACE_ALIGN(64)[(5 * sym_klon)];
    double* zconvsrce;
    zconvsrce = new double DACE_ALIGN(64)[(5 * sym_klon)];
    double* zconvsink;
    zconvsink = new double DACE_ALIGN(64)[(5 * sym_klon)];
    double* zpsupsatsrce;
    zpsupsatsrce = new double DACE_ALIGN(64)[(5 * sym_klon)];
    double zsubsat;
    double* zcldtopdist;
    zcldtopdist = new double DACE_ALIGN(64)[sym_klon];
    double* zrainacc;
    zrainacc = new double DACE_ALIGN(64)[sym_klon];
    double* zraincld;
    zraincld = new double DACE_ALIGN(64)[sym_klon];
    double* zsnowcld;
    zsnowcld = new double DACE_ALIGN(64)[sym_klon];
    double zfallcorr;
    double zlambda;
    double zconst;
    int* llrainliq;
    llrainliq = new int DACE_ALIGN(64)[sym_klon];
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
    double* v_ydcst_var_47_rg;
    v_ydcst_var_47_rg = (double*)(&(ydcst_var_47->rg));
    double* v_ydcst_var_47_rcpd;
    v_ydcst_var_47_rcpd = (double*)(&(ydcst_var_47->rcpd));
    double* v_ydcst_var_47_rd;
    v_ydcst_var_47_rd = (double*)(&(ydcst_var_47->rd));
    double* v_ydecldp_var_49_rtaumel;
    v_ydecldp_var_49_rtaumel = (double*)(&(ydecldp_var_49->rtaumel));
    double* v_ydthf_var_48_ralsdcp;
    v_ydthf_var_48_ralsdcp = (double*)(&(ydthf_var_48->ralsdcp));
    double* v_ydthf_var_48_ralvdcp;
    v_ydthf_var_48_ralvdcp = (double*)(&(ydthf_var_48->ralvdcp));
    double* v_ydecldp_var_49_rlmin;
    v_ydecldp_var_49_rlmin = (double*)(&(ydecldp_var_49->rlmin));
    double* v_ydecldp_var_49_ramin;
    v_ydecldp_var_49_ramin = (double*)(&(ydecldp_var_49->ramin));
    double* v_ydcst_var_47_retv;
    v_ydcst_var_47_retv = (double*)(&(ydcst_var_47->retv));
    int* v_ydecldp_var_49_ncldtop;
    v_ydecldp_var_49_ncldtop = (int*)(&(ydecldp_var_49->ncldtop));
    double* v_ydcst_var_47_rtt;
    v_ydcst_var_47_rtt = (double*)(&(ydcst_var_47->rtt));
    int* v_ydecldp_var_49_nssopt;
    v_ydecldp_var_49_nssopt = (int*)(&(ydecldp_var_49->nssopt));
    double* v_ydecldp_var_49_rthomo;
    v_ydecldp_var_49_rthomo = (double*)(&(ydecldp_var_49->rthomo));
    double* v_ydecldp_var_49_ramid;
    v_ydecldp_var_49_ramid = (double*)(&(ydecldp_var_49->ramid));
    double* v_ydcst_var_47_rv;
    v_ydcst_var_47_rv = (double*)(&(ydcst_var_47->rv));
    double* v_ydcst_var_47_rlstt;
    v_ydcst_var_47_rlstt = (double*)(&(ydcst_var_47->rlstt));
    double* v_ydecldp_var_49_rcovpmin;
    v_ydecldp_var_49_rcovpmin = (double*)(&(ydecldp_var_49->rcovpmin));
    double* v_ydecldp_var_49_rdensref;
    v_ydecldp_var_49_rdensref = (double*)(&(ydecldp_var_49->rdensref));
    double* v_ydecldp_var_49_rcl_fac1;
    v_ydecldp_var_49_rcl_fac1 = (double*)(&(ydecldp_var_49->rcl_fac1));
    double* v_ydecldp_var_49_rcl_fac2;
    v_ydecldp_var_49_rcl_fac2 = (double*)(&(ydecldp_var_49->rcl_fac2));
    double* v_ydecldp_var_49_rprecrhmax;
    v_ydecldp_var_49_rprecrhmax = (double*)(&(ydecldp_var_49->rprecrhmax));
    double* v_ydthf_var_62_r3les;
    v_ydthf_var_62_r3les = (double*)(&(ydthf_var_48->r3les));
    double* v_ydcst_var_63_rtt;
    v_ydcst_var_63_rtt = (double*)(&(ydcst_var_47->rtt));
    double* v_ydthf_var_62_r4les;
    v_ydthf_var_62_r4les = (double*)(&(ydthf_var_48->r4les));
    double* v_ydthf_var_62_r2es;
    v_ydthf_var_62_r2es = (double*)(&(ydthf_var_48->r2es));
    double* v_ydthf_var_65_r3ies;
    v_ydthf_var_65_r3ies = (double*)(&(ydthf_var_48->r3ies));
    double* v_ydcst_var_66_rtt;
    v_ydcst_var_66_rtt = (double*)(&(ydcst_var_47->rtt));
    double* v_ydthf_var_65_r4ies;
    v_ydthf_var_65_r4ies = (double*)(&(ydthf_var_48->r4ies));
    double* v_ydthf_var_65_r2es;
    v_ydthf_var_65_r2es = (double*)(&(ydthf_var_48->r2es));
    double* v_ydthf_var_58_r4ies;
    v_ydthf_var_58_r4ies = (double*)(&(ydthf_var_48->r4ies));
    double* v_ydthf_var_58_r4les;
    v_ydthf_var_58_r4les = (double*)(&(ydthf_var_48->r4les));
    double* v_ydthf_var_58_r5alvcp;
    v_ydthf_var_58_r5alvcp = (double*)(&(ydthf_var_48->r5alvcp));
    double* v_ydthf_var_58_r5alscp;
    v_ydthf_var_58_r5alscp = (double*)(&(ydthf_var_48->r5alscp));
    double* v_ydthf_var_53_rtwat;
    v_ydthf_var_53_rtwat = (double*)(&(ydthf_var_48->rtwat));
    double* v_ydthf_var_53_rtice;
    v_ydthf_var_53_rtice = (double*)(&(ydthf_var_48->rtice));
    double* v_ydthf_var_53_rtwat_rtice_r;
    v_ydthf_var_53_rtwat_rtice_r = (double*)(&(ydthf_var_48->rtwat_rtice_r));
    double tmp_call_114_0;
    double tmp_call_113_0;
    double tmp_call_112_0;
    double tmp_call_105_0_0;
    double tmp_call_105_1_0;
    double* v_ydthf_var_60_ralvdcp;
    v_ydthf_var_60_ralvdcp = (double*)(&(ydthf_var_48->ralvdcp));
    double* v_ydthf_var_60_ralsdcp;
    v_ydthf_var_60_ralsdcp = (double*)(&(ydthf_var_48->ralsdcp));
    double tmp_call_116_0;
    double tmp_call_105_0_1;
    double tmp_call_105_1_1;
    double tmp_call_114_1;
    double tmp_call_113_1;
    double tmp_call_112_1;
    double tmp_call_105_0_2;
    double tmp_call_105_1_2;
    double* v_ydthf_var_55_r3ies;
    v_ydthf_var_55_r3ies = (double*)(&(ydthf_var_48->r3ies));
    double* v_ydcst_var_56_rtt;
    v_ydcst_var_56_rtt = (double*)(&(ydcst_var_47->rtt));
    double* v_ydthf_var_55_r4ies;
    v_ydthf_var_55_r4ies = (double*)(&(ydthf_var_48->r4ies));
    double* v_ydthf_var_55_r3les;
    v_ydthf_var_55_r3les = (double*)(&(ydthf_var_48->r3les));
    double* v_ydthf_var_55_r4les;
    v_ydthf_var_55_r4les = (double*)(&(ydthf_var_48->r4les));
    double* v_ydthf_var_55_r2es;
    v_ydthf_var_55_r2es = (double*)(&(ydthf_var_48->r2es));
    double tmp_call_110_0;
    double tmp_call_109_0;
    double tmp_call_108_0;
    double tmp_call_105_0_3;
    double tmp_call_105_1_3;
    double tmp_call_116_1;
    double tmp_call_105_0_4;
    double tmp_call_105_1_4;
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
    double tmp_call_116_2;
    double tmp_call_105_0_7;
    double tmp_call_105_1_7;
    double* v_ydcst_var_51_rtt;
    v_ydcst_var_51_rtt = (double*)(&(ydcst_var_47->rtt));
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
    int _if_cond_23;
    int _for_it_38;
    double _if_cond_24;
    int _for_it_39;
    double _if_cond_25;
    int _for_it_40;
    int _if_cond_26;
    int _for_it_41;
    int _for_it_42;
    int _for_it_43;
    double _if_cond_27;
    int _for_it_44;
    int _for_it_45;
    double _if_cond_29;
    int _for_it_46;
    int tmp_index_992;
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
    int tmp_index_1572;
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
            // Tasklet code (T_l390_c390)
            zepsilon_out = (100.0 * 2.220446049250313e-16);
            ///////////////////

            zepsilon = zepsilon_out;
        }
        {
            double ptsphy_var_5_0_in = ptsphy_var_5[0];
            double zqtmst_out;

            ///////////////////
            // Tasklet code (T_l395_c395)
            zqtmst_out = (1.0 / ptsphy_var_5_0_in);
            ///////////////////

            zqtmst = zqtmst_out;
        }
    }

    {
        {
            double ydcst_var_47_0_in_rd = v_ydcst_var_47_rd[0];
            double ydcst_var_47_1_in_rcpd = v_ydcst_var_47_rcpd[0];
            double zrdcp_out;

            ///////////////////
            // Tasklet code (T_l397_c397)
            zrdcp_out = (ydcst_var_47_0_in_rd / ydcst_var_47_1_in_rcpd);
            ///////////////////

            zrdcp = zrdcp_out;
        }
        {
            double zepsec_out;

            ///////////////////
            // Tasklet code (T_l399_c399)
            zepsec_out = 1e-14;
            ///////////////////

            zepsec = zepsec_out;
        }
    }

    {
        {
            double ydcst_var_47_0_in_rg = v_ydcst_var_47_rg[0];
            double zrg_r_out;

            ///////////////////
            // Tasklet code (T_l400_c400)
            zrg_r_out = (1.0 / ydcst_var_47_0_in_rg);
            ///////////////////

            zrg_r = zrg_r_out;
        }
        {
            double ydthf_var_48_0_in_ralsdcp = v_ydthf_var_48_ralsdcp[0];
            double ydthf_var_48_1_in_ralvdcp = v_ydthf_var_48_ralvdcp[0];
            double zrldcp_out;

            ///////////////////
            // Tasklet code (T_l401_c401)
            zrldcp_out = (1.0 / (ydthf_var_48_0_in_ralsdcp - ydthf_var_48_1_in_ralvdcp));
            ///////////////////

            zrldcp = zrldcp_out;
        }
        {
            int iphase_out_0;

            ///////////////////
            // Tasklet code (T_l402_c402)
            iphase_out_0 = 0;
            ///////////////////

            iphase[4] = iphase_out_0;
        }
        {
            int iphase_out_0;

            ///////////////////
            // Tasklet code (T_l403_c403)
            iphase_out_0 = 1;
            ///////////////////

            iphase[0] = iphase_out_0;
        }
        {
            int iphase_out_0;

            ///////////////////
            // Tasklet code (T_l404_c404)
            iphase_out_0 = 1;
            ///////////////////

            iphase[2] = iphase_out_0;
        }
        {
            int iphase_out_0;

            ///////////////////
            // Tasklet code (T_l405_c405)
            iphase_out_0 = 2;
            ///////////////////

            iphase[1] = iphase_out_0;
        }
        {
            int iphase_out_0;

            ///////////////////
            // Tasklet code (T_l406_c406)
            iphase_out_0 = 2;
            ///////////////////

            iphase[3] = iphase_out_0;
        }
        {
            int imelt_out_0;

            ///////////////////
            // Tasklet code (T_l407_c407)
            imelt_out_0 = -99;
            ///////////////////

            imelt[4] = imelt_out_0;
        }
        {
            int imelt_out_0;

            ///////////////////
            // Tasklet code (T_l408_c408)
            imelt_out_0 = 2;
            ///////////////////

            imelt[0] = imelt_out_0;
        }
        {
            int imelt_out_0;

            ///////////////////
            // Tasklet code (T_l409_c409)
            imelt_out_0 = 4;
            ///////////////////

            imelt[2] = imelt_out_0;
        }
        {
            int imelt_out_0;

            ///////////////////
            // Tasklet code (T_l410_c410)
            imelt_out_0 = 3;
            ///////////////////

            imelt[1] = imelt_out_0;
        }
        {
            int imelt_out_0;

            ///////////////////
            // Tasklet code (T_l411_c411)
            imelt_out_0 = 3;
            ///////////////////

            imelt[3] = imelt_out_0;
        }
    }

    for (_for_it_0 = 1; (_for_it_0 <= sym_klev); _for_it_0 = (_for_it_0 + 1)) {
        for (_for_it_1 = 1; (_for_it_1 <= icend); _for_it_1 = (_for_it_1 + 1)) {
            {
                {
                    double ptendency_loc_t_out_0;

                    ///////////////////
                    // Tasklet code (T_l414_c414)
                    ptendency_loc_t_out_0 = 0.0;
                    ///////////////////

                    ptendency_loc_t[((_for_it_1 + (sym_klon * (_for_it_0 - 1))) - 1)] = ptendency_loc_t_out_0;
                }
                {
                    double ptendency_loc_q_out_0;

                    ///////////////////
                    // Tasklet code (T_l415_c415)
                    ptendency_loc_q_out_0 = 0.0;
                    ///////////////////

                    ptendency_loc_q[((_for_it_1 + (sym_klon * (_for_it_0 - 1))) - 1)] = ptendency_loc_q_out_0;
                }
                {
                    double ptendency_loc_a_out_0;

                    ///////////////////
                    // Tasklet code (T_l416_c416)
                    ptendency_loc_a_out_0 = 0.0;
                    ///////////////////

                    ptendency_loc_a[((_for_it_1 + (sym_klon * (_for_it_0 - 1))) - 1)] = ptendency_loc_a_out_0;
                }
            }
        }
    }

    for (_for_it_2 = 1; (_for_it_2 <= 4); _for_it_2 = (_for_it_2 + 1)) {
        for (_for_it_3 = 1; (_for_it_3 <= sym_klev); _for_it_3 = (_for_it_3 + 1)) {
            for (_for_it_4 = 1; (_for_it_4 <= icend); _for_it_4 = (_for_it_4 + 1)) {
                {
                    {
                        double ptendency_loc_cld_out_0;

                        ///////////////////
                        // Tasklet code (T_l422_c422)
                        ptendency_loc_cld_out_0 = 0.0;
                        ///////////////////

                        ptendency_loc_cld[(((_for_it_4 + ((sym_klev * sym_klon) * (_for_it_2 - 1))) + (sym_klon * (_for_it_3 - 1))) - 1)] = ptendency_loc_cld_out_0;
                    }
                }
            }
        }
    }

    {
        double* v_ydecldp_var_49_rvice;
        v_ydecldp_var_49_rvice = (double*)(&(ydecldp_var_49->rvice));
        double* v_ydecldp_var_49_rvrain;
        v_ydecldp_var_49_rvrain = (double*)(&(ydecldp_var_49->rvrain));
        double* v_ydecldp_var_49_rvsnow;
        v_ydecldp_var_49_rvsnow = (double*)(&(ydecldp_var_49->rvsnow));

        {
            double zvqx_out_0;

            ///////////////////
            // Tasklet code (T_l426_c426)
            zvqx_out_0 = 0.0;
            ///////////////////

            zvqx[4] = zvqx_out_0;
        }
        {
            double zvqx_out_0;

            ///////////////////
            // Tasklet code (T_l427_c427)
            zvqx_out_0 = 0.0;
            ///////////////////

            zvqx[0] = zvqx_out_0;
        }
        {
            double ydecldp_var_49_0_in_rvice = v_ydecldp_var_49_rvice[0];
            double zvqx_out_0;

            ///////////////////
            // Tasklet code (T_l428_c428)
            zvqx_out_0 = ydecldp_var_49_0_in_rvice;
            ///////////////////

            zvqx[1] = zvqx_out_0;
        }
        {
            double ydecldp_var_49_0_in_rvrain = v_ydecldp_var_49_rvrain[0];
            double zvqx_out_0;

            ///////////////////
            // Tasklet code (T_l429_c429)
            zvqx_out_0 = ydecldp_var_49_0_in_rvrain;
            ///////////////////

            zvqx[2] = zvqx_out_0;
        }
        {
            double ydecldp_var_49_0_in_rvsnow = v_ydecldp_var_49_rvsnow[0];
            double zvqx_out_0;

            ///////////////////
            // Tasklet code (T_l430_c430)
            zvqx_out_0 = ydecldp_var_49_0_in_rvsnow;
            ///////////////////

            zvqx[3] = zvqx_out_0;
        }
    }

    for (tmp_parfor_0 = 1; (tmp_parfor_0 <= 5); tmp_parfor_0 = (tmp_parfor_0 + 1)) {
        {
            {
                int llfall_out_0;

                ///////////////////
                // Tasklet code (T_l431_c431)
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
                    // Tasklet code (T_l433_c433)
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
            // Tasklet code (T_l435_c435)
            llfall_out_0 = 0;
            ///////////////////

            llfall[1] = llfall_out_0;
        }
    }

    for (_for_it_6 = 1; (_for_it_6 <= sym_klev); _for_it_6 = (_for_it_6 + 1)) {
        for (_for_it_7 = 1; (_for_it_7 <= icend); _for_it_7 = (_for_it_7 + 1)) {
            {
                {
                    double pt_var_6_0_in_0 = pt_var_6[((_for_it_7 + (sym_klon * (_for_it_6 - 1))) - 1)];
                    double ptendency_tmp_t_0_in_0 = ptendency_tmp_t[((_for_it_7 + (sym_klon * (_for_it_6 - 1))) - 1)];
                    double ptsphy_var_5_0_in = ptsphy_var_5[0];
                    double ztp1_out_0;

                    ///////////////////
                    // Tasklet code (T_l438_c438)
                    ztp1_out_0 = (pt_var_6_0_in_0 + (ptsphy_var_5_0_in * ptendency_tmp_t_0_in_0));
                    ///////////////////

                    ztp1[((_for_it_7 + (sym_klon * (_for_it_6 - 1))) - 1)] = ztp1_out_0;
                }
                {
                    double pq_var_7_0_in_0 = pq_var_7[((_for_it_7 + (sym_klon * (_for_it_6 - 1))) - 1)];
                    double ptendency_tmp_q_0_in_0 = ptendency_tmp_q[((_for_it_7 + (sym_klon * (_for_it_6 - 1))) - 1)];
                    double ptsphy_var_5_0_in = ptsphy_var_5[0];
                    double zqx_out_0;

                    ///////////////////
                    // Tasklet code (T_l439_c439)
                    zqx_out_0 = (pq_var_7_0_in_0 + (ptsphy_var_5_0_in * ptendency_tmp_q_0_in_0));
                    ///////////////////

                    zqx[(((_for_it_7 + ((4 * sym_klev) * sym_klon)) + (sym_klon * (_for_it_6 - 1))) - 1)] = zqx_out_0;
                }
                {
                    double pq_var_7_0_in_0 = pq_var_7[((_for_it_7 + (sym_klon * (_for_it_6 - 1))) - 1)];
                    double ptendency_tmp_q_0_in_0 = ptendency_tmp_q[((_for_it_7 + (sym_klon * (_for_it_6 - 1))) - 1)];
                    double ptsphy_var_5_0_in = ptsphy_var_5[0];
                    double zqx0_out_0;

                    ///////////////////
                    // Tasklet code (T_l440_c440)
                    zqx0_out_0 = (pq_var_7_0_in_0 + (ptsphy_var_5_0_in * ptendency_tmp_q_0_in_0));
                    ///////////////////

                    zqx0[(((_for_it_7 + ((4 * sym_klev) * sym_klon)) + (sym_klon * (_for_it_6 - 1))) - 1)] = zqx0_out_0;
                }
                {
                    double pa_var_27_0_in_0 = pa_var_27[((_for_it_7 + (sym_klon * (_for_it_6 - 1))) - 1)];
                    double ptendency_tmp_a_0_in_0 = ptendency_tmp_a[((_for_it_7 + (sym_klon * (_for_it_6 - 1))) - 1)];
                    double ptsphy_var_5_0_in = ptsphy_var_5[0];
                    double za_out_0;

                    ///////////////////
                    // Tasklet code (T_l441_c441)
                    za_out_0 = (pa_var_27_0_in_0 + (ptsphy_var_5_0_in * ptendency_tmp_a_0_in_0));
                    ///////////////////

                    za[((_for_it_7 + (sym_klon * (_for_it_6 - 1))) - 1)] = za_out_0;
                }
                {
                    double pa_var_27_0_in_0 = pa_var_27[((_for_it_7 + (sym_klon * (_for_it_6 - 1))) - 1)];
                    double ptendency_tmp_a_0_in_0 = ptendency_tmp_a[((_for_it_7 + (sym_klon * (_for_it_6 - 1))) - 1)];
                    double ptsphy_var_5_0_in = ptsphy_var_5[0];
                    double zaorig_out_0;

                    ///////////////////
                    // Tasklet code (T_l442_c442)
                    zaorig_out_0 = (pa_var_27_0_in_0 + (ptsphy_var_5_0_in * ptendency_tmp_a_0_in_0));
                    ///////////////////

                    zaorig[((_for_it_7 + (sym_klon * (_for_it_6 - 1))) - 1)] = zaorig_out_0;
                }
            }
        }
    }

    for (_for_it_8 = 1; (_for_it_8 <= 4); _for_it_8 = (_for_it_8 + 1)) {
        for (_for_it_9 = 1; (_for_it_9 <= sym_klev); _for_it_9 = (_for_it_9 + 1)) {
            for (_for_it_10 = 1; (_for_it_10 <= icend); _for_it_10 = (_for_it_10 + 1)) {
                {
                    {
                        double pclv_var_29_0_in_0 = pclv_var_29[(((_for_it_10 + ((sym_klev * sym_klon) * (_for_it_8 - 1))) + (sym_klon * (_for_it_9 - 1))) - 1)];
                        double ptendency_tmp_cld_0_in_0 = ptendency_tmp_cld[(((_for_it_10 + ((sym_klev * sym_klon) * (_for_it_8 - 1))) + (sym_klon * (_for_it_9 - 1))) - 1)];
                        double ptsphy_var_5_0_in = ptsphy_var_5[0];
                        double zqx_out_0;

                        ///////////////////
                        // Tasklet code (T_l448_c448)
                        zqx_out_0 = (pclv_var_29_0_in_0 + (ptsphy_var_5_0_in * ptendency_tmp_cld_0_in_0));
                        ///////////////////

                        zqx[(((_for_it_10 + ((sym_klev * sym_klon) * (_for_it_8 - 1))) + (sym_klon * (_for_it_9 - 1))) - 1)] = zqx_out_0;
                    }
                    {
                        double pclv_var_29_0_in_0 = pclv_var_29[(((_for_it_10 + ((sym_klev * sym_klon) * (_for_it_8 - 1))) + (sym_klon * (_for_it_9 - 1))) - 1)];
                        double ptendency_tmp_cld_0_in_0 = ptendency_tmp_cld[(((_for_it_10 + ((sym_klev * sym_klon) * (_for_it_8 - 1))) + (sym_klon * (_for_it_9 - 1))) - 1)];
                        double ptsphy_var_5_0_in = ptsphy_var_5[0];
                        double zqx0_out_0;

                        ///////////////////
                        // Tasklet code (T_l449_c449)
                        zqx0_out_0 = (pclv_var_29_0_in_0 + (ptsphy_var_5_0_in * ptendency_tmp_cld_0_in_0));
                        ///////////////////

                        zqx0[(((_for_it_10 + ((sym_klev * sym_klon) * (_for_it_8 - 1))) + (sym_klon * (_for_it_9 - 1))) - 1)] = zqx0_out_0;
                    }
                }
            }
        }
    }

    for (tmp_parfor_3 = 1; (tmp_parfor_3 <= 5); tmp_parfor_3 = (tmp_parfor_3 + 1)) {
        for (tmp_parfor_2 = 1; (tmp_parfor_2 <= (sym_klev + 1)); tmp_parfor_2 = (tmp_parfor_2 + 1)) {
            for (tmp_parfor_1 = 1; (tmp_parfor_1 <= sym_klon); tmp_parfor_1 = (tmp_parfor_1 + 1)) {
                {
                    {
                        double zpfplsx_out_0;

                        ///////////////////
                        // Tasklet code (T_l453_c453)
                        zpfplsx_out_0 = 0.0;
                        ///////////////////

                        zpfplsx[(((((sym_klon * (sym_klev + 1)) * (tmp_parfor_3 - 1)) + (sym_klon * (tmp_parfor_2 - 1))) + tmp_parfor_1) - 1)] = zpfplsx_out_0;
                    }
                }
            }
        }
    }

    for (tmp_parfor_6 = 1; (tmp_parfor_6 <= 5); tmp_parfor_6 = (tmp_parfor_6 + 1)) {
        for (tmp_parfor_5 = 1; (tmp_parfor_5 <= sym_klev); tmp_parfor_5 = (tmp_parfor_5 + 1)) {
            for (tmp_parfor_4 = 1; (tmp_parfor_4 <= sym_klon); tmp_parfor_4 = (tmp_parfor_4 + 1)) {
                {
                    {
                        double zqxn2d_out_0;

                        ///////////////////
                        // Tasklet code (T_l454_c454)
                        zqxn2d_out_0 = 0.0;
                        ///////////////////

                        zqxn2d[(((((sym_klev * sym_klon) * (tmp_parfor_6 - 1)) + (sym_klon * (tmp_parfor_5 - 1))) + tmp_parfor_4) - 1)] = zqxn2d_out_0;
                    }
                }
            }
        }
    }

    for (tmp_parfor_9 = 1; (tmp_parfor_9 <= 5); tmp_parfor_9 = (tmp_parfor_9 + 1)) {
        for (tmp_parfor_8 = 1; (tmp_parfor_8 <= sym_klev); tmp_parfor_8 = (tmp_parfor_8 + 1)) {
            for (tmp_parfor_7 = 1; (tmp_parfor_7 <= sym_klon); tmp_parfor_7 = (tmp_parfor_7 + 1)) {
                {
                    {
                        double zlneg_out_0;

                        ///////////////////
                        // Tasklet code (T_l455_c455)
                        zlneg_out_0 = 0.0;
                        ///////////////////

                        zlneg[(((((sym_klev * sym_klon) * (tmp_parfor_9 - 1)) + (sym_klon * (tmp_parfor_8 - 1))) + tmp_parfor_7) - 1)] = zlneg_out_0;
                    }
                }
            }
        }
    }

    for (tmp_parfor_10 = 1; (tmp_parfor_10 <= sym_klon); tmp_parfor_10 = (tmp_parfor_10 + 1)) {
        {
            {
                double prainfrac_toprfz_var_32_out_0;

                ///////////////////
                // Tasklet code (T_l456_c456)
                prainfrac_toprfz_var_32_out_0 = 0.0;
                ///////////////////

                prainfrac_toprfz_var_32[(tmp_parfor_10 - 1)] = prainfrac_toprfz_var_32_out_0;
            }
        }
    }

    for (tmp_parfor_11 = 1; (tmp_parfor_11 <= sym_klon); tmp_parfor_11 = (tmp_parfor_11 + 1)) {
        {
            {
                int llrainliq_out_0;

                ///////////////////
                // Tasklet code (T_l457_c457)
                llrainliq_out_0 = 1;
                ///////////////////

                llrainliq[(tmp_parfor_11 - 1)] = llrainliq_out_0;
            }
        }
    }

    for (_for_it_11 = 1; (_for_it_11 <= sym_klev); _for_it_11 = (_for_it_11 + 1)) {
        for (_for_it_12 = 1; (_for_it_12 <= icend); _for_it_12 = (_for_it_12 + 1)) {
            {
                {
                    double ydecldp_var_49_0_in_rlmin = v_ydecldp_var_49_rlmin[0];
                    double ydecldp_var_49_1_in_ramin = v_ydecldp_var_49_ramin[0];
                    double za_0_in_0 = za[((_for_it_12 + (sym_klon * (_for_it_11 - 1))) - 1)];
                    double zqx_0_in_0 = zqx[((_for_it_12 + (sym_klon * (_for_it_11 - 1))) - 1)];
                    double zqx_1_in_0 = zqx[(((_for_it_12 + (sym_klev * sym_klon)) + (sym_klon * (_for_it_11 - 1))) - 1)];
                    double _if_cond_1_out;

                    ///////////////////
                    // Tasklet code (T_l0_c0)
                    _if_cond_1_out = (((zqx_0_in_0 + zqx_1_in_0) < ydecldp_var_49_0_in_rlmin) || (za_0_in_0 < ydecldp_var_49_1_in_ramin));
                    ///////////////////

                    _if_cond_1 = _if_cond_1_out;
                }
            }
            if ((_if_cond_1 == 1)) {
                {
                    {
                        double zlneg_0_in_0 = zlneg[((_for_it_12 + (sym_klon * (_for_it_11 - 1))) - 1)];
                        double zqx_0_in_0 = zqx[((_for_it_12 + (sym_klon * (_for_it_11 - 1))) - 1)];
                        double zlneg_out_0;

                        ///////////////////
                        // Tasklet code (T_l461_c461)
                        zlneg_out_0 = (zlneg_0_in_0 + zqx_0_in_0);
                        ///////////////////

                        zlneg[((_for_it_12 + (sym_klon * (_for_it_11 - 1))) - 1)] = zlneg_out_0;
                    }
                    {
                        double zqx_0_in_0 = zqx[(((_for_it_12 + ((4 * sym_klev) * sym_klon)) + (sym_klon * (_for_it_11 - 1))) - 1)];
                        double zqx_1_in_0 = zqx[((_for_it_12 + (sym_klon * (_for_it_11 - 1))) - 1)];
                        double zqx_out_0;

                        ///////////////////
                        // Tasklet code (T_l465_c465)
                        zqx_out_0 = (zqx_0_in_0 + zqx_1_in_0);
                        ///////////////////

                        zqx[(((_for_it_12 + ((4 * sym_klev) * sym_klon)) + (sym_klon * (_for_it_11 - 1))) - 1)] = zqx_out_0;
                    }
                    {
                        double zqtmst_0_in = zqtmst;
                        double zqx_0_in_0 = zqx[((_for_it_12 + (sym_klon * (_for_it_11 - 1))) - 1)];
                        double zqadj_out;

                        ///////////////////
                        // Tasklet code (T_l462_c462)
                        zqadj_out = (zqx_0_in_0 * zqtmst_0_in);
                        ///////////////////

                        zqadj = zqadj_out;
                    }
                    {
                        double ptendency_loc_q_0_in_0 = ptendency_loc_q[((_for_it_12 + (sym_klon * (_for_it_11 - 1))) - 1)];
                        double zqadj_0_in = zqadj;
                        double ptendency_loc_q_out_0;

                        ///////////////////
                        // Tasklet code (T_l463_c463)
                        ptendency_loc_q_out_0 = (ptendency_loc_q_0_in_0 + zqadj_0_in);
                        ///////////////////

                        ptendency_loc_q[((_for_it_12 + (sym_klon * (_for_it_11 - 1))) - 1)] = ptendency_loc_q_out_0;
                    }
                    {
                        double ptendency_loc_t_0_in_0 = ptendency_loc_t[((_for_it_12 + (sym_klon * (_for_it_11 - 1))) - 1)];
                        double ydthf_var_48_0_in_ralvdcp = v_ydthf_var_48_ralvdcp[0];
                        double zqadj_0_in = zqadj;
                        double ptendency_loc_t_out_0;

                        ///////////////////
                        // Tasklet code (T_l464_c464)
                        ptendency_loc_t_out_0 = (ptendency_loc_t_0_in_0 - (ydthf_var_48_0_in_ralvdcp * zqadj_0_in));
                        ///////////////////

                        ptendency_loc_t[((_for_it_12 + (sym_klon * (_for_it_11 - 1))) - 1)] = ptendency_loc_t_out_0;
                    }
                }
                {
                    {
                        double zqx_out_0;

                        ///////////////////
                        // Tasklet code (T_l466_c466)
                        zqx_out_0 = 0.0;
                        ///////////////////

                        zqx[((_for_it_12 + (sym_klon * (_for_it_11 - 1))) - 1)] = zqx_out_0;
                    }
                    {
                        double zlneg_0_in_0 = zlneg[(((_for_it_12 + (sym_klev * sym_klon)) + (sym_klon * (_for_it_11 - 1))) - 1)];
                        double zqx_0_in_0 = zqx[(((_for_it_12 + (sym_klev * sym_klon)) + (sym_klon * (_for_it_11 - 1))) - 1)];
                        double zlneg_out_0;

                        ///////////////////
                        // Tasklet code (T_l467_c467)
                        zlneg_out_0 = (zlneg_0_in_0 + zqx_0_in_0);
                        ///////////////////

                        zlneg[(((_for_it_12 + (sym_klev * sym_klon)) + (sym_klon * (_for_it_11 - 1))) - 1)] = zlneg_out_0;
                    }
                    {
                        double zqtmst_0_in = zqtmst;
                        double zqx_0_in_0 = zqx[(((_for_it_12 + (sym_klev * sym_klon)) + (sym_klon * (_for_it_11 - 1))) - 1)];
                        double zqadj_out;

                        ///////////////////
                        // Tasklet code (T_l468_c468)
                        zqadj_out = (zqx_0_in_0 * zqtmst_0_in);
                        ///////////////////

                        zqadj = zqadj_out;
                    }
                    {
                        double ptendency_loc_q_0_in_0 = ptendency_loc_q[((_for_it_12 + (sym_klon * (_for_it_11 - 1))) - 1)];
                        double zqadj_0_in = zqadj;
                        double ptendency_loc_q_out_0;

                        ///////////////////
                        // Tasklet code (T_l469_c469)
                        ptendency_loc_q_out_0 = (ptendency_loc_q_0_in_0 + zqadj_0_in);
                        ///////////////////

                        ptendency_loc_q[((_for_it_12 + (sym_klon * (_for_it_11 - 1))) - 1)] = ptendency_loc_q_out_0;
                    }
                    {
                        double ptendency_loc_t_0_in_0 = ptendency_loc_t[((_for_it_12 + (sym_klon * (_for_it_11 - 1))) - 1)];
                        double ydthf_var_48_0_in_ralsdcp = v_ydthf_var_48_ralsdcp[0];
                        double zqadj_0_in = zqadj;
                        double ptendency_loc_t_out_0;

                        ///////////////////
                        // Tasklet code (T_l470_c470)
                        ptendency_loc_t_out_0 = (ptendency_loc_t_0_in_0 - (ydthf_var_48_0_in_ralsdcp * zqadj_0_in));
                        ///////////////////

                        ptendency_loc_t[((_for_it_12 + (sym_klon * (_for_it_11 - 1))) - 1)] = ptendency_loc_t_out_0;
                    }
                }
                {
                    {
                        double zqx_0_in_0 = zqx[(((_for_it_12 + ((4 * sym_klev) * sym_klon)) + (sym_klon * (_for_it_11 - 1))) - 1)];
                        double zqx_1_in_0 = zqx[(((_for_it_12 + (sym_klev * sym_klon)) + (sym_klon * (_for_it_11 - 1))) - 1)];
                        double zqx_out_0;

                        ///////////////////
                        // Tasklet code (T_l471_c471)
                        zqx_out_0 = (zqx_0_in_0 + zqx_1_in_0);
                        ///////////////////

                        zqx[(((_for_it_12 + ((4 * sym_klev) * sym_klon)) + (sym_klon * (_for_it_11 - 1))) - 1)] = zqx_out_0;
                    }
                }
                {
                    {
                        double zqx_out_0;

                        ///////////////////
                        // Tasklet code (T_l472_c472)
                        zqx_out_0 = 0.0;
                        ///////////////////

                        zqx[(((_for_it_12 + (sym_klev * sym_klon)) + (sym_klon * (_for_it_11 - 1))) - 1)] = zqx_out_0;
                    }
                    {
                        double za_out_0;

                        ///////////////////
                        // Tasklet code (T_l473_c473)
                        za_out_0 = 0.0;
                        ///////////////////

                        za[((_for_it_12 + (sym_klon * (_for_it_11 - 1))) - 1)] = za_out_0;
                    }
                }
            }
        }
    }

    for (_for_it_13 = 1; (_for_it_13 <= 4); _for_it_13 = (_for_it_13 + 1)) {
        for (_for_it_14 = 1; (_for_it_14 <= sym_klev); _for_it_14 = (_for_it_14 + 1)) {
            for (_for_it_15 = 1; (_for_it_15 <= icend); _for_it_15 = (_for_it_15 + 1)) {
                {
                    {
                        double ydecldp_var_49_0_in_rlmin = v_ydecldp_var_49_rlmin[0];
                        double zqx_0_in_0 = zqx[(((_for_it_15 + ((sym_klev * sym_klon) * (_for_it_13 - 1))) + (sym_klon * (_for_it_14 - 1))) - 1)];
                        double _if_cond_2_out;

                        ///////////////////
                        // Tasklet code (T_l0_c0)
                        _if_cond_2_out = (zqx_0_in_0 < ydecldp_var_49_0_in_rlmin);
                        ///////////////////

                        _if_cond_2 = _if_cond_2_out;
                    }
                }
                if ((_if_cond_2 == 1)) {
                    _if_cond_3 = (iphase[(_for_it_13 - 1)] == 1);
                    {
                        {
                            double zlneg_0_in_0 = zlneg[(((_for_it_15 + ((sym_klev * sym_klon) * (_for_it_13 - 1))) + (sym_klon * (_for_it_14 - 1))) - 1)];
                            double zqx_0_in_0 = zqx[(((_for_it_15 + ((sym_klev * sym_klon) * (_for_it_13 - 1))) + (sym_klon * (_for_it_14 - 1))) - 1)];
                            double zlneg_out_0;

                            ///////////////////
                            // Tasklet code (T_l481_c481)
                            zlneg_out_0 = (zlneg_0_in_0 + zqx_0_in_0);
                            ///////////////////

                            zlneg[(((_for_it_15 + ((sym_klev * sym_klon) * (_for_it_13 - 1))) + (sym_klon * (_for_it_14 - 1))) - 1)] = zlneg_out_0;
                        }
                        {
                            double zqtmst_0_in = zqtmst;
                            double zqx_0_in_0 = zqx[(((_for_it_15 + ((sym_klev * sym_klon) * (_for_it_13 - 1))) + (sym_klon * (_for_it_14 - 1))) - 1)];
                            double zqadj_out;

                            ///////////////////
                            // Tasklet code (T_l482_c482)
                            zqadj_out = (zqx_0_in_0 * zqtmst_0_in);
                            ///////////////////

                            zqadj = zqadj_out;
                        }
                        {
                            double ptendency_loc_q_0_in_0 = ptendency_loc_q[((_for_it_15 + (sym_klon * (_for_it_14 - 1))) - 1)];
                            double zqadj_0_in = zqadj;
                            double ptendency_loc_q_out_0;

                            ///////////////////
                            // Tasklet code (T_l483_c483)
                            ptendency_loc_q_out_0 = (ptendency_loc_q_0_in_0 + zqadj_0_in);
                            ///////////////////

                            ptendency_loc_q[((_for_it_15 + (sym_klon * (_for_it_14 - 1))) - 1)] = ptendency_loc_q_out_0;
                        }
                    }
                    if ((_if_cond_3 == 1)) {
                        {
                            {
                                double ptendency_loc_t_0_in_0 = ptendency_loc_t[((_for_it_15 + (sym_klon * (_for_it_14 - 1))) - 1)];
                                double ydthf_var_48_0_in_ralvdcp = v_ydthf_var_48_ralvdcp[0];
                                double zqadj_0_in = zqadj;
                                double ptendency_loc_t_out_0;

                                ///////////////////
                                // Tasklet code (T_l484_c484)
                                ptendency_loc_t_out_0 = (ptendency_loc_t_0_in_0 - (ydthf_var_48_0_in_ralvdcp * zqadj_0_in));
                                ///////////////////

                                ptendency_loc_t[((_for_it_15 + (sym_klon * (_for_it_14 - 1))) - 1)] = ptendency_loc_t_out_0;
                            }
                        }
                    }
                    _if_cond_4 = (iphase[(_for_it_13 - 1)] == 2);
                    if ((_if_cond_4 == 1)) {
                        {
                            {
                                double ptendency_loc_t_0_in_0 = ptendency_loc_t[((_for_it_15 + (sym_klon * (_for_it_14 - 1))) - 1)];
                                double ydthf_var_48_0_in_ralsdcp = v_ydthf_var_48_ralsdcp[0];
                                double zqadj_0_in = zqadj;
                                double ptendency_loc_t_out_0;

                                ///////////////////
                                // Tasklet code (T_l485_c485)
                                ptendency_loc_t_out_0 = (ptendency_loc_t_0_in_0 - (ydthf_var_48_0_in_ralsdcp * zqadj_0_in));
                                ///////////////////

                                ptendency_loc_t[((_for_it_15 + (sym_klon * (_for_it_14 - 1))) - 1)] = ptendency_loc_t_out_0;
                            }
                        }
                    }
                    {
                        {
                            double zqx_0_in_0 = zqx[(((_for_it_15 + ((4 * sym_klev) * sym_klon)) + (sym_klon * (_for_it_14 - 1))) - 1)];
                            double zqx_1_in_0 = zqx[(((_for_it_15 + ((sym_klev * sym_klon) * (_for_it_13 - 1))) + (sym_klon * (_for_it_14 - 1))) - 1)];
                            double zqx_out_0;

                            ///////////////////
                            // Tasklet code (T_l486_c486)
                            zqx_out_0 = (zqx_0_in_0 + zqx_1_in_0);
                            ///////////////////

                            zqx[(((_for_it_15 + ((4 * sym_klev) * sym_klon)) + (sym_klon * (_for_it_14 - 1))) - 1)] = zqx_out_0;
                        }
                    }
                    {
                        {
                            double zqx_out_0;

                            ///////////////////
                            // Tasklet code (T_l487_c487)
                            zqx_out_0 = 0.0;
                            ///////////////////

                            zqx[(((_for_it_15 + ((sym_klev * sym_klon) * (_for_it_13 - 1))) + (sym_klon * (_for_it_14 - 1))) - 1)] = zqx_out_0;
                        }
                    }
                }
            }
        }
    }

    for (_for_it_16 = 1; (_for_it_16 <= sym_klev); _for_it_16 = (_for_it_16 + 1)) {
        for (_for_it_17 = 1; (_for_it_17 <= icend); _for_it_17 = (_for_it_17 + 1)) {
            {
                double tmp_call_106_0;

                {
                    double ztp1_0_in_0 = ztp1[((_for_it_17 + (sym_klon * (_for_it_16 - 1))) - 1)];
                    double oka_out;

                    ///////////////////
                    // Tasklet code (T_l494_c494)
                    oka_out = ztp1_0_in_0;
                    ///////////////////

                    oka = oka_out;
                }
                {
                    double ptare_var_52_0_in = oka;
                    double ydthf_var_53_0_in_rtwat = v_ydthf_var_53_rtwat[0];
                    double tmp_call_106_out;

                    ///////////////////
                    // Tasklet code (T_l1362_c1362)
                    tmp_call_106_out = min(ydthf_var_53_0_in_rtwat, ptare_var_52_0_in);
                    ///////////////////

                    tmp_call_106_0 = tmp_call_106_out;
                }
                {
                    double tmp_call_106_0_in = tmp_call_106_0;
                    double ydthf_var_53_0_in_rtice = v_ydthf_var_53_rtice[0];
                    double tmp_call_105_out;

                    ///////////////////
                    // Tasklet code (T_l1362_c1362)
                    tmp_call_105_out = max(ydthf_var_53_0_in_rtice, tmp_call_106_0_in);
                    ///////////////////

                    tmp_call_105_0 = tmp_call_105_out;
                }
            }
            {
                double tmp_call_104_0;
                double tmp_arg_66_0;

                {
                    double tmp_call_105_0_in = tmp_call_105_0;
                    double ydthf_var_53_0_in_rtice = v_ydthf_var_53_rtice[0];
                    double ydthf_var_53_1_in_rtwat_rtice_r = v_ydthf_var_53_rtwat_rtice_r[0];
                    double tmp_arg_66_out;

                    ///////////////////
                    // Tasklet code (T_l1362_c1362)
                    tmp_arg_66_out = ((tmp_call_105_0_in - ydthf_var_53_0_in_rtice) * ydthf_var_53_1_in_rtwat_rtice_r);
                    ///////////////////

                    tmp_arg_66_0 = tmp_arg_66_out;
                }
                {
                    double tmp_arg_66_0_in = tmp_arg_66_0;
                    double tmp_call_104_out;

                    ///////////////////
                    // Tasklet code (T_l1362_c1362)
                    tmp_call_104_out = (dace::math::ipow(tmp_arg_66_0_in, 2));
                    ///////////////////

                    tmp_call_104_0 = tmp_call_104_out;
                }
                {
                    double tmp_call_104_0_in = tmp_call_104_0;
                    double foealfa__ret_out;

                    ///////////////////
                    // Tasklet code (T_l1362_c1362)
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
                    // Tasklet code (T_l495_c495)
                    zfoealfa_out_0 = tmp_call_0_0_in;
                    ///////////////////

                    zfoealfa[((_for_it_17 + (sym_klon * (_for_it_16 - 1))) - 1)] = zfoealfa_out_0;
                }
                {
                    double ztp1_0_in_0 = ztp1[((_for_it_17 + (sym_klon * (_for_it_16 - 1))) - 1)];
                    double oka_out;

                    ///////////////////
                    // Tasklet code (T_l496_c496)
                    oka_out = ztp1_0_in_0;
                    ///////////////////

                    oka = oka_out;
                }
                {
                    double ptare_var_52_0_in = oka;
                    double ydthf_var_53_0_in_rtwat = v_ydthf_var_53_rtwat[0];
                    double tmp_call_106_out;

                    ///////////////////
                    // Tasklet code (T_l1362_c1362)
                    tmp_call_106_out = min(ydthf_var_53_0_in_rtwat, ptare_var_52_0_in);
                    ///////////////////

                    tmp_call_106_1_8 = tmp_call_106_out;
                }
                {
                    double tmp_call_106_0_in = tmp_call_106_1_8;
                    double ydthf_var_53_0_in_rtice = v_ydthf_var_53_rtice[0];
                    double tmp_call_105_out;

                    ///////////////////
                    // Tasklet code (T_l1362_c1362)
                    tmp_call_105_out = max(ydthf_var_53_0_in_rtice, tmp_call_106_0_in);
                    ///////////////////

                    tmp_call_105_1_8 = tmp_call_105_out;
                }
                {
                    double ptare_var_54_0_in = oka;
                    double ptare_var_54_1_in = oka;
                    double ydcst_var_56_0_in_rtt = v_ydcst_var_56_rtt[0];
                    double ydthf_var_55_0_in_r3ies = v_ydthf_var_55_r3ies[0];
                    double ydthf_var_55_1_in_r4ies = v_ydthf_var_55_r4ies[0];
                    double tmp_arg_67_out;

                    ///////////////////
                    // Tasklet code (T_l1371_c1371)
                    tmp_arg_67_out = ((ydthf_var_55_0_in_r3ies * (ptare_var_54_0_in - ydcst_var_56_0_in_rtt)) / (ptare_var_54_1_in - ydthf_var_55_1_in_r4ies));
                    ///////////////////

                    tmp_arg_67_2 = tmp_arg_67_out;
                }
                {
                    double tmp_arg_67_0_in = tmp_arg_67_2;
                    double tmp_call_110_out;

                    ///////////////////
                    // Tasklet code (T_l1371_c1371)
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
                    double ydthf_var_53_0_in_rtice = v_ydthf_var_53_rtice[0];
                    double ydthf_var_53_1_in_rtwat_rtice_r = v_ydthf_var_53_rtwat_rtice_r[0];
                    double tmp_arg_66_out;

                    ///////////////////
                    // Tasklet code (T_l1362_c1362)
                    tmp_arg_66_out = ((tmp_call_105_0_in - ydthf_var_53_0_in_rtice) * ydthf_var_53_1_in_rtwat_rtice_r);
                    ///////////////////

                    tmp_arg_66_1_8 = tmp_arg_66_out;
                }
                {
                    double tmp_arg_66_0_in = tmp_arg_66_1_8;
                    double tmp_call_104_out;

                    ///////////////////
                    // Tasklet code (T_l1362_c1362)
                    tmp_call_104_out = (dace::math::ipow(tmp_arg_66_0_in, 2));
                    ///////////////////

                    tmp_call_104_1_8 = tmp_call_104_out;
                }
                {
                    double tmp_call_104_0_in = tmp_call_104_1_8;
                    double foealfa__ret_out;

                    ///////////////////
                    // Tasklet code (T_l1362_c1362)
                    foealfa__ret_out = min(1.0, tmp_call_104_0_in);
                    ///////////////////

                    tmp_call_109_2 = foealfa__ret_out;
                }
            }
            {
                double tmp_arg_68_2;
                double tmp_call_106_0_8;

                {
                    double ptare_var_52_0_in = oka;
                    double ydthf_var_53_0_in_rtwat = v_ydthf_var_53_rtwat[0];
                    double tmp_call_106_out;

                    ///////////////////
                    // Tasklet code (T_l1362_c1362)
                    tmp_call_106_out = min(ydthf_var_53_0_in_rtwat, ptare_var_52_0_in);
                    ///////////////////

                    tmp_call_106_0_8 = tmp_call_106_out;
                }
                {
                    double tmp_call_106_0_in = tmp_call_106_0_8;
                    double ydthf_var_53_0_in_rtice = v_ydthf_var_53_rtice[0];
                    double tmp_call_105_out;

                    ///////////////////
                    // Tasklet code (T_l1362_c1362)
                    tmp_call_105_out = max(ydthf_var_53_0_in_rtice, tmp_call_106_0_in);
                    ///////////////////

                    tmp_call_105_0_8 = tmp_call_105_out;
                }
                {
                    double ptare_var_54_0_in = oka;
                    double ptare_var_54_1_in = oka;
                    double ydcst_var_56_0_in_rtt = v_ydcst_var_56_rtt[0];
                    double ydthf_var_55_0_in_r3les = v_ydthf_var_55_r3les[0];
                    double ydthf_var_55_1_in_r4les = v_ydthf_var_55_r4les[0];
                    double tmp_arg_68_out;

                    ///////////////////
                    // Tasklet code (T_l1371_c1371)
                    tmp_arg_68_out = ((ydthf_var_55_0_in_r3les * (ptare_var_54_0_in - ydcst_var_56_0_in_rtt)) / (ptare_var_54_1_in - ydthf_var_55_1_in_r4les));
                    ///////////////////

                    tmp_arg_68_2 = tmp_arg_68_out;
                }
                {
                    double tmp_arg_68_0_in = tmp_arg_68_2;
                    double tmp_call_108_out;

                    ///////////////////
                    // Tasklet code (T_l1371_c1371)
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
                    double ydthf_var_53_0_in_rtice = v_ydthf_var_53_rtice[0];
                    double ydthf_var_53_1_in_rtwat_rtice_r = v_ydthf_var_53_rtwat_rtice_r[0];
                    double tmp_arg_66_out;

                    ///////////////////
                    // Tasklet code (T_l1362_c1362)
                    tmp_arg_66_out = ((tmp_call_105_0_in - ydthf_var_53_0_in_rtice) * ydthf_var_53_1_in_rtwat_rtice_r);
                    ///////////////////

                    tmp_arg_66_0_8 = tmp_arg_66_out;
                }
                {
                    double tmp_arg_66_0_in = tmp_arg_66_0_8;
                    double tmp_call_104_out;

                    ///////////////////
                    // Tasklet code (T_l1362_c1362)
                    tmp_call_104_out = (dace::math::ipow(tmp_arg_66_0_in, 2));
                    ///////////////////

                    tmp_call_104_0_8 = tmp_call_104_out;
                }
                {
                    double tmp_call_104_0_in = tmp_call_104_0_8;
                    double foealfa__ret_out;

                    ///////////////////
                    // Tasklet code (T_l1362_c1362)
                    foealfa__ret_out = min(1.0, tmp_call_104_0_in);
                    ///////////////////

                    tmp_call_107_2 = foealfa__ret_out;
                }
                {
                    double tmp_call_107_0_in = tmp_call_107_2;
                    double tmp_call_108_0_in = tmp_call_108_2;
                    double tmp_call_109_0_in = tmp_call_109_2;
                    double tmp_call_110_0_in = tmp_call_110_2;
                    double ydthf_var_55_0_in_r2es = v_ydthf_var_55_r2es[0];
                    double foeewm__ret_out;

                    ///////////////////
                    // Tasklet code (T_l1371_c1371)
                    foeewm__ret_out = (ydthf_var_55_0_in_r2es * ((tmp_call_107_0_in * tmp_call_108_0_in) + ((1.0 - tmp_call_109_0_in) * tmp_call_110_0_in)));
                    ///////////////////

                    tmp_call_5 = foeewm__ret_out;
                }
                {
                    double pap_var_17_0_in_0 = pap_var_17[((_for_it_17 + (sym_klon * (_for_it_16 - 1))) - 1)];
                    double tmp_call_5_0_in = tmp_call_5;
                    double tmp_arg_0_out;

                    ///////////////////
                    // Tasklet code (T_l497_c497)
                    tmp_arg_0_out = (tmp_call_5_0_in / pap_var_17_0_in_0);
                    ///////////////////

                    tmp_arg_0 = tmp_arg_0_out;
                }
                {
                    double tmp_arg_0_0_in = tmp_arg_0;
                    double tmp_call_1_out;

                    ///////////////////
                    // Tasklet code (T_l497_c497)
                    tmp_call_1_out = min(tmp_arg_0_0_in, 0.5);
                    ///////////////////

                    tmp_call_1 = tmp_call_1_out;
                }
                {
                    double tmp_call_1_0_in = tmp_call_1;
                    double zfoeewmt_out_0;

                    ///////////////////
                    // Tasklet code (T_l497_c497)
                    zfoeewmt_out_0 = tmp_call_1_0_in;
                    ///////////////////

                    zfoeewmt[((_for_it_17 + (sym_klon * (_for_it_16 - 1))) - 1)] = zfoeewmt_out_0;
                }
                {
                    double zfoeewmt_0_in_0 = zfoeewmt[((_for_it_17 + (sym_klon * (_for_it_16 - 1))) - 1)];
                    double zqsmix_out_0;

                    ///////////////////
                    // Tasklet code (T_l498_c498)
                    zqsmix_out_0 = zfoeewmt_0_in_0;
                    ///////////////////

                    zqsmix[((_for_it_17 + (sym_klon * (_for_it_16 - 1))) - 1)] = zqsmix_out_0;
                }
                {
                    double ydcst_var_47_0_in_retv = v_ydcst_var_47_retv[0];
                    double zqsmix_0_in_0 = zqsmix[((_for_it_17 + (sym_klon * (_for_it_16 - 1))) - 1)];
                    double zqsmix_1_in_0 = zqsmix[((_for_it_17 + (sym_klon * (_for_it_16 - 1))) - 1)];
                    double zqsmix_out_0;

                    ///////////////////
                    // Tasklet code (T_l499_c499)
                    zqsmix_out_0 = (zqsmix_0_in_0 / (1.0 - (ydcst_var_47_0_in_retv * zqsmix_1_in_0)));
                    ///////////////////

                    zqsmix[((_for_it_17 + (sym_klon * (_for_it_16 - 1))) - 1)] = zqsmix_out_0;
                }
                {
                    double ztp1_0_in_0 = ztp1[((_for_it_17 + (sym_klon * (_for_it_16 - 1))) - 1)];
                    double oka_out;

                    ///////////////////
                    // Tasklet code (T_l500_c500)
                    oka_out = ztp1_0_in_0;
                    ///////////////////

                    oka = oka_out;
                }
            }
            if (((oka - *v_ydcst_var_51_rtt) >= 0.0)) {
                {
                    {
                        double tmp_call_103_out;

                        ///////////////////
                        // Tasklet code (T_l1355_c1355)
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
                        // Tasklet code (T_l1355_c1355)
                        tmp_call_1_out = abs(1.0);
                        ///////////////////

                        tmp_call_1_0 = tmp_call_1_out;
                    }
                    {
                        double tmp_call_1_0_in = tmp_call_1_0;
                        double tmp_call_103_out;

                        ///////////////////
                        // Tasklet code (T_l1355_c1355)
                        tmp_call_103_out = (-tmp_call_1_0_in);
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
                    // Tasklet code (T_l1355_c1355)
                    foedelta__ret_out = max(0.0, tmp_call_103_0_in);
                    ///////////////////

                    zalfa = foedelta__ret_out;
                }
                {
                    double ztp1_0_in_0 = ztp1[((_for_it_17 + (sym_klon * (_for_it_16 - 1))) - 1)];
                    double oka_out;

                    ///////////////////
                    // Tasklet code (T_l502_c502)
                    oka_out = ztp1_0_in_0;
                    ///////////////////

                    oka = oka_out;
                }
                {
                    double ptare_var_64_0_in = oka;
                    double ptare_var_64_1_in = oka;
                    double ydcst_var_66_0_in_rtt = v_ydcst_var_66_rtt[0];
                    double ydthf_var_65_0_in_r3ies = v_ydthf_var_65_r3ies[0];
                    double ydthf_var_65_1_in_r4ies = v_ydthf_var_65_r4ies[0];
                    double tmp_arg_72_out;

                    ///////////////////
                    // Tasklet code (T_l1403_c1403)
                    tmp_arg_72_out = ((ydthf_var_65_0_in_r3ies * (ptare_var_64_0_in - ydcst_var_66_0_in_rtt)) / (ptare_var_64_1_in - ydthf_var_65_1_in_r4ies));
                    ///////////////////

                    tmp_arg_72_1 = tmp_arg_72_out;
                }
                {
                    double tmp_arg_72_0_in = tmp_arg_72_1;
                    double tmp_call_118_out;

                    ///////////////////
                    // Tasklet code (T_l1403_c1403)
                    tmp_call_118_out = exp(tmp_arg_72_0_in);
                    ///////////////////

                    tmp_call_118_1 = tmp_call_118_out;
                }
                {
                    double tmp_call_118_0_in = tmp_call_118_1;
                    double ydthf_var_65_0_in_r2es = v_ydthf_var_65_r2es[0];
                    double foeeice__ret_out;

                    ///////////////////
                    // Tasklet code (T_l1403_c1403)
                    foeeice__ret_out = (ydthf_var_65_0_in_r2es * tmp_call_118_0_in);
                    ///////////////////

                    tmp_call_7 = foeeice__ret_out;
                }
                {
                    double ptare_var_61_0_in = oka;
                    double ptare_var_61_1_in = oka;
                    double ydcst_var_63_0_in_rtt = v_ydcst_var_63_rtt[0];
                    double ydthf_var_62_0_in_r3les = v_ydthf_var_62_r3les[0];
                    double ydthf_var_62_1_in_r4les = v_ydthf_var_62_r4les[0];
                    double tmp_arg_71_out;

                    ///////////////////
                    // Tasklet code (T_l1394_c1394)
                    tmp_arg_71_out = ((ydthf_var_62_0_in_r3les * (ptare_var_61_0_in - ydcst_var_63_0_in_rtt)) / (ptare_var_61_1_in - ydthf_var_62_1_in_r4les));
                    ///////////////////

                    tmp_arg_71_2 = tmp_arg_71_out;
                }
                {
                    double tmp_arg_71_0_in = tmp_arg_71_2;
                    double tmp_call_117_out;

                    ///////////////////
                    // Tasklet code (T_l1394_c1394)
                    tmp_call_117_out = exp(tmp_arg_71_0_in);
                    ///////////////////

                    tmp_call_117_2 = tmp_call_117_out;
                }
                {
                    double tmp_call_117_0_in = tmp_call_117_2;
                    double ydthf_var_62_0_in_r2es = v_ydthf_var_62_r2es[0];
                    double foeeliq__ret_out;

                    ///////////////////
                    // Tasklet code (T_l1394_c1394)
                    foeeliq__ret_out = (ydthf_var_62_0_in_r2es * tmp_call_117_0_in);
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

                {
                    double pap_var_17_0_in_0 = pap_var_17[((_for_it_17 + (sym_klon * (_for_it_16 - 1))) - 1)];
                    double tmp_call_6_0_in = tmp_call_6;
                    double tmp_call_7_0_in = tmp_call_7;
                    double zalfa_0_in = zalfa;
                    double zalfa_1_in = zalfa;
                    double tmp_arg_1_out;

                    ///////////////////
                    // Tasklet code (T_l503_c503)
                    tmp_arg_1_out = (((zalfa_0_in * tmp_call_6_0_in) + ((1.0 - zalfa_1_in) * tmp_call_7_0_in)) / pap_var_17_0_in_0);
                    ///////////////////

                    tmp_arg_1 = tmp_arg_1_out;
                }
                {
                    double tmp_arg_1_0_in = tmp_arg_1;
                    double tmp_call_2_out;

                    ///////////////////
                    // Tasklet code (T_l503_c503)
                    tmp_call_2_out = min(tmp_arg_1_0_in, 0.5);
                    ///////////////////

                    tmp_call_2 = tmp_call_2_out;
                }
                {
                    double tmp_call_2_0_in = tmp_call_2;
                    double zfoeew_out_0;

                    ///////////////////
                    // Tasklet code (T_l503_c503)
                    zfoeew_out_0 = tmp_call_2_0_in;
                    ///////////////////

                    zfoeew[((_for_it_17 + (sym_klon * (_for_it_16 - 1))) - 1)] = zfoeew_out_0;
                }
                {
                    double zfoeew_0_in_0 = zfoeew[((_for_it_17 + (sym_klon * (_for_it_16 - 1))) - 1)];
                    double tmp_call_3_out;

                    ///////////////////
                    // Tasklet code (T_l504_c504)
                    tmp_call_3_out = min(0.5, zfoeew_0_in_0);
                    ///////////////////

                    tmp_call_3 = tmp_call_3_out;
                }
                {
                    double tmp_call_3_0_in = tmp_call_3;
                    double zfoeew_out_0;

                    ///////////////////
                    // Tasklet code (T_l504_c504)
                    zfoeew_out_0 = tmp_call_3_0_in;
                    ///////////////////

                    zfoeew[((_for_it_17 + (sym_klon * (_for_it_16 - 1))) - 1)] = zfoeew_out_0;
                }
                {
                    double ydcst_var_47_0_in_retv = v_ydcst_var_47_retv[0];
                    double zfoeew_0_in_0 = zfoeew[((_for_it_17 + (sym_klon * (_for_it_16 - 1))) - 1)];
                    double zfoeew_1_in_0 = zfoeew[((_for_it_17 + (sym_klon * (_for_it_16 - 1))) - 1)];
                    double zqsice_out_0;

                    ///////////////////
                    // Tasklet code (T_l505_c505)
                    zqsice_out_0 = (zfoeew_0_in_0 / (1.0 - (ydcst_var_47_0_in_retv * zfoeew_1_in_0)));
                    ///////////////////

                    zqsice[((_for_it_17 + (sym_klon * (_for_it_16 - 1))) - 1)] = zqsice_out_0;
                }
                {
                    double ztp1_0_in_0 = ztp1[((_for_it_17 + (sym_klon * (_for_it_16 - 1))) - 1)];
                    double oka_out;

                    ///////////////////
                    // Tasklet code (T_l506_c506)
                    oka_out = ztp1_0_in_0;
                    ///////////////////

                    oka = oka_out;
                }
                {
                    double ptare_var_61_0_in = oka;
                    double ptare_var_61_1_in = oka;
                    double ydcst_var_63_0_in_rtt = v_ydcst_var_63_rtt[0];
                    double ydthf_var_62_0_in_r3les = v_ydthf_var_62_r3les[0];
                    double ydthf_var_62_1_in_r4les = v_ydthf_var_62_r4les[0];
                    double tmp_arg_71_out;

                    ///////////////////
                    // Tasklet code (T_l1394_c1394)
                    tmp_arg_71_out = ((ydthf_var_62_0_in_r3les * (ptare_var_61_0_in - ydcst_var_63_0_in_rtt)) / (ptare_var_61_1_in - ydthf_var_62_1_in_r4les));
                    ///////////////////

                    tmp_arg_71_1 = tmp_arg_71_out;
                }
                {
                    double tmp_arg_71_0_in = tmp_arg_71_1;
                    double tmp_call_117_out;

                    ///////////////////
                    // Tasklet code (T_l1394_c1394)
                    tmp_call_117_out = exp(tmp_arg_71_0_in);
                    ///////////////////

                    tmp_call_117_1 = tmp_call_117_out;
                }
                {
                    double tmp_call_117_0_in = tmp_call_117_1;
                    double ydthf_var_62_0_in_r2es = v_ydthf_var_62_r2es[0];
                    double foeeliq__ret_out;

                    ///////////////////
                    // Tasklet code (T_l1394_c1394)
                    foeeliq__ret_out = (ydthf_var_62_0_in_r2es * tmp_call_117_0_in);
                    ///////////////////

                    tmp_call_8 = foeeliq__ret_out;
                }
                {
                    double pap_var_17_0_in_0 = pap_var_17[((_for_it_17 + (sym_klon * (_for_it_16 - 1))) - 1)];
                    double tmp_call_8_0_in = tmp_call_8;
                    double tmp_arg_2_out;

                    ///////////////////
                    // Tasklet code (T_l507_c507)
                    tmp_arg_2_out = (tmp_call_8_0_in / pap_var_17_0_in_0);
                    ///////////////////

                    tmp_arg_2 = tmp_arg_2_out;
                }
                {
                    double tmp_arg_2_0_in = tmp_arg_2;
                    double tmp_call_4_out;

                    ///////////////////
                    // Tasklet code (T_l507_c507)
                    tmp_call_4_out = min(tmp_arg_2_0_in, 0.5);
                    ///////////////////

                    tmp_call_4 = tmp_call_4_out;
                }
                {
                    double tmp_call_4_0_in = tmp_call_4;
                    double zfoeeliqt_out_0;

                    ///////////////////
                    // Tasklet code (T_l507_c507)
                    zfoeeliqt_out_0 = tmp_call_4_0_in;
                    ///////////////////

                    zfoeeliqt[((_for_it_17 + (sym_klon * (_for_it_16 - 1))) - 1)] = zfoeeliqt_out_0;
                }
                {
                    double zfoeeliqt_0_in_0 = zfoeeliqt[((_for_it_17 + (sym_klon * (_for_it_16 - 1))) - 1)];
                    double zqsliq_out_0;

                    ///////////////////
                    // Tasklet code (T_l508_c508)
                    zqsliq_out_0 = zfoeeliqt_0_in_0;
                    ///////////////////

                    zqsliq[((_for_it_17 + (sym_klon * (_for_it_16 - 1))) - 1)] = zqsliq_out_0;
                }
            }
            {
                {
                    double ydcst_var_47_0_in_retv = v_ydcst_var_47_retv[0];
                    double zqsliq_0_in_0 = zqsliq[((_for_it_17 + (sym_klon * (_for_it_16 - 1))) - 1)];
                    double zqsliq_1_in_0 = zqsliq[((_for_it_17 + (sym_klon * (_for_it_16 - 1))) - 1)];
                    double zqsliq_out_0;

                    ///////////////////
                    // Tasklet code (T_l509_c509)
                    zqsliq_out_0 = (zqsliq_0_in_0 / (1.0 - (ydcst_var_47_0_in_retv * zqsliq_1_in_0)));
                    ///////////////////

                    zqsliq[((_for_it_17 + (sym_klon * (_for_it_16 - 1))) - 1)] = zqsliq_out_0;
                }
            }
        }
    }

    for (_for_it_18 = 1; (_for_it_18 <= sym_klev); _for_it_18 = (_for_it_18 + 1)) {
        for (_for_it_19 = 1; (_for_it_19 <= icend); _for_it_19 = (_for_it_19 + 1)) {
            {
                double tmp_call_9;
                double tmp_call_10;

                {
                    double za_0_in_0 = za[((_for_it_19 + (sym_klon * (_for_it_18 - 1))) - 1)];
                    double tmp_call_10_out;

                    ///////////////////
                    // Tasklet code (T_l514_c514)
                    tmp_call_10_out = min(1.0, za_0_in_0);
                    ///////////////////

                    tmp_call_10 = tmp_call_10_out;
                }
                {
                    double tmp_call_10_0_in = tmp_call_10;
                    double tmp_call_9_out;

                    ///////////////////
                    // Tasklet code (T_l514_c514)
                    tmp_call_9_out = max(0.0, tmp_call_10_0_in);
                    ///////////////////

                    tmp_call_9 = tmp_call_9_out;
                }
                {
                    double tmp_call_9_0_in = tmp_call_9;
                    double za_out_0;

                    ///////////////////
                    // Tasklet code (T_l514_c514)
                    za_out_0 = tmp_call_9_0_in;
                    ///////////////////

                    za[((_for_it_19 + (sym_klon * (_for_it_18 - 1))) - 1)] = za_out_0;
                }
                {
                    double zqx_0_in_0 = zqx[((_for_it_19 + (sym_klon * (_for_it_18 - 1))) - 1)];
                    double zqx_1_in_0 = zqx[(((_for_it_19 + (sym_klev * sym_klon)) + (sym_klon * (_for_it_18 - 1))) - 1)];
                    double zli_out_0;

                    ///////////////////
                    // Tasklet code (T_l515_c515)
                    zli_out_0 = (zqx_0_in_0 + zqx_1_in_0);
                    ///////////////////

                    zli[((_for_it_19 + (sym_klon * (_for_it_18 - 1))) - 1)] = zli_out_0;
                }
                {
                    double ydecldp_var_49_0_in_rlmin = v_ydecldp_var_49_rlmin[0];
                    double zli_0_in_0 = zli[((_for_it_19 + (sym_klon * (_for_it_18 - 1))) - 1)];
                    double _if_cond_5_out;

                    ///////////////////
                    // Tasklet code (T_l0_c0)
                    _if_cond_5_out = (zli_0_in_0 > ydecldp_var_49_0_in_rlmin);
                    ///////////////////

                    _if_cond_5 = _if_cond_5_out;
                }
            }
            if ((_if_cond_5 == 1)) {
                {
                    {
                        double zli_0_in_0 = zli[((_for_it_19 + (sym_klon * (_for_it_18 - 1))) - 1)];
                        double zqx_0_in_0 = zqx[((_for_it_19 + (sym_klon * (_for_it_18 - 1))) - 1)];
                        double zliqfrac_out_0;

                        ///////////////////
                        // Tasklet code (T_l517_c517)
                        zliqfrac_out_0 = (zqx_0_in_0 / zli_0_in_0);
                        ///////////////////

                        zliqfrac[((_for_it_19 + (sym_klon * (_for_it_18 - 1))) - 1)] = zliqfrac_out_0;
                    }
                    {
                        double zliqfrac_0_in_0 = zliqfrac[((_for_it_19 + (sym_klon * (_for_it_18 - 1))) - 1)];
                        double zicefrac_out_0;

                        ///////////////////
                        // Tasklet code (T_l518_c518)
                        zicefrac_out_0 = (1.0 - zliqfrac_0_in_0);
                        ///////////////////

                        zicefrac[((_for_it_19 + (sym_klon * (_for_it_18 - 1))) - 1)] = zicefrac_out_0;
                    }
                }
            } else {
                {
                    {
                        double zliqfrac_out_0;

                        ///////////////////
                        // Tasklet code (T_l520_c520)
                        zliqfrac_out_0 = 0.0;
                        ///////////////////

                        zliqfrac[((_for_it_19 + (sym_klon * (_for_it_18 - 1))) - 1)] = zliqfrac_out_0;
                    }
                    {
                        double zicefrac_out_0;

                        ///////////////////
                        // Tasklet code (T_l521_c521)
                        zicefrac_out_0 = 0.0;
                        ///////////////////

                        zicefrac[((_for_it_19 + (sym_klon * (_for_it_18 - 1))) - 1)] = zicefrac_out_0;
                    }
                }
            }
        }
    }

    for (tmp_parfor_12 = 1; (tmp_parfor_12 <= sym_klon); tmp_parfor_12 = (tmp_parfor_12 + 1)) {
        {
            {
                double zanewm1_out_0;

                ///////////////////
                // Tasklet code (T_l537_c537)
                zanewm1_out_0 = 0.0;
                ///////////////////

                zanewm1[(tmp_parfor_12 - 1)] = zanewm1_out_0;
            }
        }
    }

    for (tmp_parfor_13 = 1; (tmp_parfor_13 <= sym_klon); tmp_parfor_13 = (tmp_parfor_13 + 1)) {
        {
            {
                double zda_out_0;

                ///////////////////
                // Tasklet code (T_l538_c538)
                zda_out_0 = 0.0;
                ///////////////////

                zda[(tmp_parfor_13 - 1)] = zda_out_0;
            }
        }
    }

    for (tmp_parfor_14 = 1; (tmp_parfor_14 <= sym_klon); tmp_parfor_14 = (tmp_parfor_14 + 1)) {
        {
            {
                double zcovpclr_out_0;

                ///////////////////
                // Tasklet code (T_l539_c539)
                zcovpclr_out_0 = 0.0;
                ///////////////////

                zcovpclr[(tmp_parfor_14 - 1)] = zcovpclr_out_0;
            }
        }
    }

    for (tmp_parfor_15 = 1; (tmp_parfor_15 <= sym_klon); tmp_parfor_15 = (tmp_parfor_15 + 1)) {
        {
            {
                double zcovpmax_out_0;

                ///////////////////
                // Tasklet code (T_l540_c540)
                zcovpmax_out_0 = 0.0;
                ///////////////////

                zcovpmax[(tmp_parfor_15 - 1)] = zcovpmax_out_0;
            }
        }
    }

    for (tmp_parfor_16 = 1; (tmp_parfor_16 <= sym_klon); tmp_parfor_16 = (tmp_parfor_16 + 1)) {
        {
            {
                double zcovptot_out_0;

                ///////////////////
                // Tasklet code (T_l541_c541)
                zcovptot_out_0 = 0.0;
                ///////////////////

                zcovptot[(tmp_parfor_16 - 1)] = zcovptot_out_0;
            }
        }
    }

    for (tmp_parfor_17 = 1; (tmp_parfor_17 <= sym_klon); tmp_parfor_17 = (tmp_parfor_17 + 1)) {
        {
            {
                double zcldtopdist_out_0;

                ///////////////////
                // Tasklet code (T_l542_c542)
                zcldtopdist_out_0 = 0.0;
                ///////////////////

                zcldtopdist[(tmp_parfor_17 - 1)] = zcldtopdist_out_0;
            }
        }
    }

    {}

    for (_for_it_23 = *v_ydecldp_var_49_ncldtop; (_for_it_23 <= sym_klev); _for_it_23 = (_for_it_23 + 1)) {
        for (_for_it_24 = 1; (_for_it_24 <= 5); _for_it_24 = (_for_it_24 + 1)) {
            for (_for_it_25 = 1; (_for_it_25 <= icend); _for_it_25 = (_for_it_25 + 1)) {
                {
                    {
                        double zqx_0_in_0 = zqx[(((_for_it_25 + ((sym_klev * sym_klon) * (_for_it_24 - 1))) + (sym_klon * (_for_it_23 - 1))) - 1)];
                        double zqxfg_out_0;

                        ///////////////////
                        // Tasklet code (T_l546_c546)
                        zqxfg_out_0 = zqx_0_in_0;
                        ///////////////////

                        zqxfg[((_for_it_25 + (sym_klon * (_for_it_24 - 1))) - 1)] = zqxfg_out_0;
                    }
                }
            }
        }
        for (tmp_parfor_18 = 1; (tmp_parfor_18 <= sym_klon); tmp_parfor_18 = (tmp_parfor_18 + 1)) {
            {
                {
                    double zlicld_out_0;

                    ///////////////////
                    // Tasklet code (T_l549_c549)
                    zlicld_out_0 = 0.0;
                    ///////////////////

                    zlicld[(tmp_parfor_18 - 1)] = zlicld_out_0;
                }
            }
        }
        for (tmp_parfor_19 = 1; (tmp_parfor_19 <= sym_klon); tmp_parfor_19 = (tmp_parfor_19 + 1)) {
            {
                {
                    double zrainaut_out_0;

                    ///////////////////
                    // Tasklet code (T_l550_c550)
                    zrainaut_out_0 = 0.0;
                    ///////////////////

                    zrainaut[(tmp_parfor_19 - 1)] = zrainaut_out_0;
                }
            }
        }
        for (tmp_parfor_20 = 1; (tmp_parfor_20 <= sym_klon); tmp_parfor_20 = (tmp_parfor_20 + 1)) {
            {
                {
                    double zrainacc_out_0;

                    ///////////////////
                    // Tasklet code (T_l551_c551)
                    zrainacc_out_0 = 0.0;
                    ///////////////////

                    zrainacc[(tmp_parfor_20 - 1)] = zrainacc_out_0;
                }
            }
        }
        for (tmp_parfor_21 = 1; (tmp_parfor_21 <= sym_klon); tmp_parfor_21 = (tmp_parfor_21 + 1)) {
            {
                {
                    double zsnowaut_out_0;

                    ///////////////////
                    // Tasklet code (T_l552_c552)
                    zsnowaut_out_0 = 0.0;
                    ///////////////////

                    zsnowaut[(tmp_parfor_21 - 1)] = zsnowaut_out_0;
                }
            }
        }
        for (tmp_parfor_22 = 1; (tmp_parfor_22 <= sym_klon); tmp_parfor_22 = (tmp_parfor_22 + 1)) {
            {
                {
                    double zldefr_out_0;

                    ///////////////////
                    // Tasklet code (T_l553_c553)
                    zldefr_out_0 = 0.0;
                    ///////////////////

                    zldefr[(tmp_parfor_22 - 1)] = zldefr_out_0;
                }
            }
        }
        for (tmp_parfor_23 = 1; (tmp_parfor_23 <= sym_klon); tmp_parfor_23 = (tmp_parfor_23 + 1)) {
            {
                {
                    double zacust_out_0;

                    ///////////////////
                    // Tasklet code (T_l554_c554)
                    zacust_out_0 = 0.0;
                    ///////////////////

                    zacust[(tmp_parfor_23 - 1)] = zacust_out_0;
                }
            }
        }
        for (tmp_parfor_24 = 1; (tmp_parfor_24 <= sym_klon); tmp_parfor_24 = (tmp_parfor_24 + 1)) {
            {
                {
                    double zqpretot_out_0;

                    ///////////////////
                    // Tasklet code (T_l555_c555)
                    zqpretot_out_0 = 0.0;
                    ///////////////////

                    zqpretot[(tmp_parfor_24 - 1)] = zqpretot_out_0;
                }
            }
        }
        for (tmp_parfor_25 = 1; (tmp_parfor_25 <= sym_klon); tmp_parfor_25 = (tmp_parfor_25 + 1)) {
            {
                {
                    double zlfinalsum_out_0;

                    ///////////////////
                    // Tasklet code (T_l556_c556)
                    zlfinalsum_out_0 = 0.0;
                    ///////////////////

                    zlfinalsum[(tmp_parfor_25 - 1)] = zlfinalsum_out_0;
                }
            }
        }
        for (tmp_parfor_26 = 1; (tmp_parfor_26 <= sym_klon); tmp_parfor_26 = (tmp_parfor_26 + 1)) {
            {
                {
                    double zlcond1_out_0;

                    ///////////////////
                    // Tasklet code (T_l557_c557)
                    zlcond1_out_0 = 0.0;
                    ///////////////////

                    zlcond1[(tmp_parfor_26 - 1)] = zlcond1_out_0;
                }
            }
        }
        for (tmp_parfor_27 = 1; (tmp_parfor_27 <= sym_klon); tmp_parfor_27 = (tmp_parfor_27 + 1)) {
            {
                {
                    double zlcond2_out_0;

                    ///////////////////
                    // Tasklet code (T_l558_c558)
                    zlcond2_out_0 = 0.0;
                    ///////////////////

                    zlcond2[(tmp_parfor_27 - 1)] = zlcond2_out_0;
                }
            }
        }
        for (tmp_parfor_28 = 1; (tmp_parfor_28 <= sym_klon); tmp_parfor_28 = (tmp_parfor_28 + 1)) {
            {
                {
                    double zsupsat_out_0;

                    ///////////////////
                    // Tasklet code (T_l559_c559)
                    zsupsat_out_0 = 0.0;
                    ///////////////////

                    zsupsat[(tmp_parfor_28 - 1)] = zsupsat_out_0;
                }
            }
        }
        for (tmp_parfor_31 = 1; (tmp_parfor_31 <= sym_klon); tmp_parfor_31 = (tmp_parfor_31 + 1)) {
            {
                {
                    double zsolab_out_0;

                    ///////////////////
                    // Tasklet code (T_l562_c562)
                    zsolab_out_0 = 0.0;
                    ///////////////////

                    zsolab[(tmp_parfor_31 - 1)] = zsolab_out_0;
                }
            }
        }
        for (tmp_parfor_32 = 1; (tmp_parfor_32 <= sym_klon); tmp_parfor_32 = (tmp_parfor_32 + 1)) {
            {
                {
                    double zsolac_out_0;

                    ///////////////////
                    // Tasklet code (T_l563_c563)
                    zsolac_out_0 = 0.0;
                    ///////////////////

                    zsolac[(tmp_parfor_32 - 1)] = zsolac_out_0;
                }
            }
        }
        for (tmp_parfor_35 = 1; (tmp_parfor_35 <= 5); tmp_parfor_35 = (tmp_parfor_35 + 1)) {
            for (tmp_parfor_34 = 1; (tmp_parfor_34 <= 5); tmp_parfor_34 = (tmp_parfor_34 + 1)) {
                for (tmp_parfor_33 = 1; (tmp_parfor_33 <= sym_klon); tmp_parfor_33 = (tmp_parfor_33 + 1)) {
                    {
                        {
                            double zsolqb_out_0;

                            ///////////////////
                            // Tasklet code (T_l564_c564)
                            zsolqb_out_0 = 0.0;
                            ///////////////////

                            zsolqb[((((sym_klon * (tmp_parfor_34 - 1)) + ((5 * sym_klon) * (tmp_parfor_35 - 1))) + tmp_parfor_33) - 1)] = zsolqb_out_0;
                        }
                    }
                }
            }
        }
        for (tmp_parfor_38 = 1; (tmp_parfor_38 <= 5); tmp_parfor_38 = (tmp_parfor_38 + 1)) {
            for (tmp_parfor_37 = 1; (tmp_parfor_37 <= 5); tmp_parfor_37 = (tmp_parfor_37 + 1)) {
                for (tmp_parfor_36 = 1; (tmp_parfor_36 <= sym_klon); tmp_parfor_36 = (tmp_parfor_36 + 1)) {
                    {
                        {
                            double zsolqa_out_0;

                            ///////////////////
                            // Tasklet code (T_l565_c565)
                            zsolqa_out_0 = 0.0;
                            ///////////////////

                            zsolqa[((((sym_klon * (tmp_parfor_37 - 1)) + ((5 * sym_klon) * (tmp_parfor_38 - 1))) + tmp_parfor_36) - 1)] = zsolqa_out_0;
                        }
                    }
                }
            }
        }
        for (tmp_parfor_40 = 1; (tmp_parfor_40 <= 5); tmp_parfor_40 = (tmp_parfor_40 + 1)) {
            for (tmp_parfor_39 = 1; (tmp_parfor_39 <= sym_klon); tmp_parfor_39 = (tmp_parfor_39 + 1)) {
                {
                    {
                        double zfallsrce_out_0;

                        ///////////////////
                        // Tasklet code (T_l566_c566)
                        zfallsrce_out_0 = 0.0;
                        ///////////////////

                        zfallsrce[(((sym_klon * (tmp_parfor_40 - 1)) + tmp_parfor_39) - 1)] = zfallsrce_out_0;
                    }
                }
            }
        }
        for (tmp_parfor_42 = 1; (tmp_parfor_42 <= 5); tmp_parfor_42 = (tmp_parfor_42 + 1)) {
            for (tmp_parfor_41 = 1; (tmp_parfor_41 <= sym_klon); tmp_parfor_41 = (tmp_parfor_41 + 1)) {
                {
                    {
                        double zfallsink_out_0;

                        ///////////////////
                        // Tasklet code (T_l567_c567)
                        zfallsink_out_0 = 0.0;
                        ///////////////////

                        zfallsink[(((sym_klon * (tmp_parfor_42 - 1)) + tmp_parfor_41) - 1)] = zfallsink_out_0;
                    }
                }
            }
        }
        for (tmp_parfor_44 = 1; (tmp_parfor_44 <= 5); tmp_parfor_44 = (tmp_parfor_44 + 1)) {
            for (tmp_parfor_43 = 1; (tmp_parfor_43 <= sym_klon); tmp_parfor_43 = (tmp_parfor_43 + 1)) {
                {
                    {
                        double zconvsrce_out_0;

                        ///////////////////
                        // Tasklet code (T_l568_c568)
                        zconvsrce_out_0 = 0.0;
                        ///////////////////

                        zconvsrce[(((sym_klon * (tmp_parfor_44 - 1)) + tmp_parfor_43) - 1)] = zconvsrce_out_0;
                    }
                }
            }
        }
        for (tmp_parfor_46 = 1; (tmp_parfor_46 <= 5); tmp_parfor_46 = (tmp_parfor_46 + 1)) {
            for (tmp_parfor_45 = 1; (tmp_parfor_45 <= sym_klon); tmp_parfor_45 = (tmp_parfor_45 + 1)) {
                {
                    {
                        double zconvsink_out_0;

                        ///////////////////
                        // Tasklet code (T_l569_c569)
                        zconvsink_out_0 = 0.0;
                        ///////////////////

                        zconvsink[(((sym_klon * (tmp_parfor_46 - 1)) + tmp_parfor_45) - 1)] = zconvsink_out_0;
                    }
                }
            }
        }
        for (tmp_parfor_48 = 1; (tmp_parfor_48 <= 5); tmp_parfor_48 = (tmp_parfor_48 + 1)) {
            for (tmp_parfor_47 = 1; (tmp_parfor_47 <= sym_klon); tmp_parfor_47 = (tmp_parfor_47 + 1)) {
                {
                    {
                        double zpsupsatsrce_out_0;

                        ///////////////////
                        // Tasklet code (T_l570_c570)
                        zpsupsatsrce_out_0 = 0.0;
                        ///////////////////

                        zpsupsatsrce[(((sym_klon * (tmp_parfor_48 - 1)) + tmp_parfor_47) - 1)] = zpsupsatsrce_out_0;
                    }
                }
            }
        }
        for (tmp_parfor_50 = 1; (tmp_parfor_50 <= 5); tmp_parfor_50 = (tmp_parfor_50 + 1)) {
            for (tmp_parfor_49 = 1; (tmp_parfor_49 <= sym_klon); tmp_parfor_49 = (tmp_parfor_49 + 1)) {
                {
                    {
                        double zratio_out_0;

                        ///////////////////
                        // Tasklet code (T_l571_c571)
                        zratio_out_0 = 0.0;
                        ///////////////////

                        zratio[(((sym_klon * (tmp_parfor_50 - 1)) + tmp_parfor_49) - 1)] = zratio_out_0;
                    }
                }
            }
        }
        for (tmp_parfor_51 = 1; (tmp_parfor_51 <= sym_klon); tmp_parfor_51 = (tmp_parfor_51 + 1)) {
            {
                {
                    double zicetot_out_0;

                    ///////////////////
                    // Tasklet code (T_l572_c572)
                    zicetot_out_0 = 0.0;
                    ///////////////////

                    zicetot[(tmp_parfor_51 - 1)] = zicetot_out_0;
                }
            }
        }
        for (_for_it_26 = 1; (_for_it_26 <= icend); _for_it_26 = (_for_it_26 + 1)) {
            {
                double* zgdp;
                zgdp = new double DACE_ALIGN(64)[sym_klon];

                {
                    double pap_var_17_0_in_0 = pap_var_17[((_for_it_26 + (sym_klon * (_for_it_23 - 1))) - 1)];
                    double ydcst_var_47_0_in_rd = v_ydcst_var_47_rd[0];
                    double ztp1_0_in_0 = ztp1[((_for_it_26 + (sym_klon * (_for_it_23 - 1))) - 1)];
                    double zrho_out_0;

                    ///////////////////
                    // Tasklet code (T_l576_c576)
                    zrho_out_0 = (pap_var_17_0_in_0 / (ydcst_var_47_0_in_rd * ztp1_0_in_0));
                    ///////////////////

                    zrho[(_for_it_26 - 1)] = zrho_out_0;
                }
                {
                    double paph_var_18_0_in_0 = paph_var_18[(((_for_it_23 * sym_klon) + _for_it_26) - 1)];
                    double paph_var_18_1_in_0 = paph_var_18[((_for_it_26 + (sym_klon * (_for_it_23 - 1))) - 1)];
                    double zdp_out_0;

                    ///////////////////
                    // Tasklet code (T_l574_c574)
                    zdp_out_0 = (paph_var_18_0_in_0 - paph_var_18_1_in_0);
                    ///////////////////

                    zdp[(_for_it_26 - 1)] = zdp_out_0;
                }
                {
                    double ydcst_var_47_0_in_rg = v_ydcst_var_47_rg[0];
                    double zdp_0_in_0 = zdp[(_for_it_26 - 1)];
                    double zgdp_out_0;

                    ///////////////////
                    // Tasklet code (T_l575_c575)
                    zgdp_out_0 = (ydcst_var_47_0_in_rg / zdp_0_in_0);
                    ///////////////////

                    zgdp[(_for_it_26 - 1)] = zgdp_out_0;
                }
                {
                    double ptsphy_var_5_0_in = ptsphy_var_5[0];
                    double zgdp_0_in_0 = zgdp[(_for_it_26 - 1)];
                    double zdtgdp_out_0;

                    ///////////////////
                    // Tasklet code (T_l577_c577)
                    zdtgdp_out_0 = (ptsphy_var_5_0_in * zgdp_0_in_0);
                    ///////////////////

                    zdtgdp[(_for_it_26 - 1)] = zdtgdp_out_0;
                }
                delete[] zgdp;
            }
            {
                {
                    double ptsphy_var_5_0_in = ptsphy_var_5[0];
                    double ydcst_var_47_0_in_rg = v_ydcst_var_47_rg[0];
                    double zdp_0_in_0 = zdp[(_for_it_26 - 1)];
                    double zrdtgdp_out_0;

                    ///////////////////
                    // Tasklet code (T_l578_c578)
                    zrdtgdp_out_0 = (zdp_0_in_0 * (1.0 / (ptsphy_var_5_0_in * ydcst_var_47_0_in_rg)));
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
                double* v_ydthf_var_48_r4les;
                v_ydthf_var_48_r4les = (double*)(&(ydthf_var_48->r4les));
                double* v_ydthf_var_48_r5les;
                v_ydthf_var_48_r5les = (double*)(&(ydthf_var_48->r5les));

                {
                    double ydthf_var_48_0_in_r4les = v_ydthf_var_48_r4les[0];
                    double ztp1_0_in_0 = ztp1[((_for_it_26 + (sym_klon * (_for_it_23 - 1))) - 1)];
                    double tmp_arg_3_out;

                    ///////////////////
                    // Tasklet code (T_l580_c580)
                    tmp_arg_3_out = (ztp1_0_in_0 - ydthf_var_48_0_in_r4les);
                    ///////////////////

                    tmp_arg_3 = tmp_arg_3_out;
                }
                {
                    double tmp_arg_3_0_in = tmp_arg_3;
                    double tmp_call_11_out;

                    ///////////////////
                    // Tasklet code (T_l580_c580)
                    tmp_call_11_out = (dace::math::ipow(tmp_arg_3_0_in, 2));
                    ///////////////////

                    tmp_call_11 = tmp_call_11_out;
                }
                {
                    double tmp_call_11_0_in = tmp_call_11;
                    double ydthf_var_48_0_in_r5les = v_ydthf_var_48_r5les[0];
                    double zfacw_out;

                    ///////////////////
                    // Tasklet code (T_l580_c580)
                    zfacw_out = (ydthf_var_48_0_in_r5les / tmp_call_11_0_in);
                    ///////////////////

                    zfacw = zfacw_out;
                }
                {
                    double ydcst_var_47_0_in_retv = v_ydcst_var_47_retv[0];
                    double zfoeeliqt_0_in_0 = zfoeeliqt[((_for_it_26 + (sym_klon * (_for_it_23 - 1))) - 1)];
                    double zcor_out;

                    ///////////////////
                    // Tasklet code (T_l581_c581)
                    zcor_out = (1.0 / (1.0 - (ydcst_var_47_0_in_retv * zfoeeliqt_0_in_0)));
                    ///////////////////

                    zcor = zcor_out;
                }
            }
            zalfaw = zfoealfa[((_for_it_26 + (sym_klon * (_for_it_23 - 1))) - 1)];
            {
                double* zdqsicedt;
                zdqsicedt = new double DACE_ALIGN(64)[sym_klon];
                double tmp_call_12;
                double tmp_arg_4;
                double* v_ydthf_var_48_r4ies;
                v_ydthf_var_48_r4ies = (double*)(&(ydthf_var_48->r4ies));
                double* v_ydthf_var_48_r5ies;
                v_ydthf_var_48_r5ies = (double*)(&(ydthf_var_48->r5ies));

                {
                    double ydthf_var_48_0_in_r4ies = v_ydthf_var_48_r4ies[0];
                    double ztp1_0_in_0 = ztp1[((_for_it_26 + (sym_klon * (_for_it_23 - 1))) - 1)];
                    double tmp_arg_4_out;

                    ///////////////////
                    // Tasklet code (T_l584_c584)
                    tmp_arg_4_out = (ztp1_0_in_0 - ydthf_var_48_0_in_r4ies);
                    ///////////////////

                    tmp_arg_4 = tmp_arg_4_out;
                }
                {
                    double tmp_arg_4_0_in = tmp_arg_4;
                    double tmp_call_12_out;

                    ///////////////////
                    // Tasklet code (T_l584_c584)
                    tmp_call_12_out = (dace::math::ipow(tmp_arg_4_0_in, 2));
                    ///////////////////

                    tmp_call_12 = tmp_call_12_out;
                }
                {
                    double tmp_call_12_0_in = tmp_call_12;
                    double ydthf_var_48_0_in_r5ies = v_ydthf_var_48_r5ies[0];
                    double zfaci_out;

                    ///////////////////
                    // Tasklet code (T_l584_c584)
                    zfaci_out = (ydthf_var_48_0_in_r5ies / tmp_call_12_0_in);
                    ///////////////////

                    zfaci = zfaci_out;
                }
                {
                    double ydcst_var_47_0_in_retv = v_ydcst_var_47_retv[0];
                    double zfoeew_0_in_0 = zfoeew[((_for_it_26 + (sym_klon * (_for_it_23 - 1))) - 1)];
                    double zcor_out;

                    ///////////////////
                    // Tasklet code (T_l585_c585)
                    zcor_out = (1.0 / (1.0 - (ydcst_var_47_0_in_retv * zfoeew_0_in_0)));
                    ///////////////////

                    zcor = zcor_out;
                }
                {
                    double zcor_0_in = zcor;
                    double zfaci_0_in = zfaci;
                    double zqsice_0_in_0 = zqsice[((_for_it_26 + (sym_klon * (_for_it_23 - 1))) - 1)];
                    double zdqsicedt_out_0;

                    ///////////////////
                    // Tasklet code (T_l586_c586)
                    zdqsicedt_out_0 = ((zfaci_0_in * zcor_0_in) * zqsice_0_in_0);
                    ///////////////////

                    zdqsicedt[(_for_it_26 - 1)] = zdqsicedt_out_0;
                }
                {
                    double ydthf_var_48_0_in_ralsdcp = v_ydthf_var_48_ralsdcp[0];
                    double zdqsicedt_0_in_0 = zdqsicedt[(_for_it_26 - 1)];
                    double zcorqsice_out_0;

                    ///////////////////
                    // Tasklet code (T_l587_c587)
                    zcorqsice_out_0 = (1.0 + (ydthf_var_48_0_in_ralsdcp * zdqsicedt_0_in_0));
                    ///////////////////

                    zcorqsice[(_for_it_26 - 1)] = zcorqsice_out_0;
                }
                delete[] zdqsicedt;
            }
            zfac = ((zalfaw * zfacw) + ((1.0 - zalfaw) * zfaci));
            {
                double tmp_call_106_1_7;

                {
                    double ydcst_var_47_0_in_retv = v_ydcst_var_47_retv[0];
                    double zfoeewmt_0_in_0 = zfoeewmt[((_for_it_26 + (sym_klon * (_for_it_23 - 1))) - 1)];
                    double zcor_out;

                    ///////////////////
                    // Tasklet code (T_l591_c591)
                    zcor_out = (1.0 / (1.0 - (ydcst_var_47_0_in_retv * zfoeewmt_0_in_0)));
                    ///////////////////

                    zcor = zcor_out;
                }
                {
                    double zcor_0_in = zcor;
                    double zqsmix_0_in_0 = zqsmix[((_for_it_26 + (sym_klon * (_for_it_23 - 1))) - 1)];
                    double zdqsmixdt_out_0;

                    ///////////////////
                    // Tasklet code (T_l592_c592)
                    zdqsmixdt_out_0 = ((zfac * zcor_0_in) * zqsmix_0_in_0);
                    ///////////////////

                    zdqsmixdt[(_for_it_26 - 1)] = zdqsmixdt_out_0;
                }
                {
                    double ztp1_0_in_0 = ztp1[((_for_it_26 + (sym_klon * (_for_it_23 - 1))) - 1)];
                    double oka_out;

                    ///////////////////
                    // Tasklet code (T_l593_c593)
                    oka_out = ztp1_0_in_0;
                    ///////////////////

                    oka = oka_out;
                }
                {
                    double ptare_var_52_0_in = oka;
                    double ydthf_var_53_0_in_rtwat = v_ydthf_var_53_rtwat[0];
                    double tmp_call_106_out;

                    ///////////////////
                    // Tasklet code (T_l1362_c1362)
                    tmp_call_106_out = min(ydthf_var_53_0_in_rtwat, ptare_var_52_0_in);
                    ///////////////////

                    tmp_call_106_1_7 = tmp_call_106_out;
                }
                {
                    double tmp_call_106_0_in = tmp_call_106_1_7;
                    double ydthf_var_53_0_in_rtice = v_ydthf_var_53_rtice[0];
                    double tmp_call_105_out;

                    ///////////////////
                    // Tasklet code (T_l1362_c1362)
                    tmp_call_105_out = max(ydthf_var_53_0_in_rtice, tmp_call_106_0_in);
                    ///////////////////

                    tmp_call_105_1_7 = tmp_call_105_out;
                }
            }
            {
                double tmp_call_104_1_7;
                double tmp_arg_66_1_7;

                {
                    double tmp_call_105_0_in = tmp_call_105_1_7;
                    double ydthf_var_53_0_in_rtice = v_ydthf_var_53_rtice[0];
                    double ydthf_var_53_1_in_rtwat_rtice_r = v_ydthf_var_53_rtwat_rtice_r[0];
                    double tmp_arg_66_out;

                    ///////////////////
                    // Tasklet code (T_l1362_c1362)
                    tmp_arg_66_out = ((tmp_call_105_0_in - ydthf_var_53_0_in_rtice) * ydthf_var_53_1_in_rtwat_rtice_r);
                    ///////////////////

                    tmp_arg_66_1_7 = tmp_arg_66_out;
                }
                {
                    double tmp_arg_66_0_in = tmp_arg_66_1_7;
                    double tmp_call_104_out;

                    ///////////////////
                    // Tasklet code (T_l1362_c1362)
                    tmp_call_104_out = (dace::math::ipow(tmp_arg_66_0_in, 2));
                    ///////////////////

                    tmp_call_104_1_7 = tmp_call_104_out;
                }
                {
                    double tmp_call_104_0_in = tmp_call_104_1_7;
                    double foealfa__ret_out;

                    ///////////////////
                    // Tasklet code (T_l1362_c1362)
                    foealfa__ret_out = min(1.0, tmp_call_104_0_in);
                    ///////////////////

                    tmp_call_116_2 = foealfa__ret_out;
                }
            }
            {
                double tmp_call_106_0_7;

                {
                    double ptare_var_52_0_in = oka;
                    double ydthf_var_53_0_in_rtwat = v_ydthf_var_53_rtwat[0];
                    double tmp_call_106_out;

                    ///////////////////
                    // Tasklet code (T_l1362_c1362)
                    tmp_call_106_out = min(ydthf_var_53_0_in_rtwat, ptare_var_52_0_in);
                    ///////////////////

                    tmp_call_106_0_7 = tmp_call_106_out;
                }
                {
                    double tmp_call_106_0_in = tmp_call_106_0_7;
                    double ydthf_var_53_0_in_rtice = v_ydthf_var_53_rtice[0];
                    double tmp_call_105_out;

                    ///////////////////
                    // Tasklet code (T_l1362_c1362)
                    tmp_call_105_out = max(ydthf_var_53_0_in_rtice, tmp_call_106_0_in);
                    ///////////////////

                    tmp_call_105_0_7 = tmp_call_105_out;
                }
            }
            {
                double* zcorqsmix;
                zcorqsmix = new double DACE_ALIGN(64)[sym_klon];
                double tmp_call_13;
                double tmp_call_14;
                double tmp_call_17;
                double tmp_arg_5;
                double tmp_call_115_2;
                double tmp_call_104_0_7;
                double tmp_arg_66_0_7;

                {
                    double tmp_call_105_0_in = tmp_call_105_0_7;
                    double ydthf_var_53_0_in_rtice = v_ydthf_var_53_rtice[0];
                    double ydthf_var_53_1_in_rtwat_rtice_r = v_ydthf_var_53_rtwat_rtice_r[0];
                    double tmp_arg_66_out;

                    ///////////////////
                    // Tasklet code (T_l1362_c1362)
                    tmp_arg_66_out = ((tmp_call_105_0_in - ydthf_var_53_0_in_rtice) * ydthf_var_53_1_in_rtwat_rtice_r);
                    ///////////////////

                    tmp_arg_66_0_7 = tmp_arg_66_out;
                }
                {
                    double tmp_arg_66_0_in = tmp_arg_66_0_7;
                    double tmp_call_104_out;

                    ///////////////////
                    // Tasklet code (T_l1362_c1362)
                    tmp_call_104_out = (dace::math::ipow(tmp_arg_66_0_in, 2));
                    ///////////////////

                    tmp_call_104_0_7 = tmp_call_104_out;
                }
                {
                    double tmp_call_104_0_in = tmp_call_104_0_7;
                    double foealfa__ret_out;

                    ///////////////////
                    // Tasklet code (T_l1362_c1362)
                    foealfa__ret_out = min(1.0, tmp_call_104_0_in);
                    ///////////////////

                    tmp_call_115_2 = foealfa__ret_out;
                }
                {
                    double tmp_call_115_0_in = tmp_call_115_2;
                    double tmp_call_116_0_in = tmp_call_116_2;
                    double ydthf_var_60_0_in_ralvdcp = v_ydthf_var_60_ralvdcp[0];
                    double ydthf_var_60_1_in_ralsdcp = v_ydthf_var_60_ralsdcp[0];
                    double foeldcpm__ret_out;

                    ///////////////////
                    // Tasklet code (T_l1385_c1385)
                    foeldcpm__ret_out = ((tmp_call_115_0_in * ydthf_var_60_0_in_ralvdcp) + ((1.0 - tmp_call_116_0_in) * ydthf_var_60_1_in_ralsdcp));
                    ///////////////////

                    tmp_call_13 = foeldcpm__ret_out;
                }
                {
                    double tmp_call_13_0_in = tmp_call_13;
                    double zdqsmixdt_0_in_0 = zdqsmixdt[(_for_it_26 - 1)];
                    double zcorqsmix_out_0;

                    ///////////////////
                    // Tasklet code (T_l594_c594)
                    zcorqsmix_out_0 = (1.0 + (tmp_call_13_0_in * zdqsmixdt_0_in_0));
                    ///////////////////

                    zcorqsmix[(_for_it_26 - 1)] = zcorqsmix_out_0;
                }
                {
                    double zcorqsmix_0_in_0 = zcorqsmix[(_for_it_26 - 1)];
                    double zqsmix_0_in_0 = zqsmix[((_for_it_26 + (sym_klon * (_for_it_23 - 1))) - 1)];
                    double zqx_0_in_0 = zqx[(((_for_it_26 + ((4 * sym_klev) * sym_klon)) + (sym_klon * (_for_it_23 - 1))) - 1)];
                    double tmp_arg_5_out;

                    ///////////////////
                    // Tasklet code (T_l595_c595)
                    tmp_arg_5_out = ((zqsmix_0_in_0 - zqx_0_in_0) / zcorqsmix_0_in_0);
                    ///////////////////

                    tmp_arg_5 = tmp_arg_5_out;
                }
                {
                    double tmp_arg_5_0_in = tmp_arg_5;
                    double tmp_call_14_out;

                    ///////////////////
                    // Tasklet code (T_l595_c595)
                    tmp_call_14_out = max(tmp_arg_5_0_in, 0.0);
                    ///////////////////

                    tmp_call_14 = tmp_call_14_out;
                }
                {
                    double tmp_call_14_0_in = tmp_call_14;
                    double zevaplimmix_out_0;

                    ///////////////////
                    // Tasklet code (T_l595_c595)
                    zevaplimmix_out_0 = tmp_call_14_0_in;
                    ///////////////////

                    zevaplimmix[(_for_it_26 - 1)] = zevaplimmix_out_0;
                }
                {
                    double za_0_in_0 = za[((_for_it_26 + (sym_klon * (_for_it_23 - 1))) - 1)];
                    double zepsec_0_in = zepsec;
                    double tmp_call_17_out;

                    ///////////////////
                    // Tasklet code (T_l598_c598)
                    tmp_call_17_out = max(za_0_in_0, zepsec_0_in);
                    ///////////////////

                    tmp_call_17 = tmp_call_17_out;
                }
                {
                    double tmp_call_17_0_in = tmp_call_17;
                    double ztmpa_out;

                    ///////////////////
                    // Tasklet code (T_l598_c598)
                    ztmpa_out = (1.0 / tmp_call_17_0_in);
                    ///////////////////

                    ztmpa = ztmpa_out;
                }
                {
                    double zqx_0_in_0 = zqx[((_for_it_26 + (sym_klon * (_for_it_23 - 1))) - 1)];
                    double ztmpa_0_in = ztmpa;
                    double zliqcld_out_0;

                    ///////////////////
                    // Tasklet code (T_l599_c599)
                    zliqcld_out_0 = (zqx_0_in_0 * ztmpa_0_in);
                    ///////////////////

                    zliqcld[(_for_it_26 - 1)] = zliqcld_out_0;
                }
                {
                    double zqx_0_in_0 = zqx[(((_for_it_26 + (sym_klev * sym_klon)) + (sym_klon * (_for_it_23 - 1))) - 1)];
                    double ztmpa_0_in = ztmpa;
                    double zicecld_out_0;

                    ///////////////////
                    // Tasklet code (T_l600_c600)
                    zicecld_out_0 = (zqx_0_in_0 * ztmpa_0_in);
                    ///////////////////

                    zicecld[(_for_it_26 - 1)] = zicecld_out_0;
                }
                {
                    double zicecld_0_in_0 = zicecld[(_for_it_26 - 1)];
                    double zliqcld_0_in_0 = zliqcld[(_for_it_26 - 1)];
                    double zlicld_out_0;

                    ///////////////////
                    // Tasklet code (T_l601_c601)
                    zlicld_out_0 = (zliqcld_0_in_0 + zicecld_0_in_0);
                    ///////////////////

                    zlicld[(_for_it_26 - 1)] = zlicld_out_0;
                }
                delete[] zcorqsmix;
            }
        }
        for (_for_it_27 = 1; (_for_it_27 <= icend); _for_it_27 = (_for_it_27 + 1)) {
            {
                {
                    double ydecldp_var_49_0_in_rlmin = v_ydecldp_var_49_rlmin[0];
                    double zqx_0_in_0 = zqx[((_for_it_27 + (sym_klon * (_for_it_23 - 1))) - 1)];
                    double _if_cond_8_out;

                    ///////////////////
                    // Tasklet code (T_l0_c0)
                    _if_cond_8_out = (zqx_0_in_0 < ydecldp_var_49_0_in_rlmin);
                    ///////////////////

                    _if_cond_8 = _if_cond_8_out;
                }
            }
            if ((_if_cond_8 == 1)) {
                {
                    {
                        double zqx_0_in_0 = zqx[((_for_it_27 + (sym_klon * (_for_it_23 - 1))) - 1)];
                        double zsolqa_out_0;

                        ///////////////////
                        // Tasklet code (T_l605_c605)
                        zsolqa_out_0 = zqx_0_in_0;
                        ///////////////////

                        zsolqa[((_for_it_27 + (4 * sym_klon)) - 1)] = zsolqa_out_0;
                    }
                    {
                        double zqx_0_in_0 = zqx[((_for_it_27 + (sym_klon * (_for_it_23 - 1))) - 1)];
                        double zsolqa_out_0;

                        ///////////////////
                        // Tasklet code (T_l606_c606)
                        zsolqa_out_0 = (-zqx_0_in_0);
                        ///////////////////

                        zsolqa[((_for_it_27 + (20 * sym_klon)) - 1)] = zsolqa_out_0;
                    }
                }
            }
            {
                {
                    double ydecldp_var_49_0_in_rlmin = v_ydecldp_var_49_rlmin[0];
                    double zqx_0_in_0 = zqx[(((_for_it_27 + (sym_klev * sym_klon)) + (sym_klon * (_for_it_23 - 1))) - 1)];
                    double _if_cond_9_out;

                    ///////////////////
                    // Tasklet code (T_l0_c0)
                    _if_cond_9_out = (zqx_0_in_0 < ydecldp_var_49_0_in_rlmin);
                    ///////////////////

                    _if_cond_9 = _if_cond_9_out;
                }
            }
            if ((_if_cond_9 == 1)) {
                {
                    {
                        double zqx_0_in_0 = zqx[(((_for_it_27 + (sym_klev * sym_klon)) + (sym_klon * (_for_it_23 - 1))) - 1)];
                        double zsolqa_out_0;

                        ///////////////////
                        // Tasklet code (T_l609_c609)
                        zsolqa_out_0 = zqx_0_in_0;
                        ///////////////////

                        zsolqa[((_for_it_27 + (9 * sym_klon)) - 1)] = zsolqa_out_0;
                    }
                    {
                        double zqx_0_in_0 = zqx[(((_for_it_27 + (sym_klev * sym_klon)) + (sym_klon * (_for_it_23 - 1))) - 1)];
                        double zsolqa_out_0;

                        ///////////////////
                        // Tasklet code (T_l610_c610)
                        zsolqa_out_0 = (-zqx_0_in_0);
                        ///////////////////

                        zsolqa[((_for_it_27 + (21 * sym_klon)) - 1)] = zsolqa_out_0;
                    }
                }
            }
        }
        for (_for_it_28 = 1; (_for_it_28 <= icend); _for_it_28 = (_for_it_28 + 1)) {
            {
                double tmp_call_18;
                double* v_ydthf_var_68_rkoop1;
                v_ydthf_var_68_rkoop1 = (double*)(&(ydthf_var_48->rkoop1));
                double* v_ydthf_var_68_rkoop2;
                v_ydthf_var_68_rkoop2 = (double*)(&(ydthf_var_48->rkoop2));
                double tmp_call_120_0;
                double tmp_call_119_0;
                double tmp_arg_73_0;
                double tmp_arg_74_0;
                double tmp_call_117_0_0;
                double tmp_arg_71_0_0;
                double tmp_call_118_0_0;
                double tmp_arg_72_0_0;

                {
                    double ztp1_0_in_0 = ztp1[((_for_it_28 + (sym_klon * (_for_it_23 - 1))) - 1)];
                    double oka_out;

                    ///////////////////
                    // Tasklet code (T_l614_c614)
                    oka_out = ztp1_0_in_0;
                    ///////////////////

                    oka = oka_out;
                }
                {
                    double ptare_var_67_0_in = oka;
                    double ydthf_var_68_0_in_rkoop1 = v_ydthf_var_68_rkoop1[0];
                    double ydthf_var_68_1_in_rkoop2 = v_ydthf_var_68_rkoop2[0];
                    double tmp_arg_73_out;

                    ///////////////////
                    // Tasklet code (T_l1412_c1412)
                    tmp_arg_73_out = (ydthf_var_68_0_in_rkoop1 - (ydthf_var_68_1_in_rkoop2 * ptare_var_67_0_in));
                    ///////////////////

                    tmp_arg_73_0 = tmp_arg_73_out;
                }
                {
                    double ptare_var_64_0_in = oka;
                    double ptare_var_64_1_in = oka;
                    double ydcst_var_66_0_in_rtt = v_ydcst_var_66_rtt[0];
                    double ydthf_var_65_0_in_r3ies = v_ydthf_var_65_r3ies[0];
                    double ydthf_var_65_1_in_r4ies = v_ydthf_var_65_r4ies[0];
                    double tmp_arg_72_out;

                    ///////////////////
                    // Tasklet code (T_l1403_c1403)
                    tmp_arg_72_out = ((ydthf_var_65_0_in_r3ies * (ptare_var_64_0_in - ydcst_var_66_0_in_rtt)) / (ptare_var_64_1_in - ydthf_var_65_1_in_r4ies));
                    ///////////////////

                    tmp_arg_72_0_0 = tmp_arg_72_out;
                }
                {
                    double tmp_arg_72_0_in = tmp_arg_72_0_0;
                    double tmp_call_118_out;

                    ///////////////////
                    // Tasklet code (T_l1403_c1403)
                    tmp_call_118_out = exp(tmp_arg_72_0_in);
                    ///////////////////

                    tmp_call_118_0_0 = tmp_call_118_out;
                }
                {
                    double tmp_call_118_0_in = tmp_call_118_0_0;
                    double ydthf_var_65_0_in_r2es = v_ydthf_var_65_r2es[0];
                    double foeeice__ret_out;

                    ///////////////////
                    // Tasklet code (T_l1403_c1403)
                    foeeice__ret_out = (ydthf_var_65_0_in_r2es * tmp_call_118_0_in);
                    ///////////////////

                    tmp_call_120_0 = foeeice__ret_out;
                }
                {
                    double ptare_var_61_0_in = oka;
                    double ptare_var_61_1_in = oka;
                    double ydcst_var_63_0_in_rtt = v_ydcst_var_63_rtt[0];
                    double ydthf_var_62_0_in_r3les = v_ydthf_var_62_r3les[0];
                    double ydthf_var_62_1_in_r4les = v_ydthf_var_62_r4les[0];
                    double tmp_arg_71_out;

                    ///////////////////
                    // Tasklet code (T_l1394_c1394)
                    tmp_arg_71_out = ((ydthf_var_62_0_in_r3les * (ptare_var_61_0_in - ydcst_var_63_0_in_rtt)) / (ptare_var_61_1_in - ydthf_var_62_1_in_r4les));
                    ///////////////////

                    tmp_arg_71_0_0 = tmp_arg_71_out;
                }
                {
                    double tmp_arg_71_0_in = tmp_arg_71_0_0;
                    double tmp_call_117_out;

                    ///////////////////
                    // Tasklet code (T_l1394_c1394)
                    tmp_call_117_out = exp(tmp_arg_71_0_in);
                    ///////////////////

                    tmp_call_117_0_0 = tmp_call_117_out;
                }
                {
                    double tmp_call_117_0_in = tmp_call_117_0_0;
                    double ydthf_var_62_0_in_r2es = v_ydthf_var_62_r2es[0];
                    double foeeliq__ret_out;

                    ///////////////////
                    // Tasklet code (T_l1394_c1394)
                    foeeliq__ret_out = (ydthf_var_62_0_in_r2es * tmp_call_117_0_in);
                    ///////////////////

                    tmp_call_119_0 = foeeliq__ret_out;
                }
                {
                    double tmp_call_119_0_in = tmp_call_119_0;
                    double tmp_call_120_0_in = tmp_call_120_0;
                    double tmp_arg_74_out;

                    ///////////////////
                    // Tasklet code (T_l1412_c1412)
                    tmp_arg_74_out = (tmp_call_119_0_in / tmp_call_120_0_in);
                    ///////////////////

                    tmp_arg_74_0 = tmp_arg_74_out;
                }
                {
                    double tmp_arg_73_0_in = tmp_arg_73_0;
                    double tmp_arg_74_0_in = tmp_arg_74_0;
                    double fokoop__ret_out;

                    ///////////////////
                    // Tasklet code (T_l1412_c1412)
                    fokoop__ret_out = min(tmp_arg_73_0_in, tmp_arg_74_0_in);
                    ///////////////////

                    tmp_call_18 = fokoop__ret_out;
                }
                {
                    double tmp_call_18_0_in = tmp_call_18;
                    double zfokoop_out_0;

                    ///////////////////
                    // Tasklet code (T_l615_c615)
                    zfokoop_out_0 = tmp_call_18_0_in;
                    ///////////////////

                    zfokoop[(_for_it_28 - 1)] = zfokoop_out_0;
                }
            }
        }
        for (_for_it_29 = 1; (_for_it_29 <= icend); _for_it_29 = (_for_it_29 + 1)) {
            {
                {
                    double ydcst_var_47_0_in_rtt = v_ydcst_var_47_rtt[0];
                    int ydecldp_var_49_0_in_nssopt = v_ydecldp_var_49_nssopt[0];
                    double ztp1_0_in_0 = ztp1[((_for_it_29 + (sym_klon * (_for_it_23 - 1))) - 1)];
                    double _if_cond_10_out;

                    ///////////////////
                    // Tasklet code (T_l0_c0)
                    _if_cond_10_out = ((ztp1_0_in_0 >= ydcst_var_47_0_in_rtt) || (ydecldp_var_49_0_in_nssopt == 0));
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
                        // Tasklet code (T_l620_c620)
                        zfaci_out = 1.0;
                        ///////////////////

                        zfaci = zfaci_out;
                    }
                }
            } else {
                zfac = (za[((_for_it_29 + (sym_klon * (_for_it_23 - 1))) - 1)] + (zfokoop[(_for_it_29 - 1)] * (1.0 - za[((_for_it_29 + (sym_klon * (_for_it_23 - 1))) - 1)])));
                {
                    double* v_ydecldp_var_49_rkooptau;
                    v_ydecldp_var_49_rkooptau = (double*)(&(ydecldp_var_49->rkooptau));

                    {
                        double ptsphy_var_5_0_in = ptsphy_var_5[0];
                        double ydecldp_var_49_0_in_rkooptau = v_ydecldp_var_49_rkooptau[0];
                        double zfaci_out;

                        ///////////////////
                        // Tasklet code (T_l623_c623)
                        zfaci_out = (ptsphy_var_5_0_in / ydecldp_var_49_0_in_rkooptau);
                        ///////////////////

                        zfaci = zfaci_out;
                    }
                }
            }
            {
                {
                    double ydecldp_var_49_0_in_ramin = v_ydecldp_var_49_ramin[0];
                    double za_0_in_0 = za[((_for_it_29 + (sym_klon * (_for_it_23 - 1))) - 1)];
                    double _if_cond_11_out;

                    ///////////////////
                    // Tasklet code (T_l0_c0)
                    _if_cond_11_out = (za_0_in_0 > (1.0 - ydecldp_var_49_0_in_ramin));
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
                        double zqsice_0_in_0 = zqsice[((_for_it_29 + (sym_klon * (_for_it_23 - 1))) - 1)];
                        double zqx_0_in_0 = zqx[(((_for_it_29 + ((4 * sym_klev) * sym_klon)) + (sym_klon * (_for_it_23 - 1))) - 1)];
                        double tmp_arg_8_out;

                        ///////////////////
                        // Tasklet code (T_l626_c626)
                        tmp_arg_8_out = ((zqx_0_in_0 - (zfac * zqsice_0_in_0)) / zcorqsice_0_in_0);
                        ///////////////////

                        tmp_arg_8 = tmp_arg_8_out;
                    }
                    {
                        double tmp_arg_8_0_in = tmp_arg_8;
                        double tmp_call_19_out;

                        ///////////////////
                        // Tasklet code (T_l626_c626)
                        tmp_call_19_out = max(tmp_arg_8_0_in, 0.0);
                        ///////////////////

                        tmp_call_19 = tmp_call_19_out;
                    }
                    {
                        double tmp_call_19_0_in = tmp_call_19;
                        double zsupsat_out_0;

                        ///////////////////
                        // Tasklet code (T_l626_c626)
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
                        double za_0_in_0 = za[((_for_it_29 + (sym_klon * (_for_it_23 - 1))) - 1)];
                        double tmp_arg_9_out;

                        ///////////////////
                        // Tasklet code (T_l628_c628)
                        tmp_arg_9_out = (1.0 - za_0_in_0);
                        ///////////////////

                        tmp_arg_9 = tmp_arg_9_out;
                    }
                    {
                        double tmp_arg_9_0_in = tmp_arg_9;
                        double zepsilon_0_in = zepsilon;
                        double tmp_call_20_out;

                        ///////////////////
                        // Tasklet code (T_l628_c628)
                        tmp_call_20_out = max(tmp_arg_9_0_in, zepsilon_0_in);
                        ///////////////////

                        tmp_call_20 = tmp_call_20_out;
                    }
                    {
                        double tmp_call_20_0_in = tmp_call_20;
                        double za_0_in_0 = za[((_for_it_29 + (sym_klon * (_for_it_23 - 1))) - 1)];
                        double zqsice_0_in_0 = zqsice[((_for_it_29 + (sym_klon * (_for_it_23 - 1))) - 1)];
                        double zqx_0_in_0 = zqx[(((_for_it_29 + ((4 * sym_klev) * sym_klon)) + (sym_klon * (_for_it_23 - 1))) - 1)];
                        double zqp1env_out;

                        ///////////////////
                        // Tasklet code (T_l628_c628)
                        zqp1env_out = ((zqx_0_in_0 - (za_0_in_0 * zqsice_0_in_0)) / tmp_call_20_0_in);
                        ///////////////////

                        zqp1env = zqp1env_out;
                    }
                    {
                        double za_0_in_0 = za[((_for_it_29 + (sym_klon * (_for_it_23 - 1))) - 1)];
                        double zcorqsice_0_in_0 = zcorqsice[(_for_it_29 - 1)];
                        double zqp1env_0_in = zqp1env;
                        double zqsice_0_in_0 = zqsice[((_for_it_29 + (sym_klon * (_for_it_23 - 1))) - 1)];
                        double tmp_arg_10_out;

                        ///////////////////
                        // Tasklet code (T_l629_c629)
                        tmp_arg_10_out = (((1.0 - za_0_in_0) * (zqp1env_0_in - (zfac * zqsice_0_in_0))) / zcorqsice_0_in_0);
                        ///////////////////

                        tmp_arg_10 = tmp_arg_10_out;
                    }
                    {
                        double tmp_arg_10_0_in = tmp_arg_10;
                        double tmp_call_21_out;

                        ///////////////////
                        // Tasklet code (T_l629_c629)
                        tmp_call_21_out = max(tmp_arg_10_0_in, 0.0);
                        ///////////////////

                        tmp_call_21 = tmp_call_21_out;
                    }
                    {
                        double tmp_call_21_0_in = tmp_call_21;
                        double zsupsat_out_0;

                        ///////////////////
                        // Tasklet code (T_l629_c629)
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
                        double ydecldp_var_49_0_in_rthomo = v_ydecldp_var_49_rthomo[0];
                        double ztp1_0_in_0 = ztp1[((_for_it_29 + (sym_klon * (_for_it_23 - 1))) - 1)];
                        double _if_cond_13_out;

                        ///////////////////
                        // Tasklet code (T_l0_c0)
                        _if_cond_13_out = (ztp1_0_in_0 > ydecldp_var_49_0_in_rthomo);
                        ///////////////////

                        _if_cond_13 = _if_cond_13_out;
                    }
                }
                if ((_if_cond_13 == 1)) {
                    {
                        {
                            double zsolqa_0_in_0 = zsolqa[((_for_it_29 + (20 * sym_klon)) - 1)];
                            double zsupsat_0_in_0 = zsupsat[(_for_it_29 - 1)];
                            double zsolqa_out_0;

                            ///////////////////
                            // Tasklet code (T_l633_c633)
                            zsolqa_out_0 = (zsolqa_0_in_0 + zsupsat_0_in_0);
                            ///////////////////

                            zsolqa[((_for_it_29 + (20 * sym_klon)) - 1)] = zsolqa_out_0;
                        }
                        {
                            double zsolqa_0_in_0 = zsolqa[((_for_it_29 + (4 * sym_klon)) - 1)];
                            double zsupsat_0_in_0 = zsupsat[(_for_it_29 - 1)];
                            double zsolqa_out_0;

                            ///////////////////
                            // Tasklet code (T_l634_c634)
                            zsolqa_out_0 = (zsolqa_0_in_0 - zsupsat_0_in_0);
                            ///////////////////

                            zsolqa[((_for_it_29 + (4 * sym_klon)) - 1)] = zsolqa_out_0;
                        }
                        {
                            double zqxfg_0_in_0 = zqxfg[(_for_it_29 - 1)];
                            double zsupsat_0_in_0 = zsupsat[(_for_it_29 - 1)];
                            double zqxfg_out_0;

                            ///////////////////
                            // Tasklet code (T_l635_c635)
                            zqxfg_out_0 = (zqxfg_0_in_0 + zsupsat_0_in_0);
                            ///////////////////

                            zqxfg[(_for_it_29 - 1)] = zqxfg_out_0;
                        }
                    }
                } else {
                    {
                        {
                            double zsolqa_0_in_0 = zsolqa[((_for_it_29 + (21 * sym_klon)) - 1)];
                            double zsupsat_0_in_0 = zsupsat[(_for_it_29 - 1)];
                            double zsolqa_out_0;

                            ///////////////////
                            // Tasklet code (T_l637_c637)
                            zsolqa_out_0 = (zsolqa_0_in_0 + zsupsat_0_in_0);
                            ///////////////////

                            zsolqa[((_for_it_29 + (21 * sym_klon)) - 1)] = zsolqa_out_0;
                        }
                        {
                            double zsolqa_0_in_0 = zsolqa[((_for_it_29 + (9 * sym_klon)) - 1)];
                            double zsupsat_0_in_0 = zsupsat[(_for_it_29 - 1)];
                            double zsolqa_out_0;

                            ///////////////////
                            // Tasklet code (T_l638_c638)
                            zsolqa_out_0 = (zsolqa_0_in_0 - zsupsat_0_in_0);
                            ///////////////////

                            zsolqa[((_for_it_29 + (9 * sym_klon)) - 1)] = zsolqa_out_0;
                        }
                        {
                            double zqxfg_0_in_0 = zqxfg[((_for_it_29 + sym_klon) - 1)];
                            double zsupsat_0_in_0 = zsupsat[(_for_it_29 - 1)];
                            double zqxfg_out_0;

                            ///////////////////
                            // Tasklet code (T_l639_c639)
                            zqxfg_out_0 = (zqxfg_0_in_0 + zsupsat_0_in_0);
                            ///////////////////

                            zqxfg[((_for_it_29 + sym_klon) - 1)] = zqxfg_out_0;
                        }
                    }
                }
                {
                    {
                        double za_0_in_0 = za[((_for_it_29 + (sym_klon * (_for_it_23 - 1))) - 1)];
                        double zfaci_0_in = zfaci;
                        double zsolac_out_0;

                        ///////////////////
                        // Tasklet code (T_l641_c641)
                        zsolac_out_0 = ((1.0 - za_0_in_0) * zfaci_0_in);
                        ///////////////////

                        zsolac[(_for_it_29 - 1)] = zsolac_out_0;
                    }
                }
            }
            _if_cond_14 = (psupsat_var_30[((_for_it_29 + (sym_klon * (_for_it_23 - 1))) - 1)] > 1e-14);
            if ((_if_cond_14 == 1)) {
                {
                    {
                        double ydecldp_var_49_0_in_rthomo = v_ydecldp_var_49_rthomo[0];
                        double ztp1_0_in_0 = ztp1[((_for_it_29 + (sym_klon * (_for_it_23 - 1))) - 1)];
                        double _if_cond_15_out;

                        ///////////////////
                        // Tasklet code (T_l0_c0)
                        _if_cond_15_out = (ztp1_0_in_0 > ydecldp_var_49_0_in_rthomo);
                        ///////////////////

                        _if_cond_15 = _if_cond_15_out;
                    }
                }
                if ((_if_cond_15 == 1)) {
                    {
                        {
                            double psupsat_var_30_0_in_0 = psupsat_var_30[((_for_it_29 + (sym_klon * (_for_it_23 - 1))) - 1)];
                            double zsolqa_0_in_0 = zsolqa[(_for_it_29 - 1)];
                            double zsolqa_out_0;

                            ///////////////////
                            // Tasklet code (T_l645_c645)
                            zsolqa_out_0 = (zsolqa_0_in_0 + psupsat_var_30_0_in_0);
                            ///////////////////

                            zsolqa[(_for_it_29 - 1)] = zsolqa_out_0;
                        }
                        {
                            double psupsat_var_30_0_in_0 = psupsat_var_30[((_for_it_29 + (sym_klon * (_for_it_23 - 1))) - 1)];
                            double zpsupsatsrce_out_0;

                            ///////////////////
                            // Tasklet code (T_l646_c646)
                            zpsupsatsrce_out_0 = psupsat_var_30_0_in_0;
                            ///////////////////

                            zpsupsatsrce[(_for_it_29 - 1)] = zpsupsatsrce_out_0;
                        }
                        {
                            double psupsat_var_30_0_in_0 = psupsat_var_30[((_for_it_29 + (sym_klon * (_for_it_23 - 1))) - 1)];
                            double zqxfg_0_in_0 = zqxfg[(_for_it_29 - 1)];
                            double zqxfg_out_0;

                            ///////////////////
                            // Tasklet code (T_l647_c647)
                            zqxfg_out_0 = (zqxfg_0_in_0 + psupsat_var_30_0_in_0);
                            ///////////////////

                            zqxfg[(_for_it_29 - 1)] = zqxfg_out_0;
                        }
                    }
                } else {
                    {
                        {
                            double psupsat_var_30_0_in_0 = psupsat_var_30[((_for_it_29 + (sym_klon * (_for_it_23 - 1))) - 1)];
                            double zsolqa_0_in_0 = zsolqa[((_for_it_29 + (6 * sym_klon)) - 1)];
                            double zsolqa_out_0;

                            ///////////////////
                            // Tasklet code (T_l649_c649)
                            zsolqa_out_0 = (zsolqa_0_in_0 + psupsat_var_30_0_in_0);
                            ///////////////////

                            zsolqa[((_for_it_29 + (6 * sym_klon)) - 1)] = zsolqa_out_0;
                        }
                        {
                            double psupsat_var_30_0_in_0 = psupsat_var_30[((_for_it_29 + (sym_klon * (_for_it_23 - 1))) - 1)];
                            double zpsupsatsrce_out_0;

                            ///////////////////
                            // Tasklet code (T_l650_c650)
                            zpsupsatsrce_out_0 = psupsat_var_30_0_in_0;
                            ///////////////////

                            zpsupsatsrce[((_for_it_29 + sym_klon) - 1)] = zpsupsatsrce_out_0;
                        }
                        {
                            double psupsat_var_30_0_in_0 = psupsat_var_30[((_for_it_29 + (sym_klon * (_for_it_23 - 1))) - 1)];
                            double zqxfg_0_in_0 = zqxfg[((_for_it_29 + sym_klon) - 1)];
                            double zqxfg_out_0;

                            ///////////////////
                            // Tasklet code (T_l651_c651)
                            zqxfg_out_0 = (zqxfg_0_in_0 + psupsat_var_30_0_in_0);
                            ///////////////////

                            zqxfg[((_for_it_29 + sym_klon) - 1)] = zqxfg_out_0;
                        }
                    }
                }
                {
                    {
                        double za_0_in_0 = za[((_for_it_29 + (sym_klon * (_for_it_23 - 1))) - 1)];
                        double zfaci_0_in = zfaci;
                        double zsolac_out_0;

                        ///////////////////
                        // Tasklet code (T_l653_c653)
                        zsolac_out_0 = ((1.0 - za_0_in_0) * zfaci_0_in);
                        ///////////////////

                        zsolac[(_for_it_29 - 1)] = zsolac_out_0;
                    }
                }
            }
        }
        {
            {
                int klev_0_in = klev[0];
                int ydecldp_var_49_0_in_ncldtop = v_ydecldp_var_49_ncldtop[0];
                int _if_cond_16_out;

                ///////////////////
                // Tasklet code (T_l0_c0)
                _if_cond_16_out = ((_for_it_23 < klev_0_in) && (_for_it_23 >= ydecldp_var_49_0_in_ncldtop));
                ///////////////////

                _if_cond_16 = _if_cond_16_out;
            }
        }
        if ((_if_cond_16 == 1)) {
            for (_for_it_30 = 1; (_for_it_30 <= icend); _for_it_30 = (_for_it_30 + 1)) {
                {
                    {
                        double plude_var_23_0_in_0 = plude_var_23[((_for_it_30 + (sym_klon * (_for_it_23 - 1))) - 1)];
                        double zdtgdp_0_in_0 = zdtgdp[(_for_it_30 - 1)];
                        double plude_var_23_out_0;

                        ///////////////////
                        // Tasklet code (T_l658_c658)
                        plude_var_23_out_0 = (plude_var_23_0_in_0 * zdtgdp_0_in_0);
                        ///////////////////

                        plude_var_23[((_for_it_30 + (sym_klon * (_for_it_23 - 1))) - 1)] = plude_var_23_out_0;
                    }
                    {
                        int ldcum_var_20_0_in_0 = ldcum_var_20[(_for_it_30 - 1)];
                        double plu_var_22_0_in_0 = plu_var_22[(((_for_it_23 * sym_klon) + _for_it_30) - 1)];
                        double plude_var_23_0_in_0 = plude_var_23[((_for_it_30 + (sym_klon * (_for_it_23 - 1))) - 1)];
                        double ydecldp_var_49_0_in_rlmin = v_ydecldp_var_49_rlmin[0];
                        double _if_cond_17_out;

                        ///////////////////
                        // Tasklet code (T_l0_c0)
                        _if_cond_17_out = ((ldcum_var_20_0_in_0 && (plude_var_23_0_in_0 > ydecldp_var_49_0_in_rlmin)) && (plu_var_22_0_in_0 > 1e-14));
                        ///////////////////

                        _if_cond_17 = _if_cond_17_out;
                    }
                }
                if ((_if_cond_17 == 1)) {
                    zalfaw = zfoealfa[((_for_it_30 + (sym_klon * (_for_it_23 - 1))) - 1)];
                    {
                        {
                            double plu_var_22_0_in_0 = plu_var_22[(((_for_it_23 * sym_klon) + _for_it_30) - 1)];
                            double plude_var_23_0_in_0 = plude_var_23[((_for_it_30 + (sym_klon * (_for_it_23 - 1))) - 1)];
                            double zsolac_0_in_0 = zsolac[(_for_it_30 - 1)];
                            double zsolac_out_0;

                            ///////////////////
                            // Tasklet code (T_l660_c660)
                            zsolac_out_0 = (zsolac_0_in_0 + (plude_var_23_0_in_0 / plu_var_22_0_in_0));
                            ///////////////////

                            zsolac[(_for_it_30 - 1)] = zsolac_out_0;
                        }
                        {
                            double plude_var_23_0_in_0 = plude_var_23[((_for_it_30 + (sym_klon * (_for_it_23 - 1))) - 1)];
                            double zconvsrce_out_0;

                            ///////////////////
                            // Tasklet code (T_l662_c662)
                            zconvsrce_out_0 = (zalfaw * plude_var_23_0_in_0);
                            ///////////////////

                            zconvsrce[(_for_it_30 - 1)] = zconvsrce_out_0;
                        }
                        {
                            double plude_var_23_0_in_0 = plude_var_23[((_for_it_30 + (sym_klon * (_for_it_23 - 1))) - 1)];
                            double zconvsrce_out_0;

                            ///////////////////
                            // Tasklet code (T_l663_c663)
                            zconvsrce_out_0 = ((1.0 - zalfaw) * plude_var_23_0_in_0);
                            ///////////////////

                            zconvsrce[((_for_it_30 + sym_klon) - 1)] = zconvsrce_out_0;
                        }
                        {
                            double zconvsrce_0_in_0 = zconvsrce[(_for_it_30 - 1)];
                            double zsolqa_0_in_0 = zsolqa[(_for_it_30 - 1)];
                            double zsolqa_out_0;

                            ///////////////////
                            // Tasklet code (T_l664_c664)
                            zsolqa_out_0 = (zsolqa_0_in_0 + zconvsrce_0_in_0);
                            ///////////////////

                            zsolqa[(_for_it_30 - 1)] = zsolqa_out_0;
                        }
                        {
                            double zconvsrce_0_in_0 = zconvsrce[((_for_it_30 + sym_klon) - 1)];
                            double zsolqa_0_in_0 = zsolqa[((_for_it_30 + (6 * sym_klon)) - 1)];
                            double zsolqa_out_0;

                            ///////////////////
                            // Tasklet code (T_l665_c665)
                            zsolqa_out_0 = (zsolqa_0_in_0 + zconvsrce_0_in_0);
                            ///////////////////

                            zsolqa[((_for_it_30 + (6 * sym_klon)) - 1)] = zsolqa_out_0;
                        }
                    }
                } else {
                    {
                        {
                            double plude_var_23_out_0;

                            ///////////////////
                            // Tasklet code (T_l667_c667)
                            plude_var_23_out_0 = 0.0;
                            ///////////////////

                            plude_var_23[((_for_it_30 + (sym_klon * (_for_it_23 - 1))) - 1)] = plude_var_23_out_0;
                        }
                    }
                }
                _if_cond_18 = ldcum_var_20[(_for_it_30 - 1)];
                if ((_if_cond_18 == 1)) {
                    {
                        {
                            double psnde_var_24_0_in_0 = psnde_var_24[((_for_it_30 + (sym_klon * (_for_it_23 - 1))) - 1)];
                            double zdtgdp_0_in_0 = zdtgdp[(_for_it_30 - 1)];
                            double zsolqa_0_in_0 = zsolqa[((_for_it_30 + (18 * sym_klon)) - 1)];
                            double zsolqa_out_0;

                            ///////////////////
                            // Tasklet code (T_l669_c669)
                            zsolqa_out_0 = (zsolqa_0_in_0 + (psnde_var_24_0_in_0 * zdtgdp_0_in_0));
                            ///////////////////

                            zsolqa[((_for_it_30 + (18 * sym_klon)) - 1)] = zsolqa_out_0;
                        }
                    }
                }
            }
        }
        {
            {
                int ydecldp_var_49_0_in_ncldtop = v_ydecldp_var_49_ncldtop[0];
                int _if_cond_19_out;

                ///////////////////
                // Tasklet code (T_l0_c0)
                _if_cond_19_out = (_for_it_23 > ydecldp_var_49_0_in_ncldtop);
                ///////////////////

                _if_cond_19 = _if_cond_19_out;
            }
        }
        if ((_if_cond_19 == 1)) {
            for (_for_it_31 = 1; (_for_it_31 <= icend); _for_it_31 = (_for_it_31 + 1)) {
                {
                    double tmp_call_22;
                    double tmp_arg_11;

                    {
                        double pmfd_var_26_0_in_0 = pmfd_var_26[((_for_it_31 + (sym_klon * (_for_it_23 - 1))) - 1)];
                        double pmfu_var_25_0_in_0 = pmfu_var_25[((_for_it_31 + (sym_klon * (_for_it_23 - 1))) - 1)];
                        double zdtgdp_0_in_0 = zdtgdp[(_for_it_31 - 1)];
                        double tmp_arg_11_out;

                        ///////////////////
                        // Tasklet code (T_l674_c674)
                        tmp_arg_11_out = ((pmfu_var_25_0_in_0 + pmfd_var_26_0_in_0) * zdtgdp_0_in_0);
                        ///////////////////

                        tmp_arg_11 = tmp_arg_11_out;
                    }
                    {
                        double tmp_arg_11_0_in = tmp_arg_11;
                        double tmp_call_22_out;

                        ///////////////////
                        // Tasklet code (T_l674_c674)
                        tmp_call_22_out = max(0.0, tmp_arg_11_0_in);
                        ///////////////////

                        tmp_call_22 = tmp_call_22_out;
                    }
                    {
                        double tmp_call_22_0_in = tmp_call_22;
                        double zmf_out_0;

                        ///////////////////
                        // Tasklet code (T_l674_c674)
                        zmf_out_0 = tmp_call_22_0_in;
                        ///////////////////

                        zmf[(_for_it_31 - 1)] = zmf_out_0;
                    }
                    {
                        double zanewm1_0_in_0 = zanewm1[(_for_it_31 - 1)];
                        double zmf_0_in_0 = zmf[(_for_it_31 - 1)];
                        double zacust_out_0;

                        ///////////////////
                        // Tasklet code (T_l675_c675)
                        zacust_out_0 = (zmf_0_in_0 * zanewm1_0_in_0);
                        ///////////////////

                        zacust[(_for_it_31 - 1)] = zacust_out_0;
                    }
                }
            }
            for (_for_it_32 = 1; (_for_it_32 <= 5); _for_it_32 = (_for_it_32 + 1)) {
                _if_cond_20 = ((1 - llfall[(_for_it_32 - 1)]) && (iphase[(_for_it_32 - 1)] > 0));
                if ((_if_cond_20 == 1)) {
                    for (_for_it_33 = 1; (_for_it_33 <= icend); _for_it_33 = (_for_it_33 + 1)) {
                        {
                            {
                                double zmf_0_in_0 = zmf[(_for_it_33 - 1)];
                                double zqxnm1_0_in_0 = zqxnm1[((_for_it_33 + (sym_klon * (_for_it_32 - 1))) - 1)];
                                double zlcust_out_0;

                                ///////////////////
                                // Tasklet code (T_l680_c680)
                                zlcust_out_0 = (zmf_0_in_0 * zqxnm1_0_in_0);
                                ///////////////////

                                zlcust[((_for_it_33 + (sym_klon * (_for_it_32 - 1))) - 1)] = zlcust_out_0;
                            }
                            {
                                double zconvsrce_0_in_0 = zconvsrce[((_for_it_33 + (sym_klon * (_for_it_32 - 1))) - 1)];
                                double zlcust_0_in_0 = zlcust[((_for_it_33 + (sym_klon * (_for_it_32 - 1))) - 1)];
                                double zconvsrce_out_0;

                                ///////////////////
                                // Tasklet code (T_l681_c681)
                                zconvsrce_out_0 = (zconvsrce_0_in_0 + zlcust_0_in_0);
                                ///////////////////

                                zconvsrce[((_for_it_33 + (sym_klon * (_for_it_32 - 1))) - 1)] = zconvsrce_out_0;
                            }
                        }
                    }
                }
            }
            for (_for_it_34 = 1; (_for_it_34 <= icend); _for_it_34 = (_for_it_34 + 1)) {
                {
                    {
                        double paph_var_18_0_in_0 = paph_var_18[((_for_it_34 + (sym_klon * (_for_it_23 - 1))) - 1)];
                        double zrdcp_0_in = zrdcp;
                        double ztp1_0_in_0 = ztp1[((_for_it_34 + (sym_klon * (_for_it_23 - 2))) - 1)];
                        double ztp1_1_in_0 = ztp1[((_for_it_34 + (sym_klon * (_for_it_23 - 1))) - 1)];
                        double zdtdp_out;

                        ///////////////////
                        // Tasklet code (T_l686_c686)
                        zdtdp_out = (((zrdcp_0_in * 0.5) * (ztp1_0_in_0 + ztp1_1_in_0)) / paph_var_18_0_in_0);
                        ///////////////////

                        zdtdp = zdtdp_out;
                    }
                    {
                        double pap_var_17_0_in_0 = pap_var_17[((_for_it_34 + (sym_klon * (_for_it_23 - 1))) - 1)];
                        double pap_var_17_1_in_0 = pap_var_17[((_for_it_34 + (sym_klon * (_for_it_23 - 2))) - 1)];
                        double zdtdp_0_in = zdtdp;
                        double zdtforc_out;

                        ///////////////////
                        // Tasklet code (T_l687_c687)
                        zdtforc_out = (zdtdp_0_in * (pap_var_17_0_in_0 - pap_var_17_1_in_0));
                        ///////////////////

                        zdtforc = zdtforc_out;
                    }
                    {
                        double zanewm1_0_in_0 = zanewm1[(_for_it_34 - 1)];
                        double zdqsmixdt_0_in_0 = zdqsmixdt[(_for_it_34 - 1)];
                        double zdtforc_0_in = zdtforc;
                        double zdqs_out_0;

                        ///////////////////
                        // Tasklet code (T_l688_c688)
                        zdqs_out_0 = ((zanewm1_0_in_0 * zdtforc_0_in) * zdqsmixdt_0_in_0);
                        ///////////////////

                        zdqs[(_for_it_34 - 1)] = zdqs_out_0;
                    }
                }
            }
            for (_for_it_35 = 1; (_for_it_35 <= 5); _for_it_35 = (_for_it_35 + 1)) {
                _if_cond_21 = ((1 - llfall[(_for_it_35 - 1)]) && (iphase[(_for_it_35 - 1)] > 0));
                if ((_if_cond_21 == 1)) {
                    for (_for_it_36 = 1; (_for_it_36 <= icend); _for_it_36 = (_for_it_36 + 1)) {
                        {
                            double zlfinal;
                            double tmp_arg_12;
                            double tmp_arg_13;

                            {
                                double zdqs_0_in_0 = zdqs[(_for_it_36 - 1)];
                                double zlcust_0_in_0 = zlcust[((_for_it_36 + (sym_klon * (_for_it_35 - 1))) - 1)];
                                double tmp_arg_12_out;

                                ///////////////////
                                // Tasklet code (T_l693_c693)
                                tmp_arg_12_out = (zlcust_0_in_0 - zdqs_0_in_0);
                                ///////////////////

                                tmp_arg_12 = tmp_arg_12_out;
                            }
                            {
                                double tmp_arg_12_0_in = tmp_arg_12;
                                double zlfinal_out;

                                ///////////////////
                                // Tasklet code (T_l693_c693)
                                zlfinal_out = max(0.0, tmp_arg_12_0_in);
                                ///////////////////

                                zlfinal = zlfinal_out;
                            }
                            {
                                double zlcust_0_in_0 = zlcust[((_for_it_36 + (sym_klon * (_for_it_35 - 1))) - 1)];
                                double zlfinal_0_in = zlfinal;
                                double tmp_arg_13_out;

                                ///////////////////
                                // Tasklet code (T_l694_c694)
                                tmp_arg_13_out = (zlcust_0_in_0 - zlfinal_0_in);
                                ///////////////////

                                tmp_arg_13 = tmp_arg_13_out;
                            }
                            {
                                double tmp_arg_13_0_in = tmp_arg_13;
                                double zevaplimmix_0_in_0 = zevaplimmix[(_for_it_36 - 1)];
                                double zevap_out;

                                ///////////////////
                                // Tasklet code (T_l694_c694)
                                zevap_out = min(tmp_arg_13_0_in, zevaplimmix_0_in_0);
                                ///////////////////

                                zevap = zevap_out;
                            }
                            {
                                double zevap_0_in = zevap;
                                double zlcust_0_in_0 = zlcust[((_for_it_36 + (sym_klon * (_for_it_35 - 1))) - 1)];
                                double zlfinal_out;

                                ///////////////////
                                // Tasklet code (T_l695_c695)
                                zlfinal_out = (zlcust_0_in_0 - zevap_0_in);
                                ///////////////////

                                zlfinal = zlfinal_out;
                            }
                            {
                                double zlfinal_0_in = zlfinal;
                                double zlfinalsum_0_in_0 = zlfinalsum[(_for_it_36 - 1)];
                                double zlfinalsum_out_0;

                                ///////////////////
                                // Tasklet code (T_l696_c696)
                                zlfinalsum_out_0 = (zlfinalsum_0_in_0 + zlfinal_0_in);
                                ///////////////////

                                zlfinalsum[(_for_it_36 - 1)] = zlfinalsum_out_0;
                            }
                            {
                                double zlcust_0_in_0 = zlcust[((_for_it_36 + (sym_klon * (_for_it_35 - 1))) - 1)];
                                double zsolqa_0_in_0 = zsolqa[((_for_it_36 + ((6 * sym_klon) * (_for_it_35 - 1))) - 1)];
                                double zsolqa_out_0;

                                ///////////////////
                                // Tasklet code (T_l697_c697)
                                zsolqa_out_0 = (zsolqa_0_in_0 + zlcust_0_in_0);
                                ///////////////////

                                zsolqa[((_for_it_36 + ((6 * sym_klon) * (_for_it_35 - 1))) - 1)] = zsolqa_out_0;
                            }
                            {
                                double zevap_0_in = zevap;
                                double zsolqa_0_in_0 = zsolqa[(((_for_it_36 + ((5 * sym_klon) * (_for_it_35 - 1))) + (4 * sym_klon)) - 1)];
                                double zsolqa_out_0;

                                ///////////////////
                                // Tasklet code (T_l698_c698)
                                zsolqa_out_0 = (zsolqa_0_in_0 + zevap_0_in);
                                ///////////////////

                                zsolqa[(((_for_it_36 + ((5 * sym_klon) * (_for_it_35 - 1))) + (4 * sym_klon)) - 1)] = zsolqa_out_0;
                            }
                            {
                                double zevap_0_in = zevap;
                                double zsolqa_0_in_0 = zsolqa[(((_for_it_36 + (sym_klon * (_for_it_35 - 1))) + (20 * sym_klon)) - 1)];
                                double zsolqa_out_0;

                                ///////////////////
                                // Tasklet code (T_l699_c699)
                                zsolqa_out_0 = (zsolqa_0_in_0 - zevap_0_in);
                                ///////////////////

                                zsolqa[(((_for_it_36 + (sym_klon * (_for_it_35 - 1))) + (20 * sym_klon)) - 1)] = zsolqa_out_0;
                            }
                        }
                    }
                }
            }
            for (_for_it_37 = 1; (_for_it_37 <= icend); _for_it_37 = (_for_it_37 + 1)) {
                _if_cond_22 = (zlfinalsum[(_for_it_37 - 1)] < 1e-14);
                if ((_if_cond_22 == 1)) {
                    {
                        {
                            double zacust_out_0;

                            ///////////////////
                            // Tasklet code (T_l704_c704)
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
                        // Tasklet code (T_l705_c705)
                        zsolac_out_0 = (zsolac_0_in_0 + zacust_0_in_0);
                        ///////////////////

                        zsolac[(_for_it_37 - 1)] = zsolac_out_0;
                    }
                }
            }
        }
        for (_for_it_38 = 1; (_for_it_38 <= icend); _for_it_38 = (_for_it_38 + 1)) {
            _if_cond_23 = (_for_it_23 < klev[0]);
            if ((_if_cond_23 == 1)) {
                {
                    double tmp_arg_14;

                    {
                        double pmfd_var_26_0_in_0 = pmfd_var_26[(((_for_it_23 * sym_klon) + _for_it_38) - 1)];
                        double pmfu_var_25_0_in_0 = pmfu_var_25[(((_for_it_23 * sym_klon) + _for_it_38) - 1)];
                        double zdtgdp_0_in_0 = zdtgdp[(_for_it_38 - 1)];
                        double tmp_arg_14_out;

                        ///////////////////
                        // Tasklet code (T_l710_c710)
                        tmp_arg_14_out = ((pmfu_var_25_0_in_0 + pmfd_var_26_0_in_0) * zdtgdp_0_in_0);
                        ///////////////////

                        tmp_arg_14 = tmp_arg_14_out;
                    }
                    {
                        double tmp_arg_14_0_in = tmp_arg_14;
                        double zmfdn_out;

                        ///////////////////
                        // Tasklet code (T_l710_c710)
                        zmfdn_out = max(0.0, tmp_arg_14_0_in);
                        ///////////////////

                        zmfdn = zmfdn_out;
                    }
                    {
                        double zmfdn_0_in = zmfdn;
                        double zconvsink_out_0;

                        ///////////////////
                        // Tasklet code (T_l714_c714)
                        zconvsink_out_0 = zmfdn_0_in;
                        ///////////////////

                        zconvsink[(_for_it_38 - 1)] = zconvsink_out_0;
                    }
                    {
                        double zmfdn_0_in = zmfdn;
                        double zconvsink_out_0;

                        ///////////////////
                        // Tasklet code (T_l715_c715)
                        zconvsink_out_0 = zmfdn_0_in;
                        ///////////////////

                        zconvsink[((_for_it_38 + sym_klon) - 1)] = zconvsink_out_0;
                    }
                    {
                        double zmfdn_0_in = zmfdn;
                        double zsolab_0_in_0 = zsolab[(_for_it_38 - 1)];
                        double zsolab_out_0;

                        ///////////////////
                        // Tasklet code (T_l711_c711)
                        zsolab_out_0 = (zsolab_0_in_0 + zmfdn_0_in);
                        ///////////////////

                        zsolab[(_for_it_38 - 1)] = zsolab_out_0;
                    }
                    {
                        double zmfdn_0_in = zmfdn;
                        double zsolqb_0_in_0 = zsolqb[(_for_it_38 - 1)];
                        double zsolqb_out_0;

                        ///////////////////
                        // Tasklet code (T_l712_c712)
                        zsolqb_out_0 = (zsolqb_0_in_0 + zmfdn_0_in);
                        ///////////////////

                        zsolqb[(_for_it_38 - 1)] = zsolqb_out_0;
                    }
                    {
                        double zmfdn_0_in = zmfdn;
                        double zsolqb_0_in_0 = zsolqb[((_for_it_38 + (6 * sym_klon)) - 1)];
                        double zsolqb_out_0;

                        ///////////////////
                        // Tasklet code (T_l713_c713)
                        zsolqb_out_0 = (zsolqb_0_in_0 + zmfdn_0_in);
                        ///////////////////

                        zsolqb[((_for_it_38 + (6 * sym_klon)) - 1)] = zsolqb_out_0;
                    }
                }
            }
        }
        for (_for_it_39 = 1; (_for_it_39 <= icend); _for_it_39 = (_for_it_39 + 1)) {
            _if_cond_24 = ((ktype_var_21[(_for_it_39 - 1)] > 0) && (plude_var_23[((_for_it_39 + (sym_klon * (_for_it_23 - 1))) - 1)] > 1e-14));
            {
                double* v_ydecldp_var_49_rcldiff;
                v_ydecldp_var_49_rcldiff = (double*)(&(ydecldp_var_49->rcldiff));

                {
                    double ptsphy_var_5_0_in = ptsphy_var_5[0];
                    double ydecldp_var_49_0_in_rcldiff = v_ydecldp_var_49_rcldiff[0];
                    double zldifdt_out_0;

                    ///////////////////
                    // Tasklet code (T_l719_c719)
                    zldifdt_out_0 = (ydecldp_var_49_0_in_rcldiff * ptsphy_var_5_0_in);
                    ///////////////////

                    zldifdt[(_for_it_39 - 1)] = zldifdt_out_0;
                }
            }
            if ((_if_cond_24 == 1)) {
                {
                    double* v_ydecldp_var_49_rcldiff_convi;
                    v_ydecldp_var_49_rcldiff_convi = (double*)(&(ydecldp_var_49->rcldiff_convi));

                    {
                        double ydecldp_var_49_0_in_rcldiff_convi = v_ydecldp_var_49_rcldiff_convi[0];
                        double zldifdt_0_in_0 = zldifdt[(_for_it_39 - 1)];
                        double zldifdt_out_0;

                        ///////////////////
                        // Tasklet code (T_l720_c720)
                        zldifdt_out_0 = (ydecldp_var_49_0_in_rcldiff_convi * zldifdt_0_in_0);
                        ///////////////////

                        zldifdt[(_for_it_39 - 1)] = zldifdt_out_0;
                    }
                }
            }
        }
        for (_for_it_40 = 1; (_for_it_40 <= icend); _for_it_40 = (_for_it_40 + 1)) {
            _if_cond_25 = (zli[((_for_it_40 + (sym_klon * (_for_it_23 - 1))) - 1)] > 1e-14);
            if ((_if_cond_25 == 1)) {
                {
                    double zleros;
                    double zaeros;
                    double ze;
                    double tmp_call_23;
                    double tmp_arg_15;

                    {
                        double zqsmix_0_in_0 = zqsmix[((_for_it_40 + (sym_klon * (_for_it_23 - 1))) - 1)];
                        double zqx_0_in_0 = zqx[(((_for_it_40 + ((4 * sym_klev) * sym_klon)) + (sym_klon * (_for_it_23 - 1))) - 1)];
                        double tmp_arg_15_out;

                        ///////////////////
                        // Tasklet code (T_l724_c724)
                        tmp_arg_15_out = (zqsmix_0_in_0 - zqx_0_in_0);
                        ///////////////////

                        tmp_arg_15 = tmp_arg_15_out;
                    }
                    {
                        double tmp_arg_15_0_in = tmp_arg_15;
                        double tmp_call_23_out;

                        ///////////////////
                        // Tasklet code (T_l724_c724)
                        tmp_call_23_out = max(tmp_arg_15_0_in, 0.0);
                        ///////////////////

                        tmp_call_23 = tmp_call_23_out;
                    }
                    {
                        double tmp_call_23_0_in = tmp_call_23;
                        double zldifdt_0_in_0 = zldifdt[(_for_it_40 - 1)];
                        double ze_out;

                        ///////////////////
                        // Tasklet code (T_l724_c724)
                        ze_out = (zldifdt_0_in_0 * tmp_call_23_0_in);
                        ///////////////////

                        ze = ze_out;
                    }
                    {
                        double za_0_in_0 = za[((_for_it_40 + (sym_klon * (_for_it_23 - 1))) - 1)];
                        double ze_0_in = ze;
                        double zleros_out;

                        ///////////////////
                        // Tasklet code (T_l725_c725)
                        zleros_out = (za_0_in_0 * ze_0_in);
                        ///////////////////

                        zleros = zleros_out;
                    }
                    {
                        double zevaplimmix_0_in_0 = zevaplimmix[(_for_it_40 - 1)];
                        double zleros_0_in = zleros;
                        double zleros_out;

                        ///////////////////
                        // Tasklet code (T_l726_c726)
                        zleros_out = min(zleros_0_in, zevaplimmix_0_in_0);
                        ///////////////////

                        zleros = zleros_out;
                    }
                    {
                        double zleros_0_in = zleros;
                        double zli_0_in_0 = zli[((_for_it_40 + (sym_klon * (_for_it_23 - 1))) - 1)];
                        double zleros_out;

                        ///////////////////
                        // Tasklet code (T_l727_c727)
                        zleros_out = min(zleros_0_in, zli_0_in_0);
                        ///////////////////

                        zleros = zleros_out;
                    }
                    {
                        double zleros_0_in = zleros;
                        double zlicld_0_in_0 = zlicld[(_for_it_40 - 1)];
                        double zaeros_out;

                        ///////////////////
                        // Tasklet code (T_l728_c728)
                        zaeros_out = (zleros_0_in / zlicld_0_in_0);
                        ///////////////////

                        zaeros = zaeros_out;
                    }
                    {
                        double zaeros_0_in = zaeros;
                        double zsolac_0_in_0 = zsolac[(_for_it_40 - 1)];
                        double zsolac_out_0;

                        ///////////////////
                        // Tasklet code (T_l729_c729)
                        zsolac_out_0 = (zsolac_0_in_0 - zaeros_0_in);
                        ///////////////////

                        zsolac[(_for_it_40 - 1)] = zsolac_out_0;
                    }
                    {
                        double zleros_0_in = zleros;
                        double zliqfrac_0_in_0 = zliqfrac[((_for_it_40 + (sym_klon * (_for_it_23 - 1))) - 1)];
                        double zsolqa_0_in_0 = zsolqa[((_for_it_40 + (4 * sym_klon)) - 1)];
                        double zsolqa_out_0;

                        ///////////////////
                        // Tasklet code (T_l730_c730)
                        zsolqa_out_0 = (zsolqa_0_in_0 + (zliqfrac_0_in_0 * zleros_0_in));
                        ///////////////////

                        zsolqa[((_for_it_40 + (4 * sym_klon)) - 1)] = zsolqa_out_0;
                    }
                    {
                        double zleros_0_in = zleros;
                        double zliqfrac_0_in_0 = zliqfrac[((_for_it_40 + (sym_klon * (_for_it_23 - 1))) - 1)];
                        double zsolqa_0_in_0 = zsolqa[((_for_it_40 + (20 * sym_klon)) - 1)];
                        double zsolqa_out_0;

                        ///////////////////
                        // Tasklet code (T_l731_c731)
                        zsolqa_out_0 = (zsolqa_0_in_0 - (zliqfrac_0_in_0 * zleros_0_in));
                        ///////////////////

                        zsolqa[((_for_it_40 + (20 * sym_klon)) - 1)] = zsolqa_out_0;
                    }
                    {
                        double zicefrac_0_in_0 = zicefrac[((_for_it_40 + (sym_klon * (_for_it_23 - 1))) - 1)];
                        double zleros_0_in = zleros;
                        double zsolqa_0_in_0 = zsolqa[((_for_it_40 + (9 * sym_klon)) - 1)];
                        double zsolqa_out_0;

                        ///////////////////
                        // Tasklet code (T_l732_c732)
                        zsolqa_out_0 = (zsolqa_0_in_0 + (zicefrac_0_in_0 * zleros_0_in));
                        ///////////////////

                        zsolqa[((_for_it_40 + (9 * sym_klon)) - 1)] = zsolqa_out_0;
                    }
                    {
                        double zicefrac_0_in_0 = zicefrac[((_for_it_40 + (sym_klon * (_for_it_23 - 1))) - 1)];
                        double zleros_0_in = zleros;
                        double zsolqa_0_in_0 = zsolqa[((_for_it_40 + (21 * sym_klon)) - 1)];
                        double zsolqa_out_0;

                        ///////////////////
                        // Tasklet code (T_l733_c733)
                        zsolqa_out_0 = (zsolqa_0_in_0 - (zicefrac_0_in_0 * zleros_0_in));
                        ///////////////////

                        zsolqa[((_for_it_40 + (21 * sym_klon)) - 1)] = zsolqa_out_0;
                    }
                }
            }
        }
        for (_for_it_41 = 1; (_for_it_41 <= icend); _for_it_41 = (_for_it_41 + 1)) {
            {
                {
                    double pap_var_17_0_in_0 = pap_var_17[((_for_it_41 + (sym_klon * (_for_it_23 - 1))) - 1)];
                    double zrdcp_0_in = zrdcp;
                    double ztp1_0_in_0 = ztp1[((_for_it_41 + (sym_klon * (_for_it_23 - 1))) - 1)];
                    double zdtdp_out;

                    ///////////////////
                    // Tasklet code (T_l737_c737)
                    zdtdp_out = ((zrdcp_0_in * ztp1_0_in_0) / pap_var_17_0_in_0);
                    ///////////////////

                    zdtdp = zdtdp_out;
                }
                {
                    double zdp_0_in_0 = zdp[(_for_it_41 - 1)];
                    double zqtmst_0_in = zqtmst;
                    double zdpmxdt_out;

                    ///////////////////
                    // Tasklet code (T_l738_c738)
                    zdpmxdt_out = (zdp_0_in_0 * zqtmst_0_in);
                    ///////////////////

                    zdpmxdt = zdpmxdt_out;
                }
                {
                    double zmfdn_out;

                    ///////////////////
                    // Tasklet code (T_l739_c739)
                    zmfdn_out = 0.0;
                    ///////////////////

                    zmfdn = zmfdn_out;
                }
            }
            _if_cond_26 = (_for_it_23 < klev[0]);
            if ((_if_cond_26 == 1)) {
                {
                    {
                        double pmfd_var_26_0_in_0 = pmfd_var_26[(((_for_it_23 * sym_klon) + _for_it_41) - 1)];
                        double pmfu_var_25_0_in_0 = pmfu_var_25[(((_for_it_23 * sym_klon) + _for_it_41) - 1)];
                        double zmfdn_out;

                        ///////////////////
                        // Tasklet code (T_l740_c740)
                        zmfdn_out = (pmfu_var_25_0_in_0 + pmfd_var_26_0_in_0);
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
                double* v_ydthf_var_48_ralfdcp;
                v_ydthf_var_48_ralfdcp = (double*)(&(ydthf_var_48->ralfdcp));

                {
                    double pmfd_var_26_0_in_0 = pmfd_var_26[((_for_it_41 + (sym_klon * (_for_it_23 - 1))) - 1)];
                    double pmfu_var_25_0_in_0 = pmfu_var_25[((_for_it_41 + (sym_klon * (_for_it_23 - 1))) - 1)];
                    double pvervel_var_16_0_in_0 = pvervel_var_16[((_for_it_41 + (sym_klon * (_for_it_23 - 1))) - 1)];
                    double ydcst_var_47_0_in_rg = v_ydcst_var_47_rg[0];
                    double zmfdn_0_in = zmfdn;
                    double zwtot_out;

                    ///////////////////
                    // Tasklet code (T_l741_c741)
                    zwtot_out = (pvervel_var_16_0_in_0 + ((0.5 * ydcst_var_47_0_in_rg) * ((pmfu_var_25_0_in_0 + pmfd_var_26_0_in_0) + zmfdn_0_in)));
                    ///////////////////

                    zwtot = zwtot_out;
                }
                {
                    double zdpmxdt_0_in = zdpmxdt;
                    double tmp_arg_16_out;

                    ///////////////////
                    // Tasklet code (T_l742_c742)
                    tmp_arg_16_out = (-zdpmxdt_0_in);
                    ///////////////////

                    tmp_arg_16 = tmp_arg_16_out;
                }
                {
                    double tmp_arg_16_0_in = tmp_arg_16;
                    double zwtot_0_in = zwtot;
                    double tmp_call_24_out;

                    ///////////////////
                    // Tasklet code (T_l742_c742)
                    tmp_call_24_out = max(tmp_arg_16_0_in, zwtot_0_in);
                    ///////////////////

                    tmp_call_24 = tmp_call_24_out;
                }
                {
                    double tmp_call_24_0_in = tmp_call_24;
                    double zdpmxdt_0_in = zdpmxdt;
                    double zwtot_out;

                    ///////////////////
                    // Tasklet code (T_l742_c742)
                    zwtot_out = min(zdpmxdt_0_in, tmp_call_24_0_in);
                    ///////////////////

                    zwtot = zwtot_out;
                }
                {
                    double phrlw_var_15_0_in_0 = phrlw_var_15[((_for_it_41 + (sym_klon * (_for_it_23 - 1))) - 1)];
                    double phrsw_var_14_0_in_0 = phrsw_var_14[((_for_it_41 + (sym_klon * (_for_it_23 - 1))) - 1)];
                    double zzzdt_out;

                    ///////////////////
                    // Tasklet code (T_l743_c743)
                    zzzdt_out = (phrsw_var_14_0_in_0 + phrlw_var_15_0_in_0);
                    ///////////////////

                    zzzdt = zzzdt_out;
                }
                {
                    double zdpmxdt_0_in = zdpmxdt;
                    double zdtdp_0_in = zdtdp;
                    double tmp_arg_17_out;

                    ///////////////////
                    // Tasklet code (T_l744_c744)
                    tmp_arg_17_out = (-(zdpmxdt_0_in * zdtdp_0_in));
                    ///////////////////

                    tmp_arg_17 = tmp_arg_17_out;
                }
                {
                    double tmp_arg_17_0_in = tmp_arg_17;
                    double zzzdt_0_in = zzzdt;
                    double tmp_call_27_out;

                    ///////////////////
                    // Tasklet code (T_l744_c744)
                    tmp_call_27_out = max(tmp_arg_17_0_in, zzzdt_0_in);
                    ///////////////////

                    tmp_call_27 = tmp_call_27_out;
                }
                {
                    double zdpmxdt_0_in = zdpmxdt;
                    double zdtdp_0_in = zdtdp;
                    double tmp_arg_18_out;

                    ///////////////////
                    // Tasklet code (T_l744_c744)
                    tmp_arg_18_out = (zdpmxdt_0_in * zdtdp_0_in);
                    ///////////////////

                    tmp_arg_18 = tmp_arg_18_out;
                }
                {
                    double tmp_arg_18_0_in = tmp_arg_18;
                    double tmp_call_27_0_in = tmp_call_27;
                    double tmp_call_25_out;

                    ///////////////////
                    // Tasklet code (T_l744_c744)
                    tmp_call_25_out = min(tmp_arg_18_0_in, tmp_call_27_0_in);
                    ///////////////////

                    tmp_call_25 = tmp_call_25_out;
                }
                {
                    double ptsphy_var_5_0_in = ptsphy_var_5[0];
                    double tmp_call_25_0_in = tmp_call_25;
                    double ydthf_var_48_0_in_ralfdcp = v_ydthf_var_48_ralfdcp[0];
                    double zldefr_0_in_0 = zldefr[(_for_it_41 - 1)];
                    double zdtdiab_out;

                    ///////////////////
                    // Tasklet code (T_l744_c744)
                    zdtdiab_out = ((tmp_call_25_0_in * ptsphy_var_5_0_in) + (ydthf_var_48_0_in_ralfdcp * zldefr_0_in_0));
                    ///////////////////

                    zdtdiab = zdtdiab_out;
                }
                {
                    double ptsphy_var_5_0_in = ptsphy_var_5[0];
                    double zdtdiab_0_in = zdtdiab;
                    double zdtdp_0_in = zdtdp;
                    double zwtot_0_in = zwtot;
                    double zdtforc_out;

                    ///////////////////
                    // Tasklet code (T_l745_c745)
                    zdtforc_out = (((zdtdp_0_in * zwtot_0_in) * ptsphy_var_5_0_in) + zdtdiab_0_in);
                    ///////////////////

                    zdtforc = zdtforc_out;
                }
                {
                    double zqsmix_0_in_0 = zqsmix[((_for_it_41 + (sym_klon * (_for_it_23 - 1))) - 1)];
                    double zqold_out_0;

                    ///////////////////
                    // Tasklet code (T_l746_c746)
                    zqold_out_0 = zqsmix_0_in_0;
                    ///////////////////

                    zqold[(_for_it_41 - 1)] = zqold_out_0;
                }
                {
                    double ztp1_0_in_0 = ztp1[((_for_it_41 + (sym_klon * (_for_it_23 - 1))) - 1)];
                    double ztold_out_0;

                    ///////////////////
                    // Tasklet code (T_l747_c747)
                    ztold_out_0 = ztp1_0_in_0;
                    ///////////////////

                    ztold[(_for_it_41 - 1)] = ztold_out_0;
                }
            }
            {
                double tmp_call_26;

                {
                    double zdtforc_0_in = zdtforc;
                    double ztp1_0_in_0 = ztp1[((_for_it_41 + (sym_klon * (_for_it_23 - 1))) - 1)];
                    double ztp1_out_0;

                    ///////////////////
                    // Tasklet code (T_l748_c748)
                    ztp1_out_0 = (ztp1_0_in_0 + zdtforc_0_in);
                    ///////////////////

                    ztp1[((_for_it_41 + (sym_klon * (_for_it_23 - 1))) - 1)] = ztp1_out_0;
                }
                {
                    double ztp1_0_in_0 = ztp1[((_for_it_41 + (sym_klon * (_for_it_23 - 1))) - 1)];
                    double tmp_call_26_out;

                    ///////////////////
                    // Tasklet code (T_l749_c749)
                    tmp_call_26_out = max(ztp1_0_in_0, 160.0);
                    ///////////////////

                    tmp_call_26 = tmp_call_26_out;
                }
                {
                    double tmp_call_26_0_in = tmp_call_26;
                    double ztp1_out_0;

                    ///////////////////
                    // Tasklet code (T_l749_c749)
                    ztp1_out_0 = tmp_call_26_0_in;
                    ///////////////////

                    ztp1[((_for_it_41 + (sym_klon * (_for_it_23 - 1))) - 1)] = ztp1_out_0;
                }
            }
        }
        for (_for_it_42 = 1; (_for_it_42 <= icend); _for_it_42 = (_for_it_42 + 1)) {
            {
                double tmp_arg_67_1;
                double tmp_call_106_1_6;

                {
                    double pap_var_17_0_in_0 = pap_var_17[((_for_it_42 + (sym_klon * (_for_it_23 - 1))) - 1)];
                    double zqp_out;

                    ///////////////////
                    // Tasklet code (T_l753_c753)
                    zqp_out = (1.0 / pap_var_17_0_in_0);
                    ///////////////////

                    zqp = zqp_out;
                }
                {
                    double ztp1_0_in_0 = ztp1[((_for_it_42 + (sym_klon * (_for_it_23 - 1))) - 1)];
                    double oka_out;

                    ///////////////////
                    // Tasklet code (T_l754_c754)
                    oka_out = ztp1_0_in_0;
                    ///////////////////

                    oka = oka_out;
                }
                {
                    double ptare_var_52_0_in = oka;
                    double ydthf_var_53_0_in_rtwat = v_ydthf_var_53_rtwat[0];
                    double tmp_call_106_out;

                    ///////////////////
                    // Tasklet code (T_l1362_c1362)
                    tmp_call_106_out = min(ydthf_var_53_0_in_rtwat, ptare_var_52_0_in);
                    ///////////////////

                    tmp_call_106_1_6 = tmp_call_106_out;
                }
                {
                    double tmp_call_106_0_in = tmp_call_106_1_6;
                    double ydthf_var_53_0_in_rtice = v_ydthf_var_53_rtice[0];
                    double tmp_call_105_out;

                    ///////////////////
                    // Tasklet code (T_l1362_c1362)
                    tmp_call_105_out = max(ydthf_var_53_0_in_rtice, tmp_call_106_0_in);
                    ///////////////////

                    tmp_call_105_1_6 = tmp_call_105_out;
                }
                {
                    double ptare_var_54_0_in = oka;
                    double ptare_var_54_1_in = oka;
                    double ydcst_var_56_0_in_rtt = v_ydcst_var_56_rtt[0];
                    double ydthf_var_55_0_in_r3ies = v_ydthf_var_55_r3ies[0];
                    double ydthf_var_55_1_in_r4ies = v_ydthf_var_55_r4ies[0];
                    double tmp_arg_67_out;

                    ///////////////////
                    // Tasklet code (T_l1371_c1371)
                    tmp_arg_67_out = ((ydthf_var_55_0_in_r3ies * (ptare_var_54_0_in - ydcst_var_56_0_in_rtt)) / (ptare_var_54_1_in - ydthf_var_55_1_in_r4ies));
                    ///////////////////

                    tmp_arg_67_1 = tmp_arg_67_out;
                }
                {
                    double tmp_arg_67_0_in = tmp_arg_67_1;
                    double tmp_call_110_out;

                    ///////////////////
                    // Tasklet code (T_l1371_c1371)
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
                    double ydthf_var_53_0_in_rtice = v_ydthf_var_53_rtice[0];
                    double ydthf_var_53_1_in_rtwat_rtice_r = v_ydthf_var_53_rtwat_rtice_r[0];
                    double tmp_arg_66_out;

                    ///////////////////
                    // Tasklet code (T_l1362_c1362)
                    tmp_arg_66_out = ((tmp_call_105_0_in - ydthf_var_53_0_in_rtice) * ydthf_var_53_1_in_rtwat_rtice_r);
                    ///////////////////

                    tmp_arg_66_1_6 = tmp_arg_66_out;
                }
                {
                    double tmp_arg_66_0_in = tmp_arg_66_1_6;
                    double tmp_call_104_out;

                    ///////////////////
                    // Tasklet code (T_l1362_c1362)
                    tmp_call_104_out = (dace::math::ipow(tmp_arg_66_0_in, 2));
                    ///////////////////

                    tmp_call_104_1_6 = tmp_call_104_out;
                }
                {
                    double tmp_call_104_0_in = tmp_call_104_1_6;
                    double foealfa__ret_out;

                    ///////////////////
                    // Tasklet code (T_l1362_c1362)
                    foealfa__ret_out = min(1.0, tmp_call_104_0_in);
                    ///////////////////

                    tmp_call_109_1 = foealfa__ret_out;
                }
            }
            {
                double tmp_arg_68_1;
                double tmp_call_106_0_6;

                {
                    double ptare_var_52_0_in = oka;
                    double ydthf_var_53_0_in_rtwat = v_ydthf_var_53_rtwat[0];
                    double tmp_call_106_out;

                    ///////////////////
                    // Tasklet code (T_l1362_c1362)
                    tmp_call_106_out = min(ydthf_var_53_0_in_rtwat, ptare_var_52_0_in);
                    ///////////////////

                    tmp_call_106_0_6 = tmp_call_106_out;
                }
                {
                    double tmp_call_106_0_in = tmp_call_106_0_6;
                    double ydthf_var_53_0_in_rtice = v_ydthf_var_53_rtice[0];
                    double tmp_call_105_out;

                    ///////////////////
                    // Tasklet code (T_l1362_c1362)
                    tmp_call_105_out = max(ydthf_var_53_0_in_rtice, tmp_call_106_0_in);
                    ///////////////////

                    tmp_call_105_0_6 = tmp_call_105_out;
                }
                {
                    double ptare_var_54_0_in = oka;
                    double ptare_var_54_1_in = oka;
                    double ydcst_var_56_0_in_rtt = v_ydcst_var_56_rtt[0];
                    double ydthf_var_55_0_in_r3les = v_ydthf_var_55_r3les[0];
                    double ydthf_var_55_1_in_r4les = v_ydthf_var_55_r4les[0];
                    double tmp_arg_68_out;

                    ///////////////////
                    // Tasklet code (T_l1371_c1371)
                    tmp_arg_68_out = ((ydthf_var_55_0_in_r3les * (ptare_var_54_0_in - ydcst_var_56_0_in_rtt)) / (ptare_var_54_1_in - ydthf_var_55_1_in_r4les));
                    ///////////////////

                    tmp_arg_68_1 = tmp_arg_68_out;
                }
                {
                    double tmp_arg_68_0_in = tmp_arg_68_1;
                    double tmp_call_108_out;

                    ///////////////////
                    // Tasklet code (T_l1371_c1371)
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
                    double ydthf_var_53_0_in_rtice = v_ydthf_var_53_rtice[0];
                    double ydthf_var_53_1_in_rtwat_rtice_r = v_ydthf_var_53_rtwat_rtice_r[0];
                    double tmp_arg_66_out;

                    ///////////////////
                    // Tasklet code (T_l1362_c1362)
                    tmp_arg_66_out = ((tmp_call_105_0_in - ydthf_var_53_0_in_rtice) * ydthf_var_53_1_in_rtwat_rtice_r);
                    ///////////////////

                    tmp_arg_66_0_6 = tmp_arg_66_out;
                }
                {
                    double tmp_arg_66_0_in = tmp_arg_66_0_6;
                    double tmp_call_104_out;

                    ///////////////////
                    // Tasklet code (T_l1362_c1362)
                    tmp_call_104_out = (dace::math::ipow(tmp_arg_66_0_in, 2));
                    ///////////////////

                    tmp_call_104_0_6 = tmp_call_104_out;
                }
                {
                    double tmp_call_104_0_in = tmp_call_104_0_6;
                    double foealfa__ret_out;

                    ///////////////////
                    // Tasklet code (T_l1362_c1362)
                    foealfa__ret_out = min(1.0, tmp_call_104_0_in);
                    ///////////////////

                    tmp_call_107_1 = foealfa__ret_out;
                }
                {
                    double tmp_call_107_0_in = tmp_call_107_1;
                    double tmp_call_108_0_in = tmp_call_108_1;
                    double tmp_call_109_0_in = tmp_call_109_1;
                    double tmp_call_110_0_in = tmp_call_110_1;
                    double ydthf_var_55_0_in_r2es = v_ydthf_var_55_r2es[0];
                    double foeewm__ret_out;

                    ///////////////////
                    // Tasklet code (T_l1371_c1371)
                    foeewm__ret_out = (ydthf_var_55_0_in_r2es * ((tmp_call_107_0_in * tmp_call_108_0_in) + ((1.0 - tmp_call_109_0_in) * tmp_call_110_0_in)));
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
                    // Tasklet code (T_l755_c755)
                    zqsat_out = (tmp_call_28_0_in * zqp_0_in);
                    ///////////////////

                    zqsat = zqsat_out;
                }
                {
                    double zqsat_0_in = zqsat;
                    double zqsat_out;

                    ///////////////////
                    // Tasklet code (T_l756_c756)
                    zqsat_out = min(0.5, zqsat_0_in);
                    ///////////////////

                    zqsat = zqsat_out;
                }
                {
                    double ydcst_var_47_0_in_retv = v_ydcst_var_47_retv[0];
                    double zqsat_0_in = zqsat;
                    double zcor_out;

                    ///////////////////
                    // Tasklet code (T_l757_c757)
                    zcor_out = (1.0 / (1.0 - (ydcst_var_47_0_in_retv * zqsat_0_in)));
                    ///////////////////

                    zcor = zcor_out;
                }
                {
                    double zcor_0_in = zcor;
                    double zqsat_0_in = zqsat;
                    double zqsat_out;

                    ///////////////////
                    // Tasklet code (T_l758_c758)
                    zqsat_out = (zqsat_0_in * zcor_0_in);
                    ///////////////////

                    zqsat = zqsat_out;
                }
                {
                    double ztp1_0_in_0 = ztp1[((_for_it_42 + (sym_klon * (_for_it_23 - 1))) - 1)];
                    double oka_out;

                    ///////////////////
                    // Tasklet code (T_l759_c759)
                    oka_out = ztp1_0_in_0;
                    ///////////////////

                    oka = oka_out;
                }
                {
                    double ptare_var_57_0_in = oka;
                    double ydthf_var_58_0_in_r4ies = v_ydthf_var_58_r4ies[0];
                    double tmp_arg_69_out;

                    ///////////////////
                    // Tasklet code (T_l1378_c1378)
                    tmp_arg_69_out = (ptare_var_57_0_in - ydthf_var_58_0_in_r4ies);
                    ///////////////////

                    tmp_arg_69_2 = tmp_arg_69_out;
                }
                {
                    double tmp_arg_69_0_in = tmp_arg_69_2;
                    double tmp_call_114_out;

                    ///////////////////
                    // Tasklet code (T_l1378_c1378)
                    tmp_call_114_out = (dace::math::ipow(tmp_arg_69_0_in, 2));
                    ///////////////////

                    tmp_call_114_2 = tmp_call_114_out;
                }
                {
                    double ptare_var_52_0_in = oka;
                    double ydthf_var_53_0_in_rtwat = v_ydthf_var_53_rtwat[0];
                    double tmp_call_106_out;

                    ///////////////////
                    // Tasklet code (T_l1362_c1362)
                    tmp_call_106_out = min(ydthf_var_53_0_in_rtwat, ptare_var_52_0_in);
                    ///////////////////

                    tmp_call_106_1_5 = tmp_call_106_out;
                }
                {
                    double tmp_call_106_0_in = tmp_call_106_1_5;
                    double ydthf_var_53_0_in_rtice = v_ydthf_var_53_rtice[0];
                    double tmp_call_105_out;

                    ///////////////////
                    // Tasklet code (T_l1362_c1362)
                    tmp_call_105_out = max(ydthf_var_53_0_in_rtice, tmp_call_106_0_in);
                    ///////////////////

                    tmp_call_105_1_5 = tmp_call_105_out;
                }
            }
            {
                double tmp_call_104_1_5;
                double tmp_arg_66_1_5;

                {
                    double tmp_call_105_0_in = tmp_call_105_1_5;
                    double ydthf_var_53_0_in_rtice = v_ydthf_var_53_rtice[0];
                    double ydthf_var_53_1_in_rtwat_rtice_r = v_ydthf_var_53_rtwat_rtice_r[0];
                    double tmp_arg_66_out;

                    ///////////////////
                    // Tasklet code (T_l1362_c1362)
                    tmp_arg_66_out = ((tmp_call_105_0_in - ydthf_var_53_0_in_rtice) * ydthf_var_53_1_in_rtwat_rtice_r);
                    ///////////////////

                    tmp_arg_66_1_5 = tmp_arg_66_out;
                }
                {
                    double tmp_arg_66_0_in = tmp_arg_66_1_5;
                    double tmp_call_104_out;

                    ///////////////////
                    // Tasklet code (T_l1362_c1362)
                    tmp_call_104_out = (dace::math::ipow(tmp_arg_66_0_in, 2));
                    ///////////////////

                    tmp_call_104_1_5 = tmp_call_104_out;
                }
                {
                    double tmp_call_104_0_in = tmp_call_104_1_5;
                    double foealfa__ret_out;

                    ///////////////////
                    // Tasklet code (T_l1362_c1362)
                    foealfa__ret_out = min(1.0, tmp_call_104_0_in);
                    ///////////////////

                    tmp_call_113_2 = foealfa__ret_out;
                }
            }
            {
                double tmp_arg_70_2;
                double tmp_call_106_0_5;

                {
                    double ptare_var_57_0_in = oka;
                    double ydthf_var_58_0_in_r4les = v_ydthf_var_58_r4les[0];
                    double tmp_arg_70_out;

                    ///////////////////
                    // Tasklet code (T_l1378_c1378)
                    tmp_arg_70_out = (ptare_var_57_0_in - ydthf_var_58_0_in_r4les);
                    ///////////////////

                    tmp_arg_70_2 = tmp_arg_70_out;
                }
                {
                    double tmp_arg_70_0_in = tmp_arg_70_2;
                    double tmp_call_112_out;

                    ///////////////////
                    // Tasklet code (T_l1378_c1378)
                    tmp_call_112_out = (dace::math::ipow(tmp_arg_70_0_in, 2));
                    ///////////////////

                    tmp_call_112_2 = tmp_call_112_out;
                }
                {
                    double ptare_var_52_0_in = oka;
                    double ydthf_var_53_0_in_rtwat = v_ydthf_var_53_rtwat[0];
                    double tmp_call_106_out;

                    ///////////////////
                    // Tasklet code (T_l1362_c1362)
                    tmp_call_106_out = min(ydthf_var_53_0_in_rtwat, ptare_var_52_0_in);
                    ///////////////////

                    tmp_call_106_0_5 = tmp_call_106_out;
                }
                {
                    double tmp_call_106_0_in = tmp_call_106_0_5;
                    double ydthf_var_53_0_in_rtice = v_ydthf_var_53_rtice[0];
                    double tmp_call_105_out;

                    ///////////////////
                    // Tasklet code (T_l1362_c1362)
                    tmp_call_105_out = max(ydthf_var_53_0_in_rtice, tmp_call_106_0_in);
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
                    double ydthf_var_53_0_in_rtice = v_ydthf_var_53_rtice[0];
                    double ydthf_var_53_1_in_rtwat_rtice_r = v_ydthf_var_53_rtwat_rtice_r[0];
                    double tmp_arg_66_out;

                    ///////////////////
                    // Tasklet code (T_l1362_c1362)
                    tmp_arg_66_out = ((tmp_call_105_0_in - ydthf_var_53_0_in_rtice) * ydthf_var_53_1_in_rtwat_rtice_r);
                    ///////////////////

                    tmp_arg_66_0_5 = tmp_arg_66_out;
                }
                {
                    double tmp_arg_66_0_in = tmp_arg_66_0_5;
                    double tmp_call_104_out;

                    ///////////////////
                    // Tasklet code (T_l1362_c1362)
                    tmp_call_104_out = (dace::math::ipow(tmp_arg_66_0_in, 2));
                    ///////////////////

                    tmp_call_104_0_5 = tmp_call_104_out;
                }
                {
                    double tmp_call_104_0_in = tmp_call_104_0_5;
                    double foealfa__ret_out;

                    ///////////////////
                    // Tasklet code (T_l1362_c1362)
                    foealfa__ret_out = min(1.0, tmp_call_104_0_in);
                    ///////////////////

                    tmp_call_111_2 = foealfa__ret_out;
                }
                {
                    double tmp_call_111_0_in = tmp_call_111_2;
                    double tmp_call_112_0_in = tmp_call_112_2;
                    double tmp_call_113_0_in = tmp_call_113_2;
                    double tmp_call_114_0_in = tmp_call_114_2;
                    double ydthf_var_58_0_in_r5alvcp = v_ydthf_var_58_r5alvcp[0];
                    double ydthf_var_58_1_in_r5alscp = v_ydthf_var_58_r5alscp[0];
                    double foedem__ret_out;

                    ///////////////////
                    // Tasklet code (T_l1378_c1378)
                    foedem__ret_out =
                        (((tmp_call_111_0_in * ydthf_var_58_0_in_r5alvcp) * (1.0 / tmp_call_112_0_in)) + (((1.0 - tmp_call_113_0_in) * ydthf_var_58_1_in_r5alscp) * (1.0 / tmp_call_114_0_in)));
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
                    double zqsmix_0_in_0 = zqsmix[((_for_it_42 + (sym_klon * (_for_it_23 - 1))) - 1)];
                    double zcond_out;

                    ///////////////////
                    // Tasklet code (T_l760_c760)
                    zcond_out = ((zqsmix_0_in_0 - zqsat_0_in) / (1.0 + ((zqsat_1_in * zcor_0_in) * tmp_call_29_0_in)));
                    ///////////////////

                    zcond = zcond_out;
                }
                {
                    double ztp1_0_in_0 = ztp1[((_for_it_42 + (sym_klon * (_for_it_23 - 1))) - 1)];
                    double oka_out;

                    ///////////////////
                    // Tasklet code (T_l761_c761)
                    oka_out = ztp1_0_in_0;
                    ///////////////////

                    oka = oka_out;
                }
                {
                    double ptare_var_52_0_in = oka;
                    double ydthf_var_53_0_in_rtwat = v_ydthf_var_53_rtwat[0];
                    double tmp_call_106_out;

                    ///////////////////
                    // Tasklet code (T_l1362_c1362)
                    tmp_call_106_out = min(ydthf_var_53_0_in_rtwat, ptare_var_52_0_in);
                    ///////////////////

                    tmp_call_106_1_4 = tmp_call_106_out;
                }
                {
                    double tmp_call_106_0_in = tmp_call_106_1_4;
                    double ydthf_var_53_0_in_rtice = v_ydthf_var_53_rtice[0];
                    double tmp_call_105_out;

                    ///////////////////
                    // Tasklet code (T_l1362_c1362)
                    tmp_call_105_out = max(ydthf_var_53_0_in_rtice, tmp_call_106_0_in);
                    ///////////////////

                    tmp_call_105_1_4 = tmp_call_105_out;
                }
            }
            {
                double tmp_call_104_1_4;
                double tmp_arg_66_1_4;

                {
                    double tmp_call_105_0_in = tmp_call_105_1_4;
                    double ydthf_var_53_0_in_rtice = v_ydthf_var_53_rtice[0];
                    double ydthf_var_53_1_in_rtwat_rtice_r = v_ydthf_var_53_rtwat_rtice_r[0];
                    double tmp_arg_66_out;

                    ///////////////////
                    // Tasklet code (T_l1362_c1362)
                    tmp_arg_66_out = ((tmp_call_105_0_in - ydthf_var_53_0_in_rtice) * ydthf_var_53_1_in_rtwat_rtice_r);
                    ///////////////////

                    tmp_arg_66_1_4 = tmp_arg_66_out;
                }
                {
                    double tmp_arg_66_0_in = tmp_arg_66_1_4;
                    double tmp_call_104_out;

                    ///////////////////
                    // Tasklet code (T_l1362_c1362)
                    tmp_call_104_out = (dace::math::ipow(tmp_arg_66_0_in, 2));
                    ///////////////////

                    tmp_call_104_1_4 = tmp_call_104_out;
                }
                {
                    double tmp_call_104_0_in = tmp_call_104_1_4;
                    double foealfa__ret_out;

                    ///////////////////
                    // Tasklet code (T_l1362_c1362)
                    foealfa__ret_out = min(1.0, tmp_call_104_0_in);
                    ///////////////////

                    tmp_call_116_1 = foealfa__ret_out;
                }
            }
            {
                double tmp_call_106_0_4;

                {
                    double ptare_var_52_0_in = oka;
                    double ydthf_var_53_0_in_rtwat = v_ydthf_var_53_rtwat[0];
                    double tmp_call_106_out;

                    ///////////////////
                    // Tasklet code (T_l1362_c1362)
                    tmp_call_106_out = min(ydthf_var_53_0_in_rtwat, ptare_var_52_0_in);
                    ///////////////////

                    tmp_call_106_0_4 = tmp_call_106_out;
                }
                {
                    double tmp_call_106_0_in = tmp_call_106_0_4;
                    double ydthf_var_53_0_in_rtice = v_ydthf_var_53_rtice[0];
                    double tmp_call_105_out;

                    ///////////////////
                    // Tasklet code (T_l1362_c1362)
                    tmp_call_105_out = max(ydthf_var_53_0_in_rtice, tmp_call_106_0_in);
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
                    double ydthf_var_53_0_in_rtice = v_ydthf_var_53_rtice[0];
                    double ydthf_var_53_1_in_rtwat_rtice_r = v_ydthf_var_53_rtwat_rtice_r[0];
                    double tmp_arg_66_out;

                    ///////////////////
                    // Tasklet code (T_l1362_c1362)
                    tmp_arg_66_out = ((tmp_call_105_0_in - ydthf_var_53_0_in_rtice) * ydthf_var_53_1_in_rtwat_rtice_r);
                    ///////////////////

                    tmp_arg_66_0_4 = tmp_arg_66_out;
                }
                {
                    double tmp_arg_66_0_in = tmp_arg_66_0_4;
                    double tmp_call_104_out;

                    ///////////////////
                    // Tasklet code (T_l1362_c1362)
                    tmp_call_104_out = (dace::math::ipow(tmp_arg_66_0_in, 2));
                    ///////////////////

                    tmp_call_104_0_4 = tmp_call_104_out;
                }
                {
                    double tmp_call_104_0_in = tmp_call_104_0_4;
                    double foealfa__ret_out;

                    ///////////////////
                    // Tasklet code (T_l1362_c1362)
                    foealfa__ret_out = min(1.0, tmp_call_104_0_in);
                    ///////////////////

                    tmp_call_115_1 = foealfa__ret_out;
                }
                {
                    double tmp_call_115_0_in = tmp_call_115_1;
                    double tmp_call_116_0_in = tmp_call_116_1;
                    double ydthf_var_60_0_in_ralvdcp = v_ydthf_var_60_ralvdcp[0];
                    double ydthf_var_60_1_in_ralsdcp = v_ydthf_var_60_ralsdcp[0];
                    double foeldcpm__ret_out;

                    ///////////////////
                    // Tasklet code (T_l1385_c1385)
                    foeldcpm__ret_out = ((tmp_call_115_0_in * ydthf_var_60_0_in_ralvdcp) + ((1.0 - tmp_call_116_0_in) * ydthf_var_60_1_in_ralsdcp));
                    ///////////////////

                    tmp_call_30 = foeldcpm__ret_out;
                }
            }
            {
                double tmp_arg_67_0;
                double tmp_call_106_1_3;

                {
                    double zcond_0_in = zcond;
                    double zqsmix_0_in_0 = zqsmix[((_for_it_42 + (sym_klon * (_for_it_23 - 1))) - 1)];
                    double zqsmix_out_0;

                    ///////////////////
                    // Tasklet code (T_l763_c763)
                    zqsmix_out_0 = (zqsmix_0_in_0 - zcond_0_in);
                    ///////////////////

                    zqsmix[((_for_it_42 + (sym_klon * (_for_it_23 - 1))) - 1)] = zqsmix_out_0;
                }
                {
                    double tmp_call_30_0_in = tmp_call_30;
                    double zcond_0_in = zcond;
                    double ztp1_0_in_0 = ztp1[((_for_it_42 + (sym_klon * (_for_it_23 - 1))) - 1)];
                    double ztp1_out_0;

                    ///////////////////
                    // Tasklet code (T_l762_c762)
                    ztp1_out_0 = (ztp1_0_in_0 + (tmp_call_30_0_in * zcond_0_in));
                    ///////////////////

                    ztp1[((_for_it_42 + (sym_klon * (_for_it_23 - 1))) - 1)] = ztp1_out_0;
                }
                {
                    double ztp1_0_in_0 = ztp1[((_for_it_42 + (sym_klon * (_for_it_23 - 1))) - 1)];
                    double oka_out;

                    ///////////////////
                    // Tasklet code (T_l764_c764)
                    oka_out = ztp1_0_in_0;
                    ///////////////////

                    oka = oka_out;
                }
                {
                    double ptare_var_52_0_in = oka;
                    double ydthf_var_53_0_in_rtwat = v_ydthf_var_53_rtwat[0];
                    double tmp_call_106_out;

                    ///////////////////
                    // Tasklet code (T_l1362_c1362)
                    tmp_call_106_out = min(ydthf_var_53_0_in_rtwat, ptare_var_52_0_in);
                    ///////////////////

                    tmp_call_106_1_3 = tmp_call_106_out;
                }
                {
                    double tmp_call_106_0_in = tmp_call_106_1_3;
                    double ydthf_var_53_0_in_rtice = v_ydthf_var_53_rtice[0];
                    double tmp_call_105_out;

                    ///////////////////
                    // Tasklet code (T_l1362_c1362)
                    tmp_call_105_out = max(ydthf_var_53_0_in_rtice, tmp_call_106_0_in);
                    ///////////////////

                    tmp_call_105_1_3 = tmp_call_105_out;
                }
                {
                    double ptare_var_54_0_in = oka;
                    double ptare_var_54_1_in = oka;
                    double ydcst_var_56_0_in_rtt = v_ydcst_var_56_rtt[0];
                    double ydthf_var_55_0_in_r3ies = v_ydthf_var_55_r3ies[0];
                    double ydthf_var_55_1_in_r4ies = v_ydthf_var_55_r4ies[0];
                    double tmp_arg_67_out;

                    ///////////////////
                    // Tasklet code (T_l1371_c1371)
                    tmp_arg_67_out = ((ydthf_var_55_0_in_r3ies * (ptare_var_54_0_in - ydcst_var_56_0_in_rtt)) / (ptare_var_54_1_in - ydthf_var_55_1_in_r4ies));
                    ///////////////////

                    tmp_arg_67_0 = tmp_arg_67_out;
                }
                {
                    double tmp_arg_67_0_in = tmp_arg_67_0;
                    double tmp_call_110_out;

                    ///////////////////
                    // Tasklet code (T_l1371_c1371)
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
                    double ydthf_var_53_0_in_rtice = v_ydthf_var_53_rtice[0];
                    double ydthf_var_53_1_in_rtwat_rtice_r = v_ydthf_var_53_rtwat_rtice_r[0];
                    double tmp_arg_66_out;

                    ///////////////////
                    // Tasklet code (T_l1362_c1362)
                    tmp_arg_66_out = ((tmp_call_105_0_in - ydthf_var_53_0_in_rtice) * ydthf_var_53_1_in_rtwat_rtice_r);
                    ///////////////////

                    tmp_arg_66_1_3 = tmp_arg_66_out;
                }
                {
                    double tmp_arg_66_0_in = tmp_arg_66_1_3;
                    double tmp_call_104_out;

                    ///////////////////
                    // Tasklet code (T_l1362_c1362)
                    tmp_call_104_out = (dace::math::ipow(tmp_arg_66_0_in, 2));
                    ///////////////////

                    tmp_call_104_1_3 = tmp_call_104_out;
                }
                {
                    double tmp_call_104_0_in = tmp_call_104_1_3;
                    double foealfa__ret_out;

                    ///////////////////
                    // Tasklet code (T_l1362_c1362)
                    foealfa__ret_out = min(1.0, tmp_call_104_0_in);
                    ///////////////////

                    tmp_call_109_0 = foealfa__ret_out;
                }
            }
            {
                double tmp_arg_68_0;
                double tmp_call_106_0_3;

                {
                    double ptare_var_52_0_in = oka;
                    double ydthf_var_53_0_in_rtwat = v_ydthf_var_53_rtwat[0];
                    double tmp_call_106_out;

                    ///////////////////
                    // Tasklet code (T_l1362_c1362)
                    tmp_call_106_out = min(ydthf_var_53_0_in_rtwat, ptare_var_52_0_in);
                    ///////////////////

                    tmp_call_106_0_3 = tmp_call_106_out;
                }
                {
                    double tmp_call_106_0_in = tmp_call_106_0_3;
                    double ydthf_var_53_0_in_rtice = v_ydthf_var_53_rtice[0];
                    double tmp_call_105_out;

                    ///////////////////
                    // Tasklet code (T_l1362_c1362)
                    tmp_call_105_out = max(ydthf_var_53_0_in_rtice, tmp_call_106_0_in);
                    ///////////////////

                    tmp_call_105_0_3 = tmp_call_105_out;
                }
                {
                    double ptare_var_54_0_in = oka;
                    double ptare_var_54_1_in = oka;
                    double ydcst_var_56_0_in_rtt = v_ydcst_var_56_rtt[0];
                    double ydthf_var_55_0_in_r3les = v_ydthf_var_55_r3les[0];
                    double ydthf_var_55_1_in_r4les = v_ydthf_var_55_r4les[0];
                    double tmp_arg_68_out;

                    ///////////////////
                    // Tasklet code (T_l1371_c1371)
                    tmp_arg_68_out = ((ydthf_var_55_0_in_r3les * (ptare_var_54_0_in - ydcst_var_56_0_in_rtt)) / (ptare_var_54_1_in - ydthf_var_55_1_in_r4les));
                    ///////////////////

                    tmp_arg_68_0 = tmp_arg_68_out;
                }
                {
                    double tmp_arg_68_0_in = tmp_arg_68_0;
                    double tmp_call_108_out;

                    ///////////////////
                    // Tasklet code (T_l1371_c1371)
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
                    double ydthf_var_53_0_in_rtice = v_ydthf_var_53_rtice[0];
                    double ydthf_var_53_1_in_rtwat_rtice_r = v_ydthf_var_53_rtwat_rtice_r[0];
                    double tmp_arg_66_out;

                    ///////////////////
                    // Tasklet code (T_l1362_c1362)
                    tmp_arg_66_out = ((tmp_call_105_0_in - ydthf_var_53_0_in_rtice) * ydthf_var_53_1_in_rtwat_rtice_r);
                    ///////////////////

                    tmp_arg_66_0_3 = tmp_arg_66_out;
                }
                {
                    double tmp_arg_66_0_in = tmp_arg_66_0_3;
                    double tmp_call_104_out;

                    ///////////////////
                    // Tasklet code (T_l1362_c1362)
                    tmp_call_104_out = (dace::math::ipow(tmp_arg_66_0_in, 2));
                    ///////////////////

                    tmp_call_104_0_3 = tmp_call_104_out;
                }
                {
                    double tmp_call_104_0_in = tmp_call_104_0_3;
                    double foealfa__ret_out;

                    ///////////////////
                    // Tasklet code (T_l1362_c1362)
                    foealfa__ret_out = min(1.0, tmp_call_104_0_in);
                    ///////////////////

                    tmp_call_107_0 = foealfa__ret_out;
                }
                {
                    double tmp_call_107_0_in = tmp_call_107_0;
                    double tmp_call_108_0_in = tmp_call_108_0;
                    double tmp_call_109_0_in = tmp_call_109_0;
                    double tmp_call_110_0_in = tmp_call_110_0;
                    double ydthf_var_55_0_in_r2es = v_ydthf_var_55_r2es[0];
                    double foeewm__ret_out;

                    ///////////////////
                    // Tasklet code (T_l1371_c1371)
                    foeewm__ret_out = (ydthf_var_55_0_in_r2es * ((tmp_call_107_0_in * tmp_call_108_0_in) + ((1.0 - tmp_call_109_0_in) * tmp_call_110_0_in)));
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
                    // Tasklet code (T_l765_c765)
                    zqsat_out = (tmp_call_31_0_in * zqp_0_in);
                    ///////////////////

                    zqsat = zqsat_out;
                }
                {
                    double zqsat_0_in = zqsat;
                    double zqsat_out;

                    ///////////////////
                    // Tasklet code (T_l766_c766)
                    zqsat_out = min(0.5, zqsat_0_in);
                    ///////////////////

                    zqsat = zqsat_out;
                }
                {
                    double ydcst_var_47_0_in_retv = v_ydcst_var_47_retv[0];
                    double zqsat_0_in = zqsat;
                    double zcor_out;

                    ///////////////////
                    // Tasklet code (T_l767_c767)
                    zcor_out = (1.0 / (1.0 - (ydcst_var_47_0_in_retv * zqsat_0_in)));
                    ///////////////////

                    zcor = zcor_out;
                }
                {
                    double zcor_0_in = zcor;
                    double zqsat_0_in = zqsat;
                    double zqsat_out;

                    ///////////////////
                    // Tasklet code (T_l768_c768)
                    zqsat_out = (zqsat_0_in * zcor_0_in);
                    ///////////////////

                    zqsat = zqsat_out;
                }
                {
                    double ztp1_0_in_0 = ztp1[((_for_it_42 + (sym_klon * (_for_it_23 - 1))) - 1)];
                    double oka_out;

                    ///////////////////
                    // Tasklet code (T_l769_c769)
                    oka_out = ztp1_0_in_0;
                    ///////////////////

                    oka = oka_out;
                }
                {
                    double ptare_var_57_0_in = oka;
                    double ydthf_var_58_0_in_r4ies = v_ydthf_var_58_r4ies[0];
                    double tmp_arg_69_out;

                    ///////////////////
                    // Tasklet code (T_l1378_c1378)
                    tmp_arg_69_out = (ptare_var_57_0_in - ydthf_var_58_0_in_r4ies);
                    ///////////////////

                    tmp_arg_69_1 = tmp_arg_69_out;
                }
                {
                    double tmp_arg_69_0_in = tmp_arg_69_1;
                    double tmp_call_114_out;

                    ///////////////////
                    // Tasklet code (T_l1378_c1378)
                    tmp_call_114_out = (dace::math::ipow(tmp_arg_69_0_in, 2));
                    ///////////////////

                    tmp_call_114_1 = tmp_call_114_out;
                }
                {
                    double ptare_var_52_0_in = oka;
                    double ydthf_var_53_0_in_rtwat = v_ydthf_var_53_rtwat[0];
                    double tmp_call_106_out;

                    ///////////////////
                    // Tasklet code (T_l1362_c1362)
                    tmp_call_106_out = min(ydthf_var_53_0_in_rtwat, ptare_var_52_0_in);
                    ///////////////////

                    tmp_call_106_1_2 = tmp_call_106_out;
                }
                {
                    double tmp_call_106_0_in = tmp_call_106_1_2;
                    double ydthf_var_53_0_in_rtice = v_ydthf_var_53_rtice[0];
                    double tmp_call_105_out;

                    ///////////////////
                    // Tasklet code (T_l1362_c1362)
                    tmp_call_105_out = max(ydthf_var_53_0_in_rtice, tmp_call_106_0_in);
                    ///////////////////

                    tmp_call_105_1_2 = tmp_call_105_out;
                }
            }
            {
                double tmp_call_104_1_2;
                double tmp_arg_66_1_2;

                {
                    double tmp_call_105_0_in = tmp_call_105_1_2;
                    double ydthf_var_53_0_in_rtice = v_ydthf_var_53_rtice[0];
                    double ydthf_var_53_1_in_rtwat_rtice_r = v_ydthf_var_53_rtwat_rtice_r[0];
                    double tmp_arg_66_out;

                    ///////////////////
                    // Tasklet code (T_l1362_c1362)
                    tmp_arg_66_out = ((tmp_call_105_0_in - ydthf_var_53_0_in_rtice) * ydthf_var_53_1_in_rtwat_rtice_r);
                    ///////////////////

                    tmp_arg_66_1_2 = tmp_arg_66_out;
                }
                {
                    double tmp_arg_66_0_in = tmp_arg_66_1_2;
                    double tmp_call_104_out;

                    ///////////////////
                    // Tasklet code (T_l1362_c1362)
                    tmp_call_104_out = (dace::math::ipow(tmp_arg_66_0_in, 2));
                    ///////////////////

                    tmp_call_104_1_2 = tmp_call_104_out;
                }
                {
                    double tmp_call_104_0_in = tmp_call_104_1_2;
                    double foealfa__ret_out;

                    ///////////////////
                    // Tasklet code (T_l1362_c1362)
                    foealfa__ret_out = min(1.0, tmp_call_104_0_in);
                    ///////////////////

                    tmp_call_113_1 = foealfa__ret_out;
                }
            }
            {
                double tmp_arg_70_1;
                double tmp_call_106_0_2;

                {
                    double ptare_var_57_0_in = oka;
                    double ydthf_var_58_0_in_r4les = v_ydthf_var_58_r4les[0];
                    double tmp_arg_70_out;

                    ///////////////////
                    // Tasklet code (T_l1378_c1378)
                    tmp_arg_70_out = (ptare_var_57_0_in - ydthf_var_58_0_in_r4les);
                    ///////////////////

                    tmp_arg_70_1 = tmp_arg_70_out;
                }
                {
                    double tmp_arg_70_0_in = tmp_arg_70_1;
                    double tmp_call_112_out;

                    ///////////////////
                    // Tasklet code (T_l1378_c1378)
                    tmp_call_112_out = (dace::math::ipow(tmp_arg_70_0_in, 2));
                    ///////////////////

                    tmp_call_112_1 = tmp_call_112_out;
                }
                {
                    double ptare_var_52_0_in = oka;
                    double ydthf_var_53_0_in_rtwat = v_ydthf_var_53_rtwat[0];
                    double tmp_call_106_out;

                    ///////////////////
                    // Tasklet code (T_l1362_c1362)
                    tmp_call_106_out = min(ydthf_var_53_0_in_rtwat, ptare_var_52_0_in);
                    ///////////////////

                    tmp_call_106_0_2 = tmp_call_106_out;
                }
                {
                    double tmp_call_106_0_in = tmp_call_106_0_2;
                    double ydthf_var_53_0_in_rtice = v_ydthf_var_53_rtice[0];
                    double tmp_call_105_out;

                    ///////////////////
                    // Tasklet code (T_l1362_c1362)
                    tmp_call_105_out = max(ydthf_var_53_0_in_rtice, tmp_call_106_0_in);
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
                    double ydthf_var_53_0_in_rtice = v_ydthf_var_53_rtice[0];
                    double ydthf_var_53_1_in_rtwat_rtice_r = v_ydthf_var_53_rtwat_rtice_r[0];
                    double tmp_arg_66_out;

                    ///////////////////
                    // Tasklet code (T_l1362_c1362)
                    tmp_arg_66_out = ((tmp_call_105_0_in - ydthf_var_53_0_in_rtice) * ydthf_var_53_1_in_rtwat_rtice_r);
                    ///////////////////

                    tmp_arg_66_0_2 = tmp_arg_66_out;
                }
                {
                    double tmp_arg_66_0_in = tmp_arg_66_0_2;
                    double tmp_call_104_out;

                    ///////////////////
                    // Tasklet code (T_l1362_c1362)
                    tmp_call_104_out = (dace::math::ipow(tmp_arg_66_0_in, 2));
                    ///////////////////

                    tmp_call_104_0_2 = tmp_call_104_out;
                }
                {
                    double tmp_call_104_0_in = tmp_call_104_0_2;
                    double foealfa__ret_out;

                    ///////////////////
                    // Tasklet code (T_l1362_c1362)
                    foealfa__ret_out = min(1.0, tmp_call_104_0_in);
                    ///////////////////

                    tmp_call_111_1 = foealfa__ret_out;
                }
                {
                    double tmp_call_111_0_in = tmp_call_111_1;
                    double tmp_call_112_0_in = tmp_call_112_1;
                    double tmp_call_113_0_in = tmp_call_113_1;
                    double tmp_call_114_0_in = tmp_call_114_1;
                    double ydthf_var_58_0_in_r5alvcp = v_ydthf_var_58_r5alvcp[0];
                    double ydthf_var_58_1_in_r5alscp = v_ydthf_var_58_r5alscp[0];
                    double foedem__ret_out;

                    ///////////////////
                    // Tasklet code (T_l1378_c1378)
                    foedem__ret_out =
                        (((tmp_call_111_0_in * ydthf_var_58_0_in_r5alvcp) * (1.0 / tmp_call_112_0_in)) + (((1.0 - tmp_call_113_0_in) * ydthf_var_58_1_in_r5alscp) * (1.0 / tmp_call_114_0_in)));
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
                    double zqsmix_0_in_0 = zqsmix[((_for_it_42 + (sym_klon * (_for_it_23 - 1))) - 1)];
                    double zcond1_out;

                    ///////////////////
                    // Tasklet code (T_l770_c770)
                    zcond1_out = ((zqsmix_0_in_0 - zqsat_0_in) / (1.0 + ((zqsat_1_in * zcor_0_in) * tmp_call_32_0_in)));
                    ///////////////////

                    zcond1 = zcond1_out;
                }
                {
                    double ztp1_0_in_0 = ztp1[((_for_it_42 + (sym_klon * (_for_it_23 - 1))) - 1)];
                    double oka_out;

                    ///////////////////
                    // Tasklet code (T_l771_c771)
                    oka_out = ztp1_0_in_0;
                    ///////////////////

                    oka = oka_out;
                }
                {
                    double ptare_var_52_0_in = oka;
                    double ydthf_var_53_0_in_rtwat = v_ydthf_var_53_rtwat[0];
                    double tmp_call_106_out;

                    ///////////////////
                    // Tasklet code (T_l1362_c1362)
                    tmp_call_106_out = min(ydthf_var_53_0_in_rtwat, ptare_var_52_0_in);
                    ///////////////////

                    tmp_call_106_1_1 = tmp_call_106_out;
                }
                {
                    double tmp_call_106_0_in = tmp_call_106_1_1;
                    double ydthf_var_53_0_in_rtice = v_ydthf_var_53_rtice[0];
                    double tmp_call_105_out;

                    ///////////////////
                    // Tasklet code (T_l1362_c1362)
                    tmp_call_105_out = max(ydthf_var_53_0_in_rtice, tmp_call_106_0_in);
                    ///////////////////

                    tmp_call_105_1_1 = tmp_call_105_out;
                }
            }
            {
                double tmp_call_104_1_1;
                double tmp_arg_66_1_1;

                {
                    double tmp_call_105_0_in = tmp_call_105_1_1;
                    double ydthf_var_53_0_in_rtice = v_ydthf_var_53_rtice[0];
                    double ydthf_var_53_1_in_rtwat_rtice_r = v_ydthf_var_53_rtwat_rtice_r[0];
                    double tmp_arg_66_out;

                    ///////////////////
                    // Tasklet code (T_l1362_c1362)
                    tmp_arg_66_out = ((tmp_call_105_0_in - ydthf_var_53_0_in_rtice) * ydthf_var_53_1_in_rtwat_rtice_r);
                    ///////////////////

                    tmp_arg_66_1_1 = tmp_arg_66_out;
                }
                {
                    double tmp_arg_66_0_in = tmp_arg_66_1_1;
                    double tmp_call_104_out;

                    ///////////////////
                    // Tasklet code (T_l1362_c1362)
                    tmp_call_104_out = (dace::math::ipow(tmp_arg_66_0_in, 2));
                    ///////////////////

                    tmp_call_104_1_1 = tmp_call_104_out;
                }
                {
                    double tmp_call_104_0_in = tmp_call_104_1_1;
                    double foealfa__ret_out;

                    ///////////////////
                    // Tasklet code (T_l1362_c1362)
                    foealfa__ret_out = min(1.0, tmp_call_104_0_in);
                    ///////////////////

                    tmp_call_116_0 = foealfa__ret_out;
                }
            }
            {
                double tmp_call_106_0_1;

                {
                    double ptare_var_52_0_in = oka;
                    double ydthf_var_53_0_in_rtwat = v_ydthf_var_53_rtwat[0];
                    double tmp_call_106_out;

                    ///////////////////
                    // Tasklet code (T_l1362_c1362)
                    tmp_call_106_out = min(ydthf_var_53_0_in_rtwat, ptare_var_52_0_in);
                    ///////////////////

                    tmp_call_106_0_1 = tmp_call_106_out;
                }
                {
                    double tmp_call_106_0_in = tmp_call_106_0_1;
                    double ydthf_var_53_0_in_rtice = v_ydthf_var_53_rtice[0];
                    double tmp_call_105_out;

                    ///////////////////
                    // Tasklet code (T_l1362_c1362)
                    tmp_call_105_out = max(ydthf_var_53_0_in_rtice, tmp_call_106_0_in);
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
                    double ydthf_var_53_0_in_rtice = v_ydthf_var_53_rtice[0];
                    double ydthf_var_53_1_in_rtwat_rtice_r = v_ydthf_var_53_rtwat_rtice_r[0];
                    double tmp_arg_66_out;

                    ///////////////////
                    // Tasklet code (T_l1362_c1362)
                    tmp_arg_66_out = ((tmp_call_105_0_in - ydthf_var_53_0_in_rtice) * ydthf_var_53_1_in_rtwat_rtice_r);
                    ///////////////////

                    tmp_arg_66_0_1 = tmp_arg_66_out;
                }
                {
                    double tmp_arg_66_0_in = tmp_arg_66_0_1;
                    double tmp_call_104_out;

                    ///////////////////
                    // Tasklet code (T_l1362_c1362)
                    tmp_call_104_out = (dace::math::ipow(tmp_arg_66_0_in, 2));
                    ///////////////////

                    tmp_call_104_0_1 = tmp_call_104_out;
                }
                {
                    double tmp_call_104_0_in = tmp_call_104_0_1;
                    double foealfa__ret_out;

                    ///////////////////
                    // Tasklet code (T_l1362_c1362)
                    foealfa__ret_out = min(1.0, tmp_call_104_0_in);
                    ///////////////////

                    tmp_call_115_0 = foealfa__ret_out;
                }
                {
                    double tmp_call_115_0_in = tmp_call_115_0;
                    double tmp_call_116_0_in = tmp_call_116_0;
                    double ydthf_var_60_0_in_ralvdcp = v_ydthf_var_60_ralvdcp[0];
                    double ydthf_var_60_1_in_ralsdcp = v_ydthf_var_60_ralsdcp[0];
                    double foeldcpm__ret_out;

                    ///////////////////
                    // Tasklet code (T_l1385_c1385)
                    foeldcpm__ret_out = ((tmp_call_115_0_in * ydthf_var_60_0_in_ralvdcp) + ((1.0 - tmp_call_116_0_in) * ydthf_var_60_1_in_ralsdcp));
                    ///////////////////

                    tmp_call_33 = foeldcpm__ret_out;
                }
                {
                    double tmp_call_33_0_in = tmp_call_33;
                    double zcond1_0_in = zcond1;
                    double ztp1_0_in_0 = ztp1[((_for_it_42 + (sym_klon * (_for_it_23 - 1))) - 1)];
                    double ztp1_out_0;

                    ///////////////////
                    // Tasklet code (T_l772_c772)
                    ztp1_out_0 = (ztp1_0_in_0 + (tmp_call_33_0_in * zcond1_0_in));
                    ///////////////////

                    ztp1[((_for_it_42 + (sym_klon * (_for_it_23 - 1))) - 1)] = ztp1_out_0;
                }
                {
                    double zcond1_0_in = zcond1;
                    double zqsmix_0_in_0 = zqsmix[((_for_it_42 + (sym_klon * (_for_it_23 - 1))) - 1)];
                    double zqsmix_out_0;

                    ///////////////////
                    // Tasklet code (T_l773_c773)
                    zqsmix_out_0 = (zqsmix_0_in_0 - zcond1_0_in);
                    ///////////////////

                    zqsmix[((_for_it_42 + (sym_klon * (_for_it_23 - 1))) - 1)] = zqsmix_out_0;
                }
            }
        }
        for (_for_it_43 = 1; (_for_it_43 <= icend); _for_it_43 = (_for_it_43 + 1)) {
            {
                {
                    double zqold_0_in_0 = zqold[(_for_it_43 - 1)];
                    double zqsmix_0_in_0 = zqsmix[((_for_it_43 + (sym_klon * (_for_it_23 - 1))) - 1)];
                    double zdqs_out_0;

                    ///////////////////
                    // Tasklet code (T_l776_c776)
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
                    // Tasklet code (T_l777_c777)
                    zqsmix_out_0 = zqold_0_in_0;
                    ///////////////////

                    zqsmix[((_for_it_43 + (sym_klon * (_for_it_23 - 1))) - 1)] = zqsmix_out_0;
                }
                {
                    double ztold_0_in_0 = ztold[(_for_it_43 - 1)];
                    double ztp1_out_0;

                    ///////////////////
                    // Tasklet code (T_l778_c778)
                    ztp1_out_0 = ztold_0_in_0;
                    ///////////////////

                    ztp1[((_for_it_43 + (sym_klon * (_for_it_23 - 1))) - 1)] = ztp1_out_0;
                }
            }
        }
        for (_for_it_44 = 1; (_for_it_44 <= icend); _for_it_44 = (_for_it_44 + 1)) {
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
                        // Tasklet code (T_l782_c782)
                        tmp_call_34_out = min(zdqs_0_in_0, zlicld_0_in_0);
                        ///////////////////

                        tmp_call_34 = tmp_call_34_out;
                    }
                    {
                        double tmp_call_34_0_in = tmp_call_34;
                        double za_0_in_0 = za[((_for_it_44 + (sym_klon * (_for_it_23 - 1))) - 1)];
                        double zlevap_out;

                        ///////////////////
                        // Tasklet code (T_l782_c782)
                        zlevap_out = (za_0_in_0 * tmp_call_34_0_in);
                        ///////////////////

                        zlevap = zlevap_out;
                    }
                    {
                        double zevaplimmix_0_in_0 = zevaplimmix[(_for_it_44 - 1)];
                        double zlevap_0_in = zlevap;
                        double zlevap_out;

                        ///////////////////
                        // Tasklet code (T_l783_c783)
                        zlevap_out = min(zlevap_0_in, zevaplimmix_0_in_0);
                        ///////////////////

                        zlevap = zlevap_out;
                    }
                    {
                        double zqsmix_0_in_0 = zqsmix[((_for_it_44 + (sym_klon * (_for_it_23 - 1))) - 1)];
                        double zqx_0_in_0 = zqx[(((_for_it_44 + ((4 * sym_klev) * sym_klon)) + (sym_klon * (_for_it_23 - 1))) - 1)];
                        double tmp_arg_19_out;

                        ///////////////////
                        // Tasklet code (T_l784_c784)
                        tmp_arg_19_out = (zqsmix_0_in_0 - zqx_0_in_0);
                        ///////////////////

                        tmp_arg_19 = tmp_arg_19_out;
                    }
                    {
                        double tmp_arg_19_0_in = tmp_arg_19;
                        double tmp_call_35_out;

                        ///////////////////
                        // Tasklet code (T_l784_c784)
                        tmp_call_35_out = max(tmp_arg_19_0_in, 0.0);
                        ///////////////////

                        tmp_call_35 = tmp_call_35_out;
                    }
                    {
                        double tmp_call_35_0_in = tmp_call_35;
                        double zlevap_0_in = zlevap;
                        double zlevap_out;

                        ///////////////////
                        // Tasklet code (T_l784_c784)
                        zlevap_out = min(zlevap_0_in, tmp_call_35_0_in);
                        ///////////////////

                        zlevap = zlevap_out;
                    }
                    {
                        double zlevap_0_in = zlevap;
                        double zliqfrac_0_in_0 = zliqfrac[((_for_it_44 + (sym_klon * (_for_it_23 - 1))) - 1)];
                        double zsolqa_0_in_0 = zsolqa[((_for_it_44 + (4 * sym_klon)) - 1)];
                        double zsolqa_out_0;

                        ///////////////////
                        // Tasklet code (T_l787_c787)
                        zsolqa_out_0 = (zsolqa_0_in_0 + (zliqfrac_0_in_0 * zlevap_0_in));
                        ///////////////////

                        zsolqa[((_for_it_44 + (4 * sym_klon)) - 1)] = zsolqa_out_0;
                    }
                    {
                        double zlevap_0_in = zlevap;
                        double zliqfrac_0_in_0 = zliqfrac[((_for_it_44 + (sym_klon * (_for_it_23 - 1))) - 1)];
                        double zsolqa_0_in_0 = zsolqa[((_for_it_44 + (20 * sym_klon)) - 1)];
                        double zsolqa_out_0;

                        ///////////////////
                        // Tasklet code (T_l788_c788)
                        zsolqa_out_0 = (zsolqa_0_in_0 - (zliqfrac_0_in_0 * zlevap_0_in));
                        ///////////////////

                        zsolqa[((_for_it_44 + (20 * sym_klon)) - 1)] = zsolqa_out_0;
                    }
                    {
                        double zicefrac_0_in_0 = zicefrac[((_for_it_44 + (sym_klon * (_for_it_23 - 1))) - 1)];
                        double zlevap_0_in = zlevap;
                        double zsolqa_0_in_0 = zsolqa[((_for_it_44 + (9 * sym_klon)) - 1)];
                        double zsolqa_out_0;

                        ///////////////////
                        // Tasklet code (T_l789_c789)
                        zsolqa_out_0 = (zsolqa_0_in_0 + (zicefrac_0_in_0 * zlevap_0_in));
                        ///////////////////

                        zsolqa[((_for_it_44 + (9 * sym_klon)) - 1)] = zsolqa_out_0;
                    }
                    {
                        double zicefrac_0_in_0 = zicefrac[((_for_it_44 + (sym_klon * (_for_it_23 - 1))) - 1)];
                        double zlevap_0_in = zlevap;
                        double zsolqa_0_in_0 = zsolqa[((_for_it_44 + (21 * sym_klon)) - 1)];
                        double zsolqa_out_0;

                        ///////////////////
                        // Tasklet code (T_l790_c790)
                        zsolqa_out_0 = (zsolqa_0_in_0 - (zicefrac_0_in_0 * zlevap_0_in));
                        ///////////////////

                        zsolqa[((_for_it_44 + (21 * sym_klon)) - 1)] = zsolqa_out_0;
                    }
                }
            }
        }
        for (_for_it_45 = 1; (_for_it_45 <= icend); _for_it_45 = (_for_it_45 + 1)) {
            {
                {
                    double ydecldp_var_49_0_in_rlmin = v_ydecldp_var_49_rlmin[0];
                    double za_0_in_0 = za[((_for_it_45 + (sym_klon * (_for_it_23 - 1))) - 1)];
                    double zdqs_0_in_0 = zdqs[(_for_it_45 - 1)];
                    double _if_cond_28_out;

                    ///////////////////
                    // Tasklet code (T_l0_c0)
                    _if_cond_28_out = ((za_0_in_0 > 1e-14) && (zdqs_0_in_0 <= (-ydecldp_var_49_0_in_rlmin)));
                    ///////////////////

                    _if_cond_28 = _if_cond_28_out;
                }
            }
            if ((_if_cond_28 == 1)) {
                _if_cond_29 = (za[((_for_it_45 + (sym_klon * (_for_it_23 - 1))) - 1)] > 0.99);
                {
                    double tmp_call_36;
                    double tmp_arg_20;

                    {
                        double zdqs_0_in_0 = zdqs[(_for_it_45 - 1)];
                        double tmp_arg_20_out;

                        ///////////////////
                        // Tasklet code (T_l795_c795)
                        tmp_arg_20_out = (-zdqs_0_in_0);
                        ///////////////////

                        tmp_arg_20 = tmp_arg_20_out;
                    }
                    {
                        double tmp_arg_20_0_in = tmp_arg_20;
                        double tmp_call_36_out;

                        ///////////////////
                        // Tasklet code (T_l795_c795)
                        tmp_call_36_out = max(tmp_arg_20_0_in, 0.0);
                        ///////////////////

                        tmp_call_36 = tmp_call_36_out;
                    }
                    {
                        double tmp_call_36_0_in = tmp_call_36;
                        double zlcond1_out_0;

                        ///////////////////
                        // Tasklet code (T_l795_c795)
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
                            double ydcst_var_47_0_in_retv = v_ydcst_var_47_retv[0];
                            double zqsmix_0_in_0 = zqsmix[((_for_it_45 + (sym_klon * (_for_it_23 - 1))) - 1)];
                            double zcor_out;

                            ///////////////////
                            // Tasklet code (T_l797_c797)
                            zcor_out = (1.0 / (1.0 - (ydcst_var_47_0_in_retv * zqsmix_0_in_0)));
                            ///////////////////

                            zcor = zcor_out;
                        }
                        {
                            double ztp1_0_in_0 = ztp1[((_for_it_45 + (sym_klon * (_for_it_23 - 1))) - 1)];
                            double oka_out;

                            ///////////////////
                            // Tasklet code (T_l798_c798)
                            oka_out = ztp1_0_in_0;
                            ///////////////////

                            oka = oka_out;
                        }
                        {
                            double ptare_var_57_0_in = oka;
                            double ydthf_var_58_0_in_r4ies = v_ydthf_var_58_r4ies[0];
                            double tmp_arg_69_out;

                            ///////////////////
                            // Tasklet code (T_l1378_c1378)
                            tmp_arg_69_out = (ptare_var_57_0_in - ydthf_var_58_0_in_r4ies);
                            ///////////////////

                            tmp_arg_69_0 = tmp_arg_69_out;
                        }
                        {
                            double tmp_arg_69_0_in = tmp_arg_69_0;
                            double tmp_call_114_out;

                            ///////////////////
                            // Tasklet code (T_l1378_c1378)
                            tmp_call_114_out = (dace::math::ipow(tmp_arg_69_0_in, 2));
                            ///////////////////

                            tmp_call_114_0 = tmp_call_114_out;
                        }
                        {
                            double ptare_var_52_0_in = oka;
                            double ydthf_var_53_0_in_rtwat = v_ydthf_var_53_rtwat[0];
                            double tmp_call_106_out;

                            ///////////////////
                            // Tasklet code (T_l1362_c1362)
                            tmp_call_106_out = min(ydthf_var_53_0_in_rtwat, ptare_var_52_0_in);
                            ///////////////////

                            tmp_call_106_1_0 = tmp_call_106_out;
                        }
                        {
                            double tmp_call_106_0_in = tmp_call_106_1_0;
                            double ydthf_var_53_0_in_rtice = v_ydthf_var_53_rtice[0];
                            double tmp_call_105_out;

                            ///////////////////
                            // Tasklet code (T_l1362_c1362)
                            tmp_call_105_out = max(ydthf_var_53_0_in_rtice, tmp_call_106_0_in);
                            ///////////////////

                            tmp_call_105_1_0 = tmp_call_105_out;
                        }
                    }
                    {
                        double tmp_call_104_1_0;
                        double tmp_arg_66_1_0;

                        {
                            double tmp_call_105_0_in = tmp_call_105_1_0;
                            double ydthf_var_53_0_in_rtice = v_ydthf_var_53_rtice[0];
                            double ydthf_var_53_1_in_rtwat_rtice_r = v_ydthf_var_53_rtwat_rtice_r[0];
                            double tmp_arg_66_out;

                            ///////////////////
                            // Tasklet code (T_l1362_c1362)
                            tmp_arg_66_out = ((tmp_call_105_0_in - ydthf_var_53_0_in_rtice) * ydthf_var_53_1_in_rtwat_rtice_r);
                            ///////////////////

                            tmp_arg_66_1_0 = tmp_arg_66_out;
                        }
                        {
                            double tmp_arg_66_0_in = tmp_arg_66_1_0;
                            double tmp_call_104_out;

                            ///////////////////
                            // Tasklet code (T_l1362_c1362)
                            tmp_call_104_out = (dace::math::ipow(tmp_arg_66_0_in, 2));
                            ///////////////////

                            tmp_call_104_1_0 = tmp_call_104_out;
                        }
                        {
                            double tmp_call_104_0_in = tmp_call_104_1_0;
                            double foealfa__ret_out;

                            ///////////////////
                            // Tasklet code (T_l1362_c1362)
                            foealfa__ret_out = min(1.0, tmp_call_104_0_in);
                            ///////////////////

                            tmp_call_113_0 = foealfa__ret_out;
                        }
                    }
                    {
                        double tmp_arg_70_0;
                        double tmp_call_106_0_0;

                        {
                            double ptare_var_57_0_in = oka;
                            double ydthf_var_58_0_in_r4les = v_ydthf_var_58_r4les[0];
                            double tmp_arg_70_out;

                            ///////////////////
                            // Tasklet code (T_l1378_c1378)
                            tmp_arg_70_out = (ptare_var_57_0_in - ydthf_var_58_0_in_r4les);
                            ///////////////////

                            tmp_arg_70_0 = tmp_arg_70_out;
                        }
                        {
                            double tmp_arg_70_0_in = tmp_arg_70_0;
                            double tmp_call_112_out;

                            ///////////////////
                            // Tasklet code (T_l1378_c1378)
                            tmp_call_112_out = (dace::math::ipow(tmp_arg_70_0_in, 2));
                            ///////////////////

                            tmp_call_112_0 = tmp_call_112_out;
                        }
                        {
                            double ptare_var_52_0_in = oka;
                            double ydthf_var_53_0_in_rtwat = v_ydthf_var_53_rtwat[0];
                            double tmp_call_106_out;

                            ///////////////////
                            // Tasklet code (T_l1362_c1362)
                            tmp_call_106_out = min(ydthf_var_53_0_in_rtwat, ptare_var_52_0_in);
                            ///////////////////

                            tmp_call_106_0_0 = tmp_call_106_out;
                        }
                        {
                            double tmp_call_106_0_in = tmp_call_106_0_0;
                            double ydthf_var_53_0_in_rtice = v_ydthf_var_53_rtice[0];
                            double tmp_call_105_out;

                            ///////////////////
                            // Tasklet code (T_l1362_c1362)
                            tmp_call_105_out = max(ydthf_var_53_0_in_rtice, tmp_call_106_0_in);
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
                            double ydthf_var_53_0_in_rtice = v_ydthf_var_53_rtice[0];
                            double ydthf_var_53_1_in_rtwat_rtice_r = v_ydthf_var_53_rtwat_rtice_r[0];
                            double tmp_arg_66_out;

                            ///////////////////
                            // Tasklet code (T_l1362_c1362)
                            tmp_arg_66_out = ((tmp_call_105_0_in - ydthf_var_53_0_in_rtice) * ydthf_var_53_1_in_rtwat_rtice_r);
                            ///////////////////

                            tmp_arg_66_0_0 = tmp_arg_66_out;
                        }
                        {
                            double tmp_arg_66_0_in = tmp_arg_66_0_0;
                            double tmp_call_104_out;

                            ///////////////////
                            // Tasklet code (T_l1362_c1362)
                            tmp_call_104_out = (dace::math::ipow(tmp_arg_66_0_in, 2));
                            ///////////////////

                            tmp_call_104_0_0 = tmp_call_104_out;
                        }
                        {
                            double tmp_call_104_0_in = tmp_call_104_0_0;
                            double foealfa__ret_out;

                            ///////////////////
                            // Tasklet code (T_l1362_c1362)
                            foealfa__ret_out = min(1.0, tmp_call_104_0_in);
                            ///////////////////

                            tmp_call_111_0 = foealfa__ret_out;
                        }
                        {
                            double tmp_call_111_0_in = tmp_call_111_0;
                            double tmp_call_112_0_in = tmp_call_112_0;
                            double tmp_call_113_0_in = tmp_call_113_0;
                            double tmp_call_114_0_in = tmp_call_114_0;
                            double ydthf_var_58_0_in_r5alvcp = v_ydthf_var_58_r5alvcp[0];
                            double ydthf_var_58_1_in_r5alscp = v_ydthf_var_58_r5alscp[0];
                            double foedem__ret_out;

                            ///////////////////
                            // Tasklet code (T_l1378_c1378)
                            foedem__ret_out =
                                (((tmp_call_111_0_in * ydthf_var_58_0_in_r5alvcp) * (1.0 / tmp_call_112_0_in)) + (((1.0 - tmp_call_113_0_in) * ydthf_var_58_1_in_r5alscp) * (1.0 / tmp_call_114_0_in)));
                            ///////////////////

                            tmp_call_37 = foedem__ret_out;
                        }
                        {
                            double tmp_call_37_0_in = tmp_call_37;
                            double zcor_0_in = zcor;
                            double zqsmix_0_in_0 = zqsmix[((_for_it_45 + (sym_klon * (_for_it_23 - 1))) - 1)];
                            double zqsmix_1_in_0 = zqsmix[((_for_it_45 + (sym_klon * (_for_it_23 - 1))) - 1)];
                            double zqx_0_in_0 = zqx[(((_for_it_45 + ((4 * sym_klev) * sym_klon)) + (sym_klon * (_for_it_23 - 1))) - 1)];
                            double zcdmax_out;

                            ///////////////////
                            // Tasklet code (T_l799_c799)
                            zcdmax_out = ((zqx_0_in_0 - zqsmix_0_in_0) / (1.0 + ((zcor_0_in * zqsmix_1_in_0) * tmp_call_37_0_in)));
                            ///////////////////

                            zcdmax = zcdmax_out;
                        }
                    }
                } else {
                    {
                        {
                            double za_0_in_0 = za[((_for_it_45 + (sym_klon * (_for_it_23 - 1))) - 1)];
                            double za_1_in_0 = za[((_for_it_45 + (sym_klon * (_for_it_23 - 1))) - 1)];
                            double zqsmix_0_in_0 = zqsmix[((_for_it_45 + (sym_klon * (_for_it_23 - 1))) - 1)];
                            double zqx_0_in_0 = zqx[(((_for_it_45 + ((4 * sym_klev) * sym_klon)) + (sym_klon * (_for_it_23 - 1))) - 1)];
                            double zcdmax_out;

                            ///////////////////
                            // Tasklet code (T_l801_c801)
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
                        // Tasklet code (T_l803_c803)
                        tmp_call_39_out = min(zlcond1_0_in_0, zcdmax_0_in);
                        ///////////////////

                        tmp_call_39 = tmp_call_39_out;
                    }
                    {
                        double tmp_call_39_0_in = tmp_call_39;
                        double tmp_call_38_out;

                        ///////////////////
                        // Tasklet code (T_l803_c803)
                        tmp_call_38_out = max(tmp_call_39_0_in, 0.0);
                        ///////////////////

                        tmp_call_38 = tmp_call_38_out;
                    }
                    {
                        double tmp_call_38_0_in = tmp_call_38;
                        double zlcond1_out_0;

                        ///////////////////
                        // Tasklet code (T_l803_c803)
                        zlcond1_out_0 = tmp_call_38_0_in;
                        ///////////////////

                        zlcond1[(_for_it_45 - 1)] = zlcond1_out_0;
                    }
                    {
                        double za_0_in_0 = za[((_for_it_45 + (sym_klon * (_for_it_23 - 1))) - 1)];
                        double zlcond1_0_in_0 = zlcond1[(_for_it_45 - 1)];
                        double zlcond1_out_0;

                        ///////////////////
                        // Tasklet code (T_l804_c804)
                        zlcond1_out_0 = (za_0_in_0 * zlcond1_0_in_0);
                        ///////////////////

                        zlcond1[(_for_it_45 - 1)] = zlcond1_out_0;
                    }
                    {
                        double ydecldp_var_49_0_in_rlmin = v_ydecldp_var_49_rlmin[0];
                        double zlcond1_0_in_0 = zlcond1[(_for_it_45 - 1)];
                        double _if_cond_30_out;

                        ///////////////////
                        // Tasklet code (T_l805_c805)
                        _if_cond_30_out = (zlcond1_0_in_0 < ydecldp_var_49_0_in_rlmin);
                        ///////////////////

                        _if_cond_30 = _if_cond_30_out;
                    }
                }
                if ((_if_cond_30 == 1)) {
                    {
                        {
                            double zlcond1_out_0;

                            ///////////////////
                            // Tasklet code (T_l805_c805)
                            zlcond1_out_0 = 0.0;
                            ///////////////////

                            zlcond1[(_for_it_45 - 1)] = zlcond1_out_0;
                        }
                    }
                }
                {
                    {
                        double ydecldp_var_49_0_in_rthomo = v_ydecldp_var_49_rthomo[0];
                        double ztp1_0_in_0 = ztp1[((_for_it_45 + (sym_klon * (_for_it_23 - 1))) - 1)];
                        double _if_cond_31_out;

                        ///////////////////
                        // Tasklet code (T_l0_c0)
                        _if_cond_31_out = (ztp1_0_in_0 > ydecldp_var_49_0_in_rthomo);
                        ///////////////////

                        _if_cond_31 = _if_cond_31_out;
                    }
                }
                if ((_if_cond_31 == 1)) {
                    {
                        {
                            double zlcond1_0_in_0 = zlcond1[(_for_it_45 - 1)];
                            double zsolqa_0_in_0 = zsolqa[((_for_it_45 + (20 * sym_klon)) - 1)];
                            double zsolqa_out_0;

                            ///////////////////
                            // Tasklet code (T_l807_c807)
                            zsolqa_out_0 = (zsolqa_0_in_0 + zlcond1_0_in_0);
                            ///////////////////

                            zsolqa[((_for_it_45 + (20 * sym_klon)) - 1)] = zsolqa_out_0;
                        }
                        {
                            double zlcond1_0_in_0 = zlcond1[(_for_it_45 - 1)];
                            double zsolqa_0_in_0 = zsolqa[((_for_it_45 + (4 * sym_klon)) - 1)];
                            double zsolqa_out_0;

                            ///////////////////
                            // Tasklet code (T_l808_c808)
                            zsolqa_out_0 = (zsolqa_0_in_0 - zlcond1_0_in_0);
                            ///////////////////

                            zsolqa[((_for_it_45 + (4 * sym_klon)) - 1)] = zsolqa_out_0;
                        }
                        {
                            double zlcond1_0_in_0 = zlcond1[(_for_it_45 - 1)];
                            double zqxfg_0_in_0 = zqxfg[(_for_it_45 - 1)];
                            double zqxfg_out_0;

                            ///////////////////
                            // Tasklet code (T_l809_c809)
                            zqxfg_out_0 = (zqxfg_0_in_0 + zlcond1_0_in_0);
                            ///////////////////

                            zqxfg[(_for_it_45 - 1)] = zqxfg_out_0;
                        }
                    }
                } else {
                    {
                        {
                            double zlcond1_0_in_0 = zlcond1[(_for_it_45 - 1)];
                            double zsolqa_0_in_0 = zsolqa[((_for_it_45 + (21 * sym_klon)) - 1)];
                            double zsolqa_out_0;

                            ///////////////////
                            // Tasklet code (T_l811_c811)
                            zsolqa_out_0 = (zsolqa_0_in_0 + zlcond1_0_in_0);
                            ///////////////////

                            zsolqa[((_for_it_45 + (21 * sym_klon)) - 1)] = zsolqa_out_0;
                        }
                        {
                            double zlcond1_0_in_0 = zlcond1[(_for_it_45 - 1)];
                            double zsolqa_0_in_0 = zsolqa[((_for_it_45 + (9 * sym_klon)) - 1)];
                            double zsolqa_out_0;

                            ///////////////////
                            // Tasklet code (T_l812_c812)
                            zsolqa_out_0 = (zsolqa_0_in_0 - zlcond1_0_in_0);
                            ///////////////////

                            zsolqa[((_for_it_45 + (9 * sym_klon)) - 1)] = zsolqa_out_0;
                        }
                        {
                            double zlcond1_0_in_0 = zlcond1[(_for_it_45 - 1)];
                            double zqxfg_0_in_0 = zqxfg[((_for_it_45 + sym_klon) - 1)];
                            double zqxfg_out_0;

                            ///////////////////
                            // Tasklet code (T_l813_c813)
                            zqxfg_out_0 = (zqxfg_0_in_0 + zlcond1_0_in_0);
                            ///////////////////

                            zqxfg[((_for_it_45 + sym_klon) - 1)] = zqxfg_out_0;
                        }
                    }
                }
            }
        }
        for (_for_it_46 = 1; (_for_it_46 <= icend); _for_it_46 = (_for_it_46 + 1)) {
            {
                {
                    double ydecldp_var_49_0_in_rlmin = v_ydecldp_var_49_rlmin[0];
                    double za_0_in_0 = za[((_for_it_46 + (sym_klon * (_for_it_23 - 1))) - 1)];
                    double zdqs_0_in_0 = zdqs[(_for_it_46 - 1)];
                    double _if_cond_32_out;

                    ///////////////////
                    // Tasklet code (T_l0_c0)
                    _if_cond_32_out = ((zdqs_0_in_0 <= (-ydecldp_var_49_0_in_rlmin)) && (za_0_in_0 < 0.99999999999999));
                    ///////////////////

                    _if_cond_32 = _if_cond_32_out;
                }
            }
            if ((_if_cond_32 == 1)) {
                {
                    {
                        double ydecldp_var_49_0_in_ramid = v_ydecldp_var_49_ramid[0];
                        double zrhc_out;

                        ///////////////////
                        // Tasklet code (T_l819_c819)
                        zrhc_out = ydecldp_var_49_0_in_ramid;
                        ///////////////////

                        zrhc = zrhc_out;
                    }
                }
                tmp_index_992 = ((klev[0] + 1) - 1);

                zsigk = (pap_var_17[((_for_it_46 + (sym_klon * (_for_it_23 - 1))) - 1)] / paph_var_18[((_for_it_46 + (sym_klon * tmp_index_992)) - 1)]);
                if (((zsigk > 0.8) == 1)) {
                    {
                        double tmp_call_40;
                        double tmp_arg_21;

                        {
                            double tmp_arg_21_out;

                            ///////////////////
                            // Tasklet code (T_l822_c822)
                            tmp_arg_21_out = ((zsigk - 0.8) / 0.2);
                            ///////////////////

                            tmp_arg_21 = tmp_arg_21_out;
                        }
                        {
                            double tmp_arg_21_0_in = tmp_arg_21;
                            double tmp_call_40_out;

                            ///////////////////
                            // Tasklet code (T_l822_c822)
                            tmp_call_40_out = (dace::math::ipow(tmp_arg_21_0_in, 2));
                            ///////////////////

                            tmp_call_40 = tmp_call_40_out;
                        }
                        {
                            double tmp_call_40_0_in = tmp_call_40;
                            double ydecldp_var_49_0_in_ramid = v_ydecldp_var_49_ramid[0];
                            double ydecldp_var_49_1_in_ramid = v_ydecldp_var_49_ramid[0];
                            double zrhc_out;

                            ///////////////////
                            // Tasklet code (T_l822_c822)
                            zrhc_out = (ydecldp_var_49_0_in_ramid + ((1.0 - ydecldp_var_49_1_in_ramid) * tmp_call_40_0_in));
                            ///////////////////

                            zrhc = zrhc_out;
                        }
                    }
                }
                {
                    {
                        int ydecldp_var_49_0_in_nssopt = v_ydecldp_var_49_nssopt[0];
                        int _if_cond_34_out;

                        ///////////////////
                        // Tasklet code (T_l0_c0)
                        _if_cond_34_out = (ydecldp_var_49_0_in_nssopt == 0);
                        ///////////////////

                        _if_cond_34 = _if_cond_34_out;
                    }
                }
                if ((_if_cond_34 == 1)) {
                    {
                        double tmp_call_41;
                        double tmp_arg_22;

                        {
                            double za_0_in_0 = za[((_for_it_46 + (sym_klon * (_for_it_23 - 1))) - 1)];
                            double tmp_arg_22_out;

                            ///////////////////
                            // Tasklet code (T_l825_c825)
                            tmp_arg_22_out = (1.0 - za_0_in_0);
                            ///////////////////

                            tmp_arg_22 = tmp_arg_22_out;
                        }
                        {
                            double tmp_arg_22_0_in = tmp_arg_22;
                            double zepsec_0_in = zepsec;
                            double tmp_call_41_out;

                            ///////////////////
                            // Tasklet code (T_l825_c825)
                            tmp_call_41_out = max(zepsec_0_in, tmp_arg_22_0_in);
                            ///////////////////

                            tmp_call_41 = tmp_call_41_out;
                        }
                        {
                            double tmp_call_41_0_in = tmp_call_41;
                            double za_0_in_0 = za[((_for_it_46 + (sym_klon * (_for_it_23 - 1))) - 1)];
                            double zqsice_0_in_0 = zqsice[((_for_it_46 + (sym_klon * (_for_it_23 - 1))) - 1)];
                            double zqx_0_in_0 = zqx[(((_for_it_46 + ((4 * sym_klev) * sym_klon)) + (sym_klon * (_for_it_23 - 1))) - 1)];
                            double zqe_out;

                            ///////////////////
                            // Tasklet code (T_l825_c825)
                            zqe_out = ((zqx_0_in_0 - (za_0_in_0 * zqsice_0_in_0)) / tmp_call_41_0_in);
                            ///////////////////

                            zqe = zqe_out;
                        }
                        {
                            double zqe_0_in = zqe;
                            double zqe_out;

                            ///////////////////
                            // Tasklet code (T_l826_c826)
                            zqe_out = max(0.0, zqe_0_in);
                            ///////////////////

                            zqe = zqe_out;
                        }
                    }
                } else {
                    {
                        {
                            int ydecldp_var_49_0_in_nssopt = v_ydecldp_var_49_nssopt[0];
                            int _if_cond_35_out;

                            ///////////////////
                            // Tasklet code (T_l827_c827)
                            _if_cond_35_out = (ydecldp_var_49_0_in_nssopt == 1);
                            ///////////////////

                            _if_cond_35 = _if_cond_35_out;
                        }
                    }
                    if ((_if_cond_35 == 1)) {
                        {
                            double tmp_call_42;
                            double tmp_arg_23;

                            {
                                double za_0_in_0 = za[((_for_it_46 + (sym_klon * (_for_it_23 - 1))) - 1)];
                                double tmp_arg_23_out;

                                ///////////////////
                                // Tasklet code (T_l828_c828)
                                tmp_arg_23_out = (1.0 - za_0_in_0);
                                ///////////////////

                                tmp_arg_23 = tmp_arg_23_out;
                            }
                            {
                                double tmp_arg_23_0_in = tmp_arg_23;
                                double zepsec_0_in = zepsec;
                                double tmp_call_42_out;

                                ///////////////////
                                // Tasklet code (T_l828_c828)
                                tmp_call_42_out = max(zepsec_0_in, tmp_arg_23_0_in);
                                ///////////////////

                                tmp_call_42 = tmp_call_42_out;
                            }
                            {
                                double tmp_call_42_0_in = tmp_call_42;
                                double za_0_in_0 = za[((_for_it_46 + (sym_klon * (_for_it_23 - 1))) - 1)];
                                double zqsice_0_in_0 = zqsice[((_for_it_46 + (sym_klon * (_for_it_23 - 1))) - 1)];
                                double zqx_0_in_0 = zqx[(((_for_it_46 + ((4 * sym_klev) * sym_klon)) + (sym_klon * (_for_it_23 - 1))) - 1)];
                                double zqe_out;

                                ///////////////////
                                // Tasklet code (T_l828_c828)
                                zqe_out = ((zqx_0_in_0 - (za_0_in_0 * zqsice_0_in_0)) / tmp_call_42_0_in);
                                ///////////////////

                                zqe = zqe_out;
                            }
                            {
                                double zqe_0_in = zqe;
                                double zqe_out;

                                ///////////////////
                                // Tasklet code (T_l829_c829)
                                zqe_out = max(0.0, zqe_0_in);
                                ///////////////////

                                zqe = zqe_out;
                            }
                        }
                    } else {
                        {
                            {
                                int ydecldp_var_49_0_in_nssopt = v_ydecldp_var_49_nssopt[0];
                                int _if_cond_36_out;

                                ///////////////////
                                // Tasklet code (T_l830_c830)
                                _if_cond_36_out = (ydecldp_var_49_0_in_nssopt == 2);
                                ///////////////////

                                _if_cond_36 = _if_cond_36_out;
                            }
                        }
                        if ((_if_cond_36 == 1)) {
                            {
                                {
                                    double zqx_0_in_0 = zqx[(((_for_it_46 + ((4 * sym_klev) * sym_klon)) + (sym_klon * (_for_it_23 - 1))) - 1)];
                                    double zqe_out;

                                    ///////////////////
                                    // Tasklet code (T_l831_c831)
                                    zqe_out = zqx_0_in_0;
                                    ///////////////////

                                    zqe = zqe_out;
                                }
                            }
                        } else {
                            {
                                {
                                    int ydecldp_var_49_0_in_nssopt = v_ydecldp_var_49_nssopt[0];
                                    int _if_cond_37_out;

                                    ///////////////////
                                    // Tasklet code (T_l832_c832)
                                    _if_cond_37_out = (ydecldp_var_49_0_in_nssopt == 3);
                                    ///////////////////

                                    _if_cond_37 = _if_cond_37_out;
                                }
                            }
                            if ((_if_cond_37 == 1)) {
                                {
                                    {
                                        double zli_0_in_0 = zli[((_for_it_46 + (sym_klon * (_for_it_23 - 1))) - 1)];
                                        double zqx_0_in_0 = zqx[(((_for_it_46 + ((4 * sym_klev) * sym_klon)) + (sym_klon * (_for_it_23 - 1))) - 1)];
                                        double zqe_out;

                                        ///////////////////
                                        // Tasklet code (T_l833_c833)
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
                        double ydcst_var_47_0_in_rtt = v_ydcst_var_47_rtt[0];
                        int ydecldp_var_49_0_in_nssopt = v_ydecldp_var_49_nssopt[0];
                        double ztp1_0_in_0 = ztp1[((_for_it_46 + (sym_klon * (_for_it_23 - 1))) - 1)];
                        double _if_cond_38_out;

                        ///////////////////
                        // Tasklet code (T_l0_c0)
                        _if_cond_38_out = ((ztp1_0_in_0 >= ydcst_var_47_0_in_rtt) || (ydecldp_var_49_0_in_nssopt == 0));
                        ///////////////////

                        _if_cond_38 = _if_cond_38_out;
                    }
                }
                if ((_if_cond_38 == 1)) {
                    zfac = 1.0;

                } else {
                    zfac = zfokoop[(_for_it_46 - 1)];
                }
                _if_cond_39 = ((zqe >= ((zrhc * zqsice[((_for_it_46 + (sym_klon * (_for_it_23 - 1))) - 1)]) * zfac)) && (zqe < (zqsice[((_for_it_46 + (sym_klon * (_for_it_23 - 1))) - 1)] * zfac)));
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
                            double zqsice_0_in_0 = zqsice[((_for_it_46 + (sym_klon * (_for_it_23 - 1))) - 1)];
                            double tmp_arg_24_out;

                            ///////////////////
                            // Tasklet code (T_l841_c841)
                            tmp_arg_24_out = (2.0 * ((zfac * zqsice_0_in_0) - zqe_0_in));
                            ///////////////////

                            tmp_arg_24 = tmp_arg_24_out;
                        }
                        {
                            double tmp_arg_24_0_in = tmp_arg_24;
                            double zepsec_0_in = zepsec;
                            double tmp_call_43_out;

                            ///////////////////
                            // Tasklet code (T_l841_c841)
                            tmp_call_43_out = max(tmp_arg_24_0_in, zepsec_0_in);
                            ///////////////////

                            tmp_call_43 = tmp_call_43_out;
                        }
                        {
                            double za_0_in_0 = za[((_for_it_46 + (sym_klon * (_for_it_23 - 1))) - 1)];
                            double tmp_arg_25_out;

                            ///////////////////
                            // Tasklet code (T_l842_c842)
                            tmp_arg_25_out = (1.0 - za_0_in_0);
                            ///////////////////

                            tmp_arg_25 = tmp_arg_25_out;
                        }
                        {
                            double tmp_call_43_0_in = tmp_call_43;
                            double za_0_in_0 = za[((_for_it_46 + (sym_klon * (_for_it_23 - 1))) - 1)];
                            double zdqs_0_in_0 = zdqs[(_for_it_46 - 1)];
                            double zacond_out;

                            ///////////////////
                            // Tasklet code (T_l841_c841)
                            zacond_out = (-((((1.0 - za_0_in_0) * zfac) * zdqs_0_in_0) / tmp_call_43_0_in));
                            ///////////////////

                            zacond = zacond_out;
                        }
                        {
                            double tmp_arg_25_0_in = tmp_arg_25;
                            double zacond_0_in = zacond;
                            double zacond_out;

                            ///////////////////
                            // Tasklet code (T_l842_c842)
                            zacond_out = min(zacond_0_in, tmp_arg_25_0_in);
                            ///////////////////

                            zacond = zacond_out;
                        }
                        {
                            double zacond_0_in = zacond;
                            double zdqs_0_in_0 = zdqs[(_for_it_46 - 1)];
                            double zlcond2_out_0;

                            ///////////////////
                            // Tasklet code (T_l843_c843)
                            zlcond2_out_0 = (-(((zfac * zdqs_0_in_0) * 0.5) * zacond_0_in));
                            ///////////////////

                            zlcond2[(_for_it_46 - 1)] = zlcond2_out_0;
                        }
                        {
                            double za_0_in_0 = za[((_for_it_46 + (sym_klon * (_for_it_23 - 1))) - 1)];
                            double tmp_arg_26_out;

                            ///////////////////
                            // Tasklet code (T_l844_c844)
                            tmp_arg_26_out = (1.0 - za_0_in_0);
                            ///////////////////

                            tmp_arg_26 = tmp_arg_26_out;
                        }
                        {
                            double tmp_arg_26_0_in = tmp_arg_26;
                            double zepsec_0_in = zepsec;
                            double tmp_call_44_out;

                            ///////////////////
                            // Tasklet code (T_l844_c844)
                            tmp_call_44_out = max(zepsec_0_in, tmp_arg_26_0_in);
                            ///////////////////

                            tmp_call_44 = tmp_call_44_out;
                        }
                        {
                            double tmp_call_44_0_in = tmp_call_44;
                            double zqe_0_in = zqe;
                            double zqsice_0_in_0 = zqsice[((_for_it_46 + (sym_klon * (_for_it_23 - 1))) - 1)];
                            double zzdl_out;

                            ///////////////////
                            // Tasklet code (T_l844_c844)
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
                            _if_cond_40_out = ((zfac * zdqs_0_in_0) < (-zzdl_0_in));
                            ///////////////////

                            _if_cond_40 = _if_cond_40_out;
                        }
                    }
                    if ((_if_cond_40 == 1)) {
                        {
                            double zlcondlim;
                            double tmp_call_45;

                            {
                                double za_0_in_0 = za[((_for_it_46 + (sym_klon * (_for_it_23 - 1))) - 1)];
                                double zdqs_0_in_0 = zdqs[(_for_it_46 - 1)];
                                double zqsice_0_in_0 = zqsice[((_for_it_46 + (sym_klon * (_for_it_23 - 1))) - 1)];
                                double zqx_0_in_0 = zqx[(((_for_it_46 + ((4 * sym_klev) * sym_klon)) + (sym_klon * (_for_it_23 - 1))) - 1)];
                                double zlcondlim_out;

                                ///////////////////
                                // Tasklet code (T_l846_c846)
                                zlcondlim_out = (((((za_0_in_0 - 1.0) * zfac) * zdqs_0_in_0) - (zfac * zqsice_0_in_0)) + zqx_0_in_0);
                                ///////////////////

                                zlcondlim = zlcondlim_out;
                            }
                            {
                                double zlcond2_0_in_0 = zlcond2[(_for_it_46 - 1)];
                                double zlcondlim_0_in = zlcondlim;
                                double tmp_call_45_out;

                                ///////////////////
                                // Tasklet code (T_l847_c847)
                                tmp_call_45_out = min(zlcond2_0_in_0, zlcondlim_0_in);
                                ///////////////////

                                tmp_call_45 = tmp_call_45_out;
                            }
                            {
                                double tmp_call_45_0_in = tmp_call_45;
                                double zlcond2_out_0;

                                ///////////////////
                                // Tasklet code (T_l847_c847)
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
                            // Tasklet code (T_l849_c849)
                            tmp_call_46_out = max(zlcond2_0_in_0, 0.0);
                            ///////////////////

                            tmp_call_46 = tmp_call_46_out;
                        }
                        {
                            double tmp_call_46_0_in = tmp_call_46;
                            double zlcond2_out_0;

                            ///////////////////
                            // Tasklet code (T_l849_c849)
                            zlcond2_out_0 = tmp_call_46_0_in;
                            ///////////////////

                            zlcond2[(_for_it_46 - 1)] = zlcond2_out_0;
                        }
                        {
                            double ydecldp_var_49_0_in_rlmin = v_ydecldp_var_49_rlmin[0];
                            double za_0_in_0 = za[((_for_it_46 + (sym_klon * (_for_it_23 - 1))) - 1)];
                            double zlcond2_0_in_0 = zlcond2[(_for_it_46 - 1)];
                            double _if_cond_41_out;

                            ///////////////////
                            // Tasklet code (T_l0_c0)
                            _if_cond_41_out = ((zlcond2_0_in_0 < ydecldp_var_49_0_in_rlmin) || ((1.0 - za_0_in_0) < 1e-14));
                            ///////////////////

                            _if_cond_41 = _if_cond_41_out;
                        }
                    }
                    if ((_if_cond_41 == 1)) {
                        {
                            {
                                double zlcond2_out_0;

                                ///////////////////
                                // Tasklet code (T_l851_c851)
                                zlcond2_out_0 = 0.0;
                                ///////////////////

                                zlcond2[(_for_it_46 - 1)] = zlcond2_out_0;
                            }
                            {
                                double zacond_out;

                                ///////////////////
                                // Tasklet code (T_l852_c852)
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
                                // Tasklet code (T_l854_c854)
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
                            // Tasklet code (T_l855_c855)
                            zsolac_out_0 = (zsolac_0_in_0 + zacond_0_in);
                            ///////////////////

                            zsolac[(_for_it_46 - 1)] = zsolac_out_0;
                        }
                        {
                            double ydecldp_var_49_0_in_rthomo = v_ydecldp_var_49_rthomo[0];
                            double ztp1_0_in_0 = ztp1[((_for_it_46 + (sym_klon * (_for_it_23 - 1))) - 1)];
                            double _if_cond_43_out;

                            ///////////////////
                            // Tasklet code (T_l0_c0)
                            _if_cond_43_out = (ztp1_0_in_0 > ydecldp_var_49_0_in_rthomo);
                            ///////////////////

                            _if_cond_43 = _if_cond_43_out;
                        }
                    }
                    if ((_if_cond_43 == 1)) {
                        {
                            {
                                double zlcond2_0_in_0 = zlcond2[(_for_it_46 - 1)];
                                double zsolqa_0_in_0 = zsolqa[((_for_it_46 + (20 * sym_klon)) - 1)];
                                double zsolqa_out_0;

                                ///////////////////
                                // Tasklet code (T_l857_c857)
                                zsolqa_out_0 = (zsolqa_0_in_0 + zlcond2_0_in_0);
                                ///////////////////

                                zsolqa[((_for_it_46 + (20 * sym_klon)) - 1)] = zsolqa_out_0;
                            }
                            {
                                double zlcond2_0_in_0 = zlcond2[(_for_it_46 - 1)];
                                double zsolqa_0_in_0 = zsolqa[((_for_it_46 + (4 * sym_klon)) - 1)];
                                double zsolqa_out_0;

                                ///////////////////
                                // Tasklet code (T_l858_c858)
                                zsolqa_out_0 = (zsolqa_0_in_0 - zlcond2_0_in_0);
                                ///////////////////

                                zsolqa[((_for_it_46 + (4 * sym_klon)) - 1)] = zsolqa_out_0;
                            }
                            {
                                double zlcond2_0_in_0 = zlcond2[(_for_it_46 - 1)];
                                double zqxfg_0_in_0 = zqxfg[(_for_it_46 - 1)];
                                double zqxfg_out_0;

                                ///////////////////
                                // Tasklet code (T_l859_c859)
                                zqxfg_out_0 = (zqxfg_0_in_0 + zlcond2_0_in_0);
                                ///////////////////

                                zqxfg[(_for_it_46 - 1)] = zqxfg_out_0;
                            }
                        }
                    } else {
                        {
                            {
                                double zlcond2_0_in_0 = zlcond2[(_for_it_46 - 1)];
                                double zsolqa_0_in_0 = zsolqa[((_for_it_46 + (21 * sym_klon)) - 1)];
                                double zsolqa_out_0;

                                ///////////////////
                                // Tasklet code (T_l861_c861)
                                zsolqa_out_0 = (zsolqa_0_in_0 + zlcond2_0_in_0);
                                ///////////////////

                                zsolqa[((_for_it_46 + (21 * sym_klon)) - 1)] = zsolqa_out_0;
                            }
                            {
                                double zlcond2_0_in_0 = zlcond2[(_for_it_46 - 1)];
                                double zsolqa_0_in_0 = zsolqa[((_for_it_46 + (9 * sym_klon)) - 1)];
                                double zsolqa_out_0;

                                ///////////////////
                                // Tasklet code (T_l862_c862)
                                zsolqa_out_0 = (zsolqa_0_in_0 - zlcond2_0_in_0);
                                ///////////////////

                                zsolqa[((_for_it_46 + (9 * sym_klon)) - 1)] = zsolqa_out_0;
                            }
                            {
                                double zlcond2_0_in_0 = zlcond2[(_for_it_46 - 1)];
                                double zqxfg_0_in_0 = zqxfg[((_for_it_46 + sym_klon) - 1)];
                                double zqxfg_out_0;

                                ///////////////////
                                // Tasklet code (T_l863_c863)
                                zqxfg_out_0 = (zqxfg_0_in_0 + zlcond2_0_in_0);
                                ///////////////////

                                zqxfg[((_for_it_46 + sym_klon) - 1)] = zqxfg_out_0;
                            }
                        }
                    }
                }
            }
        }
        for (_for_it_47 = 1; (_for_it_47 <= icend); _for_it_47 = (_for_it_47 + 1)) {
            {
                double* v_ydecldp_var_49_rcldtopcf;
                v_ydecldp_var_49_rcldtopcf = (double*)(&(ydecldp_var_49->rcldtopcf));

                {
                    double ydecldp_var_49_0_in_rcldtopcf = v_ydecldp_var_49_rcldtopcf[0];
                    double ydecldp_var_49_1_in_rcldtopcf = v_ydecldp_var_49_rcldtopcf[0];
                    double za_0_in_0 = za[((_for_it_47 + (sym_klon * (_for_it_23 - 2))) - 1)];
                    double za_1_in_0 = za[((_for_it_47 + (sym_klon * (_for_it_23 - 1))) - 1)];
                    double _if_cond_44_out;

                    ///////////////////
                    // Tasklet code (T_l0_c0)
                    _if_cond_44_out = ((za_0_in_0 < ydecldp_var_49_0_in_rcldtopcf) && (za_1_in_0 >= ydecldp_var_49_1_in_rcldtopcf));
                    ///////////////////

                    _if_cond_44 = _if_cond_44_out;
                }
            }
            if ((_if_cond_44 == 1)) {
                {
                    {
                        double zcldtopdist_out_0;

                        ///////////////////
                        // Tasklet code (T_l870_c870)
                        zcldtopdist_out_0 = 0.0;
                        ///////////////////

                        zcldtopdist[(_for_it_47 - 1)] = zcldtopdist_out_0;
                    }
                }
            } else {
                {
                    {
                        double ydcst_var_47_0_in_rg = v_ydcst_var_47_rg[0];
                        double zcldtopdist_0_in_0 = zcldtopdist[(_for_it_47 - 1)];
                        double zdp_0_in_0 = zdp[(_for_it_47 - 1)];
                        double zrho_0_in_0 = zrho[(_for_it_47 - 1)];
                        double zcldtopdist_out_0;

                        ///////////////////
                        // Tasklet code (T_l872_c872)
                        zcldtopdist_out_0 = (zcldtopdist_0_in_0 + (zdp_0_in_0 / (zrho_0_in_0 * ydcst_var_47_0_in_rg)));
                        ///////////////////

                        zcldtopdist[(_for_it_47 - 1)] = zcldtopdist_out_0;
                    }
                }
            }
            {
                {
                    double ydcst_var_47_0_in_rtt = v_ydcst_var_47_rtt[0];
                    double ydecldp_var_49_0_in_rlmin = v_ydecldp_var_49_rlmin[0];
                    double zqxfg_0_in_0 = zqxfg[(_for_it_47 - 1)];
                    double ztp1_0_in_0 = ztp1[((_for_it_47 + (sym_klon * (_for_it_23 - 1))) - 1)];
                    double _if_cond_45_out;

                    ///////////////////
                    // Tasklet code (T_l0_c0)
                    _if_cond_45_out = ((ztp1_0_in_0 < ydcst_var_47_0_in_rtt) && (zqxfg_0_in_0 > ydecldp_var_49_0_in_rlmin));
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
                        double ztp1_0_in_0 = ztp1[((_for_it_47 + (sym_klon * (_for_it_23 - 1))) - 1)];
                        double oka_out;

                        ///////////////////
                        // Tasklet code (T_l875_c875)
                        oka_out = ztp1_0_in_0;
                        ///////////////////

                        oka = oka_out;
                    }
                    {
                        double ptare_var_64_0_in = oka;
                        double ptare_var_64_1_in = oka;
                        double ydcst_var_66_0_in_rtt = v_ydcst_var_66_rtt[0];
                        double ydthf_var_65_0_in_r3ies = v_ydthf_var_65_r3ies[0];
                        double ydthf_var_65_1_in_r4ies = v_ydthf_var_65_r4ies[0];
                        double tmp_arg_72_out;

                        ///////////////////
                        // Tasklet code (T_l1403_c1403)
                        tmp_arg_72_out = ((ydthf_var_65_0_in_r3ies * (ptare_var_64_0_in - ydcst_var_66_0_in_rtt)) / (ptare_var_64_1_in - ydthf_var_65_1_in_r4ies));
                        ///////////////////

                        tmp_arg_72_0 = tmp_arg_72_out;
                    }
                    {
                        double tmp_arg_72_0_in = tmp_arg_72_0;
                        double tmp_call_118_out;

                        ///////////////////
                        // Tasklet code (T_l1403_c1403)
                        tmp_call_118_out = exp(tmp_arg_72_0_in);
                        ///////////////////

                        tmp_call_118_0 = tmp_call_118_out;
                    }
                    {
                        double tmp_call_118_0_in = tmp_call_118_0;
                        double ydthf_var_65_0_in_r2es = v_ydthf_var_65_r2es[0];
                        double foeeice__ret_out;

                        ///////////////////
                        // Tasklet code (T_l1403_c1403)
                        foeeice__ret_out = (ydthf_var_65_0_in_r2es * tmp_call_118_0_in);
                        ///////////////////

                        tmp_call_47 = foeeice__ret_out;
                    }
                    {
                        double tmp_call_47_0_in = tmp_call_47;
                        double ydcst_var_47_0_in_rv = v_ydcst_var_47_rv[0];
                        double ydcst_var_47_1_in_rd = v_ydcst_var_47_rd[0];
                        double zvpice_out;

                        ///////////////////
                        // Tasklet code (T_l876_c876)
                        zvpice_out = ((tmp_call_47_0_in * ydcst_var_47_0_in_rv) / ydcst_var_47_1_in_rd);
                        ///////////////////

                        zvpice = zvpice_out;
                    }
                    {
                        double zfokoop_0_in_0 = zfokoop[(_for_it_47 - 1)];
                        double zvpice_0_in = zvpice;
                        double zvpliq_out;

                        ///////////////////
                        // Tasklet code (T_l877_c877)
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
                        // Tasklet code (T_l878_c878)
                        tmp_arg_27_out = (((12.96 * (zvpliq_0_in - zvpice_0_in)) / zvpliq_1_in) - 0.639);
                        ///////////////////

                        tmp_arg_27 = tmp_arg_27_out;
                    }
                    {
                        double tmp_arg_27_0_in = tmp_arg_27;
                        double tmp_call_48_out;

                        ///////////////////
                        // Tasklet code (T_l878_c878)
                        tmp_call_48_out = exp(tmp_arg_27_0_in);
                        ///////////////////

                        tmp_call_48 = tmp_call_48_out;
                    }
                    {
                        double tmp_call_48_0_in = tmp_call_48;
                        double zicenuclei_out_0;

                        ///////////////////
                        // Tasklet code (T_l878_c878)
                        zicenuclei_out_0 = (1000.0 * tmp_call_48_0_in);
                        ///////////////////

                        zicenuclei[(_for_it_47 - 1)] = zicenuclei_out_0;
                    }
                    {
                        double ydcst_var_47_0_in_rlstt = v_ydcst_var_47_rlstt[0];
                        double ydcst_var_47_1_in_rlstt = v_ydcst_var_47_rlstt[0];
                        double ydcst_var_47_2_in_rv = v_ydcst_var_47_rv[0];
                        double ztp1_0_in_0 = ztp1[((_for_it_47 + (sym_klon * (_for_it_23 - 1))) - 1)];
                        double ztp1_1_in_0 = ztp1[((_for_it_47 + (sym_klon * (_for_it_23 - 1))) - 1)];
                        double zadd_out;

                        ///////////////////
                        // Tasklet code (T_l879_c879)
                        zadd_out = ((ydcst_var_47_0_in_rlstt * ((ydcst_var_47_1_in_rlstt / (ydcst_var_47_2_in_rv * ztp1_0_in_0)) - 1.0)) / (0.024 * ztp1_1_in_0));
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
                    double* v_ydecldp_var_49_riceinit;
                    v_ydecldp_var_49_riceinit = (double*)(&(ydecldp_var_49->riceinit));
                    double* v_ydecldp_var_49_rdepliqrefrate;
                    v_ydecldp_var_49_rdepliqrefrate = (double*)(&(ydecldp_var_49->rdepliqrefrate));
                    double* v_ydecldp_var_49_rdepliqrefdepth;
                    v_ydecldp_var_49_rdepliqrefdepth = (double*)(&(ydecldp_var_49->rdepliqrefdepth));

                    {
                        double pap_var_17_0_in_0 = pap_var_17[((_for_it_47 + (sym_klon * (_for_it_23 - 1))) - 1)];
                        double ydcst_var_47_0_in_rv = v_ydcst_var_47_rv[0];
                        double ztp1_0_in_0 = ztp1[((_for_it_47 + (sym_klon * (_for_it_23 - 1))) - 1)];
                        double zvpice_0_in = zvpice;
                        double zbdd_out;

                        ///////////////////
                        // Tasklet code (T_l880_c880)
                        zbdd_out = (((ydcst_var_47_0_in_rv * ztp1_0_in_0) * pap_var_17_0_in_0) / (2.21 * zvpice_0_in));
                        ///////////////////

                        zbdd = zbdd_out;
                    }
                    {
                        double zicenuclei_0_in_0 = zicenuclei[(_for_it_47 - 1)];
                        double tmp_arg_32_out;

                        ///////////////////
                        // Tasklet code (T_l886_c886)
                        tmp_arg_32_out = (zicenuclei_0_in_0 / 15000.0);
                        ///////////////////

                        tmp_arg_32 = tmp_arg_32_out;
                    }
                    {
                        double tmp_arg_32_0_in = tmp_arg_32;
                        double zinfactor_out;

                        ///////////////////
                        // Tasklet code (T_l886_c886)
                        zinfactor_out = min(tmp_arg_32_0_in, 1.0);
                        ///////////////////

                        zinfactor = zinfactor_out;
                    }
                    {
                        double zicenuclei_0_in_0 = zicenuclei[(_for_it_47 - 1)];
                        double zrho_0_in_0 = zrho[(_for_it_47 - 1)];
                        double tmp_arg_28_out;

                        ///////////////////
                        // Tasklet code (T_l881_c881)
                        tmp_arg_28_out = (zicenuclei_0_in_0 / zrho_0_in_0);
                        ///////////////////

                        tmp_arg_28 = tmp_arg_28_out;
                    }
                    {
                        double tmp_arg_28_0_in = tmp_arg_28;
                        double tmp_call_49_out;

                        ///////////////////
                        // Tasklet code (T_l881_c881)
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
                        // Tasklet code (T_l881_c881)
                        zcvds_out = (((7.8 * tmp_call_49_0_in) * (zvpliq_0_in - zvpice_0_in)) / ((8.87 * (zadd_0_in + zbdd_0_in)) * zvpice_1_in));
                        ///////////////////

                        zcvds = zcvds_out;
                    }
                    {
                        double ydecldp_var_49_0_in_riceinit = v_ydecldp_var_49_riceinit[0];
                        double zicenuclei_0_in_0 = zicenuclei[(_for_it_47 - 1)];
                        double zrho_0_in_0 = zrho[(_for_it_47 - 1)];
                        double tmp_arg_29_out;

                        ///////////////////
                        // Tasklet code (T_l882_c882)
                        tmp_arg_29_out = ((zicenuclei_0_in_0 * ydecldp_var_49_0_in_riceinit) / zrho_0_in_0);
                        ///////////////////

                        tmp_arg_29 = tmp_arg_29_out;
                    }
                    {
                        double tmp_arg_29_0_in = tmp_arg_29;
                        double zicecld_0_in_0 = zicecld[(_for_it_47 - 1)];
                        double zice0_out;

                        ///////////////////
                        // Tasklet code (T_l882_c882)
                        zice0_out = max(zicecld_0_in_0, tmp_arg_29_0_in);
                        ///////////////////

                        zice0 = zice0_out;
                    }
                    {
                        double zice0_0_in = zice0;
                        double tmp_call_50_out;

                        ///////////////////
                        // Tasklet code (T_l883_c883)
                        tmp_call_50_out = dace::math::pow(zice0_0_in, 0.666);
                        ///////////////////

                        tmp_call_50 = tmp_call_50_out;
                    }
                    {
                        double ptsphy_var_5_0_in = ptsphy_var_5[0];
                        double tmp_call_50_0_in = tmp_call_50;
                        double zcvds_0_in = zcvds;
                        double tmp_arg_30_out;

                        ///////////////////
                        // Tasklet code (T_l883_c883)
                        tmp_arg_30_out = (((0.666 * zcvds_0_in) * ptsphy_var_5_0_in) + tmp_call_50_0_in);
                        ///////////////////

                        tmp_arg_30 = tmp_arg_30_out;
                    }
                    {
                        double tmp_arg_30_0_in = tmp_arg_30;
                        double zinew_out;

                        ///////////////////
                        // Tasklet code (T_l883_c883)
                        zinew_out = dace::math::pow(tmp_arg_30_0_in, 1.5);
                        ///////////////////

                        zinew = zinew_out;
                    }
                    {
                        double za_0_in_0 = za[((_for_it_47 + (sym_klon * (_for_it_23 - 1))) - 1)];
                        double zice0_0_in = zice0;
                        double zinew_0_in = zinew;
                        double tmp_arg_31_out;

                        ///////////////////
                        // Tasklet code (T_l884_c884)
                        tmp_arg_31_out = (za_0_in_0 * (zinew_0_in - zice0_0_in));
                        ///////////////////

                        tmp_arg_31 = tmp_arg_31_out;
                    }
                    {
                        double tmp_arg_31_0_in = tmp_arg_31;
                        double zdepos_out;

                        ///////////////////
                        // Tasklet code (T_l884_c884)
                        zdepos_out = max(tmp_arg_31_0_in, 0.0);
                        ///////////////////

                        zdepos = zdepos_out;
                    }
                    {
                        double zdepos_0_in = zdepos;
                        double zqxfg_0_in_0 = zqxfg[(_for_it_47 - 1)];
                        double zdepos_out;

                        ///////////////////
                        // Tasklet code (T_l885_c885)
                        zdepos_out = min(zdepos_0_in, zqxfg_0_in_0);
                        ///////////////////

                        zdepos = zdepos_out;
                    }
                    {
                        double ydecldp_var_49_0_in_rdepliqrefrate = v_ydecldp_var_49_rdepliqrefrate[0];
                        double ydecldp_var_49_1_in_rdepliqrefdepth = v_ydecldp_var_49_rdepliqrefdepth[0];
                        double zcldtopdist_0_in_0 = zcldtopdist[(_for_it_47 - 1)];
                        double zinfactor_0_in = zinfactor;
                        double zinfactor_1_in = zinfactor;
                        double tmp_arg_33_out;

                        ///////////////////
                        // Tasklet code (T_l887_c887)
                        tmp_arg_33_out = (zinfactor_0_in + ((1.0 - zinfactor_1_in) * (ydecldp_var_49_0_in_rdepliqrefrate + (zcldtopdist_0_in_0 / ydecldp_var_49_1_in_rdepliqrefdepth))));
                        ///////////////////

                        tmp_arg_33 = tmp_arg_33_out;
                    }
                    {
                        double tmp_arg_33_0_in = tmp_arg_33;
                        double tmp_call_51_out;

                        ///////////////////
                        // Tasklet code (T_l887_c887)
                        tmp_call_51_out = min(tmp_arg_33_0_in, 1.0);
                        ///////////////////

                        tmp_call_51 = tmp_call_51_out;
                    }
                    {
                        double tmp_call_51_0_in = tmp_call_51;
                        double zdepos_0_in = zdepos;
                        double zdepos_out;

                        ///////////////////
                        // Tasklet code (T_l887_c887)
                        zdepos_out = (zdepos_0_in * tmp_call_51_0_in);
                        ///////////////////

                        zdepos = zdepos_out;
                    }
                    {
                        double zdepos_0_in = zdepos;
                        double zqxfg_0_in_0 = zqxfg[((_for_it_47 + sym_klon) - 1)];
                        double zqxfg_out_0;

                        ///////////////////
                        // Tasklet code (T_l890_c890)
                        zqxfg_out_0 = (zqxfg_0_in_0 + zdepos_0_in);
                        ///////////////////

                        zqxfg[((_for_it_47 + sym_klon) - 1)] = zqxfg_out_0;
                    }
                    {
                        double zdepos_0_in = zdepos;
                        double zqxfg_0_in_0 = zqxfg[(_for_it_47 - 1)];
                        double zqxfg_out_0;

                        ///////////////////
                        // Tasklet code (T_l891_c891)
                        zqxfg_out_0 = (zqxfg_0_in_0 - zdepos_0_in);
                        ///////////////////

                        zqxfg[(_for_it_47 - 1)] = zqxfg_out_0;
                    }
                    {
                        double zdepos_0_in = zdepos;
                        double zsolqa_0_in_0 = zsolqa[((_for_it_47 + sym_klon) - 1)];
                        double zsolqa_out_0;

                        ///////////////////
                        // Tasklet code (T_l888_c888)
                        zsolqa_out_0 = (zsolqa_0_in_0 + zdepos_0_in);
                        ///////////////////

                        zsolqa[((_for_it_47 + sym_klon) - 1)] = zsolqa_out_0;
                    }
                    {
                        double zdepos_0_in = zdepos;
                        double zsolqa_0_in_0 = zsolqa[((_for_it_47 + (5 * sym_klon)) - 1)];
                        double zsolqa_out_0;

                        ///////////////////
                        // Tasklet code (T_l889_c889)
                        zsolqa_out_0 = (zsolqa_0_in_0 - zdepos_0_in);
                        ///////////////////

                        zsolqa[((_for_it_47 + (5 * sym_klon)) - 1)] = zsolqa_out_0;
                    }
                }
            }
        }
        for (_for_it_48 = 1; (_for_it_48 <= icend); _for_it_48 = (_for_it_48 + 1)) {
            {
                double tmp_call_52;

                {
                    double za_0_in_0 = za[((_for_it_48 + (sym_klon * (_for_it_23 - 1))) - 1)];
                    double zepsec_0_in = zepsec;
                    double tmp_call_52_out;

                    ///////////////////
                    // Tasklet code (T_l895_c895)
                    tmp_call_52_out = max(za_0_in_0, zepsec_0_in);
                    ///////////////////

                    tmp_call_52 = tmp_call_52_out;
                }
                {
                    double tmp_call_52_0_in = tmp_call_52;
                    double ztmpa_out;

                    ///////////////////
                    // Tasklet code (T_l895_c895)
                    ztmpa_out = (1.0 / tmp_call_52_0_in);
                    ///////////////////

                    ztmpa = ztmpa_out;
                }
                {
                    double zqxfg_0_in_0 = zqxfg[(_for_it_48 - 1)];
                    double ztmpa_0_in = ztmpa;
                    double zliqcld_out_0;

                    ///////////////////
                    // Tasklet code (T_l896_c896)
                    zliqcld_out_0 = (zqxfg_0_in_0 * ztmpa_0_in);
                    ///////////////////

                    zliqcld[(_for_it_48 - 1)] = zliqcld_out_0;
                }
                {
                    double zqxfg_0_in_0 = zqxfg[((_for_it_48 + sym_klon) - 1)];
                    double ztmpa_0_in = ztmpa;
                    double zicecld_out_0;

                    ///////////////////
                    // Tasklet code (T_l897_c897)
                    zicecld_out_0 = (zqxfg_0_in_0 * ztmpa_0_in);
                    ///////////////////

                    zicecld[(_for_it_48 - 1)] = zicecld_out_0;
                }
                {
                    double zicecld_0_in_0 = zicecld[(_for_it_48 - 1)];
                    double zliqcld_0_in_0 = zliqcld[(_for_it_48 - 1)];
                    double zlicld_out_0;

                    ///////////////////
                    // Tasklet code (T_l898_c898)
                    zlicld_out_0 = (zliqcld_0_in_0 + zicecld_0_in_0);
                    ///////////////////

                    zlicld[(_for_it_48 - 1)] = zlicld_out_0;
                }
            }
        }
        for (_for_it_49 = 1; (_for_it_49 <= 5); _for_it_49 = (_for_it_49 + 1)) {
            _if_cond_46 = (llfall[(_for_it_49 - 1)] || (_for_it_49 == 2));
            if ((_if_cond_46 == 1)) {
                for (_for_it_50 = 1; (_for_it_50 <= icend); _for_it_50 = (_for_it_50 + 1)) {
                    {
                        {
                            int ydecldp_var_49_0_in_ncldtop = v_ydecldp_var_49_ncldtop[0];
                            int _if_cond_47_out;

                            ///////////////////
                            // Tasklet code (T_l0_c0)
                            _if_cond_47_out = (_for_it_23 > ydecldp_var_49_0_in_ncldtop);
                            ///////////////////

                            _if_cond_47 = _if_cond_47_out;
                        }
                    }
                    if ((_if_cond_47 == 1)) {
                        {
                            {
                                double zdtgdp_0_in_0 = zdtgdp[(_for_it_50 - 1)];
                                double zpfplsx_0_in_0 = zpfplsx[(((_for_it_50 + (sym_klon * (_for_it_23 - 1))) + ((sym_klon * (_for_it_49 - 1)) * (sym_klev + 1))) - 1)];
                                double zfallsrce_out_0;

                                ///////////////////
                                // Tasklet code (T_l904_c904)
                                zfallsrce_out_0 = (zpfplsx_0_in_0 * zdtgdp_0_in_0);
                                ///////////////////

                                zfallsrce[((_for_it_50 + (sym_klon * (_for_it_49 - 1))) - 1)] = zfallsrce_out_0;
                            }
                            {
                                double zfallsrce_0_in_0 = zfallsrce[((_for_it_50 + (sym_klon * (_for_it_49 - 1))) - 1)];
                                double zsolqa_0_in_0 = zsolqa[((_for_it_50 + ((6 * sym_klon) * (_for_it_49 - 1))) - 1)];
                                double zsolqa_out_0;

                                ///////////////////
                                // Tasklet code (T_l905_c905)
                                zsolqa_out_0 = (zsolqa_0_in_0 + zfallsrce_0_in_0);
                                ///////////////////

                                zsolqa[((_for_it_50 + ((6 * sym_klon) * (_for_it_49 - 1))) - 1)] = zsolqa_out_0;
                            }
                            {
                                double zfallsrce_0_in_0 = zfallsrce[((_for_it_50 + (sym_klon * (_for_it_49 - 1))) - 1)];
                                double zqxfg_0_in_0 = zqxfg[((_for_it_50 + (sym_klon * (_for_it_49 - 1))) - 1)];
                                double zqxfg_out_0;

                                ///////////////////
                                // Tasklet code (T_l906_c906)
                                zqxfg_out_0 = (zqxfg_0_in_0 + zfallsrce_0_in_0);
                                ///////////////////

                                zqxfg[((_for_it_50 + (sym_klon * (_for_it_49 - 1))) - 1)] = zqxfg_out_0;
                            }
                            {
                                double zqpretot_0_in_0 = zqpretot[(_for_it_50 - 1)];
                                double zqxfg_0_in_0 = zqxfg[((_for_it_50 + (sym_klon * (_for_it_49 - 1))) - 1)];
                                double zqpretot_out_0;

                                ///////////////////
                                // Tasklet code (T_l907_c907)
                                zqpretot_out_0 = (zqpretot_0_in_0 + zqxfg_0_in_0);
                                ///////////////////

                                zqpretot[(_for_it_50 - 1)] = zqpretot_out_0;
                            }
                        }
                    }
                    {
                        int* v_ydecldp_var_49_laericesed;
                        v_ydecldp_var_49_laericesed = (int*)(&(ydecldp_var_49->laericesed));

                        {
                            int ydecldp_var_49_0_in_laericesed = v_ydecldp_var_49_laericesed[0];
                            int _if_cond_48_out;

                            ///////////////////
                            // Tasklet code (T_l0_c0)
                            _if_cond_48_out = (ydecldp_var_49_0_in_laericesed && (_for_it_49 == 2));
                            ///////////////////

                            _if_cond_48 = _if_cond_48_out;
                        }
                    }
                    if ((_if_cond_48 == 1)) {
                        {
                            double zre_ice;
                            double tmp_call_53;

                            {
                                double pre_ice_var_2_0_in_0 = pre_ice_var_2[((_for_it_50 + (sym_klon * (_for_it_23 - 1))) - 1)];
                                double zre_ice_out;

                                ///////////////////
                                // Tasklet code (T_l910_c910)
                                zre_ice_out = pre_ice_var_2_0_in_0;
                                ///////////////////

                                zre_ice = zre_ice_out;
                            }
                            {
                                double zre_ice_0_in = zre_ice;
                                double tmp_call_53_out;

                                ///////////////////
                                // Tasklet code (T_l911_c911)
                                tmp_call_53_out = (dace::math::ipow(zre_ice_0_in, 1));
                                ///////////////////

                                tmp_call_53 = tmp_call_53_out;
                            }
                            {
                                double tmp_call_53_0_in = tmp_call_53;
                                double zvqx_out_0;

                                ///////////////////
                                // Tasklet code (T_l911_c911)
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
                            // Tasklet code (T_l913_c913)
                            zfall_out = (zvqx_0_in_0 * zrho_0_in_0);
                            ///////////////////

                            zfall = zfall_out;
                        }
                        {
                            double zdtgdp_0_in_0 = zdtgdp[(_for_it_50 - 1)];
                            double zfall_0_in = zfall;
                            double zfallsink_out_0;

                            ///////////////////
                            // Tasklet code (T_l914_c914)
                            zfallsink_out_0 = (zdtgdp_0_in_0 * zfall_0_in);
                            ///////////////////

                            zfallsink[((_for_it_50 + (sym_klon * (_for_it_49 - 1))) - 1)] = zfallsink_out_0;
                        }
                    }
                }
            }
        }
        for (_for_it_51 = 1; (_for_it_51 <= icend); _for_it_51 = (_for_it_51 + 1)) {
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
                        double za_0_in_0 = za[((_for_it_51 + (sym_klon * (_for_it_23 - 2))) - 1)];
                        double tmp_call_55_out;

                        ///////////////////
                        // Tasklet code (T_l920_c920)
                        tmp_call_55_out = min(za_0_in_0, 0.999999);
                        ///////////////////

                        tmp_call_55 = tmp_call_55_out;
                    }
                    {
                        double za_0_in_0 = za[((_for_it_51 + (sym_klon * (_for_it_23 - 1))) - 1)];
                        double za_1_in_0 = za[((_for_it_51 + (sym_klon * (_for_it_23 - 2))) - 1)];
                        double tmp_call_54_out;

                        ///////////////////
                        // Tasklet code (T_l920_c920)
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
                        // Tasklet code (T_l920_c920)
                        zcovptot_out_0 = (1.0 - (((1.0 - zcovptot_0_in_0) * (1.0 - tmp_call_54_0_in)) / (1.0 - tmp_call_55_0_in)));
                        ///////////////////

                        zcovptot[(_for_it_51 - 1)] = zcovptot_out_0;
                    }
                    {
                        double ydecldp_var_49_0_in_rcovpmin = v_ydecldp_var_49_rcovpmin[0];
                        double zcovptot_0_in_0 = zcovptot[(_for_it_51 - 1)];
                        double tmp_call_56_out;

                        ///////////////////
                        // Tasklet code (T_l921_c921)
                        tmp_call_56_out = max(zcovptot_0_in_0, ydecldp_var_49_0_in_rcovpmin);
                        ///////////////////

                        tmp_call_56 = tmp_call_56_out;
                    }
                    {
                        double tmp_call_56_0_in = tmp_call_56;
                        double zcovptot_out_0;

                        ///////////////////
                        // Tasklet code (T_l921_c921)
                        zcovptot_out_0 = tmp_call_56_0_in;
                        ///////////////////

                        zcovptot[(_for_it_51 - 1)] = zcovptot_out_0;
                    }
                    {
                        double za_0_in_0 = za[((_for_it_51 + (sym_klon * (_for_it_23 - 1))) - 1)];
                        double zcovptot_0_in_0 = zcovptot[(_for_it_51 - 1)];
                        double tmp_arg_34_out;

                        ///////////////////
                        // Tasklet code (T_l922_c922)
                        tmp_arg_34_out = (zcovptot_0_in_0 - za_0_in_0);
                        ///////////////////

                        tmp_arg_34 = tmp_arg_34_out;
                    }
                    {
                        double tmp_arg_34_0_in = tmp_arg_34;
                        double tmp_call_57_out;

                        ///////////////////
                        // Tasklet code (T_l922_c922)
                        tmp_call_57_out = max(0.0, tmp_arg_34_0_in);
                        ///////////////////

                        tmp_call_57 = tmp_call_57_out;
                    }
                    {
                        double tmp_call_57_0_in = tmp_call_57;
                        double zcovpclr_out_0;

                        ///////////////////
                        // Tasklet code (T_l922_c922)
                        zcovpclr_out_0 = tmp_call_57_0_in;
                        ///////////////////

                        zcovpclr[(_for_it_51 - 1)] = zcovpclr_out_0;
                    }
                    {
                        double zcovptot_0_in_0 = zcovptot[(_for_it_51 - 1)];
                        double zqxfg_0_in_0 = zqxfg[((_for_it_51 + (2 * sym_klon)) - 1)];
                        double zraincld_out_0;

                        ///////////////////
                        // Tasklet code (T_l923_c923)
                        zraincld_out_0 = (zqxfg_0_in_0 / zcovptot_0_in_0);
                        ///////////////////

                        zraincld[(_for_it_51 - 1)] = zraincld_out_0;
                    }
                    {
                        double zcovptot_0_in_0 = zcovptot[(_for_it_51 - 1)];
                        double zqxfg_0_in_0 = zqxfg[((_for_it_51 + (3 * sym_klon)) - 1)];
                        double zsnowcld_out_0;

                        ///////////////////
                        // Tasklet code (T_l924_c924)
                        zsnowcld_out_0 = (zqxfg_0_in_0 / zcovptot_0_in_0);
                        ///////////////////

                        zsnowcld[(_for_it_51 - 1)] = zsnowcld_out_0;
                    }
                    {
                        double zcovpmax_0_in_0 = zcovpmax[(_for_it_51 - 1)];
                        double zcovptot_0_in_0 = zcovptot[(_for_it_51 - 1)];
                        double tmp_call_58_out;

                        ///////////////////
                        // Tasklet code (T_l925_c925)
                        tmp_call_58_out = max(zcovptot_0_in_0, zcovpmax_0_in_0);
                        ///////////////////

                        tmp_call_58 = tmp_call_58_out;
                    }
                    {
                        double tmp_call_58_0_in = tmp_call_58;
                        double zcovpmax_out_0;

                        ///////////////////
                        // Tasklet code (T_l925_c925)
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
                        // Tasklet code (T_l927_c927)
                        zraincld_out_0 = 0.0;
                        ///////////////////

                        zraincld[(_for_it_51 - 1)] = zraincld_out_0;
                    }
                    {
                        double zsnowcld_out_0;

                        ///////////////////
                        // Tasklet code (T_l928_c928)
                        zsnowcld_out_0 = 0.0;
                        ///////////////////

                        zsnowcld[(_for_it_51 - 1)] = zsnowcld_out_0;
                    }
                    {
                        double zcovptot_out_0;

                        ///////////////////
                        // Tasklet code (T_l929_c929)
                        zcovptot_out_0 = 0.0;
                        ///////////////////

                        zcovptot[(_for_it_51 - 1)] = zcovptot_out_0;
                    }
                    {
                        double zcovpclr_out_0;

                        ///////////////////
                        // Tasklet code (T_l930_c930)
                        zcovpclr_out_0 = 0.0;
                        ///////////////////

                        zcovpclr[(_for_it_51 - 1)] = zcovpclr_out_0;
                    }
                    {
                        double zcovpmax_out_0;

                        ///////////////////
                        // Tasklet code (T_l931_c931)
                        zcovpmax_out_0 = 0.0;
                        ///////////////////

                        zcovpmax[(_for_it_51 - 1)] = zcovpmax_out_0;
                    }
                }
            }
        }
        for (_for_it_52 = 1; (_for_it_52 <= icend); _for_it_52 = (_for_it_52 + 1)) {
            {
                {
                    double ydcst_var_47_0_in_rtt = v_ydcst_var_47_rtt[0];
                    double ztp1_0_in_0 = ztp1[((_for_it_52 + (sym_klon * (_for_it_23 - 1))) - 1)];
                    double _if_cond_50_out;

                    ///////////////////
                    // Tasklet code (T_l0_c0)
                    _if_cond_50_out = (ztp1_0_in_0 <= ydcst_var_47_0_in_rtt);
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
                        double* v_ydecldp_var_49_rsnowlin2;
                        v_ydecldp_var_49_rsnowlin2 = (double*)(&(ydecldp_var_49->rsnowlin2));
                        double* v_ydecldp_var_49_rsnowlin1;
                        v_ydecldp_var_49_rsnowlin1 = (double*)(&(ydecldp_var_49->rsnowlin1));
                        int* v_ydecldp_var_49_laericeauto;
                        v_ydecldp_var_49_laericeauto = (int*)(&(ydecldp_var_49->laericeauto));

                        {
                            int ydecldp_var_49_0_in_laericeauto = v_ydecldp_var_49_laericeauto[0];
                            int _if_cond_52_out;

                            ///////////////////
                            // Tasklet code (T_l0_c0)
                            _if_cond_52_out = ydecldp_var_49_0_in_laericeauto;
                            ///////////////////

                            _if_cond_52 = _if_cond_52_out;
                        }
                        {
                            double ydcst_var_47_0_in_rtt = v_ydcst_var_47_rtt[0];
                            double ydecldp_var_49_0_in_rsnowlin2 = v_ydecldp_var_49_rsnowlin2[0];
                            double ztp1_0_in_0 = ztp1[((_for_it_52 + (sym_klon * (_for_it_23 - 1))) - 1)];
                            double tmp_arg_35_out;

                            ///////////////////
                            // Tasklet code (T_l937_c937)
                            tmp_arg_35_out = (ydecldp_var_49_0_in_rsnowlin2 * (ztp1_0_in_0 - ydcst_var_47_0_in_rtt));
                            ///////////////////

                            tmp_arg_35 = tmp_arg_35_out;
                        }
                        {
                            double tmp_arg_35_0_in = tmp_arg_35;
                            double tmp_call_59_out;

                            ///////////////////
                            // Tasklet code (T_l937_c937)
                            tmp_call_59_out = exp(tmp_arg_35_0_in);
                            ///////////////////

                            tmp_call_59 = tmp_call_59_out;
                        }
                        {
                            double ptsphy_var_5_0_in = ptsphy_var_5[0];
                            double tmp_call_59_0_in = tmp_call_59;
                            double ydecldp_var_49_0_in_rsnowlin1 = v_ydecldp_var_49_rsnowlin1[0];
                            double zzco_out;

                            ///////////////////
                            // Tasklet code (T_l937_c937)
                            zzco_out = ((ptsphy_var_5_0_in * ydecldp_var_49_0_in_rsnowlin1) * tmp_call_59_0_in);
                            ///////////////////

                            zzco = zzco_out;
                        }
                    }
                    if ((_if_cond_52 == 1)) {
                        {
                            double tmp_call_60;
                            double tmp_arg_36;
                            double* v_ydecldp_var_49_rnice;
                            v_ydecldp_var_49_rnice = (double*)(&(ydecldp_var_49->rnice));

                            {
                                double picrit_aer_var_1_0_in_0 = picrit_aer_var_1[((_for_it_52 + (sym_klon * (_for_it_23 - 1))) - 1)];
                                double zlcrit_out;

                                ///////////////////
                                // Tasklet code (T_l939_c939)
                                zlcrit_out = picrit_aer_var_1_0_in_0;
                                ///////////////////

                                zlcrit = zlcrit_out;
                            }
                            {
                                double pnice_var_4_0_in_0 = pnice_var_4[((_for_it_52 + (sym_klon * (_for_it_23 - 1))) - 1)];
                                double ydecldp_var_49_0_in_rnice = v_ydecldp_var_49_rnice[0];
                                double tmp_arg_36_out;

                                ///////////////////
                                // Tasklet code (T_l940_c940)
                                tmp_arg_36_out = (ydecldp_var_49_0_in_rnice / pnice_var_4_0_in_0);
                                ///////////////////

                                tmp_arg_36 = tmp_arg_36_out;
                            }
                            {
                                double tmp_arg_36_0_in = tmp_arg_36;
                                double tmp_call_60_out;

                                ///////////////////
                                // Tasklet code (T_l940_c940)
                                tmp_call_60_out = dace::math::pow(tmp_arg_36_0_in, 0.333);
                                ///////////////////

                                tmp_call_60 = tmp_call_60_out;
                            }
                            {
                                double tmp_call_60_0_in = tmp_call_60;
                                double zzco_0_in = zzco;
                                double zzco_out;

                                ///////////////////
                                // Tasklet code (T_l940_c940)
                                zzco_out = (zzco_0_in * tmp_call_60_0_in);
                                ///////////////////

                                zzco = zzco_out;
                            }
                        }
                    } else {
                        {
                            double* v_ydecldp_var_49_rlcritsnow;
                            v_ydecldp_var_49_rlcritsnow = (double*)(&(ydecldp_var_49->rlcritsnow));

                            {
                                double ydecldp_var_49_0_in_rlcritsnow = v_ydecldp_var_49_rlcritsnow[0];
                                double zlcrit_out;

                                ///////////////////
                                // Tasklet code (T_l942_c942)
                                zlcrit_out = ydecldp_var_49_0_in_rlcritsnow;
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
                            // Tasklet code (T_l944_c944)
                            tmp_arg_37_out = (zicecld_0_in_0 / zlcrit_0_in);
                            ///////////////////

                            tmp_arg_37 = tmp_arg_37_out;
                        }
                        {
                            double tmp_arg_37_0_in = tmp_arg_37;
                            double tmp_call_62_out;

                            ///////////////////
                            // Tasklet code (T_l944_c944)
                            tmp_call_62_out = (dace::math::ipow(tmp_arg_37_0_in, 2));
                            ///////////////////

                            tmp_call_62 = tmp_call_62_out;
                        }
                        {
                            double tmp_call_62_0_in = tmp_call_62;
                            double tmp_arg_38_out;

                            ///////////////////
                            // Tasklet code (T_l944_c944)
                            tmp_arg_38_out = (-tmp_call_62_0_in);
                            ///////////////////

                            tmp_arg_38 = tmp_arg_38_out;
                        }
                        {
                            double tmp_arg_38_0_in = tmp_arg_38;
                            double tmp_call_61_out;

                            ///////////////////
                            // Tasklet code (T_l944_c944)
                            tmp_call_61_out = exp(tmp_arg_38_0_in);
                            ///////////////////

                            tmp_call_61 = tmp_call_61_out;
                        }
                        {
                            double tmp_call_61_0_in = tmp_call_61;
                            double zzco_0_in = zzco;
                            double zsnowaut_out_0;

                            ///////////////////
                            // Tasklet code (T_l944_c944)
                            zsnowaut_out_0 = (zzco_0_in * (1.0 - tmp_call_61_0_in));
                            ///////////////////

                            zsnowaut[(_for_it_52 - 1)] = zsnowaut_out_0;
                        }
                        {
                            double zsnowaut_0_in_0 = zsnowaut[(_for_it_52 - 1)];
                            double zsolqb_0_in_0 = zsolqb[((_for_it_52 + (8 * sym_klon)) - 1)];
                            double zsolqb_out_0;

                            ///////////////////
                            // Tasklet code (T_l945_c945)
                            zsolqb_out_0 = (zsolqb_0_in_0 + zsnowaut_0_in_0);
                            ///////////////////

                            zsolqb[((_for_it_52 + (8 * sym_klon)) - 1)] = zsolqb_out_0;
                        }
                    }
                }
            }
            _if_cond_53 = (zliqcld[(_for_it_52 - 1)] > 1e-14);
            if ((_if_cond_53 == 1)) {
                _if_cond_54 = (plsm_var_19[(_for_it_52 - 1)] > 0.5);
                if ((_if_cond_54 == 1)) {
                    {
                        double* v_ydecldp_var_49_rcl_kk_cloud_num_land;
                        v_ydecldp_var_49_rcl_kk_cloud_num_land = (double*)(&(ydecldp_var_49->rcl_kk_cloud_num_land));
                        double* v_ydecldp_var_49_rclcrit_land;
                        v_ydecldp_var_49_rclcrit_land = (double*)(&(ydecldp_var_49->rclcrit_land));

                        {
                            double ydecldp_var_49_0_in_rcl_kk_cloud_num_land = v_ydecldp_var_49_rcl_kk_cloud_num_land[0];
                            double zconst_out;

                            ///////////////////
                            // Tasklet code (T_l950_c950)
                            zconst_out = ydecldp_var_49_0_in_rcl_kk_cloud_num_land;
                            ///////////////////

                            zconst = zconst_out;
                        }
                        {
                            double ydecldp_var_49_0_in_rclcrit_land = v_ydecldp_var_49_rclcrit_land[0];
                            double zlcrit_out;

                            ///////////////////
                            // Tasklet code (T_l951_c951)
                            zlcrit_out = ydecldp_var_49_0_in_rclcrit_land;
                            ///////////////////

                            zlcrit = zlcrit_out;
                        }
                    }
                } else {
                    {
                        double* v_ydecldp_var_49_rcl_kk_cloud_num_sea;
                        v_ydecldp_var_49_rcl_kk_cloud_num_sea = (double*)(&(ydecldp_var_49->rcl_kk_cloud_num_sea));
                        double* v_ydecldp_var_49_rclcrit_sea;
                        v_ydecldp_var_49_rclcrit_sea = (double*)(&(ydecldp_var_49->rclcrit_sea));

                        {
                            double ydecldp_var_49_0_in_rcl_kk_cloud_num_sea = v_ydecldp_var_49_rcl_kk_cloud_num_sea[0];
                            double zconst_out;

                            ///////////////////
                            // Tasklet code (T_l953_c953)
                            zconst_out = ydecldp_var_49_0_in_rcl_kk_cloud_num_sea;
                            ///////////////////

                            zconst = zconst_out;
                        }
                        {
                            double ydecldp_var_49_0_in_rclcrit_sea = v_ydecldp_var_49_rclcrit_sea[0];
                            double zlcrit_out;

                            ///////////////////
                            // Tasklet code (T_l954_c954)
                            zlcrit_out = ydecldp_var_49_0_in_rclcrit_sea;
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
                        double* v_ydecldp_var_49_rcl_kkbaun;
                        v_ydecldp_var_49_rcl_kkbaun = (double*)(&(ydecldp_var_49->rcl_kkbaun));
                        double* v_ydecldp_var_49_rcl_kkbauq;
                        v_ydecldp_var_49_rcl_kkbauq = (double*)(&(ydecldp_var_49->rcl_kkbauq));
                        double* v_ydecldp_var_49_rcl_kkaau;
                        v_ydecldp_var_49_rcl_kkaau = (double*)(&(ydecldp_var_49->rcl_kkaau));

                        {
                            double ydecldp_var_49_0_in_rcl_kkbaun = v_ydecldp_var_49_rcl_kkbaun[0];
                            double zconst_0_in = zconst;
                            double tmp_call_64_out;

                            ///////////////////
                            // Tasklet code (T_l957_c957)
                            tmp_call_64_out = dace::math::pow(zconst_0_in, ydecldp_var_49_0_in_rcl_kkbaun);
                            ///////////////////

                            tmp_call_64 = tmp_call_64_out;
                        }
                        {
                            double ydecldp_var_49_0_in_rcl_kkbauq = v_ydecldp_var_49_rcl_kkbauq[0];
                            double zliqcld_0_in_0 = zliqcld[(_for_it_52 - 1)];
                            double tmp_call_63_out;

                            ///////////////////
                            // Tasklet code (T_l957_c957)
                            tmp_call_63_out = dace::math::pow(zliqcld_0_in_0, ydecldp_var_49_0_in_rcl_kkbauq);
                            ///////////////////

                            tmp_call_63 = tmp_call_63_out;
                        }
                        {
                            double ptsphy_var_5_0_in = ptsphy_var_5[0];
                            double tmp_call_63_0_in = tmp_call_63;
                            double tmp_call_64_0_in = tmp_call_64;
                            double ydecldp_var_49_0_in_rcl_kkaau = v_ydecldp_var_49_rcl_kkaau[0];
                            double za_0_in_0 = za[((_for_it_52 + (sym_klon * (_for_it_23 - 1))) - 1)];
                            double zrainaut_out_0;

                            ///////////////////
                            // Tasklet code (T_l957_c957)
                            zrainaut_out_0 = (((((1.5 * za_0_in_0) * ptsphy_var_5_0_in) * ydecldp_var_49_0_in_rcl_kkaau) * tmp_call_63_0_in) * tmp_call_64_0_in);
                            ///////////////////

                            zrainaut[(_for_it_52 - 1)] = zrainaut_out_0;
                        }
                        {
                            double zqxfg_0_in_0 = zqxfg[(_for_it_52 - 1)];
                            double zrainaut_0_in_0 = zrainaut[(_for_it_52 - 1)];
                            double tmp_call_65_out;

                            ///////////////////
                            // Tasklet code (T_l958_c958)
                            tmp_call_65_out = min(zrainaut_0_in_0, zqxfg_0_in_0);
                            ///////////////////

                            tmp_call_65 = tmp_call_65_out;
                        }
                        {
                            double tmp_call_65_0_in = tmp_call_65;
                            double zrainaut_out_0;

                            ///////////////////
                            // Tasklet code (T_l958_c958)
                            zrainaut_out_0 = tmp_call_65_0_in;
                            ///////////////////

                            zrainaut[(_for_it_52 - 1)] = zrainaut_out_0;
                        }
                        {
                            double zrainaut_0_in_0 = zrainaut[(_for_it_52 - 1)];
                            double _if_cond_56_out;

                            ///////////////////
                            // Tasklet code (T_l959_c959)
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
                                // Tasklet code (T_l959_c959)
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
                        double* v_ydecldp_var_49_rcl_kkbac;
                        v_ydecldp_var_49_rcl_kkbac = (double*)(&(ydecldp_var_49->rcl_kkbac));
                        double* v_ydecldp_var_49_rcl_kkaac;
                        v_ydecldp_var_49_rcl_kkaac = (double*)(&(ydecldp_var_49->rcl_kkaac));

                        {
                            double zliqcld_0_in_0 = zliqcld[(_for_it_52 - 1)];
                            double zraincld_0_in_0 = zraincld[(_for_it_52 - 1)];
                            double tmp_arg_39_out;

                            ///////////////////
                            // Tasklet code (T_l960_c960)
                            tmp_arg_39_out = (zliqcld_0_in_0 * zraincld_0_in_0);
                            ///////////////////

                            tmp_arg_39 = tmp_arg_39_out;
                        }
                        {
                            double tmp_arg_39_0_in = tmp_arg_39;
                            double ydecldp_var_49_0_in_rcl_kkbac = v_ydecldp_var_49_rcl_kkbac[0];
                            double tmp_call_66_out;

                            ///////////////////
                            // Tasklet code (T_l960_c960)
                            tmp_call_66_out = dace::math::pow(tmp_arg_39_0_in, ydecldp_var_49_0_in_rcl_kkbac);
                            ///////////////////

                            tmp_call_66 = tmp_call_66_out;
                        }
                        {
                            double ptsphy_var_5_0_in = ptsphy_var_5[0];
                            double tmp_call_66_0_in = tmp_call_66;
                            double ydecldp_var_49_0_in_rcl_kkaac = v_ydecldp_var_49_rcl_kkaac[0];
                            double za_0_in_0 = za[((_for_it_52 + (sym_klon * (_for_it_23 - 1))) - 1)];
                            double zrainacc_out_0;

                            ///////////////////
                            // Tasklet code (T_l960_c960)
                            zrainacc_out_0 = ((((2.0 * za_0_in_0) * ptsphy_var_5_0_in) * ydecldp_var_49_0_in_rcl_kkaac) * tmp_call_66_0_in);
                            ///////////////////

                            zrainacc[(_for_it_52 - 1)] = zrainacc_out_0;
                        }
                        {
                            double zqxfg_0_in_0 = zqxfg[(_for_it_52 - 1)];
                            double zrainacc_0_in_0 = zrainacc[(_for_it_52 - 1)];
                            double tmp_call_67_out;

                            ///////////////////
                            // Tasklet code (T_l961_c961)
                            tmp_call_67_out = min(zrainacc_0_in_0, zqxfg_0_in_0);
                            ///////////////////

                            tmp_call_67 = tmp_call_67_out;
                        }
                        {
                            double tmp_call_67_0_in = tmp_call_67;
                            double zrainacc_out_0;

                            ///////////////////
                            // Tasklet code (T_l961_c961)
                            zrainacc_out_0 = tmp_call_67_0_in;
                            ///////////////////

                            zrainacc[(_for_it_52 - 1)] = zrainacc_out_0;
                        }
                        {
                            double zrainacc_0_in_0 = zrainacc[(_for_it_52 - 1)];
                            double _if_cond_57_out;

                            ///////////////////
                            // Tasklet code (T_l962_c962)
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
                                // Tasklet code (T_l962_c962)
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
                            // Tasklet code (T_l964_c964)
                            zrainaut_out_0 = 0.0;
                            ///////////////////

                            zrainaut[(_for_it_52 - 1)] = zrainaut_out_0;
                        }
                        {
                            double zrainacc_out_0;

                            ///////////////////
                            // Tasklet code (T_l965_c965)
                            zrainacc_out_0 = 0.0;
                            ///////////////////

                            zrainacc[(_for_it_52 - 1)] = zrainacc_out_0;
                        }
                    }
                }
                {
                    {
                        double ydcst_var_47_0_in_rtt = v_ydcst_var_47_rtt[0];
                        double ztp1_0_in_0 = ztp1[((_for_it_52 + (sym_klon * (_for_it_23 - 1))) - 1)];
                        double _if_cond_58_out;

                        ///////////////////
                        // Tasklet code (T_l0_c0)
                        _if_cond_58_out = (ztp1_0_in_0 <= ydcst_var_47_0_in_rtt);
                        ///////////////////

                        _if_cond_58 = _if_cond_58_out;
                    }
                }
                if ((_if_cond_58 == 1)) {
                    {
                        {
                            double zrainaut_0_in_0 = zrainaut[(_for_it_52 - 1)];
                            double zsolqa_0_in_0 = zsolqa[((_for_it_52 + (3 * sym_klon)) - 1)];
                            double zsolqa_out_0;

                            ///////////////////
                            // Tasklet code (T_l968_c968)
                            zsolqa_out_0 = (zsolqa_0_in_0 + zrainaut_0_in_0);
                            ///////////////////

                            zsolqa[((_for_it_52 + (3 * sym_klon)) - 1)] = zsolqa_out_0;
                        }
                        {
                            double zrainacc_0_in_0 = zrainacc[(_for_it_52 - 1)];
                            double zsolqa_0_in_0 = zsolqa[((_for_it_52 + (3 * sym_klon)) - 1)];
                            double zsolqa_out_0;

                            ///////////////////
                            // Tasklet code (T_l969_c969)
                            zsolqa_out_0 = (zsolqa_0_in_0 + zrainacc_0_in_0);
                            ///////////////////

                            zsolqa[((_for_it_52 + (3 * sym_klon)) - 1)] = zsolqa_out_0;
                        }
                        {
                            double zrainaut_0_in_0 = zrainaut[(_for_it_52 - 1)];
                            double zsolqa_0_in_0 = zsolqa[((_for_it_52 + (15 * sym_klon)) - 1)];
                            double zsolqa_out_0;

                            ///////////////////
                            // Tasklet code (T_l970_c970)
                            zsolqa_out_0 = (zsolqa_0_in_0 - zrainaut_0_in_0);
                            ///////////////////

                            zsolqa[((_for_it_52 + (15 * sym_klon)) - 1)] = zsolqa_out_0;
                        }
                        {
                            double zrainacc_0_in_0 = zrainacc[(_for_it_52 - 1)];
                            double zsolqa_0_in_0 = zsolqa[((_for_it_52 + (15 * sym_klon)) - 1)];
                            double zsolqa_out_0;

                            ///////////////////
                            // Tasklet code (T_l971_c971)
                            zsolqa_out_0 = (zsolqa_0_in_0 - zrainacc_0_in_0);
                            ///////////////////

                            zsolqa[((_for_it_52 + (15 * sym_klon)) - 1)] = zsolqa_out_0;
                        }
                    }
                } else {
                    {
                        {
                            double zrainaut_0_in_0 = zrainaut[(_for_it_52 - 1)];
                            double zsolqa_0_in_0 = zsolqa[((_for_it_52 + (2 * sym_klon)) - 1)];
                            double zsolqa_out_0;

                            ///////////////////
                            // Tasklet code (T_l973_c973)
                            zsolqa_out_0 = (zsolqa_0_in_0 + zrainaut_0_in_0);
                            ///////////////////

                            zsolqa[((_for_it_52 + (2 * sym_klon)) - 1)] = zsolqa_out_0;
                        }
                        {
                            double zrainacc_0_in_0 = zrainacc[(_for_it_52 - 1)];
                            double zsolqa_0_in_0 = zsolqa[((_for_it_52 + (2 * sym_klon)) - 1)];
                            double zsolqa_out_0;

                            ///////////////////
                            // Tasklet code (T_l974_c974)
                            zsolqa_out_0 = (zsolqa_0_in_0 + zrainacc_0_in_0);
                            ///////////////////

                            zsolqa[((_for_it_52 + (2 * sym_klon)) - 1)] = zsolqa_out_0;
                        }
                        {
                            double zrainaut_0_in_0 = zrainaut[(_for_it_52 - 1)];
                            double zsolqa_0_in_0 = zsolqa[((_for_it_52 + (10 * sym_klon)) - 1)];
                            double zsolqa_out_0;

                            ///////////////////
                            // Tasklet code (T_l975_c975)
                            zsolqa_out_0 = (zsolqa_0_in_0 - zrainaut_0_in_0);
                            ///////////////////

                            zsolqa[((_for_it_52 + (10 * sym_klon)) - 1)] = zsolqa_out_0;
                        }
                        {
                            double zrainacc_0_in_0 = zrainacc[(_for_it_52 - 1)];
                            double zsolqa_0_in_0 = zsolqa[((_for_it_52 + (10 * sym_klon)) - 1)];
                            double zsolqa_out_0;

                            ///////////////////
                            // Tasklet code (T_l976_c976)
                            zsolqa_out_0 = (zsolqa_0_in_0 - zrainacc_0_in_0);
                            ///////////////////

                            zsolqa[((_for_it_52 + (10 * sym_klon)) - 1)] = zsolqa_out_0;
                        }
                    }
                }
            }
        }
        for (_for_it_53 = 1; (_for_it_53 <= icend); _for_it_53 = (_for_it_53 + 1)) {
            {
                {
                    double ydcst_var_47_0_in_rtt = v_ydcst_var_47_rtt[0];
                    double zliqcld_0_in_0 = zliqcld[(_for_it_53 - 1)];
                    double ztp1_0_in_0 = ztp1[((_for_it_53 + (sym_klon * (_for_it_23 - 1))) - 1)];
                    double _if_cond_59_out;

                    ///////////////////
                    // Tasklet code (T_l0_c0)
                    _if_cond_59_out = ((ztp1_0_in_0 <= ydcst_var_47_0_in_rtt) && (zliqcld_0_in_0 > 1e-14));
                    ///////////////////

                    _if_cond_59 = _if_cond_59_out;
                }
            }
            if ((_if_cond_59 == 1)) {
                _if_cond_60 = ((zsnowcld[(_for_it_53 - 1)] > 1e-14) && (zcovptot[(_for_it_53 - 1)] > 0.01));
                {
                    double tmp_arg_40;

                    {
                        double ydecldp_var_49_0_in_rdensref = v_ydecldp_var_49_rdensref[0];
                        double zrho_0_in_0 = zrho[(_for_it_53 - 1)];
                        double tmp_arg_40_out;

                        ///////////////////
                        // Tasklet code (T_l982_c982)
                        tmp_arg_40_out = (ydecldp_var_49_0_in_rdensref / zrho_0_in_0);
                        ///////////////////

                        tmp_arg_40 = tmp_arg_40_out;
                    }
                    {
                        double tmp_arg_40_0_in = tmp_arg_40;
                        double zfallcorr_out;

                        ///////////////////
                        // Tasklet code (T_l982_c982)
                        zfallcorr_out = dace::math::pow(tmp_arg_40_0_in, 0.4);
                        ///////////////////

                        zfallcorr = zfallcorr_out;
                    }
                }
                if ((_if_cond_60 == 1)) {
                    {
                        double* zsnowrime;
                        zsnowrime = new double DACE_ALIGN(64)[sym_klon];
                        double tmp_call_68;
                        double tmp_call_69;
                        double tmp_arg_41;
                        double* v_ydecldp_var_49_rcl_const1s;
                        v_ydecldp_var_49_rcl_const1s = (double*)(&(ydecldp_var_49->rcl_const1s));
                        double* v_ydecldp_var_49_rcl_const8s;
                        v_ydecldp_var_49_rcl_const8s = (double*)(&(ydecldp_var_49->rcl_const8s));
                        double* v_ydecldp_var_49_rcl_const7s;
                        v_ydecldp_var_49_rcl_const7s = (double*)(&(ydecldp_var_49->rcl_const7s));

                        {
                            double ydecldp_var_49_0_in_rcl_const1s = v_ydecldp_var_49_rcl_const1s[0];
                            double zrho_0_in_0 = zrho[(_for_it_53 - 1)];
                            double zsnowcld_0_in_0 = zsnowcld[(_for_it_53 - 1)];
                            double tmp_arg_41_out;

                            ///////////////////
                            // Tasklet code (T_l984_c984)
                            tmp_arg_41_out = ((zrho_0_in_0 * zsnowcld_0_in_0) * ydecldp_var_49_0_in_rcl_const1s);
                            ///////////////////

                            tmp_arg_41 = tmp_arg_41_out;
                        }
                        {
                            double tmp_arg_41_0_in = tmp_arg_41;
                            double ydecldp_var_49_0_in_rcl_const8s = v_ydecldp_var_49_rcl_const8s[0];
                            double tmp_call_68_out;

                            ///////////////////
                            // Tasklet code (T_l984_c984)
                            tmp_call_68_out = dace::math::pow(tmp_arg_41_0_in, ydecldp_var_49_0_in_rcl_const8s);
                            ///////////////////

                            tmp_call_68 = tmp_call_68_out;
                        }
                        {
                            double ptsphy_var_5_0_in = ptsphy_var_5[0];
                            double tmp_call_68_0_in = tmp_call_68;
                            double ydecldp_var_49_0_in_rcl_const7s = v_ydecldp_var_49_rcl_const7s[0];
                            double zcovptot_0_in_0 = zcovptot[(_for_it_53 - 1)];
                            double zfallcorr_0_in = zfallcorr;
                            double zsnowrime_out_0;

                            ///////////////////
                            // Tasklet code (T_l984_c984)
                            zsnowrime_out_0 = (((((0.3 * zcovptot_0_in_0) * ptsphy_var_5_0_in) * ydecldp_var_49_0_in_rcl_const7s) * zfallcorr_0_in) * tmp_call_68_0_in);
                            ///////////////////

                            zsnowrime[(_for_it_53 - 1)] = zsnowrime_out_0;
                        }
                        {
                            double zsnowrime_0_in_0 = zsnowrime[(_for_it_53 - 1)];
                            double tmp_call_69_out;

                            ///////////////////
                            // Tasklet code (T_l985_c985)
                            tmp_call_69_out = min(zsnowrime_0_in_0, 1.0);
                            ///////////////////

                            tmp_call_69 = tmp_call_69_out;
                        }
                        {
                            double tmp_call_69_0_in = tmp_call_69;
                            double zsnowrime_out_0;

                            ///////////////////
                            // Tasklet code (T_l985_c985)
                            zsnowrime_out_0 = tmp_call_69_0_in;
                            ///////////////////

                            zsnowrime[(_for_it_53 - 1)] = zsnowrime_out_0;
                        }
                        {
                            double zsnowrime_0_in_0 = zsnowrime[(_for_it_53 - 1)];
                            double zsolqb_0_in_0 = zsolqb[((_for_it_53 + (3 * sym_klon)) - 1)];
                            double zsolqb_out_0;

                            ///////////////////
                            // Tasklet code (T_l986_c986)
                            zsolqb_out_0 = (zsolqb_0_in_0 + zsnowrime_0_in_0);
                            ///////////////////

                            zsolqb[((_for_it_53 + (3 * sym_klon)) - 1)] = zsolqb_out_0;
                        }
                        delete[] zsnowrime;
                    }
                }
            }
        }
        for (_for_it_54 = 1; (_for_it_54 <= icend); _for_it_54 = (_for_it_54 + 1)) {
            {
                {
                    double zmeltmax_out_0;

                    ///////////////////
                    // Tasklet code (T_l992_c992)
                    zmeltmax_out_0 = 0.0;
                    ///////////////////

                    zmeltmax[(_for_it_54 - 1)] = zmeltmax_out_0;
                }
                {
                    double zqxfg_0_in_0 = zqxfg[((_for_it_54 + sym_klon) - 1)];
                    double zqxfg_1_in_0 = zqxfg[((_for_it_54 + (3 * sym_klon)) - 1)];
                    double zicetot_out_0;

                    ///////////////////
                    // Tasklet code (T_l991_c991)
                    zicetot_out_0 = (zqxfg_0_in_0 + zqxfg_1_in_0);
                    ///////////////////

                    zicetot[(_for_it_54 - 1)] = zicetot_out_0;
                }
                {
                    double ydcst_var_47_0_in_rtt = v_ydcst_var_47_rtt[0];
                    double zicetot_0_in_0 = zicetot[(_for_it_54 - 1)];
                    double ztp1_0_in_0 = ztp1[((_for_it_54 + (sym_klon * (_for_it_23 - 1))) - 1)];
                    double _if_cond_61_out;

                    ///////////////////
                    // Tasklet code (T_l0_c0)
                    _if_cond_61_out = ((zicetot_0_in_0 > 1e-14) && (ztp1_0_in_0 > ydcst_var_47_0_in_rtt));
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
                        double zqsice_0_in_0 = zqsice[((_for_it_54 + (sym_klon * (_for_it_23 - 1))) - 1)];
                        double zqx_0_in_0 = zqx[(((_for_it_54 + ((4 * sym_klev) * sym_klon)) + (sym_klon * (_for_it_23 - 1))) - 1)];
                        double tmp_arg_42_out;

                        ///////////////////
                        // Tasklet code (T_l994_c994)
                        tmp_arg_42_out = (zqsice_0_in_0 - zqx_0_in_0);
                        ///////////////////

                        tmp_arg_42 = tmp_arg_42_out;
                    }
                    {
                        double tmp_arg_42_0_in = tmp_arg_42;
                        double zsubsat_out;

                        ///////////////////
                        // Tasklet code (T_l994_c994)
                        zsubsat_out = max(tmp_arg_42_0_in, 0.0);
                        ///////////////////

                        zsubsat = zsubsat_out;
                    }
                    {
                        double pap_var_17_0_in_0 = pap_var_17[((_for_it_54 + (sym_klon * (_for_it_23 - 1))) - 1)];
                        double ydcst_var_47_0_in_rtt = v_ydcst_var_47_rtt[0];
                        double zsubsat_0_in = zsubsat;
                        double ztp1_0_in_0 = ztp1[((_for_it_54 + (sym_klon * (_for_it_23 - 1))) - 1)];
                        double ztp1_1_in_0 = ztp1[((_for_it_54 + (sym_klon * (_for_it_23 - 1))) - 1)];
                        double ztdmtw0_out;

                        ///////////////////
                        // Tasklet code (T_l995_c995)
                        ztdmtw0_out = ((ztp1_0_in_0 - ydcst_var_47_0_in_rtt) - (zsubsat_0_in * ((1329.31 + (0.0074615 * (pap_var_17_0_in_0 - 85000.0))) - (40.637 * (ztp1_1_in_0 - 275.0)))));
                        ///////////////////

                        ztdmtw0 = ztdmtw0_out;
                    }
                    {
                        double ptsphy_var_5_0_in = ptsphy_var_5[0];
                        double ydecldp_var_49_0_in_rtaumel = v_ydecldp_var_49_rtaumel[0];
                        double ztdmtw0_0_in = ztdmtw0;
                        double tmp_arg_43_out;

                        ///////////////////
                        // Tasklet code (T_l996_c996)
                        tmp_arg_43_out = ((ptsphy_var_5_0_in * (1.0 + (0.5 * ztdmtw0_0_in))) / ydecldp_var_49_0_in_rtaumel);
                        ///////////////////

                        tmp_arg_43 = tmp_arg_43_out;
                    }
                    {
                        double tmp_arg_43_0_in = tmp_arg_43;
                        double zcons1_out;

                        ///////////////////
                        // Tasklet code (T_l996_c996)
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
                        // Tasklet code (T_l997_c997)
                        tmp_arg_44_out = ((ztdmtw0_0_in * zcons1_0_in) * zrldcp_0_in);
                        ///////////////////

                        tmp_arg_44 = tmp_arg_44_out;
                    }
                    {
                        double tmp_arg_44_0_in = tmp_arg_44;
                        double tmp_call_70_out;

                        ///////////////////
                        // Tasklet code (T_l997_c997)
                        tmp_call_70_out = max(tmp_arg_44_0_in, 0.0);
                        ///////////////////

                        tmp_call_70 = tmp_call_70_out;
                    }
                    {
                        double tmp_call_70_0_in = tmp_call_70;
                        double zmeltmax_out_0;

                        ///////////////////
                        // Tasklet code (T_l997_c997)
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
                for (_for_it_56 = 1; (_for_it_56 <= icend); _for_it_56 = (_for_it_56 + 1)) {
                    _if_cond_63 = ((zmeltmax[(_for_it_56 - 1)] > 1e-14) && (zicetot[(_for_it_56 - 1)] > 1e-14));
                    if ((_if_cond_63 == 1)) {
                        {
                            double zmelt;
                            double tmp_arg_45;

                            {
                                double zicetot_0_in_0 = zicetot[(_for_it_56 - 1)];
                                double zqxfg_0_in_0 = zqxfg[((_for_it_56 + (sym_klon * (_for_it_55 - 1))) - 1)];
                                double zalfa_out;

                                ///////////////////
                                // Tasklet code (T_l1005_c1005)
                                zalfa_out = (zqxfg_0_in_0 / zicetot_0_in_0);
                                ///////////////////

                                zalfa = zalfa_out;
                            }
                            {
                                double zalfa_0_in = zalfa;
                                double zmeltmax_0_in_0 = zmeltmax[(_for_it_56 - 1)];
                                double tmp_arg_45_out;

                                ///////////////////
                                // Tasklet code (T_l1006_c1006)
                                tmp_arg_45_out = (zalfa_0_in * zmeltmax_0_in_0);
                                ///////////////////

                                tmp_arg_45 = tmp_arg_45_out;
                            }
                            {
                                double tmp_arg_45_0_in = tmp_arg_45;
                                double zqxfg_0_in_0 = zqxfg[((_for_it_56 + (sym_klon * (_for_it_55 - 1))) - 1)];
                                double zmelt_out;

                                ///////////////////
                                // Tasklet code (T_l1006_c1006)
                                zmelt_out = min(zqxfg_0_in_0, tmp_arg_45_0_in);
                                ///////////////////

                                zmelt = zmelt_out;
                            }
                            {
                                double zmelt_0_in = zmelt;
                                double zqxfg_0_in_0 = zqxfg[((_for_it_56 + (sym_klon * (_for_it_55 - 1))) - 1)];
                                double zqxfg_out_0;

                                ///////////////////
                                // Tasklet code (T_l1007_c1007)
                                zqxfg_out_0 = (zqxfg_0_in_0 - zmelt_0_in);
                                ///////////////////

                                zqxfg[((_for_it_56 + (sym_klon * (_for_it_55 - 1))) - 1)] = zqxfg_out_0;
                            }
                            {
                                double zmelt_0_in = zmelt;
                                double zqxfg_0_in_0 = zqxfg[((_for_it_56 + (sym_klon * (jnn - 1))) - 1)];
                                double zqxfg_out_0;

                                ///////////////////
                                // Tasklet code (T_l1008_c1008)
                                zqxfg_out_0 = (zqxfg_0_in_0 + zmelt_0_in);
                                ///////////////////

                                zqxfg[((_for_it_56 + (sym_klon * (jnn - 1))) - 1)] = zqxfg_out_0;
                            }
                            {
                                double zmelt_0_in = zmelt;
                                double zsolqa_0_in_0 = zsolqa[(((_for_it_56 + ((5 * sym_klon) * (_for_it_55 - 1))) + (sym_klon * (jnn - 1))) - 1)];
                                double zsolqa_out_0;

                                ///////////////////
                                // Tasklet code (T_l1009_c1009)
                                zsolqa_out_0 = (zsolqa_0_in_0 + zmelt_0_in);
                                ///////////////////

                                zsolqa[(((_for_it_56 + ((5 * sym_klon) * (_for_it_55 - 1))) + (sym_klon * (jnn - 1))) - 1)] = zsolqa_out_0;
                            }
                            {
                                double zmelt_0_in = zmelt;
                                double zsolqa_0_in_0 = zsolqa[(((_for_it_56 + (sym_klon * (_for_it_55 - 1))) + ((5 * sym_klon) * (jnn - 1))) - 1)];
                                double zsolqa_out_0;

                                ///////////////////
                                // Tasklet code (T_l1010_c1010)
                                zsolqa_out_0 = (zsolqa_0_in_0 - zmelt_0_in);
                                ///////////////////

                                zsolqa[(((_for_it_56 + (sym_klon * (_for_it_55 - 1))) + ((5 * sym_klon) * (jnn - 1))) - 1)] = zsolqa_out_0;
                            }
                        }
                    }
                }
            }
        }
        for (_for_it_57 = 1; (_for_it_57 <= icend); _for_it_57 = (_for_it_57 + 1)) {
            _if_cond_64 = (zqx[(((_for_it_57 + ((2 * sym_klev) * sym_klon)) + (sym_klon * (_for_it_23 - 1))) - 1)] > 1e-14);
            if ((_if_cond_64 == 1)) {
                {
                    {
                        double ydcst_var_47_0_in_rtt = v_ydcst_var_47_rtt[0];
                        double ydcst_var_47_1_in_rtt = v_ydcst_var_47_rtt[0];
                        double ztp1_0_in_0 = ztp1[((_for_it_57 + (sym_klon * (_for_it_23 - 1))) - 1)];
                        double ztp1_1_in_0 = ztp1[((_for_it_57 + (sym_klon * (_for_it_23 - 2))) - 1)];
                        double _if_cond_65_out;

                        ///////////////////
                        // Tasklet code (T_l0_c0)
                        _if_cond_65_out = ((ztp1_0_in_0 <= ydcst_var_47_0_in_rtt) && (ztp1_1_in_0 > ydcst_var_47_1_in_rtt));
                        ///////////////////

                        _if_cond_65 = _if_cond_65_out;
                    }
                }
                if ((_if_cond_65 == 1)) {
                    {
                        double tmp_call_71;
                        double tmp_arg_46;

                        {
                            double zqx_0_in_0 = zqx[(((_for_it_57 + ((3 * sym_klev) * sym_klon)) + (sym_klon * (_for_it_23 - 1))) - 1)];
                            double zqx_1_in_0 = zqx[(((_for_it_57 + ((2 * sym_klev) * sym_klon)) + (sym_klon * (_for_it_23 - 1))) - 1)];
                            double tmp_arg_46_out;

                            ///////////////////
                            // Tasklet code (T_l1018_c1018)
                            tmp_arg_46_out = (zqx_0_in_0 + zqx_1_in_0);
                            ///////////////////

                            tmp_arg_46 = tmp_arg_46_out;
                        }
                        {
                            double tmp_arg_46_0_in = tmp_arg_46;
                            double zepsec_0_in = zepsec;
                            double tmp_call_71_out;

                            ///////////////////
                            // Tasklet code (T_l1018_c1018)
                            tmp_call_71_out = max(tmp_arg_46_0_in, zepsec_0_in);
                            ///////////////////

                            tmp_call_71 = tmp_call_71_out;
                        }
                        {
                            double tmp_call_71_0_in = tmp_call_71;
                            double zqpretot_out_0;

                            ///////////////////
                            // Tasklet code (T_l1018_c1018)
                            zqpretot_out_0 = tmp_call_71_0_in;
                            ///////////////////

                            zqpretot[(_for_it_57 - 1)] = zqpretot_out_0;
                        }
                        {
                            double zqpretot_0_in_0 = zqpretot[(_for_it_57 - 1)];
                            double zqx_0_in_0 = zqx[(((_for_it_57 + ((2 * sym_klev) * sym_klon)) + (sym_klon * (_for_it_23 - 1))) - 1)];
                            double prainfrac_toprfz_var_32_out_0;

                            ///////////////////
                            // Tasklet code (T_l1019_c1019)
                            prainfrac_toprfz_var_32_out_0 = (zqx_0_in_0 / zqpretot_0_in_0);
                            ///////////////////

                            prainfrac_toprfz_var_32[(_for_it_57 - 1)] = prainfrac_toprfz_var_32_out_0;
                        }
                        {
                            double prainfrac_toprfz_var_32_0_in_0 = prainfrac_toprfz_var_32[(_for_it_57 - 1)];
                            double _if_cond_66_out;

                            ///////////////////
                            // Tasklet code (T_l0_c0)
                            _if_cond_66_out = (prainfrac_toprfz_var_32_0_in_0 > 0.8);
                            ///////////////////

                            _if_cond_66 = _if_cond_66_out;
                        }
                    }
                    if ((_if_cond_66 == 1)) {
                        {
                            {
                                int llrainliq_out_0;

                                ///////////////////
                                // Tasklet code (T_l1021_c1021)
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
                                // Tasklet code (T_l1023_c1023)
                                llrainliq_out_0 = 0;
                                ///////////////////

                                llrainliq[(_for_it_57 - 1)] = llrainliq_out_0;
                            }
                        }
                    }
                }
                {
                    {
                        double ydcst_var_47_0_in_rtt = v_ydcst_var_47_rtt[0];
                        double ztp1_0_in_0 = ztp1[((_for_it_57 + (sym_klon * (_for_it_23 - 1))) - 1)];
                        double _if_cond_67_out;

                        ///////////////////
                        // Tasklet code (T_l0_c0)
                        _if_cond_67_out = (ztp1_0_in_0 < ydcst_var_47_0_in_rtt);
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
                            double* v_ydecldp_var_49_rcl_fzrab;
                            v_ydecldp_var_49_rcl_fzrab = (double*)(&(ydecldp_var_49->rcl_fzrab));
                            double* v_ydecldp_var_49_rcl_const6r;
                            v_ydecldp_var_49_rcl_const6r = (double*)(&(ydecldp_var_49->rcl_const6r));
                            double* v_ydecldp_var_49_rcl_const5r;
                            v_ydecldp_var_49_rcl_const5r = (double*)(&(ydecldp_var_49->rcl_const5r));

                            {
                                double ydecldp_var_49_0_in_rcl_fac1 = v_ydecldp_var_49_rcl_fac1[0];
                                double zqx_0_in_0 = zqx[(((_for_it_57 + ((2 * sym_klev) * sym_klon)) + (sym_klon * (_for_it_23 - 1))) - 1)];
                                double zrho_0_in_0 = zrho[(_for_it_57 - 1)];
                                double tmp_arg_47_out;

                                ///////////////////
                                // Tasklet code (T_l1028_c1028)
                                tmp_arg_47_out = (ydecldp_var_49_0_in_rcl_fac1 / (zrho_0_in_0 * zqx_0_in_0));
                                ///////////////////

                                tmp_arg_47 = tmp_arg_47_out;
                            }
                            {
                                double tmp_arg_47_0_in = tmp_arg_47;
                                double ydecldp_var_49_0_in_rcl_fac2 = v_ydecldp_var_49_rcl_fac2[0];
                                double zlambda_out;

                                ///////////////////
                                // Tasklet code (T_l1028_c1028)
                                zlambda_out = dace::math::pow(tmp_arg_47_0_in, ydecldp_var_49_0_in_rcl_fac2);
                                ///////////////////

                                zlambda = zlambda_out;
                            }
                            {
                                double ydecldp_var_49_0_in_rcl_const6r = v_ydecldp_var_49_rcl_const6r[0];
                                double zlambda_0_in = zlambda;
                                double tmp_call_73_out;

                                ///////////////////
                                // Tasklet code (T_l1030_c1030)
                                tmp_call_73_out = dace::math::pow(zlambda_0_in, ydecldp_var_49_0_in_rcl_const6r);
                                ///////////////////

                                tmp_call_73 = tmp_call_73_out;
                            }
                            {
                                double ydcst_var_47_0_in_rtt = v_ydcst_var_47_rtt[0];
                                double ydecldp_var_49_0_in_rcl_fzrab = v_ydecldp_var_49_rcl_fzrab[0];
                                double ztp1_0_in_0 = ztp1[((_for_it_57 + (sym_klon * (_for_it_23 - 1))) - 1)];
                                double ztemp_out;

                                ///////////////////
                                // Tasklet code (T_l1029_c1029)
                                ztemp_out = (ydecldp_var_49_0_in_rcl_fzrab * (ztp1_0_in_0 - ydcst_var_47_0_in_rtt));
                                ///////////////////

                                ztemp = ztemp_out;
                            }
                            {
                                double ztemp_0_in = ztemp;
                                double tmp_call_72_out;

                                ///////////////////
                                // Tasklet code (T_l1030_c1030)
                                tmp_call_72_out = exp(ztemp_0_in);
                                ///////////////////

                                tmp_call_72 = tmp_call_72_out;
                            }
                            {
                                double ptsphy_var_5_0_in = ptsphy_var_5[0];
                                double tmp_call_72_0_in = tmp_call_72;
                                double tmp_call_73_0_in = tmp_call_73;
                                double ydecldp_var_49_0_in_rcl_const5r = v_ydecldp_var_49_rcl_const5r[0];
                                double zrho_0_in_0 = zrho[(_for_it_57 - 1)];
                                double zfrz_out;

                                ///////////////////
                                // Tasklet code (T_l1030_c1030)
                                zfrz_out = (((ptsphy_var_5_0_in * (ydecldp_var_49_0_in_rcl_const5r / zrho_0_in_0)) * (tmp_call_72_0_in - 1.0)) * tmp_call_73_0_in);
                                ///////////////////

                                zfrz = zfrz_out;
                            }
                            {
                                double zfrz_0_in = zfrz;
                                double tmp_call_74_out;

                                ///////////////////
                                // Tasklet code (T_l1031_c1031)
                                tmp_call_74_out = max(zfrz_0_in, 0.0);
                                ///////////////////

                                tmp_call_74 = tmp_call_74_out;
                            }
                            {
                                double tmp_call_74_0_in = tmp_call_74;
                                double zfrzmax_out_0;

                                ///////////////////
                                // Tasklet code (T_l1031_c1031)
                                zfrzmax_out_0 = tmp_call_74_0_in;
                                ///////////////////

                                zfrzmax[(_for_it_57 - 1)] = zfrzmax_out_0;
                            }
                        }
                    } else {
                        {
                            double tmp_arg_48;

                            {
                                double ptsphy_var_5_0_in = ptsphy_var_5[0];
                                double ydcst_var_47_0_in_rtt = v_ydcst_var_47_rtt[0];
                                double ydecldp_var_49_0_in_rtaumel = v_ydecldp_var_49_rtaumel[0];
                                double ztp1_0_in_0 = ztp1[((_for_it_57 + (sym_klon * (_for_it_23 - 1))) - 1)];
                                double tmp_arg_48_out;

                                ///////////////////
                                // Tasklet code (T_l1033_c1033)
                                tmp_arg_48_out = ((ptsphy_var_5_0_in * (1.0 + (0.5 * (ydcst_var_47_0_in_rtt - ztp1_0_in_0)))) / ydecldp_var_49_0_in_rtaumel);
                                ///////////////////

                                tmp_arg_48 = tmp_arg_48_out;
                            }
                            {
                                double tmp_arg_48_0_in = tmp_arg_48;
                                double zcons1_out;

                                ///////////////////
                                // Tasklet code (T_l1033_c1033)
                                zcons1_out = abs(tmp_arg_48_0_in);
                                ///////////////////

                                zcons1 = zcons1_out;
                            }
                        }
                        {
                            double tmp_call_75;
                            double tmp_arg_49;

                            {
                                double ydcst_var_47_0_in_rtt = v_ydcst_var_47_rtt[0];
                                double zcons1_0_in = zcons1;
                                double zrldcp_0_in = zrldcp;
                                double ztp1_0_in_0 = ztp1[((_for_it_57 + (sym_klon * (_for_it_23 - 1))) - 1)];
                                double tmp_arg_49_out;

                                ///////////////////
                                // Tasklet code (T_l1034_c1034)
                                tmp_arg_49_out = (((ydcst_var_47_0_in_rtt - ztp1_0_in_0) * zcons1_0_in) * zrldcp_0_in);
                                ///////////////////

                                tmp_arg_49 = tmp_arg_49_out;
                            }
                            {
                                double tmp_arg_49_0_in = tmp_arg_49;
                                double tmp_call_75_out;

                                ///////////////////
                                // Tasklet code (T_l1034_c1034)
                                tmp_call_75_out = max(tmp_arg_49_0_in, 0.0);
                                ///////////////////

                                tmp_call_75 = tmp_call_75_out;
                            }
                            {
                                double tmp_call_75_0_in = tmp_call_75;
                                double zfrzmax_out_0;

                                ///////////////////
                                // Tasklet code (T_l1034_c1034)
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
                                double zqx_0_in_0 = zqx[(((_for_it_57 + ((2 * sym_klev) * sym_klon)) + (sym_klon * (_for_it_23 - 1))) - 1)];
                                double zfrz_out;

                                ///////////////////
                                // Tasklet code (T_l1037_c1037)
                                zfrz_out = min(zqx_0_in_0, zfrzmax_0_in_0);
                                ///////////////////

                                zfrz = zfrz_out;
                            }
                            {
                                double zfrz_0_in = zfrz;
                                double zsolqa_0_in_0 = zsolqa[((_for_it_57 + (13 * sym_klon)) - 1)];
                                double zsolqa_out_0;

                                ///////////////////
                                // Tasklet code (T_l1038_c1038)
                                zsolqa_out_0 = (zsolqa_0_in_0 + zfrz_0_in);
                                ///////////////////

                                zsolqa[((_for_it_57 + (13 * sym_klon)) - 1)] = zsolqa_out_0;
                            }
                            {
                                double zfrz_0_in = zfrz;
                                double zsolqa_0_in_0 = zsolqa[((_for_it_57 + (17 * sym_klon)) - 1)];
                                double zsolqa_out_0;

                                ///////////////////
                                // Tasklet code (T_l1039_c1039)
                                zsolqa_out_0 = (zsolqa_0_in_0 - zfrz_0_in);
                                ///////////////////

                                zsolqa[((_for_it_57 + (17 * sym_klon)) - 1)] = zsolqa_out_0;
                            }
                        }
                    }
                }
            }
        }
        for (_for_it_58 = 1; (_for_it_58 <= icend); _for_it_58 = (_for_it_58 + 1)) {
            {
                double tmp_call_76;
                double tmp_arg_50;

                {
                    double ydecldp_var_49_0_in_rthomo = v_ydecldp_var_49_rthomo[0];
                    double zrldcp_0_in = zrldcp;
                    double ztp1_0_in_0 = ztp1[((_for_it_58 + (sym_klon * (_for_it_23 - 1))) - 1)];
                    double tmp_arg_50_out;

                    ///////////////////
                    // Tasklet code (T_l1045_c1045)
                    tmp_arg_50_out = ((ydecldp_var_49_0_in_rthomo - ztp1_0_in_0) * zrldcp_0_in);
                    ///////////////////

                    tmp_arg_50 = tmp_arg_50_out;
                }
                {
                    double tmp_arg_50_0_in = tmp_arg_50;
                    double tmp_call_76_out;

                    ///////////////////
                    // Tasklet code (T_l1045_c1045)
                    tmp_call_76_out = max(tmp_arg_50_0_in, 0.0);
                    ///////////////////

                    tmp_call_76 = tmp_call_76_out;
                }
                {
                    double tmp_call_76_0_in = tmp_call_76;
                    double zfrzmax_out_0;

                    ///////////////////
                    // Tasklet code (T_l1045_c1045)
                    zfrzmax_out_0 = tmp_call_76_0_in;
                    ///////////////////

                    zfrzmax[(_for_it_58 - 1)] = zfrzmax_out_0;
                }
            }
        }
        jnn = imelt[0];
        for (_for_it_59 = 1; (_for_it_59 <= icend); _for_it_59 = (_for_it_59 + 1)) {
            _if_cond_70 = ((zfrzmax[(_for_it_59 - 1)] > 1e-14) && (zqxfg[(_for_it_59 - 1)] > 1e-14));
            if ((_if_cond_70 == 1)) {
                {
                    {
                        double zfrzmax_0_in_0 = zfrzmax[(_for_it_59 - 1)];
                        double zqxfg_0_in_0 = zqxfg[(_for_it_59 - 1)];
                        double zfrz_out;

                        ///////////////////
                        // Tasklet code (T_l1051_c1051)
                        zfrz_out = min(zqxfg_0_in_0, zfrzmax_0_in_0);
                        ///////////////////

                        zfrz = zfrz_out;
                    }
                    {
                        double zfrz_0_in = zfrz;
                        double zsolqa_0_in_0 = zsolqa[((_for_it_59 + (sym_klon * (jnn - 1))) - 1)];
                        double zsolqa_out_0;

                        ///////////////////
                        // Tasklet code (T_l1052_c1052)
                        zsolqa_out_0 = (zsolqa_0_in_0 + zfrz_0_in);
                        ///////////////////

                        zsolqa[((_for_it_59 + (sym_klon * (jnn - 1))) - 1)] = zsolqa_out_0;
                    }
                    {
                        double zfrz_0_in = zfrz;
                        double zsolqa_0_in_0 = zsolqa[((_for_it_59 + ((5 * sym_klon) * (jnn - 1))) - 1)];
                        double zsolqa_out_0;

                        ///////////////////
                        // Tasklet code (T_l1053_c1053)
                        zsolqa_out_0 = (zsolqa_0_in_0 - zfrz_0_in);
                        ///////////////////

                        zsolqa[((_for_it_59 + ((5 * sym_klon) * (jnn - 1))) - 1)] = zsolqa_out_0;
                    }
                }
            }
        }
        for (_for_it_60 = 1; (_for_it_60 <= icend); _for_it_60 = (_for_it_60 + 1)) {
            {
                double tmp_call_77;
                double tmp_arg_51;

                {
                    double za_0_in_0 = za[((_for_it_60 + (sym_klon * (_for_it_23 - 1))) - 1)];
                    double tmp_arg_51_out;

                    ///////////////////
                    // Tasklet code (T_l1057_c1057)
                    tmp_arg_51_out = (1.0 - za_0_in_0);
                    ///////////////////

                    tmp_arg_51 = tmp_arg_51_out;
                }
                {
                    double tmp_arg_51_0_in = tmp_arg_51;
                    double zepsec_0_in = zepsec;
                    double tmp_call_77_out;

                    ///////////////////
                    // Tasklet code (T_l1057_c1057)
                    tmp_call_77_out = max(zepsec_0_in, tmp_arg_51_0_in);
                    ///////////////////

                    tmp_call_77 = tmp_call_77_out;
                }
                {
                    double tmp_call_77_0_in = tmp_call_77;
                    double ydecldp_var_49_0_in_rprecrhmax = v_ydecldp_var_49_rprecrhmax[0];
                    double ydecldp_var_49_1_in_rprecrhmax = v_ydecldp_var_49_rprecrhmax[0];
                    double zcovpmax_0_in_0 = zcovpmax[(_for_it_60 - 1)];
                    double zzrh_out;

                    ///////////////////
                    // Tasklet code (T_l1057_c1057)
                    zzrh_out = (ydecldp_var_49_0_in_rprecrhmax + (((1.0 - ydecldp_var_49_1_in_rprecrhmax) * zcovpmax_0_in_0) / tmp_call_77_0_in));
                    ///////////////////

                    zzrh = zzrh_out;
                }
            }
            {
                double tmp_call_78;
                double tmp_call_79;

                {
                    double ydecldp_var_49_0_in_rprecrhmax = v_ydecldp_var_49_rprecrhmax[0];
                    double zzrh_0_in = zzrh;
                    double tmp_call_78_out;

                    ///////////////////
                    // Tasklet code (T_l1058_c1058)
                    tmp_call_78_out = max(zzrh_0_in, ydecldp_var_49_0_in_rprecrhmax);
                    ///////////////////

                    tmp_call_78 = tmp_call_78_out;
                }
                {
                    double tmp_call_78_0_in = tmp_call_78;
                    double zzrh_out;

                    ///////////////////
                    // Tasklet code (T_l1058_c1058)
                    zzrh_out = min(tmp_call_78_0_in, 1.0);
                    ///////////////////

                    zzrh = zzrh_out;
                }
                {
                    double zzrh_0_in = zzrh;
                    double zzrh_out;

                    ///////////////////
                    // Tasklet code (T_l1059_c1059)
                    zzrh_out = min(0.8, zzrh_0_in);
                    ///////////////////

                    zzrh = zzrh_out;
                }
                {
                    double zqsliq_0_in_0 = zqsliq[((_for_it_60 + (sym_klon * (_for_it_23 - 1))) - 1)];
                    double zqx_0_in_0 = zqx[(((_for_it_60 + ((4 * sym_klev) * sym_klon)) + (sym_klon * (_for_it_23 - 1))) - 1)];
                    double tmp_call_79_out;

                    ///////////////////
                    // Tasklet code (T_l1060_c1060)
                    tmp_call_79_out = min(zqx_0_in_0, zqsliq_0_in_0);
                    ///////////////////

                    tmp_call_79 = tmp_call_79_out;
                }
                {
                    double tmp_call_79_0_in = tmp_call_79;
                    double zqe_out;

                    ///////////////////
                    // Tasklet code (T_l1060_c1060)
                    zqe_out = max(0.0, tmp_call_79_0_in);
                    ///////////////////

                    zqe = zqe_out;
                }
                {
                    double zcovpclr_0_in_0 = zcovpclr[(_for_it_60 - 1)];
                    double zqe_0_in = zqe;
                    double zqsliq_0_in_0 = zqsliq[((_for_it_60 + (sym_klon * (_for_it_23 - 1))) - 1)];
                    double zqxfg_0_in_0 = zqxfg[((_for_it_60 + (2 * sym_klon)) - 1)];
                    double zzrh_0_in = zzrh;
                    int llo1_out;

                    ///////////////////
                    // Tasklet code (T_l1061_c1061)
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
                    double* v_ydecldp_var_49_rcl_cdenom1;
                    v_ydecldp_var_49_rcl_cdenom1 = (double*)(&(ydecldp_var_49->rcl_cdenom1));
                    double* v_ydecldp_var_49_rcl_cdenom2;
                    v_ydecldp_var_49_rcl_cdenom2 = (double*)(&(ydecldp_var_49->rcl_cdenom2));
                    double* v_ydecldp_var_49_rcl_cdenom3;
                    v_ydecldp_var_49_rcl_cdenom3 = (double*)(&(ydecldp_var_49->rcl_cdenom3));
                    double* v_ydecldp_var_49_rcl_const3r;
                    v_ydecldp_var_49_rcl_const3r = (double*)(&(ydecldp_var_49->rcl_const3r));
                    double* v_ydecldp_var_49_rcl_const4r;
                    v_ydecldp_var_49_rcl_const4r = (double*)(&(ydecldp_var_49->rcl_const4r));
                    double* v_ydecldp_var_49_rcl_const1r;
                    v_ydecldp_var_49_rcl_const1r = (double*)(&(ydecldp_var_49->rcl_const1r));
                    double* v_ydecldp_var_49_rcl_const2r;
                    v_ydecldp_var_49_rcl_const2r = (double*)(&(ydecldp_var_49->rcl_const2r));
                    double tmp_call_117_0;
                    double tmp_arg_71_0;

                    {
                        double zcovptot_0_in_0 = zcovptot[(_for_it_60 - 1)];
                        double zqxfg_0_in_0 = zqxfg[((_for_it_60 + (2 * sym_klon)) - 1)];
                        double zpreclr_out;

                        ///////////////////
                        // Tasklet code (T_l1063_c1063)
                        zpreclr_out = (zqxfg_0_in_0 / zcovptot_0_in_0);
                        ///////////////////

                        zpreclr = zpreclr_out;
                    }
                    {
                        double ydecldp_var_49_0_in_rdensref = v_ydecldp_var_49_rdensref[0];
                        double zrho_0_in_0 = zrho[(_for_it_60 - 1)];
                        double tmp_arg_52_out;

                        ///////////////////
                        // Tasklet code (T_l1064_c1064)
                        tmp_arg_52_out = (ydecldp_var_49_0_in_rdensref / zrho_0_in_0);
                        ///////////////////

                        tmp_arg_52 = tmp_arg_52_out;
                    }
                    {
                        double tmp_arg_52_0_in = tmp_arg_52;
                        double zfallcorr_out;

                        ///////////////////
                        // Tasklet code (T_l1064_c1064)
                        zfallcorr_out = dace::math::pow(tmp_arg_52_0_in, 0.4);
                        ///////////////////

                        zfallcorr = zfallcorr_out;
                    }
                    {
                        double zfallcorr_0_in = zfallcorr;
                        double zrho_0_in_0 = zrho[(_for_it_60 - 1)];
                        double tmp_arg_56_out;

                        ///////////////////
                        // Tasklet code (T_l1072_c1072)
                        tmp_arg_56_out = (zrho_0_in_0 * zfallcorr_0_in);
                        ///////////////////

                        tmp_arg_56 = tmp_arg_56_out;
                    }
                    {
                        double tmp_arg_56_0_in = tmp_arg_56;
                        double tmp_call_85_out;

                        ///////////////////
                        // Tasklet code (T_l1072_c1072)
                        tmp_call_85_out = dace::math::sqrt(tmp_arg_56_0_in);
                        ///////////////////

                        tmp_call_85 = tmp_call_85_out;
                    }
                    {
                        double ydecldp_var_49_0_in_rcl_fac1 = v_ydecldp_var_49_rcl_fac1[0];
                        double zpreclr_0_in = zpreclr;
                        double zrho_0_in_0 = zrho[(_for_it_60 - 1)];
                        double tmp_arg_53_out;

                        ///////////////////
                        // Tasklet code (T_l1067_c1067)
                        tmp_arg_53_out = (ydecldp_var_49_0_in_rcl_fac1 / (zrho_0_in_0 * zpreclr_0_in));
                        ///////////////////

                        tmp_arg_53 = tmp_arg_53_out;
                    }
                    {
                        double tmp_arg_53_0_in = tmp_arg_53;
                        double ydecldp_var_49_0_in_rcl_fac2 = v_ydecldp_var_49_rcl_fac2[0];
                        double zlambda_out;

                        ///////////////////
                        // Tasklet code (T_l1067_c1067)
                        zlambda_out = dace::math::pow(tmp_arg_53_0_in, ydecldp_var_49_0_in_rcl_fac2);
                        ///////////////////

                        zlambda = zlambda_out;
                    }
                    {
                        double ydecldp_var_49_0_in_rcl_const3r = v_ydecldp_var_49_rcl_const3r[0];
                        double zlambda_0_in = zlambda;
                        double tmp_call_87_out;

                        ///////////////////
                        // Tasklet code (T_l1072_c1072)
                        tmp_call_87_out = dace::math::pow(zlambda_0_in, ydecldp_var_49_0_in_rcl_const3r);
                        ///////////////////

                        tmp_call_87 = tmp_call_87_out;
                    }
                    {
                        double ydecldp_var_49_0_in_rcl_const4r = v_ydecldp_var_49_rcl_const4r[0];
                        double zlambda_0_in = zlambda;
                        double tmp_call_84_out;

                        ///////////////////
                        // Tasklet code (T_l1072_c1072)
                        tmp_call_84_out = dace::math::pow(zlambda_0_in, ydecldp_var_49_0_in_rcl_const4r);
                        ///////////////////

                        tmp_call_84 = tmp_call_84_out;
                    }
                    {
                        double ztp1_0_in_0 = ztp1[((_for_it_60 + (sym_klon * (_for_it_23 - 1))) - 1)];
                        double oka_out;

                        ///////////////////
                        // Tasklet code (T_l1065_c1065)
                        oka_out = ztp1_0_in_0;
                        ///////////////////

                        oka = oka_out;
                    }
                    {
                        double ztp1_0_in_0 = ztp1[((_for_it_60 + (sym_klon * (_for_it_23 - 1))) - 1)];
                        double tmp_call_81_out;

                        ///////////////////
                        // Tasklet code (T_l1068_c1068)
                        tmp_call_81_out = (dace::math::ipow(ztp1_0_in_0, 3));
                        ///////////////////

                        tmp_call_81 = tmp_call_81_out;
                    }
                    {
                        double ztp1_0_in_0 = ztp1[((_for_it_60 + (sym_klon * (_for_it_23 - 1))) - 1)];
                        double tmp_arg_54_out;

                        ///////////////////
                        // Tasklet code (T_l1069_c1069)
                        tmp_arg_54_out = (ztp1_0_in_0 / 273.0);
                        ///////////////////

                        tmp_arg_54 = tmp_arg_54_out;
                    }
                    {
                        double tmp_arg_54_0_in = tmp_arg_54;
                        double tmp_call_82_out;

                        ///////////////////
                        // Tasklet code (T_l1069_c1069)
                        tmp_call_82_out = dace::math::pow(tmp_arg_54_0_in, 1.5);
                        ///////////////////

                        tmp_call_82 = tmp_call_82_out;
                    }
                    {
                        double tmp_call_82_0_in = tmp_call_82;
                        double ztp1_0_in_0 = ztp1[((_for_it_60 + (sym_klon * (_for_it_23 - 1))) - 1)];
                        double zcorr2_out;

                        ///////////////////
                        // Tasklet code (T_l1069_c1069)
                        zcorr2_out = ((tmp_call_82_0_in * 393.0) / (ztp1_0_in_0 + 120.0));
                        ///////////////////

                        zcorr2 = zcorr2_out;
                    }
                    {
                        double zcorr2_0_in = zcorr2;
                        double tmp_call_86_out;

                        ///////////////////
                        // Tasklet code (T_l1072_c1072)
                        tmp_call_86_out = dace::math::sqrt(zcorr2_0_in);
                        ///////////////////

                        tmp_call_86 = tmp_call_86_out;
                    }
                    {
                        double ztp1_0_in_0 = ztp1[((_for_it_60 + (sym_klon * (_for_it_23 - 1))) - 1)];
                        double tmp_call_83_out;

                        ///////////////////
                        // Tasklet code (T_l1072_c1072)
                        tmp_call_83_out = (dace::math::ipow(ztp1_0_in_0, 2));
                        ///////////////////

                        tmp_call_83 = tmp_call_83_out;
                    }
                    {
                        double ptare_var_61_0_in = oka;
                        double ptare_var_61_1_in = oka;
                        double ydcst_var_63_0_in_rtt = v_ydcst_var_63_rtt[0];
                        double ydthf_var_62_0_in_r3les = v_ydthf_var_62_r3les[0];
                        double ydthf_var_62_1_in_r4les = v_ydthf_var_62_r4les[0];
                        double tmp_arg_71_out;

                        ///////////////////
                        // Tasklet code (T_l1394_c1394)
                        tmp_arg_71_out = ((ydthf_var_62_0_in_r3les * (ptare_var_61_0_in - ydcst_var_63_0_in_rtt)) / (ptare_var_61_1_in - ydthf_var_62_1_in_r4les));
                        ///////////////////

                        tmp_arg_71_0 = tmp_arg_71_out;
                    }
                    {
                        double tmp_arg_71_0_in = tmp_arg_71_0;
                        double tmp_call_117_out;

                        ///////////////////
                        // Tasklet code (T_l1394_c1394)
                        tmp_call_117_out = exp(tmp_arg_71_0_in);
                        ///////////////////

                        tmp_call_117_0 = tmp_call_117_out;
                    }
                    {
                        double tmp_call_117_0_in = tmp_call_117_0;
                        double ydthf_var_62_0_in_r2es = v_ydthf_var_62_r2es[0];
                        double foeeliq__ret_out;

                        ///////////////////
                        // Tasklet code (T_l1394_c1394)
                        foeeliq__ret_out = (ydthf_var_62_0_in_r2es * tmp_call_117_0_in);
                        ///////////////////

                        tmp_call_80 = foeeliq__ret_out;
                    }
                    {
                        double tmp_call_80_0_in = tmp_call_80;
                        double ydcst_var_47_0_in_rv = v_ydcst_var_47_rv[0];
                        double ydcst_var_47_1_in_rd = v_ydcst_var_47_rd[0];
                        double zesatliq_out;

                        ///////////////////
                        // Tasklet code (T_l1066_c1066)
                        zesatliq_out = ((ydcst_var_47_0_in_rv / ydcst_var_47_1_in_rd) * tmp_call_80_0_in);
                        ///////////////////

                        zesatliq = zesatliq_out;
                    }
                    {
                        double pap_var_17_0_in_0 = pap_var_17[((_for_it_60 + (sym_klon * (_for_it_23 - 1))) - 1)];
                        double tmp_call_81_0_in = tmp_call_81;
                        double ydecldp_var_49_0_in_rcl_cdenom1 = v_ydecldp_var_49_rcl_cdenom1[0];
                        double ydecldp_var_49_1_in_rcl_cdenom2 = v_ydecldp_var_49_rcl_cdenom2[0];
                        double ydecldp_var_49_2_in_rcl_cdenom3 = v_ydecldp_var_49_rcl_cdenom3[0];
                        double zesatliq_0_in = zesatliq;
                        double zesatliq_1_in = zesatliq;
                        double ztp1_0_in_0 = ztp1[((_for_it_60 + (sym_klon * (_for_it_23 - 1))) - 1)];
                        double zevap_denom_out;

                        ///////////////////
                        // Tasklet code (T_l1068_c1068)
                        zevap_denom_out =
                            (((ydecldp_var_49_0_in_rcl_cdenom1 * zesatliq_0_in) - ((ydecldp_var_49_1_in_rcl_cdenom2 * ztp1_0_in_0) * zesatliq_1_in)) +
                             ((ydecldp_var_49_2_in_rcl_cdenom3 * tmp_call_81_0_in) * pap_var_17_0_in_0));
                        ///////////////////

                        zevap_denom = zevap_denom_out;
                    }
                    {
                        double tmp_call_83_0_in = tmp_call_83;
                        double tmp_call_84_0_in = tmp_call_84;
                        double tmp_call_85_0_in = tmp_call_85;
                        double tmp_call_86_0_in = tmp_call_86;
                        double tmp_call_87_0_in = tmp_call_87;
                        double ydecldp_var_49_0_in_rcl_const1r = v_ydecldp_var_49_rcl_const1r[0];
                        double ydecldp_var_49_1_in_rcl_const2r = v_ydecldp_var_49_rcl_const2r[0];
                        double zcorr2_0_in = zcorr2;
                        double zesatliq_0_in = zesatliq;
                        double zevap_denom_0_in = zevap_denom;
                        double zqsliq_0_in_0 = zqsliq[((_for_it_60 + (sym_klon * (_for_it_23 - 1))) - 1)];
                        double zbeta_out;

                        ///////////////////
                        // Tasklet code (T_l1072_c1072)
                        zbeta_out =
                            ((((((0.5 / zqsliq_0_in_0) * tmp_call_83_0_in) * zesatliq_0_in) * ydecldp_var_49_0_in_rcl_const1r) * (zcorr2_0_in / zevap_denom_0_in)) *
                             ((0.78 / tmp_call_84_0_in) + ((ydecldp_var_49_1_in_rcl_const2r * tmp_call_85_0_in) / (tmp_call_86_0_in * tmp_call_87_0_in))));
                        ///////////////////

                        zbeta = zbeta_out;
                    }
                    {
                        double zqe_0_in = zqe;
                        double zqsliq_0_in_0 = zqsliq[((_for_it_60 + (sym_klon * (_for_it_23 - 1))) - 1)];
                        double zzrh_0_in = zzrh;
                        double tmp_arg_55_out;

                        ///////////////////
                        // Tasklet code (T_l1071_c1071)
                        tmp_arg_55_out = ((zzrh_0_in * zqsliq_0_in_0) - zqe_0_in);
                        ///////////////////

                        tmp_arg_55 = tmp_arg_55_out;
                    }
                    {
                        double tmp_arg_55_0_in = tmp_arg_55;
                        double zsubsat_out;

                        ///////////////////
                        // Tasklet code (T_l1071_c1071)
                        zsubsat_out = max(tmp_arg_55_0_in, 0.0);
                        ///////////////////

                        zsubsat = zsubsat_out;
                    }
                    {
                        double ptsphy_var_5_0_in = ptsphy_var_5[0];
                        double zbeta_0_in = zbeta;
                        double zdenom_out;

                        ///////////////////
                        // Tasklet code (T_l1073_c1073)
                        zdenom_out = (1.0 + (zbeta_0_in * ptsphy_var_5_0_in));
                        ///////////////////

                        zdenom = zdenom_out;
                    }
                    {
                        double ptsphy_var_5_0_in = ptsphy_var_5[0];
                        double zbeta_0_in = zbeta;
                        double zcovpclr_0_in_0 = zcovpclr[(_for_it_60 - 1)];
                        double zdenom_0_in = zdenom;
                        double zsubsat_0_in = zsubsat;
                        double zdpevap_out;

                        ///////////////////
                        // Tasklet code (T_l1074_c1074)
                        zdpevap_out = ((((zcovpclr_0_in_0 * zbeta_0_in) * ptsphy_var_5_0_in) * zsubsat_0_in) / zdenom_0_in);
                        ///////////////////

                        zdpevap = zdpevap_out;
                    }
                    {
                        double zdpevap_0_in = zdpevap;
                        double zqxfg_0_in_0 = zqxfg[((_for_it_60 + (2 * sym_klon)) - 1)];
                        double zevap_out;

                        ///////////////////
                        // Tasklet code (T_l1075_c1075)
                        zevap_out = min(zdpevap_0_in, zqxfg_0_in_0);
                        ///////////////////

                        zevap = zevap_out;
                    }
                    {
                        double zevap_0_in = zevap;
                        double zsolqa_0_in_0 = zsolqa[((_for_it_60 + (14 * sym_klon)) - 1)];
                        double zsolqa_out_0;

                        ///////////////////
                        // Tasklet code (T_l1076_c1076)
                        zsolqa_out_0 = (zsolqa_0_in_0 + zevap_0_in);
                        ///////////////////

                        zsolqa[((_for_it_60 + (14 * sym_klon)) - 1)] = zsolqa_out_0;
                    }
                    {
                        double zevap_0_in = zevap;
                        double zsolqa_0_in_0 = zsolqa[((_for_it_60 + (22 * sym_klon)) - 1)];
                        double zsolqa_out_0;

                        ///////////////////
                        // Tasklet code (T_l1077_c1077)
                        zsolqa_out_0 = (zsolqa_0_in_0 - zevap_0_in);
                        ///////////////////

                        zsolqa[((_for_it_60 + (22 * sym_klon)) - 1)] = zsolqa_out_0;
                    }
                    {
                        double za_0_in_0 = za[((_for_it_60 + (sym_klon * (_for_it_23 - 1))) - 1)];
                        double zcovptot_0_in_0 = zcovptot[(_for_it_60 - 1)];
                        double zevap_0_in = zevap;
                        double zqxfg_0_in_0 = zqxfg[((_for_it_60 + (2 * sym_klon)) - 1)];
                        double tmp_arg_57_out;

                        ///////////////////
                        // Tasklet code (T_l1078_c1078)
                        tmp_arg_57_out = (((zcovptot_0_in_0 - za_0_in_0) * zevap_0_in) / zqxfg_0_in_0);
                        ///////////////////

                        tmp_arg_57 = tmp_arg_57_out;
                    }
                    {
                        double tmp_arg_57_0_in = tmp_arg_57;
                        double tmp_call_89_out;

                        ///////////////////
                        // Tasklet code (T_l1078_c1078)
                        tmp_call_89_out = max(0.0, tmp_arg_57_0_in);
                        ///////////////////

                        tmp_call_89 = tmp_call_89_out;
                    }
                    {
                        double tmp_call_89_0_in = tmp_call_89;
                        double zcovptot_0_in_0 = zcovptot[(_for_it_60 - 1)];
                        double tmp_arg_58_out;

                        ///////////////////
                        // Tasklet code (T_l1078_c1078)
                        tmp_arg_58_out = (zcovptot_0_in_0 - tmp_call_89_0_in);
                        ///////////////////

                        tmp_arg_58 = tmp_arg_58_out;
                    }
                    {
                        double tmp_arg_58_0_in = tmp_arg_58;
                        double ydecldp_var_49_0_in_rcovpmin = v_ydecldp_var_49_rcovpmin[0];
                        double tmp_call_88_out;

                        ///////////////////
                        // Tasklet code (T_l1078_c1078)
                        tmp_call_88_out = max(ydecldp_var_49_0_in_rcovpmin, tmp_arg_58_0_in);
                        ///////////////////

                        tmp_call_88 = tmp_call_88_out;
                    }
                    {
                        double tmp_call_88_0_in = tmp_call_88;
                        double zcovptot_out_0;

                        ///////////////////
                        // Tasklet code (T_l1078_c1078)
                        zcovptot_out_0 = tmp_call_88_0_in;
                        ///////////////////

                        zcovptot[(_for_it_60 - 1)] = zcovptot_out_0;
                    }
                }
                {
                    {
                        double zevap_0_in = zevap;
                        double zqxfg_0_in_0 = zqxfg[((_for_it_60 + (2 * sym_klon)) - 1)];
                        double zqxfg_out_0;

                        ///////////////////
                        // Tasklet code (T_l1079_c1079)
                        zqxfg_out_0 = (zqxfg_0_in_0 - zevap_0_in);
                        ///////////////////

                        zqxfg[((_for_it_60 + (2 * sym_klon)) - 1)] = zqxfg_out_0;
                    }
                }
            }
        }
        for (_for_it_61 = 1; (_for_it_61 <= icend); _for_it_61 = (_for_it_61 + 1)) {
            {
                double tmp_call_90;
                double tmp_arg_59;

                {
                    double za_0_in_0 = za[((_for_it_61 + (sym_klon * (_for_it_23 - 1))) - 1)];
                    double tmp_arg_59_out;

                    ///////////////////
                    // Tasklet code (T_l1083_c1083)
                    tmp_arg_59_out = (1.0 - za_0_in_0);
                    ///////////////////

                    tmp_arg_59 = tmp_arg_59_out;
                }
                {
                    double tmp_arg_59_0_in = tmp_arg_59;
                    double zepsec_0_in = zepsec;
                    double tmp_call_90_out;

                    ///////////////////
                    // Tasklet code (T_l1083_c1083)
                    tmp_call_90_out = max(zepsec_0_in, tmp_arg_59_0_in);
                    ///////////////////

                    tmp_call_90 = tmp_call_90_out;
                }
                {
                    double tmp_call_90_0_in = tmp_call_90;
                    double ydecldp_var_49_0_in_rprecrhmax = v_ydecldp_var_49_rprecrhmax[0];
                    double ydecldp_var_49_1_in_rprecrhmax = v_ydecldp_var_49_rprecrhmax[0];
                    double zcovpmax_0_in_0 = zcovpmax[(_for_it_61 - 1)];
                    double zzrh_out;

                    ///////////////////
                    // Tasklet code (T_l1083_c1083)
                    zzrh_out = (ydecldp_var_49_0_in_rprecrhmax + (((1.0 - ydecldp_var_49_1_in_rprecrhmax) * zcovpmax_0_in_0) / tmp_call_90_0_in));
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
                    double ydecldp_var_49_0_in_rprecrhmax = v_ydecldp_var_49_rprecrhmax[0];
                    double zzrh_0_in = zzrh;
                    double tmp_call_91_out;

                    ///////////////////
                    // Tasklet code (T_l1084_c1084)
                    tmp_call_91_out = max(zzrh_0_in, ydecldp_var_49_0_in_rprecrhmax);
                    ///////////////////

                    tmp_call_91 = tmp_call_91_out;
                }
                {
                    double tmp_call_91_0_in = tmp_call_91;
                    double zzrh_out;

                    ///////////////////
                    // Tasklet code (T_l1084_c1084)
                    zzrh_out = min(tmp_call_91_0_in, 1.0);
                    ///////////////////

                    zzrh = zzrh_out;
                }
                {
                    double za_0_in_0 = za[((_for_it_61 + (sym_klon * (_for_it_23 - 1))) - 1)];
                    double tmp_arg_60_out;

                    ///////////////////
                    // Tasklet code (T_l1085_c1085)
                    tmp_arg_60_out = (1.0 - za_0_in_0);
                    ///////////////////

                    tmp_arg_60 = tmp_arg_60_out;
                }
                {
                    double tmp_arg_60_0_in = tmp_arg_60;
                    double zepsec_0_in = zepsec;
                    double tmp_call_92_out;

                    ///////////////////
                    // Tasklet code (T_l1085_c1085)
                    tmp_call_92_out = max(zepsec_0_in, tmp_arg_60_0_in);
                    ///////////////////

                    tmp_call_92 = tmp_call_92_out;
                }
                {
                    double tmp_call_92_0_in = tmp_call_92;
                    double za_0_in_0 = za[((_for_it_61 + (sym_klon * (_for_it_23 - 1))) - 1)];
                    double zqsice_0_in_0 = zqsice[((_for_it_61 + (sym_klon * (_for_it_23 - 1))) - 1)];
                    double zqx_0_in_0 = zqx[(((_for_it_61 + ((4 * sym_klev) * sym_klon)) + (sym_klon * (_for_it_23 - 1))) - 1)];
                    double zqe_out;

                    ///////////////////
                    // Tasklet code (T_l1085_c1085)
                    zqe_out = ((zqx_0_in_0 - (za_0_in_0 * zqsice_0_in_0)) / tmp_call_92_0_in);
                    ///////////////////

                    zqe = zqe_out;
                }
                {
                    double zqe_0_in = zqe;
                    double zqsice_0_in_0 = zqsice[((_for_it_61 + (sym_klon * (_for_it_23 - 1))) - 1)];
                    double tmp_call_93_out;

                    ///////////////////
                    // Tasklet code (T_l1086_c1086)
                    tmp_call_93_out = min(zqe_0_in, zqsice_0_in_0);
                    ///////////////////

                    tmp_call_93 = tmp_call_93_out;
                }
                {
                    double tmp_call_93_0_in = tmp_call_93;
                    double zqe_out;

                    ///////////////////
                    // Tasklet code (T_l1086_c1086)
                    zqe_out = max(0.0, tmp_call_93_0_in);
                    ///////////////////

                    zqe = zqe_out;
                }
                {
                    double zcovpclr_0_in_0 = zcovpclr[(_for_it_61 - 1)];
                    double zqe_0_in = zqe;
                    double zqsice_0_in_0 = zqsice[((_for_it_61 + (sym_klon * (_for_it_23 - 1))) - 1)];
                    double zqxfg_0_in_0 = zqxfg[((_for_it_61 + (3 * sym_klon)) - 1)];
                    double zzrh_0_in = zzrh;
                    int llo1_out;

                    ///////////////////
                    // Tasklet code (T_l1087_c1087)
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
                        // Tasklet code (T_l1089_c1089)
                        tmp_arg_61_out = (zcovptot_0_in_0 * zdtgdp_0_in_0);
                        ///////////////////

                        tmp_arg_61 = tmp_arg_61_out;
                    }
                    {
                        double tmp_arg_61_0_in = tmp_arg_61;
                        double tmp_call_101_out;

                        ///////////////////
                        // Tasklet code (T_l1089_c1089)
                        tmp_call_101_out = abs(tmp_arg_61_0_in);
                        ///////////////////

                        tmp_call_101 = tmp_call_101_out;
                    }
                    {
                        double tmp_call_101_0_in = tmp_call_101;
                        double zepsilon_0_in = zepsilon;
                        double tmp_call_99_out;

                        ///////////////////
                        // Tasklet code (T_l1089_c1089)
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
                            // Tasklet code (T_l1089_c1089)
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
                            // Tasklet code (T_l1089_c1089)
                            tmp_call_0_out = abs(tmp_call_99_0_in);
                            ///////////////////

                            tmp_call_0 = tmp_call_0_out;
                        }
                        {
                            double tmp_call_0_0_in = tmp_call_0;
                            double tmp_call_94_out;

                            ///////////////////
                            // Tasklet code (T_l1089_c1089)
                            tmp_call_94_out = (-tmp_call_0_0_in);
                            ///////////////////

                            tmp_call_94 = tmp_call_94_out;
                        }
                    }
                }
                tmp_index_1572 = ((klev[0] + 1) - 1);
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
                    double* v_ydecldp_var_49_rvrfactor;
                    v_ydecldp_var_49_rvrfactor = (double*)(&(ydecldp_var_49->rvrfactor));
                    double* v_ydecldp_var_49_rpecons;
                    v_ydecldp_var_49_rpecons = (double*)(&(ydecldp_var_49->rpecons));

                    {
                        double tmp_call_94_0_in = tmp_call_94;
                        double zcovpclr_0_in_0 = zcovpclr[(_for_it_61 - 1)];
                        double zqxfg_0_in_0 = zqxfg[((_for_it_61 + (3 * sym_klon)) - 1)];
                        double zpreclr_out;

                        ///////////////////
                        // Tasklet code (T_l1089_c1089)
                        zpreclr_out = ((zqxfg_0_in_0 * zcovpclr_0_in_0) / tmp_call_94_0_in);
                        ///////////////////

                        zpreclr = zpreclr_out;
                    }
                    {
                        double zcovpclr_0_in_0 = zcovpclr[(_for_it_61 - 1)];
                        double zepsec_0_in = zepsec;
                        double tmp_call_96_out;

                        ///////////////////
                        // Tasklet code (T_l1090_c1090)
                        tmp_call_96_out = max(zcovpclr_0_in_0, zepsec_0_in);
                        ///////////////////

                        tmp_call_96 = tmp_call_96_out;
                    }
                    {
                        double pap_var_17_0_in_0 = pap_var_17[((_for_it_61 + (sym_klon * (_for_it_23 - 1))) - 1)];
                        double paph_var_18_0_in_0 = paph_var_18[((_for_it_61 + (sym_klon * tmp_index_1572)) - 1)];
                        double tmp_arg_62_out;

                        ///////////////////
                        // Tasklet code (T_l1090_c1090)
                        tmp_arg_62_out = (pap_var_17_0_in_0 / paph_var_18_0_in_0);
                        ///////////////////

                        tmp_arg_62 = tmp_arg_62_out;
                    }
                    {
                        double tmp_arg_62_0_in = tmp_arg_62;
                        double tmp_call_95_out;

                        ///////////////////
                        // Tasklet code (T_l1090_c1090)
                        tmp_call_95_out = sqrt(tmp_arg_62_0_in);
                        ///////////////////

                        tmp_call_95 = tmp_call_95_out;
                    }
                    {
                        double tmp_call_95_0_in = tmp_call_95;
                        double tmp_call_96_0_in = tmp_call_96;
                        double ydecldp_var_49_0_in_rvrfactor = v_ydecldp_var_49_rvrfactor[0];
                        double zpreclr_0_in = zpreclr;
                        double zbeta1_out;

                        ///////////////////
                        // Tasklet code (T_l1090_c1090)
                        zbeta1_out = (((tmp_call_95_0_in / ydecldp_var_49_0_in_rvrfactor) * zpreclr_0_in) / tmp_call_96_0_in);
                        ///////////////////

                        zbeta1 = zbeta1_out;
                    }
                    {
                        double zbeta1_0_in = zbeta1;
                        double tmp_arg_63_out;

                        ///////////////////
                        // Tasklet code (T_l1091_c1091)
                        tmp_arg_63_out = zbeta1_0_in;
                        ///////////////////

                        tmp_arg_63 = tmp_arg_63_out;
                    }
                    {
                        double tmp_arg_63_0_in = tmp_arg_63;
                        double tmp_call_97_out;

                        ///////////////////
                        // Tasklet code (T_l1091_c1091)
                        tmp_call_97_out = dace::math::pow(tmp_arg_63_0_in, 0.5777);
                        ///////////////////

                        tmp_call_97 = tmp_call_97_out;
                    }
                    {
                        double tmp_call_97_0_in = tmp_call_97;
                        double ydcst_var_47_0_in_rg = v_ydcst_var_47_rg[0];
                        double ydecldp_var_49_0_in_rpecons = v_ydecldp_var_49_rpecons[0];
                        double zbeta_out;

                        ///////////////////
                        // Tasklet code (T_l1091_c1091)
                        zbeta_out = ((ydcst_var_47_0_in_rg * ydecldp_var_49_0_in_rpecons) * tmp_call_97_0_in);
                        ///////////////////

                        zbeta = zbeta_out;
                    }
                    {
                        double ptsphy_var_5_0_in = ptsphy_var_5[0];
                        double zbeta_0_in = zbeta;
                        double zcorqsice_0_in_0 = zcorqsice[(_for_it_61 - 1)];
                        double zdenom_out;

                        ///////////////////
                        // Tasklet code (T_l1092_c1092)
                        zdenom_out = (1.0 + ((zbeta_0_in * ptsphy_var_5_0_in) * zcorqsice_0_in_0));
                        ///////////////////

                        zdenom = zdenom_out;
                    }
                    {
                        double zbeta_0_in = zbeta;
                        double zcovpclr_0_in_0 = zcovpclr[(_for_it_61 - 1)];
                        double zdenom_0_in = zdenom;
                        double zdp_0_in_0 = zdp[(_for_it_61 - 1)];
                        double zqe_0_in = zqe;
                        double zqsice_0_in_0 = zqsice[((_for_it_61 + (sym_klon * (_for_it_23 - 1))) - 1)];
                        double zrg_r_0_in = zrg_r;
                        double zdpr_out;

                        ///////////////////
                        // Tasklet code (T_l1093_c1093)
                        zdpr_out = (((((zcovpclr_0_in_0 * zbeta_0_in) * (zqsice_0_in_0 - zqe_0_in)) / zdenom_0_in) * zdp_0_in_0) * zrg_r_0_in);
                        ///////////////////

                        zdpr = zdpr_out;
                    }
                    {
                        double zdpr_0_in = zdpr;
                        double zdtgdp_0_in_0 = zdtgdp[(_for_it_61 - 1)];
                        double zdpevap_out;

                        ///////////////////
                        // Tasklet code (T_l1094_c1094)
                        zdpevap_out = (zdpr_0_in * zdtgdp_0_in_0);
                        ///////////////////

                        zdpevap = zdpevap_out;
                    }
                    {
                        double zdpevap_0_in = zdpevap;
                        double zqxfg_0_in_0 = zqxfg[((_for_it_61 + (3 * sym_klon)) - 1)];
                        double zevap_out;

                        ///////////////////
                        // Tasklet code (T_l1095_c1095)
                        zevap_out = min(zdpevap_0_in, zqxfg_0_in_0);
                        ///////////////////

                        zevap = zevap_out;
                    }
                    {
                        double zevap_0_in = zevap;
                        double zsolqa_0_in_0 = zsolqa[((_for_it_61 + (19 * sym_klon)) - 1)];
                        double zsolqa_out_0;

                        ///////////////////
                        // Tasklet code (T_l1096_c1096)
                        zsolqa_out_0 = (zsolqa_0_in_0 + zevap_0_in);
                        ///////////////////

                        zsolqa[((_for_it_61 + (19 * sym_klon)) - 1)] = zsolqa_out_0;
                    }
                    {
                        double zevap_0_in = zevap;
                        double zsolqa_0_in_0 = zsolqa[((_for_it_61 + (23 * sym_klon)) - 1)];
                        double zsolqa_out_0;

                        ///////////////////
                        // Tasklet code (T_l1097_c1097)
                        zsolqa_out_0 = (zsolqa_0_in_0 - zevap_0_in);
                        ///////////////////

                        zsolqa[((_for_it_61 + (23 * sym_klon)) - 1)] = zsolqa_out_0;
                    }
                    {
                        double za_0_in_0 = za[((_for_it_61 + (sym_klon * (_for_it_23 - 1))) - 1)];
                        double zcovptot_0_in_0 = zcovptot[(_for_it_61 - 1)];
                        double zevap_0_in = zevap;
                        double zqxfg_0_in_0 = zqxfg[((_for_it_61 + (3 * sym_klon)) - 1)];
                        double tmp_arg_64_out;

                        ///////////////////
                        // Tasklet code (T_l1098_c1098)
                        tmp_arg_64_out = (((zcovptot_0_in_0 - za_0_in_0) * zevap_0_in) / zqxfg_0_in_0);
                        ///////////////////

                        tmp_arg_64 = tmp_arg_64_out;
                    }
                    {
                        double tmp_arg_64_0_in = tmp_arg_64;
                        double tmp_call_100_out;

                        ///////////////////
                        // Tasklet code (T_l1098_c1098)
                        tmp_call_100_out = max(0.0, tmp_arg_64_0_in);
                        ///////////////////

                        tmp_call_100 = tmp_call_100_out;
                    }
                    {
                        double tmp_call_100_0_in = tmp_call_100;
                        double zcovptot_0_in_0 = zcovptot[(_for_it_61 - 1)];
                        double tmp_arg_65_out;

                        ///////////////////
                        // Tasklet code (T_l1098_c1098)
                        tmp_arg_65_out = (zcovptot_0_in_0 - tmp_call_100_0_in);
                        ///////////////////

                        tmp_arg_65 = tmp_arg_65_out;
                    }
                    {
                        double tmp_arg_65_0_in = tmp_arg_65;
                        double ydecldp_var_49_0_in_rcovpmin = v_ydecldp_var_49_rcovpmin[0];
                        double tmp_call_98_out;

                        ///////////////////
                        // Tasklet code (T_l1098_c1098)
                        tmp_call_98_out = max(ydecldp_var_49_0_in_rcovpmin, tmp_arg_65_0_in);
                        ///////////////////

                        tmp_call_98 = tmp_call_98_out;
                    }
                    {
                        double tmp_call_98_0_in = tmp_call_98;
                        double zcovptot_out_0;

                        ///////////////////
                        // Tasklet code (T_l1098_c1098)
                        zcovptot_out_0 = tmp_call_98_0_in;
                        ///////////////////

                        zcovptot[(_for_it_61 - 1)] = zcovptot_out_0;
                    }
                }
                {
                    {
                        double zevap_0_in = zevap;
                        double zqxfg_0_in_0 = zqxfg[((_for_it_61 + (3 * sym_klon)) - 1)];
                        double zqxfg_out_0;

                        ///////////////////
                        // Tasklet code (T_l1099_c1099)
                        zqxfg_out_0 = (zqxfg_0_in_0 - zevap_0_in);
                        ///////////////////

                        zqxfg[((_for_it_61 + (3 * sym_klon)) - 1)] = zqxfg_out_0;
                    }
                }
            }
        }
        for (_for_it_62 = 1; (_for_it_62 <= 5); _for_it_62 = (_for_it_62 + 1)) {
            _if_cond_73 = llfall[(_for_it_62 - 1)];
            if ((_if_cond_73 == 1)) {
                for (_for_it_63 = 1; (_for_it_63 <= icend); _for_it_63 = (_for_it_63 + 1)) {
                    {
                        {
                            double ydecldp_var_49_0_in_rlmin = v_ydecldp_var_49_rlmin[0];
                            double zqxfg_0_in_0 = zqxfg[((_for_it_63 + (sym_klon * (_for_it_62 - 1))) - 1)];
                            double _if_cond_74_out;

                            ///////////////////
                            // Tasklet code (T_l0_c0)
                            _if_cond_74_out = (zqxfg_0_in_0 < ydecldp_var_49_0_in_rlmin);
                            ///////////////////

                            _if_cond_74 = _if_cond_74_out;
                        }
                    }
                    if ((_if_cond_74 == 1)) {
                        {
                            {
                                double zqxfg_0_in_0 = zqxfg[((_for_it_63 + (sym_klon * (_for_it_62 - 1))) - 1)];
                                double zsolqa_0_in_0 = zsolqa[(((_for_it_63 + ((5 * sym_klon) * (_for_it_62 - 1))) + (4 * sym_klon)) - 1)];
                                double zsolqa_out_0;

                                ///////////////////
                                // Tasklet code (T_l1106_c1106)
                                zsolqa_out_0 = (zsolqa_0_in_0 + zqxfg_0_in_0);
                                ///////////////////

                                zsolqa[(((_for_it_63 + ((5 * sym_klon) * (_for_it_62 - 1))) + (4 * sym_klon)) - 1)] = zsolqa_out_0;
                            }
                            {
                                double zqxfg_0_in_0 = zqxfg[((_for_it_63 + (sym_klon * (_for_it_62 - 1))) - 1)];
                                double zsolqa_0_in_0 = zsolqa[(((_for_it_63 + (sym_klon * (_for_it_62 - 1))) + (20 * sym_klon)) - 1)];
                                double zsolqa_out_0;

                                ///////////////////
                                // Tasklet code (T_l1107_c1107)
                                zsolqa_out_0 = (zsolqa_0_in_0 - zqxfg_0_in_0);
                                ///////////////////

                                zsolqa[(((_for_it_63 + (sym_klon * (_for_it_62 - 1))) + (20 * sym_klon)) - 1)] = zsolqa_out_0;
                            }
                        }
                    }
                }
            }
        }
        for (_for_it_64 = 1; (_for_it_64 <= icend); _for_it_64 = (_for_it_64 + 1)) {
            {
                {
                    double za_0_in_0 = za[((_for_it_64 + (sym_klon * (_for_it_23 - 1))) - 1)];
                    double zsolab_0_in_0 = zsolab[(_for_it_64 - 1)];
                    double zsolac_0_in_0 = zsolac[(_for_it_64 - 1)];
                    double zanew_out;

                    ///////////////////
                    // Tasklet code (T_l1113_c1113)
                    zanew_out = ((za_0_in_0 + zsolac_0_in_0) / (1.0 + zsolab_0_in_0));
                    ///////////////////

                    zanew = zanew_out;
                }
                {
                    double zanew_0_in = zanew;
                    double zanew_out;

                    ///////////////////
                    // Tasklet code (T_l1114_c1114)
                    zanew_out = min(zanew_0_in, 1.0);
                    ///////////////////

                    zanew = zanew_out;
                }
                {
                    double ydecldp_var_49_0_in_ramin = v_ydecldp_var_49_ramin[0];
                    double zanew_0_in = zanew;
                    double _if_cond_75_out;

                    ///////////////////
                    // Tasklet code (T_l1115_c1115)
                    _if_cond_75_out = (zanew_0_in < ydecldp_var_49_0_in_ramin);
                    ///////////////////

                    _if_cond_75 = _if_cond_75_out;
                }
            }
            if ((_if_cond_75 == 1)) {
                {
                    {
                        double zanew_out;

                        ///////////////////
                        // Tasklet code (T_l1115_c1115)
                        zanew_out = 0.0;
                        ///////////////////

                        zanew = zanew_out;
                    }
                }
            }
            {
                {
                    double zanew_0_in = zanew;
                    double zaorig_0_in_0 = zaorig[((_for_it_64 + (sym_klon * (_for_it_23 - 1))) - 1)];
                    double zda_out_0;

                    ///////////////////
                    // Tasklet code (T_l1116_c1116)
                    zda_out_0 = (zanew_0_in - zaorig_0_in_0);
                    ///////////////////

                    zda[(_for_it_64 - 1)] = zda_out_0;
                }
                {
                    double zanew_0_in = zanew;
                    double zanewm1_out_0;

                    ///////////////////
                    // Tasklet code (T_l1117_c1117)
                    zanewm1_out_0 = zanew_0_in;
                    ///////////////////

                    zanewm1[(_for_it_64 - 1)] = zanewm1_out_0;
                }
            }
        }
        for (_for_it_65 = 1; (_for_it_65 <= 5); _for_it_65 = (_for_it_65 + 1)) {
            for (_for_it_66 = 1; (_for_it_66 <= 5); _for_it_66 = (_for_it_66 + 1)) {
                for (_for_it_67 = 1; (_for_it_67 <= icend); _for_it_67 = (_for_it_67 + 1)) {
                    {
                        {
                            int llindex3_out_0;

                            ///////////////////
                            // Tasklet code (T_l1122_c1122)
                            llindex3_out_0 = 0;
                            ///////////////////

                            llindex3[(((_for_it_67 + ((5 * sym_klon) * (_for_it_65 - 1))) + (sym_klon * (_for_it_66 - 1))) - 1)] = llindex3_out_0;
                        }
                    }
                }
            }
            for (_for_it_68 = 1; (_for_it_68 <= icend); _for_it_68 = (_for_it_68 + 1)) {
                {
                    {
                        double zsinksum_out_0;

                        ///////////////////
                        // Tasklet code (T_l1126_c1126)
                        zsinksum_out_0 = 0.0;
                        ///////////////////

                        zsinksum[((_for_it_68 + (sym_klon * (_for_it_65 - 1))) - 1)] = zsinksum_out_0;
                    }
                }
            }
        }
        for (_for_it_69 = 1; (_for_it_69 <= 5); _for_it_69 = (_for_it_69 + 1)) {
            for (_for_it_70 = 1; (_for_it_70 <= 5); _for_it_70 = (_for_it_70 + 1)) {
                for (_for_it_71 = 1; (_for_it_71 <= icend); _for_it_71 = (_for_it_71 + 1)) {
                    {
                        {
                            double zsinksum_0_in_0 = zsinksum[((_for_it_71 + (sym_klon * (_for_it_69 - 1))) - 1)];
                            double zsolqa_0_in_0 = zsolqa[(((_for_it_71 + (sym_klon * (_for_it_69 - 1))) + ((5 * sym_klon) * (_for_it_70 - 1))) - 1)];
                            double zsinksum_out_0;

                            ///////////////////
                            // Tasklet code (T_l1132_c1132)
                            zsinksum_out_0 = (zsinksum_0_in_0 - zsolqa_0_in_0);
                            ///////////////////

                            zsinksum[((_for_it_71 + (sym_klon * (_for_it_69 - 1))) - 1)] = zsinksum_out_0;
                        }
                    }
                }
            }
        }
        for (_for_it_72 = 1; (_for_it_72 <= 5); _for_it_72 = (_for_it_72 + 1)) {
            for (_for_it_73 = 1; (_for_it_73 <= icend); _for_it_73 = (_for_it_73 + 1)) {
                {
                    double zmax;
                    double zrat;

                    {
                        double zepsec_0_in = zepsec;
                        double zqx_0_in_0 = zqx[(((_for_it_73 + ((sym_klev * sym_klon) * (_for_it_72 - 1))) + (sym_klon * (_for_it_23 - 1))) - 1)];
                        double zmax_out;

                        ///////////////////
                        // Tasklet code (T_l1138_c1138)
                        zmax_out = max(zqx_0_in_0, zepsec_0_in);
                        ///////////////////

                        zmax = zmax_out;
                    }
                    {
                        double zmax_0_in = zmax;
                        double zsinksum_0_in_0 = zsinksum[((_for_it_73 + (sym_klon * (_for_it_72 - 1))) - 1)];
                        double zrat_out;

                        ///////////////////
                        // Tasklet code (T_l1139_c1139)
                        zrat_out = max(zsinksum_0_in_0, zmax_0_in);
                        ///////////////////

                        zrat = zrat_out;
                    }
                    {
                        double zmax_0_in = zmax;
                        double zrat_0_in = zrat;
                        double zratio_out_0;

                        ///////////////////
                        // Tasklet code (T_l1140_c1140)
                        zratio_out_0 = (zmax_0_in / zrat_0_in);
                        ///////////////////

                        zratio[((_for_it_73 + (sym_klon * (_for_it_72 - 1))) - 1)] = zratio_out_0;
                    }
                }
            }
        }
        for (_for_it_74 = 1; (_for_it_74 <= 5); _for_it_74 = (_for_it_74 + 1)) {
            for (_for_it_75 = 1; (_for_it_75 <= icend); _for_it_75 = (_for_it_75 + 1)) {
                {
                    {
                        int iorder_out_0;

                        ///////////////////
                        // Tasklet code (T_l1145_c1145)
                        iorder_out_0 = -999;
                        ///////////////////

                        iorder[((_for_it_75 + (sym_klon * (_for_it_74 - 1))) - 1)] = iorder_out_0;
                    }
                }
            }
        }
        for (_for_it_76 = 1; (_for_it_76 <= 5); _for_it_76 = (_for_it_76 + 1)) {
            for (_for_it_77 = 1; (_for_it_77 <= icend); _for_it_77 = (_for_it_77 + 1)) {
                {
                    {
                        int llindex1_out_0;

                        ///////////////////
                        // Tasklet code (T_l1150_c1150)
                        llindex1_out_0 = 1;
                        ///////////////////

                        llindex1[((_for_it_77 + (sym_klon * (_for_it_76 - 1))) - 1)] = llindex1_out_0;
                    }
                }
            }
        }
        for (_for_it_78 = 1; (_for_it_78 <= 5); _for_it_78 = (_for_it_78 + 1)) {
            for (_for_it_79 = 1; (_for_it_79 <= icend); _for_it_79 = (_for_it_79 + 1)) {
                {
                    {
                        double zmin_out_0;

                        ///////////////////
                        // Tasklet code (T_l1155_c1155)
                        zmin_out_0 = 1e+32;
                        ///////////////////

                        zmin[(_for_it_79 - 1)] = zmin_out_0;
                    }
                }
            }
            for (_for_it_80 = 1; (_for_it_80 <= 5); _for_it_80 = (_for_it_80 + 1)) {
                for (_for_it_81 = 1; (_for_it_81 <= icend); _for_it_81 = (_for_it_81 + 1)) {
                    _if_cond_76 = (llindex1[((_for_it_81 + (sym_klon * (_for_it_80 - 1))) - 1)] && (zratio[((_for_it_81 + (sym_klon * (_for_it_80 - 1))) - 1)] < zmin[(_for_it_81 - 1)]));
                    if ((_if_cond_76 == 1)) {
                        {
                            {
                                int iorder_out_0;

                                ///////////////////
                                // Tasklet code (T_l1160_c1160)
                                iorder_out_0 = _for_it_80;
                                ///////////////////

                                iorder[((_for_it_81 + (sym_klon * (_for_it_78 - 1))) - 1)] = iorder_out_0;
                            }
                            {
                                double zratio_0_in_0 = zratio[((_for_it_81 + (sym_klon * (_for_it_80 - 1))) - 1)];
                                double zmin_out_0;

                                ///////////////////
                                // Tasklet code (T_l1161_c1161)
                                zmin_out_0 = zratio_0_in_0;
                                ///////////////////

                                zmin[(_for_it_81 - 1)] = zmin_out_0;
                            }
                        }
                    }
                }
            }
            for (_for_it_82 = 1; (_for_it_82 <= icend); _for_it_82 = (_for_it_82 + 1)) {
                tmp_index_1668 = (iorder[((_for_it_82 + (sym_klon * (_for_it_78 - 1))) - 1)] - 1);
                {
                    {
                        int llindex1_out_0;

                        ///////////////////
                        // Tasklet code (T_l1166_c1166)
                        llindex1_out_0 = 0;
                        ///////////////////

                        llindex1[((_for_it_82 + (sym_klon * tmp_index_1668)) - 1)] = llindex1_out_0;
                    }
                }
            }
        }
        for (_for_it_83 = 1; (_for_it_83 <= 5); _for_it_83 = (_for_it_83 + 1)) {
            for (_for_it_84 = 1; (_for_it_84 <= icend); _for_it_84 = (_for_it_84 + 1)) {
                {
                    {
                        double zsinksum_out_0;

                        ///////////////////
                        // Tasklet code (T_l1171_c1171)
                        zsinksum_out_0 = 0.0;
                        ///////////////////

                        zsinksum[((_for_it_84 + (sym_klon * (_for_it_83 - 1))) - 1)] = zsinksum_out_0;
                    }
                }
            }
        }
        for (_for_it_85 = 1; (_for_it_85 <= 5); _for_it_85 = (_for_it_85 + 1)) {
            for (_for_it_86 = 1; (_for_it_86 <= icend); _for_it_86 = (_for_it_86 + 1)) {
                jo = iorder[((_for_it_86 + (sym_klon * (_for_it_85 - 1))) - 1)];
                for (_for_it_87 = 1; (_for_it_87 <= 5); _for_it_87 = (_for_it_87 + 1)) {
                    {
                        {
                            double zsolqa_0_in_0 = zsolqa[(((_for_it_86 + ((5 * sym_klon) * (_for_it_87 - 1))) + (sym_klon * (jo - 1))) - 1)];
                            int llindex3_out_0;

                            ///////////////////
                            // Tasklet code (T_l1178_c1178)
                            llindex3_out_0 = (zsolqa_0_in_0 < 0.0);
                            ///////////////////

                            llindex3[(((_for_it_86 + ((5 * sym_klon) * (_for_it_87 - 1))) + (sym_klon * (jo - 1))) - 1)] = llindex3_out_0;
                        }
                    }
                }
                {
                    {
                        double tmp_call_102_out;

                        ///////////////////
                        // Tasklet code (T_l1180_c1180)
                        tmp_call_102_out = 0;
                        ///////////////////

                        tmp_call_102 = tmp_call_102_out;
                    }
                }
                for (tmp_parfor_0 = 1; (tmp_parfor_0 <= 5); tmp_parfor_0 = (tmp_parfor_0 + 1)) {
                    {
                        {
                            double tmp_call_102_0_in = tmp_call_102;
                            double zsolqa_0_in_0 = zsolqa[(((_for_it_86 + (sym_klon * (jo - 1))) + ((5 * sym_klon) * (tmp_parfor_0 - 1))) - 1)];
                            double tmp_call_102_out;

                            ///////////////////
                            // Tasklet code (T_l1180_c1180)
                            tmp_call_102_out = (tmp_call_102_0_in + zsolqa_0_in_0);
                            ///////////////////

                            tmp_call_102 = tmp_call_102_out;
                        }
                    }
                }
                {
                    {
                        double tmp_call_102_0_in = tmp_call_102;
                        double zsinksum_0_in_0 = zsinksum[((_for_it_86 + (sym_klon * (jo - 1))) - 1)];
                        double zsinksum_out_0;

                        ///////////////////
                        // Tasklet code (T_l1180_c1180)
                        zsinksum_out_0 = (zsinksum_0_in_0 - tmp_call_102_0_in);
                        ///////////////////

                        zsinksum[((_for_it_86 + (sym_klon * (jo - 1))) - 1)] = zsinksum_out_0;
                    }
                }
            }
            for (_for_it_88 = 1; (_for_it_88 <= icend); _for_it_88 = (_for_it_88 + 1)) {
                jo = iorder[((_for_it_88 + (sym_klon * (_for_it_85 - 1))) - 1)];
                {
                    double zmm;
                    double zrr;

                    {
                        double zepsec_0_in = zepsec;
                        double zqx_0_in_0 = zqx[(((_for_it_88 + ((sym_klev * sym_klon) * (jo - 1))) + (sym_klon * (_for_it_23 - 1))) - 1)];
                        double zmm_out;

                        ///////////////////
                        // Tasklet code (T_l1184_c1184)
                        zmm_out = max(zqx_0_in_0, zepsec_0_in);
                        ///////////////////

                        zmm = zmm_out;
                    }
                    {
                        double zmm_0_in = zmm;
                        double zsinksum_0_in_0 = zsinksum[((_for_it_88 + (sym_klon * (jo - 1))) - 1)];
                        double zrr_out;

                        ///////////////////
                        // Tasklet code (T_l1185_c1185)
                        zrr_out = max(zsinksum_0_in_0, zmm_0_in);
                        ///////////////////

                        zrr = zrr_out;
                    }
                    {
                        double zmm_0_in = zmm;
                        double zrr_0_in = zrr;
                        double zratio_out_0;

                        ///////////////////
                        // Tasklet code (T_l1186_c1186)
                        zratio_out_0 = (zmm_0_in / zrr_0_in);
                        ///////////////////

                        zratio[((_for_it_88 + (sym_klon * (jo - 1))) - 1)] = zratio_out_0;
                    }
                }
            }
            for (_for_it_89 = 1; (_for_it_89 <= icend); _for_it_89 = (_for_it_89 + 1)) {
                jo = iorder[((_for_it_89 + (sym_klon * (_for_it_85 - 1))) - 1)];
                {
                    {
                        double zratio_0_in_0 = zratio[((_for_it_89 + (sym_klon * (jo - 1))) - 1)];
                        double zzratio_out;

                        ///////////////////
                        // Tasklet code (T_l1190_c1190)
                        zzratio_out = zratio_0_in_0;
                        ///////////////////

                        zzratio = zzratio_out;
                    }
                }
                for (_for_it_90 = 1; (_for_it_90 <= 5); _for_it_90 = (_for_it_90 + 1)) {
                    _if_cond_77 = llindex3[(((_for_it_89 + ((5 * sym_klon) * (_for_it_90 - 1))) + (sym_klon * (jo - 1))) - 1)];
                    if ((_if_cond_77 == 1)) {
                        {
                            {
                                double zsolqa_0_in_0 = zsolqa[(((_for_it_89 + ((5 * sym_klon) * (_for_it_90 - 1))) + (sym_klon * (jo - 1))) - 1)];
                                double zzratio_0_in = zzratio;
                                double zsolqa_out_0;

                                ///////////////////
                                // Tasklet code (T_l1193_c1193)
                                zsolqa_out_0 = (zsolqa_0_in_0 * zzratio_0_in);
                                ///////////////////

                                zsolqa[(((_for_it_89 + ((5 * sym_klon) * (_for_it_90 - 1))) + (sym_klon * (jo - 1))) - 1)] = zsolqa_out_0;
                            }
                            {
                                double zsolqa_0_in_0 = zsolqa[(((_for_it_89 + (sym_klon * (_for_it_90 - 1))) + ((5 * sym_klon) * (jo - 1))) - 1)];
                                double zzratio_0_in = zzratio;
                                double zsolqa_out_0;

                                ///////////////////
                                // Tasklet code (T_l1194_c1194)
                                zsolqa_out_0 = (zsolqa_0_in_0 * zzratio_0_in);
                                ///////////////////

                                zsolqa[(((_for_it_89 + (sym_klon * (_for_it_90 - 1))) + ((5 * sym_klon) * (jo - 1))) - 1)] = zsolqa_out_0;
                            }
                        }
                    }
                }
            }
        }
        for (_for_it_91 = 1; (_for_it_91 <= 5); _for_it_91 = (_for_it_91 + 1)) {
            for (_for_it_92 = 1; (_for_it_92 <= 5); _for_it_92 = (_for_it_92 + 1)) {
                if (((_for_it_92 == _for_it_91) == 1)) {
                    for (_for_it_93 = 1; (_for_it_93 <= icend); _for_it_93 = (_for_it_93 + 1)) {
                        {
                            {
                                double zfallsink_0_in_0 = zfallsink[((_for_it_93 + (sym_klon * (_for_it_91 - 1))) - 1)];
                                double zqlhs_out_0;

                                ///////////////////
                                // Tasklet code (T_l1203_c1203)
                                zqlhs_out_0 = (1.0 + zfallsink_0_in_0);
                                ///////////////////

                                zqlhs[(((_for_it_93 + ((5 * sym_klon) * (_for_it_91 - 1))) + (sym_klon * (_for_it_92 - 1))) - 1)] = zqlhs_out_0;
                            }
                        }
                        for (_for_it_94 = 1; (_for_it_94 <= 5); _for_it_94 = (_for_it_94 + 1)) {
                            {
                                {
                                    double zqlhs_0_in_0 = zqlhs[(((_for_it_93 + ((5 * sym_klon) * (_for_it_91 - 1))) + (sym_klon * (_for_it_92 - 1))) - 1)];
                                    double zsolqb_0_in_0 = zsolqb[(((_for_it_93 + ((5 * sym_klon) * (_for_it_92 - 1))) + (sym_klon * (_for_it_94 - 1))) - 1)];
                                    double zqlhs_out_0;

                                    ///////////////////
                                    // Tasklet code (T_l1205_c1205)
                                    zqlhs_out_0 = (zqlhs_0_in_0 + zsolqb_0_in_0);
                                    ///////////////////

                                    zqlhs[(((_for_it_93 + ((5 * sym_klon) * (_for_it_91 - 1))) + (sym_klon * (_for_it_92 - 1))) - 1)] = zqlhs_out_0;
                                }
                            }
                        }
                    }
                } else {
                    for (_for_it_95 = 1; (_for_it_95 <= icend); _for_it_95 = (_for_it_95 + 1)) {
                        {
                            {
                                double zsolqb_0_in_0 = zsolqb[(((_for_it_95 + ((5 * sym_klon) * (_for_it_91 - 1))) + (sym_klon * (_for_it_92 - 1))) - 1)];
                                double zqlhs_out_0;

                                ///////////////////
                                // Tasklet code (T_l1210_c1210)
                                zqlhs_out_0 = (-zsolqb_0_in_0);
                                ///////////////////

                                zqlhs[(((_for_it_95 + ((5 * sym_klon) * (_for_it_91 - 1))) + (sym_klon * (_for_it_92 - 1))) - 1)] = zqlhs_out_0;
                            }
                        }
                    }
                }
            }
        }
        for (_for_it_96 = 1; (_for_it_96 <= 5); _for_it_96 = (_for_it_96 + 1)) {
            for (_for_it_97 = 1; (_for_it_97 <= icend); _for_it_97 = (_for_it_97 + 1)) {
                {
                    {
                        double zexplicit_out;

                        ///////////////////
                        // Tasklet code (T_l1217_c1217)
                        zexplicit_out = 0.0;
                        ///////////////////

                        zexplicit = zexplicit_out;
                    }
                }
                for (_for_it_98 = 1; (_for_it_98 <= 5); _for_it_98 = (_for_it_98 + 1)) {
                    {
                        {
                            double zexplicit_0_in = zexplicit;
                            double zsolqa_0_in_0 = zsolqa[(((_for_it_97 + (sym_klon * (_for_it_96 - 1))) + ((5 * sym_klon) * (_for_it_98 - 1))) - 1)];
                            double zexplicit_out;

                            ///////////////////
                            // Tasklet code (T_l1219_c1219)
                            zexplicit_out = (zexplicit_0_in + zsolqa_0_in_0);
                            ///////////////////

                            zexplicit = zexplicit_out;
                        }
                    }
                }
                {
                    {
                        double zexplicit_0_in = zexplicit;
                        double zqx_0_in_0 = zqx[(((_for_it_97 + ((sym_klev * sym_klon) * (_for_it_96 - 1))) + (sym_klon * (_for_it_23 - 1))) - 1)];
                        double zqxn_out_0;

                        ///////////////////
                        // Tasklet code (T_l1221_c1221)
                        zqxn_out_0 = (zqx_0_in_0 + zexplicit_0_in);
                        ///////////////////

                        zqxn[((_for_it_97 + (sym_klon * (_for_it_96 - 1))) - 1)] = zqxn_out_0;
                    }
                }
            }
        }
        for (_for_it_99 = 1; (_for_it_99 <= 4); _for_it_99 = (_for_it_99 + 1)) {
            for (_for_it_100 = (_for_it_99 + 1); (_for_it_100 <= 5); _for_it_100 = (_for_it_100 + 1)) {
                for (tmp_parfor_52 = 1; (tmp_parfor_52 <= icend); tmp_parfor_52 = (tmp_parfor_52 + 1)) {
                    {
                        {
                            double zqlhs_0_in_0 = zqlhs[((((sym_klon * (_for_it_100 - 1)) + ((5 * sym_klon) * (_for_it_99 - 1))) + tmp_parfor_52) - 1)];
                            double zqlhs_1_in_0 = zqlhs[((((6 * sym_klon) * (_for_it_99 - 1)) + tmp_parfor_52) - 1)];
                            double zqlhs_out_0;

                            ///////////////////
                            // Tasklet code (T_l1226_c1226)
                            zqlhs_out_0 = (zqlhs_0_in_0 / zqlhs_1_in_0);
                            ///////////////////

                            zqlhs[((((sym_klon * (_for_it_100 - 1)) + ((5 * sym_klon) * (_for_it_99 - 1))) + tmp_parfor_52) - 1)] = zqlhs_out_0;
                        }
                    }
                }
                for (_for_it_101 = (_for_it_99 + 1); (_for_it_101 <= 5); _for_it_101 = (_for_it_101 + 1)) {
                    for (_for_it_102 = 1; (_for_it_102 <= icend); _for_it_102 = (_for_it_102 + 1)) {
                        {
                            {
                                double zqlhs_0_in_0 = zqlhs[(((_for_it_102 + (sym_klon * (_for_it_100 - 1))) + ((5 * sym_klon) * (_for_it_101 - 1))) - 1)];
                                double zqlhs_1_in_0 = zqlhs[(((_for_it_102 + (sym_klon * (_for_it_100 - 1))) + ((5 * sym_klon) * (_for_it_99 - 1))) - 1)];
                                double zqlhs_2_in_0 = zqlhs[(((_for_it_102 + ((5 * sym_klon) * (_for_it_101 - 1))) + (sym_klon * (_for_it_99 - 1))) - 1)];
                                double zqlhs_out_0;

                                ///////////////////
                                // Tasklet code (T_l1229_c1229)
                                zqlhs_out_0 = (zqlhs_0_in_0 - (zqlhs_1_in_0 * zqlhs_2_in_0));
                                ///////////////////

                                zqlhs[(((_for_it_102 + (sym_klon * (_for_it_100 - 1))) + ((5 * sym_klon) * (_for_it_101 - 1))) - 1)] = zqlhs_out_0;
                            }
                        }
                    }
                }
            }
        }
        for (_for_it_103 = 2; (_for_it_103 <= 5); _for_it_103 = (_for_it_103 + 1)) {
            for (_for_it_104 = 1; (_for_it_104 <= (_for_it_103 - 1)); _for_it_104 = (_for_it_104 + 1)) {
                for (tmp_parfor_53 = 1; (tmp_parfor_53 <= icend); tmp_parfor_53 = (tmp_parfor_53 + 1)) {
                    {
                        {
                            double zqlhs_0_in_0 = zqlhs[((((sym_klon * (_for_it_103 - 1)) + ((5 * sym_klon) * (_for_it_104 - 1))) + tmp_parfor_53) - 1)];
                            double zqxn_0_in_0 = zqxn[(((sym_klon * (_for_it_103 - 1)) + tmp_parfor_53) - 1)];
                            double zqxn_1_in_0 = zqxn[(((sym_klon * (_for_it_104 - 1)) + tmp_parfor_53) - 1)];
                            double zqxn_out_0;

                            ///////////////////
                            // Tasklet code (T_l1236_c1236)
                            zqxn_out_0 = (zqxn_0_in_0 - (zqlhs_0_in_0 * zqxn_1_in_0));
                            ///////////////////

                            zqxn[(((sym_klon * (_for_it_103 - 1)) + tmp_parfor_53) - 1)] = zqxn_out_0;
                        }
                    }
                }
            }
        }
        for (tmp_parfor_54 = 1; (tmp_parfor_54 <= icend); tmp_parfor_54 = (tmp_parfor_54 + 1)) {
            {
                {
                    double zqlhs_0_in_0 = zqlhs[(((24 * sym_klon) + tmp_parfor_54) - 1)];
                    double zqxn_0_in_0 = zqxn[(((4 * sym_klon) + tmp_parfor_54) - 1)];
                    double zqxn_out_0;

                    ///////////////////
                    // Tasklet code (T_l1239_c1239)
                    zqxn_out_0 = (zqxn_0_in_0 / zqlhs_0_in_0);
                    ///////////////////

                    zqxn[(((4 * sym_klon) + tmp_parfor_54) - 1)] = zqxn_out_0;
                }
            }
        }
        for (_for_it_105 = 4; (_for_it_105 >= 1); _for_it_105 = (_for_it_105 + -1)) {
            for (_for_it_106 = (_for_it_105 + 1); (_for_it_106 <= 5); _for_it_106 = (_for_it_106 + 1)) {
                for (tmp_parfor_55 = 1; (tmp_parfor_55 <= icend); tmp_parfor_55 = (tmp_parfor_55 + 1)) {
                    {
                        {
                            double zqlhs_0_in_0 = zqlhs[((((sym_klon * (_for_it_105 - 1)) + ((5 * sym_klon) * (_for_it_106 - 1))) + tmp_parfor_55) - 1)];
                            double zqxn_0_in_0 = zqxn[(((sym_klon * (_for_it_105 - 1)) + tmp_parfor_55) - 1)];
                            double zqxn_1_in_0 = zqxn[(((sym_klon * (_for_it_106 - 1)) + tmp_parfor_55) - 1)];
                            double zqxn_out_0;

                            ///////////////////
                            // Tasklet code (T_l1242_c1242)
                            zqxn_out_0 = (zqxn_0_in_0 - (zqlhs_0_in_0 * zqxn_1_in_0));
                            ///////////////////

                            zqxn[(((sym_klon * (_for_it_105 - 1)) + tmp_parfor_55) - 1)] = zqxn_out_0;
                        }
                    }
                }
            }
            for (tmp_parfor_56 = 1; (tmp_parfor_56 <= icend); tmp_parfor_56 = (tmp_parfor_56 + 1)) {
                {
                    {
                        double zqlhs_0_in_0 = zqlhs[((((6 * sym_klon) * (_for_it_105 - 1)) + tmp_parfor_56) - 1)];
                        double zqxn_0_in_0 = zqxn[(((sym_klon * (_for_it_105 - 1)) + tmp_parfor_56) - 1)];
                        double zqxn_out_0;

                        ///////////////////
                        // Tasklet code (T_l1244_c1244)
                        zqxn_out_0 = (zqxn_0_in_0 / zqlhs_0_in_0);
                        ///////////////////

                        zqxn[(((sym_klon * (_for_it_105 - 1)) + tmp_parfor_56) - 1)] = zqxn_out_0;
                    }
                }
            }
        }
        for (_for_it_107 = 1; (_for_it_107 <= 4); _for_it_107 = (_for_it_107 + 1)) {
            for (_for_it_108 = 1; (_for_it_108 <= icend); _for_it_108 = (_for_it_108 + 1)) {
                _if_cond_79 = (zqxn[((_for_it_108 + (sym_klon * (_for_it_107 - 1))) - 1)] < 1e-14);
                if ((_if_cond_79 == 1)) {
                    {
                        {
                            double zqxn_0_in_0 = zqxn[((_for_it_108 + (4 * sym_klon)) - 1)];
                            double zqxn_1_in_0 = zqxn[((_for_it_108 + (sym_klon * (_for_it_107 - 1))) - 1)];
                            double zqxn_out_0;

                            ///////////////////
                            // Tasklet code (T_l1249_c1249)
                            zqxn_out_0 = (zqxn_0_in_0 + zqxn_1_in_0);
                            ///////////////////

                            zqxn[((_for_it_108 + (4 * sym_klon)) - 1)] = zqxn_out_0;
                        }
                    }
                    {
                        {
                            double zqxn_out_0;

                            ///////////////////
                            // Tasklet code (T_l1250_c1250)
                            zqxn_out_0 = 0.0;
                            ///////////////////

                            zqxn[((_for_it_108 + (sym_klon * (_for_it_107 - 1))) - 1)] = zqxn_out_0;
                        }
                    }
                }
            }
        }
        for (_for_it_109 = 1; (_for_it_109 <= 5); _for_it_109 = (_for_it_109 + 1)) {
            for (_for_it_110 = 1; (_for_it_110 <= icend); _for_it_110 = (_for_it_110 + 1)) {
                {
                    {
                        double zqxn_0_in_0 = zqxn[((_for_it_110 + (sym_klon * (_for_it_109 - 1))) - 1)];
                        double zqxnm1_out_0;

                        ///////////////////
                        // Tasklet code (T_l1256_c1256)
                        zqxnm1_out_0 = zqxn_0_in_0;
                        ///////////////////

                        zqxnm1[((_for_it_110 + (sym_klon * (_for_it_109 - 1))) - 1)] = zqxnm1_out_0;
                    }
                    {
                        double zqxn_0_in_0 = zqxn[((_for_it_110 + (sym_klon * (_for_it_109 - 1))) - 1)];
                        double zqxn2d_out_0;

                        ///////////////////
                        // Tasklet code (T_l1257_c1257)
                        zqxn2d_out_0 = zqxn_0_in_0;
                        ///////////////////

                        zqxn2d[(((_for_it_110 + ((sym_klev * sym_klon) * (_for_it_109 - 1))) + (sym_klon * (_for_it_23 - 1))) - 1)] = zqxn2d_out_0;
                    }
                }
            }
        }
        for (_for_it_111 = 1; (_for_it_111 <= 5); _for_it_111 = (_for_it_111 + 1)) {
            for (_for_it_112 = 1; (_for_it_112 <= icend); _for_it_112 = (_for_it_112 + 1)) {
                {
                    {
                        double zfallsink_0_in_0 = zfallsink[((_for_it_112 + (sym_klon * (_for_it_111 - 1))) - 1)];
                        double zqxn_0_in_0 = zqxn[((_for_it_112 + (sym_klon * (_for_it_111 - 1))) - 1)];
                        double zrdtgdp_0_in_0 = zrdtgdp[(_for_it_112 - 1)];
                        double zpfplsx_out_0;

                        ///////////////////
                        // Tasklet code (T_l1262_c1262)
                        zpfplsx_out_0 = ((zfallsink_0_in_0 * zqxn_0_in_0) * zrdtgdp_0_in_0);
                        ///////////////////

                        zpfplsx[(((_for_it_112 + (_for_it_23 * sym_klon)) + ((sym_klon * (_for_it_111 - 1)) * (sym_klev + 1))) - 1)] = zpfplsx_out_0;
                    }
                }
            }
        }
        for (_for_it_113 = 1; (_for_it_113 <= icend); _for_it_113 = (_for_it_113 + 1)) {
            {
                {
                    double zpfplsx_0_in_0 = zpfplsx[(((_for_it_113 + (_for_it_23 * sym_klon)) + ((3 * sym_klon) * (sym_klev + 1))) - 1)];
                    double zpfplsx_1_in_0 = zpfplsx[(((_for_it_113 + (_for_it_23 * sym_klon)) + ((2 * sym_klon) * (sym_klev + 1))) - 1)];
                    double zqpretot_out_0;

                    ///////////////////
                    // Tasklet code (T_l1266_c1266)
                    zqpretot_out_0 = (zpfplsx_0_in_0 + zpfplsx_1_in_0);
                    ///////////////////

                    zqpretot[(_for_it_113 - 1)] = zqpretot_out_0;
                }
            }
        }
        for (_for_it_114 = 1; (_for_it_114 <= icend); _for_it_114 = (_for_it_114 + 1)) {
            _if_cond_80 = (zqpretot[(_for_it_114 - 1)] < 1e-14);
            if ((_if_cond_80 == 1)) {
                {
                    {
                        double zcovptot_out_0;

                        ///////////////////
                        // Tasklet code (T_l1270_c1270)
                        zcovptot_out_0 = 0.0;
                        ///////////////////

                        zcovptot[(_for_it_114 - 1)] = zcovptot_out_0;
                    }
                }
            }
        }
        for (_for_it_115 = 1; (_for_it_115 <= 4); _for_it_115 = (_for_it_115 + 1)) {
            for (_for_it_116 = 1; (_for_it_116 <= icend); _for_it_116 = (_for_it_116 + 1)) {
                {
                    {
                        double zconvsink_0_in_0 = zconvsink[((_for_it_116 + (sym_klon * (_for_it_115 - 1))) - 1)];
                        double zconvsrce_0_in_0 = zconvsrce[((_for_it_116 + (sym_klon * (_for_it_115 - 1))) - 1)];
                        double zfallsink_0_in_0 = zfallsink[((_for_it_116 + (sym_klon * (_for_it_115 - 1))) - 1)];
                        double zfallsrce_0_in_0 = zfallsrce[((_for_it_116 + (sym_klon * (_for_it_115 - 1))) - 1)];
                        double zpsupsatsrce_0_in_0 = zpsupsatsrce[((_for_it_116 + (sym_klon * (_for_it_115 - 1))) - 1)];
                        double zqxn_0_in_0 = zqxn[((_for_it_116 + (sym_klon * (_for_it_115 - 1))) - 1)];
                        double zfluxq_out_0;

                        ///////////////////
                        // Tasklet code (T_l1275_c1275)
                        zfluxq_out_0 = (((zpsupsatsrce_0_in_0 + zconvsrce_0_in_0) + zfallsrce_0_in_0) - ((zfallsink_0_in_0 + zconvsink_0_in_0) * zqxn_0_in_0));
                        ///////////////////

                        zfluxq[((_for_it_116 + (sym_klon * (_for_it_115 - 1))) - 1)] = zfluxq_out_0;
                    }
                }
            }
            _if_cond_81 = (iphase[(_for_it_115 - 1)] == 1);
            if ((_if_cond_81 == 1)) {
                for (_for_it_117 = 1; (_for_it_117 <= icend); _for_it_117 = (_for_it_117 + 1)) {
                    {
                        {
                            double ptendency_loc_t_0_in_0 = ptendency_loc_t[((_for_it_117 + (sym_klon * (_for_it_23 - 1))) - 1)];
                            double ydthf_var_48_0_in_ralvdcp = v_ydthf_var_48_ralvdcp[0];
                            double zfluxq_0_in_0 = zfluxq[((_for_it_117 + (sym_klon * (_for_it_115 - 1))) - 1)];
                            double zqtmst_0_in = zqtmst;
                            double zqx_0_in_0 = zqx[(((_for_it_117 + ((sym_klev * sym_klon) * (_for_it_115 - 1))) + (sym_klon * (_for_it_23 - 1))) - 1)];
                            double zqxn_0_in_0 = zqxn[((_for_it_117 + (sym_klon * (_for_it_115 - 1))) - 1)];
                            double ptendency_loc_t_out_0;

                            ///////////////////
                            // Tasklet code (T_l1279_c1279)
                            ptendency_loc_t_out_0 = (ptendency_loc_t_0_in_0 + ((ydthf_var_48_0_in_ralvdcp * ((zqxn_0_in_0 - zqx_0_in_0) - zfluxq_0_in_0)) * zqtmst_0_in));
                            ///////////////////

                            ptendency_loc_t[((_for_it_117 + (sym_klon * (_for_it_23 - 1))) - 1)] = ptendency_loc_t_out_0;
                        }
                    }
                }
            }
            _if_cond_82 = (iphase[(_for_it_115 - 1)] == 2);
            if ((_if_cond_82 == 1)) {
                for (_for_it_118 = 1; (_for_it_118 <= icend); _for_it_118 = (_for_it_118 + 1)) {
                    {
                        {
                            double ptendency_loc_t_0_in_0 = ptendency_loc_t[((_for_it_118 + (sym_klon * (_for_it_23 - 1))) - 1)];
                            double ydthf_var_48_0_in_ralsdcp = v_ydthf_var_48_ralsdcp[0];
                            double zfluxq_0_in_0 = zfluxq[((_for_it_118 + (sym_klon * (_for_it_115 - 1))) - 1)];
                            double zqtmst_0_in = zqtmst;
                            double zqx_0_in_0 = zqx[(((_for_it_118 + ((sym_klev * sym_klon) * (_for_it_115 - 1))) + (sym_klon * (_for_it_23 - 1))) - 1)];
                            double zqxn_0_in_0 = zqxn[((_for_it_118 + (sym_klon * (_for_it_115 - 1))) - 1)];
                            double ptendency_loc_t_out_0;

                            ///////////////////
                            // Tasklet code (T_l1284_c1284)
                            ptendency_loc_t_out_0 = (ptendency_loc_t_0_in_0 + ((ydthf_var_48_0_in_ralsdcp * ((zqxn_0_in_0 - zqx_0_in_0) - zfluxq_0_in_0)) * zqtmst_0_in));
                            ///////////////////

                            ptendency_loc_t[((_for_it_118 + (sym_klon * (_for_it_23 - 1))) - 1)] = ptendency_loc_t_out_0;
                        }
                    }
                }
            }
            for (_for_it_119 = 1; (_for_it_119 <= icend); _for_it_119 = (_for_it_119 + 1)) {
                {
                    {
                        double ptendency_loc_cld_0_in_0 = ptendency_loc_cld[(((_for_it_119 + ((sym_klev * sym_klon) * (_for_it_115 - 1))) + (sym_klon * (_for_it_23 - 1))) - 1)];
                        double zqtmst_0_in = zqtmst;
                        double zqx0_0_in_0 = zqx0[(((_for_it_119 + ((sym_klev * sym_klon) * (_for_it_115 - 1))) + (sym_klon * (_for_it_23 - 1))) - 1)];
                        double zqxn_0_in_0 = zqxn[((_for_it_119 + (sym_klon * (_for_it_115 - 1))) - 1)];
                        double ptendency_loc_cld_out_0;

                        ///////////////////
                        // Tasklet code (T_l1288_c1288)
                        ptendency_loc_cld_out_0 = (ptendency_loc_cld_0_in_0 + ((zqxn_0_in_0 - zqx0_0_in_0) * zqtmst_0_in));
                        ///////////////////

                        ptendency_loc_cld[(((_for_it_119 + ((sym_klev * sym_klon) * (_for_it_115 - 1))) + (sym_klon * (_for_it_23 - 1))) - 1)] = ptendency_loc_cld_out_0;
                    }
                }
            }
        }
        for (_for_it_120 = 1; (_for_it_120 <= icend); _for_it_120 = (_for_it_120 + 1)) {
            {
                {
                    double ptendency_loc_q_0_in_0 = ptendency_loc_q[((_for_it_120 + (sym_klon * (_for_it_23 - 1))) - 1)];
                    double zqtmst_0_in = zqtmst;
                    double zqx_0_in_0 = zqx[(((_for_it_120 + ((4 * sym_klev) * sym_klon)) + (sym_klon * (_for_it_23 - 1))) - 1)];
                    double zqxn_0_in_0 = zqxn[((_for_it_120 + (4 * sym_klon)) - 1)];
                    double ptendency_loc_q_out_0;

                    ///////////////////
                    // Tasklet code (T_l1292_c1292)
                    ptendency_loc_q_out_0 = (ptendency_loc_q_0_in_0 + ((zqxn_0_in_0 - zqx_0_in_0) * zqtmst_0_in));
                    ///////////////////

                    ptendency_loc_q[((_for_it_120 + (sym_klon * (_for_it_23 - 1))) - 1)] = ptendency_loc_q_out_0;
                }
                {
                    double ptendency_loc_a_0_in_0 = ptendency_loc_a[((_for_it_120 + (sym_klon * (_for_it_23 - 1))) - 1)];
                    double zda_0_in_0 = zda[(_for_it_120 - 1)];
                    double zqtmst_0_in = zqtmst;
                    double ptendency_loc_a_out_0;

                    ///////////////////
                    // Tasklet code (T_l1293_c1293)
                    ptendency_loc_a_out_0 = (ptendency_loc_a_0_in_0 + (zda_0_in_0 * zqtmst_0_in));
                    ///////////////////

                    ptendency_loc_a[((_for_it_120 + (sym_klon * (_for_it_23 - 1))) - 1)] = ptendency_loc_a_out_0;
                }
            }
        }
        for (_for_it_121 = 1; (_for_it_121 <= icend); _for_it_121 = (_for_it_121 + 1)) {
            {
                {
                    double zcovptot_0_in_0 = zcovptot[(_for_it_121 - 1)];
                    double pcovptot_var_31_out_0;

                    ///////////////////
                    // Tasklet code (T_l1296_c1296)
                    pcovptot_var_31_out_0 = zcovptot_0_in_0;
                    ///////////////////

                    pcovptot_var_31[((_for_it_121 + (sym_klon * (_for_it_23 - 1))) - 1)] = pcovptot_var_31_out_0;
                }
            }
        }
    }

    for (_for_it_122 = 1; (_for_it_122 <= (sym_klev + 1)); _for_it_122 = (_for_it_122 + 1)) {
        for (_for_it_123 = 1; (_for_it_123 <= icend); _for_it_123 = (_for_it_123 + 1)) {
            {
                {
                    double zpfplsx_0_in_0 = zpfplsx[(((_for_it_123 + (sym_klon * (_for_it_122 - 1))) + ((2 * sym_klon) * (sym_klev + 1))) - 1)];
                    double zpfplsx_1_in_0 = zpfplsx[((_for_it_123 + (sym_klon * (_for_it_122 - 1))) - 1)];
                    double pfplsl_var_43_out_0;

                    ///////////////////
                    // Tasklet code (T_l1301_c1301)
                    pfplsl_var_43_out_0 = (zpfplsx_0_in_0 + zpfplsx_1_in_0);
                    ///////////////////

                    pfplsl_var_43[((_for_it_123 + (sym_klon * (_for_it_122 - 1))) - 1)] = pfplsl_var_43_out_0;
                }
                {
                    double zpfplsx_0_in_0 = zpfplsx[(((_for_it_123 + (sym_klon * (_for_it_122 - 1))) + ((3 * sym_klon) * (sym_klev + 1))) - 1)];
                    double zpfplsx_1_in_0 = zpfplsx[(((_for_it_123 + (sym_klon * (_for_it_122 - 1))) + (sym_klon * (sym_klev + 1))) - 1)];
                    double pfplsn_var_44_out_0;

                    ///////////////////
                    // Tasklet code (T_l1302_c1302)
                    pfplsn_var_44_out_0 = (zpfplsx_0_in_0 + zpfplsx_1_in_0);
                    ///////////////////

                    pfplsn_var_44[((_for_it_123 + (sym_klon * (_for_it_122 - 1))) - 1)] = pfplsn_var_44_out_0;
                }
            }
        }
    }

    for (_for_it_124 = 1; (_for_it_124 <= icend); _for_it_124 = (_for_it_124 + 1)) {
        {
            {
                double pfsqlf_var_33_out_0;

                ///////////////////
                // Tasklet code (T_l1306_c1306)
                pfsqlf_var_33_out_0 = 0.0;
                ///////////////////

                pfsqlf_var_33[(_for_it_124 - 1)] = pfsqlf_var_33_out_0;
            }
            {
                double pfsqif_var_34_out_0;

                ///////////////////
                // Tasklet code (T_l1307_c1307)
                pfsqif_var_34_out_0 = 0.0;
                ///////////////////

                pfsqif_var_34[(_for_it_124 - 1)] = pfsqif_var_34_out_0;
            }
            {
                double pfsqrf_var_37_out_0;

                ///////////////////
                // Tasklet code (T_l1308_c1308)
                pfsqrf_var_37_out_0 = 0.0;
                ///////////////////

                pfsqrf_var_37[(_for_it_124 - 1)] = pfsqrf_var_37_out_0;
            }
            {
                double pfsqsf_var_38_out_0;

                ///////////////////
                // Tasklet code (T_l1309_c1309)
                pfsqsf_var_38_out_0 = 0.0;
                ///////////////////

                pfsqsf_var_38[(_for_it_124 - 1)] = pfsqsf_var_38_out_0;
            }
            {
                double pfcqlng_var_35_out_0;

                ///////////////////
                // Tasklet code (T_l1310_c1310)
                pfcqlng_var_35_out_0 = 0.0;
                ///////////////////

                pfcqlng_var_35[(_for_it_124 - 1)] = pfcqlng_var_35_out_0;
            }
            {
                double pfcqnng_var_36_out_0;

                ///////////////////
                // Tasklet code (T_l1311_c1311)
                pfcqnng_var_36_out_0 = 0.0;
                ///////////////////

                pfcqnng_var_36[(_for_it_124 - 1)] = pfcqnng_var_36_out_0;
            }
            {
                double pfcqrng_var_39_out_0;

                ///////////////////
                // Tasklet code (T_l1312_c1312)
                pfcqrng_var_39_out_0 = 0.0;
                ///////////////////

                pfcqrng_var_39[(_for_it_124 - 1)] = pfcqrng_var_39_out_0;
            }
            {
                double pfcqsng_var_40_out_0;

                ///////////////////
                // Tasklet code (T_l1313_c1313)
                pfcqsng_var_40_out_0 = 0.0;
                ///////////////////

                pfcqsng_var_40[(_for_it_124 - 1)] = pfcqsng_var_40_out_0;
            }
            {
                double pfsqltur_var_41_out_0;

                ///////////////////
                // Tasklet code (T_l1314_c1314)
                pfsqltur_var_41_out_0 = 0.0;
                ///////////////////

                pfsqltur_var_41[(_for_it_124 - 1)] = pfsqltur_var_41_out_0;
            }
            {
                double pfsqitur_var_42_out_0;

                ///////////////////
                // Tasklet code (T_l1315_c1315)
                pfsqitur_var_42_out_0 = 0.0;
                ///////////////////

                pfsqitur_var_42[(_for_it_124 - 1)] = pfsqitur_var_42_out_0;
            }
        }
    }

    for (_for_it_125 = 1; (_for_it_125 <= sym_klev); _for_it_125 = (_for_it_125 + 1)) {
        for (_for_it_126 = 1; (_for_it_126 <= icend); _for_it_126 = (_for_it_126 + 1)) {
            zalfaw = zfoealfa[((_for_it_126 + (sym_klon * (_for_it_125 - 1))) - 1)];
            {
                {
                    double paph_var_18_0_in_0 = paph_var_18[(((_for_it_125 * sym_klon) + _for_it_126) - 1)];
                    double paph_var_18_1_in_0 = paph_var_18[((_for_it_126 + (sym_klon * (_for_it_125 - 1))) - 1)];
                    double zqtmst_0_in = zqtmst;
                    double zrg_r_0_in = zrg_r;
                    double zgdph_r_out;

                    ///////////////////
                    // Tasklet code (T_l1319_c1319)
                    zgdph_r_out = (-((zrg_r_0_in * (paph_var_18_0_in_0 - paph_var_18_1_in_0)) * zqtmst_0_in));
                    ///////////////////

                    zgdph_r = zgdph_r_out;
                }
                {
                    double pfsqlf_var_33_0_in_0 = pfsqlf_var_33[((_for_it_126 + (sym_klon * (_for_it_125 - 1))) - 1)];
                    double pfsqlf_var_33_out_0;

                    ///////////////////
                    // Tasklet code (T_l1320_c1320)
                    pfsqlf_var_33_out_0 = pfsqlf_var_33_0_in_0;
                    ///////////////////

                    pfsqlf_var_33[(((_for_it_125 * sym_klon) + _for_it_126) - 1)] = pfsqlf_var_33_out_0;
                }
                {
                    double pfsqlf_var_33_0_in_0 = pfsqlf_var_33[((_for_it_126 + (sym_klon * (_for_it_125 - 1))) - 1)];
                    double pfsqrf_var_37_out_0;

                    ///////////////////
                    // Tasklet code (T_l1322_c1322)
                    pfsqrf_var_37_out_0 = pfsqlf_var_33_0_in_0;
                    ///////////////////

                    pfsqrf_var_37[(((_for_it_125 * sym_klon) + _for_it_126) - 1)] = pfsqrf_var_37_out_0;
                }
                {
                    double pfsqif_var_34_0_in_0 = pfsqif_var_34[((_for_it_126 + (sym_klon * (_for_it_125 - 1))) - 1)];
                    double pfsqif_var_34_out_0;

                    ///////////////////
                    // Tasklet code (T_l1321_c1321)
                    pfsqif_var_34_out_0 = pfsqif_var_34_0_in_0;
                    ///////////////////

                    pfsqif_var_34[(((_for_it_125 * sym_klon) + _for_it_126) - 1)] = pfsqif_var_34_out_0;
                }
                {
                    double pfsqif_var_34_0_in_0 = pfsqif_var_34[((_for_it_126 + (sym_klon * (_for_it_125 - 1))) - 1)];
                    double pfsqsf_var_38_out_0;

                    ///////////////////
                    // Tasklet code (T_l1323_c1323)
                    pfsqsf_var_38_out_0 = pfsqif_var_34_0_in_0;
                    ///////////////////

                    pfsqsf_var_38[(((_for_it_125 * sym_klon) + _for_it_126) - 1)] = pfsqsf_var_38_out_0;
                }
                {
                    double pfcqlng_var_35_0_in_0 = pfcqlng_var_35[((_for_it_126 + (sym_klon * (_for_it_125 - 1))) - 1)];
                    double pfcqlng_var_35_out_0;

                    ///////////////////
                    // Tasklet code (T_l1324_c1324)
                    pfcqlng_var_35_out_0 = pfcqlng_var_35_0_in_0;
                    ///////////////////

                    pfcqlng_var_35[(((_for_it_125 * sym_klon) + _for_it_126) - 1)] = pfcqlng_var_35_out_0;
                }
                {
                    double pfcqlng_var_35_0_in_0 = pfcqlng_var_35[((_for_it_126 + (sym_klon * (_for_it_125 - 1))) - 1)];
                    double pfcqrng_var_39_out_0;

                    ///////////////////
                    // Tasklet code (T_l1326_c1326)
                    pfcqrng_var_39_out_0 = pfcqlng_var_35_0_in_0;
                    ///////////////////

                    pfcqrng_var_39[(((_for_it_125 * sym_klon) + _for_it_126) - 1)] = pfcqrng_var_39_out_0;
                }
                {
                    double pfcqnng_var_36_0_in_0 = pfcqnng_var_36[((_for_it_126 + (sym_klon * (_for_it_125 - 1))) - 1)];
                    double pfcqnng_var_36_out_0;

                    ///////////////////
                    // Tasklet code (T_l1325_c1325)
                    pfcqnng_var_36_out_0 = pfcqnng_var_36_0_in_0;
                    ///////////////////

                    pfcqnng_var_36[(((_for_it_125 * sym_klon) + _for_it_126) - 1)] = pfcqnng_var_36_out_0;
                }
                {
                    double pfcqnng_var_36_0_in_0 = pfcqnng_var_36[((_for_it_126 + (sym_klon * (_for_it_125 - 1))) - 1)];
                    double pfcqsng_var_40_out_0;

                    ///////////////////
                    // Tasklet code (T_l1327_c1327)
                    pfcqsng_var_40_out_0 = pfcqnng_var_36_0_in_0;
                    ///////////////////

                    pfcqsng_var_40[(((_for_it_125 * sym_klon) + _for_it_126) - 1)] = pfcqsng_var_40_out_0;
                }
                {
                    double pfsqltur_var_41_0_in_0 = pfsqltur_var_41[((_for_it_126 + (sym_klon * (_for_it_125 - 1))) - 1)];
                    double pfsqltur_var_41_out_0;

                    ///////////////////
                    // Tasklet code (T_l1328_c1328)
                    pfsqltur_var_41_out_0 = pfsqltur_var_41_0_in_0;
                    ///////////////////

                    pfsqltur_var_41[(((_for_it_125 * sym_klon) + _for_it_126) - 1)] = pfsqltur_var_41_out_0;
                }
                {
                    double pfsqitur_var_42_0_in_0 = pfsqitur_var_42[((_for_it_126 + (sym_klon * (_for_it_125 - 1))) - 1)];
                    double pfsqitur_var_42_out_0;

                    ///////////////////
                    // Tasklet code (T_l1329_c1329)
                    pfsqitur_var_42_out_0 = pfsqitur_var_42_0_in_0;
                    ///////////////////

                    pfsqitur_var_42[(((_for_it_125 * sym_klon) + _for_it_126) - 1)] = pfsqitur_var_42_out_0;
                }
            }
            {
                {
                    double pfsqlf_var_33_0_in_0 = pfsqlf_var_33[(((_for_it_125 * sym_klon) + _for_it_126) - 1)];
                    double plude_var_23_0_in_0 = plude_var_23[((_for_it_126 + (sym_klon * (_for_it_125 - 1))) - 1)];
                    double ptsphy_var_5_0_in = ptsphy_var_5[0];
                    double pvfl_var_9_0_in_0 = pvfl_var_9[((_for_it_126 + (sym_klon * (_for_it_125 - 1))) - 1)];
                    double zgdph_r_0_in = zgdph_r;
                    double zqx0_0_in_0 = zqx0[((_for_it_126 + (sym_klon * (_for_it_125 - 1))) - 1)];
                    double zqxn2d_0_in_0 = zqxn2d[((_for_it_126 + (sym_klon * (_for_it_125 - 1))) - 1)];
                    double pfsqlf_var_33_out_0;

                    ///////////////////
                    // Tasklet code (T_l1331_c1331)
                    pfsqlf_var_33_out_0 = (pfsqlf_var_33_0_in_0 + ((((zqxn2d_0_in_0 - zqx0_0_in_0) + (pvfl_var_9_0_in_0 * ptsphy_var_5_0_in)) - (zalfaw * plude_var_23_0_in_0)) * zgdph_r_0_in));
                    ///////////////////

                    pfsqlf_var_33[(((_for_it_125 * sym_klon) + _for_it_126) - 1)] = pfsqlf_var_33_out_0;
                }
                {
                    double pfsqrf_var_37_0_in_0 = pfsqrf_var_37[(((_for_it_125 * sym_klon) + _for_it_126) - 1)];
                    double zgdph_r_0_in = zgdph_r;
                    double zqx0_0_in_0 = zqx0[(((_for_it_126 + ((2 * sym_klev) * sym_klon)) + (sym_klon * (_for_it_125 - 1))) - 1)];
                    double zqxn2d_0_in_0 = zqxn2d[(((_for_it_126 + ((2 * sym_klev) * sym_klon)) + (sym_klon * (_for_it_125 - 1))) - 1)];
                    double pfsqrf_var_37_out_0;

                    ///////////////////
                    // Tasklet code (T_l1334_c1334)
                    pfsqrf_var_37_out_0 = (pfsqrf_var_37_0_in_0 + ((zqxn2d_0_in_0 - zqx0_0_in_0) * zgdph_r_0_in));
                    ///////////////////

                    pfsqrf_var_37[(((_for_it_125 * sym_klon) + _for_it_126) - 1)] = pfsqrf_var_37_out_0;
                }
                {
                    double pfsqif_var_34_0_in_0 = pfsqif_var_34[(((_for_it_125 * sym_klon) + _for_it_126) - 1)];
                    double plude_var_23_0_in_0 = plude_var_23[((_for_it_126 + (sym_klon * (_for_it_125 - 1))) - 1)];
                    double ptsphy_var_5_0_in = ptsphy_var_5[0];
                    double pvfi_var_10_0_in_0 = pvfi_var_10[((_for_it_126 + (sym_klon * (_for_it_125 - 1))) - 1)];
                    double zgdph_r_0_in = zgdph_r;
                    double zqx0_0_in_0 = zqx0[(((_for_it_126 + (sym_klev * sym_klon)) + (sym_klon * (_for_it_125 - 1))) - 1)];
                    double zqxn2d_0_in_0 = zqxn2d[(((_for_it_126 + (sym_klev * sym_klon)) + (sym_klon * (_for_it_125 - 1))) - 1)];
                    double pfsqif_var_34_out_0;

                    ///////////////////
                    // Tasklet code (T_l1336_c1336)
                    pfsqif_var_34_out_0 =
                        (pfsqif_var_34_0_in_0 + ((((zqxn2d_0_in_0 - zqx0_0_in_0) + (pvfi_var_10_0_in_0 * ptsphy_var_5_0_in)) - ((1.0 - zalfaw) * plude_var_23_0_in_0)) * zgdph_r_0_in));
                    ///////////////////

                    pfsqif_var_34[(((_for_it_125 * sym_klon) + _for_it_126) - 1)] = pfsqif_var_34_out_0;
                }
                {
                    double pfsqsf_var_38_0_in_0 = pfsqsf_var_38[(((_for_it_125 * sym_klon) + _for_it_126) - 1)];
                    double zgdph_r_0_in = zgdph_r;
                    double zqx0_0_in_0 = zqx0[(((_for_it_126 + ((3 * sym_klev) * sym_klon)) + (sym_klon * (_for_it_125 - 1))) - 1)];
                    double zqxn2d_0_in_0 = zqxn2d[(((_for_it_126 + ((3 * sym_klev) * sym_klon)) + (sym_klon * (_for_it_125 - 1))) - 1)];
                    double pfsqsf_var_38_out_0;

                    ///////////////////
                    // Tasklet code (T_l1339_c1339)
                    pfsqsf_var_38_out_0 = (pfsqsf_var_38_0_in_0 + ((zqxn2d_0_in_0 - zqx0_0_in_0) * zgdph_r_0_in));
                    ///////////////////

                    pfsqsf_var_38[(((_for_it_125 * sym_klon) + _for_it_126) - 1)] = pfsqsf_var_38_out_0;
                }
                {
                    double pfsqltur_var_41_0_in_0 = pfsqltur_var_41[(((_for_it_125 * sym_klon) + _for_it_126) - 1)];
                    double ptsphy_var_5_0_in = ptsphy_var_5[0];
                    double pvfl_var_9_0_in_0 = pvfl_var_9[((_for_it_126 + (sym_klon * (_for_it_125 - 1))) - 1)];
                    double zgdph_r_0_in = zgdph_r;
                    double pfsqltur_var_41_out_0;

                    ///////////////////
                    // Tasklet code (T_l1333_c1333)
                    pfsqltur_var_41_out_0 = (pfsqltur_var_41_0_in_0 + ((pvfl_var_9_0_in_0 * ptsphy_var_5_0_in) * zgdph_r_0_in));
                    ///////////////////

                    pfsqltur_var_41[(((_for_it_125 * sym_klon) + _for_it_126) - 1)] = pfsqltur_var_41_out_0;
                }
                {
                    double pfsqitur_var_42_0_in_0 = pfsqitur_var_42[(((_for_it_125 * sym_klon) + _for_it_126) - 1)];
                    double ptsphy_var_5_0_in = ptsphy_var_5[0];
                    double pvfi_var_10_0_in_0 = pvfi_var_10[((_for_it_126 + (sym_klon * (_for_it_125 - 1))) - 1)];
                    double zgdph_r_0_in = zgdph_r;
                    double pfsqitur_var_42_out_0;

                    ///////////////////
                    // Tasklet code (T_l1338_c1338)
                    pfsqitur_var_42_out_0 = (pfsqitur_var_42_0_in_0 + ((pvfi_var_10_0_in_0 * ptsphy_var_5_0_in) * zgdph_r_0_in));
                    ///////////////////

                    pfsqitur_var_42[(((_for_it_125 * sym_klon) + _for_it_126) - 1)] = pfsqitur_var_42_out_0;
                }
                {
                    double pfcqlng_var_35_0_in_0 = pfcqlng_var_35[(((_for_it_125 * sym_klon) + _for_it_126) - 1)];
                    double zgdph_r_0_in = zgdph_r;
                    double zlneg_0_in_0 = zlneg[((_for_it_126 + (sym_klon * (_for_it_125 - 1))) - 1)];
                    double pfcqlng_var_35_out_0;

                    ///////////////////
                    // Tasklet code (T_l1332_c1332)
                    pfcqlng_var_35_out_0 = (pfcqlng_var_35_0_in_0 + (zlneg_0_in_0 * zgdph_r_0_in));
                    ///////////////////

                    pfcqlng_var_35[(((_for_it_125 * sym_klon) + _for_it_126) - 1)] = pfcqlng_var_35_out_0;
                }
                {
                    double pfcqrng_var_39_0_in_0 = pfcqrng_var_39[(((_for_it_125 * sym_klon) + _for_it_126) - 1)];
                    double zgdph_r_0_in = zgdph_r;
                    double zlneg_0_in_0 = zlneg[(((_for_it_126 + ((2 * sym_klev) * sym_klon)) + (sym_klon * (_for_it_125 - 1))) - 1)];
                    double pfcqrng_var_39_out_0;

                    ///////////////////
                    // Tasklet code (T_l1335_c1335)
                    pfcqrng_var_39_out_0 = (pfcqrng_var_39_0_in_0 + (zlneg_0_in_0 * zgdph_r_0_in));
                    ///////////////////

                    pfcqrng_var_39[(((_for_it_125 * sym_klon) + _for_it_126) - 1)] = pfcqrng_var_39_out_0;
                }
                {
                    double pfcqnng_var_36_0_in_0 = pfcqnng_var_36[(((_for_it_125 * sym_klon) + _for_it_126) - 1)];
                    double zgdph_r_0_in = zgdph_r;
                    double zlneg_0_in_0 = zlneg[(((_for_it_126 + (sym_klev * sym_klon)) + (sym_klon * (_for_it_125 - 1))) - 1)];
                    double pfcqnng_var_36_out_0;

                    ///////////////////
                    // Tasklet code (T_l1337_c1337)
                    pfcqnng_var_36_out_0 = (pfcqnng_var_36_0_in_0 + (zlneg_0_in_0 * zgdph_r_0_in));
                    ///////////////////

                    pfcqnng_var_36[(((_for_it_125 * sym_klon) + _for_it_126) - 1)] = pfcqnng_var_36_out_0;
                }
                {
                    double pfcqsng_var_40_0_in_0 = pfcqsng_var_40[(((_for_it_125 * sym_klon) + _for_it_126) - 1)];
                    double zgdph_r_0_in = zgdph_r;
                    double zlneg_0_in_0 = zlneg[(((_for_it_126 + ((3 * sym_klev) * sym_klon)) + (sym_klon * (_for_it_125 - 1))) - 1)];
                    double pfcqsng_var_40_out_0;

                    ///////////////////
                    // Tasklet code (T_l1340_c1340)
                    pfcqsng_var_40_out_0 = (pfcqsng_var_40_0_in_0 + (zlneg_0_in_0 * zgdph_r_0_in));
                    ///////////////////

                    pfcqsng_var_40[(((_for_it_125 * sym_klon) + _for_it_126) - 1)] = pfcqsng_var_40_out_0;
                }
            }
        }
    }

    for (_for_it_127 = 1; (_for_it_127 <= (sym_klev + 1)); _for_it_127 = (_for_it_127 + 1)) {
        for (_for_it_128 = 1; (_for_it_128 <= icend); _for_it_128 = (_for_it_128 + 1)) {
            {
                double* v_ydcst_var_47_rlvtt;
                v_ydcst_var_47_rlvtt = (double*)(&(ydcst_var_47->rlvtt));

                {
                    double pfplsl_var_43_0_in_0 = pfplsl_var_43[((_for_it_128 + (sym_klon * (_for_it_127 - 1))) - 1)];
                    double ydcst_var_47_0_in_rlvtt = v_ydcst_var_47_rlvtt[0];
                    double pfhpsl_var_45_out_0;

                    ///////////////////
                    // Tasklet code (T_l1345_c1345)
                    pfhpsl_var_45_out_0 = (-(ydcst_var_47_0_in_rlvtt * pfplsl_var_43_0_in_0));
                    ///////////////////

                    pfhpsl_var_45[((_for_it_128 + (sym_klon * (_for_it_127 - 1))) - 1)] = pfhpsl_var_45_out_0;
                }
                {
                    double pfplsn_var_44_0_in_0 = pfplsn_var_44[((_for_it_128 + (sym_klon * (_for_it_127 - 1))) - 1)];
                    double ydcst_var_47_0_in_rlstt = v_ydcst_var_47_rlstt[0];
                    double pfhpsn_var_46_out_0;

                    ///////////////////
                    // Tasklet code (T_l1346_c1346)
                    pfhpsn_var_46_out_0 = (-(ydcst_var_47_0_in_rlstt * pfplsn_var_44_0_in_0));
                    ///////////////////

                    pfhpsn_var_46[((_for_it_128 + (sym_klon * (_for_it_127 - 1))) - 1)] = pfhpsn_var_46_out_0;
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

inline void loop_body_0_2_0(
    cloudsc_driver_state_t* __state, const int& kfldx, int* __restrict__ ktype, int* __restrict__ ldcum, const int& ngptot, const int& nlev, const int& nproma, double* __restrict__ pa,
    double* __restrict__ pap, double* __restrict__ paph, double* __restrict__ pccn, double* __restrict__ pclv, double* __restrict__ pdyna, double* __restrict__ pdyni, double* __restrict__ pdynl,
    double* __restrict__ phrlw, double* __restrict__ phrsw, double* __restrict__ picrit_aer, double* __restrict__ plcrit_aer, double* __restrict__ plsm, double* __restrict__ plu,
    double* __restrict__ pmfd, double* __restrict__ pmfu, double* __restrict__ pnice, double* __restrict__ pq, double* __restrict__ pre_ice, double* __restrict__ psnde, double* __restrict__ psupsat,
    double* __restrict__ pt, const double& ptsphy, double* __restrict__ pvervel, double* __restrict__ pvfa, double* __restrict__ pvfi, double* __restrict__ pvfl, double* __restrict__ tendency_tmp_a,
    double* __restrict__ tendency_tmp_cld, double* __restrict__ tendency_tmp_q, double* __restrict__ tendency_tmp_t, double* __restrict__ pcovptot, double* __restrict__ pfcqlng,
    double* __restrict__ pfcqnng, double* __restrict__ pfcqrng, double* __restrict__ pfcqsng, double* __restrict__ pfhpsl, double* __restrict__ pfhpsn, double* __restrict__ pfplsl,
    double* __restrict__ pfplsn, double* __restrict__ pfsqif, double* __restrict__ pfsqitur, double* __restrict__ pfsqlf, double* __restrict__ pfsqltur, double* __restrict__ pfsqrf,
    double* __restrict__ pfsqsf, double* __restrict__ plude, double* __restrict__ prainfrac_toprfz, double* __restrict__ tendency_loc_a, double* __restrict__ tendency_loc_cld,
    double* __restrict__ tendency_loc_q, double* __restrict__ tendency_loc_t, tecldp* __restrict__ ydecldp, toethf* __restrict__ ydoethf, tomcst* __restrict__ ydomcst, int __f2dace_A_ktype_d_0_s_69,
    int __f2dace_A_ldcum_d_0_s_67, int __f2dace_A_pa_d_0_s_86, int __f2dace_A_pa_d_1_s_87, int __f2dace_A_pap_d_0_s_59, int __f2dace_A_pap_d_1_s_60, int __f2dace_A_paph_d_0_s_62,
    int __f2dace_A_paph_d_1_s_63, int __f2dace_A_pccn_d_0_s_105, int __f2dace_A_pccn_d_1_s_106, int __f2dace_A_pclv_d_0_s_89, int __f2dace_A_pclv_d_1_s_90, int __f2dace_A_pclv_d_2_s_91,
    int __f2dace_A_pcovptot_d_0_s_111, int __f2dace_A_pcovptot_d_1_s_112, int __f2dace_A_pdyna_d_0_s_41, int __f2dace_A_pdyna_d_1_s_42, int __f2dace_A_pdyni_d_0_s_47, int __f2dace_A_pdyni_d_1_s_48,
    int __f2dace_A_pdynl_d_0_s_44, int __f2dace_A_pdynl_d_1_s_45, int __f2dace_A_pfcqlng_d_0_s_122, int __f2dace_A_pfcqlng_d_1_s_123, int __f2dace_A_pfcqnng_d_0_s_125,
    int __f2dace_A_pfcqnng_d_1_s_126, int __f2dace_A_pfcqrng_d_0_s_134, int __f2dace_A_pfcqrng_d_1_s_135, int __f2dace_A_pfcqsng_d_0_s_137, int __f2dace_A_pfcqsng_d_1_s_138,
    int __f2dace_A_pfhpsl_d_0_s_152, int __f2dace_A_pfhpsl_d_1_s_153, int __f2dace_A_pfhpsn_d_0_s_155, int __f2dace_A_pfhpsn_d_1_s_156, int __f2dace_A_pfplsl_d_0_s_146,
    int __f2dace_A_pfplsl_d_1_s_147, int __f2dace_A_pfplsn_d_0_s_149, int __f2dace_A_pfplsn_d_1_s_150, int __f2dace_A_pfsqif_d_0_s_119, int __f2dace_A_pfsqif_d_1_s_120,
    int __f2dace_A_pfsqitur_d_0_s_143, int __f2dace_A_pfsqitur_d_1_s_144, int __f2dace_A_pfsqlf_d_0_s_116, int __f2dace_A_pfsqlf_d_1_s_117, int __f2dace_A_pfsqltur_d_0_s_140,
    int __f2dace_A_pfsqltur_d_1_s_141, int __f2dace_A_pfsqrf_d_0_s_128, int __f2dace_A_pfsqrf_d_1_s_129, int __f2dace_A_pfsqsf_d_0_s_131, int __f2dace_A_pfsqsf_d_1_s_132,
    int __f2dace_A_phrlw_d_0_s_53, int __f2dace_A_phrlw_d_1_s_54, int __f2dace_A_phrsw_d_0_s_50, int __f2dace_A_phrsw_d_1_s_51, int __f2dace_A_picrit_aer_d_0_s_99, int __f2dace_A_picrit_aer_d_1_s_100,
    int __f2dace_A_plcrit_aer_d_0_s_96, int __f2dace_A_plcrit_aer_d_1_s_97, int __f2dace_A_plsm_d_0_s_65, int __f2dace_A_plu_d_0_s_71, int __f2dace_A_plu_d_1_s_72, int __f2dace_A_plude_d_0_s_74,
    int __f2dace_A_plude_d_1_s_75, int __f2dace_A_pmfd_d_0_s_83, int __f2dace_A_pmfd_d_1_s_84, int __f2dace_A_pmfu_d_0_s_80, int __f2dace_A_pmfu_d_1_s_81, int __f2dace_A_pnice_d_0_s_108,
    int __f2dace_A_pnice_d_1_s_109, int __f2dace_A_pq_d_0_s_3, int __f2dace_A_pq_d_1_s_4, int __f2dace_A_prainfrac_toprfz_d_0_s_114, int __f2dace_A_pre_ice_d_0_s_102, int __f2dace_A_pre_ice_d_1_s_103,
    int __f2dace_A_psnde_d_0_s_77, int __f2dace_A_psnde_d_1_s_78, int __f2dace_A_psupsat_d_0_s_93, int __f2dace_A_psupsat_d_1_s_94, int __f2dace_A_pt_d_0_s_0, int __f2dace_A_pt_d_1_s_1,
    int __f2dace_A_pvervel_d_0_s_56, int __f2dace_A_pvervel_d_1_s_57, int __f2dace_A_pvfa_d_0_s_32, int __f2dace_A_pvfa_d_1_s_33, int __f2dace_A_pvfi_d_0_s_38, int __f2dace_A_pvfi_d_1_s_39,
    int __f2dace_A_pvfl_d_0_s_35, int __f2dace_A_pvfl_d_1_s_36, int __f2dace_A_tendency_loc_a_d_0_s_25, int __f2dace_A_tendency_loc_a_d_1_s_26, int __f2dace_A_tendency_loc_cld_d_0_s_28,
    int __f2dace_A_tendency_loc_cld_d_1_s_29, int __f2dace_A_tendency_loc_cld_d_2_s_30, int __f2dace_A_tendency_loc_q_d_0_s_22, int __f2dace_A_tendency_loc_q_d_1_s_23,
    int __f2dace_A_tendency_loc_t_d_0_s_19, int __f2dace_A_tendency_loc_t_d_1_s_20, int __f2dace_A_tendency_tmp_a_d_0_s_12, int __f2dace_A_tendency_tmp_a_d_1_s_13,
    int __f2dace_A_tendency_tmp_cld_d_0_s_15, int __f2dace_A_tendency_tmp_cld_d_1_s_16, int __f2dace_A_tendency_tmp_cld_d_2_s_17, int __f2dace_A_tendency_tmp_q_d_0_s_9,
    int __f2dace_A_tendency_tmp_q_d_1_s_10, int __f2dace_A_tendency_tmp_t_d_0_s_6, int __f2dace_A_tendency_tmp_t_d_1_s_7, int __f2dace_OA_pcovptot_d_0_s_111, int __f2dace_OA_pcovptot_d_1_s_112,
    int __f2dace_OA_tendency_loc_cld_d_0_s_28, int __f2dace_OA_tendency_loc_cld_d_1_s_29, int __f2dace_OA_tendency_loc_cld_d_2_s_30, int _for_it_129) {
    int jkglo;
    int tmp_arg_75;
    int icend;
    int64_t tmp_parfor_58;
    int64_t tmp_parfor_57;
    int64_t tmp_parfor_60;
    int64_t tmp_parfor_59;

    jkglo = (((_for_it_129 - 1) * nproma) + 1);

    tmp_arg_75 = ((ngptot - jkglo) + 1);

    icend = min(nproma, tmp_arg_75);

    for (tmp_parfor_58 = __f2dace_OA_pcovptot_d_1_s_112; (tmp_parfor_58 <= ((__f2dace_A_pcovptot_d_1_s_112 + __f2dace_OA_pcovptot_d_1_s_112) - 1)); tmp_parfor_58 = (tmp_parfor_58 + 1)) {
        for (tmp_parfor_57 = __f2dace_OA_pcovptot_d_0_s_111; (tmp_parfor_57 <= ((__f2dace_A_pcovptot_d_0_s_111 + __f2dace_OA_pcovptot_d_0_s_111) - 1)); tmp_parfor_57 = (tmp_parfor_57 + 1)) {
            {
                {
                    double pcovptot_out_0;

                    ///////////////////
                    // Tasklet code (T_l170_c170)
                    pcovptot_out_0 = 0.0;
                    ///////////////////

                    pcovptot[(((__f2dace_A_pcovptot_d_0_s_111 * ((-__f2dace_OA_pcovptot_d_1_s_112) + tmp_parfor_58)) - __f2dace_OA_pcovptot_d_0_s_111) + tmp_parfor_57)] = pcovptot_out_0;
                }
            }
        }
    }

    for (tmp_parfor_60 = __f2dace_OA_tendency_loc_cld_d_1_s_29; (tmp_parfor_60 <= ((__f2dace_A_tendency_loc_cld_d_1_s_29 + __f2dace_OA_tendency_loc_cld_d_1_s_29) - 1));
         tmp_parfor_60 = (tmp_parfor_60 + 1)) {
        for (tmp_parfor_59 = __f2dace_OA_tendency_loc_cld_d_0_s_28; (tmp_parfor_59 <= ((__f2dace_A_tendency_loc_cld_d_0_s_28 + __f2dace_OA_tendency_loc_cld_d_0_s_28) - 1));
             tmp_parfor_59 = (tmp_parfor_59 + 1)) {
            {
                {
                    double tendency_loc_cld_out_0;

                    ///////////////////
                    // Tasklet code (T_l171_c171)
                    tendency_loc_cld_out_0 = 0.0;
                    ///////////////////

                    tendency_loc_cld[(
                        ((((__f2dace_A_tendency_loc_cld_d_0_s_28 * __f2dace_A_tendency_loc_cld_d_1_s_29) * (5 - __f2dace_OA_tendency_loc_cld_d_2_s_30)) +
                          (__f2dace_A_tendency_loc_cld_d_0_s_28 * ((-__f2dace_OA_tendency_loc_cld_d_1_s_29) + tmp_parfor_60))) -
                         __f2dace_OA_tendency_loc_cld_d_0_s_28) +
                        tmp_parfor_59)] = tendency_loc_cld_out_0;
                }
            }
        }
    }

    {
        double* pfcqsng_view_46;
        pfcqsng_view_46 = &pfcqsng[0];
        double* tendency_loc_t_view_6;
        tendency_loc_t_view_6 = &tendency_loc_t[0];
        double* pnice_view_36;
        pnice_view_36 = &pnice[0];
        double* pfsqlf_view_39;
        pfsqlf_view_39 = &pfsqlf[0];
        double* pq_view_1;
        pq_view_1 = &pq[0];
        double* pa_view_29;
        pa_view_29 = &pa[0];
        double* pvfl_view_11;
        pvfl_view_11 = &pvfl[0];
        double* pdynl_view_14;
        pdynl_view_14 = &pdynl[0];
        double* plcrit_aer_view_32;
        plcrit_aer_view_32 = &plcrit_aer[0];
        double* pfhpsn_view_52;
        pfhpsn_view_52 = &pfhpsn[0];
        double* pclv_view_30;
        pclv_view_30 = &pclv[0];
        double* pfsqltur_view_47;
        pfsqltur_view_47 = &pfsqltur[0];
        double* phrsw_view_16;
        phrsw_view_16 = &phrsw[0];
        double* tendency_tmp_t_view_2;
        tendency_tmp_t_view_2 = &tendency_tmp_t[0];
        double* pap_view_19;
        pap_view_19 = &pap[0];
        double* pfsqrf_view_43;
        pfsqrf_view_43 = &pfsqrf[0];
        double* pmfu_view_27;
        pmfu_view_27 = &pmfu[0];
        double* pfsqitur_view_48;
        pfsqitur_view_48 = &pfsqitur[0];
        double* pfsqif_view_40;
        pfsqif_view_40 = &pfsqif[0];
        double* pvervel_view_18;
        pvervel_view_18 = &pvervel[0];
        double* pmfd_view_28;
        pmfd_view_28 = &pmfd[0];
        double* pdyna_view_13;
        pdyna_view_13 = &pdyna[0];
        double* psupsat_view_31;
        psupsat_view_31 = &psupsat[0];
        double* picrit_aer_view_33;
        picrit_aer_view_33 = &picrit_aer[0];
        double* pt_view_0;
        pt_view_0 = &pt[0];
        double* plu_view_24;
        plu_view_24 = &plu[0];
        double* pre_ice_view_34;
        pre_ice_view_34 = &pre_ice[0];
        double* pccn_view_35;
        pccn_view_35 = &pccn[0];
        double* plude_view_25;
        plude_view_25 = &plude[0];
        double* psnde_view_26;
        psnde_view_26 = &psnde[0];
        double* tendency_loc_a_view_8;
        tendency_loc_a_view_8 = &tendency_loc_a[0];
        double* pvfa_view_10;
        pvfa_view_10 = &pvfa[0];
        double* pvfi_view_12;
        pvfi_view_12 = &pvfi[0];
        double* tendency_tmp_cld_view_5;
        tendency_tmp_cld_view_5 = &tendency_tmp_cld[0];
        double* paph_view_20;
        paph_view_20 = &paph[0];
        double* tendency_tmp_a_view_4;
        tendency_tmp_a_view_4 = &tendency_tmp_a[0];
        double* tendency_tmp_q_view_3;
        tendency_tmp_q_view_3 = &tendency_tmp_q[0];
        double* pfplsn_view_50;
        pfplsn_view_50 = &pfplsn[0];
        double* pfcqrng_view_45;
        pfcqrng_view_45 = &pfcqrng[0];
        double* pfcqlng_view_42;
        pfcqlng_view_42 = &pfcqlng[0];
        double* tendency_loc_cld_view_9;
        tendency_loc_cld_view_9 = &tendency_loc_cld[0];
        double* phrlw_view_17;
        phrlw_view_17 = &phrlw[0];
        double* pdyni_view_15;
        pdyni_view_15 = &pdyni[0];
        double* pfplsl_view_49;
        pfplsl_view_49 = &pfplsl[0];
        double* pfhpsl_view_51;
        pfhpsl_view_51 = &pfhpsl[0];
        double* pfcqnng_view_41;
        pfcqnng_view_41 = &pfcqnng[0];
        double* pfsqsf_view_44;
        pfsqsf_view_44 = &pfsqsf[0];
        double* pcovptot_view_37;
        pcovptot_view_37 = &pcovptot[0];
        double* tendency_loc_q_view_7;
        tendency_loc_q_view_7 = &tendency_loc_q[0];

        mycloudsc0_1_3_123(
            __state, &kfldx, &nlev, &nproma, &ktype[0], &ldcum[0], &pa_view_29[0], &pap_view_19[0], &paph_view_20[0], &pccn_view_35[0], &pclv_view_30[0], &pdyna_view_13[0], &pdyni_view_15[0],
            &pdynl_view_14[0], &phrlw_view_17[0], &phrsw_view_16[0], &picrit_aer_view_33[0], &plcrit_aer_view_32[0], &plsm[0], &plu_view_24[0], &pmfd_view_28[0], &pmfu_view_27[0], &pnice_view_36[0],
            &pq_view_1[0], &pre_ice_view_34[0], &psnde_view_26[0], &psupsat_view_31[0], &pt_view_0[0], &tendency_tmp_a_view_4[0], &tendency_tmp_cld_view_5[0], &tendency_tmp_q_view_3[0],
            &tendency_tmp_t_view_2[0], &ptsphy, &pvervel_view_18[0], &pvfa_view_10[0], &pvfi_view_12[0], &pvfl_view_11[0], &pcovptot[0], &pfcqlng[0], &pfcqnng[0], &pfcqrng[0], &pfcqsng[0], &pfhpsl[0],
            &pfhpsn[0], &pfplsl[0], &pfplsn[0], &pfsqif[0], &pfsqitur[0], &pfsqlf[0], &pfsqltur[0], &pfsqrf[0], &pfsqsf[0], &plude[0], &prainfrac_toprfz[0], &tendency_loc_a[0], &tendency_loc_cld[0],
            &tendency_loc_q[0], &tendency_loc_t[0], ydomcst, ydecldp, ydoethf, icend, nlev, nproma);
    }
}

void __program_cloudsc_driver_internal(
    cloudsc_driver_state_t* __state, int* __restrict__ ktype, int* __restrict__ ldcum, double* __restrict__ pa, double* __restrict__ pap, double* __restrict__ paph, double* __restrict__ pccn,
    double* __restrict__ pclv, double* __restrict__ pcovptot, double* __restrict__ pdyna, double* __restrict__ pdyni, double* __restrict__ pdynl, double* __restrict__ pfcqlng,
    double* __restrict__ pfcqnng, double* __restrict__ pfcqrng, double* __restrict__ pfcqsng, double* __restrict__ pfhpsl, double* __restrict__ pfhpsn, double* __restrict__ pfplsl,
    double* __restrict__ pfplsn, double* __restrict__ pfsqif, double* __restrict__ pfsqitur, double* __restrict__ pfsqlf, double* __restrict__ pfsqltur, double* __restrict__ pfsqrf,
    double* __restrict__ pfsqsf, double* __restrict__ phrlw, double* __restrict__ phrsw, double* __restrict__ picrit_aer, double* __restrict__ plcrit_aer, double* __restrict__ plsm,
    double* __restrict__ plu, double* __restrict__ plude, double* __restrict__ pmfd, double* __restrict__ pmfu, double* __restrict__ pnice, double* __restrict__ pq,
    double* __restrict__ prainfrac_toprfz, double* __restrict__ pre_ice, double* __restrict__ psnde, double* __restrict__ psupsat, double* __restrict__ pt, double* __restrict__ pvervel,
    double* __restrict__ pvfa, double* __restrict__ pvfi, double* __restrict__ pvfl, double* __restrict__ tendency_loc_a, double* __restrict__ tendency_loc_cld, double* __restrict__ tendency_loc_q,
    double* __restrict__ tendency_loc_t, double* __restrict__ tendency_tmp_a, double* __restrict__ tendency_tmp_cld, double* __restrict__ tendency_tmp_q, double* __restrict__ tendency_tmp_t,
    tecldp* ydecldp, toethf* ydoethf, tomcst* ydomcst, int __f2dace_A_ktype_d_0_s_69, int __f2dace_A_ldcum_d_0_s_67, int __f2dace_A_pa_d_0_s_86, int __f2dace_A_pa_d_1_s_87,
    int __f2dace_A_pap_d_0_s_59, int __f2dace_A_pap_d_1_s_60, int __f2dace_A_paph_d_0_s_62, int __f2dace_A_paph_d_1_s_63, int __f2dace_A_pccn_d_0_s_105, int __f2dace_A_pccn_d_1_s_106,
    int __f2dace_A_pclv_d_0_s_89, int __f2dace_A_pclv_d_1_s_90, int __f2dace_A_pclv_d_2_s_91, int __f2dace_A_pcovptot_d_0_s_111, int __f2dace_A_pcovptot_d_1_s_112, int __f2dace_A_pdyna_d_0_s_41,
    int __f2dace_A_pdyna_d_1_s_42, int __f2dace_A_pdyni_d_0_s_47, int __f2dace_A_pdyni_d_1_s_48, int __f2dace_A_pdynl_d_0_s_44, int __f2dace_A_pdynl_d_1_s_45, int __f2dace_A_pfcqlng_d_0_s_122,
    int __f2dace_A_pfcqlng_d_1_s_123, int __f2dace_A_pfcqnng_d_0_s_125, int __f2dace_A_pfcqnng_d_1_s_126, int __f2dace_A_pfcqrng_d_0_s_134, int __f2dace_A_pfcqrng_d_1_s_135,
    int __f2dace_A_pfcqsng_d_0_s_137, int __f2dace_A_pfcqsng_d_1_s_138, int __f2dace_A_pfhpsl_d_0_s_152, int __f2dace_A_pfhpsl_d_1_s_153, int __f2dace_A_pfhpsn_d_0_s_155,
    int __f2dace_A_pfhpsn_d_1_s_156, int __f2dace_A_pfplsl_d_0_s_146, int __f2dace_A_pfplsl_d_1_s_147, int __f2dace_A_pfplsn_d_0_s_149, int __f2dace_A_pfplsn_d_1_s_150,
    int __f2dace_A_pfsqif_d_0_s_119, int __f2dace_A_pfsqif_d_1_s_120, int __f2dace_A_pfsqitur_d_0_s_143, int __f2dace_A_pfsqitur_d_1_s_144, int __f2dace_A_pfsqlf_d_0_s_116,
    int __f2dace_A_pfsqlf_d_1_s_117, int __f2dace_A_pfsqltur_d_0_s_140, int __f2dace_A_pfsqltur_d_1_s_141, int __f2dace_A_pfsqrf_d_0_s_128, int __f2dace_A_pfsqrf_d_1_s_129,
    int __f2dace_A_pfsqsf_d_0_s_131, int __f2dace_A_pfsqsf_d_1_s_132, int __f2dace_A_phrlw_d_0_s_53, int __f2dace_A_phrlw_d_1_s_54, int __f2dace_A_phrsw_d_0_s_50, int __f2dace_A_phrsw_d_1_s_51,
    int __f2dace_A_picrit_aer_d_0_s_99, int __f2dace_A_picrit_aer_d_1_s_100, int __f2dace_A_plcrit_aer_d_0_s_96, int __f2dace_A_plcrit_aer_d_1_s_97, int __f2dace_A_plsm_d_0_s_65,
    int __f2dace_A_plu_d_0_s_71, int __f2dace_A_plu_d_1_s_72, int __f2dace_A_plude_d_0_s_74, int __f2dace_A_plude_d_1_s_75, int __f2dace_A_pmfd_d_0_s_83, int __f2dace_A_pmfd_d_1_s_84,
    int __f2dace_A_pmfu_d_0_s_80, int __f2dace_A_pmfu_d_1_s_81, int __f2dace_A_pnice_d_0_s_108, int __f2dace_A_pnice_d_1_s_109, int __f2dace_A_pq_d_0_s_3, int __f2dace_A_pq_d_1_s_4,
    int __f2dace_A_prainfrac_toprfz_d_0_s_114, int __f2dace_A_pre_ice_d_0_s_102, int __f2dace_A_pre_ice_d_1_s_103, int __f2dace_A_psnde_d_0_s_77, int __f2dace_A_psnde_d_1_s_78,
    int __f2dace_A_psupsat_d_0_s_93, int __f2dace_A_psupsat_d_1_s_94, int __f2dace_A_pt_d_0_s_0, int __f2dace_A_pt_d_1_s_1, int __f2dace_A_pvervel_d_0_s_56, int __f2dace_A_pvervel_d_1_s_57,
    int __f2dace_A_pvfa_d_0_s_32, int __f2dace_A_pvfa_d_1_s_33, int __f2dace_A_pvfi_d_0_s_38, int __f2dace_A_pvfi_d_1_s_39, int __f2dace_A_pvfl_d_0_s_35, int __f2dace_A_pvfl_d_1_s_36,
    int __f2dace_A_tendency_loc_a_d_0_s_25, int __f2dace_A_tendency_loc_a_d_1_s_26, int __f2dace_A_tendency_loc_cld_d_0_s_28, int __f2dace_A_tendency_loc_cld_d_1_s_29,
    int __f2dace_A_tendency_loc_cld_d_2_s_30, int __f2dace_A_tendency_loc_q_d_0_s_22, int __f2dace_A_tendency_loc_q_d_1_s_23, int __f2dace_A_tendency_loc_t_d_0_s_19,
    int __f2dace_A_tendency_loc_t_d_1_s_20, int __f2dace_A_tendency_tmp_a_d_0_s_12, int __f2dace_A_tendency_tmp_a_d_1_s_13, int __f2dace_A_tendency_tmp_cld_d_0_s_15,
    int __f2dace_A_tendency_tmp_cld_d_1_s_16, int __f2dace_A_tendency_tmp_cld_d_2_s_17, int __f2dace_A_tendency_tmp_q_d_0_s_9, int __f2dace_A_tendency_tmp_q_d_1_s_10,
    int __f2dace_A_tendency_tmp_t_d_0_s_6, int __f2dace_A_tendency_tmp_t_d_1_s_7, int __f2dace_OA_ktype_d_1_s_70, int __f2dace_OA_ldcum_d_1_s_68, int __f2dace_OA_pa_d_2_s_88,
    int __f2dace_OA_pap_d_2_s_61, int __f2dace_OA_paph_d_2_s_64, int __f2dace_OA_pccn_d_2_s_107, int __f2dace_OA_pclv_d_3_s_92, int __f2dace_OA_pcovptot_d_0_s_111, int __f2dace_OA_pcovptot_d_1_s_112,
    int __f2dace_OA_pcovptot_d_2_s_113, int __f2dace_OA_pdyna_d_2_s_43, int __f2dace_OA_pdyni_d_2_s_49, int __f2dace_OA_pdynl_d_2_s_46, int __f2dace_OA_pfcqlng_d_2_s_124,
    int __f2dace_OA_pfcqnng_d_2_s_127, int __f2dace_OA_pfcqrng_d_2_s_136, int __f2dace_OA_pfcqsng_d_2_s_139, int __f2dace_OA_pfhpsl_d_2_s_154, int __f2dace_OA_pfhpsn_d_2_s_157,
    int __f2dace_OA_pfplsl_d_2_s_148, int __f2dace_OA_pfplsn_d_2_s_151, int __f2dace_OA_pfsqif_d_2_s_121, int __f2dace_OA_pfsqitur_d_2_s_145, int __f2dace_OA_pfsqlf_d_2_s_118,
    int __f2dace_OA_pfsqltur_d_2_s_142, int __f2dace_OA_pfsqrf_d_2_s_130, int __f2dace_OA_pfsqsf_d_2_s_133, int __f2dace_OA_phrlw_d_2_s_55, int __f2dace_OA_phrsw_d_2_s_52,
    int __f2dace_OA_picrit_aer_d_2_s_101, int __f2dace_OA_plcrit_aer_d_2_s_98, int __f2dace_OA_plsm_d_1_s_66, int __f2dace_OA_plu_d_2_s_73, int __f2dace_OA_plude_d_2_s_76,
    int __f2dace_OA_pmfd_d_2_s_85, int __f2dace_OA_pmfu_d_2_s_82, int __f2dace_OA_pnice_d_2_s_110, int __f2dace_OA_pq_d_2_s_5, int __f2dace_OA_prainfrac_toprfz_d_1_s_115,
    int __f2dace_OA_pre_ice_d_2_s_104, int __f2dace_OA_psnde_d_2_s_79, int __f2dace_OA_psupsat_d_2_s_95, int __f2dace_OA_pt_d_2_s_2, int __f2dace_OA_pvervel_d_2_s_58, int __f2dace_OA_pvfa_d_2_s_34,
    int __f2dace_OA_pvfi_d_2_s_40, int __f2dace_OA_pvfl_d_2_s_37, int __f2dace_OA_tendency_loc_a_d_2_s_27, int __f2dace_OA_tendency_loc_cld_d_0_s_28, int __f2dace_OA_tendency_loc_cld_d_1_s_29,
    int __f2dace_OA_tendency_loc_cld_d_2_s_30, int __f2dace_OA_tendency_loc_cld_d_3_s_31, int __f2dace_OA_tendency_loc_q_d_2_s_24, int __f2dace_OA_tendency_loc_t_d_2_s_21,
    int __f2dace_OA_tendency_tmp_a_d_2_s_14, int __f2dace_OA_tendency_tmp_cld_d_3_s_18, int __f2dace_OA_tendency_tmp_q_d_2_s_11, int __f2dace_OA_tendency_tmp_t_d_2_s_8, int kfldx, int ngptot,
    int ngptotg, int nlev, int nproma, int numomp, double ptsphy) {
    int tmp_call_122;
    int ngpblks;

    tmp_call_122 = Mod(ngptot, nproma);

    ngpblks = ((ngptot / nproma) + min(tmp_call_122, 1));

    {
        {
#pragma omp parallel for
            for (auto _for_it_129 = 1; _for_it_129 < (ngpblks + 1); _for_it_129 += 1) {
                loop_body_0_2_0(
                    __state, kfldx, &ktype[(__f2dace_A_ktype_d_0_s_69 * ((-__f2dace_OA_ktype_d_1_s_70) + _for_it_129))],
                    &ldcum[(__f2dace_A_ldcum_d_0_s_67 * ((-__f2dace_OA_ldcum_d_1_s_68) + _for_it_129))], ngptot, nlev, nproma,
                    &pa[((__f2dace_A_pa_d_0_s_86 * __f2dace_A_pa_d_1_s_87) * ((-__f2dace_OA_pa_d_2_s_88) + _for_it_129))],
                    &pap[((__f2dace_A_pap_d_0_s_59 * __f2dace_A_pap_d_1_s_60) * ((-__f2dace_OA_pap_d_2_s_61) + _for_it_129))],
                    &paph[((__f2dace_A_paph_d_0_s_62 * __f2dace_A_paph_d_1_s_63) * ((-__f2dace_OA_paph_d_2_s_64) + _for_it_129))],
                    &pccn[((__f2dace_A_pccn_d_0_s_105 * __f2dace_A_pccn_d_1_s_106) * ((-__f2dace_OA_pccn_d_2_s_107) + _for_it_129))],
                    &pclv[(((__f2dace_A_pclv_d_0_s_89 * __f2dace_A_pclv_d_1_s_90) * __f2dace_A_pclv_d_2_s_91) * ((-__f2dace_OA_pclv_d_3_s_92) + _for_it_129))],
                    &pdyna[((__f2dace_A_pdyna_d_0_s_41 * __f2dace_A_pdyna_d_1_s_42) * ((-__f2dace_OA_pdyna_d_2_s_43) + _for_it_129))],
                    &pdyni[((__f2dace_A_pdyni_d_0_s_47 * __f2dace_A_pdyni_d_1_s_48) * ((-__f2dace_OA_pdyni_d_2_s_49) + _for_it_129))],
                    &pdynl[((__f2dace_A_pdynl_d_0_s_44 * __f2dace_A_pdynl_d_1_s_45) * ((-__f2dace_OA_pdynl_d_2_s_46) + _for_it_129))],
                    &phrlw[((__f2dace_A_phrlw_d_0_s_53 * __f2dace_A_phrlw_d_1_s_54) * ((-__f2dace_OA_phrlw_d_2_s_55) + _for_it_129))],
                    &phrsw[((__f2dace_A_phrsw_d_0_s_50 * __f2dace_A_phrsw_d_1_s_51) * ((-__f2dace_OA_phrsw_d_2_s_52) + _for_it_129))],
                    &picrit_aer[((__f2dace_A_picrit_aer_d_0_s_99 * __f2dace_A_picrit_aer_d_1_s_100) * ((-__f2dace_OA_picrit_aer_d_2_s_101) + _for_it_129))],
                    &plcrit_aer[((__f2dace_A_plcrit_aer_d_0_s_96 * __f2dace_A_plcrit_aer_d_1_s_97) * ((-__f2dace_OA_plcrit_aer_d_2_s_98) + _for_it_129))],
                    &plsm[(__f2dace_A_plsm_d_0_s_65 * ((-__f2dace_OA_plsm_d_1_s_66) + _for_it_129))],
                    &plu[((__f2dace_A_plu_d_0_s_71 * __f2dace_A_plu_d_1_s_72) * ((-__f2dace_OA_plu_d_2_s_73) + _for_it_129))],
                    &pmfd[((__f2dace_A_pmfd_d_0_s_83 * __f2dace_A_pmfd_d_1_s_84) * ((-__f2dace_OA_pmfd_d_2_s_85) + _for_it_129))],
                    &pmfu[((__f2dace_A_pmfu_d_0_s_80 * __f2dace_A_pmfu_d_1_s_81) * ((-__f2dace_OA_pmfu_d_2_s_82) + _for_it_129))],
                    &pnice[((__f2dace_A_pnice_d_0_s_108 * __f2dace_A_pnice_d_1_s_109) * ((-__f2dace_OA_pnice_d_2_s_110) + _for_it_129))],
                    &pq[((__f2dace_A_pq_d_0_s_3 * __f2dace_A_pq_d_1_s_4) * ((-__f2dace_OA_pq_d_2_s_5) + _for_it_129))],
                    &pre_ice[((__f2dace_A_pre_ice_d_0_s_102 * __f2dace_A_pre_ice_d_1_s_103) * ((-__f2dace_OA_pre_ice_d_2_s_104) + _for_it_129))],
                    &psnde[((__f2dace_A_psnde_d_0_s_77 * __f2dace_A_psnde_d_1_s_78) * ((-__f2dace_OA_psnde_d_2_s_79) + _for_it_129))],
                    &psupsat[((__f2dace_A_psupsat_d_0_s_93 * __f2dace_A_psupsat_d_1_s_94) * ((-__f2dace_OA_psupsat_d_2_s_95) + _for_it_129))],
                    &pt[((__f2dace_A_pt_d_0_s_0 * __f2dace_A_pt_d_1_s_1) * ((-__f2dace_OA_pt_d_2_s_2) + _for_it_129))], ptsphy,
                    &pvervel[((__f2dace_A_pvervel_d_0_s_56 * __f2dace_A_pvervel_d_1_s_57) * ((-__f2dace_OA_pvervel_d_2_s_58) + _for_it_129))],
                    &pvfa[((__f2dace_A_pvfa_d_0_s_32 * __f2dace_A_pvfa_d_1_s_33) * ((-__f2dace_OA_pvfa_d_2_s_34) + _for_it_129))],
                    &pvfi[((__f2dace_A_pvfi_d_0_s_38 * __f2dace_A_pvfi_d_1_s_39) * ((-__f2dace_OA_pvfi_d_2_s_40) + _for_it_129))],
                    &pvfl[((__f2dace_A_pvfl_d_0_s_35 * __f2dace_A_pvfl_d_1_s_36) * ((-__f2dace_OA_pvfl_d_2_s_37) + _for_it_129))],
                    &tendency_tmp_a[((__f2dace_A_tendency_tmp_a_d_0_s_12 * __f2dace_A_tendency_tmp_a_d_1_s_13) * ((-__f2dace_OA_tendency_tmp_a_d_2_s_14) + _for_it_129))],
                    &tendency_tmp_cld[(
                        ((__f2dace_A_tendency_tmp_cld_d_0_s_15 * __f2dace_A_tendency_tmp_cld_d_1_s_16) * __f2dace_A_tendency_tmp_cld_d_2_s_17) *
                        ((-__f2dace_OA_tendency_tmp_cld_d_3_s_18) + _for_it_129))],
                    &tendency_tmp_q[((__f2dace_A_tendency_tmp_q_d_0_s_9 * __f2dace_A_tendency_tmp_q_d_1_s_10) * ((-__f2dace_OA_tendency_tmp_q_d_2_s_11) + _for_it_129))],
                    &tendency_tmp_t[((__f2dace_A_tendency_tmp_t_d_0_s_6 * __f2dace_A_tendency_tmp_t_d_1_s_7) * ((-__f2dace_OA_tendency_tmp_t_d_2_s_8) + _for_it_129))],
                    &pcovptot[((__f2dace_A_pcovptot_d_0_s_111 * __f2dace_A_pcovptot_d_1_s_112) * ((-__f2dace_OA_pcovptot_d_2_s_113) + _for_it_129))],
                    &pfcqlng[((__f2dace_A_pfcqlng_d_0_s_122 * __f2dace_A_pfcqlng_d_1_s_123) * ((-__f2dace_OA_pfcqlng_d_2_s_124) + _for_it_129))],
                    &pfcqnng[((__f2dace_A_pfcqnng_d_0_s_125 * __f2dace_A_pfcqnng_d_1_s_126) * ((-__f2dace_OA_pfcqnng_d_2_s_127) + _for_it_129))],
                    &pfcqrng[((__f2dace_A_pfcqrng_d_0_s_134 * __f2dace_A_pfcqrng_d_1_s_135) * ((-__f2dace_OA_pfcqrng_d_2_s_136) + _for_it_129))],
                    &pfcqsng[((__f2dace_A_pfcqsng_d_0_s_137 * __f2dace_A_pfcqsng_d_1_s_138) * ((-__f2dace_OA_pfcqsng_d_2_s_139) + _for_it_129))],
                    &pfhpsl[((__f2dace_A_pfhpsl_d_0_s_152 * __f2dace_A_pfhpsl_d_1_s_153) * ((-__f2dace_OA_pfhpsl_d_2_s_154) + _for_it_129))],
                    &pfhpsn[((__f2dace_A_pfhpsn_d_0_s_155 * __f2dace_A_pfhpsn_d_1_s_156) * ((-__f2dace_OA_pfhpsn_d_2_s_157) + _for_it_129))],
                    &pfplsl[((__f2dace_A_pfplsl_d_0_s_146 * __f2dace_A_pfplsl_d_1_s_147) * ((-__f2dace_OA_pfplsl_d_2_s_148) + _for_it_129))],
                    &pfplsn[((__f2dace_A_pfplsn_d_0_s_149 * __f2dace_A_pfplsn_d_1_s_150) * ((-__f2dace_OA_pfplsn_d_2_s_151) + _for_it_129))],
                    &pfsqif[((__f2dace_A_pfsqif_d_0_s_119 * __f2dace_A_pfsqif_d_1_s_120) * ((-__f2dace_OA_pfsqif_d_2_s_121) + _for_it_129))],
                    &pfsqitur[((__f2dace_A_pfsqitur_d_0_s_143 * __f2dace_A_pfsqitur_d_1_s_144) * ((-__f2dace_OA_pfsqitur_d_2_s_145) + _for_it_129))],
                    &pfsqlf[((__f2dace_A_pfsqlf_d_0_s_116 * __f2dace_A_pfsqlf_d_1_s_117) * ((-__f2dace_OA_pfsqlf_d_2_s_118) + _for_it_129))],
                    &pfsqltur[((__f2dace_A_pfsqltur_d_0_s_140 * __f2dace_A_pfsqltur_d_1_s_141) * ((-__f2dace_OA_pfsqltur_d_2_s_142) + _for_it_129))],
                    &pfsqrf[((__f2dace_A_pfsqrf_d_0_s_128 * __f2dace_A_pfsqrf_d_1_s_129) * ((-__f2dace_OA_pfsqrf_d_2_s_130) + _for_it_129))],
                    &pfsqsf[((__f2dace_A_pfsqsf_d_0_s_131 * __f2dace_A_pfsqsf_d_1_s_132) * ((-__f2dace_OA_pfsqsf_d_2_s_133) + _for_it_129))],
                    &plude[((__f2dace_A_plude_d_0_s_74 * __f2dace_A_plude_d_1_s_75) * ((-__f2dace_OA_plude_d_2_s_76) + _for_it_129))],
                    &prainfrac_toprfz[(__f2dace_A_prainfrac_toprfz_d_0_s_114 * ((-__f2dace_OA_prainfrac_toprfz_d_1_s_115) + _for_it_129))],
                    &tendency_loc_a[((__f2dace_A_tendency_loc_a_d_0_s_25 * __f2dace_A_tendency_loc_a_d_1_s_26) * ((-__f2dace_OA_tendency_loc_a_d_2_s_27) + _for_it_129))],
                    &tendency_loc_cld[(
                        ((__f2dace_A_tendency_loc_cld_d_0_s_28 * __f2dace_A_tendency_loc_cld_d_1_s_29) * __f2dace_A_tendency_loc_cld_d_2_s_30) *
                        ((-__f2dace_OA_tendency_loc_cld_d_3_s_31) + _for_it_129))],
                    &tendency_loc_q[((__f2dace_A_tendency_loc_q_d_0_s_22 * __f2dace_A_tendency_loc_q_d_1_s_23) * ((-__f2dace_OA_tendency_loc_q_d_2_s_24) + _for_it_129))],
                    &tendency_loc_t[((__f2dace_A_tendency_loc_t_d_0_s_19 * __f2dace_A_tendency_loc_t_d_1_s_20) * ((-__f2dace_OA_tendency_loc_t_d_2_s_21) + _for_it_129))], ydecldp, ydoethf, ydomcst,
                    __f2dace_A_ktype_d_0_s_69, __f2dace_A_ldcum_d_0_s_67, __f2dace_A_pa_d_0_s_86, __f2dace_A_pa_d_1_s_87, __f2dace_A_pap_d_0_s_59, __f2dace_A_pap_d_1_s_60, __f2dace_A_paph_d_0_s_62,
                    __f2dace_A_paph_d_1_s_63, __f2dace_A_pccn_d_0_s_105, __f2dace_A_pccn_d_1_s_106, __f2dace_A_pclv_d_0_s_89, __f2dace_A_pclv_d_1_s_90, __f2dace_A_pclv_d_2_s_91,
                    __f2dace_A_pcovptot_d_0_s_111, __f2dace_A_pcovptot_d_1_s_112, __f2dace_A_pdyna_d_0_s_41, __f2dace_A_pdyna_d_1_s_42, __f2dace_A_pdyni_d_0_s_47, __f2dace_A_pdyni_d_1_s_48,
                    __f2dace_A_pdynl_d_0_s_44, __f2dace_A_pdynl_d_1_s_45, __f2dace_A_pfcqlng_d_0_s_122, __f2dace_A_pfcqlng_d_1_s_123, __f2dace_A_pfcqnng_d_0_s_125, __f2dace_A_pfcqnng_d_1_s_126,
                    __f2dace_A_pfcqrng_d_0_s_134, __f2dace_A_pfcqrng_d_1_s_135, __f2dace_A_pfcqsng_d_0_s_137, __f2dace_A_pfcqsng_d_1_s_138, __f2dace_A_pfhpsl_d_0_s_152, __f2dace_A_pfhpsl_d_1_s_153,
                    __f2dace_A_pfhpsn_d_0_s_155, __f2dace_A_pfhpsn_d_1_s_156, __f2dace_A_pfplsl_d_0_s_146, __f2dace_A_pfplsl_d_1_s_147, __f2dace_A_pfplsn_d_0_s_149, __f2dace_A_pfplsn_d_1_s_150,
                    __f2dace_A_pfsqif_d_0_s_119, __f2dace_A_pfsqif_d_1_s_120, __f2dace_A_pfsqitur_d_0_s_143, __f2dace_A_pfsqitur_d_1_s_144, __f2dace_A_pfsqlf_d_0_s_116, __f2dace_A_pfsqlf_d_1_s_117,
                    __f2dace_A_pfsqltur_d_0_s_140, __f2dace_A_pfsqltur_d_1_s_141, __f2dace_A_pfsqrf_d_0_s_128, __f2dace_A_pfsqrf_d_1_s_129, __f2dace_A_pfsqsf_d_0_s_131, __f2dace_A_pfsqsf_d_1_s_132,
                    __f2dace_A_phrlw_d_0_s_53, __f2dace_A_phrlw_d_1_s_54, __f2dace_A_phrsw_d_0_s_50, __f2dace_A_phrsw_d_1_s_51, __f2dace_A_picrit_aer_d_0_s_99, __f2dace_A_picrit_aer_d_1_s_100,
                    __f2dace_A_plcrit_aer_d_0_s_96, __f2dace_A_plcrit_aer_d_1_s_97, __f2dace_A_plsm_d_0_s_65, __f2dace_A_plu_d_0_s_71, __f2dace_A_plu_d_1_s_72, __f2dace_A_plude_d_0_s_74,
                    __f2dace_A_plude_d_1_s_75, __f2dace_A_pmfd_d_0_s_83, __f2dace_A_pmfd_d_1_s_84, __f2dace_A_pmfu_d_0_s_80, __f2dace_A_pmfu_d_1_s_81, __f2dace_A_pnice_d_0_s_108,
                    __f2dace_A_pnice_d_1_s_109, __f2dace_A_pq_d_0_s_3, __f2dace_A_pq_d_1_s_4, __f2dace_A_prainfrac_toprfz_d_0_s_114, __f2dace_A_pre_ice_d_0_s_102, __f2dace_A_pre_ice_d_1_s_103,
                    __f2dace_A_psnde_d_0_s_77, __f2dace_A_psnde_d_1_s_78, __f2dace_A_psupsat_d_0_s_93, __f2dace_A_psupsat_d_1_s_94, __f2dace_A_pt_d_0_s_0, __f2dace_A_pt_d_1_s_1,
                    __f2dace_A_pvervel_d_0_s_56, __f2dace_A_pvervel_d_1_s_57, __f2dace_A_pvfa_d_0_s_32, __f2dace_A_pvfa_d_1_s_33, __f2dace_A_pvfi_d_0_s_38, __f2dace_A_pvfi_d_1_s_39,
                    __f2dace_A_pvfl_d_0_s_35, __f2dace_A_pvfl_d_1_s_36, __f2dace_A_tendency_loc_a_d_0_s_25, __f2dace_A_tendency_loc_a_d_1_s_26, __f2dace_A_tendency_loc_cld_d_0_s_28,
                    __f2dace_A_tendency_loc_cld_d_1_s_29, __f2dace_A_tendency_loc_cld_d_2_s_30, __f2dace_A_tendency_loc_q_d_0_s_22, __f2dace_A_tendency_loc_q_d_1_s_23,
                    __f2dace_A_tendency_loc_t_d_0_s_19, __f2dace_A_tendency_loc_t_d_1_s_20, __f2dace_A_tendency_tmp_a_d_0_s_12, __f2dace_A_tendency_tmp_a_d_1_s_13,
                    __f2dace_A_tendency_tmp_cld_d_0_s_15, __f2dace_A_tendency_tmp_cld_d_1_s_16, __f2dace_A_tendency_tmp_cld_d_2_s_17, __f2dace_A_tendency_tmp_q_d_0_s_9,
                    __f2dace_A_tendency_tmp_q_d_1_s_10, __f2dace_A_tendency_tmp_t_d_0_s_6, __f2dace_A_tendency_tmp_t_d_1_s_7, __f2dace_OA_pcovptot_d_0_s_111, __f2dace_OA_pcovptot_d_1_s_112,
                    __f2dace_OA_tendency_loc_cld_d_0_s_28, __f2dace_OA_tendency_loc_cld_d_1_s_29, __f2dace_OA_tendency_loc_cld_d_2_s_30, _for_it_129);
            }
        }
    }
}

DACE_EXPORTED void __program_cloudsc_driver(
    cloudsc_driver_state_t* __state, int* __restrict__ ktype, int* __restrict__ ldcum, double* __restrict__ pa, double* __restrict__ pap, double* __restrict__ paph, double* __restrict__ pccn,
    double* __restrict__ pclv, double* __restrict__ pcovptot, double* __restrict__ pdyna, double* __restrict__ pdyni, double* __restrict__ pdynl, double* __restrict__ pfcqlng,
    double* __restrict__ pfcqnng, double* __restrict__ pfcqrng, double* __restrict__ pfcqsng, double* __restrict__ pfhpsl, double* __restrict__ pfhpsn, double* __restrict__ pfplsl,
    double* __restrict__ pfplsn, double* __restrict__ pfsqif, double* __restrict__ pfsqitur, double* __restrict__ pfsqlf, double* __restrict__ pfsqltur, double* __restrict__ pfsqrf,
    double* __restrict__ pfsqsf, double* __restrict__ phrlw, double* __restrict__ phrsw, double* __restrict__ picrit_aer, double* __restrict__ plcrit_aer, double* __restrict__ plsm,
    double* __restrict__ plu, double* __restrict__ plude, double* __restrict__ pmfd, double* __restrict__ pmfu, double* __restrict__ pnice, double* __restrict__ pq,
    double* __restrict__ prainfrac_toprfz, double* __restrict__ pre_ice, double* __restrict__ psnde, double* __restrict__ psupsat, double* __restrict__ pt, double* __restrict__ pvervel,
    double* __restrict__ pvfa, double* __restrict__ pvfi, double* __restrict__ pvfl, double* __restrict__ tendency_loc_a, double* __restrict__ tendency_loc_cld, double* __restrict__ tendency_loc_q,
    double* __restrict__ tendency_loc_t, double* __restrict__ tendency_tmp_a, double* __restrict__ tendency_tmp_cld, double* __restrict__ tendency_tmp_q, double* __restrict__ tendency_tmp_t,
    tecldp* ydecldp, toethf* ydoethf, tomcst* ydomcst, int __f2dace_A_ktype_d_0_s_69, int __f2dace_A_ldcum_d_0_s_67, int __f2dace_A_pa_d_0_s_86, int __f2dace_A_pa_d_1_s_87,
    int __f2dace_A_pap_d_0_s_59, int __f2dace_A_pap_d_1_s_60, int __f2dace_A_paph_d_0_s_62, int __f2dace_A_paph_d_1_s_63, int __f2dace_A_pccn_d_0_s_105, int __f2dace_A_pccn_d_1_s_106,
    int __f2dace_A_pclv_d_0_s_89, int __f2dace_A_pclv_d_1_s_90, int __f2dace_A_pclv_d_2_s_91, int __f2dace_A_pcovptot_d_0_s_111, int __f2dace_A_pcovptot_d_1_s_112, int __f2dace_A_pdyna_d_0_s_41,
    int __f2dace_A_pdyna_d_1_s_42, int __f2dace_A_pdyni_d_0_s_47, int __f2dace_A_pdyni_d_1_s_48, int __f2dace_A_pdynl_d_0_s_44, int __f2dace_A_pdynl_d_1_s_45, int __f2dace_A_pfcqlng_d_0_s_122,
    int __f2dace_A_pfcqlng_d_1_s_123, int __f2dace_A_pfcqnng_d_0_s_125, int __f2dace_A_pfcqnng_d_1_s_126, int __f2dace_A_pfcqrng_d_0_s_134, int __f2dace_A_pfcqrng_d_1_s_135,
    int __f2dace_A_pfcqsng_d_0_s_137, int __f2dace_A_pfcqsng_d_1_s_138, int __f2dace_A_pfhpsl_d_0_s_152, int __f2dace_A_pfhpsl_d_1_s_153, int __f2dace_A_pfhpsn_d_0_s_155,
    int __f2dace_A_pfhpsn_d_1_s_156, int __f2dace_A_pfplsl_d_0_s_146, int __f2dace_A_pfplsl_d_1_s_147, int __f2dace_A_pfplsn_d_0_s_149, int __f2dace_A_pfplsn_d_1_s_150,
    int __f2dace_A_pfsqif_d_0_s_119, int __f2dace_A_pfsqif_d_1_s_120, int __f2dace_A_pfsqitur_d_0_s_143, int __f2dace_A_pfsqitur_d_1_s_144, int __f2dace_A_pfsqlf_d_0_s_116,
    int __f2dace_A_pfsqlf_d_1_s_117, int __f2dace_A_pfsqltur_d_0_s_140, int __f2dace_A_pfsqltur_d_1_s_141, int __f2dace_A_pfsqrf_d_0_s_128, int __f2dace_A_pfsqrf_d_1_s_129,
    int __f2dace_A_pfsqsf_d_0_s_131, int __f2dace_A_pfsqsf_d_1_s_132, int __f2dace_A_phrlw_d_0_s_53, int __f2dace_A_phrlw_d_1_s_54, int __f2dace_A_phrsw_d_0_s_50, int __f2dace_A_phrsw_d_1_s_51,
    int __f2dace_A_picrit_aer_d_0_s_99, int __f2dace_A_picrit_aer_d_1_s_100, int __f2dace_A_plcrit_aer_d_0_s_96, int __f2dace_A_plcrit_aer_d_1_s_97, int __f2dace_A_plsm_d_0_s_65,
    int __f2dace_A_plu_d_0_s_71, int __f2dace_A_plu_d_1_s_72, int __f2dace_A_plude_d_0_s_74, int __f2dace_A_plude_d_1_s_75, int __f2dace_A_pmfd_d_0_s_83, int __f2dace_A_pmfd_d_1_s_84,
    int __f2dace_A_pmfu_d_0_s_80, int __f2dace_A_pmfu_d_1_s_81, int __f2dace_A_pnice_d_0_s_108, int __f2dace_A_pnice_d_1_s_109, int __f2dace_A_pq_d_0_s_3, int __f2dace_A_pq_d_1_s_4,
    int __f2dace_A_prainfrac_toprfz_d_0_s_114, int __f2dace_A_pre_ice_d_0_s_102, int __f2dace_A_pre_ice_d_1_s_103, int __f2dace_A_psnde_d_0_s_77, int __f2dace_A_psnde_d_1_s_78,
    int __f2dace_A_psupsat_d_0_s_93, int __f2dace_A_psupsat_d_1_s_94, int __f2dace_A_pt_d_0_s_0, int __f2dace_A_pt_d_1_s_1, int __f2dace_A_pvervel_d_0_s_56, int __f2dace_A_pvervel_d_1_s_57,
    int __f2dace_A_pvfa_d_0_s_32, int __f2dace_A_pvfa_d_1_s_33, int __f2dace_A_pvfi_d_0_s_38, int __f2dace_A_pvfi_d_1_s_39, int __f2dace_A_pvfl_d_0_s_35, int __f2dace_A_pvfl_d_1_s_36,
    int __f2dace_A_tendency_loc_a_d_0_s_25, int __f2dace_A_tendency_loc_a_d_1_s_26, int __f2dace_A_tendency_loc_cld_d_0_s_28, int __f2dace_A_tendency_loc_cld_d_1_s_29,
    int __f2dace_A_tendency_loc_cld_d_2_s_30, int __f2dace_A_tendency_loc_q_d_0_s_22, int __f2dace_A_tendency_loc_q_d_1_s_23, int __f2dace_A_tendency_loc_t_d_0_s_19,
    int __f2dace_A_tendency_loc_t_d_1_s_20, int __f2dace_A_tendency_tmp_a_d_0_s_12, int __f2dace_A_tendency_tmp_a_d_1_s_13, int __f2dace_A_tendency_tmp_cld_d_0_s_15,
    int __f2dace_A_tendency_tmp_cld_d_1_s_16, int __f2dace_A_tendency_tmp_cld_d_2_s_17, int __f2dace_A_tendency_tmp_q_d_0_s_9, int __f2dace_A_tendency_tmp_q_d_1_s_10,
    int __f2dace_A_tendency_tmp_t_d_0_s_6, int __f2dace_A_tendency_tmp_t_d_1_s_7, int __f2dace_OA_ktype_d_1_s_70, int __f2dace_OA_ldcum_d_1_s_68, int __f2dace_OA_pa_d_2_s_88,
    int __f2dace_OA_pap_d_2_s_61, int __f2dace_OA_paph_d_2_s_64, int __f2dace_OA_pccn_d_2_s_107, int __f2dace_OA_pclv_d_3_s_92, int __f2dace_OA_pcovptot_d_0_s_111, int __f2dace_OA_pcovptot_d_1_s_112,
    int __f2dace_OA_pcovptot_d_2_s_113, int __f2dace_OA_pdyna_d_2_s_43, int __f2dace_OA_pdyni_d_2_s_49, int __f2dace_OA_pdynl_d_2_s_46, int __f2dace_OA_pfcqlng_d_2_s_124,
    int __f2dace_OA_pfcqnng_d_2_s_127, int __f2dace_OA_pfcqrng_d_2_s_136, int __f2dace_OA_pfcqsng_d_2_s_139, int __f2dace_OA_pfhpsl_d_2_s_154, int __f2dace_OA_pfhpsn_d_2_s_157,
    int __f2dace_OA_pfplsl_d_2_s_148, int __f2dace_OA_pfplsn_d_2_s_151, int __f2dace_OA_pfsqif_d_2_s_121, int __f2dace_OA_pfsqitur_d_2_s_145, int __f2dace_OA_pfsqlf_d_2_s_118,
    int __f2dace_OA_pfsqltur_d_2_s_142, int __f2dace_OA_pfsqrf_d_2_s_130, int __f2dace_OA_pfsqsf_d_2_s_133, int __f2dace_OA_phrlw_d_2_s_55, int __f2dace_OA_phrsw_d_2_s_52,
    int __f2dace_OA_picrit_aer_d_2_s_101, int __f2dace_OA_plcrit_aer_d_2_s_98, int __f2dace_OA_plsm_d_1_s_66, int __f2dace_OA_plu_d_2_s_73, int __f2dace_OA_plude_d_2_s_76,
    int __f2dace_OA_pmfd_d_2_s_85, int __f2dace_OA_pmfu_d_2_s_82, int __f2dace_OA_pnice_d_2_s_110, int __f2dace_OA_pq_d_2_s_5, int __f2dace_OA_prainfrac_toprfz_d_1_s_115,
    int __f2dace_OA_pre_ice_d_2_s_104, int __f2dace_OA_psnde_d_2_s_79, int __f2dace_OA_psupsat_d_2_s_95, int __f2dace_OA_pt_d_2_s_2, int __f2dace_OA_pvervel_d_2_s_58, int __f2dace_OA_pvfa_d_2_s_34,
    int __f2dace_OA_pvfi_d_2_s_40, int __f2dace_OA_pvfl_d_2_s_37, int __f2dace_OA_tendency_loc_a_d_2_s_27, int __f2dace_OA_tendency_loc_cld_d_0_s_28, int __f2dace_OA_tendency_loc_cld_d_1_s_29,
    int __f2dace_OA_tendency_loc_cld_d_2_s_30, int __f2dace_OA_tendency_loc_cld_d_3_s_31, int __f2dace_OA_tendency_loc_q_d_2_s_24, int __f2dace_OA_tendency_loc_t_d_2_s_21,
    int __f2dace_OA_tendency_tmp_a_d_2_s_14, int __f2dace_OA_tendency_tmp_cld_d_3_s_18, int __f2dace_OA_tendency_tmp_q_d_2_s_11, int __f2dace_OA_tendency_tmp_t_d_2_s_8, int kfldx, int ngptot,
    int ngptotg, int nlev, int nproma, int numomp, double ptsphy) {
    __program_cloudsc_driver_internal(
        __state, ktype, ldcum, pa, pap, paph, pccn, pclv, pcovptot, pdyna, pdyni, pdynl, pfcqlng, pfcqnng, pfcqrng, pfcqsng, pfhpsl, pfhpsn, pfplsl, pfplsn, pfsqif, pfsqitur, pfsqlf, pfsqltur, pfsqrf,
        pfsqsf, phrlw, phrsw, picrit_aer, plcrit_aer, plsm, plu, plude, pmfd, pmfu, pnice, pq, prainfrac_toprfz, pre_ice, psnde, psupsat, pt, pvervel, pvfa, pvfi, pvfl, tendency_loc_a,
        tendency_loc_cld, tendency_loc_q, tendency_loc_t, tendency_tmp_a, tendency_tmp_cld, tendency_tmp_q, tendency_tmp_t, ydecldp, ydoethf, ydomcst, __f2dace_A_ktype_d_0_s_69,
        __f2dace_A_ldcum_d_0_s_67, __f2dace_A_pa_d_0_s_86, __f2dace_A_pa_d_1_s_87, __f2dace_A_pap_d_0_s_59, __f2dace_A_pap_d_1_s_60, __f2dace_A_paph_d_0_s_62, __f2dace_A_paph_d_1_s_63,
        __f2dace_A_pccn_d_0_s_105, __f2dace_A_pccn_d_1_s_106, __f2dace_A_pclv_d_0_s_89, __f2dace_A_pclv_d_1_s_90, __f2dace_A_pclv_d_2_s_91, __f2dace_A_pcovptot_d_0_s_111,
        __f2dace_A_pcovptot_d_1_s_112, __f2dace_A_pdyna_d_0_s_41, __f2dace_A_pdyna_d_1_s_42, __f2dace_A_pdyni_d_0_s_47, __f2dace_A_pdyni_d_1_s_48, __f2dace_A_pdynl_d_0_s_44, __f2dace_A_pdynl_d_1_s_45,
        __f2dace_A_pfcqlng_d_0_s_122, __f2dace_A_pfcqlng_d_1_s_123, __f2dace_A_pfcqnng_d_0_s_125, __f2dace_A_pfcqnng_d_1_s_126, __f2dace_A_pfcqrng_d_0_s_134, __f2dace_A_pfcqrng_d_1_s_135,
        __f2dace_A_pfcqsng_d_0_s_137, __f2dace_A_pfcqsng_d_1_s_138, __f2dace_A_pfhpsl_d_0_s_152, __f2dace_A_pfhpsl_d_1_s_153, __f2dace_A_pfhpsn_d_0_s_155, __f2dace_A_pfhpsn_d_1_s_156,
        __f2dace_A_pfplsl_d_0_s_146, __f2dace_A_pfplsl_d_1_s_147, __f2dace_A_pfplsn_d_0_s_149, __f2dace_A_pfplsn_d_1_s_150, __f2dace_A_pfsqif_d_0_s_119, __f2dace_A_pfsqif_d_1_s_120,
        __f2dace_A_pfsqitur_d_0_s_143, __f2dace_A_pfsqitur_d_1_s_144, __f2dace_A_pfsqlf_d_0_s_116, __f2dace_A_pfsqlf_d_1_s_117, __f2dace_A_pfsqltur_d_0_s_140, __f2dace_A_pfsqltur_d_1_s_141,
        __f2dace_A_pfsqrf_d_0_s_128, __f2dace_A_pfsqrf_d_1_s_129, __f2dace_A_pfsqsf_d_0_s_131, __f2dace_A_pfsqsf_d_1_s_132, __f2dace_A_phrlw_d_0_s_53, __f2dace_A_phrlw_d_1_s_54,
        __f2dace_A_phrsw_d_0_s_50, __f2dace_A_phrsw_d_1_s_51, __f2dace_A_picrit_aer_d_0_s_99, __f2dace_A_picrit_aer_d_1_s_100, __f2dace_A_plcrit_aer_d_0_s_96, __f2dace_A_plcrit_aer_d_1_s_97,
        __f2dace_A_plsm_d_0_s_65, __f2dace_A_plu_d_0_s_71, __f2dace_A_plu_d_1_s_72, __f2dace_A_plude_d_0_s_74, __f2dace_A_plude_d_1_s_75, __f2dace_A_pmfd_d_0_s_83, __f2dace_A_pmfd_d_1_s_84,
        __f2dace_A_pmfu_d_0_s_80, __f2dace_A_pmfu_d_1_s_81, __f2dace_A_pnice_d_0_s_108, __f2dace_A_pnice_d_1_s_109, __f2dace_A_pq_d_0_s_3, __f2dace_A_pq_d_1_s_4, __f2dace_A_prainfrac_toprfz_d_0_s_114,
        __f2dace_A_pre_ice_d_0_s_102, __f2dace_A_pre_ice_d_1_s_103, __f2dace_A_psnde_d_0_s_77, __f2dace_A_psnde_d_1_s_78, __f2dace_A_psupsat_d_0_s_93, __f2dace_A_psupsat_d_1_s_94,
        __f2dace_A_pt_d_0_s_0, __f2dace_A_pt_d_1_s_1, __f2dace_A_pvervel_d_0_s_56, __f2dace_A_pvervel_d_1_s_57, __f2dace_A_pvfa_d_0_s_32, __f2dace_A_pvfa_d_1_s_33, __f2dace_A_pvfi_d_0_s_38,
        __f2dace_A_pvfi_d_1_s_39, __f2dace_A_pvfl_d_0_s_35, __f2dace_A_pvfl_d_1_s_36, __f2dace_A_tendency_loc_a_d_0_s_25, __f2dace_A_tendency_loc_a_d_1_s_26, __f2dace_A_tendency_loc_cld_d_0_s_28,
        __f2dace_A_tendency_loc_cld_d_1_s_29, __f2dace_A_tendency_loc_cld_d_2_s_30, __f2dace_A_tendency_loc_q_d_0_s_22, __f2dace_A_tendency_loc_q_d_1_s_23, __f2dace_A_tendency_loc_t_d_0_s_19,
        __f2dace_A_tendency_loc_t_d_1_s_20, __f2dace_A_tendency_tmp_a_d_0_s_12, __f2dace_A_tendency_tmp_a_d_1_s_13, __f2dace_A_tendency_tmp_cld_d_0_s_15, __f2dace_A_tendency_tmp_cld_d_1_s_16,
        __f2dace_A_tendency_tmp_cld_d_2_s_17, __f2dace_A_tendency_tmp_q_d_0_s_9, __f2dace_A_tendency_tmp_q_d_1_s_10, __f2dace_A_tendency_tmp_t_d_0_s_6, __f2dace_A_tendency_tmp_t_d_1_s_7,
        __f2dace_OA_ktype_d_1_s_70, __f2dace_OA_ldcum_d_1_s_68, __f2dace_OA_pa_d_2_s_88, __f2dace_OA_pap_d_2_s_61, __f2dace_OA_paph_d_2_s_64, __f2dace_OA_pccn_d_2_s_107, __f2dace_OA_pclv_d_3_s_92,
        __f2dace_OA_pcovptot_d_0_s_111, __f2dace_OA_pcovptot_d_1_s_112, __f2dace_OA_pcovptot_d_2_s_113, __f2dace_OA_pdyna_d_2_s_43, __f2dace_OA_pdyni_d_2_s_49, __f2dace_OA_pdynl_d_2_s_46,
        __f2dace_OA_pfcqlng_d_2_s_124, __f2dace_OA_pfcqnng_d_2_s_127, __f2dace_OA_pfcqrng_d_2_s_136, __f2dace_OA_pfcqsng_d_2_s_139, __f2dace_OA_pfhpsl_d_2_s_154, __f2dace_OA_pfhpsn_d_2_s_157,
        __f2dace_OA_pfplsl_d_2_s_148, __f2dace_OA_pfplsn_d_2_s_151, __f2dace_OA_pfsqif_d_2_s_121, __f2dace_OA_pfsqitur_d_2_s_145, __f2dace_OA_pfsqlf_d_2_s_118, __f2dace_OA_pfsqltur_d_2_s_142,
        __f2dace_OA_pfsqrf_d_2_s_130, __f2dace_OA_pfsqsf_d_2_s_133, __f2dace_OA_phrlw_d_2_s_55, __f2dace_OA_phrsw_d_2_s_52, __f2dace_OA_picrit_aer_d_2_s_101, __f2dace_OA_plcrit_aer_d_2_s_98,
        __f2dace_OA_plsm_d_1_s_66, __f2dace_OA_plu_d_2_s_73, __f2dace_OA_plude_d_2_s_76, __f2dace_OA_pmfd_d_2_s_85, __f2dace_OA_pmfu_d_2_s_82, __f2dace_OA_pnice_d_2_s_110, __f2dace_OA_pq_d_2_s_5,
        __f2dace_OA_prainfrac_toprfz_d_1_s_115, __f2dace_OA_pre_ice_d_2_s_104, __f2dace_OA_psnde_d_2_s_79, __f2dace_OA_psupsat_d_2_s_95, __f2dace_OA_pt_d_2_s_2, __f2dace_OA_pvervel_d_2_s_58,
        __f2dace_OA_pvfa_d_2_s_34, __f2dace_OA_pvfi_d_2_s_40, __f2dace_OA_pvfl_d_2_s_37, __f2dace_OA_tendency_loc_a_d_2_s_27, __f2dace_OA_tendency_loc_cld_d_0_s_28,
        __f2dace_OA_tendency_loc_cld_d_1_s_29, __f2dace_OA_tendency_loc_cld_d_2_s_30, __f2dace_OA_tendency_loc_cld_d_3_s_31, __f2dace_OA_tendency_loc_q_d_2_s_24, __f2dace_OA_tendency_loc_t_d_2_s_21,
        __f2dace_OA_tendency_tmp_a_d_2_s_14, __f2dace_OA_tendency_tmp_cld_d_3_s_18, __f2dace_OA_tendency_tmp_q_d_2_s_11, __f2dace_OA_tendency_tmp_t_d_2_s_8, kfldx, ngptot, ngptotg, nlev, nproma,
        numomp, ptsphy);
}

DACE_EXPORTED cloudsc_driver_state_t* __dace_init_cloudsc_driver(
    int* __restrict__ ktype, int* __restrict__ ldcum, double* __restrict__ pa, double* __restrict__ pap, double* __restrict__ paph, double* __restrict__ pccn, double* __restrict__ pclv,
    double* __restrict__ pcovptot, double* __restrict__ pdyna, double* __restrict__ pdyni, double* __restrict__ pdynl, double* __restrict__ pfcqlng, double* __restrict__ pfcqnng,
    double* __restrict__ pfcqrng, double* __restrict__ pfcqsng, double* __restrict__ pfhpsl, double* __restrict__ pfhpsn, double* __restrict__ pfplsl, double* __restrict__ pfplsn,
    double* __restrict__ pfsqif, double* __restrict__ pfsqitur, double* __restrict__ pfsqlf, double* __restrict__ pfsqltur, double* __restrict__ pfsqrf, double* __restrict__ pfsqsf,
    double* __restrict__ phrlw, double* __restrict__ phrsw, double* __restrict__ picrit_aer, double* __restrict__ plcrit_aer, double* __restrict__ plsm, double* __restrict__ plu,
    double* __restrict__ plude, double* __restrict__ pmfd, double* __restrict__ pmfu, double* __restrict__ pnice, double* __restrict__ pq, double* __restrict__ prainfrac_toprfz,
    double* __restrict__ pre_ice, double* __restrict__ psnde, double* __restrict__ psupsat, double* __restrict__ pt, double* __restrict__ pvervel, double* __restrict__ pvfa, double* __restrict__ pvfi,
    double* __restrict__ pvfl, double* __restrict__ tendency_loc_a, double* __restrict__ tendency_loc_cld, double* __restrict__ tendency_loc_q, double* __restrict__ tendency_loc_t,
    double* __restrict__ tendency_tmp_a, double* __restrict__ tendency_tmp_cld, double* __restrict__ tendency_tmp_q, double* __restrict__ tendency_tmp_t, tecldp* ydecldp, toethf* ydoethf,
    tomcst* ydomcst, int __f2dace_A_ktype_d_0_s_69, int __f2dace_A_ldcum_d_0_s_67, int __f2dace_A_pa_d_0_s_86, int __f2dace_A_pa_d_1_s_87, int __f2dace_A_pap_d_0_s_59, int __f2dace_A_pap_d_1_s_60,
    int __f2dace_A_paph_d_0_s_62, int __f2dace_A_paph_d_1_s_63, int __f2dace_A_pccn_d_0_s_105, int __f2dace_A_pccn_d_1_s_106, int __f2dace_A_pclv_d_0_s_89, int __f2dace_A_pclv_d_1_s_90,
    int __f2dace_A_pclv_d_2_s_91, int __f2dace_A_pcovptot_d_0_s_111, int __f2dace_A_pcovptot_d_1_s_112, int __f2dace_A_pdyna_d_0_s_41, int __f2dace_A_pdyna_d_1_s_42, int __f2dace_A_pdyni_d_0_s_47,
    int __f2dace_A_pdyni_d_1_s_48, int __f2dace_A_pdynl_d_0_s_44, int __f2dace_A_pdynl_d_1_s_45, int __f2dace_A_pfcqlng_d_0_s_122, int __f2dace_A_pfcqlng_d_1_s_123, int __f2dace_A_pfcqnng_d_0_s_125,
    int __f2dace_A_pfcqnng_d_1_s_126, int __f2dace_A_pfcqrng_d_0_s_134, int __f2dace_A_pfcqrng_d_1_s_135, int __f2dace_A_pfcqsng_d_0_s_137, int __f2dace_A_pfcqsng_d_1_s_138,
    int __f2dace_A_pfhpsl_d_0_s_152, int __f2dace_A_pfhpsl_d_1_s_153, int __f2dace_A_pfhpsn_d_0_s_155, int __f2dace_A_pfhpsn_d_1_s_156, int __f2dace_A_pfplsl_d_0_s_146,
    int __f2dace_A_pfplsl_d_1_s_147, int __f2dace_A_pfplsn_d_0_s_149, int __f2dace_A_pfplsn_d_1_s_150, int __f2dace_A_pfsqif_d_0_s_119, int __f2dace_A_pfsqif_d_1_s_120,
    int __f2dace_A_pfsqitur_d_0_s_143, int __f2dace_A_pfsqitur_d_1_s_144, int __f2dace_A_pfsqlf_d_0_s_116, int __f2dace_A_pfsqlf_d_1_s_117, int __f2dace_A_pfsqltur_d_0_s_140,
    int __f2dace_A_pfsqltur_d_1_s_141, int __f2dace_A_pfsqrf_d_0_s_128, int __f2dace_A_pfsqrf_d_1_s_129, int __f2dace_A_pfsqsf_d_0_s_131, int __f2dace_A_pfsqsf_d_1_s_132,
    int __f2dace_A_phrlw_d_0_s_53, int __f2dace_A_phrlw_d_1_s_54, int __f2dace_A_phrsw_d_0_s_50, int __f2dace_A_phrsw_d_1_s_51, int __f2dace_A_picrit_aer_d_0_s_99, int __f2dace_A_picrit_aer_d_1_s_100,
    int __f2dace_A_plcrit_aer_d_0_s_96, int __f2dace_A_plcrit_aer_d_1_s_97, int __f2dace_A_plsm_d_0_s_65, int __f2dace_A_plu_d_0_s_71, int __f2dace_A_plu_d_1_s_72, int __f2dace_A_plude_d_0_s_74,
    int __f2dace_A_plude_d_1_s_75, int __f2dace_A_pmfd_d_0_s_83, int __f2dace_A_pmfd_d_1_s_84, int __f2dace_A_pmfu_d_0_s_80, int __f2dace_A_pmfu_d_1_s_81, int __f2dace_A_pnice_d_0_s_108,
    int __f2dace_A_pnice_d_1_s_109, int __f2dace_A_pq_d_0_s_3, int __f2dace_A_pq_d_1_s_4, int __f2dace_A_prainfrac_toprfz_d_0_s_114, int __f2dace_A_pre_ice_d_0_s_102, int __f2dace_A_pre_ice_d_1_s_103,
    int __f2dace_A_psnde_d_0_s_77, int __f2dace_A_psnde_d_1_s_78, int __f2dace_A_psupsat_d_0_s_93, int __f2dace_A_psupsat_d_1_s_94, int __f2dace_A_pt_d_0_s_0, int __f2dace_A_pt_d_1_s_1,
    int __f2dace_A_pvervel_d_0_s_56, int __f2dace_A_pvervel_d_1_s_57, int __f2dace_A_pvfa_d_0_s_32, int __f2dace_A_pvfa_d_1_s_33, int __f2dace_A_pvfi_d_0_s_38, int __f2dace_A_pvfi_d_1_s_39,
    int __f2dace_A_pvfl_d_0_s_35, int __f2dace_A_pvfl_d_1_s_36, int __f2dace_A_tendency_loc_a_d_0_s_25, int __f2dace_A_tendency_loc_a_d_1_s_26, int __f2dace_A_tendency_loc_cld_d_0_s_28,
    int __f2dace_A_tendency_loc_cld_d_1_s_29, int __f2dace_A_tendency_loc_cld_d_2_s_30, int __f2dace_A_tendency_loc_q_d_0_s_22, int __f2dace_A_tendency_loc_q_d_1_s_23,
    int __f2dace_A_tendency_loc_t_d_0_s_19, int __f2dace_A_tendency_loc_t_d_1_s_20, int __f2dace_A_tendency_tmp_a_d_0_s_12, int __f2dace_A_tendency_tmp_a_d_1_s_13,
    int __f2dace_A_tendency_tmp_cld_d_0_s_15, int __f2dace_A_tendency_tmp_cld_d_1_s_16, int __f2dace_A_tendency_tmp_cld_d_2_s_17, int __f2dace_A_tendency_tmp_q_d_0_s_9,
    int __f2dace_A_tendency_tmp_q_d_1_s_10, int __f2dace_A_tendency_tmp_t_d_0_s_6, int __f2dace_A_tendency_tmp_t_d_1_s_7, int __f2dace_OA_ktype_d_1_s_70, int __f2dace_OA_ldcum_d_1_s_68,
    int __f2dace_OA_pa_d_2_s_88, int __f2dace_OA_pap_d_2_s_61, int __f2dace_OA_paph_d_2_s_64, int __f2dace_OA_pccn_d_2_s_107, int __f2dace_OA_pclv_d_3_s_92, int __f2dace_OA_pcovptot_d_0_s_111,
    int __f2dace_OA_pcovptot_d_1_s_112, int __f2dace_OA_pcovptot_d_2_s_113, int __f2dace_OA_pdyna_d_2_s_43, int __f2dace_OA_pdyni_d_2_s_49, int __f2dace_OA_pdynl_d_2_s_46,
    int __f2dace_OA_pfcqlng_d_2_s_124, int __f2dace_OA_pfcqnng_d_2_s_127, int __f2dace_OA_pfcqrng_d_2_s_136, int __f2dace_OA_pfcqsng_d_2_s_139, int __f2dace_OA_pfhpsl_d_2_s_154,
    int __f2dace_OA_pfhpsn_d_2_s_157, int __f2dace_OA_pfplsl_d_2_s_148, int __f2dace_OA_pfplsn_d_2_s_151, int __f2dace_OA_pfsqif_d_2_s_121, int __f2dace_OA_pfsqitur_d_2_s_145,
    int __f2dace_OA_pfsqlf_d_2_s_118, int __f2dace_OA_pfsqltur_d_2_s_142, int __f2dace_OA_pfsqrf_d_2_s_130, int __f2dace_OA_pfsqsf_d_2_s_133, int __f2dace_OA_phrlw_d_2_s_55,
    int __f2dace_OA_phrsw_d_2_s_52, int __f2dace_OA_picrit_aer_d_2_s_101, int __f2dace_OA_plcrit_aer_d_2_s_98, int __f2dace_OA_plsm_d_1_s_66, int __f2dace_OA_plu_d_2_s_73,
    int __f2dace_OA_plude_d_2_s_76, int __f2dace_OA_pmfd_d_2_s_85, int __f2dace_OA_pmfu_d_2_s_82, int __f2dace_OA_pnice_d_2_s_110, int __f2dace_OA_pq_d_2_s_5,
    int __f2dace_OA_prainfrac_toprfz_d_1_s_115, int __f2dace_OA_pre_ice_d_2_s_104, int __f2dace_OA_psnde_d_2_s_79, int __f2dace_OA_psupsat_d_2_s_95, int __f2dace_OA_pt_d_2_s_2,
    int __f2dace_OA_pvervel_d_2_s_58, int __f2dace_OA_pvfa_d_2_s_34, int __f2dace_OA_pvfi_d_2_s_40, int __f2dace_OA_pvfl_d_2_s_37, int __f2dace_OA_tendency_loc_a_d_2_s_27,
    int __f2dace_OA_tendency_loc_cld_d_0_s_28, int __f2dace_OA_tendency_loc_cld_d_1_s_29, int __f2dace_OA_tendency_loc_cld_d_2_s_30, int __f2dace_OA_tendency_loc_cld_d_3_s_31,
    int __f2dace_OA_tendency_loc_q_d_2_s_24, int __f2dace_OA_tendency_loc_t_d_2_s_21, int __f2dace_OA_tendency_tmp_a_d_2_s_14, int __f2dace_OA_tendency_tmp_cld_d_3_s_18,
    int __f2dace_OA_tendency_tmp_q_d_2_s_11, int __f2dace_OA_tendency_tmp_t_d_2_s_8, int kfldx, int ngptot, int ngptotg, int nlev, int nproma, int numomp, double ptsphy) {
    int __result = 0;
    cloudsc_driver_state_t* __state = new cloudsc_driver_state_t;

    if (__result) {
        delete __state;
        return nullptr;
    }
    return __state;
}

DACE_EXPORTED int __dace_exit_cloudsc_driver(cloudsc_driver_state_t* __state) {
    int __err = 0;
    delete __state;
    return __err;
}
