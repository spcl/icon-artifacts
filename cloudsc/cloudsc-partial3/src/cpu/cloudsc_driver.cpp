/* DaCe AUTO-GENERATED FILE. DO NOT MODIFY */
#include <dace/dace.h>

#include "../../../struct_defs.h"
#include "../../include/hash.h"

struct cloudsc_driver_state_t {
    double* __restrict__ __6_zlcond1;
    double* __restrict__ __6_zlcond2;
    double* __restrict__ __6_zrainaut;
    double* __restrict__ __6_zsnowaut;
    double* __restrict__ __6_zliqcld;
    double* __restrict__ __6_zicecld;
    double* __restrict__ __6_zfokoop;
    double* __restrict__ __6_zfoealfa;
    double* __restrict__ __6_zicenuclei;
    double* __restrict__ __6_zlicld;
    double __6_zacond;
    double* __restrict__ __6_zlfinalsum;
    double* __restrict__ __6_zdqs;
    double* __restrict__ __6_ztold;
    double* __restrict__ __6_zqold;
    double* __restrict__ __6_zdtgdp;
    double* __restrict__ __6_zrdtgdp;
    double* __restrict__ __6_zcovpclr;
    double __6_zpreclr;
    double* __restrict__ __6_zcovptot;
    double* __restrict__ __6_zcovpmax;
    double* __restrict__ __6_zqpretot;
    double __6_zdpevap;
    double __6_zdtforc;
    double __6_zdtdiab;
    double* __restrict__ __6_ztp1;
    double* __restrict__ __6_zldefr;
    double* __restrict__ __6_zldifdt;
    double* __restrict__ __6_zlcust;
    double* __restrict__ __6_zacust;
    double* __restrict__ __6_zmf;
    double* __restrict__ __6_zrho;
    double* __restrict__ __6_zsolab;
    double* __restrict__ __6_zsolac;
    double* __restrict__ __6_zanewm1;
    double* __restrict__ __6_zgdp;
    double* __restrict__ __6_zda;
    double* __restrict__ __6_zli;
    double* __restrict__ __6_za;
    double* __restrict__ __6_zaorig;
    int __6_llo1;
    double* __restrict__ __6_zdp;
    double __6_zalfa;
    double __6_zbeta;
    double __6_zbeta1;
    double __6_zcor;
    double __6_zcdmax;
    double* __restrict__ __6_zmin;
    double __6_zlcondlim;
    double __6_zdenom;
    double __6_zdpmxdt;
    double __6_zdpr;
    double __6_zdtdp;
    double __6_zepsec;
    double __6_zfaci;
    double __6_zfacw;
    double __6_zinew;
    double __6_zmfdn;
    double __6_zqe;
    double __6_zqsat;
    double __6_zqtmst;
    double __6_zrdcp;
    double __6_zrhc;
    double __6_zwtot;
    double __6_zzdl;
    double __6_zzrh;
    double __6_zzzdt;
    double __6_zqadj;
    double __6_zrg_r;
    double __6_zcons1;
    double __6_zcond;
    double __6_zlfinal;
    double __6_zmelt;
    double __6_zevap;
    double __6_zfrz;
    double __6_zvpliq;
    double __6_zvpice;
    double __6_zadd;
    double __6_zbdd;
    double __6_zcvds;
    double __6_zice0;
    double __6_zdepos;
    double* __restrict__ __6_zsupsat;
    double __6_zfall;
    double __6_zre_ice;
    double __6_zrldcp;
    double __6_zqp1env;
    int* __restrict__ __6_iphase;
    int* __restrict__ __6_imelt;
    int* __restrict__ __6_llfall;
    int* __restrict__ __6_llindex1;
    int* __restrict__ __6_llindex3;
    int* __restrict__ __6_iorder;
    double* __restrict__ __6_zliqfrac;
    double* __restrict__ __6_zicefrac;
    double* __restrict__ __6_zqx;
    double* __restrict__ __6_zqx0;
    double* __restrict__ __6_zqxn;
    double* __restrict__ __6_zqxfg;
    double* __restrict__ __6_zqxnm1;
    double* __restrict__ __6_zfluxq;
    double* __restrict__ __6_zpfplsx;
    double* __restrict__ __6_zlneg;
    double* __restrict__ __6_zmeltmax;
    double* __restrict__ __6_zfrzmax;
    double* __restrict__ __6_zicetot;
    double* __restrict__ __6_zqxn2d;
    double* __restrict__ __6_zqsmix;
    double* __restrict__ __6_zqsliq;
    double* __restrict__ __6_zqsice;
    double* __restrict__ __6_zfoeewmt;
    double* __restrict__ __6_zfoeew;
    double* __restrict__ __6_zfoeeliqt;
    double* __restrict__ __6_zdqsicedt;
    double* __restrict__ __6_zdqsmixdt;
    double* __restrict__ __6_zcorqsice;
    double* __restrict__ __6_zcorqsmix;
    double* __restrict__ __6_zevaplimmix;
    double* __restrict__ __6_zsolqa;
    double* __restrict__ __6_zsolqb;
    double* __restrict__ __6_zqlhs;
    double* __restrict__ __6_zvqx;
    double* __restrict__ __6_zratio;
    double* __restrict__ __6_zsinksum;
    double* __restrict__ __6_zfallsink;
    double* __restrict__ __6_zfallsrce;
    double* __restrict__ __6_zconvsrce;
    double* __restrict__ __6_zconvsink;
    double* __restrict__ __6_zpsupsatsrce;
    double __6_zsubsat;
    double __6_ztdmtw0;
    double* __restrict__ __6_zcldtopdist;
    double __6_zinfactor;
    double* __restrict__ __6_zrainacc;
    double* __restrict__ __6_zraincld;
    double* __restrict__ __6_zsnowrime;
    double* __restrict__ __6_zsnowcld;
    double __6_zesatliq;
    double __6_zfallcorr;
    double __6_zlambda;
    double __6_zevap_denom;
    double __6_zcorr2;
    double __6_ztemp;
    int* __restrict__ __6_llrainliq;
    double __6_ztmpa;
    double __6_zepsilon;
    double __6_zcond1;
    double __6_zqp;
    double __6_oka;
    double __6_tmp_call_0;
    double __6_tmp_call_1;
    double __6_tmp_call_2;
    double __6_tmp_call_3;
    double __6_tmp_call_4;
    double __6_tmp_call_5;
    double __6_tmp_call_6;
    double __6_tmp_call_10;
    double __6_tmp_call_9;
    double __6_tmp_call_8;
    double __6_tmp_call_7;
    double __6_tmp_call_12;
    double __6_tmp_call_11;
    double __6_tmp_call_13;
    double __6_tmp_call_14;
    double __6_tmp_call_15;
    double __6_tmp_call_16;
    double __6_tmp_call_17;
    double __6_tmp_call_18;
    double __6_tmp_call_19;
    double __6_tmp_call_20;
    double __6_tmp_call_21;
    double __6_tmp_call_24;
    double __6_tmp_call_25;
    double __6_tmp_call_27;
    double __6_tmp_call_26;
    double __6_tmp_call_28;
    double __6_tmp_call_31;
    double __6_tmp_call_32;
    double __6_tmp_call_33;
    double __6_tmp_call_34;
    double __6_tmp_call_35;
    double __6_tmp_call_36;
    double __6_tmp_call_37;
    double __6_tmp_call_38;
    double __6_tmp_call_40;
    double __6_tmp_call_39;
    double __6_tmp_call_41;
    double __6_tmp_call_42;
    double __6_tmp_call_43;
    double __6_tmp_call_46;
    double __6_tmp_call_47;
    double __6_tmp_call_48;
    double __6_tmp_call_49;
    double __6_tmp_call_53;
    double __6_tmp_call_52;
    double __6_tmp_call_51;
    double __6_tmp_call_50;
    double __6_tmp_call_57;
    double __6_tmp_call_56;
    double __6_tmp_call_55;
    double __6_tmp_call_54;
    double __6_tmp_call_59;
    double __6_tmp_call_58;
    double __6_tmp_call_63;
    double __6_tmp_call_62;
    double __6_tmp_call_61;
    double __6_tmp_call_60;
    double __6_tmp_call_67;
    double __6_tmp_call_66;
    double __6_tmp_call_65;
    double __6_tmp_call_64;
    double __6_tmp_call_69;
    double __6_tmp_call_68;
    double __6_tmp_call_70;
    double __6_tmp_call_71;
    double __6_tmp_call_72;
    double __6_tmp_call_73;
    double __6_tmp_call_74;
    double __6_tmp_call_75;
    double __6_tmp_call_76;
    double __6_tmp_call_77;
    double __6_tmp_call_78;
    double __6_tmp_call_79;
    double __6_tmp_call_80;
    double __6_tmp_call_81;
    double __6_tmp_call_82;
    double __6_tmp_call_83;
    double __6_tmp_call_84;
    double __6_tmp_call_85;
    double __6_tmp_call_86;
    double __6_tmp_call_87;
    double __6_tmp_call_88;
    double __6_tmp_call_89;
    double __6_tmp_call_90;
    double __6_tmp_call_91;
    double __6_tmp_call_92;
    double __6_tmp_call_93;
    double __6_tmp_call_94;
    double __6_tmp_call_95;
    double __6_tmp_call_96;
    double __6_tmp_call_97;
    double __6_tmp_call_98;
    double __6_tmp_call_99;
    double __6_tmp_call_100;
    double __6_tmp_call_101;
    double __6_tmp_call_102;
    double __6_tmp_call_103;
    double __6_tmp_call_104;
    double __6_tmp_call_105;
    double __6_tmp_call_108;
    double __6_tmp_call_112;
    double __6_tmp_call_111;
    double __6_tmp_call_110;
    double __6_tmp_call_109;
    double __6_tmp_call_113;
    double __6_tmp_call_114;
    double __6_tmp_call_115;
    double __6_tmp_call_116;
    double __6_tmp_call_117;
    double __6_tmp_call_118;
    double __6_tmp_call_119;
    double __6_tmp_call_120;
    double __6_tmp_call_121;
    double __6_tmp_call_122;
    double __6_tmp_call_123;
    double __6_tmp_call_124;
    double __6_tmp_call_125;
    double __6_tmp_call_126;
    double __6_tmp_call_127;
    double __6_tmp_call_128;
    double __6_tmp_call_129;
    double __6_tmp_call_130;
    double __6_tmp_call_131;
    double __6_tmp_call_132;
    double __6_tmp_call_133;
    double __6_tmp_call_134;
    double __6_tmp_call_149;
    double __6_tmp_call_150;
    double __6_tmp_call_151;
    double __6_tmp_call_152;
    double __6_tmp_call_154;
    double __6_tmp_call_153;
    double __6_tmp_call_155;
    double __6_tmp_call_156;
    double __6_tmp_call_158;
    double __6_tmp_call_159;
    double __6_tmp_call_160;
    double __6_tmp_call_161;
    double __6_tmp_call_162;
    double __6_tmp_call_163;
    double __6_tmp_call_168;
    double __6_tmp_call_167;
    double __6_tmp_call_166;
    double __6_tmp_call_165;
    double __6_tmp_call_164;
    double __6_tmp_call_169;
    double __6_tmp_call_170;
    double __6_tmp_call_171;
    double __6_tmp_call_172;
    double __6_tmp_call_173;
    double __6_tmp_call_174;
    double __6_tmp_call_175;
    double __6_tmp_call_177;
    double __6_tmp_call_176;
    double __6_tmp_call_178;
    double __6_tmp_call_179;
    double __6_tmp_call_180;
    double __6_tmp_call_181;
    double __6_tmp_call_182;
    double __6_tmp_arg_0;
    double __6_tmp_arg_1;
    double __6_tmp_arg_2;
    double __6_tmp_arg_3;
    double __6_tmp_arg_4;
    double __6_tmp_arg_5;
    double __6_tmp_arg_6;
    double __6_tmp_arg_7;
    double __6_tmp_arg_8;
    double __6_tmp_arg_9;
    double __6_tmp_arg_10;
    double __6_tmp_arg_11;
    double __6_tmp_arg_12;
    double __6_tmp_arg_13;
    double __6_tmp_arg_14;
    double __6_tmp_arg_15;
    double __6_tmp_arg_18;
    double __6_tmp_arg_19;
    double __6_tmp_arg_20;
    double __6_tmp_arg_21;
    double __6_tmp_arg_22;
    double __6_tmp_arg_23;
    double __6_tmp_arg_24;
    double __6_tmp_arg_26;
    double __6_tmp_arg_27;
    double __6_tmp_arg_28;
    double __6_tmp_arg_30;
    double __6_tmp_arg_31;
    double __6_tmp_arg_32;
    double __6_tmp_arg_33;
    double __6_tmp_arg_34;
    double __6_tmp_arg_35;
    double __6_tmp_arg_36;
    double __6_tmp_arg_37;
    double __6_tmp_arg_38;
    double __6_tmp_arg_39;
    double __6_tmp_arg_40;
    double __6_tmp_arg_41;
    double __6_tmp_arg_42;
    double __6_tmp_arg_43;
    double __6_tmp_arg_44;
    double __6_tmp_arg_45;
    double __6_tmp_arg_46;
    double __6_tmp_arg_47;
    double __6_tmp_arg_48;
    double __6_tmp_arg_49;
    double __6_tmp_arg_50;
    double __6_tmp_arg_51;
    double __6_tmp_arg_52;
    double __6_tmp_arg_54;
    double __6_tmp_arg_55;
    double __6_tmp_arg_56;
    double __6_tmp_arg_57;
    double __6_tmp_arg_58;
    double __6_tmp_arg_59;
    double __6_tmp_arg_60;
    double __6_tmp_arg_61;
    double __6_tmp_arg_62;
    double __6_tmp_arg_63;
    double __6_tmp_arg_64;
    double __6_tmp_arg_65;
    double __6_tmp_arg_66;
    double __6_tmp_arg_67;
    double __6_tmp_arg_68;
    double __6_tmp_arg_69;
    double __6_tmp_arg_70;
    double __6_tmp_arg_71;
    double __6_tmp_arg_72;
    double __6_tmp_arg_79;
    double __6_tmp_arg_80;
    double __6_tmp_arg_81;
    double __6_tmp_arg_82;
    double __6_tmp_arg_83;
    double __6_tmp_arg_84;
    double __6_tmp_arg_85;
    double __6_tmp_arg_86;
    double __6_tmp_arg_87;
    double __6_tmp_arg_88;
    double __6_tmp_arg_90;
    double __6_tmp_arg_91;
    double __6_tmp_arg_92;
    double __6_tmp_arg_93;
    double __6_tmp_arg_94;
    double __6_tmp_arg_95;
    double __6_tmp_arg_96;
    double __6_tmp_arg_97;
    double __6_tmp_arg_98;
    double __6_tmp_arg_99;
    double __6_tmp_arg_100;
    double __6_tmp_arg_101;
    double __6_tmp_arg_102;
    double __6_tmp_arg_103;
    double __6_tmp_arg_104;
    double __6_tmp_arg_105;
    double __6__if_cond_1;
    double __6__if_cond_2;
    double __6__if_cond_10;
    double __6__if_cond_11;
    double __6__if_cond_13;
    double __6__if_cond_15;
    int __6__if_cond_16;
    int __6__if_cond_19;
    double __6__if_cond_28;
    double __6__if_cond_30;
    double __6__if_cond_31;
    double __6__if_cond_32;
    int __6__if_cond_34;
    int __6__if_cond_35;
    int __6__if_cond_36;
    int __6__if_cond_37;
    double __6__if_cond_38;
    double __6__if_cond_40;
    double __6__if_cond_41;
    double __6__if_cond_43;
    double __6__if_cond_44;
    double __6__if_cond_45;
    int __6__if_cond_47;
    int __6__if_cond_48;
    double __6__if_cond_59;
    double __6__if_cond_61;
    double __6__if_cond_65;
    double __6__if_cond_66;
    double __6__if_cond_67;
    double __33_tmp_call_23;
    double __33_tmp_call_22;
    double __33__if_cond_5;
    double __49_zgdph_r;
    double __85_tmp_call_138;
    double __85_tmp_call_135;
    double __85_tmp_arg_73;
    double __85_tmp_call_136;
    double __85_tmp_call_137;
    double __85_tmp_call_139;
    double __89__if_cond_57;
    double __89__if_cond_58;
    double __89_tmp_call_140;
    double __89_tmp_arg_76;
    double __89__if_cond_56;
    double __89_tmp_call_148;
    double __89_tmp_call_142;
    double __89_tmp_arg_77;
    double __89_tmp_arg_78;
    double __89_tmp_arg_75;
    double __89_tmp_call_141;
    double __89_tmp_call_144;
    double __89_tmp_call_146;
    double __89_zlcrit;
    double __89_tmp_arg_74;
    double __89_tmp_call_143;
    double __89_zconst;
    double __89_zzco;
    double __89_tmp_call_147;
    double __89_tmp_call_145;
    double __89__if_cond_50;
    int __89__if_cond_52;
    double __112_tmp_call_157;
    double __112_tmp_arg_89;
    double __114_tmp_call_107;
    double __114_zlevap;
    double __114_tmp_call_106;
    double __114_tmp_arg_53;
    double __120_zanew;
    double __120__if_cond_75;
    double __132_zrat;
    double __132_zmax;
    double __148_zexplicit;
    double __153_tmp_arg_29;
    double __153_zaeros;
    double __153_zleros;
    double __153_tmp_call_45;
    double __153_ze;
    double __156__if_cond_9;
    double __156__if_cond_8;
    double __200__if_cond_74;
    double __215_tmp_call_183;
    double __218_zmm;
    double __218_zrr;
    double __219_zzratio;
    double __348_tmp_arg_25;
    double __348_tmp_call_44;
    double __359__if_cond_17;
};

inline void loop_body_2_0_0(cloudsc_driver_state_t* __state, double* __restrict__ pcovptot, int __f2dace_A_pcovptot_d_0_s_111, int __f2dace_A_pcovptot_d_1_s_112) {
    {
        {
            double pcovptot_out_0;

            ///////////////////
            // Tasklet code (T_l178_c178)
            pcovptot_out_0 = 0.0;
            ///////////////////

            pcovptot[0] = pcovptot_out_0;
        }
    }
}

inline void loop_body_1_2_0(cloudsc_driver_state_t* __state, double* __restrict__ pcovptot, int __f2dace_A_pcovptot_d_0_s_111, int __f2dace_A_pcovptot_d_1_s_112, int __f2dace_OA_pcovptot_d_0_s_111) {
    {
        {
            for (auto tmp_parfor_57 = __f2dace_OA_pcovptot_d_0_s_111; tmp_parfor_57 < (__f2dace_A_pcovptot_d_0_s_111 + __f2dace_OA_pcovptot_d_0_s_111); tmp_parfor_57 += 1) {
                loop_body_2_0_0(__state, &pcovptot[((-__f2dace_OA_pcovptot_d_0_s_111) + tmp_parfor_57)], __f2dace_A_pcovptot_d_0_s_111, __f2dace_A_pcovptot_d_1_s_112);
            }
        }
    }
}

inline void loop_body_4_0_0(
    cloudsc_driver_state_t* __state, double* __restrict__ tendency_loc_cld, int __f2dace_A_tendency_loc_cld_d_0_s_28, int __f2dace_A_tendency_loc_cld_d_1_s_29,
    int __f2dace_A_tendency_loc_cld_d_2_s_30) {
    {
        {
            double tendency_loc_cld_out_0;

            ///////////////////
            // Tasklet code (T_l179_c179)
            tendency_loc_cld_out_0 = 0.0;
            ///////////////////

            tendency_loc_cld[0] = tendency_loc_cld_out_0;
        }
    }
}

inline void loop_body_1_2_4(
    cloudsc_driver_state_t* __state, double* __restrict__ tendency_loc_cld, int __f2dace_A_tendency_loc_cld_d_0_s_28, int __f2dace_A_tendency_loc_cld_d_1_s_29,
    int __f2dace_A_tendency_loc_cld_d_2_s_30, int __f2dace_OA_tendency_loc_cld_d_0_s_28) {
    {
        {
            for (auto tmp_parfor_59 = __f2dace_OA_tendency_loc_cld_d_0_s_28; tmp_parfor_59 < (__f2dace_A_tendency_loc_cld_d_0_s_28 + __f2dace_OA_tendency_loc_cld_d_0_s_28); tmp_parfor_59 += 1) {
                loop_body_4_0_0(
                    __state, &tendency_loc_cld[((-__f2dace_OA_tendency_loc_cld_d_0_s_28) + tmp_parfor_59)], __f2dace_A_tendency_loc_cld_d_0_s_28, __f2dace_A_tendency_loc_cld_d_1_s_29,
                    __f2dace_A_tendency_loc_cld_d_2_s_30);
            }
        }
    }
}

inline void loop_body_10_0_0(cloudsc_driver_state_t* __state, double* __restrict__ ptendency_loc_cld, int sym_klev, int sym_klon) {
    {
        {
            double ptendency_loc_cld_out_0;

            ///////////////////
            // Tasklet code (T_l430_c430)
            ptendency_loc_cld_out_0 = 0.0;
            ///////////////////

            ptendency_loc_cld[0] = ptendency_loc_cld_out_0;
        }
    }
}

inline void loop_body_9_0_0(cloudsc_driver_state_t* __state, double* __restrict__ ptendency_loc_cld, int icend, int sym_klev, int sym_klon) {
    {
        {
            for (auto _for_it_4 = 1; _for_it_4 < (icend + 1); _for_it_4 += 1) {
                loop_body_10_0_0(__state, &ptendency_loc_cld[(_for_it_4 - 1)], sym_klev, sym_klon);
            }
        }
    }
}

inline void loop_body_6_2_28(cloudsc_driver_state_t* __state, const int* __restrict__ klev, double* __restrict__ ptendency_loc_cld, int icend, int sym_klev, int sym_klon) {
    {
        {
            for (auto _for_it_3 = 1; _for_it_3 < (sym_klev + 1); _for_it_3 += 1) {
                loop_body_9_0_0(__state, &ptendency_loc_cld[(sym_klon * (_for_it_3 - 1))], icend, sym_klev, sym_klon);
            }
        }
    }
}

inline void loop_body_7_0_0(cloudsc_driver_state_t* __state, double* __restrict__ ptendency_loc_a, double* __restrict__ ptendency_loc_q, double* __restrict__ ptendency_loc_t, int sym_klon) {
    {
        {
            double ptendency_loc_t_out_0;

            ///////////////////
            // Tasklet code (T_l422_c422)
            ptendency_loc_t_out_0 = 0.0;
            ///////////////////

            ptendency_loc_t[0] = ptendency_loc_t_out_0;
        }
        {
            double ptendency_loc_q_out_0;

            ///////////////////
            // Tasklet code (T_l423_c423)
            ptendency_loc_q_out_0 = 0.0;
            ///////////////////

            ptendency_loc_q[0] = ptendency_loc_q_out_0;
        }
        {
            double ptendency_loc_a_out_0;

            ///////////////////
            // Tasklet code (T_l424_c424)
            ptendency_loc_a_out_0 = 0.0;
            ///////////////////

            ptendency_loc_a[0] = ptendency_loc_a_out_0;
        }
    }
}

inline void loop_body_6_2_21(
    cloudsc_driver_state_t* __state, double* __restrict__ ptendency_loc_a, double* __restrict__ ptendency_loc_q, double* __restrict__ ptendency_loc_t, int icend, int sym_klon) {
    {
        {
            for (auto _for_it_1 = 1; _for_it_1 < (icend + 1); _for_it_1 += 1) {
                loop_body_7_0_0(__state, &ptendency_loc_a[(_for_it_1 - 1)], &ptendency_loc_q[(_for_it_1 - 1)], &ptendency_loc_t[(_for_it_1 - 1)], sym_klon);
            }
        }
    }
}

inline void loop_body_6_2_42(cloudsc_driver_state_t* __state, int* __restrict__ llfall) {
    {
        {
            int llfall_out_0;

            ///////////////////
            // Tasklet code (T_l439_c439)
            llfall_out_0 = 0;
            ///////////////////

            llfall[0] = llfall_out_0;
        }
    }
}

inline void loop_body_6_4_0(cloudsc_driver_state_t* __state, double* __restrict__ zvqx, int* __restrict__ llfall) {
    double _if_cond_0;

    _if_cond_0 = (zvqx[0] > 0.0);

    if ((_if_cond_0 == 1)) {
        {
            {
                int llfall_out_0;

                ///////////////////
                // Tasklet code (T_l441_c441)
                llfall_out_0 = 1;
                ///////////////////

                llfall[0] = llfall_out_0;
            }
        }
    }
}

inline void loop_body_13_0_0(
    cloudsc_driver_state_t* __state, double* __restrict__ pa_var_27, double* __restrict__ pq_var_7, double* __restrict__ pt_var_6, double* __restrict__ ptendency_tmp_a,
    double* __restrict__ ptendency_tmp_q, double* __restrict__ ptendency_tmp_t, const double* __restrict__ ptsphy_var_5, double* __restrict__ za, double* __restrict__ zaorig, double* __restrict__ zqx,
    double* __restrict__ zqx0, double* __restrict__ ztp1, int sym_klev, int sym_klon) {
    {
        {
            double pt_var_6_0_in_0 = pt_var_6[0];
            double ptendency_tmp_t_0_in_0 = ptendency_tmp_t[0];
            double ptsphy_var_5_0_in = ptsphy_var_5[0];
            double ztp1_out_0;

            ///////////////////
            // Tasklet code (T_l446_c446)
            ztp1_out_0 = (pt_var_6_0_in_0 + (ptsphy_var_5_0_in * ptendency_tmp_t_0_in_0));
            ///////////////////

            ztp1[0] = ztp1_out_0;
        }
        {
            double pq_var_7_0_in_0 = pq_var_7[0];
            double ptendency_tmp_q_0_in_0 = ptendency_tmp_q[0];
            double ptsphy_var_5_0_in = ptsphy_var_5[0];
            double zqx_out_0;

            ///////////////////
            // Tasklet code (T_l447_c447)
            zqx_out_0 = (pq_var_7_0_in_0 + (ptsphy_var_5_0_in * ptendency_tmp_q_0_in_0));
            ///////////////////

            zqx[0] = zqx_out_0;
        }
        {
            double pq_var_7_0_in_0 = pq_var_7[0];
            double ptendency_tmp_q_0_in_0 = ptendency_tmp_q[0];
            double ptsphy_var_5_0_in = ptsphy_var_5[0];
            double zqx0_out_0;

            ///////////////////
            // Tasklet code (T_l448_c448)
            zqx0_out_0 = (pq_var_7_0_in_0 + (ptsphy_var_5_0_in * ptendency_tmp_q_0_in_0));
            ///////////////////

            zqx0[0] = zqx0_out_0;
        }
        {
            double pa_var_27_0_in_0 = pa_var_27[0];
            double ptendency_tmp_a_0_in_0 = ptendency_tmp_a[0];
            double ptsphy_var_5_0_in = ptsphy_var_5[0];
            double za_out_0;

            ///////////////////
            // Tasklet code (T_l449_c449)
            za_out_0 = (pa_var_27_0_in_0 + (ptsphy_var_5_0_in * ptendency_tmp_a_0_in_0));
            ///////////////////

            za[0] = za_out_0;
        }
        {
            double pa_var_27_0_in_0 = pa_var_27[0];
            double ptendency_tmp_a_0_in_0 = ptendency_tmp_a[0];
            double ptsphy_var_5_0_in = ptsphy_var_5[0];
            double zaorig_out_0;

            ///////////////////
            // Tasklet code (T_l450_c450)
            zaorig_out_0 = (pa_var_27_0_in_0 + (ptsphy_var_5_0_in * ptendency_tmp_a_0_in_0));
            ///////////////////

            zaorig[0] = zaorig_out_0;
        }
    }
}

inline void loop_body_6_3_2(
    cloudsc_driver_state_t* __state, double* __restrict__ pa_var_27, double* __restrict__ pq_var_7, double* __restrict__ pt_var_6, double* __restrict__ ptendency_tmp_a,
    double* __restrict__ ptendency_tmp_q, double* __restrict__ ptendency_tmp_t, const double* __restrict__ ptsphy_var_5, double* __restrict__ za, double* __restrict__ zaorig, double* __restrict__ zqx,
    double* __restrict__ zqx0, double* __restrict__ ztp1, int icend, int sym_klev, int sym_klon) {
    {
        {
            for (auto _for_it_7 = 1; _for_it_7 < (icend + 1); _for_it_7 += 1) {
                loop_body_13_0_0(
                    __state, &pa_var_27[(_for_it_7 - 1)], &pq_var_7[(_for_it_7 - 1)], &pt_var_6[(_for_it_7 - 1)], &ptendency_tmp_a[(_for_it_7 - 1)], &ptendency_tmp_q[(_for_it_7 - 1)],
                    &ptendency_tmp_t[(_for_it_7 - 1)], &ptsphy_var_5[0], &za[(_for_it_7 - 1)], &zaorig[(_for_it_7 - 1)], &zqx[(_for_it_7 - 1)], &zqx0[(_for_it_7 - 1)], &ztp1[(_for_it_7 - 1)],
                    sym_klev, sym_klon);
            }
        }
    }
}

inline void loop_body_16_0_0(
    cloudsc_driver_state_t* __state, double* __restrict__ pclv_var_29, double* __restrict__ ptendency_tmp_cld, const double* __restrict__ ptsphy_var_5, double* __restrict__ zqx,
    double* __restrict__ zqx0, int sym_klev, int sym_klon) {
    {
        {
            double pclv_var_29_0_in_0 = pclv_var_29[0];
            double ptendency_tmp_cld_0_in_0 = ptendency_tmp_cld[0];
            double ptsphy_var_5_0_in = ptsphy_var_5[0];
            double zqx_out_0;

            ///////////////////
            // Tasklet code (T_l456_c456)
            zqx_out_0 = (pclv_var_29_0_in_0 + (ptsphy_var_5_0_in * ptendency_tmp_cld_0_in_0));
            ///////////////////

            zqx[0] = zqx_out_0;
        }
        {
            double pclv_var_29_0_in_0 = pclv_var_29[0];
            double ptendency_tmp_cld_0_in_0 = ptendency_tmp_cld[0];
            double ptsphy_var_5_0_in = ptsphy_var_5[0];
            double zqx0_out_0;

            ///////////////////
            // Tasklet code (T_l457_c457)
            zqx0_out_0 = (pclv_var_29_0_in_0 + (ptsphy_var_5_0_in * ptendency_tmp_cld_0_in_0));
            ///////////////////

            zqx0[0] = zqx0_out_0;
        }
    }
}

inline void loop_body_15_0_0(
    cloudsc_driver_state_t* __state, double* __restrict__ pclv_var_29, double* __restrict__ ptendency_tmp_cld, const double* __restrict__ ptsphy_var_5, double* __restrict__ zqx,
    double* __restrict__ zqx0, int icend, int sym_klev, int sym_klon) {
    {
        {
            for (auto _for_it_10 = 1; _for_it_10 < (icend + 1); _for_it_10 += 1) {
                loop_body_16_0_0(__state, &pclv_var_29[(_for_it_10 - 1)], &ptendency_tmp_cld[(_for_it_10 - 1)], &ptsphy_var_5[0], &zqx[(_for_it_10 - 1)], &zqx0[(_for_it_10 - 1)], sym_klev, sym_klon);
            }
        }
    }
}

inline void loop_body_6_3_18(
    cloudsc_driver_state_t* __state, const int* __restrict__ klev, double* __restrict__ pclv_var_29, double* __restrict__ ptendency_tmp_cld, const double* __restrict__ ptsphy_var_5,
    double* __restrict__ zqx, double* __restrict__ zqx0, int icend, int sym_klev, int sym_klon) {
    {
        {
            for (auto _for_it_9 = 1; _for_it_9 < (sym_klev + 1); _for_it_9 += 1) {
                loop_body_15_0_0(
                    __state, &pclv_var_29[(sym_klon * (_for_it_9 - 1))], &ptendency_tmp_cld[(sym_klon * (_for_it_9 - 1))], &ptsphy_var_5[0], &zqx[(sym_klon * (_for_it_9 - 1))],
                    &zqx0[(sym_klon * (_for_it_9 - 1))], icend, sym_klev, sym_klon);
            }
        }
    }
}

inline void loop_body_19_0_0(cloudsc_driver_state_t* __state, double* __restrict__ zpfplsx, int sym_klev, int sym_klon) {
    {
        {
            double zpfplsx_out_0;

            ///////////////////
            // Tasklet code (T_l461_c461)
            zpfplsx_out_0 = 0.0;
            ///////////////////

            zpfplsx[0] = zpfplsx_out_0;
        }
    }
}

inline void loop_body_18_0_0(cloudsc_driver_state_t* __state, double* __restrict__ zpfplsx, int sym_klev, int sym_klon) {
    {
        {
            for (auto tmp_parfor_1 = 1; tmp_parfor_1 < (sym_klon + 1); tmp_parfor_1 += 1) {
                loop_body_19_0_0(__state, &zpfplsx[(tmp_parfor_1 - 1)], sym_klev, sym_klon);
            }
        }
    }
}

inline void loop_body_6_3_23(cloudsc_driver_state_t* __state, double* __restrict__ zpfplsx, int sym_klev, int sym_klon) {
    {
        {
            for (auto tmp_parfor_2 = 1; tmp_parfor_2 < (sym_klev + 2); tmp_parfor_2 += 1) {
                loop_body_18_0_0(__state, &zpfplsx[(sym_klon * (tmp_parfor_2 - 1))], sym_klev, sym_klon);
            }
        }
    }
}

inline void loop_body_22_0_0(cloudsc_driver_state_t* __state, double* __restrict__ zqxn2d, int sym_klev, int sym_klon) {
    {
        {
            double zqxn2d_out_0;

            ///////////////////
            // Tasklet code (T_l462_c462)
            zqxn2d_out_0 = 0.0;
            ///////////////////

            zqxn2d[0] = zqxn2d_out_0;
        }
    }
}

inline void loop_body_21_0_0(cloudsc_driver_state_t* __state, double* __restrict__ zqxn2d, int sym_klev, int sym_klon) {
    {
        {
            for (auto tmp_parfor_4 = 1; tmp_parfor_4 < (sym_klon + 1); tmp_parfor_4 += 1) {
                loop_body_22_0_0(__state, &zqxn2d[(tmp_parfor_4 - 1)], sym_klev, sym_klon);
            }
        }
    }
}

inline void loop_body_6_3_27(cloudsc_driver_state_t* __state, double* __restrict__ zqxn2d, int sym_klev, int sym_klon) {
    {
        {
            for (auto tmp_parfor_5 = 1; tmp_parfor_5 < (sym_klev + 1); tmp_parfor_5 += 1) {
                loop_body_21_0_0(__state, &zqxn2d[(sym_klon * (tmp_parfor_5 - 1))], sym_klev, sym_klon);
            }
        }
    }
}

inline void loop_body_25_0_0(cloudsc_driver_state_t* __state, double* __restrict__ zlneg, int sym_klev, int sym_klon) {
    {
        {
            double zlneg_out_0;

            ///////////////////
            // Tasklet code (T_l463_c463)
            zlneg_out_0 = 0.0;
            ///////////////////

            zlneg[0] = zlneg_out_0;
        }
    }
}

inline void loop_body_24_0_0(cloudsc_driver_state_t* __state, double* __restrict__ zlneg, int sym_klev, int sym_klon) {
    {
        {
            for (auto tmp_parfor_7 = 1; tmp_parfor_7 < (sym_klon + 1); tmp_parfor_7 += 1) {
                loop_body_25_0_0(__state, &zlneg[(tmp_parfor_7 - 1)], sym_klev, sym_klon);
            }
        }
    }
}

inline void loop_body_6_3_31(cloudsc_driver_state_t* __state, double* __restrict__ zlneg, int sym_klev, int sym_klon) {
    {
        {
            for (auto tmp_parfor_8 = 1; tmp_parfor_8 < (sym_klev + 1); tmp_parfor_8 += 1) {
                loop_body_24_0_0(__state, &zlneg[(sym_klon * (tmp_parfor_8 - 1))], sym_klev, sym_klon);
            }
        }
    }
}

inline void loop_body_6_3_35(cloudsc_driver_state_t* __state, double* __restrict__ prainfrac_toprfz_var_32) {
    {
        {
            double prainfrac_toprfz_var_32_out_0;

            ///////////////////
            // Tasklet code (T_l464_c464)
            prainfrac_toprfz_var_32_out_0 = 0.0;
            ///////////////////

            prainfrac_toprfz_var_32[0] = prainfrac_toprfz_var_32_out_0;
        }
    }
}

inline void loop_body_6_3_39(cloudsc_driver_state_t* __state, int* __restrict__ llrainliq) {
    {
        {
            int llrainliq_out_0;

            ///////////////////
            // Tasklet code (T_l465_c465)
            llrainliq_out_0 = 1;
            ///////////////////

            llrainliq[0] = llrainliq_out_0;
        }
    }
}

inline void loop_body_32_0_0(
    cloudsc_driver_state_t* __state, tecldp* __restrict__ ydecldp_var_47, double* __restrict__ zqx, double* __restrict__ za, double* __restrict__ zicefrac, double* __restrict__ zli,
    double* __restrict__ zliqfrac, int sym_klev, int sym_klon) {
    {
        double* v_ydecldp_var_47_rlmin;
        v_ydecldp_var_47_rlmin = (double*)(&(ydecldp_var_47->rlmin));

        {
            double za_0_in_0 = za[0];
            double tmp_call_23_out;

            ///////////////////
            // Tasklet code (T_l521_c521)
            tmp_call_23_out = min(1.0, za_0_in_0);
            ///////////////////

            __state->__33_tmp_call_23 = tmp_call_23_out;
        }
        {
            double tmp_call_23_0_in = __state->__33_tmp_call_23;
            double tmp_call_22_out;

            ///////////////////
            // Tasklet code (T_l521_c521)
            tmp_call_22_out = max(0.0, tmp_call_23_0_in);
            ///////////////////

            __state->__33_tmp_call_22 = tmp_call_22_out;
        }
        {
            double tmp_call_22_0_in = __state->__33_tmp_call_22;
            double za_out_0;

            ///////////////////
            // Tasklet code (T_l521_c521)
            za_out_0 = tmp_call_22_0_in;
            ///////////////////

            za[0] = za_out_0;
        }
        {
            double zqx_0_in_0 = zqx[0];
            double zqx_1_in_0 = zqx[(sym_klev * sym_klon)];
            double zli_out_0;

            ///////////////////
            // Tasklet code (T_l522_c522)
            zli_out_0 = (zqx_0_in_0 + zqx_1_in_0);
            ///////////////////

            zli[0] = zli_out_0;
        }
        {
            double ydecldp_var_47_0_in_rlmin = v_ydecldp_var_47_rlmin[0];
            double zli_0_in_0 = zli[0];
            double _if_cond_5_out;

            ///////////////////
            // Tasklet code (T_l0_c0)
            _if_cond_5_out = (zli_0_in_0 > ydecldp_var_47_0_in_rlmin);
            ///////////////////

            __state->__33__if_cond_5 = _if_cond_5_out;
        }
    }

    if ((__state->__33__if_cond_5 == 1)) {
        {
            {
                double zli_0_in_0 = zli[0];
                double zqx_0_in_0 = zqx[0];
                double zliqfrac_out_0;

                ///////////////////
                // Tasklet code (T_l524_c524)
                zliqfrac_out_0 = (zqx_0_in_0 / zli_0_in_0);
                ///////////////////

                zliqfrac[0] = zliqfrac_out_0;
            }
            {
                double zliqfrac_0_in_0 = zliqfrac[0];
                double zicefrac_out_0;

                ///////////////////
                // Tasklet code (T_l525_c525)
                zicefrac_out_0 = (1.0 - zliqfrac_0_in_0);
                ///////////////////

                zicefrac[0] = zicefrac_out_0;
            }
        }
    } else if ((!(__state->__33__if_cond_5 == 1))) {
        {
            {
                double zliqfrac_out_0;

                ///////////////////
                // Tasklet code (T_l527_c527)
                zliqfrac_out_0 = 0.0;
                ///////////////////

                zliqfrac[0] = zliqfrac_out_0;
            }
            {
                double zicefrac_out_0;

                ///////////////////
                // Tasklet code (T_l528_c528)
                zicefrac_out_0 = 0.0;
                ///////////////////

                zicefrac[0] = zicefrac_out_0;
            }
        }
    }
}

inline void loop_body_6_5_0(
    cloudsc_driver_state_t* __state, tecldp* __restrict__ ydecldp_var_47, double* __restrict__ zqx, double* __restrict__ za, double* __restrict__ zicefrac, double* __restrict__ zli,
    double* __restrict__ zliqfrac, int icend, int sym_klev, int sym_klon) {
    {
        {
            for (auto _for_it_19 = 1; _for_it_19 < (icend + 1); _for_it_19 += 1) {
                loop_body_32_0_0(
                    __state, ydecldp_var_47, &zqx[(_for_it_19 - 1)], &za[(_for_it_19 - 1)], &zicefrac[(_for_it_19 - 1)], &zli[(_for_it_19 - 1)], &zliqfrac[(_for_it_19 - 1)], sym_klev, sym_klon);
            }
        }
    }
}

inline void loop_body_6_5_13(cloudsc_driver_state_t* __state, double* __restrict__ zanewm1) {
    {
        {
            double zanewm1_out_0;

            ///////////////////
            // Tasklet code (T_l544_c544)
            zanewm1_out_0 = 0.0;
            ///////////////////

            zanewm1[0] = zanewm1_out_0;
        }
    }
}

inline void loop_body_6_5_17(cloudsc_driver_state_t* __state, double* __restrict__ zda) {
    {
        {
            double zda_out_0;

            ///////////////////
            // Tasklet code (T_l545_c545)
            zda_out_0 = 0.0;
            ///////////////////

            zda[0] = zda_out_0;
        }
    }
}

inline void loop_body_6_5_21(cloudsc_driver_state_t* __state, double* __restrict__ zcovpclr) {
    {
        {
            double zcovpclr_out_0;

            ///////////////////
            // Tasklet code (T_l546_c546)
            zcovpclr_out_0 = 0.0;
            ///////////////////

            zcovpclr[0] = zcovpclr_out_0;
        }
    }
}

inline void loop_body_6_5_25(cloudsc_driver_state_t* __state, double* __restrict__ zcovpmax) {
    {
        {
            double zcovpmax_out_0;

            ///////////////////
            // Tasklet code (T_l547_c547)
            zcovpmax_out_0 = 0.0;
            ///////////////////

            zcovpmax[0] = zcovpmax_out_0;
        }
    }
}

inline void loop_body_6_5_29(cloudsc_driver_state_t* __state, double* __restrict__ zcovptot) {
    {
        {
            double zcovptot_out_0;

            ///////////////////
            // Tasklet code (T_l548_c548)
            zcovptot_out_0 = 0.0;
            ///////////////////

            zcovptot[0] = zcovptot_out_0;
        }
    }
}

inline void loop_body_6_5_33(cloudsc_driver_state_t* __state, double* __restrict__ zcldtopdist) {
    {
        {
            double zcldtopdist_out_0;

            ///////////////////
            // Tasklet code (T_l549_c549)
            zcldtopdist_out_0 = 0.0;
            ///////////////////

            zcldtopdist[0] = zcldtopdist_out_0;
        }
    }
}

inline void loop_body_51_0_0(cloudsc_driver_state_t* __state, double* __restrict__ zqx, double* __restrict__ zqxfg, int sym_klev, int sym_klon) {
    {
        {
            double zqx_0_in_0 = zqx[0];
            double zqxfg_out_0;

            ///////////////////
            // Tasklet code (T_l553_c553)
            zqxfg_out_0 = zqx_0_in_0;
            ///////////////////

            zqxfg[0] = zqxfg_out_0;
        }
    }
}

inline void loop_body_50_0_0(cloudsc_driver_state_t* __state, double* __restrict__ zqx, double* __restrict__ zqxfg, int icend, int sym_klev, int sym_klon) {
    {
        {
            for (auto _for_it_25 = 1; _for_it_25 < (icend + 1); _for_it_25 += 1) {
                loop_body_51_0_0(__state, &zqx[(_for_it_25 - 1)], &zqxfg[(_for_it_25 - 1)], sym_klev, sym_klon);
            }
        }
    }
}

inline void loop_body_50_0_5(cloudsc_driver_state_t* __state, double* __restrict__ zlicld) {
    {
        {
            double zlicld_out_0;

            ///////////////////
            // Tasklet code (T_l556_c556)
            zlicld_out_0 = 0.0;
            ///////////////////

            zlicld[0] = zlicld_out_0;
        }
    }
}

inline void loop_body_50_0_9(cloudsc_driver_state_t* __state, double* __restrict__ zrainaut) {
    {
        {
            double zrainaut_out_0;

            ///////////////////
            // Tasklet code (T_l557_c557)
            zrainaut_out_0 = 0.0;
            ///////////////////

            zrainaut[0] = zrainaut_out_0;
        }
    }
}

inline void loop_body_50_0_13(cloudsc_driver_state_t* __state, double* __restrict__ zrainacc) {
    {
        {
            double zrainacc_out_0;

            ///////////////////
            // Tasklet code (T_l558_c558)
            zrainacc_out_0 = 0.0;
            ///////////////////

            zrainacc[0] = zrainacc_out_0;
        }
    }
}

inline void loop_body_50_0_17(cloudsc_driver_state_t* __state, double* __restrict__ zsnowaut) {
    {
        {
            double zsnowaut_out_0;

            ///////////////////
            // Tasklet code (T_l559_c559)
            zsnowaut_out_0 = 0.0;
            ///////////////////

            zsnowaut[0] = zsnowaut_out_0;
        }
    }
}

inline void loop_body_50_0_21(cloudsc_driver_state_t* __state, double* __restrict__ zldefr) {
    {
        {
            double zldefr_out_0;

            ///////////////////
            // Tasklet code (T_l560_c560)
            zldefr_out_0 = 0.0;
            ///////////////////

            zldefr[0] = zldefr_out_0;
        }
    }
}

inline void loop_body_50_0_25(cloudsc_driver_state_t* __state, double* __restrict__ zacust) {
    {
        {
            double zacust_out_0;

            ///////////////////
            // Tasklet code (T_l561_c561)
            zacust_out_0 = 0.0;
            ///////////////////

            zacust[0] = zacust_out_0;
        }
    }
}

inline void loop_body_50_0_29(cloudsc_driver_state_t* __state, double* __restrict__ zqpretot) {
    {
        {
            double zqpretot_out_0;

            ///////////////////
            // Tasklet code (T_l562_c562)
            zqpretot_out_0 = 0.0;
            ///////////////////

            zqpretot[0] = zqpretot_out_0;
        }
    }
}

inline void loop_body_50_0_33(cloudsc_driver_state_t* __state, double* __restrict__ zlfinalsum) {
    {
        {
            double zlfinalsum_out_0;

            ///////////////////
            // Tasklet code (T_l563_c563)
            zlfinalsum_out_0 = 0.0;
            ///////////////////

            zlfinalsum[0] = zlfinalsum_out_0;
        }
    }
}

inline void loop_body_50_0_37(cloudsc_driver_state_t* __state, double* __restrict__ zlcond1) {
    {
        {
            double zlcond1_out_0;

            ///////////////////
            // Tasklet code (T_l564_c564)
            zlcond1_out_0 = 0.0;
            ///////////////////

            zlcond1[0] = zlcond1_out_0;
        }
    }
}

inline void loop_body_50_0_41(cloudsc_driver_state_t* __state, double* __restrict__ zlcond2) {
    {
        {
            double zlcond2_out_0;

            ///////////////////
            // Tasklet code (T_l565_c565)
            zlcond2_out_0 = 0.0;
            ///////////////////

            zlcond2[0] = zlcond2_out_0;
        }
    }
}

inline void loop_body_50_0_45(cloudsc_driver_state_t* __state, double* __restrict__ zsupsat) {
    {
        {
            double zsupsat_out_0;

            ///////////////////
            // Tasklet code (T_l566_c566)
            zsupsat_out_0 = 0.0;
            ///////////////////

            zsupsat[0] = zsupsat_out_0;
        }
    }
}

inline void loop_body_50_0_49(cloudsc_driver_state_t* __state, double* __restrict__ zsolab) {
    {
        {
            double zsolab_out_0;

            ///////////////////
            // Tasklet code (T_l569_c569)
            zsolab_out_0 = 0.0;
            ///////////////////

            zsolab[0] = zsolab_out_0;
        }
    }
}

inline void loop_body_50_0_53(cloudsc_driver_state_t* __state, double* __restrict__ zsolac) {
    {
        {
            double zsolac_out_0;

            ///////////////////
            // Tasklet code (T_l570_c570)
            zsolac_out_0 = 0.0;
            ///////////////////

            zsolac[0] = zsolac_out_0;
        }
    }
}

inline void loop_body_67_0_0(cloudsc_driver_state_t* __state, double* __restrict__ zsolqb, int sym_klon) {
    {
        {
            double zsolqb_out_0;

            ///////////////////
            // Tasklet code (T_l571_c571)
            zsolqb_out_0 = 0.0;
            ///////////////////

            zsolqb[0] = zsolqb_out_0;
        }
    }
}

inline void loop_body_66_0_0(cloudsc_driver_state_t* __state, double* __restrict__ zsolqb, int sym_klon) {
    {
        {
            for (auto tmp_parfor_33 = 1; tmp_parfor_33 < (sym_klon + 1); tmp_parfor_33 += 1) {
                loop_body_67_0_0(__state, &zsolqb[(tmp_parfor_33 - 1)], sym_klon);
            }
        }
    }
}

inline void loop_body_50_0_57(cloudsc_driver_state_t* __state, double* __restrict__ zsolqb, int sym_klon) {
    {
        {
            for (auto tmp_parfor_34 = 1; tmp_parfor_34 < 6; tmp_parfor_34 += 1) {
                loop_body_66_0_0(__state, &zsolqb[(sym_klon * (tmp_parfor_34 - 1))], sym_klon);
            }
        }
    }
}

inline void loop_body_70_0_0(cloudsc_driver_state_t* __state, double* __restrict__ zsolqa, int sym_klon) {
    {
        {
            double zsolqa_out_0;

            ///////////////////
            // Tasklet code (T_l572_c572)
            zsolqa_out_0 = 0.0;
            ///////////////////

            zsolqa[0] = zsolqa_out_0;
        }
    }
}

inline void loop_body_69_0_0(cloudsc_driver_state_t* __state, double* __restrict__ zsolqa, int sym_klon) {
    {
        {
            for (auto tmp_parfor_36 = 1; tmp_parfor_36 < (sym_klon + 1); tmp_parfor_36 += 1) {
                loop_body_70_0_0(__state, &zsolqa[(tmp_parfor_36 - 1)], sym_klon);
            }
        }
    }
}

inline void loop_body_50_0_61(cloudsc_driver_state_t* __state, double* __restrict__ zsolqa, int sym_klon) {
    {
        {
            for (auto tmp_parfor_37 = 1; tmp_parfor_37 < 6; tmp_parfor_37 += 1) {
                loop_body_69_0_0(__state, &zsolqa[(sym_klon * (tmp_parfor_37 - 1))], sym_klon);
            }
        }
    }
}

inline void loop_body_72_0_0(cloudsc_driver_state_t* __state, double* __restrict__ zfallsrce, int sym_klon) {
    {
        {
            double zfallsrce_out_0;

            ///////////////////
            // Tasklet code (T_l573_c573)
            zfallsrce_out_0 = 0.0;
            ///////////////////

            zfallsrce[0] = zfallsrce_out_0;
        }
    }
}

inline void loop_body_50_0_65(cloudsc_driver_state_t* __state, double* __restrict__ zfallsrce, int sym_klon) {
    {
        {
            for (auto tmp_parfor_39 = 1; tmp_parfor_39 < (sym_klon + 1); tmp_parfor_39 += 1) {
                loop_body_72_0_0(__state, &zfallsrce[(tmp_parfor_39 - 1)], sym_klon);
            }
        }
    }
}

inline void loop_body_74_0_0(cloudsc_driver_state_t* __state, double* __restrict__ zfallsink, int sym_klon) {
    {
        {
            double zfallsink_out_0;

            ///////////////////
            // Tasklet code (T_l574_c574)
            zfallsink_out_0 = 0.0;
            ///////////////////

            zfallsink[0] = zfallsink_out_0;
        }
    }
}

inline void loop_body_50_0_69(cloudsc_driver_state_t* __state, double* __restrict__ zfallsink, int sym_klon) {
    {
        {
            for (auto tmp_parfor_41 = 1; tmp_parfor_41 < (sym_klon + 1); tmp_parfor_41 += 1) {
                loop_body_74_0_0(__state, &zfallsink[(tmp_parfor_41 - 1)], sym_klon);
            }
        }
    }
}

inline void loop_body_76_0_0(cloudsc_driver_state_t* __state, double* __restrict__ zconvsrce, int sym_klon) {
    {
        {
            double zconvsrce_out_0;

            ///////////////////
            // Tasklet code (T_l575_c575)
            zconvsrce_out_0 = 0.0;
            ///////////////////

            zconvsrce[0] = zconvsrce_out_0;
        }
    }
}

inline void loop_body_50_0_73(cloudsc_driver_state_t* __state, double* __restrict__ zconvsrce, int sym_klon) {
    {
        {
            for (auto tmp_parfor_43 = 1; tmp_parfor_43 < (sym_klon + 1); tmp_parfor_43 += 1) {
                loop_body_76_0_0(__state, &zconvsrce[(tmp_parfor_43 - 1)], sym_klon);
            }
        }
    }
}

inline void loop_body_78_0_0(cloudsc_driver_state_t* __state, double* __restrict__ zconvsink, int sym_klon) {
    {
        {
            double zconvsink_out_0;

            ///////////////////
            // Tasklet code (T_l576_c576)
            zconvsink_out_0 = 0.0;
            ///////////////////

            zconvsink[0] = zconvsink_out_0;
        }
    }
}

inline void loop_body_50_0_77(cloudsc_driver_state_t* __state, double* __restrict__ zconvsink, int sym_klon) {
    {
        {
            for (auto tmp_parfor_45 = 1; tmp_parfor_45 < (sym_klon + 1); tmp_parfor_45 += 1) {
                loop_body_78_0_0(__state, &zconvsink[(tmp_parfor_45 - 1)], sym_klon);
            }
        }
    }
}

inline void loop_body_80_0_0(cloudsc_driver_state_t* __state, double* __restrict__ zpsupsatsrce, int sym_klon) {
    {
        {
            double zpsupsatsrce_out_0;

            ///////////////////
            // Tasklet code (T_l577_c577)
            zpsupsatsrce_out_0 = 0.0;
            ///////////////////

            zpsupsatsrce[0] = zpsupsatsrce_out_0;
        }
    }
}

inline void loop_body_50_0_81(cloudsc_driver_state_t* __state, double* __restrict__ zpsupsatsrce, int sym_klon) {
    {
        {
            for (auto tmp_parfor_47 = 1; tmp_parfor_47 < (sym_klon + 1); tmp_parfor_47 += 1) {
                loop_body_80_0_0(__state, &zpsupsatsrce[(tmp_parfor_47 - 1)], sym_klon);
            }
        }
    }
}

inline void loop_body_82_0_0(cloudsc_driver_state_t* __state, double* __restrict__ zratio, int sym_klon) {
    {
        {
            double zratio_out_0;

            ///////////////////
            // Tasklet code (T_l578_c578)
            zratio_out_0 = 0.0;
            ///////////////////

            zratio[0] = zratio_out_0;
        }
    }
}

inline void loop_body_50_0_85(cloudsc_driver_state_t* __state, double* __restrict__ zratio, int sym_klon) {
    {
        {
            for (auto tmp_parfor_49 = 1; tmp_parfor_49 < (sym_klon + 1); tmp_parfor_49 += 1) {
                loop_body_82_0_0(__state, &zratio[(tmp_parfor_49 - 1)], sym_klon);
            }
        }
    }
}

inline void loop_body_50_0_89(cloudsc_driver_state_t* __state, double* __restrict__ zicetot) {
    {
        {
            double zicetot_out_0;

            ///////////////////
            // Tasklet code (T_l579_c579)
            zicetot_out_0 = 0.0;
            ///////////////////

            zicetot[0] = zicetot_out_0;
        }
    }
}

inline void loop_body_50_12_0(cloudsc_driver_state_t* __state, tecldp* __restrict__ ydecldp_var_47, double* __restrict__ zqx, double* __restrict__ zsolqa, int sym_klev, int sym_klon) {
    double* v_ydecldp_var_47_rlmin;
    v_ydecldp_var_47_rlmin = (double*)(&(ydecldp_var_47->rlmin));

    {
        {
            double ydecldp_var_47_0_in_rlmin = v_ydecldp_var_47_rlmin[0];
            double zqx_0_in_0 = zqx[0];
            double _if_cond_8_out;

            ///////////////////
            // Tasklet code (T_l0_c0)
            _if_cond_8_out = (zqx_0_in_0 < ydecldp_var_47_0_in_rlmin);
            ///////////////////

            __state->__156__if_cond_8 = _if_cond_8_out;
        }
    }

    if ((__state->__156__if_cond_8 == 1)) {
        {
            {
                double zqx_0_in_0 = zqx[0];
                double zsolqa_out_0;

                ///////////////////
                // Tasklet code (T_l612_c612)
                zsolqa_out_0 = zqx_0_in_0;
                ///////////////////

                zsolqa[(4 * sym_klon)] = zsolqa_out_0;
            }
            {
                double zqx_0_in_0 = zqx[0];
                double zsolqa_out_0;

                ///////////////////
                // Tasklet code (T_l613_c613)
                zsolqa_out_0 = (-zqx_0_in_0);
                ///////////////////

                zsolqa[(20 * sym_klon)] = zsolqa_out_0;
            }
        }
    }

    {
        {
            double ydecldp_var_47_0_in_rlmin = v_ydecldp_var_47_rlmin[0];
            double zqx_0_in_0 = zqx[(sym_klev * sym_klon)];
            double _if_cond_9_out;

            ///////////////////
            // Tasklet code (T_l0_c0)
            _if_cond_9_out = (zqx_0_in_0 < ydecldp_var_47_0_in_rlmin);
            ///////////////////

            __state->__156__if_cond_9 = _if_cond_9_out;
        }
    }

    if ((__state->__156__if_cond_9 == 1)) {
        {
            {
                double zqx_0_in_0 = zqx[(sym_klev * sym_klon)];
                double zsolqa_out_0;

                ///////////////////
                // Tasklet code (T_l616_c616)
                zsolqa_out_0 = zqx_0_in_0;
                ///////////////////

                zsolqa[(9 * sym_klon)] = zsolqa_out_0;
            }
            {
                double zqx_0_in_0 = zqx[(sym_klev * sym_klon)];
                double zsolqa_out_0;

                ///////////////////
                // Tasklet code (T_l617_c617)
                zsolqa_out_0 = (-zqx_0_in_0);
                ///////////////////

                zsolqa[(21 * sym_klon)] = zsolqa_out_0;
            }
        }
    }
}

inline void loop_body_358_0_0(
    cloudsc_driver_state_t* __state, int* __restrict__ ldcum_var_20, double* __restrict__ plu_var_22, double* __restrict__ psnde_var_24, tecldp* __restrict__ ydecldp_var_47,
    double* __restrict__ zdtgdp, double* __restrict__ zfoealfa, double* __restrict__ plude_var_23, double* __restrict__ zconvsrce, double* __restrict__ zsolac, double* __restrict__ zsolqa,
    int sym_klon) {
    int _if_cond_18;
    double zalfaw;

    {
        double* v_ydecldp_var_47_rlmin;
        v_ydecldp_var_47_rlmin = (double*)(&(ydecldp_var_47->rlmin));

        {
            double plude_var_23_0_in_0 = plude_var_23[0];
            double zdtgdp_0_in_0 = zdtgdp[0];
            double plude_var_23_out_0;

            ///////////////////
            // Tasklet code (T_l665_c665)
            plude_var_23_out_0 = (plude_var_23_0_in_0 * zdtgdp_0_in_0);
            ///////////////////

            plude_var_23[0] = plude_var_23_out_0;
        }
        {
            int ldcum_var_20_0_in_0 = ldcum_var_20[0];
            double plu_var_22_0_in_0 = plu_var_22[0];
            double plude_var_23_0_in_0 = plude_var_23[0];
            double ydecldp_var_47_0_in_rlmin = v_ydecldp_var_47_rlmin[0];
            double _if_cond_17_out;

            ///////////////////
            // Tasklet code (T_l0_c0)
            _if_cond_17_out = ((ldcum_var_20_0_in_0 && (plude_var_23_0_in_0 > ydecldp_var_47_0_in_rlmin)) && (plu_var_22_0_in_0 > 1e-14));
            ///////////////////

            __state->__359__if_cond_17 = _if_cond_17_out;
        }
    }

    if ((__state->__359__if_cond_17 == 1)) {
        zalfaw = zfoealfa[0];
        {
            {
                double plu_var_22_0_in_0 = plu_var_22[0];
                double plude_var_23_0_in_0 = plude_var_23[0];
                double zsolac_0_in_0 = zsolac[0];
                double zsolac_out_0;

                ///////////////////
                // Tasklet code (T_l667_c667)
                zsolac_out_0 = (zsolac_0_in_0 + (plude_var_23_0_in_0 / plu_var_22_0_in_0));
                ///////////////////

                zsolac[0] = zsolac_out_0;
            }
            {
                double plude_var_23_0_in_0 = plude_var_23[0];
                double zconvsrce_out_0;

                ///////////////////
                // Tasklet code (T_l669_c669)
                zconvsrce_out_0 = (zalfaw * plude_var_23_0_in_0);
                ///////////////////

                zconvsrce[0] = zconvsrce_out_0;
            }
            {
                double plude_var_23_0_in_0 = plude_var_23[0];
                double zconvsrce_out_0;

                ///////////////////
                // Tasklet code (T_l670_c670)
                zconvsrce_out_0 = ((1.0 - zalfaw) * plude_var_23_0_in_0);
                ///////////////////

                zconvsrce[sym_klon] = zconvsrce_out_0;
            }
            {
                double zconvsrce_0_in_0 = zconvsrce[0];
                double zsolqa_0_in_0 = zsolqa[0];
                double zsolqa_out_0;

                ///////////////////
                // Tasklet code (T_l671_c671)
                zsolqa_out_0 = (zsolqa_0_in_0 + zconvsrce_0_in_0);
                ///////////////////

                zsolqa[0] = zsolqa_out_0;
            }
            {
                double zconvsrce_0_in_0 = zconvsrce[sym_klon];
                double zsolqa_0_in_0 = zsolqa[(6 * sym_klon)];
                double zsolqa_out_0;

                ///////////////////
                // Tasklet code (T_l672_c672)
                zsolqa_out_0 = (zsolqa_0_in_0 + zconvsrce_0_in_0);
                ///////////////////

                zsolqa[(6 * sym_klon)] = zsolqa_out_0;
            }
        }
    } else if ((!(__state->__359__if_cond_17 == 1))) {
        {
            {
                double plude_var_23_out_0;

                ///////////////////
                // Tasklet code (T_l674_c674)
                plude_var_23_out_0 = 0.0;
                ///////////////////

                plude_var_23[0] = plude_var_23_out_0;
            }
        }
    }
    _if_cond_18 = ldcum_var_20[0];

    if ((_if_cond_18 == 1)) {
        {
            {
                double psnde_var_24_0_in_0 = psnde_var_24[0];
                double zdtgdp_0_in_0 = zdtgdp[0];
                double zsolqa_0_in_0 = zsolqa[(18 * sym_klon)];
                double zsolqa_out_0;

                ///////////////////
                // Tasklet code (T_l676_c676)
                zsolqa_out_0 = (zsolqa_0_in_0 + (psnde_var_24_0_in_0 * zdtgdp_0_in_0));
                ///////////////////

                zsolqa[(18 * sym_klon)] = zsolqa_out_0;
            }
        }
    }
}

inline void loop_body_343_2_0(
    cloudsc_driver_state_t* __state, double* __restrict__ pmfd_var_26, double* __restrict__ pmfu_var_25, double* __restrict__ zanewm1, double* __restrict__ zdtgdp, double* __restrict__ zacust,
    double* __restrict__ zmf, int sym_klon) {
    {
        {
            double pmfd_var_26_0_in_0 = pmfd_var_26[0];
            double pmfu_var_25_0_in_0 = pmfu_var_25[0];
            double zdtgdp_0_in_0 = zdtgdp[0];
            double tmp_arg_25_out;

            ///////////////////
            // Tasklet code (T_l681_c681)
            tmp_arg_25_out = ((pmfu_var_25_0_in_0 + pmfd_var_26_0_in_0) * zdtgdp_0_in_0);
            ///////////////////

            __state->__348_tmp_arg_25 = tmp_arg_25_out;
        }
        {
            double tmp_arg_25_0_in = __state->__348_tmp_arg_25;
            double tmp_call_44_out;

            ///////////////////
            // Tasklet code (T_l681_c681)
            tmp_call_44_out = max(0.0, tmp_arg_25_0_in);
            ///////////////////

            __state->__348_tmp_call_44 = tmp_call_44_out;
        }
        {
            double tmp_call_44_0_in = __state->__348_tmp_call_44;
            double zmf_out_0;

            ///////////////////
            // Tasklet code (T_l681_c681)
            zmf_out_0 = tmp_call_44_0_in;
            ///////////////////

            zmf[0] = zmf_out_0;
        }
        {
            double zanewm1_0_in_0 = zanewm1[0];
            double zmf_0_in_0 = zmf[0];
            double zacust_out_0;

            ///////////////////
            // Tasklet code (T_l682_c682)
            zacust_out_0 = (zmf_0_in_0 * zanewm1_0_in_0);
            ///////////////////

            zacust[0] = zacust_out_0;
        }
    }
}

inline void loop_body_351_0_0(cloudsc_driver_state_t* __state, double* __restrict__ zmf, double* __restrict__ zqxnm1, double* __restrict__ zconvsrce, double* __restrict__ zlcust, int sym_klon) {
    {
        {
            double zmf_0_in_0 = zmf[0];
            double zqxnm1_0_in_0 = zqxnm1[0];
            double zlcust_out_0;

            ///////////////////
            // Tasklet code (T_l687_c687)
            zlcust_out_0 = (zmf_0_in_0 * zqxnm1_0_in_0);
            ///////////////////

            zlcust[0] = zlcust_out_0;
        }
        {
            double zconvsrce_0_in_0 = zconvsrce[0];
            double zlcust_0_in_0 = zlcust[0];
            double zconvsrce_out_0;

            ///////////////////
            // Tasklet code (T_l688_c688)
            zconvsrce_out_0 = (zconvsrce_0_in_0 + zlcust_0_in_0);
            ///////////////////

            zconvsrce[0] = zconvsrce_out_0;
        }
    }
}

inline void loop_body_343_2_10(
    cloudsc_driver_state_t* __state, int* __restrict__ iphase, int* __restrict__ llfall, double* __restrict__ zmf, double* __restrict__ zqxnm1, double* __restrict__ zconvsrce,
    double* __restrict__ zlcust, int icend, int sym_klon) {
    int _if_cond_20;

    _if_cond_20 = ((1 - llfall[0]) && (iphase[0] > 0));

    if ((_if_cond_20 == 1)) {
        {
            {
                for (auto _for_it_33 = 1; _for_it_33 < (icend + 1); _for_it_33 += 1) {
                    loop_body_351_0_0(__state, &zmf[(_for_it_33 - 1)], &zqxnm1[(_for_it_33 - 1)], &zconvsrce[(_for_it_33 - 1)], &zlcust[(_for_it_33 - 1)], sym_klon);
                }
            }
        }
    }
}

inline void loop_body_343_1_0(cloudsc_driver_state_t* __state, double* __restrict__ zlfinalsum, double* __restrict__ zacust, double* __restrict__ zsolac) {
    double _if_cond_22;

    _if_cond_22 = (zlfinalsum[0] < 1e-14);

    if ((_if_cond_22 == 1)) {
        {
            {
                double zacust_out_0;

                ///////////////////
                // Tasklet code (T_l711_c711)
                zacust_out_0 = 0.0;
                ///////////////////

                zacust[0] = zacust_out_0;
            }
        }
    }

    {
        {
            double zacust_0_in_0 = zacust[0];
            double zsolac_0_in_0 = zsolac[0];
            double zsolac_out_0;

            ///////////////////
            // Tasklet code (T_l712_c712)
            zsolac_out_0 = (zsolac_0_in_0 + zacust_0_in_0);
            ///////////////////

            zsolac[0] = zsolac_out_0;
        }
    }
}

inline void loop_body_50_11_0(
    cloudsc_driver_state_t* __state, int* __restrict__ ktype_var_21, double* __restrict__ plude_var_23, const double* __restrict__ ptsphy_var_5, tecldp* __restrict__ ydecldp_var_47,
    double* __restrict__ zldifdt, int sym_klon) {
    double _if_cond_24;

    _if_cond_24 = ((ktype_var_21[0] > 0) && (plude_var_23[0] > 1e-14));

    {
        double* v_ydecldp_var_47_rcldiff;
        v_ydecldp_var_47_rcldiff = (double*)(&(ydecldp_var_47->rcldiff));

        {
            double ptsphy_var_5_0_in = ptsphy_var_5[0];
            double ydecldp_var_47_0_in_rcldiff = v_ydecldp_var_47_rcldiff[0];
            double zldifdt_out_0;

            ///////////////////
            // Tasklet code (T_l726_c726)
            zldifdt_out_0 = (ydecldp_var_47_0_in_rcldiff * ptsphy_var_5_0_in);
            ///////////////////

            zldifdt[0] = zldifdt_out_0;
        }
    }

    if ((_if_cond_24 == 1)) {
        {
            double* v_ydecldp_var_47_rcldiff_convi;
            v_ydecldp_var_47_rcldiff_convi = (double*)(&(ydecldp_var_47->rcldiff_convi));

            {
                double ydecldp_var_47_0_in_rcldiff_convi = v_ydecldp_var_47_rcldiff_convi[0];
                double zldifdt_0_in_0 = zldifdt[0];
                double zldifdt_out_0;

                ///////////////////
                // Tasklet code (T_l727_c727)
                zldifdt_out_0 = (ydecldp_var_47_0_in_rcldiff_convi * zldifdt_0_in_0);
                ///////////////////

                zldifdt[0] = zldifdt_out_0;
            }
        }
    }
}

inline void loop_body_50_11_9(
    cloudsc_driver_state_t* __state, double* __restrict__ za, double* __restrict__ zevaplimmix, double* __restrict__ zicefrac, double* __restrict__ zldifdt, double* __restrict__ zli,
    double* __restrict__ zlicld, double* __restrict__ zliqfrac, double* __restrict__ zqsmix, double* __restrict__ zqx, double* __restrict__ zsolac, double* __restrict__ zsolqa, int sym_klev,
    int sym_klon) {
    double _if_cond_25;

    _if_cond_25 = (zli[0] > 1e-14);

    if ((_if_cond_25 == 1)) {
        {
            {
                double zqsmix_0_in_0 = zqsmix[0];
                double zqx_0_in_0 = zqx[0];
                double tmp_arg_29_out;

                ///////////////////
                // Tasklet code (T_l731_c731)
                tmp_arg_29_out = (zqsmix_0_in_0 - zqx_0_in_0);
                ///////////////////

                __state->__153_tmp_arg_29 = tmp_arg_29_out;
            }
            {
                double tmp_arg_29_0_in = __state->__153_tmp_arg_29;
                double tmp_call_45_out;

                ///////////////////
                // Tasklet code (T_l731_c731)
                tmp_call_45_out = max(tmp_arg_29_0_in, 0.0);
                ///////////////////

                __state->__153_tmp_call_45 = tmp_call_45_out;
            }
            {
                double tmp_call_45_0_in = __state->__153_tmp_call_45;
                double zldifdt_0_in_0 = zldifdt[0];
                double ze_out;

                ///////////////////
                // Tasklet code (T_l731_c731)
                ze_out = (zldifdt_0_in_0 * tmp_call_45_0_in);
                ///////////////////

                __state->__153_ze = ze_out;
            }
            {
                double za_0_in_0 = za[0];
                double ze_0_in = __state->__153_ze;
                double zleros_out;

                ///////////////////
                // Tasklet code (T_l732_c732)
                zleros_out = (za_0_in_0 * ze_0_in);
                ///////////////////

                __state->__153_zleros = zleros_out;
            }
            {
                double zevaplimmix_0_in_0 = zevaplimmix[0];
                double zleros_0_in = __state->__153_zleros;
                double zleros_out;

                ///////////////////
                // Tasklet code (T_l733_c733)
                zleros_out = min(zleros_0_in, zevaplimmix_0_in_0);
                ///////////////////

                __state->__153_zleros = zleros_out;
            }
            {
                double zleros_0_in = __state->__153_zleros;
                double zli_0_in_0 = zli[0];
                double zleros_out;

                ///////////////////
                // Tasklet code (T_l734_c734)
                zleros_out = min(zleros_0_in, zli_0_in_0);
                ///////////////////

                __state->__153_zleros = zleros_out;
            }
            {
                double zleros_0_in = __state->__153_zleros;
                double zlicld_0_in_0 = zlicld[0];
                double zaeros_out;

                ///////////////////
                // Tasklet code (T_l735_c735)
                zaeros_out = (zleros_0_in / zlicld_0_in_0);
                ///////////////////

                __state->__153_zaeros = zaeros_out;
            }
            {
                double zaeros_0_in = __state->__153_zaeros;
                double zsolac_0_in_0 = zsolac[0];
                double zsolac_out_0;

                ///////////////////
                // Tasklet code (T_l736_c736)
                zsolac_out_0 = (zsolac_0_in_0 - zaeros_0_in);
                ///////////////////

                zsolac[0] = zsolac_out_0;
            }
            {
                double zleros_0_in = __state->__153_zleros;
                double zliqfrac_0_in_0 = zliqfrac[0];
                double zsolqa_0_in_0 = zsolqa[(4 * sym_klon)];
                double zsolqa_out_0;

                ///////////////////
                // Tasklet code (T_l737_c737)
                zsolqa_out_0 = (zsolqa_0_in_0 + (zliqfrac_0_in_0 * zleros_0_in));
                ///////////////////

                zsolqa[(4 * sym_klon)] = zsolqa_out_0;
            }
            {
                double zleros_0_in = __state->__153_zleros;
                double zliqfrac_0_in_0 = zliqfrac[0];
                double zsolqa_0_in_0 = zsolqa[(20 * sym_klon)];
                double zsolqa_out_0;

                ///////////////////
                // Tasklet code (T_l738_c738)
                zsolqa_out_0 = (zsolqa_0_in_0 - (zliqfrac_0_in_0 * zleros_0_in));
                ///////////////////

                zsolqa[(20 * sym_klon)] = zsolqa_out_0;
            }
            {
                double zicefrac_0_in_0 = zicefrac[0];
                double zleros_0_in = __state->__153_zleros;
                double zsolqa_0_in_0 = zsolqa[(9 * sym_klon)];
                double zsolqa_out_0;

                ///////////////////
                // Tasklet code (T_l739_c739)
                zsolqa_out_0 = (zsolqa_0_in_0 + (zicefrac_0_in_0 * zleros_0_in));
                ///////////////////

                zsolqa[(9 * sym_klon)] = zsolqa_out_0;
            }
            {
                double zicefrac_0_in_0 = zicefrac[0];
                double zleros_0_in = __state->__153_zleros;
                double zsolqa_0_in_0 = zsolqa[(21 * sym_klon)];
                double zsolqa_out_0;

                ///////////////////
                // Tasklet code (T_l740_c740)
                zsolqa_out_0 = (zsolqa_0_in_0 - (zicefrac_0_in_0 * zleros_0_in));
                ///////////////////

                zsolqa[(21 * sym_klon)] = zsolqa_out_0;
            }
        }
    }
}

inline void loop_body_50_3_0(
    cloudsc_driver_state_t* __state, double* __restrict__ zqold, double* __restrict__ ztold, double* __restrict__ zdqs, double* __restrict__ zqsmix, double* __restrict__ ztp1, int sym_klon) {
    {
        {
            double zqold_0_in_0 = zqold[0];
            double zqsmix_0_in_0 = zqsmix[0];
            double zdqs_out_0;

            ///////////////////
            // Tasklet code (T_l783_c783)
            zdqs_out_0 = (zqsmix_0_in_0 - zqold_0_in_0);
            ///////////////////

            zdqs[0] = zdqs_out_0;
        }
    }

    {
        {
            double zqold_0_in_0 = zqold[0];
            double zqsmix_out_0;

            ///////////////////
            // Tasklet code (T_l784_c784)
            zqsmix_out_0 = zqold_0_in_0;
            ///////////////////

            zqsmix[0] = zqsmix_out_0;
        }
        {
            double ztold_0_in_0 = ztold[0];
            double ztp1_out_0;

            ///////////////////
            // Tasklet code (T_l785_c785)
            ztp1_out_0 = ztold_0_in_0;
            ///////////////////

            ztp1[0] = ztp1_out_0;
        }
    }
}

inline void loop_body_50_3_9(
    cloudsc_driver_state_t* __state, double* __restrict__ za, double* __restrict__ zdqs, double* __restrict__ zevaplimmix, double* __restrict__ zicefrac, double* __restrict__ zlicld,
    double* __restrict__ zliqfrac, double* __restrict__ zqsmix, double* __restrict__ zqx, double* __restrict__ zsolqa, int sym_klev, int sym_klon) {
    double _if_cond_27;

    _if_cond_27 = (zdqs[0] > 0.0);

    if ((_if_cond_27 == 1)) {
        {
            {
                double zdqs_0_in_0 = zdqs[0];
                double zlicld_0_in_0 = zlicld[0];
                double tmp_call_106_out;

                ///////////////////
                // Tasklet code (T_l789_c789)
                tmp_call_106_out = min(zdqs_0_in_0, zlicld_0_in_0);
                ///////////////////

                __state->__114_tmp_call_106 = tmp_call_106_out;
            }
            {
                double tmp_call_106_0_in = __state->__114_tmp_call_106;
                double za_0_in_0 = za[0];
                double zlevap_out;

                ///////////////////
                // Tasklet code (T_l789_c789)
                zlevap_out = (za_0_in_0 * tmp_call_106_0_in);
                ///////////////////

                __state->__114_zlevap = zlevap_out;
            }
            {
                double zevaplimmix_0_in_0 = zevaplimmix[0];
                double zlevap_0_in = __state->__114_zlevap;
                double zlevap_out;

                ///////////////////
                // Tasklet code (T_l790_c790)
                zlevap_out = min(zlevap_0_in, zevaplimmix_0_in_0);
                ///////////////////

                __state->__114_zlevap = zlevap_out;
            }
            {
                double zqsmix_0_in_0 = zqsmix[0];
                double zqx_0_in_0 = zqx[0];
                double tmp_arg_53_out;

                ///////////////////
                // Tasklet code (T_l791_c791)
                tmp_arg_53_out = (zqsmix_0_in_0 - zqx_0_in_0);
                ///////////////////

                __state->__114_tmp_arg_53 = tmp_arg_53_out;
            }
            {
                double tmp_arg_53_0_in = __state->__114_tmp_arg_53;
                double tmp_call_107_out;

                ///////////////////
                // Tasklet code (T_l791_c791)
                tmp_call_107_out = max(tmp_arg_53_0_in, 0.0);
                ///////////////////

                __state->__114_tmp_call_107 = tmp_call_107_out;
            }
            {
                double tmp_call_107_0_in = __state->__114_tmp_call_107;
                double zlevap_0_in = __state->__114_zlevap;
                double zlevap_out;

                ///////////////////
                // Tasklet code (T_l791_c791)
                zlevap_out = min(zlevap_0_in, tmp_call_107_0_in);
                ///////////////////

                __state->__114_zlevap = zlevap_out;
            }
            {
                double zlevap_0_in = __state->__114_zlevap;
                double zliqfrac_0_in_0 = zliqfrac[0];
                double zsolqa_0_in_0 = zsolqa[(4 * sym_klon)];
                double zsolqa_out_0;

                ///////////////////
                // Tasklet code (T_l794_c794)
                zsolqa_out_0 = (zsolqa_0_in_0 + (zliqfrac_0_in_0 * zlevap_0_in));
                ///////////////////

                zsolqa[(4 * sym_klon)] = zsolqa_out_0;
            }
            {
                double zlevap_0_in = __state->__114_zlevap;
                double zliqfrac_0_in_0 = zliqfrac[0];
                double zsolqa_0_in_0 = zsolqa[(20 * sym_klon)];
                double zsolqa_out_0;

                ///////////////////
                // Tasklet code (T_l795_c795)
                zsolqa_out_0 = (zsolqa_0_in_0 - (zliqfrac_0_in_0 * zlevap_0_in));
                ///////////////////

                zsolqa[(20 * sym_klon)] = zsolqa_out_0;
            }
            {
                double zicefrac_0_in_0 = zicefrac[0];
                double zlevap_0_in = __state->__114_zlevap;
                double zsolqa_0_in_0 = zsolqa[(9 * sym_klon)];
                double zsolqa_out_0;

                ///////////////////
                // Tasklet code (T_l796_c796)
                zsolqa_out_0 = (zsolqa_0_in_0 + (zicefrac_0_in_0 * zlevap_0_in));
                ///////////////////

                zsolqa[(9 * sym_klon)] = zsolqa_out_0;
            }
            {
                double zicefrac_0_in_0 = zicefrac[0];
                double zlevap_0_in = __state->__114_zlevap;
                double zsolqa_0_in_0 = zsolqa[(21 * sym_klon)];
                double zsolqa_out_0;

                ///////////////////
                // Tasklet code (T_l797_c797)
                zsolqa_out_0 = (zsolqa_0_in_0 - (zicefrac_0_in_0 * zlevap_0_in));
                ///////////////////

                zsolqa[(21 * sym_klon)] = zsolqa_out_0;
            }
        }
    }
}

inline void loop_body_50_1_0(
    cloudsc_driver_state_t* __state, tecldp* __restrict__ ydecldp_var_47, double* __restrict__ za, double* __restrict__ zqpretot, double* __restrict__ zqxfg, double* __restrict__ zcovpclr,
    double* __restrict__ zcovpmax, double* __restrict__ zcovptot, double* __restrict__ zraincld, double* __restrict__ zsnowcld, int _for_it_23, int sym_klon) {
    double _if_cond_49;

    _if_cond_49 = (zqpretot[0] > 1e-14);

    if ((_if_cond_49 == 1)) {
        {
            double* v_ydecldp_var_47_rcovpmin;
            v_ydecldp_var_47_rcovpmin = (double*)(&(ydecldp_var_47->rcovpmin));

            {
                double za_0_in_0 = za[(sym_klon * (_for_it_23 - 2))];
                double tmp_call_136_out;

                ///////////////////
                // Tasklet code (T_l927_c927)
                tmp_call_136_out = min(za_0_in_0, 0.999999);
                ///////////////////

                __state->__85_tmp_call_136 = tmp_call_136_out;
            }
            {
                double za_0_in_0 = za[(sym_klon * (_for_it_23 - 1))];
                double za_1_in_0 = za[(sym_klon * (_for_it_23 - 2))];
                double tmp_call_135_out;

                ///////////////////
                // Tasklet code (T_l927_c927)
                tmp_call_135_out = max(za_0_in_0, za_1_in_0);
                ///////////////////

                __state->__85_tmp_call_135 = tmp_call_135_out;
            }
            {
                double tmp_call_135_0_in = __state->__85_tmp_call_135;
                double tmp_call_136_0_in = __state->__85_tmp_call_136;
                double zcovptot_0_in_0 = zcovptot[0];
                double zcovptot_out_0;

                ///////////////////
                // Tasklet code (T_l927_c927)
                zcovptot_out_0 = (1.0 - (((1.0 - zcovptot_0_in_0) * (1.0 - tmp_call_135_0_in)) / (1.0 - tmp_call_136_0_in)));
                ///////////////////

                zcovptot[0] = zcovptot_out_0;
            }
            {
                double ydecldp_var_47_0_in_rcovpmin = v_ydecldp_var_47_rcovpmin[0];
                double zcovptot_0_in_0 = zcovptot[0];
                double tmp_call_137_out;

                ///////////////////
                // Tasklet code (T_l928_c928)
                tmp_call_137_out = max(zcovptot_0_in_0, ydecldp_var_47_0_in_rcovpmin);
                ///////////////////

                __state->__85_tmp_call_137 = tmp_call_137_out;
            }
            {
                double tmp_call_137_0_in = __state->__85_tmp_call_137;
                double zcovptot_out_0;

                ///////////////////
                // Tasklet code (T_l928_c928)
                zcovptot_out_0 = tmp_call_137_0_in;
                ///////////////////

                zcovptot[0] = zcovptot_out_0;
            }
            {
                double za_0_in_0 = za[(sym_klon * (_for_it_23 - 1))];
                double zcovptot_0_in_0 = zcovptot[0];
                double tmp_arg_73_out;

                ///////////////////
                // Tasklet code (T_l929_c929)
                tmp_arg_73_out = (zcovptot_0_in_0 - za_0_in_0);
                ///////////////////

                __state->__85_tmp_arg_73 = tmp_arg_73_out;
            }
            {
                double tmp_arg_73_0_in = __state->__85_tmp_arg_73;
                double tmp_call_138_out;

                ///////////////////
                // Tasklet code (T_l929_c929)
                tmp_call_138_out = max(0.0, tmp_arg_73_0_in);
                ///////////////////

                __state->__85_tmp_call_138 = tmp_call_138_out;
            }
            {
                double tmp_call_138_0_in = __state->__85_tmp_call_138;
                double zcovpclr_out_0;

                ///////////////////
                // Tasklet code (T_l929_c929)
                zcovpclr_out_0 = tmp_call_138_0_in;
                ///////////////////

                zcovpclr[0] = zcovpclr_out_0;
            }
            {
                double zcovptot_0_in_0 = zcovptot[0];
                double zqxfg_0_in_0 = zqxfg[(2 * sym_klon)];
                double zraincld_out_0;

                ///////////////////
                // Tasklet code (T_l930_c930)
                zraincld_out_0 = (zqxfg_0_in_0 / zcovptot_0_in_0);
                ///////////////////

                zraincld[0] = zraincld_out_0;
            }
            {
                double zcovptot_0_in_0 = zcovptot[0];
                double zqxfg_0_in_0 = zqxfg[(3 * sym_klon)];
                double zsnowcld_out_0;

                ///////////////////
                // Tasklet code (T_l931_c931)
                zsnowcld_out_0 = (zqxfg_0_in_0 / zcovptot_0_in_0);
                ///////////////////

                zsnowcld[0] = zsnowcld_out_0;
            }
            {
                double zcovpmax_0_in_0 = zcovpmax[0];
                double zcovptot_0_in_0 = zcovptot[0];
                double tmp_call_139_out;

                ///////////////////
                // Tasklet code (T_l932_c932)
                tmp_call_139_out = max(zcovptot_0_in_0, zcovpmax_0_in_0);
                ///////////////////

                __state->__85_tmp_call_139 = tmp_call_139_out;
            }
            {
                double tmp_call_139_0_in = __state->__85_tmp_call_139;
                double zcovpmax_out_0;

                ///////////////////
                // Tasklet code (T_l932_c932)
                zcovpmax_out_0 = tmp_call_139_0_in;
                ///////////////////

                zcovpmax[0] = zcovpmax_out_0;
            }
        }
    } else if ((!(_if_cond_49 == 1))) {
        {
            {
                double zraincld_out_0;

                ///////////////////
                // Tasklet code (T_l934_c934)
                zraincld_out_0 = 0.0;
                ///////////////////

                zraincld[0] = zraincld_out_0;
            }
            {
                double zsnowcld_out_0;

                ///////////////////
                // Tasklet code (T_l935_c935)
                zsnowcld_out_0 = 0.0;
                ///////////////////

                zsnowcld[0] = zsnowcld_out_0;
            }
            {
                double zcovptot_out_0;

                ///////////////////
                // Tasklet code (T_l936_c936)
                zcovptot_out_0 = 0.0;
                ///////////////////

                zcovptot[0] = zcovptot_out_0;
            }
            {
                double zcovpclr_out_0;

                ///////////////////
                // Tasklet code (T_l937_c937)
                zcovpclr_out_0 = 0.0;
                ///////////////////

                zcovpclr[0] = zcovpclr_out_0;
            }
            {
                double zcovpmax_out_0;

                ///////////////////
                // Tasklet code (T_l938_c938)
                zcovpmax_out_0 = 0.0;
                ///////////////////

                zcovpmax[0] = zcovpmax_out_0;
            }
        }
    }
}

inline void loop_body_50_1_14(
    cloudsc_driver_state_t* __state, double* __restrict__ picrit_aer_var_1, double* __restrict__ plsm_var_19, double* __restrict__ pnice_var_4, const double* __restrict__ ptsphy_var_5,
    tomcst* __restrict__ ydcst, tecldp* __restrict__ ydecldp_var_47, double* __restrict__ za, double* __restrict__ zicecld, double* __restrict__ zliqcld, double* __restrict__ zqxfg,
    double* __restrict__ zraincld, double* __restrict__ ztp1, double* __restrict__ zrainacc, double* __restrict__ zrainaut, double* __restrict__ zsnowaut, double* __restrict__ zsolqa,
    double* __restrict__ zsolqb, int sym_klon) {
    double* v_ydcst_rtt;
    v_ydcst_rtt = (double*)(&(ydcst->rtt));
    double _if_cond_53;
    bool _if_cond_54;
    bool _if_cond_55;
    bool _if_cond_51;

    {
        {
            double ydcst_0_in_rtt = v_ydcst_rtt[0];
            double ztp1_0_in_0 = ztp1[0];
            double _if_cond_50_out;

            ///////////////////
            // Tasklet code (T_l0_c0)
            _if_cond_50_out = (ztp1_0_in_0 <= ydcst_0_in_rtt);
            ///////////////////

            __state->__89__if_cond_50 = _if_cond_50_out;
        }
    }

    if ((__state->__89__if_cond_50 == 1)) {
        _if_cond_51 = (zicecld[0] > 1e-14);
        if ((_if_cond_51 == 1)) {
            {
                double* v_ydecldp_var_47_rsnowlin2;
                v_ydecldp_var_47_rsnowlin2 = (double*)(&(ydecldp_var_47->rsnowlin2));
                int* v_ydecldp_var_47_laericeauto;
                v_ydecldp_var_47_laericeauto = (int*)(&(ydecldp_var_47->laericeauto));
                double* v_ydecldp_var_47_rsnowlin1;
                v_ydecldp_var_47_rsnowlin1 = (double*)(&(ydecldp_var_47->rsnowlin1));

                {
                    int ydecldp_var_47_0_in_laericeauto = v_ydecldp_var_47_laericeauto[0];
                    int _if_cond_52_out;

                    ///////////////////
                    // Tasklet code (T_l0_c0)
                    _if_cond_52_out = ydecldp_var_47_0_in_laericeauto;
                    ///////////////////

                    __state->__89__if_cond_52 = _if_cond_52_out;
                }
                {
                    double ydcst_0_in_rtt = v_ydcst_rtt[0];
                    double ydecldp_var_47_0_in_rsnowlin2 = v_ydecldp_var_47_rsnowlin2[0];
                    double ztp1_0_in_0 = ztp1[0];
                    double tmp_arg_74_out;

                    ///////////////////
                    // Tasklet code (T_l944_c944)
                    tmp_arg_74_out = (ydecldp_var_47_0_in_rsnowlin2 * (ztp1_0_in_0 - ydcst_0_in_rtt));
                    ///////////////////

                    __state->__89_tmp_arg_74 = tmp_arg_74_out;
                }
                {
                    double tmp_arg_74_0_in = __state->__89_tmp_arg_74;
                    double tmp_call_140_out;

                    ///////////////////
                    // Tasklet code (T_l944_c944)
                    tmp_call_140_out = exp(tmp_arg_74_0_in);
                    ///////////////////

                    __state->__89_tmp_call_140 = tmp_call_140_out;
                }
                {
                    double ptsphy_var_5_0_in = ptsphy_var_5[0];
                    double tmp_call_140_0_in = __state->__89_tmp_call_140;
                    double ydecldp_var_47_0_in_rsnowlin1 = v_ydecldp_var_47_rsnowlin1[0];
                    double zzco_out;

                    ///////////////////
                    // Tasklet code (T_l944_c944)
                    zzco_out = ((ptsphy_var_5_0_in * ydecldp_var_47_0_in_rsnowlin1) * tmp_call_140_0_in);
                    ///////////////////

                    __state->__89_zzco = zzco_out;
                }
            }
            if ((__state->__89__if_cond_52 == 1)) {
                {
                    double* v_ydecldp_var_47_rnice;
                    v_ydecldp_var_47_rnice = (double*)(&(ydecldp_var_47->rnice));

                    {
                        double picrit_aer_var_1_0_in_0 = picrit_aer_var_1[0];
                        double zlcrit_out;

                        ///////////////////
                        // Tasklet code (T_l946_c946)
                        zlcrit_out = picrit_aer_var_1_0_in_0;
                        ///////////////////

                        __state->__89_zlcrit = zlcrit_out;
                    }
                    {
                        double pnice_var_4_0_in_0 = pnice_var_4[0];
                        double ydecldp_var_47_0_in_rnice = v_ydecldp_var_47_rnice[0];
                        double tmp_arg_75_out;

                        ///////////////////
                        // Tasklet code (T_l947_c947)
                        tmp_arg_75_out = (ydecldp_var_47_0_in_rnice / pnice_var_4_0_in_0);
                        ///////////////////

                        __state->__89_tmp_arg_75 = tmp_arg_75_out;
                    }
                    {
                        double tmp_arg_75_0_in = __state->__89_tmp_arg_75;
                        double tmp_call_141_out;

                        ///////////////////
                        // Tasklet code (T_l947_c947)
                        tmp_call_141_out = dace::math::pow(tmp_arg_75_0_in, 0.333);
                        ///////////////////

                        __state->__89_tmp_call_141 = tmp_call_141_out;
                    }
                    {
                        double tmp_call_141_0_in = __state->__89_tmp_call_141;
                        double zzco_0_in = __state->__89_zzco;
                        double zzco_out;

                        ///////////////////
                        // Tasklet code (T_l947_c947)
                        zzco_out = (zzco_0_in * tmp_call_141_0_in);
                        ///////////////////

                        __state->__89_zzco = zzco_out;
                    }
                }
            } else if ((!(__state->__89__if_cond_52 == 1))) {
                {
                    double* v_ydecldp_var_47_rlcritsnow;
                    v_ydecldp_var_47_rlcritsnow = (double*)(&(ydecldp_var_47->rlcritsnow));

                    {
                        double ydecldp_var_47_0_in_rlcritsnow = v_ydecldp_var_47_rlcritsnow[0];
                        double zlcrit_out;

                        ///////////////////
                        // Tasklet code (T_l949_c949)
                        zlcrit_out = ydecldp_var_47_0_in_rlcritsnow;
                        ///////////////////

                        __state->__89_zlcrit = zlcrit_out;
                    }
                }
            }
            {
                {
                    double zicecld_0_in_0 = zicecld[0];
                    double zlcrit_0_in = __state->__89_zlcrit;
                    double tmp_arg_76_out;

                    ///////////////////
                    // Tasklet code (T_l951_c951)
                    tmp_arg_76_out = (zicecld_0_in_0 / zlcrit_0_in);
                    ///////////////////

                    __state->__89_tmp_arg_76 = tmp_arg_76_out;
                }
                {
                    double tmp_arg_76_0_in = __state->__89_tmp_arg_76;
                    double tmp_call_143_out;

                    ///////////////////
                    // Tasklet code (T_l951_c951)
                    tmp_call_143_out = (dace::math::ipow(tmp_arg_76_0_in, 2));
                    ///////////////////

                    __state->__89_tmp_call_143 = tmp_call_143_out;
                }
                {
                    double tmp_call_143_0_in = __state->__89_tmp_call_143;
                    double tmp_arg_77_out;

                    ///////////////////
                    // Tasklet code (T_l951_c951)
                    tmp_arg_77_out = (-tmp_call_143_0_in);
                    ///////////////////

                    __state->__89_tmp_arg_77 = tmp_arg_77_out;
                }
                {
                    double tmp_arg_77_0_in = __state->__89_tmp_arg_77;
                    double tmp_call_142_out;

                    ///////////////////
                    // Tasklet code (T_l951_c951)
                    tmp_call_142_out = exp(tmp_arg_77_0_in);
                    ///////////////////

                    __state->__89_tmp_call_142 = tmp_call_142_out;
                }
                {
                    double tmp_call_142_0_in = __state->__89_tmp_call_142;
                    double zzco_0_in = __state->__89_zzco;
                    double zsnowaut_out_0;

                    ///////////////////
                    // Tasklet code (T_l951_c951)
                    zsnowaut_out_0 = (zzco_0_in * (1.0 - tmp_call_142_0_in));
                    ///////////////////

                    zsnowaut[0] = zsnowaut_out_0;
                }
                {
                    double zsnowaut_0_in_0 = zsnowaut[0];
                    double zsolqb_0_in_0 = zsolqb[0];
                    double zsolqb_out_0;

                    ///////////////////
                    // Tasklet code (T_l952_c952)
                    zsolqb_out_0 = (zsolqb_0_in_0 + zsnowaut_0_in_0);
                    ///////////////////

                    zsolqb[0] = zsolqb_out_0;
                }
            }
        }
    }
    _if_cond_53 = (zliqcld[0] > 1e-14);

    if ((_if_cond_53 == 1)) {
        _if_cond_54 = (plsm_var_19[0] > 0.5);
        if ((_if_cond_54 == 1)) {
            {
                double* v_ydecldp_var_47_rcl_kk_cloud_num_land;
                v_ydecldp_var_47_rcl_kk_cloud_num_land = (double*)(&(ydecldp_var_47->rcl_kk_cloud_num_land));
                double* v_ydecldp_var_47_rclcrit_land;
                v_ydecldp_var_47_rclcrit_land = (double*)(&(ydecldp_var_47->rclcrit_land));

                {
                    double ydecldp_var_47_0_in_rcl_kk_cloud_num_land = v_ydecldp_var_47_rcl_kk_cloud_num_land[0];
                    double zconst_out;

                    ///////////////////
                    // Tasklet code (T_l957_c957)
                    zconst_out = ydecldp_var_47_0_in_rcl_kk_cloud_num_land;
                    ///////////////////

                    __state->__89_zconst = zconst_out;
                }
                {
                    double ydecldp_var_47_0_in_rclcrit_land = v_ydecldp_var_47_rclcrit_land[0];
                    double zlcrit_out;

                    ///////////////////
                    // Tasklet code (T_l958_c958)
                    zlcrit_out = ydecldp_var_47_0_in_rclcrit_land;
                    ///////////////////

                    __state->__89_zlcrit = zlcrit_out;
                }
            }
        } else if ((!(_if_cond_54 == 1))) {
            {
                double* v_ydecldp_var_47_rcl_kk_cloud_num_sea;
                v_ydecldp_var_47_rcl_kk_cloud_num_sea = (double*)(&(ydecldp_var_47->rcl_kk_cloud_num_sea));
                double* v_ydecldp_var_47_rclcrit_sea;
                v_ydecldp_var_47_rclcrit_sea = (double*)(&(ydecldp_var_47->rclcrit_sea));

                {
                    double ydecldp_var_47_0_in_rcl_kk_cloud_num_sea = v_ydecldp_var_47_rcl_kk_cloud_num_sea[0];
                    double zconst_out;

                    ///////////////////
                    // Tasklet code (T_l960_c960)
                    zconst_out = ydecldp_var_47_0_in_rcl_kk_cloud_num_sea;
                    ///////////////////

                    __state->__89_zconst = zconst_out;
                }
                {
                    double ydecldp_var_47_0_in_rclcrit_sea = v_ydecldp_var_47_rclcrit_sea[0];
                    double zlcrit_out;

                    ///////////////////
                    // Tasklet code (T_l961_c961)
                    zlcrit_out = ydecldp_var_47_0_in_rclcrit_sea;
                    ///////////////////

                    __state->__89_zlcrit = zlcrit_out;
                }
            }
        }
        _if_cond_55 = (zliqcld[0] > __state->__89_zlcrit);
        if ((!(_if_cond_55 == 1))) {
            {
                {
                    double zrainaut_out_0;

                    ///////////////////
                    // Tasklet code (T_l971_c971)
                    zrainaut_out_0 = 0.0;
                    ///////////////////

                    zrainaut[0] = zrainaut_out_0;
                }
                {
                    double zrainacc_out_0;

                    ///////////////////
                    // Tasklet code (T_l972_c972)
                    zrainacc_out_0 = 0.0;
                    ///////////////////

                    zrainacc[0] = zrainacc_out_0;
                }
            }
        } else if ((_if_cond_55 == 1)) {
            {
                double* v_ydecldp_var_47_rcl_kkbaun;
                v_ydecldp_var_47_rcl_kkbaun = (double*)(&(ydecldp_var_47->rcl_kkbaun));
                double* v_ydecldp_var_47_rcl_kkaau;
                v_ydecldp_var_47_rcl_kkaau = (double*)(&(ydecldp_var_47->rcl_kkaau));
                double* v_ydecldp_var_47_rcl_kkbauq;
                v_ydecldp_var_47_rcl_kkbauq = (double*)(&(ydecldp_var_47->rcl_kkbauq));

                {
                    double ydecldp_var_47_0_in_rcl_kkbaun = v_ydecldp_var_47_rcl_kkbaun[0];
                    double zconst_0_in = __state->__89_zconst;
                    double tmp_call_145_out;

                    ///////////////////
                    // Tasklet code (T_l964_c964)
                    tmp_call_145_out = dace::math::pow(zconst_0_in, ydecldp_var_47_0_in_rcl_kkbaun);
                    ///////////////////

                    __state->__89_tmp_call_145 = tmp_call_145_out;
                }
                {
                    double ydecldp_var_47_0_in_rcl_kkbauq = v_ydecldp_var_47_rcl_kkbauq[0];
                    double zliqcld_0_in_0 = zliqcld[0];
                    double tmp_call_144_out;

                    ///////////////////
                    // Tasklet code (T_l964_c964)
                    tmp_call_144_out = dace::math::pow(zliqcld_0_in_0, ydecldp_var_47_0_in_rcl_kkbauq);
                    ///////////////////

                    __state->__89_tmp_call_144 = tmp_call_144_out;
                }
                {
                    double ptsphy_var_5_0_in = ptsphy_var_5[0];
                    double tmp_call_144_0_in = __state->__89_tmp_call_144;
                    double tmp_call_145_0_in = __state->__89_tmp_call_145;
                    double ydecldp_var_47_0_in_rcl_kkaau = v_ydecldp_var_47_rcl_kkaau[0];
                    double za_0_in_0 = za[0];
                    double zrainaut_out_0;

                    ///////////////////
                    // Tasklet code (T_l964_c964)
                    zrainaut_out_0 = (((((1.5 * za_0_in_0) * ptsphy_var_5_0_in) * ydecldp_var_47_0_in_rcl_kkaau) * tmp_call_144_0_in) * tmp_call_145_0_in);
                    ///////////////////

                    zrainaut[0] = zrainaut_out_0;
                }
                {
                    double zqxfg_0_in_0 = zqxfg[0];
                    double zrainaut_0_in_0 = zrainaut[0];
                    double tmp_call_146_out;

                    ///////////////////
                    // Tasklet code (T_l965_c965)
                    tmp_call_146_out = min(zrainaut_0_in_0, zqxfg_0_in_0);
                    ///////////////////

                    __state->__89_tmp_call_146 = tmp_call_146_out;
                }
                {
                    double tmp_call_146_0_in = __state->__89_tmp_call_146;
                    double zrainaut_out_0;

                    ///////////////////
                    // Tasklet code (T_l965_c965)
                    zrainaut_out_0 = tmp_call_146_0_in;
                    ///////////////////

                    zrainaut[0] = zrainaut_out_0;
                }
                {
                    double zrainaut_0_in_0 = zrainaut[0];
                    double _if_cond_56_out;

                    ///////////////////
                    // Tasklet code (T_l966_c966)
                    _if_cond_56_out = (zrainaut_0_in_0 < 1e-14);
                    ///////////////////

                    __state->__89__if_cond_56 = _if_cond_56_out;
                }
            }
            if ((__state->__89__if_cond_56 == 1)) {
                {
                    {
                        double zrainaut_out_0;

                        ///////////////////
                        // Tasklet code (T_l966_c966)
                        zrainaut_out_0 = 0.0;
                        ///////////////////

                        zrainaut[0] = zrainaut_out_0;
                    }
                }
            }
            {
                double* v_ydecldp_var_47_rcl_kkbac;
                v_ydecldp_var_47_rcl_kkbac = (double*)(&(ydecldp_var_47->rcl_kkbac));
                double* v_ydecldp_var_47_rcl_kkaac;
                v_ydecldp_var_47_rcl_kkaac = (double*)(&(ydecldp_var_47->rcl_kkaac));

                {
                    double zliqcld_0_in_0 = zliqcld[0];
                    double zraincld_0_in_0 = zraincld[0];
                    double tmp_arg_78_out;

                    ///////////////////
                    // Tasklet code (T_l967_c967)
                    tmp_arg_78_out = (zliqcld_0_in_0 * zraincld_0_in_0);
                    ///////////////////

                    __state->__89_tmp_arg_78 = tmp_arg_78_out;
                }
                {
                    double tmp_arg_78_0_in = __state->__89_tmp_arg_78;
                    double ydecldp_var_47_0_in_rcl_kkbac = v_ydecldp_var_47_rcl_kkbac[0];
                    double tmp_call_147_out;

                    ///////////////////
                    // Tasklet code (T_l967_c967)
                    tmp_call_147_out = dace::math::pow(tmp_arg_78_0_in, ydecldp_var_47_0_in_rcl_kkbac);
                    ///////////////////

                    __state->__89_tmp_call_147 = tmp_call_147_out;
                }
                {
                    double ptsphy_var_5_0_in = ptsphy_var_5[0];
                    double tmp_call_147_0_in = __state->__89_tmp_call_147;
                    double ydecldp_var_47_0_in_rcl_kkaac = v_ydecldp_var_47_rcl_kkaac[0];
                    double za_0_in_0 = za[0];
                    double zrainacc_out_0;

                    ///////////////////
                    // Tasklet code (T_l967_c967)
                    zrainacc_out_0 = ((((2.0 * za_0_in_0) * ptsphy_var_5_0_in) * ydecldp_var_47_0_in_rcl_kkaac) * tmp_call_147_0_in);
                    ///////////////////

                    zrainacc[0] = zrainacc_out_0;
                }
                {
                    double zqxfg_0_in_0 = zqxfg[0];
                    double zrainacc_0_in_0 = zrainacc[0];
                    double tmp_call_148_out;

                    ///////////////////
                    // Tasklet code (T_l968_c968)
                    tmp_call_148_out = min(zrainacc_0_in_0, zqxfg_0_in_0);
                    ///////////////////

                    __state->__89_tmp_call_148 = tmp_call_148_out;
                }
                {
                    double tmp_call_148_0_in = __state->__89_tmp_call_148;
                    double zrainacc_out_0;

                    ///////////////////
                    // Tasklet code (T_l968_c968)
                    zrainacc_out_0 = tmp_call_148_0_in;
                    ///////////////////

                    zrainacc[0] = zrainacc_out_0;
                }
                {
                    double zrainacc_0_in_0 = zrainacc[0];
                    double _if_cond_57_out;

                    ///////////////////
                    // Tasklet code (T_l969_c969)
                    _if_cond_57_out = (zrainacc_0_in_0 < 1e-14);
                    ///////////////////

                    __state->__89__if_cond_57 = _if_cond_57_out;
                }
            }
            if ((__state->__89__if_cond_57 == 1)) {
                {
                    {
                        double zrainacc_out_0;

                        ///////////////////
                        // Tasklet code (T_l969_c969)
                        zrainacc_out_0 = 0.0;
                        ///////////////////

                        zrainacc[0] = zrainacc_out_0;
                    }
                }
            }
        }
        {
            {
                double ydcst_0_in_rtt = v_ydcst_rtt[0];
                double ztp1_0_in_0 = ztp1[0];
                double _if_cond_58_out;

                ///////////////////
                // Tasklet code (T_l0_c0)
                _if_cond_58_out = (ztp1_0_in_0 <= ydcst_0_in_rtt);
                ///////////////////

                __state->__89__if_cond_58 = _if_cond_58_out;
            }
        }
        if ((!(__state->__89__if_cond_58 == 1))) {
            {
                {
                    double zrainaut_0_in_0 = zrainaut[0];
                    double zsolqa_0_in_0 = zsolqa[(2 * sym_klon)];
                    double zsolqa_out_0;

                    ///////////////////
                    // Tasklet code (T_l980_c980)
                    zsolqa_out_0 = (zsolqa_0_in_0 + zrainaut_0_in_0);
                    ///////////////////

                    zsolqa[(2 * sym_klon)] = zsolqa_out_0;
                }
                {
                    double zrainacc_0_in_0 = zrainacc[0];
                    double zsolqa_0_in_0 = zsolqa[(2 * sym_klon)];
                    double zsolqa_out_0;

                    ///////////////////
                    // Tasklet code (T_l981_c981)
                    zsolqa_out_0 = (zsolqa_0_in_0 + zrainacc_0_in_0);
                    ///////////////////

                    zsolqa[(2 * sym_klon)] = zsolqa_out_0;
                }
                {
                    double zrainaut_0_in_0 = zrainaut[0];
                    double zsolqa_0_in_0 = zsolqa[(10 * sym_klon)];
                    double zsolqa_out_0;

                    ///////////////////
                    // Tasklet code (T_l982_c982)
                    zsolqa_out_0 = (zsolqa_0_in_0 - zrainaut_0_in_0);
                    ///////////////////

                    zsolqa[(10 * sym_klon)] = zsolqa_out_0;
                }
                {
                    double zrainacc_0_in_0 = zrainacc[0];
                    double zsolqa_0_in_0 = zsolqa[(10 * sym_klon)];
                    double zsolqa_out_0;

                    ///////////////////
                    // Tasklet code (T_l983_c983)
                    zsolqa_out_0 = (zsolqa_0_in_0 - zrainacc_0_in_0);
                    ///////////////////

                    zsolqa[(10 * sym_klon)] = zsolqa_out_0;
                }
            }
        } else if ((__state->__89__if_cond_58 == 1)) {
            {
                {
                    double zrainaut_0_in_0 = zrainaut[0];
                    double zsolqa_0_in_0 = zsolqa[(3 * sym_klon)];
                    double zsolqa_out_0;

                    ///////////////////
                    // Tasklet code (T_l975_c975)
                    zsolqa_out_0 = (zsolqa_0_in_0 + zrainaut_0_in_0);
                    ///////////////////

                    zsolqa[(3 * sym_klon)] = zsolqa_out_0;
                }
                {
                    double zrainacc_0_in_0 = zrainacc[0];
                    double zsolqa_0_in_0 = zsolqa[(3 * sym_klon)];
                    double zsolqa_out_0;

                    ///////////////////
                    // Tasklet code (T_l976_c976)
                    zsolqa_out_0 = (zsolqa_0_in_0 + zrainacc_0_in_0);
                    ///////////////////

                    zsolqa[(3 * sym_klon)] = zsolqa_out_0;
                }
                {
                    double zrainaut_0_in_0 = zrainaut[0];
                    double zsolqa_0_in_0 = zsolqa[(15 * sym_klon)];
                    double zsolqa_out_0;

                    ///////////////////
                    // Tasklet code (T_l977_c977)
                    zsolqa_out_0 = (zsolqa_0_in_0 - zrainaut_0_in_0);
                    ///////////////////

                    zsolqa[(15 * sym_klon)] = zsolqa_out_0;
                }
                {
                    double zrainacc_0_in_0 = zrainacc[0];
                    double zsolqa_0_in_0 = zsolqa[(15 * sym_klon)];
                    double zsolqa_out_0;

                    ///////////////////
                    // Tasklet code (T_l978_c978)
                    zsolqa_out_0 = (zsolqa_0_in_0 - zrainacc_0_in_0);
                    ///////////////////

                    zsolqa[(15 * sym_klon)] = zsolqa_out_0;
                }
            }
        }
    }
}

inline void loop_body_50_2_0(cloudsc_driver_state_t* __state, tecldp* __restrict__ ydecldp_var_47, const double& zrldcp, double* __restrict__ ztp1, double* __restrict__ zfrzmax, int sym_klon) {
    {
        double* v_ydecldp_var_47_rthomo;
        v_ydecldp_var_47_rthomo = (double*)(&(ydecldp_var_47->rthomo));

        {
            double ydecldp_var_47_0_in_rthomo = v_ydecldp_var_47_rthomo[0];
            double zrldcp_0_in = zrldcp;
            double ztp1_0_in_0 = ztp1[0];
            double tmp_arg_89_out;

            ///////////////////
            // Tasklet code (T_l1052_c1052)
            tmp_arg_89_out = ((ydecldp_var_47_0_in_rthomo - ztp1_0_in_0) * zrldcp_0_in);
            ///////////////////

            __state->__112_tmp_arg_89 = tmp_arg_89_out;
        }
        {
            double tmp_arg_89_0_in = __state->__112_tmp_arg_89;
            double tmp_call_157_out;

            ///////////////////
            // Tasklet code (T_l1052_c1052)
            tmp_call_157_out = max(tmp_arg_89_0_in, 0.0);
            ///////////////////

            __state->__112_tmp_call_157 = tmp_call_157_out;
        }
        {
            double tmp_call_157_0_in = __state->__112_tmp_call_157;
            double zfrzmax_out_0;

            ///////////////////
            // Tasklet code (T_l1052_c1052)
            zfrzmax_out_0 = tmp_call_157_0_in;
            ///////////////////

            zfrzmax[0] = zfrzmax_out_0;
        }
    }
}

inline void loop_body_199_0_0(cloudsc_driver_state_t* __state, tecldp* __restrict__ ydecldp_var_47, double* __restrict__ zqxfg, double* __restrict__ zsolqa, int _for_it_62, int sym_klon) {
    {
        double* v_ydecldp_var_47_rlmin;
        v_ydecldp_var_47_rlmin = (double*)(&(ydecldp_var_47->rlmin));

        {
            double ydecldp_var_47_0_in_rlmin = v_ydecldp_var_47_rlmin[0];
            double zqxfg_0_in_0 = zqxfg[0];
            double _if_cond_74_out;

            ///////////////////
            // Tasklet code (T_l0_c0)
            _if_cond_74_out = (zqxfg_0_in_0 < ydecldp_var_47_0_in_rlmin);
            ///////////////////

            __state->__200__if_cond_74 = _if_cond_74_out;
        }
    }

    if ((__state->__200__if_cond_74 == 1)) {
        {
            {
                double zqxfg_0_in_0 = zqxfg[0];
                double zsolqa_0_in_0 = zsolqa[(((5 * sym_klon) * (_for_it_62 - 1)) + (4 * sym_klon))];
                double zsolqa_out_0;

                ///////////////////
                // Tasklet code (T_l1113_c1113)
                zsolqa_out_0 = (zsolqa_0_in_0 + zqxfg_0_in_0);
                ///////////////////

                zsolqa[(((5 * sym_klon) * (_for_it_62 - 1)) + (4 * sym_klon))] = zsolqa_out_0;
            }
            {
                double zqxfg_0_in_0 = zqxfg[0];
                double zsolqa_0_in_0 = zsolqa[((sym_klon * (_for_it_62 - 1)) + (20 * sym_klon))];
                double zsolqa_out_0;

                ///////////////////
                // Tasklet code (T_l1114_c1114)
                zsolqa_out_0 = (zsolqa_0_in_0 - zqxfg_0_in_0);
                ///////////////////

                zsolqa[((sym_klon * (_for_it_62 - 1)) + (20 * sym_klon))] = zsolqa_out_0;
            }
        }
    }
}

inline void loop_body_50_6_0(
    cloudsc_driver_state_t* __state, tecldp* __restrict__ ydecldp_var_47, double* __restrict__ za, double* __restrict__ zaorig, double* __restrict__ zsolab, double* __restrict__ zsolac,
    double* __restrict__ zanewm1, double* __restrict__ zda, int sym_klon) {
    {
        double* v_ydecldp_var_47_ramin;
        v_ydecldp_var_47_ramin = (double*)(&(ydecldp_var_47->ramin));

        {
            double za_0_in_0 = za[0];
            double zsolab_0_in_0 = zsolab[0];
            double zsolac_0_in_0 = zsolac[0];
            double zanew_out;

            ///////////////////
            // Tasklet code (T_l1120_c1120)
            zanew_out = ((za_0_in_0 + zsolac_0_in_0) / (1.0 + zsolab_0_in_0));
            ///////////////////

            __state->__120_zanew = zanew_out;
        }
        {
            double zanew_0_in = __state->__120_zanew;
            double zanew_out;

            ///////////////////
            // Tasklet code (T_l1121_c1121)
            zanew_out = min(zanew_0_in, 1.0);
            ///////////////////

            __state->__120_zanew = zanew_out;
        }
        {
            double ydecldp_var_47_0_in_ramin = v_ydecldp_var_47_ramin[0];
            double zanew_0_in = __state->__120_zanew;
            double _if_cond_75_out;

            ///////////////////
            // Tasklet code (T_l1122_c1122)
            _if_cond_75_out = (zanew_0_in < ydecldp_var_47_0_in_ramin);
            ///////////////////

            __state->__120__if_cond_75 = _if_cond_75_out;
        }
    }

    if ((__state->__120__if_cond_75 == 1)) {
        {
            {
                double zanew_out;

                ///////////////////
                // Tasklet code (T_l1122_c1122)
                zanew_out = 0.0;
                ///////////////////

                __state->__120_zanew = zanew_out;
            }
        }
    }

    {
        {
            double zanew_0_in = __state->__120_zanew;
            double zaorig_0_in_0 = zaorig[0];
            double zda_out_0;

            ///////////////////
            // Tasklet code (T_l1123_c1123)
            zda_out_0 = (zanew_0_in - zaorig_0_in_0);
            ///////////////////

            zda[0] = zda_out_0;
        }
        {
            double zanew_0_in = __state->__120_zanew;
            double zanewm1_out_0;

            ///////////////////
            // Tasklet code (T_l1124_c1124)
            zanewm1_out_0 = zanew_0_in;
            ///////////////////

            zanewm1[0] = zanewm1_out_0;
        }
    }
}

inline void loop_body_124_0_0(cloudsc_driver_state_t* __state, int* __restrict__ llindex3, int sym_klon) {
    {
        {
            int llindex3_out_0;

            ///////////////////
            // Tasklet code (T_l1129_c1129)
            llindex3_out_0 = 0;
            ///////////////////

            llindex3[0] = llindex3_out_0;
        }
    }
}

inline void loop_body_123_0_0(cloudsc_driver_state_t* __state, int* __restrict__ llindex3, int icend, int sym_klon) {
    {
        {
            for (auto _for_it_67 = 1; _for_it_67 < (icend + 1); _for_it_67 += 1) {
                loop_body_124_0_0(__state, &llindex3[(_for_it_67 - 1)], sym_klon);
            }
        }
    }
}

inline void loop_body_123_0_4(cloudsc_driver_state_t* __state, double* __restrict__ zsinksum, int sym_klon) {
    {
        {
            double zsinksum_out_0;

            ///////////////////
            // Tasklet code (T_l1133_c1133)
            zsinksum_out_0 = 0.0;
            ///////////////////

            zsinksum[0] = zsinksum_out_0;
        }
    }
}

inline void loop_body_50_6_10(cloudsc_driver_state_t* __state, int* __restrict__ llindex3, double* __restrict__ zsinksum, int icend, int sym_klon) {
    {
        {
            for (auto _for_it_66 = 1; _for_it_66 < 6; _for_it_66 += 1) {
                loop_body_123_0_0(__state, &llindex3[(sym_klon * (_for_it_66 - 1))], icend, sym_klon);
            }
        }
        {
            for (auto _for_it_68 = 1; _for_it_68 < (icend + 1); _for_it_68 += 1) {
                loop_body_123_0_4(__state, &zsinksum[(_for_it_68 - 1)], sym_klon);
            }
        }
    }
}

inline void loop_body_129_0_0(cloudsc_driver_state_t* __state, double* __restrict__ zsolqa, double* __restrict__ zsinksum, int sym_klon) {
    {
        {
            double zsinksum_0_in_0 = zsinksum[0];
            double zsolqa_0_in_0 = zsolqa[0];
            double zsinksum_out_0;

            ///////////////////
            // Tasklet code (T_l1139_c1139)
            zsinksum_out_0 = (zsinksum_0_in_0 - zsolqa_0_in_0);
            ///////////////////

            zsinksum[0] = zsinksum_out_0;
        }
    }
}

inline void nested_single_state_body_127_0_5(cloudsc_driver_state_t* __state, double* __restrict__ zsolqa, double* __restrict__ zsinksum, int _for_it_69, int64_t _for_it_71, int sym_klon) {
    int64_t _for_it_70;

    for (_for_it_70 = 1; (_for_it_70 <= 5); _for_it_70 = (_for_it_70 + 1)) {
        {
            loop_body_129_0_0(__state, &zsolqa[(((_for_it_71 + (sym_klon * (_for_it_69 - 1))) + ((5 * sym_klon) * (_for_it_70 - 1))) - 1)], &zsinksum[0], sym_klon);
        }
    }
}

inline void loop_body_50_6_15(cloudsc_driver_state_t* __state, double* __restrict__ zsolqa, double* __restrict__ zsinksum, int _for_it_69, int icend, int sym_klon) {
    {
        {
            for (auto _for_it_71 = 1; _for_it_71 < (icend + 1); _for_it_71 += 1) {
                nested_single_state_body_127_0_5(__state, &zsolqa[0], &zsinksum[(_for_it_71 - 1)], _for_it_69, _for_it_71, sym_klon);
            }
        }
    }
}

inline void loop_body_131_0_0(cloudsc_driver_state_t* __state, const double& zepsec, double* __restrict__ zqx, double* __restrict__ zsinksum, double* __restrict__ zratio, int sym_klev, int sym_klon) {
    {
        {
            double zepsec_0_in = zepsec;
            double zqx_0_in_0 = zqx[0];
            double zmax_out;

            ///////////////////
            // Tasklet code (T_l1145_c1145)
            zmax_out = max(zqx_0_in_0, zepsec_0_in);
            ///////////////////

            __state->__132_zmax = zmax_out;
        }
        {
            double zmax_0_in = __state->__132_zmax;
            double zsinksum_0_in_0 = zsinksum[0];
            double zrat_out;

            ///////////////////
            // Tasklet code (T_l1146_c1146)
            zrat_out = max(zsinksum_0_in_0, zmax_0_in);
            ///////////////////

            __state->__132_zrat = zrat_out;
        }
        {
            double zmax_0_in = __state->__132_zmax;
            double zrat_0_in = __state->__132_zrat;
            double zratio_out_0;

            ///////////////////
            // Tasklet code (T_l1147_c1147)
            zratio_out_0 = (zmax_0_in / zrat_0_in);
            ///////////////////

            zratio[0] = zratio_out_0;
        }
    }
}

inline void loop_body_50_6_20(
    cloudsc_driver_state_t* __state, const double& zepsec, double* __restrict__ zqx, double* __restrict__ zsinksum, double* __restrict__ zratio, int icend, int sym_klev, int sym_klon) {
    {
        {
            for (auto _for_it_73 = 1; _for_it_73 < (icend + 1); _for_it_73 += 1) {
                loop_body_131_0_0(__state, zepsec, &zqx[(_for_it_73 - 1)], &zsinksum[(_for_it_73 - 1)], &zratio[(_for_it_73 - 1)], sym_klev, sym_klon);
            }
        }
    }
}

inline void loop_body_133_0_0(cloudsc_driver_state_t* __state, int* __restrict__ iorder, int sym_klon) {
    {
        {
            int iorder_out_0;

            ///////////////////
            // Tasklet code (T_l1152_c1152)
            iorder_out_0 = -999;
            ///////////////////

            iorder[0] = iorder_out_0;
        }
    }
}

inline void loop_body_50_6_26(cloudsc_driver_state_t* __state, int* __restrict__ iorder, int icend, int sym_klon) {
    {
        {
            for (auto _for_it_75 = 1; _for_it_75 < (icend + 1); _for_it_75 += 1) {
                loop_body_133_0_0(__state, &iorder[(_for_it_75 - 1)], sym_klon);
            }
        }
    }
}

inline void loop_body_135_0_0(cloudsc_driver_state_t* __state, int* __restrict__ llindex1, int sym_klon) {
    {
        {
            int llindex1_out_0;

            ///////////////////
            // Tasklet code (T_l1157_c1157)
            llindex1_out_0 = 1;
            ///////////////////

            llindex1[0] = llindex1_out_0;
        }
    }
}

inline void loop_body_50_6_30(cloudsc_driver_state_t* __state, int* __restrict__ llindex1, int icend, int sym_klon) {
    {
        {
            for (auto _for_it_77 = 1; _for_it_77 < (icend + 1); _for_it_77 += 1) {
                loop_body_135_0_0(__state, &llindex1[(_for_it_77 - 1)], sym_klon);
            }
        }
    }
}

inline void loop_body_223_0_0(cloudsc_driver_state_t* __state, double* __restrict__ zmin) {
    {
        {
            double zmin_out_0;

            ///////////////////
            // Tasklet code (T_l1162_c1162)
            zmin_out_0 = 1e+32;
            ///////////////////

            zmin[0] = zmin_out_0;
        }
    }
}

inline void loop_body_226_0_0(
    cloudsc_driver_state_t* __state, int* __restrict__ llindex1, double* __restrict__ zratio, int* __restrict__ iorder, double* __restrict__ zmin, int _for_it_80, int sym_klon) {
    double _if_cond_76;

    _if_cond_76 = (llindex1[0] && (zratio[0] < zmin[0]));

    if ((_if_cond_76 == 1)) {
        {
            {
                int iorder_out_0;

                ///////////////////
                // Tasklet code (T_l1167_c1167)
                iorder_out_0 = _for_it_80;
                ///////////////////

                iorder[0] = iorder_out_0;
            }
            {
                double zratio_0_in_0 = zratio[0];
                double zmin_out_0;

                ///////////////////
                // Tasklet code (T_l1168_c1168)
                zmin_out_0 = zratio_0_in_0;
                ///////////////////

                zmin[0] = zmin_out_0;
            }
        }
    }
}

inline void nested_single_state_body_223_0_10(
    cloudsc_driver_state_t* __state, int* __restrict__ llindex1, double* __restrict__ zratio, int* __restrict__ iorder, double* __restrict__ zmin, int64_t _for_it_81, int sym_klon) {
    int _for_it_80;

    for (_for_it_80 = 1; (_for_it_80 <= 5); _for_it_80 = (_for_it_80 + 1)) {
        {
            loop_body_226_0_0(
                __state, &llindex1[((_for_it_81 + (sym_klon * (_for_it_80 - 1))) - 1)], &zratio[((_for_it_81 + (sym_klon * (_for_it_80 - 1))) - 1)], &iorder[0], &zmin[0], _for_it_80, sym_klon);
        }
    }
}

inline void loop_body_223_0_11(cloudsc_driver_state_t* __state, int* __restrict__ iorder, int* __restrict__ llindex1, int _for_it_82, int sym_klon) {
    int tmp_index_1666;

    tmp_index_1666 = (iorder[0] - 1);

    {
        {
            int llindex1_out_0;

            ///////////////////
            // Tasklet code (T_l1173_c1173)
            llindex1_out_0 = 0;
            ///////////////////

            llindex1[((_for_it_82 + (sym_klon * tmp_index_1666)) - 1)] = llindex1_out_0;
        }
    }
}

inline void loop_body_137_0_0(cloudsc_driver_state_t* __state, double* __restrict__ zsinksum, int sym_klon) {
    {
        {
            double zsinksum_out_0;

            ///////////////////
            // Tasklet code (T_l1178_c1178)
            zsinksum_out_0 = 0.0;
            ///////////////////

            zsinksum[0] = zsinksum_out_0;
        }
    }
}

inline void loop_body_50_8_0(cloudsc_driver_state_t* __state, double* __restrict__ zsinksum, int icend, int sym_klon) {
    {
        {
            for (auto _for_it_84 = 1; _for_it_84 < (icend + 1); _for_it_84 += 1) {
                loop_body_137_0_0(__state, &zsinksum[(_for_it_84 - 1)], sym_klon);
            }
        }
    }
}

inline void loop_body_215_2_0(cloudsc_driver_state_t* __state, double* __restrict__ zsolqa, int* __restrict__ llindex3, int sym_klon) {
    {
        {
            double zsolqa_0_in_0 = zsolqa[0];
            int llindex3_out_0;

            ///////////////////
            // Tasklet code (T_l1185_c1185)
            llindex3_out_0 = (zsolqa_0_in_0 < 0.0);
            ///////////////////

            llindex3[0] = llindex3_out_0;
        }
    }
}

inline void loop_body_214_0_0(
    cloudsc_driver_state_t* __state, int* __restrict__ iorder, double* __restrict__ zsolqa, int* __restrict__ llindex3, double* __restrict__ zsinksum, int _for_it_86, int sym_klon) {
    int jo;
    int64_t tmp_parfor_0;

    jo = iorder[0];

    {
        {
            for (auto _for_it_87 = 1; _for_it_87 < 6; _for_it_87 += 1) {
                loop_body_215_2_0(
                    __state, &zsolqa[(((_for_it_86 + ((5 * sym_klon) * (_for_it_87 - 1))) + (sym_klon * (jo - 1))) - 1)],
                    &llindex3[(((_for_it_86 + ((5 * sym_klon) * (_for_it_87 - 1))) + (sym_klon * (jo - 1))) - 1)], sym_klon);
            }
        }
        {
            double tmp_call_183_out;

            ///////////////////
            // Tasklet code (T_l1187_c1187)
            tmp_call_183_out = 0;
            ///////////////////

            __state->__215_tmp_call_183 = tmp_call_183_out;
        }
    }

    for (tmp_parfor_0 = 1; (tmp_parfor_0 <= 5); tmp_parfor_0 = (tmp_parfor_0 + 1)) {
        {
            {
                double tmp_call_183_0_in = __state->__215_tmp_call_183;
                double zsolqa_0_in_0 = zsolqa[(((_for_it_86 + (sym_klon * (jo - 1))) + ((5 * sym_klon) * (tmp_parfor_0 - 1))) - 1)];
                double tmp_call_183_out;

                ///////////////////
                // Tasklet code (T_l1187_c1187)
                tmp_call_183_out = (tmp_call_183_0_in + zsolqa_0_in_0);
                ///////////////////

                __state->__215_tmp_call_183 = tmp_call_183_out;
            }
        }
    }

    {
        {
            double tmp_call_183_0_in = __state->__215_tmp_call_183;
            double zsinksum_0_in_0 = zsinksum[((_for_it_86 + (sym_klon * (jo - 1))) - 1)];
            double zsinksum_out_0;

            ///////////////////
            // Tasklet code (T_l1187_c1187)
            zsinksum_out_0 = (zsinksum_0_in_0 - tmp_call_183_0_in);
            ///////////////////

            zsinksum[((_for_it_86 + (sym_klon * (jo - 1))) - 1)] = zsinksum_out_0;
        }
    }
}

inline void loop_body_214_0_8(
    cloudsc_driver_state_t* __state, int* __restrict__ iorder, const double& zepsec, double* __restrict__ zqx, double* __restrict__ zsinksum, double* __restrict__ zratio, int _for_it_23,
    int _for_it_88, int sym_klev, int sym_klon) {
    int jo;

    jo = iorder[0];

    {
        {
            double zepsec_0_in = zepsec;
            double zqx_0_in_0 = zqx[(((_for_it_88 + ((sym_klev * sym_klon) * (jo - 1))) + (sym_klon * (_for_it_23 - 1))) - 1)];
            double zmm_out;

            ///////////////////
            // Tasklet code (T_l1191_c1191)
            zmm_out = max(zqx_0_in_0, zepsec_0_in);
            ///////////////////

            __state->__218_zmm = zmm_out;
        }
        {
            double zmm_0_in = __state->__218_zmm;
            double zsinksum_0_in_0 = zsinksum[((_for_it_88 + (sym_klon * (jo - 1))) - 1)];
            double zrr_out;

            ///////////////////
            // Tasklet code (T_l1192_c1192)
            zrr_out = max(zsinksum_0_in_0, zmm_0_in);
            ///////////////////

            __state->__218_zrr = zrr_out;
        }
        {
            double zmm_0_in = __state->__218_zmm;
            double zrr_0_in = __state->__218_zrr;
            double zratio_out_0;

            ///////////////////
            // Tasklet code (T_l1193_c1193)
            zratio_out_0 = (zmm_0_in / zrr_0_in);
            ///////////////////

            zratio[((_for_it_88 + (sym_klon * (jo - 1))) - 1)] = zratio_out_0;
        }
    }
}

inline void loop_body_214_0_14(
    cloudsc_driver_state_t* __state, int* __restrict__ iorder, int* __restrict__ llindex3, double* __restrict__ zratio, double* __restrict__ zsolqa, int _for_it_89, int sym_klon) {
    int jo;
    int _if_cond_77;
    int64_t _for_it_90;

    jo = iorder[0];

    {
        {
            double zratio_0_in_0 = zratio[((_for_it_89 + (sym_klon * (jo - 1))) - 1)];
            double zzratio_out;

            ///////////////////
            // Tasklet code (T_l1197_c1197)
            zzratio_out = zratio_0_in_0;
            ///////////////////

            __state->__219_zzratio = zzratio_out;
        }
    }

    for (_for_it_90 = 1; (_for_it_90 <= 5); _for_it_90 = (_for_it_90 + 1)) {
        _if_cond_77 = llindex3[(((_for_it_89 + ((5 * sym_klon) * (_for_it_90 - 1))) + (sym_klon * (jo - 1))) - 1)];
        if ((_if_cond_77 == 1)) {
            {
                {
                    double zsolqa_0_in_0 = zsolqa[(((5 * sym_klon) * (_for_it_90 - 1)) + (sym_klon * (jo - 1)))];
                    double zzratio_0_in = __state->__219_zzratio;
                    double zsolqa_out_0;

                    ///////////////////
                    // Tasklet code (T_l1200_c1200)
                    zsolqa_out_0 = (zsolqa_0_in_0 * zzratio_0_in);
                    ///////////////////

                    zsolqa[(((5 * sym_klon) * (_for_it_90 - 1)) + (sym_klon * (jo - 1)))] = zsolqa_out_0;
                }
                {
                    double zsolqa_0_in_0 = zsolqa[((sym_klon * (_for_it_90 - 1)) + ((5 * sym_klon) * (jo - 1)))];
                    double zzratio_0_in = __state->__219_zzratio;
                    double zsolqa_out_0;

                    ///////////////////
                    // Tasklet code (T_l1201_c1201)
                    zsolqa_out_0 = (zsolqa_0_in_0 * zzratio_0_in);
                    ///////////////////

                    zsolqa[((sym_klon * (_for_it_90 - 1)) + ((5 * sym_klon) * (jo - 1)))] = zsolqa_out_0;
                }
            }
        }
    }
}

inline void loop_body_142_0_0(
    cloudsc_driver_state_t* __state, double* __restrict__ zfallsink, double* __restrict__ zsolqb, double* __restrict__ zqlhs, int64_t _for_it_92, int64_t _for_it_93, int sym_klon) {
    int64_t _for_it_94;

    {
        {
            double zfallsink_0_in_0 = zfallsink[0];
            double zqlhs_out_0;

            ///////////////////
            // Tasklet code (T_l1210_c1210)
            zqlhs_out_0 = (1.0 + zfallsink_0_in_0);
            ///////////////////

            zqlhs[0] = zqlhs_out_0;
        }
    }

    for (_for_it_94 = 1; (_for_it_94 <= 5); _for_it_94 = (_for_it_94 + 1)) {
        {
            {
                double zqlhs_0_in_0 = zqlhs[0];
                double zsolqb_0_in_0 = zsolqb[(((_for_it_93 + ((5 * sym_klon) * (_for_it_92 - 1))) + (sym_klon * (_for_it_94 - 1))) - 1)];
                double zqlhs_out_0;

                ///////////////////
                // Tasklet code (T_l1212_c1212)
                zqlhs_out_0 = (zqlhs_0_in_0 + zsolqb_0_in_0);
                ///////////////////

                zqlhs[0] = zqlhs_out_0;
            }
        }
    }
}

inline void loop_body_145_0_0(cloudsc_driver_state_t* __state, double* __restrict__ zsolqb, double* __restrict__ zqlhs, int sym_klon) {
    {
        {
            double zsolqb_0_in_0 = zsolqb[0];
            double zqlhs_out_0;

            ///////////////////
            // Tasklet code (T_l1217_c1217)
            zqlhs_out_0 = (-zsolqb_0_in_0);
            ///////////////////

            zqlhs[0] = zqlhs_out_0;
        }
    }
}

inline void loop_body_139_0_0(
    cloudsc_driver_state_t* __state, double* __restrict__ zfallsink, double* __restrict__ zsolqb, double* __restrict__ zqlhs, int _for_it_91, int64_t _for_it_92, int icend, int sym_klon) {
    if (((_for_it_92 == _for_it_91) == 1)) {
        {
            {
                for (auto _for_it_93 = 1; _for_it_93 < (icend + 1); _for_it_93 += 1) {
                    loop_body_142_0_0(__state, &zfallsink[(_for_it_93 - 1)], &zsolqb[0], &zqlhs[(_for_it_93 - 1)], _for_it_92, _for_it_93, sym_klon);
                }
            }
        }
    } else if ((!((_for_it_92 == _for_it_91) == 1))) {
        {
            {
                for (auto _for_it_95 = 1; _for_it_95 < (icend + 1); _for_it_95 += 1) {
                    loop_body_145_0_0(__state, &zsolqb[(((_for_it_95 + ((5 * sym_klon) * (_for_it_91 - 1))) + (sym_klon * (_for_it_92 - 1))) - 1)], &zqlhs[(_for_it_95 - 1)], sym_klon);
                }
            }
        }
    }
}

inline void loop_body_50_9_0(cloudsc_driver_state_t* __state, double* __restrict__ zfallsink, double* __restrict__ zsolqb, double* __restrict__ zqlhs, int _for_it_91, int icend, int sym_klon) {
    {
        {
            for (auto _for_it_92 = 1; _for_it_92 < 6; _for_it_92 += 1) {
                loop_body_139_0_0(__state, &zfallsink[0], &zsolqb[0], &zqlhs[(sym_klon * (_for_it_92 - 1))], _for_it_91, _for_it_92, icend, sym_klon);
            }
        }
    }
}

inline void loop_body_147_0_0(
    cloudsc_driver_state_t* __state, double* __restrict__ zqx, double* __restrict__ zsolqa, double* __restrict__ zqxn, int _for_it_96, int64_t _for_it_97, int sym_klev, int sym_klon) {
    int64_t _for_it_98;

    {
        {
            double zexplicit_out;

            ///////////////////
            // Tasklet code (T_l1224_c1224)
            zexplicit_out = 0.0;
            ///////////////////

            __state->__148_zexplicit = zexplicit_out;
        }
    }

    for (_for_it_98 = 1; (_for_it_98 <= 5); _for_it_98 = (_for_it_98 + 1)) {
        {
            {
                double zexplicit_0_in = __state->__148_zexplicit;
                double zsolqa_0_in_0 = zsolqa[(((_for_it_97 + (sym_klon * (_for_it_96 - 1))) + ((5 * sym_klon) * (_for_it_98 - 1))) - 1)];
                double zexplicit_out;

                ///////////////////
                // Tasklet code (T_l1226_c1226)
                zexplicit_out = (zexplicit_0_in + zsolqa_0_in_0);
                ///////////////////

                __state->__148_zexplicit = zexplicit_out;
            }
        }
    }

    {
        {
            double zexplicit_0_in = __state->__148_zexplicit;
            double zqx_0_in_0 = zqx[0];
            double zqxn_out_0;

            ///////////////////
            // Tasklet code (T_l1228_c1228)
            zqxn_out_0 = (zqx_0_in_0 + zexplicit_0_in);
            ///////////////////

            zqxn[0] = zqxn_out_0;
        }
    }
}

inline void loop_body_50_9_7(cloudsc_driver_state_t* __state, double* __restrict__ zqx, double* __restrict__ zsolqa, double* __restrict__ zqxn, int _for_it_96, int icend, int sym_klev, int sym_klon) {
    {
        {
            for (auto _for_it_97 = 1; _for_it_97 < (icend + 1); _for_it_97 += 1) {
                loop_body_147_0_0(__state, &zqx[(_for_it_97 - 1)], &zsolqa[0], &zqxn[(_for_it_97 - 1)], _for_it_96, _for_it_97, sym_klev, sym_klon);
            }
        }
    }
}

inline void loop_body_204_0_0(cloudsc_driver_state_t* __state, double* __restrict__ zqlhs, int _for_it_100, int _for_it_99, int sym_klon) {
    {
        {
            double zqlhs_0_in_0 = zqlhs[(sym_klon * (_for_it_100 - 1))];
            double zqlhs_1_in_0 = zqlhs[(sym_klon * (_for_it_99 - 1))];
            double zqlhs_out_0;

            ///////////////////
            // Tasklet code (T_l1233_c1233)
            zqlhs_out_0 = (zqlhs_0_in_0 / zqlhs_1_in_0);
            ///////////////////

            zqlhs[(sym_klon * (_for_it_100 - 1))] = zqlhs_out_0;
        }
    }
}

inline void loop_body_206_0_0(cloudsc_driver_state_t* __state, double* __restrict__ zqlhs, int _for_it_100, int _for_it_101, int _for_it_99, int sym_klon) {
    {
        {
            double zqlhs_0_in_0 = zqlhs[((sym_klon * (_for_it_100 - 1)) + ((5 * sym_klon) * (_for_it_101 - 1)))];
            double zqlhs_1_in_0 = zqlhs[((sym_klon * (_for_it_100 - 1)) + ((5 * sym_klon) * (_for_it_99 - 1)))];
            double zqlhs_2_in_0 = zqlhs[(((5 * sym_klon) * (_for_it_101 - 1)) + (sym_klon * (_for_it_99 - 1)))];
            double zqlhs_out_0;

            ///////////////////
            // Tasklet code (T_l1236_c1236)
            zqlhs_out_0 = (zqlhs_0_in_0 - (zqlhs_1_in_0 * zqlhs_2_in_0));
            ///////////////////

            zqlhs[((sym_klon * (_for_it_100 - 1)) + ((5 * sym_klon) * (_for_it_101 - 1)))] = zqlhs_out_0;
        }
    }
}

inline void loop_body_192_0_0(cloudsc_driver_state_t* __state, double* __restrict__ zqlhs, double* __restrict__ zqxn, int _for_it_103, int _for_it_104, int sym_klon) {
    {
        {
            double zqlhs_0_in_0 = zqlhs[0];
            double zqxn_0_in_0 = zqxn[(sym_klon * (_for_it_103 - 1))];
            double zqxn_1_in_0 = zqxn[(sym_klon * (_for_it_104 - 1))];
            double zqxn_out_0;

            ///////////////////
            // Tasklet code (T_l1243_c1243)
            zqxn_out_0 = (zqxn_0_in_0 - (zqlhs_0_in_0 * zqxn_1_in_0));
            ///////////////////

            zqxn[(sym_klon * (_for_it_103 - 1))] = zqxn_out_0;
        }
    }
}

inline void loop_body_50_5_0(cloudsc_driver_state_t* __state, double* __restrict__ zqlhs, double* __restrict__ zqxn, int sym_klon) {
    {
        {
            double zqlhs_0_in_0 = zqlhs[0];
            double zqxn_0_in_0 = zqxn[0];
            double zqxn_out_0;

            ///////////////////
            // Tasklet code (T_l1246_c1246)
            zqxn_out_0 = (zqxn_0_in_0 / zqlhs_0_in_0);
            ///////////////////

            zqxn[0] = zqxn_out_0;
        }
    }
}

inline void loop_body_174_0_0(cloudsc_driver_state_t* __state, double* __restrict__ zqlhs, double* __restrict__ zqxn, int _for_it_105, int _for_it_106, int sym_klon) {
    {
        {
            double zqlhs_0_in_0 = zqlhs[0];
            double zqxn_0_in_0 = zqxn[(sym_klon * (_for_it_105 - 1))];
            double zqxn_1_in_0 = zqxn[(sym_klon * (_for_it_106 - 1))];
            double zqxn_out_0;

            ///////////////////
            // Tasklet code (T_l1249_c1249)
            zqxn_out_0 = (zqxn_0_in_0 - (zqlhs_0_in_0 * zqxn_1_in_0));
            ///////////////////

            zqxn[(sym_klon * (_for_it_105 - 1))] = zqxn_out_0;
        }
    }
}

inline void loop_body_172_0_0(cloudsc_driver_state_t* __state, double* __restrict__ zqlhs, double* __restrict__ zqxn, int sym_klon) {
    {
        {
            double zqlhs_0_in_0 = zqlhs[0];
            double zqxn_0_in_0 = zqxn[0];
            double zqxn_out_0;

            ///////////////////
            // Tasklet code (T_l1251_c1251)
            zqxn_out_0 = (zqxn_0_in_0 / zqlhs_0_in_0);
            ///////////////////

            zqxn[0] = zqxn_out_0;
        }
    }
}

inline void loop_body_237_0_0(cloudsc_driver_state_t* __state, double* __restrict__ zqxn, int _for_it_107, int sym_klon) {
    double _if_cond_79;

    _if_cond_79 = (zqxn[(sym_klon * (_for_it_107 - 1))] < 1e-14);

    if ((_if_cond_79 == 1)) {
        {
            {
                double zqxn_0_in_0 = zqxn[(4 * sym_klon)];
                double zqxn_1_in_0 = zqxn[(sym_klon * (_for_it_107 - 1))];
                double zqxn_out_0;

                ///////////////////
                // Tasklet code (T_l1256_c1256)
                zqxn_out_0 = (zqxn_0_in_0 + zqxn_1_in_0);
                ///////////////////

                zqxn[(4 * sym_klon)] = zqxn_out_0;
            }
        }
        {
            {
                double zqxn_out_0;

                ///////////////////
                // Tasklet code (T_l1257_c1257)
                zqxn_out_0 = 0.0;
                ///////////////////

                zqxn[(sym_klon * (_for_it_107 - 1))] = zqxn_out_0;
            }
        }
    }
}

inline void loop_body_161_0_0(cloudsc_driver_state_t* __state, double* __restrict__ zqxn, double* __restrict__ zqxn2d, double* __restrict__ zqxnm1, int sym_klev, int sym_klon) {
    {
        {
            double zqxn_0_in_0 = zqxn[0];
            double zqxnm1_out_0;

            ///////////////////
            // Tasklet code (T_l1263_c1263)
            zqxnm1_out_0 = zqxn_0_in_0;
            ///////////////////

            zqxnm1[0] = zqxnm1_out_0;
        }
        {
            double zqxn_0_in_0 = zqxn[0];
            double zqxn2d_out_0;

            ///////////////////
            // Tasklet code (T_l1264_c1264)
            zqxn2d_out_0 = zqxn_0_in_0;
            ///////////////////

            zqxn2d[0] = zqxn2d_out_0;
        }
    }
}

inline void loop_body_50_13_0(cloudsc_driver_state_t* __state, double* __restrict__ zqxn, double* __restrict__ zqxn2d, double* __restrict__ zqxnm1, int icend, int sym_klev, int sym_klon) {
    {
        {
            for (auto _for_it_110 = 1; _for_it_110 < (icend + 1); _for_it_110 += 1) {
                loop_body_161_0_0(__state, &zqxn[(_for_it_110 - 1)], &zqxn2d[(_for_it_110 - 1)], &zqxnm1[(_for_it_110 - 1)], sym_klev, sym_klon);
            }
        }
    }
}

inline void loop_body_163_0_0(
    cloudsc_driver_state_t* __state, double* __restrict__ zfallsink, double* __restrict__ zqxn, double* __restrict__ zrdtgdp, double* __restrict__ zpfplsx, int sym_klev, int sym_klon) {
    {
        {
            double zfallsink_0_in_0 = zfallsink[0];
            double zqxn_0_in_0 = zqxn[0];
            double zrdtgdp_0_in_0 = zrdtgdp[0];
            double zpfplsx_out_0;

            ///////////////////
            // Tasklet code (T_l1269_c1269)
            zpfplsx_out_0 = ((zfallsink_0_in_0 * zqxn_0_in_0) * zrdtgdp_0_in_0);
            ///////////////////

            zpfplsx[0] = zpfplsx_out_0;
        }
    }
}

inline void loop_body_50_13_6(
    cloudsc_driver_state_t* __state, double* __restrict__ zfallsink, double* __restrict__ zqxn, double* __restrict__ zrdtgdp, double* __restrict__ zpfplsx, int icend, int sym_klev, int sym_klon) {
    {
        {
            for (auto _for_it_112 = 1; _for_it_112 < (icend + 1); _for_it_112 += 1) {
                loop_body_163_0_0(__state, &zfallsink[(_for_it_112 - 1)], &zqxn[(_for_it_112 - 1)], &zrdtgdp[(_for_it_112 - 1)], &zpfplsx[(_for_it_112 - 1)], sym_klev, sym_klon);
            }
        }
    }
}

inline void loop_body_50_13_12(cloudsc_driver_state_t* __state, double* __restrict__ zpfplsx, double* __restrict__ zqpretot, int sym_klev, int sym_klon) {
    {
        {
            double zpfplsx_0_in_0 = zpfplsx[((3 * sym_klon) * (sym_klev + 1))];
            double zpfplsx_1_in_0 = zpfplsx[((2 * sym_klon) * (sym_klev + 1))];
            double zqpretot_out_0;

            ///////////////////
            // Tasklet code (T_l1273_c1273)
            zqpretot_out_0 = (zpfplsx_0_in_0 + zpfplsx_1_in_0);
            ///////////////////

            zqpretot[0] = zqpretot_out_0;
        }
    }
}

inline void loop_body_50_13_16(cloudsc_driver_state_t* __state, double* __restrict__ zqpretot, double* __restrict__ zcovptot) {
    double _if_cond_80;

    _if_cond_80 = (zqpretot[0] < 1e-14);

    if ((_if_cond_80 == 1)) {
        {
            {
                double zcovptot_out_0;

                ///////////////////
                // Tasklet code (T_l1277_c1277)
                zcovptot_out_0 = 0.0;
                ///////////////////

                zcovptot[0] = zcovptot_out_0;
            }
        }
    }
}

inline void loop_body_322_1_0(
    cloudsc_driver_state_t* __state, double* __restrict__ zconvsink, double* __restrict__ zconvsrce, double* __restrict__ zfallsink, double* __restrict__ zfallsrce, double* __restrict__ zpsupsatsrce,
    double* __restrict__ zqxn, double* __restrict__ zfluxq, int sym_klon) {
    {
        {
            double zconvsink_0_in_0 = zconvsink[0];
            double zconvsrce_0_in_0 = zconvsrce[0];
            double zfallsink_0_in_0 = zfallsink[0];
            double zfallsrce_0_in_0 = zfallsrce[0];
            double zpsupsatsrce_0_in_0 = zpsupsatsrce[0];
            double zqxn_0_in_0 = zqxn[0];
            double zfluxq_out_0;

            ///////////////////
            // Tasklet code (T_l1282_c1282)
            zfluxq_out_0 = (((zpsupsatsrce_0_in_0 + zconvsrce_0_in_0) + zfallsrce_0_in_0) - ((zfallsink_0_in_0 + zconvsink_0_in_0) * zqxn_0_in_0));
            ///////////////////

            zfluxq[0] = zfluxq_out_0;
        }
    }
}

inline void loop_body_326_0_0(
    cloudsc_driver_state_t* __state, toethf* __restrict__ ydthf, double* __restrict__ zfluxq, const double& zqtmst, double* __restrict__ zqx, double* __restrict__ zqxn,
    double* __restrict__ ptendency_loc_t, int sym_klev, int sym_klon) {
    {
        double* v_ydthf_ralvdcp;
        v_ydthf_ralvdcp = (double*)(&(ydthf->ralvdcp));

        {
            double ptendency_loc_t_0_in_0 = ptendency_loc_t[0];
            double ydthf_0_in_ralvdcp = v_ydthf_ralvdcp[0];
            double zfluxq_0_in_0 = zfluxq[0];
            double zqtmst_0_in = zqtmst;
            double zqx_0_in_0 = zqx[0];
            double zqxn_0_in_0 = zqxn[0];
            double ptendency_loc_t_out_0;

            ///////////////////
            // Tasklet code (T_l1286_c1286)
            ptendency_loc_t_out_0 = (ptendency_loc_t_0_in_0 + ((ydthf_0_in_ralvdcp * ((zqxn_0_in_0 - zqx_0_in_0) - zfluxq_0_in_0)) * zqtmst_0_in));
            ///////////////////

            ptendency_loc_t[0] = ptendency_loc_t_out_0;
        }
    }
}

inline void loop_body_329_0_0(
    cloudsc_driver_state_t* __state, toethf* __restrict__ ydthf, double* __restrict__ zfluxq, const double& zqtmst, double* __restrict__ zqx, double* __restrict__ zqxn,
    double* __restrict__ ptendency_loc_t, int sym_klev, int sym_klon) {
    {
        double* v_ydthf_ralsdcp;
        v_ydthf_ralsdcp = (double*)(&(ydthf->ralsdcp));

        {
            double ptendency_loc_t_0_in_0 = ptendency_loc_t[0];
            double ydthf_0_in_ralsdcp = v_ydthf_ralsdcp[0];
            double zfluxq_0_in_0 = zfluxq[0];
            double zqtmst_0_in = zqtmst;
            double zqx_0_in_0 = zqx[0];
            double zqxn_0_in_0 = zqxn[0];
            double ptendency_loc_t_out_0;

            ///////////////////
            // Tasklet code (T_l1291_c1291)
            ptendency_loc_t_out_0 = (ptendency_loc_t_0_in_0 + ((ydthf_0_in_ralsdcp * ((zqxn_0_in_0 - zqx_0_in_0) - zfluxq_0_in_0)) * zqtmst_0_in));
            ///////////////////

            ptendency_loc_t[0] = ptendency_loc_t_out_0;
        }
    }
}

inline void loop_body_322_0_0(
    cloudsc_driver_state_t* __state, const double& zqtmst, double* __restrict__ zqx0, double* __restrict__ zqxn, double* __restrict__ ptendency_loc_cld, int sym_klev, int sym_klon) {
    {
        {
            double ptendency_loc_cld_0_in_0 = ptendency_loc_cld[0];
            double zqtmst_0_in = zqtmst;
            double zqx0_0_in_0 = zqx0[0];
            double zqxn_0_in_0 = zqxn[0];
            double ptendency_loc_cld_out_0;

            ///////////////////
            // Tasklet code (T_l1295_c1295)
            ptendency_loc_cld_out_0 = (ptendency_loc_cld_0_in_0 + ((zqxn_0_in_0 - zqx0_0_in_0) * zqtmst_0_in));
            ///////////////////

            ptendency_loc_cld[0] = ptendency_loc_cld_out_0;
        }
    }
}

inline void loop_body_50_4_0(
    cloudsc_driver_state_t* __state, double* __restrict__ zda, const double& zqtmst, double* __restrict__ zqx, double* __restrict__ zqxn, double* __restrict__ ptendency_loc_a,
    double* __restrict__ ptendency_loc_q, int sym_klev, int sym_klon) {
    {
        {
            double ptendency_loc_q_0_in_0 = ptendency_loc_q[0];
            double zqtmst_0_in = zqtmst;
            double zqx_0_in_0 = zqx[0];
            double zqxn_0_in_0 = zqxn[0];
            double ptendency_loc_q_out_0;

            ///////////////////
            // Tasklet code (T_l1299_c1299)
            ptendency_loc_q_out_0 = (ptendency_loc_q_0_in_0 + ((zqxn_0_in_0 - zqx_0_in_0) * zqtmst_0_in));
            ///////////////////

            ptendency_loc_q[0] = ptendency_loc_q_out_0;
        }
        {
            double ptendency_loc_a_0_in_0 = ptendency_loc_a[0];
            double zda_0_in_0 = zda[0];
            double zqtmst_0_in = zqtmst;
            double ptendency_loc_a_out_0;

            ///////////////////
            // Tasklet code (T_l1300_c1300)
            ptendency_loc_a_out_0 = (ptendency_loc_a_0_in_0 + (zda_0_in_0 * zqtmst_0_in));
            ///////////////////

            ptendency_loc_a[0] = ptendency_loc_a_out_0;
        }
    }
}

inline void loop_body_50_4_11(cloudsc_driver_state_t* __state, double* __restrict__ zcovptot, double* __restrict__ pcovptot_var_31, int sym_klon) {
    {
        {
            double zcovptot_0_in_0 = zcovptot[0];
            double pcovptot_var_31_out_0;

            ///////////////////
            // Tasklet code (T_l1303_c1303)
            pcovptot_var_31_out_0 = zcovptot_0_in_0;
            ///////////////////

            pcovptot_var_31[0] = pcovptot_var_31_out_0;
        }
    }
}

inline void loop_body_43_0_0(cloudsc_driver_state_t* __state, double* __restrict__ zpfplsx, double* __restrict__ pfplsl_var_43, double* __restrict__ pfplsn_var_44, int sym_klev, int sym_klon) {
    {
        {
            double zpfplsx_0_in_0 = zpfplsx[((2 * sym_klon) * (sym_klev + 1))];
            double zpfplsx_1_in_0 = zpfplsx[0];
            double pfplsl_var_43_out_0;

            ///////////////////
            // Tasklet code (T_l1308_c1308)
            pfplsl_var_43_out_0 = (zpfplsx_0_in_0 + zpfplsx_1_in_0);
            ///////////////////

            pfplsl_var_43[0] = pfplsl_var_43_out_0;
        }
        {
            double zpfplsx_0_in_0 = zpfplsx[((3 * sym_klon) * (sym_klev + 1))];
            double zpfplsx_1_in_0 = zpfplsx[(sym_klon * (sym_klev + 1))];
            double pfplsn_var_44_out_0;

            ///////////////////
            // Tasklet code (T_l1309_c1309)
            pfplsn_var_44_out_0 = (zpfplsx_0_in_0 + zpfplsx_1_in_0);
            ///////////////////

            pfplsn_var_44[0] = pfplsn_var_44_out_0;
        }
    }
}

inline void loop_body_6_6_0(
    cloudsc_driver_state_t* __state, double* __restrict__ zpfplsx, double* __restrict__ pfplsl_var_43, double* __restrict__ pfplsn_var_44, int icend, int sym_klev, int sym_klon) {
    {
        {
            for (auto _for_it_123 = 1; _for_it_123 < (icend + 1); _for_it_123 += 1) {
                loop_body_43_0_0(__state, &zpfplsx[(_for_it_123 - 1)], &pfplsl_var_43[(_for_it_123 - 1)], &pfplsn_var_44[(_for_it_123 - 1)], sym_klev, sym_klon);
            }
        }
    }
}

inline void loop_body_6_6_7(
    cloudsc_driver_state_t* __state, double* __restrict__ pfcqlng_var_35, double* __restrict__ pfcqnng_var_36, double* __restrict__ pfcqrng_var_39, double* __restrict__ pfcqsng_var_40,
    double* __restrict__ pfsqif_var_34, double* __restrict__ pfsqitur_var_42, double* __restrict__ pfsqlf_var_33, double* __restrict__ pfsqltur_var_41, double* __restrict__ pfsqrf_var_37,
    double* __restrict__ pfsqsf_var_38, int sym_klon) {
    {
        {
            double pfsqlf_var_33_out_0;

            ///////////////////
            // Tasklet code (T_l1313_c1313)
            pfsqlf_var_33_out_0 = 0.0;
            ///////////////////

            pfsqlf_var_33[0] = pfsqlf_var_33_out_0;
        }
        {
            double pfsqif_var_34_out_0;

            ///////////////////
            // Tasklet code (T_l1314_c1314)
            pfsqif_var_34_out_0 = 0.0;
            ///////////////////

            pfsqif_var_34[0] = pfsqif_var_34_out_0;
        }
        {
            double pfsqrf_var_37_out_0;

            ///////////////////
            // Tasklet code (T_l1315_c1315)
            pfsqrf_var_37_out_0 = 0.0;
            ///////////////////

            pfsqrf_var_37[0] = pfsqrf_var_37_out_0;
        }
        {
            double pfsqsf_var_38_out_0;

            ///////////////////
            // Tasklet code (T_l1316_c1316)
            pfsqsf_var_38_out_0 = 0.0;
            ///////////////////

            pfsqsf_var_38[0] = pfsqsf_var_38_out_0;
        }
        {
            double pfcqlng_var_35_out_0;

            ///////////////////
            // Tasklet code (T_l1317_c1317)
            pfcqlng_var_35_out_0 = 0.0;
            ///////////////////

            pfcqlng_var_35[0] = pfcqlng_var_35_out_0;
        }
        {
            double pfcqnng_var_36_out_0;

            ///////////////////
            // Tasklet code (T_l1318_c1318)
            pfcqnng_var_36_out_0 = 0.0;
            ///////////////////

            pfcqnng_var_36[0] = pfcqnng_var_36_out_0;
        }
        {
            double pfcqrng_var_39_out_0;

            ///////////////////
            // Tasklet code (T_l1319_c1319)
            pfcqrng_var_39_out_0 = 0.0;
            ///////////////////

            pfcqrng_var_39[0] = pfcqrng_var_39_out_0;
        }
        {
            double pfcqsng_var_40_out_0;

            ///////////////////
            // Tasklet code (T_l1320_c1320)
            pfcqsng_var_40_out_0 = 0.0;
            ///////////////////

            pfcqsng_var_40[0] = pfcqsng_var_40_out_0;
        }
        {
            double pfsqltur_var_41_out_0;

            ///////////////////
            // Tasklet code (T_l1321_c1321)
            pfsqltur_var_41_out_0 = 0.0;
            ///////////////////

            pfsqltur_var_41[0] = pfsqltur_var_41_out_0;
        }
        {
            double pfsqitur_var_42_out_0;

            ///////////////////
            // Tasklet code (T_l1322_c1322)
            pfsqitur_var_42_out_0 = 0.0;
            ///////////////////

            pfsqitur_var_42[0] = pfsqitur_var_42_out_0;
        }
    }
}

inline void loop_body_48_0_0(
    cloudsc_driver_state_t* __state, double* __restrict__ paph_var_18, double* __restrict__ plude_var_23, const double* __restrict__ ptsphy_var_5, double* __restrict__ pvfi_var_10,
    double* __restrict__ pvfl_var_9, double* __restrict__ zfoealfa, double* __restrict__ zlneg, const double& zqtmst, double* __restrict__ zqx0, double* __restrict__ zqxn2d, const double& zrg_r,
    double* __restrict__ pfcqlng_var_35, double* __restrict__ pfcqnng_var_36, double* __restrict__ pfcqrng_var_39, double* __restrict__ pfcqsng_var_40, double* __restrict__ pfsqif_var_34,
    double* __restrict__ pfsqitur_var_42, double* __restrict__ pfsqlf_var_33, double* __restrict__ pfsqltur_var_41, double* __restrict__ pfsqrf_var_37, double* __restrict__ pfsqsf_var_38,
    int _for_it_125, int sym_klev, int sym_klon) {
    double zalfaw;

    zalfaw = zfoealfa[0];

    {
        {
            double paph_var_18_0_in_0 = paph_var_18[(_for_it_125 * sym_klon)];
            double paph_var_18_1_in_0 = paph_var_18[(sym_klon * (_for_it_125 - 1))];
            double zqtmst_0_in = zqtmst;
            double zrg_r_0_in = zrg_r;
            double zgdph_r_out;

            ///////////////////
            // Tasklet code (T_l1326_c1326)
            zgdph_r_out = (-((zrg_r_0_in * (paph_var_18_0_in_0 - paph_var_18_1_in_0)) * zqtmst_0_in));
            ///////////////////

            __state->__49_zgdph_r = zgdph_r_out;
        }
        {
            double pfsqlf_var_33_0_in_0 = pfsqlf_var_33[(sym_klon * (_for_it_125 - 1))];
            double pfsqlf_var_33_out_0;

            ///////////////////
            // Tasklet code (T_l1327_c1327)
            pfsqlf_var_33_out_0 = pfsqlf_var_33_0_in_0;
            ///////////////////

            pfsqlf_var_33[(_for_it_125 * sym_klon)] = pfsqlf_var_33_out_0;
        }
        {
            double pfsqlf_var_33_0_in_0 = pfsqlf_var_33[(sym_klon * (_for_it_125 - 1))];
            double pfsqrf_var_37_out_0;

            ///////////////////
            // Tasklet code (T_l1329_c1329)
            pfsqrf_var_37_out_0 = pfsqlf_var_33_0_in_0;
            ///////////////////

            pfsqrf_var_37[0] = pfsqrf_var_37_out_0;
        }
        {
            double pfsqif_var_34_0_in_0 = pfsqif_var_34[(sym_klon * (_for_it_125 - 1))];
            double pfsqif_var_34_out_0;

            ///////////////////
            // Tasklet code (T_l1328_c1328)
            pfsqif_var_34_out_0 = pfsqif_var_34_0_in_0;
            ///////////////////

            pfsqif_var_34[(_for_it_125 * sym_klon)] = pfsqif_var_34_out_0;
        }
        {
            double pfsqif_var_34_0_in_0 = pfsqif_var_34[(sym_klon * (_for_it_125 - 1))];
            double pfsqsf_var_38_out_0;

            ///////////////////
            // Tasklet code (T_l1330_c1330)
            pfsqsf_var_38_out_0 = pfsqif_var_34_0_in_0;
            ///////////////////

            pfsqsf_var_38[0] = pfsqsf_var_38_out_0;
        }
        {
            double pfcqlng_var_35_0_in_0 = pfcqlng_var_35[(sym_klon * (_for_it_125 - 1))];
            double pfcqlng_var_35_out_0;

            ///////////////////
            // Tasklet code (T_l1331_c1331)
            pfcqlng_var_35_out_0 = pfcqlng_var_35_0_in_0;
            ///////////////////

            pfcqlng_var_35[(_for_it_125 * sym_klon)] = pfcqlng_var_35_out_0;
        }
        {
            double pfcqlng_var_35_0_in_0 = pfcqlng_var_35[(sym_klon * (_for_it_125 - 1))];
            double pfcqrng_var_39_out_0;

            ///////////////////
            // Tasklet code (T_l1333_c1333)
            pfcqrng_var_39_out_0 = pfcqlng_var_35_0_in_0;
            ///////////////////

            pfcqrng_var_39[0] = pfcqrng_var_39_out_0;
        }
        {
            double pfcqnng_var_36_0_in_0 = pfcqnng_var_36[(sym_klon * (_for_it_125 - 1))];
            double pfcqnng_var_36_out_0;

            ///////////////////
            // Tasklet code (T_l1332_c1332)
            pfcqnng_var_36_out_0 = pfcqnng_var_36_0_in_0;
            ///////////////////

            pfcqnng_var_36[(_for_it_125 * sym_klon)] = pfcqnng_var_36_out_0;
        }
        {
            double pfcqnng_var_36_0_in_0 = pfcqnng_var_36[(sym_klon * (_for_it_125 - 1))];
            double pfcqsng_var_40_out_0;

            ///////////////////
            // Tasklet code (T_l1334_c1334)
            pfcqsng_var_40_out_0 = pfcqnng_var_36_0_in_0;
            ///////////////////

            pfcqsng_var_40[0] = pfcqsng_var_40_out_0;
        }
        {
            double pfsqltur_var_41_0_in_0 = pfsqltur_var_41[(sym_klon * (_for_it_125 - 1))];
            double pfsqltur_var_41_out_0;

            ///////////////////
            // Tasklet code (T_l1335_c1335)
            pfsqltur_var_41_out_0 = pfsqltur_var_41_0_in_0;
            ///////////////////

            pfsqltur_var_41[(_for_it_125 * sym_klon)] = pfsqltur_var_41_out_0;
        }
        {
            double pfsqitur_var_42_0_in_0 = pfsqitur_var_42[(sym_klon * (_for_it_125 - 1))];
            double pfsqitur_var_42_out_0;

            ///////////////////
            // Tasklet code (T_l1336_c1336)
            pfsqitur_var_42_out_0 = pfsqitur_var_42_0_in_0;
            ///////////////////

            pfsqitur_var_42[(_for_it_125 * sym_klon)] = pfsqitur_var_42_out_0;
        }
    }

    {
        {
            double pfsqlf_var_33_0_in_0 = pfsqlf_var_33[(_for_it_125 * sym_klon)];
            double plude_var_23_0_in_0 = plude_var_23[0];
            double ptsphy_var_5_0_in = ptsphy_var_5[0];
            double pvfl_var_9_0_in_0 = pvfl_var_9[0];
            double zgdph_r_0_in = __state->__49_zgdph_r;
            double zqx0_0_in_0 = zqx0[0];
            double zqxn2d_0_in_0 = zqxn2d[0];
            double pfsqlf_var_33_out_0;

            ///////////////////
            // Tasklet code (T_l1338_c1338)
            pfsqlf_var_33_out_0 = (pfsqlf_var_33_0_in_0 + ((((zqxn2d_0_in_0 - zqx0_0_in_0) + (pvfl_var_9_0_in_0 * ptsphy_var_5_0_in)) - (zalfaw * plude_var_23_0_in_0)) * zgdph_r_0_in));
            ///////////////////

            pfsqlf_var_33[(_for_it_125 * sym_klon)] = pfsqlf_var_33_out_0;
        }
        {
            double pfsqrf_var_37_0_in_0 = pfsqrf_var_37[0];
            double zgdph_r_0_in = __state->__49_zgdph_r;
            double zqx0_0_in_0 = zqx0[((2 * sym_klev) * sym_klon)];
            double zqxn2d_0_in_0 = zqxn2d[((2 * sym_klev) * sym_klon)];
            double pfsqrf_var_37_out_0;

            ///////////////////
            // Tasklet code (T_l1341_c1341)
            pfsqrf_var_37_out_0 = (pfsqrf_var_37_0_in_0 + ((zqxn2d_0_in_0 - zqx0_0_in_0) * zgdph_r_0_in));
            ///////////////////

            pfsqrf_var_37[0] = pfsqrf_var_37_out_0;
        }
        {
            double pfsqif_var_34_0_in_0 = pfsqif_var_34[(_for_it_125 * sym_klon)];
            double plude_var_23_0_in_0 = plude_var_23[0];
            double ptsphy_var_5_0_in = ptsphy_var_5[0];
            double pvfi_var_10_0_in_0 = pvfi_var_10[0];
            double zgdph_r_0_in = __state->__49_zgdph_r;
            double zqx0_0_in_0 = zqx0[(sym_klev * sym_klon)];
            double zqxn2d_0_in_0 = zqxn2d[(sym_klev * sym_klon)];
            double pfsqif_var_34_out_0;

            ///////////////////
            // Tasklet code (T_l1343_c1343)
            pfsqif_var_34_out_0 = (pfsqif_var_34_0_in_0 + ((((zqxn2d_0_in_0 - zqx0_0_in_0) + (pvfi_var_10_0_in_0 * ptsphy_var_5_0_in)) - ((1.0 - zalfaw) * plude_var_23_0_in_0)) * zgdph_r_0_in));
            ///////////////////

            pfsqif_var_34[(_for_it_125 * sym_klon)] = pfsqif_var_34_out_0;
        }
        {
            double pfsqsf_var_38_0_in_0 = pfsqsf_var_38[0];
            double zgdph_r_0_in = __state->__49_zgdph_r;
            double zqx0_0_in_0 = zqx0[((3 * sym_klev) * sym_klon)];
            double zqxn2d_0_in_0 = zqxn2d[((3 * sym_klev) * sym_klon)];
            double pfsqsf_var_38_out_0;

            ///////////////////
            // Tasklet code (T_l1346_c1346)
            pfsqsf_var_38_out_0 = (pfsqsf_var_38_0_in_0 + ((zqxn2d_0_in_0 - zqx0_0_in_0) * zgdph_r_0_in));
            ///////////////////

            pfsqsf_var_38[0] = pfsqsf_var_38_out_0;
        }
        {
            double pfsqltur_var_41_0_in_0 = pfsqltur_var_41[(_for_it_125 * sym_klon)];
            double ptsphy_var_5_0_in = ptsphy_var_5[0];
            double pvfl_var_9_0_in_0 = pvfl_var_9[0];
            double zgdph_r_0_in = __state->__49_zgdph_r;
            double pfsqltur_var_41_out_0;

            ///////////////////
            // Tasklet code (T_l1340_c1340)
            pfsqltur_var_41_out_0 = (pfsqltur_var_41_0_in_0 + ((pvfl_var_9_0_in_0 * ptsphy_var_5_0_in) * zgdph_r_0_in));
            ///////////////////

            pfsqltur_var_41[(_for_it_125 * sym_klon)] = pfsqltur_var_41_out_0;
        }
        {
            double pfsqitur_var_42_0_in_0 = pfsqitur_var_42[(_for_it_125 * sym_klon)];
            double ptsphy_var_5_0_in = ptsphy_var_5[0];
            double pvfi_var_10_0_in_0 = pvfi_var_10[0];
            double zgdph_r_0_in = __state->__49_zgdph_r;
            double pfsqitur_var_42_out_0;

            ///////////////////
            // Tasklet code (T_l1345_c1345)
            pfsqitur_var_42_out_0 = (pfsqitur_var_42_0_in_0 + ((pvfi_var_10_0_in_0 * ptsphy_var_5_0_in) * zgdph_r_0_in));
            ///////////////////

            pfsqitur_var_42[(_for_it_125 * sym_klon)] = pfsqitur_var_42_out_0;
        }
        {
            double pfcqlng_var_35_0_in_0 = pfcqlng_var_35[(_for_it_125 * sym_klon)];
            double zgdph_r_0_in = __state->__49_zgdph_r;
            double zlneg_0_in_0 = zlneg[0];
            double pfcqlng_var_35_out_0;

            ///////////////////
            // Tasklet code (T_l1339_c1339)
            pfcqlng_var_35_out_0 = (pfcqlng_var_35_0_in_0 + (zlneg_0_in_0 * zgdph_r_0_in));
            ///////////////////

            pfcqlng_var_35[(_for_it_125 * sym_klon)] = pfcqlng_var_35_out_0;
        }
        {
            double pfcqrng_var_39_0_in_0 = pfcqrng_var_39[0];
            double zgdph_r_0_in = __state->__49_zgdph_r;
            double zlneg_0_in_0 = zlneg[((2 * sym_klev) * sym_klon)];
            double pfcqrng_var_39_out_0;

            ///////////////////
            // Tasklet code (T_l1342_c1342)
            pfcqrng_var_39_out_0 = (pfcqrng_var_39_0_in_0 + (zlneg_0_in_0 * zgdph_r_0_in));
            ///////////////////

            pfcqrng_var_39[0] = pfcqrng_var_39_out_0;
        }
        {
            double pfcqnng_var_36_0_in_0 = pfcqnng_var_36[(_for_it_125 * sym_klon)];
            double zgdph_r_0_in = __state->__49_zgdph_r;
            double zlneg_0_in_0 = zlneg[(sym_klev * sym_klon)];
            double pfcqnng_var_36_out_0;

            ///////////////////
            // Tasklet code (T_l1344_c1344)
            pfcqnng_var_36_out_0 = (pfcqnng_var_36_0_in_0 + (zlneg_0_in_0 * zgdph_r_0_in));
            ///////////////////

            pfcqnng_var_36[(_for_it_125 * sym_klon)] = pfcqnng_var_36_out_0;
        }
        {
            double pfcqsng_var_40_0_in_0 = pfcqsng_var_40[0];
            double zgdph_r_0_in = __state->__49_zgdph_r;
            double zlneg_0_in_0 = zlneg[((3 * sym_klev) * sym_klon)];
            double pfcqsng_var_40_out_0;

            ///////////////////
            // Tasklet code (T_l1347_c1347)
            pfcqsng_var_40_out_0 = (pfcqsng_var_40_0_in_0 + (zlneg_0_in_0 * zgdph_r_0_in));
            ///////////////////

            pfcqsng_var_40[0] = pfcqsng_var_40_out_0;
        }
    }
}

inline void loop_body_46_0_0(
    cloudsc_driver_state_t* __state, double* __restrict__ pfplsl_var_43, double* __restrict__ pfplsn_var_44, tomcst* __restrict__ ydcst, double* __restrict__ pfhpsl_var_45,
    double* __restrict__ pfhpsn_var_46, int sym_klon) {
    {
        double* v_ydcst_rlstt;
        v_ydcst_rlstt = (double*)(&(ydcst->rlstt));
        double* v_ydcst_rlvtt;
        v_ydcst_rlvtt = (double*)(&(ydcst->rlvtt));

        {
            double pfplsl_var_43_0_in_0 = pfplsl_var_43[0];
            double ydcst_0_in_rlvtt = v_ydcst_rlvtt[0];
            double pfhpsl_var_45_out_0;

            ///////////////////
            // Tasklet code (T_l1352_c1352)
            pfhpsl_var_45_out_0 = (-(ydcst_0_in_rlvtt * pfplsl_var_43_0_in_0));
            ///////////////////

            pfhpsl_var_45[0] = pfhpsl_var_45_out_0;
        }
        {
            double pfplsn_var_44_0_in_0 = pfplsn_var_44[0];
            double ydcst_0_in_rlstt = v_ydcst_rlstt[0];
            double pfhpsn_var_46_out_0;

            ///////////////////
            // Tasklet code (T_l1353_c1353)
            pfhpsn_var_46_out_0 = (-(ydcst_0_in_rlstt * pfplsn_var_44_0_in_0));
            ///////////////////

            pfhpsn_var_46[0] = pfhpsn_var_46_out_0;
        }
    }
}

inline void loop_body_6_7_0(
    cloudsc_driver_state_t* __state, double* __restrict__ pfplsl_var_43, double* __restrict__ pfplsn_var_44, tomcst* __restrict__ ydcst, double* __restrict__ pfhpsl_var_45,
    double* __restrict__ pfhpsn_var_46, int icend, int sym_klon) {
    {
        {
            for (auto _for_it_128 = 1; _for_it_128 < (icend + 1); _for_it_128 += 1) {
                loop_body_46_0_0(__state, &pfplsl_var_43[(_for_it_128 - 1)], &pfplsn_var_44[(_for_it_128 - 1)], ydcst, &pfhpsl_var_45[(_for_it_128 - 1)], &pfhpsn_var_46[(_for_it_128 - 1)], sym_klon);
            }
        }
    }
}

inline void cloudsc0_1_2_129(
    cloudsc_driver_state_t* __state, const int* __restrict__ kfldx_var_28, const int* __restrict__ klev, const int* __restrict__ klon, int* __restrict__ ktype_var_21, int* __restrict__ ldcum_var_20,
    double* __restrict__ pa_var_27, double* __restrict__ pap_var_17, double* __restrict__ paph_var_18, double* __restrict__ pccn_var_3, double* __restrict__ pclv_var_29,
    double* __restrict__ pdyna_var_11, double* __restrict__ pdyni_var_13, double* __restrict__ pdynl_var_12, double* __restrict__ phrlw_var_15, double* __restrict__ phrsw_var_14,
    double* __restrict__ picrit_aer_var_1, double* __restrict__ plcrit_aer_var_0, double* __restrict__ plsm_var_19, double* __restrict__ plu_var_22, double* __restrict__ pmfd_var_26,
    double* __restrict__ pmfu_var_25, double* __restrict__ pnice_var_4, double* __restrict__ pq_var_7, double* __restrict__ pre_ice_var_2, double* __restrict__ psnde_var_24,
    double* __restrict__ psupsat_var_30, double* __restrict__ pt_var_6, double* __restrict__ ptendency_tmp_a, double* __restrict__ ptendency_tmp_cld, double* __restrict__ ptendency_tmp_q,
    double* __restrict__ ptendency_tmp_t, const double* __restrict__ ptsphy_var_5, double* __restrict__ pvervel_var_16, double* __restrict__ pvfa_var_8, double* __restrict__ pvfi_var_10,
    double* __restrict__ pvfl_var_9, tomcst* __restrict__ ydcst, double* __restrict__ pcovptot_var_31, double* __restrict__ pfcqlng_var_35, double* __restrict__ pfcqnng_var_36,
    double* __restrict__ pfcqrng_var_39, double* __restrict__ pfcqsng_var_40, double* __restrict__ pfhpsl_var_45, double* __restrict__ pfhpsn_var_46, double* __restrict__ pfplsl_var_43,
    double* __restrict__ pfplsn_var_44, double* __restrict__ pfsqif_var_34, double* __restrict__ pfsqitur_var_42, double* __restrict__ pfsqlf_var_33, double* __restrict__ pfsqltur_var_41,
    double* __restrict__ pfsqrf_var_37, double* __restrict__ pfsqsf_var_38, double* __restrict__ plude_var_23, double* __restrict__ prainfrac_toprfz_var_32, double* __restrict__ ptendency_loc_a,
    double* __restrict__ ptendency_loc_cld, double* __restrict__ ptendency_loc_q, double* __restrict__ ptendency_loc_t, tecldp* __restrict__ ydecldp_var_47, toethf* __restrict__ ydthf, int icend,
    int sym_klev, int sym_klon) {
    double* v_ydcst_rg;
    v_ydcst_rg = (double*)(&(ydcst->rg));
    double* v_ydcst_rcpd;
    v_ydcst_rcpd = (double*)(&(ydcst->rcpd));
    double* v_ydcst_rd;
    v_ydcst_rd = (double*)(&(ydcst->rd));
    double* v_ydecldp_var_47_rtaumel;
    v_ydecldp_var_47_rtaumel = (double*)(&(ydecldp_var_47->rtaumel));
    double* v_ydthf_ralsdcp;
    v_ydthf_ralsdcp = (double*)(&(ydthf->ralsdcp));
    double* v_ydthf_ralvdcp;
    v_ydthf_ralvdcp = (double*)(&(ydthf->ralvdcp));
    double* v_ydecldp_var_47_rlmin;
    v_ydecldp_var_47_rlmin = (double*)(&(ydecldp_var_47->rlmin));
    double* v_ydecldp_var_47_ramin;
    v_ydecldp_var_47_ramin = (double*)(&(ydecldp_var_47->ramin));
    double* v_ydthf_rtwat;
    v_ydthf_rtwat = (double*)(&(ydthf->rtwat));
    double* v_ydthf_rtice;
    v_ydthf_rtice = (double*)(&(ydthf->rtice));
    double* v_ydthf_rtwat_rtice_r;
    v_ydthf_rtwat_rtice_r = (double*)(&(ydthf->rtwat_rtice_r));
    double* v_ydthf_r3ies;
    v_ydthf_r3ies = (double*)(&(ydthf->r3ies));
    double* v_ydcst_rtt;
    v_ydcst_rtt = (double*)(&(ydcst->rtt));
    double* v_ydthf_r4ies;
    v_ydthf_r4ies = (double*)(&(ydthf->r4ies));
    double* v_ydthf_r3les;
    v_ydthf_r3les = (double*)(&(ydthf->r3les));
    double* v_ydthf_r4les;
    v_ydthf_r4les = (double*)(&(ydthf->r4les));
    double* v_ydthf_r2es;
    v_ydthf_r2es = (double*)(&(ydthf->r2es));
    double* v_ydcst_retv;
    v_ydcst_retv = (double*)(&(ydcst->retv));
    int* v_ydecldp_var_47_ncldtop;
    v_ydecldp_var_47_ncldtop = (int*)(&(ydecldp_var_47->ncldtop));
    int* v_ydecldp_var_47_nssopt;
    v_ydecldp_var_47_nssopt = (int*)(&(ydecldp_var_47->nssopt));
    double* v_ydecldp_var_47_rthomo;
    v_ydecldp_var_47_rthomo = (double*)(&(ydecldp_var_47->rthomo));
    double* v_ydthf_r5alvcp;
    v_ydthf_r5alvcp = (double*)(&(ydthf->r5alvcp));
    double* v_ydthf_r5alscp;
    v_ydthf_r5alscp = (double*)(&(ydthf->r5alscp));
    double* v_ydecldp_var_47_ramid;
    v_ydecldp_var_47_ramid = (double*)(&(ydecldp_var_47->ramid));
    double* v_ydcst_rv;
    v_ydcst_rv = (double*)(&(ydcst->rv));
    double* v_ydecldp_var_47_rcovpmin;
    v_ydecldp_var_47_rcovpmin = (double*)(&(ydecldp_var_47->rcovpmin));
    double* v_ydecldp_var_47_rdensref;
    v_ydecldp_var_47_rdensref = (double*)(&(ydecldp_var_47->rdensref));
    double* v_ydecldp_var_47_rcl_fac1;
    v_ydecldp_var_47_rcl_fac1 = (double*)(&(ydecldp_var_47->rcl_fac1));
    double* v_ydecldp_var_47_rcl_fac2;
    v_ydecldp_var_47_rcl_fac2 = (double*)(&(ydecldp_var_47->rcl_fac2));
    double* v_ydecldp_var_47_rprecrhmax;
    v_ydecldp_var_47_rprecrhmax = (double*)(&(ydecldp_var_47->rprecrhmax));
    int _for_it_125;
    int jnn;
    int _for_it_23;
    double zalfaw;
    double zfac;
    int _for_it_26;
    int _for_it_105;
    int _for_it_106;
    int _for_it_42;
    int _if_cond_71;
    int _for_it_60;
    int _if_cond_72;
    int _for_it_61;
    int tmp_index_1570;
    int _for_it_53;
    double _if_cond_60;
    int _for_it_103;
    int _for_it_104;
    double _if_cond_70;
    int _for_it_59;
    int _if_cond_73;
    int _for_it_62;
    int _for_it_99;
    int _for_it_100;
    int _for_it_101;
    int _for_it_47;
    int _for_it_85;
    int _for_it_78;
    int _if_cond_62;
    int _for_it_55;
    double _if_cond_63;
    int _for_it_56;
    int _for_it_107;
    int _if_cond_26;
    int _for_it_41;
    int _if_cond_46;
    int _for_it_49;
    int _for_it_50;
    int _if_cond_23;
    int _for_it_38;
    int _for_it_46;
    int tmp_index_990;
    double zsigk;
    double _if_cond_39;
    double _if_cond_42;
    int _for_it_48;
    double _if_cond_12;
    double _if_cond_14;
    int _for_it_29;
    int _for_it_54;
    int _for_it_28;
    double _if_cond_64;
    int _for_it_57;
    int _if_cond_68;
    double _if_cond_69;
    int _if_cond_81;
    int _if_cond_82;
    int _for_it_115;
    int _for_it_45;
    double _if_cond_29;
    int _for_it_34;
    int _if_cond_21;
    int _for_it_35;
    int _for_it_36;
    int _for_it_16;
    int _for_it_17;
    int _for_it_13;
    int _for_it_14;
    int _for_it_15;
    int _if_cond_3;
    int _if_cond_4;
    int _for_it_11;
    int _for_it_12;

    {
        {
            double zepsilon_out;

            ///////////////////
            // Tasklet code (T_l398_c398)
            zepsilon_out = (100.0 * 2.220446049250313e-16);
            ///////////////////

            __state->__6_zepsilon = zepsilon_out;
        }
        {
            double ptsphy_var_5_0_in = ptsphy_var_5[0];
            double zqtmst_out;

            ///////////////////
            // Tasklet code (T_l403_c403)
            zqtmst_out = (1.0 / ptsphy_var_5_0_in);
            ///////////////////

            __state->__6_zqtmst = zqtmst_out;
        }
    }

    {
        {
            double ydcst_0_in_rd = v_ydcst_rd[0];
            double ydcst_1_in_rcpd = v_ydcst_rcpd[0];
            double zrdcp_out;

            ///////////////////
            // Tasklet code (T_l405_c405)
            zrdcp_out = (ydcst_0_in_rd / ydcst_1_in_rcpd);
            ///////////////////

            __state->__6_zrdcp = zrdcp_out;
        }
        {
            double zepsec_out;

            ///////////////////
            // Tasklet code (T_l407_c407)
            zepsec_out = 1e-14;
            ///////////////////

            __state->__6_zepsec = zepsec_out;
        }
    }

    {
        double* v_ydecldp_var_47_rvice;
        v_ydecldp_var_47_rvice = (double*)(&(ydecldp_var_47->rvice));
        double* v_ydecldp_var_47_rvrain;
        v_ydecldp_var_47_rvrain = (double*)(&(ydecldp_var_47->rvrain));
        double* v_ydecldp_var_47_rvsnow;
        v_ydecldp_var_47_rvsnow = (double*)(&(ydecldp_var_47->rvsnow));

        {
            double ydcst_0_in_rg = v_ydcst_rg[0];
            double zrg_r_out;

            ///////////////////
            // Tasklet code (T_l408_c408)
            zrg_r_out = (1.0 / ydcst_0_in_rg);
            ///////////////////

            __state->__6_zrg_r = zrg_r_out;
        }
        {
            double ydthf_0_in_ralsdcp = v_ydthf_ralsdcp[0];
            double ydthf_1_in_ralvdcp = v_ydthf_ralvdcp[0];
            double zrldcp_out;

            ///////////////////
            // Tasklet code (T_l409_c409)
            zrldcp_out = (1.0 / (ydthf_0_in_ralsdcp - ydthf_1_in_ralvdcp));
            ///////////////////

            __state->__6_zrldcp = zrldcp_out;
        }
        {
            int iphase_out_0;

            ///////////////////
            // Tasklet code (T_l410_c410)
            iphase_out_0 = 0;
            ///////////////////

            __state->__6_iphase[4] = iphase_out_0;
        }
        {
            int iphase_out_0;

            ///////////////////
            // Tasklet code (T_l411_c411)
            iphase_out_0 = 1;
            ///////////////////

            __state->__6_iphase[0] = iphase_out_0;
        }
        {
            int iphase_out_0;

            ///////////////////
            // Tasklet code (T_l412_c412)
            iphase_out_0 = 1;
            ///////////////////

            __state->__6_iphase[2] = iphase_out_0;
        }
        {
            int iphase_out_0;

            ///////////////////
            // Tasklet code (T_l413_c413)
            iphase_out_0 = 2;
            ///////////////////

            __state->__6_iphase[1] = iphase_out_0;
        }
        {
            int iphase_out_0;

            ///////////////////
            // Tasklet code (T_l414_c414)
            iphase_out_0 = 2;
            ///////////////////

            __state->__6_iphase[3] = iphase_out_0;
        }
        {
            int imelt_out_0;

            ///////////////////
            // Tasklet code (T_l415_c415)
            imelt_out_0 = -99;
            ///////////////////

            __state->__6_imelt[4] = imelt_out_0;
        }
        {
            int imelt_out_0;

            ///////////////////
            // Tasklet code (T_l416_c416)
            imelt_out_0 = 2;
            ///////////////////

            __state->__6_imelt[0] = imelt_out_0;
        }
        {
            int imelt_out_0;

            ///////////////////
            // Tasklet code (T_l417_c417)
            imelt_out_0 = 4;
            ///////////////////

            __state->__6_imelt[2] = imelt_out_0;
        }
        {
            int imelt_out_0;

            ///////////////////
            // Tasklet code (T_l418_c418)
            imelt_out_0 = 3;
            ///////////////////

            __state->__6_imelt[1] = imelt_out_0;
        }
        {
            int imelt_out_0;

            ///////////////////
            // Tasklet code (T_l419_c419)
            imelt_out_0 = 3;
            ///////////////////

            __state->__6_imelt[3] = imelt_out_0;
        }
        {
#pragma omp parallel for
            for (auto _for_it_2 = 1; _for_it_2 < 5; _for_it_2 += 1) {
                loop_body_6_2_28(__state, &klev[0], &ptendency_loc_cld[((sym_klev * sym_klon) * (_for_it_2 - 1))], icend, sym_klev, sym_klon);
            }
        }
        {
#pragma omp parallel for
            for (auto _for_it_0 = 1; _for_it_0 < (sym_klev + 1); _for_it_0 += 1) {
                loop_body_6_2_21(
                    __state, &ptendency_loc_a[(sym_klon * (_for_it_0 - 1))], &ptendency_loc_q[(sym_klon * (_for_it_0 - 1))], &ptendency_loc_t[(sym_klon * (_for_it_0 - 1))], icend, sym_klon);
            }
        }
        {
            double zvqx_out_0;

            ///////////////////
            // Tasklet code (T_l434_c434)
            zvqx_out_0 = 0.0;
            ///////////////////

            __state->__6_zvqx[4] = zvqx_out_0;
        }
        {
            double zvqx_out_0;

            ///////////////////
            // Tasklet code (T_l435_c435)
            zvqx_out_0 = 0.0;
            ///////////////////

            __state->__6_zvqx[0] = zvqx_out_0;
        }
        {
            double ydecldp_var_47_0_in_rvice = v_ydecldp_var_47_rvice[0];
            double zvqx_out_0;

            ///////////////////
            // Tasklet code (T_l436_c436)
            zvqx_out_0 = ydecldp_var_47_0_in_rvice;
            ///////////////////

            __state->__6_zvqx[1] = zvqx_out_0;
        }
        {
            double ydecldp_var_47_0_in_rvrain = v_ydecldp_var_47_rvrain[0];
            double zvqx_out_0;

            ///////////////////
            // Tasklet code (T_l437_c437)
            zvqx_out_0 = ydecldp_var_47_0_in_rvrain;
            ///////////////////

            __state->__6_zvqx[2] = zvqx_out_0;
        }
        {
            double ydecldp_var_47_0_in_rvsnow = v_ydecldp_var_47_rvsnow[0];
            double zvqx_out_0;

            ///////////////////
            // Tasklet code (T_l438_c438)
            zvqx_out_0 = ydecldp_var_47_0_in_rvsnow;
            ///////////////////

            __state->__6_zvqx[3] = zvqx_out_0;
        }
        {
#pragma omp parallel for
            for (auto tmp_parfor_0 = 1; tmp_parfor_0 < 6; tmp_parfor_0 += 1) {
                loop_body_6_2_42(__state, &__state->__6_llfall[(tmp_parfor_0 - 1)]);
            }
        }
    }

    {
        {
#pragma omp parallel for
            for (auto _for_it_5 = 1; _for_it_5 < 6; _for_it_5 += 1) {
                loop_body_6_4_0(__state, &__state->__6_zvqx[(_for_it_5 - 1)], &__state->__6_llfall[(_for_it_5 - 1)]);
            }
        }
    }

    {
        {
            int llfall_out_0;

            ///////////////////
            // Tasklet code (T_l443_c443)
            llfall_out_0 = 0;
            ///////////////////

            __state->__6_llfall[1] = llfall_out_0;
        }
        {
#pragma omp parallel for
            for (auto _for_it_6 = 1; _for_it_6 < (sym_klev + 1); _for_it_6 += 1) {
                loop_body_6_3_2(
                    __state, &pa_var_27[(sym_klon * (_for_it_6 - 1))], &pq_var_7[(sym_klon * (_for_it_6 - 1))], &pt_var_6[(sym_klon * (_for_it_6 - 1))], &ptendency_tmp_a[(sym_klon * (_for_it_6 - 1))],
                    &ptendency_tmp_q[(sym_klon * (_for_it_6 - 1))], &ptendency_tmp_t[(sym_klon * (_for_it_6 - 1))], &ptsphy_var_5[0], &__state->__6_za[(sym_klon * (_for_it_6 - 1))],
                    &__state->__6_zaorig[(sym_klon * (_for_it_6 - 1))], &__state->__6_zqx[(((4 * sym_klev) * sym_klon) + (sym_klon * (_for_it_6 - 1)))],
                    &__state->__6_zqx0[(((4 * sym_klev) * sym_klon) + (sym_klon * (_for_it_6 - 1)))], &__state->__6_ztp1[(sym_klon * (_for_it_6 - 1))], icend, sym_klev, sym_klon);
            }
        }
        {
#pragma omp parallel for
            for (auto _for_it_8 = 1; _for_it_8 < 5; _for_it_8 += 1) {
                loop_body_6_3_18(
                    __state, &klev[0], &pclv_var_29[((sym_klev * sym_klon) * (_for_it_8 - 1))], &ptendency_tmp_cld[((sym_klev * sym_klon) * (_for_it_8 - 1))], &ptsphy_var_5[0],
                    &__state->__6_zqx[((sym_klev * sym_klon) * (_for_it_8 - 1))], &__state->__6_zqx0[((sym_klev * sym_klon) * (_for_it_8 - 1))], icend, sym_klev, sym_klon);
            }
        }
        {
#pragma omp parallel for
            for (auto tmp_parfor_3 = 1; tmp_parfor_3 < 6; tmp_parfor_3 += 1) {
                loop_body_6_3_23(__state, &__state->__6_zpfplsx[((sym_klon * (sym_klev + 1)) * (tmp_parfor_3 - 1))], sym_klev, sym_klon);
            }
        }
        {
#pragma omp parallel for
            for (auto tmp_parfor_6 = 1; tmp_parfor_6 < 6; tmp_parfor_6 += 1) {
                loop_body_6_3_27(__state, &__state->__6_zqxn2d[((sym_klev * sym_klon) * (tmp_parfor_6 - 1))], sym_klev, sym_klon);
            }
        }
        {
#pragma omp parallel for
            for (auto tmp_parfor_9 = 1; tmp_parfor_9 < 6; tmp_parfor_9 += 1) {
                loop_body_6_3_31(__state, &__state->__6_zlneg[((sym_klev * sym_klon) * (tmp_parfor_9 - 1))], sym_klev, sym_klon);
            }
        }
        {
#pragma omp parallel for
            for (auto tmp_parfor_10 = 1; tmp_parfor_10 < (sym_klon + 1); tmp_parfor_10 += 1) {
                loop_body_6_3_35(__state, &prainfrac_toprfz_var_32[(tmp_parfor_10 - 1)]);
            }
        }
        {
#pragma omp parallel for
            for (auto tmp_parfor_11 = 1; tmp_parfor_11 < (sym_klon + 1); tmp_parfor_11 += 1) {
                loop_body_6_3_39(__state, &__state->__6_llrainliq[(tmp_parfor_11 - 1)]);
            }
        }
    }

    for (_for_it_11 = 1; (_for_it_11 <= sym_klev); _for_it_11 = (_for_it_11 + 1)) {
        for (_for_it_12 = 1; (_for_it_12 <= icend); _for_it_12 = (_for_it_12 + 1)) {
            {
                {
                    double ydecldp_var_47_0_in_rlmin = v_ydecldp_var_47_rlmin[0];
                    double ydecldp_var_47_1_in_ramin = v_ydecldp_var_47_ramin[0];
                    double za_0_in_0 = __state->__6_za[((_for_it_12 + (sym_klon * (_for_it_11 - 1))) - 1)];
                    double zqx_0_in_0 = __state->__6_zqx[((_for_it_12 + (sym_klon * (_for_it_11 - 1))) - 1)];
                    double zqx_1_in_0 = __state->__6_zqx[(((_for_it_12 + (sym_klev * sym_klon)) + (sym_klon * (_for_it_11 - 1))) - 1)];
                    double _if_cond_1_out;

                    ///////////////////
                    // Tasklet code (T_l0_c0)
                    _if_cond_1_out = (((zqx_0_in_0 + zqx_1_in_0) < ydecldp_var_47_0_in_rlmin) || (za_0_in_0 < ydecldp_var_47_1_in_ramin));
                    ///////////////////

                    __state->__6__if_cond_1 = _if_cond_1_out;
                }
            }
            if ((__state->__6__if_cond_1 == 1)) {
                {
                    {
                        double zlneg_0_in_0 = __state->__6_zlneg[((_for_it_12 + (sym_klon * (_for_it_11 - 1))) - 1)];
                        double zqx_0_in_0 = __state->__6_zqx[((_for_it_12 + (sym_klon * (_for_it_11 - 1))) - 1)];
                        double zlneg_out_0;

                        ///////////////////
                        // Tasklet code (T_l469_c469)
                        zlneg_out_0 = (zlneg_0_in_0 + zqx_0_in_0);
                        ///////////////////

                        __state->__6_zlneg[((_for_it_12 + (sym_klon * (_for_it_11 - 1))) - 1)] = zlneg_out_0;
                    }
                    {
                        double zqx_0_in_0 = __state->__6_zqx[(((_for_it_12 + ((4 * sym_klev) * sym_klon)) + (sym_klon * (_for_it_11 - 1))) - 1)];
                        double zqx_1_in_0 = __state->__6_zqx[((_for_it_12 + (sym_klon * (_for_it_11 - 1))) - 1)];
                        double zqx_out_0;

                        ///////////////////
                        // Tasklet code (T_l473_c473)
                        zqx_out_0 = (zqx_0_in_0 + zqx_1_in_0);
                        ///////////////////

                        __state->__6_zqx[(((_for_it_12 + ((4 * sym_klev) * sym_klon)) + (sym_klon * (_for_it_11 - 1))) - 1)] = zqx_out_0;
                    }
                    {
                        double zqtmst_0_in = __state->__6_zqtmst;
                        double zqx_0_in_0 = __state->__6_zqx[((_for_it_12 + (sym_klon * (_for_it_11 - 1))) - 1)];
                        double zqadj_out;

                        ///////////////////
                        // Tasklet code (T_l470_c470)
                        zqadj_out = (zqx_0_in_0 * zqtmst_0_in);
                        ///////////////////

                        __state->__6_zqadj = zqadj_out;
                    }
                    {
                        double ptendency_loc_q_0_in_0 = ptendency_loc_q[((_for_it_12 + (sym_klon * (_for_it_11 - 1))) - 1)];
                        double zqadj_0_in = __state->__6_zqadj;
                        double ptendency_loc_q_out_0;

                        ///////////////////
                        // Tasklet code (T_l471_c471)
                        ptendency_loc_q_out_0 = (ptendency_loc_q_0_in_0 + zqadj_0_in);
                        ///////////////////

                        ptendency_loc_q[((_for_it_12 + (sym_klon * (_for_it_11 - 1))) - 1)] = ptendency_loc_q_out_0;
                    }
                    {
                        double ptendency_loc_t_0_in_0 = ptendency_loc_t[((_for_it_12 + (sym_klon * (_for_it_11 - 1))) - 1)];
                        double ydthf_0_in_ralvdcp = v_ydthf_ralvdcp[0];
                        double zqadj_0_in = __state->__6_zqadj;
                        double ptendency_loc_t_out_0;

                        ///////////////////
                        // Tasklet code (T_l472_c472)
                        ptendency_loc_t_out_0 = (ptendency_loc_t_0_in_0 - (ydthf_0_in_ralvdcp * zqadj_0_in));
                        ///////////////////

                        ptendency_loc_t[((_for_it_12 + (sym_klon * (_for_it_11 - 1))) - 1)] = ptendency_loc_t_out_0;
                    }
                }
                {
                    {
                        double zqx_out_0;

                        ///////////////////
                        // Tasklet code (T_l474_c474)
                        zqx_out_0 = 0.0;
                        ///////////////////

                        __state->__6_zqx[((_for_it_12 + (sym_klon * (_for_it_11 - 1))) - 1)] = zqx_out_0;
                    }
                    {
                        double zlneg_0_in_0 = __state->__6_zlneg[(((_for_it_12 + (sym_klev * sym_klon)) + (sym_klon * (_for_it_11 - 1))) - 1)];
                        double zqx_0_in_0 = __state->__6_zqx[(((_for_it_12 + (sym_klev * sym_klon)) + (sym_klon * (_for_it_11 - 1))) - 1)];
                        double zlneg_out_0;

                        ///////////////////
                        // Tasklet code (T_l475_c475)
                        zlneg_out_0 = (zlneg_0_in_0 + zqx_0_in_0);
                        ///////////////////

                        __state->__6_zlneg[(((_for_it_12 + (sym_klev * sym_klon)) + (sym_klon * (_for_it_11 - 1))) - 1)] = zlneg_out_0;
                    }
                    {
                        double zqtmst_0_in = __state->__6_zqtmst;
                        double zqx_0_in_0 = __state->__6_zqx[(((_for_it_12 + (sym_klev * sym_klon)) + (sym_klon * (_for_it_11 - 1))) - 1)];
                        double zqadj_out;

                        ///////////////////
                        // Tasklet code (T_l476_c476)
                        zqadj_out = (zqx_0_in_0 * zqtmst_0_in);
                        ///////////////////

                        __state->__6_zqadj = zqadj_out;
                    }
                    {
                        double ptendency_loc_q_0_in_0 = ptendency_loc_q[((_for_it_12 + (sym_klon * (_for_it_11 - 1))) - 1)];
                        double zqadj_0_in = __state->__6_zqadj;
                        double ptendency_loc_q_out_0;

                        ///////////////////
                        // Tasklet code (T_l477_c477)
                        ptendency_loc_q_out_0 = (ptendency_loc_q_0_in_0 + zqadj_0_in);
                        ///////////////////

                        ptendency_loc_q[((_for_it_12 + (sym_klon * (_for_it_11 - 1))) - 1)] = ptendency_loc_q_out_0;
                    }
                    {
                        double ptendency_loc_t_0_in_0 = ptendency_loc_t[((_for_it_12 + (sym_klon * (_for_it_11 - 1))) - 1)];
                        double ydthf_0_in_ralsdcp = v_ydthf_ralsdcp[0];
                        double zqadj_0_in = __state->__6_zqadj;
                        double ptendency_loc_t_out_0;

                        ///////////////////
                        // Tasklet code (T_l478_c478)
                        ptendency_loc_t_out_0 = (ptendency_loc_t_0_in_0 - (ydthf_0_in_ralsdcp * zqadj_0_in));
                        ///////////////////

                        ptendency_loc_t[((_for_it_12 + (sym_klon * (_for_it_11 - 1))) - 1)] = ptendency_loc_t_out_0;
                    }
                }
                {
                    {
                        double zqx_0_in_0 = __state->__6_zqx[(((_for_it_12 + ((4 * sym_klev) * sym_klon)) + (sym_klon * (_for_it_11 - 1))) - 1)];
                        double zqx_1_in_0 = __state->__6_zqx[(((_for_it_12 + (sym_klev * sym_klon)) + (sym_klon * (_for_it_11 - 1))) - 1)];
                        double zqx_out_0;

                        ///////////////////
                        // Tasklet code (T_l479_c479)
                        zqx_out_0 = (zqx_0_in_0 + zqx_1_in_0);
                        ///////////////////

                        __state->__6_zqx[(((_for_it_12 + ((4 * sym_klev) * sym_klon)) + (sym_klon * (_for_it_11 - 1))) - 1)] = zqx_out_0;
                    }
                }
                {
                    {
                        double zqx_out_0;

                        ///////////////////
                        // Tasklet code (T_l480_c480)
                        zqx_out_0 = 0.0;
                        ///////////////////

                        __state->__6_zqx[(((_for_it_12 + (sym_klev * sym_klon)) + (sym_klon * (_for_it_11 - 1))) - 1)] = zqx_out_0;
                    }
                    {
                        double za_out_0;

                        ///////////////////
                        // Tasklet code (T_l481_c481)
                        za_out_0 = 0.0;
                        ///////////////////

                        __state->__6_za[((_for_it_12 + (sym_klon * (_for_it_11 - 1))) - 1)] = za_out_0;
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
                        double ydecldp_var_47_0_in_rlmin = v_ydecldp_var_47_rlmin[0];
                        double zqx_0_in_0 = __state->__6_zqx[(((_for_it_15 + ((sym_klev * sym_klon) * (_for_it_13 - 1))) + (sym_klon * (_for_it_14 - 1))) - 1)];
                        double _if_cond_2_out;

                        ///////////////////
                        // Tasklet code (T_l0_c0)
                        _if_cond_2_out = (zqx_0_in_0 < ydecldp_var_47_0_in_rlmin);
                        ///////////////////

                        __state->__6__if_cond_2 = _if_cond_2_out;
                    }
                }
                if ((__state->__6__if_cond_2 == 1)) {
                    _if_cond_3 = (__state->__6_iphase[(_for_it_13 - 1)] == 1);
                    {
                        {
                            double zlneg_0_in_0 = __state->__6_zlneg[(((_for_it_15 + ((sym_klev * sym_klon) * (_for_it_13 - 1))) + (sym_klon * (_for_it_14 - 1))) - 1)];
                            double zqx_0_in_0 = __state->__6_zqx[(((_for_it_15 + ((sym_klev * sym_klon) * (_for_it_13 - 1))) + (sym_klon * (_for_it_14 - 1))) - 1)];
                            double zlneg_out_0;

                            ///////////////////
                            // Tasklet code (T_l489_c489)
                            zlneg_out_0 = (zlneg_0_in_0 + zqx_0_in_0);
                            ///////////////////

                            __state->__6_zlneg[(((_for_it_15 + ((sym_klev * sym_klon) * (_for_it_13 - 1))) + (sym_klon * (_for_it_14 - 1))) - 1)] = zlneg_out_0;
                        }
                        {
                            double zqtmst_0_in = __state->__6_zqtmst;
                            double zqx_0_in_0 = __state->__6_zqx[(((_for_it_15 + ((sym_klev * sym_klon) * (_for_it_13 - 1))) + (sym_klon * (_for_it_14 - 1))) - 1)];
                            double zqadj_out;

                            ///////////////////
                            // Tasklet code (T_l490_c490)
                            zqadj_out = (zqx_0_in_0 * zqtmst_0_in);
                            ///////////////////

                            __state->__6_zqadj = zqadj_out;
                        }
                        {
                            double ptendency_loc_q_0_in_0 = ptendency_loc_q[((_for_it_15 + (sym_klon * (_for_it_14 - 1))) - 1)];
                            double zqadj_0_in = __state->__6_zqadj;
                            double ptendency_loc_q_out_0;

                            ///////////////////
                            // Tasklet code (T_l491_c491)
                            ptendency_loc_q_out_0 = (ptendency_loc_q_0_in_0 + zqadj_0_in);
                            ///////////////////

                            ptendency_loc_q[((_for_it_15 + (sym_klon * (_for_it_14 - 1))) - 1)] = ptendency_loc_q_out_0;
                        }
                    }
                    if ((_if_cond_3 == 1)) {
                        {
                            {
                                double ptendency_loc_t_0_in_0 = ptendency_loc_t[((_for_it_15 + (sym_klon * (_for_it_14 - 1))) - 1)];
                                double ydthf_0_in_ralvdcp = v_ydthf_ralvdcp[0];
                                double zqadj_0_in = __state->__6_zqadj;
                                double ptendency_loc_t_out_0;

                                ///////////////////
                                // Tasklet code (T_l492_c492)
                                ptendency_loc_t_out_0 = (ptendency_loc_t_0_in_0 - (ydthf_0_in_ralvdcp * zqadj_0_in));
                                ///////////////////

                                ptendency_loc_t[((_for_it_15 + (sym_klon * (_for_it_14 - 1))) - 1)] = ptendency_loc_t_out_0;
                            }
                        }
                    }
                    _if_cond_4 = (__state->__6_iphase[(_for_it_13 - 1)] == 2);
                    if ((_if_cond_4 == 1)) {
                        {
                            {
                                double ptendency_loc_t_0_in_0 = ptendency_loc_t[((_for_it_15 + (sym_klon * (_for_it_14 - 1))) - 1)];
                                double ydthf_0_in_ralsdcp = v_ydthf_ralsdcp[0];
                                double zqadj_0_in = __state->__6_zqadj;
                                double ptendency_loc_t_out_0;

                                ///////////////////
                                // Tasklet code (T_l493_c493)
                                ptendency_loc_t_out_0 = (ptendency_loc_t_0_in_0 - (ydthf_0_in_ralsdcp * zqadj_0_in));
                                ///////////////////

                                ptendency_loc_t[((_for_it_15 + (sym_klon * (_for_it_14 - 1))) - 1)] = ptendency_loc_t_out_0;
                            }
                        }
                    }
                    {
                        {
                            double zqx_0_in_0 = __state->__6_zqx[(((_for_it_15 + ((4 * sym_klev) * sym_klon)) + (sym_klon * (_for_it_14 - 1))) - 1)];
                            double zqx_1_in_0 = __state->__6_zqx[(((_for_it_15 + ((sym_klev * sym_klon) * (_for_it_13 - 1))) + (sym_klon * (_for_it_14 - 1))) - 1)];
                            double zqx_out_0;

                            ///////////////////
                            // Tasklet code (T_l494_c494)
                            zqx_out_0 = (zqx_0_in_0 + zqx_1_in_0);
                            ///////////////////

                            __state->__6_zqx[(((_for_it_15 + ((4 * sym_klev) * sym_klon)) + (sym_klon * (_for_it_14 - 1))) - 1)] = zqx_out_0;
                        }
                    }
                    {
                        {
                            double zqx_out_0;

                            ///////////////////
                            // Tasklet code (T_l495_c495)
                            zqx_out_0 = 0.0;
                            ///////////////////

                            __state->__6_zqx[(((_for_it_15 + ((sym_klev * sym_klon) * (_for_it_13 - 1))) + (sym_klon * (_for_it_14 - 1))) - 1)] = zqx_out_0;
                        }
                    }
                }
            }
        }
    }

    for (_for_it_16 = 1; (_for_it_16 <= sym_klev); _for_it_16 = (_for_it_16 + 1)) {
        for (_for_it_17 = 1; (_for_it_17 <= icend); _for_it_17 = (_for_it_17 + 1)) {
            {
                {
                    double ztp1_0_in_0 = __state->__6_ztp1[((_for_it_17 + (sym_klon * (_for_it_16 - 1))) - 1)];
                    double oka_out;

                    ///////////////////
                    // Tasklet code (T_l502_c502)
                    oka_out = ztp1_0_in_0;
                    ///////////////////

                    __state->__6_oka = oka_out;
                }
                {
                    double oka_0_in = __state->__6_oka;
                    double ydthf_0_in_rtwat = v_ydthf_rtwat[0];
                    double tmp_call_17_out;

                    ///////////////////
                    // Tasklet code (T_l503_c503)
                    tmp_call_17_out = min(ydthf_0_in_rtwat, oka_0_in);
                    ///////////////////

                    __state->__6_tmp_call_17 = tmp_call_17_out;
                }
                {
                    double tmp_call_17_0_in = __state->__6_tmp_call_17;
                    double ydthf_0_in_rtice = v_ydthf_rtice[0];
                    double tmp_call_14_out;

                    ///////////////////
                    // Tasklet code (T_l503_c503)
                    tmp_call_14_out = max(ydthf_0_in_rtice, tmp_call_17_0_in);
                    ///////////////////

                    __state->__6_tmp_call_14 = tmp_call_14_out;
                }
            }
            {
                {
                    double tmp_call_14_0_in = __state->__6_tmp_call_14;
                    double ydthf_0_in_rtice = v_ydthf_rtice[0];
                    double ydthf_1_in_rtwat_rtice_r = v_ydthf_rtwat_rtice_r[0];
                    double tmp_arg_0_out;

                    ///////////////////
                    // Tasklet code (T_l503_c503)
                    tmp_arg_0_out = ((tmp_call_14_0_in - ydthf_0_in_rtice) * ydthf_1_in_rtwat_rtice_r);
                    ///////////////////

                    __state->__6_tmp_arg_0 = tmp_arg_0_out;
                }
                {
                    double tmp_arg_0_0_in = __state->__6_tmp_arg_0;
                    double tmp_call_6_out;

                    ///////////////////
                    // Tasklet code (T_l503_c503)
                    tmp_call_6_out = (dace::math::ipow(tmp_arg_0_0_in, 2));
                    ///////////////////

                    __state->__6_tmp_call_6 = tmp_call_6_out;
                }
                {
                    double tmp_call_6_0_in = __state->__6_tmp_call_6;
                    double tmp_call_0_out;

                    ///////////////////
                    // Tasklet code (T_l503_c503)
                    tmp_call_0_out = min(1.0, tmp_call_6_0_in);
                    ///////////////////

                    __state->__6_tmp_call_0 = tmp_call_0_out;
                }
                {
                    double tmp_call_0_0_in = __state->__6_tmp_call_0;
                    double zfoealfa_out_0;

                    ///////////////////
                    // Tasklet code (T_l503_c503)
                    zfoealfa_out_0 = tmp_call_0_0_in;
                    ///////////////////

                    __state->__6_zfoealfa[((_for_it_17 + (sym_klon * (_for_it_16 - 1))) - 1)] = zfoealfa_out_0;
                }
            }
            {
                {
                    double oka_0_in = __state->__6_oka;
                    double ydthf_0_in_rtwat = v_ydthf_rtwat[0];
                    double tmp_call_20_out;

                    ///////////////////
                    // Tasklet code (T_l504_c504)
                    tmp_call_20_out = min(ydthf_0_in_rtwat, oka_0_in);
                    ///////////////////

                    __state->__6_tmp_call_20 = tmp_call_20_out;
                }
                {
                    double tmp_call_20_0_in = __state->__6_tmp_call_20;
                    double ydthf_0_in_rtice = v_ydthf_rtice[0];
                    double tmp_call_18_out;

                    ///////////////////
                    // Tasklet code (T_l504_c504)
                    tmp_call_18_out = max(ydthf_0_in_rtice, tmp_call_20_0_in);
                    ///////////////////

                    __state->__6_tmp_call_18 = tmp_call_18_out;
                }
                {
                    double oka_0_in = __state->__6_oka;
                    double oka_1_in = __state->__6_oka;
                    double ydcst_0_in_rtt = v_ydcst_rtt[0];
                    double ydthf_0_in_r3ies = v_ydthf_r3ies[0];
                    double ydthf_1_in_r4ies = v_ydthf_r4ies[0];
                    double tmp_arg_1_out;

                    ///////////////////
                    // Tasklet code (T_l504_c504)
                    tmp_arg_1_out = ((ydthf_0_in_r3ies * (oka_0_in - ydcst_0_in_rtt)) / (oka_1_in - ydthf_1_in_r4ies));
                    ///////////////////

                    __state->__6_tmp_arg_1 = tmp_arg_1_out;
                }
                {
                    double tmp_arg_1_0_in = __state->__6_tmp_arg_1;
                    double tmp_call_10_out;

                    ///////////////////
                    // Tasklet code (T_l504_c504)
                    tmp_call_10_out = exp(tmp_arg_1_0_in);
                    ///////////////////

                    __state->__6_tmp_call_10 = tmp_call_10_out;
                }
            }
            {
                {
                    double tmp_call_18_0_in = __state->__6_tmp_call_18;
                    double ydthf_0_in_rtice = v_ydthf_rtice[0];
                    double ydthf_1_in_rtwat_rtice_r = v_ydthf_rtwat_rtice_r[0];
                    double tmp_arg_2_out;

                    ///////////////////
                    // Tasklet code (T_l504_c504)
                    tmp_arg_2_out = ((tmp_call_18_0_in - ydthf_0_in_rtice) * ydthf_1_in_rtwat_rtice_r);
                    ///////////////////

                    __state->__6_tmp_arg_2 = tmp_arg_2_out;
                }
                {
                    double tmp_arg_2_0_in = __state->__6_tmp_arg_2;
                    double tmp_call_15_out;

                    ///////////////////
                    // Tasklet code (T_l504_c504)
                    tmp_call_15_out = (dace::math::ipow(tmp_arg_2_0_in, 2));
                    ///////////////////

                    __state->__6_tmp_call_15 = tmp_call_15_out;
                }
                {
                    double tmp_call_15_0_in = __state->__6_tmp_call_15;
                    double tmp_call_9_out;

                    ///////////////////
                    // Tasklet code (T_l504_c504)
                    tmp_call_9_out = min(1.0, tmp_call_15_0_in);
                    ///////////////////

                    __state->__6_tmp_call_9 = tmp_call_9_out;
                }
            }
            {
                {
                    double oka_0_in = __state->__6_oka;
                    double ydthf_0_in_rtwat = v_ydthf_rtwat[0];
                    double tmp_call_21_out;

                    ///////////////////
                    // Tasklet code (T_l504_c504)
                    tmp_call_21_out = min(ydthf_0_in_rtwat, oka_0_in);
                    ///////////////////

                    __state->__6_tmp_call_21 = tmp_call_21_out;
                }
                {
                    double tmp_call_21_0_in = __state->__6_tmp_call_21;
                    double ydthf_0_in_rtice = v_ydthf_rtice[0];
                    double tmp_call_19_out;

                    ///////////////////
                    // Tasklet code (T_l504_c504)
                    tmp_call_19_out = max(ydthf_0_in_rtice, tmp_call_21_0_in);
                    ///////////////////

                    __state->__6_tmp_call_19 = tmp_call_19_out;
                }
                {
                    double oka_0_in = __state->__6_oka;
                    double oka_1_in = __state->__6_oka;
                    double ydcst_0_in_rtt = v_ydcst_rtt[0];
                    double ydthf_0_in_r3les = v_ydthf_r3les[0];
                    double ydthf_1_in_r4les = v_ydthf_r4les[0];
                    double tmp_arg_3_out;

                    ///////////////////
                    // Tasklet code (T_l504_c504)
                    tmp_arg_3_out = ((ydthf_0_in_r3les * (oka_0_in - ydcst_0_in_rtt)) / (oka_1_in - ydthf_1_in_r4les));
                    ///////////////////

                    __state->__6_tmp_arg_3 = tmp_arg_3_out;
                }
                {
                    double tmp_arg_3_0_in = __state->__6_tmp_arg_3;
                    double tmp_call_8_out;

                    ///////////////////
                    // Tasklet code (T_l504_c504)
                    tmp_call_8_out = exp(tmp_arg_3_0_in);
                    ///////////////////

                    __state->__6_tmp_call_8 = tmp_call_8_out;
                }
            }
            {
                {
                    double tmp_call_19_0_in = __state->__6_tmp_call_19;
                    double ydthf_0_in_rtice = v_ydthf_rtice[0];
                    double ydthf_1_in_rtwat_rtice_r = v_ydthf_rtwat_rtice_r[0];
                    double tmp_arg_4_out;

                    ///////////////////
                    // Tasklet code (T_l504_c504)
                    tmp_arg_4_out = ((tmp_call_19_0_in - ydthf_0_in_rtice) * ydthf_1_in_rtwat_rtice_r);
                    ///////////////////

                    __state->__6_tmp_arg_4 = tmp_arg_4_out;
                }
                {
                    double tmp_arg_4_0_in = __state->__6_tmp_arg_4;
                    double tmp_call_16_out;

                    ///////////////////
                    // Tasklet code (T_l504_c504)
                    tmp_call_16_out = (dace::math::ipow(tmp_arg_4_0_in, 2));
                    ///////////////////

                    __state->__6_tmp_call_16 = tmp_call_16_out;
                }
                {
                    double tmp_call_16_0_in = __state->__6_tmp_call_16;
                    double tmp_call_7_out;

                    ///////////////////
                    // Tasklet code (T_l504_c504)
                    tmp_call_7_out = min(1.0, tmp_call_16_0_in);
                    ///////////////////

                    __state->__6_tmp_call_7 = tmp_call_7_out;
                }
                {
                    double pap_var_17_0_in_0 = pap_var_17[((_for_it_17 + (sym_klon * (_for_it_16 - 1))) - 1)];
                    double tmp_call_10_0_in = __state->__6_tmp_call_10;
                    double tmp_call_7_0_in = __state->__6_tmp_call_7;
                    double tmp_call_8_0_in = __state->__6_tmp_call_8;
                    double tmp_call_9_0_in = __state->__6_tmp_call_9;
                    double ydthf_0_in_r2es = v_ydthf_r2es[0];
                    double tmp_arg_5_out;

                    ///////////////////
                    // Tasklet code (T_l504_c504)
                    tmp_arg_5_out = ((ydthf_0_in_r2es * ((tmp_call_7_0_in * tmp_call_8_0_in) + ((1.0 - tmp_call_9_0_in) * tmp_call_10_0_in))) / pap_var_17_0_in_0);
                    ///////////////////

                    __state->__6_tmp_arg_5 = tmp_arg_5_out;
                }
                {
                    double tmp_arg_5_0_in = __state->__6_tmp_arg_5;
                    double tmp_call_1_out;

                    ///////////////////
                    // Tasklet code (T_l504_c504)
                    tmp_call_1_out = min(tmp_arg_5_0_in, 0.5);
                    ///////////////////

                    __state->__6_tmp_call_1 = tmp_call_1_out;
                }
                {
                    double tmp_call_1_0_in = __state->__6_tmp_call_1;
                    double zfoeewmt_out_0;

                    ///////////////////
                    // Tasklet code (T_l504_c504)
                    zfoeewmt_out_0 = tmp_call_1_0_in;
                    ///////////////////

                    __state->__6_zfoeewmt[((_for_it_17 + (sym_klon * (_for_it_16 - 1))) - 1)] = zfoeewmt_out_0;
                }
                {
                    double zfoeewmt_0_in_0 = __state->__6_zfoeewmt[((_for_it_17 + (sym_klon * (_for_it_16 - 1))) - 1)];
                    double zqsmix_out_0;

                    ///////////////////
                    // Tasklet code (T_l505_c505)
                    zqsmix_out_0 = zfoeewmt_0_in_0;
                    ///////////////////

                    __state->__6_zqsmix[((_for_it_17 + (sym_klon * (_for_it_16 - 1))) - 1)] = zqsmix_out_0;
                }
                {
                    double ydcst_0_in_retv = v_ydcst_retv[0];
                    double zqsmix_0_in_0 = __state->__6_zqsmix[((_for_it_17 + (sym_klon * (_for_it_16 - 1))) - 1)];
                    double zqsmix_1_in_0 = __state->__6_zqsmix[((_for_it_17 + (sym_klon * (_for_it_16 - 1))) - 1)];
                    double zqsmix_out_0;

                    ///////////////////
                    // Tasklet code (T_l506_c506)
                    zqsmix_out_0 = (zqsmix_0_in_0 / (1.0 - (ydcst_0_in_retv * zqsmix_1_in_0)));
                    ///////////////////

                    __state->__6_zqsmix[((_for_it_17 + (sym_klon * (_for_it_16 - 1))) - 1)] = zqsmix_out_0;
                }
                {
                    double ztp1_0_in_0 = __state->__6_ztp1[((_for_it_17 + (sym_klon * (_for_it_16 - 1))) - 1)];
                    double oka_out;

                    ///////////////////
                    // Tasklet code (T_l507_c507)
                    oka_out = ztp1_0_in_0;
                    ///////////////////

                    __state->__6_oka = oka_out;
                }
            }
            if (((__state->__6_oka - *v_ydcst_rtt) >= 0.0)) {
                {
                    {
                        double tmp_call_2_out;

                        ///////////////////
                        // Tasklet code (T_l508_c508)
                        tmp_call_2_out = abs(1.0);
                        ///////////////////

                        __state->__6_tmp_call_2 = tmp_call_2_out;
                    }
                }
            } else if ((!((__state->__6_oka - *v_ydcst_rtt) >= 0.0))) {
                {
                    {
                        double tmp_call_0_out;

                        ///////////////////
                        // Tasklet code (T_l508_c508)
                        tmp_call_0_out = abs(1.0);
                        ///////////////////

                        __state->__6_tmp_call_0 = tmp_call_0_out;
                    }
                    {
                        double tmp_call_0_0_in = __state->__6_tmp_call_0;
                        double tmp_call_2_out;

                        ///////////////////
                        // Tasklet code (T_l508_c508)
                        tmp_call_2_out = (-tmp_call_0_0_in);
                        ///////////////////

                        __state->__6_tmp_call_2 = tmp_call_2_out;
                    }
                }
            }
            {
                {
                    double tmp_call_2_0_in = __state->__6_tmp_call_2;
                    double zalfa_out;

                    ///////////////////
                    // Tasklet code (T_l508_c508)
                    zalfa_out = max(0.0, tmp_call_2_0_in);
                    ///////////////////

                    __state->__6_zalfa = zalfa_out;
                }
                {
                    double ztp1_0_in_0 = __state->__6_ztp1[((_for_it_17 + (sym_klon * (_for_it_16 - 1))) - 1)];
                    double oka_out;

                    ///////////////////
                    // Tasklet code (T_l509_c509)
                    oka_out = ztp1_0_in_0;
                    ///////////////////

                    __state->__6_oka = oka_out;
                }
                {
                    double oka_0_in = __state->__6_oka;
                    double oka_1_in = __state->__6_oka;
                    double ydcst_0_in_rtt = v_ydcst_rtt[0];
                    double ydthf_0_in_r3ies = v_ydthf_r3ies[0];
                    double ydthf_1_in_r4ies = v_ydthf_r4ies[0];
                    double tmp_arg_6_out;

                    ///////////////////
                    // Tasklet code (T_l510_c510)
                    tmp_arg_6_out = ((ydthf_0_in_r3ies * (oka_0_in - ydcst_0_in_rtt)) / (oka_1_in - ydthf_1_in_r4ies));
                    ///////////////////

                    __state->__6_tmp_arg_6 = tmp_arg_6_out;
                }
                {
                    double tmp_arg_6_0_in = __state->__6_tmp_arg_6;
                    double tmp_call_12_out;

                    ///////////////////
                    // Tasklet code (T_l510_c510)
                    tmp_call_12_out = exp(tmp_arg_6_0_in);
                    ///////////////////

                    __state->__6_tmp_call_12 = tmp_call_12_out;
                }
            }
            {
                {
                    double oka_0_in = __state->__6_oka;
                    double oka_1_in = __state->__6_oka;
                    double ydcst_0_in_rtt = v_ydcst_rtt[0];
                    double ydthf_0_in_r3les = v_ydthf_r3les[0];
                    double ydthf_1_in_r4les = v_ydthf_r4les[0];
                    double tmp_arg_7_out;

                    ///////////////////
                    // Tasklet code (T_l510_c510)
                    tmp_arg_7_out = ((ydthf_0_in_r3les * (oka_0_in - ydcst_0_in_rtt)) / (oka_1_in - ydthf_1_in_r4les));
                    ///////////////////

                    __state->__6_tmp_arg_7 = tmp_arg_7_out;
                }
                {
                    double tmp_arg_7_0_in = __state->__6_tmp_arg_7;
                    double tmp_call_11_out;

                    ///////////////////
                    // Tasklet code (T_l510_c510)
                    tmp_call_11_out = exp(tmp_arg_7_0_in);
                    ///////////////////

                    __state->__6_tmp_call_11 = tmp_call_11_out;
                }
                {
                    double pap_var_17_0_in_0 = pap_var_17[((_for_it_17 + (sym_klon * (_for_it_16 - 1))) - 1)];
                    double tmp_call_11_0_in = __state->__6_tmp_call_11;
                    double tmp_call_12_0_in = __state->__6_tmp_call_12;
                    double ydthf_0_in_r2es = v_ydthf_r2es[0];
                    double ydthf_1_in_r2es = v_ydthf_r2es[0];
                    double zalfa_0_in = __state->__6_zalfa;
                    double zalfa_1_in = __state->__6_zalfa;
                    double tmp_arg_8_out;

                    ///////////////////
                    // Tasklet code (T_l510_c510)
                    tmp_arg_8_out = ((((zalfa_0_in * ydthf_0_in_r2es) * tmp_call_11_0_in) + (((1.0 - zalfa_1_in) * ydthf_1_in_r2es) * tmp_call_12_0_in)) / pap_var_17_0_in_0);
                    ///////////////////

                    __state->__6_tmp_arg_8 = tmp_arg_8_out;
                }
                {
                    double tmp_arg_8_0_in = __state->__6_tmp_arg_8;
                    double tmp_call_3_out;

                    ///////////////////
                    // Tasklet code (T_l510_c510)
                    tmp_call_3_out = min(tmp_arg_8_0_in, 0.5);
                    ///////////////////

                    __state->__6_tmp_call_3 = tmp_call_3_out;
                }
                {
                    double tmp_call_3_0_in = __state->__6_tmp_call_3;
                    double zfoeew_out_0;

                    ///////////////////
                    // Tasklet code (T_l510_c510)
                    zfoeew_out_0 = tmp_call_3_0_in;
                    ///////////////////

                    __state->__6_zfoeew[((_for_it_17 + (sym_klon * (_for_it_16 - 1))) - 1)] = zfoeew_out_0;
                }
                {
                    double zfoeew_0_in_0 = __state->__6_zfoeew[((_for_it_17 + (sym_klon * (_for_it_16 - 1))) - 1)];
                    double tmp_call_4_out;

                    ///////////////////
                    // Tasklet code (T_l511_c511)
                    tmp_call_4_out = min(0.5, zfoeew_0_in_0);
                    ///////////////////

                    __state->__6_tmp_call_4 = tmp_call_4_out;
                }
                {
                    double tmp_call_4_0_in = __state->__6_tmp_call_4;
                    double zfoeew_out_0;

                    ///////////////////
                    // Tasklet code (T_l511_c511)
                    zfoeew_out_0 = tmp_call_4_0_in;
                    ///////////////////

                    __state->__6_zfoeew[((_for_it_17 + (sym_klon * (_for_it_16 - 1))) - 1)] = zfoeew_out_0;
                }
            }
            {
                {
                    double ydcst_0_in_retv = v_ydcst_retv[0];
                    double zfoeew_0_in_0 = __state->__6_zfoeew[((_for_it_17 + (sym_klon * (_for_it_16 - 1))) - 1)];
                    double zfoeew_1_in_0 = __state->__6_zfoeew[((_for_it_17 + (sym_klon * (_for_it_16 - 1))) - 1)];
                    double zqsice_out_0;

                    ///////////////////
                    // Tasklet code (T_l512_c512)
                    zqsice_out_0 = (zfoeew_0_in_0 / (1.0 - (ydcst_0_in_retv * zfoeew_1_in_0)));
                    ///////////////////

                    __state->__6_zqsice[((_for_it_17 + (sym_klon * (_for_it_16 - 1))) - 1)] = zqsice_out_0;
                }
                {
                    double ztp1_0_in_0 = __state->__6_ztp1[((_for_it_17 + (sym_klon * (_for_it_16 - 1))) - 1)];
                    double oka_out;

                    ///////////////////
                    // Tasklet code (T_l513_c513)
                    oka_out = ztp1_0_in_0;
                    ///////////////////

                    __state->__6_oka = oka_out;
                }
                {
                    double oka_0_in = __state->__6_oka;
                    double oka_1_in = __state->__6_oka;
                    double ydcst_0_in_rtt = v_ydcst_rtt[0];
                    double ydthf_0_in_r3les = v_ydthf_r3les[0];
                    double ydthf_1_in_r4les = v_ydthf_r4les[0];
                    double tmp_arg_9_out;

                    ///////////////////
                    // Tasklet code (T_l514_c514)
                    tmp_arg_9_out = ((ydthf_0_in_r3les * (oka_0_in - ydcst_0_in_rtt)) / (oka_1_in - ydthf_1_in_r4les));
                    ///////////////////

                    __state->__6_tmp_arg_9 = tmp_arg_9_out;
                }
                {
                    double tmp_arg_9_0_in = __state->__6_tmp_arg_9;
                    double tmp_call_13_out;

                    ///////////////////
                    // Tasklet code (T_l514_c514)
                    tmp_call_13_out = exp(tmp_arg_9_0_in);
                    ///////////////////

                    __state->__6_tmp_call_13 = tmp_call_13_out;
                }
                {
                    double pap_var_17_0_in_0 = pap_var_17[((_for_it_17 + (sym_klon * (_for_it_16 - 1))) - 1)];
                    double tmp_call_13_0_in = __state->__6_tmp_call_13;
                    double ydthf_0_in_r2es = v_ydthf_r2es[0];
                    double tmp_arg_10_out;

                    ///////////////////
                    // Tasklet code (T_l514_c514)
                    tmp_arg_10_out = ((ydthf_0_in_r2es * tmp_call_13_0_in) / pap_var_17_0_in_0);
                    ///////////////////

                    __state->__6_tmp_arg_10 = tmp_arg_10_out;
                }
                {
                    double tmp_arg_10_0_in = __state->__6_tmp_arg_10;
                    double tmp_call_5_out;

                    ///////////////////
                    // Tasklet code (T_l514_c514)
                    tmp_call_5_out = min(tmp_arg_10_0_in, 0.5);
                    ///////////////////

                    __state->__6_tmp_call_5 = tmp_call_5_out;
                }
                {
                    double tmp_call_5_0_in = __state->__6_tmp_call_5;
                    double zfoeeliqt_out_0;

                    ///////////////////
                    // Tasklet code (T_l514_c514)
                    zfoeeliqt_out_0 = tmp_call_5_0_in;
                    ///////////////////

                    __state->__6_zfoeeliqt[((_for_it_17 + (sym_klon * (_for_it_16 - 1))) - 1)] = zfoeeliqt_out_0;
                }
                {
                    double zfoeeliqt_0_in_0 = __state->__6_zfoeeliqt[((_for_it_17 + (sym_klon * (_for_it_16 - 1))) - 1)];
                    double zqsliq_out_0;

                    ///////////////////
                    // Tasklet code (T_l515_c515)
                    zqsliq_out_0 = zfoeeliqt_0_in_0;
                    ///////////////////

                    __state->__6_zqsliq[((_for_it_17 + (sym_klon * (_for_it_16 - 1))) - 1)] = zqsliq_out_0;
                }
            }
            {
                {
                    double ydcst_0_in_retv = v_ydcst_retv[0];
                    double zqsliq_0_in_0 = __state->__6_zqsliq[((_for_it_17 + (sym_klon * (_for_it_16 - 1))) - 1)];
                    double zqsliq_1_in_0 = __state->__6_zqsliq[((_for_it_17 + (sym_klon * (_for_it_16 - 1))) - 1)];
                    double zqsliq_out_0;

                    ///////////////////
                    // Tasklet code (T_l516_c516)
                    zqsliq_out_0 = (zqsliq_0_in_0 / (1.0 - (ydcst_0_in_retv * zqsliq_1_in_0)));
                    ///////////////////

                    __state->__6_zqsliq[((_for_it_17 + (sym_klon * (_for_it_16 - 1))) - 1)] = zqsliq_out_0;
                }
            }
        }
    }

    {
        {
#pragma omp parallel for
            for (auto _for_it_18 = 1; _for_it_18 < (sym_klev + 1); _for_it_18 += 1) {
                loop_body_6_5_0(
                    __state, ydecldp_var_47, &__state->__6_zqx[(sym_klon * (_for_it_18 - 1))], &__state->__6_za[(sym_klon * (_for_it_18 - 1))], &__state->__6_zicefrac[(sym_klon * (_for_it_18 - 1))],
                    &__state->__6_zli[(sym_klon * (_for_it_18 - 1))], &__state->__6_zliqfrac[(sym_klon * (_for_it_18 - 1))], icend, sym_klev, sym_klon);
            }
        }
        {
#pragma omp parallel for
            for (auto tmp_parfor_12 = 1; tmp_parfor_12 < (sym_klon + 1); tmp_parfor_12 += 1) {
                loop_body_6_5_13(__state, &__state->__6_zanewm1[(tmp_parfor_12 - 1)]);
            }
        }
        {
#pragma omp parallel for
            for (auto tmp_parfor_13 = 1; tmp_parfor_13 < (sym_klon + 1); tmp_parfor_13 += 1) {
                loop_body_6_5_17(__state, &__state->__6_zda[(tmp_parfor_13 - 1)]);
            }
        }
        {
#pragma omp parallel for
            for (auto tmp_parfor_14 = 1; tmp_parfor_14 < (sym_klon + 1); tmp_parfor_14 += 1) {
                loop_body_6_5_21(__state, &__state->__6_zcovpclr[(tmp_parfor_14 - 1)]);
            }
        }
        {
#pragma omp parallel for
            for (auto tmp_parfor_15 = 1; tmp_parfor_15 < (sym_klon + 1); tmp_parfor_15 += 1) {
                loop_body_6_5_25(__state, &__state->__6_zcovpmax[(tmp_parfor_15 - 1)]);
            }
        }
        {
#pragma omp parallel for
            for (auto tmp_parfor_16 = 1; tmp_parfor_16 < (sym_klon + 1); tmp_parfor_16 += 1) {
                loop_body_6_5_29(__state, &__state->__6_zcovptot[(tmp_parfor_16 - 1)]);
            }
        }
        {
#pragma omp parallel for
            for (auto tmp_parfor_17 = 1; tmp_parfor_17 < (sym_klon + 1); tmp_parfor_17 += 1) {
                loop_body_6_5_33(__state, &__state->__6_zcldtopdist[(tmp_parfor_17 - 1)]);
            }
        }
    }

    for (_for_it_23 = *v_ydecldp_var_47_ncldtop; (_for_it_23 <= sym_klev); _for_it_23 = (_for_it_23 + 1)) {
        {
            {
#pragma omp parallel for
                for (auto _for_it_24 = 1; _for_it_24 < 6; _for_it_24 += 1) {
                    loop_body_50_0_0(
                        __state, &__state->__6_zqx[(((sym_klev * sym_klon) * (_for_it_24 - 1)) + (sym_klon * (_for_it_23 - 1)))], &__state->__6_zqxfg[(sym_klon * (_for_it_24 - 1))], icend, sym_klev,
                        sym_klon);
                }
            }
            {
#pragma omp parallel for
                for (auto tmp_parfor_18 = 1; tmp_parfor_18 < (sym_klon + 1); tmp_parfor_18 += 1) {
                    loop_body_50_0_5(__state, &__state->__6_zlicld[(tmp_parfor_18 - 1)]);
                }
            }
            {
#pragma omp parallel for
                for (auto tmp_parfor_19 = 1; tmp_parfor_19 < (sym_klon + 1); tmp_parfor_19 += 1) {
                    loop_body_50_0_9(__state, &__state->__6_zrainaut[(tmp_parfor_19 - 1)]);
                }
            }
            {
#pragma omp parallel for
                for (auto tmp_parfor_20 = 1; tmp_parfor_20 < (sym_klon + 1); tmp_parfor_20 += 1) {
                    loop_body_50_0_13(__state, &__state->__6_zrainacc[(tmp_parfor_20 - 1)]);
                }
            }
            {
#pragma omp parallel for
                for (auto tmp_parfor_21 = 1; tmp_parfor_21 < (sym_klon + 1); tmp_parfor_21 += 1) {
                    loop_body_50_0_17(__state, &__state->__6_zsnowaut[(tmp_parfor_21 - 1)]);
                }
            }
            {
#pragma omp parallel for
                for (auto tmp_parfor_22 = 1; tmp_parfor_22 < (sym_klon + 1); tmp_parfor_22 += 1) {
                    loop_body_50_0_21(__state, &__state->__6_zldefr[(tmp_parfor_22 - 1)]);
                }
            }
            {
#pragma omp parallel for
                for (auto tmp_parfor_23 = 1; tmp_parfor_23 < (sym_klon + 1); tmp_parfor_23 += 1) {
                    loop_body_50_0_25(__state, &__state->__6_zacust[(tmp_parfor_23 - 1)]);
                }
            }
            {
#pragma omp parallel for
                for (auto tmp_parfor_24 = 1; tmp_parfor_24 < (sym_klon + 1); tmp_parfor_24 += 1) {
                    loop_body_50_0_29(__state, &__state->__6_zqpretot[(tmp_parfor_24 - 1)]);
                }
            }
            {
#pragma omp parallel for
                for (auto tmp_parfor_25 = 1; tmp_parfor_25 < (sym_klon + 1); tmp_parfor_25 += 1) {
                    loop_body_50_0_33(__state, &__state->__6_zlfinalsum[(tmp_parfor_25 - 1)]);
                }
            }
            {
#pragma omp parallel for
                for (auto tmp_parfor_26 = 1; tmp_parfor_26 < (sym_klon + 1); tmp_parfor_26 += 1) {
                    loop_body_50_0_37(__state, &__state->__6_zlcond1[(tmp_parfor_26 - 1)]);
                }
            }
            {
#pragma omp parallel for
                for (auto tmp_parfor_27 = 1; tmp_parfor_27 < (sym_klon + 1); tmp_parfor_27 += 1) {
                    loop_body_50_0_41(__state, &__state->__6_zlcond2[(tmp_parfor_27 - 1)]);
                }
            }
            {
#pragma omp parallel for
                for (auto tmp_parfor_28 = 1; tmp_parfor_28 < (sym_klon + 1); tmp_parfor_28 += 1) {
                    loop_body_50_0_45(__state, &__state->__6_zsupsat[(tmp_parfor_28 - 1)]);
                }
            }
            {
#pragma omp parallel for
                for (auto tmp_parfor_31 = 1; tmp_parfor_31 < (sym_klon + 1); tmp_parfor_31 += 1) {
                    loop_body_50_0_49(__state, &__state->__6_zsolab[(tmp_parfor_31 - 1)]);
                }
            }
            {
#pragma omp parallel for
                for (auto tmp_parfor_32 = 1; tmp_parfor_32 < (sym_klon + 1); tmp_parfor_32 += 1) {
                    loop_body_50_0_53(__state, &__state->__6_zsolac[(tmp_parfor_32 - 1)]);
                }
            }
            {
#pragma omp parallel for
                for (auto tmp_parfor_35 = 1; tmp_parfor_35 < 6; tmp_parfor_35 += 1) {
                    loop_body_50_0_57(__state, &__state->__6_zsolqb[((5 * sym_klon) * (tmp_parfor_35 - 1))], sym_klon);
                }
            }
            {
#pragma omp parallel for
                for (auto tmp_parfor_38 = 1; tmp_parfor_38 < 6; tmp_parfor_38 += 1) {
                    loop_body_50_0_61(__state, &__state->__6_zsolqa[((5 * sym_klon) * (tmp_parfor_38 - 1))], sym_klon);
                }
            }
            {
#pragma omp parallel for
                for (auto tmp_parfor_40 = 1; tmp_parfor_40 < 6; tmp_parfor_40 += 1) {
                    loop_body_50_0_65(__state, &__state->__6_zfallsrce[(sym_klon * (tmp_parfor_40 - 1))], sym_klon);
                }
            }
            {
#pragma omp parallel for
                for (auto tmp_parfor_42 = 1; tmp_parfor_42 < 6; tmp_parfor_42 += 1) {
                    loop_body_50_0_69(__state, &__state->__6_zfallsink[(sym_klon * (tmp_parfor_42 - 1))], sym_klon);
                }
            }
            {
#pragma omp parallel for
                for (auto tmp_parfor_44 = 1; tmp_parfor_44 < 6; tmp_parfor_44 += 1) {
                    loop_body_50_0_73(__state, &__state->__6_zconvsrce[(sym_klon * (tmp_parfor_44 - 1))], sym_klon);
                }
            }
            {
#pragma omp parallel for
                for (auto tmp_parfor_46 = 1; tmp_parfor_46 < 6; tmp_parfor_46 += 1) {
                    loop_body_50_0_77(__state, &__state->__6_zconvsink[(sym_klon * (tmp_parfor_46 - 1))], sym_klon);
                }
            }
            {
#pragma omp parallel for
                for (auto tmp_parfor_48 = 1; tmp_parfor_48 < 6; tmp_parfor_48 += 1) {
                    loop_body_50_0_81(__state, &__state->__6_zpsupsatsrce[(sym_klon * (tmp_parfor_48 - 1))], sym_klon);
                }
            }
            {
#pragma omp parallel for
                for (auto tmp_parfor_50 = 1; tmp_parfor_50 < 6; tmp_parfor_50 += 1) {
                    loop_body_50_0_85(__state, &__state->__6_zratio[(sym_klon * (tmp_parfor_50 - 1))], sym_klon);
                }
            }
            {
#pragma omp parallel for
                for (auto tmp_parfor_51 = 1; tmp_parfor_51 < (sym_klon + 1); tmp_parfor_51 += 1) {
                    loop_body_50_0_89(__state, &__state->__6_zicetot[(tmp_parfor_51 - 1)]);
                }
            }
        }
        for (_for_it_26 = 1; (_for_it_26 <= icend); _for_it_26 = (_for_it_26 + 1)) {
            {
                {
                    double pap_var_17_0_in_0 = pap_var_17[((_for_it_26 + (sym_klon * (_for_it_23 - 1))) - 1)];
                    double ydcst_0_in_rd = v_ydcst_rd[0];
                    double ztp1_0_in_0 = __state->__6_ztp1[((_for_it_26 + (sym_klon * (_for_it_23 - 1))) - 1)];
                    double zrho_out_0;

                    ///////////////////
                    // Tasklet code (T_l583_c583)
                    zrho_out_0 = (pap_var_17_0_in_0 / (ydcst_0_in_rd * ztp1_0_in_0));
                    ///////////////////

                    __state->__6_zrho[(_for_it_26 - 1)] = zrho_out_0;
                }
                {
                    double paph_var_18_0_in_0 = paph_var_18[(((_for_it_23 * sym_klon) + _for_it_26) - 1)];
                    double paph_var_18_1_in_0 = paph_var_18[((_for_it_26 + (sym_klon * (_for_it_23 - 1))) - 1)];
                    double zdp_out_0;

                    ///////////////////
                    // Tasklet code (T_l581_c581)
                    zdp_out_0 = (paph_var_18_0_in_0 - paph_var_18_1_in_0);
                    ///////////////////

                    __state->__6_zdp[(_for_it_26 - 1)] = zdp_out_0;
                }
                {
                    double ydcst_0_in_rg = v_ydcst_rg[0];
                    double zdp_0_in_0 = __state->__6_zdp[(_for_it_26 - 1)];
                    double zgdp_out_0;

                    ///////////////////
                    // Tasklet code (T_l582_c582)
                    zgdp_out_0 = (ydcst_0_in_rg / zdp_0_in_0);
                    ///////////////////

                    __state->__6_zgdp[(_for_it_26 - 1)] = zgdp_out_0;
                }
                {
                    double ptsphy_var_5_0_in = ptsphy_var_5[0];
                    double zgdp_0_in_0 = __state->__6_zgdp[(_for_it_26 - 1)];
                    double zdtgdp_out_0;

                    ///////////////////
                    // Tasklet code (T_l584_c584)
                    zdtgdp_out_0 = (ptsphy_var_5_0_in * zgdp_0_in_0);
                    ///////////////////

                    __state->__6_zdtgdp[(_for_it_26 - 1)] = zdtgdp_out_0;
                }
            }
            {
                {
                    double ptsphy_var_5_0_in = ptsphy_var_5[0];
                    double ydcst_0_in_rg = v_ydcst_rg[0];
                    double zdp_0_in_0 = __state->__6_zdp[(_for_it_26 - 1)];
                    double zrdtgdp_out_0;

                    ///////////////////
                    // Tasklet code (T_l585_c585)
                    zrdtgdp_out_0 = (zdp_0_in_0 * (1.0 / (ptsphy_var_5_0_in * ydcst_0_in_rg)));
                    ///////////////////

                    __state->__6_zrdtgdp[(_for_it_26 - 1)] = zrdtgdp_out_0;
                }
            }
            if (((_for_it_23 > 1) == 1)) {
                {
                }
            }
            {
                double* v_ydthf_r5les;
                v_ydthf_r5les = (double*)(&(ydthf->r5les));

                {
                    double ydthf_0_in_r4les = v_ydthf_r4les[0];
                    double ztp1_0_in_0 = __state->__6_ztp1[((_for_it_26 + (sym_klon * (_for_it_23 - 1))) - 1)];
                    double tmp_arg_11_out;

                    ///////////////////
                    // Tasklet code (T_l587_c587)
                    tmp_arg_11_out = (ztp1_0_in_0 - ydthf_0_in_r4les);
                    ///////////////////

                    __state->__6_tmp_arg_11 = tmp_arg_11_out;
                }
                {
                    double tmp_arg_11_0_in = __state->__6_tmp_arg_11;
                    double tmp_call_24_out;

                    ///////////////////
                    // Tasklet code (T_l587_c587)
                    tmp_call_24_out = (dace::math::ipow(tmp_arg_11_0_in, 2));
                    ///////////////////

                    __state->__6_tmp_call_24 = tmp_call_24_out;
                }
                {
                    double tmp_call_24_0_in = __state->__6_tmp_call_24;
                    double ydthf_0_in_r5les = v_ydthf_r5les[0];
                    double zfacw_out;

                    ///////////////////
                    // Tasklet code (T_l587_c587)
                    zfacw_out = (ydthf_0_in_r5les / tmp_call_24_0_in);
                    ///////////////////

                    __state->__6_zfacw = zfacw_out;
                }
                {
                    double ydcst_0_in_retv = v_ydcst_retv[0];
                    double zfoeeliqt_0_in_0 = __state->__6_zfoeeliqt[((_for_it_26 + (sym_klon * (_for_it_23 - 1))) - 1)];
                    double zcor_out;

                    ///////////////////
                    // Tasklet code (T_l588_c588)
                    zcor_out = (1.0 / (1.0 - (ydcst_0_in_retv * zfoeeliqt_0_in_0)));
                    ///////////////////

                    __state->__6_zcor = zcor_out;
                }
            }
            zalfaw = __state->__6_zfoealfa[((_for_it_26 + (sym_klon * (_for_it_23 - 1))) - 1)];
            {
                double* v_ydthf_r5ies;
                v_ydthf_r5ies = (double*)(&(ydthf->r5ies));

                {
                    double ydthf_0_in_r4ies = v_ydthf_r4ies[0];
                    double ztp1_0_in_0 = __state->__6_ztp1[((_for_it_26 + (sym_klon * (_for_it_23 - 1))) - 1)];
                    double tmp_arg_12_out;

                    ///////////////////
                    // Tasklet code (T_l591_c591)
                    tmp_arg_12_out = (ztp1_0_in_0 - ydthf_0_in_r4ies);
                    ///////////////////

                    __state->__6_tmp_arg_12 = tmp_arg_12_out;
                }
                {
                    double tmp_arg_12_0_in = __state->__6_tmp_arg_12;
                    double tmp_call_25_out;

                    ///////////////////
                    // Tasklet code (T_l591_c591)
                    tmp_call_25_out = (dace::math::ipow(tmp_arg_12_0_in, 2));
                    ///////////////////

                    __state->__6_tmp_call_25 = tmp_call_25_out;
                }
                {
                    double tmp_call_25_0_in = __state->__6_tmp_call_25;
                    double ydthf_0_in_r5ies = v_ydthf_r5ies[0];
                    double zfaci_out;

                    ///////////////////
                    // Tasklet code (T_l591_c591)
                    zfaci_out = (ydthf_0_in_r5ies / tmp_call_25_0_in);
                    ///////////////////

                    __state->__6_zfaci = zfaci_out;
                }
                {
                    double ydcst_0_in_retv = v_ydcst_retv[0];
                    double zfoeew_0_in_0 = __state->__6_zfoeew[((_for_it_26 + (sym_klon * (_for_it_23 - 1))) - 1)];
                    double zcor_out;

                    ///////////////////
                    // Tasklet code (T_l592_c592)
                    zcor_out = (1.0 / (1.0 - (ydcst_0_in_retv * zfoeew_0_in_0)));
                    ///////////////////

                    __state->__6_zcor = zcor_out;
                }
                {
                    double zcor_0_in = __state->__6_zcor;
                    double zfaci_0_in = __state->__6_zfaci;
                    double zqsice_0_in_0 = __state->__6_zqsice[((_for_it_26 + (sym_klon * (_for_it_23 - 1))) - 1)];
                    double zdqsicedt_out_0;

                    ///////////////////
                    // Tasklet code (T_l593_c593)
                    zdqsicedt_out_0 = ((zfaci_0_in * zcor_0_in) * zqsice_0_in_0);
                    ///////////////////

                    __state->__6_zdqsicedt[(_for_it_26 - 1)] = zdqsicedt_out_0;
                }
                {
                    double ydthf_0_in_ralsdcp = v_ydthf_ralsdcp[0];
                    double zdqsicedt_0_in_0 = __state->__6_zdqsicedt[(_for_it_26 - 1)];
                    double zcorqsice_out_0;

                    ///////////////////
                    // Tasklet code (T_l594_c594)
                    zcorqsice_out_0 = (1.0 + (ydthf_0_in_ralsdcp * zdqsicedt_0_in_0));
                    ///////////////////

                    __state->__6_zcorqsice[(_for_it_26 - 1)] = zcorqsice_out_0;
                }
            }
            zfac = ((zalfaw * __state->__6_zfacw) + ((1.0 - zalfaw) * __state->__6_zfaci));
            {
                {
                    double ydcst_0_in_retv = v_ydcst_retv[0];
                    double zfoeewmt_0_in_0 = __state->__6_zfoeewmt[((_for_it_26 + (sym_klon * (_for_it_23 - 1))) - 1)];
                    double zcor_out;

                    ///////////////////
                    // Tasklet code (T_l598_c598)
                    zcor_out = (1.0 / (1.0 - (ydcst_0_in_retv * zfoeewmt_0_in_0)));
                    ///////////////////

                    __state->__6_zcor = zcor_out;
                }
                {
                    double zcor_0_in = __state->__6_zcor;
                    double zqsmix_0_in_0 = __state->__6_zqsmix[((_for_it_26 + (sym_klon * (_for_it_23 - 1))) - 1)];
                    double zdqsmixdt_out_0;

                    ///////////////////
                    // Tasklet code (T_l599_c599)
                    zdqsmixdt_out_0 = ((zfac * zcor_0_in) * zqsmix_0_in_0);
                    ///////////////////

                    __state->__6_zdqsmixdt[(_for_it_26 - 1)] = zdqsmixdt_out_0;
                }
                {
                    double ztp1_0_in_0 = __state->__6_ztp1[((_for_it_26 + (sym_klon * (_for_it_23 - 1))) - 1)];
                    double oka_out;

                    ///////////////////
                    // Tasklet code (T_l600_c600)
                    oka_out = ztp1_0_in_0;
                    ///////////////////

                    __state->__6_oka = oka_out;
                }
                {
                    double oka_0_in = __state->__6_oka;
                    double ydthf_0_in_rtwat = v_ydthf_rtwat[0];
                    double tmp_call_36_out;

                    ///////////////////
                    // Tasklet code (T_l601_c601)
                    tmp_call_36_out = min(ydthf_0_in_rtwat, oka_0_in);
                    ///////////////////

                    __state->__6_tmp_call_36 = tmp_call_36_out;
                }
                {
                    double tmp_call_36_0_in = __state->__6_tmp_call_36;
                    double ydthf_0_in_rtice = v_ydthf_rtice[0];
                    double tmp_call_34_out;

                    ///////////////////
                    // Tasklet code (T_l601_c601)
                    tmp_call_34_out = max(ydthf_0_in_rtice, tmp_call_36_0_in);
                    ///////////////////

                    __state->__6_tmp_call_34 = tmp_call_34_out;
                }
            }
            {
                {
                    double tmp_call_34_0_in = __state->__6_tmp_call_34;
                    double ydthf_0_in_rtice = v_ydthf_rtice[0];
                    double ydthf_1_in_rtwat_rtice_r = v_ydthf_rtwat_rtice_r[0];
                    double tmp_arg_13_out;

                    ///////////////////
                    // Tasklet code (T_l601_c601)
                    tmp_arg_13_out = ((tmp_call_34_0_in - ydthf_0_in_rtice) * ydthf_1_in_rtwat_rtice_r);
                    ///////////////////

                    __state->__6_tmp_arg_13 = tmp_arg_13_out;
                }
                {
                    double tmp_arg_13_0_in = __state->__6_tmp_arg_13;
                    double tmp_call_32_out;

                    ///////////////////
                    // Tasklet code (T_l601_c601)
                    tmp_call_32_out = (dace::math::ipow(tmp_arg_13_0_in, 2));
                    ///////////////////

                    __state->__6_tmp_call_32 = tmp_call_32_out;
                }
                {
                    double tmp_call_32_0_in = __state->__6_tmp_call_32;
                    double tmp_call_27_out;

                    ///////////////////
                    // Tasklet code (T_l601_c601)
                    tmp_call_27_out = min(1.0, tmp_call_32_0_in);
                    ///////////////////

                    __state->__6_tmp_call_27 = tmp_call_27_out;
                }
                {
                    double oka_0_in = __state->__6_oka;
                    double ydthf_0_in_rtwat = v_ydthf_rtwat[0];
                    double tmp_call_37_out;

                    ///////////////////
                    // Tasklet code (T_l601_c601)
                    tmp_call_37_out = min(ydthf_0_in_rtwat, oka_0_in);
                    ///////////////////

                    __state->__6_tmp_call_37 = tmp_call_37_out;
                }
            }
            {
                {
                    double tmp_call_37_0_in = __state->__6_tmp_call_37;
                    double ydthf_0_in_rtice = v_ydthf_rtice[0];
                    double tmp_call_35_out;

                    ///////////////////
                    // Tasklet code (T_l601_c601)
                    tmp_call_35_out = max(ydthf_0_in_rtice, tmp_call_37_0_in);
                    ///////////////////

                    __state->__6_tmp_call_35 = tmp_call_35_out;
                }
            }
            {
                {
                    double tmp_call_35_0_in = __state->__6_tmp_call_35;
                    double ydthf_0_in_rtice = v_ydthf_rtice[0];
                    double ydthf_1_in_rtwat_rtice_r = v_ydthf_rtwat_rtice_r[0];
                    double tmp_arg_14_out;

                    ///////////////////
                    // Tasklet code (T_l601_c601)
                    tmp_arg_14_out = ((tmp_call_35_0_in - ydthf_0_in_rtice) * ydthf_1_in_rtwat_rtice_r);
                    ///////////////////

                    __state->__6_tmp_arg_14 = tmp_arg_14_out;
                }
                {
                    double tmp_arg_14_0_in = __state->__6_tmp_arg_14;
                    double tmp_call_33_out;

                    ///////////////////
                    // Tasklet code (T_l601_c601)
                    tmp_call_33_out = (dace::math::ipow(tmp_arg_14_0_in, 2));
                    ///////////////////

                    __state->__6_tmp_call_33 = tmp_call_33_out;
                }
                {
                    double tmp_call_33_0_in = __state->__6_tmp_call_33;
                    double tmp_call_26_out;

                    ///////////////////
                    // Tasklet code (T_l601_c601)
                    tmp_call_26_out = min(1.0, tmp_call_33_0_in);
                    ///////////////////

                    __state->__6_tmp_call_26 = tmp_call_26_out;
                }
                {
                    double tmp_call_26_0_in = __state->__6_tmp_call_26;
                    double tmp_call_27_0_in = __state->__6_tmp_call_27;
                    double ydthf_0_in_ralvdcp = v_ydthf_ralvdcp[0];
                    double ydthf_1_in_ralsdcp = v_ydthf_ralsdcp[0];
                    double zdqsmixdt_0_in_0 = __state->__6_zdqsmixdt[(_for_it_26 - 1)];
                    double zcorqsmix_out_0;

                    ///////////////////
                    // Tasklet code (T_l601_c601)
                    zcorqsmix_out_0 = ((1.0 + (tmp_call_26_0_in * ydthf_0_in_ralvdcp)) + (((1.0 - tmp_call_27_0_in) * ydthf_1_in_ralsdcp) * zdqsmixdt_0_in_0));
                    ///////////////////

                    __state->__6_zcorqsmix[(_for_it_26 - 1)] = zcorqsmix_out_0;
                }
                {
                    double zcorqsmix_0_in_0 = __state->__6_zcorqsmix[(_for_it_26 - 1)];
                    double zqsmix_0_in_0 = __state->__6_zqsmix[((_for_it_26 + (sym_klon * (_for_it_23 - 1))) - 1)];
                    double zqx_0_in_0 = __state->__6_zqx[(((_for_it_26 + ((4 * sym_klev) * sym_klon)) + (sym_klon * (_for_it_23 - 1))) - 1)];
                    double tmp_arg_15_out;

                    ///////////////////
                    // Tasklet code (T_l602_c602)
                    tmp_arg_15_out = ((zqsmix_0_in_0 - zqx_0_in_0) / zcorqsmix_0_in_0);
                    ///////////////////

                    __state->__6_tmp_arg_15 = tmp_arg_15_out;
                }
                {
                    double tmp_arg_15_0_in = __state->__6_tmp_arg_15;
                    double tmp_call_28_out;

                    ///////////////////
                    // Tasklet code (T_l602_c602)
                    tmp_call_28_out = max(tmp_arg_15_0_in, 0.0);
                    ///////////////////

                    __state->__6_tmp_call_28 = tmp_call_28_out;
                }
                {
                    double tmp_call_28_0_in = __state->__6_tmp_call_28;
                    double zevaplimmix_out_0;

                    ///////////////////
                    // Tasklet code (T_l602_c602)
                    zevaplimmix_out_0 = tmp_call_28_0_in;
                    ///////////////////

                    __state->__6_zevaplimmix[(_for_it_26 - 1)] = zevaplimmix_out_0;
                }
                {
                    double za_0_in_0 = __state->__6_za[((_for_it_26 + (sym_klon * (_for_it_23 - 1))) - 1)];
                    double zepsec_0_in = __state->__6_zepsec;
                    double tmp_call_31_out;

                    ///////////////////
                    // Tasklet code (T_l605_c605)
                    tmp_call_31_out = max(za_0_in_0, zepsec_0_in);
                    ///////////////////

                    __state->__6_tmp_call_31 = tmp_call_31_out;
                }
                {
                    double tmp_call_31_0_in = __state->__6_tmp_call_31;
                    double ztmpa_out;

                    ///////////////////
                    // Tasklet code (T_l605_c605)
                    ztmpa_out = (1.0 / tmp_call_31_0_in);
                    ///////////////////

                    __state->__6_ztmpa = ztmpa_out;
                }
                {
                    double zqx_0_in_0 = __state->__6_zqx[((_for_it_26 + (sym_klon * (_for_it_23 - 1))) - 1)];
                    double ztmpa_0_in = __state->__6_ztmpa;
                    double zliqcld_out_0;

                    ///////////////////
                    // Tasklet code (T_l606_c606)
                    zliqcld_out_0 = (zqx_0_in_0 * ztmpa_0_in);
                    ///////////////////

                    __state->__6_zliqcld[(_for_it_26 - 1)] = zliqcld_out_0;
                }
                {
                    double zqx_0_in_0 = __state->__6_zqx[(((_for_it_26 + (sym_klev * sym_klon)) + (sym_klon * (_for_it_23 - 1))) - 1)];
                    double ztmpa_0_in = __state->__6_ztmpa;
                    double zicecld_out_0;

                    ///////////////////
                    // Tasklet code (T_l607_c607)
                    zicecld_out_0 = (zqx_0_in_0 * ztmpa_0_in);
                    ///////////////////

                    __state->__6_zicecld[(_for_it_26 - 1)] = zicecld_out_0;
                }
                {
                    double zicecld_0_in_0 = __state->__6_zicecld[(_for_it_26 - 1)];
                    double zliqcld_0_in_0 = __state->__6_zliqcld[(_for_it_26 - 1)];
                    double zlicld_out_0;

                    ///////////////////
                    // Tasklet code (T_l608_c608)
                    zlicld_out_0 = (zliqcld_0_in_0 + zicecld_0_in_0);
                    ///////////////////

                    __state->__6_zlicld[(_for_it_26 - 1)] = zlicld_out_0;
                }
            }
        }
        {
            {
#pragma omp parallel for
                for (auto _for_it_27 = 1; _for_it_27 < (icend + 1); _for_it_27 += 1) {
                    loop_body_50_12_0(__state, ydecldp_var_47, &__state->__6_zqx[((_for_it_27 + (sym_klon * (_for_it_23 - 1))) - 1)], &__state->__6_zsolqa[(_for_it_27 - 1)], sym_klev, sym_klon);
                }
            }
        }
        for (_for_it_28 = 1; (_for_it_28 <= icend); _for_it_28 = (_for_it_28 + 1)) {
            {
                {
                    double ztp1_0_in_0 = __state->__6_ztp1[((_for_it_28 + (sym_klon * (_for_it_23 - 1))) - 1)];
                    double oka_out;

                    ///////////////////
                    // Tasklet code (T_l621_c621)
                    oka_out = ztp1_0_in_0;
                    ///////////////////

                    __state->__6_oka = oka_out;
                }
                {
                    double oka_0_in = __state->__6_oka;
                    double oka_1_in = __state->__6_oka;
                    double ydcst_0_in_rtt = v_ydcst_rtt[0];
                    double ydthf_0_in_r3ies = v_ydthf_r3ies[0];
                    double ydthf_1_in_r4ies = v_ydthf_r4ies[0];
                    double tmp_arg_18_out;

                    ///////////////////
                    // Tasklet code (T_l622_c622)
                    tmp_arg_18_out = ((ydthf_0_in_r3ies * (oka_0_in - ydcst_0_in_rtt)) / (oka_1_in - ydthf_1_in_r4ies));
                    ///////////////////

                    __state->__6_tmp_arg_18 = tmp_arg_18_out;
                }
                {
                    double tmp_arg_18_0_in = __state->__6_tmp_arg_18;
                    double tmp_call_40_out;

                    ///////////////////
                    // Tasklet code (T_l622_c622)
                    tmp_call_40_out = exp(tmp_arg_18_0_in);
                    ///////////////////

                    __state->__6_tmp_call_40 = tmp_call_40_out;
                }
            }
            {
                double* v_ydthf_rkoop1;
                v_ydthf_rkoop1 = (double*)(&(ydthf->rkoop1));
                double* v_ydthf_rkoop2;
                v_ydthf_rkoop2 = (double*)(&(ydthf->rkoop2));

                {
                    double oka_0_in = __state->__6_oka;
                    double ydthf_0_in_rkoop1 = v_ydthf_rkoop1[0];
                    double ydthf_1_in_rkoop2 = v_ydthf_rkoop2[0];
                    double tmp_arg_20_out;

                    ///////////////////
                    // Tasklet code (T_l622_c622)
                    tmp_arg_20_out = (ydthf_0_in_rkoop1 - (ydthf_1_in_rkoop2 * oka_0_in));
                    ///////////////////

                    __state->__6_tmp_arg_20 = tmp_arg_20_out;
                }
                {
                    double oka_0_in = __state->__6_oka;
                    double oka_1_in = __state->__6_oka;
                    double ydcst_0_in_rtt = v_ydcst_rtt[0];
                    double ydthf_0_in_r3les = v_ydthf_r3les[0];
                    double ydthf_1_in_r4les = v_ydthf_r4les[0];
                    double tmp_arg_19_out;

                    ///////////////////
                    // Tasklet code (T_l622_c622)
                    tmp_arg_19_out = ((ydthf_0_in_r3les * (oka_0_in - ydcst_0_in_rtt)) / (oka_1_in - ydthf_1_in_r4les));
                    ///////////////////

                    __state->__6_tmp_arg_19 = tmp_arg_19_out;
                }
                {
                    double tmp_arg_19_0_in = __state->__6_tmp_arg_19;
                    double tmp_call_39_out;

                    ///////////////////
                    // Tasklet code (T_l622_c622)
                    tmp_call_39_out = exp(tmp_arg_19_0_in);
                    ///////////////////

                    __state->__6_tmp_call_39 = tmp_call_39_out;
                }
                {
                    double tmp_call_39_0_in = __state->__6_tmp_call_39;
                    double tmp_call_40_0_in = __state->__6_tmp_call_40;
                    double ydthf_0_in_r2es = v_ydthf_r2es[0];
                    double ydthf_1_in_r2es = v_ydthf_r2es[0];
                    double tmp_arg_21_out;

                    ///////////////////
                    // Tasklet code (T_l622_c622)
                    tmp_arg_21_out = (((ydthf_0_in_r2es * tmp_call_39_0_in) / ydthf_1_in_r2es) * tmp_call_40_0_in);
                    ///////////////////

                    __state->__6_tmp_arg_21 = tmp_arg_21_out;
                }
                {
                    double tmp_arg_20_0_in = __state->__6_tmp_arg_20;
                    double tmp_arg_21_0_in = __state->__6_tmp_arg_21;
                    double tmp_call_38_out;

                    ///////////////////
                    // Tasklet code (T_l622_c622)
                    tmp_call_38_out = min(tmp_arg_20_0_in, tmp_arg_21_0_in);
                    ///////////////////

                    __state->__6_tmp_call_38 = tmp_call_38_out;
                }
                {
                    double tmp_call_38_0_in = __state->__6_tmp_call_38;
                    double zfokoop_out_0;

                    ///////////////////
                    // Tasklet code (T_l622_c622)
                    zfokoop_out_0 = tmp_call_38_0_in;
                    ///////////////////

                    __state->__6_zfokoop[(_for_it_28 - 1)] = zfokoop_out_0;
                }
            }
        }
        for (_for_it_29 = 1; (_for_it_29 <= icend); _for_it_29 = (_for_it_29 + 1)) {
            {
                {
                    double ydcst_0_in_rtt = v_ydcst_rtt[0];
                    int ydecldp_var_47_0_in_nssopt = v_ydecldp_var_47_nssopt[0];
                    double ztp1_0_in_0 = __state->__6_ztp1[((_for_it_29 + (sym_klon * (_for_it_23 - 1))) - 1)];
                    double _if_cond_10_out;

                    ///////////////////
                    // Tasklet code (T_l0_c0)
                    _if_cond_10_out = ((ztp1_0_in_0 >= ydcst_0_in_rtt) || (ydecldp_var_47_0_in_nssopt == 0));
                    ///////////////////

                    __state->__6__if_cond_10 = _if_cond_10_out;
                }
            }
            if ((__state->__6__if_cond_10 == 1)) {
                zfac = 1.0;
                {
                    {
                        double zfaci_out;

                        ///////////////////
                        // Tasklet code (T_l627_c627)
                        zfaci_out = 1.0;
                        ///////////////////

                        __state->__6_zfaci = zfaci_out;
                    }
                }
            } else if ((!(__state->__6__if_cond_10 == 1))) {
                zfac =
                    (__state->__6_za[((_for_it_29 + (sym_klon * (_for_it_23 - 1))) - 1)] +
                     (__state->__6_zfokoop[(_for_it_29 - 1)] * (1.0 - __state->__6_za[((_for_it_29 + (sym_klon * (_for_it_23 - 1))) - 1)])));
                {
                    double* v_ydecldp_var_47_rkooptau;
                    v_ydecldp_var_47_rkooptau = (double*)(&(ydecldp_var_47->rkooptau));

                    {
                        double ptsphy_var_5_0_in = ptsphy_var_5[0];
                        double ydecldp_var_47_0_in_rkooptau = v_ydecldp_var_47_rkooptau[0];
                        double zfaci_out;

                        ///////////////////
                        // Tasklet code (T_l630_c630)
                        zfaci_out = (ptsphy_var_5_0_in / ydecldp_var_47_0_in_rkooptau);
                        ///////////////////

                        __state->__6_zfaci = zfaci_out;
                    }
                }
            }
            {
                {
                    double ydecldp_var_47_0_in_ramin = v_ydecldp_var_47_ramin[0];
                    double za_0_in_0 = __state->__6_za[((_for_it_29 + (sym_klon * (_for_it_23 - 1))) - 1)];
                    double _if_cond_11_out;

                    ///////////////////
                    // Tasklet code (T_l0_c0)
                    _if_cond_11_out = (za_0_in_0 > (1.0 - ydecldp_var_47_0_in_ramin));
                    ///////////////////

                    __state->__6__if_cond_11 = _if_cond_11_out;
                }
            }
            if ((__state->__6__if_cond_11 == 1)) {
                {
                    {
                        double zcorqsice_0_in_0 = __state->__6_zcorqsice[(_for_it_29 - 1)];
                        double zqsice_0_in_0 = __state->__6_zqsice[((_for_it_29 + (sym_klon * (_for_it_23 - 1))) - 1)];
                        double zqx_0_in_0 = __state->__6_zqx[(((_for_it_29 + ((4 * sym_klev) * sym_klon)) + (sym_klon * (_for_it_23 - 1))) - 1)];
                        double tmp_arg_22_out;

                        ///////////////////
                        // Tasklet code (T_l633_c633)
                        tmp_arg_22_out = ((zqx_0_in_0 - (zfac * zqsice_0_in_0)) / zcorqsice_0_in_0);
                        ///////////////////

                        __state->__6_tmp_arg_22 = tmp_arg_22_out;
                    }
                    {
                        double tmp_arg_22_0_in = __state->__6_tmp_arg_22;
                        double tmp_call_41_out;

                        ///////////////////
                        // Tasklet code (T_l633_c633)
                        tmp_call_41_out = max(tmp_arg_22_0_in, 0.0);
                        ///////////////////

                        __state->__6_tmp_call_41 = tmp_call_41_out;
                    }
                    {
                        double tmp_call_41_0_in = __state->__6_tmp_call_41;
                        double zsupsat_out_0;

                        ///////////////////
                        // Tasklet code (T_l633_c633)
                        zsupsat_out_0 = tmp_call_41_0_in;
                        ///////////////////

                        __state->__6_zsupsat[(_for_it_29 - 1)] = zsupsat_out_0;
                    }
                }
            } else if ((!(__state->__6__if_cond_11 == 1))) {
                {
                    {
                        double za_0_in_0 = __state->__6_za[((_for_it_29 + (sym_klon * (_for_it_23 - 1))) - 1)];
                        double tmp_arg_23_out;

                        ///////////////////
                        // Tasklet code (T_l635_c635)
                        tmp_arg_23_out = (1.0 - za_0_in_0);
                        ///////////////////

                        __state->__6_tmp_arg_23 = tmp_arg_23_out;
                    }
                    {
                        double tmp_arg_23_0_in = __state->__6_tmp_arg_23;
                        double zepsilon_0_in = __state->__6_zepsilon;
                        double tmp_call_42_out;

                        ///////////////////
                        // Tasklet code (T_l635_c635)
                        tmp_call_42_out = max(tmp_arg_23_0_in, zepsilon_0_in);
                        ///////////////////

                        __state->__6_tmp_call_42 = tmp_call_42_out;
                    }
                    {
                        double tmp_call_42_0_in = __state->__6_tmp_call_42;
                        double za_0_in_0 = __state->__6_za[((_for_it_29 + (sym_klon * (_for_it_23 - 1))) - 1)];
                        double zqsice_0_in_0 = __state->__6_zqsice[((_for_it_29 + (sym_klon * (_for_it_23 - 1))) - 1)];
                        double zqx_0_in_0 = __state->__6_zqx[(((_for_it_29 + ((4 * sym_klev) * sym_klon)) + (sym_klon * (_for_it_23 - 1))) - 1)];
                        double zqp1env_out;

                        ///////////////////
                        // Tasklet code (T_l635_c635)
                        zqp1env_out = ((zqx_0_in_0 - (za_0_in_0 * zqsice_0_in_0)) / tmp_call_42_0_in);
                        ///////////////////

                        __state->__6_zqp1env = zqp1env_out;
                    }
                    {
                        double za_0_in_0 = __state->__6_za[((_for_it_29 + (sym_klon * (_for_it_23 - 1))) - 1)];
                        double zcorqsice_0_in_0 = __state->__6_zcorqsice[(_for_it_29 - 1)];
                        double zqp1env_0_in = __state->__6_zqp1env;
                        double zqsice_0_in_0 = __state->__6_zqsice[((_for_it_29 + (sym_klon * (_for_it_23 - 1))) - 1)];
                        double tmp_arg_24_out;

                        ///////////////////
                        // Tasklet code (T_l636_c636)
                        tmp_arg_24_out = (((1.0 - za_0_in_0) * (zqp1env_0_in - (zfac * zqsice_0_in_0))) / zcorqsice_0_in_0);
                        ///////////////////

                        __state->__6_tmp_arg_24 = tmp_arg_24_out;
                    }
                    {
                        double tmp_arg_24_0_in = __state->__6_tmp_arg_24;
                        double tmp_call_43_out;

                        ///////////////////
                        // Tasklet code (T_l636_c636)
                        tmp_call_43_out = max(tmp_arg_24_0_in, 0.0);
                        ///////////////////

                        __state->__6_tmp_call_43 = tmp_call_43_out;
                    }
                    {
                        double tmp_call_43_0_in = __state->__6_tmp_call_43;
                        double zsupsat_out_0;

                        ///////////////////
                        // Tasklet code (T_l636_c636)
                        zsupsat_out_0 = tmp_call_43_0_in;
                        ///////////////////

                        __state->__6_zsupsat[(_for_it_29 - 1)] = zsupsat_out_0;
                    }
                }
            }
            _if_cond_12 = (__state->__6_zsupsat[(_for_it_29 - 1)] > 1e-14);
            if ((_if_cond_12 == 1)) {
                {
                    {
                        double ydecldp_var_47_0_in_rthomo = v_ydecldp_var_47_rthomo[0];
                        double ztp1_0_in_0 = __state->__6_ztp1[((_for_it_29 + (sym_klon * (_for_it_23 - 1))) - 1)];
                        double _if_cond_13_out;

                        ///////////////////
                        // Tasklet code (T_l0_c0)
                        _if_cond_13_out = (ztp1_0_in_0 > ydecldp_var_47_0_in_rthomo);
                        ///////////////////

                        __state->__6__if_cond_13 = _if_cond_13_out;
                    }
                }
                if ((__state->__6__if_cond_13 == 1)) {
                    {
                        {
                            double zsolqa_0_in_0 = __state->__6_zsolqa[((_for_it_29 + (20 * sym_klon)) - 1)];
                            double zsupsat_0_in_0 = __state->__6_zsupsat[(_for_it_29 - 1)];
                            double zsolqa_out_0;

                            ///////////////////
                            // Tasklet code (T_l640_c640)
                            zsolqa_out_0 = (zsolqa_0_in_0 + zsupsat_0_in_0);
                            ///////////////////

                            __state->__6_zsolqa[((_for_it_29 + (20 * sym_klon)) - 1)] = zsolqa_out_0;
                        }
                        {
                            double zsolqa_0_in_0 = __state->__6_zsolqa[((_for_it_29 + (4 * sym_klon)) - 1)];
                            double zsupsat_0_in_0 = __state->__6_zsupsat[(_for_it_29 - 1)];
                            double zsolqa_out_0;

                            ///////////////////
                            // Tasklet code (T_l641_c641)
                            zsolqa_out_0 = (zsolqa_0_in_0 - zsupsat_0_in_0);
                            ///////////////////

                            __state->__6_zsolqa[((_for_it_29 + (4 * sym_klon)) - 1)] = zsolqa_out_0;
                        }
                        {
                            double zqxfg_0_in_0 = __state->__6_zqxfg[(_for_it_29 - 1)];
                            double zsupsat_0_in_0 = __state->__6_zsupsat[(_for_it_29 - 1)];
                            double zqxfg_out_0;

                            ///////////////////
                            // Tasklet code (T_l642_c642)
                            zqxfg_out_0 = (zqxfg_0_in_0 + zsupsat_0_in_0);
                            ///////////////////

                            __state->__6_zqxfg[(_for_it_29 - 1)] = zqxfg_out_0;
                        }
                    }
                } else if ((!(__state->__6__if_cond_13 == 1))) {
                    {
                        {
                            double zsolqa_0_in_0 = __state->__6_zsolqa[((_for_it_29 + (21 * sym_klon)) - 1)];
                            double zsupsat_0_in_0 = __state->__6_zsupsat[(_for_it_29 - 1)];
                            double zsolqa_out_0;

                            ///////////////////
                            // Tasklet code (T_l644_c644)
                            zsolqa_out_0 = (zsolqa_0_in_0 + zsupsat_0_in_0);
                            ///////////////////

                            __state->__6_zsolqa[((_for_it_29 + (21 * sym_klon)) - 1)] = zsolqa_out_0;
                        }
                        {
                            double zsolqa_0_in_0 = __state->__6_zsolqa[((_for_it_29 + (9 * sym_klon)) - 1)];
                            double zsupsat_0_in_0 = __state->__6_zsupsat[(_for_it_29 - 1)];
                            double zsolqa_out_0;

                            ///////////////////
                            // Tasklet code (T_l645_c645)
                            zsolqa_out_0 = (zsolqa_0_in_0 - zsupsat_0_in_0);
                            ///////////////////

                            __state->__6_zsolqa[((_for_it_29 + (9 * sym_klon)) - 1)] = zsolqa_out_0;
                        }
                        {
                            double zqxfg_0_in_0 = __state->__6_zqxfg[((_for_it_29 + sym_klon) - 1)];
                            double zsupsat_0_in_0 = __state->__6_zsupsat[(_for_it_29 - 1)];
                            double zqxfg_out_0;

                            ///////////////////
                            // Tasklet code (T_l646_c646)
                            zqxfg_out_0 = (zqxfg_0_in_0 + zsupsat_0_in_0);
                            ///////////////////

                            __state->__6_zqxfg[((_for_it_29 + sym_klon) - 1)] = zqxfg_out_0;
                        }
                    }
                }
                {
                    {
                        double za_0_in_0 = __state->__6_za[((_for_it_29 + (sym_klon * (_for_it_23 - 1))) - 1)];
                        double zfaci_0_in = __state->__6_zfaci;
                        double zsolac_out_0;

                        ///////////////////
                        // Tasklet code (T_l648_c648)
                        zsolac_out_0 = ((1.0 - za_0_in_0) * zfaci_0_in);
                        ///////////////////

                        __state->__6_zsolac[(_for_it_29 - 1)] = zsolac_out_0;
                    }
                }
            }
            _if_cond_14 = (psupsat_var_30[((_for_it_29 + (sym_klon * (_for_it_23 - 1))) - 1)] > 1e-14);
            if ((_if_cond_14 == 1)) {
                {
                    {
                        double ydecldp_var_47_0_in_rthomo = v_ydecldp_var_47_rthomo[0];
                        double ztp1_0_in_0 = __state->__6_ztp1[((_for_it_29 + (sym_klon * (_for_it_23 - 1))) - 1)];
                        double _if_cond_15_out;

                        ///////////////////
                        // Tasklet code (T_l0_c0)
                        _if_cond_15_out = (ztp1_0_in_0 > ydecldp_var_47_0_in_rthomo);
                        ///////////////////

                        __state->__6__if_cond_15 = _if_cond_15_out;
                    }
                }
                if ((!(__state->__6__if_cond_15 == 1))) {
                    {
                        {
                            double psupsat_var_30_0_in_0 = psupsat_var_30[((_for_it_29 + (sym_klon * (_for_it_23 - 1))) - 1)];
                            double zsolqa_0_in_0 = __state->__6_zsolqa[((_for_it_29 + (6 * sym_klon)) - 1)];
                            double zsolqa_out_0;

                            ///////////////////
                            // Tasklet code (T_l656_c656)
                            zsolqa_out_0 = (zsolqa_0_in_0 + psupsat_var_30_0_in_0);
                            ///////////////////

                            __state->__6_zsolqa[((_for_it_29 + (6 * sym_klon)) - 1)] = zsolqa_out_0;
                        }
                        {
                            double psupsat_var_30_0_in_0 = psupsat_var_30[((_for_it_29 + (sym_klon * (_for_it_23 - 1))) - 1)];
                            double zpsupsatsrce_out_0;

                            ///////////////////
                            // Tasklet code (T_l657_c657)
                            zpsupsatsrce_out_0 = psupsat_var_30_0_in_0;
                            ///////////////////

                            __state->__6_zpsupsatsrce[((_for_it_29 + sym_klon) - 1)] = zpsupsatsrce_out_0;
                        }
                        {
                            double psupsat_var_30_0_in_0 = psupsat_var_30[((_for_it_29 + (sym_klon * (_for_it_23 - 1))) - 1)];
                            double zqxfg_0_in_0 = __state->__6_zqxfg[((_for_it_29 + sym_klon) - 1)];
                            double zqxfg_out_0;

                            ///////////////////
                            // Tasklet code (T_l658_c658)
                            zqxfg_out_0 = (zqxfg_0_in_0 + psupsat_var_30_0_in_0);
                            ///////////////////

                            __state->__6_zqxfg[((_for_it_29 + sym_klon) - 1)] = zqxfg_out_0;
                        }
                    }
                } else if ((__state->__6__if_cond_15 == 1)) {
                    {
                        {
                            double psupsat_var_30_0_in_0 = psupsat_var_30[((_for_it_29 + (sym_klon * (_for_it_23 - 1))) - 1)];
                            double zsolqa_0_in_0 = __state->__6_zsolqa[(_for_it_29 - 1)];
                            double zsolqa_out_0;

                            ///////////////////
                            // Tasklet code (T_l652_c652)
                            zsolqa_out_0 = (zsolqa_0_in_0 + psupsat_var_30_0_in_0);
                            ///////////////////

                            __state->__6_zsolqa[(_for_it_29 - 1)] = zsolqa_out_0;
                        }
                        {
                            double psupsat_var_30_0_in_0 = psupsat_var_30[((_for_it_29 + (sym_klon * (_for_it_23 - 1))) - 1)];
                            double zpsupsatsrce_out_0;

                            ///////////////////
                            // Tasklet code (T_l653_c653)
                            zpsupsatsrce_out_0 = psupsat_var_30_0_in_0;
                            ///////////////////

                            __state->__6_zpsupsatsrce[(_for_it_29 - 1)] = zpsupsatsrce_out_0;
                        }
                        {
                            double psupsat_var_30_0_in_0 = psupsat_var_30[((_for_it_29 + (sym_klon * (_for_it_23 - 1))) - 1)];
                            double zqxfg_0_in_0 = __state->__6_zqxfg[(_for_it_29 - 1)];
                            double zqxfg_out_0;

                            ///////////////////
                            // Tasklet code (T_l654_c654)
                            zqxfg_out_0 = (zqxfg_0_in_0 + psupsat_var_30_0_in_0);
                            ///////////////////

                            __state->__6_zqxfg[(_for_it_29 - 1)] = zqxfg_out_0;
                        }
                    }
                }
                {
                    {
                        double za_0_in_0 = __state->__6_za[((_for_it_29 + (sym_klon * (_for_it_23 - 1))) - 1)];
                        double zfaci_0_in = __state->__6_zfaci;
                        double zsolac_out_0;

                        ///////////////////
                        // Tasklet code (T_l660_c660)
                        zsolac_out_0 = ((1.0 - za_0_in_0) * zfaci_0_in);
                        ///////////////////

                        __state->__6_zsolac[(_for_it_29 - 1)] = zsolac_out_0;
                    }
                }
            }
        }
        {
            {
                int klev_0_in = klev[0];
                int ydecldp_var_47_0_in_ncldtop = v_ydecldp_var_47_ncldtop[0];
                int _if_cond_16_out;

                ///////////////////
                // Tasklet code (T_l0_c0)
                _if_cond_16_out = ((_for_it_23 < klev_0_in) && (_for_it_23 >= ydecldp_var_47_0_in_ncldtop));
                ///////////////////

                __state->__6__if_cond_16 = _if_cond_16_out;
            }
        }
        if ((__state->__6__if_cond_16 == 1)) {
            {
                {
#pragma omp parallel for
                    for (auto _for_it_30 = 1; _for_it_30 < (icend + 1); _for_it_30 += 1) {
                        loop_body_358_0_0(
                            __state, &ldcum_var_20[(_for_it_30 - 1)], &plu_var_22[(((_for_it_23 * sym_klon) + _for_it_30) - 1)], &psnde_var_24[((_for_it_30 + (sym_klon * (_for_it_23 - 1))) - 1)],
                            ydecldp_var_47, &__state->__6_zdtgdp[(_for_it_30 - 1)], &__state->__6_zfoealfa[((_for_it_30 + (sym_klon * (_for_it_23 - 1))) - 1)],
                            &plude_var_23[((_for_it_30 + (sym_klon * (_for_it_23 - 1))) - 1)], &__state->__6_zconvsrce[(_for_it_30 - 1)], &__state->__6_zsolac[(_for_it_30 - 1)],
                            &__state->__6_zsolqa[(_for_it_30 - 1)], sym_klon);
                    }
                }
            }
        }
        {
            {
                int ydecldp_var_47_0_in_ncldtop = v_ydecldp_var_47_ncldtop[0];
                int _if_cond_19_out;

                ///////////////////
                // Tasklet code (T_l0_c0)
                _if_cond_19_out = (_for_it_23 > ydecldp_var_47_0_in_ncldtop);
                ///////////////////

                __state->__6__if_cond_19 = _if_cond_19_out;
            }
        }
        if ((__state->__6__if_cond_19 == 1)) {
            {
                {
#pragma omp parallel for
                    for (auto _for_it_31 = 1; _for_it_31 < (icend + 1); _for_it_31 += 1) {
                        loop_body_343_2_0(
                            __state, &pmfd_var_26[((_for_it_31 + (sym_klon * (_for_it_23 - 1))) - 1)], &pmfu_var_25[((_for_it_31 + (sym_klon * (_for_it_23 - 1))) - 1)],
                            &__state->__6_zanewm1[(_for_it_31 - 1)], &__state->__6_zdtgdp[(_for_it_31 - 1)], &__state->__6_zacust[(_for_it_31 - 1)], &__state->__6_zmf[(_for_it_31 - 1)], sym_klon);
                    }
                }
                {
#pragma omp parallel for
                    for (auto _for_it_32 = 1; _for_it_32 < 6; _for_it_32 += 1) {
                        loop_body_343_2_10(
                            __state, &__state->__6_iphase[(_for_it_32 - 1)], &__state->__6_llfall[(_for_it_32 - 1)], &__state->__6_zmf[0], &__state->__6_zqxnm1[(sym_klon * (_for_it_32 - 1))],
                            &__state->__6_zconvsrce[(sym_klon * (_for_it_32 - 1))], &__state->__6_zlcust[(sym_klon * (_for_it_32 - 1))], icend, sym_klon);
                    }
                }
            }
            for (_for_it_34 = 1; (_for_it_34 <= icend); _for_it_34 = (_for_it_34 + 1)) {
                {
                    {
                        double paph_var_18_0_in_0 = paph_var_18[((_for_it_34 + (sym_klon * (_for_it_23 - 1))) - 1)];
                        double zrdcp_0_in = __state->__6_zrdcp;
                        double ztp1_0_in_0 = __state->__6_ztp1[((_for_it_34 + (sym_klon * (_for_it_23 - 2))) - 1)];
                        double ztp1_1_in_0 = __state->__6_ztp1[((_for_it_34 + (sym_klon * (_for_it_23 - 1))) - 1)];
                        double zdtdp_out;

                        ///////////////////
                        // Tasklet code (T_l693_c693)
                        zdtdp_out = (((zrdcp_0_in * 0.5) * (ztp1_0_in_0 + ztp1_1_in_0)) / paph_var_18_0_in_0);
                        ///////////////////

                        __state->__6_zdtdp = zdtdp_out;
                    }
                    {
                        double pap_var_17_0_in_0 = pap_var_17[((_for_it_34 + (sym_klon * (_for_it_23 - 1))) - 1)];
                        double pap_var_17_1_in_0 = pap_var_17[((_for_it_34 + (sym_klon * (_for_it_23 - 2))) - 1)];
                        double zdtdp_0_in = __state->__6_zdtdp;
                        double zdtforc_out;

                        ///////////////////
                        // Tasklet code (T_l694_c694)
                        zdtforc_out = (zdtdp_0_in * (pap_var_17_0_in_0 - pap_var_17_1_in_0));
                        ///////////////////

                        __state->__6_zdtforc = zdtforc_out;
                    }
                    {
                        double zanewm1_0_in_0 = __state->__6_zanewm1[(_for_it_34 - 1)];
                        double zdqsmixdt_0_in_0 = __state->__6_zdqsmixdt[(_for_it_34 - 1)];
                        double zdtforc_0_in = __state->__6_zdtforc;
                        double zdqs_out_0;

                        ///////////////////
                        // Tasklet code (T_l695_c695)
                        zdqs_out_0 = ((zanewm1_0_in_0 * zdtforc_0_in) * zdqsmixdt_0_in_0);
                        ///////////////////

                        __state->__6_zdqs[(_for_it_34 - 1)] = zdqs_out_0;
                    }
                }
            }
            for (_for_it_35 = 1; (_for_it_35 <= 5); _for_it_35 = (_for_it_35 + 1)) {
                _if_cond_21 = ((1 - __state->__6_llfall[(_for_it_35 - 1)]) && (__state->__6_iphase[(_for_it_35 - 1)] > 0));
                if ((_if_cond_21 == 1)) {
                    for (_for_it_36 = 1; (_for_it_36 <= icend); _for_it_36 = (_for_it_36 + 1)) {
                        {
                            {
                                double zdqs_0_in_0 = __state->__6_zdqs[(_for_it_36 - 1)];
                                double zlcust_0_in_0 = __state->__6_zlcust[((_for_it_36 + (sym_klon * (_for_it_35 - 1))) - 1)];
                                double tmp_arg_26_out;

                                ///////////////////
                                // Tasklet code (T_l700_c700)
                                tmp_arg_26_out = (zlcust_0_in_0 - zdqs_0_in_0);
                                ///////////////////

                                __state->__6_tmp_arg_26 = tmp_arg_26_out;
                            }
                            {
                                double tmp_arg_26_0_in = __state->__6_tmp_arg_26;
                                double zlfinal_out;

                                ///////////////////
                                // Tasklet code (T_l700_c700)
                                zlfinal_out = max(0.0, tmp_arg_26_0_in);
                                ///////////////////

                                __state->__6_zlfinal = zlfinal_out;
                            }
                            {
                                double zlcust_0_in_0 = __state->__6_zlcust[((_for_it_36 + (sym_klon * (_for_it_35 - 1))) - 1)];
                                double zlfinal_0_in = __state->__6_zlfinal;
                                double tmp_arg_27_out;

                                ///////////////////
                                // Tasklet code (T_l701_c701)
                                tmp_arg_27_out = (zlcust_0_in_0 - zlfinal_0_in);
                                ///////////////////

                                __state->__6_tmp_arg_27 = tmp_arg_27_out;
                            }
                            {
                                double tmp_arg_27_0_in = __state->__6_tmp_arg_27;
                                double zevaplimmix_0_in_0 = __state->__6_zevaplimmix[(_for_it_36 - 1)];
                                double zevap_out;

                                ///////////////////
                                // Tasklet code (T_l701_c701)
                                zevap_out = min(tmp_arg_27_0_in, zevaplimmix_0_in_0);
                                ///////////////////

                                __state->__6_zevap = zevap_out;
                            }
                            {
                                double zevap_0_in = __state->__6_zevap;
                                double zlcust_0_in_0 = __state->__6_zlcust[((_for_it_36 + (sym_klon * (_for_it_35 - 1))) - 1)];
                                double zlfinal_out;

                                ///////////////////
                                // Tasklet code (T_l702_c702)
                                zlfinal_out = (zlcust_0_in_0 - zevap_0_in);
                                ///////////////////

                                __state->__6_zlfinal = zlfinal_out;
                            }
                            {
                                double zlfinal_0_in = __state->__6_zlfinal;
                                double zlfinalsum_0_in_0 = __state->__6_zlfinalsum[(_for_it_36 - 1)];
                                double zlfinalsum_out_0;

                                ///////////////////
                                // Tasklet code (T_l703_c703)
                                zlfinalsum_out_0 = (zlfinalsum_0_in_0 + zlfinal_0_in);
                                ///////////////////

                                __state->__6_zlfinalsum[(_for_it_36 - 1)] = zlfinalsum_out_0;
                            }
                            {
                                double zlcust_0_in_0 = __state->__6_zlcust[((_for_it_36 + (sym_klon * (_for_it_35 - 1))) - 1)];
                                double zsolqa_0_in_0 = __state->__6_zsolqa[((_for_it_36 + ((6 * sym_klon) * (_for_it_35 - 1))) - 1)];
                                double zsolqa_out_0;

                                ///////////////////
                                // Tasklet code (T_l704_c704)
                                zsolqa_out_0 = (zsolqa_0_in_0 + zlcust_0_in_0);
                                ///////////////////

                                __state->__6_zsolqa[((_for_it_36 + ((6 * sym_klon) * (_for_it_35 - 1))) - 1)] = zsolqa_out_0;
                            }
                            {
                                double zevap_0_in = __state->__6_zevap;
                                double zsolqa_0_in_0 = __state->__6_zsolqa[(((_for_it_36 + ((5 * sym_klon) * (_for_it_35 - 1))) + (4 * sym_klon)) - 1)];
                                double zsolqa_out_0;

                                ///////////////////
                                // Tasklet code (T_l705_c705)
                                zsolqa_out_0 = (zsolqa_0_in_0 + zevap_0_in);
                                ///////////////////

                                __state->__6_zsolqa[(((_for_it_36 + ((5 * sym_klon) * (_for_it_35 - 1))) + (4 * sym_klon)) - 1)] = zsolqa_out_0;
                            }
                            {
                                double zevap_0_in = __state->__6_zevap;
                                double zsolqa_0_in_0 = __state->__6_zsolqa[(((_for_it_36 + (sym_klon * (_for_it_35 - 1))) + (20 * sym_klon)) - 1)];
                                double zsolqa_out_0;

                                ///////////////////
                                // Tasklet code (T_l706_c706)
                                zsolqa_out_0 = (zsolqa_0_in_0 - zevap_0_in);
                                ///////////////////

                                __state->__6_zsolqa[(((_for_it_36 + (sym_klon * (_for_it_35 - 1))) + (20 * sym_klon)) - 1)] = zsolqa_out_0;
                            }
                        }
                    }
                }
            }
            {
                {
#pragma omp parallel for
                    for (auto _for_it_37 = 1; _for_it_37 < (icend + 1); _for_it_37 += 1) {
                        loop_body_343_1_0(__state, &__state->__6_zlfinalsum[(_for_it_37 - 1)], &__state->__6_zacust[(_for_it_37 - 1)], &__state->__6_zsolac[(_for_it_37 - 1)]);
                    }
                }
            }
        }
        for (_for_it_38 = 1; (_for_it_38 <= icend); _for_it_38 = (_for_it_38 + 1)) {
            _if_cond_23 = (_for_it_23 < klev[0]);
            if ((_if_cond_23 == 1)) {
                {
                    {
                        double pmfd_var_26_0_in_0 = pmfd_var_26[(((_for_it_23 * sym_klon) + _for_it_38) - 1)];
                        double pmfu_var_25_0_in_0 = pmfu_var_25[(((_for_it_23 * sym_klon) + _for_it_38) - 1)];
                        double zdtgdp_0_in_0 = __state->__6_zdtgdp[(_for_it_38 - 1)];
                        double tmp_arg_28_out;

                        ///////////////////
                        // Tasklet code (T_l717_c717)
                        tmp_arg_28_out = ((pmfu_var_25_0_in_0 + pmfd_var_26_0_in_0) * zdtgdp_0_in_0);
                        ///////////////////

                        __state->__6_tmp_arg_28 = tmp_arg_28_out;
                    }
                    {
                        double tmp_arg_28_0_in = __state->__6_tmp_arg_28;
                        double zmfdn_out;

                        ///////////////////
                        // Tasklet code (T_l717_c717)
                        zmfdn_out = max(0.0, tmp_arg_28_0_in);
                        ///////////////////

                        __state->__6_zmfdn = zmfdn_out;
                    }
                    {
                        double zmfdn_0_in = __state->__6_zmfdn;
                        double zconvsink_out_0;

                        ///////////////////
                        // Tasklet code (T_l721_c721)
                        zconvsink_out_0 = zmfdn_0_in;
                        ///////////////////

                        __state->__6_zconvsink[(_for_it_38 - 1)] = zconvsink_out_0;
                    }
                    {
                        double zmfdn_0_in = __state->__6_zmfdn;
                        double zconvsink_out_0;

                        ///////////////////
                        // Tasklet code (T_l722_c722)
                        zconvsink_out_0 = zmfdn_0_in;
                        ///////////////////

                        __state->__6_zconvsink[((_for_it_38 + sym_klon) - 1)] = zconvsink_out_0;
                    }
                    {
                        double zmfdn_0_in = __state->__6_zmfdn;
                        double zsolab_0_in_0 = __state->__6_zsolab[(_for_it_38 - 1)];
                        double zsolab_out_0;

                        ///////////////////
                        // Tasklet code (T_l718_c718)
                        zsolab_out_0 = (zsolab_0_in_0 + zmfdn_0_in);
                        ///////////////////

                        __state->__6_zsolab[(_for_it_38 - 1)] = zsolab_out_0;
                    }
                    {
                        double zmfdn_0_in = __state->__6_zmfdn;
                        double zsolqb_0_in_0 = __state->__6_zsolqb[(_for_it_38 - 1)];
                        double zsolqb_out_0;

                        ///////////////////
                        // Tasklet code (T_l719_c719)
                        zsolqb_out_0 = (zsolqb_0_in_0 + zmfdn_0_in);
                        ///////////////////

                        __state->__6_zsolqb[(_for_it_38 - 1)] = zsolqb_out_0;
                    }
                    {
                        double zmfdn_0_in = __state->__6_zmfdn;
                        double zsolqb_0_in_0 = __state->__6_zsolqb[((_for_it_38 + (6 * sym_klon)) - 1)];
                        double zsolqb_out_0;

                        ///////////////////
                        // Tasklet code (T_l720_c720)
                        zsolqb_out_0 = (zsolqb_0_in_0 + zmfdn_0_in);
                        ///////////////////

                        __state->__6_zsolqb[((_for_it_38 + (6 * sym_klon)) - 1)] = zsolqb_out_0;
                    }
                }
            }
        }
        {
            {
#pragma omp parallel for
                for (auto _for_it_39 = 1; _for_it_39 < (icend + 1); _for_it_39 += 1) {
                    loop_body_50_11_0(
                        __state, &ktype_var_21[(_for_it_39 - 1)], &plude_var_23[((_for_it_39 + (sym_klon * (_for_it_23 - 1))) - 1)], &ptsphy_var_5[0], ydecldp_var_47,
                        &__state->__6_zldifdt[(_for_it_39 - 1)], sym_klon);
                }
            }
            {
#pragma omp parallel for
                for (auto _for_it_40 = 1; _for_it_40 < (icend + 1); _for_it_40 += 1) {
                    loop_body_50_11_9(
                        __state, &__state->__6_za[((_for_it_40 + (sym_klon * (_for_it_23 - 1))) - 1)], &__state->__6_zevaplimmix[(_for_it_40 - 1)],
                        &__state->__6_zicefrac[((_for_it_40 + (sym_klon * (_for_it_23 - 1))) - 1)], &__state->__6_zldifdt[(_for_it_40 - 1)],
                        &__state->__6_zli[((_for_it_40 + (sym_klon * (_for_it_23 - 1))) - 1)], &__state->__6_zlicld[(_for_it_40 - 1)],
                        &__state->__6_zliqfrac[((_for_it_40 + (sym_klon * (_for_it_23 - 1))) - 1)], &__state->__6_zqsmix[((_for_it_40 + (sym_klon * (_for_it_23 - 1))) - 1)],
                        &__state->__6_zqx[(((_for_it_40 + ((4 * sym_klev) * sym_klon)) + (sym_klon * (_for_it_23 - 1))) - 1)], &__state->__6_zsolac[(_for_it_40 - 1)],
                        &__state->__6_zsolqa[(_for_it_40 - 1)], sym_klev, sym_klon);
                }
            }
        }
        for (_for_it_41 = 1; (_for_it_41 <= icend); _for_it_41 = (_for_it_41 + 1)) {
            {
                {
                    double pap_var_17_0_in_0 = pap_var_17[((_for_it_41 + (sym_klon * (_for_it_23 - 1))) - 1)];
                    double zrdcp_0_in = __state->__6_zrdcp;
                    double ztp1_0_in_0 = __state->__6_ztp1[((_for_it_41 + (sym_klon * (_for_it_23 - 1))) - 1)];
                    double zdtdp_out;

                    ///////////////////
                    // Tasklet code (T_l744_c744)
                    zdtdp_out = ((zrdcp_0_in * ztp1_0_in_0) / pap_var_17_0_in_0);
                    ///////////////////

                    __state->__6_zdtdp = zdtdp_out;
                }
                {
                    double zdp_0_in_0 = __state->__6_zdp[(_for_it_41 - 1)];
                    double zqtmst_0_in = __state->__6_zqtmst;
                    double zdpmxdt_out;

                    ///////////////////
                    // Tasklet code (T_l745_c745)
                    zdpmxdt_out = (zdp_0_in_0 * zqtmst_0_in);
                    ///////////////////

                    __state->__6_zdpmxdt = zdpmxdt_out;
                }
                {
                    double zmfdn_out;

                    ///////////////////
                    // Tasklet code (T_l746_c746)
                    zmfdn_out = 0.0;
                    ///////////////////

                    __state->__6_zmfdn = zmfdn_out;
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
                        // Tasklet code (T_l747_c747)
                        zmfdn_out = (pmfu_var_25_0_in_0 + pmfd_var_26_0_in_0);
                        ///////////////////

                        __state->__6_zmfdn = zmfdn_out;
                    }
                }
            }
            {
                double* v_ydthf_ralfdcp;
                v_ydthf_ralfdcp = (double*)(&(ydthf->ralfdcp));

                {
                    double pmfd_var_26_0_in_0 = pmfd_var_26[((_for_it_41 + (sym_klon * (_for_it_23 - 1))) - 1)];
                    double pmfu_var_25_0_in_0 = pmfu_var_25[((_for_it_41 + (sym_klon * (_for_it_23 - 1))) - 1)];
                    double pvervel_var_16_0_in_0 = pvervel_var_16[((_for_it_41 + (sym_klon * (_for_it_23 - 1))) - 1)];
                    double ydcst_0_in_rg = v_ydcst_rg[0];
                    double zmfdn_0_in = __state->__6_zmfdn;
                    double zwtot_out;

                    ///////////////////
                    // Tasklet code (T_l748_c748)
                    zwtot_out = (pvervel_var_16_0_in_0 + ((0.5 * ydcst_0_in_rg) * ((pmfu_var_25_0_in_0 + pmfd_var_26_0_in_0) + zmfdn_0_in)));
                    ///////////////////

                    __state->__6_zwtot = zwtot_out;
                }
                {
                    double zdpmxdt_0_in = __state->__6_zdpmxdt;
                    double tmp_arg_30_out;

                    ///////////////////
                    // Tasklet code (T_l749_c749)
                    tmp_arg_30_out = (-zdpmxdt_0_in);
                    ///////////////////

                    __state->__6_tmp_arg_30 = tmp_arg_30_out;
                }
                {
                    double tmp_arg_30_0_in = __state->__6_tmp_arg_30;
                    double zwtot_0_in = __state->__6_zwtot;
                    double tmp_call_46_out;

                    ///////////////////
                    // Tasklet code (T_l749_c749)
                    tmp_call_46_out = max(tmp_arg_30_0_in, zwtot_0_in);
                    ///////////////////

                    __state->__6_tmp_call_46 = tmp_call_46_out;
                }
                {
                    double tmp_call_46_0_in = __state->__6_tmp_call_46;
                    double zdpmxdt_0_in = __state->__6_zdpmxdt;
                    double zwtot_out;

                    ///////////////////
                    // Tasklet code (T_l749_c749)
                    zwtot_out = min(zdpmxdt_0_in, tmp_call_46_0_in);
                    ///////////////////

                    __state->__6_zwtot = zwtot_out;
                }
                {
                    double phrlw_var_15_0_in_0 = phrlw_var_15[((_for_it_41 + (sym_klon * (_for_it_23 - 1))) - 1)];
                    double phrsw_var_14_0_in_0 = phrsw_var_14[((_for_it_41 + (sym_klon * (_for_it_23 - 1))) - 1)];
                    double zzzdt_out;

                    ///////////////////
                    // Tasklet code (T_l750_c750)
                    zzzdt_out = (phrsw_var_14_0_in_0 + phrlw_var_15_0_in_0);
                    ///////////////////

                    __state->__6_zzzdt = zzzdt_out;
                }
                {
                    double zdpmxdt_0_in = __state->__6_zdpmxdt;
                    double zdtdp_0_in = __state->__6_zdtdp;
                    double tmp_arg_31_out;

                    ///////////////////
                    // Tasklet code (T_l751_c751)
                    tmp_arg_31_out = (-(zdpmxdt_0_in * zdtdp_0_in));
                    ///////////////////

                    __state->__6_tmp_arg_31 = tmp_arg_31_out;
                }
                {
                    double tmp_arg_31_0_in = __state->__6_tmp_arg_31;
                    double zzzdt_0_in = __state->__6_zzzdt;
                    double tmp_call_49_out;

                    ///////////////////
                    // Tasklet code (T_l751_c751)
                    tmp_call_49_out = max(tmp_arg_31_0_in, zzzdt_0_in);
                    ///////////////////

                    __state->__6_tmp_call_49 = tmp_call_49_out;
                }
                {
                    double zdpmxdt_0_in = __state->__6_zdpmxdt;
                    double zdtdp_0_in = __state->__6_zdtdp;
                    double tmp_arg_32_out;

                    ///////////////////
                    // Tasklet code (T_l751_c751)
                    tmp_arg_32_out = (zdpmxdt_0_in * zdtdp_0_in);
                    ///////////////////

                    __state->__6_tmp_arg_32 = tmp_arg_32_out;
                }
                {
                    double tmp_arg_32_0_in = __state->__6_tmp_arg_32;
                    double tmp_call_49_0_in = __state->__6_tmp_call_49;
                    double tmp_call_47_out;

                    ///////////////////
                    // Tasklet code (T_l751_c751)
                    tmp_call_47_out = min(tmp_arg_32_0_in, tmp_call_49_0_in);
                    ///////////////////

                    __state->__6_tmp_call_47 = tmp_call_47_out;
                }
                {
                    double ptsphy_var_5_0_in = ptsphy_var_5[0];
                    double tmp_call_47_0_in = __state->__6_tmp_call_47;
                    double ydthf_0_in_ralfdcp = v_ydthf_ralfdcp[0];
                    double zldefr_0_in_0 = __state->__6_zldefr[(_for_it_41 - 1)];
                    double zdtdiab_out;

                    ///////////////////
                    // Tasklet code (T_l751_c751)
                    zdtdiab_out = ((tmp_call_47_0_in * ptsphy_var_5_0_in) + (ydthf_0_in_ralfdcp * zldefr_0_in_0));
                    ///////////////////

                    __state->__6_zdtdiab = zdtdiab_out;
                }
                {
                    double ptsphy_var_5_0_in = ptsphy_var_5[0];
                    double zdtdiab_0_in = __state->__6_zdtdiab;
                    double zdtdp_0_in = __state->__6_zdtdp;
                    double zwtot_0_in = __state->__6_zwtot;
                    double zdtforc_out;

                    ///////////////////
                    // Tasklet code (T_l752_c752)
                    zdtforc_out = (((zdtdp_0_in * zwtot_0_in) * ptsphy_var_5_0_in) + zdtdiab_0_in);
                    ///////////////////

                    __state->__6_zdtforc = zdtforc_out;
                }
                {
                    double zqsmix_0_in_0 = __state->__6_zqsmix[((_for_it_41 + (sym_klon * (_for_it_23 - 1))) - 1)];
                    double zqold_out_0;

                    ///////////////////
                    // Tasklet code (T_l753_c753)
                    zqold_out_0 = zqsmix_0_in_0;
                    ///////////////////

                    __state->__6_zqold[(_for_it_41 - 1)] = zqold_out_0;
                }
                {
                    double ztp1_0_in_0 = __state->__6_ztp1[((_for_it_41 + (sym_klon * (_for_it_23 - 1))) - 1)];
                    double ztold_out_0;

                    ///////////////////
                    // Tasklet code (T_l754_c754)
                    ztold_out_0 = ztp1_0_in_0;
                    ///////////////////

                    __state->__6_ztold[(_for_it_41 - 1)] = ztold_out_0;
                }
            }
            {
                {
                    double zdtforc_0_in = __state->__6_zdtforc;
                    double ztp1_0_in_0 = __state->__6_ztp1[((_for_it_41 + (sym_klon * (_for_it_23 - 1))) - 1)];
                    double ztp1_out_0;

                    ///////////////////
                    // Tasklet code (T_l755_c755)
                    ztp1_out_0 = (ztp1_0_in_0 + zdtforc_0_in);
                    ///////////////////

                    __state->__6_ztp1[((_for_it_41 + (sym_klon * (_for_it_23 - 1))) - 1)] = ztp1_out_0;
                }
                {
                    double ztp1_0_in_0 = __state->__6_ztp1[((_for_it_41 + (sym_klon * (_for_it_23 - 1))) - 1)];
                    double tmp_call_48_out;

                    ///////////////////
                    // Tasklet code (T_l756_c756)
                    tmp_call_48_out = max(ztp1_0_in_0, 160.0);
                    ///////////////////

                    __state->__6_tmp_call_48 = tmp_call_48_out;
                }
                {
                    double tmp_call_48_0_in = __state->__6_tmp_call_48;
                    double ztp1_out_0;

                    ///////////////////
                    // Tasklet code (T_l756_c756)
                    ztp1_out_0 = tmp_call_48_0_in;
                    ///////////////////

                    __state->__6_ztp1[((_for_it_41 + (sym_klon * (_for_it_23 - 1))) - 1)] = ztp1_out_0;
                }
            }
        }
        for (_for_it_42 = 1; (_for_it_42 <= icend); _for_it_42 = (_for_it_42 + 1)) {
            {
                {
                    double pap_var_17_0_in_0 = pap_var_17[((_for_it_42 + (sym_klon * (_for_it_23 - 1))) - 1)];
                    double zqp_out;

                    ///////////////////
                    // Tasklet code (T_l760_c760)
                    zqp_out = (1.0 / pap_var_17_0_in_0);
                    ///////////////////

                    __state->__6_zqp = zqp_out;
                }
                {
                    double ztp1_0_in_0 = __state->__6_ztp1[((_for_it_42 + (sym_klon * (_for_it_23 - 1))) - 1)];
                    double oka_out;

                    ///////////////////
                    // Tasklet code (T_l761_c761)
                    oka_out = ztp1_0_in_0;
                    ///////////////////

                    __state->__6_oka = oka_out;
                }
                {
                    double oka_0_in = __state->__6_oka;
                    double ydthf_0_in_rtwat = v_ydthf_rtwat[0];
                    double tmp_call_94_out;

                    ///////////////////
                    // Tasklet code (T_l762_c762)
                    tmp_call_94_out = min(ydthf_0_in_rtwat, oka_0_in);
                    ///////////////////

                    __state->__6_tmp_call_94 = tmp_call_94_out;
                }
                {
                    double tmp_call_94_0_in = __state->__6_tmp_call_94;
                    double ydthf_0_in_rtice = v_ydthf_rtice[0];
                    double tmp_call_82_out;

                    ///////////////////
                    // Tasklet code (T_l762_c762)
                    tmp_call_82_out = max(ydthf_0_in_rtice, tmp_call_94_0_in);
                    ///////////////////

                    __state->__6_tmp_call_82 = tmp_call_82_out;
                }
                {
                    double oka_0_in = __state->__6_oka;
                    double oka_1_in = __state->__6_oka;
                    double ydcst_0_in_rtt = v_ydcst_rtt[0];
                    double ydthf_0_in_r3ies = v_ydthf_r3ies[0];
                    double ydthf_1_in_r4ies = v_ydthf_r4ies[0];
                    double tmp_arg_33_out;

                    ///////////////////
                    // Tasklet code (T_l762_c762)
                    tmp_arg_33_out = ((ydthf_0_in_r3ies * (oka_0_in - ydcst_0_in_rtt)) / (oka_1_in - ydthf_1_in_r4ies));
                    ///////////////////

                    __state->__6_tmp_arg_33 = tmp_arg_33_out;
                }
                {
                    double tmp_arg_33_0_in = __state->__6_tmp_arg_33;
                    double tmp_call_53_out;

                    ///////////////////
                    // Tasklet code (T_l762_c762)
                    tmp_call_53_out = exp(tmp_arg_33_0_in);
                    ///////////////////

                    __state->__6_tmp_call_53 = tmp_call_53_out;
                }
            }
            {
                {
                    double tmp_call_82_0_in = __state->__6_tmp_call_82;
                    double ydthf_0_in_rtice = v_ydthf_rtice[0];
                    double ydthf_1_in_rtwat_rtice_r = v_ydthf_rtwat_rtice_r[0];
                    double tmp_arg_34_out;

                    ///////////////////
                    // Tasklet code (T_l762_c762)
                    tmp_arg_34_out = ((tmp_call_82_0_in - ydthf_0_in_rtice) * ydthf_1_in_rtwat_rtice_r);
                    ///////////////////

                    __state->__6_tmp_arg_34 = tmp_arg_34_out;
                }
                {
                    double tmp_arg_34_0_in = __state->__6_tmp_arg_34;
                    double tmp_call_70_out;

                    ///////////////////
                    // Tasklet code (T_l762_c762)
                    tmp_call_70_out = (dace::math::ipow(tmp_arg_34_0_in, 2));
                    ///////////////////

                    __state->__6_tmp_call_70 = tmp_call_70_out;
                }
                {
                    double tmp_call_70_0_in = __state->__6_tmp_call_70;
                    double tmp_call_52_out;

                    ///////////////////
                    // Tasklet code (T_l762_c762)
                    tmp_call_52_out = min(1.0, tmp_call_70_0_in);
                    ///////////////////

                    __state->__6_tmp_call_52 = tmp_call_52_out;
                }
            }
            {
                {
                    double oka_0_in = __state->__6_oka;
                    double ydthf_0_in_rtwat = v_ydthf_rtwat[0];
                    double tmp_call_95_out;

                    ///////////////////
                    // Tasklet code (T_l762_c762)
                    tmp_call_95_out = min(ydthf_0_in_rtwat, oka_0_in);
                    ///////////////////

                    __state->__6_tmp_call_95 = tmp_call_95_out;
                }
                {
                    double tmp_call_95_0_in = __state->__6_tmp_call_95;
                    double ydthf_0_in_rtice = v_ydthf_rtice[0];
                    double tmp_call_83_out;

                    ///////////////////
                    // Tasklet code (T_l762_c762)
                    tmp_call_83_out = max(ydthf_0_in_rtice, tmp_call_95_0_in);
                    ///////////////////

                    __state->__6_tmp_call_83 = tmp_call_83_out;
                }
                {
                    double oka_0_in = __state->__6_oka;
                    double oka_1_in = __state->__6_oka;
                    double ydcst_0_in_rtt = v_ydcst_rtt[0];
                    double ydthf_0_in_r3les = v_ydthf_r3les[0];
                    double ydthf_1_in_r4les = v_ydthf_r4les[0];
                    double tmp_arg_35_out;

                    ///////////////////
                    // Tasklet code (T_l762_c762)
                    tmp_arg_35_out = ((ydthf_0_in_r3les * (oka_0_in - ydcst_0_in_rtt)) / (oka_1_in - ydthf_1_in_r4les));
                    ///////////////////

                    __state->__6_tmp_arg_35 = tmp_arg_35_out;
                }
                {
                    double tmp_arg_35_0_in = __state->__6_tmp_arg_35;
                    double tmp_call_51_out;

                    ///////////////////
                    // Tasklet code (T_l762_c762)
                    tmp_call_51_out = exp(tmp_arg_35_0_in);
                    ///////////////////

                    __state->__6_tmp_call_51 = tmp_call_51_out;
                }
            }
            {
                {
                    double tmp_call_83_0_in = __state->__6_tmp_call_83;
                    double ydthf_0_in_rtice = v_ydthf_rtice[0];
                    double ydthf_1_in_rtwat_rtice_r = v_ydthf_rtwat_rtice_r[0];
                    double tmp_arg_36_out;

                    ///////////////////
                    // Tasklet code (T_l762_c762)
                    tmp_arg_36_out = ((tmp_call_83_0_in - ydthf_0_in_rtice) * ydthf_1_in_rtwat_rtice_r);
                    ///////////////////

                    __state->__6_tmp_arg_36 = tmp_arg_36_out;
                }
                {
                    double tmp_arg_36_0_in = __state->__6_tmp_arg_36;
                    double tmp_call_71_out;

                    ///////////////////
                    // Tasklet code (T_l762_c762)
                    tmp_call_71_out = (dace::math::ipow(tmp_arg_36_0_in, 2));
                    ///////////////////

                    __state->__6_tmp_call_71 = tmp_call_71_out;
                }
                {
                    double tmp_call_71_0_in = __state->__6_tmp_call_71;
                    double tmp_call_50_out;

                    ///////////////////
                    // Tasklet code (T_l762_c762)
                    tmp_call_50_out = min(1.0, tmp_call_71_0_in);
                    ///////////////////

                    __state->__6_tmp_call_50 = tmp_call_50_out;
                }
                {
                    double tmp_call_50_0_in = __state->__6_tmp_call_50;
                    double tmp_call_51_0_in = __state->__6_tmp_call_51;
                    double tmp_call_52_0_in = __state->__6_tmp_call_52;
                    double tmp_call_53_0_in = __state->__6_tmp_call_53;
                    double ydthf_0_in_r2es = v_ydthf_r2es[0];
                    double zqp_0_in = __state->__6_zqp;
                    double zqsat_out;

                    ///////////////////
                    // Tasklet code (T_l762_c762)
                    zqsat_out = ((ydthf_0_in_r2es * ((tmp_call_50_0_in * tmp_call_51_0_in) + ((1.0 - tmp_call_52_0_in) * tmp_call_53_0_in))) * zqp_0_in);
                    ///////////////////

                    __state->__6_zqsat = zqsat_out;
                }
                {
                    double zqsat_0_in = __state->__6_zqsat;
                    double zqsat_out;

                    ///////////////////
                    // Tasklet code (T_l763_c763)
                    zqsat_out = min(0.5, zqsat_0_in);
                    ///////////////////

                    __state->__6_zqsat = zqsat_out;
                }
                {
                    double ydcst_0_in_retv = v_ydcst_retv[0];
                    double zqsat_0_in = __state->__6_zqsat;
                    double zcor_out;

                    ///////////////////
                    // Tasklet code (T_l764_c764)
                    zcor_out = (1.0 / (1.0 - (ydcst_0_in_retv * zqsat_0_in)));
                    ///////////////////

                    __state->__6_zcor = zcor_out;
                }
            }
            {
                {
                    double zcor_0_in = __state->__6_zcor;
                    double zqsat_0_in = __state->__6_zqsat;
                    double zqsat_out;

                    ///////////////////
                    // Tasklet code (T_l765_c765)
                    zqsat_out = (zqsat_0_in * zcor_0_in);
                    ///////////////////

                    __state->__6_zqsat = zqsat_out;
                }
                {
                    double ztp1_0_in_0 = __state->__6_ztp1[((_for_it_42 + (sym_klon * (_for_it_23 - 1))) - 1)];
                    double oka_out;

                    ///////////////////
                    // Tasklet code (T_l766_c766)
                    oka_out = ztp1_0_in_0;
                    ///////////////////

                    __state->__6_oka = oka_out;
                }
                {
                    double oka_0_in = __state->__6_oka;
                    double ydthf_0_in_r4ies = v_ydthf_r4ies[0];
                    double tmp_arg_37_out;

                    ///////////////////
                    // Tasklet code (T_l767_c767)
                    tmp_arg_37_out = (oka_0_in - ydthf_0_in_r4ies);
                    ///////////////////

                    __state->__6_tmp_arg_37 = tmp_arg_37_out;
                }
                {
                    double tmp_arg_37_0_in = __state->__6_tmp_arg_37;
                    double tmp_call_57_out;

                    ///////////////////
                    // Tasklet code (T_l767_c767)
                    tmp_call_57_out = (dace::math::ipow(tmp_arg_37_0_in, 2));
                    ///////////////////

                    __state->__6_tmp_call_57 = tmp_call_57_out;
                }
                {
                    double oka_0_in = __state->__6_oka;
                    double ydthf_0_in_rtwat = v_ydthf_rtwat[0];
                    double tmp_call_96_out;

                    ///////////////////
                    // Tasklet code (T_l767_c767)
                    tmp_call_96_out = min(ydthf_0_in_rtwat, oka_0_in);
                    ///////////////////

                    __state->__6_tmp_call_96 = tmp_call_96_out;
                }
                {
                    double tmp_call_96_0_in = __state->__6_tmp_call_96;
                    double ydthf_0_in_rtice = v_ydthf_rtice[0];
                    double tmp_call_84_out;

                    ///////////////////
                    // Tasklet code (T_l767_c767)
                    tmp_call_84_out = max(ydthf_0_in_rtice, tmp_call_96_0_in);
                    ///////////////////

                    __state->__6_tmp_call_84 = tmp_call_84_out;
                }
            }
            {
                {
                    double tmp_call_84_0_in = __state->__6_tmp_call_84;
                    double ydthf_0_in_rtice = v_ydthf_rtice[0];
                    double ydthf_1_in_rtwat_rtice_r = v_ydthf_rtwat_rtice_r[0];
                    double tmp_arg_38_out;

                    ///////////////////
                    // Tasklet code (T_l767_c767)
                    tmp_arg_38_out = ((tmp_call_84_0_in - ydthf_0_in_rtice) * ydthf_1_in_rtwat_rtice_r);
                    ///////////////////

                    __state->__6_tmp_arg_38 = tmp_arg_38_out;
                }
                {
                    double tmp_arg_38_0_in = __state->__6_tmp_arg_38;
                    double tmp_call_72_out;

                    ///////////////////
                    // Tasklet code (T_l767_c767)
                    tmp_call_72_out = (dace::math::ipow(tmp_arg_38_0_in, 2));
                    ///////////////////

                    __state->__6_tmp_call_72 = tmp_call_72_out;
                }
                {
                    double tmp_call_72_0_in = __state->__6_tmp_call_72;
                    double tmp_call_56_out;

                    ///////////////////
                    // Tasklet code (T_l767_c767)
                    tmp_call_56_out = min(1.0, tmp_call_72_0_in);
                    ///////////////////

                    __state->__6_tmp_call_56 = tmp_call_56_out;
                }
                {
                    double oka_0_in = __state->__6_oka;
                    double ydthf_0_in_r4les = v_ydthf_r4les[0];
                    double tmp_arg_39_out;

                    ///////////////////
                    // Tasklet code (T_l767_c767)
                    tmp_arg_39_out = (oka_0_in - ydthf_0_in_r4les);
                    ///////////////////

                    __state->__6_tmp_arg_39 = tmp_arg_39_out;
                }
            }
            {
                {
                    double tmp_arg_39_0_in = __state->__6_tmp_arg_39;
                    double tmp_call_55_out;

                    ///////////////////
                    // Tasklet code (T_l767_c767)
                    tmp_call_55_out = (dace::math::ipow(tmp_arg_39_0_in, 2));
                    ///////////////////

                    __state->__6_tmp_call_55 = tmp_call_55_out;
                }
                {
                    double oka_0_in = __state->__6_oka;
                    double ydthf_0_in_rtwat = v_ydthf_rtwat[0];
                    double tmp_call_97_out;

                    ///////////////////
                    // Tasklet code (T_l767_c767)
                    tmp_call_97_out = min(ydthf_0_in_rtwat, oka_0_in);
                    ///////////////////

                    __state->__6_tmp_call_97 = tmp_call_97_out;
                }
                {
                    double tmp_call_97_0_in = __state->__6_tmp_call_97;
                    double ydthf_0_in_rtice = v_ydthf_rtice[0];
                    double tmp_call_85_out;

                    ///////////////////
                    // Tasklet code (T_l767_c767)
                    tmp_call_85_out = max(ydthf_0_in_rtice, tmp_call_97_0_in);
                    ///////////////////

                    __state->__6_tmp_call_85 = tmp_call_85_out;
                }
            }
            {
                {
                    double tmp_call_85_0_in = __state->__6_tmp_call_85;
                    double ydthf_0_in_rtice = v_ydthf_rtice[0];
                    double ydthf_1_in_rtwat_rtice_r = v_ydthf_rtwat_rtice_r[0];
                    double tmp_arg_40_out;

                    ///////////////////
                    // Tasklet code (T_l767_c767)
                    tmp_arg_40_out = ((tmp_call_85_0_in - ydthf_0_in_rtice) * ydthf_1_in_rtwat_rtice_r);
                    ///////////////////

                    __state->__6_tmp_arg_40 = tmp_arg_40_out;
                }
                {
                    double tmp_arg_40_0_in = __state->__6_tmp_arg_40;
                    double tmp_call_73_out;

                    ///////////////////
                    // Tasklet code (T_l767_c767)
                    tmp_call_73_out = (dace::math::ipow(tmp_arg_40_0_in, 2));
                    ///////////////////

                    __state->__6_tmp_call_73 = tmp_call_73_out;
                }
                {
                    double tmp_call_73_0_in = __state->__6_tmp_call_73;
                    double tmp_call_54_out;

                    ///////////////////
                    // Tasklet code (T_l767_c767)
                    tmp_call_54_out = min(1.0, tmp_call_73_0_in);
                    ///////////////////

                    __state->__6_tmp_call_54 = tmp_call_54_out;
                }
            }
            {
                {
                    double tmp_call_54_0_in = __state->__6_tmp_call_54;
                    double tmp_call_55_0_in = __state->__6_tmp_call_55;
                    double tmp_call_56_0_in = __state->__6_tmp_call_56;
                    double tmp_call_57_0_in = __state->__6_tmp_call_57;
                    double ydthf_0_in_r5alvcp = v_ydthf_r5alvcp[0];
                    double ydthf_1_in_r5alscp = v_ydthf_r5alscp[0];
                    double zcor_0_in = __state->__6_zcor;
                    double zqsat_0_in = __state->__6_zqsat;
                    double zqsat_1_in = __state->__6_zqsat;
                    double zqsmix_0_in_0 = __state->__6_zqsmix[((_for_it_42 + (sym_klon * (_for_it_23 - 1))) - 1)];
                    double zcond_out;

                    ///////////////////
                    // Tasklet code (T_l767_c767)
                    zcond_out =
                        ((zqsmix_0_in_0 - zqsat_0_in) / ((1.0 + ((((zqsat_1_in * zcor_0_in) * tmp_call_54_0_in) * ydthf_0_in_r5alvcp) * (1.0 / tmp_call_55_0_in))) +
                                                         (((1.0 - tmp_call_56_0_in) * ydthf_1_in_r5alscp) * (1.0 / tmp_call_57_0_in))));
                    ///////////////////

                    __state->__6_zcond = zcond_out;
                }
                {
                    double ztp1_0_in_0 = __state->__6_ztp1[((_for_it_42 + (sym_klon * (_for_it_23 - 1))) - 1)];
                    double oka_out;

                    ///////////////////
                    // Tasklet code (T_l768_c768)
                    oka_out = ztp1_0_in_0;
                    ///////////////////

                    __state->__6_oka = oka_out;
                }
                {
                    double oka_0_in = __state->__6_oka;
                    double ydthf_0_in_rtwat = v_ydthf_rtwat[0];
                    double tmp_call_98_out;

                    ///////////////////
                    // Tasklet code (T_l769_c769)
                    tmp_call_98_out = min(ydthf_0_in_rtwat, oka_0_in);
                    ///////////////////

                    __state->__6_tmp_call_98 = tmp_call_98_out;
                }
                {
                    double tmp_call_98_0_in = __state->__6_tmp_call_98;
                    double ydthf_0_in_rtice = v_ydthf_rtice[0];
                    double tmp_call_86_out;

                    ///////////////////
                    // Tasklet code (T_l769_c769)
                    tmp_call_86_out = max(ydthf_0_in_rtice, tmp_call_98_0_in);
                    ///////////////////

                    __state->__6_tmp_call_86 = tmp_call_86_out;
                }
            }
            {
                {
                    double tmp_call_86_0_in = __state->__6_tmp_call_86;
                    double ydthf_0_in_rtice = v_ydthf_rtice[0];
                    double ydthf_1_in_rtwat_rtice_r = v_ydthf_rtwat_rtice_r[0];
                    double tmp_arg_41_out;

                    ///////////////////
                    // Tasklet code (T_l769_c769)
                    tmp_arg_41_out = ((tmp_call_86_0_in - ydthf_0_in_rtice) * ydthf_1_in_rtwat_rtice_r);
                    ///////////////////

                    __state->__6_tmp_arg_41 = tmp_arg_41_out;
                }
                {
                    double tmp_arg_41_0_in = __state->__6_tmp_arg_41;
                    double tmp_call_74_out;

                    ///////////////////
                    // Tasklet code (T_l769_c769)
                    tmp_call_74_out = (dace::math::ipow(tmp_arg_41_0_in, 2));
                    ///////////////////

                    __state->__6_tmp_call_74 = tmp_call_74_out;
                }
                {
                    double tmp_call_74_0_in = __state->__6_tmp_call_74;
                    double tmp_call_59_out;

                    ///////////////////
                    // Tasklet code (T_l769_c769)
                    tmp_call_59_out = min(1.0, tmp_call_74_0_in);
                    ///////////////////

                    __state->__6_tmp_call_59 = tmp_call_59_out;
                }
                {
                    double oka_0_in = __state->__6_oka;
                    double ydthf_0_in_rtwat = v_ydthf_rtwat[0];
                    double tmp_call_99_out;

                    ///////////////////
                    // Tasklet code (T_l769_c769)
                    tmp_call_99_out = min(ydthf_0_in_rtwat, oka_0_in);
                    ///////////////////

                    __state->__6_tmp_call_99 = tmp_call_99_out;
                }
            }
            {
                {
                    double tmp_call_99_0_in = __state->__6_tmp_call_99;
                    double ydthf_0_in_rtice = v_ydthf_rtice[0];
                    double tmp_call_87_out;

                    ///////////////////
                    // Tasklet code (T_l769_c769)
                    tmp_call_87_out = max(ydthf_0_in_rtice, tmp_call_99_0_in);
                    ///////////////////

                    __state->__6_tmp_call_87 = tmp_call_87_out;
                }
            }
            {
                {
                    double tmp_call_87_0_in = __state->__6_tmp_call_87;
                    double ydthf_0_in_rtice = v_ydthf_rtice[0];
                    double ydthf_1_in_rtwat_rtice_r = v_ydthf_rtwat_rtice_r[0];
                    double tmp_arg_42_out;

                    ///////////////////
                    // Tasklet code (T_l769_c769)
                    tmp_arg_42_out = ((tmp_call_87_0_in - ydthf_0_in_rtice) * ydthf_1_in_rtwat_rtice_r);
                    ///////////////////

                    __state->__6_tmp_arg_42 = tmp_arg_42_out;
                }
                {
                    double tmp_arg_42_0_in = __state->__6_tmp_arg_42;
                    double tmp_call_75_out;

                    ///////////////////
                    // Tasklet code (T_l769_c769)
                    tmp_call_75_out = (dace::math::ipow(tmp_arg_42_0_in, 2));
                    ///////////////////

                    __state->__6_tmp_call_75 = tmp_call_75_out;
                }
                {
                    double tmp_call_75_0_in = __state->__6_tmp_call_75;
                    double tmp_call_58_out;

                    ///////////////////
                    // Tasklet code (T_l769_c769)
                    tmp_call_58_out = min(1.0, tmp_call_75_0_in);
                    ///////////////////

                    __state->__6_tmp_call_58 = tmp_call_58_out;
                }
                {
                    double tmp_call_58_0_in = __state->__6_tmp_call_58;
                    double tmp_call_59_0_in = __state->__6_tmp_call_59;
                    double ydthf_0_in_ralvdcp = v_ydthf_ralvdcp[0];
                    double ydthf_1_in_ralsdcp = v_ydthf_ralsdcp[0];
                    double zcond_0_in = __state->__6_zcond;
                    double ztp1_0_in_0 = __state->__6_ztp1[((_for_it_42 + (sym_klon * (_for_it_23 - 1))) - 1)];
                    double ztp1_out_0;

                    ///////////////////
                    // Tasklet code (T_l769_c769)
                    ztp1_out_0 = ((ztp1_0_in_0 + (tmp_call_58_0_in * ydthf_0_in_ralvdcp)) + (((1.0 - tmp_call_59_0_in) * ydthf_1_in_ralsdcp) * zcond_0_in));
                    ///////////////////

                    __state->__6_ztp1[((_for_it_42 + (sym_klon * (_for_it_23 - 1))) - 1)] = ztp1_out_0;
                }
                {
                    double ztp1_0_in_0 = __state->__6_ztp1[((_for_it_42 + (sym_klon * (_for_it_23 - 1))) - 1)];
                    double oka_out;

                    ///////////////////
                    // Tasklet code (T_l771_c771)
                    oka_out = ztp1_0_in_0;
                    ///////////////////

                    __state->__6_oka = oka_out;
                }
                {
                    double zcond_0_in = __state->__6_zcond;
                    double zqsmix_0_in_0 = __state->__6_zqsmix[((_for_it_42 + (sym_klon * (_for_it_23 - 1))) - 1)];
                    double zqsmix_out_0;

                    ///////////////////
                    // Tasklet code (T_l770_c770)
                    zqsmix_out_0 = (zqsmix_0_in_0 - zcond_0_in);
                    ///////////////////

                    __state->__6_zqsmix[((_for_it_42 + (sym_klon * (_for_it_23 - 1))) - 1)] = zqsmix_out_0;
                }
            }
            {
                {
                    double oka_0_in = __state->__6_oka;
                    double ydthf_0_in_rtwat = v_ydthf_rtwat[0];
                    double tmp_call_100_out;

                    ///////////////////
                    // Tasklet code (T_l772_c772)
                    tmp_call_100_out = min(ydthf_0_in_rtwat, oka_0_in);
                    ///////////////////

                    __state->__6_tmp_call_100 = tmp_call_100_out;
                }
                {
                    double tmp_call_100_0_in = __state->__6_tmp_call_100;
                    double ydthf_0_in_rtice = v_ydthf_rtice[0];
                    double tmp_call_88_out;

                    ///////////////////
                    // Tasklet code (T_l772_c772)
                    tmp_call_88_out = max(ydthf_0_in_rtice, tmp_call_100_0_in);
                    ///////////////////

                    __state->__6_tmp_call_88 = tmp_call_88_out;
                }
                {
                    double oka_0_in = __state->__6_oka;
                    double oka_1_in = __state->__6_oka;
                    double ydcst_0_in_rtt = v_ydcst_rtt[0];
                    double ydthf_0_in_r3ies = v_ydthf_r3ies[0];
                    double ydthf_1_in_r4ies = v_ydthf_r4ies[0];
                    double tmp_arg_43_out;

                    ///////////////////
                    // Tasklet code (T_l772_c772)
                    tmp_arg_43_out = ((ydthf_0_in_r3ies * (oka_0_in - ydcst_0_in_rtt)) / (oka_1_in - ydthf_1_in_r4ies));
                    ///////////////////

                    __state->__6_tmp_arg_43 = tmp_arg_43_out;
                }
                {
                    double tmp_arg_43_0_in = __state->__6_tmp_arg_43;
                    double tmp_call_63_out;

                    ///////////////////
                    // Tasklet code (T_l772_c772)
                    tmp_call_63_out = exp(tmp_arg_43_0_in);
                    ///////////////////

                    __state->__6_tmp_call_63 = tmp_call_63_out;
                }
            }
            {
                {
                    double tmp_call_88_0_in = __state->__6_tmp_call_88;
                    double ydthf_0_in_rtice = v_ydthf_rtice[0];
                    double ydthf_1_in_rtwat_rtice_r = v_ydthf_rtwat_rtice_r[0];
                    double tmp_arg_44_out;

                    ///////////////////
                    // Tasklet code (T_l772_c772)
                    tmp_arg_44_out = ((tmp_call_88_0_in - ydthf_0_in_rtice) * ydthf_1_in_rtwat_rtice_r);
                    ///////////////////

                    __state->__6_tmp_arg_44 = tmp_arg_44_out;
                }
                {
                    double tmp_arg_44_0_in = __state->__6_tmp_arg_44;
                    double tmp_call_76_out;

                    ///////////////////
                    // Tasklet code (T_l772_c772)
                    tmp_call_76_out = (dace::math::ipow(tmp_arg_44_0_in, 2));
                    ///////////////////

                    __state->__6_tmp_call_76 = tmp_call_76_out;
                }
                {
                    double tmp_call_76_0_in = __state->__6_tmp_call_76;
                    double tmp_call_62_out;

                    ///////////////////
                    // Tasklet code (T_l772_c772)
                    tmp_call_62_out = min(1.0, tmp_call_76_0_in);
                    ///////////////////

                    __state->__6_tmp_call_62 = tmp_call_62_out;
                }
            }
            {
                {
                    double oka_0_in = __state->__6_oka;
                    double ydthf_0_in_rtwat = v_ydthf_rtwat[0];
                    double tmp_call_101_out;

                    ///////////////////
                    // Tasklet code (T_l772_c772)
                    tmp_call_101_out = min(ydthf_0_in_rtwat, oka_0_in);
                    ///////////////////

                    __state->__6_tmp_call_101 = tmp_call_101_out;
                }
                {
                    double tmp_call_101_0_in = __state->__6_tmp_call_101;
                    double ydthf_0_in_rtice = v_ydthf_rtice[0];
                    double tmp_call_89_out;

                    ///////////////////
                    // Tasklet code (T_l772_c772)
                    tmp_call_89_out = max(ydthf_0_in_rtice, tmp_call_101_0_in);
                    ///////////////////

                    __state->__6_tmp_call_89 = tmp_call_89_out;
                }
                {
                    double oka_0_in = __state->__6_oka;
                    double oka_1_in = __state->__6_oka;
                    double ydcst_0_in_rtt = v_ydcst_rtt[0];
                    double ydthf_0_in_r3les = v_ydthf_r3les[0];
                    double ydthf_1_in_r4les = v_ydthf_r4les[0];
                    double tmp_arg_45_out;

                    ///////////////////
                    // Tasklet code (T_l772_c772)
                    tmp_arg_45_out = ((ydthf_0_in_r3les * (oka_0_in - ydcst_0_in_rtt)) / (oka_1_in - ydthf_1_in_r4les));
                    ///////////////////

                    __state->__6_tmp_arg_45 = tmp_arg_45_out;
                }
                {
                    double tmp_arg_45_0_in = __state->__6_tmp_arg_45;
                    double tmp_call_61_out;

                    ///////////////////
                    // Tasklet code (T_l772_c772)
                    tmp_call_61_out = exp(tmp_arg_45_0_in);
                    ///////////////////

                    __state->__6_tmp_call_61 = tmp_call_61_out;
                }
            }
            {
                {
                    double tmp_call_89_0_in = __state->__6_tmp_call_89;
                    double ydthf_0_in_rtice = v_ydthf_rtice[0];
                    double ydthf_1_in_rtwat_rtice_r = v_ydthf_rtwat_rtice_r[0];
                    double tmp_arg_46_out;

                    ///////////////////
                    // Tasklet code (T_l772_c772)
                    tmp_arg_46_out = ((tmp_call_89_0_in - ydthf_0_in_rtice) * ydthf_1_in_rtwat_rtice_r);
                    ///////////////////

                    __state->__6_tmp_arg_46 = tmp_arg_46_out;
                }
                {
                    double tmp_arg_46_0_in = __state->__6_tmp_arg_46;
                    double tmp_call_77_out;

                    ///////////////////
                    // Tasklet code (T_l772_c772)
                    tmp_call_77_out = (dace::math::ipow(tmp_arg_46_0_in, 2));
                    ///////////////////

                    __state->__6_tmp_call_77 = tmp_call_77_out;
                }
                {
                    double tmp_call_77_0_in = __state->__6_tmp_call_77;
                    double tmp_call_60_out;

                    ///////////////////
                    // Tasklet code (T_l772_c772)
                    tmp_call_60_out = min(1.0, tmp_call_77_0_in);
                    ///////////////////

                    __state->__6_tmp_call_60 = tmp_call_60_out;
                }
                {
                    double tmp_call_60_0_in = __state->__6_tmp_call_60;
                    double tmp_call_61_0_in = __state->__6_tmp_call_61;
                    double tmp_call_62_0_in = __state->__6_tmp_call_62;
                    double tmp_call_63_0_in = __state->__6_tmp_call_63;
                    double ydthf_0_in_r2es = v_ydthf_r2es[0];
                    double zqp_0_in = __state->__6_zqp;
                    double zqsat_out;

                    ///////////////////
                    // Tasklet code (T_l772_c772)
                    zqsat_out = ((ydthf_0_in_r2es * ((tmp_call_60_0_in * tmp_call_61_0_in) + ((1.0 - tmp_call_62_0_in) * tmp_call_63_0_in))) * zqp_0_in);
                    ///////////////////

                    __state->__6_zqsat = zqsat_out;
                }
                {
                    double zqsat_0_in = __state->__6_zqsat;
                    double zqsat_out;

                    ///////////////////
                    // Tasklet code (T_l773_c773)
                    zqsat_out = min(0.5, zqsat_0_in);
                    ///////////////////

                    __state->__6_zqsat = zqsat_out;
                }
                {
                    double ydcst_0_in_retv = v_ydcst_retv[0];
                    double zqsat_0_in = __state->__6_zqsat;
                    double zcor_out;

                    ///////////////////
                    // Tasklet code (T_l774_c774)
                    zcor_out = (1.0 / (1.0 - (ydcst_0_in_retv * zqsat_0_in)));
                    ///////////////////

                    __state->__6_zcor = zcor_out;
                }
            }
            {
                {
                    double zcor_0_in = __state->__6_zcor;
                    double zqsat_0_in = __state->__6_zqsat;
                    double zqsat_out;

                    ///////////////////
                    // Tasklet code (T_l775_c775)
                    zqsat_out = (zqsat_0_in * zcor_0_in);
                    ///////////////////

                    __state->__6_zqsat = zqsat_out;
                }
                {
                    double ztp1_0_in_0 = __state->__6_ztp1[((_for_it_42 + (sym_klon * (_for_it_23 - 1))) - 1)];
                    double oka_out;

                    ///////////////////
                    // Tasklet code (T_l776_c776)
                    oka_out = ztp1_0_in_0;
                    ///////////////////

                    __state->__6_oka = oka_out;
                }
                {
                    double oka_0_in = __state->__6_oka;
                    double ydthf_0_in_r4ies = v_ydthf_r4ies[0];
                    double tmp_arg_47_out;

                    ///////////////////
                    // Tasklet code (T_l777_c777)
                    tmp_arg_47_out = (oka_0_in - ydthf_0_in_r4ies);
                    ///////////////////

                    __state->__6_tmp_arg_47 = tmp_arg_47_out;
                }
                {
                    double tmp_arg_47_0_in = __state->__6_tmp_arg_47;
                    double tmp_call_67_out;

                    ///////////////////
                    // Tasklet code (T_l777_c777)
                    tmp_call_67_out = (dace::math::ipow(tmp_arg_47_0_in, 2));
                    ///////////////////

                    __state->__6_tmp_call_67 = tmp_call_67_out;
                }
                {
                    double oka_0_in = __state->__6_oka;
                    double ydthf_0_in_rtwat = v_ydthf_rtwat[0];
                    double tmp_call_102_out;

                    ///////////////////
                    // Tasklet code (T_l777_c777)
                    tmp_call_102_out = min(ydthf_0_in_rtwat, oka_0_in);
                    ///////////////////

                    __state->__6_tmp_call_102 = tmp_call_102_out;
                }
                {
                    double tmp_call_102_0_in = __state->__6_tmp_call_102;
                    double ydthf_0_in_rtice = v_ydthf_rtice[0];
                    double tmp_call_90_out;

                    ///////////////////
                    // Tasklet code (T_l777_c777)
                    tmp_call_90_out = max(ydthf_0_in_rtice, tmp_call_102_0_in);
                    ///////////////////

                    __state->__6_tmp_call_90 = tmp_call_90_out;
                }
            }
            {
                {
                    double tmp_call_90_0_in = __state->__6_tmp_call_90;
                    double ydthf_0_in_rtice = v_ydthf_rtice[0];
                    double ydthf_1_in_rtwat_rtice_r = v_ydthf_rtwat_rtice_r[0];
                    double tmp_arg_48_out;

                    ///////////////////
                    // Tasklet code (T_l777_c777)
                    tmp_arg_48_out = ((tmp_call_90_0_in - ydthf_0_in_rtice) * ydthf_1_in_rtwat_rtice_r);
                    ///////////////////

                    __state->__6_tmp_arg_48 = tmp_arg_48_out;
                }
                {
                    double tmp_arg_48_0_in = __state->__6_tmp_arg_48;
                    double tmp_call_78_out;

                    ///////////////////
                    // Tasklet code (T_l777_c777)
                    tmp_call_78_out = (dace::math::ipow(tmp_arg_48_0_in, 2));
                    ///////////////////

                    __state->__6_tmp_call_78 = tmp_call_78_out;
                }
                {
                    double tmp_call_78_0_in = __state->__6_tmp_call_78;
                    double tmp_call_66_out;

                    ///////////////////
                    // Tasklet code (T_l777_c777)
                    tmp_call_66_out = min(1.0, tmp_call_78_0_in);
                    ///////////////////

                    __state->__6_tmp_call_66 = tmp_call_66_out;
                }
                {
                    double oka_0_in = __state->__6_oka;
                    double ydthf_0_in_r4les = v_ydthf_r4les[0];
                    double tmp_arg_49_out;

                    ///////////////////
                    // Tasklet code (T_l777_c777)
                    tmp_arg_49_out = (oka_0_in - ydthf_0_in_r4les);
                    ///////////////////

                    __state->__6_tmp_arg_49 = tmp_arg_49_out;
                }
            }
            {
                {
                    double tmp_arg_49_0_in = __state->__6_tmp_arg_49;
                    double tmp_call_65_out;

                    ///////////////////
                    // Tasklet code (T_l777_c777)
                    tmp_call_65_out = (dace::math::ipow(tmp_arg_49_0_in, 2));
                    ///////////////////

                    __state->__6_tmp_call_65 = tmp_call_65_out;
                }
                {
                    double oka_0_in = __state->__6_oka;
                    double ydthf_0_in_rtwat = v_ydthf_rtwat[0];
                    double tmp_call_103_out;

                    ///////////////////
                    // Tasklet code (T_l777_c777)
                    tmp_call_103_out = min(ydthf_0_in_rtwat, oka_0_in);
                    ///////////////////

                    __state->__6_tmp_call_103 = tmp_call_103_out;
                }
                {
                    double tmp_call_103_0_in = __state->__6_tmp_call_103;
                    double ydthf_0_in_rtice = v_ydthf_rtice[0];
                    double tmp_call_91_out;

                    ///////////////////
                    // Tasklet code (T_l777_c777)
                    tmp_call_91_out = max(ydthf_0_in_rtice, tmp_call_103_0_in);
                    ///////////////////

                    __state->__6_tmp_call_91 = tmp_call_91_out;
                }
            }
            {
                {
                    double tmp_call_91_0_in = __state->__6_tmp_call_91;
                    double ydthf_0_in_rtice = v_ydthf_rtice[0];
                    double ydthf_1_in_rtwat_rtice_r = v_ydthf_rtwat_rtice_r[0];
                    double tmp_arg_50_out;

                    ///////////////////
                    // Tasklet code (T_l777_c777)
                    tmp_arg_50_out = ((tmp_call_91_0_in - ydthf_0_in_rtice) * ydthf_1_in_rtwat_rtice_r);
                    ///////////////////

                    __state->__6_tmp_arg_50 = tmp_arg_50_out;
                }
                {
                    double tmp_arg_50_0_in = __state->__6_tmp_arg_50;
                    double tmp_call_79_out;

                    ///////////////////
                    // Tasklet code (T_l777_c777)
                    tmp_call_79_out = (dace::math::ipow(tmp_arg_50_0_in, 2));
                    ///////////////////

                    __state->__6_tmp_call_79 = tmp_call_79_out;
                }
                {
                    double tmp_call_79_0_in = __state->__6_tmp_call_79;
                    double tmp_call_64_out;

                    ///////////////////
                    // Tasklet code (T_l777_c777)
                    tmp_call_64_out = min(1.0, tmp_call_79_0_in);
                    ///////////////////

                    __state->__6_tmp_call_64 = tmp_call_64_out;
                }
            }
            {
                {
                    double tmp_call_64_0_in = __state->__6_tmp_call_64;
                    double tmp_call_65_0_in = __state->__6_tmp_call_65;
                    double tmp_call_66_0_in = __state->__6_tmp_call_66;
                    double tmp_call_67_0_in = __state->__6_tmp_call_67;
                    double ydthf_0_in_r5alvcp = v_ydthf_r5alvcp[0];
                    double ydthf_1_in_r5alscp = v_ydthf_r5alscp[0];
                    double zcor_0_in = __state->__6_zcor;
                    double zqsat_0_in = __state->__6_zqsat;
                    double zqsat_1_in = __state->__6_zqsat;
                    double zqsmix_0_in_0 = __state->__6_zqsmix[((_for_it_42 + (sym_klon * (_for_it_23 - 1))) - 1)];
                    double zcond1_out;

                    ///////////////////
                    // Tasklet code (T_l777_c777)
                    zcond1_out =
                        ((zqsmix_0_in_0 - zqsat_0_in) / ((1.0 + ((((zqsat_1_in * zcor_0_in) * tmp_call_64_0_in) * ydthf_0_in_r5alvcp) * (1.0 / tmp_call_65_0_in))) +
                                                         (((1.0 - tmp_call_66_0_in) * ydthf_1_in_r5alscp) * (1.0 / tmp_call_67_0_in))));
                    ///////////////////

                    __state->__6_zcond1 = zcond1_out;
                }
                {
                    double ztp1_0_in_0 = __state->__6_ztp1[((_for_it_42 + (sym_klon * (_for_it_23 - 1))) - 1)];
                    double oka_out;

                    ///////////////////
                    // Tasklet code (T_l778_c778)
                    oka_out = ztp1_0_in_0;
                    ///////////////////

                    __state->__6_oka = oka_out;
                }
                {
                    double oka_0_in = __state->__6_oka;
                    double ydthf_0_in_rtwat = v_ydthf_rtwat[0];
                    double tmp_call_104_out;

                    ///////////////////
                    // Tasklet code (T_l779_c779)
                    tmp_call_104_out = min(ydthf_0_in_rtwat, oka_0_in);
                    ///////////////////

                    __state->__6_tmp_call_104 = tmp_call_104_out;
                }
                {
                    double tmp_call_104_0_in = __state->__6_tmp_call_104;
                    double ydthf_0_in_rtice = v_ydthf_rtice[0];
                    double tmp_call_92_out;

                    ///////////////////
                    // Tasklet code (T_l779_c779)
                    tmp_call_92_out = max(ydthf_0_in_rtice, tmp_call_104_0_in);
                    ///////////////////

                    __state->__6_tmp_call_92 = tmp_call_92_out;
                }
            }
            {
                {
                    double tmp_call_92_0_in = __state->__6_tmp_call_92;
                    double ydthf_0_in_rtice = v_ydthf_rtice[0];
                    double ydthf_1_in_rtwat_rtice_r = v_ydthf_rtwat_rtice_r[0];
                    double tmp_arg_51_out;

                    ///////////////////
                    // Tasklet code (T_l779_c779)
                    tmp_arg_51_out = ((tmp_call_92_0_in - ydthf_0_in_rtice) * ydthf_1_in_rtwat_rtice_r);
                    ///////////////////

                    __state->__6_tmp_arg_51 = tmp_arg_51_out;
                }
                {
                    double tmp_arg_51_0_in = __state->__6_tmp_arg_51;
                    double tmp_call_80_out;

                    ///////////////////
                    // Tasklet code (T_l779_c779)
                    tmp_call_80_out = (dace::math::ipow(tmp_arg_51_0_in, 2));
                    ///////////////////

                    __state->__6_tmp_call_80 = tmp_call_80_out;
                }
                {
                    double tmp_call_80_0_in = __state->__6_tmp_call_80;
                    double tmp_call_69_out;

                    ///////////////////
                    // Tasklet code (T_l779_c779)
                    tmp_call_69_out = min(1.0, tmp_call_80_0_in);
                    ///////////////////

                    __state->__6_tmp_call_69 = tmp_call_69_out;
                }
                {
                    double oka_0_in = __state->__6_oka;
                    double ydthf_0_in_rtwat = v_ydthf_rtwat[0];
                    double tmp_call_105_out;

                    ///////////////////
                    // Tasklet code (T_l779_c779)
                    tmp_call_105_out = min(ydthf_0_in_rtwat, oka_0_in);
                    ///////////////////

                    __state->__6_tmp_call_105 = tmp_call_105_out;
                }
            }
            {
                {
                    double tmp_call_105_0_in = __state->__6_tmp_call_105;
                    double ydthf_0_in_rtice = v_ydthf_rtice[0];
                    double tmp_call_93_out;

                    ///////////////////
                    // Tasklet code (T_l779_c779)
                    tmp_call_93_out = max(ydthf_0_in_rtice, tmp_call_105_0_in);
                    ///////////////////

                    __state->__6_tmp_call_93 = tmp_call_93_out;
                }
            }
            {
                {
                    double tmp_call_93_0_in = __state->__6_tmp_call_93;
                    double ydthf_0_in_rtice = v_ydthf_rtice[0];
                    double ydthf_1_in_rtwat_rtice_r = v_ydthf_rtwat_rtice_r[0];
                    double tmp_arg_52_out;

                    ///////////////////
                    // Tasklet code (T_l779_c779)
                    tmp_arg_52_out = ((tmp_call_93_0_in - ydthf_0_in_rtice) * ydthf_1_in_rtwat_rtice_r);
                    ///////////////////

                    __state->__6_tmp_arg_52 = tmp_arg_52_out;
                }
                {
                    double tmp_arg_52_0_in = __state->__6_tmp_arg_52;
                    double tmp_call_81_out;

                    ///////////////////
                    // Tasklet code (T_l779_c779)
                    tmp_call_81_out = (dace::math::ipow(tmp_arg_52_0_in, 2));
                    ///////////////////

                    __state->__6_tmp_call_81 = tmp_call_81_out;
                }
                {
                    double tmp_call_81_0_in = __state->__6_tmp_call_81;
                    double tmp_call_68_out;

                    ///////////////////
                    // Tasklet code (T_l779_c779)
                    tmp_call_68_out = min(1.0, tmp_call_81_0_in);
                    ///////////////////

                    __state->__6_tmp_call_68 = tmp_call_68_out;
                }
                {
                    double tmp_call_68_0_in = __state->__6_tmp_call_68;
                    double tmp_call_69_0_in = __state->__6_tmp_call_69;
                    double ydthf_0_in_ralvdcp = v_ydthf_ralvdcp[0];
                    double ydthf_1_in_ralsdcp = v_ydthf_ralsdcp[0];
                    double zcond1_0_in = __state->__6_zcond1;
                    double ztp1_0_in_0 = __state->__6_ztp1[((_for_it_42 + (sym_klon * (_for_it_23 - 1))) - 1)];
                    double ztp1_out_0;

                    ///////////////////
                    // Tasklet code (T_l779_c779)
                    ztp1_out_0 = ((ztp1_0_in_0 + (tmp_call_68_0_in * ydthf_0_in_ralvdcp)) + (((1.0 - tmp_call_69_0_in) * ydthf_1_in_ralsdcp) * zcond1_0_in));
                    ///////////////////

                    __state->__6_ztp1[((_for_it_42 + (sym_klon * (_for_it_23 - 1))) - 1)] = ztp1_out_0;
                }
                {
                    double zcond1_0_in = __state->__6_zcond1;
                    double zqsmix_0_in_0 = __state->__6_zqsmix[((_for_it_42 + (sym_klon * (_for_it_23 - 1))) - 1)];
                    double zqsmix_out_0;

                    ///////////////////
                    // Tasklet code (T_l780_c780)
                    zqsmix_out_0 = (zqsmix_0_in_0 - zcond1_0_in);
                    ///////////////////

                    __state->__6_zqsmix[((_for_it_42 + (sym_klon * (_for_it_23 - 1))) - 1)] = zqsmix_out_0;
                }
            }
        }
        {
            {
#pragma omp parallel for
                for (auto _for_it_43 = 1; _for_it_43 < (icend + 1); _for_it_43 += 1) {
                    loop_body_50_3_0(
                        __state, &__state->__6_zqold[(_for_it_43 - 1)], &__state->__6_ztold[(_for_it_43 - 1)], &__state->__6_zdqs[(_for_it_43 - 1)],
                        &__state->__6_zqsmix[((_for_it_43 + (sym_klon * (_for_it_23 - 1))) - 1)], &__state->__6_ztp1[((_for_it_43 + (sym_klon * (_for_it_23 - 1))) - 1)], sym_klon);
                }
            }
            {
#pragma omp parallel for
                for (auto _for_it_44 = 1; _for_it_44 < (icend + 1); _for_it_44 += 1) {
                    loop_body_50_3_9(
                        __state, &__state->__6_za[((_for_it_44 + (sym_klon * (_for_it_23 - 1))) - 1)], &__state->__6_zdqs[(_for_it_44 - 1)], &__state->__6_zevaplimmix[(_for_it_44 - 1)],
                        &__state->__6_zicefrac[((_for_it_44 + (sym_klon * (_for_it_23 - 1))) - 1)], &__state->__6_zlicld[(_for_it_44 - 1)],
                        &__state->__6_zliqfrac[((_for_it_44 + (sym_klon * (_for_it_23 - 1))) - 1)], &__state->__6_zqsmix[((_for_it_44 + (sym_klon * (_for_it_23 - 1))) - 1)],
                        &__state->__6_zqx[(((_for_it_44 + ((4 * sym_klev) * sym_klon)) + (sym_klon * (_for_it_23 - 1))) - 1)], &__state->__6_zsolqa[(_for_it_44 - 1)], sym_klev, sym_klon);
                }
            }
        }
        for (_for_it_45 = 1; (_for_it_45 <= icend); _for_it_45 = (_for_it_45 + 1)) {
            {
                {
                    double ydecldp_var_47_0_in_rlmin = v_ydecldp_var_47_rlmin[0];
                    double za_0_in_0 = __state->__6_za[((_for_it_45 + (sym_klon * (_for_it_23 - 1))) - 1)];
                    double zdqs_0_in_0 = __state->__6_zdqs[(_for_it_45 - 1)];
                    double _if_cond_28_out;

                    ///////////////////
                    // Tasklet code (T_l0_c0)
                    _if_cond_28_out = ((za_0_in_0 > 1e-14) && (zdqs_0_in_0 <= (-ydecldp_var_47_0_in_rlmin)));
                    ///////////////////

                    __state->__6__if_cond_28 = _if_cond_28_out;
                }
            }
            if ((__state->__6__if_cond_28 == 1)) {
                _if_cond_29 = (__state->__6_za[((_for_it_45 + (sym_klon * (_for_it_23 - 1))) - 1)] > 0.99);
                {
                    {
                        double zdqs_0_in_0 = __state->__6_zdqs[(_for_it_45 - 1)];
                        double tmp_arg_54_out;

                        ///////////////////
                        // Tasklet code (T_l802_c802)
                        tmp_arg_54_out = (-zdqs_0_in_0);
                        ///////////////////

                        __state->__6_tmp_arg_54 = tmp_arg_54_out;
                    }
                    {
                        double tmp_arg_54_0_in = __state->__6_tmp_arg_54;
                        double tmp_call_108_out;

                        ///////////////////
                        // Tasklet code (T_l802_c802)
                        tmp_call_108_out = max(tmp_arg_54_0_in, 0.0);
                        ///////////////////

                        __state->__6_tmp_call_108 = tmp_call_108_out;
                    }
                    {
                        double tmp_call_108_0_in = __state->__6_tmp_call_108;
                        double zlcond1_out_0;

                        ///////////////////
                        // Tasklet code (T_l802_c802)
                        zlcond1_out_0 = tmp_call_108_0_in;
                        ///////////////////

                        __state->__6_zlcond1[(_for_it_45 - 1)] = zlcond1_out_0;
                    }
                }
                if ((!(_if_cond_29 == 1))) {
                    {
                        {
                            double za_0_in_0 = __state->__6_za[((_for_it_45 + (sym_klon * (_for_it_23 - 1))) - 1)];
                            double za_1_in_0 = __state->__6_za[((_for_it_45 + (sym_klon * (_for_it_23 - 1))) - 1)];
                            double zqsmix_0_in_0 = __state->__6_zqsmix[((_for_it_45 + (sym_klon * (_for_it_23 - 1))) - 1)];
                            double zqx_0_in_0 = __state->__6_zqx[(((_for_it_45 + ((4 * sym_klev) * sym_klon)) + (sym_klon * (_for_it_23 - 1))) - 1)];
                            double zcdmax_out;

                            ///////////////////
                            // Tasklet code (T_l808_c808)
                            zcdmax_out = ((zqx_0_in_0 - (za_0_in_0 * zqsmix_0_in_0)) / za_1_in_0);
                            ///////////////////

                            __state->__6_zcdmax = zcdmax_out;
                        }
                    }
                } else if ((_if_cond_29 == 1)) {
                    {
                        {
                            double ydcst_0_in_retv = v_ydcst_retv[0];
                            double zqsmix_0_in_0 = __state->__6_zqsmix[((_for_it_45 + (sym_klon * (_for_it_23 - 1))) - 1)];
                            double zcor_out;

                            ///////////////////
                            // Tasklet code (T_l804_c804)
                            zcor_out = (1.0 / (1.0 - (ydcst_0_in_retv * zqsmix_0_in_0)));
                            ///////////////////

                            __state->__6_zcor = zcor_out;
                        }
                        {
                            double ztp1_0_in_0 = __state->__6_ztp1[((_for_it_45 + (sym_klon * (_for_it_23 - 1))) - 1)];
                            double oka_out;

                            ///////////////////
                            // Tasklet code (T_l805_c805)
                            oka_out = ztp1_0_in_0;
                            ///////////////////

                            __state->__6_oka = oka_out;
                        }
                        {
                            double oka_0_in = __state->__6_oka;
                            double ydthf_0_in_r4ies = v_ydthf_r4ies[0];
                            double tmp_arg_55_out;

                            ///////////////////
                            // Tasklet code (T_l806_c806)
                            tmp_arg_55_out = (oka_0_in - ydthf_0_in_r4ies);
                            ///////////////////

                            __state->__6_tmp_arg_55 = tmp_arg_55_out;
                        }
                        {
                            double tmp_arg_55_0_in = __state->__6_tmp_arg_55;
                            double tmp_call_112_out;

                            ///////////////////
                            // Tasklet code (T_l806_c806)
                            tmp_call_112_out = (dace::math::ipow(tmp_arg_55_0_in, 2));
                            ///////////////////

                            __state->__6_tmp_call_112 = tmp_call_112_out;
                        }
                        {
                            double oka_0_in = __state->__6_oka;
                            double ydthf_0_in_rtwat = v_ydthf_rtwat[0];
                            double tmp_call_117_out;

                            ///////////////////
                            // Tasklet code (T_l806_c806)
                            tmp_call_117_out = min(ydthf_0_in_rtwat, oka_0_in);
                            ///////////////////

                            __state->__6_tmp_call_117 = tmp_call_117_out;
                        }
                        {
                            double tmp_call_117_0_in = __state->__6_tmp_call_117;
                            double ydthf_0_in_rtice = v_ydthf_rtice[0];
                            double tmp_call_115_out;

                            ///////////////////
                            // Tasklet code (T_l806_c806)
                            tmp_call_115_out = max(ydthf_0_in_rtice, tmp_call_117_0_in);
                            ///////////////////

                            __state->__6_tmp_call_115 = tmp_call_115_out;
                        }
                    }
                    {
                        {
                            double tmp_call_115_0_in = __state->__6_tmp_call_115;
                            double ydthf_0_in_rtice = v_ydthf_rtice[0];
                            double ydthf_1_in_rtwat_rtice_r = v_ydthf_rtwat_rtice_r[0];
                            double tmp_arg_56_out;

                            ///////////////////
                            // Tasklet code (T_l806_c806)
                            tmp_arg_56_out = ((tmp_call_115_0_in - ydthf_0_in_rtice) * ydthf_1_in_rtwat_rtice_r);
                            ///////////////////

                            __state->__6_tmp_arg_56 = tmp_arg_56_out;
                        }
                        {
                            double tmp_arg_56_0_in = __state->__6_tmp_arg_56;
                            double tmp_call_113_out;

                            ///////////////////
                            // Tasklet code (T_l806_c806)
                            tmp_call_113_out = (dace::math::ipow(tmp_arg_56_0_in, 2));
                            ///////////////////

                            __state->__6_tmp_call_113 = tmp_call_113_out;
                        }
                        {
                            double tmp_call_113_0_in = __state->__6_tmp_call_113;
                            double tmp_call_111_out;

                            ///////////////////
                            // Tasklet code (T_l806_c806)
                            tmp_call_111_out = min(1.0, tmp_call_113_0_in);
                            ///////////////////

                            __state->__6_tmp_call_111 = tmp_call_111_out;
                        }
                        {
                            double oka_0_in = __state->__6_oka;
                            double ydthf_0_in_r4les = v_ydthf_r4les[0];
                            double tmp_arg_57_out;

                            ///////////////////
                            // Tasklet code (T_l806_c806)
                            tmp_arg_57_out = (oka_0_in - ydthf_0_in_r4les);
                            ///////////////////

                            __state->__6_tmp_arg_57 = tmp_arg_57_out;
                        }
                    }
                    {
                        {
                            double tmp_arg_57_0_in = __state->__6_tmp_arg_57;
                            double tmp_call_110_out;

                            ///////////////////
                            // Tasklet code (T_l806_c806)
                            tmp_call_110_out = (dace::math::ipow(tmp_arg_57_0_in, 2));
                            ///////////////////

                            __state->__6_tmp_call_110 = tmp_call_110_out;
                        }
                        {
                            double oka_0_in = __state->__6_oka;
                            double ydthf_0_in_rtwat = v_ydthf_rtwat[0];
                            double tmp_call_118_out;

                            ///////////////////
                            // Tasklet code (T_l806_c806)
                            tmp_call_118_out = min(ydthf_0_in_rtwat, oka_0_in);
                            ///////////////////

                            __state->__6_tmp_call_118 = tmp_call_118_out;
                        }
                        {
                            double tmp_call_118_0_in = __state->__6_tmp_call_118;
                            double ydthf_0_in_rtice = v_ydthf_rtice[0];
                            double tmp_call_116_out;

                            ///////////////////
                            // Tasklet code (T_l806_c806)
                            tmp_call_116_out = max(ydthf_0_in_rtice, tmp_call_118_0_in);
                            ///////////////////

                            __state->__6_tmp_call_116 = tmp_call_116_out;
                        }
                    }
                    {
                        {
                            double tmp_call_116_0_in = __state->__6_tmp_call_116;
                            double ydthf_0_in_rtice = v_ydthf_rtice[0];
                            double ydthf_1_in_rtwat_rtice_r = v_ydthf_rtwat_rtice_r[0];
                            double tmp_arg_58_out;

                            ///////////////////
                            // Tasklet code (T_l806_c806)
                            tmp_arg_58_out = ((tmp_call_116_0_in - ydthf_0_in_rtice) * ydthf_1_in_rtwat_rtice_r);
                            ///////////////////

                            __state->__6_tmp_arg_58 = tmp_arg_58_out;
                        }
                        {
                            double tmp_arg_58_0_in = __state->__6_tmp_arg_58;
                            double tmp_call_114_out;

                            ///////////////////
                            // Tasklet code (T_l806_c806)
                            tmp_call_114_out = (dace::math::ipow(tmp_arg_58_0_in, 2));
                            ///////////////////

                            __state->__6_tmp_call_114 = tmp_call_114_out;
                        }
                        {
                            double tmp_call_114_0_in = __state->__6_tmp_call_114;
                            double tmp_call_109_out;

                            ///////////////////
                            // Tasklet code (T_l806_c806)
                            tmp_call_109_out = min(1.0, tmp_call_114_0_in);
                            ///////////////////

                            __state->__6_tmp_call_109 = tmp_call_109_out;
                        }
                        {
                            double tmp_call_109_0_in = __state->__6_tmp_call_109;
                            double tmp_call_110_0_in = __state->__6_tmp_call_110;
                            double tmp_call_111_0_in = __state->__6_tmp_call_111;
                            double tmp_call_112_0_in = __state->__6_tmp_call_112;
                            double ydthf_0_in_r5alvcp = v_ydthf_r5alvcp[0];
                            double ydthf_1_in_r5alscp = v_ydthf_r5alscp[0];
                            double zcor_0_in = __state->__6_zcor;
                            double zqsmix_0_in_0 = __state->__6_zqsmix[((_for_it_45 + (sym_klon * (_for_it_23 - 1))) - 1)];
                            double zqsmix_1_in_0 = __state->__6_zqsmix[((_for_it_45 + (sym_klon * (_for_it_23 - 1))) - 1)];
                            double zqx_0_in_0 = __state->__6_zqx[(((_for_it_45 + ((4 * sym_klev) * sym_klon)) + (sym_klon * (_for_it_23 - 1))) - 1)];
                            double zcdmax_out;

                            ///////////////////
                            // Tasklet code (T_l806_c806)
                            zcdmax_out =
                                ((zqx_0_in_0 - zqsmix_0_in_0) / ((1.0 + ((((zcor_0_in * zqsmix_1_in_0) * tmp_call_109_0_in) * ydthf_0_in_r5alvcp) * (1.0 / tmp_call_110_0_in))) +
                                                                 (((1.0 - tmp_call_111_0_in) * ydthf_1_in_r5alscp) * (1.0 / tmp_call_112_0_in))));
                            ///////////////////

                            __state->__6_zcdmax = zcdmax_out;
                        }
                    }
                }
                {
                    {
                        double zcdmax_0_in = __state->__6_zcdmax;
                        double zlcond1_0_in_0 = __state->__6_zlcond1[(_for_it_45 - 1)];
                        double tmp_call_120_out;

                        ///////////////////
                        // Tasklet code (T_l810_c810)
                        tmp_call_120_out = min(zlcond1_0_in_0, zcdmax_0_in);
                        ///////////////////

                        __state->__6_tmp_call_120 = tmp_call_120_out;
                    }
                    {
                        double tmp_call_120_0_in = __state->__6_tmp_call_120;
                        double tmp_call_119_out;

                        ///////////////////
                        // Tasklet code (T_l810_c810)
                        tmp_call_119_out = max(tmp_call_120_0_in, 0.0);
                        ///////////////////

                        __state->__6_tmp_call_119 = tmp_call_119_out;
                    }
                    {
                        double tmp_call_119_0_in = __state->__6_tmp_call_119;
                        double zlcond1_out_0;

                        ///////////////////
                        // Tasklet code (T_l810_c810)
                        zlcond1_out_0 = tmp_call_119_0_in;
                        ///////////////////

                        __state->__6_zlcond1[(_for_it_45 - 1)] = zlcond1_out_0;
                    }
                    {
                        double za_0_in_0 = __state->__6_za[((_for_it_45 + (sym_klon * (_for_it_23 - 1))) - 1)];
                        double zlcond1_0_in_0 = __state->__6_zlcond1[(_for_it_45 - 1)];
                        double zlcond1_out_0;

                        ///////////////////
                        // Tasklet code (T_l811_c811)
                        zlcond1_out_0 = (za_0_in_0 * zlcond1_0_in_0);
                        ///////////////////

                        __state->__6_zlcond1[(_for_it_45 - 1)] = zlcond1_out_0;
                    }
                    {
                        double ydecldp_var_47_0_in_rlmin = v_ydecldp_var_47_rlmin[0];
                        double zlcond1_0_in_0 = __state->__6_zlcond1[(_for_it_45 - 1)];
                        double _if_cond_30_out;

                        ///////////////////
                        // Tasklet code (T_l812_c812)
                        _if_cond_30_out = (zlcond1_0_in_0 < ydecldp_var_47_0_in_rlmin);
                        ///////////////////

                        __state->__6__if_cond_30 = _if_cond_30_out;
                    }
                }
                if ((__state->__6__if_cond_30 == 1)) {
                    {
                        {
                            double zlcond1_out_0;

                            ///////////////////
                            // Tasklet code (T_l812_c812)
                            zlcond1_out_0 = 0.0;
                            ///////////////////

                            __state->__6_zlcond1[(_for_it_45 - 1)] = zlcond1_out_0;
                        }
                    }
                }
                {
                    {
                        double ydecldp_var_47_0_in_rthomo = v_ydecldp_var_47_rthomo[0];
                        double ztp1_0_in_0 = __state->__6_ztp1[((_for_it_45 + (sym_klon * (_for_it_23 - 1))) - 1)];
                        double _if_cond_31_out;

                        ///////////////////
                        // Tasklet code (T_l0_c0)
                        _if_cond_31_out = (ztp1_0_in_0 > ydecldp_var_47_0_in_rthomo);
                        ///////////////////

                        __state->__6__if_cond_31 = _if_cond_31_out;
                    }
                }
                if ((!(__state->__6__if_cond_31 == 1))) {
                    {
                        {
                            double zlcond1_0_in_0 = __state->__6_zlcond1[(_for_it_45 - 1)];
                            double zsolqa_0_in_0 = __state->__6_zsolqa[((_for_it_45 + (21 * sym_klon)) - 1)];
                            double zsolqa_out_0;

                            ///////////////////
                            // Tasklet code (T_l818_c818)
                            zsolqa_out_0 = (zsolqa_0_in_0 + zlcond1_0_in_0);
                            ///////////////////

                            __state->__6_zsolqa[((_for_it_45 + (21 * sym_klon)) - 1)] = zsolqa_out_0;
                        }
                        {
                            double zlcond1_0_in_0 = __state->__6_zlcond1[(_for_it_45 - 1)];
                            double zsolqa_0_in_0 = __state->__6_zsolqa[((_for_it_45 + (9 * sym_klon)) - 1)];
                            double zsolqa_out_0;

                            ///////////////////
                            // Tasklet code (T_l819_c819)
                            zsolqa_out_0 = (zsolqa_0_in_0 - zlcond1_0_in_0);
                            ///////////////////

                            __state->__6_zsolqa[((_for_it_45 + (9 * sym_klon)) - 1)] = zsolqa_out_0;
                        }
                        {
                            double zlcond1_0_in_0 = __state->__6_zlcond1[(_for_it_45 - 1)];
                            double zqxfg_0_in_0 = __state->__6_zqxfg[((_for_it_45 + sym_klon) - 1)];
                            double zqxfg_out_0;

                            ///////////////////
                            // Tasklet code (T_l820_c820)
                            zqxfg_out_0 = (zqxfg_0_in_0 + zlcond1_0_in_0);
                            ///////////////////

                            __state->__6_zqxfg[((_for_it_45 + sym_klon) - 1)] = zqxfg_out_0;
                        }
                    }
                } else if ((__state->__6__if_cond_31 == 1)) {
                    {
                        {
                            double zlcond1_0_in_0 = __state->__6_zlcond1[(_for_it_45 - 1)];
                            double zsolqa_0_in_0 = __state->__6_zsolqa[((_for_it_45 + (20 * sym_klon)) - 1)];
                            double zsolqa_out_0;

                            ///////////////////
                            // Tasklet code (T_l814_c814)
                            zsolqa_out_0 = (zsolqa_0_in_0 + zlcond1_0_in_0);
                            ///////////////////

                            __state->__6_zsolqa[((_for_it_45 + (20 * sym_klon)) - 1)] = zsolqa_out_0;
                        }
                        {
                            double zlcond1_0_in_0 = __state->__6_zlcond1[(_for_it_45 - 1)];
                            double zsolqa_0_in_0 = __state->__6_zsolqa[((_for_it_45 + (4 * sym_klon)) - 1)];
                            double zsolqa_out_0;

                            ///////////////////
                            // Tasklet code (T_l815_c815)
                            zsolqa_out_0 = (zsolqa_0_in_0 - zlcond1_0_in_0);
                            ///////////////////

                            __state->__6_zsolqa[((_for_it_45 + (4 * sym_klon)) - 1)] = zsolqa_out_0;
                        }
                        {
                            double zlcond1_0_in_0 = __state->__6_zlcond1[(_for_it_45 - 1)];
                            double zqxfg_0_in_0 = __state->__6_zqxfg[(_for_it_45 - 1)];
                            double zqxfg_out_0;

                            ///////////////////
                            // Tasklet code (T_l816_c816)
                            zqxfg_out_0 = (zqxfg_0_in_0 + zlcond1_0_in_0);
                            ///////////////////

                            __state->__6_zqxfg[(_for_it_45 - 1)] = zqxfg_out_0;
                        }
                    }
                }
            }
        }
        for (_for_it_46 = 1; (_for_it_46 <= icend); _for_it_46 = (_for_it_46 + 1)) {
            {
                {
                    double ydecldp_var_47_0_in_rlmin = v_ydecldp_var_47_rlmin[0];
                    double za_0_in_0 = __state->__6_za[((_for_it_46 + (sym_klon * (_for_it_23 - 1))) - 1)];
                    double zdqs_0_in_0 = __state->__6_zdqs[(_for_it_46 - 1)];
                    double _if_cond_32_out;

                    ///////////////////
                    // Tasklet code (T_l0_c0)
                    _if_cond_32_out = ((zdqs_0_in_0 <= (-ydecldp_var_47_0_in_rlmin)) && (za_0_in_0 < 0.99999999999999));
                    ///////////////////

                    __state->__6__if_cond_32 = _if_cond_32_out;
                }
            }
            if ((__state->__6__if_cond_32 == 1)) {
                {
                    {
                        double ydecldp_var_47_0_in_ramid = v_ydecldp_var_47_ramid[0];
                        double zrhc_out;

                        ///////////////////
                        // Tasklet code (T_l826_c826)
                        zrhc_out = ydecldp_var_47_0_in_ramid;
                        ///////////////////

                        __state->__6_zrhc = zrhc_out;
                    }
                }
                tmp_index_990 = ((klev[0] + 1) - 1);

                zsigk = (pap_var_17[((_for_it_46 + (sym_klon * (_for_it_23 - 1))) - 1)] / paph_var_18[((_for_it_46 + (sym_klon * tmp_index_990)) - 1)]);
                if (((zsigk > 0.8) == 1)) {
                    {
                        {
                            double tmp_arg_59_out;

                            ///////////////////
                            // Tasklet code (T_l829_c829)
                            tmp_arg_59_out = ((zsigk - 0.8) / 0.2);
                            ///////////////////

                            __state->__6_tmp_arg_59 = tmp_arg_59_out;
                        }
                        {
                            double tmp_arg_59_0_in = __state->__6_tmp_arg_59;
                            double tmp_call_121_out;

                            ///////////////////
                            // Tasklet code (T_l829_c829)
                            tmp_call_121_out = (dace::math::ipow(tmp_arg_59_0_in, 2));
                            ///////////////////

                            __state->__6_tmp_call_121 = tmp_call_121_out;
                        }
                        {
                            double tmp_call_121_0_in = __state->__6_tmp_call_121;
                            double ydecldp_var_47_0_in_ramid = v_ydecldp_var_47_ramid[0];
                            double ydecldp_var_47_1_in_ramid = v_ydecldp_var_47_ramid[0];
                            double zrhc_out;

                            ///////////////////
                            // Tasklet code (T_l829_c829)
                            zrhc_out = (ydecldp_var_47_0_in_ramid + ((1.0 - ydecldp_var_47_1_in_ramid) * tmp_call_121_0_in));
                            ///////////////////

                            __state->__6_zrhc = zrhc_out;
                        }
                    }
                }
                {
                    {
                        int ydecldp_var_47_0_in_nssopt = v_ydecldp_var_47_nssopt[0];
                        int _if_cond_34_out;

                        ///////////////////
                        // Tasklet code (T_l0_c0)
                        _if_cond_34_out = (ydecldp_var_47_0_in_nssopt == 0);
                        ///////////////////

                        __state->__6__if_cond_34 = _if_cond_34_out;
                    }
                }
                if ((!(__state->__6__if_cond_34 == 1))) {
                    {
                        {
                            int ydecldp_var_47_0_in_nssopt = v_ydecldp_var_47_nssopt[0];
                            int _if_cond_35_out;

                            ///////////////////
                            // Tasklet code (T_l834_c834)
                            _if_cond_35_out = (ydecldp_var_47_0_in_nssopt == 1);
                            ///////////////////

                            __state->__6__if_cond_35 = _if_cond_35_out;
                        }
                    }
                    if ((__state->__6__if_cond_35 == 1)) {
                        {
                            {
                                double za_0_in_0 = __state->__6_za[((_for_it_46 + (sym_klon * (_for_it_23 - 1))) - 1)];
                                double tmp_arg_61_out;

                                ///////////////////
                                // Tasklet code (T_l835_c835)
                                tmp_arg_61_out = (1.0 - za_0_in_0);
                                ///////////////////

                                __state->__6_tmp_arg_61 = tmp_arg_61_out;
                            }
                            {
                                double tmp_arg_61_0_in = __state->__6_tmp_arg_61;
                                double zepsec_0_in = __state->__6_zepsec;
                                double tmp_call_123_out;

                                ///////////////////
                                // Tasklet code (T_l835_c835)
                                tmp_call_123_out = max(zepsec_0_in, tmp_arg_61_0_in);
                                ///////////////////

                                __state->__6_tmp_call_123 = tmp_call_123_out;
                            }
                            {
                                double tmp_call_123_0_in = __state->__6_tmp_call_123;
                                double za_0_in_0 = __state->__6_za[((_for_it_46 + (sym_klon * (_for_it_23 - 1))) - 1)];
                                double zqsice_0_in_0 = __state->__6_zqsice[((_for_it_46 + (sym_klon * (_for_it_23 - 1))) - 1)];
                                double zqx_0_in_0 = __state->__6_zqx[(((_for_it_46 + ((4 * sym_klev) * sym_klon)) + (sym_klon * (_for_it_23 - 1))) - 1)];
                                double zqe_out;

                                ///////////////////
                                // Tasklet code (T_l835_c835)
                                zqe_out = ((zqx_0_in_0 - (za_0_in_0 * zqsice_0_in_0)) / tmp_call_123_0_in);
                                ///////////////////

                                __state->__6_zqe = zqe_out;
                            }
                            {
                                double zqe_0_in = __state->__6_zqe;
                                double zqe_out;

                                ///////////////////
                                // Tasklet code (T_l836_c836)
                                zqe_out = max(0.0, zqe_0_in);
                                ///////////////////

                                __state->__6_zqe = zqe_out;
                            }
                        }
                    } else if ((!(__state->__6__if_cond_35 == 1))) {
                        {
                            {
                                int ydecldp_var_47_0_in_nssopt = v_ydecldp_var_47_nssopt[0];
                                int _if_cond_36_out;

                                ///////////////////
                                // Tasklet code (T_l837_c837)
                                _if_cond_36_out = (ydecldp_var_47_0_in_nssopt == 2);
                                ///////////////////

                                __state->__6__if_cond_36 = _if_cond_36_out;
                            }
                        }
                        if ((!(__state->__6__if_cond_36 == 1))) {
                            {
                                {
                                    int ydecldp_var_47_0_in_nssopt = v_ydecldp_var_47_nssopt[0];
                                    int _if_cond_37_out;

                                    ///////////////////
                                    // Tasklet code (T_l839_c839)
                                    _if_cond_37_out = (ydecldp_var_47_0_in_nssopt == 3);
                                    ///////////////////

                                    __state->__6__if_cond_37 = _if_cond_37_out;
                                }
                            }
                            if ((__state->__6__if_cond_37 == 1)) {
                                {
                                    {
                                        double zli_0_in_0 = __state->__6_zli[((_for_it_46 + (sym_klon * (_for_it_23 - 1))) - 1)];
                                        double zqx_0_in_0 = __state->__6_zqx[(((_for_it_46 + ((4 * sym_klev) * sym_klon)) + (sym_klon * (_for_it_23 - 1))) - 1)];
                                        double zqe_out;

                                        ///////////////////
                                        // Tasklet code (T_l840_c840)
                                        zqe_out = (zqx_0_in_0 + zli_0_in_0);
                                        ///////////////////

                                        __state->__6_zqe = zqe_out;
                                    }
                                }
                            }
                        } else if ((__state->__6__if_cond_36 == 1)) {
                            {
                                {
                                    double zqx_0_in_0 = __state->__6_zqx[(((_for_it_46 + ((4 * sym_klev) * sym_klon)) + (sym_klon * (_for_it_23 - 1))) - 1)];
                                    double zqe_out;

                                    ///////////////////
                                    // Tasklet code (T_l838_c838)
                                    zqe_out = zqx_0_in_0;
                                    ///////////////////

                                    __state->__6_zqe = zqe_out;
                                }
                            }
                        }
                    }
                } else if ((__state->__6__if_cond_34 == 1)) {
                    {
                        {
                            double za_0_in_0 = __state->__6_za[((_for_it_46 + (sym_klon * (_for_it_23 - 1))) - 1)];
                            double tmp_arg_60_out;

                            ///////////////////
                            // Tasklet code (T_l832_c832)
                            tmp_arg_60_out = (1.0 - za_0_in_0);
                            ///////////////////

                            __state->__6_tmp_arg_60 = tmp_arg_60_out;
                        }
                        {
                            double tmp_arg_60_0_in = __state->__6_tmp_arg_60;
                            double zepsec_0_in = __state->__6_zepsec;
                            double tmp_call_122_out;

                            ///////////////////
                            // Tasklet code (T_l832_c832)
                            tmp_call_122_out = max(zepsec_0_in, tmp_arg_60_0_in);
                            ///////////////////

                            __state->__6_tmp_call_122 = tmp_call_122_out;
                        }
                        {
                            double tmp_call_122_0_in = __state->__6_tmp_call_122;
                            double za_0_in_0 = __state->__6_za[((_for_it_46 + (sym_klon * (_for_it_23 - 1))) - 1)];
                            double zqsice_0_in_0 = __state->__6_zqsice[((_for_it_46 + (sym_klon * (_for_it_23 - 1))) - 1)];
                            double zqx_0_in_0 = __state->__6_zqx[(((_for_it_46 + ((4 * sym_klev) * sym_klon)) + (sym_klon * (_for_it_23 - 1))) - 1)];
                            double zqe_out;

                            ///////////////////
                            // Tasklet code (T_l832_c832)
                            zqe_out = ((zqx_0_in_0 - (za_0_in_0 * zqsice_0_in_0)) / tmp_call_122_0_in);
                            ///////////////////

                            __state->__6_zqe = zqe_out;
                        }
                        {
                            double zqe_0_in = __state->__6_zqe;
                            double zqe_out;

                            ///////////////////
                            // Tasklet code (T_l833_c833)
                            zqe_out = max(0.0, zqe_0_in);
                            ///////////////////

                            __state->__6_zqe = zqe_out;
                        }
                    }
                }
                {
                    {
                        double ydcst_0_in_rtt = v_ydcst_rtt[0];
                        int ydecldp_var_47_0_in_nssopt = v_ydecldp_var_47_nssopt[0];
                        double ztp1_0_in_0 = __state->__6_ztp1[((_for_it_46 + (sym_klon * (_for_it_23 - 1))) - 1)];
                        double _if_cond_38_out;

                        ///////////////////
                        // Tasklet code (T_l0_c0)
                        _if_cond_38_out = ((ztp1_0_in_0 >= ydcst_0_in_rtt) || (ydecldp_var_47_0_in_nssopt == 0));
                        ///////////////////

                        __state->__6__if_cond_38 = _if_cond_38_out;
                    }
                }
                if ((__state->__6__if_cond_38 == 1)) {
                    zfac = 1.0;

                } else if ((!(__state->__6__if_cond_38 == 1))) {
                    zfac = __state->__6_zfokoop[(_for_it_46 - 1)];
                }
                _if_cond_39 =
                    ((__state->__6_zqe >= ((__state->__6_zrhc * __state->__6_zqsice[((_for_it_46 + (sym_klon * (_for_it_23 - 1))) - 1)]) * zfac)) &&
                     (__state->__6_zqe < (__state->__6_zqsice[((_for_it_46 + (sym_klon * (_for_it_23 - 1))) - 1)] * zfac)));
                if ((_if_cond_39 == 1)) {
                    {
                        {
                            double zqe_0_in = __state->__6_zqe;
                            double zqsice_0_in_0 = __state->__6_zqsice[((_for_it_46 + (sym_klon * (_for_it_23 - 1))) - 1)];
                            double tmp_arg_62_out;

                            ///////////////////
                            // Tasklet code (T_l848_c848)
                            tmp_arg_62_out = (2.0 * ((zfac * zqsice_0_in_0) - zqe_0_in));
                            ///////////////////

                            __state->__6_tmp_arg_62 = tmp_arg_62_out;
                        }
                        {
                            double tmp_arg_62_0_in = __state->__6_tmp_arg_62;
                            double zepsec_0_in = __state->__6_zepsec;
                            double tmp_call_124_out;

                            ///////////////////
                            // Tasklet code (T_l848_c848)
                            tmp_call_124_out = max(tmp_arg_62_0_in, zepsec_0_in);
                            ///////////////////

                            __state->__6_tmp_call_124 = tmp_call_124_out;
                        }
                        {
                            double za_0_in_0 = __state->__6_za[((_for_it_46 + (sym_klon * (_for_it_23 - 1))) - 1)];
                            double tmp_arg_63_out;

                            ///////////////////
                            // Tasklet code (T_l849_c849)
                            tmp_arg_63_out = (1.0 - za_0_in_0);
                            ///////////////////

                            __state->__6_tmp_arg_63 = tmp_arg_63_out;
                        }
                        {
                            double tmp_call_124_0_in = __state->__6_tmp_call_124;
                            double za_0_in_0 = __state->__6_za[((_for_it_46 + (sym_klon * (_for_it_23 - 1))) - 1)];
                            double zdqs_0_in_0 = __state->__6_zdqs[(_for_it_46 - 1)];
                            double zacond_out;

                            ///////////////////
                            // Tasklet code (T_l848_c848)
                            zacond_out = (-((((1.0 - za_0_in_0) * zfac) * zdqs_0_in_0) / tmp_call_124_0_in));
                            ///////////////////

                            __state->__6_zacond = zacond_out;
                        }
                        {
                            double tmp_arg_63_0_in = __state->__6_tmp_arg_63;
                            double zacond_0_in = __state->__6_zacond;
                            double zacond_out;

                            ///////////////////
                            // Tasklet code (T_l849_c849)
                            zacond_out = min(zacond_0_in, tmp_arg_63_0_in);
                            ///////////////////

                            __state->__6_zacond = zacond_out;
                        }
                        {
                            double zacond_0_in = __state->__6_zacond;
                            double zdqs_0_in_0 = __state->__6_zdqs[(_for_it_46 - 1)];
                            double zlcond2_out_0;

                            ///////////////////
                            // Tasklet code (T_l850_c850)
                            zlcond2_out_0 = (-(((zfac * zdqs_0_in_0) * 0.5) * zacond_0_in));
                            ///////////////////

                            __state->__6_zlcond2[(_for_it_46 - 1)] = zlcond2_out_0;
                        }
                        {
                            double za_0_in_0 = __state->__6_za[((_for_it_46 + (sym_klon * (_for_it_23 - 1))) - 1)];
                            double tmp_arg_64_out;

                            ///////////////////
                            // Tasklet code (T_l851_c851)
                            tmp_arg_64_out = (1.0 - za_0_in_0);
                            ///////////////////

                            __state->__6_tmp_arg_64 = tmp_arg_64_out;
                        }
                        {
                            double tmp_arg_64_0_in = __state->__6_tmp_arg_64;
                            double zepsec_0_in = __state->__6_zepsec;
                            double tmp_call_125_out;

                            ///////////////////
                            // Tasklet code (T_l851_c851)
                            tmp_call_125_out = max(zepsec_0_in, tmp_arg_64_0_in);
                            ///////////////////

                            __state->__6_tmp_call_125 = tmp_call_125_out;
                        }
                        {
                            double tmp_call_125_0_in = __state->__6_tmp_call_125;
                            double zqe_0_in = __state->__6_zqe;
                            double zqsice_0_in_0 = __state->__6_zqsice[((_for_it_46 + (sym_klon * (_for_it_23 - 1))) - 1)];
                            double zzdl_out;

                            ///////////////////
                            // Tasklet code (T_l851_c851)
                            zzdl_out = ((2.0 * ((zfac * zqsice_0_in_0) - zqe_0_in)) / tmp_call_125_0_in);
                            ///////////////////

                            __state->__6_zzdl = zzdl_out;
                        }
                        {
                            double zdqs_0_in_0 = __state->__6_zdqs[(_for_it_46 - 1)];
                            double zzdl_0_in = __state->__6_zzdl;
                            double _if_cond_40_out;

                            ///////////////////
                            // Tasklet code (T_l0_c0)
                            _if_cond_40_out = ((zfac * zdqs_0_in_0) < (-zzdl_0_in));
                            ///////////////////

                            __state->__6__if_cond_40 = _if_cond_40_out;
                        }
                    }
                    if ((__state->__6__if_cond_40 == 1)) {
                        {
                            {
                                double za_0_in_0 = __state->__6_za[((_for_it_46 + (sym_klon * (_for_it_23 - 1))) - 1)];
                                double zdqs_0_in_0 = __state->__6_zdqs[(_for_it_46 - 1)];
                                double zqsice_0_in_0 = __state->__6_zqsice[((_for_it_46 + (sym_klon * (_for_it_23 - 1))) - 1)];
                                double zqx_0_in_0 = __state->__6_zqx[(((_for_it_46 + ((4 * sym_klev) * sym_klon)) + (sym_klon * (_for_it_23 - 1))) - 1)];
                                double zlcondlim_out;

                                ///////////////////
                                // Tasklet code (T_l853_c853)
                                zlcondlim_out = (((((za_0_in_0 - 1.0) * zfac) * zdqs_0_in_0) - (zfac * zqsice_0_in_0)) + zqx_0_in_0);
                                ///////////////////

                                __state->__6_zlcondlim = zlcondlim_out;
                            }
                            {
                                double zlcond2_0_in_0 = __state->__6_zlcond2[(_for_it_46 - 1)];
                                double zlcondlim_0_in = __state->__6_zlcondlim;
                                double tmp_call_126_out;

                                ///////////////////
                                // Tasklet code (T_l854_c854)
                                tmp_call_126_out = min(zlcond2_0_in_0, zlcondlim_0_in);
                                ///////////////////

                                __state->__6_tmp_call_126 = tmp_call_126_out;
                            }
                            {
                                double tmp_call_126_0_in = __state->__6_tmp_call_126;
                                double zlcond2_out_0;

                                ///////////////////
                                // Tasklet code (T_l854_c854)
                                zlcond2_out_0 = tmp_call_126_0_in;
                                ///////////////////

                                __state->__6_zlcond2[(_for_it_46 - 1)] = zlcond2_out_0;
                            }
                        }
                    }
                    {
                        {
                            double zlcond2_0_in_0 = __state->__6_zlcond2[(_for_it_46 - 1)];
                            double tmp_call_127_out;

                            ///////////////////
                            // Tasklet code (T_l856_c856)
                            tmp_call_127_out = max(zlcond2_0_in_0, 0.0);
                            ///////////////////

                            __state->__6_tmp_call_127 = tmp_call_127_out;
                        }
                        {
                            double tmp_call_127_0_in = __state->__6_tmp_call_127;
                            double zlcond2_out_0;

                            ///////////////////
                            // Tasklet code (T_l856_c856)
                            zlcond2_out_0 = tmp_call_127_0_in;
                            ///////////////////

                            __state->__6_zlcond2[(_for_it_46 - 1)] = zlcond2_out_0;
                        }
                        {
                            double ydecldp_var_47_0_in_rlmin = v_ydecldp_var_47_rlmin[0];
                            double za_0_in_0 = __state->__6_za[((_for_it_46 + (sym_klon * (_for_it_23 - 1))) - 1)];
                            double zlcond2_0_in_0 = __state->__6_zlcond2[(_for_it_46 - 1)];
                            double _if_cond_41_out;

                            ///////////////////
                            // Tasklet code (T_l0_c0)
                            _if_cond_41_out = ((zlcond2_0_in_0 < ydecldp_var_47_0_in_rlmin) || ((1.0 - za_0_in_0) < 1e-14));
                            ///////////////////

                            __state->__6__if_cond_41 = _if_cond_41_out;
                        }
                    }
                    if ((__state->__6__if_cond_41 == 1)) {
                        {
                            {
                                double zlcond2_out_0;

                                ///////////////////
                                // Tasklet code (T_l858_c858)
                                zlcond2_out_0 = 0.0;
                                ///////////////////

                                __state->__6_zlcond2[(_for_it_46 - 1)] = zlcond2_out_0;
                            }
                            {
                                double zacond_out;

                                ///////////////////
                                // Tasklet code (T_l859_c859)
                                zacond_out = 0.0;
                                ///////////////////

                                __state->__6_zacond = zacond_out;
                            }
                        }
                    }
                    _if_cond_42 = (__state->__6_zlcond2[(_for_it_46 - 1)] == 0.0);
                    if ((_if_cond_42 == 1)) {
                        {
                            {
                                double zacond_out;

                                ///////////////////
                                // Tasklet code (T_l861_c861)
                                zacond_out = 0.0;
                                ///////////////////

                                __state->__6_zacond = zacond_out;
                            }
                        }
                    }
                    {
                        {
                            double zacond_0_in = __state->__6_zacond;
                            double zsolac_0_in_0 = __state->__6_zsolac[(_for_it_46 - 1)];
                            double zsolac_out_0;

                            ///////////////////
                            // Tasklet code (T_l862_c862)
                            zsolac_out_0 = (zsolac_0_in_0 + zacond_0_in);
                            ///////////////////

                            __state->__6_zsolac[(_for_it_46 - 1)] = zsolac_out_0;
                        }
                        {
                            double ydecldp_var_47_0_in_rthomo = v_ydecldp_var_47_rthomo[0];
                            double ztp1_0_in_0 = __state->__6_ztp1[((_for_it_46 + (sym_klon * (_for_it_23 - 1))) - 1)];
                            double _if_cond_43_out;

                            ///////////////////
                            // Tasklet code (T_l0_c0)
                            _if_cond_43_out = (ztp1_0_in_0 > ydecldp_var_47_0_in_rthomo);
                            ///////////////////

                            __state->__6__if_cond_43 = _if_cond_43_out;
                        }
                    }
                    if ((__state->__6__if_cond_43 == 1)) {
                        {
                            {
                                double zlcond2_0_in_0 = __state->__6_zlcond2[(_for_it_46 - 1)];
                                double zsolqa_0_in_0 = __state->__6_zsolqa[((_for_it_46 + (20 * sym_klon)) - 1)];
                                double zsolqa_out_0;

                                ///////////////////
                                // Tasklet code (T_l864_c864)
                                zsolqa_out_0 = (zsolqa_0_in_0 + zlcond2_0_in_0);
                                ///////////////////

                                __state->__6_zsolqa[((_for_it_46 + (20 * sym_klon)) - 1)] = zsolqa_out_0;
                            }
                            {
                                double zlcond2_0_in_0 = __state->__6_zlcond2[(_for_it_46 - 1)];
                                double zsolqa_0_in_0 = __state->__6_zsolqa[((_for_it_46 + (4 * sym_klon)) - 1)];
                                double zsolqa_out_0;

                                ///////////////////
                                // Tasklet code (T_l865_c865)
                                zsolqa_out_0 = (zsolqa_0_in_0 - zlcond2_0_in_0);
                                ///////////////////

                                __state->__6_zsolqa[((_for_it_46 + (4 * sym_klon)) - 1)] = zsolqa_out_0;
                            }
                            {
                                double zlcond2_0_in_0 = __state->__6_zlcond2[(_for_it_46 - 1)];
                                double zqxfg_0_in_0 = __state->__6_zqxfg[(_for_it_46 - 1)];
                                double zqxfg_out_0;

                                ///////////////////
                                // Tasklet code (T_l866_c866)
                                zqxfg_out_0 = (zqxfg_0_in_0 + zlcond2_0_in_0);
                                ///////////////////

                                __state->__6_zqxfg[(_for_it_46 - 1)] = zqxfg_out_0;
                            }
                        }
                    } else if ((!(__state->__6__if_cond_43 == 1))) {
                        {
                            {
                                double zlcond2_0_in_0 = __state->__6_zlcond2[(_for_it_46 - 1)];
                                double zsolqa_0_in_0 = __state->__6_zsolqa[((_for_it_46 + (21 * sym_klon)) - 1)];
                                double zsolqa_out_0;

                                ///////////////////
                                // Tasklet code (T_l868_c868)
                                zsolqa_out_0 = (zsolqa_0_in_0 + zlcond2_0_in_0);
                                ///////////////////

                                __state->__6_zsolqa[((_for_it_46 + (21 * sym_klon)) - 1)] = zsolqa_out_0;
                            }
                            {
                                double zlcond2_0_in_0 = __state->__6_zlcond2[(_for_it_46 - 1)];
                                double zsolqa_0_in_0 = __state->__6_zsolqa[((_for_it_46 + (9 * sym_klon)) - 1)];
                                double zsolqa_out_0;

                                ///////////////////
                                // Tasklet code (T_l869_c869)
                                zsolqa_out_0 = (zsolqa_0_in_0 - zlcond2_0_in_0);
                                ///////////////////

                                __state->__6_zsolqa[((_for_it_46 + (9 * sym_klon)) - 1)] = zsolqa_out_0;
                            }
                            {
                                double zlcond2_0_in_0 = __state->__6_zlcond2[(_for_it_46 - 1)];
                                double zqxfg_0_in_0 = __state->__6_zqxfg[((_for_it_46 + sym_klon) - 1)];
                                double zqxfg_out_0;

                                ///////////////////
                                // Tasklet code (T_l870_c870)
                                zqxfg_out_0 = (zqxfg_0_in_0 + zlcond2_0_in_0);
                                ///////////////////

                                __state->__6_zqxfg[((_for_it_46 + sym_klon) - 1)] = zqxfg_out_0;
                            }
                        }
                    }
                }
            }
        }
        for (_for_it_47 = 1; (_for_it_47 <= icend); _for_it_47 = (_for_it_47 + 1)) {
            {
                double* v_ydecldp_var_47_rcldtopcf;
                v_ydecldp_var_47_rcldtopcf = (double*)(&(ydecldp_var_47->rcldtopcf));

                {
                    double ydecldp_var_47_0_in_rcldtopcf = v_ydecldp_var_47_rcldtopcf[0];
                    double ydecldp_var_47_1_in_rcldtopcf = v_ydecldp_var_47_rcldtopcf[0];
                    double za_0_in_0 = __state->__6_za[((_for_it_47 + (sym_klon * (_for_it_23 - 2))) - 1)];
                    double za_1_in_0 = __state->__6_za[((_for_it_47 + (sym_klon * (_for_it_23 - 1))) - 1)];
                    double _if_cond_44_out;

                    ///////////////////
                    // Tasklet code (T_l0_c0)
                    _if_cond_44_out = ((za_0_in_0 < ydecldp_var_47_0_in_rcldtopcf) && (za_1_in_0 >= ydecldp_var_47_1_in_rcldtopcf));
                    ///////////////////

                    __state->__6__if_cond_44 = _if_cond_44_out;
                }
            }
            if ((__state->__6__if_cond_44 == 1)) {
                {
                    {
                        double zcldtopdist_out_0;

                        ///////////////////
                        // Tasklet code (T_l877_c877)
                        zcldtopdist_out_0 = 0.0;
                        ///////////////////

                        __state->__6_zcldtopdist[(_for_it_47 - 1)] = zcldtopdist_out_0;
                    }
                }
            } else if ((!(__state->__6__if_cond_44 == 1))) {
                {
                    {
                        double ydcst_0_in_rg = v_ydcst_rg[0];
                        double zcldtopdist_0_in_0 = __state->__6_zcldtopdist[(_for_it_47 - 1)];
                        double zdp_0_in_0 = __state->__6_zdp[(_for_it_47 - 1)];
                        double zrho_0_in_0 = __state->__6_zrho[(_for_it_47 - 1)];
                        double zcldtopdist_out_0;

                        ///////////////////
                        // Tasklet code (T_l879_c879)
                        zcldtopdist_out_0 = (zcldtopdist_0_in_0 + (zdp_0_in_0 / (zrho_0_in_0 * ydcst_0_in_rg)));
                        ///////////////////

                        __state->__6_zcldtopdist[(_for_it_47 - 1)] = zcldtopdist_out_0;
                    }
                }
            }
            {
                {
                    double ydcst_0_in_rtt = v_ydcst_rtt[0];
                    double ydecldp_var_47_0_in_rlmin = v_ydecldp_var_47_rlmin[0];
                    double zqxfg_0_in_0 = __state->__6_zqxfg[(_for_it_47 - 1)];
                    double ztp1_0_in_0 = __state->__6_ztp1[((_for_it_47 + (sym_klon * (_for_it_23 - 1))) - 1)];
                    double _if_cond_45_out;

                    ///////////////////
                    // Tasklet code (T_l0_c0)
                    _if_cond_45_out = ((ztp1_0_in_0 < ydcst_0_in_rtt) && (zqxfg_0_in_0 > ydecldp_var_47_0_in_rlmin));
                    ///////////////////

                    __state->__6__if_cond_45 = _if_cond_45_out;
                }
            }
            if ((__state->__6__if_cond_45 == 1)) {
                {
                    {
                        double ztp1_0_in_0 = __state->__6_ztp1[((_for_it_47 + (sym_klon * (_for_it_23 - 1))) - 1)];
                        double oka_out;

                        ///////////////////
                        // Tasklet code (T_l882_c882)
                        oka_out = ztp1_0_in_0;
                        ///////////////////

                        __state->__6_oka = oka_out;
                    }
                    {
                        double oka_0_in = __state->__6_oka;
                        double oka_1_in = __state->__6_oka;
                        double ydcst_0_in_rtt = v_ydcst_rtt[0];
                        double ydthf_0_in_r3ies = v_ydthf_r3ies[0];
                        double ydthf_1_in_r4ies = v_ydthf_r4ies[0];
                        double tmp_arg_65_out;

                        ///////////////////
                        // Tasklet code (T_l883_c883)
                        tmp_arg_65_out = ((ydthf_0_in_r3ies * (oka_0_in - ydcst_0_in_rtt)) / (oka_1_in - ydthf_1_in_r4ies));
                        ///////////////////

                        __state->__6_tmp_arg_65 = tmp_arg_65_out;
                    }
                    {
                        double tmp_arg_65_0_in = __state->__6_tmp_arg_65;
                        double tmp_call_128_out;

                        ///////////////////
                        // Tasklet code (T_l883_c883)
                        tmp_call_128_out = exp(tmp_arg_65_0_in);
                        ///////////////////

                        __state->__6_tmp_call_128 = tmp_call_128_out;
                    }
                    {
                        double tmp_call_128_0_in = __state->__6_tmp_call_128;
                        double ydcst_0_in_rv = v_ydcst_rv[0];
                        double ydcst_1_in_rd = v_ydcst_rd[0];
                        double ydthf_0_in_r2es = v_ydthf_r2es[0];
                        double zvpice_out;

                        ///////////////////
                        // Tasklet code (T_l883_c883)
                        zvpice_out = (((ydthf_0_in_r2es * tmp_call_128_0_in) * ydcst_0_in_rv) / ydcst_1_in_rd);
                        ///////////////////

                        __state->__6_zvpice = zvpice_out;
                    }
                    {
                        double zfokoop_0_in_0 = __state->__6_zfokoop[(_for_it_47 - 1)];
                        double zvpice_0_in = __state->__6_zvpice;
                        double zvpliq_out;

                        ///////////////////
                        // Tasklet code (T_l884_c884)
                        zvpliq_out = (zvpice_0_in * zfokoop_0_in_0);
                        ///////////////////

                        __state->__6_zvpliq = zvpliq_out;
                    }
                    {
                        double zvpice_0_in = __state->__6_zvpice;
                        double zvpliq_0_in = __state->__6_zvpliq;
                        double zvpliq_1_in = __state->__6_zvpliq;
                        double tmp_arg_66_out;

                        ///////////////////
                        // Tasklet code (T_l885_c885)
                        tmp_arg_66_out = (((12.96 * (zvpliq_0_in - zvpice_0_in)) / zvpliq_1_in) - 0.639);
                        ///////////////////

                        __state->__6_tmp_arg_66 = tmp_arg_66_out;
                    }
                    {
                        double tmp_arg_66_0_in = __state->__6_tmp_arg_66;
                        double tmp_call_129_out;

                        ///////////////////
                        // Tasklet code (T_l885_c885)
                        tmp_call_129_out = exp(tmp_arg_66_0_in);
                        ///////////////////

                        __state->__6_tmp_call_129 = tmp_call_129_out;
                    }
                    {
                        double tmp_call_129_0_in = __state->__6_tmp_call_129;
                        double zicenuclei_out_0;

                        ///////////////////
                        // Tasklet code (T_l885_c885)
                        zicenuclei_out_0 = (1000.0 * tmp_call_129_0_in);
                        ///////////////////

                        __state->__6_zicenuclei[(_for_it_47 - 1)] = zicenuclei_out_0;
                    }
                }
                {
                    double* v_ydcst_rlstt;
                    v_ydcst_rlstt = (double*)(&(ydcst->rlstt));

                    {
                        double ydcst_0_in_rlstt = v_ydcst_rlstt[0];
                        double ydcst_1_in_rlstt = v_ydcst_rlstt[0];
                        double ydcst_2_in_rv = v_ydcst_rv[0];
                        double ztp1_0_in_0 = __state->__6_ztp1[((_for_it_47 + (sym_klon * (_for_it_23 - 1))) - 1)];
                        double ztp1_1_in_0 = __state->__6_ztp1[((_for_it_47 + (sym_klon * (_for_it_23 - 1))) - 1)];
                        double zadd_out;

                        ///////////////////
                        // Tasklet code (T_l886_c886)
                        zadd_out = ((ydcst_0_in_rlstt * ((ydcst_1_in_rlstt / (ydcst_2_in_rv * ztp1_0_in_0)) - 1.0)) / (0.024 * ztp1_1_in_0));
                        ///////////////////

                        __state->__6_zadd = zadd_out;
                    }
                }
                {
                    double* v_ydecldp_var_47_riceinit;
                    v_ydecldp_var_47_riceinit = (double*)(&(ydecldp_var_47->riceinit));
                    double* v_ydecldp_var_47_rdepliqrefrate;
                    v_ydecldp_var_47_rdepliqrefrate = (double*)(&(ydecldp_var_47->rdepliqrefrate));
                    double* v_ydecldp_var_47_rdepliqrefdepth;
                    v_ydecldp_var_47_rdepliqrefdepth = (double*)(&(ydecldp_var_47->rdepliqrefdepth));

                    {
                        double pap_var_17_0_in_0 = pap_var_17[((_for_it_47 + (sym_klon * (_for_it_23 - 1))) - 1)];
                        double ydcst_0_in_rv = v_ydcst_rv[0];
                        double ztp1_0_in_0 = __state->__6_ztp1[((_for_it_47 + (sym_klon * (_for_it_23 - 1))) - 1)];
                        double zvpice_0_in = __state->__6_zvpice;
                        double zbdd_out;

                        ///////////////////
                        // Tasklet code (T_l887_c887)
                        zbdd_out = (((ydcst_0_in_rv * ztp1_0_in_0) * pap_var_17_0_in_0) / (2.21 * zvpice_0_in));
                        ///////////////////

                        __state->__6_zbdd = zbdd_out;
                    }
                    {
                        double zicenuclei_0_in_0 = __state->__6_zicenuclei[(_for_it_47 - 1)];
                        double tmp_arg_71_out;

                        ///////////////////
                        // Tasklet code (T_l893_c893)
                        tmp_arg_71_out = (zicenuclei_0_in_0 / 15000.0);
                        ///////////////////

                        __state->__6_tmp_arg_71 = tmp_arg_71_out;
                    }
                    {
                        double tmp_arg_71_0_in = __state->__6_tmp_arg_71;
                        double zinfactor_out;

                        ///////////////////
                        // Tasklet code (T_l893_c893)
                        zinfactor_out = min(tmp_arg_71_0_in, 1.0);
                        ///////////////////

                        __state->__6_zinfactor = zinfactor_out;
                    }
                    {
                        double zicenuclei_0_in_0 = __state->__6_zicenuclei[(_for_it_47 - 1)];
                        double zrho_0_in_0 = __state->__6_zrho[(_for_it_47 - 1)];
                        double tmp_arg_67_out;

                        ///////////////////
                        // Tasklet code (T_l888_c888)
                        tmp_arg_67_out = (zicenuclei_0_in_0 / zrho_0_in_0);
                        ///////////////////

                        __state->__6_tmp_arg_67 = tmp_arg_67_out;
                    }
                    {
                        double tmp_arg_67_0_in = __state->__6_tmp_arg_67;
                        double tmp_call_130_out;

                        ///////////////////
                        // Tasklet code (T_l888_c888)
                        tmp_call_130_out = dace::math::pow(tmp_arg_67_0_in, 0.666);
                        ///////////////////

                        __state->__6_tmp_call_130 = tmp_call_130_out;
                    }
                    {
                        double tmp_call_130_0_in = __state->__6_tmp_call_130;
                        double zadd_0_in = __state->__6_zadd;
                        double zbdd_0_in = __state->__6_zbdd;
                        double zvpice_0_in = __state->__6_zvpice;
                        double zvpice_1_in = __state->__6_zvpice;
                        double zvpliq_0_in = __state->__6_zvpliq;
                        double zcvds_out;

                        ///////////////////
                        // Tasklet code (T_l888_c888)
                        zcvds_out = (((7.8 * tmp_call_130_0_in) * (zvpliq_0_in - zvpice_0_in)) / ((8.87 * (zadd_0_in + zbdd_0_in)) * zvpice_1_in));
                        ///////////////////

                        __state->__6_zcvds = zcvds_out;
                    }
                    {
                        double ydecldp_var_47_0_in_riceinit = v_ydecldp_var_47_riceinit[0];
                        double zicenuclei_0_in_0 = __state->__6_zicenuclei[(_for_it_47 - 1)];
                        double zrho_0_in_0 = __state->__6_zrho[(_for_it_47 - 1)];
                        double tmp_arg_68_out;

                        ///////////////////
                        // Tasklet code (T_l889_c889)
                        tmp_arg_68_out = ((zicenuclei_0_in_0 * ydecldp_var_47_0_in_riceinit) / zrho_0_in_0);
                        ///////////////////

                        __state->__6_tmp_arg_68 = tmp_arg_68_out;
                    }
                    {
                        double tmp_arg_68_0_in = __state->__6_tmp_arg_68;
                        double zicecld_0_in_0 = __state->__6_zicecld[(_for_it_47 - 1)];
                        double zice0_out;

                        ///////////////////
                        // Tasklet code (T_l889_c889)
                        zice0_out = max(zicecld_0_in_0, tmp_arg_68_0_in);
                        ///////////////////

                        __state->__6_zice0 = zice0_out;
                    }
                    {
                        double zice0_0_in = __state->__6_zice0;
                        double tmp_call_131_out;

                        ///////////////////
                        // Tasklet code (T_l890_c890)
                        tmp_call_131_out = dace::math::pow(zice0_0_in, 0.666);
                        ///////////////////

                        __state->__6_tmp_call_131 = tmp_call_131_out;
                    }
                    {
                        double ptsphy_var_5_0_in = ptsphy_var_5[0];
                        double tmp_call_131_0_in = __state->__6_tmp_call_131;
                        double zcvds_0_in = __state->__6_zcvds;
                        double tmp_arg_69_out;

                        ///////////////////
                        // Tasklet code (T_l890_c890)
                        tmp_arg_69_out = (((0.666 * zcvds_0_in) * ptsphy_var_5_0_in) + tmp_call_131_0_in);
                        ///////////////////

                        __state->__6_tmp_arg_69 = tmp_arg_69_out;
                    }
                    {
                        double tmp_arg_69_0_in = __state->__6_tmp_arg_69;
                        double zinew_out;

                        ///////////////////
                        // Tasklet code (T_l890_c890)
                        zinew_out = dace::math::pow(tmp_arg_69_0_in, 1.5);
                        ///////////////////

                        __state->__6_zinew = zinew_out;
                    }
                    {
                        double za_0_in_0 = __state->__6_za[((_for_it_47 + (sym_klon * (_for_it_23 - 1))) - 1)];
                        double zice0_0_in = __state->__6_zice0;
                        double zinew_0_in = __state->__6_zinew;
                        double tmp_arg_70_out;

                        ///////////////////
                        // Tasklet code (T_l891_c891)
                        tmp_arg_70_out = (za_0_in_0 * (zinew_0_in - zice0_0_in));
                        ///////////////////

                        __state->__6_tmp_arg_70 = tmp_arg_70_out;
                    }
                    {
                        double tmp_arg_70_0_in = __state->__6_tmp_arg_70;
                        double zdepos_out;

                        ///////////////////
                        // Tasklet code (T_l891_c891)
                        zdepos_out = max(tmp_arg_70_0_in, 0.0);
                        ///////////////////

                        __state->__6_zdepos = zdepos_out;
                    }
                    {
                        double zdepos_0_in = __state->__6_zdepos;
                        double zqxfg_0_in_0 = __state->__6_zqxfg[(_for_it_47 - 1)];
                        double zdepos_out;

                        ///////////////////
                        // Tasklet code (T_l892_c892)
                        zdepos_out = min(zdepos_0_in, zqxfg_0_in_0);
                        ///////////////////

                        __state->__6_zdepos = zdepos_out;
                    }
                    {
                        double ydecldp_var_47_0_in_rdepliqrefrate = v_ydecldp_var_47_rdepliqrefrate[0];
                        double ydecldp_var_47_1_in_rdepliqrefdepth = v_ydecldp_var_47_rdepliqrefdepth[0];
                        double zcldtopdist_0_in_0 = __state->__6_zcldtopdist[(_for_it_47 - 1)];
                        double zinfactor_0_in = __state->__6_zinfactor;
                        double zinfactor_1_in = __state->__6_zinfactor;
                        double tmp_arg_72_out;

                        ///////////////////
                        // Tasklet code (T_l894_c894)
                        tmp_arg_72_out = (zinfactor_0_in + ((1.0 - zinfactor_1_in) * (ydecldp_var_47_0_in_rdepliqrefrate + (zcldtopdist_0_in_0 / ydecldp_var_47_1_in_rdepliqrefdepth))));
                        ///////////////////

                        __state->__6_tmp_arg_72 = tmp_arg_72_out;
                    }
                    {
                        double tmp_arg_72_0_in = __state->__6_tmp_arg_72;
                        double tmp_call_132_out;

                        ///////////////////
                        // Tasklet code (T_l894_c894)
                        tmp_call_132_out = min(tmp_arg_72_0_in, 1.0);
                        ///////////////////

                        __state->__6_tmp_call_132 = tmp_call_132_out;
                    }
                    {
                        double tmp_call_132_0_in = __state->__6_tmp_call_132;
                        double zdepos_0_in = __state->__6_zdepos;
                        double zdepos_out;

                        ///////////////////
                        // Tasklet code (T_l894_c894)
                        zdepos_out = (zdepos_0_in * tmp_call_132_0_in);
                        ///////////////////

                        __state->__6_zdepos = zdepos_out;
                    }
                    {
                        double zdepos_0_in = __state->__6_zdepos;
                        double zqxfg_0_in_0 = __state->__6_zqxfg[((_for_it_47 + sym_klon) - 1)];
                        double zqxfg_out_0;

                        ///////////////////
                        // Tasklet code (T_l897_c897)
                        zqxfg_out_0 = (zqxfg_0_in_0 + zdepos_0_in);
                        ///////////////////

                        __state->__6_zqxfg[((_for_it_47 + sym_klon) - 1)] = zqxfg_out_0;
                    }
                    {
                        double zdepos_0_in = __state->__6_zdepos;
                        double zqxfg_0_in_0 = __state->__6_zqxfg[(_for_it_47 - 1)];
                        double zqxfg_out_0;

                        ///////////////////
                        // Tasklet code (T_l898_c898)
                        zqxfg_out_0 = (zqxfg_0_in_0 - zdepos_0_in);
                        ///////////////////

                        __state->__6_zqxfg[(_for_it_47 - 1)] = zqxfg_out_0;
                    }
                    {
                        double zdepos_0_in = __state->__6_zdepos;
                        double zsolqa_0_in_0 = __state->__6_zsolqa[((_for_it_47 + sym_klon) - 1)];
                        double zsolqa_out_0;

                        ///////////////////
                        // Tasklet code (T_l895_c895)
                        zsolqa_out_0 = (zsolqa_0_in_0 + zdepos_0_in);
                        ///////////////////

                        __state->__6_zsolqa[((_for_it_47 + sym_klon) - 1)] = zsolqa_out_0;
                    }
                    {
                        double zdepos_0_in = __state->__6_zdepos;
                        double zsolqa_0_in_0 = __state->__6_zsolqa[((_for_it_47 + (5 * sym_klon)) - 1)];
                        double zsolqa_out_0;

                        ///////////////////
                        // Tasklet code (T_l896_c896)
                        zsolqa_out_0 = (zsolqa_0_in_0 - zdepos_0_in);
                        ///////////////////

                        __state->__6_zsolqa[((_for_it_47 + (5 * sym_klon)) - 1)] = zsolqa_out_0;
                    }
                }
            }
        }
        for (_for_it_48 = 1; (_for_it_48 <= icend); _for_it_48 = (_for_it_48 + 1)) {
            {
                {
                    double za_0_in_0 = __state->__6_za[((_for_it_48 + (sym_klon * (_for_it_23 - 1))) - 1)];
                    double zepsec_0_in = __state->__6_zepsec;
                    double tmp_call_133_out;

                    ///////////////////
                    // Tasklet code (T_l902_c902)
                    tmp_call_133_out = max(za_0_in_0, zepsec_0_in);
                    ///////////////////

                    __state->__6_tmp_call_133 = tmp_call_133_out;
                }
                {
                    double tmp_call_133_0_in = __state->__6_tmp_call_133;
                    double ztmpa_out;

                    ///////////////////
                    // Tasklet code (T_l902_c902)
                    ztmpa_out = (1.0 / tmp_call_133_0_in);
                    ///////////////////

                    __state->__6_ztmpa = ztmpa_out;
                }
                {
                    double zqxfg_0_in_0 = __state->__6_zqxfg[(_for_it_48 - 1)];
                    double ztmpa_0_in = __state->__6_ztmpa;
                    double zliqcld_out_0;

                    ///////////////////
                    // Tasklet code (T_l903_c903)
                    zliqcld_out_0 = (zqxfg_0_in_0 * ztmpa_0_in);
                    ///////////////////

                    __state->__6_zliqcld[(_for_it_48 - 1)] = zliqcld_out_0;
                }
                {
                    double zqxfg_0_in_0 = __state->__6_zqxfg[((_for_it_48 + sym_klon) - 1)];
                    double ztmpa_0_in = __state->__6_ztmpa;
                    double zicecld_out_0;

                    ///////////////////
                    // Tasklet code (T_l904_c904)
                    zicecld_out_0 = (zqxfg_0_in_0 * ztmpa_0_in);
                    ///////////////////

                    __state->__6_zicecld[(_for_it_48 - 1)] = zicecld_out_0;
                }
                {
                    double zicecld_0_in_0 = __state->__6_zicecld[(_for_it_48 - 1)];
                    double zliqcld_0_in_0 = __state->__6_zliqcld[(_for_it_48 - 1)];
                    double zlicld_out_0;

                    ///////////////////
                    // Tasklet code (T_l905_c905)
                    zlicld_out_0 = (zliqcld_0_in_0 + zicecld_0_in_0);
                    ///////////////////

                    __state->__6_zlicld[(_for_it_48 - 1)] = zlicld_out_0;
                }
            }
        }
        for (_for_it_49 = 1; (_for_it_49 <= 5); _for_it_49 = (_for_it_49 + 1)) {
            _if_cond_46 = (__state->__6_llfall[(_for_it_49 - 1)] || (_for_it_49 == 2));
            if ((_if_cond_46 == 1)) {
                for (_for_it_50 = 1; (_for_it_50 <= icend); _for_it_50 = (_for_it_50 + 1)) {
                    {
                        {
                            int ydecldp_var_47_0_in_ncldtop = v_ydecldp_var_47_ncldtop[0];
                            int _if_cond_47_out;

                            ///////////////////
                            // Tasklet code (T_l0_c0)
                            _if_cond_47_out = (_for_it_23 > ydecldp_var_47_0_in_ncldtop);
                            ///////////////////

                            __state->__6__if_cond_47 = _if_cond_47_out;
                        }
                    }
                    if ((__state->__6__if_cond_47 == 1)) {
                        {
                            {
                                double zdtgdp_0_in_0 = __state->__6_zdtgdp[(_for_it_50 - 1)];
                                double zpfplsx_0_in_0 = __state->__6_zpfplsx[(((_for_it_50 + (sym_klon * (_for_it_23 - 1))) + ((sym_klon * (_for_it_49 - 1)) * (sym_klev + 1))) - 1)];
                                double zfallsrce_out_0;

                                ///////////////////
                                // Tasklet code (T_l911_c911)
                                zfallsrce_out_0 = (zpfplsx_0_in_0 * zdtgdp_0_in_0);
                                ///////////////////

                                __state->__6_zfallsrce[((_for_it_50 + (sym_klon * (_for_it_49 - 1))) - 1)] = zfallsrce_out_0;
                            }
                            {
                                double zfallsrce_0_in_0 = __state->__6_zfallsrce[((_for_it_50 + (sym_klon * (_for_it_49 - 1))) - 1)];
                                double zsolqa_0_in_0 = __state->__6_zsolqa[((_for_it_50 + ((6 * sym_klon) * (_for_it_49 - 1))) - 1)];
                                double zsolqa_out_0;

                                ///////////////////
                                // Tasklet code (T_l912_c912)
                                zsolqa_out_0 = (zsolqa_0_in_0 + zfallsrce_0_in_0);
                                ///////////////////

                                __state->__6_zsolqa[((_for_it_50 + ((6 * sym_klon) * (_for_it_49 - 1))) - 1)] = zsolqa_out_0;
                            }
                            {
                                double zfallsrce_0_in_0 = __state->__6_zfallsrce[((_for_it_50 + (sym_klon * (_for_it_49 - 1))) - 1)];
                                double zqxfg_0_in_0 = __state->__6_zqxfg[((_for_it_50 + (sym_klon * (_for_it_49 - 1))) - 1)];
                                double zqxfg_out_0;

                                ///////////////////
                                // Tasklet code (T_l913_c913)
                                zqxfg_out_0 = (zqxfg_0_in_0 + zfallsrce_0_in_0);
                                ///////////////////

                                __state->__6_zqxfg[((_for_it_50 + (sym_klon * (_for_it_49 - 1))) - 1)] = zqxfg_out_0;
                            }
                            {
                                double zqpretot_0_in_0 = __state->__6_zqpretot[(_for_it_50 - 1)];
                                double zqxfg_0_in_0 = __state->__6_zqxfg[((_for_it_50 + (sym_klon * (_for_it_49 - 1))) - 1)];
                                double zqpretot_out_0;

                                ///////////////////
                                // Tasklet code (T_l914_c914)
                                zqpretot_out_0 = (zqpretot_0_in_0 + zqxfg_0_in_0);
                                ///////////////////

                                __state->__6_zqpretot[(_for_it_50 - 1)] = zqpretot_out_0;
                            }
                        }
                    }
                    {
                        int* v_ydecldp_var_47_laericesed;
                        v_ydecldp_var_47_laericesed = (int*)(&(ydecldp_var_47->laericesed));

                        {
                            int ydecldp_var_47_0_in_laericesed = v_ydecldp_var_47_laericesed[0];
                            int _if_cond_48_out;

                            ///////////////////
                            // Tasklet code (T_l0_c0)
                            _if_cond_48_out = (ydecldp_var_47_0_in_laericesed && (_for_it_49 == 2));
                            ///////////////////

                            __state->__6__if_cond_48 = _if_cond_48_out;
                        }
                    }
                    if ((__state->__6__if_cond_48 == 1)) {
                        {
                            {
                                double pre_ice_var_2_0_in_0 = pre_ice_var_2[((_for_it_50 + (sym_klon * (_for_it_23 - 1))) - 1)];
                                double zre_ice_out;

                                ///////////////////
                                // Tasklet code (T_l917_c917)
                                zre_ice_out = pre_ice_var_2_0_in_0;
                                ///////////////////

                                __state->__6_zre_ice = zre_ice_out;
                            }
                            {
                                double zre_ice_0_in = __state->__6_zre_ice;
                                double tmp_call_134_out;

                                ///////////////////
                                // Tasklet code (T_l918_c918)
                                tmp_call_134_out = (dace::math::ipow(zre_ice_0_in, 1));
                                ///////////////////

                                __state->__6_tmp_call_134 = tmp_call_134_out;
                            }
                            {
                                double tmp_call_134_0_in = __state->__6_tmp_call_134;
                                double zvqx_out_0;

                                ///////////////////
                                // Tasklet code (T_l918_c918)
                                zvqx_out_0 = (0.002 * tmp_call_134_0_in);
                                ///////////////////

                                __state->__6_zvqx[1] = zvqx_out_0;
                            }
                        }
                    }
                    {
                        {
                            double zrho_0_in_0 = __state->__6_zrho[(_for_it_50 - 1)];
                            double zvqx_0_in_0 = __state->__6_zvqx[(_for_it_49 - 1)];
                            double zfall_out;

                            ///////////////////
                            // Tasklet code (T_l920_c920)
                            zfall_out = (zvqx_0_in_0 * zrho_0_in_0);
                            ///////////////////

                            __state->__6_zfall = zfall_out;
                        }
                        {
                            double zdtgdp_0_in_0 = __state->__6_zdtgdp[(_for_it_50 - 1)];
                            double zfall_0_in = __state->__6_zfall;
                            double zfallsink_out_0;

                            ///////////////////
                            // Tasklet code (T_l921_c921)
                            zfallsink_out_0 = (zdtgdp_0_in_0 * zfall_0_in);
                            ///////////////////

                            __state->__6_zfallsink[((_for_it_50 + (sym_klon * (_for_it_49 - 1))) - 1)] = zfallsink_out_0;
                        }
                    }
                }
            }
        }
        {
            {
#pragma omp parallel for
                for (auto _for_it_51 = 1; _for_it_51 < (icend + 1); _for_it_51 += 1) {
                    loop_body_50_1_0(
                        __state, ydecldp_var_47, &__state->__6_za[(_for_it_51 - 1)], &__state->__6_zqpretot[(_for_it_51 - 1)], &__state->__6_zqxfg[(_for_it_51 - 1)],
                        &__state->__6_zcovpclr[(_for_it_51 - 1)], &__state->__6_zcovpmax[(_for_it_51 - 1)], &__state->__6_zcovptot[(_for_it_51 - 1)], &__state->__6_zraincld[(_for_it_51 - 1)],
                        &__state->__6_zsnowcld[(_for_it_51 - 1)], _for_it_23, sym_klon);
                }
            }
            {
#pragma omp parallel for
                for (auto _for_it_52 = 1; _for_it_52 < (icend + 1); _for_it_52 += 1) {
                    loop_body_50_1_14(
                        __state, &picrit_aer_var_1[((_for_it_52 + (sym_klon * (_for_it_23 - 1))) - 1)], &plsm_var_19[(_for_it_52 - 1)],
                        &pnice_var_4[((_for_it_52 + (sym_klon * (_for_it_23 - 1))) - 1)], &ptsphy_var_5[0], ydcst, ydecldp_var_47, &__state->__6_za[((_for_it_52 + (sym_klon * (_for_it_23 - 1))) - 1)],
                        &__state->__6_zicecld[(_for_it_52 - 1)], &__state->__6_zliqcld[(_for_it_52 - 1)], &__state->__6_zqxfg[(_for_it_52 - 1)], &__state->__6_zraincld[(_for_it_52 - 1)],
                        &__state->__6_ztp1[((_for_it_52 + (sym_klon * (_for_it_23 - 1))) - 1)], &__state->__6_zrainacc[(_for_it_52 - 1)], &__state->__6_zrainaut[(_for_it_52 - 1)],
                        &__state->__6_zsnowaut[(_for_it_52 - 1)], &__state->__6_zsolqa[(_for_it_52 - 1)], &__state->__6_zsolqb[((_for_it_52 + (8 * sym_klon)) - 1)], sym_klon);
                }
            }
        }
        for (_for_it_53 = 1; (_for_it_53 <= icend); _for_it_53 = (_for_it_53 + 1)) {
            {
                {
                    double ydcst_0_in_rtt = v_ydcst_rtt[0];
                    double zliqcld_0_in_0 = __state->__6_zliqcld[(_for_it_53 - 1)];
                    double ztp1_0_in_0 = __state->__6_ztp1[((_for_it_53 + (sym_klon * (_for_it_23 - 1))) - 1)];
                    double _if_cond_59_out;

                    ///////////////////
                    // Tasklet code (T_l0_c0)
                    _if_cond_59_out = ((ztp1_0_in_0 <= ydcst_0_in_rtt) && (zliqcld_0_in_0 > 1e-14));
                    ///////////////////

                    __state->__6__if_cond_59 = _if_cond_59_out;
                }
            }
            if ((__state->__6__if_cond_59 == 1)) {
                _if_cond_60 = ((__state->__6_zsnowcld[(_for_it_53 - 1)] > 1e-14) && (__state->__6_zcovptot[(_for_it_53 - 1)] > 0.01));
                {
                    {
                        double ydecldp_var_47_0_in_rdensref = v_ydecldp_var_47_rdensref[0];
                        double zrho_0_in_0 = __state->__6_zrho[(_for_it_53 - 1)];
                        double tmp_arg_79_out;

                        ///////////////////
                        // Tasklet code (T_l989_c989)
                        tmp_arg_79_out = (ydecldp_var_47_0_in_rdensref / zrho_0_in_0);
                        ///////////////////

                        __state->__6_tmp_arg_79 = tmp_arg_79_out;
                    }
                    {
                        double tmp_arg_79_0_in = __state->__6_tmp_arg_79;
                        double zfallcorr_out;

                        ///////////////////
                        // Tasklet code (T_l989_c989)
                        zfallcorr_out = dace::math::pow(tmp_arg_79_0_in, 0.4);
                        ///////////////////

                        __state->__6_zfallcorr = zfallcorr_out;
                    }
                }
                if ((_if_cond_60 == 1)) {
                    {
                        double* v_ydecldp_var_47_rcl_const1s;
                        v_ydecldp_var_47_rcl_const1s = (double*)(&(ydecldp_var_47->rcl_const1s));
                        double* v_ydecldp_var_47_rcl_const8s;
                        v_ydecldp_var_47_rcl_const8s = (double*)(&(ydecldp_var_47->rcl_const8s));
                        double* v_ydecldp_var_47_rcl_const7s;
                        v_ydecldp_var_47_rcl_const7s = (double*)(&(ydecldp_var_47->rcl_const7s));

                        {
                            double ydecldp_var_47_0_in_rcl_const1s = v_ydecldp_var_47_rcl_const1s[0];
                            double zrho_0_in_0 = __state->__6_zrho[(_for_it_53 - 1)];
                            double zsnowcld_0_in_0 = __state->__6_zsnowcld[(_for_it_53 - 1)];
                            double tmp_arg_80_out;

                            ///////////////////
                            // Tasklet code (T_l991_c991)
                            tmp_arg_80_out = ((zrho_0_in_0 * zsnowcld_0_in_0) * ydecldp_var_47_0_in_rcl_const1s);
                            ///////////////////

                            __state->__6_tmp_arg_80 = tmp_arg_80_out;
                        }
                        {
                            double tmp_arg_80_0_in = __state->__6_tmp_arg_80;
                            double ydecldp_var_47_0_in_rcl_const8s = v_ydecldp_var_47_rcl_const8s[0];
                            double tmp_call_149_out;

                            ///////////////////
                            // Tasklet code (T_l991_c991)
                            tmp_call_149_out = dace::math::pow(tmp_arg_80_0_in, ydecldp_var_47_0_in_rcl_const8s);
                            ///////////////////

                            __state->__6_tmp_call_149 = tmp_call_149_out;
                        }
                        {
                            double ptsphy_var_5_0_in = ptsphy_var_5[0];
                            double tmp_call_149_0_in = __state->__6_tmp_call_149;
                            double ydecldp_var_47_0_in_rcl_const7s = v_ydecldp_var_47_rcl_const7s[0];
                            double zcovptot_0_in_0 = __state->__6_zcovptot[(_for_it_53 - 1)];
                            double zfallcorr_0_in = __state->__6_zfallcorr;
                            double zsnowrime_out_0;

                            ///////////////////
                            // Tasklet code (T_l991_c991)
                            zsnowrime_out_0 = (((((0.3 * zcovptot_0_in_0) * ptsphy_var_5_0_in) * ydecldp_var_47_0_in_rcl_const7s) * zfallcorr_0_in) * tmp_call_149_0_in);
                            ///////////////////

                            __state->__6_zsnowrime[(_for_it_53 - 1)] = zsnowrime_out_0;
                        }
                        {
                            double zsnowrime_0_in_0 = __state->__6_zsnowrime[(_for_it_53 - 1)];
                            double tmp_call_150_out;

                            ///////////////////
                            // Tasklet code (T_l992_c992)
                            tmp_call_150_out = min(zsnowrime_0_in_0, 1.0);
                            ///////////////////

                            __state->__6_tmp_call_150 = tmp_call_150_out;
                        }
                        {
                            double tmp_call_150_0_in = __state->__6_tmp_call_150;
                            double zsnowrime_out_0;

                            ///////////////////
                            // Tasklet code (T_l992_c992)
                            zsnowrime_out_0 = tmp_call_150_0_in;
                            ///////////////////

                            __state->__6_zsnowrime[(_for_it_53 - 1)] = zsnowrime_out_0;
                        }
                        {
                            double zsnowrime_0_in_0 = __state->__6_zsnowrime[(_for_it_53 - 1)];
                            double zsolqb_0_in_0 = __state->__6_zsolqb[((_for_it_53 + (3 * sym_klon)) - 1)];
                            double zsolqb_out_0;

                            ///////////////////
                            // Tasklet code (T_l993_c993)
                            zsolqb_out_0 = (zsolqb_0_in_0 + zsnowrime_0_in_0);
                            ///////////////////

                            __state->__6_zsolqb[((_for_it_53 + (3 * sym_klon)) - 1)] = zsolqb_out_0;
                        }
                    }
                }
            }
        }
        for (_for_it_54 = 1; (_for_it_54 <= icend); _for_it_54 = (_for_it_54 + 1)) {
            {
                {
                    double zmeltmax_out_0;

                    ///////////////////
                    // Tasklet code (T_l999_c999)
                    zmeltmax_out_0 = 0.0;
                    ///////////////////

                    __state->__6_zmeltmax[(_for_it_54 - 1)] = zmeltmax_out_0;
                }
                {
                    double zqxfg_0_in_0 = __state->__6_zqxfg[((_for_it_54 + sym_klon) - 1)];
                    double zqxfg_1_in_0 = __state->__6_zqxfg[((_for_it_54 + (3 * sym_klon)) - 1)];
                    double zicetot_out_0;

                    ///////////////////
                    // Tasklet code (T_l998_c998)
                    zicetot_out_0 = (zqxfg_0_in_0 + zqxfg_1_in_0);
                    ///////////////////

                    __state->__6_zicetot[(_for_it_54 - 1)] = zicetot_out_0;
                }
                {
                    double ydcst_0_in_rtt = v_ydcst_rtt[0];
                    double zicetot_0_in_0 = __state->__6_zicetot[(_for_it_54 - 1)];
                    double ztp1_0_in_0 = __state->__6_ztp1[((_for_it_54 + (sym_klon * (_for_it_23 - 1))) - 1)];
                    double _if_cond_61_out;

                    ///////////////////
                    // Tasklet code (T_l0_c0)
                    _if_cond_61_out = ((zicetot_0_in_0 > 1e-14) && (ztp1_0_in_0 > ydcst_0_in_rtt));
                    ///////////////////

                    __state->__6__if_cond_61 = _if_cond_61_out;
                }
            }
            if ((__state->__6__if_cond_61 == 1)) {
                {
                    {
                        double zqsice_0_in_0 = __state->__6_zqsice[((_for_it_54 + (sym_klon * (_for_it_23 - 1))) - 1)];
                        double zqx_0_in_0 = __state->__6_zqx[(((_for_it_54 + ((4 * sym_klev) * sym_klon)) + (sym_klon * (_for_it_23 - 1))) - 1)];
                        double tmp_arg_81_out;

                        ///////////////////
                        // Tasklet code (T_l1001_c1001)
                        tmp_arg_81_out = (zqsice_0_in_0 - zqx_0_in_0);
                        ///////////////////

                        __state->__6_tmp_arg_81 = tmp_arg_81_out;
                    }
                    {
                        double tmp_arg_81_0_in = __state->__6_tmp_arg_81;
                        double zsubsat_out;

                        ///////////////////
                        // Tasklet code (T_l1001_c1001)
                        zsubsat_out = max(tmp_arg_81_0_in, 0.0);
                        ///////////////////

                        __state->__6_zsubsat = zsubsat_out;
                    }
                    {
                        double pap_var_17_0_in_0 = pap_var_17[((_for_it_54 + (sym_klon * (_for_it_23 - 1))) - 1)];
                        double ydcst_0_in_rtt = v_ydcst_rtt[0];
                        double zsubsat_0_in = __state->__6_zsubsat;
                        double ztp1_0_in_0 = __state->__6_ztp1[((_for_it_54 + (sym_klon * (_for_it_23 - 1))) - 1)];
                        double ztp1_1_in_0 = __state->__6_ztp1[((_for_it_54 + (sym_klon * (_for_it_23 - 1))) - 1)];
                        double ztdmtw0_out;

                        ///////////////////
                        // Tasklet code (T_l1002_c1002)
                        ztdmtw0_out = ((ztp1_0_in_0 - ydcst_0_in_rtt) - (zsubsat_0_in * ((1329.31 + (0.0074615 * (pap_var_17_0_in_0 - 85000.0))) - (40.637 * (ztp1_1_in_0 - 275.0)))));
                        ///////////////////

                        __state->__6_ztdmtw0 = ztdmtw0_out;
                    }
                    {
                        double ptsphy_var_5_0_in = ptsphy_var_5[0];
                        double ydecldp_var_47_0_in_rtaumel = v_ydecldp_var_47_rtaumel[0];
                        double ztdmtw0_0_in = __state->__6_ztdmtw0;
                        double tmp_arg_82_out;

                        ///////////////////
                        // Tasklet code (T_l1003_c1003)
                        tmp_arg_82_out = ((ptsphy_var_5_0_in * (1.0 + (0.5 * ztdmtw0_0_in))) / ydecldp_var_47_0_in_rtaumel);
                        ///////////////////

                        __state->__6_tmp_arg_82 = tmp_arg_82_out;
                    }
                    {
                        double tmp_arg_82_0_in = __state->__6_tmp_arg_82;
                        double zcons1_out;

                        ///////////////////
                        // Tasklet code (T_l1003_c1003)
                        zcons1_out = abs(tmp_arg_82_0_in);
                        ///////////////////

                        __state->__6_zcons1 = zcons1_out;
                    }
                    {
                        double zcons1_0_in = __state->__6_zcons1;
                        double zrldcp_0_in = __state->__6_zrldcp;
                        double ztdmtw0_0_in = __state->__6_ztdmtw0;
                        double tmp_arg_83_out;

                        ///////////////////
                        // Tasklet code (T_l1004_c1004)
                        tmp_arg_83_out = ((ztdmtw0_0_in * zcons1_0_in) * zrldcp_0_in);
                        ///////////////////

                        __state->__6_tmp_arg_83 = tmp_arg_83_out;
                    }
                    {
                        double tmp_arg_83_0_in = __state->__6_tmp_arg_83;
                        double tmp_call_151_out;

                        ///////////////////
                        // Tasklet code (T_l1004_c1004)
                        tmp_call_151_out = max(tmp_arg_83_0_in, 0.0);
                        ///////////////////

                        __state->__6_tmp_call_151 = tmp_call_151_out;
                    }
                    {
                        double tmp_call_151_0_in = __state->__6_tmp_call_151;
                        double zmeltmax_out_0;

                        ///////////////////
                        // Tasklet code (T_l1004_c1004)
                        zmeltmax_out_0 = tmp_call_151_0_in;
                        ///////////////////

                        __state->__6_zmeltmax[(_for_it_54 - 1)] = zmeltmax_out_0;
                    }
                }
            }
        }
        for (_for_it_55 = 1; (_for_it_55 <= 5); _for_it_55 = (_for_it_55 + 1)) {
            _if_cond_62 = (__state->__6_iphase[(_for_it_55 - 1)] == 2);
            if ((_if_cond_62 == 1)) {
                jnn = __state->__6_imelt[(_for_it_55 - 1)];
                for (_for_it_56 = 1; (_for_it_56 <= icend); _for_it_56 = (_for_it_56 + 1)) {
                    _if_cond_63 = ((__state->__6_zmeltmax[(_for_it_56 - 1)] > 1e-14) && (__state->__6_zicetot[(_for_it_56 - 1)] > 1e-14));
                    if ((_if_cond_63 == 1)) {
                        {
                            {
                                double zicetot_0_in_0 = __state->__6_zicetot[(_for_it_56 - 1)];
                                double zqxfg_0_in_0 = __state->__6_zqxfg[((_for_it_56 + (sym_klon * (_for_it_55 - 1))) - 1)];
                                double zalfa_out;

                                ///////////////////
                                // Tasklet code (T_l1012_c1012)
                                zalfa_out = (zqxfg_0_in_0 / zicetot_0_in_0);
                                ///////////////////

                                __state->__6_zalfa = zalfa_out;
                            }
                            {
                                double zalfa_0_in = __state->__6_zalfa;
                                double zmeltmax_0_in_0 = __state->__6_zmeltmax[(_for_it_56 - 1)];
                                double tmp_arg_84_out;

                                ///////////////////
                                // Tasklet code (T_l1013_c1013)
                                tmp_arg_84_out = (zalfa_0_in * zmeltmax_0_in_0);
                                ///////////////////

                                __state->__6_tmp_arg_84 = tmp_arg_84_out;
                            }
                            {
                                double tmp_arg_84_0_in = __state->__6_tmp_arg_84;
                                double zqxfg_0_in_0 = __state->__6_zqxfg[((_for_it_56 + (sym_klon * (_for_it_55 - 1))) - 1)];
                                double zmelt_out;

                                ///////////////////
                                // Tasklet code (T_l1013_c1013)
                                zmelt_out = min(zqxfg_0_in_0, tmp_arg_84_0_in);
                                ///////////////////

                                __state->__6_zmelt = zmelt_out;
                            }
                            {
                                double zmelt_0_in = __state->__6_zmelt;
                                double zqxfg_0_in_0 = __state->__6_zqxfg[((_for_it_56 + (sym_klon * (_for_it_55 - 1))) - 1)];
                                double zqxfg_out_0;

                                ///////////////////
                                // Tasklet code (T_l1014_c1014)
                                zqxfg_out_0 = (zqxfg_0_in_0 - zmelt_0_in);
                                ///////////////////

                                __state->__6_zqxfg[((_for_it_56 + (sym_klon * (_for_it_55 - 1))) - 1)] = zqxfg_out_0;
                            }
                            {
                                double zmelt_0_in = __state->__6_zmelt;
                                double zqxfg_0_in_0 = __state->__6_zqxfg[((_for_it_56 + (sym_klon * (jnn - 1))) - 1)];
                                double zqxfg_out_0;

                                ///////////////////
                                // Tasklet code (T_l1015_c1015)
                                zqxfg_out_0 = (zqxfg_0_in_0 + zmelt_0_in);
                                ///////////////////

                                __state->__6_zqxfg[((_for_it_56 + (sym_klon * (jnn - 1))) - 1)] = zqxfg_out_0;
                            }
                            {
                                double zmelt_0_in = __state->__6_zmelt;
                                double zsolqa_0_in_0 = __state->__6_zsolqa[(((_for_it_56 + ((5 * sym_klon) * (_for_it_55 - 1))) + (sym_klon * (jnn - 1))) - 1)];
                                double zsolqa_out_0;

                                ///////////////////
                                // Tasklet code (T_l1016_c1016)
                                zsolqa_out_0 = (zsolqa_0_in_0 + zmelt_0_in);
                                ///////////////////

                                __state->__6_zsolqa[(((_for_it_56 + ((5 * sym_klon) * (_for_it_55 - 1))) + (sym_klon * (jnn - 1))) - 1)] = zsolqa_out_0;
                            }
                            {
                                double zmelt_0_in = __state->__6_zmelt;
                                double zsolqa_0_in_0 = __state->__6_zsolqa[(((_for_it_56 + (sym_klon * (_for_it_55 - 1))) + ((5 * sym_klon) * (jnn - 1))) - 1)];
                                double zsolqa_out_0;

                                ///////////////////
                                // Tasklet code (T_l1017_c1017)
                                zsolqa_out_0 = (zsolqa_0_in_0 - zmelt_0_in);
                                ///////////////////

                                __state->__6_zsolqa[(((_for_it_56 + (sym_klon * (_for_it_55 - 1))) + ((5 * sym_klon) * (jnn - 1))) - 1)] = zsolqa_out_0;
                            }
                        }
                    }
                }
            }
        }
        for (_for_it_57 = 1; (_for_it_57 <= icend); _for_it_57 = (_for_it_57 + 1)) {
            _if_cond_64 = (__state->__6_zqx[(((_for_it_57 + ((2 * sym_klev) * sym_klon)) + (sym_klon * (_for_it_23 - 1))) - 1)] > 1e-14);
            if ((_if_cond_64 == 1)) {
                {
                    {
                        double ydcst_0_in_rtt = v_ydcst_rtt[0];
                        double ydcst_1_in_rtt = v_ydcst_rtt[0];
                        double ztp1_0_in_0 = __state->__6_ztp1[((_for_it_57 + (sym_klon * (_for_it_23 - 1))) - 1)];
                        double ztp1_1_in_0 = __state->__6_ztp1[((_for_it_57 + (sym_klon * (_for_it_23 - 2))) - 1)];
                        double _if_cond_65_out;

                        ///////////////////
                        // Tasklet code (T_l0_c0)
                        _if_cond_65_out = ((ztp1_0_in_0 <= ydcst_0_in_rtt) && (ztp1_1_in_0 > ydcst_1_in_rtt));
                        ///////////////////

                        __state->__6__if_cond_65 = _if_cond_65_out;
                    }
                }
                if ((__state->__6__if_cond_65 == 1)) {
                    {
                        {
                            double zqx_0_in_0 = __state->__6_zqx[(((_for_it_57 + ((3 * sym_klev) * sym_klon)) + (sym_klon * (_for_it_23 - 1))) - 1)];
                            double zqx_1_in_0 = __state->__6_zqx[(((_for_it_57 + ((2 * sym_klev) * sym_klon)) + (sym_klon * (_for_it_23 - 1))) - 1)];
                            double tmp_arg_85_out;

                            ///////////////////
                            // Tasklet code (T_l1025_c1025)
                            tmp_arg_85_out = (zqx_0_in_0 + zqx_1_in_0);
                            ///////////////////

                            __state->__6_tmp_arg_85 = tmp_arg_85_out;
                        }
                        {
                            double tmp_arg_85_0_in = __state->__6_tmp_arg_85;
                            double zepsec_0_in = __state->__6_zepsec;
                            double tmp_call_152_out;

                            ///////////////////
                            // Tasklet code (T_l1025_c1025)
                            tmp_call_152_out = max(tmp_arg_85_0_in, zepsec_0_in);
                            ///////////////////

                            __state->__6_tmp_call_152 = tmp_call_152_out;
                        }
                        {
                            double tmp_call_152_0_in = __state->__6_tmp_call_152;
                            double zqpretot_out_0;

                            ///////////////////
                            // Tasklet code (T_l1025_c1025)
                            zqpretot_out_0 = tmp_call_152_0_in;
                            ///////////////////

                            __state->__6_zqpretot[(_for_it_57 - 1)] = zqpretot_out_0;
                        }
                        {
                            double zqpretot_0_in_0 = __state->__6_zqpretot[(_for_it_57 - 1)];
                            double zqx_0_in_0 = __state->__6_zqx[(((_for_it_57 + ((2 * sym_klev) * sym_klon)) + (sym_klon * (_for_it_23 - 1))) - 1)];
                            double prainfrac_toprfz_var_32_out_0;

                            ///////////////////
                            // Tasklet code (T_l1026_c1026)
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

                            __state->__6__if_cond_66 = _if_cond_66_out;
                        }
                    }
                    if ((__state->__6__if_cond_66 == 1)) {
                        {
                            {
                                int llrainliq_out_0;

                                ///////////////////
                                // Tasklet code (T_l1028_c1028)
                                llrainliq_out_0 = 1;
                                ///////////////////

                                __state->__6_llrainliq[(_for_it_57 - 1)] = llrainliq_out_0;
                            }
                        }
                    } else if ((!(__state->__6__if_cond_66 == 1))) {
                        {
                            {
                                int llrainliq_out_0;

                                ///////////////////
                                // Tasklet code (T_l1030_c1030)
                                llrainliq_out_0 = 0;
                                ///////////////////

                                __state->__6_llrainliq[(_for_it_57 - 1)] = llrainliq_out_0;
                            }
                        }
                    }
                }
                {
                    {
                        double ydcst_0_in_rtt = v_ydcst_rtt[0];
                        double ztp1_0_in_0 = __state->__6_ztp1[((_for_it_57 + (sym_klon * (_for_it_23 - 1))) - 1)];
                        double _if_cond_67_out;

                        ///////////////////
                        // Tasklet code (T_l0_c0)
                        _if_cond_67_out = (ztp1_0_in_0 < ydcst_0_in_rtt);
                        ///////////////////

                        __state->__6__if_cond_67 = _if_cond_67_out;
                    }
                }
                if ((__state->__6__if_cond_67 == 1)) {
                    _if_cond_68 = __state->__6_llrainliq[(_for_it_57 - 1)];
                    if ((!(_if_cond_68 == 1))) {
                        {
                            {
                                double ptsphy_var_5_0_in = ptsphy_var_5[0];
                                double ydcst_0_in_rtt = v_ydcst_rtt[0];
                                double ydecldp_var_47_0_in_rtaumel = v_ydecldp_var_47_rtaumel[0];
                                double ztp1_0_in_0 = __state->__6_ztp1[((_for_it_57 + (sym_klon * (_for_it_23 - 1))) - 1)];
                                double tmp_arg_87_out;

                                ///////////////////
                                // Tasklet code (T_l1040_c1040)
                                tmp_arg_87_out = ((ptsphy_var_5_0_in * (1.0 + (0.5 * (ydcst_0_in_rtt - ztp1_0_in_0)))) / ydecldp_var_47_0_in_rtaumel);
                                ///////////////////

                                __state->__6_tmp_arg_87 = tmp_arg_87_out;
                            }
                            {
                                double tmp_arg_87_0_in = __state->__6_tmp_arg_87;
                                double zcons1_out;

                                ///////////////////
                                // Tasklet code (T_l1040_c1040)
                                zcons1_out = abs(tmp_arg_87_0_in);
                                ///////////////////

                                __state->__6_zcons1 = zcons1_out;
                            }
                        }
                        {
                            {
                                double ydcst_0_in_rtt = v_ydcst_rtt[0];
                                double zcons1_0_in = __state->__6_zcons1;
                                double zrldcp_0_in = __state->__6_zrldcp;
                                double ztp1_0_in_0 = __state->__6_ztp1[((_for_it_57 + (sym_klon * (_for_it_23 - 1))) - 1)];
                                double tmp_arg_88_out;

                                ///////////////////
                                // Tasklet code (T_l1041_c1041)
                                tmp_arg_88_out = (((ydcst_0_in_rtt - ztp1_0_in_0) * zcons1_0_in) * zrldcp_0_in);
                                ///////////////////

                                __state->__6_tmp_arg_88 = tmp_arg_88_out;
                            }
                            {
                                double tmp_arg_88_0_in = __state->__6_tmp_arg_88;
                                double tmp_call_156_out;

                                ///////////////////
                                // Tasklet code (T_l1041_c1041)
                                tmp_call_156_out = max(tmp_arg_88_0_in, 0.0);
                                ///////////////////

                                __state->__6_tmp_call_156 = tmp_call_156_out;
                            }
                            {
                                double tmp_call_156_0_in = __state->__6_tmp_call_156;
                                double zfrzmax_out_0;

                                ///////////////////
                                // Tasklet code (T_l1041_c1041)
                                zfrzmax_out_0 = tmp_call_156_0_in;
                                ///////////////////

                                __state->__6_zfrzmax[(_for_it_57 - 1)] = zfrzmax_out_0;
                            }
                        }
                    } else if ((_if_cond_68 == 1)) {
                        {
                            double* v_ydecldp_var_47_rcl_fzrab;
                            v_ydecldp_var_47_rcl_fzrab = (double*)(&(ydecldp_var_47->rcl_fzrab));
                            double* v_ydecldp_var_47_rcl_const6r;
                            v_ydecldp_var_47_rcl_const6r = (double*)(&(ydecldp_var_47->rcl_const6r));
                            double* v_ydecldp_var_47_rcl_const5r;
                            v_ydecldp_var_47_rcl_const5r = (double*)(&(ydecldp_var_47->rcl_const5r));

                            {
                                double ydecldp_var_47_0_in_rcl_fac1 = v_ydecldp_var_47_rcl_fac1[0];
                                double zqx_0_in_0 = __state->__6_zqx[(((_for_it_57 + ((2 * sym_klev) * sym_klon)) + (sym_klon * (_for_it_23 - 1))) - 1)];
                                double zrho_0_in_0 = __state->__6_zrho[(_for_it_57 - 1)];
                                double tmp_arg_86_out;

                                ///////////////////
                                // Tasklet code (T_l1035_c1035)
                                tmp_arg_86_out = (ydecldp_var_47_0_in_rcl_fac1 / (zrho_0_in_0 * zqx_0_in_0));
                                ///////////////////

                                __state->__6_tmp_arg_86 = tmp_arg_86_out;
                            }
                            {
                                double tmp_arg_86_0_in = __state->__6_tmp_arg_86;
                                double ydecldp_var_47_0_in_rcl_fac2 = v_ydecldp_var_47_rcl_fac2[0];
                                double zlambda_out;

                                ///////////////////
                                // Tasklet code (T_l1035_c1035)
                                zlambda_out = dace::math::pow(tmp_arg_86_0_in, ydecldp_var_47_0_in_rcl_fac2);
                                ///////////////////

                                __state->__6_zlambda = zlambda_out;
                            }
                            {
                                double ydecldp_var_47_0_in_rcl_const6r = v_ydecldp_var_47_rcl_const6r[0];
                                double zlambda_0_in = __state->__6_zlambda;
                                double tmp_call_154_out;

                                ///////////////////
                                // Tasklet code (T_l1037_c1037)
                                tmp_call_154_out = dace::math::pow(zlambda_0_in, ydecldp_var_47_0_in_rcl_const6r);
                                ///////////////////

                                __state->__6_tmp_call_154 = tmp_call_154_out;
                            }
                            {
                                double ydcst_0_in_rtt = v_ydcst_rtt[0];
                                double ydecldp_var_47_0_in_rcl_fzrab = v_ydecldp_var_47_rcl_fzrab[0];
                                double ztp1_0_in_0 = __state->__6_ztp1[((_for_it_57 + (sym_klon * (_for_it_23 - 1))) - 1)];
                                double ztemp_out;

                                ///////////////////
                                // Tasklet code (T_l1036_c1036)
                                ztemp_out = (ydecldp_var_47_0_in_rcl_fzrab * (ztp1_0_in_0 - ydcst_0_in_rtt));
                                ///////////////////

                                __state->__6_ztemp = ztemp_out;
                            }
                            {
                                double ztemp_0_in = __state->__6_ztemp;
                                double tmp_call_153_out;

                                ///////////////////
                                // Tasklet code (T_l1037_c1037)
                                tmp_call_153_out = exp(ztemp_0_in);
                                ///////////////////

                                __state->__6_tmp_call_153 = tmp_call_153_out;
                            }
                            {
                                double ptsphy_var_5_0_in = ptsphy_var_5[0];
                                double tmp_call_153_0_in = __state->__6_tmp_call_153;
                                double tmp_call_154_0_in = __state->__6_tmp_call_154;
                                double ydecldp_var_47_0_in_rcl_const5r = v_ydecldp_var_47_rcl_const5r[0];
                                double zrho_0_in_0 = __state->__6_zrho[(_for_it_57 - 1)];
                                double zfrz_out;

                                ///////////////////
                                // Tasklet code (T_l1037_c1037)
                                zfrz_out = (((ptsphy_var_5_0_in * (ydecldp_var_47_0_in_rcl_const5r / zrho_0_in_0)) * (tmp_call_153_0_in - 1.0)) * tmp_call_154_0_in);
                                ///////////////////

                                __state->__6_zfrz = zfrz_out;
                            }
                            {
                                double zfrz_0_in = __state->__6_zfrz;
                                double tmp_call_155_out;

                                ///////////////////
                                // Tasklet code (T_l1038_c1038)
                                tmp_call_155_out = max(zfrz_0_in, 0.0);
                                ///////////////////

                                __state->__6_tmp_call_155 = tmp_call_155_out;
                            }
                            {
                                double tmp_call_155_0_in = __state->__6_tmp_call_155;
                                double zfrzmax_out_0;

                                ///////////////////
                                // Tasklet code (T_l1038_c1038)
                                zfrzmax_out_0 = tmp_call_155_0_in;
                                ///////////////////

                                __state->__6_zfrzmax[(_for_it_57 - 1)] = zfrzmax_out_0;
                            }
                        }
                    }
                    _if_cond_69 = (__state->__6_zfrzmax[(_for_it_57 - 1)] > 1e-14);
                    if ((_if_cond_69 == 1)) {
                        {
                            {
                                double zfrzmax_0_in_0 = __state->__6_zfrzmax[(_for_it_57 - 1)];
                                double zqx_0_in_0 = __state->__6_zqx[(((_for_it_57 + ((2 * sym_klev) * sym_klon)) + (sym_klon * (_for_it_23 - 1))) - 1)];
                                double zfrz_out;

                                ///////////////////
                                // Tasklet code (T_l1044_c1044)
                                zfrz_out = min(zqx_0_in_0, zfrzmax_0_in_0);
                                ///////////////////

                                __state->__6_zfrz = zfrz_out;
                            }
                            {
                                double zfrz_0_in = __state->__6_zfrz;
                                double zsolqa_0_in_0 = __state->__6_zsolqa[((_for_it_57 + (13 * sym_klon)) - 1)];
                                double zsolqa_out_0;

                                ///////////////////
                                // Tasklet code (T_l1045_c1045)
                                zsolqa_out_0 = (zsolqa_0_in_0 + zfrz_0_in);
                                ///////////////////

                                __state->__6_zsolqa[((_for_it_57 + (13 * sym_klon)) - 1)] = zsolqa_out_0;
                            }
                            {
                                double zfrz_0_in = __state->__6_zfrz;
                                double zsolqa_0_in_0 = __state->__6_zsolqa[((_for_it_57 + (17 * sym_klon)) - 1)];
                                double zsolqa_out_0;

                                ///////////////////
                                // Tasklet code (T_l1046_c1046)
                                zsolqa_out_0 = (zsolqa_0_in_0 - zfrz_0_in);
                                ///////////////////

                                __state->__6_zsolqa[((_for_it_57 + (17 * sym_klon)) - 1)] = zsolqa_out_0;
                            }
                        }
                    }
                }
            }
        }
        {
            {
#pragma omp parallel for
                for (auto _for_it_58 = 1; _for_it_58 < (icend + 1); _for_it_58 += 1) {
                    loop_body_50_2_0(
                        __state, ydecldp_var_47, __state->__6_zrldcp, &__state->__6_ztp1[((_for_it_58 + (sym_klon * (_for_it_23 - 1))) - 1)], &__state->__6_zfrzmax[(_for_it_58 - 1)], sym_klon);
                }
            }
        }
        jnn = __state->__6_imelt[0];
        for (_for_it_59 = 1; (_for_it_59 <= icend); _for_it_59 = (_for_it_59 + 1)) {
            _if_cond_70 = ((__state->__6_zfrzmax[(_for_it_59 - 1)] > 1e-14) && (__state->__6_zqxfg[(_for_it_59 - 1)] > 1e-14));
            if ((_if_cond_70 == 1)) {
                {
                    {
                        double zfrzmax_0_in_0 = __state->__6_zfrzmax[(_for_it_59 - 1)];
                        double zqxfg_0_in_0 = __state->__6_zqxfg[(_for_it_59 - 1)];
                        double zfrz_out;

                        ///////////////////
                        // Tasklet code (T_l1058_c1058)
                        zfrz_out = min(zqxfg_0_in_0, zfrzmax_0_in_0);
                        ///////////////////

                        __state->__6_zfrz = zfrz_out;
                    }
                    {
                        double zfrz_0_in = __state->__6_zfrz;
                        double zsolqa_0_in_0 = __state->__6_zsolqa[((_for_it_59 + (sym_klon * (jnn - 1))) - 1)];
                        double zsolqa_out_0;

                        ///////////////////
                        // Tasklet code (T_l1059_c1059)
                        zsolqa_out_0 = (zsolqa_0_in_0 + zfrz_0_in);
                        ///////////////////

                        __state->__6_zsolqa[((_for_it_59 + (sym_klon * (jnn - 1))) - 1)] = zsolqa_out_0;
                    }
                    {
                        double zfrz_0_in = __state->__6_zfrz;
                        double zsolqa_0_in_0 = __state->__6_zsolqa[((_for_it_59 + ((5 * sym_klon) * (jnn - 1))) - 1)];
                        double zsolqa_out_0;

                        ///////////////////
                        // Tasklet code (T_l1060_c1060)
                        zsolqa_out_0 = (zsolqa_0_in_0 - zfrz_0_in);
                        ///////////////////

                        __state->__6_zsolqa[((_for_it_59 + ((5 * sym_klon) * (jnn - 1))) - 1)] = zsolqa_out_0;
                    }
                }
            }
        }
        for (_for_it_60 = 1; (_for_it_60 <= icend); _for_it_60 = (_for_it_60 + 1)) {
            {
                {
                    double za_0_in_0 = __state->__6_za[((_for_it_60 + (sym_klon * (_for_it_23 - 1))) - 1)];
                    double tmp_arg_90_out;

                    ///////////////////
                    // Tasklet code (T_l1064_c1064)
                    tmp_arg_90_out = (1.0 - za_0_in_0);
                    ///////////////////

                    __state->__6_tmp_arg_90 = tmp_arg_90_out;
                }
                {
                    double tmp_arg_90_0_in = __state->__6_tmp_arg_90;
                    double zepsec_0_in = __state->__6_zepsec;
                    double tmp_call_158_out;

                    ///////////////////
                    // Tasklet code (T_l1064_c1064)
                    tmp_call_158_out = max(zepsec_0_in, tmp_arg_90_0_in);
                    ///////////////////

                    __state->__6_tmp_call_158 = tmp_call_158_out;
                }
                {
                    double tmp_call_158_0_in = __state->__6_tmp_call_158;
                    double ydecldp_var_47_0_in_rprecrhmax = v_ydecldp_var_47_rprecrhmax[0];
                    double ydecldp_var_47_1_in_rprecrhmax = v_ydecldp_var_47_rprecrhmax[0];
                    double zcovpmax_0_in_0 = __state->__6_zcovpmax[(_for_it_60 - 1)];
                    double zzrh_out;

                    ///////////////////
                    // Tasklet code (T_l1064_c1064)
                    zzrh_out = (ydecldp_var_47_0_in_rprecrhmax + (((1.0 - ydecldp_var_47_1_in_rprecrhmax) * zcovpmax_0_in_0) / tmp_call_158_0_in));
                    ///////////////////

                    __state->__6_zzrh = zzrh_out;
                }
            }
            {
                {
                    double ydecldp_var_47_0_in_rprecrhmax = v_ydecldp_var_47_rprecrhmax[0];
                    double zzrh_0_in = __state->__6_zzrh;
                    double tmp_call_159_out;

                    ///////////////////
                    // Tasklet code (T_l1065_c1065)
                    tmp_call_159_out = max(zzrh_0_in, ydecldp_var_47_0_in_rprecrhmax);
                    ///////////////////

                    __state->__6_tmp_call_159 = tmp_call_159_out;
                }
                {
                    double tmp_call_159_0_in = __state->__6_tmp_call_159;
                    double zzrh_out;

                    ///////////////////
                    // Tasklet code (T_l1065_c1065)
                    zzrh_out = min(tmp_call_159_0_in, 1.0);
                    ///////////////////

                    __state->__6_zzrh = zzrh_out;
                }
                {
                    double zzrh_0_in = __state->__6_zzrh;
                    double zzrh_out;

                    ///////////////////
                    // Tasklet code (T_l1066_c1066)
                    zzrh_out = min(0.8, zzrh_0_in);
                    ///////////////////

                    __state->__6_zzrh = zzrh_out;
                }
                {
                    double zqsliq_0_in_0 = __state->__6_zqsliq[((_for_it_60 + (sym_klon * (_for_it_23 - 1))) - 1)];
                    double zqx_0_in_0 = __state->__6_zqx[(((_for_it_60 + ((4 * sym_klev) * sym_klon)) + (sym_klon * (_for_it_23 - 1))) - 1)];
                    double tmp_call_160_out;

                    ///////////////////
                    // Tasklet code (T_l1067_c1067)
                    tmp_call_160_out = min(zqx_0_in_0, zqsliq_0_in_0);
                    ///////////////////

                    __state->__6_tmp_call_160 = tmp_call_160_out;
                }
                {
                    double tmp_call_160_0_in = __state->__6_tmp_call_160;
                    double zqe_out;

                    ///////////////////
                    // Tasklet code (T_l1067_c1067)
                    zqe_out = max(0.0, tmp_call_160_0_in);
                    ///////////////////

                    __state->__6_zqe = zqe_out;
                }
                {
                    double zcovpclr_0_in_0 = __state->__6_zcovpclr[(_for_it_60 - 1)];
                    double zqe_0_in = __state->__6_zqe;
                    double zqsliq_0_in_0 = __state->__6_zqsliq[((_for_it_60 + (sym_klon * (_for_it_23 - 1))) - 1)];
                    double zqxfg_0_in_0 = __state->__6_zqxfg[((_for_it_60 + (2 * sym_klon)) - 1)];
                    double zzrh_0_in = __state->__6_zzrh;
                    int llo1_out;

                    ///////////////////
                    // Tasklet code (T_l1068_c1068)
                    llo1_out = (((zcovpclr_0_in_0 > 1e-14) && (zqxfg_0_in_0 > 1e-14)) && (zqe_0_in < (zzrh_0_in * zqsliq_0_in_0)));
                    ///////////////////

                    __state->__6_llo1 = llo1_out;
                }
            }
            _if_cond_71 = __state->__6_llo1;
            if ((_if_cond_71 == 1)) {
                {
                    double* v_ydecldp_var_47_rcl_cdenom1;
                    v_ydecldp_var_47_rcl_cdenom1 = (double*)(&(ydecldp_var_47->rcl_cdenom1));
                    double* v_ydecldp_var_47_rcl_cdenom2;
                    v_ydecldp_var_47_rcl_cdenom2 = (double*)(&(ydecldp_var_47->rcl_cdenom2));
                    double* v_ydecldp_var_47_rcl_cdenom3;
                    v_ydecldp_var_47_rcl_cdenom3 = (double*)(&(ydecldp_var_47->rcl_cdenom3));
                    double* v_ydecldp_var_47_rcl_const3r;
                    v_ydecldp_var_47_rcl_const3r = (double*)(&(ydecldp_var_47->rcl_const3r));
                    double* v_ydecldp_var_47_rcl_const4r;
                    v_ydecldp_var_47_rcl_const4r = (double*)(&(ydecldp_var_47->rcl_const4r));
                    double* v_ydecldp_var_47_rcl_const1r;
                    v_ydecldp_var_47_rcl_const1r = (double*)(&(ydecldp_var_47->rcl_const1r));
                    double* v_ydecldp_var_47_rcl_const2r;
                    v_ydecldp_var_47_rcl_const2r = (double*)(&(ydecldp_var_47->rcl_const2r));

                    {
                        double zcovptot_0_in_0 = __state->__6_zcovptot[(_for_it_60 - 1)];
                        double zqxfg_0_in_0 = __state->__6_zqxfg[((_for_it_60 + (2 * sym_klon)) - 1)];
                        double zpreclr_out;

                        ///////////////////
                        // Tasklet code (T_l1070_c1070)
                        zpreclr_out = (zqxfg_0_in_0 / zcovptot_0_in_0);
                        ///////////////////

                        __state->__6_zpreclr = zpreclr_out;
                    }
                    {
                        double ydecldp_var_47_0_in_rdensref = v_ydecldp_var_47_rdensref[0];
                        double zrho_0_in_0 = __state->__6_zrho[(_for_it_60 - 1)];
                        double tmp_arg_91_out;

                        ///////////////////
                        // Tasklet code (T_l1071_c1071)
                        tmp_arg_91_out = (ydecldp_var_47_0_in_rdensref / zrho_0_in_0);
                        ///////////////////

                        __state->__6_tmp_arg_91 = tmp_arg_91_out;
                    }
                    {
                        double tmp_arg_91_0_in = __state->__6_tmp_arg_91;
                        double zfallcorr_out;

                        ///////////////////
                        // Tasklet code (T_l1071_c1071)
                        zfallcorr_out = dace::math::pow(tmp_arg_91_0_in, 0.4);
                        ///////////////////

                        __state->__6_zfallcorr = zfallcorr_out;
                    }
                    {
                        double zfallcorr_0_in = __state->__6_zfallcorr;
                        double zrho_0_in_0 = __state->__6_zrho[(_for_it_60 - 1)];
                        double tmp_arg_96_out;

                        ///////////////////
                        // Tasklet code (T_l1079_c1079)
                        tmp_arg_96_out = (zrho_0_in_0 * zfallcorr_0_in);
                        ///////////////////

                        __state->__6_tmp_arg_96 = tmp_arg_96_out;
                    }
                    {
                        double tmp_arg_96_0_in = __state->__6_tmp_arg_96;
                        double tmp_call_166_out;

                        ///////////////////
                        // Tasklet code (T_l1079_c1079)
                        tmp_call_166_out = dace::math::sqrt(tmp_arg_96_0_in);
                        ///////////////////

                        __state->__6_tmp_call_166 = tmp_call_166_out;
                    }
                    {
                        double ydecldp_var_47_0_in_rcl_fac1 = v_ydecldp_var_47_rcl_fac1[0];
                        double zpreclr_0_in = __state->__6_zpreclr;
                        double zrho_0_in_0 = __state->__6_zrho[(_for_it_60 - 1)];
                        double tmp_arg_93_out;

                        ///////////////////
                        // Tasklet code (T_l1074_c1074)
                        tmp_arg_93_out = (ydecldp_var_47_0_in_rcl_fac1 / (zrho_0_in_0 * zpreclr_0_in));
                        ///////////////////

                        __state->__6_tmp_arg_93 = tmp_arg_93_out;
                    }
                    {
                        double tmp_arg_93_0_in = __state->__6_tmp_arg_93;
                        double ydecldp_var_47_0_in_rcl_fac2 = v_ydecldp_var_47_rcl_fac2[0];
                        double zlambda_out;

                        ///////////////////
                        // Tasklet code (T_l1074_c1074)
                        zlambda_out = dace::math::pow(tmp_arg_93_0_in, ydecldp_var_47_0_in_rcl_fac2);
                        ///////////////////

                        __state->__6_zlambda = zlambda_out;
                    }
                    {
                        double ydecldp_var_47_0_in_rcl_const3r = v_ydecldp_var_47_rcl_const3r[0];
                        double zlambda_0_in = __state->__6_zlambda;
                        double tmp_call_168_out;

                        ///////////////////
                        // Tasklet code (T_l1079_c1079)
                        tmp_call_168_out = dace::math::pow(zlambda_0_in, ydecldp_var_47_0_in_rcl_const3r);
                        ///////////////////

                        __state->__6_tmp_call_168 = tmp_call_168_out;
                    }
                    {
                        double ydecldp_var_47_0_in_rcl_const4r = v_ydecldp_var_47_rcl_const4r[0];
                        double zlambda_0_in = __state->__6_zlambda;
                        double tmp_call_165_out;

                        ///////////////////
                        // Tasklet code (T_l1079_c1079)
                        tmp_call_165_out = dace::math::pow(zlambda_0_in, ydecldp_var_47_0_in_rcl_const4r);
                        ///////////////////

                        __state->__6_tmp_call_165 = tmp_call_165_out;
                    }
                    {
                        double ztp1_0_in_0 = __state->__6_ztp1[((_for_it_60 + (sym_klon * (_for_it_23 - 1))) - 1)];
                        double oka_out;

                        ///////////////////
                        // Tasklet code (T_l1072_c1072)
                        oka_out = ztp1_0_in_0;
                        ///////////////////

                        __state->__6_oka = oka_out;
                    }
                    {
                        double ztp1_0_in_0 = __state->__6_ztp1[((_for_it_60 + (sym_klon * (_for_it_23 - 1))) - 1)];
                        double tmp_call_162_out;

                        ///////////////////
                        // Tasklet code (T_l1075_c1075)
                        tmp_call_162_out = (dace::math::ipow(ztp1_0_in_0, 3));
                        ///////////////////

                        __state->__6_tmp_call_162 = tmp_call_162_out;
                    }
                    {
                        double ztp1_0_in_0 = __state->__6_ztp1[((_for_it_60 + (sym_klon * (_for_it_23 - 1))) - 1)];
                        double tmp_arg_94_out;

                        ///////////////////
                        // Tasklet code (T_l1076_c1076)
                        tmp_arg_94_out = (ztp1_0_in_0 / 273.0);
                        ///////////////////

                        __state->__6_tmp_arg_94 = tmp_arg_94_out;
                    }
                    {
                        double tmp_arg_94_0_in = __state->__6_tmp_arg_94;
                        double tmp_call_163_out;

                        ///////////////////
                        // Tasklet code (T_l1076_c1076)
                        tmp_call_163_out = dace::math::pow(tmp_arg_94_0_in, 1.5);
                        ///////////////////

                        __state->__6_tmp_call_163 = tmp_call_163_out;
                    }
                    {
                        double tmp_call_163_0_in = __state->__6_tmp_call_163;
                        double ztp1_0_in_0 = __state->__6_ztp1[((_for_it_60 + (sym_klon * (_for_it_23 - 1))) - 1)];
                        double zcorr2_out;

                        ///////////////////
                        // Tasklet code (T_l1076_c1076)
                        zcorr2_out = ((tmp_call_163_0_in * 393.0) / (ztp1_0_in_0 + 120.0));
                        ///////////////////

                        __state->__6_zcorr2 = zcorr2_out;
                    }
                    {
                        double zcorr2_0_in = __state->__6_zcorr2;
                        double tmp_call_167_out;

                        ///////////////////
                        // Tasklet code (T_l1079_c1079)
                        tmp_call_167_out = dace::math::sqrt(zcorr2_0_in);
                        ///////////////////

                        __state->__6_tmp_call_167 = tmp_call_167_out;
                    }
                    {
                        double ztp1_0_in_0 = __state->__6_ztp1[((_for_it_60 + (sym_klon * (_for_it_23 - 1))) - 1)];
                        double tmp_call_164_out;

                        ///////////////////
                        // Tasklet code (T_l1079_c1079)
                        tmp_call_164_out = (dace::math::ipow(ztp1_0_in_0, 2));
                        ///////////////////

                        __state->__6_tmp_call_164 = tmp_call_164_out;
                    }
                    {
                        double oka_0_in = __state->__6_oka;
                        double oka_1_in = __state->__6_oka;
                        double ydcst_0_in_rtt = v_ydcst_rtt[0];
                        double ydthf_0_in_r3les = v_ydthf_r3les[0];
                        double ydthf_1_in_r4les = v_ydthf_r4les[0];
                        double tmp_arg_92_out;

                        ///////////////////
                        // Tasklet code (T_l1073_c1073)
                        tmp_arg_92_out = ((ydthf_0_in_r3les * (oka_0_in - ydcst_0_in_rtt)) / (oka_1_in - ydthf_1_in_r4les));
                        ///////////////////

                        __state->__6_tmp_arg_92 = tmp_arg_92_out;
                    }
                    {
                        double tmp_arg_92_0_in = __state->__6_tmp_arg_92;
                        double tmp_call_161_out;

                        ///////////////////
                        // Tasklet code (T_l1073_c1073)
                        tmp_call_161_out = exp(tmp_arg_92_0_in);
                        ///////////////////

                        __state->__6_tmp_call_161 = tmp_call_161_out;
                    }
                    {
                        double tmp_call_161_0_in = __state->__6_tmp_call_161;
                        double ydcst_0_in_rv = v_ydcst_rv[0];
                        double ydcst_1_in_rd = v_ydcst_rd[0];
                        double ydthf_0_in_r2es = v_ydthf_r2es[0];
                        double zesatliq_out;

                        ///////////////////
                        // Tasklet code (T_l1073_c1073)
                        zesatliq_out = (((ydcst_0_in_rv / ydcst_1_in_rd) * ydthf_0_in_r2es) * tmp_call_161_0_in);
                        ///////////////////

                        __state->__6_zesatliq = zesatliq_out;
                    }
                    {
                        double pap_var_17_0_in_0 = pap_var_17[((_for_it_60 + (sym_klon * (_for_it_23 - 1))) - 1)];
                        double tmp_call_162_0_in = __state->__6_tmp_call_162;
                        double ydecldp_var_47_0_in_rcl_cdenom1 = v_ydecldp_var_47_rcl_cdenom1[0];
                        double ydecldp_var_47_1_in_rcl_cdenom2 = v_ydecldp_var_47_rcl_cdenom2[0];
                        double ydecldp_var_47_2_in_rcl_cdenom3 = v_ydecldp_var_47_rcl_cdenom3[0];
                        double zesatliq_0_in = __state->__6_zesatliq;
                        double zesatliq_1_in = __state->__6_zesatliq;
                        double ztp1_0_in_0 = __state->__6_ztp1[((_for_it_60 + (sym_klon * (_for_it_23 - 1))) - 1)];
                        double zevap_denom_out;

                        ///////////////////
                        // Tasklet code (T_l1075_c1075)
                        zevap_denom_out =
                            (((ydecldp_var_47_0_in_rcl_cdenom1 * zesatliq_0_in) - ((ydecldp_var_47_1_in_rcl_cdenom2 * ztp1_0_in_0) * zesatliq_1_in)) +
                             ((ydecldp_var_47_2_in_rcl_cdenom3 * tmp_call_162_0_in) * pap_var_17_0_in_0));
                        ///////////////////

                        __state->__6_zevap_denom = zevap_denom_out;
                    }
                    {
                        double tmp_call_164_0_in = __state->__6_tmp_call_164;
                        double tmp_call_165_0_in = __state->__6_tmp_call_165;
                        double tmp_call_166_0_in = __state->__6_tmp_call_166;
                        double tmp_call_167_0_in = __state->__6_tmp_call_167;
                        double tmp_call_168_0_in = __state->__6_tmp_call_168;
                        double ydecldp_var_47_0_in_rcl_const1r = v_ydecldp_var_47_rcl_const1r[0];
                        double ydecldp_var_47_1_in_rcl_const2r = v_ydecldp_var_47_rcl_const2r[0];
                        double zcorr2_0_in = __state->__6_zcorr2;
                        double zesatliq_0_in = __state->__6_zesatliq;
                        double zevap_denom_0_in = __state->__6_zevap_denom;
                        double zqsliq_0_in_0 = __state->__6_zqsliq[((_for_it_60 + (sym_klon * (_for_it_23 - 1))) - 1)];
                        double zbeta_out;

                        ///////////////////
                        // Tasklet code (T_l1079_c1079)
                        zbeta_out =
                            ((((((0.5 / zqsliq_0_in_0) * tmp_call_164_0_in) * zesatliq_0_in) * ydecldp_var_47_0_in_rcl_const1r) * (zcorr2_0_in / zevap_denom_0_in)) *
                             ((0.78 / tmp_call_165_0_in) + ((ydecldp_var_47_1_in_rcl_const2r * tmp_call_166_0_in) / (tmp_call_167_0_in * tmp_call_168_0_in))));
                        ///////////////////

                        __state->__6_zbeta = zbeta_out;
                    }
                    {
                        double zqe_0_in = __state->__6_zqe;
                        double zqsliq_0_in_0 = __state->__6_zqsliq[((_for_it_60 + (sym_klon * (_for_it_23 - 1))) - 1)];
                        double zzrh_0_in = __state->__6_zzrh;
                        double tmp_arg_95_out;

                        ///////////////////
                        // Tasklet code (T_l1078_c1078)
                        tmp_arg_95_out = ((zzrh_0_in * zqsliq_0_in_0) - zqe_0_in);
                        ///////////////////

                        __state->__6_tmp_arg_95 = tmp_arg_95_out;
                    }
                    {
                        double tmp_arg_95_0_in = __state->__6_tmp_arg_95;
                        double zsubsat_out;

                        ///////////////////
                        // Tasklet code (T_l1078_c1078)
                        zsubsat_out = max(tmp_arg_95_0_in, 0.0);
                        ///////////////////

                        __state->__6_zsubsat = zsubsat_out;
                    }
                    {
                        double ptsphy_var_5_0_in = ptsphy_var_5[0];
                        double zbeta_0_in = __state->__6_zbeta;
                        double zdenom_out;

                        ///////////////////
                        // Tasklet code (T_l1080_c1080)
                        zdenom_out = (1.0 + (zbeta_0_in * ptsphy_var_5_0_in));
                        ///////////////////

                        __state->__6_zdenom = zdenom_out;
                    }
                    {
                        double ptsphy_var_5_0_in = ptsphy_var_5[0];
                        double zbeta_0_in = __state->__6_zbeta;
                        double zcovpclr_0_in_0 = __state->__6_zcovpclr[(_for_it_60 - 1)];
                        double zdenom_0_in = __state->__6_zdenom;
                        double zsubsat_0_in = __state->__6_zsubsat;
                        double zdpevap_out;

                        ///////////////////
                        // Tasklet code (T_l1081_c1081)
                        zdpevap_out = ((((zcovpclr_0_in_0 * zbeta_0_in) * ptsphy_var_5_0_in) * zsubsat_0_in) / zdenom_0_in);
                        ///////////////////

                        __state->__6_zdpevap = zdpevap_out;
                    }
                    {
                        double zdpevap_0_in = __state->__6_zdpevap;
                        double zqxfg_0_in_0 = __state->__6_zqxfg[((_for_it_60 + (2 * sym_klon)) - 1)];
                        double zevap_out;

                        ///////////////////
                        // Tasklet code (T_l1082_c1082)
                        zevap_out = min(zdpevap_0_in, zqxfg_0_in_0);
                        ///////////////////

                        __state->__6_zevap = zevap_out;
                    }
                    {
                        double zevap_0_in = __state->__6_zevap;
                        double zsolqa_0_in_0 = __state->__6_zsolqa[((_for_it_60 + (14 * sym_klon)) - 1)];
                        double zsolqa_out_0;

                        ///////////////////
                        // Tasklet code (T_l1083_c1083)
                        zsolqa_out_0 = (zsolqa_0_in_0 + zevap_0_in);
                        ///////////////////

                        __state->__6_zsolqa[((_for_it_60 + (14 * sym_klon)) - 1)] = zsolqa_out_0;
                    }
                    {
                        double zevap_0_in = __state->__6_zevap;
                        double zsolqa_0_in_0 = __state->__6_zsolqa[((_for_it_60 + (22 * sym_klon)) - 1)];
                        double zsolqa_out_0;

                        ///////////////////
                        // Tasklet code (T_l1084_c1084)
                        zsolqa_out_0 = (zsolqa_0_in_0 - zevap_0_in);
                        ///////////////////

                        __state->__6_zsolqa[((_for_it_60 + (22 * sym_klon)) - 1)] = zsolqa_out_0;
                    }
                    {
                        double za_0_in_0 = __state->__6_za[((_for_it_60 + (sym_klon * (_for_it_23 - 1))) - 1)];
                        double zcovptot_0_in_0 = __state->__6_zcovptot[(_for_it_60 - 1)];
                        double zevap_0_in = __state->__6_zevap;
                        double zqxfg_0_in_0 = __state->__6_zqxfg[((_for_it_60 + (2 * sym_klon)) - 1)];
                        double tmp_arg_97_out;

                        ///////////////////
                        // Tasklet code (T_l1085_c1085)
                        tmp_arg_97_out = (((zcovptot_0_in_0 - za_0_in_0) * zevap_0_in) / zqxfg_0_in_0);
                        ///////////////////

                        __state->__6_tmp_arg_97 = tmp_arg_97_out;
                    }
                    {
                        double tmp_arg_97_0_in = __state->__6_tmp_arg_97;
                        double tmp_call_170_out;

                        ///////////////////
                        // Tasklet code (T_l1085_c1085)
                        tmp_call_170_out = max(0.0, tmp_arg_97_0_in);
                        ///////////////////

                        __state->__6_tmp_call_170 = tmp_call_170_out;
                    }
                    {
                        double tmp_call_170_0_in = __state->__6_tmp_call_170;
                        double zcovptot_0_in_0 = __state->__6_zcovptot[(_for_it_60 - 1)];
                        double tmp_arg_98_out;

                        ///////////////////
                        // Tasklet code (T_l1085_c1085)
                        tmp_arg_98_out = (zcovptot_0_in_0 - tmp_call_170_0_in);
                        ///////////////////

                        __state->__6_tmp_arg_98 = tmp_arg_98_out;
                    }
                    {
                        double tmp_arg_98_0_in = __state->__6_tmp_arg_98;
                        double ydecldp_var_47_0_in_rcovpmin = v_ydecldp_var_47_rcovpmin[0];
                        double tmp_call_169_out;

                        ///////////////////
                        // Tasklet code (T_l1085_c1085)
                        tmp_call_169_out = max(ydecldp_var_47_0_in_rcovpmin, tmp_arg_98_0_in);
                        ///////////////////

                        __state->__6_tmp_call_169 = tmp_call_169_out;
                    }
                    {
                        double tmp_call_169_0_in = __state->__6_tmp_call_169;
                        double zcovptot_out_0;

                        ///////////////////
                        // Tasklet code (T_l1085_c1085)
                        zcovptot_out_0 = tmp_call_169_0_in;
                        ///////////////////

                        __state->__6_zcovptot[(_for_it_60 - 1)] = zcovptot_out_0;
                    }
                }
                {
                    {
                        double zevap_0_in = __state->__6_zevap;
                        double zqxfg_0_in_0 = __state->__6_zqxfg[((_for_it_60 + (2 * sym_klon)) - 1)];
                        double zqxfg_out_0;

                        ///////////////////
                        // Tasklet code (T_l1086_c1086)
                        zqxfg_out_0 = (zqxfg_0_in_0 - zevap_0_in);
                        ///////////////////

                        __state->__6_zqxfg[((_for_it_60 + (2 * sym_klon)) - 1)] = zqxfg_out_0;
                    }
                }
            }
        }
        for (_for_it_61 = 1; (_for_it_61 <= icend); _for_it_61 = (_for_it_61 + 1)) {
            {
                {
                    double za_0_in_0 = __state->__6_za[((_for_it_61 + (sym_klon * (_for_it_23 - 1))) - 1)];
                    double tmp_arg_99_out;

                    ///////////////////
                    // Tasklet code (T_l1090_c1090)
                    tmp_arg_99_out = (1.0 - za_0_in_0);
                    ///////////////////

                    __state->__6_tmp_arg_99 = tmp_arg_99_out;
                }
                {
                    double tmp_arg_99_0_in = __state->__6_tmp_arg_99;
                    double zepsec_0_in = __state->__6_zepsec;
                    double tmp_call_171_out;

                    ///////////////////
                    // Tasklet code (T_l1090_c1090)
                    tmp_call_171_out = max(zepsec_0_in, tmp_arg_99_0_in);
                    ///////////////////

                    __state->__6_tmp_call_171 = tmp_call_171_out;
                }
                {
                    double tmp_call_171_0_in = __state->__6_tmp_call_171;
                    double ydecldp_var_47_0_in_rprecrhmax = v_ydecldp_var_47_rprecrhmax[0];
                    double ydecldp_var_47_1_in_rprecrhmax = v_ydecldp_var_47_rprecrhmax[0];
                    double zcovpmax_0_in_0 = __state->__6_zcovpmax[(_for_it_61 - 1)];
                    double zzrh_out;

                    ///////////////////
                    // Tasklet code (T_l1090_c1090)
                    zzrh_out = (ydecldp_var_47_0_in_rprecrhmax + (((1.0 - ydecldp_var_47_1_in_rprecrhmax) * zcovpmax_0_in_0) / tmp_call_171_0_in));
                    ///////////////////

                    __state->__6_zzrh = zzrh_out;
                }
            }
            {
                {
                    double ydecldp_var_47_0_in_rprecrhmax = v_ydecldp_var_47_rprecrhmax[0];
                    double zzrh_0_in = __state->__6_zzrh;
                    double tmp_call_172_out;

                    ///////////////////
                    // Tasklet code (T_l1091_c1091)
                    tmp_call_172_out = max(zzrh_0_in, ydecldp_var_47_0_in_rprecrhmax);
                    ///////////////////

                    __state->__6_tmp_call_172 = tmp_call_172_out;
                }
                {
                    double tmp_call_172_0_in = __state->__6_tmp_call_172;
                    double zzrh_out;

                    ///////////////////
                    // Tasklet code (T_l1091_c1091)
                    zzrh_out = min(tmp_call_172_0_in, 1.0);
                    ///////////////////

                    __state->__6_zzrh = zzrh_out;
                }
                {
                    double za_0_in_0 = __state->__6_za[((_for_it_61 + (sym_klon * (_for_it_23 - 1))) - 1)];
                    double tmp_arg_100_out;

                    ///////////////////
                    // Tasklet code (T_l1092_c1092)
                    tmp_arg_100_out = (1.0 - za_0_in_0);
                    ///////////////////

                    __state->__6_tmp_arg_100 = tmp_arg_100_out;
                }
                {
                    double tmp_arg_100_0_in = __state->__6_tmp_arg_100;
                    double zepsec_0_in = __state->__6_zepsec;
                    double tmp_call_173_out;

                    ///////////////////
                    // Tasklet code (T_l1092_c1092)
                    tmp_call_173_out = max(zepsec_0_in, tmp_arg_100_0_in);
                    ///////////////////

                    __state->__6_tmp_call_173 = tmp_call_173_out;
                }
                {
                    double tmp_call_173_0_in = __state->__6_tmp_call_173;
                    double za_0_in_0 = __state->__6_za[((_for_it_61 + (sym_klon * (_for_it_23 - 1))) - 1)];
                    double zqsice_0_in_0 = __state->__6_zqsice[((_for_it_61 + (sym_klon * (_for_it_23 - 1))) - 1)];
                    double zqx_0_in_0 = __state->__6_zqx[(((_for_it_61 + ((4 * sym_klev) * sym_klon)) + (sym_klon * (_for_it_23 - 1))) - 1)];
                    double zqe_out;

                    ///////////////////
                    // Tasklet code (T_l1092_c1092)
                    zqe_out = ((zqx_0_in_0 - (za_0_in_0 * zqsice_0_in_0)) / tmp_call_173_0_in);
                    ///////////////////

                    __state->__6_zqe = zqe_out;
                }
                {
                    double zqe_0_in = __state->__6_zqe;
                    double zqsice_0_in_0 = __state->__6_zqsice[((_for_it_61 + (sym_klon * (_for_it_23 - 1))) - 1)];
                    double tmp_call_174_out;

                    ///////////////////
                    // Tasklet code (T_l1093_c1093)
                    tmp_call_174_out = min(zqe_0_in, zqsice_0_in_0);
                    ///////////////////

                    __state->__6_tmp_call_174 = tmp_call_174_out;
                }
                {
                    double tmp_call_174_0_in = __state->__6_tmp_call_174;
                    double zqe_out;

                    ///////////////////
                    // Tasklet code (T_l1093_c1093)
                    zqe_out = max(0.0, tmp_call_174_0_in);
                    ///////////////////

                    __state->__6_zqe = zqe_out;
                }
                {
                    double zcovpclr_0_in_0 = __state->__6_zcovpclr[(_for_it_61 - 1)];
                    double zqe_0_in = __state->__6_zqe;
                    double zqsice_0_in_0 = __state->__6_zqsice[((_for_it_61 + (sym_klon * (_for_it_23 - 1))) - 1)];
                    double zqxfg_0_in_0 = __state->__6_zqxfg[((_for_it_61 + (3 * sym_klon)) - 1)];
                    double zzrh_0_in = __state->__6_zzrh;
                    int llo1_out;

                    ///////////////////
                    // Tasklet code (T_l1094_c1094)
                    llo1_out = (((zcovpclr_0_in_0 > 1e-14) && (zqxfg_0_in_0 > 1e-14)) && (zqe_0_in < (zzrh_0_in * zqsice_0_in_0)));
                    ///////////////////

                    __state->__6_llo1 = llo1_out;
                }
            }
            _if_cond_72 = __state->__6_llo1;
            if ((_if_cond_72 == 1)) {
                {
                    {
                        double zcovptot_0_in_0 = __state->__6_zcovptot[(_for_it_61 - 1)];
                        double zdtgdp_0_in_0 = __state->__6_zdtgdp[(_for_it_61 - 1)];
                        double tmp_arg_101_out;

                        ///////////////////
                        // Tasklet code (T_l1096_c1096)
                        tmp_arg_101_out = (zcovptot_0_in_0 * zdtgdp_0_in_0);
                        ///////////////////

                        __state->__6_tmp_arg_101 = tmp_arg_101_out;
                    }
                    {
                        double tmp_arg_101_0_in = __state->__6_tmp_arg_101;
                        double tmp_call_182_out;

                        ///////////////////
                        // Tasklet code (T_l1096_c1096)
                        tmp_call_182_out = abs(tmp_arg_101_0_in);
                        ///////////////////

                        __state->__6_tmp_call_182 = tmp_call_182_out;
                    }
                    {
                        double tmp_call_182_0_in = __state->__6_tmp_call_182;
                        double zepsilon_0_in = __state->__6_zepsilon;
                        double tmp_call_180_out;

                        ///////////////////
                        // Tasklet code (T_l1096_c1096)
                        tmp_call_180_out = max(tmp_call_182_0_in, zepsilon_0_in);
                        ///////////////////

                        __state->__6_tmp_call_180 = tmp_call_180_out;
                    }
                }
                if ((!((__state->__6_zcovptot[(_for_it_61 - 1)] * __state->__6_zdtgdp[(_for_it_61 - 1)]) >= 0.0))) {
                    {
                        {
                            double tmp_call_180_0_in = __state->__6_tmp_call_180;
                            double tmp_call_1_out;

                            ///////////////////
                            // Tasklet code (T_l1096_c1096)
                            tmp_call_1_out = abs(tmp_call_180_0_in);
                            ///////////////////

                            __state->__6_tmp_call_1 = tmp_call_1_out;
                        }
                        {
                            double tmp_call_1_0_in = __state->__6_tmp_call_1;
                            double tmp_call_175_out;

                            ///////////////////
                            // Tasklet code (T_l1096_c1096)
                            tmp_call_175_out = (-tmp_call_1_0_in);
                            ///////////////////

                            __state->__6_tmp_call_175 = tmp_call_175_out;
                        }
                    }
                } else if (((__state->__6_zcovptot[(_for_it_61 - 1)] * __state->__6_zdtgdp[(_for_it_61 - 1)]) >= 0.0)) {
                    {
                        {
                            double tmp_call_180_0_in = __state->__6_tmp_call_180;
                            double tmp_call_175_out;

                            ///////////////////
                            // Tasklet code (T_l1096_c1096)
                            tmp_call_175_out = abs(tmp_call_180_0_in);
                            ///////////////////

                            __state->__6_tmp_call_175 = tmp_call_175_out;
                        }
                    }
                }
                tmp_index_1570 = ((klev[0] + 1) - 1);
                {
                    double* v_ydecldp_var_47_rvrfactor;
                    v_ydecldp_var_47_rvrfactor = (double*)(&(ydecldp_var_47->rvrfactor));
                    double* v_ydecldp_var_47_rpecons;
                    v_ydecldp_var_47_rpecons = (double*)(&(ydecldp_var_47->rpecons));

                    {
                        double tmp_call_175_0_in = __state->__6_tmp_call_175;
                        double zcovpclr_0_in_0 = __state->__6_zcovpclr[(_for_it_61 - 1)];
                        double zqxfg_0_in_0 = __state->__6_zqxfg[((_for_it_61 + (3 * sym_klon)) - 1)];
                        double zpreclr_out;

                        ///////////////////
                        // Tasklet code (T_l1096_c1096)
                        zpreclr_out = ((zqxfg_0_in_0 * zcovpclr_0_in_0) / tmp_call_175_0_in);
                        ///////////////////

                        __state->__6_zpreclr = zpreclr_out;
                    }
                    {
                        double zcovpclr_0_in_0 = __state->__6_zcovpclr[(_for_it_61 - 1)];
                        double zepsec_0_in = __state->__6_zepsec;
                        double tmp_call_177_out;

                        ///////////////////
                        // Tasklet code (T_l1097_c1097)
                        tmp_call_177_out = max(zcovpclr_0_in_0, zepsec_0_in);
                        ///////////////////

                        __state->__6_tmp_call_177 = tmp_call_177_out;
                    }
                    {
                        double pap_var_17_0_in_0 = pap_var_17[((_for_it_61 + (sym_klon * (_for_it_23 - 1))) - 1)];
                        double paph_var_18_0_in_0 = paph_var_18[((_for_it_61 + (sym_klon * tmp_index_1570)) - 1)];
                        double tmp_arg_102_out;

                        ///////////////////
                        // Tasklet code (T_l1097_c1097)
                        tmp_arg_102_out = (pap_var_17_0_in_0 / paph_var_18_0_in_0);
                        ///////////////////

                        __state->__6_tmp_arg_102 = tmp_arg_102_out;
                    }
                    {
                        double tmp_arg_102_0_in = __state->__6_tmp_arg_102;
                        double tmp_call_176_out;

                        ///////////////////
                        // Tasklet code (T_l1097_c1097)
                        tmp_call_176_out = sqrt(tmp_arg_102_0_in);
                        ///////////////////

                        __state->__6_tmp_call_176 = tmp_call_176_out;
                    }
                    {
                        double tmp_call_176_0_in = __state->__6_tmp_call_176;
                        double tmp_call_177_0_in = __state->__6_tmp_call_177;
                        double ydecldp_var_47_0_in_rvrfactor = v_ydecldp_var_47_rvrfactor[0];
                        double zpreclr_0_in = __state->__6_zpreclr;
                        double zbeta1_out;

                        ///////////////////
                        // Tasklet code (T_l1097_c1097)
                        zbeta1_out = (((tmp_call_176_0_in / ydecldp_var_47_0_in_rvrfactor) * zpreclr_0_in) / tmp_call_177_0_in);
                        ///////////////////

                        __state->__6_zbeta1 = zbeta1_out;
                    }
                    {
                        double zbeta1_0_in = __state->__6_zbeta1;
                        double tmp_arg_103_out;

                        ///////////////////
                        // Tasklet code (T_l1098_c1098)
                        tmp_arg_103_out = zbeta1_0_in;
                        ///////////////////

                        __state->__6_tmp_arg_103 = tmp_arg_103_out;
                    }
                    {
                        double tmp_arg_103_0_in = __state->__6_tmp_arg_103;
                        double tmp_call_178_out;

                        ///////////////////
                        // Tasklet code (T_l1098_c1098)
                        tmp_call_178_out = dace::math::pow(tmp_arg_103_0_in, 0.5777);
                        ///////////////////

                        __state->__6_tmp_call_178 = tmp_call_178_out;
                    }
                    {
                        double tmp_call_178_0_in = __state->__6_tmp_call_178;
                        double ydcst_0_in_rg = v_ydcst_rg[0];
                        double ydecldp_var_47_0_in_rpecons = v_ydecldp_var_47_rpecons[0];
                        double zbeta_out;

                        ///////////////////
                        // Tasklet code (T_l1098_c1098)
                        zbeta_out = ((ydcst_0_in_rg * ydecldp_var_47_0_in_rpecons) * tmp_call_178_0_in);
                        ///////////////////

                        __state->__6_zbeta = zbeta_out;
                    }
                    {
                        double ptsphy_var_5_0_in = ptsphy_var_5[0];
                        double zbeta_0_in = __state->__6_zbeta;
                        double zcorqsice_0_in_0 = __state->__6_zcorqsice[(_for_it_61 - 1)];
                        double zdenom_out;

                        ///////////////////
                        // Tasklet code (T_l1099_c1099)
                        zdenom_out = (1.0 + ((zbeta_0_in * ptsphy_var_5_0_in) * zcorqsice_0_in_0));
                        ///////////////////

                        __state->__6_zdenom = zdenom_out;
                    }
                    {
                        double zbeta_0_in = __state->__6_zbeta;
                        double zcovpclr_0_in_0 = __state->__6_zcovpclr[(_for_it_61 - 1)];
                        double zdenom_0_in = __state->__6_zdenom;
                        double zdp_0_in_0 = __state->__6_zdp[(_for_it_61 - 1)];
                        double zqe_0_in = __state->__6_zqe;
                        double zqsice_0_in_0 = __state->__6_zqsice[((_for_it_61 + (sym_klon * (_for_it_23 - 1))) - 1)];
                        double zrg_r_0_in = __state->__6_zrg_r;
                        double zdpr_out;

                        ///////////////////
                        // Tasklet code (T_l1100_c1100)
                        zdpr_out = (((((zcovpclr_0_in_0 * zbeta_0_in) * (zqsice_0_in_0 - zqe_0_in)) / zdenom_0_in) * zdp_0_in_0) * zrg_r_0_in);
                        ///////////////////

                        __state->__6_zdpr = zdpr_out;
                    }
                    {
                        double zdpr_0_in = __state->__6_zdpr;
                        double zdtgdp_0_in_0 = __state->__6_zdtgdp[(_for_it_61 - 1)];
                        double zdpevap_out;

                        ///////////////////
                        // Tasklet code (T_l1101_c1101)
                        zdpevap_out = (zdpr_0_in * zdtgdp_0_in_0);
                        ///////////////////

                        __state->__6_zdpevap = zdpevap_out;
                    }
                    {
                        double zdpevap_0_in = __state->__6_zdpevap;
                        double zqxfg_0_in_0 = __state->__6_zqxfg[((_for_it_61 + (3 * sym_klon)) - 1)];
                        double zevap_out;

                        ///////////////////
                        // Tasklet code (T_l1102_c1102)
                        zevap_out = min(zdpevap_0_in, zqxfg_0_in_0);
                        ///////////////////

                        __state->__6_zevap = zevap_out;
                    }
                    {
                        double zevap_0_in = __state->__6_zevap;
                        double zsolqa_0_in_0 = __state->__6_zsolqa[((_for_it_61 + (19 * sym_klon)) - 1)];
                        double zsolqa_out_0;

                        ///////////////////
                        // Tasklet code (T_l1103_c1103)
                        zsolqa_out_0 = (zsolqa_0_in_0 + zevap_0_in);
                        ///////////////////

                        __state->__6_zsolqa[((_for_it_61 + (19 * sym_klon)) - 1)] = zsolqa_out_0;
                    }
                    {
                        double zevap_0_in = __state->__6_zevap;
                        double zsolqa_0_in_0 = __state->__6_zsolqa[((_for_it_61 + (23 * sym_klon)) - 1)];
                        double zsolqa_out_0;

                        ///////////////////
                        // Tasklet code (T_l1104_c1104)
                        zsolqa_out_0 = (zsolqa_0_in_0 - zevap_0_in);
                        ///////////////////

                        __state->__6_zsolqa[((_for_it_61 + (23 * sym_klon)) - 1)] = zsolqa_out_0;
                    }
                    {
                        double za_0_in_0 = __state->__6_za[((_for_it_61 + (sym_klon * (_for_it_23 - 1))) - 1)];
                        double zcovptot_0_in_0 = __state->__6_zcovptot[(_for_it_61 - 1)];
                        double zevap_0_in = __state->__6_zevap;
                        double zqxfg_0_in_0 = __state->__6_zqxfg[((_for_it_61 + (3 * sym_klon)) - 1)];
                        double tmp_arg_104_out;

                        ///////////////////
                        // Tasklet code (T_l1105_c1105)
                        tmp_arg_104_out = (((zcovptot_0_in_0 - za_0_in_0) * zevap_0_in) / zqxfg_0_in_0);
                        ///////////////////

                        __state->__6_tmp_arg_104 = tmp_arg_104_out;
                    }
                    {
                        double tmp_arg_104_0_in = __state->__6_tmp_arg_104;
                        double tmp_call_181_out;

                        ///////////////////
                        // Tasklet code (T_l1105_c1105)
                        tmp_call_181_out = max(0.0, tmp_arg_104_0_in);
                        ///////////////////

                        __state->__6_tmp_call_181 = tmp_call_181_out;
                    }
                    {
                        double tmp_call_181_0_in = __state->__6_tmp_call_181;
                        double zcovptot_0_in_0 = __state->__6_zcovptot[(_for_it_61 - 1)];
                        double tmp_arg_105_out;

                        ///////////////////
                        // Tasklet code (T_l1105_c1105)
                        tmp_arg_105_out = (zcovptot_0_in_0 - tmp_call_181_0_in);
                        ///////////////////

                        __state->__6_tmp_arg_105 = tmp_arg_105_out;
                    }
                    {
                        double tmp_arg_105_0_in = __state->__6_tmp_arg_105;
                        double ydecldp_var_47_0_in_rcovpmin = v_ydecldp_var_47_rcovpmin[0];
                        double tmp_call_179_out;

                        ///////////////////
                        // Tasklet code (T_l1105_c1105)
                        tmp_call_179_out = max(ydecldp_var_47_0_in_rcovpmin, tmp_arg_105_0_in);
                        ///////////////////

                        __state->__6_tmp_call_179 = tmp_call_179_out;
                    }
                    {
                        double tmp_call_179_0_in = __state->__6_tmp_call_179;
                        double zcovptot_out_0;

                        ///////////////////
                        // Tasklet code (T_l1105_c1105)
                        zcovptot_out_0 = tmp_call_179_0_in;
                        ///////////////////

                        __state->__6_zcovptot[(_for_it_61 - 1)] = zcovptot_out_0;
                    }
                }
                {
                    {
                        double zevap_0_in = __state->__6_zevap;
                        double zqxfg_0_in_0 = __state->__6_zqxfg[((_for_it_61 + (3 * sym_klon)) - 1)];
                        double zqxfg_out_0;

                        ///////////////////
                        // Tasklet code (T_l1106_c1106)
                        zqxfg_out_0 = (zqxfg_0_in_0 - zevap_0_in);
                        ///////////////////

                        __state->__6_zqxfg[((_for_it_61 + (3 * sym_klon)) - 1)] = zqxfg_out_0;
                    }
                }
            }
        }
        for (_for_it_62 = 1; (_for_it_62 <= 5); _for_it_62 = (_for_it_62 + 1)) {
            _if_cond_73 = __state->__6_llfall[(_for_it_62 - 1)];
            if ((_if_cond_73 == 1)) {
                {
                    {
#pragma omp parallel for
                        for (auto _for_it_63 = 1; _for_it_63 < (icend + 1); _for_it_63 += 1) {
                            loop_body_199_0_0(
                                __state, ydecldp_var_47, &__state->__6_zqxfg[((_for_it_63 + (sym_klon * (_for_it_62 - 1))) - 1)], &__state->__6_zsolqa[(_for_it_63 - 1)], _for_it_62, sym_klon);
                        }
                    }
                }
            }
        }
        {
            {
#pragma omp parallel for
                for (auto _for_it_64 = 1; _for_it_64 < (icend + 1); _for_it_64 += 1) {
                    loop_body_50_6_0(
                        __state, ydecldp_var_47, &__state->__6_za[((_for_it_64 + (sym_klon * (_for_it_23 - 1))) - 1)], &__state->__6_zaorig[((_for_it_64 + (sym_klon * (_for_it_23 - 1))) - 1)],
                        &__state->__6_zsolab[(_for_it_64 - 1)], &__state->__6_zsolac[(_for_it_64 - 1)], &__state->__6_zanewm1[(_for_it_64 - 1)], &__state->__6_zda[(_for_it_64 - 1)], sym_klon);
                }
            }
            {
#pragma omp parallel for
                for (auto _for_it_65 = 1; _for_it_65 < 6; _for_it_65 += 1) {
                    loop_body_50_6_10(__state, &__state->__6_llindex3[((5 * sym_klon) * (_for_it_65 - 1))], &__state->__6_zsinksum[(sym_klon * (_for_it_65 - 1))], icend, sym_klon);
                }
            }
            {
#pragma omp parallel for
                for (auto _for_it_69 = 1; _for_it_69 < 6; _for_it_69 += 1) {
                    loop_body_50_6_15(__state, &__state->__6_zsolqa[0], &__state->__6_zsinksum[(sym_klon * (_for_it_69 - 1))], _for_it_69, icend, sym_klon);
                }
            }
            {
#pragma omp parallel for
                for (auto _for_it_72 = 1; _for_it_72 < 6; _for_it_72 += 1) {
                    loop_body_50_6_20(
                        __state, __state->__6_zepsec, &__state->__6_zqx[(((sym_klev * sym_klon) * (_for_it_72 - 1)) + (sym_klon * (_for_it_23 - 1)))],
                        &__state->__6_zsinksum[(sym_klon * (_for_it_72 - 1))], &__state->__6_zratio[(sym_klon * (_for_it_72 - 1))], icend, sym_klev, sym_klon);
                }
            }
            {
#pragma omp parallel for
                for (auto _for_it_74 = 1; _for_it_74 < 6; _for_it_74 += 1) {
                    loop_body_50_6_26(__state, &__state->__6_iorder[(sym_klon * (_for_it_74 - 1))], icend, sym_klon);
                }
            }
            {
#pragma omp parallel for
                for (auto _for_it_76 = 1; _for_it_76 < 6; _for_it_76 += 1) {
                    loop_body_50_6_30(__state, &__state->__6_llindex1[(sym_klon * (_for_it_76 - 1))], icend, sym_klon);
                }
            }
        }
        for (_for_it_78 = 1; (_for_it_78 <= 5); _for_it_78 = (_for_it_78 + 1)) {
            {
                {
#pragma omp parallel for
                    for (auto _for_it_79 = 1; _for_it_79 < (icend + 1); _for_it_79 += 1) {
                        loop_body_223_0_0(__state, &__state->__6_zmin[(_for_it_79 - 1)]);
                    }
                }
                {
#pragma omp parallel for
                    for (auto _for_it_81 = 1; _for_it_81 < (icend + 1); _for_it_81 += 1) {
                        nested_single_state_body_223_0_10(
                            __state, &__state->__6_llindex1[0], &__state->__6_zratio[0], &__state->__6_iorder[((_for_it_81 + (sym_klon * (_for_it_78 - 1))) - 1)], &__state->__6_zmin[(_for_it_81 - 1)],
                            _for_it_81, sym_klon);
                    }
                }
                {
#pragma omp parallel for
                    for (auto _for_it_82 = 1; _for_it_82 < (icend + 1); _for_it_82 += 1) {
                        loop_body_223_0_11(__state, &__state->__6_iorder[((_for_it_82 + (sym_klon * (_for_it_78 - 1))) - 1)], &__state->__6_llindex1[0], _for_it_82, sym_klon);
                    }
                }
            }
        }
        {
            {
#pragma omp parallel for
                for (auto _for_it_83 = 1; _for_it_83 < 6; _for_it_83 += 1) {
                    loop_body_50_8_0(__state, &__state->__6_zsinksum[(sym_klon * (_for_it_83 - 1))], icend, sym_klon);
                }
            }
        }
        for (_for_it_85 = 1; (_for_it_85 <= 5); _for_it_85 = (_for_it_85 + 1)) {
            {
                {
#pragma omp parallel for
                    for (auto _for_it_86 = 1; _for_it_86 < (icend + 1); _for_it_86 += 1) {
                        loop_body_214_0_0(
                            __state, &__state->__6_iorder[((_for_it_86 + (sym_klon * (_for_it_85 - 1))) - 1)], &__state->__6_zsolqa[0], &__state->__6_llindex3[0], &__state->__6_zsinksum[0],
                            _for_it_86, sym_klon);
                    }
                }
                {
#pragma omp parallel for
                    for (auto _for_it_88 = 1; _for_it_88 < (icend + 1); _for_it_88 += 1) {
                        loop_body_214_0_8(
                            __state, &__state->__6_iorder[((_for_it_88 + (sym_klon * (_for_it_85 - 1))) - 1)], __state->__6_zepsec, &__state->__6_zqx[0], &__state->__6_zsinksum[0],
                            &__state->__6_zratio[0], _for_it_23, _for_it_88, sym_klev, sym_klon);
                    }
                }
                {
#pragma omp parallel for
                    for (auto _for_it_89 = 1; _for_it_89 < (icend + 1); _for_it_89 += 1) {
                        loop_body_214_0_14(
                            __state, &__state->__6_iorder[((_for_it_89 + (sym_klon * (_for_it_85 - 1))) - 1)], &__state->__6_llindex3[0], &__state->__6_zratio[0],
                            &__state->__6_zsolqa[(_for_it_89 - 1)], _for_it_89, sym_klon);
                    }
                }
            }
        }
        {
            {
#pragma omp parallel for
                for (auto _for_it_91 = 1; _for_it_91 < 6; _for_it_91 += 1) {
                    loop_body_50_9_0(
                        __state, &__state->__6_zfallsink[(sym_klon * (_for_it_91 - 1))], &__state->__6_zsolqb[0], &__state->__6_zqlhs[((5 * sym_klon) * (_for_it_91 - 1))], _for_it_91, icend,
                        sym_klon);
                }
            }
            {
#pragma omp parallel for
                for (auto _for_it_96 = 1; _for_it_96 < 6; _for_it_96 += 1) {
                    loop_body_50_9_7(
                        __state, &__state->__6_zqx[(((sym_klev * sym_klon) * (_for_it_96 - 1)) + (sym_klon * (_for_it_23 - 1)))], &__state->__6_zsolqa[0],
                        &__state->__6_zqxn[(sym_klon * (_for_it_96 - 1))], _for_it_96, icend, sym_klev, sym_klon);
                }
            }
        }
        for (_for_it_99 = 1; (_for_it_99 <= 4); _for_it_99 = (_for_it_99 + 1)) {
            for (_for_it_100 = (_for_it_99 + 1); (_for_it_100 <= 5); _for_it_100 = (_for_it_100 + 1)) {
                {
                    {
#pragma omp parallel for
                        for (auto tmp_parfor_52 = 1; tmp_parfor_52 < (icend + 1); tmp_parfor_52 += 1) {
                            loop_body_204_0_0(__state, &__state->__6_zqlhs[((((5 * sym_klon) * (_for_it_99 - 1)) + tmp_parfor_52) - 1)], _for_it_100, _for_it_99, sym_klon);
                        }
                    }
                }
                for (_for_it_101 = (_for_it_99 + 1); (_for_it_101 <= 5); _for_it_101 = (_for_it_101 + 1)) {
                    {
                        {
#pragma omp parallel for
                            for (auto _for_it_102 = 1; _for_it_102 < (icend + 1); _for_it_102 += 1) {
                                loop_body_206_0_0(__state, &__state->__6_zqlhs[(_for_it_102 - 1)], _for_it_100, _for_it_101, _for_it_99, sym_klon);
                            }
                        }
                    }
                }
            }
        }
        for (_for_it_103 = 2; (_for_it_103 <= 5); _for_it_103 = (_for_it_103 + 1)) {
            for (_for_it_104 = 1; (_for_it_104 <= (_for_it_103 - 1)); _for_it_104 = (_for_it_104 + 1)) {
                {
                    {
#pragma omp parallel for
                        for (auto tmp_parfor_53 = 1; tmp_parfor_53 < (icend + 1); tmp_parfor_53 += 1) {
                            loop_body_192_0_0(
                                __state, &__state->__6_zqlhs[((((sym_klon * (_for_it_103 - 1)) + ((5 * sym_klon) * (_for_it_104 - 1))) + tmp_parfor_53) - 1)], &__state->__6_zqxn[(tmp_parfor_53 - 1)],
                                _for_it_103, _for_it_104, sym_klon);
                        }
                    }
                }
            }
        }
        {
            {
#pragma omp parallel for
                for (auto tmp_parfor_54 = 1; tmp_parfor_54 < (icend + 1); tmp_parfor_54 += 1) {
                    loop_body_50_5_0(__state, &__state->__6_zqlhs[(((24 * sym_klon) + tmp_parfor_54) - 1)], &__state->__6_zqxn[(((4 * sym_klon) + tmp_parfor_54) - 1)], sym_klon);
                }
            }
        }
        for (_for_it_105 = 4; (_for_it_105 >= 1); _for_it_105 = (_for_it_105 + -1)) {
            for (_for_it_106 = (_for_it_105 + 1); (_for_it_106 <= 5); _for_it_106 = (_for_it_106 + 1)) {
                {
                    {
#pragma omp parallel for
                        for (auto tmp_parfor_55 = 1; tmp_parfor_55 < (icend + 1); tmp_parfor_55 += 1) {
                            loop_body_174_0_0(
                                __state, &__state->__6_zqlhs[((((sym_klon * (_for_it_105 - 1)) + ((5 * sym_klon) * (_for_it_106 - 1))) + tmp_parfor_55) - 1)], &__state->__6_zqxn[(tmp_parfor_55 - 1)],
                                _for_it_105, _for_it_106, sym_klon);
                        }
                    }
                }
            }
            {
                {
#pragma omp parallel for
                    for (auto tmp_parfor_56 = 1; tmp_parfor_56 < (icend + 1); tmp_parfor_56 += 1) {
                        loop_body_172_0_0(
                            __state, &__state->__6_zqlhs[((((6 * sym_klon) * (_for_it_105 - 1)) + tmp_parfor_56) - 1)], &__state->__6_zqxn[(((sym_klon * (_for_it_105 - 1)) + tmp_parfor_56) - 1)],
                            sym_klon);
                    }
                }
            }
        }
        for (_for_it_107 = 1; (_for_it_107 <= 4); _for_it_107 = (_for_it_107 + 1)) {
            {
                {
#pragma omp parallel for
                    for (auto _for_it_108 = 1; _for_it_108 < (icend + 1); _for_it_108 += 1) {
                        loop_body_237_0_0(__state, &__state->__6_zqxn[(_for_it_108 - 1)], _for_it_107, sym_klon);
                    }
                }
            }
        }
        {
            {
#pragma omp parallel for
                for (auto _for_it_109 = 1; _for_it_109 < 6; _for_it_109 += 1) {
                    loop_body_50_13_0(
                        __state, &__state->__6_zqxn[(sym_klon * (_for_it_109 - 1))], &__state->__6_zqxn2d[(((sym_klev * sym_klon) * (_for_it_109 - 1)) + (sym_klon * (_for_it_23 - 1)))],
                        &__state->__6_zqxnm1[(sym_klon * (_for_it_109 - 1))], icend, sym_klev, sym_klon);
                }
            }
            {
#pragma omp parallel for
                for (auto _for_it_111 = 1; _for_it_111 < 6; _for_it_111 += 1) {
                    loop_body_50_13_6(
                        __state, &__state->__6_zfallsink[(sym_klon * (_for_it_111 - 1))], &__state->__6_zqxn[(sym_klon * (_for_it_111 - 1))], &__state->__6_zrdtgdp[0],
                        &__state->__6_zpfplsx[((_for_it_23 * sym_klon) + ((sym_klon * (_for_it_111 - 1)) * (sym_klev + 1)))], icend, sym_klev, sym_klon);
                }
            }
            {
#pragma omp parallel for
                for (auto _for_it_113 = 1; _for_it_113 < (icend + 1); _for_it_113 += 1) {
                    loop_body_50_13_12(__state, &__state->__6_zpfplsx[((_for_it_113 + (_for_it_23 * sym_klon)) - 1)], &__state->__6_zqpretot[(_for_it_113 - 1)], sym_klev, sym_klon);
                }
            }
            {
#pragma omp parallel for
                for (auto _for_it_114 = 1; _for_it_114 < (icend + 1); _for_it_114 += 1) {
                    loop_body_50_13_16(__state, &__state->__6_zqpretot[(_for_it_114 - 1)], &__state->__6_zcovptot[(_for_it_114 - 1)]);
                }
            }
        }
        for (_for_it_115 = 1; (_for_it_115 <= 4); _for_it_115 = (_for_it_115 + 1)) {
            {
                {
#pragma omp parallel for
                    for (auto _for_it_116 = 1; _for_it_116 < (icend + 1); _for_it_116 += 1) {
                        loop_body_322_1_0(
                            __state, &__state->__6_zconvsink[((_for_it_116 + (sym_klon * (_for_it_115 - 1))) - 1)], &__state->__6_zconvsrce[((_for_it_116 + (sym_klon * (_for_it_115 - 1))) - 1)],
                            &__state->__6_zfallsink[((_for_it_116 + (sym_klon * (_for_it_115 - 1))) - 1)], &__state->__6_zfallsrce[((_for_it_116 + (sym_klon * (_for_it_115 - 1))) - 1)],
                            &__state->__6_zpsupsatsrce[((_for_it_116 + (sym_klon * (_for_it_115 - 1))) - 1)], &__state->__6_zqxn[((_for_it_116 + (sym_klon * (_for_it_115 - 1))) - 1)],
                            &__state->__6_zfluxq[((_for_it_116 + (sym_klon * (_for_it_115 - 1))) - 1)], sym_klon);
                    }
                }
            }
            _if_cond_81 = (__state->__6_iphase[(_for_it_115 - 1)] == 1);
            if ((_if_cond_81 == 1)) {
                {
                    {
#pragma omp parallel for
                        for (auto _for_it_117 = 1; _for_it_117 < (icend + 1); _for_it_117 += 1) {
                            loop_body_326_0_0(
                                __state, ydthf, &__state->__6_zfluxq[((_for_it_117 + (sym_klon * (_for_it_115 - 1))) - 1)], __state->__6_zqtmst,
                                &__state->__6_zqx[(((_for_it_117 + ((sym_klev * sym_klon) * (_for_it_115 - 1))) + (sym_klon * (_for_it_23 - 1))) - 1)],
                                &__state->__6_zqxn[((_for_it_117 + (sym_klon * (_for_it_115 - 1))) - 1)], &ptendency_loc_t[((_for_it_117 + (sym_klon * (_for_it_23 - 1))) - 1)], sym_klev, sym_klon);
                        }
                    }
                }
            }
            _if_cond_82 = (__state->__6_iphase[(_for_it_115 - 1)] == 2);
            if ((_if_cond_82 == 1)) {
                {
                    {
#pragma omp parallel for
                        for (auto _for_it_118 = 1; _for_it_118 < (icend + 1); _for_it_118 += 1) {
                            loop_body_329_0_0(
                                __state, ydthf, &__state->__6_zfluxq[((_for_it_118 + (sym_klon * (_for_it_115 - 1))) - 1)], __state->__6_zqtmst,
                                &__state->__6_zqx[(((_for_it_118 + ((sym_klev * sym_klon) * (_for_it_115 - 1))) + (sym_klon * (_for_it_23 - 1))) - 1)],
                                &__state->__6_zqxn[((_for_it_118 + (sym_klon * (_for_it_115 - 1))) - 1)], &ptendency_loc_t[((_for_it_118 + (sym_klon * (_for_it_23 - 1))) - 1)], sym_klev, sym_klon);
                        }
                    }
                }
            }
            {
                {
#pragma omp parallel for
                    for (auto _for_it_119 = 1; _for_it_119 < (icend + 1); _for_it_119 += 1) {
                        loop_body_322_0_0(
                            __state, __state->__6_zqtmst, &__state->__6_zqx0[(((_for_it_119 + ((sym_klev * sym_klon) * (_for_it_115 - 1))) + (sym_klon * (_for_it_23 - 1))) - 1)],
                            &__state->__6_zqxn[((_for_it_119 + (sym_klon * (_for_it_115 - 1))) - 1)],
                            &ptendency_loc_cld[(((_for_it_119 + ((sym_klev * sym_klon) * (_for_it_115 - 1))) + (sym_klon * (_for_it_23 - 1))) - 1)], sym_klev, sym_klon);
                    }
                }
            }
        }
        {
            {
#pragma omp parallel for
                for (auto _for_it_120 = 1; _for_it_120 < (icend + 1); _for_it_120 += 1) {
                    loop_body_50_4_0(
                        __state, &__state->__6_zda[(_for_it_120 - 1)], __state->__6_zqtmst, &__state->__6_zqx[(((_for_it_120 + ((4 * sym_klev) * sym_klon)) + (sym_klon * (_for_it_23 - 1))) - 1)],
                        &__state->__6_zqxn[((_for_it_120 + (4 * sym_klon)) - 1)], &ptendency_loc_a[((_for_it_120 + (sym_klon * (_for_it_23 - 1))) - 1)],
                        &ptendency_loc_q[((_for_it_120 + (sym_klon * (_for_it_23 - 1))) - 1)], sym_klev, sym_klon);
                }
            }
            {
#pragma omp parallel for
                for (auto _for_it_121 = 1; _for_it_121 < (icend + 1); _for_it_121 += 1) {
                    loop_body_50_4_11(__state, &__state->__6_zcovptot[(_for_it_121 - 1)], &pcovptot_var_31[((_for_it_121 + (sym_klon * (_for_it_23 - 1))) - 1)], sym_klon);
                }
            }
        }
    }

    {
        {
#pragma omp parallel for
            for (auto _for_it_122 = 1; _for_it_122 < (sym_klev + 2); _for_it_122 += 1) {
                loop_body_6_6_0(
                    __state, &__state->__6_zpfplsx[(sym_klon * (_for_it_122 - 1))], &pfplsl_var_43[(sym_klon * (_for_it_122 - 1))], &pfplsn_var_44[(sym_klon * (_for_it_122 - 1))], icend, sym_klev,
                    sym_klon);
            }
        }
        {
#pragma omp parallel for
            for (auto _for_it_124 = 1; _for_it_124 < (icend + 1); _for_it_124 += 1) {
                loop_body_6_6_7(
                    __state, &pfcqlng_var_35[(_for_it_124 - 1)], &pfcqnng_var_36[(_for_it_124 - 1)], &pfcqrng_var_39[(_for_it_124 - 1)], &pfcqsng_var_40[(_for_it_124 - 1)],
                    &pfsqif_var_34[(_for_it_124 - 1)], &pfsqitur_var_42[(_for_it_124 - 1)], &pfsqlf_var_33[(_for_it_124 - 1)], &pfsqltur_var_41[(_for_it_124 - 1)], &pfsqrf_var_37[(_for_it_124 - 1)],
                    &pfsqsf_var_38[(_for_it_124 - 1)], sym_klon);
            }
        }
    }

    for (_for_it_125 = 1; (_for_it_125 <= sym_klev); _for_it_125 = (_for_it_125 + 1)) {
        {
            {
#pragma omp parallel for
                for (auto _for_it_126 = 1; _for_it_126 < (icend + 1); _for_it_126 += 1) {
                    loop_body_48_0_0(
                        __state, &paph_var_18[(_for_it_126 - 1)], &plude_var_23[((_for_it_126 + (sym_klon * (_for_it_125 - 1))) - 1)], &ptsphy_var_5[0],
                        &pvfi_var_10[((_for_it_126 + (sym_klon * (_for_it_125 - 1))) - 1)], &pvfl_var_9[((_for_it_126 + (sym_klon * (_for_it_125 - 1))) - 1)],
                        &__state->__6_zfoealfa[((_for_it_126 + (sym_klon * (_for_it_125 - 1))) - 1)], &__state->__6_zlneg[((_for_it_126 + (sym_klon * (_for_it_125 - 1))) - 1)], __state->__6_zqtmst,
                        &__state->__6_zqx0[((_for_it_126 + (sym_klon * (_for_it_125 - 1))) - 1)], &__state->__6_zqxn2d[((_for_it_126 + (sym_klon * (_for_it_125 - 1))) - 1)], __state->__6_zrg_r,
                        &pfcqlng_var_35[(_for_it_126 - 1)], &pfcqnng_var_36[(_for_it_126 - 1)], &pfcqrng_var_39[(((_for_it_125 * sym_klon) + _for_it_126) - 1)],
                        &pfcqsng_var_40[(((_for_it_125 * sym_klon) + _for_it_126) - 1)], &pfsqif_var_34[(_for_it_126 - 1)], &pfsqitur_var_42[(_for_it_126 - 1)], &pfsqlf_var_33[(_for_it_126 - 1)],
                        &pfsqltur_var_41[(_for_it_126 - 1)], &pfsqrf_var_37[(((_for_it_125 * sym_klon) + _for_it_126) - 1)], &pfsqsf_var_38[(((_for_it_125 * sym_klon) + _for_it_126) - 1)],
                        _for_it_125, sym_klev, sym_klon);
                }
            }
        }
    }

    {
        {
#pragma omp parallel for
            for (auto _for_it_127 = 1; _for_it_127 < (sym_klev + 2); _for_it_127 += 1) {
                loop_body_6_7_0(
                    __state, &pfplsl_var_43[(sym_klon * (_for_it_127 - 1))], &pfplsn_var_44[(sym_klon * (_for_it_127 - 1))], ydcst, &pfhpsl_var_45[(sym_klon * (_for_it_127 - 1))],
                    &pfhpsn_var_46[(sym_klon * (_for_it_127 - 1))], icend, sym_klon);
            }
        }
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
    int ibl;
    int tmp_arg_106;
    int icend;
    int _for_it_129;

    for (_for_it_129 = 1; (_for_it_129 <= ngptot); _for_it_129 = (_for_it_129 + nproma)) {
        ibl = (((_for_it_129 - 1) / nproma) + 1);
        tmp_arg_106 = ((ngptot - _for_it_129) + 1);

        icend = min(nproma, tmp_arg_106);
        {
            double* pt_view_0;
            pt_view_0 = &pt[((__f2dace_A_pt_d_0_s_0 * __f2dace_A_pt_d_1_s_1) * ((-__f2dace_OA_pt_d_2_s_2) + ibl))];
            double* pq_view_1;
            pq_view_1 = &pq[((__f2dace_A_pq_d_0_s_3 * __f2dace_A_pq_d_1_s_4) * ((-__f2dace_OA_pq_d_2_s_5) + ibl))];
            double* tendency_tmp_t_view_2;
            tendency_tmp_t_view_2 = &tendency_tmp_t[((__f2dace_A_tendency_tmp_t_d_0_s_6 * __f2dace_A_tendency_tmp_t_d_1_s_7) * ((-__f2dace_OA_tendency_tmp_t_d_2_s_8) + ibl))];
            double* tendency_tmp_q_view_3;
            tendency_tmp_q_view_3 = &tendency_tmp_q[((__f2dace_A_tendency_tmp_q_d_0_s_9 * __f2dace_A_tendency_tmp_q_d_1_s_10) * ((-__f2dace_OA_tendency_tmp_q_d_2_s_11) + ibl))];
            double* tendency_tmp_a_view_4;
            tendency_tmp_a_view_4 = &tendency_tmp_a[((__f2dace_A_tendency_tmp_a_d_0_s_12 * __f2dace_A_tendency_tmp_a_d_1_s_13) * ((-__f2dace_OA_tendency_tmp_a_d_2_s_14) + ibl))];
            double* tendency_tmp_cld_view_5;
            tendency_tmp_cld_view_5 = &tendency_tmp_cld[(
                ((__f2dace_A_tendency_tmp_cld_d_0_s_15 * __f2dace_A_tendency_tmp_cld_d_1_s_16) * __f2dace_A_tendency_tmp_cld_d_2_s_17) * ((-__f2dace_OA_tendency_tmp_cld_d_3_s_18) + ibl))];
            double* tendency_loc_t_view_6;
            tendency_loc_t_view_6 = &tendency_loc_t[((__f2dace_A_tendency_loc_t_d_0_s_19 * __f2dace_A_tendency_loc_t_d_1_s_20) * ((-__f2dace_OA_tendency_loc_t_d_2_s_21) + ibl))];
            double* tendency_loc_q_view_7;
            tendency_loc_q_view_7 = &tendency_loc_q[((__f2dace_A_tendency_loc_q_d_0_s_22 * __f2dace_A_tendency_loc_q_d_1_s_23) * ((-__f2dace_OA_tendency_loc_q_d_2_s_24) + ibl))];
            double* tendency_loc_a_view_8;
            tendency_loc_a_view_8 = &tendency_loc_a[((__f2dace_A_tendency_loc_a_d_0_s_25 * __f2dace_A_tendency_loc_a_d_1_s_26) * ((-__f2dace_OA_tendency_loc_a_d_2_s_27) + ibl))];
            double* tendency_loc_cld_view_9;
            tendency_loc_cld_view_9 = &tendency_loc_cld[(
                ((__f2dace_A_tendency_loc_cld_d_0_s_28 * __f2dace_A_tendency_loc_cld_d_1_s_29) * __f2dace_A_tendency_loc_cld_d_2_s_30) * ((-__f2dace_OA_tendency_loc_cld_d_3_s_31) + ibl))];
            double* pvfa_view_10;
            pvfa_view_10 = &pvfa[((__f2dace_A_pvfa_d_0_s_32 * __f2dace_A_pvfa_d_1_s_33) * ((-__f2dace_OA_pvfa_d_2_s_34) + ibl))];
            double* pvfl_view_11;
            pvfl_view_11 = &pvfl[((__f2dace_A_pvfl_d_0_s_35 * __f2dace_A_pvfl_d_1_s_36) * ((-__f2dace_OA_pvfl_d_2_s_37) + ibl))];
            double* pvfi_view_12;
            pvfi_view_12 = &pvfi[((__f2dace_A_pvfi_d_0_s_38 * __f2dace_A_pvfi_d_1_s_39) * ((-__f2dace_OA_pvfi_d_2_s_40) + ibl))];
            double* pdyna_view_13;
            pdyna_view_13 = &pdyna[((__f2dace_A_pdyna_d_0_s_41 * __f2dace_A_pdyna_d_1_s_42) * ((-__f2dace_OA_pdyna_d_2_s_43) + ibl))];
            double* pdynl_view_14;
            pdynl_view_14 = &pdynl[((__f2dace_A_pdynl_d_0_s_44 * __f2dace_A_pdynl_d_1_s_45) * ((-__f2dace_OA_pdynl_d_2_s_46) + ibl))];
            double* pdyni_view_15;
            pdyni_view_15 = &pdyni[((__f2dace_A_pdyni_d_0_s_47 * __f2dace_A_pdyni_d_1_s_48) * ((-__f2dace_OA_pdyni_d_2_s_49) + ibl))];
            double* phrsw_view_16;
            phrsw_view_16 = &phrsw[((__f2dace_A_phrsw_d_0_s_50 * __f2dace_A_phrsw_d_1_s_51) * ((-__f2dace_OA_phrsw_d_2_s_52) + ibl))];
            double* phrlw_view_17;
            phrlw_view_17 = &phrlw[((__f2dace_A_phrlw_d_0_s_53 * __f2dace_A_phrlw_d_1_s_54) * ((-__f2dace_OA_phrlw_d_2_s_55) + ibl))];
            double* pvervel_view_18;
            pvervel_view_18 = &pvervel[((__f2dace_A_pvervel_d_0_s_56 * __f2dace_A_pvervel_d_1_s_57) * ((-__f2dace_OA_pvervel_d_2_s_58) + ibl))];
            double* pap_view_19;
            pap_view_19 = &pap[((__f2dace_A_pap_d_0_s_59 * __f2dace_A_pap_d_1_s_60) * ((-__f2dace_OA_pap_d_2_s_61) + ibl))];
            double* paph_view_20;
            paph_view_20 = &paph[((__f2dace_A_paph_d_0_s_62 * __f2dace_A_paph_d_1_s_63) * ((-__f2dace_OA_paph_d_2_s_64) + ibl))];
            double* plu_view_24;
            plu_view_24 = &plu[((__f2dace_A_plu_d_0_s_71 * __f2dace_A_plu_d_1_s_72) * ((-__f2dace_OA_plu_d_2_s_73) + ibl))];
            double* plude_view_25;
            plude_view_25 = &plude[((__f2dace_A_plude_d_0_s_74 * __f2dace_A_plude_d_1_s_75) * ((-__f2dace_OA_plude_d_2_s_76) + ibl))];
            double* psnde_view_26;
            psnde_view_26 = &psnde[((__f2dace_A_psnde_d_0_s_77 * __f2dace_A_psnde_d_1_s_78) * ((-__f2dace_OA_psnde_d_2_s_79) + ibl))];
            double* pmfu_view_27;
            pmfu_view_27 = &pmfu[((__f2dace_A_pmfu_d_0_s_80 * __f2dace_A_pmfu_d_1_s_81) * ((-__f2dace_OA_pmfu_d_2_s_82) + ibl))];
            double* pmfd_view_28;
            pmfd_view_28 = &pmfd[((__f2dace_A_pmfd_d_0_s_83 * __f2dace_A_pmfd_d_1_s_84) * ((-__f2dace_OA_pmfd_d_2_s_85) + ibl))];
            double* pa_view_29;
            pa_view_29 = &pa[((__f2dace_A_pa_d_0_s_86 * __f2dace_A_pa_d_1_s_87) * ((-__f2dace_OA_pa_d_2_s_88) + ibl))];
            double* pclv_view_30;
            pclv_view_30 = &pclv[(((__f2dace_A_pclv_d_0_s_89 * __f2dace_A_pclv_d_1_s_90) * __f2dace_A_pclv_d_2_s_91) * ((-__f2dace_OA_pclv_d_3_s_92) + ibl))];
            double* psupsat_view_31;
            psupsat_view_31 = &psupsat[((__f2dace_A_psupsat_d_0_s_93 * __f2dace_A_psupsat_d_1_s_94) * ((-__f2dace_OA_psupsat_d_2_s_95) + ibl))];
            double* plcrit_aer_view_32;
            plcrit_aer_view_32 = &plcrit_aer[((__f2dace_A_plcrit_aer_d_0_s_96 * __f2dace_A_plcrit_aer_d_1_s_97) * ((-__f2dace_OA_plcrit_aer_d_2_s_98) + ibl))];
            double* picrit_aer_view_33;
            picrit_aer_view_33 = &picrit_aer[((__f2dace_A_picrit_aer_d_0_s_99 * __f2dace_A_picrit_aer_d_1_s_100) * ((-__f2dace_OA_picrit_aer_d_2_s_101) + ibl))];
            double* pre_ice_view_34;
            pre_ice_view_34 = &pre_ice[((__f2dace_A_pre_ice_d_0_s_102 * __f2dace_A_pre_ice_d_1_s_103) * ((-__f2dace_OA_pre_ice_d_2_s_104) + ibl))];
            double* pccn_view_35;
            pccn_view_35 = &pccn[((__f2dace_A_pccn_d_0_s_105 * __f2dace_A_pccn_d_1_s_106) * ((-__f2dace_OA_pccn_d_2_s_107) + ibl))];
            double* pnice_view_36;
            pnice_view_36 = &pnice[((__f2dace_A_pnice_d_0_s_108 * __f2dace_A_pnice_d_1_s_109) * ((-__f2dace_OA_pnice_d_2_s_110) + ibl))];
            double* pcovptot_view_37;
            pcovptot_view_37 = &pcovptot[((__f2dace_A_pcovptot_d_0_s_111 * __f2dace_A_pcovptot_d_1_s_112) * ((-__f2dace_OA_pcovptot_d_2_s_113) + ibl))];
            double* pfsqlf_view_39;
            pfsqlf_view_39 = &pfsqlf[((__f2dace_A_pfsqlf_d_0_s_116 * __f2dace_A_pfsqlf_d_1_s_117) * ((-__f2dace_OA_pfsqlf_d_2_s_118) + ibl))];
            double* pfsqif_view_40;
            pfsqif_view_40 = &pfsqif[((__f2dace_A_pfsqif_d_0_s_119 * __f2dace_A_pfsqif_d_1_s_120) * ((-__f2dace_OA_pfsqif_d_2_s_121) + ibl))];
            double* pfcqnng_view_41;
            pfcqnng_view_41 = &pfcqnng[((__f2dace_A_pfcqnng_d_0_s_125 * __f2dace_A_pfcqnng_d_1_s_126) * ((-__f2dace_OA_pfcqnng_d_2_s_127) + ibl))];
            double* pfcqlng_view_42;
            pfcqlng_view_42 = &pfcqlng[((__f2dace_A_pfcqlng_d_0_s_122 * __f2dace_A_pfcqlng_d_1_s_123) * ((-__f2dace_OA_pfcqlng_d_2_s_124) + ibl))];
            double* pfsqrf_view_43;
            pfsqrf_view_43 = &pfsqrf[((__f2dace_A_pfsqrf_d_0_s_128 * __f2dace_A_pfsqrf_d_1_s_129) * ((-__f2dace_OA_pfsqrf_d_2_s_130) + ibl))];
            double* pfsqsf_view_44;
            pfsqsf_view_44 = &pfsqsf[((__f2dace_A_pfsqsf_d_0_s_131 * __f2dace_A_pfsqsf_d_1_s_132) * ((-__f2dace_OA_pfsqsf_d_2_s_133) + ibl))];
            double* pfcqrng_view_45;
            pfcqrng_view_45 = &pfcqrng[((__f2dace_A_pfcqrng_d_0_s_134 * __f2dace_A_pfcqrng_d_1_s_135) * ((-__f2dace_OA_pfcqrng_d_2_s_136) + ibl))];
            double* pfcqsng_view_46;
            pfcqsng_view_46 = &pfcqsng[((__f2dace_A_pfcqsng_d_0_s_137 * __f2dace_A_pfcqsng_d_1_s_138) * ((-__f2dace_OA_pfcqsng_d_2_s_139) + ibl))];
            double* pfsqltur_view_47;
            pfsqltur_view_47 = &pfsqltur[((__f2dace_A_pfsqltur_d_0_s_140 * __f2dace_A_pfsqltur_d_1_s_141) * ((-__f2dace_OA_pfsqltur_d_2_s_142) + ibl))];
            double* pfsqitur_view_48;
            pfsqitur_view_48 = &pfsqitur[((__f2dace_A_pfsqitur_d_0_s_143 * __f2dace_A_pfsqitur_d_1_s_144) * ((-__f2dace_OA_pfsqitur_d_2_s_145) + ibl))];
            double* pfplsl_view_49;
            pfplsl_view_49 = &pfplsl[((__f2dace_A_pfplsl_d_0_s_146 * __f2dace_A_pfplsl_d_1_s_147) * ((-__f2dace_OA_pfplsl_d_2_s_148) + ibl))];
            double* pfplsn_view_50;
            pfplsn_view_50 = &pfplsn[((__f2dace_A_pfplsn_d_0_s_149 * __f2dace_A_pfplsn_d_1_s_150) * ((-__f2dace_OA_pfplsn_d_2_s_151) + ibl))];
            double* pfhpsl_view_51;
            pfhpsl_view_51 = &pfhpsl[((__f2dace_A_pfhpsl_d_0_s_152 * __f2dace_A_pfhpsl_d_1_s_153) * ((-__f2dace_OA_pfhpsl_d_2_s_154) + ibl))];
            double* pfhpsn_view_52;
            pfhpsn_view_52 = &pfhpsn[((__f2dace_A_pfhpsn_d_0_s_155 * __f2dace_A_pfhpsn_d_1_s_156) * ((-__f2dace_OA_pfhpsn_d_2_s_157) + ibl))];

            {
#pragma omp parallel for
                for (auto tmp_parfor_58 = __f2dace_OA_pcovptot_d_1_s_112; tmp_parfor_58 < (__f2dace_A_pcovptot_d_1_s_112 + __f2dace_OA_pcovptot_d_1_s_112); tmp_parfor_58 += 1) {
                    loop_body_1_2_0(
                        __state,
                        &pcovptot[(
                            ((__f2dace_A_pcovptot_d_0_s_111 * __f2dace_A_pcovptot_d_1_s_112) * ((-__f2dace_OA_pcovptot_d_2_s_113) + ibl)) +
                            (__f2dace_A_pcovptot_d_0_s_111 * ((-__f2dace_OA_pcovptot_d_1_s_112) + tmp_parfor_58)))],
                        __f2dace_A_pcovptot_d_0_s_111, __f2dace_A_pcovptot_d_1_s_112, __f2dace_OA_pcovptot_d_0_s_111);
                }
            }
            {
#pragma omp parallel for
                for (auto tmp_parfor_60 = __f2dace_OA_tendency_loc_cld_d_1_s_29; tmp_parfor_60 < (__f2dace_A_tendency_loc_cld_d_1_s_29 + __f2dace_OA_tendency_loc_cld_d_1_s_29); tmp_parfor_60 += 1) {
                    loop_body_1_2_4(
                        __state,
                        &tendency_loc_cld[(
                            ((((__f2dace_A_tendency_loc_cld_d_0_s_28 * __f2dace_A_tendency_loc_cld_d_1_s_29) * __f2dace_A_tendency_loc_cld_d_2_s_30) *
                              ((-__f2dace_OA_tendency_loc_cld_d_3_s_31) + ibl)) +
                             ((__f2dace_A_tendency_loc_cld_d_0_s_28 * __f2dace_A_tendency_loc_cld_d_1_s_29) * (5 - __f2dace_OA_tendency_loc_cld_d_2_s_30))) +
                            (__f2dace_A_tendency_loc_cld_d_0_s_28 * ((-__f2dace_OA_tendency_loc_cld_d_1_s_29) + tmp_parfor_60)))],
                        __f2dace_A_tendency_loc_cld_d_0_s_28, __f2dace_A_tendency_loc_cld_d_1_s_29, __f2dace_A_tendency_loc_cld_d_2_s_30, __f2dace_OA_tendency_loc_cld_d_0_s_28);
                }
            }
            cloudsc0_1_2_129(
                __state, &kfldx, &nlev, &nproma, &ktype[(__f2dace_A_ktype_d_0_s_69 * ((-__f2dace_OA_ktype_d_1_s_70) + ibl))],
                &ldcum[(__f2dace_A_ldcum_d_0_s_67 * ((-__f2dace_OA_ldcum_d_1_s_68) + ibl))], &pa_view_29[0], &pap_view_19[0], &paph_view_20[0], &pccn_view_35[0], &pclv_view_30[0], &pdyna_view_13[0],
                &pdyni_view_15[0], &pdynl_view_14[0], &phrlw_view_17[0], &phrsw_view_16[0], &picrit_aer_view_33[0], &plcrit_aer_view_32[0],
                &plsm[(__f2dace_A_plsm_d_0_s_65 * ((-__f2dace_OA_plsm_d_1_s_66) + ibl))], &plu_view_24[0], &pmfd_view_28[0], &pmfu_view_27[0], &pnice_view_36[0], &pq_view_1[0], &pre_ice_view_34[0],
                &psnde_view_26[0], &psupsat_view_31[0], &pt_view_0[0], &tendency_tmp_a_view_4[0], &tendency_tmp_cld_view_5[0], &tendency_tmp_q_view_3[0], &tendency_tmp_t_view_2[0], &ptsphy,
                &pvervel_view_18[0], &pvfa_view_10[0], &pvfi_view_12[0], &pvfl_view_11[0], ydomcst,
                &pcovptot[((__f2dace_A_pcovptot_d_0_s_111 * __f2dace_A_pcovptot_d_1_s_112) * ((-__f2dace_OA_pcovptot_d_2_s_113) + ibl))],
                &pfcqlng[((__f2dace_A_pfcqlng_d_0_s_122 * __f2dace_A_pfcqlng_d_1_s_123) * ((-__f2dace_OA_pfcqlng_d_2_s_124) + ibl))],
                &pfcqnng[((__f2dace_A_pfcqnng_d_0_s_125 * __f2dace_A_pfcqnng_d_1_s_126) * ((-__f2dace_OA_pfcqnng_d_2_s_127) + ibl))],
                &pfcqrng[((__f2dace_A_pfcqrng_d_0_s_134 * __f2dace_A_pfcqrng_d_1_s_135) * ((-__f2dace_OA_pfcqrng_d_2_s_136) + ibl))],
                &pfcqsng[((__f2dace_A_pfcqsng_d_0_s_137 * __f2dace_A_pfcqsng_d_1_s_138) * ((-__f2dace_OA_pfcqsng_d_2_s_139) + ibl))],
                &pfhpsl[((__f2dace_A_pfhpsl_d_0_s_152 * __f2dace_A_pfhpsl_d_1_s_153) * ((-__f2dace_OA_pfhpsl_d_2_s_154) + ibl))],
                &pfhpsn[((__f2dace_A_pfhpsn_d_0_s_155 * __f2dace_A_pfhpsn_d_1_s_156) * ((-__f2dace_OA_pfhpsn_d_2_s_157) + ibl))],
                &pfplsl[((__f2dace_A_pfplsl_d_0_s_146 * __f2dace_A_pfplsl_d_1_s_147) * ((-__f2dace_OA_pfplsl_d_2_s_148) + ibl))],
                &pfplsn[((__f2dace_A_pfplsn_d_0_s_149 * __f2dace_A_pfplsn_d_1_s_150) * ((-__f2dace_OA_pfplsn_d_2_s_151) + ibl))],
                &pfsqif[((__f2dace_A_pfsqif_d_0_s_119 * __f2dace_A_pfsqif_d_1_s_120) * ((-__f2dace_OA_pfsqif_d_2_s_121) + ibl))],
                &pfsqitur[((__f2dace_A_pfsqitur_d_0_s_143 * __f2dace_A_pfsqitur_d_1_s_144) * ((-__f2dace_OA_pfsqitur_d_2_s_145) + ibl))],
                &pfsqlf[((__f2dace_A_pfsqlf_d_0_s_116 * __f2dace_A_pfsqlf_d_1_s_117) * ((-__f2dace_OA_pfsqlf_d_2_s_118) + ibl))],
                &pfsqltur[((__f2dace_A_pfsqltur_d_0_s_140 * __f2dace_A_pfsqltur_d_1_s_141) * ((-__f2dace_OA_pfsqltur_d_2_s_142) + ibl))],
                &pfsqrf[((__f2dace_A_pfsqrf_d_0_s_128 * __f2dace_A_pfsqrf_d_1_s_129) * ((-__f2dace_OA_pfsqrf_d_2_s_130) + ibl))],
                &pfsqsf[((__f2dace_A_pfsqsf_d_0_s_131 * __f2dace_A_pfsqsf_d_1_s_132) * ((-__f2dace_OA_pfsqsf_d_2_s_133) + ibl))],
                &plude[((__f2dace_A_plude_d_0_s_74 * __f2dace_A_plude_d_1_s_75) * ((-__f2dace_OA_plude_d_2_s_76) + ibl))],
                &prainfrac_toprfz[(__f2dace_A_prainfrac_toprfz_d_0_s_114 * ((-__f2dace_OA_prainfrac_toprfz_d_1_s_115) + ibl))],
                &tendency_loc_a[((__f2dace_A_tendency_loc_a_d_0_s_25 * __f2dace_A_tendency_loc_a_d_1_s_26) * ((-__f2dace_OA_tendency_loc_a_d_2_s_27) + ibl))],
                &tendency_loc_cld[(
                    ((__f2dace_A_tendency_loc_cld_d_0_s_28 * __f2dace_A_tendency_loc_cld_d_1_s_29) * __f2dace_A_tendency_loc_cld_d_2_s_30) * ((-__f2dace_OA_tendency_loc_cld_d_3_s_31) + ibl))],
                &tendency_loc_q[((__f2dace_A_tendency_loc_q_d_0_s_22 * __f2dace_A_tendency_loc_q_d_1_s_23) * ((-__f2dace_OA_tendency_loc_q_d_2_s_24) + ibl))],
                &tendency_loc_t[((__f2dace_A_tendency_loc_t_d_0_s_19 * __f2dace_A_tendency_loc_t_d_1_s_20) * ((-__f2dace_OA_tendency_loc_t_d_2_s_21) + ibl))], ydecldp, ydoethf, icend, nlev, nproma);
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

    __state->__6_zlcond1 = new double DACE_ALIGN(64)[nproma];
    __state->__6_zlcond2 = new double DACE_ALIGN(64)[nproma];
    __state->__6_zrainaut = new double DACE_ALIGN(64)[nproma];
    __state->__6_zsnowaut = new double DACE_ALIGN(64)[nproma];
    __state->__6_zliqcld = new double DACE_ALIGN(64)[nproma];
    __state->__6_zicecld = new double DACE_ALIGN(64)[nproma];
    __state->__6_zfokoop = new double DACE_ALIGN(64)[nproma];
    __state->__6_zfoealfa = new double DACE_ALIGN(64)[((nlev * nproma) + nproma)];
    __state->__6_zicenuclei = new double DACE_ALIGN(64)[nproma];
    __state->__6_zlicld = new double DACE_ALIGN(64)[nproma];
    __state->__6_zlfinalsum = new double DACE_ALIGN(64)[nproma];
    __state->__6_zdqs = new double DACE_ALIGN(64)[nproma];
    __state->__6_ztold = new double DACE_ALIGN(64)[nproma];
    __state->__6_zqold = new double DACE_ALIGN(64)[nproma];
    __state->__6_zdtgdp = new double DACE_ALIGN(64)[nproma];
    __state->__6_zrdtgdp = new double DACE_ALIGN(64)[nproma];
    __state->__6_zcovpclr = new double DACE_ALIGN(64)[nproma];
    __state->__6_zcovptot = new double DACE_ALIGN(64)[nproma];
    __state->__6_zcovpmax = new double DACE_ALIGN(64)[nproma];
    __state->__6_zqpretot = new double DACE_ALIGN(64)[nproma];
    __state->__6_ztp1 = new double DACE_ALIGN(64)[((nproma * (nlev - 1)) + nproma)];
    __state->__6_zldefr = new double DACE_ALIGN(64)[nproma];
    __state->__6_zldifdt = new double DACE_ALIGN(64)[nproma];
    __state->__6_zlcust = new double DACE_ALIGN(64)[(5 * nproma)];
    __state->__6_zacust = new double DACE_ALIGN(64)[nproma];
    __state->__6_zmf = new double DACE_ALIGN(64)[nproma];
    __state->__6_zrho = new double DACE_ALIGN(64)[nproma];
    __state->__6_zsolab = new double DACE_ALIGN(64)[nproma];
    __state->__6_zsolac = new double DACE_ALIGN(64)[nproma];
    __state->__6_zanewm1 = new double DACE_ALIGN(64)[nproma];
    __state->__6_zgdp = new double DACE_ALIGN(64)[nproma];
    __state->__6_zda = new double DACE_ALIGN(64)[nproma];
    __state->__6_zli = new double DACE_ALIGN(64)[((nproma * (nlev - 1)) + nproma)];
    __state->__6_za = new double DACE_ALIGN(64)[((nproma * (nlev - 1)) + nproma)];
    __state->__6_zaorig = new double DACE_ALIGN(64)[((nproma * (nlev - 1)) + nproma)];
    __state->__6_zdp = new double DACE_ALIGN(64)[nproma];
    __state->__6_zmin = new double DACE_ALIGN(64)[nproma];
    __state->__6_zsupsat = new double DACE_ALIGN(64)[nproma];
    __state->__6_iphase = new int DACE_ALIGN(64)[5];
    __state->__6_imelt = new int DACE_ALIGN(64)[5];
    __state->__6_llfall = new int DACE_ALIGN(64)[5];
    __state->__6_llindex1 = new int DACE_ALIGN(64)[(5 * nproma)];
    __state->__6_llindex3 = new int DACE_ALIGN(64)[(25 * nproma)];
    __state->__6_iorder = new int DACE_ALIGN(64)[(5 * nproma)];
    __state->__6_zliqfrac = new double DACE_ALIGN(64)[((nproma * (nlev - 1)) + nproma)];
    __state->__6_zicefrac = new double DACE_ALIGN(64)[((nproma * (nlev - 1)) + nproma)];
    __state->__6_zqx = new double DACE_ALIGN(64)[((((4 * nlev) * nproma) + (nproma * (nlev - 1))) + nproma)];
    __state->__6_zqx0 = new double DACE_ALIGN(64)[((((4 * nlev) * nproma) + (nproma * (nlev - 1))) + nproma)];
    __state->__6_zqxn = new double DACE_ALIGN(64)[(5 * nproma)];
    __state->__6_zqxfg = new double DACE_ALIGN(64)[(5 * nproma)];
    __state->__6_zqxnm1 = new double DACE_ALIGN(64)[(5 * nproma)];
    __state->__6_zfluxq = new double DACE_ALIGN(64)[(5 * nproma)];
    __state->__6_zpfplsx = new double DACE_ALIGN(64)[(((nlev * nproma) + ((4 * nproma) * (nlev + 1))) + nproma)];
    __state->__6_zlneg = new double DACE_ALIGN(64)[((((4 * nlev) * nproma) + (nproma * (nlev - 1))) + nproma)];
    __state->__6_zmeltmax = new double DACE_ALIGN(64)[nproma];
    __state->__6_zfrzmax = new double DACE_ALIGN(64)[nproma];
    __state->__6_zicetot = new double DACE_ALIGN(64)[nproma];
    __state->__6_zqxn2d = new double DACE_ALIGN(64)[((((4 * nlev) * nproma) + (nproma * (nlev - 1))) + nproma)];
    __state->__6_zqsmix = new double DACE_ALIGN(64)[((nproma * (nlev - 1)) + nproma)];
    __state->__6_zqsliq = new double DACE_ALIGN(64)[((nproma * (nlev - 1)) + nproma)];
    __state->__6_zqsice = new double DACE_ALIGN(64)[((nproma * (nlev - 1)) + nproma)];
    __state->__6_zfoeewmt = new double DACE_ALIGN(64)[((nproma * (nlev - 1)) + nproma)];
    __state->__6_zfoeew = new double DACE_ALIGN(64)[((nproma * (nlev - 1)) + nproma)];
    __state->__6_zfoeeliqt = new double DACE_ALIGN(64)[((nproma * (nlev - 1)) + nproma)];
    __state->__6_zdqsicedt = new double DACE_ALIGN(64)[nproma];
    __state->__6_zdqsmixdt = new double DACE_ALIGN(64)[nproma];
    __state->__6_zcorqsice = new double DACE_ALIGN(64)[nproma];
    __state->__6_zcorqsmix = new double DACE_ALIGN(64)[nproma];
    __state->__6_zevaplimmix = new double DACE_ALIGN(64)[nproma];
    __state->__6_zsolqa = new double DACE_ALIGN(64)[(25 * nproma)];
    __state->__6_zsolqb = new double DACE_ALIGN(64)[(25 * nproma)];
    __state->__6_zqlhs = new double DACE_ALIGN(64)[(25 * nproma)];
    __state->__6_zvqx = new double DACE_ALIGN(64)[5];
    __state->__6_zratio = new double DACE_ALIGN(64)[(5 * nproma)];
    __state->__6_zsinksum = new double DACE_ALIGN(64)[(5 * nproma)];
    __state->__6_zfallsink = new double DACE_ALIGN(64)[(5 * nproma)];
    __state->__6_zfallsrce = new double DACE_ALIGN(64)[(5 * nproma)];
    __state->__6_zconvsrce = new double DACE_ALIGN(64)[(5 * nproma)];
    __state->__6_zconvsink = new double DACE_ALIGN(64)[(5 * nproma)];
    __state->__6_zpsupsatsrce = new double DACE_ALIGN(64)[(5 * nproma)];
    __state->__6_zcldtopdist = new double DACE_ALIGN(64)[nproma];
    __state->__6_zrainacc = new double DACE_ALIGN(64)[nproma];
    __state->__6_zraincld = new double DACE_ALIGN(64)[nproma];
    __state->__6_zsnowrime = new double DACE_ALIGN(64)[nproma];
    __state->__6_zsnowcld = new double DACE_ALIGN(64)[nproma];
    __state->__6_llrainliq = new int DACE_ALIGN(64)[nproma];

    if (__result) {
        delete __state;
        return nullptr;
    }
    return __state;
}

DACE_EXPORTED int __dace_exit_cloudsc_driver(cloudsc_driver_state_t* __state) {
    int __err = 0;
    delete[] __state->__6_zlcond1;
    delete[] __state->__6_zlcond2;
    delete[] __state->__6_zrainaut;
    delete[] __state->__6_zsnowaut;
    delete[] __state->__6_zliqcld;
    delete[] __state->__6_zicecld;
    delete[] __state->__6_zfokoop;
    delete[] __state->__6_zfoealfa;
    delete[] __state->__6_zicenuclei;
    delete[] __state->__6_zlicld;
    delete[] __state->__6_zlfinalsum;
    delete[] __state->__6_zdqs;
    delete[] __state->__6_ztold;
    delete[] __state->__6_zqold;
    delete[] __state->__6_zdtgdp;
    delete[] __state->__6_zrdtgdp;
    delete[] __state->__6_zcovpclr;
    delete[] __state->__6_zcovptot;
    delete[] __state->__6_zcovpmax;
    delete[] __state->__6_zqpretot;
    delete[] __state->__6_ztp1;
    delete[] __state->__6_zldefr;
    delete[] __state->__6_zldifdt;
    delete[] __state->__6_zlcust;
    delete[] __state->__6_zacust;
    delete[] __state->__6_zmf;
    delete[] __state->__6_zrho;
    delete[] __state->__6_zsolab;
    delete[] __state->__6_zsolac;
    delete[] __state->__6_zanewm1;
    delete[] __state->__6_zgdp;
    delete[] __state->__6_zda;
    delete[] __state->__6_zli;
    delete[] __state->__6_za;
    delete[] __state->__6_zaorig;
    delete[] __state->__6_zdp;
    delete[] __state->__6_zmin;
    delete[] __state->__6_zsupsat;
    delete[] __state->__6_iphase;
    delete[] __state->__6_imelt;
    delete[] __state->__6_llfall;
    delete[] __state->__6_llindex1;
    delete[] __state->__6_llindex3;
    delete[] __state->__6_iorder;
    delete[] __state->__6_zliqfrac;
    delete[] __state->__6_zicefrac;
    delete[] __state->__6_zqx;
    delete[] __state->__6_zqx0;
    delete[] __state->__6_zqxn;
    delete[] __state->__6_zqxfg;
    delete[] __state->__6_zqxnm1;
    delete[] __state->__6_zfluxq;
    delete[] __state->__6_zpfplsx;
    delete[] __state->__6_zlneg;
    delete[] __state->__6_zmeltmax;
    delete[] __state->__6_zfrzmax;
    delete[] __state->__6_zicetot;
    delete[] __state->__6_zqxn2d;
    delete[] __state->__6_zqsmix;
    delete[] __state->__6_zqsliq;
    delete[] __state->__6_zqsice;
    delete[] __state->__6_zfoeewmt;
    delete[] __state->__6_zfoeew;
    delete[] __state->__6_zfoeeliqt;
    delete[] __state->__6_zdqsicedt;
    delete[] __state->__6_zdqsmixdt;
    delete[] __state->__6_zcorqsice;
    delete[] __state->__6_zcorqsmix;
    delete[] __state->__6_zevaplimmix;
    delete[] __state->__6_zsolqa;
    delete[] __state->__6_zsolqb;
    delete[] __state->__6_zqlhs;
    delete[] __state->__6_zvqx;
    delete[] __state->__6_zratio;
    delete[] __state->__6_zsinksum;
    delete[] __state->__6_zfallsink;
    delete[] __state->__6_zfallsrce;
    delete[] __state->__6_zconvsrce;
    delete[] __state->__6_zconvsink;
    delete[] __state->__6_zpsupsatsrce;
    delete[] __state->__6_zcldtopdist;
    delete[] __state->__6_zrainacc;
    delete[] __state->__6_zraincld;
    delete[] __state->__6_zsnowrime;
    delete[] __state->__6_zsnowcld;
    delete[] __state->__6_llrainliq;
    delete __state;
    return __err;
}
