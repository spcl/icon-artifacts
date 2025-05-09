rm velocity_cpu
rm cpu_*.sdfgz
rm *.got
rm *.want
rm -rf .dacecache
python compile_velocity_cpu.py
./velocity_cpu 1
./velocity_cpu 2
./velocity_cpu 7
./velocity_cpu 9
./velocity_cpu 43
./velocity_cpu 93
./velocity_cpu 463
./velocity_cpu 519
./velocity_cpu 1140
./velocity_cpu 1814
./velocity_cpu 2593
./velocity_cpu 5701
./velocity_cpu 6519
python utils/compare_got_and_want.py 1
python utils/compare_got_and_want.py 2
python utils/compare_got_and_want.py 7
python utils/compare_got_and_want.py 9
python utils/compare_got_and_want.py 43
python utils/compare_got_and_want.py 93
python utils/compare_got_and_want.py 463
python utils/compare_got_and_want.py 519
python utils/compare_got_and_want.py 1140
python utils/compare_got_and_want.py 1814
python utils/compare_got_and_want.py 2593
python utils/compare_got_and_want.py 5701
python utils/compare_got_and_want.py 6591