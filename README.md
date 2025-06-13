# PACE 2025 challenge

Submission for the PACE 2025 challenge.

Compile:
```shell
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build --config Release --parallel
cmake --install build --config Release --prefix install
```

Run:
```shell
./install/bin/pace2025_ds_heuristic < heuristic_001.gr
./install/bin/pace2025_hs_heuristic < heuristic_001.hgr
```
