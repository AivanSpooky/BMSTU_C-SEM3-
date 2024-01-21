import ctypes
import tkinter as tk
        
class ArrayApplication(tk.Tk):
    def __init__(self, lib, default_lib):
        super().__init__()

        # self.INT_MAX = 2147483647
        __get_int_max = lib.get_max_int
        __get_int_max.argtypes = ()
        __get_int_max.restype = ctypes.c_int

        self.INT_MAX = __get_int_max()

        # Получаем функции из библиотеки
        self.__fill_arr_with_primes__ = lib.fill_arr_with_primes
        self.__fill_arr_with_primes__.argtypes = (ctypes.POINTER(ctypes.c_int), ctypes.c_size_t)
        self.__fill_arr_with_primes__.restype = ctypes.c_int

        self.__rewrite_arr__ = lib.rewrite_arr
        self.__rewrite_arr__.argtypes = (ctypes.POINTER(ctypes.c_int), ctypes.POINTER(ctypes.c_int), ctypes.c_size_t, ctypes.POINTER(ctypes.c_size_t), ctypes.c_int)
        self.__rewrite_arr__.restype = ctypes.c_int

        # Настройки самого окна
        self.title("Array Application")

        self.array = []
        self.array_size = 0

        self.canvas = tk.Canvas(self, width=400, height=100, highlightthickness=2, highlightbackground="black")
        self.canvas.grid(row=0, column=1, columnspan=3)

        self.error_label = tk.Label(self, text="", fg="red")
        self.error_label.grid(row=1, column=0, columnspan=3)

        self.scrollbar = tk.Scrollbar(self, orient="horizontal", command=self.canvas.xview, width=50)
        self.scrollbar.grid(row=0, column=0)
        self.canvas.configure(xscrollcommand=self.scrollbar.set)

        self.prime_label = tk.Label(self, text="Введите число:", fg="black")
        self.prime_label.grid(row=2, column=0)

        self.entry = tk.Entry(self)
        self.entry.grid(row=2, column=1, sticky="w")

        self.create_array_button = tk.Button(self, text="Создать массив из простых чисел", command=self.create_array)
        self.create_array_button.grid(row=2, column=2, sticky="w")

        self.recreate_array_button = tk.Button(self, text="Добавить число после четных", command=self.recreate_array)
        self.recreate_array_button.grid(row=2, column=3, sticky="w")

        self.entry_elem = tk.Entry(self)
        self.entry_elem.grid(row=0, column=4, sticky="s")

        self.add_elem_to_array_button = tk.Button(self, text="Добавить число", command=self.add_elem_to_array)
        self.add_elem_to_array_button.grid(row=1, column=4, sticky="w")

        self.del_elem_from_array_button = tk.Button(self, text="Удалить число", command=self.del_elem_from_array)
        self.del_elem_from_array_button.grid(row=2, column=4, sticky="w")

    # Функция добавления элемента в массив (питонячее добавление)
    def add_elem_to_array(self):
        try:
            self.elem = int(self.entry_elem.get())
            if (self.elem <= 0):
                self.error_label.config(text="Ошибка! Введите положительное число!")
            elif (self.elem >= self.INT_MAX):
                self.error_label.config(text="Ошибка! Введите число в пределах INT!")
            else:
                try:
                    self.array.append(self.elem)
                    self.draw_array()
                    self.error_label.config(text="")
                except MemoryError:
                    self.error_label.config(text="Ошибка! Не удалось выделить память!")
        except ValueError:
            self.error_label.config(text="Ошибка! Введите целое число!")

    # Функция удаления элемента из массив (питонячее удаление)
    def del_elem_from_array(self):
        try:
            self.elem = int(self.entry_elem.get())
            if (self.elem <= 0):
                self.error_label.config(text="Ошибка! Введите положительное число!")
            elif (self.elem >= self.INT_MAX):
                self.error_label.config(text="Ошибка! Введите число в пределах INT!")
            else:
                try:
                    self.array.remove(self.elem)
                    self.draw_array()
                    self.error_label.config(text="")
                except MemoryError:
                    self.error_label.config(text="Ошибка! Не удалось выделить память!")
                except ValueError:
                    self.error_label.config(text="Ошибка! Не удалось удалить элемент!")
        except ValueError:
            self.error_label.config(text="Ошибка! Введите целое число!")

    def create_array(self):
        try:
            self.array_size = int(self.entry.get())
            if (self.array_size <= 0):
                self.error_label.config(text="Ошибка! Введите положительное число!")
            elif (self.array_size >= self.INT_MAX):
                self.error_label.config(text="Ошибка! Не удалось выделить память!")
            else:
                try:
                    self.array = self.fill_arr_with_primes(self.array_size)
                    self.draw_array()
                    self.error_label.config(text="")
                except MemoryError:
                    self.error_label.config(text="Ошибка! Не удалось выделить память!")
        except ValueError:
            self.error_label.config(text="Ошибка! Введите целое число!")
            
    def recreate_array(self):
        try:
            self.adder = int(self.entry.get())
            if (abs(self.adder) >= self.INT_MAX):
                self.error_label.config(text="Ошибка! Введите число в пределах INT!")
            else:
                try:
                    # Здесь при необходимости можно поменять способ выделения памяти
                    self.array = self.rewrite_arr_2(self.array, self.adder)
                    self.array_size = len(self.array)
                    self.draw_array()
                    self.error_label.config(text="")
                except MemoryError:
                    self.error_label.config(text="Ошибка! Не удалось выделить память!")
        except ValueError:
            self.error_label.config(text="Ошибка! Введите целое число!")

    def fill_arr_with_primes(self, n: int):
        buffer = (ctypes.c_int * n)()
        self.__fill_arr_with_primes__(buffer, n)
        return list(buffer)

    # Первая имплементация выделения памяти под массив
    def rewrite_arr_1(self, src: list[int], number: int):
        old_size = len(src)
        old_buffer = (ctypes.c_int * old_size)(*src)
        # Выделяем память c запасом
        new_size = ctypes.c_size_t(old_size * 2)
        buffer = (ctypes.c_int * new_size.value)()
        # Вызываем функцию
        self.__rewrite_arr__(old_buffer, buffer, old_size, new_size, number)
        # Возвращаем только реальное количество элементов
        return list(buffer)[:new_size.value]
    
    # Вторая имплементация выделения памяти под массив
    def rewrite_arr_2(self, src: list[int], number: int):
        old_size = len(src)
        old_buffer = (ctypes.c_int * old_size)(*src)
        new_size = ctypes.c_size_t(0)
        # Вычимляем размер массива, вызвав функцию в первый раз
        self.__rewrite_arr__(old_buffer, None, old_size, new_size, number)
        # Выделяем память
        buffer = (ctypes.c_int * new_size.value)()
        # Вызываем функцию во второй раз
        self.__rewrite_arr__(old_buffer, buffer, old_size, new_size, number)
        return list(buffer)
    
    # Функция, которая на canvas рисует массив в виде квадратиков
    def draw_array(self):
        self.canvas.delete("all")
        square_size = 30
        x = 2 * (square_size + 10) + 10
        y = 50
        i = 0
        if (len(self.array) > 0):
            self.canvas.create_text(x - square_size, y - square_size/2, text="индекс")
            self.canvas.create_text(x - square_size, y + square_size/2, text="начало")
            for num in self.array:
                self.canvas.create_rectangle(x, y, x + square_size, y + square_size, outline="black")
                self.canvas.create_text(x + square_size/2, y + square_size/2, text=str(num))
                self.canvas.create_text(x + square_size/2, y - square_size/2, text=str(i))
                x += square_size + 10
                i += 1
            self.canvas.create_text(x + square_size, y + square_size/2, text="конец")
    
    def run(self):
        self.mainloop()
