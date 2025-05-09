rm velocity_cpu
rm cpu_*.sdfgz
rm *.got
rm *.want
rm -rf .dacecache
python compile_velocity_cpu.py
./velocity_cpu 7
python utils/compare_got_and_want.py 7