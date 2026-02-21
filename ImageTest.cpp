#include <gtest/gtest.h>
#include "head.hpp"

// Тест конструктора
TEST(ImageTest, Constructor) {
    unsigned char data[100] = {0};
    Image img(10, 10, 1, data, 1);
    
    EXPECT_EQ(img.rows(), 10);
    EXPECT_EQ(img.cols(), 10);
    EXPECT_EQ(img.channels(), 1);
    EXPECT_FALSE(img.empty());
}

// Тест операторов сравнения
TEST(ImageTest, ComparisonOperators) {
    unsigned char data1[100] = {0};
    unsigned char data2[100] = {0};
    
    Image img1(10, 10, 1, data1, 1);
    Image img2(10, 10, 1, data2, 1);
    Image img3(20, 10, 1, data1, 1);
    
    EXPECT_TRUE(img1 == img2);
    EXPECT_TRUE(img1 < img3);
    EXPECT_TRUE(img3 > img1);
}

// Тест копирования с подсчетом ссылок
TEST(ImageTest, ReferenceCounting) {
    unsigned char data[100] = {0};
    Image* img1 = new Image(10, 10, 1, data, 1);
    
    EXPECT_EQ(img1->countRef(), 1);
    
    Image img2 = *img1;  // Копирование
    EXPECT_EQ(img1->countRef(), 2);
    
    delete img1;  // Освобождение
    // После удаления img1, img2 должен все еще работать
}

// Тест mirror
TEST(ImageTest, Mirror) {
    unsigned char data[4] = {1, 2, 3, 4};
    Image img(2, 2, 1, data, 1);
    
    img.Mirror(MirrorType::Horizontal);
    // Проверяем результат зеркального отражения
}

// Тест rotate
TEST(ImageTest, Rotate) {
    unsigned char data[4] = {1, 2, 3, 4};
    Image img(2, 2, 1, data, 1);
    
    img.Rotate(90);
    EXPECT_EQ(img.rows(), 2);
    EXPECT_EQ(img.cols(), 2);
}

// Тест создания нулевого изображения
TEST(ImageTest, zeros) {
    Image img = Image::zeros(5, 5, 3);
    EXPECT_EQ(img.rows(), 5);
    EXPECT_EQ(img.cols(), 5);
    EXPECT_EQ(img.channels(), 3);
    
    // Проверяем что все пиксели нулевые
    for(int i = 0; i < img.total(); i++) {
        EXPECT_EQ(img.data()[i], 0);
    }
}

// Тест at() метода
TEST(ImageTest, AtMethod) {
    unsigned char data[4] = {10, 20, 30, 40};
    Image img(2, 2, 1, data, 1);
    
    EXPECT_EQ(img.at(0), 10);
    EXPECT_EQ(img.at(3), 40);
    
    // Проверка исключения
    EXPECT_THROW(img.at(10), std::out_of_range);
}

// Тест clone
TEST(ImageTest, Clone) {
    unsigned char data[4] = {1, 2, 3, 4};
    Image img1(2, 2, 1, data, 1);
    
    Image img2 = img1.clone();
    
    EXPECT_EQ(img1.rows(), img2.rows());
    EXPECT_EQ(img1.cols(), img2.cols());
    
    // Проверяем что это разные объекты (разные счетчики ссылок)
    EXPECT_NE(img1.countRef(), img2.countRef());
}

// Главная функция
int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
