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

void work_with_array(int* _array1, int* _array2, unsigned int* width, std::ifstream& _file1, std::ofstream& _file2) {
    // Работа с первым массивом
    fill_array(_array1, _file1, width);

    int temp = _array1[0];
    for (unsigned int i = 0; i < (*width - 1); ++i)
        _array1[i] = _array1[i + 1];
    _array1[*width - 1] = temp;

    unsigned const int temp_width = *width; // Хранение размера первого массива

    // Работа над вторым массивом
    _file1 >> *width;
    fill_array(_array2, _file1, width);

    temp = _array2[*width - 1];
    for (unsigned int i = *width - 1; i > 0; --i)
        _array2[i] = _array2[i - 1];
    _array2[0] = temp;

    write_array(_array2, width, _file2); // Записываем второй массив в файл
    write_array(_array1, &temp_width, _file2); // Записываем первый массив в файл

    // Закрываем файлы
    _file1.close();
    _file2.close();
}

int main(void) {
    std::ifstream i_file("in.txt");
    std::ofstream o_file("out.txt");

    if (i_file.is_open() && o_file.is_open()) {
        unsigned int width = 0;

        i_file >> width;
        int* num_array1 = Memory::dynamic_array_alloc(&width);
        int* num_array2 = Memory::dynamic_array_alloc(&width);

        work_with_array(num_array1, num_array2, &width, i_file, o_file);

        Memory::dynamic_array_free(num_array1);
        Memory::dynamic_array_free(num_array2);
    } else {
       
        std::cout << "File don't open!\n Create file and fill him of data!" << std::endl;
    }

    return 0;
}