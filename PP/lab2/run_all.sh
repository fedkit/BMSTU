#!/bin/bash

# Очищаем файл перед запуском
> answer.txt

# Запускаем lab2.py от 1 до 14 процессов
for np in {1..14}; do
    echo "Запуск с $np процессами..."
    mpirun -np $np python3 lab2.py
done



