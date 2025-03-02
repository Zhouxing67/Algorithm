g++ -std=c++17 *.cpp  -o app
chcp 65001
app
cd ./data
:: python compare.py
C:\Windows\System32\fc.exe data.txt expand.txt
cd ..