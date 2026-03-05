#!/usr/bin/env python3
"""
Script pour mesurer et afficher le speedup du brute-force OpenMP
en fonction du nombre de threads.
"""

import argparse
import os
import re
import statistics
import subprocess
from pathlib import Path


def parse_total_time_ms(output: str) -> float:
    """Extrait 'Total time: XXX ms' de la sortie du programme."""
    m = re.search(r"Total time:\s*([0-9]+(?:\.[0-9]+)?)\s*ms", output)
    if not m:
        raise RuntimeError(f"Cannot parse 'Total time' in:\n{output}")
    return float(m.group(1))


def run_once(binary: Path, threads: int, input_file: Path) -> float:
    """Lance le programme avec N threads et retourne le temps en ms."""
    cmd = [str(binary), str(threads), str(input_file)]
    result = subprocess.run(cmd, stdout=subprocess.PIPE, stderr=subprocess.PIPE, text=True, check=True)
    return parse_total_time_ms(result.stdout)


def main():
    parser = argparse.ArgumentParser(
        description="Mesure et affiche le speedup du brute-force OpenMP"
    )
    parser.add_argument(
        "--input",
        default="../input_10000_pirecas.txt",
        help="Fichier d'entrée (défaut: ../input_10000_pirecas.txt)",
    )
    parser.add_argument(
        "--binary",
        default="./test",
        help="Chemin vers l'exécutable (défaut: ./test)",
    )
    parser.add_argument(
        "--reps",
        type=int,
        default=5,
        help="Nombre de répétitions (défaut: 5)",
    )
    parser.add_argument(
        "--max-threads",
        type=int,
        default=None,
        help="Max number of threads to test (default: 1024)",
    )
    parser.add_argument(
        "--threads",
        nargs="*",
        type=int,
        help="Threads à tester (ex: --threads 1 2 4 8). Par défaut: 1 2 4 8",
    )

    args = parser.parse_args()

    binary = Path(args.binary).resolve()
    input_file = Path(args.input).resolve()

    if not binary.exists():
        print(f"Binary not found: {binary}")
        return 1

    if not input_file.exists():
        print(f"Input file not found: {input_file}")
        return 1

    # Threads à tester
    if args.threads:
        thread_list = sorted(set(args.threads))
    else:
        max_threads = args.max_threads or 1024
        # Générer 1, 2, 4, 8, 16, 32... jusqu'à max_threads
        thread_list = []
        p = 1
        while p <= max_threads:
            thread_list.append(p)
            p *= 2
        # Ajouter aussi les valeurs intermédiaires jusqu'à cpu_count
        for i in range(1, (os.cpu_count() or 4) + 1):
            thread_list.append(i)
        # Ajouter multiples de cpu_count (2x, 4x, 8x, 16x, 32x, 64x, 128x, 256x)
        cpu_count = os.cpu_count() or 4
        for mult in [2, 4, 8, 16, 32, 64, 128, 256]:
            thread_list.append(cpu_count * mult)
        thread_list = sorted(set([t for t in thread_list if t <= max_threads]))

    print(f"Speedup measurement of OpenMP brute-force")
    print(f"   Binary: {binary}")
    print(f"   Input : {input_file}")
    print(f"   Threads: {thread_list}")
    print(f"   Reps   : {args.reps}")
    print()

    results = {}

    for t in thread_list:
        samples = []
        print(f"  Thread {t}...", end="", flush=True)
        for _ in range(args.reps):
            ms = run_once(binary, t, input_file)
            samples.append(ms)
        
        median = statistics.median(samples)
        mean = statistics.mean(samples)
        stdev = statistics.stdev(samples) if len(samples) >= 2 else 0.0
        cv = (stdev / mean * 100.0) if mean > 0 else 0.0

        results[t] = {
            "median": median,
            "mean": mean,
            "stdev": stdev,
            "cv": cv,
        }
        print(f" {median:.1f}ms (CV={cv:.1f}%)")

    # Calcul speedup et efficacité
    t1_median = results[1]["median"]
    if t1_median <= 0:
        print("Error: 1 thread time is 0ms. Program too fast or too short.")
        print("   Try with a larger input file or increase work.")
        return 1
    
    for t in thread_list:
        tp_median = results[t]["median"]
        if tp_median <= 0:
            # Si temps 0, on considère speedup infini (ou speedup = 1 conservateur)
            speedup = 1.0
        else:
            speedup = t1_median / tp_median
        efficiency = speedup / t
        results[t]["speedup"] = speedup
        results[t]["efficiency"] = efficiency

    # Affichage tableau
    print()
    print("Summary:")
    print("Threads | Median (ms) | Speedup | Efficiency")
    print("--------|-------------|---------|----------")
    for t in thread_list:
        r = results[t]
        print(f"{t:7d} | {r['median']:11.3f} | {r['speedup']:7.3f} | {r['efficiency']:8.1%}")

    # Créer graphique
    try:
        import matplotlib.pyplot as plt

        fig, axes = plt.subplots(1, 3, figsize=(16, 5))

        xs = thread_list
        times = [results[t]["median"] for t in xs]
        speedups = [results[t]["speedup"] for t in xs]
        efficiencies = [results[t]["efficiency"] * 100 for t in xs]
        ideal = xs

        # Graph 1: Time
        axes[0].plot(xs, times, "o-", linewidth=2, markersize=8, color="tab:blue")
        axes[0].set_title("Execution Time vs Threads", fontsize=12, fontweight="bold")
        axes[0].set_xlabel("Number of threads")
        axes[0].set_ylabel("Time (ms)")
        axes[0].grid(True, alpha=0.3)

        # Graph 2: Speedup
        axes[1].plot(xs, speedups, "o-", linewidth=2, markersize=8, label="Measured", color="tab:green")
        axes[1].plot(xs, ideal, "--", linewidth=2, label="Ideal (linear)", color="gray")
        axes[1].set_title("Speedup S(p) = T₁/Tₚ", fontsize=12, fontweight="bold")
        axes[1].set_xlabel("Number of threads")
        axes[1].set_ylabel("Speedup")
        axes[1].grid(True, alpha=0.3)
        axes[1].legend()
        axes[1].set_xscale("log")
        axes[1].set_yscale("log")

        # Graph 3: Efficiency
        axes[2].plot(xs, efficiencies, "o-", linewidth=2, markersize=8, color="tab:orange")
        axes[2].axhline(100, linestyle="--", color="gray", linewidth=1.5, label="Ideal efficiency (100%)")
        axes[2].set_title("Efficiency E(p) = S(p)/p", fontsize=12, fontweight="bold")
        axes[2].set_xlabel("Number of threads")
        axes[2].set_ylabel("Efficiency (%)")
        axes[2].set_ylim([0, max(efficiencies) * 1.1])
        axes[2].grid(True, alpha=0.3)
        axes[2].legend()

        fig.tight_layout()
        plt.show()

    except ImportError:
        print("Matplotlib not available, graph not generated")


if __name__ == "__main__":
    main()
