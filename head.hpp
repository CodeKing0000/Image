#pragma once
#include <iostream>
#include <string>
#include <compare>

enum class MirrorType {
    Vertical,
    Horizontal
};

class Image {

    int rows_;
    int cols_;
    int channels_;
    unsigned char* data_;
    int ref_count_;

public:
    Image(int rows, int cols, int channels, unsigned char* data, int ref_count);

    bool operator<(const Image& other) const {};
    bool operator>(const Image& other) const {};
    bool operator<=(const Image& other) const {};
    bool operator>=(const Image& other) const {};
    bool operator==(const Image& other) const {};

    //конструктор копий. Данный конструктор не выделяет новую память, а применяет технику reference counting. Сложность создания копии объекта O(1).
    Image(const Image& image) {};

    // деструктор
    ~Image();

    //оператор присваивания. В некотором роде похож на конструктор. Т.е. не выделяет новую память, а применяет технику reference counting. Сложность данной операции O(1).
    Image& operator=(const Image& image) {};

    // Вернуть клон изборажения, создает полную копию изображения. Выделяет новую память и производит копирование пикселей. Сложность операции O(n), где n - количество пикселей.
    Image clone() {};

    //Скопировать изображение.
    void copyTo(Image& image) {};

    void create(int obj_rows, int obj_cols, int obj_channels, unsigned char* obj_data, int obj_ref_count) {};

    bool empty() {};

//декрементирует счетчик ссылок и в случае необходимости освобождает ресурсы (память).
    void release() {};

//возвращает новое изображение, которое содержит один столбец по индексу x.
    Image col(int x) {};

//аналог метода col(int x) для строк.
    Image row(int y) {};

    const unsigned char* data() const {};
    unsigned char* data() {};
    int rows() const {};
    int cols() const {};
    int total() const {};
    int channels() const {};

    //Вернуть ЧАСТЬ пикселя
    unsigned char& at(int index) {};
    const unsigned char& at(int index) const {};

//создает новое изображение, которое инициализируется нулями.
    static Image zeros(int rows, int cols, int channels) {};

//создает новое изображение, которое инициализируется значением value.
    Image values(int rows, int cols, int channels, unsigned char* value) {};

    //Отразить изображение по вертикали или по горизонтали
    void Mirror(MirrorType type) {};

    //Повернуть на угол кратный 90
    void Rotate(double angle) {};

    //Возвращает текущее количество ссылок на изображение.
    //Т.е. количество объектов, которые ссылаются на данное изображение. Этот метод нужен для unit test'ов.
    size_t countRef() {};

};
