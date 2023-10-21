#!/bin/bash

# Имя исполняемого файла
output_file="my_program"

# Компиляция всех файлов .cpp в текущем каталоге
g++ *.cpp -o "$output_file"

# Проверка успешности компиляции
if [ $? -eq 0 ]; then
  echo "Компиляция завершена успешно. Выполните ./$output_file для запуска программы."
else
  echo "Компиляция завершилась с ошибками."
fi
