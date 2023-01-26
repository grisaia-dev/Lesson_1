#include <iostream>
#include <fstream>

namespace Memory {
    int *dynamic_array_alloc(unsigned const int* width) {
        int* _array = new int[*width];
        return _array;
    }

    void dynamic_array_free(int* _array) {
        delete[] _array;
    }
}

void fill_array(int* _array, std::ifstream& _file, unsigned int* width) {
    for (unsigned int i = 0; i < *width; ++i) {
        _file >> _array[i];
    }
}

void write_array(int* _array, unsigned const int* width, std::ofstream &_file) {
    _file << *width << "\n";
    for (unsigned int i = 0; i < *width; ++i)
        _file << _array[i] << " ";
    _file << "\n";
}

void shift_left(int *_array, unsigned const int *_width) {
    const int temp = _array[0];
    for (unsigned int i = 0; i < (*_width - 1); ++i)
        _array[i] = _array[i + 1];
    _array[*_width - 1] = temp;
}

void shift_right(int *_array, unsigned const int *_width) {
    const int temp = _array[*_width - 1];
    for (unsigned int i = *_width - 1; i > 0; --i)
        _array[i] = _array[i - 1];
    _array[0] = temp;
}

int main(void) {
    std::ifstream i_file("in.txt");
    std::ofstream o_file("out.txt");

    if (i_file.is_open() && o_file.is_open()) {
        unsigned int width = 0;

        // Работа с первым массивом
        i_file >> width;
        int* num_array1 = Memory::dynamic_array_alloc(&width);
        fill_array(num_array1, i_file, &width);
        shift_left(num_array1, &width);

        unsigned const int temp_width = width; // Хранение размера первого массива

        // Работа с вторым массивом
        i_file >> width;
        int* num_array2 = Memory::dynamic_array_alloc(&width);
        fill_array(num_array2, i_file, &width);
        shift_right(num_array2, &width);

        // Запись массивов и размер массива в файл
        write_array(num_array2, &width, o_file);
        write_array(num_array1, &temp_width, o_file);
        
        // Закрываем файлы
        i_file.close();
        o_file.close();

        // Очищаем память
        Memory::dynamic_array_free(num_array1);
        Memory::dynamic_array_free(num_array2);
    } else {
        std::cout << "File don't open!\n Create file and fill him of data!" << std::endl;
    }
    return 0;
}