MODULE yoecldp
  IMPLICIT NONE
  SAVE
  TYPE :: tecldp
    REAL(KIND = 8) :: ramid
    REAL(KIND = 8) :: rcldiff
    REAL(KIND = 8) :: rcldiff_convi
    REAL(KIND = 8) :: rclcrit_sea
    REAL(KIND = 8) :: rclcrit_land
    REAL(KIND = 8) :: rpecons
    REAL(KIND = 8) :: rvrfactor
    REAL(KIND = 8) :: rprecrhmax
    REAL(KIND = 8) :: rtaumel
    REAL(KIND = 8) :: ramin
    REAL(KIND = 8) :: rlmin
    REAL(KIND = 8) :: rkooptau
    REAL(KIND = 8) :: rlcritsnow
    REAL(KIND = 8) :: rsnowlin1
    REAL(KIND = 8) :: rsnowlin2
    REAL(KIND = 8) :: riceinit
    REAL(KIND = 8) :: rvice
    REAL(KIND = 8) :: rvrain
    REAL(KIND = 8) :: rvsnow
    REAL(KIND = 8) :: rthomo
    REAL(KIND = 8) :: rcovpmin
    REAL(KIND = 8) :: rnice
    REAL(KIND = 8) :: rcldtopcf
    REAL(KIND = 8) :: rdepliqrefrate
    REAL(KIND = 8) :: rdepliqrefdepth
    REAL(KIND = 8) :: rcl_kkaac
    REAL(KIND = 8) :: rcl_kkbac
    REAL(KIND = 8) :: rcl_kkaau
    REAL(KIND = 8) :: rcl_kkbauq
    REAL(KIND = 8) :: rcl_kkbaun
    REAL(KIND = 8) :: rcl_kk_cloud_num_sea
    REAL(KIND = 8) :: rcl_kk_cloud_num_land
    REAL(KIND = 8) :: rcl_const1s
    REAL(KIND = 8) :: rcl_const7s
    REAL(KIND = 8) :: rcl_const8s
    REAL(KIND = 8) :: rdensref
    REAL(KIND = 8) :: rcl_ka273
    REAL(KIND = 8) :: rcl_cdenom1
    REAL(KIND = 8) :: rcl_cdenom2
    REAL(KIND = 8) :: rcl_cdenom3
    REAL(KIND = 8) :: rcl_const1r
    REAL(KIND = 8) :: rcl_const2r
    REAL(KIND = 8) :: rcl_const3r
    REAL(KIND = 8) :: rcl_const4r
    REAL(KIND = 8) :: rcl_fac1
    REAL(KIND = 8) :: rcl_fac2
    REAL(KIND = 8) :: rcl_const5r
    REAL(KIND = 8) :: rcl_const6r
    REAL(KIND = 8) :: rcl_fzrab
    INTEGER(KIND = 4) :: nssopt
    INTEGER(KIND = 4) :: ncldtop
    LOGICAL :: laericesed
    LOGICAL :: laericeauto
  END TYPE tecldp
  CONTAINS
END MODULE yoecldp
MODULE yoethf
  IMPLICIT NONE
  SAVE
  TYPE :: toethf
    REAL(KIND = 8) :: r2es
    REAL(KIND = 8) :: r3les
    REAL(KIND = 8) :: r3ies
    REAL(KIND = 8) :: r4les
    REAL(KIND = 8) :: r4ies
    REAL(KIND = 8) :: r5les
    REAL(KIND = 8) :: r5ies
    REAL(KIND = 8) :: r5alvcp
    REAL(KIND = 8) :: r5alscp
    REAL(KIND = 8) :: ralvdcp
    REAL(KIND = 8) :: ralsdcp
    REAL(KIND = 8) :: ralfdcp
    REAL(KIND = 8) :: rtwat
    REAL(KIND = 8) :: rtice
    REAL(KIND = 8) :: rtwat_rtice_r
    REAL(KIND = 8) :: rkoop1
    REAL(KIND = 8) :: rkoop2
  END TYPE toethf
  CONTAINS
END MODULE yoethf
MODULE yomcst
  IMPLICIT NONE
  SAVE
  TYPE :: tomcst
    REAL(KIND = 8) :: rg
    REAL(KIND = 8) :: rd
    REAL(KIND = 8) :: rv
    REAL(KIND = 8) :: rcpd
    REAL(KIND = 8) :: retv
    REAL(KIND = 8) :: rtt
    REAL(KIND = 8) :: rlvtt
    REAL(KIND = 8) :: rlstt
    REAL(KIND = 8) :: rlmlt
  END TYPE tomcst
  CONTAINS
END MODULE yomcst
MODULE yomphyder
  IMPLICIT NONE
  SAVE
  TYPE :: state_type
    REAL(KIND = 8), DIMENSION(:, :), POINTER :: t
    REAL(KIND = 8), DIMENSION(:, :), POINTER :: q, a
    REAL(KIND = 8), DIMENSION(:, :, :), POINTER :: cld
  END TYPE state_type
END MODULE yomphyder
MODULE cloudsc_driver_mod
  IMPLICIT NONE
  CONTAINS
  SUBROUTINE cloudsc_driver(numomp, nproma, nlev, ngptot, ngptotg, kfldx, ptsphy, pt, pq, tendency_cml, tendency_tmp, tendency_loc, pvfa, pvfl, pvfi, pdyna, pdynl, pdyni, phrsw, phrlw, pvervel, pap, paph, plsm, ldcum, ktype, plu, plude, psnde, pmfu, pmfd, pa, pclv, psupsat, plcrit_aer, picrit_aer, pre_ice, pccn, pnice, pcovptot, prainfrac_toprfz, pfsqlf, pfsqif, pfcqnng, pfcqlng, pfsqrf, pfsqsf, pfcqrng, pfcqsng, pfsqltur, pfsqitur, pfplsl, pfplsn, pfhpsl, pfhpsn, ydomcst, ydoethf, ydecldp)
    USE yomphyder, ONLY: state_type
    USE yomcst, ONLY: tomcst
    USE yoethf, ONLY: toethf
    USE yoecldp, ONLY: tecldp
    INTEGER(KIND = 4), INTENT(IN) :: numomp, nproma, nlev, ngptot, ngptotg
    INTEGER(KIND = 4), INTENT(IN) :: kfldx
    REAL(KIND = 8), INTENT(IN) :: ptsphy
    REAL(KIND = 8), INTENT(IN) :: pt(:, :, :)
    REAL(KIND = 8), INTENT(IN) :: pq(:, :, :)
    TYPE(state_type), INTENT(IN) :: tendency_cml(:)
    TYPE(state_type), INTENT(IN) :: tendency_tmp(:)
    TYPE(state_type), INTENT(OUT) :: tendency_loc(:)
    REAL(KIND = 8), INTENT(IN) :: pvfa(:, :, :)
    REAL(KIND = 8), INTENT(IN) :: pvfl(:, :, :)
    REAL(KIND = 8), INTENT(IN) :: pvfi(:, :, :)
    REAL(KIND = 8), INTENT(IN) :: pdyna(:, :, :)
    REAL(KIND = 8), INTENT(IN) :: pdynl(:, :, :)
    REAL(KIND = 8), INTENT(IN) :: pdyni(:, :, :)
    REAL(KIND = 8), INTENT(IN) :: phrsw(:, :, :)
    REAL(KIND = 8), INTENT(IN) :: phrlw(:, :, :)
    REAL(KIND = 8), INTENT(IN) :: pvervel(:, :, :)
    REAL(KIND = 8), INTENT(IN) :: pap(:, :, :)
    REAL(KIND = 8), INTENT(IN) :: paph(:, :, :)
    REAL(KIND = 8), INTENT(IN) :: plsm(:, :)
    LOGICAL, INTENT(IN) :: ldcum(:, :)
    INTEGER(KIND = 4), INTENT(IN) :: ktype(:, :)
    REAL(KIND = 8), INTENT(IN) :: plu(:, :, :)
    REAL(KIND = 8), INTENT(INOUT) :: plude(:, :, :)
    REAL(KIND = 8), INTENT(IN) :: psnde(:, :, :)
    REAL(KIND = 8), INTENT(IN) :: pmfu(:, :, :)
    REAL(KIND = 8), INTENT(IN) :: pmfd(:, :, :)
    REAL(KIND = 8), INTENT(IN) :: pa(:, :, :)
    REAL(KIND = 8), INTENT(IN) :: pclv(:, :, :, :)
    REAL(KIND = 8), INTENT(IN) :: psupsat(:, :, :)
    REAL(KIND = 8), INTENT(IN) :: plcrit_aer(:, :, :)
    REAL(KIND = 8), INTENT(IN) :: picrit_aer(:, :, :)
    REAL(KIND = 8), INTENT(IN) :: pre_ice(:, :, :)
    REAL(KIND = 8), INTENT(IN) :: pccn(:, :, :)
    REAL(KIND = 8), INTENT(IN) :: pnice(:, :, :)
    REAL(KIND = 8), INTENT(INOUT) :: pcovptot(:, :, :)
    REAL(KIND = 8), INTENT(OUT) :: prainfrac_toprfz(:, :)
    REAL(KIND = 8), INTENT(OUT) :: pfsqlf(:, :, :)
    REAL(KIND = 8), INTENT(OUT) :: pfsqif(:, :, :)
    REAL(KIND = 8), INTENT(OUT) :: pfcqlng(:, :, :)
    REAL(KIND = 8), INTENT(OUT) :: pfcqnng(:, :, :)
    REAL(KIND = 8), INTENT(OUT) :: pfsqrf(:, :, :)
    REAL(KIND = 8), INTENT(OUT) :: pfsqsf(:, :, :)
    REAL(KIND = 8), INTENT(OUT) :: pfcqrng(:, :, :)
    REAL(KIND = 8), INTENT(OUT) :: pfcqsng(:, :, :)
    REAL(KIND = 8), INTENT(OUT) :: pfsqltur(:, :, :)
    REAL(KIND = 8), INTENT(OUT) :: pfsqitur(:, :, :)
    REAL(KIND = 8), INTENT(OUT) :: pfplsl(:, :, :)
    REAL(KIND = 8), INTENT(OUT) :: pfplsn(:, :, :)
    REAL(KIND = 8), INTENT(OUT) :: pfhpsl(:, :, :)
    REAL(KIND = 8), INTENT(OUT) :: pfhpsn(:, :, :)
    INTEGER(KIND = 4) :: jkglo, ibl, icend
    TYPE(tomcst) :: ydomcst
    TYPE(toethf) :: ydoethf
    TYPE(tecldp) :: ydecldp
    DO jkglo = 1, ngptot, nproma
      ibl = (jkglo - 1) / nproma + 1
      icend = MIN(nproma, ngptot - jkglo + 1)
      pcovptot(:, :, ibl) = 0.0D0
      tendency_loc(ibl) % cld(:, :, 5) = 0.0D0
      CALL cloudsc(1, icend, nproma, nlev, ptsphy, pt(:, :, ibl), pq(:, :, ibl), tendency_tmp(ibl) % t, tendency_tmp(ibl) % q, tendency_tmp(ibl) % a, tendency_tmp(ibl) % cld, tendency_loc(ibl) % t, tendency_loc(ibl) % q, tendency_loc(ibl) % a, tendency_loc(ibl) % cld, pvfa(:, :, ibl), pvfl(:, :, ibl), pvfi(:, :, ibl), pdyna(:, :, ibl), pdynl(:, :, ibl), pdyni(:, :, ibl), phrsw(:, :, ibl), phrlw(:, :, ibl), pvervel(:, :, ibl), pap(:, :, ibl), paph(:, :, ibl), plsm(:, ibl), ldcum(:, ibl), ktype(:, ibl), plu(:, :, ibl), plude(:, :, ibl), psnde(:, :, ibl), pmfu(:, :, ibl), pmfd(:, :, ibl), pa(:, :, ibl), pclv(:, :, :, ibl), psupsat(:, :, ibl), plcrit_aer(:, :, ibl), picrit_aer(:, :, ibl), pre_ice(:, :, ibl), pccn(:, :, ibl), pnice(:, :, ibl), pcovptot(:, :, ibl), prainfrac_toprfz(:, ibl), pfsqlf(:, :, ibl), pfsqif(:, :, ibl), pfcqnng(:, :, ibl), pfcqlng(:, :, ibl), pfsqrf(:, :, ibl), pfsqsf(:, :, ibl), pfcqrng(:, :, ibl), pfcqsng(:, :, ibl), pfsqltur(:, :, ibl), pfsqitur(:, :, ibl), pfplsl(:, :, ibl), pfplsn(:, :, ibl), pfhpsl(:, :, ibl), pfhpsn(:, :, ibl), kfldx, ydomcst, ydoethf, ydecldp)
    END DO
  END SUBROUTINE cloudsc_driver
