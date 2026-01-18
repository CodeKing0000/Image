enum class MirrorType {
  Vertical,
  Horizontal
}

class Image {

public:
    Image(int rows, int cols, int channels, unsigned char* data, int ref_count);

    //конструктор копий. Данный конструктор не выделяет новую память, а применяет технику reference counting. Сложность создания копии объекта O(1).
    Image(const Image& image);
    virtual ~Image();

    //оператор присваивания. В некотором роде похож на конструктор. Т.е. не выделяет новую память, а применяет технику reference counting. Сложность данной операции O(1).
    Image& operator=(const Image& image);

    // Вернуть клон изборажения, создает полную копию изображения. Выделяет новую память и производит копирование пикселей. Сложность операции O(n), где n - количество пикселей.
    Image clone() {
        Image a = Image;
        return a;
    };
    //Скопировать изображение.
    void copyTo(Image& image) {
        Image& image = Image; 
    };
    void create(int rows, int cols, int channels);
    bool empty();

    //декрементирует счетчик ссылок и в случае необходимости освобождает ресурсы (память).
    void release();

//возвращает новое изображение, которое содержит один столбец по индексу x.
    Image col(int x);

//аналог метода col(int x) для строк.
    Image row(int y);

    const unsigned char* data() const;
    unsigned char* data();

    int rows() {
        return rows;
    };
    int cols();
    int total();
    int channels();

    //Вернуть ЧАСТЬ пикселя
    unsigned char& at(int index);
    const unsigned char& at(int index) const;

//создает новое изображение, которое инициализируется нулями.
    Image zeros(int rows, int cols, int channels);

//создает новое изображение, которое инициализируется значением value.
    Image values(int rows, int cols, int channels, unsigned char value);

    //Отразить изображение по вертикали или по горизонтали
    void Mirror(MirrorType type);

    //Повернуть на угол кратный 90
    void Rotate(double angle) {
        int count = angle / 90;

    };

    //Возвращает текущее количество ссылок на изображение.
    //Т.е. количество объектов, которые ссылаются на данное изображение. Этот метод нужен для unit test'ов.
    size_t countRef(std::string obj) {
        return obj.ref_count;
    };
};