import tkinter as tk
import ctypes

class LibraryPathDialog(tk.Tk):
    def __init__(self, default_lib, main_app):
        super().__init__()

        self.title("Укажите путь к библиотеке")
        self.main_app = main_app
        self.label = tk.Label(self, text="Путь к библиотеке:")
        self.label.pack()
        
        self.path_entry = tk.Entry(self)
        self.path_entry.pack()
        
        self.confirm_button = tk.Button(self, text="Подтвердить", command=self.get_path)
        self.confirm_button.pack()

        self.error_label = tk.Label(self, text="", fg="red")
        self.error_label.pack()

        self.path_entry.insert(0, default_lib)
        self.get_path()
        
    def load_library(self, path):
        try:
            self.error_label.config(text="")
            self.lib = ctypes.CDLL(path)
            if (self.lib._name == ""):
                raise Exception
            
            # Проверка совпадания прототипов функций

            self.destroy()
            self.main_app.set_lib(self.lib)
        except ReferenceError:
            self.error_label.config(text="Ошибка: прототипы функций библиотеки и приложения не совпадают!")
        except Exception:
            self.error_label.config(text="Ошибка: библиотека не найдена!")

    def get_path(self):
        path = self.path_entry.get()
        self.load_library(path)

    def run(self):
        self.mainloop()