END MODULE cloudsc_driver_mod
SUBROUTINE cloudsc(kidia, kfdia, klon, klev, ptsphy, pt, pq, ptendency_tmp_t, ptendency_tmp_q, ptendency_tmp_a, ptendency_tmp_cld, ptendency_loc_t, ptendency_loc_q, ptendency_loc_a, ptendency_loc_cld, pvfa, pvfl, pvfi, pdyna, pdynl, pdyni, phrsw, phrlw, pvervel, pap, paph, plsm, ldcum, ktype, plu, plude, psnde, pmfu, pmfd, pa, pclv, psupsat, plcrit_aer, picrit_aer, pre_ice, pccn, pnice, pcovptot, prainfrac_toprfz, pfsqlf, pfsqif, pfcqnng, pfcqlng, pfsqrf, pfsqsf, pfcqrng, pfcqsng, pfsqltur, pfsqitur, pfplsl, pfplsn, pfhpsl, pfhpsn, kfldx, ydcst, ydthf, ydecldp)
  USE yomcst, ONLY: tomcst
  USE yoethf, ONLY: toethf
  USE yoecldp, ONLY: tecldp
  IMPLICIT NONE
  REAL(KIND = 8), INTENT(IN) :: plcrit_aer(klon, klev)
  REAL(KIND = 8), INTENT(IN) :: picrit_aer(klon, klev)
  REAL(KIND = 8), INTENT(IN) :: pre_ice(klon, klev)
  REAL(KIND = 8), INTENT(IN) :: pccn(klon, klev)
  REAL(KIND = 8), INTENT(IN) :: pnice(klon, klev)
  INTEGER(KIND = 4), INTENT(IN) :: klon
  INTEGER(KIND = 4), INTENT(IN) :: klev
  INTEGER(KIND = 4), INTENT(IN) :: kidia
  INTEGER(KIND = 4), INTENT(IN) :: kfdia
  REAL(KIND = 8), INTENT(IN) :: ptsphy
  REAL(KIND = 8), INTENT(IN) :: pt(klon, klev)
  REAL(KIND = 8), INTENT(IN) :: pq(klon, klev)
  REAL(KIND = 8), INTENT(IN) :: ptendency_tmp_t(klon, klev)
  REAL(KIND = 8), INTENT(IN) :: ptendency_tmp_q(klon, klev)
  REAL(KIND = 8), INTENT(IN) :: ptendency_tmp_a(klon, klev)
  REAL(KIND = 8), INTENT(IN) :: ptendency_tmp_cld(klon, klev, 5)
  REAL(KIND = 8), INTENT(INOUT) :: ptendency_loc_t(klon, klev)
  REAL(KIND = 8), INTENT(INOUT) :: ptendency_loc_q(klon, klev)
  REAL(KIND = 8), INTENT(INOUT) :: ptendency_loc_a(klon, klev)
  REAL(KIND = 8), INTENT(INOUT) :: ptendency_loc_cld(klon, klev, 5)
  REAL(KIND = 8), INTENT(IN) :: pvfa(klon, klev)
  REAL(KIND = 8), INTENT(IN) :: pvfl(klon, klev)
  REAL(KIND = 8), INTENT(IN) :: pvfi(klon, klev)
  REAL(KIND = 8), INTENT(IN) :: pdyna(klon, klev)
  REAL(KIND = 8), INTENT(IN) :: pdynl(klon, klev)
  REAL(KIND = 8), INTENT(IN) :: pdyni(klon, klev)
  REAL(KIND = 8), INTENT(IN) :: phrsw(klon, klev)
  REAL(KIND = 8), INTENT(IN) :: phrlw(klon, klev)
  REAL(KIND = 8), INTENT(IN) :: pvervel(klon, klev)
  REAL(KIND = 8), INTENT(IN) :: pap(klon, klev)
  REAL(KIND = 8), INTENT(IN) :: paph(klon, klev + 1)
  REAL(KIND = 8), INTENT(IN) :: plsm(klon)
  LOGICAL, INTENT(IN) :: ldcum(klon)
  INTEGER(KIND = 4), INTENT(IN) :: ktype(klon)
  REAL(KIND = 8), INTENT(IN) :: plu(klon, klev)
  REAL(KIND = 8), INTENT(INOUT) :: plude(klon, klev)
  REAL(KIND = 8), INTENT(IN) :: psnde(klon, klev)
  REAL(KIND = 8), INTENT(IN) :: pmfu(klon, klev)
  REAL(KIND = 8), INTENT(IN) :: pmfd(klon, klev)
  REAL(KIND = 8), INTENT(IN) :: pa(klon, klev)
  INTEGER(KIND = 4), INTENT(IN) :: kfldx
  REAL(KIND = 8), INTENT(IN) :: pclv(klon, klev, 5)
  REAL(KIND = 8), INTENT(IN) :: psupsat(klon, klev)
  REAL(KIND = 8), INTENT(OUT) :: pcovptot(klon, klev)
  REAL(KIND = 8), INTENT(OUT) :: prainfrac_toprfz(klon)
  REAL(KIND = 8), INTENT(OUT) :: pfsqlf(klon, klev + 1)
  REAL(KIND = 8), INTENT(OUT) :: pfsqif(klon, klev + 1)
  REAL(KIND = 8), INTENT(OUT) :: pfcqlng(klon, klev + 1)
  REAL(KIND = 8), INTENT(OUT) :: pfcqnng(klon, klev + 1)
  REAL(KIND = 8), INTENT(OUT) :: pfsqrf(klon, klev + 1)
  REAL(KIND = 8), INTENT(OUT) :: pfsqsf(klon, klev + 1)
  REAL(KIND = 8), INTENT(OUT) :: pfcqrng(klon, klev + 1)
  REAL(KIND = 8), INTENT(OUT) :: pfcqsng(klon, klev + 1)
  REAL(KIND = 8), INTENT(OUT) :: pfsqltur(klon, klev + 1)
  REAL(KIND = 8), INTENT(OUT) :: pfsqitur(klon, klev + 1)
  REAL(KIND = 8), INTENT(OUT) :: pfplsl(klon, klev + 1)
  REAL(KIND = 8), INTENT(OUT) :: pfplsn(klon, klev + 1)
  REAL(KIND = 8), INTENT(OUT) :: pfhpsl(klon, klev + 1)
  REAL(KIND = 8), INTENT(OUT) :: pfhpsn(klon, klev + 1)
  REAL(KIND = 8) :: zlcond1(klon), zlcond2(klon), zlevap, zleros, zlevapl(klon), zlevapi(klon), zrainaut(klon), zsnowaut(klon), zliqcld(klon), zicecld(klon)
  REAL(KIND = 8) :: zfokoop(klon), zfoealfa(klon, klev + 1)
  REAL(KIND = 8) :: zicenuclei(klon)
  REAL(KIND = 8) :: zlicld(klon)
  REAL(KIND = 8) :: zacond
  REAL(KIND = 8) :: zaeros
  REAL(KIND = 8) :: zlfinalsum(klon)
  REAL(KIND = 8) :: zdqs(klon)
  REAL(KIND = 8) :: ztold(klon)
  REAL(KIND = 8) :: zqold(klon)
  REAL(KIND = 8) :: zdtgdp(klon)
  REAL(KIND = 8) :: zrdtgdp(klon)
  REAL(KIND = 8) :: ztrpaus(klon)
  REAL(KIND = 8) :: zcovpclr(klon)
  REAL(KIND = 8) :: zpreclr
  REAL(KIND = 8) :: zcovptot(klon)
  REAL(KIND = 8) :: zcovpmax(klon)
  REAL(KIND = 8) :: zqpretot(klon)
  REAL(KIND = 8) :: zdpevap
  REAL(KIND = 8) :: zdtforc
  REAL(KIND = 8) :: zdtdiab
  REAL(KIND = 8) :: ztp1(klon, klev)
  REAL(KIND = 8) :: zldefr(klon)
  REAL(KIND = 8) :: zldifdt(klon)
  REAL(KIND = 8) :: zdtgdpf(klon)
  REAL(KIND = 8) :: zlcust(klon, 5)
  REAL(KIND = 8) :: zacust(klon)
  REAL(KIND = 8) :: zmf(klon)
  REAL(KIND = 8) :: zrho(klon)
  REAL(KIND = 8) :: zalfawm(klon)
  REAL(KIND = 8) :: zsolab(klon)
  REAL(KIND = 8) :: zsolac(klon)
  REAL(KIND = 8) :: zanew
  REAL(KIND = 8) :: zanewm1(klon)
  REAL(KIND = 8) :: zgdp(klon)
  REAL(KIND = 8) :: zda(klon)
  REAL(KIND = 8) :: zli(klon, klev), za(klon, klev)
  REAL(KIND = 8) :: zaorig(klon, klev)
  LOGICAL :: llflag(klon)
  LOGICAL :: llo1
  INTEGER(KIND = 4) :: ik, jk, jl, jm, jnn, jo
  REAL(KIND = 8) :: zdp(klon), zpaphd(klon)
  REAL(KIND = 8) :: zalfa
  REAL(KIND = 8) :: zalfaw
  REAL(KIND = 8) :: zbeta, zbeta1
  REAL(KIND = 8) :: zcor
  REAL(KIND = 8) :: zcdmax
  REAL(KIND = 8) :: zmin(klon)
  REAL(KIND = 8) :: zlcondlim
  REAL(KIND = 8) :: zdenom
  REAL(KIND = 8) :: zdpmxdt
  REAL(KIND = 8) :: zdpr
  REAL(KIND = 8) :: zdtdp
  REAL(KIND = 8) :: ze
  REAL(KIND = 8) :: zepsec
  REAL(KIND = 8) :: zfac, zfaci, zfacw
  REAL(KIND = 8) :: zgdcp
  REAL(KIND = 8) :: zinew
  REAL(KIND = 8) :: zlcrit
  REAL(KIND = 8) :: zmfdn
  REAL(KIND = 8) :: zqe
  REAL(KIND = 8) :: zqsat, zqtmst, zrdcp
  REAL(KIND = 8) :: zrhc, zsig, zsigk
  REAL(KIND = 8) :: zwtot
  REAL(KIND = 8) :: zzco, zzdl, zzrh, zzzdt, zqadj
  REAL(KIND = 8) :: zrg_r, zgdph_r, zcons1, zcond, zcons1a
  REAL(KIND = 8) :: zlfinal
  REAL(KIND = 8) :: zmelt
  REAL(KIND = 8) :: zevap
  REAL(KIND = 8) :: zfrz
  REAL(KIND = 8) :: zvpliq, zvpice
  REAL(KIND = 8) :: zadd, zbdd, zcvds, zice0, zdepos
  REAL(KIND = 8) :: zsupsat(klon)
  REAL(KIND = 8) :: zfall
  REAL(KIND = 8) :: zre_ice
  REAL(KIND = 8) :: zrldcp
  REAL(KIND = 8) :: zqp1env
  INTEGER(KIND = 4) :: iphase(5)
  INTEGER(KIND = 4) :: imelt(5)
  LOGICAL :: llfall(5)
  LOGICAL :: llindex1(klon, 5)
  LOGICAL :: llindex3(klon, 5, 5)
  REAL(KIND = 8) :: zmax
  REAL(KIND = 8) :: zrat
  INTEGER(KIND = 4) :: iorder(klon, 5)
  REAL(KIND = 8) :: zliqfrac(klon, klev)
  REAL(KIND = 8) :: zicefrac(klon, klev)
  REAL(KIND = 8) :: zqx(klon, klev, 5)
  REAL(KIND = 8) :: zqx0(klon, klev, 5)
  REAL(KIND = 8) :: zqxn(klon, 5)
  REAL(KIND = 8) :: zqxfg(klon, 5)
  REAL(KIND = 8) :: zqxnm1(klon, 5)
  REAL(KIND = 8) :: zfluxq(klon, 5)
  REAL(KIND = 8) :: zpfplsx(klon, klev + 1, 5)
  REAL(KIND = 8) :: zlneg(klon, klev, 5)
  REAL(KIND = 8) :: zmeltmax(klon)
  REAL(KIND = 8) :: zfrzmax(klon)
  REAL(KIND = 8) :: zicetot(klon)
  REAL(KIND = 8) :: zqxn2d(klon, klev, 5)
  REAL(KIND = 8) :: zqsmix(klon, klev)
  REAL(KIND = 8) :: zqsliq(klon, klev)
  REAL(KIND = 8) :: zqsice(klon, klev)
  REAL(KIND = 8) :: zfoeewmt(klon, klev)
  REAL(KIND = 8) :: zfoeew(klon, klev)
  REAL(KIND = 8) :: zfoeeliqt(klon, klev)
  REAL(KIND = 8) :: zdqsliqdt(klon), zdqsicedt(klon), zdqsmixdt(klon)
  REAL(KIND = 8) :: zcorqsliq(klon)
  REAL(KIND = 8) :: zcorqsice(klon)
  REAL(KIND = 8) :: zcorqsmix(klon)
  REAL(KIND = 8) :: zevaplimliq(klon), zevaplimice(klon), zevaplimmix(klon)
  REAL(KIND = 8) :: zsolqa(klon, 5, 5)
  REAL(KIND = 8) :: zsolqb(klon, 5, 5)
  REAL(KIND = 8) :: zqlhs(klon, 5, 5)
  REAL(KIND = 8) :: zvqx(5)
  REAL(KIND = 8) :: zexplicit, zratio(klon, 5), zsinksum(klon, 5)
  REAL(KIND = 8) :: zfallsink(klon, 5)
  REAL(KIND = 8) :: zfallsrce(klon, 5)
  REAL(KIND = 8) :: zconvsrce(klon, 5)
  REAL(KIND = 8) :: zconvsink(klon, 5)
  REAL(KIND = 8) :: zpsupsatsrce(klon, 5)
  REAL(KIND = 8) :: zsubsat
  REAL(KIND = 8) :: ztdmtw0
  REAL(KIND = 8) :: zcldtopdist(klon)
  REAL(KIND = 8) :: zinfactor
  INTEGER(KIND = 4) :: iwarmrain
  INTEGER(KIND = 4) :: ievaprain
  INTEGER(KIND = 4) :: ievapsnow
  INTEGER(KIND = 4) :: idepice
  REAL(KIND = 8) :: zrainacc(klon)
  REAL(KIND = 8) :: zraincld(klon)
  REAL(KIND = 8) :: zsnowrime(klon)
  REAL(KIND = 8) :: zsnowcld(klon)
  REAL(KIND = 8) :: zesatliq
  REAL(KIND = 8) :: zfallcorr
  REAL(KIND = 8) :: zlambda
  REAL(KIND = 8) :: zevap_denom
  REAL(KIND = 8) :: zcorr2
  REAL(KIND = 8) :: zka
  REAL(KIND = 8) :: zconst
  REAL(KIND = 8) :: ztemp
  LOGICAL :: llrainliq(klon)
  REAL(KIND = 8) :: ztmpa
  REAL(KIND = 8) :: zmm, zrr
  REAL(KIND = 8) :: zzratio
  REAL(KIND = 8) :: zepsilon
  REAL(KIND = 8) :: zcond1, zqp
  REAL(KIND = 8) :: oka
  TYPE(tomcst), INTENT(IN) :: ydcst
  TYPE(toethf), INTENT(IN) :: ydthf
  TYPE(tecldp), INTENT(IN) :: ydecldp
  zepsilon = 100.0D0 * EPSILON(zepsilon)
  iwarmrain = 2
  ievaprain = 2
  ievapsnow = 1
  idepice = 1
  zqtmst = 1.0D0 / ptsphy
  zgdcp = ydcst % rg / ydcst % rcpd
  zrdcp = ydcst % rd / ydcst % rcpd
  zcons1a = ydcst % rcpd / (ydcst % rlmlt * ydcst % rg * ydecldp % rtaumel)
  zepsec = 1D-14
  zrg_r = 1.0D0 / ydcst % rg
  zrldcp = 1.0D0 / (ydthf % ralsdcp - ydthf % ralvdcp)
  iphase(5) = 0
  iphase(1) = 1
  iphase(3) = 1
  iphase(2) = 2
  iphase(4) = 2
  imelt(5) = -99
  imelt(1) = 2
  imelt(3) = 4
  imelt(2) = 3
  imelt(4) = 3
  DO jk = 1, klev
    DO jl = 1, kfdia
      ptendency_loc_t(jl, jk) = 0.0D0
      ptendency_loc_q(jl, jk) = 0.0D0
      ptendency_loc_a(jl, jk) = 0.0D0
    END DO
  END DO
  DO jm = 1, 4
    DO jk = 1, klev
      DO jl = 1, kfdia
        ptendency_loc_cld(jl, jk, jm) = 0.0D0
      END DO
    END DO
  END DO
  zvqx(5) = 0.0D0
  zvqx(1) = 0.0D0
  zvqx(2) = ydecldp % rvice
  zvqx(3) = ydecldp % rvrain
  zvqx(4) = ydecldp % rvsnow
  llfall(:) = .FALSE.
  DO jm = 1, 5
    IF (zvqx(jm) > 0.0D0) llfall(jm) = .TRUE.
  END DO
  llfall(2) = .FALSE.
  DO jk = 1, klev
    DO jl = 1, kfdia
      ztp1(jl, jk) = pt(jl, jk) + ptsphy * ptendency_tmp_t(jl, jk)
      zqx(jl, jk, 5) = pq(jl, jk) + ptsphy * ptendency_tmp_q(jl, jk)
      zqx0(jl, jk, 5) = pq(jl, jk) + ptsphy * ptendency_tmp_q(jl, jk)
      za(jl, jk) = pa(jl, jk) + ptsphy * ptendency_tmp_a(jl, jk)
      zaorig(jl, jk) = pa(jl, jk) + ptsphy * ptendency_tmp_a(jl, jk)
    END DO
  END DO
  DO jm = 1, 4
    DO jk = 1, klev
      DO jl = 1, kfdia
        zqx(jl, jk, jm) = pclv(jl, jk, jm) + ptsphy * ptendency_tmp_cld(jl, jk, jm)
        zqx0(jl, jk, jm) = pclv(jl, jk, jm) + ptsphy * ptendency_tmp_cld(jl, jk, jm)
      END DO
    END DO
  END DO
  zpfplsx(:, :, :) = 0.0D0
  zqxn2d(:, :, :) = 0.0D0
  zlneg(:, :, :) = 0.0D0
  prainfrac_toprfz(:) = 0.0D0
  llrainliq(:) = .TRUE.
  DO jk = 1, klev
    DO jl = 1, kfdia
      IF (zqx(jl, jk, 1) + zqx(jl, jk, 2) < ydecldp % rlmin .OR. za(jl, jk) < ydecldp % ramin) THEN
        zlneg(jl, jk, 1) = zlneg(jl, jk, 1) + zqx(jl, jk, 1)
        zqadj = zqx(jl, jk, 1) * zqtmst
        ptendency_loc_q(jl, jk) = ptendency_loc_q(jl, jk) + zqadj
        ptendency_loc_t(jl, jk) = ptendency_loc_t(jl, jk) - ydthf % ralvdcp * zqadj
        zqx(jl, jk, 5) = zqx(jl, jk, 5) + zqx(jl, jk, 1)
        zqx(jl, jk, 1) = 0.0D0
        zlneg(jl, jk, 2) = zlneg(jl, jk, 2) + zqx(jl, jk, 2)
        zqadj = zqx(jl, jk, 2) * zqtmst
        ptendency_loc_q(jl, jk) = ptendency_loc_q(jl, jk) + zqadj
        ptendency_loc_t(jl, jk) = ptendency_loc_t(jl, jk) - ydthf % ralsdcp * zqadj
        zqx(jl, jk, 5) = zqx(jl, jk, 5) + zqx(jl, jk, 2)
        zqx(jl, jk, 2) = 0.0D0
        za(jl, jk) = 0.0D0
      END IF
    END DO
  END DO
  DO jm = 1, 4
    DO jk = 1, klev
      DO jl = 1, kfdia
        IF (zqx(jl, jk, jm) < ydecldp % rlmin) THEN
          zlneg(jl, jk, jm) = zlneg(jl, jk, jm) + zqx(jl, jk, jm)
          zqadj = zqx(jl, jk, jm) * zqtmst
          ptendency_loc_q(jl, jk) = ptendency_loc_q(jl, jk) + zqadj
          IF (iphase(jm) == 1) ptendency_loc_t(jl, jk) = ptendency_loc_t(jl, jk) - ydthf % ralvdcp * zqadj
          IF (iphase(jm) == 2) ptendency_loc_t(jl, jk) = ptendency_loc_t(jl, jk) - ydthf % ralsdcp * zqadj
          zqx(jl, jk, 5) = zqx(jl, jk, 5) + zqx(jl, jk, jm)
          zqx(jl, jk, jm) = 0.0D0
        END IF
      END DO
    END DO
  END DO
  DO jk = 1, klev
    DO jl = 1, kfdia
      oka = ztp1(jl, jk)
      zfoealfa(jl, jk) = foealfa(oka, ydthf)
      oka = ztp1(jl, jk)
      zfoeewmt(jl, jk) = MIN(foeewm(oka, ydthf, ydcst) / pap(jl, jk), 0.5D0)
      zqsmix(jl, jk) = zfoeewmt(jl, jk)
      zqsmix(jl, jk) = zqsmix(jl, jk) / (1.0D0 - ydcst % retv * zqsmix(jl, jk))
      oka = ztp1(jl, jk)
      zalfa = foedelta(oka, ydcst)
      oka = ztp1(jl, jk)
      zfoeew(jl, jk) = MIN((zalfa * foeeliq(oka, ydthf, ydcst) + (1.0D0 - zalfa) * foeeice(oka, ydthf, ydcst)) / pap(jl, jk), 0.5D0)
      zfoeew(jl, jk) = MIN(0.5D0, zfoeew(jl, jk))
      zqsice(jl, jk) = zfoeew(jl, jk) / (1.0D0 - ydcst % retv * zfoeew(jl, jk))
      oka = ztp1(jl, jk)
      zfoeeliqt(jl, jk) = MIN(foeeliq(oka, ydthf, ydcst) / pap(jl, jk), 0.5D0)
      zqsliq(jl, jk) = zfoeeliqt(jl, jk)
      zqsliq(jl, jk) = zqsliq(jl, jk) / (1.0D0 - ydcst % retv * zqsliq(jl, jk))
    END DO
  END DO
  DO jk = 1, klev
    DO jl = 1, kfdia
      za(jl, jk) = MAX(0.0D0, MIN(1.0D0, za(jl, jk)))
      zli(jl, jk) = zqx(jl, jk, 1) + zqx(jl, jk, 2)
      IF (zli(jl, jk) > ydecldp % rlmin) THEN
        zliqfrac(jl, jk) = zqx(jl, jk, 1) / zli(jl, jk)
        zicefrac(jl, jk) = 1.0D0 - zliqfrac(jl, jk)
      ELSE
        zliqfrac(jl, jk) = 0.0D0
        zicefrac(jl, jk) = 0.0D0
      END IF
    END DO
  END DO
  DO jl = 1, kfdia
    ztrpaus(jl) = 0.1D0
    zpaphd(jl) = 1.0D0 / paph(jl, klev + 1)
  END DO
  DO jk = 1, klev - 1
    DO jl = 1, kfdia
      zsig = pap(jl, jk) * zpaphd(jl)
      IF (zsig > 0.1D0 .AND. zsig < 0.4D0 .AND. ztp1(jl, jk) > ztp1(jl, jk + 1)) THEN
        ztrpaus(jl) = zsig
      END IF
    END DO
  END DO
  zanewm1(:) = 0.0D0
  zda(:) = 0.0D0
  zcovpclr(:) = 0.0D0
  zcovpmax(:) = 0.0D0
  zcovptot(:) = 0.0D0
  zcldtopdist(:) = 0.0D0
  DO jk = ydecldp % ncldtop, klev
    DO jm = 1, 5
      DO jl = 1, kfdia
        zqxfg(jl, jm) = zqx(jl, jk, jm)
      END DO
    END DO
    zlicld(:) = 0.0D0
    zrainaut(:) = 0.0D0
    zrainacc(:) = 0.0D0
    zsnowaut(:) = 0.0D0
    zldefr(:) = 0.0D0
    zacust(:) = 0.0D0
    zqpretot(:) = 0.0D0
    zlfinalsum(:) = 0.0D0
    zlcond1(:) = 0.0D0
    zlcond2(:) = 0.0D0
    zsupsat(:) = 0.0D0
    zlevapl(:) = 0.0D0
    zlevapi(:) = 0.0D0
    zsolab(:) = 0.0D0
    zsolac(:) = 0.0D0
    zsolqb(:, :, :) = 0.0D0
    zsolqa(:, :, :) = 0.0D0
    zfallsrce(:, :) = 0.0D0
    zfallsink(:, :) = 0.0D0
    zconvsrce(:, :) = 0.0D0
    zconvsink(:, :) = 0.0D0
    zpsupsatsrce(:, :) = 0.0D0
    zratio(:, :) = 0.0D0
    zicetot(:) = 0.0D0
    DO jl = 1, kfdia
      zdp(jl) = paph(jl, jk + 1) - paph(jl, jk)
      zgdp(jl) = ydcst % rg / zdp(jl)
      zrho(jl) = pap(jl, jk) / (ydcst % rd * ztp1(jl, jk))
      zdtgdp(jl) = ptsphy * zgdp(jl)
      zrdtgdp(jl) = zdp(jl) * (1.0D0 / (ptsphy * ydcst % rg))
      IF (jk > 1) zdtgdpf(jl) = ptsphy * ydcst % rg / (pap(jl, jk) - pap(jl, jk - 1))
      zfacw = ydthf % r5les / ((ztp1(jl, jk) - ydthf % r4les) ** 2)
      zcor = 1.0D0 / (1.0D0 - ydcst % retv * zfoeeliqt(jl, jk))
      zdqsliqdt(jl) = zfacw * zcor * zqsliq(jl, jk)
      zcorqsliq(jl) = 1.0D0 + ydthf % ralvdcp * zdqsliqdt(jl)
      zfaci = ydthf % r5ies / ((ztp1(jl, jk) - ydthf % r4ies) ** 2)
      zcor = 1.0D0 / (1.0D0 - ydcst % retv * zfoeew(jl, jk))
      zdqsicedt(jl) = zfaci * zcor * zqsice(jl, jk)
      zcorqsice(jl) = 1.0D0 + ydthf % ralsdcp * zdqsicedt(jl)
      zalfaw = zfoealfa(jl, jk)
      zalfawm(jl) = zalfaw
      zfac = zalfaw * zfacw + (1.0D0 - zalfaw) * zfaci
      zcor = 1.0D0 / (1.0D0 - ydcst % retv * zfoeewmt(jl, jk))
      zdqsmixdt(jl) = zfac * zcor * zqsmix(jl, jk)
      oka = ztp1(jl, jk)
      zcorqsmix(jl) = 1.0D0 + foeldcpm(oka, ydthf) * zdqsmixdt(jl)
      zevaplimmix(jl) = MAX((zqsmix(jl, jk) - zqx(jl, jk, 5)) / zcorqsmix(jl), 0.0D0)
      zevaplimliq(jl) = MAX((zqsliq(jl, jk) - zqx(jl, jk, 5)) / zcorqsliq(jl), 0.0D0)
      zevaplimice(jl) = MAX((zqsice(jl, jk) - zqx(jl, jk, 5)) / zcorqsice(jl), 0.0D0)
      ztmpa = 1.0D0 / MAX(za(jl, jk), zepsec)
      zliqcld(jl) = zqx(jl, jk, 1) * ztmpa
      zicecld(jl) = zqx(jl, jk, 2) * ztmpa
      zlicld(jl) = zliqcld(jl) + zicecld(jl)
    END DO
    DO jl = 1, kfdia
      IF (zqx(jl, jk, 1) < ydecldp % rlmin) THEN
        zsolqa(jl, 5, 1) = zqx(jl, jk, 1)
        zsolqa(jl, 1, 5) = - zqx(jl, jk, 1)
      END IF
      IF (zqx(jl, jk, 2) < ydecldp % rlmin) THEN
        zsolqa(jl, 5, 2) = zqx(jl, jk, 2)
        zsolqa(jl, 2, 5) = - zqx(jl, jk, 2)
      END IF
    END DO
    DO jl = 1, kfdia
      oka = ztp1(jl, jk)
      zfokoop(jl) = fokoop(oka, ydthf, ydcst)
    END DO
    DO jl = 1, kfdia
      IF (ztp1(jl, jk) >= ydcst % rtt .OR. ydecldp % nssopt == 0) THEN
        zfac = 1.0D0
        zfaci = 1.0D0
      ELSE
        zfac = za(jl, jk) + zfokoop(jl) * (1.0D0 - za(jl, jk))
        zfaci = ptsphy / ydecldp % rkooptau
      END IF
      IF (za(jl, jk) > 1.0D0 - ydecldp % ramin) THEN
        zsupsat(jl) = MAX((zqx(jl, jk, 5) - zfac * zqsice(jl, jk)) / zcorqsice(jl), 0.0D0)
      ELSE
        zqp1env = (zqx(jl, jk, 5) - za(jl, jk) * zqsice(jl, jk)) / MAX(1.0D0 - za(jl, jk), zepsilon)
        zsupsat(jl) = MAX((1.0D0 - za(jl, jk)) * (zqp1env - zfac * zqsice(jl, jk)) / zcorqsice(jl), 0.0D0)
      END IF
      IF (zsupsat(jl) > 1D-14) THEN
        IF (ztp1(jl, jk) > ydecldp % rthomo) THEN
          zsolqa(jl, 1, 5) = zsolqa(jl, 1, 5) + zsupsat(jl)
          zsolqa(jl, 5, 1) = zsolqa(jl, 5, 1) - zsupsat(jl)
          zqxfg(jl, 1) = zqxfg(jl, 1) + zsupsat(jl)
        ELSE
          zsolqa(jl, 2, 5) = zsolqa(jl, 2, 5) + zsupsat(jl)
          zsolqa(jl, 5, 2) = zsolqa(jl, 5, 2) - zsupsat(jl)
          zqxfg(jl, 2) = zqxfg(jl, 2) + zsupsat(jl)
        END IF
        zsolac(jl) = (1.0D0 - za(jl, jk)) * zfaci
      END IF
      IF (psupsat(jl, jk) > 1D-14) THEN
        IF (ztp1(jl, jk) > ydecldp % rthomo) THEN
          zsolqa(jl, 1, 1) = zsolqa(jl, 1, 1) + psupsat(jl, jk)
          zpsupsatsrce(jl, 1) = psupsat(jl, jk)
          zqxfg(jl, 1) = zqxfg(jl, 1) + psupsat(jl, jk)
        ELSE
          zsolqa(jl, 2, 2) = zsolqa(jl, 2, 2) + psupsat(jl, jk)
          zpsupsatsrce(jl, 2) = psupsat(jl, jk)
          zqxfg(jl, 2) = zqxfg(jl, 2) + psupsat(jl, jk)
        END IF
        zsolac(jl) = (1.0D0 - za(jl, jk)) * zfaci
      END IF
    END DO
    IF (jk < klev .AND. jk >= ydecldp % ncldtop) THEN
      DO jl = 1, kfdia
        plude(jl, jk) = plude(jl, jk) * zdtgdp(jl)
        IF (ldcum(jl) .AND. plude(jl, jk) > ydecldp % rlmin .AND. plu(jl, jk + 1) > 1D-14) THEN
          zsolac(jl) = zsolac(jl) + plude(jl, jk) / plu(jl, jk + 1)
          zalfaw = zfoealfa(jl, jk)
          zconvsrce(jl, 1) = zalfaw * plude(jl, jk)
          zconvsrce(jl, 2) = (1.0D0 - zalfaw) * plude(jl, jk)
          zsolqa(jl, 1, 1) = zsolqa(jl, 1, 1) + zconvsrce(jl, 1)
          zsolqa(jl, 2, 2) = zsolqa(jl, 2, 2) + zconvsrce(jl, 2)
        ELSE
          plude(jl, jk) = 0.0D0
        END IF
        IF (ldcum(jl)) zsolqa(jl, 4, 4) = zsolqa(jl, 4, 4) + psnde(jl, jk) * zdtgdp(jl)
      END DO
    END IF
    IF (jk > ydecldp % ncldtop) THEN
      DO jl = 1, kfdia
        zmf(jl) = MAX(0.0D0, (pmfu(jl, jk) + pmfd(jl, jk)) * zdtgdp(jl))
        zacust(jl) = zmf(jl) * zanewm1(jl)
      END DO
      DO jm = 1, 5
        IF (.NOT. llfall(jm) .AND. iphase(jm) > 0) THEN
          DO jl = 1, kfdia
            zlcust(jl, jm) = zmf(jl) * zqxnm1(jl, jm)
            zconvsrce(jl, jm) = zconvsrce(jl, jm) + zlcust(jl, jm)
          END DO
        END IF
      END DO
      DO jl = 1, kfdia
        zdtdp = zrdcp * 0.5D0 * (ztp1(jl, jk - 1) + ztp1(jl, jk)) / paph(jl, jk)
        zdtforc = zdtdp * (pap(jl, jk) - pap(jl, jk - 1))
        zdqs(jl) = zanewm1(jl) * zdtforc * zdqsmixdt(jl)
      END DO
      DO jm = 1, 5
        IF (.NOT. llfall(jm) .AND. iphase(jm) > 0) THEN
          DO jl = 1, kfdia
            zlfinal = MAX(0.0D0, zlcust(jl, jm) - zdqs(jl))
            zevap = MIN((zlcust(jl, jm) - zlfinal), zevaplimmix(jl))
            zlfinal = zlcust(jl, jm) - zevap
            zlfinalsum(jl) = zlfinalsum(jl) + zlfinal
            zsolqa(jl, jm, jm) = zsolqa(jl, jm, jm) + zlcust(jl, jm)
            zsolqa(jl, 5, jm) = zsolqa(jl, 5, jm) + zevap
            zsolqa(jl, jm, 5) = zsolqa(jl, jm, 5) - zevap
          END DO
        END IF
      END DO
      DO jl = 1, kfdia
        IF (zlfinalsum(jl) < 1D-14) zacust(jl) = 0.0D0
        zsolac(jl) = zsolac(jl) + zacust(jl)
      END DO
    END IF
    DO jl = 1, kfdia
      IF (jk < klev) THEN
        zmfdn = MAX(0.0D0, (pmfu(jl, jk + 1) + pmfd(jl, jk + 1)) * zdtgdp(jl))
        zsolab(jl) = zsolab(jl) + zmfdn
        zsolqb(jl, 1, 1) = zsolqb(jl, 1, 1) + zmfdn
        zsolqb(jl, 2, 2) = zsolqb(jl, 2, 2) + zmfdn
        zconvsink(jl, 1) = zmfdn
        zconvsink(jl, 2) = zmfdn
      END IF
    END DO
    DO jl = 1, kfdia
      zldifdt(jl) = ydecldp % rcldiff * ptsphy
      IF (ktype(jl) > 0 .AND. plude(jl, jk) > 1D-14) zldifdt(jl) = ydecldp % rcldiff_convi * zldifdt(jl)
    END DO
    DO jl = 1, kfdia
      IF (zli(jl, jk) > 1D-14) THEN
        ze = zldifdt(jl) * MAX(zqsmix(jl, jk) - zqx(jl, jk, 5), 0.0D0)
        zleros = za(jl, jk) * ze
        zleros = MIN(zleros, zevaplimmix(jl))
        zleros = MIN(zleros, zli(jl, jk))
        zaeros = zleros / zlicld(jl)
        zsolac(jl) = zsolac(jl) - zaeros
        zsolqa(jl, 5, 1) = zsolqa(jl, 5, 1) + zliqfrac(jl, jk) * zleros
        zsolqa(jl, 1, 5) = zsolqa(jl, 1, 5) - zliqfrac(jl, jk) * zleros
        zsolqa(jl, 5, 2) = zsolqa(jl, 5, 2) + zicefrac(jl, jk) * zleros
        zsolqa(jl, 2, 5) = zsolqa(jl, 2, 5) - zicefrac(jl, jk) * zleros
      END IF
    END DO
    DO jl = 1, kfdia
      zdtdp = zrdcp * ztp1(jl, jk) / pap(jl, jk)
      zdpmxdt = zdp(jl) * zqtmst
      zmfdn = 0.0D0
      IF (jk < klev) zmfdn = pmfu(jl, jk + 1) + pmfd(jl, jk + 1)
      zwtot = pvervel(jl, jk) + 0.5D0 * ydcst % rg * (pmfu(jl, jk) + pmfd(jl, jk) + zmfdn)
      zwtot = MIN(zdpmxdt, MAX(- zdpmxdt, zwtot))
      zzzdt = phrsw(jl, jk) + phrlw(jl, jk)
      zdtdiab = MIN(zdpmxdt * zdtdp, MAX(- zdpmxdt * zdtdp, zzzdt)) * ptsphy + ydthf % ralfdcp * zldefr(jl)
      zdtforc = zdtdp * zwtot * ptsphy + zdtdiab
      zqold(jl) = zqsmix(jl, jk)
      ztold(jl) = ztp1(jl, jk)
      ztp1(jl, jk) = ztp1(jl, jk) + zdtforc
      ztp1(jl, jk) = MAX(ztp1(jl, jk), 160.0D0)
      llflag(jl) = .TRUE.
    END DO
    DO jl = 1, kfdia
      zqp = 1.0D0 / pap(jl, jk)
      oka = ztp1(jl, jk)
      zqsat = foeewm(oka, ydthf, ydcst) * zqp
      zqsat = MIN(0.5D0, zqsat)
      zcor = 1.0D0 / (1.0D0 - ydcst % retv * zqsat)
      zqsat = zqsat * zcor
      oka = ztp1(jl, jk)
      zcond = (zqsmix(jl, jk) - zqsat) / (1.0D0 + zqsat * zcor * foedem(oka, ydthf))
      oka = ztp1(jl, jk)
      ztp1(jl, jk) = ztp1(jl, jk) + foeldcpm(oka, ydthf) * zcond
      zqsmix(jl, jk) = zqsmix(jl, jk) - zcond
      oka = ztp1(jl, jk)
      zqsat = foeewm(oka, ydthf, ydcst) * zqp
      zqsat = MIN(0.5D0, zqsat)
      zcor = 1.0D0 / (1.0D0 - ydcst % retv * zqsat)
      zqsat = zqsat * zcor
      oka = ztp1(jl, jk)
      zcond1 = (zqsmix(jl, jk) - zqsat) / (1.0D0 + zqsat * zcor * foedem(oka, ydthf))
      oka = ztp1(jl, jk)
      ztp1(jl, jk) = ztp1(jl, jk) + foeldcpm(oka, ydthf) * zcond1
      zqsmix(jl, jk) = zqsmix(jl, jk) - zcond1
    END DO
    DO jl = 1, kfdia
      zdqs(jl) = zqsmix(jl, jk) - zqold(jl)
      zqsmix(jl, jk) = zqold(jl)
      ztp1(jl, jk) = ztold(jl)
    END DO
    DO jl = 1, kfdia
      IF (zdqs(jl) > 0.0D0) THEN
        zlevap = za(jl, jk) * MIN(zdqs(jl), zlicld(jl))
        zlevap = MIN(zlevap, zevaplimmix(jl))
        zlevap = MIN(zlevap, MAX(zqsmix(jl, jk) - zqx(jl, jk, 5), 0.0D0))
        zlevapl(jl) = zliqfrac(jl, jk) * zlevap
        zlevapi(jl) = zicefrac(jl, jk) * zlevap
        zsolqa(jl, 5, 1) = zsolqa(jl, 5, 1) + zliqfrac(jl, jk) * zlevap
        zsolqa(jl, 1, 5) = zsolqa(jl, 1, 5) - zliqfrac(jl, jk) * zlevap
        zsolqa(jl, 5, 2) = zsolqa(jl, 5, 2) + zicefrac(jl, jk) * zlevap
        zsolqa(jl, 2, 5) = zsolqa(jl, 2, 5) - zicefrac(jl, jk) * zlevap
      END IF
    END DO
    DO jl = 1, kfdia
      IF (za(jl, jk) > 1D-14 .AND. zdqs(jl) <= - ydecldp % rlmin) THEN
        zlcond1(jl) = MAX(- zdqs(jl), 0.0D0)
        IF (za(jl, jk) > 0.99D0) THEN
          zcor = 1.0D0 / (1.0D0 - ydcst % retv * zqsmix(jl, jk))
          oka = ztp1(jl, jk)
          zcdmax = (zqx(jl, jk, 5) - zqsmix(jl, jk)) / (1.0D0 + zcor * zqsmix(jl, jk) * foedem(oka, ydthf))
        ELSE
          zcdmax = (zqx(jl, jk, 5) - za(jl, jk) * zqsmix(jl, jk)) / za(jl, jk)
        END IF
        zlcond1(jl) = MAX(MIN(zlcond1(jl), zcdmax), 0.0D0)
        zlcond1(jl) = za(jl, jk) * zlcond1(jl)
        IF (zlcond1(jl) < ydecldp % rlmin) zlcond1(jl) = 0.0D0
        IF (ztp1(jl, jk) > ydecldp % rthomo) THEN
          zsolqa(jl, 1, 5) = zsolqa(jl, 1, 5) + zlcond1(jl)
          zsolqa(jl, 5, 1) = zsolqa(jl, 5, 1) - zlcond1(jl)
          zqxfg(jl, 1) = zqxfg(jl, 1) + zlcond1(jl)
        ELSE
          zsolqa(jl, 2, 5) = zsolqa(jl, 2, 5) + zlcond1(jl)
          zsolqa(jl, 5, 2) = zsolqa(jl, 5, 2) - zlcond1(jl)
          zqxfg(jl, 2) = zqxfg(jl, 2) + zlcond1(jl)
        END IF
      END IF
    END DO
    DO jl = 1, kfdia
      IF (zdqs(jl) <= - ydecldp % rlmin .AND. za(jl, jk) < 0.99999999999999D0) THEN
        zrhc = ydecldp % ramid
        zsigk = pap(jl, jk) / paph(jl, klev + 1)
        IF (zsigk > 0.8D0) THEN
          zrhc = ydecldp % ramid + (1.0D0 - ydecldp % ramid) * ((zsigk - 0.8D0) / 0.2D0) ** 2
        END IF
        IF (ydecldp % nssopt == 0) THEN
          zqe = (zqx(jl, jk, 5) - za(jl, jk) * zqsice(jl, jk)) / MAX(zepsec, 1.0D0 - za(jl, jk))
          zqe = MAX(0.0D0, zqe)
        ELSE IF (ydecldp % nssopt == 1) THEN
          zqe = (zqx(jl, jk, 5) - za(jl, jk) * zqsice(jl, jk)) / MAX(zepsec, 1.0D0 - za(jl, jk))
          zqe = MAX(0.0D0, zqe)
        ELSE IF (ydecldp % nssopt == 2) THEN
          zqe = zqx(jl, jk, 5)
        ELSE IF (ydecldp % nssopt == 3) THEN
          zqe = zqx(jl, jk, 5) + zli(jl, jk)
        END IF
        IF (ztp1(jl, jk) >= ydcst % rtt .OR. ydecldp % nssopt == 0) THEN
          zfac = 1.0D0
        ELSE
          zfac = zfokoop(jl)
        END IF
        IF (zqe >= zrhc * zqsice(jl, jk) * zfac .AND. zqe < zqsice(jl, jk) * zfac) THEN
          zacond = - (1.0D0 - za(jl, jk)) * zfac * zdqs(jl) / MAX(2.0D0 * (zfac * zqsice(jl, jk) - zqe), zepsec)
          zacond = MIN(zacond, 1.0D0 - za(jl, jk))
          zlcond2(jl) = - zfac * zdqs(jl) * 0.5D0 * zacond
          zzdl = 2.0D0 * (zfac * zqsice(jl, jk) - zqe) / MAX(zepsec, 1.0D0 - za(jl, jk))
          IF (zfac * zdqs(jl) < - zzdl) THEN
            zlcondlim = (za(jl, jk) - 1.0D0) * zfac * zdqs(jl) - zfac * zqsice(jl, jk) + zqx(jl, jk, 5)
            zlcond2(jl) = MIN(zlcond2(jl), zlcondlim)
          END IF
          zlcond2(jl) = MAX(zlcond2(jl), 0.0D0)
          IF (zlcond2(jl) < ydecldp % rlmin .OR. (1.0D0 - za(jl, jk)) < 1D-14) THEN
            zlcond2(jl) = 0.0D0
            zacond = 0.0D0
          END IF
          IF (zlcond2(jl) == 0.0D0) zacond = 0.0D0
          zsolac(jl) = zsolac(jl) + zacond
          IF (ztp1(jl, jk) > ydecldp % rthomo) THEN
            zsolqa(jl, 1, 5) = zsolqa(jl, 1, 5) + zlcond2(jl)
            zsolqa(jl, 5, 1) = zsolqa(jl, 5, 1) - zlcond2(jl)
            zqxfg(jl, 1) = zqxfg(jl, 1) + zlcond2(jl)
          ELSE
            zsolqa(jl, 2, 5) = zsolqa(jl, 2, 5) + zlcond2(jl)
            zsolqa(jl, 5, 2) = zsolqa(jl, 5, 2) - zlcond2(jl)
            zqxfg(jl, 2) = zqxfg(jl, 2) + zlcond2(jl)
          END IF
        END IF
      END IF
    END DO
    DO jl = 1, kfdia
      IF (za(jl, jk - 1) < ydecldp % rcldtopcf .AND. za(jl, jk) >= ydecldp % rcldtopcf) THEN
        zcldtopdist(jl) = 0.0D0
      ELSE
        zcldtopdist(jl) = zcldtopdist(jl) + zdp(jl) / (zrho(jl) * ydcst % rg)
      END IF
      IF (ztp1(jl, jk) < ydcst % rtt .AND. zqxfg(jl, 1) > ydecldp % rlmin) THEN
        oka = ztp1(jl, jk)
        zvpice = foeeice(oka, ydthf, ydcst) * ydcst % rv / ydcst % rd
        zvpliq = zvpice * zfokoop(jl)
        zicenuclei(jl) = 1000.0D0 * EXP(12.96D0 * (zvpliq - zvpice) / zvpliq - 0.639D0)
        zadd = ydcst % rlstt * (ydcst % rlstt / (ydcst % rv * ztp1(jl, jk)) - 1.0D0) / (0.024D0 * ztp1(jl, jk))
        zbdd = ydcst % rv * ztp1(jl, jk) * pap(jl, jk) / (2.21D0 * zvpice)
        zcvds = 7.8D0 * (zicenuclei(jl) / zrho(jl)) ** 0.666D0 * (zvpliq - zvpice) / (8.87D0 * (zadd + zbdd) * zvpice)
        zice0 = MAX(zicecld(jl), zicenuclei(jl) * ydecldp % riceinit / zrho(jl))
        zinew = (0.666D0 * zcvds * ptsphy + zice0 ** 0.666D0) ** 1.5D0
        zdepos = MAX(za(jl, jk) * (zinew - zice0), 0.0D0)
        zdepos = MIN(zdepos, zqxfg(jl, 1))
        zinfactor = MIN(zicenuclei(jl) / 15000.0D0, 1.0D0)
        zdepos = zdepos * MIN(zinfactor + (1.0D0 - zinfactor) * (ydecldp % rdepliqrefrate + zcldtopdist(jl) / ydecldp % rdepliqrefdepth), 1.0D0)
        zsolqa(jl, 2, 1) = zsolqa(jl, 2, 1) + zdepos
        zsolqa(jl, 1, 2) = zsolqa(jl, 1, 2) - zdepos
        zqxfg(jl, 2) = zqxfg(jl, 2) + zdepos
        zqxfg(jl, 1) = zqxfg(jl, 1) - zdepos
      END IF
    END DO
    DO jl = 1, kfdia
      ztmpa = 1.0D0 / MAX(za(jl, jk), zepsec)
      zliqcld(jl) = zqxfg(jl, 1) * ztmpa
      zicecld(jl) = zqxfg(jl, 2) * ztmpa
      zlicld(jl) = zliqcld(jl) + zicecld(jl)
    END DO
    DO jm = 1, 5
      IF (llfall(jm) .OR. jm == 2) THEN
        DO jl = 1, kfdia
          IF (jk > ydecldp % ncldtop) THEN
            zfallsrce(jl, jm) = zpfplsx(jl, jk, jm) * zdtgdp(jl)
            zsolqa(jl, jm, jm) = zsolqa(jl, jm, jm) + zfallsrce(jl, jm)
            zqxfg(jl, jm) = zqxfg(jl, jm) + zfallsrce(jl, jm)
            zqpretot(jl) = zqpretot(jl) + zqxfg(jl, jm)
          END IF
          IF (ydecldp % laericesed .AND. jm == 2) THEN
            zre_ice = pre_ice(jl, jk)
            zvqx(2) = 0.002D0 * zre_ice ** 1.0D0
          END IF
          zfall = zvqx(jm) * zrho(jl)
          zfallsink(jl, jm) = zdtgdp(jl) * zfall
        END DO
      END IF
    END DO
    DO jl = 1, kfdia
      IF (zqpretot(jl) > 1D-14) THEN
        zcovptot(jl) = 1.0D0 - ((1.0D0 - zcovptot(jl)) * (1.0D0 - MAX(za(jl, jk), za(jl, jk - 1))) / (1.0D0 - MIN(za(jl, jk - 1), 0.999999D0)))
        zcovptot(jl) = MAX(zcovptot(jl), ydecldp % rcovpmin)
        zcovpclr(jl) = MAX(0.0D0, zcovptot(jl) - za(jl, jk))
        zraincld(jl) = zqxfg(jl, 3) / zcovptot(jl)
        zsnowcld(jl) = zqxfg(jl, 4) / zcovptot(jl)
        zcovpmax(jl) = MAX(zcovptot(jl), zcovpmax(jl))
      ELSE
        zraincld(jl) = 0.0D0
        zsnowcld(jl) = 0.0D0
        zcovptot(jl) = 0.0D0
        zcovpclr(jl) = 0.0D0
        zcovpmax(jl) = 0.0D0
      END IF
    END DO
    DO jl = 1, kfdia
      IF (ztp1(jl, jk) <= ydcst % rtt) THEN
        IF (zicecld(jl) > 1D-14) THEN
          zzco = ptsphy * ydecldp % rsnowlin1 * EXP(ydecldp % rsnowlin2 * (ztp1(jl, jk) - ydcst % rtt))
          IF (ydecldp % laericeauto) THEN
            zlcrit = picrit_aer(jl, jk)
            zzco = zzco * (ydecldp % rnice / pnice(jl, jk)) ** 0.333D0
          ELSE
            zlcrit = ydecldp % rlcritsnow
          END IF
          zsnowaut(jl) = zzco * (1.0D0 - EXP(- (zicecld(jl) / zlcrit) ** 2))
          zsolqb(jl, 4, 2) = zsolqb(jl, 4, 2) + zsnowaut(jl)
        END IF
      END IF
      IF (zliqcld(jl) > 1D-14) THEN
        IF (plsm(jl) > 0.5D0) THEN
          zconst = ydecldp % rcl_kk_cloud_num_land
          zlcrit = ydecldp % rclcrit_land
        ELSE
          zconst = ydecldp % rcl_kk_cloud_num_sea
          zlcrit = ydecldp % rclcrit_sea
        END IF
        IF (zliqcld(jl) > zlcrit) THEN
          zrainaut(jl) = 1.5D0 * za(jl, jk) * ptsphy * ydecldp % rcl_kkaau * zliqcld(jl) ** ydecldp % rcl_kkbauq * zconst ** ydecldp % rcl_kkbaun
          zrainaut(jl) = MIN(zrainaut(jl), zqxfg(jl, 1))
          IF (zrainaut(jl) < 1D-14) zrainaut(jl) = 0.0D0
          zrainacc(jl) = 2.0D0 * za(jl, jk) * ptsphy * ydecldp % rcl_kkaac * (zliqcld(jl) * zraincld(jl)) ** ydecldp % rcl_kkbac
          zrainacc(jl) = MIN(zrainacc(jl), zqxfg(jl, 1))
          IF (zrainacc(jl) < 1D-14) zrainacc(jl) = 0.0D0
        ELSE
          zrainaut(jl) = 0.0D0
          zrainacc(jl) = 0.0D0
        END IF
        IF (ztp1(jl, jk) <= ydcst % rtt) THEN
          zsolqa(jl, 4, 1) = zsolqa(jl, 4, 1) + zrainaut(jl)
          zsolqa(jl, 4, 1) = zsolqa(jl, 4, 1) + zrainacc(jl)
          zsolqa(jl, 1, 4) = zsolqa(jl, 1, 4) - zrainaut(jl)
          zsolqa(jl, 1, 4) = zsolqa(jl, 1, 4) - zrainacc(jl)
        ELSE
          zsolqa(jl, 3, 1) = zsolqa(jl, 3, 1) + zrainaut(jl)
          zsolqa(jl, 3, 1) = zsolqa(jl, 3, 1) + zrainacc(jl)
          zsolqa(jl, 1, 3) = zsolqa(jl, 1, 3) - zrainaut(jl)
          zsolqa(jl, 1, 3) = zsolqa(jl, 1, 3) - zrainacc(jl)
        END IF
      END IF
    END DO
    DO jl = 1, kfdia
      IF (ztp1(jl, jk) <= ydcst % rtt .AND. zliqcld(jl) > 1D-14) THEN
        zfallcorr = (ydecldp % rdensref / zrho(jl)) ** 0.4D0
        IF (zsnowcld(jl) > 1D-14 .AND. zcovptot(jl) > 0.01D0) THEN
          zsnowrime(jl) = 0.3D0 * zcovptot(jl) * ptsphy * ydecldp % rcl_const7s * zfallcorr * (zrho(jl) * zsnowcld(jl) * ydecldp % rcl_const1s) ** ydecldp % rcl_const8s
          zsnowrime(jl) = MIN(zsnowrime(jl), 1.0D0)
          zsolqb(jl, 4, 1) = zsolqb(jl, 4, 1) + zsnowrime(jl)
        END IF
      END IF
    END DO
    DO jl = 1, kfdia
      zicetot(jl) = zqxfg(jl, 2) + zqxfg(jl, 4)
      zmeltmax(jl) = 0.0D0
      IF (zicetot(jl) > 1D-14 .AND. ztp1(jl, jk) > ydcst % rtt) THEN
        zsubsat = MAX(zqsice(jl, jk) - zqx(jl, jk, 5), 0.0D0)
        ztdmtw0 = ztp1(jl, jk) - ydcst % rtt - zsubsat * (1329.31D0 + 0.0074615D0 * (pap(jl, jk) - 85000.0D0) - 40.637D0 * (ztp1(jl, jk) - 275.0D0))
        zcons1 = ABS(ptsphy * (1.0D0 + 0.5D0 * ztdmtw0) / ydecldp % rtaumel)
        zmeltmax(jl) = MAX(ztdmtw0 * zcons1 * zrldcp, 0.0D0)
      END IF
    END DO
    DO jm = 1, 5
      IF (iphase(jm) == 2) THEN
        jnn = imelt(jm)
        DO jl = 1, kfdia
          IF (zmeltmax(jl) > 1D-14 .AND. zicetot(jl) > 1D-14) THEN
            zalfa = zqxfg(jl, jm) / zicetot(jl)
            zmelt = MIN(zqxfg(jl, jm), zalfa * zmeltmax(jl))
            zqxfg(jl, jm) = zqxfg(jl, jm) - zmelt
            zqxfg(jl, jnn) = zqxfg(jl, jnn) + zmelt
            zsolqa(jl, jnn, jm) = zsolqa(jl, jnn, jm) + zmelt
            zsolqa(jl, jm, jnn) = zsolqa(jl, jm, jnn) - zmelt
          END IF
        END DO
      END IF
    END DO
    DO jl = 1, kfdia
      IF (zqx(jl, jk, 3) > 1D-14) THEN
        IF (ztp1(jl, jk) <= ydcst % rtt .AND. ztp1(jl, jk - 1) > ydcst % rtt) THEN
          zqpretot(jl) = MAX(zqx(jl, jk, 4) + zqx(jl, jk, 3), zepsec)
          prainfrac_toprfz(jl) = zqx(jl, jk, 3) / zqpretot(jl)
          IF (prainfrac_toprfz(jl) > 0.8) THEN
            llrainliq(jl) = .TRUE.
          ELSE
            llrainliq(jl) = .FALSE.
          END IF
        END IF
        IF (ztp1(jl, jk) < ydcst % rtt) THEN
          IF (llrainliq(jl)) THEN
            zlambda = (ydecldp % rcl_fac1 / (zrho(jl) * zqx(jl, jk, 3))) ** ydecldp % rcl_fac2
            ztemp = ydecldp % rcl_fzrab * (ztp1(jl, jk) - ydcst % rtt)
            zfrz = ptsphy * (ydecldp % rcl_const5r / zrho(jl)) * (EXP(ztemp) - 1.0D0) * zlambda ** ydecldp % rcl_const6r
            zfrzmax(jl) = MAX(zfrz, 0.0D0)
          ELSE
            zcons1 = ABS(ptsphy * (1.0D0 + 0.5D0 * (ydcst % rtt - ztp1(jl, jk))) / ydecldp % rtaumel)
            zfrzmax(jl) = MAX((ydcst % rtt - ztp1(jl, jk)) * zcons1 * zrldcp, 0.0D0)
          END IF
          IF (zfrzmax(jl) > 1D-14) THEN
            zfrz = MIN(zqx(jl, jk, 3), zfrzmax(jl))
            zsolqa(jl, 4, 3) = zsolqa(jl, 4, 3) + zfrz
            zsolqa(jl, 3, 4) = zsolqa(jl, 3, 4) - zfrz
          END IF
        END IF
      END IF
    END DO
    DO jl = 1, kfdia
      zfrzmax(jl) = MAX((ydecldp % rthomo - ztp1(jl, jk)) * zrldcp, 0.0D0)
    END DO
    jm = 1
    jnn = imelt(jm)
    DO jl = 1, kfdia
      IF (zfrzmax(jl) > 1D-14 .AND. zqxfg(jl, jm) > 1D-14) THEN
        zfrz = MIN(zqxfg(jl, jm), zfrzmax(jl))
        zsolqa(jl, jnn, jm) = zsolqa(jl, jnn, jm) + zfrz
        zsolqa(jl, jm, jnn) = zsolqa(jl, jm, jnn) - zfrz
      END IF
    END DO
    DO jl = 1, kfdia
      zzrh = ydecldp % rprecrhmax + (1.0D0 - ydecldp % rprecrhmax) * zcovpmax(jl) / MAX(zepsec, 1.0D0 - za(jl, jk))
      zzrh = MIN(MAX(zzrh, ydecldp % rprecrhmax), 1.0D0)
      zzrh = MIN(0.8D0, zzrh)
      zqe = MAX(0.0D0, MIN(zqx(jl, jk, 5), zqsliq(jl, jk)))
      llo1 = zcovpclr(jl) > 1D-14 .AND. zqxfg(jl, 3) > 1D-14 .AND. zqe < zzrh * zqsliq(jl, jk)
      IF (llo1) THEN
        zpreclr = zqxfg(jl, 3) / zcovptot(jl)
        zfallcorr = (ydecldp % rdensref / zrho(jl)) ** 0.4D0
        oka = ztp1(jl, jk)
        zesatliq = ydcst % rv / ydcst % rd * foeeliq(oka, ydthf, ydcst)
        zlambda = (ydecldp % rcl_fac1 / (zrho(jl) * zpreclr)) ** ydecldp % rcl_fac2
        zevap_denom = ydecldp % rcl_cdenom1 * zesatliq - ydecldp % rcl_cdenom2 * ztp1(jl, jk) * zesatliq + ydecldp % rcl_cdenom3 * ztp1(jl, jk) ** 3.0D0 * pap(jl, jk)
        zcorr2 = (ztp1(jl, jk) / 273.0D0) ** 1.5D0 * 393.0D0 / (ztp1(jl, jk) + 120.0D0)
        zka = ydecldp % rcl_ka273 * zcorr2
        zsubsat = MAX(zzrh * zqsliq(jl, jk) - zqe, 0.0D0)
        zbeta = (0.5D0 / zqsliq(jl, jk)) * ztp1(jl, jk) ** 2.0D0 * zesatliq * ydecldp % rcl_const1r * (zcorr2 / zevap_denom) * (0.78D0 / (zlambda ** ydecldp % rcl_const4r) + ydecldp % rcl_const2r * (zrho(jl) * zfallcorr) ** 0.5D0 / (zcorr2 ** 0.5D0 * zlambda ** ydecldp % rcl_const3r))
        zdenom = 1.0D0 + zbeta * ptsphy
        zdpevap = zcovpclr(jl) * zbeta * ptsphy * zsubsat / zdenom
        zevap = MIN(zdpevap, zqxfg(jl, 3))
        zsolqa(jl, 5, 3) = zsolqa(jl, 5, 3) + zevap
        zsolqa(jl, 3, 5) = zsolqa(jl, 3, 5) - zevap
        zcovptot(jl) = MAX(ydecldp % rcovpmin, zcovptot(jl) - MAX(0.0D0, (zcovptot(jl) - za(jl, jk)) * zevap / zqxfg(jl, 3)))
        zqxfg(jl, 3) = zqxfg(jl, 3) - zevap
      END IF
    END DO
    DO jl = 1, kfdia
      zzrh = ydecldp % rprecrhmax + (1.0D0 - ydecldp % rprecrhmax) * zcovpmax(jl) / MAX(zepsec, 1.0D0 - za(jl, jk))
      zzrh = MIN(MAX(zzrh, ydecldp % rprecrhmax), 1.0D0)
      zqe = (zqx(jl, jk, 5) - za(jl, jk) * zqsice(jl, jk)) / MAX(zepsec, 1.0D0 - za(jl, jk))
      zqe = MAX(0.0D0, MIN(zqe, zqsice(jl, jk)))
      llo1 = zcovpclr(jl) > 1D-14 .AND. zqxfg(jl, 4) > 1D-14 .AND. zqe < zzrh * zqsice(jl, jk)
      IF (llo1) THEN
        zpreclr = zqxfg(jl, 4) * zcovpclr(jl) / SIGN(MAX(ABS(zcovptot(jl) * zdtgdp(jl)), zepsilon), zcovptot(jl) * zdtgdp(jl))
        zbeta1 = SQRT(pap(jl, jk) / paph(jl, klev + 1)) / ydecldp % rvrfactor * zpreclr / MAX(zcovpclr(jl), zepsec)
        zbeta = ydcst % rg * ydecldp % rpecons * (zbeta1) ** 0.5777D0
        zdenom = 1.0D0 + zbeta * ptsphy * zcorqsice(jl)
        zdpr = zcovpclr(jl) * zbeta * (zqsice(jl, jk) - zqe) / zdenom * zdp(jl) * zrg_r
        zdpevap = zdpr * zdtgdp(jl)
        zevap = MIN(zdpevap, zqxfg(jl, 4))
        zsolqa(jl, 5, 4) = zsolqa(jl, 5, 4) + zevap
        zsolqa(jl, 4, 5) = zsolqa(jl, 4, 5) - zevap
        zcovptot(jl) = MAX(ydecldp % rcovpmin, zcovptot(jl) - MAX(0.0D0, (zcovptot(jl) - za(jl, jk)) * zevap / zqxfg(jl, 4)))
        zqxfg(jl, 4) = zqxfg(jl, 4) - zevap
      END IF
    END DO
    DO jm = 1, 5
      IF (llfall(jm)) THEN
        DO jl = 1, kfdia
          IF (zqxfg(jl, jm) < ydecldp % rlmin) THEN
            zsolqa(jl, 5, jm) = zsolqa(jl, 5, jm) + zqxfg(jl, jm)
            zsolqa(jl, jm, 5) = zsolqa(jl, jm, 5) - zqxfg(jl, jm)
          END IF
        END DO
      END IF
    END DO
    DO jl = 1, kfdia
      zanew = (za(jl, jk) + zsolac(jl)) / (1.0D0 + zsolab(jl))
      zanew = MIN(zanew, 1.0D0)
      IF (zanew < ydecldp % ramin) zanew = 0.0D0
      zda(jl) = zanew - zaorig(jl, jk)
      zanewm1(jl) = zanew
    END DO
    DO jm = 1, 5
      DO jnn = 1, 5
        DO jl = 1, kfdia
          llindex3(jl, jnn, jm) = .FALSE.
        END DO
      END DO
      DO jl = 1, kfdia
        zsinksum(jl, jm) = 0.0D0
      END DO
    END DO
    DO jm = 1, 5
      DO jnn = 1, 5
        DO jl = 1, kfdia
          zsinksum(jl, jm) = zsinksum(jl, jm) - zsolqa(jl, jm, jnn)
        END DO
      END DO
    END DO
    DO jm = 1, 5
      DO jl = 1, kfdia
        zmax = MAX(zqx(jl, jk, jm), zepsec)
        zrat = MAX(zsinksum(jl, jm), zmax)
        zratio(jl, jm) = zmax / zrat
      END DO
    END DO
    DO jm = 1, 5
      DO jl = 1, kfdia
        iorder(jl, jm) = -999
      END DO
    END DO
    DO jnn = 1, 5
      DO jl = 1, kfdia
        llindex1(jl, jnn) = .TRUE.
      END DO
    END DO
    DO jm = 1, 5
      DO jl = 1, kfdia
        zmin(jl) = 1D+32
      END DO
      DO jnn = 1, 5
        DO jl = 1, kfdia
          IF (llindex1(jl, jnn) .AND. zratio(jl, jnn) < zmin(jl)) THEN
            iorder(jl, jm) = jnn
            zmin(jl) = zratio(jl, jnn)
          END IF
        END DO
      END DO
      DO jl = 1, kfdia
        llindex1(jl, iorder(jl, jm)) = .FALSE.
      END DO
    END DO
    DO jm = 1, 5
      DO jl = 1, kfdia
        zsinksum(jl, jm) = 0.0D0
      END DO
    END DO
    DO jm = 1, 5
      DO jl = 1, kfdia
        jo = iorder(jl, jm)
        DO jnn = 1, 5
          llindex3(jl, jo, jnn) = zsolqa(jl, jo, jnn) < 0.0D0
        END DO
        zsinksum(jl, jo) = zsinksum(jl, jo) - SUM(zsolqa(jl, jo, 1 : 5))
      END DO
      DO jl = 1, kfdia
        jo = iorder(jl, jm)
        zmm = MAX(zqx(jl, jk, jo), zepsec)
        zrr = MAX(zsinksum(jl, jo), zmm)
        zratio(jl, jo) = zmm / zrr
      END DO
      DO jl = 1, kfdia
        jo = iorder(jl, jm)
        zzratio = zratio(jl, jo)
        DO jnn = 1, 5
          IF (llindex3(jl, jo, jnn)) THEN
            zsolqa(jl, jo, jnn) = zsolqa(jl, jo, jnn) * zzratio
            zsolqa(jl, jnn, jo) = zsolqa(jl, jnn, jo) * zzratio
          END IF
        END DO
      END DO
    END DO
    DO jm = 1, 5
      DO jnn = 1, 5
        IF (jnn == jm) THEN
          DO jl = 1, kfdia
            zqlhs(jl, jnn, jm) = 1.0D0 + zfallsink(jl, jm)
            DO jo = 1, 5
              zqlhs(jl, jnn, jm) = zqlhs(jl, jnn, jm) + zsolqb(jl, jo, jnn)
            END DO
          END DO
        ELSE
          DO jl = 1, kfdia
            zqlhs(jl, jnn, jm) = - zsolqb(jl, jnn, jm)
          END DO
        END IF
      END DO
    END DO
    DO jm = 1, 5
      DO jl = 1, kfdia
        zexplicit = 0.0D0
        DO jnn = 1, 5
          zexplicit = zexplicit + zsolqa(jl, jm, jnn)
        END DO
        zqxn(jl, jm) = zqx(jl, jk, jm) + zexplicit
      END DO
    END DO
    DO jnn = 1, 4
      DO jm = jnn + 1, 5
        zqlhs(1 : kfdia, jm, jnn) = zqlhs(1 : kfdia, jm, jnn) / zqlhs(1 : kfdia, jnn, jnn)
        DO ik = jnn + 1, 5
          DO jl = 1, kfdia
            zqlhs(jl, jm, ik) = zqlhs(jl, jm, ik) - zqlhs(jl, jm, jnn) * zqlhs(jl, jnn, ik)
          END DO
        END DO
      END DO
    END DO
    DO jnn = 2, 5
      DO jm = 1, jnn - 1
        zqxn(1 : kfdia, jnn) = zqxn(1 : kfdia, jnn) - zqlhs(1 : kfdia, jnn, jm) * zqxn(1 : kfdia, jm)
      END DO
    END DO
    zqxn(1 : kfdia, 5) = zqxn(1 : kfdia, 5) / zqlhs(1 : kfdia, 5, 5)
    DO jnn = 4, 1, - 1
      DO jm = jnn + 1, 5
        zqxn(1 : kfdia, jnn) = zqxn(1 : kfdia, jnn) - zqlhs(1 : kfdia, jnn, jm) * zqxn(1 : kfdia, jm)
      END DO
      zqxn(1 : kfdia, jnn) = zqxn(1 : kfdia, jnn) / zqlhs(1 : kfdia, jnn, jnn)
    END DO
    DO jnn = 1, 4
      DO jl = 1, kfdia
        IF (zqxn(jl, jnn) < 1D-14) THEN
          zqxn(jl, 5) = zqxn(jl, 5) + zqxn(jl, jnn)
          zqxn(jl, jnn) = 0.0D0
        END IF
      END DO
    END DO
    DO jm = 1, 5
      DO jl = 1, kfdia
        zqxnm1(jl, jm) = zqxn(jl, jm)
        zqxn2d(jl, jk, jm) = zqxn(jl, jm)
      END DO
    END DO
    DO jm = 1, 5
      DO jl = 1, kfdia
        zpfplsx(jl, jk + 1, jm) = zfallsink(jl, jm) * zqxn(jl, jm) * zrdtgdp(jl)
      END DO
    END DO
    DO jl = 1, kfdia
      zqpretot(jl) = zpfplsx(jl, jk + 1, 4) + zpfplsx(jl, jk + 1, 3)
    END DO
    DO jl = 1, kfdia
      IF (zqpretot(jl) < 1D-14) THEN
        zcovptot(jl) = 0.0D0
      END IF
    END DO
    DO jm = 1, 4
      DO jl = 1, kfdia
        zfluxq(jl, jm) = zpsupsatsrce(jl, jm) + zconvsrce(jl, jm) + zfallsrce(jl, jm) - (zfallsink(jl, jm) + zconvsink(jl, jm)) * zqxn(jl, jm)
      END DO
      IF (iphase(jm) == 1) THEN
        DO jl = 1, kfdia
          ptendency_loc_t(jl, jk) = ptendency_loc_t(jl, jk) + ydthf % ralvdcp * (zqxn(jl, jm) - zqx(jl, jk, jm) - zfluxq(jl, jm)) * zqtmst
        END DO
      END IF
      IF (iphase(jm) == 2) THEN
        DO jl = 1, kfdia
          ptendency_loc_t(jl, jk) = ptendency_loc_t(jl, jk) + ydthf % ralsdcp * (zqxn(jl, jm) - zqx(jl, jk, jm) - zfluxq(jl, jm)) * zqtmst
        END DO
      END IF
      DO jl = 1, kfdia
        ptendency_loc_cld(jl, jk, jm) = ptendency_loc_cld(jl, jk, jm) + (zqxn(jl, jm) - zqx0(jl, jk, jm)) * zqtmst
      END DO
    END DO
    DO jl = 1, kfdia
      ptendency_loc_q(jl, jk) = ptendency_loc_q(jl, jk) + (zqxn(jl, 5) - zqx(jl, jk, 5)) * zqtmst
      ptendency_loc_a(jl, jk) = ptendency_loc_a(jl, jk) + zda(jl) * zqtmst
    END DO
    DO jl = 1, kfdia
      pcovptot(jl, jk) = zcovptot(jl)
    END DO
  END DO
  DO jk = 1, klev + 1
    DO jl = 1, kfdia
      pfplsl(jl, jk) = zpfplsx(jl, jk, 3) + zpfplsx(jl, jk, 1)
      pfplsn(jl, jk) = zpfplsx(jl, jk, 4) + zpfplsx(jl, jk, 2)
    END DO
  END DO
  DO jl = 1, kfdia
    pfsqlf(jl, 1) = 0.0D0
    pfsqif(jl, 1) = 0.0D0
    pfsqrf(jl, 1) = 0.0D0
    pfsqsf(jl, 1) = 0.0D0
    pfcqlng(jl, 1) = 0.0D0
    pfcqnng(jl, 1) = 0.0D0
    pfcqrng(jl, 1) = 0.0D0
    pfcqsng(jl, 1) = 0.0D0
    pfsqltur(jl, 1) = 0.0D0
    pfsqitur(jl, 1) = 0.0D0
  END DO
  DO jk = 1, klev
    DO jl = 1, kfdia
      zgdph_r = - zrg_r * (paph(jl, jk + 1) - paph(jl, jk)) * zqtmst
      pfsqlf(jl, jk + 1) = pfsqlf(jl, jk)
      pfsqif(jl, jk + 1) = pfsqif(jl, jk)
      pfsqrf(jl, jk + 1) = pfsqlf(jl, jk)
      pfsqsf(jl, jk + 1) = pfsqif(jl, jk)
      pfcqlng(jl, jk + 1) = pfcqlng(jl, jk)
      pfcqnng(jl, jk + 1) = pfcqnng(jl, jk)
      pfcqrng(jl, jk + 1) = pfcqlng(jl, jk)
      pfcqsng(jl, jk + 1) = pfcqnng(jl, jk)
      pfsqltur(jl, jk + 1) = pfsqltur(jl, jk)
      pfsqitur(jl, jk + 1) = pfsqitur(jl, jk)
      zalfaw = zfoealfa(jl, jk)
      pfsqlf(jl, jk + 1) = pfsqlf(jl, jk + 1) + (zqxn2d(jl, jk, 1) - zqx0(jl, jk, 1) + pvfl(jl, jk) * ptsphy - zalfaw * plude(jl, jk)) * zgdph_r
      pfcqlng(jl, jk + 1) = pfcqlng(jl, jk + 1) + zlneg(jl, jk, 1) * zgdph_r
      pfsqltur(jl, jk + 1) = pfsqltur(jl, jk + 1) + pvfl(jl, jk) * ptsphy * zgdph_r
      pfsqrf(jl, jk + 1) = pfsqrf(jl, jk + 1) + (zqxn2d(jl, jk, 3) - zqx0(jl, jk, 3)) * zgdph_r
      pfcqrng(jl, jk + 1) = pfcqrng(jl, jk + 1) + zlneg(jl, jk, 3) * zgdph_r
      pfsqif(jl, jk + 1) = pfsqif(jl, jk + 1) + (zqxn2d(jl, jk, 2) - zqx0(jl, jk, 2) + pvfi(jl, jk) * ptsphy - (1.0D0 - zalfaw) * plude(jl, jk)) * zgdph_r
      pfcqnng(jl, jk + 1) = pfcqnng(jl, jk + 1) + zlneg(jl, jk, 2) * zgdph_r
      pfsqitur(jl, jk + 1) = pfsqitur(jl, jk + 1) + pvfi(jl, jk) * ptsphy * zgdph_r
      pfsqsf(jl, jk + 1) = pfsqsf(jl, jk + 1) + (zqxn2d(jl, jk, 4) - zqx0(jl, jk, 4)) * zgdph_r
      pfcqsng(jl, jk + 1) = pfcqsng(jl, jk + 1) + zlneg(jl, jk, 4) * zgdph_r
    END DO
  END DO
  DO jk = 1, klev + 1
    DO jl = 1, kfdia
      pfhpsl(jl, jk) = - ydcst % rlvtt * pfplsl(jl, jk)
      pfhpsn(jl, jk) = - ydcst % rlstt * pfplsn(jl, jk)
    END DO
  END DO
  CONTAINS
  REAL(KIND = 8) FUNCTION foedelta(ptare, ydcst)
    USE yomcst, ONLY: tomcst
    IMPLICIT NONE
    REAL(KIND = 8), INTENT(IN) :: ptare
    TYPE(tomcst), INTENT(IN) :: ydcst
    foedelta = MAX(0.0D0, SIGN(1.0D0, ptare - ydcst % rtt))
  END FUNCTION foedelta
  REAL(KIND = 8) FUNCTION foealfa(ptare, ydthf)
    USE yoethf, ONLY: toethf
    IMPLICIT NONE
    REAL(KIND = 8), INTENT(IN) :: ptare
    TYPE(toethf), INTENT(IN) :: ydthf
    foealfa = MIN(1.0D0, ((MAX(ydthf % rtice, MIN(ydthf % rtwat, ptare)) - ydthf % rtice) * ydthf % rtwat_rtice_r) ** 2)
  END FUNCTION foealfa
  REAL(KIND = 8) FUNCTION foeewm(ptare, ydthf, ydcst)
    USE yoethf, ONLY: toethf
    USE yomcst, ONLY: tomcst
    IMPLICIT NONE
    REAL(KIND = 8), INTENT(IN) :: ptare
    TYPE(toethf), INTENT(IN) :: ydthf
    TYPE(tomcst), INTENT(IN) :: ydcst
    foeewm = ydthf % r2es * (foealfa(ptare, ydthf) * EXP(ydthf % r3les * (ptare - ydcst % rtt) / (ptare - ydthf % r4les)) + (1.0D0 - foealfa(ptare, ydthf)) * EXP(ydthf % r3ies * (ptare - ydcst % rtt) / (ptare - ydthf % r4ies)))
  END FUNCTION foeewm
  REAL(KIND = 8) FUNCTION foedem(ptare, ydthf)
    USE yoethf, ONLY: toethf
    IMPLICIT NONE
    REAL(KIND = 8), INTENT(IN) :: ptare
    TYPE(toethf), INTENT(IN) :: ydthf
    foedem = foealfa(ptare, ydthf) * ydthf % r5alvcp * (1.0D0 / (ptare - ydthf % r4les) ** 2) + (1.0D0 - foealfa(ptare, ydthf)) * ydthf % r5alscp * (1.0D0 / (ptare - ydthf % r4ies) ** 2)
  END FUNCTION foedem
  REAL(KIND = 8) FUNCTION foeldcpm(ptare, ydthf)
    USE yoethf, ONLY: toethf
    IMPLICIT NONE
    REAL(KIND = 8), INTENT(IN) :: ptare
    TYPE(toethf), INTENT(IN) :: ydthf
    foeldcpm = foealfa(ptare, ydthf) * ydthf % ralvdcp + (1.0D0 - foealfa(ptare, ydthf)) * ydthf % ralsdcp
  END FUNCTION foeldcpm
  REAL(KIND = 8) FUNCTION foeeliq(ptare, ydthf, ydcst)
    USE yoethf, ONLY: toethf
    USE yomcst, ONLY: tomcst
    IMPLICIT NONE
    REAL(KIND = 8), INTENT(IN) :: ptare
    TYPE(toethf), INTENT(IN) :: ydthf
    TYPE(tomcst), INTENT(IN) :: ydcst
    foeeliq = ydthf % r2es * EXP(ydthf % r3les * (ptare - ydcst % rtt) / (ptare - ydthf % r4les))
  END FUNCTION foeeliq
  REAL(KIND = 8) FUNCTION foeeice(ptare, ydthf, ydcst)
    USE yoethf, ONLY: toethf
    USE yomcst, ONLY: tomcst
    IMPLICIT NONE
    REAL(KIND = 8), INTENT(IN) :: ptare
    TYPE(toethf), INTENT(IN) :: ydthf
    TYPE(tomcst), INTENT(IN) :: ydcst
    foeeice = ydthf % r2es * EXP(ydthf % r3ies * (ptare - ydcst % rtt) / (ptare - ydthf % r4ies))
  END FUNCTION foeeice
  REAL(KIND = 8) FUNCTION fokoop(ptare, ydthf, ydcst)
    USE yoethf, ONLY: toethf
    USE yomcst, ONLY: tomcst
    IMPLICIT NONE
    REAL(KIND = 8), INTENT(IN) :: ptare
    TYPE(toethf), INTENT(IN) :: ydthf
    TYPE(tomcst), INTENT(IN) :: ydcst
    fokoop = MIN(ydthf % rkoop1 - ydthf % rkoop2 * ptare, foeeliq(ptare, ydthf, ydcst) / foeeice(ptare, ydthf, ydcst))
  END FUNCTION fokoop
END SUBROUTINE cloudsc