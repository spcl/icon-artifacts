
#ifndef __DACE_CODEGEN_GAS_OPTICS__
#define __DACE_CODEGEN_GAS_OPTICS__

#include <dace/dace.h>


struct thermodynamics_type {
    double* pressure_fl = {};
double* pressure_hl = {};
double* temperature_fl = {};
double* temperature_hl = {};
};


struct single_level_type {
    double* cos_sza = {};
double* skin_temperature = {};
double* spectral_solar_scaling = {};
};


struct config_type {
    int* i_band_from_g_lw = {};
int* i_band_from_reordered_g_sw = {};
};


struct gas_type {
    double* mixing_ratio = {};
};


struct global_data_type {
    double* absa_var_109 = {};
double* absa_var_116 = {};
double* absa_var_122 = {};
double* absa_var_127 = {};
double* absa_var_132 = {};
double* absa_var_138 = {};
double* absa_var_143 = {};
double* absa_var_149 = {};
double* absa_var_155 = {};
double* absa_var_163 = {};
double* absa_var_169 = {};
double* absa_var_175 = {};
double* absa_var_182 = {};
double* absa_var_188 = {};
double* absa_var_197 = {};
double* absa_var_208 = {};
double* absa_var_220 = {};
double* absa_var_228 = {};
double* absa_var_236 = {};
double* absa_var_244 = {};
double* absa_var_251 = {};
double* absa_var_259 = {};
double* absa_var_267 = {};
double* absa_var_273 = {};
double* absa_var_280 = {};
double* absa_var_288 = {};
double* absa_var_296 = {};
double* absa_var_303 = {};
double* absa_var_308 = {};
double* absb_var_110 = {};
double* absb_var_117 = {};
double* absb_var_123 = {};
double* absb_var_139 = {};
double* absb_var_150 = {};
double* absb_var_156 = {};
double* absb_var_164 = {};
double* absb_var_170 = {};
double* absb_var_176 = {};
double* absb_var_189 = {};
double* absb_var_198 = {};
double* absb_var_209 = {};
double* absb_var_221 = {};
double* absb_var_229 = {};
double* absb_var_237 = {};
double* absb_var_245 = {};
double* absb_var_252 = {};
double* absb_var_260 = {};
double* absb_var_268 = {};
double* absb_var_281 = {};
double* absb_var_297 = {};
double* absb_var_304 = {};
double* absb_var_309 = {};
double* absch4c = {};
double* absco2c = {};
double* absh2oc = {};
double* abso3ac_var_285 = {};
double* abso3ac_var_291 = {};
double* abso3bc_var_286 = {};
double* abso3bc_var_292 = {};
double* ccl4 = {};
double* cfc11adj = {};
double* cfc12_var_181 = {};
double* cfc12_var_196 = {};
double* cfc22adj = {};
double* chi_mls = {};
double* delwave = {};
double* forref_var_113 = {};
double* forref_var_119 = {};
double* forref_var_125 = {};
double* forref_var_129 = {};
double* forref_var_134 = {};
double* forref_var_141 = {};
double* forref_var_146 = {};
double* forref_var_152 = {};
double* forref_var_158 = {};
double* forref_var_166 = {};
double* forref_var_172 = {};
double* forref_var_179 = {};
double* forref_var_185 = {};
double* forref_var_193 = {};
double* forref_var_205 = {};
double* forref_var_213 = {};
double* forrefc_var_223 = {};
double* forrefc_var_231 = {};
double* forrefc_var_239 = {};
double* forrefc_var_247 = {};
double* forrefc_var_254 = {};
double* forrefc_var_262 = {};
double* forrefc_var_270 = {};
double* forrefc_var_275 = {};
double* forrefc_var_283 = {};
double* forrefc_var_311 = {};
double* fracrefa_var_107 = {};
double* fracrefa_var_114 = {};
double* fracrefa_var_120 = {};
double* fracrefa_var_126 = {};
double* fracrefa_var_130 = {};
double* fracrefa_var_136 = {};
double* fracrefa_var_142 = {};
double* fracrefa_var_147 = {};
double* fracrefa_var_153 = {};
double* fracrefa_var_159 = {};
double* fracrefa_var_167 = {};
double* fracrefa_var_173 = {};
double* fracrefa_var_180 = {};
double* fracrefa_var_186 = {};
double* fracrefa_var_194 = {};
double* fracrefa_var_206 = {};
double* fracrefb_var_108 = {};
double* fracrefb_var_115 = {};
double* fracrefb_var_121 = {};
double* fracrefb_var_131 = {};
double* fracrefb_var_137 = {};
double* fracrefb_var_148 = {};
double* fracrefb_var_154 = {};
double* fracrefb_var_160 = {};
double* fracrefb_var_168 = {};
double* fracrefb_var_174 = {};
double* fracrefb_var_187 = {};
double* fracrefb_var_195 = {};
double* fracrefb_var_207 = {};
double givfac = {};
double* ka_mco = {};
double* ka_mco2_var_135 = {};
double* ka_mco2_var_184 = {};
double* ka_mco2_var_191 = {};
double* ka_mco2_var_199 = {};
double* ka_mn2_var_111 = {};
double* ka_mn2_var_144 = {};
double* ka_mn2o_var_161 = {};
double* ka_mn2o_var_200 = {};
double* ka_mn2o_var_210 = {};
double* ka_mo2 = {};
double* ka_mo3_var_177 = {};
double* ka_mo3_var_201 = {};
double* kb_mco2_var_192 = {};
double* kb_mco2_var_202 = {};
double* kb_mn2 = {};
double* kb_mn2o_var_162 = {};
double* kb_mn2o_var_203 = {};
double* kb_mn2o_var_211 = {};
double* kb_mo2 = {};
double* kb_mo3 = {};
int layreffr_var_219 = {};
int layreffr_var_227 = {};
int layreffr_var_235 = {};
int layreffr_var_243 = {};
int layreffr_var_250 = {};
int layreffr_var_258 = {};
int layreffr_var_266 = {};
int layreffr_var_272 = {};
int layreffr_var_279 = {};
int layreffr_var_287 = {};
int layreffr_var_295 = {};
int layreffr_var_302 = {};
int layreffr_var_307 = {};
int* ngc = {};
int* nspa_var_216 = {};
int* nspa_var_313 = {};
int* nspb_var_217 = {};
int* nspb_var_314 = {};
double* preflog_var_214 = {};
double* preflog_var_315 = {};
double rayl_var_218 = {};
double rayl_var_225 = {};
double rayl_var_233 = {};
double rayl_var_241 = {};
double rayl_var_249 = {};
double rayl_var_256 = {};
double rayl_var_264 = {};
double rayl_var_300 = {};
double rayl_var_306 = {};
double* raylac = {};
double* raylbc = {};
double* raylc_var_277 = {};
double* raylc_var_290 = {};
double* raylc_var_294 = {};
double* raylc_var_299 = {};
double scalekur = {};
double* selfref_var_112 = {};
double* selfref_var_118 = {};
double* selfref_var_124 = {};
double* selfref_var_128 = {};
double* selfref_var_133 = {};
double* selfref_var_140 = {};
double* selfref_var_145 = {};
double* selfref_var_151 = {};
double* selfref_var_157 = {};
double* selfref_var_165 = {};
double* selfref_var_171 = {};
double* selfref_var_178 = {};
double* selfref_var_183 = {};
double* selfref_var_190 = {};
double* selfref_var_204 = {};
double* selfref_var_212 = {};
double* selfrefc_var_222 = {};
double* selfrefc_var_230 = {};
double* selfrefc_var_238 = {};
double* selfrefc_var_246 = {};
double* selfrefc_var_253 = {};
double* selfrefc_var_261 = {};
double* selfrefc_var_269 = {};
double* selfrefc_var_274 = {};
double* selfrefc_var_282 = {};
double* selfrefc_var_310 = {};
double* sfluxrefc_var_224 = {};
double* sfluxrefc_var_232 = {};
double* sfluxrefc_var_240 = {};
double* sfluxrefc_var_248 = {};
double* sfluxrefc_var_255 = {};
double* sfluxrefc_var_263 = {};
double* sfluxrefc_var_271 = {};
double* sfluxrefc_var_276 = {};
double* sfluxrefc_var_284 = {};
double* sfluxrefc_var_289 = {};
double* sfluxrefc_var_293 = {};
double* sfluxrefc_var_298 = {};
double* sfluxrefc_var_305 = {};
double* sfluxrefc_var_312 = {};
double strrat1 = {};
double strrat_var_226 = {};
double strrat_var_234 = {};
double strrat_var_242 = {};
double strrat_var_257 = {};
double strrat_var_265 = {};
double strrat_var_278 = {};
double strrat_var_301 = {};
double* totplnk = {};
double* tref_var_215 = {};
double* tref_var_316 = {};
};




