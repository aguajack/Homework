import csv
from pathlib import Path

import matplotlib.pyplot as plt


ROOT = Path(__file__).resolve().parents[1]
DATA_DIR = ROOT / "data"
CHARTS_DIR = ROOT / "charts"

CHARTS_DIR.mkdir(exist_ok=True)


def read_csv_data(filename):
    path = DATA_DIR / filename

    rows = []

    with path.open("r", encoding="utf-8") as file:
        reader = csv.DictReader(file)

        for row in reader:
            if not row["n"]:
                continue

            try:
                rows.append({
                    "n": int(row["n"]),
                    "insertion_sort": float(row["insertion_sort"]),
                    "quick_sort": float(row["quick_sort"]),
                    "merge_sort": float(row["merge_sort"]),
                    "heap_sort": float(row["heap_sort"]),
                    "composite_sort": float(row["composite_sort"]),
                })
            except ValueError:
                # Skip rows that are not filled yet.
                continue

    return rows


def draw_runtime_chart(csv_filename, output_filename, title):
    rows = read_csv_data(csv_filename)

    if not rows:
        print(f"No valid data found in {csv_filename}.")
        return

    n_values = [row["n"] for row in rows]

    plt.figure(figsize=(10, 6))

    plt.plot(n_values, [row["insertion_sort"] for row in rows], marker="o", label="Insertion Sort")
    plt.plot(n_values, [row["quick_sort"] for row in rows], marker="o", label="Quick Sort")
    plt.plot(n_values, [row["merge_sort"] for row in rows], marker="o", label="Merge Sort")
    plt.plot(n_values, [row["heap_sort"] for row in rows], marker="o", label="Heap Sort")
    plt.plot(n_values, [row["composite_sort"] for row in rows], marker="o", label="Composite Sort")

    plt.xlabel("Input size n")
    plt.ylabel("Runtime (milliseconds)")
    plt.title(title)
    plt.legend()
    plt.grid(True)
    plt.tight_layout()

    output_path = CHARTS_DIR / output_filename
    plt.savefig(output_path, dpi=300)
    plt.close()

    print(f"Saved chart: {output_path}")


def main():
    draw_runtime_chart(
        "worst_case_results.csv",
        "worst_case_chart.png",
        "Worst-Case Runtime Comparison"
    )

    draw_runtime_chart(
        "average_case_results.csv",
        "average_case_chart.png",
        "Average-Case Runtime Comparison"
    )


if __name__ == "__main__":
    main()
