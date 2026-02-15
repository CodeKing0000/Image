#include <iostream>
#include <string>
#include <stdexcept>
#include <algorithm>
#include "head.hpp"

    Image::Image(int rows, int cols, int channels, unsigned char* data, int ref_count) {};

    bool Image::operator<(const Image& other) const {
        if (rows_ != other.rows_) {
            return rows_ < other.rows_;
        };
        if (cols_ != other.cols_) {
            return cols_ < other.cols_;
        };
        if (channels_ != other.channels_) {
            return channels_ < other.channels_;
        };
        return data_ < other.data_;
    };
    bool Image::operator>(const Image& other) const {
        if (rows_ != other.rows_) {
            return rows_ > other.rows_;
        };
        if (cols_ != other.cols_) {
            return cols_ > other.cols_;
        };
        if (channels_ != other.channels_) {
            return channels_ > other.channels_;
        };
        return data_ > other.data_;
    };
    bool Image::operator<=(const Image& other) const {
        if (rows_ != other.rows_) {
            return rows_ <= other.rows_;
        };
        if (cols_ != other.cols_) {
            return cols_ <= other.cols_;
        };
        if (channels_ != other.channels_) {
            return channels_ <= other.channels_;
        };
        return data_ <= other.data_;
    };
    bool Image::operator>=(const Image& other) const {
        if (rows_ != other.rows_) {
            return rows_ >= other.rows_;
        };
        if (cols_ != other.cols_) {
            return cols_ >= other.cols_;
        };
        if (channels_ != other.channels_) {
            return channels_ >= other.channels_;
        };
        return data_ >= other.data_;
    };
    bool Image::operator==(const Image& other) const {
        return rows_ == other.rows_ && cols_ == other.cols_ && data_ == other.data_ && channels_ == other.channels_;
    };

    //конструктор копий. Данный конструктор не выделяет новую память, а применяет технику reference counting. Сложность создания копии объекта O(1).
    Image::Image(const Image& image) {
        rows_ = image.rows_;
        cols_ = image.cols_;
        channels_ = image.channels_;
        data_ = image.data_;
        ref_count_ = image.ref_count_;
        (ref_count_)++;
    };

    //оператор присваивания. В некотором роде похож на конструктор. Т.е. не выделяет новую память, а применяет технику reference counting. Сложность данной операции O(1).
    Image& Image::operator=(const Image& image) {
        if(*this == image) {
            return *this;
        }

        if(ref_count_ != 0) {
        (ref_count_)--;

            if(ref_count_ == 0) {
                rows_ = 0;
                cols_ = 0;
                channels_ = 0;
                data_ = 0;
                ref_count_ = 0;
            }
        }
        
        rows_ = image.rows_;
        cols_ = image.cols_;
        channels_ = image.channels_;
        data_ = image.data_;
        ref_count_ = image.ref_count_;

        (ref_count_)++;
    };

    // Вернуть клон изборажения, создает полную копию изображения. Выделяет новую память и производит копирование пикселей. Сложность операции O(n), где n - количество пикселей.
    Image Image::clone() {
        Image clone = *this;
        (ref_count_)++;
        return clone;
    };

    //Скопировать изображение.
    void Image::copyTo(Image& image) {
        Image clone = *this;
        (ref_count_)++; 
    };

    void Image::create(int obj_rows, int obj_cols, int obj_channels, unsigned char* obj_data, int obj_ref_count) {
        rows_ = obj_rows;
        cols_ = obj_cols;
        channels_ = obj_channels;
        data_ = obj_data;
        ref_count_ = obj_ref_count;
    };

    bool Image::empty() {
        if(rows_ == 0, cols_ == 0, channels_ == 0, data_ == 0) {
            return true;
        }
        return false;
    };

    //декрементирует счетчик ссылок и в случае необходимости освобождает ресурсы (память).
    void Image::release() {
        if(ref_count_ != 0 && ref_count_ > 1) {
        (ref_count_)--;
        }
            rows_ = 0;
            cols_ = 0;
            channels_ = 0;
            data_ = 0;
            ref_count_ = 0;

    };

//возвращает новое изображение, которое содержит один столбец по индексу x.
    Image Image::col(int x) {
        this->cols_ = 1;
    };

//аналог метода col(int x) для строк.
    Image Image::row(int y) {
        this->rows_ = 1;
    };

    const unsigned char* Image::data() const {
        return data_;
    };
    unsigned char* Image::data() {
        return data_;
    };
    int Image::rows() {
        return rows_;
    };
    int Image::cols() {
        return cols_;
    };
    int Image::total() {
        return rows_, cols_, channels_, data_, ref_count_;
    };
    int Image::channels() {
        return channels_;
    };

    //Вернуть ЧАСТЬ пикселя
    unsigned char& Image::at(int index) {
        if(index < 0 || index > 255) {
            throw std::out_of_range("Unsigned char& at(int index) > 255 or < 0");
        }

        return data_[index];
    };
    const unsigned char& Image::at(int index) const {
        if(index < 0 || index > 255) {
            throw std::out_of_range("Const unsigned char& at(int index) const > 255 or < 0");
        }

        return data_[index];
    };

//создает новое изображение, которое инициализируется нулями.
    Image Image::zeros(int rows, int cols, int channels) {
        Image a(rows_, cols_, channels_, 0, 0);
        return a;
    };

//создает новое изображение, которое инициализируется значением value.
    Image Image::values(int rows, int cols, int channels, unsigned char* value) {
        Image a(rows_, cols_, channels_, value, 0);
        return a;
    };

    //Отразить изображение по вертикали или по горизонтали
    void Image::Mirror(MirrorType type) {
        if(type == MirrorType::Vertical) {
            for (int y = 0; y < rows_; ++y) {
                for (int x = 0; x < cols_ / 2; ++x) {
                    int x1 = (y * cols_ + x) * channels_;
                    int x2 = (y * cols_ + (this->cols_ - 1 - x)) * channels_;
                    for (int c = 0; c < channels_; ++c) {
                        unsigned char temp = data_[x1 + c];
                        data_[x1 + c] = data_[x2 + c];
                        data_[x2 + c] = temp;
                    }
                }
            }
        };
        if(type == MirrorType::Horizontal) {
            int rowSize = cols_ * channels_;
            unsigned char* tempRow = new unsigned char [rowSize];

            for (int y = 0; y < rows_ / 2; ++y) {
                unsigned char* rowTop = &data_[y * rowSize];
                unsigned char* rowBottom = &data_[(this->rows_ - 1 - y) * rowSize];
                std::swap_ranges(rowTop, rowTop + rowSize, rowBottom);
            }
        };
    };
    //Повернуть на угол кратный 90
    void Image::Rotate(double angle) {
        int count = angle / 90;
        while(count > 0) {
            int a = rows_;
            rows_ = cols_;
            cols_ = a;
            count--;
        }
    };

    //Возвращает текущее количество ссылок на изображение.
    //Т.е. количество объектов, которые ссылаются на данное изображение. Этот метод нужен для unit test'ов.
    size_t Image::countRef(Image obj) {
        return obj.ref_count_;
    };
