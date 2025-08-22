import argparse, time
import numpy as np

ap = argparse.ArgumentParser()
ap.add_argument("sizes", nargs="+", type=int)
args = ap.parse_args()

print("| n | GT(s) | CT(s) |")
print("|---:|------:|------:|")
for n in args.sizes:
    rng = np.random.default_rng(12345)
    t0 = time.perf_counter(); A = rng.random((n,n), dtype=np.float64); t1 = time.perf_counter()
    gt = (t1 - t0)
    B = rng.random((n,n), dtype=np.float64)
    t0 = time.perf_counter(); C = A @ B; t1 = time.perf_counter()
    ct = (t1 - t0)
    print(f"| {n} | {gt:.6f} | {ct:.6f} |")
