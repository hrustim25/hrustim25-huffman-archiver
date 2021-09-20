== Нормализация UNIX пути ==

На вход подается текущая директория `current_working_dir` (абсолютный путь, т.е. начинающийся с `/`) и путь `path`, который может быть как абсолютным, так и относительным. Надо вернуть нормализованный абсолютный путь, которому соответсвует `path`.

Нормализация пути заключается в приведении к абсолютному пути и избавлении от следующих элементов:
- `/` в конце пути
- `.` - текущая директория
- `..` - родительская директория
- `//` - равносильно `/`

В случае невалидного пути надо вернуть пустую строку.
Невалидным считается путь, в котором пришлось "подняться" выше корня файловой системы (например, `/..`).

Использовать готовые библиотеки для работы с путями наподобие `std::filesystem::path` нельзя. 