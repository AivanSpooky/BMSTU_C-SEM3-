import ctypes
from arr import ArrayApplication
from dialog import LibraryPathDialog

# Главный класс, который запускает второстепенные окна
class MainApplication:
    def __init__(self):
        # Попытка открыть библиотеку по дефолтному пути
        self.lib = None
        self.default_path = "укажите путь: lib/array.so"
        try:
            # Получилось открыть - присваиваем и запускаем ArrayApplication
            lib = ctypes.CDLL(self.default_path)
            self.set_lib(library=lib)
        except Exception:
            # При неудачной попытке загрузить библиотеку - открываем диалоговое окно LibraryPathDialog
            # Там просим пользователя ввести путь к библиотеке самостоятельно
            self.dialog = LibraryPathDialog(default_lib=self.default_path, main_app=self)
            self.dialog.run()

    def set_lib(self, library):
        self.lib = library
        if self.lib:
            app = ArrayApplication(self.lib, self.default_path)
            app.run()

# Запуск приложения
if __name__ == "__main__":
    app = MainApplication()