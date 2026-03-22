cd data_nproma20480

sed -i \
-e '/# ddt_vn_adv_is_associated/{N;d;}' \
-e '/# ddt_vn_cor_is_associated/{N;d;}' \
-e '/# ddt_vn_cor_pc/{N;N;d;}' \
-e '/# vn_ie_ubc/,/# vt/{/# vt/!d;}' \
p_diag.*.data

sed -i \
-e '/# id/{N;d;}' \
-e '/# nlev/{N;d;}' \
-e '/# nlevp1/{N;d;}' \
-e '/# nshift/{N;d;}' \
p_patch.*.data

sed -i \
-e '/# lvert_nest/{N;d;}' \
global_data.*.data
