# Морковный огород

Небольшая игра на C++ и SFML. Подготовьте землю, посадите семена и собирайте урожай.


## Требования

CMake 3.28+, Git, Ninja (обычно в комплекте с Cmake) и компилятор с поддержкой C++17 (g++).

## Сборка и запуск

Важно: при сборке автоматически будут скачаны зависимости SFML 3.0.

Инструкция ддя  Windows:

```powershell
cmake -S . -B build/ninja -G Ninja -DCMAKE_CXX_COMPILER=g++
cmake --build build/ninja --target main
.\build\ninja\bin\main.exe
```

Инструкция ддя  MacOS/Linux:

```bash
cmake -S . -B build/native -G Ninja -DCMAKE_BUILD_TYPE=Release
cmake --build build/native --target main
./build/native/bin/main
```


## Управление

- WASD / стрелки: движение.
- E: подготовить землю, посадить семена или собрать урожай.
- Q: показать или скрыть инвентарь.
- Escape: выход.
