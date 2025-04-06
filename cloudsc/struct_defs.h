struct tomcst {
    // A1.0 Fundamental constants
    // * RPI          : number Pi
    // * RCLUM         : light velocity
    // * RHPLA          : Planck constant
    // * RKBOL          : Bolzmann constant
    // * RNAVO          : Avogadro number
    double rpi = {};
    double rclum = {};
    double rhpla = {};
    double rkbol = {};
    double rnavo = {};

    // A1.1 Astronomical constants
    // * RDAY           : duration of the solar day
    // * RDAYI          : invariant time unit of 86400s
    // * RHOUR          : duration of the solar hour
    // * REA            : astronomical unit (mean distance Earth-sun)
    // * REPSM          : polar axis tilting angle
    // * RSIYEA         : duration of the sideral year
    // * RSIDAY         : duration of the sideral day
    // * ROMEGA         : angular velocity of the Earth rotation
    double rday = {};
    double rdayi = {};
    double rhour = {};
    double rea = {};
    double repsm = {};
    double rsiyea = {};
    double rsiday = {};
    double romega = {};

    // A1.2 Geoide
    // * RA             : Earth radius
    // * RG             : gravity constant
    // * R1SA           : 1/RA
    double ra = {};
    double rg = {};
    double r1sa = {};

    // A1.3 Radiation
    // * RSIGMA         : Stefan-Bolzman constant
    // * RI0            : solar constant
    double rsigma = {};
    double ri0 = {};

    // A1.4 Thermodynamic gas phase
    // * R              : perfect gas constant
    // * RMD            : dry air molar mass
    // * RMV            : vapour water molar mass
    // * RMO3           : ozone molar mass
    // * RD             : R_dry (dry air constant)
    // * RV             : R_vap (vapour water constant)
    // * RCPD           : Cp_dry (dry air calorific capacity at constant pressure)
    // * RCPV           : Cp_vap (vapour calorific capacity at constant pressure)
    // * RCVD           : Cv_dry (dry air calorific capacity at constant volume)
    // * RCVV           : Cv_vap (vapour calorific capacity at constant volume)
    // * RKAPPA         : Kappa = R_dry/Cp_dry
    // * RETV           : R_vap/R_dry - 1
    // * RMCO2          : CO2 (carbon dioxyde) molar mass
    // * RMCH4          : CH4 (methane) molar mass
    // * RMN2O          : N2O molar mass
    // * RMCO           : CO (carbon monoxyde) molar mass
    // * RMHCHO         : HCHO molar mass
    // * RMNO2          : NO2 (nitrogen dioxyde) molar mass
    // * RMSO2          : SO2 (sulfur dioxyde) molar mass
    // * RMSO4          : SO4 (sulphate) molar mass
    double r_gas = {};
    double rmd = {};
    double rmv = {};
    double rmo3 = {};
    double rd = {};
    double rv = {};
    double rcpd = {};
    double rcpv = {};
    double rcvd = {};
    double rcvv = {};
    double rkappa = {};
    double retv = {};
    double rmco2 = {};
    double rmch4 = {};
    double rmn2o = {};
    double rmco = {};
    double rmhcho = {};
    double rmno2 = {};
    double rmso2 = {};
    double rmso4 = {};

    // A1.5,6 Thermodynamic liquid,solid phases
    // * RCW            : Cw (calorific capacity of liquid water)
    // * RCS            : Cs (calorific capacity of solid water)
    double rcw = {};
    double rcs = {};

    // A1.7 Thermodynamic transition of phase
    // * RATM           : pre_n = "normal" pressure
    // * RTT            : Tt = temperature of water fusion at "pre_n"
    // * RLVTT          : RLvTt = vaporisation latent heat at T=Tt
    // * RLSTT          : RLsTt = sublimation latent heat at T=Tt
    // * RLVZER         : RLv0 = vaporisation latent heat at T=0K
    // * RLSZER         : RLs0 = sublimation latent heat at T=0K
    // * RLMLT          : RLMlt = melting latent heat at T=Tt
    // * RDT            : Tt - Tx(ew-ei)
    double ratm = {};
    double rtt = {};
    double rlvtt = {};
    double rlstt = {};
    double rlvzer = {};
    double rlszer = {};
    double rlmlt = {};
    double rdt = {};

    // A1.8 Curve of saturation
    // * RESTT          : es(Tt) = saturation vapour tension at T=Tt
    // * RGAMW          : Rgamw = (Cw-Cp_vap)/R_vap
    // * RBETW          : Rbetw = RLvTt/R_vap + Rgamw*Tt
    // * RALPW          : Ralpw = log(es(Tt)) + Rbetw/Tt + Rgamw*log(Tt)
    // * RGAMS          : Rgams = (Cs-Cp_vap)/R_vap
    // * RBETS          : Rbets = RLsTt/R_vap + Rgams*Tt
    // * RALPS          : Ralps = log(es(Tt)) + Rbets/Tt + Rgams*log(Tt)
    // * RALPD          : Ralpd = Ralps - Ralpw
    // * RBETD          : Rbetd = Rbets - Rbetw
    // * RGAMD          : Rgamd = Rgams - Rgamw
    double restt = {};
    double rgamw = {};
    double rbetw = {};
    double ralpw = {};
    double rgams = {};
    double rbets = {};
    double ralps = {};
    double ralpd = {};
    double rbetd = {};
    double rgamd = {};

    // NaN value
    double rsnan = {};
};

