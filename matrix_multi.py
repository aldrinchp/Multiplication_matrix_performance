import argparse, random, time

def gen_matrix(n):
    return [[random.random() for _ in range(n)] for _ in range(n)]

def matmul(A, B):
    n = len(A)
    Bt = list(zip(*B))
    C = [[0.0]*n for _ in range(n)]
    for i in range(n):
        Ai = A[i]
        for j in range(n):
            bj = Bt[j]
            s = 0.0
            for k in range(n):
                s += Ai[k] * bj[k]
            C[i][j] = s
    return C

ap = argparse.ArgumentParser()
ap.add_argument("sizes", nargs="+", type=int)
args = ap.parse_args()

print("| n | GT(s) | CT(s) |")
print("|---:|------:|------:|")
for n in args.sizes:
    random.seed(12345)
    t0 = time.perf_counter(); A = gen_matrix(n); t1 = time.perf_counter()
    gt = (t1 - t0)
    B = gen_matrix(n)
    t0 = time.perf_counter(); C = matmul(A, B); t1 = time.perf_counter()
    ct = (t1 - t0)
    print(f"| {n} | {gt:.6f} | {ct:.6f} |")
