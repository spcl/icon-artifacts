cd data_nproma20480
sed -i -e '/# ddt_vn_adv_is_associated/{N;d;}' p_diag.*.data
sed -i -e '/# ddt_vn_cor_is_associated/{N;d;}' p_diag.*.data
sed -i -e '/# ddt_vn_cor_pc/{N;N;d;}' p_diag.*.data
