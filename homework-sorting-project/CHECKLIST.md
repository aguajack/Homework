# 專案可行性測試清單

## 1. 本機測試

### Windows PowerShell

```powershell
g++ -std=c++17 -O2 src/main.cpp src/sorting.cpp src/data_generator.cpp -o sorting_project.exe
./sorting_project.exe
```

成功標準：

```text
Correctness test passed.
All experiments completed.
```

並且產生：

```text
data/worst_case_results.csv
data/average_case_results.csv
```

---

## 2. 產生圖表

```powershell
pip install matplotlib
cd scripts
python generate_charts.py
```

成功標準：

```text
charts/worst_case_chart.png
charts/average_case_chart.png
```

---

## 3. GitHub 測試方法

GitHub 本身不會自動幫你編譯，除非你設定 GitHub Actions。

最簡單的線上測試方式：

1. GitHub Codespaces
2. Replit
3. OnlineGDB
4. 自己電腦的 VSCode Terminal
5. Windows + MinGW g++
6. WSL Ubuntu

---

## 4. GPT 是否可以編譯？

可以。在有程式執行工具的 ChatGPT 對話中，可以幫你編譯、執行、檢查錯誤。

但最後正式繳交前，仍建議你在自己的電腦或 GitHub Codespaces 再跑一次，因為不同電腦的 CPU、編譯器與作業系統會影響測速結果。