struct toethf {
    double r2es = {};
    double r3les = {};
    double r3ies = {};
    double r4les = {};
    double r4ies = {};
    double r5les = {};
    double r5ies = {};
    double rvtmp2 = {};
    double rhoh2o = {};
    double r5alvcp = {};
    double r5alscp = {};
    double ralvdcp = {};
    double ralsdcp = {};
    double ralfdcp = {};
    double rtwat = {};
    double rtber = {};
    double rtbercu = {};
    double rtice = {};
    double rticecu = {};
    double rtwat_rtice_r = {};
    double rtwat_rticecu_r = {};
    double rkoop1 = {};
    double rkoop2 = {};
};

struct tecldp {
    double ramid = {};
    double rcldiff = {};
    double rcldiff_convi = {};
    double rclcrit = {};
    double rclcrit_sea = {};
    double rclcrit_land = {};
    double rkconv = {};
    double rprc1 = {};
    double rprc2 = {};
    double rcldmax = {};
    double rpecons = {};
    double rvrfactor = {};
    double rprecrhmax = {};
    double rtaumel = {};
    double ramin = {};
    double rlmin = {};
    double rkooptau = {};
    double rcldtopp = {};
    double rlcritsnow = {};
    double rsnowlin1 = {};
    double rsnowlin2 = {};
    double ricehi1 = {};
    double ricehi2 = {};
    double riceinit = {};
    double rvice = {};
    double rvrain = {};
    double rvsnow = {};
    double rthomo = {};
    double rcovpmin = {};
    double rccn = {};
    double rnice = {};
    double rccnom = {};
    double rccnss = {};
    double rccnsU = {};
    double rcldtopcf = {};
    double rdepliqrefrate = {};
    double rdepliqrefdepth = {};
    //--------------------------------------------------------
    // Autoconversion/accretion (Khairoutdinov and Kogan 2000)
    //--------------------------------------------------------
    double rcl_kkaac = {};
    double rcl_kkbac = {};
    double rcl_kkaau = {};
    double rcl_kkbauq = {};
    double rcl_kkbaun = {};
    double rcl_kk_cloud_num_sea = {};
    double rcl_kk_cloud_num_land = {};
    //--------------------------------------------------------
    // Ice
    //--------------------------------------------------------
    double rcl_ai = {};
    double rcl_bi = {};
    double rcl_ci = {};
    double rcl_di = {};
    double rcl_x1i = {};
    double rcl_x2i = {};
    double rcl_x3i = {};
    double rcl_x4i = {};
    double rcl_const1i = {};
    double rcl_const2i = {};
    double rcl_const3i = {};
    double rcl_const4i = {};
    double rcl_const5i = {};
    double rcl_const6i = {};
    double rcl_apb1 = {};
    double rcl_apb2 = {};
    double rcl_apb3 = {};
    //--------------------------------------------------------
    // Snow
    //--------------------------------------------------------
    double rcl_as = {};
    double rcl_bs = {};
    double rcl_cs = {};
    double rcl_ds = {};
    double rcl_x1s = {};
    double rcl_x2s = {};
    double rcl_x3s = {};
    double rcl_x4s = {};
    double rcl_const1s = {};
    double rcl_const2s = {};
    double rcl_const3s = {};
    double rcl_const4s = {};
    double rcl_const5s = {};
    double rcl_const6s = {};
    double rcl_const7s = {};
    double rcl_const8s = {};
    //--------------------------------------------------------
    // Rain
    //--------------------------------------------------------
    double rdenswat = {};
    double rdensref = {};
    double rcl_ar = {};
    double rcl_br = {};
    double rcl_cr = {};
    double rcl_dr = {};
    double rcl_x1r = {};
    double rcl_x2r = {};
    double rcl_x4r = {};
    double rcl_ka273 = {};
    double rcl_cdenom1 = {};
    double rcl_cdenom2 = {};
    double rcl_cdenom3 = {};
    double rcl_schmidt = {};
    double rcl_dynvisc = {};
    double rcl_const1r = {};
    double rcl_const2r = {};
    double rcl_const3r = {};
    double rcl_const4r = {};
    double rcl_fac1 = {};
    double rcl_fac2 = {};
    // Rain freezing
    double rcl_const5r = {};
    double rcl_const6r = {};
    double rcl_fzrab = {};
    double rcl_fzrbB = {};

    int32_t lcldextra = {};
    int32_t lcldbudget = {};

    int32_t nssopt = {};
    int32_t ncldtop = {};
    int32_t naeclbc = {};
    int32_t naecldu = {};
    int32_t naeclom = {};
    int32_t naeclss = {};
    int32_t naeclsu = {};
    int32_t ncldiag = {};

    // aerosols
    int32_t naercld = {};
    int32_t laerliqautolsp = {};
    int32_t laerliqautocp = {};
    int32_t laerliqautocpb = {};
    int32_t laerliqcoll = {};
    int32_t laericesed = {};
    int32_t laericeauto = {};

    // variance arrays
    double nshapep = {};
    double nshapeq = {};
    int32_t nbeta = {};
    double rbeta[101];
    double rbetap1[101];
};

//struct cloudsc_driver_state_t {};