struct gas_optics_state_t;  // Forward declaration.

DACE_EXPORTED gas_optics_state_t *__dace_init_gas_optics(config_type* config_var_457, gas_type* gas_var_460, global_data_type* global_data, double * __restrict__ incoming_sw_var_467, double * __restrict__ lw_albedo_var_461, double * __restrict__ lw_emission_var_466, double * __restrict__ od_lw_var_462, double * __restrict__ od_sw_var_463, double * __restrict__ planck_hl_var_465, single_level_type* single_level_var_458, double * __restrict__ ssa_sw_var_464, thermodynamics_type* thermodynamics_var_459, int __f2dace_OPTIONAL_incoming_sw_var_467, int __f2dace_OPTIONAL_lw_albedo_var_461, int __f2dace_OPTIONAL_lw_emission_var_466, int __f2dace_OPTIONAL_planck_hl_var_465, int iendcol_var_456, int istartcol_var_455, int ncol_var_453, int nlev_var_454, int sym_iendcol_var_456, int sym_istartcol_var_455, int sym_ncol_var_453, int sym_nlev_var_454);
DACE_EXPORTED int __dace_exit_gas_optics(gas_optics_state_t *__state);
DACE_EXPORTED void __program_gas_optics(gas_optics_state_t *__state, config_type* config_var_457, gas_type* gas_var_460, global_data_type* global_data, double * __restrict__ incoming_sw_var_467, double * __restrict__ lw_albedo_var_461, double * __restrict__ lw_emission_var_466, double * __restrict__ od_lw_var_462, double * __restrict__ od_sw_var_463, double * __restrict__ planck_hl_var_465, single_level_type* single_level_var_458, double * __restrict__ ssa_sw_var_464, thermodynamics_type* thermodynamics_var_459, int __f2dace_OPTIONAL_incoming_sw_var_467, int __f2dace_OPTIONAL_lw_albedo_var_461, int __f2dace_OPTIONAL_lw_emission_var_466, int __f2dace_OPTIONAL_planck_hl_var_465, int iendcol_var_456, int istartcol_var_455, int ncol_var_453, int nlev_var_454, int sym_iendcol_var_456, int sym_istartcol_var_455, int sym_ncol_var_453, int sym_nlev_var_454);

#endif // __DACE_CODEGEN_GAS_OPTICS__
